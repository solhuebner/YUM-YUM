#include "Arduino.h"
#include "assets.h"
#include "game.h"
#include "map_renderer.h"

#define TILE_X_SIZE 20
#define TILE_Y_SIZE 18

#define TILE_X_OFFSET 15
#define TILE_Y_OFFSET 9

// display hardware is global
extern Arduboy AB;
extern Sprites sprites;
extern Character player;
extern Ghost ghosts[];


const unsigned char* const tiles[4] PROGMEM = {
  NULL, // blank
  wall_TL_plus_mask, // wall
  small_ball_plus_mask,  // dot
  NULL
};


MapRenderer::MapRenderer(Map &map, Game &game)
{
  this->map = &map;
  this->game = &game;
  viewport_x = 0;
  viewport_y = 0;
}

// 0 - 14 (7) LR
// 0 - 8 (4) UD
void MapRenderer::getRenderOffset(Character obj, Vector &v)
{
  switch (obj.direction) {
    case Up:
      v.y = +4 - obj.fractional / 2;
      v.x = -7 + obj.fractional;
      break;
    case Down:
      v.y = -4 + obj.fractional / 2;
      v.x = +7 - obj.fractional;
      break;
    case Left:
      v.x = -1 * obj.fractional;
      v.y = 0; // no offset needed for left/right movement
      break;
    case Right:
      v.x = obj.fractional;
      v.y = 0; // no offset needed for left/right movement
      break;
    case None:
    default:
      // should be the middle position (as it appears on the grid)
      v.x = 0;
      v.y = 0;
  }
}

// 0 - 14 (7)
// 0 - 8 (4)
#define PACMAN_WIDTH 16
#define PACMAN_HEIGHT 16
void MapRenderer::renderPlayer(Character player, int screen_x, int screen_y)
{
  Vector v;
  int8_t x, y;

  getRenderOffset(player, v);
  x = screen_x;
  y = screen_y;

  sprites.drawBitmap(
    x + v.x + 4,
    y + v.y,
    YumYum16x16_plus_mask, NULL, PACMAN_WIDTH, PACMAN_HEIGHT, SPRITE_PLUS_MASK
    );
}

void MapRenderer::renderGhost(Ghost ghost, int screen_x, int screen_y)
{
  Vector v;
  int8_t x, y;

  getRenderOffset(ghost, v);
  x = screen_x;
  y = screen_y;

  sprites.drawBitmap(
    // offsets have to do with size/height of ghost and making it look
    // proper when rendered in the context of the map
    x + v.x + 4,
    y + v.y - 1,
    big_ball_plus_mask, NULL, 20, 18, SPRITE_PLUS_MASK
    );
}

void MapRenderer::renderTile(uint8_t grid_x, uint8_t grid_y,
  int screen_x, int screen_y)
{
  uint8_t look_ahead_right;
  uint8_t look_ahead_bottom;

  uint8_t tile_id;
  uint8_t render_height;
  unsigned char* tile;


  tile_id = map->objectAt(grid_x,grid_y);
  look_ahead_right = map->objectAt(grid_x+1,grid_y);
  look_ahead_bottom = map->objectAt(grid_x,grid_y+1);
  // render_height=18;

  if (look_ahead_right == WALL && look_ahead_bottom==WALL) {
    render_height=9;
  } else {
    render_height=18;
  }
  if (tile_id==DOT) {
    render_height=8;
  }

  if (tile_id==EMPTY || tile_id==OFF_GRID) {
    // nother needs to be rendered in these cases
  } else {
    tile = (unsigned char*)pgm_read_word(tiles+tile_id);
    // render tile at screen_x, screen_y
    // AB.fillScreen(WHITE);
    sprites.drawBitmap(screen_x, screen_y,
      tile, NULL, 20, render_height, SPRITE_PLUS_MASK
      // tile, tile_mask, 20, render_height, SPRITE_MASKED
      );
    // delay(300);
    // AB.display();
  }
  // render ghosts and player
  if (player.x == grid_x && player.y == grid_y) {
    renderPlayer(player, screen_x, screen_y);
  }

  for (int i=0; i < GHOST_COUNT; i++) {
    if (ghosts[i].x == grid_x && ghosts[i].y == grid_y) {
      renderGhost(ghosts[i], screen_x, screen_y);
    }
  }
}



void MapRenderer::autoCenter()
{
  Vector offset;
  getRenderOffset(player, offset);

  // the basic grid positioning, player in center
  start_x = player.x - 5;
  start_y = player.y - 4;

  // set base value for the rendering viewport
  viewport_x = -(TILE_X_SIZE / 2);
  viewport_y = -(TILE_Y_SIZE / 2);

  // take the player render offset into consideration
  viewport_x -= offset.x;
  viewport_y -= offset.y;
}



void MapRenderer::render()
{
  uint8_t render_h = 8;
  uint8_t render_w = 11;

  int screen_x = viewport_x;
  int screen_y = viewport_y;
  // now set start x, start y based on viewport

  // AB.setCursor(0, 0);
  for (int8_t y = start_y; y < start_y + render_h; y++) {
    for (int8_t x = start_x; x < start_x + render_w; x++) {

      renderTile(x, y, screen_x, screen_y);

      // move on for next tile
      screen_x += TILE_X_OFFSET;
    }
    screen_y += TILE_Y_OFFSET;
    // rewind x for next pass
    screen_x -= TILE_X_OFFSET*(render_w)+4;
  }

}

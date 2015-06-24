#include "Arduino.h"
#include "sprites.h"
#include "assets.h"
#include "game.h"
#include "map_renderer.h"


// display hardware is global
extern Arduboy AB;
extern Sprites sprites;
extern Character player;
extern Ghost ghosts[];

const unsigned char* const tiles[3] PROGMEM = {
  NULL, // blank
  wall_TL, // wall
  small_ball,  // dot

};

const unsigned char* const tile_masks[3] PROGMEM = {
  NULL,
  wall_TL_mask,
  small_ball_mask
};


MapRenderer::MapRenderer(Map &map, Game &game)
{
  this->map = &map;
  this->game = &game;
  viewport_x = 0;
  viewport_y = 0;
}

void MapRenderer::renderPlayer(int screen_x, int screen_y)
{
  int8_t x, y;
  x = screen_x;
  y = screen_y;
  // calculate offset from minor movevment and direction

  sprites.drawBitmap(screen_x, screen_y,
    YumYum16x16, YumYum16x16_mask, 20, 18, SPRITE_MASKED
    );
}

void MapRenderer::renderGhost(int screen_x, int screen_y)
{
  int8_t x, y;
  x = screen_x;
  y = screen_y;
  // calculate offset from minor movevment and direction

  sprites.drawBitmap(screen_x, screen_y,
    big_ball, big_ball_mask, 20, 18, SPRITE_MASKED
    );
}

#define TILE_X_OFFSET 15
#define TILE_Y_OFFSET 9

void MapRenderer::render()
{
  AB.clearDisplay();
  uint8_t render_h = 8;
  uint8_t render_w = 11;
  uint8_t start_x = 0;
  uint8_t start_y = 0;

  int screen_x = viewport_x;
  int screen_y = viewport_y;
  // now set start x, start y based on viewport

  // AB.setCursor(0, 0);
  uint8_t look_ahead_right;
  uint8_t look_ahead_bottom;

  uint8_t tile_id;
  uint8_t render_height;
  unsigned char* tile;
  unsigned char* tile_mask;
  for (uint8_t y = start_y; y< render_h; y++) {
    for (uint8_t x = start_x; x < render_w; x++) {
      tile_id = map->objectAt(x,y);
      look_ahead_right = map->objectAt(x+1,y);
      look_ahead_bottom = map->objectAt(x,y+1);
      if (look_ahead_right == WALL && look_ahead_bottom==WALL) {
      // if (look_ahead_right == WALL) {
        render_height=6;
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
        tile_mask = (unsigned char*)pgm_read_word(tile_masks+tile_id);
        // render tile at screen_x, screen_y
        // AB.fillScreen(WHITE);
        sprites.drawBitmap(screen_x, screen_y,
          tile, tile_mask, 20, render_height, SPRITE_MASKED
          // tile, tile_mask, 20, render_height, SPRITE_MASKED
          );
        // delay(300);
        // AB.display();
      }
      // render ghosts and player
      if (player.x == x && player.y == y) {
        renderPlayer(screen_x, screen_y);
      }

      for (int i=0; i < GHOST_COUNT; i++) {
        if (ghosts[i].x == screen_x && ghosts[i].y == screen_y) {
          renderGhost(screen_x, screen_y);
        }
      }

      // AB.print(tile_id);

      // move on for next tile
      screen_x += TILE_X_OFFSET;
    }
    // AB.println();
    screen_y += TILE_Y_OFFSET;
    // rewind x for next pass
    screen_x -= TILE_X_OFFSET*(render_w)+4;
  }

}

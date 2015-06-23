#include "Arduino.h"
#include "sprites.h"
#include "assets.h"
#include "map_renderer.h"

#define TILE_X_OFFSET 15
#define TILE_Y_OFFSET 9

// display hardware is global
extern Sprites sprites;

const unsigned char* const tiles[3] PROGMEM = {
	NULL, // blank
	wall_TL, // wall
	small_ball,  // dot

};

const unsigned char* const tile_masks[3] PROGMEM = {
	NULL,
	wall_TL,
	small_ball
};


MapRenderer::MapRenderer(Map &map, Game &game)
{
	this->map = &map;
	this->game = &game;
	viewport_x = 0;
	viewport_y = 0;
}

void MapRenderer::render()
{
	uint8_t render_h = 9;
	uint8_t render_w = 17;
	uint8_t start_x = 0;
	uint8_t start_y = 0;

	int screen_x = viewport_x;
	int screen_y = viewport_y;
	// now set start x, start y based on viewport


	uint8_t tile_id;
	unsigned char* tile;
	unsigned char* tile_mask;
	for (uint8_t y = start_y; y< render_h; y++) {
		for (uint8_t x = start_x; x < render_w; x++) {
			tile_id = map->objectAt(x,y);

			// nother needs to be rendered in these cases
			if (tile_id==EMPTY || tile_id==OFF_GRID)
				continue;

			tile = (unsigned char*)tiles[tile_id];
			tile_mask = (unsigned char*)tile_masks[tile_id];
			// render tile at screen_x, screen_y
			sprites.drawBitmap(screen_x, screen_y,
				tile, tile_mask, 20, 18, SPRITE_MASKED
				);

			// move on for next tile
			screen_x += TILE_X_OFFSET;
		}
		screen_y += TILE_Y_OFFSET;
		// rewind x for next pass
		screen_x -= TILE_X_OFFSET*(render_w) - 5;
	}
}

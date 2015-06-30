#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H

#include "sprites.h"
#include "game.h"
#include "map.h"


class MapRenderer
{
public:
	// MapRenderer();
	MapRenderer(Map &map, Game &game);

	void autoCenter();
	void render();

	void renderPlayer(Character player, int screen_x, int screen_y);
	void renderGhost(Ghost ghost, int screen_x, int screen_y);
	void renderTile(uint8_t grid_x, uint8_t grid_y, int screen_x, int screen_y);
	void getRenderOffset(Character obj, Vector &v);

	Map *map;
	Game *game;
	unsigned char *buffer;

	int viewport_x;
	int viewport_y;
	int start_x;
	int start_y;

};

#endif

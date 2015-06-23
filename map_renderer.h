#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H


#include "game.h"
#include "map.h"

class MapRenderer
{
public:
	// MapRenderer();
	MapRenderer(Map &map, Game &game);

	void render();

	Map *map;
	Game *game;
	unsigned char *buffer;

	int viewport_x;
	int viewport_y;
};

#endif

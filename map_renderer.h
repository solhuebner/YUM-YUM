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
	void renderPlayer(int screen_x, int screen_y);
	void renderGhost(int screen_x, int screen_y);

	Map *map;
	Game *game;
	unsigned char *buffer;

	int viewport_x;
	int viewport_y;
};

#endif

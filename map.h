#ifndef MAP_H
#define MAP_H

#include "Arduino.h"


// types of tiles
#define EMPTY 0
#define WALL 1
#define DOT 2
#define FRUIT 3
#define POWERUP 3
#define OFF_GRID 255

// types of fruit, also tile types
#define NONE 0
#define APPLE 10
#define CHERRY 11
#define STRAWBERRY 12


struct Item
{
public:
	uint8_t kind;
	uint8_t x;
	uint8_t y;
	boolean eaten = false;
	void eat();
};

class Map
{
	public:
	Map();

	void setObjectAt(int8_t x, int8_t y, uint8_t id);
	void removeObjectAt(uint8_t x, uint8_t y);
	uint8_t objectAt(int8_t x, int8_t y);
	void eatDot(int8_t x, int8_t y);
	boolean complete();
	void prepareFromFlash(const char *map);
	void reset();

	uint8_t ghost_start_x;
	uint8_t ghost_start_y;
	uint8_t player_start_x;
	uint8_t player_start_y;
	Item treats[10]; // maximum 10 treats
	int	 dots_left;

private:
	uint8_t width;
	uint8_t height;
	int starting_dots;
	uint8_t grid[32*32/4];
	const char *map_ptr;

};

#endif

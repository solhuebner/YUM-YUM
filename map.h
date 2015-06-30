#ifndef MAP_H
#define MAP_H

#include "Arduino.h"

// types of fruit
#define NONE 0
#define APPLE 1
#define CHERRY 2
#define STRAWBERRY 3

// types of tiles
#define EMPTY 0
#define WALL 1
#define DOT 2
#define FRUIT 3
#define POWERUP 4
#define OFF_GRID 255


// #define YUMMY_DOT 5

struct Treat
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

	uint8_t width;
	uint8_t height;
	uint8_t player_start_x;
	uint8_t player_start_y;
	uint8_t ghost_start_x;
	uint8_t ghost_start_y;
	int starting_dots;
	int	 dots_left;
	Treat treats[10]; // maximum 10 treats


	uint8_t grid[24*24];

};

#endif

#include "map.h"

Map::Map() {
	// zero out our arrays
	memset(treats, 0, sizeof(treats)+sizeof(grid));
}

void Map::prepareFromFlash(const char *map)
{

}


boolean Map::complete()
{
	return !dots_left;
}

void Map::removeObjectAt(uint8_t x, uint8_t y)
{
	setObjectAt(x,y, EMPTY);
}

void Map::setObjectAt(int8_t x, int8_t y, uint8_t id)
{
	if (objectAt(x,y)==OFF_GRID)
		return;

	grid[y*width+x] = id;
}

uint8_t Map::objectAt(int8_t x, int8_t y)
{
	if (x<0 ||
		y<0 ||
		x>width ||
		y>height)
		return OFF_GRID;
	return grid[y*width+x];
}

void Treat::eat()
{
	eaten=true;
}

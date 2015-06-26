#include "map.h"
#include "maps.h"

Map::Map() {
	// zero out our arrays
	memset(treats, 0, sizeof(treats)+sizeof(grid));
}

void Map::prepareFromFlash(const char *map)
{
	uint8_t num_treats;
	width = pgm_read_byte(map);
	height = pgm_read_byte(map+1);
	num_treats = pgm_read_byte(map+TREAT_COUNT_OFFSET);

	starting_dots = 0;

	memcpy_P(this, map, 6);
	memcpy_P(this->treats, map + TREATS_OFFSET, 3 * num_treats);

	int map_size = width * height;
	uint8_t grid_offset = TREATS_OFFSET + (3 * num_treats);
	memcpy_P(this->grid, map + grid_offset, map_size );

	// TODO: use helpers vs direct access
	for (int x=0; x < map_size; x++) {
		if (this->grid[x] == DOT)
			starting_dots++;
	}
	dots_left = starting_dots;
}

void Map::reset()
{
	//TODO : dry
	int map_size = width * height;
	dots_left = starting_dots;
	// num_treats = pgm_read_byte(map+TREAT_COUNT_OFFSET);
	// uint8_t grid_offset = TREATS_OFFSET + 1 + (3 * num_treats);
	// memcpy_P(this->grid, map + grid_offset, map_size );
}


boolean Map::complete()
{
	return !dots_left;
}

void Map::eatDot(int8_t x, int8_t y)
{
	if (!objectAt(x,y)==DOT)
		return;

	removeObjectAt(x,y);
	dots_left--;
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

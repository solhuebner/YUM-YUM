#include "map.h"
#include "maps.h"

Map::Map() {
	// zero out our arrays
	memset(treats, 0, sizeof(treats)+sizeof(grid));
}

void Map::prepareFromFlash(const char *map)
{
	map_ptr = map;
	width = pgm_read_byte(map);
	height = pgm_read_byte(map+1);

	reset();
}

void Map::reset()
{
	uint8_t num_treats;
	unsigned int map_size;
	char *map = (char*)map_ptr;

	memcpy_P(this, map, MAP_HEADER_SIZE);
	num_treats = pgm_read_byte(map+TREAT_COUNT_OFFSET);
	memcpy_P(this->treats, map + TREATS_OFFSET, 3 * num_treats);

	map_size = width * height;
	map_size = map_size/4 + (map_size%4 == 0 ? 0 : 1);
	uint8_t grid_offset = TREATS_OFFSET + (3 * num_treats);
	memcpy_P(this->grid, map + grid_offset, map_size );

	starting_dots = 0;
	for (uint8_t x=0; x < width; x++) {
		for (uint8_t y=0; y < height; y++) {
			if (objectAt(x,y)==DOT)
				starting_dots++;
		}
	}
	dots_left = starting_dots;
}


boolean Map::complete()
{
	return !dots_left;
}

bool edible(uint8_t obj)
{
	return (obj==DOT || obj==FRUIT || obj==POWERUP);
}

void Map::eatDot(int8_t x, int8_t y)
{
	uint8_t obj = objectAt(x,y);
	if (!edible(obj))
		return;

	removeObjectAt(x,y);

	if (obj==DOT) {
		dots_left--;
	}
}

void Map::removeObjectAt(uint8_t x, uint8_t y)
{
	setObjectAt(x,y, EMPTY);
}

void Map::setObjectAt(int8_t x, int8_t y, uint8_t id)
{
	if (objectAt(x,y)==OFF_GRID)
		return;

	// grid[y*width+x] = id;
	int pos;
	uint8_t mask, shift, indx;
	pos = y*width+x;
	shift = ((pos%4)*2);
	mask = ~(0x03 << shift);
	indx = pos/4;
	this->grid[indx] &= mask;
	this->grid[indx] |= ((id & 0x03) << shift);
}

uint8_t Map::objectAt(int8_t x, int8_t y)
{
	if (x<0 ||
		y<0 ||
		x>width ||
		y>height)
		return OFF_GRID;

	int pos;
	pos = y*width+x;
	return (grid[pos/4] >> ((pos%4)*2)) & 0x03;
}

void Item::eat()
{
	eaten=true;
}

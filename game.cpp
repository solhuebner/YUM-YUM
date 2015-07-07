#include "game.h"

Vector direction_vectors[5] = {
	{.x = 0, .y = 0},  // none
	{.x = 0, .y = -1}, // up
	{.x = 0, .y = 1},  // down
	{.x = 1, .y = 0},  // right
	{.x = -1, .y = 0}, // left
};


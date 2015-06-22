#ifndef MAPS_H
#define MAPS_H

#define _ 0
#define W 1
#define o 2
#define T 3

// 15x15 grid
PROGMEM const char map_intro[] = {
	16,16, // size of map
	7, 9, // start, beneath ghost cage
	7, 7, // ghosts start
	5, // treats
	APPLE, 1, 1,
	CHERRY, 1, 1,
	STRAWBERRY, 1, 1,
	STRAWBERRY, 1, 1,
	STRAWBERRY, 1, 1,
	W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,_,
	W,o,o,o,_,o,o,o,o,o,_,o,o,o,W,_,
	W,o,W,o,W,o,W,W,W,o,W,o,W,o,W,_,
	W,o,W,o,o,o,W,_,W,o,o,o,W,o,W,_,
	W,o,W,W,W,_,W,W,W,_,W,W,W,o,W,_,
	W,o,_,_,_,_,_,_,_,_,_,_,_,o,W,_,
	W,o,W,W,_,W,W,_,W,W,_,W,W,o,W,_,
	W,o,_,_,_,W,_,_,_,W,_,_,_,o,W,_,
	W,o,W,W,_,W,W,W,W,W,_,W,W,o,W,_,
	W,o,_,_,_,_,_,_,_,_,_,_,_,o,W,_,
	W,o,W,W,W,_,W,W,W,_,W,W,W,o,W,_,
	W,o,W,o,o,o,W,_,W,o,o,o,W,o,W,_,
	W,o,W,o,W,o,W,W,W,o,W,o,W,o,W,_,
	W,o,o,o,_,o,o,o,o,o,_,o,o,o,W,_,
	W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,_,
	_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
};

#endif

#ifndef MAPS_H
#define MAPS_H

#define _ 0
#define W 1
#define o 2
#define T 3

#define MAP_HEADER_SIZE 6
#define TREAT_COUNT_OFFSET 6
#define TREATS_OFFSET 7

// me = mapencode
#define me4(b1,b2,b3,b4) ((b4 << 6) + (b3 << 4) + (b2 << 2) + b1)
	// b1, b2, b3, b4
#define me8(b1,b2,b3,b4,b5,b6,b7,b8) \
	me4(b1, b2, b3, b4), me4(b5, b6, b7, b8)
#define me16(b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16) \
	me8(b1, b2, b3, b4, b5, b6, b7, b8), \
	me8(b9,b10,b11,b12,b13,b14,b15,b16)
#define me(b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16, \
	b17,b18,b19,b20,b21,b22,b23,b24,b25,b26,b27,b28,b29,b30,b31,b32) \
		me8(b1, b2, b3, b4, b5, b6, b7, b8), \
		me8(b9,b10,b11,b12,b13,b14,b15,b16), \
		me8(b17,b18,b19,b20,b21,b22,b23,b24), \
		me8(b25,b26,b27,b28,b29,b30,b31,b32)


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
	me16(W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,_),
	me16(W,2,2,2,_,2,2,2,2,2,_,2,2,2,W,_),
	me16(W,2,W,2,W,2,W,W,W,2,W,2,W,2,W,_),
	me16(W,2,W,2,2,2,W,_,W,2,2,2,W,2,W,_),
	me16(W,2,W,W,W,_,W,W,W,_,W,W,W,2,W,_),
	me16(W,2,_,_,_,_,_,_,_,_,_,_,_,2,W,_),
	me16(W,2,W,W,_,W,W,_,W,W,_,W,W,2,W,_),
	me16(W,2,_,_,_,W,_,_,_,W,_,_,_,2,W,_),
	me16(W,2,W,W,_,W,W,W,W,W,_,W,W,2,W,_),
	me16(W,2,_,_,_,_,_,_,_,_,_,_,_,2,W,_),
	me16(W,2,W,W,W,_,W,W,W,_,W,W,W,2,W,_),
	me16(W,2,W,2,2,2,W,_,W,2,2,2,W,2,W,_),
	me16(W,2,W,2,W,2,W,W,W,2,W,2,W,2,W,_),
	me16(W,2,2,2,_,2,2,2,2,2,_,2,2,2,W,_),
	me16(W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,_),
	me16(_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_)
};

PROGMEM const char pacman_map[] = {
	32, 31, // size of map
	14, 23, // start, beneath ghost cage
	14, 14, // ghosts start
	5, // treats
	APPLE, 1, 1,
	CHERRY, 1, 1,
	STRAWBERRY, 1, 1,
	STRAWBERRY, 1, 1,
	STRAWBERRY, 1, 1,
	me(W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,_,_,_,_),
	me(W,2,2,2,2,2,2,2,2,2,2,2,2,W,W,2,2,2,2,2,2,2,2,2,2,2,2,W,_,_,_,_),
	me(W,2,W,W,W,W,2,W,W,W,W,W,2,W,W,2,W,W,W,W,W,2,W,W,W,W,2,W,_,_,_,_),
	me(W,T,W,_,_,W,2,W,_,_,_,W,2,W,W,2,W,_,_,_,W,2,W,_,_,W,T,W,_,_,_,_),
	me(W,2,W,W,W,W,2,W,W,W,W,W,2,W,W,2,W,W,W,W,W,2,W,W,W,W,2,W,_,_,_,_),
	me(W,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,W,_,_,_,_),
	me(W,2,W,W,W,W,2,W,W,2,W,W,W,W,W,W,W,W,2,W,W,2,W,W,W,W,2,W,_,_,_,_),
	me(W,2,W,W,W,W,2,W,W,2,W,W,W,W,W,W,W,W,2,W,W,2,W,W,W,W,2,W,_,_,_,_),
	me(W,2,2,2,2,2,2,W,W,2,2,2,2,W,W,2,2,2,2,W,W,2,2,2,2,2,2,W,_,_,_,_),
	me(W,W,W,W,W,W,2,W,W,W,W,W,_,W,W,_,W,W,W,W,W,2,W,W,W,W,W,W,_,_,_,_),
	me(_,_,_,_,_,W,2,W,W,W,W,W,_,W,W,_,W,W,W,W,W,2,W,_,_,_,_,_,_,_,_,_),
	me(_,_,_,_,_,W,2,W,W,_,_,_,_,_,_,_,_,_,_,W,W,2,W,_,_,_,_,_,_,_,_,_),
	me(_,_,_,_,_,W,2,W,W,_,W,W,W,_,_,W,W,W,_,W,W,2,W,_,_,_,_,_,_,_,_,_),
	me(W,W,W,W,W,W,2,W,W,_,W,_,_,_,_,_,_,W,_,W,W,2,W,W,W,W,W,W,_,_,_,_),
	me(_,_,_,_,_,_,2,_,_,_,W,_,_,_,_,_,_,W,_,_,_,2,_,_,_,_,_,_,_,_,_,_),
	me(W,W,W,W,W,W,2,W,W,_,W,_,_,_,_,_,_,W,_,W,W,2,W,W,W,W,W,W,_,_,_,_),
	me(_,_,_,_,_,W,2,W,W,_,W,W,W,W,W,W,W,W,_,W,W,2,W,_,_,_,_,_,_,_,_,_),
	me(_,_,_,_,_,W,2,W,W,_,_,_,_,_,_,_,_,_,_,W,W,2,W,_,_,_,_,_,_,_,_,_),
	me(_,_,_,_,_,W,2,W,W,_,W,W,W,W,W,W,W,W,_,W,W,2,W,_,_,_,_,_,_,_,_,_),
	me(W,W,W,W,W,W,2,W,W,_,W,W,W,W,W,W,W,W,_,W,W,2,W,W,W,W,W,W,_,_,_,_),
	me(W,2,2,2,2,2,2,2,2,2,2,2,2,W,W,2,2,2,2,2,2,2,2,2,2,2,2,W,_,_,_,_),
	me(W,2,W,W,W,W,2,W,W,W,W,W,2,W,W,2,W,W,W,W,W,2,W,W,W,W,2,W,_,_,_,_),
	me(W,2,W,W,W,W,2,W,W,W,W,W,2,W,W,2,W,W,W,W,W,2,W,W,W,W,2,W,_,_,_,_),
	me(W,T,2,2,W,W,2,2,2,2,2,2,2,_,_,2,2,2,2,2,2,2,W,W,2,2,T,W,_,_,_,_),
	me(W,W,W,2,W,W,2,W,W,2,W,W,W,W,W,W,W,W,2,W,W,2,W,W,2,W,W,W,_,_,_,_),
	me(W,W,W,2,W,W,2,W,W,2,W,W,W,W,W,W,W,W,2,W,W,2,W,W,2,W,W,W,_,_,_,_),
	me(W,2,2,2,2,2,2,W,W,2,2,2,2,W,W,2,2,2,2,W,W,2,2,2,2,2,2,W,_,_,_,_),
	me(W,2,W,W,W,W,W,W,W,W,W,W,2,W,W,2,W,W,W,W,W,W,W,W,W,W,2,W,_,_,_,_),
	me(W,2,W,W,W,W,W,W,W,W,W,W,2,W,W,2,W,W,W,W,W,W,W,W,W,W,2,W,_,_,_,_),
	me(W,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,W,_,_,_,_),
	me(W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,_,_,_,_),

};


#endif

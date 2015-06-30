#ifndef GAME_H
#define GAME_H

#include "Arduino.h"

#define PAUSE_BUTTON A_BUTTON
#define GHOST_COUNT 4

enum GameState {
	MENU,
	NEW_GAME,
	GAME_OVER,
	PLAYING,
	CREDITS,
	PAUSED,
	WIN_ARCADE,
	WIN_CAMPAIGN,
};

typedef struct Vector {
	int8_t x;
	int8_t y;
};

extern Vector direction_vectors[];

enum Direction {
	Up = 0,
	Down = 1,
	Right = 2,
	Left = 3,
	None = 10
};

enum GhostMode {
	Scatter,
	Chase
};

enum GameMode {
	Arcade,
	Campaign
};


enum GhostPersonality {
	Shadow,  // speeds up as you eat more dots
	Speedy,  // not really faster
	Bashful, // weirdly shys away from you
	Pokey

};

struct Character {
	int8_t x;
	int8_t y;
	int8_t speed;
	Direction direction;
	Direction desired_direction;
	uint8_t fractional;
};

struct Ghost: public Character {
	GhostPersonality personality;
	int respawn_delay = -1;
};

struct Game {
	uint8_t lives;
	uint8_t level;
	uint8_t campaign_level;
	GameMode mode;
	unsigned long score;
};

#endif

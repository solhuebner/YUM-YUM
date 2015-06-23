#ifndef GAME_H
#define GAME_H

#include "Arduino.h"

#define PAUSE_BUTTON A_BUTTON

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
	uint8_t grid_x;
	uint8_t grid_y;
	int x;
	int y;
	int8_t speed_x;
	int8_t speed_y;
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
	long score;
};

#endif

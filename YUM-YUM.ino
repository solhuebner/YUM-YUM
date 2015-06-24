// libraries to link in
#include <SPI.h>
#include <EEPROM.h>
#include <Arduboy.h>
#include <ArduboyExtra.h>
#include <sprites.h>
#include <simple_buttons.h>

// resources
#include "assets.h"
#include "map.h"
#include "maps.h"
#include "game.h"
#include "utils.h"

#define ANY_BUTTON 0xFF


// hardware
Arduboy AB;
SimpleButtons buttons(AB);
Sprites sprites(AB);

// game
Map current_map;
GameState app_state = MENU;
Game game;
Character player;

Ghost ghosts[GHOST_COUNT];

void logo()
{
	AB.display();
	// delay(3000);
}

void gameInit()
{
	ghosts[0].personality = Shadow;
	ghosts[1].personality = Speedy;
	ghosts[2].personality = Bashful;
	ghosts[3].personality = Pokey;
}

void setup()
{
	AB.start();
	AB.setFrameRate(60);
	// setup audio?
	logo();
	gameInit();
}

void loop()
{
	if (AB.nextFrame())
		game_loop();
	// else nextFrame will sleep for 1ms then loop will
	// rinse and repeat
}

void pause()
{
	// wait for button to be released
	while (AB.pressed(PAUSE_BUTTON)) {};

	// show pause screen
	AB.display();
	delay(250);
	waitForButtons(PAUSE_BUTTON);
}

void gameOver() {
	// render game over
	// render score?
	// render achievements?
	AB.display();
	delay(250);
	waitForButtons(ANY_BUTTON);
}

void credits() {
	while(true) {
		if (!AB.nextFrame())
			continue;
		// roll credits

		if (buttons.justPressed(A_BUTTON)) {
			app_state = MENU;
			return;
		}
	}
}

extern void gameMenu();
extern void gamePlay();

void game_loop()
{
	switch (app_state) {
		case MENU:
			gameMenu();
			break;
		case NEW_GAME:
		case PLAYING:
			gamePlay();
			break;
		case GAME_OVER:
			gameOver();
			break;
		case PAUSED:
			pause();
			break;
		case CREDITS:
			credits();
			break;
		case WIN_CAMPAIGN:
		case WIN_ARCADE:
			// you_win();
			break;
	}
}


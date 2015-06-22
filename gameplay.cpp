#include "Arduboy.h"

#include "assets.h"
#include "game.h"
#include "map.h"

extern Arduboy AB;
extern Game game;
extern GameState app_state;
extern Map current_map;

void newGame()
{
	game.score = 0;
	game.level = 1;
	game.mode = Arcade;
	app_state = PLAYING;
}

void winLevel()
{
	// nice screen?
	// pause?
	// overlay?
}

void nextLevel()
{
	// if game is arcade or campaign?
	game.level++;

	// victory?
	if (game.mode == Arcade && game.level == 11) {
		app_state = WIN_ARCADE;
		return;
	}
	// load new map?
	// reset existing map?
	// change game timing?
}

void victory()
{
	// can you win win?
}

void updateScore()
{

}

void gamePlay()
{
	while(true) {
		if (!AB.nextFrame())
			continue;

		// handle dpad input for directions

		/*
		AI for ghosts runs
		move characters
		animate characters
		check collisions
		if collide fruit
			eat fruit
			remove fruit from map
			set fruit gameplay mode
			fruit timer?
		if collide with ghost
			if special mode
				eat ghost?
			else
				reduce lives
				restart level?
		if collide dot
			eat dot
			reduce dot count
			remove dot from map

		change ghost mode?
			scatter?
			chase?
		*/


		// redraw map
		updateScore();
		AB.display();

		if (current_map.dots_left == 0) {
			winLevel();
			nextLevel();
		}

		// game loss
		if (game.lives == 0) {
			app_state = GAME_OVER;
			return;
		}

		// handle post input
		 if (AB.pressed(PAUSE_BUTTON)) {
			  app_state = PAUSED;
		 }

		 if (app_state != PLAYING)
		 	return;
	}
}

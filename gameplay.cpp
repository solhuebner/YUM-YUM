#include "Arduboy.h"
#include "ArduboyExtra.h"
#include "simple_buttons.h"

#include "assets.h"
#include "game.h"
#include "map.h"
#include "maps.h"
#include "map_renderer.h"


extern Arduboy AB;
extern Game game;
extern GameState app_state;
extern Map current_map;
extern SimpleButtons buttons;

extern Character player;
extern Ghost ghosts[];

MapRenderer map_view(current_map, game);

void newGame()
{
	// prepare game and map
	current_map.prepareFromFlash(map_intro);
	game.score = 0;
	game.level = 1;
	game.lives = 3;
	game.mode = Arcade;

	// set starting positions
	player.x = current_map.player_start_x;
	player.y = current_map.player_start_y;
	player.speed_x = 0;
	player.speed_y = 0;

	for (int i=0; i<4; i++) {
		ghosts[i].x = current_map.ghost_start_x;
		ghosts[i].y = current_map.ghost_start_y;
	}

	app_state = PLAYING;
}

void winLevel()
{
	// nice screen?
	// pause?
	// overlay?
	// at least something saying level 2?
}

void nextLevel()
{
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

void updateScore()
{

}

// check dpad and player location to see if we can change our
// direction
void dpadInput()
{
	Direction dir = None;
	int new_x, new_y;
	uint8_t obj;
	if (buttons.up()) {
		dir = Up;
	} else if (buttons.down()) {
		dir = Down;
	} else if (buttons.right()) {
		dir = Right;
	} else if (buttons.left()) {
		dir = Left;
	}


	// AB.setCursor(0,0);
	// AB.println(dir);

	// AB.tunes.tone(500,50);
	if (buttons.pressed(LEFT_BUTTON)) {
		map_view.viewport_x -=1;
	} else if (buttons.pressed(RIGHT_BUTTON)) {
		map_view.viewport_x +=1;
	} else if (buttons.pressed(UP_BUTTON)) {
		map_view.viewport_y -=1;
	} else if (buttons.pressed(DOWN_BUTTON)) {
		map_view.viewport_y+=1;
	}
	if (dir == None)
		return;

	new_x = player.x + direction_vectors[dir].x;
	new_y = player.y + direction_vectors[dir].y;
	obj = current_map.objectAt(new_x, new_y);
	if (obj == EMPTY || obj == DOT) {
		player.desired_direction = Up;
	}

}

void addScore(int score)
{
	game.score += score;
}


void gamePlay()
{
	if (app_state == NEW_GAME)
		newGame();

	while(true) {



		if (!AB.nextFrame()) {
			continue;
		}

		buttons.poll();
		dpadInput();

		/*
		change ghost mode?
			scatter?
			chase?
		AI for ghosts runs
		move characters
		animate characters
		*/


		/*
		if collide with ghost
			if powerup mode
				eat ghost?
			else
				game.lives--;
				restart level?
		*/

		// if dot at currrent location and pacman centered in current
		// tile
		if (false) {
			addScore(10);
			current_map.eatDot(player.x, player.y);
		}

		// if fruit at current location and pacman centered in current
		// tile
		if (false) {
			addScore(1000);
			// eatDot also eats fruit
			current_map.eatDot(player.x, player.y);
		}

		/*
		if collid powerup
			addScore(10);
			set powerup gameplay mode
			powerup timer?
		*/



		map_view.render();
		updateScore();


		AB.setCursor(0,0);
		AB.println(AB.cpuLoad());
		AB.display();


		if (current_map.complete()) {
			winLevel();
			nextLevel();
		}

		// handle post input
		 // if (AB.pressed(PAUSE_BUTTON)) {
			//   app_state = PAUSED;
		 // }

		// game loss
		if (game.lives == 0) {
			app_state = GAME_OVER;
		}

		// back to state dispatch in main loop
		 if (app_state != PLAYING)
		 	return;

	}
}
#include "Arduboy.h"
#include "ArduboyExtra.h"
#include "simple_buttons.h"

#include "ai.h"
#include "assets.h"
#include "game.h"
#include "gameplay.h"
#include "map.h"
#include "maps.h"
#include "map_renderer.h"
#include "sounds.h"

extern Arduboy AB;
extern Game game;
extern GameState app_state;
extern Map current_map;
extern SimpleButtons buttons;
extern Sounds sound;

extern Character player;
extern Ghost ghosts[];

MapRenderer map_view(current_map, game);

#define CENTERED 7

bool centered(Character chr)
{
	return chr.fractional == CENTERED;
}

void newGame()
{
	// prepare game and map
	current_map.prepareFromFlash(pacman_map);
	// current_map.prepareFromFlash(map_intro);
	game.score = 0;
	game.level = 1;
	game.lives = 3;
	game.mode = Arcade;

	// set starting positions
	player.x = current_map.player_start_x;
	player.y = current_map.player_start_y;
	player.speed = 0;
	player.fractional = CENTERED;

	for (int i=0; i<4; i++) {
		ghosts[i].x = current_map.ghost_start_x;
		ghosts[i].y = current_map.ghost_start_y;
	}

	app_state = PLAYING;
}

void restartLevel()
{

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

	// desire has already been registered
	if (dir == player.desired_direction)
		return;

	// we are already heading that direction, no change needed
	if (dir == player.direction && player.desired_direction == None)
		return;

	if (buttons.left()) {
		map_view.viewport_x -=1;
	} else if (buttons.right()) {
		map_view.viewport_x +=1;
	} else if (buttons.up()) {
		map_view.viewport_y -=1;
	} else if (buttons.down()) {
		map_view.viewport_y+=1;
	}

	// log the desire to turn if we hit the key a little early
	if (dir != None) {
		if (player.fractional<=9) {
			new_x = player.x + direction_vectors[dir].x;
			new_y = player.y + direction_vectors[dir].y;
			obj = current_map.objectAt(new_x, new_y);
			if (obj != WALL) {
				player.desired_direction = dir;
			}
		}
	}

	// actually change our direction
	if (player.desired_direction != None) {
		if (centered(player) || player.direction == None) {
			player.direction = player.desired_direction;
			player.desired_direction = None;

			// if we're hitting a little late, rewind us when we turn
			if (player.fractional>7)
				player.fractional=7;
		}
	}

}

void addScore(int score)
{
	game.score += score;
}


bool collide(Character player, Ghost ghost)
{
	// needs to also think about fractionals?
	return (player.x == ghost.x &&
		player.y == ghost.y);
}

void eatGhost(Ghost ghost)
{
	// what happens when a ghost is eaten?
	addScore(1000);
	sound.eatGhost();
	// dry?
	ghost.x = current_map.ghost_start_x;
	ghost.y = current_map.ghost_start_y;
	ghost.direction = None;
	// set delay?
}

void handleGhostCollisions()
{
	for (uint8_t i=0; i < GHOST_COUNT; i++)
	{
		if (collide(player, ghosts[i])) {
			if (player.powered_up) {
				eatGhost(ghosts[i]);
			} else {
				// touch a ghost, lose a life
				game.lives--;
				if (game.lives > 0) { restartLevel(); }
			}
		}
	}
}

void handleEating()
{
	uint8_t current_tile;

	// we can't eat if we aren't centered
	if (!centered(player))
		return;


	current_tile = current_map.objectAt(player.x, player.y);

	if (current_tile == DOT) {
		addScore(10);
		AB.tunes.tone(3200,10);
		sound.dot();
		current_map.eatDot(player.x, player.y);
	}

	if (current_tile == FRUIT) {
		addScore(1000);
		sound.dot();
		// eatDot also eats fruit
		current_map.eatDot(player.x, player.y);
	}

	if (current_tile == POWERUP) {
		addScore(10);
		sound.powerup();
		player.powered_up = true;
		// powerup timer?
		current_map.eatDot(player.x, player.y);
	}
}

// does this need to handle wall collisions or is that elsewhere
void moveCharacters()
{
	Vector d;
	uint8_t next_tile;

	// GHOSTS

	for (uint8_t i=0; i < GHOST_COUNT; i++) {
		if (ghosts[i].direction == None)
			continue;

		// DRY?
		ghosts[i].fractional+=1;
		if (ghosts[i].fractional>14) {
			d = direction_vectors[ghosts[i].direction];
			ghosts[i].x += d.x;
			ghosts[i].y += d.y;
			ghosts[i].fractional = 0;
		}
	}

	// PLAYER

	// we may not be moving yet
	if (player.direction == None)
		return;

	d = direction_vectors[player.direction];
	next_tile = current_map.objectAt(player.x+d.x, player.y+d.y);
	// if we're about to hit a wall, simply stop moving
	if (centered(player) && next_tile == WALL) {
		player.direction = None;
		return;
	}


	// DRY?
	player.fractional+=1;
	if (player.fractional>14) {
		player.x += d.x;
		player.y += d.y;
		player.fractional = 0;
	}
}

void setGhostMode()
{
	/*
	change ghost mode?
		scatter?
		chase?
	*/
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

		setGhostMode(); // scatter, chase, etc.
		runGhostAI();

		moveCharacters();
		handleGhostCollisions();
		handleEating();


		// START render
		AB.clearDisplay();
		map_view.autoCenter();
		map_view.render();
		updateScore();


		AB.setCursor(0,0);
		AB.println(AB.cpuLoad());
		AB.println(current_map.dots_left);
		// AB.print("X: ");
		// AB.print(player.x);
		// AB.print(" Y: ");
		// AB.print(player.y);
		// AB.println("    ");
		AB.print(player.fractional);
		AB.println("    ");
		// AB.println(millis());
		AB.display();
		// END render


		// if (current_map.complete()) {
		// 	winLevel();
		// 	nextLevel();
		// }

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

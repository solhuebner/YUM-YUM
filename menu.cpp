#include "Arduboy.h"

#include "assets.h"

extern Arduboy AB;

void gameMenu()
{
	while(true) {
		if (!AB.nextFrame())
			continue;

		AB.paintScreen(intro_screen);
		AB.display();

	// case to choose item
	// case CREDITS:
	// 	credits();
	// 	break;


	}

}

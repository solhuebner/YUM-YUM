#ifndef UTILS_H
#define UTILS_H

extern Arduboy AB;

void waitForButtons(uint8_t buttons)
{
	do {
		AB.idle(); // sleep
	} while(!(AB.getInput() & buttons));
}

#endif

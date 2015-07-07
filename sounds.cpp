#include "sounds.h"

Sounds::Sounds() {}

void Sounds::on() {
	sound_on = true;
}

void Sounds::off() {
	sound_on = false;
}

bool Sounds::enabled() {
	return sound_on;
}

// sound effects

void Sounds::dot() {
	tone(3000,30);
}

void Sounds::powerup() {
	tone(3000,30);
}

void Sounds::eatGhost() {
	tone(3000,30);
}


void Sounds::tone(int freq, int dur)
{

}




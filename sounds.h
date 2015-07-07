#ifndef SOUNDS_H
#define SOUNDS_H

class Sounds {
public:
	Sounds();
	void tone(int freq, int dur);
	void on();
	void off();
	bool enabled();

	void dot();
	void eatGhost();
	void powerup();

private:
	bool sound_on;
};

#endif

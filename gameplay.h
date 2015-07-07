#ifndef GAMEPLAY_H
#define GAMEPLAY_H

bool centered(Character chr);
void addScore(unsigned int score);

void gamePlay();

// steps of the main game routine
void newGame();
void dpadInput();
void handleGhostCollisions();
void handleEating();
void eatGhost(Ghost ghost);
void moveCharacters();
void setGhostMode();
void updateScore();
void restartLevel();


#endif

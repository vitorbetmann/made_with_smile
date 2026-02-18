#ifndef STATE_SCORE_H
#define STATE_SCORE_H

// Includes
// --------
#include <raylib.h>

// Prototypes
// ----------
void StateScoreEnter(const void *args);

void StateScoreUpdate(float dt);

void StateScoreDraw(void);

// Variables
// ---------
extern Texture2D medalGoldImg, medalSilverImg, medalBronzeImg;

#endif

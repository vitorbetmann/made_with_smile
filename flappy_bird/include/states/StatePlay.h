#ifndef PLAY_STATE_H
#define PLAY_STATE_H

// Includes
#include <raylib.h>

// Data Types
// ----------
typedef struct {
  int score;
} ScoreArgs;

// --------
// Prototypes
// ----------
void StatePlayEnter(const void *args);

void StatePlayUpdate(float dt);

void StatePlayDraw(void);

void StatePlayExit(void);

// ----------

// Variables
// ---------
extern Texture pauseImg;

#endif

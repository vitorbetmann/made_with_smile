#ifndef PIPE_PAIR_H
#define PIPE_PAIR_H

#include "Pipe.h"
#include "raylib.h"

// Data types
// ----------
typedef struct {
  Pipe *top;
  Pipe *bottom;
  int width;
  Vector2 *pos;
  int score;
} PipePair;

// Prototypes
// ----------
PipePair *NewPipePair(Vector2 screen);
void PipePairUpdate(PipePair *pipePair, float dt);
void PipePairDraw(PipePair *pipePair);
void PipePairUnload(PipePair *pipePair);
// ----------

#endif
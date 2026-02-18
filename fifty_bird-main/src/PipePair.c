#include "PipePair.h"

#include <stdlib.h>

#include "Pipe.h"
#include "raylib.h"
#include "Settings.h"

const int PIPE_HEIGHT = 288;
static int pipeGap[] = {70, 90, 110};

PipePair *NewPipePair(Vector2 gapPos) {
  PipePair *newPipePair = malloc(sizeof(PipePair));
  int index = GetRandomValue(0, 2);

  newPipePair->top = NewPipe((Vector2){gapPos.x, gapPos.y - PIPE_HEIGHT}, TOP);
  newPipePair->bottom =
      NewPipe((Vector2){
                gapPos.x,
                newPipePair->top->pos.y + PIPE_HEIGHT + pipeGap[index]
              },
              BOTTOM);

  newPipePair->width = newPipePair->bottom->width;
  newPipePair->pos = &newPipePair->bottom->pos;

  newPipePair->score = PIPE_SCORE;

  return newPipePair;
}

void PipePairUpdate(PipePair *pipePair, float dt) {
  PipeUpdate(pipePair->top, dt);
  PipeUpdate(pipePair->bottom, dt);
}

void PipePairDraw(PipePair *pipePair) {
  PipeDraw(pipePair->top);
  PipeDraw(pipePair->bottom);
}

void PipePairUnload(PipePair *pipePair) {
  PipeUnload(pipePair->bottom);
  PipeUnload(pipePair->top);
  free(pipePair);
}

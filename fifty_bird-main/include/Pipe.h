#ifndef PIPE_H
#define PIPE_H
#include "raylib.h"

// Data types
// ----------
typedef enum { TOP, BOTTOM } Orientation;

typedef struct {
  Texture2D sprite;
  int width, height;
  Orientation orientation;
  Vector2 pos;
  Rectangle hitBox;
} Pipe;

// Prototypes
// ----------
Pipe *NewPipe(Vector2 screen, Orientation orientation);
void PipeUpdate(Pipe *pipe, float dt);
void PipeDraw(Pipe *pipe);
void PipeUnload(Pipe *pipe);
void PipeUnloadSprite(void);
// ----------

#endif
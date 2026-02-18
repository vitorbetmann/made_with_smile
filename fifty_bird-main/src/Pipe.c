#include "Pipe.h"

#include "Assets_paths.h"
#include "raylib.h"
#include "Settings.h"
#include "stdlib.h"

// Prototypes
// ----------
static void PipeLoadSprite(void);

// ----------

// Variables
// ---------
static Texture2D PIPE_SPRITE;
static bool spriteLoaded = false;
// ---------

static void PipeLoadSprite() {
  if (!spriteLoaded) {
    PIPE_SPRITE = LoadTexture(PIPE_IMG);
    spriteLoaded = true;
  }
}

Pipe *NewPipe(Vector2 pos, Orientation orientation) {
  Pipe *newPipe = malloc(sizeof(Pipe));
  if (newPipe == NULL) {
    return NULL;
  }

  if (!spriteLoaded) {
    PipeLoadSprite();
  }

  newPipe->sprite = PIPE_SPRITE;

  newPipe->orientation = orientation;

  newPipe->pos.x = pos.x;
  newPipe->pos.y = pos.y;

  newPipe->width = newPipe->sprite.width;
  newPipe->height = newPipe->sprite.height;

  newPipe->hitBox.width = newPipe->width;
  newPipe->hitBox.height = newPipe->height;

  return newPipe;
}

void PipeUpdate(Pipe *pipe, float dt) {
  pipe->pos.x -= PIPE_SCROLL_SPEED * dt;
  pipe->hitBox.x = pipe->pos.x;
  pipe->hitBox.y = pipe->pos.y;
}

void PipeDraw(Pipe *pipe) {
  if (pipe->orientation == TOP) {
    Rectangle source = {0, 0, pipe->width, -pipe->height};
    Rectangle dest = {pipe->pos.x, pipe->pos.y, pipe->width, pipe->height};

    DrawTexturePro(pipe->sprite, source, dest, (Vector2){0, 0}, 0.0f, WHITE);
  } else {
    DrawTexture(pipe->sprite, pipe->pos.x, pipe->pos.y, WHITE);
  }
}

void PipeUnload(Pipe *pipe) { free(pipe); }

void PipeUnloadSprite() { UnloadTexture(PIPE_SPRITE); }

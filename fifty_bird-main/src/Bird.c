#include "Bird.h"

#include "Assets_paths.h"
#include "raylib.h"
#include "Settings.h"

// Prototypes
// ----------
static bool canJump(bool isAlive);

// ----------

Bird *NewBird(Vector2 screen) {
  static Bird newBird = {0};
  BirdReset(&newBird);

  return &newBird;
}

void BirdReset(Bird *bird) {
  bird->birdSprite = LoadTexture(BIRD_IMG);

  bird->width = bird->birdSprite.width;
  bird->height = bird->birdSprite.height;

  bird->pos.x = (V_SCREEN.x - bird->width) / 2;
  bird->pos.y = (V_SCREEN.y - bird->height) / 2;

  bird->hitBox.width = bird->width - 2 * HITBOX_LEEWAY;
  bird->hitBox.height = bird->height - 2 * HITBOX_LEEWAY;

  bird->isAlive = true;
  bird->score = 0;
  bird->dy = 0;
}

void BirdUpdate(Bird *bird, float dt) {
  bird->dy += GRAVITY * dt;

  if (canJump(bird->isAlive)) {
    bird->dy -= JUMP_BURST;
    PlaySound(jumpSound);
  }

  bird->pos.y += bird->dy * dt;

  bird->hitBox.x = bird->pos.x + HITBOX_LEEWAY;
  bird->hitBox.y = bird->pos.y + HITBOX_LEEWAY;
}

static bool canJump(bool isAlive) {
  if (!isAlive) {
    return false;
  }
  return HasValidInput(input1);
}

void BirdDraw(Bird *bird) {
  DrawTexture(bird->birdSprite, bird->pos.x, bird->pos.y, WHITE);
}

void BirdUnloadSprite(void) { UnloadTexture(gBird->birdSprite); }

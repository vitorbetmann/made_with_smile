#ifndef BIRD_H
#define BIRD_H

// Includes
// --------
#include "raylib.h"
// --------

// ----------
// Data Types
// ----------
typedef struct {
  Texture2D birdSprite;
  int width, height;
  Vector2 pos;
  float dy, rotation;
  Rectangle hitBox;
  bool isAlive;
  int score;
} Bird;

// ----------
// Prototypes
// ----------
Bird *NewBird(Vector2 screen);
void BirdReset(Bird *bird);
void BirdUpdate(Bird *bird, float dt);
void BirdDraw(Bird *bird);
void BirdUnloadSprite(void);

#endif
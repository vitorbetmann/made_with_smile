#ifndef PLAYER_H
#define PLAYER_H

#include "Paddle.h"

// Data types
typedef struct {
  Paddle paddle;
  unsigned int score;
  unsigned char number;
} Player;

// Prototypes
Player NewPlayer(float left, float top, char number);
void Score(Player *player);
#endif
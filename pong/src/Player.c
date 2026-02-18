#include "Player.h"

Player NewPlayer(float left, float top, char number) {
  Player newPlayer = {.paddle = {left, top}, 0, number};
  return newPlayer;
}

void Score(Player *player) { player->score++; }
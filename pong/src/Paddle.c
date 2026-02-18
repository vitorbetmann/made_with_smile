#include "Paddle.h"
#include "Settings.h"
#include <raylib.h>

void PaddleMoveUp(Paddle *paddle, float dt) {
  int newPos = paddle->top - PADDLE_SPEED * dt;
  paddle->top = newPos < 0 ? 0 : newPos;
}

void PaddleMoveDown(Paddle *paddle, float dt) {
  int newPos = paddle->top + PADDLE_SPEED * dt;
  int lowerWindowLimit = V_HEIGHT - PADDLE_HEIGHT;
  paddle->top = newPos > lowerWindowLimit ? lowerWindowLimit : newPos;
}

void PaddleDraw(Paddle *paddle) {
  DrawRectangle(paddle->left, paddle->top, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
}
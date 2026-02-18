#include "Ball.h"
#include "Settings.h"
#include <raylib.h>

Ball NewBall() {
  Ball newBall = {0};
  BallSetXSpeedRandom(&newBall);
  BallReset(&newBall);
  return newBall;
}

void BallUpdate(Ball *ball, float dt) {
  ball->left += ball->xSpeed * dt;
  ball->top += ball->ySpeed * dt;
}

void BallDraw(Ball *ball) {
  DrawRectangle(ball->left, ball->top, BALLSIZE, BALLSIZE, WHITE);
}

void BallReset(Ball *ball) {
  BallSetYSpeedRandom(ball, false);
  ball->left = (V_WIDTH - BALLSIZE) / 2.0;
  ball->top = (V_HEIGHT - BALLSIZE) / 2.0;
  ball->xSpeed = (ball->xSpeed > 0 ? -1 : 1) * BALL_X_SPEED;
}

bool BallHitBoundaries(Ball *ball) {
  if (ball->top < 0) {
    ball->top = 0;
    BallInvertYSpeed(ball);
    return true;
  } else if (ball->top + BALLSIZE > V_HEIGHT) {
    ball->top = V_HEIGHT - BALLSIZE;
    BallInvertYSpeed(ball);
    return true;
  }
  return false;
}

void BallInvertXSpeed(Ball *ball) {
  ball->xSpeed *= -1.03;
  BallSetYSpeedRandom(ball, true);
}

void BallInvertYSpeed(Ball *ball) { ball->ySpeed *= -1; }

void BallSetXSpeedRandom(Ball *ball) {
  ball->xSpeed = GetRandomValue(0, 1) % 2 == 0 ? -BALL_X_SPEED : BALL_X_SPEED;
}

void BallSetYSpeedRandom(Ball *ball, bool keepDirection) {
  float ogDir = ball->ySpeed;
  int speed = GetRandomValue(0, BALL_Y_SPEED_MAX);
  ball->ySpeed = (GetRandomValue(0, 1) % 2 == 0) ? -speed : speed;
  if (keepDirection && ball->ySpeed * ogDir < 0) {
    ball->ySpeed *= -1;
  }
}
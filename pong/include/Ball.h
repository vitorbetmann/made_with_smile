#ifndef BALL_H
#define BALL_H

// Includes
#include <raylib.h>

// Defines
#define BALLSIZE 4
#define BALL_X_SPEED 100
#define BALL_Y_SPEED_MAX 50

// Ball Struct
typedef struct {
  float left;
  float top;
  float xSpeed;
  float ySpeed;
} Ball;

// Prototypes
Ball NewBall();
void BallUpdate(Ball *ball, float dt);
void BallDraw(Ball *ball);
void BallReset(Ball *ball);
void BallInvertXSpeed(Ball *ball);
void BallInvertYSpeed(Ball *ball);
void BallSetXSpeedRandom(Ball *ball);
void BallSetYSpeedRandom(Ball *ball, bool keepDirection);
bool BallHitBoundaries(Ball *ball);
#endif
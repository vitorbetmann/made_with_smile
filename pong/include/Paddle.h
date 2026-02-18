#ifndef PADDLE_H
#define PADDLE_H

// Defines
#define PADDLE_WIDTH 5
#define PADDLE_HEIGHT 20
#define PADDLE_SPEED 200

// Data Types
typedef struct {
  float left;
  float top;
  bool AIEnabled;
} Paddle;

// Prototypes
void PaddleMoveUp(Paddle *paddle, float dt);
void PaddleMoveDown(Paddle *paddle, float dt);
void PaddleDraw(Paddle *paddle);
#endif

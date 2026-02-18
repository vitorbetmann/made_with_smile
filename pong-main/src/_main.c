#include "Ball.h"
#include "Paddle.h"
#include "Player.h"
#include "Settings.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Data Types
typedef enum { START, SERVE, PLAY, PAUSE, GAMEOVER } GameState;

// Variables
Player player1, player2;
Ball ball;
RenderTexture2D vScreen;
Font font;
float dt;
bool canDrawFPS = false;
const Color BACKGROUND = {40, 45, 52, 255};
static const char SERVING_TEXT[] =
    "\t\tPlayer %c's serve!\nPress Enter to serve!";
static const char GAMEOVER_TEXT[] =
    "\t\t\tPlayer %c WON!\nPress Enter to restart!";
static const char PAUSE_TEXT[] = "Game Paused";
Player servingPlayer, winner;
bool hasScored;
Sound paddleHit, score, wallHit;
GameState gameState;

// Prototypes
void GameInit();
void GameRun();
void CheckChangeGameState();
void UpdateAll();
bool hasCollided(Paddle paddle);
void DrawAll();
void ScoreDraw();
void ServingDraw();
void PauseDraw();
void GameOverDraw();

void SetServingPlayer();
void CheckToggleFPS();
void DisplayFPS();
void DrawOnVScreen();
void GreetingDraw();
void DrawOnWindow();
void GameUnload();

void AIMovePaddle(Player *player);
void ToggleAI(Player *player);

// Main
int main(void) {
  GameInit();
  GameRun();
  GameUnload();
  return 0;
}

// Functions
void GameInit() {
  SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT |
                 FLAG_WINDOW_RESIZABLE);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
  vScreen = LoadRenderTexture(V_WIDTH, V_HEIGHT);
  font = LoadFont("../assets/pong_font.ttf");
  SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
  HideCursor();
  SetTargetFPS(TARGET_FPS);
  SetRandomSeed(time(NULL));

  InitAudioDevice();
  paddleHit = LoadSound("../assets/paddle_hit.wav");
  score = LoadSound("../assets/score.wav");
  wallHit = LoadSound("../assets/wall_hit.wav");

  player1 = NewPlayer(10, 30, '1');
  player2 = NewPlayer(V_WIDTH - 30, V_HEIGHT - 50, '2');
  ball = NewBall();
  SetServingPlayer();

  gameState = START;
}

void GameRun() {
  while (!WindowShouldClose()) {
    CheckChangeGameState();
    UpdateAll();
    DrawAll();
  }
}

void CheckChangeGameState() {
  switch (gameState) {
  case START:
    if (IsKeyPressed(KEY_ENTER)) {
      gameState = SERVE;
    }
    break;
  case SERVE:
    if (IsKeyPressed(KEY_ENTER)) {
      gameState = PLAY;
    }
    break;
  case PLAY:
    if (IsKeyPressed(KEY_ENTER)) {
      gameState = PAUSE;
    }
    if (hasScored) {
      BallReset(&ball);
      SetServingPlayer();
      gameState = SERVE;
    } else {
      if (BallHitBoundaries(&ball)) {
        PlaySound(wallHit);
      }
    }

    if (player1.score == MAX_SCORE || player2.score == MAX_SCORE) {
      winner = player1.score == MAX_SCORE ? player1 : player2;
      gameState = GAMEOVER;
    }
    break;
  case PAUSE:
    if (IsKeyPressed(KEY_ENTER)) {
      gameState = PLAY;
    }
    break;
  case GAMEOVER:
    if (IsKeyPressed(KEY_ENTER)) {
      BallReset(&ball);
      BallSetXSpeedRandom(&ball);
      SetServingPlayer();
      player1.score = 0;
      player2.score = 0;
      gameState = SERVE;
    }
  }
}

void UpdateAll() {
  dt = GetFrameTime();
  CheckToggleFPS();
  if (IsKeyPressed(KEY_F)) {
    ToggleFullscreen();
  }

  switch (gameState) {
  case START:
  case PAUSE:
  case SERVE:
    break;
  case PLAY:
    BallUpdate(&ball, dt);

    if (hasCollided(player1.paddle)) {
      ball.left = player1.paddle.left + PADDLE_WIDTH;
      BallInvertXSpeed(&ball);
      PlaySound(paddleHit);
    } else if (hasCollided(player2.paddle)) {
      ball.left = player2.paddle.left - BALLSIZE;
      BallInvertXSpeed(&ball);
      PlaySound(paddleHit);
    }

    hasScored = false;
    if (ball.left > V_WIDTH) {
      Score(&player1);
      hasScored = true;
      PlaySound(score);

    } else if (ball.left + BALLSIZE < 0) {
      Score(&player2);
      hasScored = true;
      PlaySound(score);
    }

    if (player1.paddle.AIEnabled) {
      AIMovePaddle(&player1);
    } else if (IsKeyDown(KEY_W)) {
      PaddleMoveUp(&player1.paddle, dt);
    } else if (IsKeyDown(KEY_S)) {
      PaddleMoveDown(&player1.paddle, dt);
    }
    if (player2.paddle.AIEnabled) {
      AIMovePaddle(&player2);
    } else if (IsKeyDown(KEY_UP)) {
      PaddleMoveUp(&player2.paddle, dt);
    } else if (IsKeyDown(KEY_DOWN)) {
      PaddleMoveDown(&player2.paddle, dt);
    }

    if (IsKeyPressed(KEY_ONE)) {
      ToggleAI(&player1);
    }
    if (IsKeyPressed(KEY_TWO)) {
      ToggleAI(&player2);
    }

    break;
  case GAMEOVER:
    break;
  }
}

void AIMovePaddle(Player *player) {
  Paddle *paddle = &(player->paddle);
  if (player->number == '1' && ball.xSpeed > 0) {
    return;
  }
  if (player->number == '2' && ball.xSpeed < 0) {
    return;
  }
  if (ball.top > paddle->top + PADDLE_HEIGHT / 4.0 &&
      ball.top + BALLSIZE < paddle->top + 3.0 * PADDLE_HEIGHT / 4.0) {
    return;
  }

  if (ball.top + BALLSIZE / 2.0 > paddle->top + PADDLE_HEIGHT / 2.0) {
    PaddleMoveDown(paddle, dt);
  } else {
    PaddleMoveUp(paddle, dt);
  }
}

void ToggleAI(Player *player) {
  player->paddle.AIEnabled = !player->paddle.AIEnabled;
}

void SetServingPlayer() {
  if (ball.xSpeed > 0) {
    servingPlayer = player1;
  } else {
    servingPlayer = player2;
  }
}

bool hasCollided(Paddle paddle) {
  return paddle.left < ball.left + BALLSIZE &&
         paddle.left + PADDLE_WIDTH > ball.left &&
         paddle.top < ball.top + BALLSIZE &&
         paddle.top + PADDLE_HEIGHT > ball.top;
}

void CheckToggleFPS() {
  if (IsKeyPressed(KEY_P)) {
    canDrawFPS = !canDrawFPS;
  }
}

void DisplayFPS() {
  if (canDrawFPS) {
    DrawFPS(10, 10);
  }
}

void DrawAll() {
  DrawOnVScreen();
  DrawOnWindow();
}

void DrawOnVScreen() {
  BeginTextureMode(vScreen);
  ClearBackground(BACKGROUND);
  DisplayFPS();
  ScoreDraw();
  PaddleDraw(&player1.paddle);
  PaddleDraw(&player2.paddle);
  BallDraw(&ball);
  switch (gameState) {
  case START:
    GreetingDraw();
    break;
  case SERVE:
    ServingDraw();
    break;
  case PAUSE:
    PauseDraw();
    break;
  case GAMEOVER:
    GameOverDraw();
    break;
  case PLAY:
    break;
  }
  EndTextureMode();
}

void ScoreDraw() {
  char buffer[MAX_SCORE_DIGITS_AMOUNT + 1];
  snprintf(buffer, sizeof(buffer), "%d", player1.score);
  DrawText(buffer, V_WIDTH / 2 - 50, V_HEIGHT / 3, SCORE_FONTSIZE, WHITE);
  snprintf(buffer, sizeof(buffer), "%d", player2.score);
  DrawText(buffer, V_WIDTH / 2 + 30, V_HEIGHT / 3, SCORE_FONTSIZE, WHITE);
}

void GreetingDraw() {
  char *greeting = "\t\tWelcome to Pong!\nPress Enter to begin";
  Vector2 textSize = MeasureTextEx(font, greeting, GREETING_FONTSIZE, 2);
  Vector2 textPosition =
      (Vector2){(V_WIDTH - textSize.x) / 2, (V_HEIGHT - textSize.y) * 0.06f};
  DrawTextEx(font, greeting, textPosition, GREETING_FONTSIZE, 2, WHITE);
}

void ServingDraw() {
  char buffer[sizeof(SERVING_TEXT)];
  snprintf(buffer, sizeof(buffer), SERVING_TEXT, servingPlayer.number);
  Vector2 textSize = MeasureTextEx(font, buffer, GREETING_FONTSIZE, 2);
  Vector2 textPosition =
      (Vector2){(V_WIDTH - textSize.x) / 2, (V_HEIGHT - textSize.y) * 0.06f};
  DrawTextEx(font, buffer, textPosition, GREETING_FONTSIZE, 2, WHITE);
}

void GameOverDraw() {
  char buffer[sizeof(GAMEOVER_TEXT)];
  snprintf(buffer, sizeof(buffer), GAMEOVER_TEXT, winner.number);
  Vector2 textSize = MeasureTextEx(font, buffer, GREETING_FONTSIZE, 2);
  Vector2 textPosition =
      (Vector2){(V_WIDTH - textSize.x) / 2, (V_HEIGHT - textSize.y) * 0.06f};
  DrawTextEx(font, buffer, textPosition, GREETING_FONTSIZE, 2, WHITE);
}

void PauseDraw() {
  Vector2 textSize = MeasureTextEx(font, PAUSE_TEXT, GREETING_FONTSIZE, 2);
  Vector2 textPosition =
      (Vector2){(V_WIDTH - textSize.x) / 2, (V_HEIGHT - textSize.y) * 0.06f};
  DrawTextEx(font, PAUSE_TEXT, textPosition, GREETING_FONTSIZE, 2, WHITE);
}

void DrawOnWindow() {
  BeginDrawing();
  ClearBackground(BLACK);

  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();

  float scale =
      fminf((float)screenWidth / V_WIDTH, (float)screenHeight / V_HEIGHT);
  int scaledWidth = V_WIDTH * scale;
  int scaledHeight = V_HEIGHT * scale;

  int offsetX = (screenWidth - scaledWidth) / 2;
  int offsetY = (screenHeight - scaledHeight) / 2;

  Rectangle source = {0, 0, V_WIDTH, -V_HEIGHT};
  Rectangle dest = {offsetX, offsetY, scaledWidth, scaledHeight};

  DrawTexturePro(vScreen.texture, source, dest, (Vector2){0, 0}, 0, WHITE);
  EndDrawing();
}

void GameUnload() {
  UnloadRenderTexture(vScreen);
  UnloadFont(font);
  UnloadSound(paddleHit);
  UnloadSound(score);
  UnloadSound(wallHit);
  CloseAudioDevice();
  CloseWindow();
}
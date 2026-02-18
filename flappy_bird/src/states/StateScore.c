#include "states/StateScore.h"

#include <StateMachine.h>
#include <stdint.h>
#include <stdio.h>

#include "raylib.h"
#include "Settings.h"
#include "string.h"
#include "states/StatePlay.h"

// Data types
// ----------


typedef enum {
  BRONZE = 5,
  SILVER = 10,
  GOLD_MEDAL = 15,
} Award;

// Variables
// ---------
static const char GAME_OVER_MSG[] = "Oof! You lost!";
static const char PLAY_AGAIN_MSG[] = "Press Enter to Play Again";
static const char SCORE_MSG[] = "Score: ";
static int score;

Texture2D medalGoldImg, medalSilverImg, medalBronzeImg;
Texture2D *medalImg;
static bool isMedalAwarded;
// ---------

void StateScoreEnter(const void *args) {
  ScoreArgs *scoreArgs = (ScoreArgs *) args;
  score = scoreArgs->score;

  if (score >= BRONZE_THRESHOLD) {
    isMedalAwarded = true;
  } else {
    isMedalAwarded = false;
  }

  if (score >= GOLD_THRESHOLD) {
    medalImg = &medalGoldImg;
  } else if (score >= SILVER_THRESHOLD) {
    medalImg = &medalSilverImg;
  } else if (score >= BRONZE_THRESHOLD) {
    medalImg = &medalBronzeImg;
  }
}

void StateScoreUpdate(float dt) {
  if (HasValidInput(input2)) {
    smSetState("countdown", nullptr);
  }
}

void StateScoreDraw(void) {
  int textWidth = MeasureText(GAME_OVER_MSG, FLAPPY_FONT_SIZE);
  float textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(flappyFont, GAME_OVER_MSG, (Vector2){textX, 64}, FLAPPY_FONT_SIZE,
             1, WHITE);

  char buffer[sizeof(SCORE_MSG) + sizeof(uint32_t)];
  snprintf(buffer, sizeof(buffer), "%s%d", SCORE_MSG, score);
  textWidth = MeasureText(buffer, MEDIUM_FONT_SIZE);
  textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(mediumFont, buffer, (Vector2){textX, 100}, MEDIUM_FONT_SIZE, 1,
             WHITE);

  if (isMedalAwarded) {
    float imgScale = 0.02;
    DrawTextureEx(
      *medalImg,
      (Vector2){
        (V_SCREEN.x - medalImg->width * imgScale) / 2.0,
        (V_SCREEN.y - medalImg->height * imgScale) / 2.0 + 10
      },
      0, imgScale, WHITE);
  }

  textWidth = MeasureText(PLAY_AGAIN_MSG, MEDIUM_FONT_SIZE);
  textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(mediumFont, PLAY_AGAIN_MSG, (Vector2){textX, 200},
             MEDIUM_FONT_SIZE, 1, WHITE);
}

#include "states/StateCountdown.h"

#include <stdio.h>

#include "Bird.h"
#include "raylib.h"
#include "Settings.h"
#include "StateMachine.h"

// Data types
// ----------


// Prototypes
// ----------
bool IsTimerOver(void);

// Variables
// ---------
static const float COUNTDOWN_TIME = 0.75;
static double timer;
// ---------

void StateCountdownEnter(const void *args) {
  BirdReset(gBird);

  timer = 4.0f;
}

void StateCountdownUpdate(float dt) {
  timer -= 1.25f * dt;

  if (IsTimerOver()) {
    smSetState("play", nullptr);
  }
}

bool IsTimerOver(void) { return timer < 1; }

void StateCountdownDraw(void) {
  BirdDraw(gBird);

  char buffer[sizeof(char) + 1];
  snprintf(buffer, sizeof(buffer), "%d", (int)(timer));
  int textWidth = MeasureText(buffer, HUGE_FONT_SIZE);
  float textX = (V_SCREEN.x - textWidth) / 2.0;
  DrawTextEx(hugeFont, buffer, (Vector2){textX, 80}, HUGE_FONT_SIZE, 1, WHITE);
}

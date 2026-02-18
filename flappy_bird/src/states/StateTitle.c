// Includes
// --------
#include "states/StateTitle.h"

#include <StateMachine.h>

#include "raylib.h"
#include "Settings.h"
// --------

// Data Types
// ----------


// Variables
// ---------
static const char PROMPT[] = "Press Enter";
// ---------

void StateTitleUpdate(float dt) {
    if (HasValidInput(input2)) {
        smSetState("countdown", nullptr);
    }
}

void StateTitleDraw(void) {
    int textWidth = MeasureText(GAME_TITLE, FLAPPY_FONT_SIZE);
    float textX = (V_SCREEN.x - textWidth) / 2.0;
    DrawTextEx(flappyFont, GAME_TITLE, (Vector2){textX, 64}, FLAPPY_FONT_SIZE,
               1,
               WHITE);

    textWidth = MeasureText(PROMPT, MEDIUM_FONT_SIZE);
    textX = (V_SCREEN.x - textWidth) / 2.0;
    DrawTextEx(mediumFont, PROMPT, (Vector2){textX, 100}, MEDIUM_FONT_SIZE, 1,
               WHITE);
    BirdDraw(gBird);
}

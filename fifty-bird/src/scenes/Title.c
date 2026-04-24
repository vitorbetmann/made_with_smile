// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>
#include <SceneManager.h>

#include "Settings.h"

#include "Title.h"
#include "Countdown.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static const char *PLAY_PROMPT = "Press Enter";

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void TitleUpdate(float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        if (!smSceneExists("countdown"))
        {
            smCreateScene("countdown", CountdownEnter, CountdownUpdate, CountdownDraw, nullptr);
        }
        smSetScene("countdown", nullptr);
    }
}

void TitleDraw(void)
{
    float spacing = (float)FLAPPY_FONT / 10;
    Vector2 textSize = MeasureTextEx(flappyFont, GAME_TITLE, (float)FLAPPY_FONT, spacing);
    float textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(flappyFont, GAME_TITLE, (Vector2){textX, 64},
               (float)FLAPPY_FONT, spacing, WHITE);

    spacing = (float)MEDIUM_FONT / 10;
    textSize = MeasureTextEx(font, PLAY_PROMPT, (float)MEDIUM_FONT, spacing);
    textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(font, PLAY_PROMPT, (Vector2){textX, 100},
               (float)MEDIUM_FONT, spacing, WHITE);
}

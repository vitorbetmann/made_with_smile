// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <raylib.h>
#include <SceneManager.h>

#include "Settings.h"

#include "Score.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Data types
// —————————————————————————————————————————————————————————————————————————————————————————————————

typedef enum
{
    BRONZE_MEDAL = 5,
    SILVER_MEDAL = 10,
    GOLD_MEDAL = 15,
} AwardThreshold;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static int score;
static constexpr char GAME_OVER_MSG[] = "Oof! You lost!";
static constexpr char PLAY_AGAIN_PROMPT[] = "Press Enter to Play Again!";
static bool shouldAwardMedal;
static Texture medal;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void ScoreEnter(void *args)
{
    const ScoreData *sd = args;
    if (sd)
    {
        score = sd->score;
    }
    shouldAwardMedal = score >= BRONZE_MEDAL;
    if (shouldAwardMedal)
    {
        if (score >= GOLD_MEDAL)
        {
            medal = medalGold;
        }
        else if (score >= SILVER_MEDAL)
        {
            medal = medalSilver;
        }
        else if (score >= BRONZE_MEDAL)
        {
            medal = medalBronze;
        }
    }
}

void ScoreUpdate(const float dt)
{
    if (IsKeyPressed(KEY_ENTER))
    {
        smSetScene("countdown", nullptr);
    }
}

void ScoreDraw(void)
{
    float spacing = (float)FLAPPY_FONT / 10;
    Vector2 textSize = MeasureTextEx(flappyFont, GAME_OVER_MSG, (float)FLAPPY_FONT, spacing);
    float textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(flappyFont, GAME_OVER_MSG, (Vector2){textX, 64}, (float)FLAPPY_FONT, spacing, WHITE);

    char buf[32];
    snprintf(buf, sizeof(buf), "Score: %d", score);
    spacing = (float)MEDIUM_FONT / 10;
    textSize = MeasureTextEx(font, buf, (float)MEDIUM_FONT, spacing);
    textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(font, buf, (Vector2){textX, 100}, (float)MEDIUM_FONT, spacing, WHITE);

    if (shouldAwardMedal)
    {
        constexpr float scale = 0.02f;
        DrawTextureEx(medal,
                      (Vector2){((float)VIRTUAL_WIDTH - (float)medal.width * scale) / 2.0f,
                                ((float)VIRTUAL_HEIGHT - (float)medal.height * scale) / 2.0f + 10},
                      0, scale, WHITE);
    }

    textSize = MeasureTextEx(font, PLAY_AGAIN_PROMPT, (float)MEDIUM_FONT, spacing);
    textX = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(font, PLAY_AGAIN_PROMPT, (Vector2){textX, 200}, (float)MEDIUM_FONT, spacing, WHITE);
}

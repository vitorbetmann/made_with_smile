// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <raylib.h>
#include <SceneManager.h>

#include "Bird.h"
#include "Settings.h"

#include "Play.h"
#include "Countdown.h"

#include <math.h>

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static int counter;
static float timer;
static constexpr float COUNTDOWN_TIME = 0.75f;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void CountdownEnter(void *args)
{
    counter = 3;
    timer = 0;
    birdReset();
}

void CountdownUpdate(float dt)
{
    timer += dt;
    if (timer > COUNTDOWN_TIME)
    {
        timer = fmodf(timer, COUNTDOWN_TIME);
        counter--;
    }

    if (counter == 0)
    {
        if (!smSceneExists("play"))
        {
            smCreateScene("play", nullptr, PlayUpdate, PlayDraw, PlayExit);
        }
        smSetScene("play", nullptr);
    }
}

void CountdownDraw(void)
{
    char buf[8];
    snprintf(buf, sizeof(buf), "%d", counter);
    const float spacing = (float)HUGE_FONT / 10;
    const Vector2 textSize = MeasureTextEx(font, buf, (float)HUGE_FONT, spacing);
    const Vector2 center = {((float)VIRTUAL_WIDTH - textSize.x) / 2.0f,
                            ((float)VIRTUAL_HEIGHT - textSize.y) / 2.0f};
    DrawTextEx(font, buf, (Vector2){center.x, center.y}, (float)HUGE_FONT, spacing, WHITE);
}

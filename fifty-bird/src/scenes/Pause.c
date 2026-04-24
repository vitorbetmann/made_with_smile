// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>
#include <SceneManager.h>

#include "Pause.h"

#include "Settings.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static drawFn drawPrevScene;
static const char *UNPAUSE_PROMPT = "Press P to Unpause";

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void PauseEnter(void *args)
{
    const PauseData *pd = (PauseData *)args;
    if (pd)
    {
        drawPrevScene = pd->draw;
    }
    PauseMusicStream(music);
    PlaySound(pauseSnd);
}

void PauseUpdate(float dt)
{
    if (IsKeyPressed(KEY_P))
    {
        smSetScene("play", nullptr);
    }
}

void PauseDraw(void)
{
    drawPrevScene();
    
    constexpr float scale = 0.1f;
    Vector2 pos = {((float)VIRTUAL_WIDTH - (float)pauseTexture.width * scale) / 2.0f,
                   ((float)VIRTUAL_HEIGHT - (float)pauseTexture.height * scale) / 2.0f,};
    DrawTextureEx(pauseTexture, pos, 0.0f, scale,WHITE);

    const float spacing = (float)MEDIUM_FONT / 10;
    const Vector2 textSize = MeasureTextEx(font, UNPAUSE_PROMPT, (float)MEDIUM_FONT, spacing);
    pos.y += 100;
    pos.x = ((float)VIRTUAL_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(font, UNPAUSE_PROMPT, pos, (float)MEDIUM_FONT, spacing, WHITE);
}

void PauseExit(void)
{
    PlaySound(pauseSnd);
    PlayMusicStream(music);
}

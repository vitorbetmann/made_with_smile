// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdio.h>
#include <SceneManager.h>

#include "Bird.h"
#include "PipePair.h"
#include "Settings.h"

#include "Play.h"

#include "Pause.h"
#include "Score.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

static bool birdCollided(void);
static void checkPause(void);

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static float stopwatch;
static float spawnTimer = 2;
static bool shouldReset;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Lifecycle
// —————————————————————————————————————————————————————————————————————————————————————————————————

void PlayUpdate(const float dt)
{
    stopwatch += dt;

    if (stopwatch >= spawnTimer)
    {
        pipeListEnqueue();
        stopwatch = 0;
        spawnTimer = (float)GetRandomValue(3, 5) * 0.5f;
    }

    birdUpdate(dt);
    pipeListUpdate(dt);

    if (birdCollided() || gBird.y + (float)gBird.height - 2 > (float)VIRTUAL_HEIGHT)
    {
        shouldReset = true;
        PlaySound(hurtSnd);
        PlaySound(explosionSnd);
        if (!smSceneExists("score"))
        {
            smCreateScene("score", ScoreEnter, ScoreUpdate, ScoreDraw, nullptr);
        }
        smSetScene("score", &(ScoreData){gBird.score});
    }

    checkPause();
}

void PlayDraw(void)
{
    pipeListDraw();
    birdDraw();

    char buf[32];
    snprintf(buf, sizeof(buf), "Score: %d", gBird.score);
    const float spacing = (float)FLAPPY_FONT / 10;
    DrawTextEx(flappyFont, buf, (Vector2){8, 8}, (float)FLAPPY_FONT, spacing, WHITE);
}

void PlayExit(void)
{
    if (!shouldReset) { return; }
    pipeListUnload();
    shouldReset = false;
}

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Static
// —————————————————————————————————————————————————————————————————————————————————————————————————

bool birdCollided(void)
{
    if (!gPipeList.head) { return false; }

    const Rectangle birdRect = {gBird.x + 2, gBird.y + 2,
                                (float)gBird.width - 4, (float)gBird.height - 2};

    const PipePair *active = gPipeList.active->pipePair;
    const Pipe *btm = active->lower;
    const Rectangle btmPipeRect = {btm->x, btm->y, (float)btm->width, (float)btm->height};
    const Pipe *top = active->upper;
    const Rectangle topPipeRect = {top->x, top->y, (float)top->width, (float)top->height};

    return CheckCollisionRecs(birdRect, btmPipeRect) || CheckCollisionRecs(birdRect, topPipeRect);
}

void checkPause(void)
{
    if (IsKeyPressed(KEY_P))
    {
        if (!smSceneExists("pause"))
        {
            smCreateScene("pause", PauseEnter, PauseUpdate, PauseDraw, PauseExit);
        }
        smSetScene("pause", &(PauseData){PlayDraw});
    }
}

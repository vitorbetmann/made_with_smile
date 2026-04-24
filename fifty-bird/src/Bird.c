// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <Bird.h>

#include "Settings.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

static void birdInit(void);

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

Bird gBird;

static bool hasInit;

static constexpr int GRAVITY = 900;
static constexpr int JUMP_SPEED = -250;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Public
// —————————————————————————————————————————————————————————————————————————————————————————————————

void birdReset(void)
{
    if (!hasInit) { birdInit(); }

    gBird.x = (float)(VIRTUAL_WIDTH - gBird.width) / 2.0f;
    gBird.y = (float)(VIRTUAL_HEIGHT - gBird.height) / 2.0f;

    gBird.dy = 0;

    gBird.score = 0;
}

void birdUpdate(const float dt)
{
    gBird.dy += (float)GRAVITY * dt;

    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        PlaySound(jumpSnd);
        gBird.dy = (float)JUMP_SPEED;
    }

    gBird.y += gBird.dy * dt;
}

void birdDraw(void)
{
    DrawTextureV(gBird.sprite, (Vector2){gBird.x, gBird.y}, WHITE);
}

void birdUnload(void)
{
    UnloadTexture(gBird.sprite);
}

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Static
// —————————————————————————————————————————————————————————————————————————————————————————————————

void birdInit(void)
{
    const Image i = LoadImage("assets/bird.png");
    gBird.sprite = LoadTextureFromImage(i);
    UnloadImage(i);

    gBird.width = gBird.sprite.width;
    gBird.height = gBird.sprite.height;

    hasInit = true;
}

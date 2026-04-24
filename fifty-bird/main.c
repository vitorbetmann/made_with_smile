// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <math.h>
#include <raylib.h>
#include <SceneManager.h>

#include "Bird.h"
#include "Settings.h"
#include "Title.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

void load(void);

void update(float dt);

void draw(void);
void drawVWindow(void);

void unload(void);

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static RenderTexture2D vWindow;
static bool displayFPS;
static float backgroundScroll, groundScroll;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Main
// —————————————————————————————————————————————————————————————————————————————————————————————————

int main(void)
{
    load();
    smStart();
    while (smIsRunning())
    {
        update(smGetDt());
        draw();
    }
    unload();
}

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void load(void)
{
    // raylib
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Fifty Bird");
    SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(30);
    vWindow = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    InitAudioDevice();

    // sprites
    Image img = LoadImage("assets/background.png");
    background = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("assets/ground.png");
    ground = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("assets/pipe.png");
    pipeTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("assets/pause.png");
    pauseTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("assets/medal_bronze.png");
    medalBronze = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("assets/medal_silver.png");
    medalSilver = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("assets/medal_gold.png");
    medalGold = LoadTextureFromImage(img);
    UnloadImage(img);

    // fonts
    flappyFont = LoadFont("assets/flappy.ttf");
    SetTextureFilter(flappyFont.texture, TEXTURE_FILTER_POINT);

    font = LoadFont("assets/font.ttf");
    SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);

    // sounds and music
    jumpSnd = LoadSound("assets/jump.wav");
    explosionSnd = LoadSound("assets/explosion.wav");
    hurtSnd = LoadSound("assets/hurt.wav");
    scoreSnd = LoadSound("assets/score.wav");
    pauseSnd = LoadSound("assets/pause.wav");

    music = LoadMusicStream("assets/marios_way.mp3");
    PlayMusicStream(music);

    // SceneManager
    smStart();
    smCreateScene("title", nullptr, TitleUpdate, TitleDraw, nullptr);
    smSetScene("title", nullptr);
}

void update(const float dt)
{
    // quit
    if (IsKeyPressed(KEY_ESCAPE))
    {
        smStop();
    }

    // toggle fps
    if (IsKeyPressed(KEY_T))
    {
        displayFPS = !displayFPS;
    }

    backgroundScroll -= (float)BACKGROUND_SCROLL_SPEED * dt;
    backgroundScroll = fmodf(backgroundScroll, (float)BACKGROUND_LOOPING_POINT);

    groundScroll -= (float)GROUND_SCROLL_SPEED * dt;
    groundScroll = fmodf(groundScroll, (float)VIRTUAL_WIDTH);

    smUpdate(dt);
    UpdateMusicStream(music);
}

void draw(void)
{
    BeginDrawing();
    drawVWindow();
    DrawTexturePro(vWindow.texture,
                   (Rectangle){0, 0, (float)VIRTUAL_WIDTH, (float)-VIRTUAL_HEIGHT},
                   (Rectangle){0, 0, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT},
                   (Vector2){0}, 0, WHITE);
    EndDrawing();
}

void drawVWindow(void)
{
    BeginTextureMode(vWindow);

    DrawTexture(background, (int)backgroundScroll, 0, WHITE);
    smDraw();
    DrawTexture(ground, (int)groundScroll, VIRTUAL_HEIGHT - 16, WHITE);

    // fps
    if (displayFPS)
    {
        DrawFPS(10, 10);
    }

    EndTextureMode();
}

void unload(void)
{
    // entities
    birdUnload();
    pipeListUnload();

    // textures
    UnloadTexture(background);
    UnloadTexture(ground);
    UnloadTexture(pauseTexture);
    UnloadTexture(pipeTexture);
    UnloadTexture(medalBronze);
    UnloadTexture(medalSilver);
    UnloadTexture(medalGold);

    // fonts
    UnloadFont(flappyFont);
    UnloadFont(font);

    // sounds and music
    UnloadSound(jumpSnd);
    UnloadSound(explosionSnd);
    UnloadSound(hurtSnd);
    UnloadSound(scoreSnd);
    UnloadSound(pauseSnd);
    UnloadMusicStream(music);

    CloseAudioDevice();
    CloseWindow();
}

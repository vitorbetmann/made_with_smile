#include <math.h>
#include <raylib.h>
#include <time.h>

#include "Assets_paths.h"
#include "Bird.h"
#include "Pipe.h"
#include "Settings.h"
#include "StateMachine.h"
#include "states/StateCountdown.h"
#include "states/StatePlay.h"
#include "states/StateScore.h"
#include "states/StateTitle.h"
// --------

// Prototypes
// ----------
// Init functions
void GameInit(void);

void LoadImages(void);

void LoadFonts(void);

void LoadMusic(void);

void LoadSounds(void);

// Run functions
void GameRun(void);

void UpdateAll(float dt);

void BGUpdate(float dt);

void GroundUpdate(float dt);

void DrawAll(void);

void DrawOnVScreen(void);

void DrawOnWindow(void);

// Unload functions
void GameUnload(void);

void UnloadImages(void);

void UnloadFonts(void);

void UnloadMusicAndSounds(void);

// ----------

// Variables
// ----------

Bird *gBird;

static float bgScroll = 0, groundScroll = 0;
static RenderTexture2D vScreen;
static Texture2D bgImg, groundImg;

bool (*HasValidInput)(int value);

int input1, input2;

Font smallFont, mediumFont, flappyFont, hugeFont;
Music music;
Sound explosionSound, hurtSound, jumpSound, scoreSound;
// ----------

// Let's have fun!
// ---------------
int main(void) {
  GameInit();
  GameRun();
  GameUnload();
}

// ---------------

// Init functions
// --------------
void GameInit(void) {
  // Window config
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(window.x, window.y, GAME_TITLE);
  vScreen = LoadRenderTexture(V_SCREEN.x, V_SCREEN.y);
  // SetTargetFPS(TARGET_FPS);

  // Sound Config
  InitAudioDevice();

  // Load stuff
  LoadImages();
  LoadFonts();
  LoadMusic();
  LoadSounds();

  // Game specifics
  PlayMusicStream(music);
  SetRandomSeed(time(nullptr));
  gBird = NewBird(V_SCREEN);

  // Pick input type
  HasValidInput = IsKeyPressed;
  input1 = KEY_SPACE;
  input2 = KEY_ENTER;

  // HasValidInput = IsMouseButtonPressed;
  // input1 = MOUSE_LEFT_BUTTON;
  // input2 = MOUSE_BUTTON_RIGHT;

  smStart();
  smCreateState("title", nullptr, StateTitleUpdate, StateTitleDraw, nullptr);
  smCreateState("countdown", StateCountdownEnter, StateCountdownUpdate,
                StateCountdownDraw, nullptr);
  smCreateState("score", StateScoreEnter, StateScoreUpdate, StateScoreDraw,
                nullptr);
  smCreateState("play", StatePlayEnter, StatePlayUpdate, StatePlayDraw,
                StatePlayExit);

  // Let us begin
  smSetState("title", nullptr);
}

void LoadImages(void) {
  bgImg = LoadTexture(BG_IMG);
  groundImg = LoadTexture(GROUND_IMG);
  pauseImg = LoadTexture(PAUSE_ICON);
  medalGoldImg = LoadTexture(MEDAL_GOLD);
  medalSilverImg = LoadTexture(MEDAL_SILVER);
  medalBronzeImg = LoadTexture(MEDAL_BRONZE);
}

void LoadFonts(void) {
  smallFont = LoadFont(FONT_REGULAR);
  mediumFont = hugeFont = flappyFont = LoadFont(FONT_FLAPPY);

  SetTextureFilter(smallFont.texture, TEXTURE_FILTER_POINT);
  SetTextureFilter(mediumFont.texture, TEXTURE_FILTER_POINT);
  SetTextureFilter(hugeFont.texture, TEXTURE_FILTER_POINT);
  SetTextureFilter(flappyFont.texture, TEXTURE_FILTER_POINT);
}

void LoadMusic(void) { music = LoadMusicStream(MUSIC); }

void LoadSounds(void) {
  explosionSound = LoadSound(EXPLOSION_SOUND);
  hurtSound = LoadSound(HURT_SOUND);
  jumpSound = LoadSound(JUMP_SOUND);
  scoreSound = LoadSound(SCORE_SOUND);
}

// --------------

// Run functions
// -------------
void GameRun(void) {
  while (smIsRunning()) {
    float dt = smGetDt();
    // float dt = GetFrameTime();
    UpdateAll(dt);
    DrawAll();
  }
}

void UpdateAll(float dt) {
  BGUpdate(dt);
  smUpdate(dt);
  GroundUpdate(dt);
  UpdateMusicStream(music);
}

void BGUpdate(float dt) {
  bgScroll -= BG_SCROLL_SPEED * dt;
  bgScroll = fmodf(bgScroll, BG_LOOPING_POINT);
}

void GroundUpdate(float dt) {
  groundScroll -= GROUND_SCROLL_SPEED * dt;
  groundScroll = fmodf(groundScroll, GROUND_SCROLL_SPEED);
}

void DrawAll(void) {
  DrawOnVScreen();
  DrawOnWindow();
}

void DrawOnVScreen(void) {
  BeginTextureMode(vScreen);
  ClearBackground(BLACK);
  DrawTexture(bgImg, bgScroll, 0, WHITE);
  smDraw();
  DrawTexture(groundImg, groundScroll, V_SCREEN.y - groundImg.height, WHITE);
  EndTextureMode();
}

void DrawOnWindow(void) {
  BeginDrawing();
  Rectangle source = {0, 0, V_SCREEN.x, -V_SCREEN.y};
  Rectangle dest = {0, 0, window.x, window.y};
  DrawTexturePro(vScreen.texture, source, dest, (Vector2){0, 0}, 0, WHITE);
  DrawFPS(20, 20);
  EndDrawing();
}

// -------------

// Unload functions
// ----------------
void GameUnload(void) {
  UnloadImages();
  UnloadFonts();
  UnloadMusicAndSounds();
}

void UnloadImages(void) {
  UnloadTexture(bgImg);
  UnloadTexture(groundImg);
  UnloadTexture(pauseImg);

  UnloadTexture(medalGoldImg);
  UnloadTexture(medalSilverImg);
  UnloadTexture(medalBronzeImg);

  BirdUnloadSprite();
  PipeUnloadSprite();
}

void UnloadFonts(void) {
  UnloadFont(smallFont);
  UnloadFont(flappyFont);
}

void UnloadMusicAndSounds(void) {
  UnloadMusicStream(music);
  UnloadSound(explosionSound);
  UnloadSound(hurtSound);
  UnloadSound(jumpSound);
  UnloadSound(scoreSound);
  CloseAudioDevice();
}

// ----------------

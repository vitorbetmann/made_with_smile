// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Dependencies.h"

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

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Main
// —————————————————————————————————————————————————————————————————————————————————————————————————

int main(void) {
  load();
  while (smIsRunning()) {
    update(smGetDt());
    draw();
  }
  unload();
}

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions
// —————————————————————————————————————————————————————————————————————————————————————————————————

void load(void) {
  // raylib
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Breakout");
  SetWindowState(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(24);
  vWindow = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
  InitAudioDevice();

  // sprites
  tdAdd(BACKGROUND, "assets/graphics/background.png");

  // fonts

  // sounds and music

  // SceneManager
  smStart();
  smCreateScene("start", StartEnter, StartUpdate, StartDraw, StartExit);
  smSetScene("start", nullptr);
}

void update(const float dt) {
  // quit
  if (IsKeyPressed(KEY_ESCAPE)) {
    smStop();
  }

  // toggle fps
  if (IsKeyPressed(KEY_T)) {
    displayFPS = !displayFPS;
  }
}

void draw(void) {
  BeginDrawing();
  drawVWindow();
  DrawTexturePro(
      vWindow.texture,
      (Rectangle){0, 0, (float)VIRTUAL_WIDTH, (float)-VIRTUAL_HEIGHT},
      (Rectangle){0, 0, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT},
      (Vector2){0}, 0, WHITE);
  EndDrawing();
}

void drawVWindow(void) {
  BeginTextureMode(vWindow);

  // fps
  if (displayFPS) {
    DrawFPS(10, 10);
  }
  DrawTexture(*tdFind(BACKGROUND), 0, 0, WHITE);

  EndTextureMode();
}

void unload(void) {
  // entities

  // textures
  tdUnloadAll();

  // fonts

  // sounds and music

  CloseAudioDevice();
  CloseWindow();
}

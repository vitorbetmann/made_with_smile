#pragma once

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Data types
// —————————————————————————————————————————————————————————————————————————————————————————————————

typedef enum {
  SMALL = 8,
  MEDIUM = 16,
  LARGE = 32,
} gFontSize;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

// UI
extern Texture pauseTexture;
extern const char *GAME_TITLE;

// Sounds and Music
extern Music music;

// Fonts

// Background
extern Texture background;

// Window
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

// Virtual Window
extern const int VIRTUAL_WIDTH;
extern const int VIRTUAL_HEIGHT;

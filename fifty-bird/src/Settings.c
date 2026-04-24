// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Settings.h"

#include "PipeManager.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

// UI
Texture pauseTexture;
const char *GAME_TITLE = "Fifty Bird";

// Medals
Texture2D medalGold, medalSilver, medalBronze;

// Pipes
Texture pipeTexture;
PipeList gPipeList;

// Sounds and Music
Sound jumpSnd, explosionSnd, hurtSnd, scoreSnd, pauseSnd;
Music music;

// Fonts
Font flappyFont, font;
const int FLAPPY_FONT = 28;
const int SMALL_FONT = 8, MEDIUM_FONT = 14, HUGE_FONT = 56;

// Background
Texture background;
const int BACKGROUND_SCROLL_SPEED = 30;
const int BACKGROUND_LOOPING_POINT = 413;

// Ground
Texture ground;
const int GROUND_SCROLL_SPEED = 60;

// Window
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// Virtual Window
const int VIRTUAL_WIDTH = 512;
const int VIRTUAL_HEIGHT = 288;

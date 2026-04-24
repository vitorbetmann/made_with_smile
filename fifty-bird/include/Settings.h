#ifndef FLAPPY_BIRD_SETTINGS_H
#define FLAPPY_BIRD_SETTINGS_H

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <raylib.h>

#include "PipeManager.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

// UI
extern Texture pauseTexture;
extern const char *GAME_TITLE;

// Medals
extern Texture2D medalGold, medalSilver, medalBronze;

// Pipes
extern PipeList gPipeList;
extern Texture pipeTexture;

// Sounds and Music
extern Sound jumpSnd, explosionSnd, hurtSnd, scoreSnd, pauseSnd;
extern Music music;

// Fonts
Font flappyFont, font;
extern const int FLAPPY_FONT;
extern const int SMALL_FONT, MEDIUM_FONT, HUGE_FONT;

// Background
extern Texture background;
extern const int BACKGROUND_SCROLL_SPEED;
extern const int BACKGROUND_LOOPING_POINT;

// Ground
extern Texture ground;
extern const int GROUND_SCROLL_SPEED;

// Window
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

// Virtual Window
extern const int VIRTUAL_WIDTH;
extern const int VIRTUAL_HEIGHT;

#endif

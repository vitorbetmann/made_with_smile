#include "Settings.h"

// Title
const char *const GAME_TITLE = "Fifty Bird";

// Window
Vector2 window = {1280, 720};
const Vector2 V_SCREEN = {512, 288};
const int BG_LOOPING_POINT = 413, GROUND_LOOPING_POINT = V_SCREEN.x;
const int TARGET_FPS = 30;

// Fonts
const int SMALL_FONT_SIZE = 8;
const int MEDIUM_FONT_SIZE = 14;
const int HUGE_FONT_SIZE = 56;
const int FLAPPY_FONT_SIZE = 28;

// Bird
const int GRAVITY = 450;
const int JUMP_BURST = 300;
const int HITBOX_LEEWAY = 2;

// Pipes
const int LARGEST_PIPE_GAP = 110;
const int PIPE_TOP_MARGIN = 30;
const int PIPE_BOTTOM_MARGIN = 45;
const int PIPE_SHIFT = 20;
const int PIPE_SCORE = 1;

// Scenery
const float BG_SCROLL_SPEED = 30.0f;
const float GROUND_SCROLL_SPEED = 60.0f;
const float PIPE_SCROLL_SPEED = GROUND_SCROLL_SPEED;

// Scoring
const int BRONZE_THRESHOLD = 5;
const int SILVER_THRESHOLD = 10;
const int GOLD_THRESHOLD = 15;

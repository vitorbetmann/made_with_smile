#include "PipePairManager.h"

#include "PipePair.h"
#include "raylib.h"
#include "raymath.h"
#include "Settings.h"
#include "stdlib.h"

// Prototypes
// ----------
static void PipesEnqueue(PipePair *pipePair, PipePairQueue *pipePairs);

static void PipesDequeue(PipePairQueue *pipePairs);

static bool CanGeneratePipePair(float dt);

static void UpdateLastGapY(void);

static void PipePairsUnloadNode(PipePairNode *pipePairNode);

// ----------

// Variables
// ---------
static float spawnTimer;
static float spawnTime[] = {1.5f, 2.0f, 2.5f};
static int index = 1;
static float gapLastY;
static bool playerCanScore;
// ---------

void PipePairManagerInit(void) {
  spawnTimer = 0.0f;
  gapLastY = GetRandomValue(PIPE_TOP_MARGIN,
                            V_SCREEN.y - LARGEST_PIPE_GAP - PIPE_BOTTOM_MARGIN);
}

static void PipesEnqueue(PipePair *pipePair, PipePairQueue *pipePairs) {
  PipePairNode *newNode = malloc(sizeof(PipePairNode));
  if (newNode == NULL) {
    return;
  }

  newNode->pipePair = pipePair;
  newNode->next = NULL;

  if (pipePairs->head == NULL) {
    pipePairs->head = pipePairs->tail = newNode;
  } else {
    pipePairs->tail->next = newNode;
    pipePairs->tail = newNode;
  }
}

static void PipesDequeue(PipePairQueue *pipes) {
  if (pipes->head == NULL) {
    return;
  }
  PipePairNode *temp = pipes->head;
  pipes->head = pipes->head->next;

  if (pipes->head == NULL) {
    pipes->tail = NULL;
  }

  PipePairsUnloadNode(temp);
}

void PipePairsUpdate(PipePairQueue *pipePairs, float dt, Vector2 screen) {
  if (CanGeneratePipePair(dt)) {
    UpdateLastGapY();
    PipePair *newPipePair = NewPipePair((Vector2){screen.x + 32, gapLastY});
    PipesEnqueue(newPipePair, pipePairs);
  }

  PipePairNode *curr = pipePairs->head;
  while (curr != NULL) {
    PipePairUpdate(curr->pipePair, dt);
    PipePairNode *next = curr->next;
    if (curr->pipePair->pos->x < -curr->pipePair->width) {
      PipesDequeue(pipePairs);
    }
    curr = next;
  }
}

static bool CanGeneratePipePair(float dt) {
  spawnTimer += dt;
  if (spawnTimer > spawnTime[index]) {
    spawnTimer = 0.0f;
    index = GetRandomValue(0, 2);
    return true;
  }
  return false;
}

static void UpdateLastGapY(void) {
  gapLastY += GetRandomValue(-PIPE_SHIFT, PIPE_SHIFT);
  gapLastY = Clamp(gapLastY, PIPE_TOP_MARGIN,
                   V_SCREEN.y - LARGEST_PIPE_GAP - PIPE_BOTTOM_MARGIN);
}

void PipePairsDraw(PipePairQueue *pipes) {
  PipePairNode *curr = pipes->head;
  while (curr != NULL) {
    PipePairDraw(curr->pipePair);
    curr = curr->next;
  }
}

void PipePairsUnload(PipePairQueue *pipes) {
  PipePairNode *curr = pipes->head;
  while (curr != NULL) {
    PipePairNode *next = curr->next;
    PipePairsUnloadNode(curr);
    curr = next;
  }

  pipes->head = pipes->tail = NULL;
}

static void PipePairsUnloadNode(PipePairNode *pipePairNode) {
  PipePairUnload(pipePairNode->pipePair);
  free(pipePairNode);
}

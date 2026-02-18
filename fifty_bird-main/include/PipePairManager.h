#ifndef PIPE_PAIR_MANAGER_H
#define PIPE_PAIR_MANAGER_H

#include "PipePair.h"

// Data types
// ----------
typedef struct Pipes_t {
  PipePair *pipePair;
  struct Pipes_t *next;
} PipePairNode;

typedef struct {
  PipePairNode *head;
  PipePairNode *tail;
} PipePairQueue;
// ----------

// Prototypes
// ----------
void PipePairManagerInit(void);
void PipePairsUpdate(PipePairQueue *pipePairs, float dt, Vector2 screen);
void PipePairsDraw(PipePairQueue *pipePairs);
void PipePairsUnload(PipePairQueue *pipePairs);
// ----------

#endif
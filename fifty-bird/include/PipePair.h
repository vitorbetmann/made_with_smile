#ifndef PIPE_PAIR_H
#define PIPE_PAIR_H

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "Pipe.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Data types
// —————————————————————————————————————————————————————————————————————————————————————————————————

typedef struct
{
    Pipe *upper;
    Pipe *lower;
} PipePair;

typedef struct PipePairNode
{
    PipePair *pipePair;
    struct PipePairNode *next;
} PipePairNode;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

PipePair *pipePairInit(void);
void pipePairEnqueue(PipePair *pp);

void pipePairUpdate(const PipePair *pp, float dt);

void pipePairDraw(const PipePair *pp);

void pipePairNodeUnload(PipePairNode *pn);
void pipePairUnload(PipePair *pp);

#endif

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <math.h>
#include <stdlib.h>

#include "PipePair.h"

#include "Bird.h"
#include "Pipe.h"
#include "Settings.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static float lastY;
static constexpr int PIPE_GAPS[] = {90, 120, 150};

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Static 
// —————————————————————————————————————————————————————————————————————————————————————————————————

void pipePairEnqueue(PipePair *pp)
{
    PipePairNode *pn = malloc(sizeof(PipePairNode));
    pn->pipePair = pp;
    pn->next = nullptr;

    if (gPipeList.tail)
    {
        gPipeList.tail->next = pn;
    }
    else
    {
        gPipeList.head = pn;
        gPipeList.active = pn;
    }
    gPipeList.tail = pn;
}

PipePair *pipePairInit(void)
{
    if (!gPipeList.head)
    {
        lastY = (float)GetRandomValue(VIRTUAL_HEIGHT / 2, VIRTUAL_HEIGHT - 10);
    }
    PipePair *pp = malloc(sizeof(PipePair));
    const int gap = PIPE_GAPS[GetRandomValue(0, 2)];
    lastY = (float)fmax(gap + 30,
                        fmin(VIRTUAL_HEIGHT - gap, lastY + (float)GetRandomValue(-20, 20)));
    pp->lower = pipeInit(lastY, BOTTOM);
    const int pHeight = pp->lower->height;
    pp->upper = pipeInit(lastY - (float)pHeight - (float)gap, TOP);
    return pp;
}

void pipePairUpdate(const PipePair *pp, const float dt)
{
    pipeUpdate(pp->upper, dt);
    pipeUpdate(pp->lower, dt);
}

void pipePairDraw(const PipePair *pp)
{
    pipeDraw(pp->upper);
    pipeDraw(pp->lower);
}

void pipePairNodeUnload(PipePairNode *pn)
{
    pipePairUnload(pn->pipePair);
    pn->pipePair = nullptr;
    free(pn);
}

void pipePairUnload(PipePair *pp)
{
    pipeUnload(pp->upper);
    pp->upper = nullptr;

    pipeUnload(pp->lower);
    pp->lower = nullptr;

    free(pp);
}

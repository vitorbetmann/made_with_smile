// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include "PipeManager.h"

#include "Bird.h"
#include "PipePair.h"
#include "Settings.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Prototypes
// —————————————————————————————————————————————————————————————————————————————————————————————————

static void pipePairsDequeue(void);

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Public
// —————————————————————————————————————————————————————————————————————————————————————————————————

void pipeListEnqueue(void)
{
    PipePair *pp = pipePairInit();
    pipePairEnqueue(pp);
}

void pipeListUpdate(const float dt)
{
    if (!gPipeList.head) { return; }

    const PipePair *first = gPipeList.head->pipePair;
    if (first->lower->x < (float)-first->lower->width)
    {
        pipePairsDequeue();
    }

    const PipePairNode *temp = gPipeList.head;
    while (temp)
    {
        pipePairUpdate(temp->pipePair, dt);
        temp = temp->next;
    }

    const PipePairNode *activeNode = gPipeList.active;
    if (activeNode->pipePair->lower->x + (float)activeNode->pipePair->lower->width < gBird.x)
    {
        PlaySound(scoreSnd);
        gBird.score++;
        gPipeList.active = activeNode->next;
    }
}

void pipeListDraw(void)
{
    const PipePairNode *temp = gPipeList.head;
    while (temp)
    {
        pipePairDraw(temp->pipePair);
        temp = temp->next;
    }
}

void pipeListUnload(void)
{
    PipePairNode *temp = gPipeList.head;
    while (temp)
    {
        PipePairNode *next = temp->next;
        pipePairNodeUnload(temp);
        temp = next;
    }
    gPipeList.head = nullptr;
    gPipeList.tail = nullptr;
    gPipeList.active = nullptr;
}

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Static 
// —————————————————————————————————————————————————————————————————————————————————————————————————

void pipePairsDequeue(void)
{
    PipePairNode *temp = gPipeList.head;
    gPipeList.head = temp->next;
    if (!gPipeList.head)
    {
        gPipeList.tail = nullptr;
    }
    pipePairNodeUnload(temp);
}

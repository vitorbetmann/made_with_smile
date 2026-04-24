// —————————————————————————————————————————————————————————————————————————————————————————————————
// Includes
// —————————————————————————————————————————————————————————————————————————————————————————————————

#include <stdlib.h>
#include <raylib.h>

#include "Pipe.h"
#include "Settings.h"

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Variables
// —————————————————————————————————————————————————————————————————————————————————————————————————

static constexpr int PIPE_SCROLL = -60;

// —————————————————————————————————————————————————————————————————————————————————————————————————
// Functions - Static
// —————————————————————————————————————————————————————————————————————————————————————————————————

Pipe *pipeInit(const float y, const Orientation o)
{
    Pipe *p = malloc(sizeof(Pipe));
    p->orientation = o;
    p->sprite = pipeTexture;

    p->x = (float)VIRTUAL_WIDTH;
    p->y = y;

    p->width = p->sprite.width;
    p->height = p->sprite.height;

    return p;
}

void pipeUpdate(Pipe *p, const float dt)
{
    p->x += (float)PIPE_SCROLL * dt;
}

void pipeDraw(const Pipe *p)
{
    if (p->orientation == TOP)
    {
        const Rectangle source = {0, 0, (float)p->width, (float)-p->height};
        const Rectangle dest = {p->x, p->y, (float)p->width, (float)p->height};
        DrawTexturePro(p->sprite, source, dest, (Vector2){0, 0}, 0.0f, WHITE);
    }
    else
    {
        DrawTextureV(p->sprite, (Vector2){p->x, p->y}, WHITE);
    }
}

void pipeUnload(Pipe *p)
{
    free(p);
}

#ifndef FORMAT_H
#define FORMAT_H

#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>
#include "parse.h"

typedef struct {
    int priority;      /***< rendering order >*/
    uint32_t width;    /***< line thickness, 0 for polygons >*/
    uint32_t color;    /***< color from palette >*/
} osmFormat;

typedef struct {
    osmFormat* format; /***< rendering format >*/
    osmWay* way;       /***< way structure >*/
} osmFigure;

/**
 * Rendering Palette
 */
extern osmFigure** queue;
extern uint32_t size;

/**
 * This function creates a rendering format from a way
 */
void
formatWay(osmWay* way);

/**
 * This function call reorders the queue to prepare for rendering
 */
void
sortQueue();

/**
 * This function frees the queue
 */
void
freeQueue();

#endif

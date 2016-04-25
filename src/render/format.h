#ifndef FORMAT_H
#define FORMAT_H

#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>
#include "parse.h"

/**
 * This structure holds a format for an element containing its priority,
 * its width and its color.
 */
typedef struct {
    int priority;      /***< rendering order >*/
    uint32_t width;    /***< line thickness, 0 for polygons >*/
    uint32_t color;    /***< color from palette >*/
} osmFormat;

/**
 * This structure is destined to be stored in the queue for rendering
 */
typedef struct {
    osmFormat* format; /***< rendering format >*/
    osmWay* way;       /***< way structure >*/
} osmFigure;

/**
 * Rendering Palette
 */
extern osmFigure** queue; /***< rendering queue >*/
extern uint32_t size;     /***< rendering queue size >*/

/**
 * This function creates a rendering format from a way
 * @param way osmWay element from the map
 * @return void
 */
void
formatWay(osmWay* way);

/**
 * This function call reorders the queue to prepare for rendering
 * @return void
 */
void
sortQueue();

/**
 * This function frees the queue
 * @return void
 */
void
freeQueue();

#endif

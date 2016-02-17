#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "parse.h"

void
renderOsm(osm* map);

int
renderDoc(const char* docname, uint32_t flags);

#endif

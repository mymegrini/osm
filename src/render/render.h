#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include <SDL2/SDL.h>

#define LOGO_BMP "data/logo480.bmp"

/**
 * Screen dimension constants
 */
int WINDOW_WIDTH;
int WINDOW_HEIGHT;

/**
 * The window we'll be rendering to
 */
SDL_Window* window = NULL;

/**
 * SDL Renderer
 */
SDL_Renderer* renderer = NULL;

/**
 * Map texture
 */
SDL_Texture* maptexture = NULL;

int
renderDoc(const char* docname, uint32_t flags);

#endif

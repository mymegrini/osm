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
 * Palette
 */
const static uint32_t background = 0xceeaffff;
const static uint32_t line = 0x795f5f2e;
const static uint32_t area = 0x7992532e;

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

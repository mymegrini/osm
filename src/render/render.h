#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include <SDL2/SDL.h>

#define LOGO_BMP "data/logo480.bmp"

/**
 * Global rendering variables
 */
int WINDOW_WIDTH;                /***< SDL window width >*/
int WINDOW_HEIGHT;               /***< SDL window height >*/

/**
 * The window we'll be rendering to
 */
SDL_Window* window = NULL;       /***< SDL window >*/

/**
 * SDL Renderer
 */
SDL_Renderer* renderer = NULL;   /***< SDL renderer >*/

/**
 * Map texture
 */
SDL_Texture* maptexture = NULL;  /***< target rendering texture >*/

/**
 * This function takes an osm document and renders it to screen
 * @param docname path to the xml file
 * @param flags customization value
 * @return int 0 on success
 */
int
renderDoc(const char* docname, uint32_t flags);

#endif

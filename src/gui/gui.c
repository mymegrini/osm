#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "render.h"
#include "parse.h"

#define LOGO_BMP "data/logo480.bmp"

/**
 * Screen dimension constants
 */
static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;

/**
 * Palette
 */
const static uint32_t background = 0xceeaffff;
const static uint32_t line = 0x795f5f2e;
const static uint32_t area = 0x7992532e;

/**
 * The window we'll be rendering to
 */
static SDL_Window* window = NULL;

/**
 * SDL Renderer
 */
static SDL_Renderer* renderer = NULL;

/**
 * This function takes care of initializing variables
 */
void
initParameters(){

    //initialize width and height for splash screen
    SCREEN_WIDTH = 480;
    SCREEN_HEIGHT = 480;
}

/**
 * This function initializes SDL and creates a renderer
 */
void
initSDL(){
    
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
	printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	return;
    }
    
    //Create window
    window = SDL_CreateWindow("osmaps",
			      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  
    if( window == NULL ) {
	printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
	return;
    }

    //get Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return;
}

/**
 * This function handles SDL events
 */
int
handleEvents(){
    
    SDL_Event evt;
    
    while(SDL_PollEvent(&evt)) {
	if(evt.type == SDL_QUIT) {
	    
	    //Destroy renderer
	    SDL_DestroyRenderer( renderer );
	    renderer = NULL;
	    
	    //Destroy window
	    SDL_DestroyWindow( window );
	    window = NULL;
	    
	    //Quit SDL subsystems
	    SDL_Quit();
	    
	    return 1;
	}
    }

    return 0;
}

/**
 * This function creates the splash window
 */
void
renderLogo(){

    SDL_Surface* logo = SDL_LoadBMP( LOGO_BMP );

    SDL_Texture* logoT = SDL_CreateTextureFromSurface(renderer, logo);

    SDL_FreeSurface(logo);

    SDL_RenderCopy(renderer, logoT, NULL, NULL);

    SDL_RenderPresent(renderer);

    SDL_RenderClear(renderer);
}

/**
 * This function launches graphical interface
 */
void
launchGUI(char* docname, int flags){

    initParameters();
    
    initSDL();
    
    renderLogo();

    //event loop
    while(1){

	if(handleEvents()) break;

    }
    
    return;
}

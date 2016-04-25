#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "render.h"

/**
 * This function takes care of initializing variables
 * @return void
 */
static void
initParameters(){

    //initialize width and height for splash screen
    WINDOW_WIDTH = 480;
    WINDOW_HEIGHT = 480;

}

/**
 * This function initializes SDL and creates a renderer
 * @return void
 */
static void
initSDL(){
    
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
	printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	return;
    }
    
    //Create window
    window = SDL_CreateWindow("osmaps",
			      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			      WINDOW_WIDTH, WINDOW_HEIGHT,
			      SDL_WINDOW_BORDERLESS | SDL_WINDOW_SHOWN );
  
    if( window == NULL ) {
	printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
	return;
    }

    //get Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if( renderer == NULL ) {
	printf( "Renderer could not be created! SDL_Eroor: %s\n",
		SDL_GetError());
	return;
    }
    
    return;
}

/**
 * This function handles SDL events
 * @return void
 */
static int
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
 * @return void
 */
static void
renderLogo(){

    SDL_Surface* logo = SDL_LoadBMP( LOGO_BMP );

    SDL_Texture* logoT = SDL_CreateTextureFromSurface(renderer, logo);

    SDL_FreeSurface(logo);

    SDL_RenderCopy(renderer, logoT, NULL, NULL);

    SDL_DestroyTexture(logoT);

    SDL_RenderPresent(renderer);

    SDL_Delay(1000);
}

void
launchGUI(char* docname, int flags){

    initParameters();
    
    initSDL();
    
    renderLogo();

    if (renderDoc(docname, flags)) return;

    //event loop
    while(1){
	
	if(handleEvents()) break;

    }
    
    return;
}

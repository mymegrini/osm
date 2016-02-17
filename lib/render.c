#include <stdio.h>
#include <stdlib.h>
#include "render.h"
#include "free.h"

#define MAP "data/logo480.bmp"

/**
 *Screen dimension constants
 */
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;

/**
 *The window we'll be rendering to
 */
SDL_Window* gWindow = NULL;

/**
 *The surface contained by the window
 */
SDL_Surface* gScreenSurface = NULL;

/**
 *The image we will load and show on the screen
 */
SDL_Surface* gMap = NULL;

void
renderOsm(osm* map){

  SDL_Delay(6000);
  return;
}

int
renderDoc(const char* docname, uint32_t flags){

  osm* map;

  //Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
    
  //Create window
  gWindow = SDL_CreateWindow("OSMaps", SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			     SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  
  if( gWindow == NULL ) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
  
  //Get window surface
  gScreenSurface = SDL_GetWindowSurface(gWindow);

  
  
  //Parse Osm xml file
  map = (osm*) malloc(sizeof(osm));
  parseDoc(docname, map);

  //Load image on gOsmaps
  gMap = SDL_LoadBMP(MAP);
  if( gMap == NULL ) {
    printf( "Unable to load image %s! SDL Error: %s\n", MAP, SDL_GetError() );
    return 1;
  }

  //Blit surface
  SDL_BlitSurface(gMap, NULL, gScreenSurface, NULL);

  //Update the surface
  SDL_UpdateWindowSurface( gWindow );

  //render osm tree
  renderOsm(map);
  
  freeOsm(map);

  //Deallocate surface
  SDL_FreeSurface( gMap );
  gMap = NULL;

  //Destroy window
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;

  //Quit SDL subsystems
  SDL_Quit();
  
  return 0;
}

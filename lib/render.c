#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "render.h"
#include "free.h"

#define MAP "data/logo480.bmp"

/**
 * Screen dimension constants
 */
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;

/**
 * Local rendering variables
 */
static int minlat;
static int maxlat;
static int minlon;
static int maxlon;

/**
 * Palette
 */
const static uint32_t background = 0xEEC1CEFF;
const static uint32_t line = 0x650A24FF;
const static uint32_t area = 0x993350FF;

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

/**
 *SDL Renderer
 */
SDL_Renderer* gRenderer = NULL;

Sint16 posx(double lon){
  
  return (Sint16)((lon-minlon)/(maxlon-minlon)*SCREEN_WIDTH);
}

Sint16 posy(double lat){

  return (Sint16)((lat-maxlat)/(minlat-maxlat)*SCREEN_HEIGHT);
}

void
renderArea(osmWay* way){

  int node;
  
  Sint16* vy = (Sint16*) malloc((way->nodec-1)*sizeof(Sint16));
  Sint16* vx = (Sint16*) malloc((way->nodec-1)*sizeof(Sint16));

  for(node = 0; node<way->nodec-1; node++){
    vy[node] = posy(way->nodev[node]->lat);
    vx[node] = posx(way->nodev[node]->lon);
  }

  aapolygonColor(gRenderer, vx, vy, way->nodec-1, area);
  
  free(vy);
  free(vx);
}

void
renderWay(osmWay* way){

  int node;
  if(way->nodec > 0)
    for(node = 0; ++node<way->nodec;)
      aalineColor(gRenderer,
		     posx(way->nodev[node-1]->lon), posy(way->nodev[node-1]->lat),
		     posx(way->nodev[node]->lon), posy(way->nodev[node]->lat),
		     line);
  
  return;
}

void
renderOsm(osm* map){
  
  int way;

  minlat = map->bounds->minlat;
  maxlat = map->bounds->maxlat;
  minlon = map->bounds->minlon;
  maxlon = map->bounds->maxlon;

  //Fill background
  SDL_FillRect(gMap, NULL, background);
  
  //Blit surface
  SDL_BlitSurface(gMap, NULL, gScreenSurface, NULL);

  //Update the surface
  SDL_UpdateWindowSurface( gWindow );
  
  //get Render
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  
  for(way=0; way<map->wayc; way++){
    osmWay* w = map->wayv[way];
    if(w->nodec>2 && w->nodev[0]->id == w->nodev[w->nodec-1]->id)
      renderArea(w);
    else renderWay(w);
  }

  puts("bug");
  return;
}

int
renderDoc(const char* docname, uint32_t flags){

  osm* map; 	
  SDL_Event evt;

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

  //Pause on logo
  SDL_Delay(1000);
  
  //render osm tree
  renderOsm(map);
  
  //Blit surface
  SDL_BlitSurface(gMap, NULL, gScreenSurface, NULL);

  //Update the surface
  SDL_UpdateWindowSurface( gWindow );

  //Wait for close  
  while(1) {
    while(SDL_PollEvent(&evt)) {
      if(evt.type == SDL_QUIT) {
	
	//deallocate osm map
	freeOsm(map);
	
	//Deallocate surface
	SDL_FreeSurface( gMap );
	gMap = NULL;
	
	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	
	//Quit SDL subsystems
	SDL_Quit();
      }
    }
  }

  return 0;
}

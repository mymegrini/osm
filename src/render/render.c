#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include "parse.h"
#include "free.h"

//#define __TRACE_RENDER__
#define LOGO "data/logo480.bmp"
#define WINDOW_SIZE 720

/**
 * Screen dimension constants
 */
static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;

/**
 * Local rendering variables
 */
static double minlat;
static double maxlat;
static double minlon;
static double maxlon;

/**
 * Palette
 */
const static uint32_t background = 0xceeaffff;
const static uint32_t line = 0x795f5f2e;
const static uint32_t area = 0x7992532e;

/**
 *The window we'll be rendering to
 */
SDL_Window* gWindow = NULL;

/**
 *SDL Renderer
 */
SDL_Renderer* gRenderer = NULL;

/**
 * Longitude to coordiante conversion
 */
static Sint16 posx(double lon){
  
  return (Sint16)(SCREEN_WIDTH * (lon-minlon)/(maxlon-minlon));
}

/**
 * Longitude to coordiante conversion
 */
static Sint16 posy(double lat){

  return (Sint16)(SCREEN_HEIGHT * (maxlat-lat)/(maxlat-minlat));
}

void
renderArea(osmWay* way){

  #ifdef __TRACE_RENDER__
  fprintf(stderr, "renderArea(way:%d): ", (way ? way->id : 0));
  #endif

  int node;
  
  Sint16* vy = (Sint16*) malloc((way->nodec-1)*sizeof(Sint16));
  Sint16* vx = (Sint16*) malloc((way->nodec-1)*sizeof(Sint16));

  for(node = 0; node<way->nodec-1; node++){
    vy[node] = posy(way->nodev[node]->lat);
    vx[node] = posx(way->nodev[node]->lon);
    
    #ifdef __TRACE_RENDER__
    fprintf(stderr, "(%d,%d)", vx[node], vy[node]);
    #endif
  }

  #ifdef __TRACE_RENDER__
  fprintf(stderr, "\n");
  #endif

  filledPolygonColor(gRenderer, vx, vy, way->nodec-1, area);
  aapolygonColor(gRenderer, vx, vy, way->nodec-1, area);
  
  free(vy);
  free(vx);
}

void
renderWay(osmWay* way){

  #ifdef __TRACE_RENDER__
  fprintf(stderr, "renderWay(way:%d)", (way? way->id : 0));
  #endif

  int node;
  if(way->nodec > 0)
    for(node = 0; node<way->nodec-1; node++) {
      aalineColor(gRenderer,
		  posx(way->nodev[node]->lon), posy(way->nodev[node]->lat),
		  posx(way->nodev[node+1]->lon), posy(way->nodev[node+1]->lat),
		  line);
    
      #ifdef __TRACE_RENDER__
      fprintf(stderr, "(%d,%d)(%d,%d) ",
	      posx(way->nodev[node]->lon), posy(way->nodev[node]->lat),
	      posx(way->nodev[node+1]->lon), posy(way->nodev[node+1]->lat));
      #endif
    }

    #ifdef __TRACE_RENDER__
    fprintf(stderr, "\n");
    #endif
  return;
}

void
renderOsm(osm* map){

  #ifdef __TRACE_RENDER__
  fprintf(stderr, "renderOsm(map)\n");
  #endif
  
  int way;
  
  //get Renderer
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  //clear screen
  uint8_t* c = (uint8_t*) &background;
  SDL_SetRenderDrawColor(gRenderer, c[0], c[1], c[2], c[3]);
  SDL_RenderClear(gRenderer);
  
  for(way=0; way<map->wayc; way++){
    osmWay* w = map->wayv[way];
    if(w->nodec>2 && w->nodev[0]->id == w->nodev[w->nodec-1]->id)
      renderArea(w);
    else renderWay(w);
  }

  //present Rendered map
  SDL_RenderPresent(gRenderer);
  return;
}

int
renderDoc(const char* docname, uint32_t flags){

  #ifdef __TRACE_RENDER__
  fprintf(stderr, "renderDoc(%s, %d)\n", docname, flags);
  #endif
  
  osm* map; 	
  SDL_Event evt;

  //Parse Osm xml file
  map = (osm*) malloc(sizeof(osm));
  parseDoc(docname, map);

  //Initialize global variables
  minlat = map->bounds->minlat;
  maxlat = map->bounds->maxlat;
  minlon = map->bounds->minlon;
  maxlon = map->bounds->maxlon;
 
  //Determine window width and height
  double ratio = cos(M_PI*(minlat+maxlat)/360);
  if ((maxlat-minlat)<(maxlon-minlon)) {
    SCREEN_WIDTH = WINDOW_SIZE;
    SCREEN_HEIGHT = (int)(WINDOW_SIZE * (maxlat-minlat)
			  /(ratio * (maxlon-minlon)));
  } else {
    SCREEN_WIDTH = (int)(WINDOW_SIZE * (maxlon-minlon) * ratio
			 /(maxlat-minlat));
    SCREEN_HEIGHT = WINDOW_SIZE;
  }
  
  #ifdef __TRACE_RENDER__
  fprintf(stderr, "Screen size: %dx%d (%lf,%lf)\n",
	  SCREEN_WIDTH, SCREEN_HEIGHT,
	  (maxlon-minlon), (maxlat-minlat));
  #endif

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

  //render osm tree
  renderOsm(map);
  
  //Wait for close  
  while(1) {
    while(SDL_PollEvent(&evt)) {
      if(evt.type == SDL_QUIT) {
	
	//deallocate osm map
	freeOsm(map);
	
	//Destroy renderer
	SDL_DestroyRenderer( gRenderer );
	
	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	
	//Quit SDL subsystems
	SDL_Quit();
	
	return 0;
      }
    }
  }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include "parse.h"
#include "free.h"
#include "print.h"
#include "render.h"
#include "format.h"

#ifdef DEBUG
#define __TRACE_RENDER__
#endif

#define WINDOW_SIZE 640
#define MS_FACTOR 2

/**
 * Local rendering variables
 */
static double minlat;
static double maxlat;
static double minlon;
static double maxlon;
static int MAP_WIDTH;
static int MAP_HEIGHT;

/**
 * Palette
 */
const static uint32_t background = 0xceeaffff;
static uint32_t line = 0x795f5f2e;
static uint32_t area = 0x7992532e;

/**
 * Longitude to coordiante conversion
 */
static Sint16 posx(double lon){
  
  return (Sint16)(MAP_WIDTH * (lon-minlon)/(maxlon-minlon));
}

/**
 * Longitude to coordiante conversion
 */
static Sint16 posy(double lat){

  return (Sint16)(MAP_HEIGHT * (maxlat-lat)/(maxlat-minlat));
}

void
renderWay(osmWay* way){

  #ifdef __TRACE_RENDER__
  fprintf(stderr, "renderWay(way:%d)", (way? way->id : 0));
  #endif

  int node;
  if(way->nodec > 0)
    for(node = 0; node<way->nodec-1; node++) {
      aalineColor(renderer,
		  posx(way->nodev[node]->lon), posy(way->nodev[node]->lat),
		  posx(way->nodev[node+1]->lon), posy(way->nodev[node+1]->lat),
		  //MS_FACTOR,
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

  filledPolygonColor(renderer, vx, vy, way->nodec-1, area);
  aapolygonColor(renderer, vx, vy, way->nodec-1, area);  
  free(vy);
  free(vx);
  
}

void
renderOsm(osm* map){

  #ifdef __TRACE_RENDER__
  fprintf(stderr, "renderOsm(map)\n");
  #endif
  
  int way;
  
  //clear screen
  uint8_t* c = (uint8_t*) &background;
  SDL_SetRenderDrawColor(renderer, c[0], c[1], c[2], c[3]);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  
  for(way=0; way<map->wayc; way++){
    osmWay* w = map->wayv[way];
    if(w->nodec>2 && w->nodev[0]->id == w->nodev[w->nodec-1]->id)
      renderArea(w);
    else renderWay(w);
  }
    
  return;
}

void
renderFormat(osm* map){

    #ifdef __TRACE_RENDER__
    fprintf(stderr, "renderFormat(map)\n");
    #endif
    
    int way;
    
    //clear screen
    uint8_t* c = (uint8_t*) &background;
    SDL_SetRenderDrawColor(renderer, c[0], c[1], c[2], c[3]);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    //allocate queue
    queue = malloc(sizeof(osmFigure*)*(map->wayc-1));

    //filling rendering queue
    for(way=0; way<map->wayc; way++)
	formatWay(map->wayv[way]);

    //rendering queue
    for(way=0; way<size; way++){
	if(queue[way]->format->width){
	    line = queue[way]->format->color;
	    renderWay(queue[way]->way);
	} else {
	    line = area = queue[way]->format->color;
	    renderArea(queue[way]->way);
	}
    }

    //emptying queue
    freeQueue();
  
    return ;
}
static int
resetSDL(){
    
  //Destroy renderer
  SDL_DestroyRenderer( renderer );
  renderer = NULL;
  
  //Destroy window
  SDL_DestroyWindow( window );
  window = NULL;
  
  //Create window
  window = SDL_CreateWindow("osmaps",
			    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			    WINDOW_WIDTH, WINDOW_HEIGHT,
			    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
  
  if( window == NULL ) {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return 1;
  }
  
  //get Renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC
				| SDL_RENDERER_TARGETTEXTURE
				| SDL_RENDERER_ACCELERATED);
  
  if( renderer == NULL ) {
      printf( "Renderer could not be created! SDL_Eroor: %s\n",
	      SDL_GetError());
      return 1;
  }

  //clear screen
  uint8_t* c = (uint8_t*) &background;
  SDL_SetRenderDrawColor(renderer, c[0], c[1], c[2], c[3]);
  SDL_RenderClear(renderer);
  
  return 0;
}

int
renderDoc(const char* docname, uint32_t flags){

  #ifdef __TRACE_RENDER__
  fprintf(stderr, "renderDoc(%s, %d)\n", docname, flags);
  #endif
  
  osm* map;
  
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
  if ((maxlat-minlat)>(maxlon-minlon)) {
    WINDOW_WIDTH = WINDOW_SIZE;
    WINDOW_HEIGHT = (int)(WINDOW_SIZE * (maxlat-minlat)
			  /(ratio * (maxlon-minlon)));
  } else {
    WINDOW_WIDTH = (int)(WINDOW_SIZE * (maxlon-minlon) * ratio
			 /(maxlat-minlat));
    WINDOW_HEIGHT = WINDOW_SIZE;
  }
  
  #ifdef __TRACE_RENDER__
  fprintf(stderr, "Screen size: %dx%d (%lf,%lf)\n",
	  WINDOW_WIDTH, WINDOW_HEIGHT,
	  (maxlon-minlon), (maxlat-minlat));
  #endif

  //reset SDL
  if(resetSDL()) {

      freeOsm(map);
      return 1;
  }

  //Create map texture and set it as rendering target
  MAP_WIDTH = WINDOW_WIDTH * MS_FACTOR;
  MAP_HEIGHT = WINDOW_HEIGHT * MS_FACTOR;
  
  //SDL Hints
  if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2") == SDL_FALSE)
      puts( "Failed to set rendering scale quality.");
    
  maptexture = SDL_CreateTexture(renderer,
				 SDL_GetWindowPixelFormat(window), 
				 SDL_TEXTUREACCESS_TARGET,
				 MAP_WIDTH,
				 MAP_HEIGHT);

  SDL_SetRenderTarget(renderer, maptexture);
  SDL_RenderSetViewport(renderer, NULL);  
  
  //render osm tree
  if (flags | F_EXT)
      renderFormat(map);
  else renderOsm(map);

  //free osm structure
  freeOsm(map);

  //reset rendering target  
  SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderSetViewport(renderer, NULL);

  //copy map to window while downscaling by MS_FACTOR
  SDL_RenderCopy(renderer, maptexture, NULL, NULL);  

  //present Rendered map
  SDL_RenderPresent(renderer);
  
  return 0;
}

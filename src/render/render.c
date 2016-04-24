#include <stdio.h>
#include <stdlib.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include "parse.h"
#include "free.h"
#include "render.h"

#ifdef DEBUG
#define __TRACE_RENDER__
#endif

#define WINDOW_SIZE 640

/**
 * Local rendering variables
 */
static double minlat;
static double maxlat;
static double minlon;
static double maxlon;

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

  filledPolygonColor(renderer, vx, vy, way->nodec-1, area);
  aapolygonColor(renderer, vx, vy, way->nodec-1, area);
  
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
      aalineColor(renderer,
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
    
  //present Rendered map
  SDL_RenderPresent(renderer);
  return;
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
  
  //Destroy renderer
  SDL_DestroyRenderer( renderer );
  renderer = NULL;
  
  //Destroy window
  SDL_DestroyWindow( window );
  window = NULL;
  
  //Create window
  window = SDL_CreateWindow("osmaps",
			    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN );
  
  if( window == NULL ) {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return 1;
  }
  
  //get Renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE
				| SDL_RENDERER_ACCELERATED);
  
  if( renderer == NULL ) {
      printf( "Renderer could not be created! SDL_Eroor: %s\n",
	      SDL_GetError());
      return 1;
  }
    
  //render osm tree
  renderOsm(map);

  //free osm structure
  freeOsm(map);

  return 0;
}

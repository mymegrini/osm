#include "sort.h"

/**
 * 
 * 
 * 
 * 
 */
void
sortNodes(osmNode** nodev, uint32_t nodec){

  
  return;
}

/**
 * 
 * 
 * 
 * 
 */
osmWay*
findNode(osm* map, uint32_t id){
int i;
i=map->nodec;
while( i > 0){
if(map->wayv[i]->id != id)
i--;
}
return *(map->wayv);
}

/**
 * 
 * 
 * 
 * 
 */
void
sortWays(osmNode** wayv, uint32_t wayc){

  return;
}

/**
 * 
 * 
 * 
 * 
 */
osmWay*
findWay(osmWay** wayv, uint32_t id){

  return *wayv; //place holder
}

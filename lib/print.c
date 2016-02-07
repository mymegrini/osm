#include "print.h"

/**
 * 
 * 
 * 
 */
void
printTag(const osmTag* tag){
}

/**
 * 
 * 
 * 
 */
void
printBounds(const osmBounds* bounds){
  
  printf("Bounds:\n\tminlat: %f\n\tmaxlat: %f\n\tminlon: %f\n\tmaxlon: %f\n",
	 bounds->minlat, bounds->maxlat, bounds->minlon, bounds->maxlon);
  return;
}
 
/**
 * 
 * 
 * 
 */
void
printNode(const osmNode* node){

  return;
}
 
/**
 * 
 * 
 * 
 */
void
printWay(const osmWay* way){

  return;
}
 
/**
 * 
 * 
 * 
 */
void
printRelation(const osmRelation* relation){

  return;
}

/**
 * 
 * 
 * 
 * 
 */
void
printDoc(const char *docname, int flags){
  
  osm map;
  int i;
  
  parseDoc(docname, &map);
  
  if (flags|F_BOUNDS)
    printBounds(map.bounds);

  if (flags|F_NODES)
    for(i=0; i<map.nodec; i++){
      printNode(map.nodev[i]);
    }
  
  if (flags|F_WAYS)
    for(i=0; i<map.wayc; i++){
      printWay(map.wayv[i]);
    }
  
  if (flags|F_RELATIONS)
    for(i=0; i<map.relationc; i++){
      printRelation(map.relationv[i]);
    }
  
  return;
}

#include "print.h"

/**
 * 
 * 
 * 
 */
void
printTag(const osmTag* tag){

  printf("Tag: (%s : %s)\n", tag->k, tag->v);
  return;
}

/**
 * 
 * 
 * 
 */
void
printBounds(const osmBounds* bounds){
  
  printf("Bounds:\n\tminlat: %f maxlat: %f\n\tminlon: %f -maxlon: %f\n",
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

  int t;
  printf("Node: %d\n\tlatitude: %lf longitude: %lf\n",
	 node->id, node->lat, node->lon);
  for(t=0; t < node->tagc; t++){printf("\t"); printTag(node->tagv[t]);}
  return;
}
 
/**
 * 
 * 
 * 
 */
void
printWay(const osmWay* way){
  /* 
   *printf("Way: %d\n\t", way->id);
   *for(int t=0;t< way->nodec; t++){printf("\t"); printNode(way->nodev[t]);}
   *for(int t=0;t< way->tagc;t++){printf("\t"); printTag(way->tagv[t];}
   */
  return;
}
 
/**
 * 
 * 
 * 
 */
void
printRelation(const osmRelation* relation){
  /*
   *printf("Relation: %d\n\t", relation->id);
   *for(int t=0; t< relation->wayc;t++){printf("\t"); printWay(relation->wayv[t]);}
   */
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
  
  if (flags & F_BOUNDS)
    printBounds(map.bounds);

  if (flags & F_NODES)
    for(i=0; i<map.nodec; i++){
      printNode(map.nodev[i]);
    }
  
  if (flags & F_WAYS)
    for(i=0; i<map.wayc; i++){
      printWay(map.wayv[i]);
    }
  
  if (flags & F_RELATIONS)
    for(i=0; i<map.relationc; i++){
      printRelation(map.relationv[i]);
    }
  
  return;
}

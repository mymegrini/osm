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
  printf("Node:\t(%d)\tlat: %lf\tlon: %lf\n",
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

  int i;
  printf("Way:\t(%d)\n", way->id);
  for(i=0; i<way->nodec; i++) printf("\tNode:\t(%d)\n", way->nodev[i]->id);
  for(i=0; i < way->tagc; i++){printf("\t"); printTag(way->tagv[i]);}
  return;
}
 
/**
 * 
 * 
 * 
 */
void
printRelation(const osmRelation* relation){

  int i;
  printf("Relation:\t(%d)\n", relation->id);
  for(i=0; i<relation->nodec; i++)
    printf("\tNode:\t(%d)\n", relation->nodev[i]->id);
  for(i=0; i<relation->wayc; i++)
    printf("\tWay:\t(%d)\n", relation->wayv[i]->id);
  for(i=0; i < relation->tagc; i++)
    {printf("\t"); printTag(relation->tagv[i]);}
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

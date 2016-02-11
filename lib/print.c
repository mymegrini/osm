#include "print.h"

#define SPACE "  "

/**
 * 
 * 
 * 
 */
void
printTag(const osmTag* tag){

  printf("Tag:\t(%s):  \t%s\n", tag->k, tag->v);
  return;
}

/**
 * 
 * 
 * 
 */
void
printBounds(const osmBounds* bounds){
  
  printf("Bounds:\n\tminlat= %f \tmaxlat= %f\n\tminlon= %f \tmaxlon= %f\n",
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
  printf("Node:\t(%d)\tlat= %lf\tlon= %lf\n",
	 node->id, node->lat, node->lon);
  for(t=0; t < node->tagc; t++)
    {printf(SPACE); printTag(node->tagv[t]);}
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
  for(i=0; i<way->nodec; i++)
    printf("%sNode:\t(%d)\n", SPACE, way->nodev[i]->id);
  for(i=0; i < way->tagc; i++)
    {printf(SPACE); printTag(way->tagv[i]);}
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
    printf("%sNode:\t(%d)\n", SPACE, relation->nodev[i]->id);
  for(i=0; i<relation->wayc; i++)
    printf("%sWay:\t(%d)\n", SPACE, relation->wayv[i]->id);
  for(i=0; i < relation->tagc; i++)
    {printf(SPACE); printTag(relation->tagv[i]);}
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
  
  if (flags & F_BOUNDS){
    printBounds(map.bounds);
    puts("");
  }

  if (flags & F_NODES){
    printf("%d\n", map.nodec);
    for(i=0; i<map.nodec; i++){
      printNode(map.nodev[i]);
    }
    puts("");
  }
  
  if (flags & F_WAYS){
    printf("%d\n", map.nodec);
    for(i=0; i<map.wayc; i++){
      printWay(map.wayv[i]);
    }
    puts("");
  }
  
  if (flags & F_RELATIONS){
    printf("%d\n", map.nodec);
    for(i=0; i<map.relationc; i++){
      printRelation(map.relationv[i]);
    }
    puts("");
  }
  
  return;
}

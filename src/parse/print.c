#include <string.h>
#include <stdio.h>
#include "print.h"
#include "sort.h"

#define SPACE " L_"
#define SPACE_S 3

/**
 * 
 * 
 * 
 */
void
printTag(const osmTag* tag){

  char line[72 - SPACE_S];

  snprintf(line, 72 - SPACE_S, "Tag:\t\t(%s): %s", tag->k, tag->v);
  if (strlen(line) > 70-SPACE_S) printf("%.*s...\n", 67-SPACE_S, line);
  else puts(line);
  
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
printElement(const char *docname, uint32_t id){
  
  osm map;
  osmNode* nd;
  osmWay* wy;
  osmRelation* rl;
  
  parseDoc(docname, &map);

  if ((nd=findNode(&map, id))) printNode(nd);
  else if ((wy=findWay(&map, id))) printWay(wy);
  else if ((rl=findRelation(&map, id))) printRelation(rl);
  else printf("Not found.\n");

  return;
}

/**
 * 
 * 
 * 
 * 
 */
void
printDoc(const char *docname, uint32_t flags){
  
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
    printf("%d\n", map.wayc);
    for(i=0; i<map.wayc; i++){
      printWay(map.wayv[i]);
    }
    puts("");
  }
  
  if (flags & F_RELATIONS){
    printf("%d\n", map.relationc);
    for(i=0; i<map.relationc; i++){
      printRelation(map.relationv[i]);
    }
    puts("");
  }
  
  return;
}

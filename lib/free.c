#include "free.h"

/**
 *
 * freeTag frees the ressources allocated for an osmTag structure
 */
void
freeTag(osmTag* tag){

  free(tag->k);
  free(tag->v);
  free(tag);
}

/**
 *
 * freeNode frees the ressources allocated for an osmNode structure
 */
void
freeNode(osmNode* node){

  int c;
  for(c=0; c<node->tagc; c++) freeTag(node->tagv[c]);
  free(node);
}

/**
 *
 * freeNode frees the ressources allocated for an osmWay structure
 */
void
freeWay(osmWay* way){

  int c;
  for(c=0; c<way->tagc; c++) freeTag(way->tagv[c]);
  free(way->tagv);
  for(c=0; c<way->nodec; c++) freeNode(way->nodev[c]);
  free(way->nodev);
  free(way);
}

/**
 *
 * freeRelation frees the ressources allocated for an osmRelation structure
 */
void
freeRelation(osmRelation* relation){

  int c;
  for(c=0; c<relation->tagc; c++) freeTag(relation->tagv[c]);
  free(relation->tagv);
  for(c=0; c<relation->nodec; c++) freeNode(relation->nodev[c]);
  free(relation->nodev);
  for(c=0; c<relation->wayc; c++) freeWay(relation->wayv[c]);
  free(relation->wayv);
  for(c=0; c<relation->relationc; c++) freeRelation(relation->relationv[c]);
  free(relation->relationv);
  free(relation);
}

/**
 *
 * freeOsm frees the ressources allocated for an osmOsm structure
 */
void
freeOsm(osm* map){

  int c;
  for(c=0; c<map->nodec; c++) freeNode(map->nodev[c]);
  free(map->nodev);
  for(c=0; c<map->wayc; c++) freeWay(map->wayv[c]);
  free(map->wayv);
  for(c=0; c<map->relationc; c++) freeRelation(map->relationv[c]);
  free(map->relationv);
  free(map->bounds);
  free(map);
}


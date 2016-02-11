#include "sort.h"
#include <stdlib.h>

/**
 * @brief comparison function for osmNode structures
 * @param n1 pointer to first osmNode structure
 * @param n2 pointer to second osmNode structure
 * @return int difference between id of \p n2 id and id of \p n1
 */
static int cmpNode(const void* n1, const void* n2){
  return ((osmNode*)n2)->id-((osmNode*)n1)->id;
}

/**
 * @brief comparison function for osmWay structures
 * @param n1 pointer to first osmWay structure
 * @param n2 pointer to second osmWay structure
 * @return int difference between id of \p n2 id and id of \p n1
 */
static int cmpWay(const void* n1, const void* n2){
  return ((osmWay*)n2)->id-((osmWay*)n1)->id;
}

/**
 * @brief comparison function for osmRelation structures
 * @param n1 pointer to first osmRelation structure
 * @param n2 pointer to second osmRelation structure
 * @return int difference between id of \p n2 id and id of \p n1
 */
static int cmpRelation(const void* n1, const void* n2){
  return ((osmRelation*)n2)->id-((osmRelation*)n1)->id;
}

/**
 *
 * sortNodes uses qsort to sort \p nodev, with cmpNode as the comparison function
 */
void
sortNodes(osmNode** nodev, uint32_t nodec){

  qsort(nodev, nodec, sizeof(osmNode *), cmpNode);
  return;
}

/**
 *
 * sortWays uses qsort to sort \p wayv, with cmpWay as the comparison function
 */
void
sortWays(osmWay** wayv, uint32_t wayc){

  qsort(wayv, wayc, sizeof(osmWay *), cmpWay);
  return;
}

/**
 *
 * sortRelations uses qsort to sort \p relationv, with cmpRelation as the 
 * comparison function
 */
void
sortRelations(osmRelation** relationv, uint32_t relationc){

  qsort(relationv, relationc, sizeof(osmRelation *), cmpRelation);
  return;
}

/*
 * 
 * 
 * 
 * 
 */
osmNode*
findNode(osmNode** nodev, uint32_t id){

  return *nodev; //place holder
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

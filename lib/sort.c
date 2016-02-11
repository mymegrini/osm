#include <stdlib.h>
#include "sort.h"
#include "print.h"

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief comparison function for osmNode structures
 * @param p1 pointer to first osmNode structure
 * @param p2 pointer to second osmNode structure
 * @return int difference between id of \p p2 id and id of \p p1
 */
static int cmpNode(const void* p1, const void* p2){
  
  osmNode* np2 = *(osmNode* const*)p2;
  osmNode* np1 = *(osmNode* const*)p1;
  return np1->id - np2->id;
}

/**
 * @brief comparison function for osmWay structures
 * @param p1 pointer to first osmWay structure
 * @param p2 pointer to second osmWay structure
 * @return int difference between id of \p p2 id and id of \p p1
 */
static int cmpWay(const void* p1, const void* p2){

  osmNode* wp2 = *(osmNode* const*)p2;
  osmNode* wp1 = *(osmNode* const*)p1;
  return wp1->id - wp2->id;
}

/**
 * @brief comparison function for osmRelation structures
 * @param p1 pointer to first osmRelation structure
 * @param p2 pointer to second osmRelation structure
 * @return int difference between id of \p p2 id and id of \p p1
 */
static int cmpRelation(const void* p1, const void* p2){
  
  osmNode* rp2 = *(osmNode* const*)p2;
  osmNode* rp1 = *(osmNode* const*)p1;
  return rp1->id - rp2->id;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/**
 *
 * sortNodes uses qsort to sort \p nodev, with cmpNode as the comparison function
 */
void
sortNodes(osmNode** nodev, uint32_t nodec){

  qsort(nodev, nodec, sizeof(osmNode*), &cmpNode);
  return;
}

/**
 *
 * sortWays uses qsort to sort \p wayv, with cmpWay as the comparison function
 */
void
sortWays(osmWay** wayv, uint32_t wayc){

  qsort(wayv, wayc, sizeof(osmWay*), cmpWay);
  return;
}

/**
 *
 * sortRelations uses qsort to sort \p relationv, with cmpRelation as the 
 * comparison function
 */
void
sortRelations(osmRelation** relationv, uint32_t relationc){

  qsort(relationv, relationc, sizeof(osmRelation*), cmpRelation);
  return;
}

/*
 * 
 * findNode implements a dichotomic search in \p nodev assumed to be in
 * ascending sorted order
 */
osmNode*
findNode(osmNode** nodev, uint32_t nodec, uint32_t id){

  uint32_t _id = nodev[nodec/2]->id;
  if (nodec>0){
    if(_id==id) return nodev[nodec/2];
    else if (_id>id) return findNode(nodev, nodec/2, id); 
    else return findNode(nodev+(nodec/2)+1, nodec-1-(nodec/2), id);
  } else return (_id==id ? nodev[0] : NULL);
}

/**
 *  
 * findWay implements a dichotomic search in \p wayv assumed to be in
 * ascending sorted order
 */
osmWay*
findWay(osmWay** wayv, uint32_t wayc, uint32_t id){

  uint32_t _id = wayv[wayc/2]->id;
  if (wayc>0){
    if(_id==id) return wayv[wayc/2];
    else if (_id>id) return findWay(wayv, wayc/2, id); 
    else return findWay(wayv+(wayc/2)+1, wayc-1-(wayc/2), id);
  } else return (_id==id ? wayv[0] : NULL);
}

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
static int _cmpNode(const void* p1, const void* p2){
  
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
static int _cmpWay(const void* p1, const void* p2){

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
static int _cmpRelation(const void* p1, const void* p2){
  
  osmNode* rp2 = *(osmNode* const*)p2;
  osmNode* rp1 = *(osmNode* const*)p1;
  return rp1->id - rp2->id;
}

/**
 * @brief This function finds a 'node' in a sorted 'node' vector
 * @param[in] id node id
 * @param[out] nodev node vector
 * @return pointer to the 'id' node
 */
static osmNode*
_findNode(osmNode** nodev, uint32_t nodec, uint32_t id){  

  uint32_t _id;
  switch(nodec){
  case 0 :
    return NULL;
  case 1 :
    return (id == nodev[0]->id ? nodev[0] : NULL);
  default :
    _id = nodev[nodec/2]->id;
    if(_id==id) return nodev[nodec/2];
    else if (_id>id) return _findNode(nodev, nodec/2, id); 
    else return _findNode(nodev+(nodec/2)+1, nodec-1-(nodec/2), id);
  }
}

/**
 * @brief This function finds a 'way' in a sorted 'way' vector
 * @param[in] id way id
 * @param[out] wayv way vector
 * @return pointer to the 'id' way
 */
static osmWay*
_findWay(osmWay** wayv, uint32_t wayc, uint32_t id){  

  uint32_t _id;
  switch(wayc){
  case 0 :
    return NULL;
  case 1 :
    return (id == wayv[0]->id ? wayv[0] : NULL);
  default :
    _id = wayv[wayc/2]->id;
    if(_id==id) return wayv[wayc/2];
    else if (_id>id) return _findWay(wayv, wayc/2, id); 
    else return _findWay(wayv+(wayc/2)+1, wayc-1-(wayc/2), id);
  }
}

/**
 * @brief This function finds a 'relation' in a sorted 'relation' vector
 * @param[in] id relation id
 * @param[out] relationv relation vector
 * @return pointer to the 'id' relation
 */
static osmRelation*
_findRelation(osmRelation** relationv, uint32_t relationc, uint32_t id){  

  uint32_t _id;
  switch(relationc){
  case 0 :
    return NULL;
  case 1 :
    return (id == relationv[0]->id ? relationv[0] : NULL);
  default :
    _id = relationv[relationc/2]->id;
    if(_id==id) return relationv[relationc/2];
    else if (_id>id) return _findRelation(relationv, relationc/2, id); 
    else return _findRelation(relationv+(relationc/2)+1,
			      relationc-1-(relationc/2), id);
  }
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/*
 * 
 * findNode implements a dichotomic search (and sorts the array if necessary 
 * using qsort and _cmpNode)
 */
osmNode*
findNode(osm* map, uint32_t id){

  #ifdef __TRACE_SORT__
  fprintf(stderr, "findNode(map, %d)\n", id);
  #endif

  if(map->nodev_s) 
    qsort(map->nodev, map->nodec, sizeof(osmNode*), &_cmpNode);

  map->nodev_s = 0;

  return _findNode(map->nodev, map->nodec, id);
}

/*
 * 
 * findWay implements a dichotomic search (and sorts the array if necessary 
 * using qsort and _cmpWay)
 */
osmWay*
findWay(osm* map, uint32_t id){

  #ifdef __TRACE_SORT__
  fprintf(stderr, "findWay(map, %d)\n", id);
  #endif
  
  if(map->wayv_s) 
    qsort(map->wayv, map->wayc, sizeof(osmWay*), &_cmpWay);

  map->wayv_s = 0;

  return _findWay(map->wayv, map->wayc, id);
}

/*
 * 
 * findRelation implements a dichotomic search (and sorts the array if necessary 
 * using qsort and _cmpRelation)
 */
osmRelation*
findRelation(osm* map, uint32_t id){

  #ifdef __TRACE_SORT__
  fprintf(stderr, "findRelation(map, %d)\n", id);
  #endif
  
  if(map->relationv_s) 
    qsort(map->relationv, map->relationc, sizeof(osmRelation*), &_cmpRelation);

  map->relationv_s = 0;

  return _findRelation(map->relationv, map->relationc, id);
}

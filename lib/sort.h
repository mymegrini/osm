#ifndef SORT_H
#define SORT_H

#include "parse.h"

/**
 * @brief This function finds a 'node' in an osm tree
 * @param[in] id node id
 * @param[in] map osm tree
 * @return pointer to the 'id' node
 */
osmNode*
findNode(osm* map, uint32_t id);

/**
 * @brief This function finds a 'way' in an osm tree
 * @param[in] id way id
 * @param[in] map osm tree
 * @return pointer to the 'id' way
 */
osmWay*
findWay(osm* map, uint32_t id);

/**
 * @brief This function finds a 'relation' in an osm tree
 * @param[in] id relation id
 * @param[in] map osm tree
 * @return pointer to the 'id' relation
 */
osmRelation*
findRelation(osm* map, uint32_t id);

#endif

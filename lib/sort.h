#ifndef SORT_H
#define SORT_H

#include "parse.h"

/**
 * @brief This function sorts a 'node' vector
 * @param[in] nodec node vector size
 * @param[out] nodev node vector
 * @return void
 */
void
sortNodes(osmNode** nodev, uint32_t nodec);

/**
 * @brief This function finds a 'node' in a sorted 'node' vector
 * @param[in] id node id
 * @param[out] nodev node vector
 * @return pointer to the 'id' node
 */
osmWay*
findNode(osm* map, uint32_t id);

/**
 * @brief This function sorts a 'way' vector
 * @param[in] wayc way vector size
 * @param[out] wayv waye vector
 * @return void
 */
void
sortWays(osmNode** wayv, uint32_t wayc);

/**
 * @brief This function finds a 'way' in a sorted 'way' vector
 * @param[in] id way id
 * @param[out] wayv way vector
 * @return pointer to the 'id' way
 */
osmWay*
findWay(osmWay** wayv, uint32_t id);

#endif

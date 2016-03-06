#include "parse.h"

/**
 * @brief This function deletes a 'tag' object
 * @param[in] tag pointer to the structure to be freed
 * @return void
 */
void
freeTag(osmTag* tag);

/**
 * @brief This function deletes a 'node' object
 * @param[in] node pointer to the structure to be freed
 * @return void
 */
void
freeNode(osmNode* node);

/**
 * @brief This function deletes a 'way' object
 * @param[in] way pointer to the structure to be freed
 * @return void
 */
void
freeWay(osmWay* way);

/**
 * @brief This function deletes a 'relation' object
 * @param[in] relation pointer to the structure to be freed
 * @return void
 */
void
freeRelation(osmRelation* relation);

/**
 * @brief This function deletes an osm tree
 * @param[in] map pointer to the structure to be freed
 * @return void
 */
void
freeOsm(osm* map);

#ifndef PRINT_H
#define PRINT_H

#include "parse.h"

#define F_BOUNDS 1     /***< print 'bounds' node */
#define F_NODES 2      /***< print 'node' nodes */
#define F_WAYS 4       /***< print 'way' nodes */
#define F_RELATIONS 8  /***< print 'relation' nodes */
#define F_TEXT 15      /***< print in text form */

/**
 * @brief This function prints attribute values for a 'tag' node
 * @param[in] tag 'tag' node structure
 * @return void
 */
void
printTag(const osmTag* tag);

/**
 * @brief This function prints attribute values for a 'bounds' node
 * @param[in] bounds 'bounds' structure
 * @return void
 */
void
printBounds(const osmBounds* bounds);

/**
 * @brief This function prints attribute values for a 'node' node
 * @param[in] node 'node' structure
 * @return void
 */
void
printNode(const osmNode* node);

/**
 * @brief This function prints structure of a 'way' subtree
 * @param[in] way 'way' structure
 * @return void
 */
void
printWay(const osmWay* way);

/**
 * @brief This function prints attribute values for a 'relation' node
 * @param[in] relation 'relation' structure
 * @return void
 */
void
printRelation(const osmRelation* relation);

/**
 * @brief This function parses an osm file and prints its contents
 * @param[in] flags selects which nodes are printed
 * @param[in] docname filename of osm file
 * @return void
 */
void
printDoc(const char *docname, int flags);

#endif

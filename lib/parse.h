#ifndef PARSE_H
#define PARSE_H

#include <libxml/xmlmemory.h>
#include <stdint.h>

/**
 * A structure to hold a 'tag' node
 */
typedef struct {
  xmlChar* k;                 /***< key >*/
  xmlChar* v;                 /***< value >*/
} osmTag;

/**
 * A structure to hold a 'node' node or subtree
 */
typedef struct {
  uint32_t id;                /***< id number >*/
  double lat;                 /***< latitude coordinate >*/
  double lon;                 /***< longitude coordinate >*/
  uint32_t tagc;              /***< tags cardinal >*/
  osmTag** tagv;              /***< tags vector >*/
} osmNode;

/**
 * A structure to hold the 'bounds' node
 */
typedef struct {
  double minlat;              /***< latitude's lower bound >*/
  double maxlat;              /***< latitude's upper bound >*/
  double minlon;              /***< longitude's lower bound >*/
  double maxlon;              /***< longitude's upper bound >*/
} osmBounds;

/**
 * A structure to hold a 'way' subtree
 */
typedef struct {
  uint32_t id;                /***< id number >*/
  uint32_t nodec;             /***< nodes cardinal >*/
  osmNode** nodev;            /***< nodes vector >*/
  uint32_t tagc;              /***< tags cardinal >*/
  osmTag** tagv;              /***< tags vector >*/
} osmWay;

/**
 * A structure to hold a relation subtree
 */
typedef struct {
  uint32_t id;                /***< id number >*/
  uint32_t nodec;             /***< nodes cardinal >*/
  osmWay** nodev;             /***< nodes vector >*/
  uint32_t wayc;              /***< ways cardinal >*/
  osmWay** wayv;              /***< ways vector >*/
  uint32_t tagc;              /***< tags cardinal >*/
  osmTag** tagv;              /***< tags vector >*/
} osmRelation;

/**
 * A structure to hold an osm tree
 */
typedef struct {
  osmBounds* bounds;         /***< 'bounds' node >*/
  uint32_t nodec;            /***< nodes cardinal >*/
  osmNode** nodev;           /***< nodes vector >*/
  uint8_t nodev_s;           /***< null if nodev is sorted */
  uint32_t wayc;             /***< ways cardinal >*/
  osmWay** wayv;             /***< ways vector >*/
  uint8_t wayv_s;            /***< null if wayv is sorted */
  uint32_t relationc;        /***< relations cardinal >*/
  osmRelation** relationv;   /***< relations vector >*/
  uint8_t relationv_s;       /***< null if relationv is sorted */
} osm;

/**
 * @brief This function parses a 'tag' node
 * @param[in] cur xml node pointer
 * @param[out] tag 'tag' structure
 * @return void
 */
void
parseTag(const xmlNodePtr cur, osmTag* tag);

/**
 * @brief This function parses a 'bounds' node
 * @param[in] cur xml node pointer
 * @param[out] bounds 'bounds' structure
 * @return void
 */
void
parseBounds(const xmlNodePtr cur, osmBounds* bounds);

/**
 * @brief This function parses a 'node' node
 * @param[in] cur xml node pointer
 * @param[out] node 'node' structure
 * @return void
 */
void
parseNode(const xmlNodePtr cur, osmNode* node);


/**
 * @brief This function parses a 'way' subtree using a set of 'node' pointers
 * @param[in] cur xml node pointer
 * @param[in] nodev 'node' vector
 * @param[out] way 'way' structure
 * @return void
 */
void
parseWay(const xmlNodePtr cur, const osm* map, osmWay* way);


/**
 * @brief This function parses a 'relation' node using a set of 'way' pointers
 * @param[in] cur xml node pointer
 * @param[in] nodev 'node' vector
 * @param[in] wayv 'way' vector
 * @param[out] relation 'relation' structure
 * @return void
 */
void
parseRelation(const xmlNodePtr cur, const osm* map, osmRelation* relation);

/**
 * @brief This function parses an osm file
 * @param[in] map an osm tree structure
 * @param[in] docname filename of osm file
 * @return void
 */
void
parseDoc(const char *docname, osm* map);

#endif

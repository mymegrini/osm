#ifndef PARSE_H
#define PARSE_H

#include <stdint.h>

/**
 * A structure to hold a 'tag' node
 */
typedef struct {
  char* k;                 /***< key >*/
  char* v;                 /***< value >*/
} osmTag;

/**
 * A structure to hold a 'node' node or subtree
 */
typedef struct {
  int32_t id;                /***< id number >*/
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
  int32_t id;                 /***< id number >*/
  uint32_t nodec;             /***< nodes cardinal >*/
  osmNode** nodev;            /***< nodes vector >*/
  uint32_t tagc;              /***< tags cardinal >*/
  osmTag** tagv;              /***< tags vector >*/
} osmWay;

/**
 * A structure to hold a relation subtree
 */
typedef struct osmRelation osmRelation;
struct osmRelation {
  int32_t id;                 /***< id number >*/
  uint32_t nodec;             /***< nodes cardinal >*/
  osmNode** nodev;            /***< nodes vector >*/
  uint32_t wayc;              /***< ways cardinal >*/
  osmWay** wayv;              /***< ways vector >*/
  uint32_t relationc;         /***< relations cardinal >*/
  osmRelation** relationv;    /***< relations vector >*/
  uint32_t tagc;              /***< tags cardinal >*/
  osmTag** tagv;              /***< tags vector >*/
};

/**
 * A structure to hold an osm tree
 */
typedef struct {
  osmBounds* bounds;          /***< 'bounds' node >*/
  uint32_t nodec;             /***< nodes cardinal >*/
  osmNode** nodev;            /***< nodes vector >*/
  uint8_t nodev_s;            /***< null if nodev is sorted */
  uint32_t wayc;              /***< ways cardinal >*/
  osmWay** wayv;              /***< ways vector >*/
  uint8_t wayv_s;             /***< null if wayv is sorted */
  uint32_t relationc;         /***< relations cardinal >*/
  osmRelation** relationv;    /***< relations vector >*/
  uint8_t relationv_s;        /***< null if relationv is sorted */
} osm;

/**
 * @brief This function parses an osm file
 * @param[in] docname filename of osm file
 * @param[out] map an osm tree structure
 * @return void
 */
void
parseDoc(const char *docname, osm* map);

#endif

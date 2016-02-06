#include <libxml/xmlmemory.h>

typedef struct {
  uint32_t id;
  double lat;
  double lon;
  uint32_t visible;
} osmNode;

typedef struct {
  double minlat;
  double maxlat;
  double minlon;
  double maxlon;
} osmBounds;

/**
 * @brief This function prints attribute values for a Bounds node
 * @param[in] cur xml Node pointer
 * @return void
 */
void
printBounds(xmlNodePtr cur);

/**
 * @brief This function prints attribute values for a Node node
 * @param[in] cur xml Node pointer
 * @return void
 */
void
printNode(xmlNodePtr cur);

/**
 * @brief This function parses an osm Node
 * @param[in] cur xml node pointer
 * @param[out] node osmNode pointer
 * @return void
 */
void
parseNode(xmlNodePtr cur, osmNode* node);


/**
 * @brief This function parses an osm Node
 * @param[in] cur xml node pointer
 * @param[out] node osmNode pointer
 * @return void
 */
void
parseBounds(xmlNodePtr cur, osmBounds* node);

/**
 * @brief This function parses an osm file
 * @param[in] docname filename of osm file
 * @return void
 */
void
parseDoc(char *docname);

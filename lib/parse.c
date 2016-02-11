#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include "parse.h"
#include "sort.h"

/**
 * 
 * 
 * 
 * 
 */
void
parseTag(const xmlNodePtr cur, osmTag* tag){

  tag->k = xmlGetProp(cur, (const xmlChar*)"k");
  tag->v = xmlGetProp(cur, (const xmlChar*)"v");
  return;
}

/**
 * 
 * 
 * 
 * 
 */
void
parseBounds(const xmlNodePtr cur, osmBounds* bounds){

  bounds->minlat = atof((const char*)xmlGetProp(cur, (const xmlChar*)"minlat"));
  bounds->maxlat = atof((const char*)xmlGetProp(cur, (const xmlChar*)"maxlat"));
  bounds->minlon = atof((const char*)xmlGetProp(cur, (const xmlChar*)"minlon"));
  bounds->maxlon = atof((const char*)xmlGetProp(cur, (const xmlChar*)"maxlon"));
  return;
}

/**
 * 
 * 
 * 
 * 
 */
void
parseNode(const xmlNodePtr cur, osmNode* node){

  xmlNodePtr child;
  node->id = atoi((const char*)xmlGetProp(cur, (const xmlChar*)"id"));
  node->lat = atof((const char*)xmlGetProp(cur, (const xmlChar*)"lat"));
  node->lon = atof((const char*)xmlGetProp(cur, (const xmlChar*)"lon"));

  node->tagc=0;
  child = cur->xmlChildrenNode;
  while (child != NULL){
    
    if(!xmlStrcmp(child->name, (const xmlChar*)"tag")) node->tagc++;

    child = child->next;
  }

  node->tagv = (osmTag**) malloc(node->tagc * sizeof(osmTag*));
  
  node->tagc=0;
  child = cur->xmlChildrenNode;
  while (child != NULL){
    
    if(!xmlStrcmp(child->name, (const xmlChar*)"tag")){
      node->tagv[node->tagc] = (osmTag*) malloc(sizeof(osmTag));
      parseTag(child, node->tagv[node->tagc]);
      node->tagc++;
    }

    child = child->next;
  }
  
  return;
}


/**
 * 
 * 
 * 
 */
void
parseWay(const xmlNodePtr cur, const osmNode** nodev,
	 uint32_t nodec, osmWay* way){

  return;
}

/**
 * 
 * 
 * 
 */
void
parseRelation(const xmlNodePtr cur, const osmNode** nodev,
	      uint32_t nodec, const osmWay** wayv,
	      uint32_t wayc, osmRelation* relation){

  return;
}

#define VISIBLE(cur) (!xmlStrcmp(xmlGetProp((cur),(const xmlChar*)"visible"),\
				 (const xmlChar*)"true"))

/**
 * parseDoc parses the file \p docname using xmlParseFile then tests if parsing
 * is successful, if the obtained tree is not empty and if its is named 'osm'.
 * parseDoc then counts the number of 'node', 'way' and 'relation' nodes and
 * allocates \p map vectors to the appropriate size. parseDoc then fills the 
 * fields in the \p map structure by calling the appropriate parsing functions.
 *
 * @see parseBounds
 * @see parseNode
 * @see parseWay
 * @see parseRelation
 */
void
parseDoc(const char *docname, osm* map) {

  xmlDocPtr doc;
  xmlNodePtr cur;
  xmlNodePtr root;
  int sortNode = 1;
  int sortWay = 1;
  
  doc = xmlParseFile(docname);

  if (doc == NULL ) {
    fprintf(stderr,"Document not parsed successfully. \n");
    return;
  }

  root = xmlDocGetRootElement(doc);

  if (root == NULL) {
    fprintf(stderr, "Empty document\n");
    xmlFreeDoc(doc);
    return;
  }

  if (xmlStrcmp(root->name, (const xmlChar *) "osm")) {
    fprintf(stderr,"Document of the wrong type, root node != osm\n");
    xmlFreeDoc(doc);
    return;
  }

  map->wayc = 0;
  map->nodec = 0;
  map->relationc = 0;

  cur = root->xmlChildrenNode;
  while (cur != NULL) {

    if (!xmlStrcmp(cur->name, (const xmlChar *)"node") && VISIBLE(cur))
      map->nodec++;

    if (!xmlStrcmp(cur->name, (const xmlChar *)"way") && VISIBLE(cur))
      map->wayc++;

    if (!xmlStrcmp(cur->name, (const xmlChar *)"relation") && VISIBLE(cur))
      map->relationc++;

    cur = cur->next;
  }

  map->bounds = (osmBounds*) malloc(sizeof(osmBounds));
  map->nodev = (osmNode**) malloc(map->nodec * sizeof(osmNode*));
  map->wayv = (osmWay**) malloc(map->wayc * sizeof(osmWay*));
  map->relationv = (osmRelation**) malloc(map->relationc * sizeof(osmRelation*));

  map->wayc = 0;
  map->nodec = 0;
  map->relationc = 0;

  cur = root->xmlChildrenNode;
  while (cur != NULL) {

    if (!xmlStrcmp(cur->name, (const xmlChar *)"bounds"))
      parseBounds(cur, map->bounds);

    if (!xmlStrcmp(cur->name, (const xmlChar *)"node") && VISIBLE(cur)){
      map->nodev[map->nodec] = (osmNode*) malloc(sizeof(osmNode));
      parseNode(cur, map->nodev[map->nodec]);
      map->nodec++;
    }

    if (!xmlStrcmp(cur->name, (const xmlChar *)"way") && VISIBLE(cur)){
      if(sortNode) {
	sortNodes(map->nodev, map->nodec);
	sortNode = 0;
      }
      map->wayv[map->wayc] = (osmWay*) malloc(sizeof(osmWay));
      parseWay(cur, (const osmNode**)map->nodev,
	       map->nodec, map->wayv[map->wayc]);
      map->wayc++;
    }

    if (!xmlStrcmp(cur->name, (const xmlChar *)"relation") && VISIBLE(cur)){      
      if(sortWay) {
	sortWays(map->wayv, map->wayc);
	sortWay = 0;
      }
      map->relationv[map->relationc] = (osmRelation*) malloc(sizeof(osmRelation));
      parseRelation(cur, (const osmNode**)map->nodev,
		    map->nodec, (const osmWay**)map->wayv,
		    map->wayc, map->relationv[map->relationc]);
      map->relationc++;
    } 

    cur = cur->next;
  }

  sortRelations(map->relationv, map->relationc);

  xmlFreeDoc(doc);

  return;
}

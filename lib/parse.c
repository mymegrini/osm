#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include "parse.h"

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

  sscanf((const char*)xmlGetProp(cur, (const xmlChar*)"minlat"),
	 "%lf", &bounds->minlat);
  sscanf((const char*)xmlGetProp(cur, (const xmlChar*)"maxlat"),
	 "%lf", &bounds->maxlat);
  sscanf((const char*)xmlGetProp(cur, (const xmlChar*)"minlon"),
	 "%lf", &bounds->minlon);
  sscanf((const char*)xmlGetProp(cur, (const xmlChar*)"maxlon"),
	 "%lf", &bounds->maxlon); 
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

  return;
}


/**
 * 
 * 
 * 
 */
void
parseWay(const xmlNodePtr cur, const osmNode** nodev, osmWay* way){

  return;
}

/**
 * 
 * 
 * 
 */
void
parseRelation(const xmlNodePtr cur, const osmWay** wayv, osmRelation* relation){

  return;
}

#define VISIBLE(cur) (!xmlStrcmp(xmlGetProp((cur),(const xmlChar*)"visible"),\
				 (const xmlChar*)"true"))

/**
 * 
 * 
 * 
 */
void
parseDoc(const char *docname, osm* map) {

  xmlDocPtr doc;
  xmlNodePtr cur;
  xmlNodePtr root;
  int node, way, relation;

  //parse document using libxml
  doc = xmlParseFile(docname);

  //test if parsing successful
  if (doc == NULL ) {
    fprintf(stderr,"Document not parsed successfully. \n");
    return;
  }

  //obtain root node
  root = xmlDocGetRootElement(doc);

  //test if document is not empty
  if (root == NULL) {
    fprintf(stderr, "Empty document\n");
    xmlFreeDoc(doc);
    return;
  }

  //test if root node is of type osm
  if (xmlStrcmp(root->name, (const xmlChar *) "osm")) {
    fprintf(stderr,"Document of the wrong type, root node != osm\n");
    xmlFreeDoc(doc);
    return;
  }

  //set counters
  way = 0;
  node = 0;
  relation = 0;
  
  //get first child
  cur = root->xmlChildrenNode;
  while (cur != NULL) {

    //count nodes
    if (!xmlStrcmp(cur->name, (const xmlChar *)"node") && VISIBLE(cur)) node++;

    //count ways
    if (!xmlStrcmp(cur->name, (const xmlChar *)"way") && VISIBLE(cur)) way++;

    //count relations
    if (!xmlStrcmp(cur->name, (const xmlChar *)"relation") && VISIBLE(cur))
      relation++;

    //get next child
    cur = cur->next;
  }

  //alocate pointers and vectors
  map->bounds = (osmBounds*) malloc(sizeof(osmBounds));
  map->nodev = (osmNode**) malloc(node * sizeof(osmNode*));
  map->wayv = (osmWay**) malloc(way * sizeof(osmWay*));
  map->relationv = (osmRelation**) malloc(relation * sizeof(osmRelation*));

  //reset counters
  way = 0;
  node = 0;
  relation = 0;

  //get first child
  cur = root->xmlChildrenNode;
  while (cur != NULL) {

    
    //parse bounds node
    if (!xmlStrcmp(cur->name, (const xmlChar *)"bounds"))
      parseBounds(cur, map->bounds);

    //parse node node
    if (!xmlStrcmp(cur->name, (const xmlChar *)"node") && VISIBLE(cur)){
      map->nodev[node] = (osmNode*) malloc(sizeof(osmNode));
      parseNode(cur, map->nodev[node]);
      node++;
    }

    //parse way node
    if (!xmlStrcmp(cur->name, (const xmlChar *)"way") && VISIBLE(cur)){
      map->wayv[way] = (osmWay*) malloc(sizeof(osmWay));
      parseWay(cur, (const osmNode**)map->nodev, map->wayv[way]);
      way++;
    }

    //parse relation node
    if (!xmlStrcmp(cur->name, (const xmlChar *)"relation") && VISIBLE(cur)){
      map->relationv[relation] = (osmRelation*) malloc(sizeof(osmRelation));
      parseRelation(cur, (const osmWay**)map->relationv,
		    map->relationv[relation]);
      relation++;
    } 

    //get next child
    cur = cur->next;
  }

  //fill counters
  map->nodec = node;
  map->wayc = way;
  map->relationc = relation;

  //free opened document
  xmlFreeDoc(doc);

  return;
}

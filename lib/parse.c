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
parseTag(const xmlNodePtr cur, osmNode* tag){

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
  
  cur = root->xmlChildrenNode;
  while (cur != NULL) {
    
    if (!xmlStrcmp(cur->name, (const xmlChar *)"node") && VISIBLE(cur)){
    }

    if (!xmlStrcmp(cur->name, (const xmlChar *)"way") && VISIBLE(cur)){
      map->wayc++;
    }

    if (!xmlStrcmp(cur->name, (const xmlChar *)"relation") && VISIBLE(cur)){
      map->relationc++;
    } 

    cur = cur->next;
  }

  map->bounds = (osmBounds*) malloc(sizeof(osmBounds));
  map->nodev = (osmNode**) malloc(map->nodec * sizeof(osmNode*));
  node = 0;
  map->wayv = (osmWay**) malloc(map->wayc * sizeof(osmWay*));
  way = 0;
  map->relationv = (osmRelation**) malloc(map->relationc*sizeof(osmRelation*));
  relation = 0;
  
  cur = root->xmlChildrenNode;
  while (cur != NULL) {
    
    if (!xmlStrcmp(cur->name, (const xmlChar *)"bounds") && VISIBLE(cur)){
      parseBounds(cur, map->bounds);
    }

    if (!xmlStrcmp(cur->name, (const xmlChar *)"node") && VISIBLE(cur)){
      map->nodev[node] = (osmNode*) malloc(sizeof(osmNode));
      parseNode(cur, map->nodev[node]);
      node++;
    }

    if (!xmlStrcmp(cur->name, (const xmlChar *)"way") && VISIBLE(cur)){
      map->wayv[way] = (osmWay*) malloc(sizeof(osmWay));
      parseWay(cur, (const osmNode**)map->nodev, map->wayv[way]);
      way++;
    }

    if (!xmlStrcmp(cur->name, (const xmlChar *)"relation") && VISIBLE(cur)){
      map->relationv[relation] = (osmRelation*) malloc(sizeof(osmRelation));
      parseRelation(cur, (const osmWay**)map->relationv,
		    map->relationv[relation]);
      relation++;
    } 

    cur = cur->next;

  }

  xmlFreeDoc(doc);

  return;
}

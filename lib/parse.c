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
parseWay(const xmlNodePtr cur, osm* map, osmWay* way){

xmlNodePtr curseur = cur->xmlChildrenNode;
int node=0;
int tag=0;

way->id=xmlGetProp(cur, "id");
way->nodec=0;
way->tagc=0;
while (curseur != NULL) {
	if ((!xmlStrcmp(curseur->name, (const xmlChar *)"nd"))) {
       		way->nodec++;
	}
	if ((!xmlStrcmp(curseur->name, (const xmlChar *)"tag"))) {
       		way->tagc++;	
	}
    	curseur = cur->next;
}

way->nodev=(osmNode**)malloc(way->nodec*sizeof(osmNode*));
way->tagv=(osmTag**)malloc(way->tagc*sizeof(osmTag*));

curseur=cur->xmlChildrenNode;
while (curseur != NULL) {
	if ((!xmlStrcmp(curseur->name, (const xmlChar *)"nd"))) {

       		way->nodev[node]=findNode(map,(int)xmlGetProp(cur, "ref"));
	node++;
	}
	if ((!xmlStrcmp(curseur->name, (const xmlChar *)"tag"))) {
       		parseTag(curseur,way->tagv+tag);
		tag++;
	}
    	curseur = cur->next;
}
way->nodec=node;
way->tagc=tag;
  return;
}

/**
 * 
 * 
 * 
 */
void
parseRelation(const xmlNodePtr cur, const osmNode** nodev,
	      const osmWay** wayv, osmRelation* relation){

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

  way = 0;
  node = 0;
  relation = 0;

  cur = root->xmlChildrenNode;
  while (cur != NULL) {

    if (!xmlStrcmp(cur->name, (const xmlChar *)"node") && VISIBLE(cur)) node++;

    if (!xmlStrcmp(cur->name, (const xmlChar *)"way") && VISIBLE(cur)) way++;

    if (!xmlStrcmp(cur->name, (const xmlChar *)"relation") && VISIBLE(cur))
      relation++;

    cur = cur->next;
  }

  map->bounds = (osmBounds*) malloc(sizeof(osmBounds));
  map->nodev = (osmNode**) malloc(node * sizeof(osmNode*));
  map->wayv = (osmWay**) malloc(way * sizeof(osmWay*));
  map->relationv = (osmRelation**) malloc(relation * sizeof(osmRelation*));

  way = 0;
  node = 0;
  relation = 0;

  cur = root->xmlChildrenNode;
  while (cur != NULL) {

    if (!xmlStrcmp(cur->name, (const xmlChar *)"bounds"))
      parseBounds(cur, map->bounds);

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
      parseRelation(cur, (const osmNode**)map->nodev,
		    (const osmWay**)map->wayv, map->relationv[relation]);
      relation++;
    } 

    cur = cur->next;
  }

  map->nodec = node;
  map->wayc = way;
  map->relationc = relation;

  xmlFreeDoc(doc);

  return;
}

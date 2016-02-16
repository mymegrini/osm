#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include "parse.h"
#include "sort.h"
#include "print.h"
#define DEBUG true

/**
 * 
 * parseTag uses xmlGetProp to parse the attributes. 
 * If parseTag fails, it stores NULL in \p tag.
 */
void
parseTag(const xmlNodePtr cur, osmTag* tag){

  xmlChar* prop;

  prop = xmlGetProp(cur, (const xmlChar*)"k");
  if (!prop) {free(prop); tag = NULL; return;}
  tag->k = (char*) prop;
  
  prop = xmlGetProp(cur, (const xmlChar*)"v");
  if (!prop) {free(prop); tag = NULL; return;}
  tag->v = (char*) prop;
  
  return;
}

/** 
 * 
 * parseBounds uses xmlGetProp to parse the attributes. 
 * If parseBounds fails, it stores NULL in \p bounds.
 */
void
parseBounds(const xmlNodePtr cur, osmBounds* bounds){

  xmlChar* prop;
  
  prop = xmlGetProp(cur, (const xmlChar*)"minlat");
  if (!prop) {free(prop); bounds = NULL; return;}
  bounds->minlat = atof((const char*) prop);
  free(prop);

  prop = xmlGetProp(cur, (const xmlChar*)"maxlat");
  if (!prop) {free(prop); bounds = NULL; return;}
  bounds->maxlat = atof((const char*) prop);
  free(prop);
  
  prop = xmlGetProp(cur, (const xmlChar*)"minlon");
  if (!prop) {free(prop); bounds = NULL; return;}
  bounds->minlon = atof((const char*) prop);
  free(prop);

  prop = xmlGetProp(cur, (const xmlChar*)"maxlon");
  if (!prop) {free(prop); bounds = NULL; return;}
  bounds->maxlon = atof((const char*) prop);
  free(prop);
  
  return;
}

/**
 * 
 * parseBounds uses xmlGetProp to parse the attributes. It then calls parseTag
 * on every child 'tag' node when they exit.
 * If parseNode fails, it stores NULL in \p node.
 *
 * @see parseTag
 */
void
parseNode(const xmlNodePtr cur, osmNode* node){

  xmlNodePtr child;
  xmlChar* prop;

  prop = xmlGetProp(cur, (const xmlChar*)"id");
  if (!prop) {free(prop); node = NULL; return;}
  node->id = atoi((const char*) prop);
  free(prop);
  
  prop = xmlGetProp(cur, (const xmlChar*)"lat");
  if (!prop) {free(prop); node = NULL; return;}
  node->lat = atof((const char*) prop);
  free(prop);

  prop = xmlGetProp(cur, (const xmlChar*)"lon");
  if (!prop) {free(prop); node = NULL; return;}
  node->lon = atof((const char*) prop);
  free(prop);

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
      if (node->tagv[node->tagc]) node->tagc++;
    }

    child = child->next;
  }
  
  return;
}


/**
 * parseWay uses xmlGetProp to parse the attributes. It then uses findNode to 
 * identify every 'nd' child node. Then parses every 'tag' child node by calling
 * parseTag.
 * If parseWay fails, it stores NULL in \p way.
 *
 * @see parseTag
 * @see findNode
 */
void
parseWay(const xmlNodePtr cur, osm* map, osmWay* way){

  xmlChar* prop;
  xmlNodePtr curseur = cur->xmlChildrenNode;

  prop = xmlGetProp(cur, (const xmlChar*)"id");
  if (!prop) {free(prop); way = NULL; return;}  
  way->id= atoi((const char*) prop);
  free(prop);
  
  way->nodec=0;
  way->tagc=0;
  
  while (curseur != NULL) {
    if ((!xmlStrcmp(curseur->name, (const xmlChar*)"nd"))) {
      way->nodec++;
    }
    else if ((!xmlStrcmp(curseur->name, (const xmlChar*)"tag"))) {
      way->tagc++;	
    }
    curseur = curseur->next;
  }

  //printf("parseWay: %d id %d node %d tag\n", way->id, way->nodec, way->tagc);
  
  way->nodev=(osmNode**)malloc(way->nodec * sizeof(osmNode*));
  way->tagv=(osmTag**)malloc(way->tagc * sizeof(osmTag*));
  
  way->nodec=0;
  way->tagc=0;
  
  curseur = cur->xmlChildrenNode;
  while (curseur != NULL) {
    
    if ((!xmlStrcmp(curseur->name, (const xmlChar *)"nd"))) {
      prop = xmlGetProp(curseur, (const xmlChar*)"ref");
      if (!prop) free(prop);
      else {
	way->nodev[way->nodec] = findNode(map, atoi((char*) prop));
	free(prop);
	if (way->nodev[way->nodec]) way->nodec++;
      }	
    }
    else if ((!xmlStrcmp(curseur->name, (const xmlChar *)"tag"))) {
      way->tagv[way->tagc] = (osmTag*) malloc(sizeof(osmTag));
      parseTag(curseur, way->tagv[way->tagc]);
      if (way->tagv[way->tagc]) way->tagc++;
    }
    
    curseur = curseur->next;
  }
  //printf("parseWay: %d id %d node %d tag\n", way->id, way->nodec, way->tagc);
  return;
}

/**
 * 
 * 
 * 
 */
void
parseRelation(const xmlNodePtr cur, osm* map, osmRelation* relation){

  xmlChar* prop;
  prop = xmlGetProp(cur, (const xmlChar*)"id");
  if (!prop) {free(prop); relation = NULL; return;}  
  relation->id= atoi((const char*) prop);
  free(prop);

  relation->nodec=0;
  relation->wayc=0;
  relation->relationc=0;
  relation->tagc=0;
  
  xmlNodePtr curseur;
  curseur = cur->xmlChildrenNode;
  
  while (curseur != NULL){

    if(!xmlStrcmp(curseur->name, (const xmlChar*)"member")){

      prop = xmlGetProp(curseur, (const xmlChar*)"type");
      if (!prop) {free(prop);}
      else {

	if(!xmlStrcmp(prop, (const xmlChar*)"node"))
	  relation->nodec++;
	else if(!xmlStrcmp(prop, (const xmlChar*)"way"))
	  relation->wayc++;
	else if(!xmlStrcmp(prop, (const xmlChar*)"relation"))
	  relation->relationc++;
	
	free(prop);
      }
    }     

    if(!xmlStrcmp(curseur->name, (const xmlChar *)"tag"))
      relation->tagc++;
    
    curseur= curseur->next;
  }
  /*
  printf("parseRelation : %d id %d node %d way %d relation %d tag\n",
	 relation->id, relation->nodec, relation->wayc, relation->relationc,
	 relation->tagc);
  */
  
  relation->nodev = (osmNode**)malloc(relation->nodec * sizeof(osmNode*)); 
  relation->wayv = (osmWay**)malloc(relation->wayc * sizeof(osmWay*));
  relation->relationv =
    (osmRelation**)malloc(relation->relationc * sizeof(osmRelation*));
  relation->tagv = (osmTag**)malloc(relation->tagc * sizeof(osmTag*));
    
  relation->nodec=0;
  relation->wayc=0;
  relation->relationc=0;
  relation->tagc=0;
  
  curseur=cur->xmlChildrenNode;
  while(curseur !=NULL){
   
    if(!xmlStrcmp(curseur->name, (const xmlChar *)"member")){
      
      prop = xmlGetProp(curseur, (const xmlChar*)"type");
      if (!prop) {free(prop);}
      else if(!xmlStrcmp(prop, (const xmlChar*)"node")){

	free(prop);
	prop = xmlGetProp(curseur, (const xmlChar*)"ref");
	if (!prop) {free(prop);}
	else {
	  relation->nodev[relation->nodec] = findNode(map, atoi((char*) prop));
	  free(prop);
	  if (relation->nodev[relation->nodec]) relation->nodec++;
	}	  
      }
      else if(!xmlStrcmp(prop, (const xmlChar*)"way")){
	
	free(prop);
	prop = xmlGetProp(curseur, (const xmlChar*)"ref");
	if (!prop) {free(prop);}
	else {
	  relation->wayv[relation->wayc] = findWay(map, atoi((char*) prop));
	  free(prop);
	  if (relation->wayv[relation->wayc]) relation->wayc++;
	}	  
      }
      else if(!xmlStrcmp(prop, (const xmlChar*)"relation")){
	free(prop);
	prop = xmlGetProp(curseur, (const xmlChar*)"ref");
	if (!prop) {free(prop);}
	else {
	  relation->relationv[relation->relationc] =
	    findRelation(map, atoi((char*) prop));
	  free(prop);
	    if (relation->relationv[relation->relationc]) relation->relationc++;
	}
      }
    }
    else if(!xmlStrcmp(curseur->name, (const xmlChar *)"tag")){
      relation->tagv[relation->tagc] = (osmTag*) malloc(sizeof(osmTag));
      parseTag(curseur, relation->tagv[relation->tagc]);
      if (relation->tagv[relation->tagc]) relation->tagc++;
    }

    curseur = curseur->next;
  }

  return;
}

#define VISIBLE(cur) \
(!xmlStrcmp(xmlGetProp((cur),(const xmlChar*)"visible"), (const xmlChar*)"true"))

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

    else if (!xmlStrcmp(cur->name, (const xmlChar *)"way") && VISIBLE(cur))
      map->wayc++;

    else if (!xmlStrcmp(cur->name, (const xmlChar *)"relation") && VISIBLE(cur))
      map->relationc++;

    cur = cur->next;
  }

  map->bounds = (osmBounds*) calloc(1, sizeof(osmBounds));
  map->nodev = (osmNode**) calloc(map->nodec, sizeof(osmNode*));
  map->wayv = (osmWay**) calloc(map->wayc, sizeof(osmWay*));
  map->relationv = (osmRelation**) calloc(map->relationc, sizeof(osmRelation*));

  map->wayc = 0;
  map->nodec = 0;
  map->relationc = 0;

  cur = root->xmlChildrenNode;
  while (cur != NULL) {

    if (!xmlStrcmp(cur->name, (const xmlChar *)"bounds"))
      parseBounds(cur, map->bounds);

    else if (!xmlStrcmp(cur->name, (const xmlChar *)"node") && VISIBLE(cur)){
      map->nodev[map->nodec] = (osmNode*) calloc(1, sizeof(osmNode));
      parseNode(cur, map->nodev[map->nodec]);
      if (map->nodev[map->nodec]){
	map->nodev_s = 1;
	map->nodec++;
      }
    }
    else if (!xmlStrcmp(cur->name, (const xmlChar *)"way") && VISIBLE(cur)){
      map->wayv[map->wayc] = (osmWay*) calloc(1, sizeof(osmWay));
      parseWay(cur, map, map->wayv[map->wayc]);
      if (map->wayv[map->wayc]){
	map->wayv_s = 1;
	map->wayc++;
      }
    }
    else if (!xmlStrcmp(cur->name, (const xmlChar *)"relation") && VISIBLE(cur)){
      map->relationv[map->relationc]=
	(osmRelation*) calloc(1, sizeof(osmRelation));
      parseRelation(cur, map, map->relationv[map->relationc]);
      map->relationv_s = 1;
      map->relationc++;
    } 
    
    cur = cur->next;
  }

  xmlFreeDoc(doc);

  return;
}

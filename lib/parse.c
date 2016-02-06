#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include "parse.h"

  
void
printBounds (xmlNodePtr cur) {
  
  xmlChar *aval;
  
  puts("Bounds:");

  aval = xmlGetProp(cur, (const xmlChar*)"minlat");
  printf("minlat: %s\n", aval);
  free(aval);
  
  aval = xmlGetProp(cur, (const xmlChar*)"maxlat");
  printf("maxlat: %s\n", aval);
  free(aval);
  
  aval = xmlGetProp(cur, (const xmlChar*)"minlon");
  printf("minlon: %s\n", aval);
  free(aval);
  
  aval = xmlGetProp(cur, (const xmlChar*)"maxlon");
  printf("maxlon: %s\n", aval);
  free(aval);

  return;
}

void
printNode(xmlNodePtr cur) {

  xmlChar* aval;

  puts("Node:");
  
  aval = xmlGetProp(cur, (const xmlChar*)"id");
  printf("id: %s\n", aval);
  free(aval);
  
  aval = xmlGetProp(cur, (const xmlChar*)"lat");
  printf("lat: %s\n", aval);
  free(aval);
  
  aval = xmlGetProp(cur, (const xmlChar*)"lon");
  printf("lon: %s\n", aval);
  free(aval);
  
  aval = xmlGetProp(cur, (const xmlChar*)"visible");
  printf("visible: %s\n", aval);
  free(aval);

  return;
}

void
parseNode(xmlNodePtr cur, osmNode* node) {
  node->id = 0;
  node->lat = 0;
  node->lon = 0;
  node->visible = 1;

  return;
}

void
parseBounds(xmlNodePtr cur, osmBounds* bounds) {
  bounds->minlat = 0;

  return;
}


void
parseDoc(char *docname) {
  
  xmlDocPtr doc;
  xmlNodePtr cur;
  
  doc = xmlParseFile(docname);
  
  if (doc == NULL ) {
    fprintf(stderr,"Document not parsed successfully. \n");
    return;
  }
  
  cur = xmlDocGetRootElement(doc);
  
  if (cur == NULL) {
    fprintf(stderr, "Empty document\n");
    xmlFreeDoc(doc);
    return;
  }
  
  if (xmlStrcmp(cur->name, (const xmlChar *) "osm")) {
    fprintf(stderr,"Document of the wrong type, root node != osm\n");
    xmlFreeDoc(doc);
    return;
  }
  
  cur = cur->xmlChildrenNode;
  while (cur != NULL) {
    
    if ((!xmlStrcmp(cur->name, (const xmlChar *)"bounds"))){  
      printBounds(cur);
    }

    if ((!xmlStrcmp(cur->name, (const xmlChar *)"node"))){
      printNode(cur);
    }

    cur = cur->next;
  }
  
  puts("Parsing done.");

  xmlFreeDoc(doc);
  return;
}

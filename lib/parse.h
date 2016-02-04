#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

void
parseStory (xmlDocPtr doc, xmlNodePtr cur);

static void
parseDoc(char *docname);

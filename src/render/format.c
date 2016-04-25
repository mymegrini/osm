#include "format.h"


typedef struct {
    const char* v;
    osmFormat format;
}osmIndex;


osmFigure** queue = NULL;
uint32_t size = 0;

/**
 * Rendering Palette indexes per value
 */
osmIndex highwayPalette[] = {
    {"service"     , { 12  , 8 , 0x77393b22 } },
    {"residential" , { 13  , 7 , 0x88393b22 } },
    {"unclassified", { 14  , 6 , 0x99393b22 } },
    {"tertiary"    , { 15  , 5 , 0xaa393b22 } },
    {"secondary"   , { 16  , 4 , 0xcc393b22 } },
    {"primary"     , { 17  , 3 , 0xdd393b22 } },
    {"trunk"       , { 18  , 2 , 0xee393b22 } },
    {"motorway"    , { 19  , 1 , 0xff393b22 } },
    {NULL, { 0  , 0 , 0 }}
};
osmIndex buildingPalette[] = {
    {""     , { 20  , 0 , 0x798e8558 } },
    {NULL, { 0  , 0 , 0 }}
};
osmIndex waterwayPalette[] = {
    {"river"     , { 1 , 4 , 0xaaD39355 } },
    {"stream"    , { 2 , 1 , 0xffD39355 } },
    {"riverbank" , { 1 , 0 , 0xaaD39355 } },
    {NULL , { 0  , 0 , 0 }}
};
osmIndex naturalPalette[] = {
    {"wood"     , { 20  , 0 , 0xaa33571e } },
    {"tree_row" , { 20  , 2 , 0xaa33571e } },
    {"scrub"    , { 20  , 0 , 0xaa6cb341 } },
    {"heath"    , { 20  , 0 , 0xaa6ce6ff } },
    {"grassland", { 20  , 0 , 0xaa6ff6ac } },
    {"fell"     , { 20  , 0 , 0xaa4cc6df } },
    {"bare_rock", { 20  , 0 , 0xaa6b82a8 } },
    {"scree"    , { 20  , 0 , 0xaa6b82a8 } },
    {"shingle"  , { 20  , 0 , 0xaa6b82a8 } },
    {"sand"     , { 20  , 0 , 0xaa52bcf1 } },
    {"mud"      , { 20  , 0 , 0xaa5cb9ff } },
    {"water"    , { 1   , 0 , 0xaaD39355 } },
    {"wetland"  , { 20  , 0 , 0xaae7edca } },
    {"glacier"  , { 3   , 0 , 0xaac9d97b } },
    {"beach"    , { 20  , 0 , 0xaa54d2f3 } },
    {"coastline", { 20  , 0 , 0xffD39355 } },
    {NULL, { 0  , 0 , 0 }}
};
osmIndex landusePalette[] = {
    {"forest"           , { 20  , 0 , 0xaa33571e } },
    {"grass"            , { 20  , 0 , 0xaa6ff6ac } },
    {"meadow"           , { 20  , 0 , 0xaa6ff6ac } },
    {"recreation-ground", { 20  , 0 , 0xaa6ff6ac } },
    {"village_green"    , { 20  , 0 , 0xaa6ff6ac } },
    {"vinyard"          , { 20  , 0 , 0xaa6ff6ac } },
    {NULL, { 0  , 0 , 0 }}
};
osmIndex leisurePalette[] = {
    {"garden"     , { 20  , 0 , 0xaa6ff6ac }},
    {"park"       , { 20  , 0 , 0xaa6ff6ac }},
    {"stadium"    , { 20  , 0 , 0xaa66ff9c }},
    {NULL, { 0  , 0 , 0 }}
};
osmIndex placePalette[] = {
    {"island"     , { 9  , 0 , 0xffeeffff } },
    {NULL, { 0  , 0 , 0 }}
};

/**
 * This function determines a way's format using a palette index
 */
static void
formatPalette(osmWay* way, int t, osmIndex* index){

    int pal = 0;
    char* type = way->tagv[t]->v;

    while(index[pal].v != NULL)
	if(!strcmp(index[pal].v, "") || !strcmp(type, index[pal].v)){
	    osmFigure* fig = malloc(sizeof(osmFigure));    
	    fig->way = way;    
	    fig->format = &(index[pal].format);
	    queue[size++] = fig;
	    break;
	} else pal++;
    return;
}

void
formatWay(osmWay* way){
    
    int t;
    
    
    if (way->tagc) {
	for(t = 0; t<way->tagc; t++){
	    if (!strcmp(way->tagv[t]->k, "building"))
		formatPalette(way, t, buildingPalette);
	    else if (!strcmp(way->tagv[t]->k, "highway"))
		formatPalette(way, t, highwayPalette);
	    else if (!strcmp(way->tagv[t]->k, "waterway"))
		formatPalette(way, t, waterwayPalette);
	    else if (!strcmp(way->tagv[t]->k, "natural"))
		formatPalette(way, t, naturalPalette);
	    else if (!strcmp(way->tagv[t]->k, "place"))
		formatPalette(way, t, placePalette);
	    else  if (!strcmp(way->tagv[t]->k, "landuse"))
		formatPalette(way, t, landusePalette);
	    else  if (!strcmp(way->tagv[t]->k, "leisure"))
		formatPalette(way, t, leisurePalette);
	    
	}
    }
    
    return;
}

/**
 * This function compares priority between two figures
 */
static int _cmpPriority(const void* p1, const void* p2){

    osmFigure* f2 = *(osmFigure* const*)p2;
    osmFigure* f1 = *(osmFigure* const*)p1;
    return (f1->format->priority) - (f2->format->priority);
}

/**
 * This function sorts the rendering queue
 */
void
sortQueue(){
    
    qsort(queue, size, sizeof(osmFigure*), &_cmpPriority);
    return;
}

/**
 * This function deallocates a rendering queue
 */
void
freeQueue(){

    int i;
    
    for(i=0; i<size; i++)
	free(queue[i]);

    free(queue);
    queue = NULL;
    size = 0;
}

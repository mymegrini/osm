#include "format.h"


/**
 * Rendering Palette
 */
osmFormat palette[] =
    {
	{ -1 , 0 , 0xceeaffff },  //background
	{ 0  , 0 , 0x8888ffff },  //water
	{ 1  , 1 , 0x795f5fff },  //line
	{ 2  , 0 , 0x799253ff },  //building
    };

osmFigure** queue = NULL;
uint32_t size = 0;

/**
 * This function formats a highway type way
 */
static void
formatHighway(osmWay* way, int t){

    //char* type = way->tagv[t]->v;
    osmFigure* fig = malloc(sizeof(osmFigure));
    fig->way = way;
    
    fig->format = palette+2;

    queue[size++] = fig;
    return;
}

static void
formatBuilding(osmWay* way, int t){

    //char* type = way->tagv[t]->v;
    osmFigure* fig = malloc(sizeof(osmFigure));
    fig->way = way;
    
    fig->format = palette+3;

    queue[size++] = fig;
    return;
}

static void
formatWaterway(osmWay* way, int t){

    //char* type = way->tagv[t]->v;
    osmFigure* fig = malloc(sizeof(osmFigure));
    fig->way = way;
    
    fig->format = palette+1;

    queue[size++] = fig;
    return;
}

static void
formatNatural(osmWay* way, int t){

    char* type = way->tagv[t]->v;
    osmFigure* fig = malloc(sizeof(osmFigure));
    fig->way = way;

    if (!strcmp(type, "water"))
	fig->format = palette+1;

    queue[size++] = fig;
    return;
}

void
formatWay(osmWay* way){
    
    int t;
    
    if (way->tagc) {
	for(t = 0; t<way->tagc; t++){
	    if (!strcmp(way->tagv[t]->k, "building"))
		formatBuilding(way, t);
	    if (!strcmp(way->tagv[t]->k, "highway"))
		formatHighway(way, t);
	    if (!strcmp(way->tagv[t]->k, "waterway"))
		formatWaterway(way, t);
	    if (!strcmp(way->tagv[t]->k, "natural"))
		formatNatural(way, t);
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
    return f1->format->priority - f2->format->priority;
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
	free(queue+i);

    free(queue);
    queue = NULL;
    size = 0;
}

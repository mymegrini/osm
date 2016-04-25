#include "format.h"


/**
 * Rendering Palette
 */

osmFormat palette[] =
    {   //prio width 0xAABBGGRR 
	{ 0  , 0 , 0xffeeffff },  //0 background
	{ -1 , 0 , 0x88D39355 },  //1 water
	{ 1  , 1 , 0xff5096ea },  //2 line
	{ 2  , 0 , 0x798e8558 },  //3 building
	{ -1 , 1 , 0x88D39355 },  //4 water line	
	{ 2  , 1 , 0x798e8558 },  //5 building line	
	{ 1  , 0 , 0x7951e651 },  //6 grass	
	{ 1  , 1 , 0x7951e651 },  //7 grass line
	{ 1  , 0 , 0x7930e630 },  //8 woods
	{ 1  , 1 , 0x7930e630 },  //8 woods line
	{ 1  , 1 , 0x7930e630 },  //9 woods line
	{ 1  , 1 , 0x7930e630 },  //10 woods line
	{ 1  , 1 , 0x7930e630 },  //11 woods line
	{ 1  , 1 , 0x7930e630 },  //12 woods line
	{ 1  , 1 , 0x7930e630 },  //13 woods line
	{ 1  , 1 , 0x7930e630 },  //14 woods line
	{ 1  , 1 , 0x7930e630 },  //15 woods line
	{ 1  , 1 , 0x7930e630 },  //16 woods line	
	{ 0 , 0 , 0 }
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
formatBuilding(osmWay* w, int t){

    //char* type = way->tagv[t]->v;
    
    osmFigure* fig = malloc(sizeof(osmFigure));
    fig->way = w;	

    if(w->nodec>2 && w->nodev[0]->id == w->nodev[w->nodec-1]->id)
	fig->format = palette+3;
    else
	fig->format = palette+5;

    queue[size++] = fig;
    
    return;
}

static void
formatWaterway(osmWay* w, int t){

    //char* type = way->tagv[t]->v;
    
    osmFigure* fig = malloc(sizeof(osmFigure));

    fig->way = w;	

    if(w->nodec>2 && w->nodev[0]->id == w->nodev[w->nodec-1]->id)
	fig->format = palette+1;
    else
	fig->format = palette+4;

    queue[size++] = fig;
    
    return;
}

static void
formatNatural(osmWay* way, int t){

    char* type = way->tagv[t]->v;
    osmFigure* fig = malloc(sizeof(osmFigure));
    fig->way = way;

    if (!strcmp(type, "water"))
	fig->format = palette+6;
    else if (!strcmp(type, "wood"))
	fig->format = palette+6;

    queue[size++] = fig;
    return;
}

static void
formatLanduse(osmWay* way, int t){

    char* type = way->tagv[t]->v;
    osmFigure* fig = malloc(sizeof(osmFigure));
    fig->way = way;

    if (!strcmp(type, "grass"))
	fig->format = palette+1;

    queue[size++] = fig;
    return;
}

static void
formatPlace(osmWay* way, int t){

    char* type = way->tagv[t]->v;
    osmFigure* fig = malloc(sizeof(osmFigure));
    fig->way = way;

    if (!strcmp(type, "island"))
	fig->format = palette;

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
	    if (!strcmp(way->tagv[t]->k, "place"))
		formatPlace(way, t);
	    if (!strcmp(way->tagv[t]->k, "landuse"))
		formatLanduse(way, t);
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
	free(queue[i]);

    free(queue);
    queue = NULL;
    size = 0;
}

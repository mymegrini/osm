#include <stdio.h>
#include <getopt.h>
#include "osmaps.h"

/**
 * @brief This function prints the command prototype
 * @param[in] argv0 command name
 * @param[out] out output stream
 * @return void
 * 
 * This function prints the command prototype to the <out> stream.
 */
static void usage(char* argv0, FILE* out){
  fprintf(out,
	  "Usage: %s [OPTIONS]... [FILE]\n",
	  argv0);
}

/**
 * @brief This function prints the command prototype
 * @param[in] argv0 command name
 * @param[out] out output stream
 * @return void
 *
 * This is the program's main function. It handles parsing command line
 * arguments and calling the appropriate function.
 */
int
main(int argc, char **argv) {

  char *docname;
  int opt;
  int flags = 0;
  int index = 0;
  static struct option long_options[] = {
    {"help", no_argument, NULL, 'h'},
    {"bounds", no_argument, NULL, 'b'},
    {"nodes", no_argument, NULL, 'n'},
    {"ways", no_argument, NULL, 'w'},
    {"relations", no_argument, NULL, 'r'},
    {"text", no_argument, NULL, 't'},
    {0, 0, 0, 0}
  };
  
  while((opt = getopt_long_only(argc,argv,"bnwrt",long_options,&index)) !=-1){

    switch(opt){
    case 'h':
      usage(argv[0], stdout);
      puts("\
OSmaps: the OpenStreetMaps renderer. This program takes an xml file containing\n\
an OSM tree and renders it on screen.\n\n\
Available options:\n\
\t-b, --bounds\n\
\t\tparse the OSM tree and list all its 'bounds' nodes\n\
\t-n, --nodes\n\
\t\tparse the OSM tree and list all its 'node' nodes\n\
\t-r, --relations\n\
\t\tparse the OSM tree and list all its 'relation' nodes\n\
\t-w, --ways\n\
\t\tparse the OSM tree and list all its 'way' nodes\n\
\t-t, --text  (equivalent to '-bnrw')\n\
\t\tparse the OSM tree and list all its nodes\n\
\t--help\n\
\t\tshow this help and exit.");
      return 0;
    case 't':
      flags |= F_TEXT;
      break;
    case 'b':
      flags |= F_BOUNDS;
      break;
    case 'n':
      flags |= F_NODES;
      break;
    case 'w':
      flags |= F_WAYS;
      break;
    case 'r':
      flags |= F_RELATIONS;
      break;
    default : /* '?' ':' */
      usage(argv[0], stderr);
      return 1;
    }
  }
  
  if(optind >= argc){
    usage(argv[0], stderr);
    return 1;
  } else docname = argv[optind];
  
  printDoc(docname, flags);
  
  return 0;
}

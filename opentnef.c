#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"
#include "tnef_api.h"



struct OTA_globals {
   char *tnef_file;
   char *output_directory;
   int verbose;
   int debug;
};

char OTA_DEFAULT_OUTPUT_DIRECTORY[]=".";
char OTA_VERSION[]="openTNEF version 0.1-dev";
char OTA_USAGE[]="openTNEF usage:\n\
\topentnef -i <TNEF encoded file> [-d <output directory>] [--verbose] [--debug] [--version]\n\
\n";

/*-----------------------------------------------------------------\
 Function Name	: parse_parameters
 Returns Type	: int
 	----Parameter List
	1. struct OTA_globals *glb, 
	2.  int argc, 
	3.  char **argv , 
 	------------------
 Exit Codes	: 
 Side Effects	: 
--------------------------------------------------------------------
 Comments:
 
--------------------------------------------------------------------
 Changes:
 
\------------------------------------------------------------------*/
int parse_parameters( struct OTA_globals *glb, int argc, char **argv )
{
   int i;
   char *p;

   if (argc < 2)
   {
      LOGGER_log("Insufficient parameters\n%s", OTA_USAGE );
      exit(1);
   }

   for (i = 1; i < argc; i++) 
   {
      p = argv[i];
      if (*p == '-')
      {
	 p++;

	 switch (*p) {
	 
	    case 'i':
	       i++;
	       glb->tnef_file = argv[i];
	       break;

	    case 'd':
	       i++;
	       glb->output_directory = argv[i];
	       break;

	    case 'v':
	       glb->verbose = 1;
	       break;

	    case '-':
	       p++;
	       if (strcmp(p,"verbose")==0)
	       {
		  glb->verbose =1;
	       } else if (strcmp(p,"debug")==0)
		  {
		  glb->debug =1;
	       } else if (strcmp(p,"version")==0) {
		  LOGGER_log("%s",OTA_VERSION);
		  exit(1);
	       } else {
		  LOGGER_log("Unknown paramters '%s'", p);
		  exit(1);
	       }

	       break;

	    default:
	       LOGGER_log("Unknown paramter '%s'\n%s\n%s", p, OTA_VERSION,OTA_USAGE);
	       exit(1);
	 } // switch *p
      } // if *p == -
   } // for i

   return 0;

}

/*-----------------------------------------------------------------\
 Function Name	: OTA_filename_report
 Returns Type	: int
 	----Parameter List
	1. char *contenttype, 
	2.  char *filename , 
 	------------------
 Exit Codes	: 
 Side Effects	: 
--------------------------------------------------------------------
 Comments:
 
--------------------------------------------------------------------
 Changes:
 
\------------------------------------------------------------------*/
int OTA_filename_report( char *contenttype, char *filename )
{
   LOGGER_log("Decoding: %s\n", filename );
   return 0;
}


/*-----------------------------------------------------------------\
 Function Name	: OTA_init
 Returns Type	: int
 	----Parameter List
	1. struct OTA_globals *glb , 
 	------------------
 Exit Codes	: 
 Side Effects	: 
--------------------------------------------------------------------
 Comments:
 
--------------------------------------------------------------------
 Changes:
 
\------------------------------------------------------------------*/
int OTA_init( struct OTA_globals *glb )
{
   glb->tnef_file = NULL;
   glb->output_directory = OTA_DEFAULT_OUTPUT_DIRECTORY;
   glb->verbose = 1;
   glb->debug = 0;
   LOGGER_set_output_mode( _LOGGER_STDOUT );
   TNEF_set_filename_report_fn( OTA_filename_report );

   return 0;
}

/*-----------------------------------------------------------------\
 Function Name	: main
 Returns Type	: int
 	----Parameter List
	1. int argc, 
	2.  char **argv , 
 	------------------
 Exit Codes	: 
 Side Effects	: 
--------------------------------------------------------------------
 Comments:
 
--------------------------------------------------------------------
 Changes:
 
\------------------------------------------------------------------*/
int main( int argc, char **argv )
{
   struct OTA_globals glb;

   OTA_init(&glb);
   TNEF_init();

   parse_parameters( &glb, argc, argv );

   TNEF_set_verbosity( glb.verbose );
   TNEF_set_debug( glb.debug );
   TNEF_set_path( glb.output_directory );
   TNEF_decode( glb.tnef_file );

   return 0;
}

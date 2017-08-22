#include <stdio.h>

extern void bimcode( char * bn );

extern int  yyparse(void);
extern FILE * yyin;
extern void add_sort( );
extern char BIM_Hello[];

void
main( int argc, char *argv[] )
{
   FILE * in;
   char filename[ 256 ];

   if( argc != 2 )
   {
	  fprintf(stderr, "%s\n", BIM_Hello);
	  fprintf(stderr, "Copyright (c) 1993-1997 TU Muenchen, Lehrstuhl Informatik II, Prof. J. Eickel\n");
      fprintf(stderr, "Usage: bim <lang>\n" );
      exit( 1 );
   }

   sprintf( filename, "%s_spec.g", argv[ 1 ] );

   if((in = fopen( filename, "r" )) != NULL)
   {
      yyin = in;
      yyparse( );
      bimcode( argv[ 1 ] ); 
      fclose( in );
   }
   else
   {
      fprintf( stderr, "Could not open Input file %s\n", filename );
      exit( 1 );
   }
   exit( 0 );   
}

void
yyerror( char * t )
{
   fprintf( stderr, "Error: %s\n", t );
}

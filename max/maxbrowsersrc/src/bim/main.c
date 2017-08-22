#include <stdio.h>

extern void bimcode( char * bn );

extern FILE * yyin;
extern void add_sort( );

main( int argc, char *argv[] )
{
   FILE * in;
   char filename[ 256 ];

   if( argc != 2 )
   {
      fprintf( stderr, "Usage: bim <lang>\n" );
      exit( 1 );
   }

   sprintf( filename, "%s_spec.g", argv[ 1 ] );

   if( in = fopen( filename, "r" ) )
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

yyerror( char * t )
{
   fprintf( stderr, "Error: %s\n", t );
}

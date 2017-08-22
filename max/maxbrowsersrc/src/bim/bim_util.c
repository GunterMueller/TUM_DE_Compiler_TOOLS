#include "/usr/stud/graf/fopra/bim_util.h"

#include <string.h>

int Bim_IsOfSort( MAX_NODE * node, char * name )
{
   int i;

   if( 0 == strcmp( node->name, name ) )
      return 1;

   for( i = 0; node->parent_sorts[ i ]; i++ )
      if( 0 == strcmp( node->parent_sorts[ i ] ) )
	 return 1;

   return 0;

}

static MAX_NODE * Bim_CopyMaxTree( MAX_NODE * tree, MAX_NODE * parent )
{
   MAX_NODE * res;

   res = malloc( sizeof( MAX_NODE ) );

   if( ! res )
   {
      fprintf( stderr, "Out of Mem\n" );
      exit( 1 );
   }

   res->next = res->prev = res->children = NULL;

   res->parent = parent;

   if( tree->children )
   {
      res->children = Bim_CopyMaxTree( tree->children, res ) ;
   }
   if( tree->next )
   {
      res->next = Bim_CopyMaxTreeIntern( tree->next, res );
      res->next->prev = res;
   }

   return res;
}

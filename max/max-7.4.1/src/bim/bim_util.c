#include "bim_util.h"

#include <string.h>
#include <stdio.h>

struct MAX_BIM_RELATION {
   long max_node;
   MAX_NODE * bim_node;
} * max_bim_relation; 

int Bim_IsOfSort( MAX_NODE * node, char * name )
{
   int i;

#ifdef DEBUG
   printf( "Testing for %s\n", name );
   printf( "Nod is of %s\n",node->node_info->name );
#endif

   if( 0 == strcmp( node->node_info->name, name ) )
      return 1;

   for( i = 0; node->node_info->parent_sorts[ i ]; i++ )
   {
#ifdef DEBUG
      printf( "testing against %s\n", node->node_info->parent_sorts[ i ] );
#endif
      if( 0 == strcmp( node->node_info->parent_sorts[ i ], name ) )
	 return 1;
   }

   return 0;

}

MAX_NODE * Bim_CopyMaxTree_Do( MAX_NODE * tree, MAX_NODE * parent )
{
   MAX_NODE * res;
   X_INFO * new_x;

   res = ( MAX_NODE * )malloc( sizeof( MAX_NODE ) );

   if( ! res )
   {
      fprintf( stderr, "Out of Mem\n" );
      exit( 1 );
   }

   * res = * tree;
   tree->origin_node = res;
   res->node_info = (NODE_INFO *)malloc( sizeof( NODE_INFO ) );

   if( ! res->node_info )
   {
      fprintf( stderr, "Out of Mem\n" );
      exit( 1 );
   }

   * ( res->node_info ) = * ( tree->node_info );

   if( tree->node_info->no_of_attributes ) 
   {
      int i;

      res->node_info->attributes = ( ATTR_INFO * )calloc( tree->node_info->no_of_attributes,
					   sizeof( ATTR_INFO ) );

      if( ! res->node_info->attributes )
	 exit( 1 );

      for( i = 0; i < res->node_info->no_of_attributes; i ++ )
	  res->node_info->attributes[ i ] = tree->node_info->attributes[ i ];
   }

   res->next = res->prev = res->children = NULL;

#if 0
   res->x_info.widget = res->x_info.context = NULL;
#else 
   res->x_info = (X_INFO *) CopyX_INFO( tree->x_info );
#endif

   res->parent = parent;

   if( tree->children )
   {
      res->children = Bim_CopyMaxTree_Do( tree->children, res ) ;
   }
   if( tree->next && parent )
   {
      res->next = Bim_CopyMaxTree_Do( tree->next, parent );
      res->next->prev = res;
   }


   return res;
}


static void sort_sort_names( char * list_of_sorts[ ] )
{
   static int is_sorted = 1;

   if( ! list_of_sorts[ 0 ] )
      return;

   do
   {
      int i;
      
      is_sorted = 1;

      for( i = 1; list_of_sorts[ i ]; i++ )
      {
	 if( strcasecmp( list_of_sorts[ i ],  list_of_sorts[ i - 1 ] ) < 0 )
	 {
	    char * h;

	    is_sorted = 0;

	    h = list_of_sorts[ i ];
	    list_of_sorts[ i ] = list_of_sorts[ i-1 ] ;
	    list_of_sorts[ i-1 ] = h;
	 }
      } 
   }while( ! is_sorted );
}

int Bim_NumberOfSorts( )
{
   
   extern char * list_of_sorts[ ];
   int nel;
   int Bim_total_sorts = 0;
   
   for( nel = 0; list_of_sorts[ nel ]; nel++ )
   {
      Bim_total_sorts++;
   }
   
   return Bim_total_sorts;

}
int Bim_NumberOfAttributes( )
{
   
   extern char * list_of_attrs[ ];
   int nel;
   int Bim_total_attributes = 0;
   
   for( nel = 0; list_of_attrs[ nel ]; nel++ )
   {
      Bim_total_attributes++;
   }
   
   return Bim_total_attributes;

}

char ** Bim_ListOfAttributes( )
{
   
   extern char * list_of_attrs[ ];
   int nel;

   sort_sort_names( list_of_attrs );


#if 0   
   for( nel = 0; list_of_attrs[ nel ]; nel++ )
      printf( "%s\n", list_of_attrs[ nel ] );
#endif
   
   return list_of_attrs;

}


char ** Bim_ListOfSorts( )
{
   
   extern char * list_of_sorts[ ];
   int nel;

   sort_sort_names( list_of_sorts );

#if 0   
   for( nel = 0; list_of_sorts[ nel ]; nel++ )
      printf( "%s\n", list_of_sorts[ nel ] );
#endif
      
   return list_of_sorts;

}
#if 0
void Bim_UpdateAttributes_MAX_NODE( MAX_NODE * tree, MAX_NODE * ref )
{
    int i;

    /* printf( " [ %x ] ", ref->origin_node ); */
    for( i = 0; i < tree->node_info->no_of_attributes; i++ )
    {
      /* printf( " %s ", tree->node_info->attributes[ i ].type ); 
       if( (0 == strcmp( "MAX_NODE", tree->node_info->attributes[ i ].type )) )
	  printf( " <%x> ", tree->node_info->attributes[ i ].attr_value ); */

	if( (0 == strcmp( "MAX_NODE", tree->node_info->attributes[ i ].type ))    &&
	     ( tree->node_info->attributes[ i ].attr_value == ( long )ref->origin_node ) )
	{
	   tree->node_info->attributes[ i ].attr_value = ( long )ref;
	   putchar( 'X' );
	   printf( " = ( %x )", ( long ) ref );
	}
	if( (0 == strcmp( "MAX_NODE", tree->node_info->attributes[ i ].type ))    &&
	     ( tree->node_info->attributes[ i ].attr_value ==  -536805377L ) )
	{
	   tree->node_info->attributes[ i ].attr_value = ( long )tree;
	}
    }

    if( tree->next )
	Bim_UpdateAttributes_MAX_NODE( tree->next, ref );

    if( tree->children )
	Bim_UpdateAttributes_MAX_NODE( tree->children, ref );

}


MAX_NODE * Bim_UpdateAttributes( MAX_NODE * tree, MAX_NODE * root )
{
   static int count = 0;


   /* printf( "Updating node %x ( o: %x ):\n", tree, tree->origin_node ); */

#if 0
   printf( "%d\n", count++ );
#endif

   Bim_UpdateAttributes_MAX_NODE( root, tree );
   /* putchar( '\n' ); */
   if( tree->next )
	Bim_UpdateAttributes( tree->next, root );

    if( tree->children )
	Bim_UpdateAttributes( tree->children, root );
   
   return tree;
}
#else

MAX_NODE * Bim_UpdateAttributes( MAX_NODE * tree, MAX_NODE * root )
{
   static int count = 0;
   int i;

   /* printf( "Updating node %x ( o: %x ):\n", tree, tree->origin_node ); */

#if 0
   printf( "%d\n", count++ );
#endif

   if( !tree )
      return NULL;

    for( i = 0; i < tree->node_info->no_of_attributes; i++ )
    {
       /* printf( " %s ", tree->node_info->attributes[ i ].type ); 
	  if( (0 == strcmp( "MAX_NODE", tree->node_info->attributes[ i ].type )) )
	  printf( " <%x> ", tree->node_info->attributes[ i ].attr_value ); */

       if( (0 == strcmp( "MAX_NODE", tree->node_info->attributes[ i ].type )) )
       {
	  if ( tree->node_info->attributes[ i ].attr_value ==  -536805377L ) 
	  {
	     tree->node_info->attributes[ i ].attr_value = 0 /*( long )tree*/;
	  }
	  else
	  {
	     /*printf( "--%x->", tree->node_info->attributes[ i ].attr_value );*/
	     tree->node_info->attributes[ i ].attr_value = (long)lookup_max_relation(  tree->node_info->attributes[ i ].attr_value );
	     /*printf( "%x--%x\n", tree->node_info->attributes[ i ].attr_value );*/
	  }
       }
       
    }


   /* putchar( '\n' ); */
   if( tree->next )
	Bim_UpdateAttributes( tree->next, root );

    if( tree->children )
	Bim_UpdateAttributes( tree->children, root );
   
   return tree;
}


#endif
static void ClearOriginNode( MAX_NODE * tree )
{
   tree->origin_node = NULL;

    if( tree->next )
	ClearOriginNode( tree->next );

    if( tree->children )
	ClearOriginNode( tree->children );
}

MAX_NODE * Bim_UpdateAttributesOnCopy( MAX_NODE * tree )
{
   int i;

#if 0
   printf( "Updating node %x\n", tree); 
   
#endif 

   for( i = 0; i < tree->node_info->no_of_attributes; i++ )
    {
      /* printf( " %s ", tree->node_info->attributes[ i ].type ); 
       if( (0 == strcmp( "MAX_NODE", tree->node_info->attributes[ i ].type )) )
	  printf( " <%x> ", tree->node_info->attributes[ i ].attr_value ); */

	if(0 == strcmp( "MAX_NODE", tree->node_info->attributes[ i ].type ) )
	{
	   if(((MAX_NODE*)(tree->node_info->attributes[ i ].attr_value))->origin_node )
	      tree->node_info->attributes[ i ].attr_value = 
		(long) ((MAX_NODE*)(tree->node_info->attributes[ i ].attr_value))->origin_node;
	}
     }

   if( tree->next )
	Bim_UpdateAttributesOnCopy( tree->next );

    if( tree->children )
	Bim_UpdateAttributesOnCopy( tree->children );
   
   return tree;
}


MAX_NODE * Bim_CopyMaxTree( MAX_NODE * tree, MAX_NODE * parent )
{
   MAX_NODE * nt, * clr;

#if 0
   printf( "CopyTree %x %x\n", tree, parent );
#endif
   
   for( clr = tree; clr->parent; clr = clr->parent );

   ClearOriginNode( clr );

   nt = Bim_CopyMaxTree_Do( tree, parent );
   return Bim_UpdateAttributesOnCopy( nt );
}

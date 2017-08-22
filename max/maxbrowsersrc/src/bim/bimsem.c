#include "bimsem.h"
#include <string.h>
#include <assert.h>

char sublist_buffer[ SUBLISTSIZE ];
char * attribute_names[ MAX_ANAMES ] = { NULL };
struct SORT sorts[ MAX_SORTS ];
struct PROD prods[ MAX_PRODS ];

int new_prod_idx = 0;
int new_sort_idx = 0;
int new_attr_name_idx = 0;


/**
**/

struct SORT * find_sort( char * name );


/**************************************************************
*
* NAME:
* PROCEDURE:
* INPUT:
* OUTPUT:
*
***************************************************************/


/**************************************************************
*
* NAME: add_production
* PROCEDURE: Fuegt zur Liste der Sortenproduktionen eine neue
*  Produktion hinzu.
* INPUT: int type: Gibt Art der Produktion an (Liste,Tupel,Klasse)
*        char * left: Zeiger auf linke Seite der Produktion
*        char * right: Zeiger auf rechte Seite
* OUTPUT:
*
***************************************************************/


void add_production( int type, char * left, char * right )
{
   prods[new_prod_idx ].prod_type = type;
   sprintf( prods[new_prod_idx ].left, "%s", left );
   memcpy( prods[new_prod_idx ].production, right, SUBLISTSIZE );
  

   new_prod_idx++;
}

/**************************************************************
*
* NAME: sem_sublist
* PROCEDURE: Hilft beim Aufbau der Subsorten einer Sorte.
*  Haengt an den Buffer eine neue Sorte an, und gibt einen
*  Zeiger zurueck, der hinter diese Sorte zeigt.
* INPUT: char * dest: Ziel
*        char * source: Ausgangssorte
* OUTPUT: char *: Zeiger auf das Ende des Buffers, hier kann die
*                 n"achste Sorte eingeh"ngt werden.
*
***************************************************************/


char * sem_sublist( char * dest, char * source )
{
   /*printf( " -- %s - %s --\n", dest, source );*/
   strcpy( dest, source );
   
   for( ; *dest; dest++ );  

    dest++;
   *dest = 0;

   return dest;
}

void add_semval( char * sortname )
{
   struct SORT * so;
   char * aname = NULL;
   char * afuncname = NULL;
   char * rsortname;

   if( 0 == strcmp( sortname, "Int" ) )
   {
      afuncname = "etoi( %s )";
      rsortname = "Int";
   } else if( 0 == strcmp( sortname, "Bool" ) ) 
   {
      afuncname = "cvt_bool_attr( %s )";
      rsortname = "Bool";
   }  else if( 0 == strcmp( sortname, "Ident" ) ) 
   {
      afuncname = "etoa( idtos( %s ) )";
      rsortname = "String";
   } else if( 0 == strcmp( sortname, "String" ) ) 
   {
      afuncname = "etoa( %s )";
      rsortname = "String";
   }

   if( !afuncname )
      return;


   if( so = find_sort( sortname ) )
   {
      
      strcpy( so->attrs[ so->new_attr_idx ].name, "<SEMVAL>" );
      strcpy( so->attrs[ so->new_attr_idx ].funcname, afuncname );
      so->attrs[ so->new_attr_idx ].rsort = find_sort( rsortname );
      so->attrs[ so->new_attr_idx ].pointer_to_node = 0;
      so->attrs[ so->new_attr_idx ].attribute_of_node = 0;
      so->new_attr_idx++;
   }
}

/**************************************************************
*
* NAME: add_sort
* PROCEDURE: F"ugt eine Sorte zur Liste der Sorten hinzu.
*  Eine Sonderbehandlung f"ur Sorten vom Typ "Node" ist n"otig,
*  da diese von nichts abgeleitet sein sollen und f"ur unsere
*  Darstellung die Wurzel des Baumes sind.
* INPUT: char * name: Name der Sorte
*        struct SORT * parent: Zeiger auf Vatersorte. Ist dies 
*             Null, so wird "Node" als Vatersorte angenommen
* OUTPUT:
*
***************************************************************/



void add_sort( char * name, struct SORT * parent )
{

   /*printf( "Adding sort %s derived from %s\n", name, parent->name );*/
   strcpy( sorts[ new_sort_idx ].name, name );

   if( !strcmp( "Node", name ) )
   {
      sorts[ new_sort_idx ].parent[ sorts[ new_sort_idx ].parent_count ] = parent ? parent : find_sort( "Node" );
      sorts[ new_sort_idx ].parent_count++;
   }
   
   /*printf( "%s\n", sorts[ new_sort_idx ].parent[ 0 ]->name );*/
   sorts[ new_sort_idx ].new_attr_idx = 0;

   

   new_sort_idx++;

   
}

/**************************************************************
*
* NAME: add_attr
* PROCEDURE: F"ugt ein Attribut zur Liste der Attribute hinzu.
* INPUT: char * asortname: Sorte, f"ur die dieses Attribut
*                          definiert ist
*        char * aname: Attributname
*        char * rsortname: Ergebnissorte
* OUTPUT:
*
***************************************************************/


void add_attr( char * asortname, char * aname , char * rsortname )
{
   struct SORT *so;
   int pointer_to_node = 0;
   int attribute_of_node = 0;

   /*printf( " ADDATTR( %s %s %s )\n", asortname, aname, rsortname );*/

   /**
     * Feststellen, ob dieses Attribut nur f"r Knoten definiert ist
     * ( Name endet mit @ )
     */


   if( '@' == asortname[ strlen( asortname ) - 1 ] )
   {
      asortname[ strlen( asortname ) - 1 ] = 0;
      attribute_of_node = 1;
   }

   /**
     * Feststellen, ob Attribut einen Knoten liefert
     */

   if( '@' == rsortname[ strlen( rsortname ) - 1 ] )
   {
      pointer_to_node =1;
      rsortname[ strlen( rsortname ) -1 ] = 0;
   }

   /*printf( " ADDATTR( %s %s %s )\n", asortname, aname, rsortname );*/

   /** 
     * Sorte finden, f"ur die dieses Attribut definiert wurde.
     */
   so = find_sort( asortname );

   /**
     * In der Sorte das Attribut eintragen
     */

   if( so )
   {
      strcpy( so->attrs[ so->new_attr_idx ].name, aname );
      
      if( 0 == strcmp( rsortname, "String" ) )
      {
	 sprintf( so->attrs[ so->new_attr_idx ].funcname, "cvt_string_attr( %s( %%s ) )", aname );
      }
#if 0
      else
      {
	 sprintf( so->attrs[ so->new_attr_idx ].funcname, "%s( %%s )", aname );
      }
#else  /* Aenderung nach Besprechung mit Arndt */
      else if( 0 == strcmp( rsortname, "Int" ) )
      {
	 sprintf( so->attrs[ so->new_attr_idx ].funcname, "cvt_int_attr( %s(%%s) )", aname );
      } 
      else if( 0 == strcmp( rsortname, "Bool" ) )
      {
	 sprintf( so->attrs[ so->new_attr_idx ].funcname, "cvt_bool_attr( %s(%%s) )", aname );
      } 
      else
      {
	 sprintf( so->attrs[ so->new_attr_idx ].funcname, "%s( %%s )", aname );
      }
#endif
      so->attrs[ so->new_attr_idx ].rsort = find_sort( rsortname );
      so->attrs[ so->new_attr_idx ].pointer_to_node = pointer_to_node;
      so->attrs[ so->new_attr_idx ].attribute_of_node = attribute_of_node;
      so->new_attr_idx++;
   }

   attribute_names[ new_attr_name_idx ++ ] = strdup( aname );
   attribute_names[ new_attr_name_idx  ] = NULL;
}



/**************************************************************
*
* NAME: add_classsort
* PROCEDURE: F"ugt eine Sorte, die eine Klasse ist, zur Liste
*   der Sorten hinzu.
* INPUT: char * name: Sortenname
* OUTPUT:
*
***************************************************************/


void add_classsort( char * name )
{
   int cs;
   char * sn;

   /*printf( "SLB:%s\n", sublist_buffer );*/

   add_sort( name, NULL ); 

   cs = new_sort_idx - 1;

  
   add_production( CLASSPROD, name, sublist_buffer );

   memcpy( sorts[ cs ].sublist_buffer, sublist_buffer, SUBLISTSIZE );
   sublist_buffer[ 0 ] = 0;
   sublist_buffer[ 1 ] = 0;
}

void add_tupleprod( char * name )
{
   add_production( TUPLEPROD, name, sublist_buffer );

}
void add_listprod( char * name )
{
   add_production( LISTPROD, name, sublist_buffer );

}

/**************************************************************
*
* NAME: dump_info
* PROCEDURE: Gibt Informationen "uber die internen Tabellen aus.
*  Wird nur zum Debuggen ben"otigt.
* INPUT:
* OUTPUT:
*
***************************************************************/


void dump_info( )
{
   int i;
   char * sn; 
   for( i = 0; i < new_sort_idx; i++ )
   {
      for( sn = sorts[ i ].sublist_buffer; *sn; )
      {
	 struct SORT * so;
	 
	 if( so = find_sort( sn ) )
	 {
	    printf( "Class %s has child %s\n", sorts[ i ].name, so->name );
	    so->parent[ so->parent_count ] = & ( sorts[ i ] );
	    so->parent_count++;
	 }
	 else
	 {
	    printf( "Error: Class %s has child of undefined class %s\n",
		  sorts[ i ].name, sn );
	    exit( 1 );
	 }

	 for( ; *sn; sn++ );
	 sn++;
      }
   }


   for( i = 0; i < new_sort_idx; i++ )
      if( (sorts[ i ].parent_count == 0) && ( 0 != strcmp( sorts[ i ].name, "Node" ) ) && ( 0 != strcmp( sorts[ i ].name, "Element" ) ))
      {
	 
	 printf( "Class %s is derived from Node\n", sorts[ i ].name );
	 sorts[ i ].parent[ 0 ] = find_sort( "Node" );
      }

   for( i = 0; i < new_sort_idx; i ++ )
   {
      int j;

      printf( "%s -->", sorts[ i ].name );
      for( j = 0 ; j < sorts[ i ].parent_count; j++ )
	  printf( "%s  ", sorts[ i ].parent[ j ]->name  );
      
      for( j = 0; j < sorts[ i ].new_attr_idx; j++ )
	 printf( "%s%s ", sorts[ i ].attrs[ j ].name,  sorts[ i ].attrs[ j ].attribute_of_node ? "@" : "");

      printf( "\n" );
   }

   for( i = 0; i < new_prod_idx; i ++ )
   {
      printf( "%d %s\n", prods[ i ].prod_type, prods[ i ].left );
   }

}

/**************************************************************
*
* NAME: find_sort
* PROCEDURE: Sucht in der Tabelle der Sorteneintr"age nach einer
*  Sorte mit angegebenem Namen.
* INPUT: char * name: Sortenname
* OUTPUT: struct SORT *: Zeiger auf den Sorteneintrag oder NULL,
*                        falls Eintrag nicht gefunden.
*
***************************************************************/


struct SORT * find_sort( char * name )
{
   int i;

   for( i = 0; i < new_sort_idx; i++ )
      if( 0 == strcmp( sorts[ i ].name, name ) )
	 return &(sorts[ i ]);

   return NULL;
}

/**********************************************************************
 *
 * MODULE: bimcode.c 
 * PROJECT: bim
 *
 * Diese Routinen "ubernehmen die Erzeugung der Datei 42.c nachdem
 * <sprache>_spec.g analysiert wurde. Dieses Modul verarbeitet die
 * Informationen, die durch bimsem.c bereitgestellt werden
 *
 ********************************************************************/

#include <stdio.h>
#include "bim_sem.h"

void emit_header( void );
void emit_bim_sort_name( void );
void emit_term_parse_table( void );
void emit_sort_dependencies( void );
void emit_bim_nodeinfo( void );
void emit_bim_number_of_attributes( void );
void emit_sort_attributes( void );
void emit_sort_dependency( void );
void emit_attr_list( void );
void emit_list_of_sorts_array( void );
void emit_list_of_attrs_array( void );
void emit_standard_code( void );
char * basename;

extern void add_semval( char * );

/**
 * Das Dateihandle f"ur die Ausgabedatei
 */

FILE * outf;

/**
 * Definieren, mit welchen Sorten max arbeitet
 */

#define SORT_TYPE "int"
#define NODE_TYPE "long int"

/**
 * Die allgemein ben"otigten Includes
 */

char * includes[] = { "<string.h>","<stdlib.h>", "<stdio.h>", "<bim_nodeinfo.h>",NULL };


/*
  
  char * treeprinter = "void treeprinter( MAX_NODE * node ){\n"\
  "\t MAX_NODE * run;\n"\
  "\t int i;\n"\
  "\t printf( \"%%s with %%d attributes\" , node->node_info->name, node->node_info->no_of_attributes );\n"\
  
  "\t if( run = node->children ){\n"\
  "\t\t printf( \"(\" );\n"\
  "\t\t while( run ){\n"\
  "\t\t\t treeprinter( run );\n"\
  "\t\t\t if( run = run->next ) printf(\",\\n\" );"\
  "\t\t }\n"\
  "\t\t printf( \")\" );\n"\
  "\t }\n"\
  "}\n";
  */


void reset_visited( struct SORT * s )
{
   int i;

   if( !s )
      return;

   s->visited = 0;
   
   for( i = 0; i < s->parent_count; i ++ )
      reset_visited( s->parent[ i ] );
}

void fap( struct SORT * s, void (*f)(struct SORT *, int * ), int * ip )
{
   int i;

   if( !s )
      return;

   for( i  = 0; i < s->parent_count; i ++ )
      if( !s->parent[ i ]->visited )
      {
	 f( s->parent[ i ], ip );
	 s->parent[ i ]->visited = 1;
	 fap( s->parent[ i ], f, ip );
      }
}

void for_all_parents( struct SORT * s, void (*f)(struct SORT *, int * ), int * ip)
{
   reset_visited( s );

   fap( s,f, ip );
}

/*****************************************************************************
 * NAME:  semval_typ                                                
 * PROCEDURE: Ermittelt zu einem Typnamen den dazugehoerigen Typ des semantischen
 *   Werts. Gibt fuer Typen, die einen semantischen Wert haben, den Typ dieses
 *   Wertes als C-String zurueck. Typen, denen kein semantischer Wert zugeordnet
 *   ist, ergeben als Resultat einen NULL-Zeiger.
 * INPUT: char * typ :    Name des Typen
 * OUTPUT: char * : Name des Typen des semantischen Werts                                                            
 *****************************************************************************/
   
   
   static char * semval_typ( char * typ )
{
   if( 0 == strcmp( "Int", typ ) )
      return "Int";
   
   if( 0 == strcmp( "Ident", typ ) )
      return "String";
   
   if( 0 == strcmp( "String", typ ) )
      return "String";
   
   if( 0 == strcmp( "Bool", typ ) )
      return "Bool";
   return NULL;
}
/*****************************************************************************
 * NAME:  actual_attributes
 * PROCEDURE: Zaehlt durch, wieviele Attribute eine Sorte wirklich hat, dazu
 *   summiert die Funktion die Anzahl die Attribute dieses Knoten und aller
 *   seiner Vorfahren.
 * INPUT: struct SORT * p : Zeiger auf Sortendefinition
 * OUTPUT: int : Anzahl der Attribute
 *****************************************************************************/

void aph( struct SORT *p, int * ip )
{
   * ip += p->new_attr_idx;
}   
   
#if 0
   int actual_attributes( struct SORT * p )
{
   int res = 0;
   
   for( ; p; p=p->parent )
      res += p->new_attr_idx;
   
   return res;
}
#else
   int actual_attributes( struct SORT * p )
{
   int res = p->new_attr_idx;
   
   for_all_parents( p, aph, &res );
   
   return res;
}
#endif
/*****************************************************************************
 * NAME:  actual_node_attributes
 * PROCEDURE: Zaehlt durch, wieviele Attribute eine Sorte wirklich hat, wenn
 *   es sich bei der Instanz um einen Knoten handelt. 
 *   Die Funktion sumimert die Anzahl der Knoten-Attribute dieses Knoten und 
 *   aller seiner Vorfahren.
 * INPUT: struct SORT * p : Zeiger auf Sortendefinition
 * OUTPUT: int : Anzahl der Attribute
 *****************************************************************************/
   

void anh( struct SORT *p, int * ip )
{
   int i;

   for( i = 0; i < p->new_attr_idx; i ++ )
      if( p->attrs[ i ].attribute_of_node )
	    (*ip)++;
}

#if 0
   int actual_node_attributes( struct SORT * p )
{
   int res = 0;
   int i;
   
   for( ; p; p=p->parent )
      for( i = 0; i < p->new_attr_idx; i ++ )
	 if( p->attrs[ i ].attribute_of_node )
	    res++;
   
   return res;
}
#else
int actual_node_attributes( struct SORT * p )
{
   int res = 0;
   int i;
   
   for( i = 0; i < p->new_attr_idx; i ++ )
      if( p->attrs[ i ].attribute_of_node )
	 res++;

   for_all_parents( p, anh, &res );
   
   return res;
}
#endif
/*****************************************************************************
 * NAME:  actual_term_attributes
 * PROCEDURE: Zaehlt durch, wieviele Attribute eine Sorte wirklich hat, wenn
 *   es sich bei der Instanz nicht um einen Knoten handelt. 
 * INPUT: struct SORT * p : Zeiger auf Sortendefinition
 * OUTPUT: int : Anzahl der Attribute
 *****************************************************************************/
   
   int actual_term_attributes( struct SORT * p )
{
   
   return actual_attributes( p ) - actual_node_attributes( p );
}



/*****************************************************************************
 * NAME:   bimcode
 * PROCEDURE: Gibt den zu erzeugenden Code in die Datei 42.c aus.
 * INPUT: char * bn: Name der Sprache
 * OUTPUT: ---
 *****************************************************************************/
   
   void bimcode( char * bn )
{
   basename = bn;
   
   add_semval( "Int" );
   add_semval( "String" );
   add_semval( "Ident" );
   add_semval( "Bool" );
   
   if( (outf = fopen( "42.c", "w" )) != NULL )
   {
      
      emit_header( );
      emit_term_parse_table( );
      emit_list_of_sorts_array( );
      emit_list_of_attrs_array( );
      emit_sort_dependencies( );
      
      emit_sort_attributes( );    
      emit_bim_sort_name( );
      
      emit_bim_nodeinfo( );
      emit_bim_number_of_attributes( );
      emit_sort_dependency( );
      emit_attr_list( );
      
      emit_standard_code( );
      fclose( outf );
   }
}
/*****************************************************************************
 * NAME:  replace_suffix
 * PROCEDURE: Ersetzt ein Dateisuffix durch ein anderes.
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   
   int replace_suffix( char * dest, int size, char * newsuff, char * source )
{
   char * p;
   
   strcpy( dest, source );
   
   for( p = dest; * p; p++ )
      if( *p == '.' )
      {
	 p++;
	 strcpy( p, newsuff );
	 return 1;
      }
   
   return 0;
}
/*****************************************************************************
 * NAME:  emit_header
 * PROCEDURE: Gibt den Header der Zieldatei aus.
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   
   void emit_header( )
{
   int i = 0;
   char fname[ 256 ];
   fprintf( outf, "/**\n ** Computer generated browserinterface to max\n **\n **/\n" );
   
   while( includes[ i ] )
      fprintf( outf, "#include %s\n", includes[ i++ ] );
   
   sprintf( fname, "%s_spec.h", basename );
   fprintf( outf, "#include \"%s\"\n",  fname );
   
   fprintf( outf, "#define PROD_CLASS ( 0 )\n" );
   fprintf( outf, "#define PROD_TUPLE ( 1 )\n" );
   fprintf( outf, "#define PROD_LIST ( 2 )\n" );
   
   fprintf( outf, "\nATTR_INFO * attr_list( );\n" );
   fprintf( outf, "\nlong Number_of_Nodes;\n" );
   fprintf( outf, "\nstruct MAX_BIM_RELATION {\n\t long max_node;\n\t MAX_NODE * bim_node;\n} * max_bim_relation;\n" );
   fprintf( outf , "\n\n char ** sort_dependency( %s );\n", SORT_TYPE );
   fprintf( outf , "long cvt_string_attr( ELEMENT );\n" );
   fprintf( outf , "long cvt_bool_attr( ELEMENT );\n" );
   fprintf( outf , "long cvt_int_attr( ELEMENT );\n" );
   fprintf( outf , "ATTR_INFO * xref_attr( long node );\n" );

   fprintf( outf , "\n/*This is a dirty hack in bimcode.c - FIXME ! */\n" );
fprintf( outf ,"#ifndef btoe\n");
fprintf( outf ,"#define btoe(BOOLVAL)       mxi_btoe(__FILE__,__LINE__,BOOLVAL)\n");
fprintf( outf ,"#define ctoe(CHARVAL)       mxi_ctoe(__FILE__,__LINE__,CHARVAL)\n");
fprintf( outf ,"#define itoe(INTVAL)        mxi_itoe(__FILE__,__LINE__,INTVAL)\n");
fprintf( outf ,"#define atoe(STRVAL)        mxi_atoe(__FILE__,__LINE__,STRVAL)\n");
fprintf( outf ,"#define ptoe(POINTVAL)      mxi_ptoe(__FILE__,__LINE__,POINTVAL)\n");
fprintf( outf ,"#define etob(BOOLELEM)      mxi_etob(__FILE__,__LINE__,BOOLELEM)\n");
fprintf( outf ,"#define etoc(CHARELEM)      mxi_etoc(__FILE__,__LINE__,CHARELEM)\n");
fprintf( outf ,"#define etoi(INTELEM)       mxi_etoi(__FILE__,__LINE__,INTELEM)\n");
fprintf( outf ,"#define etoa(STRELEM)       mxi_etoa(__FILE__,__LINE__,STRELEM)\n");
fprintf( outf ,"#define etop(REFELEM)       mxi_etop(__FILE__,__LINE__,REFELEM)\n");
fprintf( outf ,"#define stoid(STRING)       mxi_stoid(__FILE__,__LINE__,STRING)\n");
fprintf( outf ,"#define idtos(IDENT)        mxi_idtos(__FILE__,__LINE__,IDENT)\n");
fprintf( outf ,"#define sort(ELEM)          mxi_sort(__FILE__,__LINE__,ELEM)\n");
fprintf( outf ,"#define index(ELEM,SORT)    mxi_index(__FILE__,__LINE__,ELEM,SORT)\n");
fprintf( outf ,"#define element(INDEX,SORT) mxi_element(__FILE__,__LINE__,INDEX,SORT)\n");
fprintf( outf ,"#define number(SORT)        mxi_number(__FILE__,__LINE__,SORT)\n");
fprintf( outf ,"#define fath(NODE)          mxi_fath(__FILE__,__LINE__,NODE)\n");
fprintf( outf ,"#define lbroth(NODE)        mxi_lbroth(__FILE__,__LINE__,NODE)\n");
fprintf( outf ,"#define rbroth(NODE)        mxi_rbroth(__FILE__,__LINE__,NODE)\n");
fprintf( outf ,"#define son(ITH,NODE)       mxi_son(__FILE__,__LINE__,ITH,NODE)\n");
fprintf( outf ,"#define numsons(NODE)       mxi_numsons(__FILE__,__LINE__,NODE)\n");
fprintf( outf ,"#define subterm(ITH,TERM)   mxi_subterm(__FILE__,__LINE__,ITH,TERM)\n");
fprintf( outf ,"#define numsubterms(TERM)   mxi_numsubterms(__FILE__,__LINE__,TERM)\n");
fprintf( outf ,"#define term(NODE)          mxi_term(__FILE__,__LINE__,NODE)\n");
fprintf( outf ,"#define before(NODE)        mxi_before(__FILE__,__LINE__,NODE)\n");
fprintf( outf ,"#define after(NODE)         mxi_after(__FILE__,__LINE__,NODE)\n");
fprintf( outf ,"#define node(POINT)         mxi_node(__FILE__,__LINE__,POINT)\n");
fprintf( outf ,"#define eq(ELEM1,ELEM2)     mxi_eq(__FILE__,__LINE__,ELEM1,ELEM2)\n");
fprintf( outf ,"#define is(ELEM,SORT)       mxi_is(__FILE__,__LINE__,ELEM,SORT)\n");
fprintf( outf ,"#define root()         -939524095L\n");
fprintf( outf ,"#define true()         -268435455L\n");
fprintf( outf ,"#define false()        -268435456L\n");
fprintf( outf ,"#define nil()          -536805377L\n");
fprintf( outf ,"#endif\n");
fprintf( outf , "/* end of dirty hack in bimcode.c - FIXME ! */\n\n" );
   
}
/*****************************************************************************
 * NAME:  emit_bim_sort_name
 * PROCEDURE: Gibt die Funktion aus, die zu jeder Sorte deren Namen als String
 *           zur"uckgibt
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   
   void emit_bim_sort_name( )
{
   int i;
   
   fprintf( outf, "\n\nchar * bim_sort_name( %s sort )\n{\n", SORT_TYPE );
   
   fprintf( outf, "\t switch( sort )\n\t {" );
   for( i = 0; i < new_sort_idx; i++ )
   {
      fprintf( outf, "\n#ifdef _%s_\n\t\t case _%s_: return \"%s\"; break;\n#endif\n",
	      sorts[ i ].name, sorts[ i ].name, sorts[ i ].name );
      fprintf( outf, "\n#ifdef _%s\n\t\t case _%s: return \"%s\"; break;\n#endif\n",
	      sorts[ i ].name, sorts[ i ].name, sorts[ i ].name );
   }
   fprintf( outf, "\n\n\t\t default: return \"<BOGUSNAME>\"; break;\n" );
   fprintf( outf, "\t }\n" );
   fprintf( outf, "}\n" );
}
/*****************************************************************************
 * NAME:  emit_sort_dependency
 * PROCEDURE: Gibt die Liste der Sortenabhaengigkeiten aus
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   
   void emit_sort_dependency( )
{
   int i;
   
   fprintf( outf, "\n\nchar ** sort_dependency( %s sort )\n{\n", SORT_TYPE );
   
   fprintf( outf, "\t switch( sort )\n\t {\n" );
   
   for( i = 0; i < new_sort_idx; i++ )
      fprintf( outf, "\n#ifdef _%s_\n\t\t case _%s_: return sort_depen_%s; break;\n#endif\n",
	      sorts[ i ].name, sorts[ i ].name, sorts[ i ].name );
   
   fprintf( outf, "\t }\n\t return NULL;\n" );
   fprintf( outf, "}\n" );
}
/*****************************************************************************
 * NAME:   emit_bim_nodeinfo
 * PROCEDURE: Gibt die Routine get_nodeinfo() aus.
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   
   void emit_bim_nodeinfo( )
{
   fprintf( outf, "\n\nNODE_INFO * get_node_info( %s node, int with_attributes )\n{\n", NODE_TYPE );
   fprintf( outf,"\t NODE_INFO * res;\n\n" );
   
   fprintf( outf,"\t if( res = malloc( sizeof( NODE_INFO ) ) )\n\t {\n" );
   fprintf( outf,"\t\t res->name = bim_sort_name( sort( node ) );\n" );
   fprintf( outf,"\t\t res->parent_sorts = sort_dependency( sort( node ) );\n"  );
   fprintf( outf,"\t\t res->no_of_attributes = bim_number_of_attributes( sort( node ) );\n"  );
   fprintf( outf,"\t\t if( with_attributes )\n" );
   fprintf( outf,"\t\t\t res->attributes = attr_list( node,&( res->no_of_attributes) );\n" );
   /* Geaendert (long)xref....*/
    fprintf( outf,"\t\t else {res->attributes = xref_attr( node ); res->no_of_attributes = 0; }\n" );
   fprintf( outf, "\t }\n return res;\n}\n" );
   
   
}

/*****************************************************************************
 * NAME:   emit_bim_number_of_attributes
 * PROCEDURE: Gibt f"ur jede Sorte die Anzahl ihrer Attribute zur"uck.
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   
   
   void emit_bim_number_of_attributes( void )
{
   int i;
   
   fprintf( outf, "\n\nint bim_number_of_attributes( %s sort )\n{\n", SORT_TYPE );
   fprintf( outf, "\t switch( sort )\n\t {" );
   for( i = 0; i < new_sort_idx; i++ )
   {
      fprintf( outf, "\n#ifdef _%s_\n\t\t case _%s_: return %d; break;\n#endif\n",
	      sorts[ i ].name, sorts[ i ].name, actual_attributes( &sorts[ i ] ) + ( NULL != semval_typ( sorts[ i ].name )  ? 1 : 0 ));
      fprintf( outf, "\n#ifdef _%s\n\t\t case _%s: return %d; break;\n#endif\n",
	      sorts[ i ].name, sorts[ i ].name, actual_term_attributes( &sorts[ i ] ) + ( NULL != semval_typ( sorts[ i ].name )  ? 1 : 0 ));
   }
   fprintf( outf,"\t\t default: fprintf( stderr, \"Default in %%s, Line %%d\\n\", __FILE__, __LINE__ ); return 0;break;\n" );
   fprintf( outf, "\t }\n}\n" );
   
}
/*****************************************************************************
 * NAME:  emit_sort_dependencies
 * PROCEDURE: Gibt die Sortenabh"angigkeiten aus.
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   
static void esd_hlp( struct SORT * s, int * ix )
{
   fprintf( outf, "\"%s\",", s->name);
}

   void emit_sort_dependencies( )
{
   int i;
   
   for( i = 0; i < new_sort_idx; i++ )
   {
     /*      struct SORT * p;*/
      
      fprintf( outf, "char * sort_depen_%s[] = {", sorts[ i ].name );

      for_all_parents( &sorts[ i ], esd_hlp, NULL );

      fprintf( outf, "NULL };\n" );
      
   }
}


/*****************************************************************************
 * NAME:  emit_sort_attributes
 * PROCEDURE: Gibt die Funktionen aus, die die Sorten berechnen sollen.
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   

void esah( struct SORT * p, int * ix )
{
   
   int j;
	    
	    for( j = 0; j < p->new_attr_idx; j ++ )
	    {
	       /**
		* Wenn das Attribut fuer einen Knoten definiet ist, wir aber hier keinen haben,
		* dann ueberspringen
		**/
	       
	       if( p->attrs[ j ].attribute_of_node ) 
	       {
		  fprintf( outf, "\t\t if( is_a_node )\n\t\t {\n" );
	       }
	       
	       /** Attributname zuweisen **/
	       
	       fprintf( outf, 
		       "\t\t res[ idx ].name = \"%s\";\n", 
		       p->attrs[ j ].name );
	       
	       /** Attributwert zuweisen **/
	       
	       
	       if(  p->attrs[ j ].attribute_of_node )
	       {
		  fprintf( outf, 
			  "\t\t res[ idx ].attr_value = (long) " );
		  fprintf( outf,
			  p->attrs[ j ].funcname, "node" );
		  fprintf( outf, 
			  ";\n " );
	       }
	       else
	       {
		  fprintf( outf, "\t\t if( is_a_node )\n\t\t {\n" );
		  
		  fprintf( outf, 
			  "\t\t res[ idx ].attr_value = (long) " );
		  fprintf( outf,
			  p->attrs[ j ].funcname, "term( node )" );
		  fprintf( outf, 
			  ";\n " );
		  
		  fprintf( outf, "\t\t }\n\t\t else\n\t\t {\n" );
		  
		  fprintf( outf, 
			  "\t\t res[ idx ].attr_value = (long) " );
		  fprintf( outf,
			  p->attrs[ j ].funcname, "node" );
		  fprintf( outf, 
			  ";\n " );
		  
		  fprintf( outf, "\t\t }\n" );
	       }
	       if( p->attrs[ j ].pointer_to_node )
	       {
		  fprintf( outf, "\t\t res[ idx ].type = \"MAX_NODE\";\n" );
	       }
	       else
	       {
		  if( semval_typ( p->attrs[ j ].rsort->name ) )
		  {
		     fprintf( outf, "\t\t res[ idx ].type = \"%s\";\n", p->attrs[ j ].rsort->name );
		  }
		  else
		  {
		     fprintf( outf, "\t\t res[ idx ].type = \"Term %s\";\n", p->attrs[ j ].rsort->name );
		     fprintf( outf, "\t\t res[ idx ].attr_value = (long)parse_max_term(   res[ idx ].attr_value, _%s );\n", p->attrs[ j ].rsort->name );
		     fprintf( outf, "\t\t res[ idx ].attr_value = (long)Bim_UpdateAttributes( (MAX_NODE *)(res[ idx ].attr_value), (MAX_NODE *)(res[ idx ].attr_value));\n" );
		  }
	       }
	       fprintf( outf, "\t\t res[ idx ].defined_by_sort = \"%s\";\n",  p->name );
	       fprintf( outf, "\t\t idx++;\n" );
	       fprintf( outf, "\n" );
	       
	       if( p->attrs[ j ].attribute_of_node ) 
	       {
		  fprintf( outf, "\t\t }\n" );
	       }
	       
	    } /* for( j = 0; j < p->new_attr_idx; j ++ ) */
	 } /* for( p = &sorts[ i ]; p ; p = p->parent ) */
	 



void emit_sort_attributes( )
{
   int i;
   /*   struct SORT * p;*/
   
   
   fprintf( outf, "/**\n ** Attribute pro Sorte\n **/\n" );
   
   for( i = 0; i < new_sort_idx; i ++ )
   {
      if( actual_attributes( &sorts[ i ] ) || ( NULL != semval_typ( sorts[ i ].name ) ) )  /** No attributes, no function **/
      {
	 
	 fprintf( outf, "ATTR_INFO * attributes_%s( %s node, int * count )\n{\n", sorts[ i ].name, NODE_TYPE );
	 fprintf( outf, "\t ATTR_INFO * res;\n" );
	 fprintf( outf, "\t int is_a_node;\n\n" );
	 fprintf( outf, "\t int idx = 0;\n\n" );
	 fprintf( outf, "\t * count = 0;\n\n" );
	 fprintf( outf, "\t is_a_node = is( node, _Node ) ? 1 : 0;\n"  ); 
	 
	 fprintf( outf, "\t if( res = malloc( ( %d + is_a_node * %d ) * sizeof( ATTR_INFO ) ) )\n\t {\n", 
		 actual_term_attributes(  &sorts[ i ]  ),
		 actual_node_attributes(  &sorts[ i ]  ) );
	 
	 #if 0
	 for( p = &sorts[ i ]; p ; p = p->parent[ 0 ] )
	 {
	    int j;
	    
	    for( j = 0; j < p->new_attr_idx; j ++ )
	    {
	       /**
		* Wenn das Attribut fuer einen Knoten definiet ist, wir aber hier keinen haben,
		* dann ueberspringen
		**/
	       
	       if( p->attrs[ j ].attribute_of_node ) 
	       {
		  fprintf( outf, "\t\t if( is_a_node )\n\t\t {\n" );
	       }
	       
	       /** Attributname zuweisen **/
	       
	       fprintf( outf, 
		       "\t\t res[ idx ].name = \"%s\";\n", 
		       p->attrs[ j ].name );
	       
	       /** Attributwert zuweisen **/
	       
	       
	       if(  p->attrs[ j ].attribute_of_node )
	       {
		  fprintf( outf, 
			  "\t\t res[ idx ].attr_value = (long) " );
		  fprintf( outf,
			  p->attrs[ j ].funcname, "node" );
		  fprintf( outf, 
			  ";\n " );
	       }
	       else
	       {
		  fprintf( outf, "\t\t if( is_a_node )\n\t\t {\n" );
		  
		  fprintf( outf, 
			  "\t\t res[ idx ].attr_value = (long) " );
		  fprintf( outf,
			  p->attrs[ j ].funcname, "term( node )" );
		  fprintf( outf, 
			  ";\n " );
		  
		  fprintf( outf, "\t\t }\n\t\t else\n\t\t {\n" );
		  
		  fprintf( outf, 
			  "\t\t res[ idx ].attr_value = (long) " );
		  fprintf( outf,
			  p->attrs[ j ].funcname, "node" );
		  fprintf( outf, 
			  ";\n " );
		  
		  fprintf( outf, "\t\t }\n" );
	       }
	       if( p->attrs[ j ].pointer_to_node )
	       {
		  fprintf( outf, "\t\t res[ idx ].type = \"MAX_NODE\";\n" );
	       }
	       else
	       {
		  if( semval_typ( p->attrs[ j ].rsort->name ) )
		  {
		     fprintf( outf, "\t\t res[ idx ].type = \"%s\";\n", p->attrs[ j ].rsort->name );
		  }
		  else
		  {
		     fprintf( outf, "\t\t res[ idx ].type = \"Term %s\";\n", p->attrs[ j ].rsort->name );
		     fprintf( outf, "\t\t res[ idx ].attr_value = (long)parse_max_term(   res[ idx ].attr_value, _%s );\n", p->attrs[ j ].rsort->name );
		     fprintf( outf, "\t\t res[ idx ].attr_value = (long)Bim_UpdateAttributes( (MAX_NODE *)(res[ idx ].attr_value), (MAX_NODE *)(res[ idx ].attr_value));\n" );
		  }
	       }
	       fprintf( outf, "\t\t res[ idx ].defined_by_sort = \"%s\";\n",  p->name );
	       fprintf( outf, "\t\t idx++;\n" );
	       fprintf( outf, "\n" );
	       
	       if( p->attrs[ j ].attribute_of_node ) 
	       {
		  fprintf( outf, "\t\t }\n" );
	       }
	       
	    } /* for( j = 0; j < p->new_attr_idx; j ++ ) */
	 } /* for( p = &sorts[ i ]; p ; p = p->parent ) */
	 #else
	 esah( &sorts[ i ], NULL );
	 for_all_parents( &sorts[ i ], esah, NULL );
	 #endif
	 
	 fprintf( outf, "\t\t *count = idx;\n" );
	 fprintf( outf,"\t }\n\t return res;\n}\n" );
      }
   }
   
   
}
/*****************************************************************************
 * NAME:  emit_attr_list
 * PROCEDURE: Gibt f"ur ein MAX-Element die Liste der Knoten zur"uck
 * INPUT:
 * OUTPUT:
 ***************************************************************************/
   

  
void emit_attr_list( )
{
   
   int i;
   
   fprintf( outf, "\n\nATTR_INFO * attr_list( ELEMENT n, int * count )\n{\n" );
   /*fprintf( outf, "\t ELEMENT  termv = term(n);");*/
   fprintf( outf, "\t switch( sort( n ) )\n\t {\n" );
   
   for( i = 0; i < new_sort_idx; i++ )
      if( actual_attributes( &sorts[ i ] ) || ( NULL != semval_typ( sorts[ i ].name) ) )
      {
	 fprintf( outf, "#ifdef _%s_\n\t\t case _%s_: return attributes_%s( n, count ); break;\n#endif\n",
		 sorts[ i ].name, sorts[ i ].name, sorts[ i ].name );
	 fprintf( outf, "#ifdef _%s\n\t\t case _%s: return attributes_%s( n, count ); break;\n#endif\n",
		 sorts[ i ].name, sorts[ i ].name, sorts[ i ].name );
	 
      }
   
   fprintf( outf, "\t }\n\t return NULL;\n" );
   fprintf( outf, "}\n" );
}
/*****************************************************************************
 * NAME: emit_list_of_sorts_array 
 * PROCEDURE: Gibt die Liste aller vorkommenden Sorten aus.
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   
   void emit_list_of_sorts_array( )
{
   int i;
   
   fprintf( outf, "char * list_of_sorts[] = {\n" );
   
   for( i = 0; i < new_sort_idx; i++ )
   {
     /*      struct SORT * p;*/
      
      fprintf( outf, "\t \"%s\",\n", sorts[ i ].name );
      
   }
   
   fprintf( outf, "\t NULL\n\t };\n" );
}
/*****************************************************************************
 * NAME:  
 * PROCEDURE: 
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   
   void emit_list_of_attrs_array( )
{
   int i;
   
   fprintf( outf, "char * list_of_attrs[] = {\n" );
   
   for( i = 0; i < new_attr_name_idx; i++ )
   {
      fprintf( outf, "\t \"%s\",\n", attribute_names[ i ] );
      
   }
   
   fprintf( outf, "\t \"<SEMVAL>\",\n" );
   
   fprintf( outf, "\t NULL\n\t };\n" );
}



/*****************************************************************************
 * NAME:  emit_term_parse_table
 * PROCEDURE: Gibt die Parsertabelle aus, die zum Erstellen der Darstellung von
 *    Termattributen n"otig ist.
 * INPUT:
 * OUTPUT:
 *****************************************************************************/
   
   
void emit_term_parse_table( )
{
   extern struct PROD prods[];
   extern int new_prod_idx;
   
   int i;
   
   fprintf( outf, "struct TPT {\n \tlong prod_type; long left; long right[ 100 ]; long right_count;};\n" );
   fprintf( outf, "MAX_NODE * parse_max_term( long, long );\n" );
   fprintf( outf, "int tpt_size = %d;\n", new_prod_idx  );
   fprintf( outf, "struct TPT tpt[] = {\n" );
   for( i = 0; i < new_prod_idx; i++ )
   {
      int right_count = 0;
      char * p;
      char * p_type;
      
      switch( prods[ i ].prod_type )
      {
      case 0: p_type = "PROD_CLASS";
	 break;
      case 1: p_type = "PROD_TUPLE";
	 break; 
      case 2: p_type = "PROD_LIST";
	 break;
      default:
	 exit( 1 );
      }
      
      fprintf( outf, "\t { %s, _%s, {", p_type, prods[ i ].left );
      
      for( p = prods[ i ].production; * p; p += ( strlen( p ) + 1 ) )
      {
	 
	 
	 if( '@' == p[ strlen( p ) -1 ] )
	 {
	    char h;
	    
	    h = p[ strlen( p ) -1 ];
	    p[ strlen( p ) -1 ] = 0;
	    
	    fprintf( outf, "_%s_", p );
	    
	    p[ strlen( p )  ] = h;
	 }
	 else
	    fprintf( outf, "_%s", p );
	 /*if( *( p + ( strlen( p ) + 1 ) ) )*/
	    fprintf( outf, "," );
	 
	 right_count++;
      }
      
      fprintf( outf, " 0 }, %d}", right_count );
      if( i < new_prod_idx - 1 )
	 fprintf( outf, "," );
      fprintf( outf, "\n" );
   }
   
   fprintf( outf, "};\n" );
}

/*****************************************************************************
 * NAME:  emit_standard_code
 * PROCEDURE: Kopiert den Code aus {\tt bim_std.c} her"uber
 * INPUT:			
 * OUTPUT:
 *****************************************************************************/
   
void   emit_standard_code( )
{
  /*   char buffer[ 256 ];*/
   /*   FILE * stdfile;*/
   
#if 0
   if( stdfile = fopen( "bim_std.c", "r" ) )
   {
      while( !feof( stdfile ) )
      {
	 if( fgets(  buffer, sizeof( buffer ), stdfile ) )
	 {
	 
	    fputs( buffer, outf );
	 }
      }
      fclose( stdfile );
   }
#else
   fprintf( outf, "#include <bim_std.c>\n" );
#endif   
}


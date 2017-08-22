#include <stdio.h>
#include <string.h>
#include "max_spec.h"

static FILE *out;

/*************************************************************
*
* NAME: prt_sorts
* PROCEDURE: Ausgabe aller Sorten
* INPUT:
* OUTPUT:
*************************************************************/

void  prt_sorts(){
	ELEMENT  prodn;
	long     prodx;
	char    *prodname;
	int      bound;

	/**
	  * Alle Produktionen abklappern
	  */

	bound =  number(_Production_);
	for( prodx = 1; prodx <= bound ; prodx++ ){

	   /**
	     * Sortenname ermitteln
	     */

		prodn    =  element(prodx,_Production_);
		prodname = 	etoa(idtos( term( son(1,son(1,prodn)) ) ));
		fprintf(out,"%s", prodname );

		/** Wenn Class - Production, dann, 2. son(1,prodn) ist SortIdList
		  dann fuer alle aus SortIdList Den 1. Sohn ausgeben **/

		/**
		  * F"ur Klassenproduktion auch die Unterklassen ausgeben
		  */

		if( sort( prodn ) == _ClassProd_ )
		{
		   long bound2;
		   long prodx2;

		   bound2 = numsons( son( 2, prodn ) );

		   for( prodx2 = 1; prodx2 <= bound2 ; prodx2++ )
		   {
		      ELEMENT subsort;
		      char *ssn;

		      subsort = son( prodx2, son( 2, prodn ) );
		      ssn = etoa( idtos( term( son( 1, subsort ) ) ) );
		      fprintf( out, " %s", ssn );
		   }
		}

		fprintf(out,"\n" );

	}
/*
	fprintf(out,"\n");
*/
}

/*************************************************************
*
* NAME: prt_lists
* PROCEDURE: Ausgabe aller Listen, die in der abstrakten 
*            Syntax definiert sind.
* INPUT:
* OUTPUT:
*************************************************************/


void  prt_lists(){
	ELEMENT  prodn;
	long     prodx;
	char    *prodname;
	int      bound;

	bound =  number(_Production_);
	for( prodx = 1; prodx <= bound ; prodx++ ){
		prodn    =  element(prodx,_Production_);
		if( sort( prodn ) == _ListProd_ )
		{
		   ELEMENT subsort;
		   char *ssn;

		   /**
		     * Listenname ausgeben
		     */

		   prodname = 	etoa(idtos( term( son(1,son(1,prodn)) ) ));
		   fprintf(out,"%s", prodname );

		   /**
		     * Und ausgeben, aus welcher Sorte sich diese Liste 
		     * zusammensetzt
		     */


		   subsort = son( 2, prodn );
		   ssn = etoa( idtos( term( son( 1, subsort ) ) ) );
		   fprintf( out, " %s", ssn );
		   if(  is(son( 2, prodn ),_NodeSortId_)  )	fprintf(out,"@" );
		   fprintf(out,"\n" );
		}

		
	}
/*
	fprintf(out,"\n");
*/
}


/*************************************************************
*
* NAME: prt_tuples
* PROCEDURE: Ausgabe aller Tupel, die in der abstrakten 
*            Syntax definiert sind.
* INPUT:
* OUTPUT:
*************************************************************/


void  prt_tuples(){
	ELEMENT  prodn;
	long     prodx;
	char    *prodname;
	int      bound;

	bound =  number(_Production_);
	for( prodx = 1; prodx <= bound ; prodx++ ){
		prodn    =  element(prodx,_Production_);
		if( sort( prodn ) == _TupelProd_ )
		{
		   long bound2;
		   long prodx2;
		   

		   /** 
		     * Tupelname ausgeben
		     */

		   prodname = 	etoa(idtos( term( son(1,son(1,prodn)) ) ));
		   fprintf(out,"%s", prodname );

		   /** Wenn Class - Production, dann, 2. son(1,prodn) ist SortIdList
		     dann fuer alle aus SortIdList Den 1. Sohn ausgeben **/

		   bound2 = numsons( son( 2, prodn ) );

		   /**
		     * Die Sorten ausgeben, aus denen sich das Tupel zusammensetzt
		     */

		   for( prodx2 = 1; prodx2 <= bound2 ; prodx2++ )
		   {
		      ELEMENT subsort;
		      char *ssn;

		      subsort = son( prodx2, son( 2, prodn ) );
		      ssn = etoa( idtos( term( son( 1, subsort ) ) ) );
		      fprintf( out, " %s", ssn );
		      if(  is( subsort ,_NodeSortId_)  )	fprintf(out,"@" );
		   }
		   fprintf(out,"\n" );
		}

		
	}
/*
	fprintf(out,"\n");
*/
}



/*************************************************************
*
* NAME: prt_attrsigns
* PROCEDURE: Ausgabe aller Attributsignaturen
* INPUT:
* OUTPUT:
*************************************************************/



#define  IDSTR(idn)  etoa(idtos(term(son(1,idn))))

static int contains_sort_term( ELEMENT defidnodelist ){
    while(    ! eq( defidnodelist, DefIdNodeList() )
	  &&  ! eq( defidnodelist, nil() )           ){
      
      char *prodname = IDSTR(subterm(1,defidnodelist));
      if( ! strcmp("Term", prodname)  ) 	return 1;
      defidnodelist = back( defidnodelist );
    }
    return 0;
  }

void  prt_attrsign( char *prefix, char* attrname, 
		   char* domain, int withatchar, ELEMENT range ){
  if(  withatchar && ! strcmp("Point", domain)  )  return;
  fprintf(out,"%s", IDSTR(range) );
  if(  is(range,_NodeSortId_)  )	fprintf(out,"@" );
  fprintf(out," %s%s( %s%s )\n", prefix, attrname, domain,
	  (withatchar ? "@" : "") );
  /* the domain sort may be Point or Ident */
}

void  prt_attrsigns_aux( char *prefix, char* attrname, ELEMENT domsortidn,
			ELEMENT base_sort_list, ELEMENT range ){

  if(    eq( base_sort_list, AllNodes())
     ||  contains_sort_term(base_sort_list)  ){
    ELEMENT  prodn;
    char* prodname;
    long     prodx;
    int      bound;
    
    bound =  number(_Production_);
    for( prodx = 1; prodx <= bound ; prodx++ ){
      
      /** Sortenname ermitteln  */
      prodn    =  element(prodx,_Production_);
      prodname = etoa(idtos( term( son(1,son(1,prodn)) ) ));

      if(    eq( sort(prodn), _TupelProd_ ) 
	 ||  eq( sort(prodn), _ListProd_ )  ){
	prt_attrsign( prefix, attrname, prodname, 1, range );
      }

      if(    eq( sort(prodn), _PredeclProd_ ) 
	 &&(    strcmp("NodeSort",prodname)==0
	    ||  strcmp("PredeclSort",prodname)==0
	    ||  strcmp("ClassSort",prodname)==0
	    ||  strcmp("TupelSort",prodname)==0
	    ||  strcmp("ListSort",prodname)==0
	    ||  strcmp("Ident",prodname)==0
	    ||  strcmp("Bool",prodname)==0
	    ||  strcmp("Char",prodname)==0
	    ||  strcmp("Int",prodname)==0
	    ||  strcmp("String",prodname)==0
	    ||  strcmp("Reference",prodname)==0  ) ){
	prt_attrsign( prefix, attrname, prodname, 1, range );
      }
    }
  } else if(  is( fath(decl(domsortidn)),_ClassProd_)  ){
    /* variant production possibly containing Term */
    while(    ! eq( base_sort_list, DefIdNodeList() )
	  &&  ! eq( base_sort_list, nil() )           ){
      char *prodname = IDSTR(subterm(1,base_sort_list));
      prt_attrsign( prefix, attrname, prodname, 1, range );
      base_sort_list = back( base_sort_list );
    }
  } else {
    if( is( domsortidn,_NodeSortId_) ){
      prt_attrsign( prefix, attrname, IDSTR(domsortidn),1, range );
    } else {
      prt_attrsign( prefix, attrname, IDSTR(domsortidn),0, range );
    }
  }
}


void  prt_attrsigns( char *prefix ){
	ELEMENT  decln;
	long     declx;
	char 	*attrname;
	char    *prodname;
	ELEMENT  range;
	ELEMENT  sortidn;
	ELEMENT  base_sort_list;
	int      bound;

	bound =  number(_Attribute_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_Attribute_);
		attrname =  IDSTR( son(1,decln) );
		range	 =  son(4,decln);
		sortidn	 =  son(1,son(2,decln));  /* may be a variant sort */
		base_sort_list = node_basesorts( sortidn );

		prt_attrsigns_aux( prefix, attrname, sortidn, 
				  base_sort_list, range );
	      }
	bound =  number(_AttrDecl_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_AttrDecl_);
		attrname =  IDSTR( son(1,decln) );
		range	 =  son(3,decln);
		sortidn	 =  son(1,son(2,decln));  /* may be a variant sort */
		base_sort_list = node_basesorts( sortidn );

		prt_attrsigns_aux( prefix, attrname, sortidn, 
				  base_sort_list, range );
	      }
      }

/*************************************************************
*
* NAME: grphif_gen
* PROCEDURE: Ausgabe des .g-Files
* INPUT:
* OUTPUT:
*************************************************************/



void  grphif_gen( FILE *outp, char *prfx ){

	out = outp;
	fprintf(out,"%%SORTS\n");
	prt_sorts();
	fprintf(out,"%%TUPLES\n");
	prt_tuples();
	fprintf(out,"%%LISTS\n");
	prt_lists();
	fprintf(out,"%%ATTRIBUTES\n");
	prt_attrsigns(prfx);
}

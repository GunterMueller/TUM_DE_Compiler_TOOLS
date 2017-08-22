#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "config_ac.h"
#include "config_sc.h"

#include "max_std.h"

#define NODEINDX   ELEMENT
#define POINTINDX  ELEMENT
#define MAXUSHORT  65535

#define MAXERRMESSAGES  10
static  long errmesscount = 0;
extern FILE *errfile;

void  mxi_prterrm( char *filenm, int ln, char *functnm, char *errm ){
	if( errmesscount <= MAXERRMESSAGES ){
		fprintf(errfile,"\n****  %s,  %d,  call of %s:",filenm,ln,functnm);
		fprintf(errfile,"\n      %s",errm);
		errmesscount++;
	} else {
		fprintf(errfile,"\n\nExited program after %d errors!\n", MAXERRMESSAGES);
		exit( EXIT_FAILURE );
	}
}

long   mxi_conv_error = 0;


ELEMENT  mxk_btoe( long b ){
	if( b ){
		return  class_elemcd(BOOL_CL,1);
	} else {
		return  class_elemcd(BOOL_CL,0);
	}
}

ELEMENT  mxi_btoe( char* f, int l, long b ){
	mxi_conv_error = 0;
	return mxk_btoe(b);
}


long  mxk_etob( ELEMENT elem ){
	return  elemcd(elem) ;
}

long  mxi_etob( char* f, int l, ELEMENT elem ){
	if( class(elem) == BOOL_CL ){
		mxi_conv_error = 0;
		return mxk_etob(elem);
	} else {
		mxi_conv_error = 1;
		mxi_prterrm(f,l,"etob","Converted non-Bool element to boolean");
		return 0 ;
	}
}


ELEMENT  mxk_ctoe( char c ){
	return  class_code(CHAR_CL,c);
}

ELEMENT  mxi_ctoe( char* f, int l, char c ){
	mxi_conv_error = 0;
	return mxk_ctoe(c);
}


char  mxk_etoc( ELEMENT elem ){
	return (char)code(elem) ;
}

char  mxi_etoc( char* f, int l, ELEMENT elem ){
	if( class(elem) == CHAR_CL ){
		mxi_conv_error = 0;
		return mxk_etoc(elem);
	} else {
		mxi_conv_error = 1;
		mxi_prterrm(f,l,"etoc","Converted non-Char element to char");
		return '\0' ;
	}
}


ELEMENT  mxk_itoe( long i ){
	return  i ;
}

ELEMENT  mxi_itoe( char* f, int l, long i ){
	if( i <= MAXIMALINT  &&  i >= MINIMALINT ){
		mxi_conv_error = 0;
		return mxk_itoe(i);
	} else {
		mxi_conv_error = 1;
		mxi_prterrm(f,l,"itoe","Converted int too big/small");
		return 0 ;
	}
}


long  mxk_etoi( ELEMENT elem ){
	return elem ;
}

long   mxi_etoi( char* f, int l, ELEMENT elem ){
	unsigned char c = class(elem);
	if( c == POS_CL  ||  c == NEG_CL ){
		mxi_conv_error = 0;
		return mxk_etoi(elem);
	} else {
		mxi_conv_error = 1;
		mxi_prterrm(f,l,"etoi","Converted non-Int element to int");
		return (char)0 ;
	}
}


ELEMENT  mxk_ptoe( void *p ){
	return  CODEPTR( (long)p );
}

ELEMENT  mxi_ptoe( char* f, int l, void *p ){
	if(  CODABLEPTR( (long)p )  ){
		mxi_conv_error = 0;
		return mxk_ptoe(p);
	} else {
		mxi_conv_error = 1;
printf("\n %X\n", (long)p );
		mxi_prterrm(f,l,"ptoe","Converted pointer out of range");
		return mxk_ptoe(NULL) ;
	}
}


void*  mxk_etop( ELEMENT elem ){
	return (void*) DECODEREF(elem) ;
}

void*  mxi_etop( char* f, int l, ELEMENT elem ){
	if(  ISREF(elem)  ){
		mxi_conv_error = 0;
		return mxk_etop(elem);
	} else {
		mxi_conv_error = 1;
		mxi_prterrm(f,l,"etop","Converted non-Ref element to NULL");
		return NULL ;
	}
}



#define HASHTABSIZE   32233 /*=-= is prim  =-=*/
#define MAXHASHTABNUM 100

typedef 
	struct {
		char           *string;
		unsigned short  strlength;
	}  hashentry;

static hashentry  inithashtab [HASHTABSIZE];
static hashentry  *hashtabs  [MAXHASHTABNUM] = { inithashtab };
static unsigned  char  curr_htab_num = 0;


static int  hashfunct ( char *s ){
   int  sum = 0 ;
   while (  *s != '\0'  ) {
      sum +=  *s++ ;
   }
   return( sum % HASHTABSIZE ) ;
} 


/*=-= enter yields the hashcode or -1  =-=*/
static int  enter ( char *s, int slen, hashentry *hashtable ){      
	int  hnumb    =  hashfunct(s) ;
	int  tabindex =  hnumb ;
	int  coll     =  1 ;

	if( slen > MAXUSHORT ){
		mxi_prterrm("max_std.c",0,"enter","Maximum string length is MAXUSHORT");
		exit( EXIT_FAILURE );
	}
	do {
		if( hashtable[tabindex].string == 0L ){
			char *sv = (char*) malloc( slen+1 );
			if( sv == 0L ){
				mxi_prterrm("max_std.c",0,"enter","Cannot allocate space for string");
				exit( EXIT_FAILURE );
			}
			strcpy(sv,s);
			hashtable[tabindex].string = sv ;
			hashtable[tabindex].strlength = slen;
			return( tabindex ) ;
		}
		if(     slen == hashtable[tabindex].strlength
			&&  strcmp(hashtable[tabindex].string,s) == 0  )
			return( tabindex ) ;
		tabindex =  (tabindex + coll) % HASHTABSIZE ;
		coll += 2 ;
	}
	while ( tabindex != hnumb ) ;
	return( -1 ) ;
}       


ELEMENT  mxk_atoe( char* a ){
	int hashcd = -1;
	unsigned char   i = 0;
	unsigned short  slen =  (unsigned short) strlen(a);

	while( i <= curr_htab_num  &&  hashcd < 0 ){
		hashcd = enter( a, slen, hashtabs[i++] );
	}
	if( hashcd < 0 ){
		if( ++curr_htab_num == MAXHASHTABNUM ){
			mxi_prterrm("max_std.c",0,"atoe","No more hashtables available");
			exit( EXIT_FAILURE );
		}
		hashtabs[curr_htab_num] = 
				(hashentry *) calloc( HASHTABSIZE, sizeof(hashentry) );
		if( hashtabs[curr_htab_num] == 0L ){
			mxi_prterrm("max_std.c",0,"atoe","Cannot allocate a new hashtab");
			exit( EXIT_FAILURE );
		}
		hashcd = enter( a, slen, hashtabs[curr_htab_num] );
		return  class_tabno_code(STRING_CL,curr_htab_num,hashcd) ;
	} else {
		return  class_tabno_code(STRING_CL,i-1,hashcd) ;
	}
}

ELEMENT  mxi_atoe( char* f, int l, char* a ){
	mxi_conv_error = 0;
	return mxk_atoe(a);
}

char* mxk_etoa( ELEMENT elem ){
	return  hashtabs[ tabno(elem) ][ code(elem) ].string ;
}

char* mxi_etoa( char* f, int l, ELEMENT elem ){
	if(     class(elem) == STRING_CL 
		&&  tabno(elem) <= curr_htab_num
		&&  code(elem)  <  HASHTABSIZE   ){
			mxi_conv_error = 0;
			return  mxk_etoa(elem) ;
	} else {
		mxi_conv_error = 1;
		mxi_prterrm(f,l,"etoa","Converted non-String element to (char*)");
		return "" ;
	}
}


ELEMENT  mxk_strlength( ELEMENT elem ){
	return  (ELEMENT) hashtabs[ tabno(elem) ][ code(elem) ].strlength ;
}

ELEMENT  mxi_strlength( char* f, int l, ELEMENT elem ){
	if(     class(elem) == STRING_CL 
		&&  tabno(elem) <= curr_htab_num
		&&  code(elem)  <  HASHTABSIZE   ){
			mxi_conv_error = 0;
			return  mxk_strlength(elem) ;
	} else {
		mxi_conv_error = 1;
		mxi_prterrm(f,l,"strlength","Element not a String");
		return mxk_itoe(0) ;
	}
}

#define IDENTTABSIZE  65000
static ELEMENT idtostab[ IDENTTABSIZE ];
static unsigned short  curr_idtab_pos = 1;

ELEMENT  mxk_stoid( ELEMENT elem ){
	unsigned short  i;

	IFNIL(elem)
	for( i=0 ; i<curr_idtab_pos && idtostab[i]!=elem ; i++ );
	if( i == curr_idtab_pos ){
		if( curr_idtab_pos < (unsigned short)IDENTTABSIZE ){
			idtostab[ curr_idtab_pos++ ]  =  elem;
			mxi_numbertab[ IDENT_SORTCD ]++;
		} else {
			mxi_prterrm("max_std.c",0,"stoid","Ident table is full");
			exit( EXIT_FAILURE );
		}
	}
	return class_elemcd(IDENT_CL,i);
}

ELEMENT  mxi_stoid( char *f, int l, ELEMENT elem ){
	if( class(elem) != STRING_CL ){
		mxi_prterrm(f,l,"stoid","Argument is not a string");
		return  NIL;
	} else {
		return mxk_stoid(elem);
	}
}


ELEMENT  mxk_idtos( ELEMENT elem ){
	IFNIL(elem)
	return  idtostab[ elemcd(elem) ];
}

ELEMENT  mxi_idtos( char *f, int l, ELEMENT elem ){
	if(      class(elem) == (unsigned char)IDENT_CL 
		 &&  elemcd(elem) < (long)curr_idtab_pos ){
		return  mxk_idtos(elem);
	} else {
		mxi_prterrm(f,l,"idtos","Argument is not an ident");
		return  NIL;
	}
}


#define TERMTABSIZE   32500L
#define MAXTERMTABNUM 255    /*=-= maximal 256 =-=*/
static unsigned short  curr_ttab_num = 0;
static unsigned short  curr_ttab_pos = 1;

static ELEMENT   inittermtab [TERMTABSIZE];
static ELEMENT  *termtabs  [MAXTERMTABNUM] = { inittermtab };

static  NODEINDX   *pton;
static  POINTINDX  *ntoaft;
static  POINTINDX  *ntobef;
static  ELEMENT    *ntot;


static  void  alloc_term( unsigned short  size ){
	if( (long)(curr_ttab_pos + size) >= TERMTABSIZE ){
		if( ++curr_ttab_num == MAXTERMTABNUM ){
			mxi_prterrm("max_std.c",0,"alloc_term", 
					"No more termtables available");
			exit( EXIT_FAILURE );
		}
		termtabs[curr_ttab_num] = 
			(ELEMENT *) calloc( TERMTABSIZE, sizeof(ELEMENT) );
		if( termtabs[curr_ttab_num] == 0L ){
			mxi_prterrm("max_std.c",0,"alloc_term",
					"Cannot allocate newtermtab");
			exit( EXIT_FAILURE );
		}
		curr_ttab_pos = 0;
	}
}


/*=-= sort is defined for all elements yielding a sort code element =-=*/
static  short  sortcdof( ELEMENT elem ){
	switch( class(elem) ){
	case POS_CL			:	return  (short)INT_SORTCD;
	case NATERM_CL		:	{
			unsigned char tab = tabno(elem);   
			short         cd  = code(elem);   
			if( tab > curr_ttab_num  ||  cd < 0  ){
				return  0;
			} else {
				return  sortcd(termtabs[tab][cd]) ;
			}
		}
	case POINT_CL      :	return  POINT_SORTCD;
	case NODE_CL       :	return  - sortcdof( ntot[elemcd(elem)] ) ;
	case DEFCONST_CL   :	return  code(elem);
	case SORTCONST_CL  :	{
			short         cd  = code(elem);   
			if(      cd < mxi_list_sortcd_lb )	return  CLASSSORT_SORTCD;
			else if( cd < mxi_tupel_sortcd_lb )	return  LISTSORT_SORTCD;
			else if( cd < MIN_PREDECL_SORTCD )	return  TUPELSORT_SORTCD;
			else if( cd <= MAX_PREDECL_SORTCD )	return  PREDECLSORT_SORTCD;
			else								return  NODESORT_SORTCD;
		}
	case IDENT_CL      :	return  IDENT_SORTCD;
	case BOOL_CL       :	return  BOOL_SORTCD;
	case CHAR_CL       :	return  CHAR_SORTCD;
	case STRING_CL     :	return  STRING_SORTCD;
	case NEG_CL        :	return  INT_SORTCD;
	default /*REF_CL*/ :
		if(  ISREF(elem)  ){
			return REFERENCE_SORTCD;
		} else {
			return  0;
		}
	}
}


ELEMENT  mxk_sort( ELEMENT elem ){
	short  cd  = sortcdof(elem);
	if( cd == NIL_SORTCD )  return NIL;
	else					return class_code( SORTCONST_CL, cd );
}

ELEMENT  mxi_sort( char *f, int l, ELEMENT elem ){
	short  cd  = sortcdof(elem);
	if( cd == NIL_SORTCD )  return NIL;
	if( cd == 0 ){
		mxi_prterrm(f,l,"sort","applied to non-element");
		return  NIL;
	} else {
		return class_code( SORTCONST_CL, cd );
	}
}


static  int  issubsortk( SORTCDT sortcdp, SORTCDT classcd ){
/* the first argument must be a base sort code; see issubsort below */
	if( sortcdp == classcd ){
		return 1;
	} else {
		int   i = 0 ;
		SORTCDT *supersorts = mxi_supsorttab[sortcdp];
		while( supersorts[i] != classcd && supersorts[i] != 0 )  i++; 
		return ( supersorts[i] == classcd );
	}
}

static  int  issubsort( SORTCDT sortcdp, SORTCDT classcd ){
	short  scd, ccd;
	if( sortcdp > 0 ) scd = -sortcdp;	else 	scd =  sortcdp;
	if( classcd > 0 ) ccd = -classcd;	else	ccd =  classcd;
	if(		(	( scd <= NODESORT_SORTCD && scd >= mxi_class_sortcd_lb )	
			||	sortcdp == POINT_SORTCD		)
		&&  ccd >= mxi_class_sortcd_lb  &&  ccd != 0  &&  ccd != NIL_SORTCD ){
		return  issubsortk(sortcdp,classcd);
	} else {
		mxi_prterrm("max_std.c",0,"issubsort","wrong call of issubsort");
		return  0;
	}
}


ELEMENT  mxk_number( ELEMENT sort ){
	IFNIL(sort)
	return mxi_numbertab[ code(sort) ];
}

ELEMENT  mxi_number( char *f, int l, ELEMENT sort ){
	short  scd =  code(sort);

	if( sort==NIL ) return NIL;
	if( class(sort) != SORTCONST_CL ){
		mxi_prterrm(f,l,"number","sort argument badly formed");
		return  NIL;
	} else if( ! INDEXABLE( scd )  ){
		mxi_prterrm(f,l,"number","applied to non-indexable sort");
		return  NIL;
	} else {
		return  mxk_number(sort);
	}
}


ELEMENT  mxk_index( ELEMENT elem, ELEMENT sort ){
	short  ccd =  code(sort);

	IFNIL(elem)  IFNIL(sort)
	switch( ccd ){
	case IDENT_SORTCD :
	case POINT_SORTCD :
	case NODE_SORTCD  :		return  elemcd(elem);
	default :	{
			if( -ccd >= mxi_list_sortcd_lb )
				return  elemcd(elem) - mxi_offsettab[ccd];
			else {
				int   i = -1 ;
				short  scd =  sortcdof(elem) ;
				ScdOffsPair  *cop =  mxi_coffsettab[scd];
				while( cop[++i].ccd != ccd ); 
				return  elemcd(elem) - mxi_offsettab[scd] + cop[i].offs ;
			}
		}
	}
}

ELEMENT  mxi_index( char *f, int l, ELEMENT elem, ELEMENT sort ){
	short  scd =  code(sort);
	if(     class(sort) == SORTCONST_CL  &&  INDEXABLE( scd ) 
		&&  issubsortk( sortcdof(elem), scd)				){
		return  mxk_index(elem,sort);
	} else if( elem==NIL  ||  sort==NIL  ){
		;
	} else if( class(sort) != SORTCONST_CL ){
		mxi_prterrm(f,l,"index","sort argument badly formed");
	} else if( ! INDEXABLE( scd )  ){
		mxi_prterrm(f,l,"index","applied to non-indexable sort");
	} else if( ! issubsortk( sortcdof(elem), scd) ){
		mxi_prterrm(f,l,"index","element not a member of given sort");
	} else {
		mxi_prterrm(f,l,"index","unclassified error");
	}
	return  NIL;
}


ELEMENT  mxk_element( ELEMENT indx, ELEMENT sort ){
	short  ccd =  code(sort);

	IFNIL(indx)  IFNIL(sort)
	switch( ccd ){
	case IDENT_SORTCD :		return  class_elemcd(IDENT_CL,indx);
	case POINT_SORTCD :		return  class_elemcd(POINT_CL,indx);
	case NODE_SORTCD  :		return  class_elemcd(NODE_CL,indx);
	default :
		if( -ccd >= mxi_list_sortcd_lb )
			return  class_elemcd( NODE_CL, indx+mxi_offsettab[ccd] );
		else {
			int   i = 0 ;
			ScdOffsPair  *cop =  mxi_coffsettab[ccd];
			while( indx > cop[++i].offs ); 
			return class_elemcd(NODE_CL,
						indx-cop[i-1].offs+mxi_offsettab[cop[i-1].ccd]);
		}
	}
}

ELEMENT  mxi_element( char *f, int l, ELEMENT indx, ELEMENT sort ){
	short  scd =  code(sort);
	if(     class(sort) == SORTCONST_CL  &&  INDEXABLE( scd ) 
		&&  sortcdof(indx) == INT_SORTCD &&  indx <= mxk_number(sort) ){
		return  mxk_element(indx,sort);
	} else if( indx==NIL  ||  sort==NIL  ){
		;
	} else if( class(sort) != SORTCONST_CL ){
		mxi_prterrm(f,l,"element","sort argument badly formed");
	} else if( ! INDEXABLE( scd )  ){
		mxi_prterrm(f,l,"element","applied to non-indexable sort");
	} else if( sortcdof(indx) != INT_SORTCD ){
		mxi_prterrm(f,l,"element","first argument not an Int");
	} else if( indx > mxk_number(sort) ){
		mxi_prterrm(f,l,"element","index not defined for given sort");
	} else {
		mxi_prterrm(f,l,"index","unclassified error");
	}
	return  NIL;
}



ELEMENT  mxk_numsubterms( ELEMENT elem ){
	IFNIL(elem)
	if( class(elem) == NATERM_CL ){
		int  leng = length( termtabs[tabno(elem)][code(elem)] );
		if( leng >= 0 )		return leng;	else	return -leng;
	} else {
		return  0;
	}
}

ELEMENT  mxi_numsubterms( char *f, int l, ELEMENT elem ){
	if( elem == NIL )	return  NIL;
	else				return  mxk_numsubterms(elem);
}


ELEMENT  mxk_subterm( ELEMENT i, ELEMENT elem ){
	SELEMENT selem;
	SELEMENT fstcomp;
	long     leng, absleng;

	IFNIL(i)	IFNIL(elem)
	selem.f = elem;
	fstcomp.f =  termtabs[stabno(selem)][scode(selem)];
	leng      =  slength( fstcomp );
	absleng   =  (leng>0) ? leng : -leng ;
	if( i < 0 )  i = absleng + i + 1 ;
	if( ssortcd(fstcomp) >= mxi_tupel_sortcd_lb ){
		return termtabs[ stabno(selem) ][ scode(selem)+i ];
	} else if( leng > 0 ){
		for( i = absleng-i; i>0; i-- ){
			selem.f = termtabs[ stabno(selem) ][ scode(selem)+2 ];
		}
		return termtabs[ stabno(selem) ][ scode(selem)+1 ];
	} else {  /*=-=  leng < 0  =-=*/
		for( ; i>1; i-- ){
			selem.f = termtabs[ stabno(selem) ][ scode(selem)+2 ];
		}
		return  termtabs[ stabno(selem) ][ scode(selem)+1 ];
	}
}


ELEMENT  mxi_subterm( char *f, int l, ELEMENT i, ELEMENT elem ){
	long absi =	 ( i > 0 ) ?  i : -i;

	if( sortcdof(i)==INT_SORTCD  &&  elem != NIL ){
		if( absi <= mxk_numsubterms( elem )  &&  i != 0 ){
			return  mxk_subterm(i,elem);
		} else {
			mxi_prterrm(f,l,"subterm","given element hasn't an ith subterm");
			return  NIL ;
		}
	} else if ( i == NIL  ||  elem == NIL ){
		return  NIL;
	} else {
		mxi_prterrm(f,l,"subterm","first argument must be Int");
		return  NIL ;
	}
}



/*  the following macro enters the given three list components in a new  */
/*  allocated element and sets the result variable to that element       */
#define  alloc_listelem(lleng,lsort,comp,rest,resvar)	{				\
	ELEMENT *currpos;													\
	alloc_term(2);														\
	currpos    =  termtabs[curr_ttab_num] + curr_ttab_pos ;				\
	currpos[0] =  length_sortcd(lleng,lsort);							\
	currpos[1] =  comp;													\
	currpos[2] =  rest;													\
	resvar =  class_tabno_code(NATERM_CL,curr_ttab_num,curr_ttab_pos);	\
	curr_ttab_pos  = curr_ttab_pos + 3 ;								\
}




static  ELEMENT  rv_copy( ELEMENT elem ){
/*=-=  elem, a list term of length >=1, is copied with change  =-=*/
/*=-=  of representation                                      =-=*/ 
	SORTCDT	  sortv   =  sortcdof(elem);
	ELEMENT   newl    =  class_code( DEFCONST_CL, sortv); 
	ELEMENT  *poldl	  =  termtabs[tabno(elem)] + code(elem); 
	long	  i, leng =  length(poldl[0]);

	if( leng > 0 ){
		for( i= -1 ; i > -leng ; i-- ){
			alloc_listelem( i, sortv, poldl[1], newl, newl );
			poldl =  termtabs[tabno(poldl[2])] + code(poldl[2]);
		}
	} else {
		for( i=1 ; i< -leng ; i++ ){
			alloc_listelem( i, sortv, poldl[1], newl, newl );
			poldl =  termtabs[tabno(poldl[2])] + code(poldl[2]);
		}
	}
	alloc_listelem( i, sortv, poldl[1], newl, newl );
	return newl;
}


#define CHECK_LISTNIL(svar,elem,qfctnm) {							\
	svar = sortcdof(elem);											\
	if( elem == NIL )	return  NIL ;								\
	if( svar >= mxi_tupel_sortcd_lb || svar < mxi_list_sortcd_lb ){	\
		mxi_prterrm(f,l,qfctnm,"list argument isn't a list");		\
		return  NIL ;												\
	}																\
}


ELEMENT  mxk_front( ELEMENT elem ){
	ELEMENT   elemv;
	ELEMENT  *poldl;

	IFNIL(elem)
	poldl =  termtabs[tabno(elem)] + code(elem); 
	if( length(poldl[0]) < 0 ){
		elemv =  rv_copy(elem);
		poldl =  termtabs[tabno(elemv)] + code(elemv); 
	}
	return  poldl[2];
}

ELEMENT  mxi_front( char *f, int l, ELEMENT elem ){
	SORTCDT  scdv;

	CHECK_LISTNIL(scdv,elem,"front")
	if( mxk_numsubterms(elem) == 0 ){
		mxi_prterrm(f,l,"front","list argument is empty");
		return NIL;
	} else {
		return  mxk_front(elem);
	}
}


ELEMENT  mxk_back( ELEMENT elem ){
	ELEMENT   elemv;
	ELEMENT  *poldl;

	IFNIL(elem)
	poldl =  termtabs[tabno(elem)] + code(elem); 
	if( length(poldl[0]) > 0 ){
		elemv =  rv_copy(elem);
		poldl =  termtabs[tabno(elemv)] + code(elemv); 
	}
	return  poldl[2];
}

ELEMENT  mxi_back( char *f, int l, ELEMENT elem ){
	SORTCDT  scdv;

	CHECK_LISTNIL(scdv,elem,"back")
	if( mxk_numsubterms(elem) == 0 ){
		mxi_prterrm(f,l,"back","list argument is empty");
		return NIL;
	} else {
		return  mxk_back(elem);
	}
}


#define  listleng(list)  ( (class(list)==DEFCONST_CL) ? 0 :	\
				length(termtabs[tabno(list)][code(list)]) )


ELEMENT  mxk_appfront( ELEMENT el, ELEMENT list ){
	ELEMENT   listv;
	SORTCDT   sortv = sortcdof(list);
	long      leng ;

	IFNIL(el)	IFNIL(list)
	leng =  listleng(list);
	if( leng > 0 ){
		listv =  rv_copy(list);
		leng  = -leng;
	} else {
		listv = list;
	}
	alloc_listelem((leng-1),sortv,el,listv,listv)
	return listv;
}

ELEMENT  mxi_appfront( char *f, int l, ELEMENT el, ELEMENT list ){
	SORTCDT  scdv;

	CHECK_LISTNIL(scdv,list,"appfront")
	if(  issubsortk( sortcdof(el), mxi_listtoelemtab[scdv] )  ){
		return  mxk_appfront(el,list);
	} else {
		mxi_prterrm(f,l,"appfront","incompatible sorts");
		return NIL;
	}
}


ELEMENT  mxk_appback( ELEMENT list, ELEMENT el ){
	ELEMENT   listv;
	SORTCDT   sortv = sortcdof(list);
	long      leng ;

	IFNIL(el)	IFNIL(list)
	leng =  listleng(list);
	if( leng < 0 ){
		listv =  rv_copy(list);
		leng  = -leng;
	} else {
		listv = list;
	}
	alloc_listelem((leng+1),sortv,el,listv,listv)
	return listv;
}

ELEMENT  mxi_appback( char *f, int l, ELEMENT list, ELEMENT el ){
	SORTCDT  scdv;

	CHECK_LISTNIL(scdv,list,"appback")
	if(  issubsortk( sortcdof(el), mxi_listtoelemtab[scdv] )  ){
		return  mxk_appback(list,el);
	} else {
		mxi_prterrm(f,l,"appback","incompatible sorts");
		return NIL;
	}
}



static ELEMENT  conc_ll( ELEMENT list1, ELEMENT list2, long leng2 ){
	if( leng2 == 1 ){
		return mxk_appback( list1, mxk_subterm(-1,list2) ) ;
	} else {
		return mxk_appback( conc_ll( list1, mxk_front(list2), leng2-1 ),
													mxk_subterm(-1,list2) );
	}
}

static ELEMENT  conc_rr( ELEMENT list1, long leng1, ELEMENT list2 ){
	if( leng1 == 1 ){
		return mxk_appfront( mxk_subterm(1,list1), list2 ) ;
	} else {
		return mxk_appfront(  mxk_subterm(1,list1),
							  conc_rr( mxk_back(list1), leng1-1, list2 )  );
	}
}

static ELEMENT  conc_lrb( ELEMENT list1, long leng1, ELEMENT list2 ){
	if( leng1 == 1 ){
		return mxk_appfront( mxk_subterm(-1,list1), list2 ) ;
	} else {
		return conc_lrb( mxk_front(list1), leng1-1 ,
						 mxk_appfront( mxk_subterm(-1,list1), list2 )  );
	}
}


static ELEMENT  conc_lrf( ELEMENT list1, ELEMENT list2, long leng2 ){
	if( leng2 == 1 ){
		return mxk_appback( list1, mxk_subterm(1,list2) ) ;
	} else {
		return conc_lrf( mxk_appback( list1, mxk_subterm(1,list2) ),
						 mxk_back(list2),    leng2-1 				) ;
	}
}


ELEMENT  mxk_conc( ELEMENT l1, ELEMENT l2 ){
	long    leng1, leng2;
	ELEMENT list1, list2;

	IFNIL(l1)	IFNIL(l2)
	leng1 = listleng(l1);
	leng2 = listleng(l2);
	if( leng1 == 0 )  return  l2;
	if( leng2 == 0 )  return  l1;
	list1 = l1;
	list2 = l2;
	if( leng1 < 0  &&  leng2 > 0  ){
		if( -leng1 < leng2 ){
			list1 = rv_copy(list1);
			leng1 = -leng1;
		} else {
			list2 = rv_copy(list2);
			leng2 = -leng2;
		}
	}
	if( leng1 > 0  &&  leng2 > 0  ){
		return conc_ll( list1, list2, leng2 );
	} else if( leng1 < 0  &&  leng2 < 0  ){
		return conc_rr( list1, -leng1, list2 );
	} else { /*=-=  leng1 > 0  &&  leng2 < 0  =-=*/
		if( leng1 < -leng2 ){
			return conc_lrb( list1, leng1, list2 );
		} else {
			return conc_lrf( list1, list2, -leng2 );
		}
	}
}

ELEMENT  mxi_conc( char *f, int l, ELEMENT l1, ELEMENT l2 ){
	SORTCDT  scdv1,scdv2;

	CHECK_LISTNIL(scdv1,l1,"conc")
	CHECK_LISTNIL(scdv2,l2,"conc")
	if(  scdv1 == scdv2  ){
		return  mxk_conc(l1,l2);
	} else {
		mxi_prterrm(f,l,"conc","lists of different sort");
		return NIL;
	}
}

ELEMENT mxk_tc( char *consname, int sonc, int ressort, ... ){
	SORTCDT  sonccdv;
	ELEMENT  sonv;
	ELEMENT *currpos;
	int      i;
	va_list  ap;

	alloc_term(sonc);
	currpos    =  termtabs[curr_ttab_num] + curr_ttab_pos ;
	currpos[0] =  length_sortcd( (short) sonc, (SORTCDT) ressort);
	va_start( ap, ressort );

	for( i = 1; i <= sonc; i++ ){
		sonccdv = (SORTCDT) va_arg( ap, int );
		sonv    = va_arg( ap, ELEMENT );
		IFNIL(sonv)
		currpos[ i ] = sonv;
	}
	va_end( ap );
	sonv =  class_tabno_code(NATERM_CL,curr_ttab_num,curr_ttab_pos); 
	curr_ttab_pos = curr_ttab_pos + sonc + 1 ;
	return sonv;
}

ELEMENT mxi_tc( char *f, int l, char *consname, int sonc, int ressort, ... ){
	SORTCDT  sonccdv;
	ELEMENT  sonv;
	ELEMENT *currpos;
	long     errflag = 0;
	int      i;
	va_list  ap;

	alloc_term(sonc);
	currpos    =  termtabs[curr_ttab_num] + curr_ttab_pos ;
	currpos[0] =  length_sortcd( (short) sonc, (SORTCDT) ressort);
	va_start( ap, ressort );

	for( i = 1; i <= sonc; i++ ){
		sonccdv = (SORTCDT) va_arg( ap, int );
		sonv    = va_arg( ap, ELEMENT );
		if( sonv == NIL )  return  NIL;
		if( ! issubsortk(sortcdof(sonv),sonccdv)  )  errflag = 1;
		currpos[ i ] = sonv;
	}
	va_end( ap );

	if( errflag ){
		mxi_prterrm(f,l,consname,"at least one argument of wrong sort");
		return  NIL;
	} else {
		sonv =  class_tabno_code(NATERM_CL,curr_ttab_num,curr_ttab_pos); 
		curr_ttab_pos = curr_ttab_pos + sonc + 1 ;
		return sonv;
	}
}



#define CHECK_NODENIL(pfctnm,qfctnm) {								\
	if( class(elem) == NODE_CL ){									\
		return  pfctnm(elem);										\
	} else if( elem == NIL ){										\
		return  NIL ;												\
	} else {														\
		mxi_prterrm(f,l,qfctnm,"only defined for nodes and nil");	\
		return  NIL ;												\
	}																\
}


ELEMENT  mxk_fath( ELEMENT elem ){
	IFNIL(elem)
	if( elem == ROOT ){
		return NIL;
	} else {
		POINTINDX  pointv = ntoaft[elemcd(elem)] + 1 ;
		NODEINDX   nodev  = pton[pointv];
		while( pointv == ntobef[ nodev ] ){
			pointv = ntoaft[nodev] + 1 ;
			nodev  = pton[pointv];
		}
		return class_elemcd(NODE_CL,nodev);
	}
}

ELEMENT  mxi_fath( char *f, int l, ELEMENT elem ){
	CHECK_NODENIL(mxk_fath,"fath")
}

ELEMENT  mxk_lbroth( ELEMENT elem ){
	IFNIL(elem)
	if( elem == ROOT ){
		return NIL;
	} else {
		POINTINDX  pointv = ntobef[elemcd(elem)] - 1 ;
		NODEINDX   nodev  = pton[pointv];
		if( pointv == ntoaft[ nodev ] )  return  class_elemcd(NODE_CL,nodev);
		else							 return  NIL ;
	}
}

ELEMENT  mxi_lbroth( char *f, int l, ELEMENT elem ){
	CHECK_NODENIL(mxk_lbroth,"lbroth")
}


ELEMENT  mxk_rbroth( ELEMENT elem ){
	IFNIL(elem)
	if( elem == ROOT ){
		return NIL;
	} else {
		POINTINDX  pointv = ntoaft[elemcd(elem)] + 1 ;
		NODEINDX   nodev  = pton[pointv];
		if( pointv == ntobef[ nodev ] )  return  class_elemcd(NODE_CL,nodev);
		else							 return  NIL ;
	}
}

ELEMENT  mxi_rbroth( char *f, int l, ELEMENT elem ){
	CHECK_NODENIL(mxk_rbroth,"rbroth")
}


ELEMENT  mxk_term( ELEMENT elem ){
	IFNIL(elem)
	return  ntot[ elemcd(elem) ] ;
}

ELEMENT  mxi_term( char *f, int l, ELEMENT elem ){
	CHECK_NODENIL(mxk_term,"term")
}


ELEMENT   mxk_numsons( ELEMENT elem ){
	IFNIL(elem)
	return  mxk_numsubterms(mxk_term(elem));
}

ELEMENT  mxi_numsons( char *f, int l, ELEMENT elem ){
	CHECK_NODENIL(mxk_numsons,"numsons")
}


ELEMENT  mxk_son( ELEMENT i, ELEMENT elem ){
	ELEMENT leng =  mxk_numsons(elem);

	IFNIL(i)  IFNIL(elem)
	if( i > 0  && i <= leng ){
		NODEINDX   nodev  = pton[ ntobef[elemcd(elem)] + 1 ] ;
		for( ; i > 1 ; i-- ){
			nodev  = pton[ ntoaft[nodev] + 1 ] ;
		}
		return  class_elemcd(NODE_CL,nodev);
	} else if( i < 0  && i >= -leng ){
		NODEINDX   nodev  = pton[ ntoaft[elemcd(elem)] - 1 ] ;
		for( ; i < -1 ; i++ ){
			nodev  = pton[ ntobef[nodev] - 1 ] ;
		}
		return  class_elemcd(NODE_CL,nodev);
	} else {
		return  NIL;
	}
}

ELEMENT  mxi_son( char *f, int l, ELEMENT i, ELEMENT elem ){
	if(  sortcdof(i) == INT_SORTCD  &&  class(elem) == NODE_CL ){
		return  mxk_son(i,elem);
	} else if ( i == NIL  ||  elem == NIL ){
		;
	} else if( sortcdof(i) != INT_SORTCD   ){
		mxi_prterrm(f,l,"son","first argument must be Int");
	} else {
		mxi_prterrm(f,l,"son","second argument must be a node");
	}
	return  NIL ;
}


ELEMENT  mxk_before( ELEMENT elem ){
	IFNIL(elem)
	return  class_elemcd( POINT_CL, ntobef[ elemcd(elem) ] ) ;
}

ELEMENT  mxi_before( char *f, int l, ELEMENT elem ){
	CHECK_NODENIL(mxk_before,"before")
}


ELEMENT  mxk_after( ELEMENT elem ){
	IFNIL(elem)
	return  class_elemcd( POINT_CL, ntoaft[ elemcd(elem) ] ) ;
}

ELEMENT  mxi_after( char *f, int l, ELEMENT elem ){
	CHECK_NODENIL(mxk_after,"after")
}


ELEMENT  mxk_node( ELEMENT elem ){
	IFNIL(elem)
	return  class_elemcd( NODE_CL, pton[ elemcd(elem) ] ) ;
}

ELEMENT  mxi_node( char *f, int l, ELEMENT elem ){
	if( class(elem) == POINT_CL )	return  mxk_node(elem);
	else if( elem == NIL )			return  NIL ;
	else {
		mxi_prterrm(f,l,"node","only defined for points and nil");
		return  NIL ;
	}
}


long  mxk_is( ELEMENT elem, ELEMENT sort ){
	return  issubsortk( sortcdof(elem), code(sort) ); 
}

long  mxi_is( char *f, int l, ELEMENT elem, ELEMENT sort ){
	short  escd =  sortcdof(elem);
	short  ccd  =  code(sort);

	if( class(sort)==SORTCONST_CL &&  escd != 0 && issubsortk(escd, ccd) ){
		return  1;
	} else if( class(sort) != SORTCONST_CL ){
		mxi_prterrm(f,l,"is","sort argument badly formed");
	} else if( escd == 0 ){
		mxi_prterrm(f,l,"is","element argument badly formed");
	}
	return  0;
}



long  mxk_eq( ELEMENT e1, ELEMENT e2 ){
	SORTCDT sort1;
	int  i;
	int  b = 1;

	if(  class(e1) != NATERM_CL  || class(e2) != NATERM_CL  ){
		return e1==e2;
	} else if(  (sort1=sortcdof(e1)) == sortcdof(e2) ){
		long  leng1 = mxk_numsubterms(e1);
		long  leng2 = mxk_numsubterms(e2);
		if( sort1 >= mxi_tupel_sortcd_lb ){
			for( i = 1; i <= leng1; i++ ){
				b =  b  &&  mxk_eq( mxk_subterm(i,e1),mxk_subterm(i,e2) );
			}
			return b;
		} else {
			if( leng1 < 0 )  leng1 = -leng1;
			if( leng2 < 0 )  leng2 = -leng2;
			if( leng1 == leng2 ){
				for( i = 1; i <= leng1; i++ ){
					b =  b  &&  mxk_eq( mxk_subterm(i,e1),mxk_subterm(i,e2) );
				}
				return b;
			} 
		}
	}
	return 0;
}


long  mxi_eq( char *f, int l, ELEMENT e1, ELEMENT e2 ){
	SORTCDT sort1;
	int  i;
	int  b = 1;

	if(  class(e1) != NATERM_CL  ){
		return e1==e2;
	} else if(  (sort1=sortcdof(e1)) == sortcdof(e2) ){
		long  leng1 = mxk_numsubterms(e1);
		long  leng2 = mxk_numsubterms(e2);
		if( sort1 >= mxi_tupel_sortcd_lb ){
			for( i = 1; i <= leng1; i++ ){
				b =  b  &&  mxi_eq(f,l, mxk_subterm(i,e1),mxk_subterm(i,e2) );
			}
			return b;
		} else {
			if( leng1 < 0 )  leng1 = -leng1;
			if( leng2 < 0 )  leng2 = -leng2;
			if( leng1 == leng2 ){
				for( i = 1; i <= leng1; i++ ){
					b =  b  &&  mxi_eq(f,l, mxk_subterm(i,e1),mxk_subterm(i,e2) );
				}
				return b;
			} 
		}
	}
	return 0;
}


/**************************************************************************/

static  void  init_numbertab( ELEMENT elem ){
	long i, bound;
	SORTCDT scd =  sortcdof(elem);

	if( scd < TERM_SORTCD ){
		mxi_numbertab[ -scd ] ++ ;
		bound =  mxk_numsubterms(elem) ;
		for( i=1 ; i<=bound ; i++)
				init_numbertab( mxk_subterm(i,elem) );
	} else {
		mxi_prterrm("max_std.c",0,"init_numtab","syntaxterm contains nodes");
		exit( EXIT_FAILURE );
	}
}


static  POINTINDX pointindx =  1;

void  init_tabs( ELEMENT elem ){
	long i, bound;
	NODEINDX nodeindx ;

	nodeindx =  ++ mxi_offsettab[ -sortcdof(elem) ] ;
	ntot[ nodeindx ]    =  elem ;
	ntobef[ nodeindx ]  =  pointindx ;
	pton[ pointindx++ ] =  nodeindx ;

	bound =  mxk_numsubterms(elem) ;
	for( i=1 ; i<=bound ; i++){
		init_tabs( mxk_subterm(i,elem) );
	}
	ntoaft[ nodeindx ]  =  pointindx ;
	pton[ pointindx++ ] =  nodeindx ;
}

static  void  enteroffs( SORTCDT ccd, long offs, ScdOffsPair *sop ){
	int i = -1;
	while( sop[++i].ccd != ccd );
	sop[i].offs =  offs;
} 

extern  long  mxi_atteval( void ); 
/* having several structures, atteval needs a parameter */

long mxk_init( int ccd, ELEMENT ipterm ){
	int i;
	SORTCDT  rootnscd  = -sortcdof(ipterm);
	long     offsetv   = 0 ;

	init_numbertab( ipterm );
	mxi_offsettab[ rootnscd ] =  offsetv ;
	offsetv +=  mxi_numbertab[ rootnscd ] ;
	for( i = NODE_SORTCD+1 ; i < rootnscd ; i++ ){
		mxi_offsettab[ i ] =  offsetv ;
		offsetv +=  mxi_numbertab[ i ] ;
	}
	for( i = rootnscd+1 ; i <= -mxi_list_sortcd_lb ; i++ ){
		mxi_offsettab[ i ] =  offsetv ;
		offsetv +=  mxi_numbertab[ i ] ;
	}
	if( offsetv > MAXUSHORT*128 ){
		mxi_prterrm("max_std.c",0,"mxk_sc","syntaxterm two big");
		exit( EXIT_FAILURE );
	}
	mxi_numbertab[ POINT_SORTCD ] =  2*offsetv;
	mxi_numbertab[ NODE_SORTCD ]  =  offsetv;

	pton = (NODEINDX *) calloc( 2*offsetv+1, sizeof(NODEINDX) );
	if( pton == 0L ){
		mxi_prterrm("max_std.c",0,"mxk_sc","Cannot allocate pton");
		exit( EXIT_FAILURE );
	}
	ntoaft = (POINTINDX *) calloc( offsetv+1, sizeof(POINTINDX) );
	if( ntoaft == 0L ){
		mxi_prterrm("max_std.c",0,"mxk_sc","Cannot allocate ntoaft");
		exit( EXIT_FAILURE );
	}
	ntobef = (POINTINDX *) calloc( offsetv+1, sizeof(POINTINDX) );
	if( ntobef == 0L ){
		mxi_prterrm("max_std.c",0,"mxk_sc","Cannot allocate ntobef");
		exit( EXIT_FAILURE );
	}
	ntot = (ELEMENT *) calloc( offsetv+1, sizeof(ELEMENT) );
	if( ntot == 0L ){
		mxi_prterrm("max_std.c",0,"mxk_sc","Cannot allocate ntot");
		exit( EXIT_FAILURE );
	}
	init_tabs( ipterm );

	for( i = NODE_SORTCD+1 ; i <= -mxi_list_sortcd_lb ; i++ ){
		mxi_offsettab[ i ] -=  mxi_numbertab[ i ] ;
	}
	for( i = -mxi_list_sortcd_lb+1 ; i <= -mxi_class_sortcd_lb ; i++ ){
		int j = 0;
		ScdOffsPair  *cop =  mxi_coffsettab[i];
		offsetv = 0;
		while( cop[j].ccd != 0 ){
			offsetv += mxi_numbertab[ cop[j].ccd ] ;
			cop[++j].offs =  offsetv;
		} 
		mxi_numbertab[i] = offsetv;
	}
	for( i = -mxi_list_sortcd_lb+1 ; i <= -mxi_class_sortcd_lb ; i++ ){
		int k, j = 0;
		ScdOffsPair  *cop =  mxi_coffsettab[i];
		while( cop[j].ccd != 0 ){
			if( cop[j].ccd == NODE_SORTCD ){
				for( k = NODE_SORTCD+1 ; k <= -mxi_list_sortcd_lb ; k++ ){
					enteroffs( i, cop[j].offs, mxi_coffsettab[k] ); 
				}
			} else {
				enteroffs( i, cop[j].offs, mxi_coffsettab[cop[j].ccd] ); 
			}
			j++;
		}
	}
	return mxi_atteval();
}


long mxi_init( char *f, int l, int ccd, ELEMENT elem ){
	SORTCDT rootsort  = sortcdof(elem);

	if( ! issubsort( rootsort, ccd )  ){
		mxi_prterrm(f,l,"init","input term to structure construction is of wrong sort");
		return  0;
	} else {
		return  mxk_init(ccd,elem);
	}
}


long  mxk_free(){
	free( pton );
	free( ntoaft );
	free( ntobef );
	free( ntot );
	return 1L;
}

long  mxi_free( char *f, int l ){
	if( mxi_numbertab[ NODE_SORTCD ] > 0 ){
		return  mxk_free();
	} else {
		mxi_prterrm(f,l,"free","there is no structure to free");
		return  0;

	}
}



ELEMENT  mxi_string_conc( char* f, int l, long parno,...){
	ELEMENT* params;
	char*    strv;
	long     errflag = 0;
	int      i, resstrlength = 1;
	va_list  ap;

	params =  (ELEMENT*) calloc( parno+1, sizeof(ELEMENT) );
	if( params==0L ){
		mxi_prterrm("max_std.c",0,"string_conc","Cannot allocate space to copy params");
		exit( EXIT_FAILURE );
	}
	va_start( ap, parno );

	for( i = 1; i <= parno; i++ ){
		params[i] =  va_arg( ap, ELEMENT );
		if( params[i] == NIL )  return  NIL;
		if( ! mxk_is( params[i],_String )  ){
			errflag = i;
		} else {
			resstrlength +=  mxk_strlength( params[i] );
		}
	}
	va_end( ap );

	if( errflag ){
		mxi_prterrm(f,l,"string_conc","badly formed string expression");
		return  NIL;
	} else {
		strv =  (char*) malloc(resstrlength);
		if( s == 0L ){
			mxi_prterrm("max_std.c",0,"string_conc","Cannot allocate space for string");
			exit( EXIT_FAILURE );
		}
		strv[0] =  '\0';
		for( i = 1; i <= parno; i++ ){
			strcat( strv, mxk_etoa(params[i]) );
		}
		return mxk_atoe(strv);
	}
}




/* Last modified 10.5.96 */

/*    function declarations */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "max_spec.h"
#include "max_global.h"

#define  PEVAL_OPT   ((max_options.onr&1)==1)
/** PEVAL_OPT is only used in 'prt_stdpart' and 'genc_att_seq' **/

#define  WAITSTR     0
#define  HEAPSTR     1
#define  ENUMSTR     2

#define  WAITL(str)   (((str)&32)==32)
#define  PEVAL(str)   (((str)&4)==4)
#define  STRAT(str)   ((str)&3)
#define  FCT_ATT_MIX(str)    (((str)&16)==16)
#define  FCT_ATT_WAITL(str)  ( FCT_ATT_MIX(str) && WAITL(str) )
#define  FORWARD(str) (((str)&8)==0)

#define  IDSTR(idn)       etoa(idtos(term(son(1,idn))))
#define  LINE(idn)        etoi(term(son(2,idn)))

#define  P_FALSE 0
#define  P_TRUE  1
#define  AFTER  1
#define  BEFORE 2
#define  AFTBEF 3

/* #tc */
typedef long Boolean;
extern Boolean **att_sortcheck;
extern Boolean **att_nilcheck;
extern Boolean **fct_sortcheck;
extern Boolean **fct_nilcheck;


static  FILE *out;
static  char *filename;

static  SORTCDT  tupelsortcdlb;
static  SORTCDT  listsortcdlb;
static  SORTCDT  classsortcdlb;


void  prtsortconst( ELEMENT sortidn ){ /*  input is a SortId@  */
	fprintf(out,"_%s", IDSTR(sortidn) );
	if(  is(sortidn,_NodeSortId_)  )	fprintf(out,"_" );
}

void  prt_stdpart( int maxwaitpar ){
	fprintf(out,"\n");
	fprintf(out,"#include <stdio.h>\n");
	fprintf(out,"#include <stdlib.h>\n");
	fprintf(out,"#include <stdarg.h>\n");

	fprintf(out,"extern mxi_ELEMENT mxi_string_conc( char*, int, long,...);\n");
	fprintf(out,"static mxi_ELEMENT mxv_errstr;\n");
	fprintf(out,"FILE *errfile = stderr;\n");
	fprintf(out,"extern void mxi_prterrm(char*,int,char*,char*);\n");
	fprintf(out,"static char mxi_errmstr[] = \"0th parameter is of wrong sort\";\n");
	fprintf(out,"void comp_errm(char *filenm, int ln, char *fctnm, int parno){\n");
	fprintf(out,"\tmxi_errmstr[0] = (char)(parno)+'0';\n"); 
	fprintf(out,"\tmxi_prterrm(filenm,ln,fctnm,mxi_errmstr);\n");
	fprintf(out,"}\n\n");

	fprintf(out,"static  char *_c = \"%s.c\";\n", filename );
	fprintf(out,"static  char *_m = \"%s.m\";\n", filename );
	fprintf(out,"#define SORTCDT  short\n");
	fprintf(out,"#define MAXUNDEF %dL\n",MAXUNDEF);
	fprintf(out,"#define IFNIL(e) {if(e==mxs_nil(_c,0)) return mxs_nil(_c,0);}\n");

	fprintf(out,"#define IS(e,t,f,l,fct,i)  {if(!mxs_is(_c,0,e,t)){");
	fprintf(out,"comp_errm(f,l,fct,i);return mxs_nil(_c,0);}}\n");

	fprintf(out,"#define ISORNIL(e,t,f,l,fct,i)  {if(!mxs_is(_c,0,e,t)&&e!=mxs_nil(_c,0)){");
	fprintf(out,"comp_errm(f,l,fct,i);return mxs_nil(_c,0);}}\n");
	fprintf(out,"\n\n");

	fprintf(out,"typedef void (*EVALFCT1)( ELEMENT );\n");
	fprintf(out,"typedef void (*EVALFCT)( ELEMENT, ELEMENT, int, ELEMENT * );\n");

	fprintf(out,"typedef struct AttInstElem{\n");
	fprintf(out,"\tEVALFCT attevalfct;\n");
	fprintf(out,"\tELEMENT  attnode;\n");
	fprintf(out,"\tstruct AttInstElem *rest;\n");

	if( PEVAL_OPT ) {
		fprintf(out,"\tint state;\n");
		if(maxwaitpar) fprintf(out,"\tELEMENT intres_array[%d];\n",maxwaitpar);
	}

	fprintf(out,"} *AttInstSq;\n\n");

	fprintf(out,"long waitlist_count = 0;\n");

	fprintf(out,"static %sinsAttInst( EVALFCT attevalfct, ELEMENT attnode,",(maxwaitpar)?"ELEMENT *":"void ");

	if( PEVAL_OPT )	fprintf(out," int state,\n\t");
	else		fprintf(out," \n\t");

	fprintf(out,"AttInstSq* undefatt, long undefattix ) {\n");

	fprintf(out,"\tAttInstSq  waitlist  = (AttInstSq) malloc( sizeof(struct AttInstElem) );\n");

	fprintf(out,"\twaitlist_count++;\n");
	fprintf(out,"\tif( waitlist == 0L ){\n");
	fprintf(out,"\t\tfprintf(stderr,\"\\n***** Error: Cannot allocate wait list element\\n\");\n");
	fprintf(out,"\t\texit( EXIT_FAILURE );\n");
	fprintf(out,"\t}\n");
	fprintf(out,"\twaitlist->attevalfct = attevalfct;\n");
	fprintf(out,"\twaitlist->attnode    = attnode;\n");

	if( PEVAL_OPT ) fprintf(out,"\twaitlist->state      = state;\n");

	fprintf(out,"\twaitlist->rest       = undefatt[undefattix];\n");
	fprintf(out,"\tundefatt[undefattix] = waitlist;\n");

	if( maxwaitpar && PEVAL_OPT ) fprintf(out,"return &waitlist->intres_array[0];\n}\n\n");
	else	fprintf(out,"}\n\n");

	fprintf(out,"SORTCDT   mxi_tupel_sortcd_lb  = %d;\n", tupelsortcdlb );
	fprintf(out,"SORTCDT   mxi_list_sortcd_lb   = %d;\n", listsortcdlb  );
	fprintf(out,"SORTCDT   mxi_class_sortcd_lb  = %d;\n", classsortcdlb );
	fprintf(out,"\n\n");
}


static  void  prt_listtoelemtab( void ){
    ELEMENT  sortidn;
	long     prodx; 

	fprintf(out,"static  SORTCDT  mxi_auxlisttoelemtab[%d] = {\n",
		number(_ListProd_) + 1 );
	for( prodx = number(_ListProd_); prodx >= 1; prodx-- ){
		sortidn =  son( 2, element(prodx,_ListProd_) );
		if(  is( sortidn,_NodeSortId_)  ){
			fprintf(out,"%d,",-prodcd( fath(decl(sortidn)) ) );
		} else {
			fprintf(out,"%d,", prodcd( fath(decl(sortidn)) ) );
		}
	}
	fprintf(out,"0};\n\n");
	fprintf(out,"SORTCDT  *mxi_listtoelemtab = mxi_auxlisttoelemtab+%d;",
		-listsortcdlb);
	fprintf(out,"\n\n\n");
}


static  void  prt_classtosorttab( void ){
	int i, nl = 1;
	long ix, bound;

	bound =  number(_ClassProd_);
	for( ix = 1 ; ix <= bound ; ix++ ){
		SortSq  sqv = etop( subsorts(element(ix,_ClassProd_)) );
		fprintf(out,"static  SORTCDT subsort_%d[] = {", ix-listsortcdlb );
		while( sqv != NULL ){
			fprintf(out,"%d,", sqv->first);
			sqv = sqv->rest;
		}
		fprintf(out,"0};\n");
	}
	fprintf(out,"\n");

	fprintf(out,"static  SORTCDT  *mxi_auxclasstosorttab[%d] = { 0L,\n", bound+1 );
	for( i = -classsortcdlb ; i > -listsortcdlb ; i-- ){
		fprintf(out,"subsort_%d,", i );
		if( nl++ == 5 ){	nl = 1;		fprintf(out,"\n");}
	}
	fprintf(out,"};\n\nSORTCDT  **mxi_classtosorttab = ");
	fprintf(out,"mxi_auxclasstosorttab+%d;\n\n\n", -classsortcdlb+1 );
}

extern  SortSq  appSortSq( SORTCDT, SortSq);
SortSq  *supsortstab;


static  void  init_supsorts(){
	int  num_bsortcd =  2*(-listsortcdlb) + 1 ;
	int  j;
	long ix, bound;
	SORTCDT scd;

	supsortstab   = (SortSq*) calloc( num_bsortcd, sizeof(SortSq) );
	if( supsortstab==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate internal table (init_supsorts\n");
		exit( EXIT_FAILURE );
	} else {
		supsortstab =  supsortstab - listsortcdlb;
	}
	for( j = listsortcdlb ; j <= -listsortcdlb ; j++ ){
		if( j < TERM_SORTCD ){
			supsortstab[j] =  appSortSq(TERM_SORTCD,supsortstab[j]);
		} else if( j > NODE_SORTCD ){
			supsortstab[j] =  appSortSq(NODE_SORTCD,supsortstab[j]);
		}
	}
	bound =  number(_ClassProd_);
	for( ix = 1 ; ix <= bound ; ix++ ){
		SortSq  sqv = etop( subsorts(element(ix,_ClassProd_)) );
		do {
			scd =  sqv->first;
			if( scd == NODE_SORTCD ){
				for( j = NODE_SORTCD+1 ; j <= -listsortcdlb ; j++ ){
					supsortstab[j] =  appSortSq(listsortcdlb-ix,supsortstab[j]);
				}
			} else if( scd == TERM_SORTCD ){
				for( j = TERM_SORTCD-1 ; j >= listsortcdlb ; j-- ){
					supsortstab[j] =  appSortSq(listsortcdlb-ix,supsortstab[j]);
				}
				for( j = NODE_SORTCD+1 ; j <= -listsortcdlb ; j++ ){
					supsortstab[j] =  appSortSq(ix-listsortcdlb,supsortstab[j]);
				}
			} else {
				supsortstab[scd] =  appSortSq(listsortcdlb-ix,supsortstab[scd]);
				if( scd < TERM_SORTCD )
					supsortstab[-scd] =  appSortSq(ix-listsortcdlb,supsortstab[-scd]);
			}
			sqv = sqv->rest;
		} while( sqv != NULL );
	}

}  

static  void  prt_supsorttab(){
	int i, nl = 1;

	for( i = listsortcdlb ; i <= -listsortcdlb ; i++ ){
		SortSq  sqv = supsortstab[i];
		if( i< 0 ){
			fprintf(out,"static  SORTCDT supsort_%d[] = {", -i);
		} else {
			fprintf(out,"static  SORTCDT supsort%d[] = {", i);
		}
		while( sqv != NULL ){
			fprintf(out,"%d,", sqv->first);
			sqv = sqv->rest;
		}
		fprintf(out,"0};\n");
	}
	fprintf(out,"\n");

	fprintf(out,"static  SORTCDT  *mxi_auxsupsorttab[%d] = {\n",
		2*(-listsortcdlb) + 1 );
	for( i = listsortcdlb ; i <= -listsortcdlb ; i++ ){
		if( i< 0 ){
			fprintf(out,"supsort_%d,", -i );
		} else {
			fprintf(out,"supsort%d,", i );
		}
		if( nl++ == 5 ){	nl = 1;		fprintf(out,"\n");}
	}
	fprintf(out,"};\n\nSORTCDT  **mxi_supsorttab = ");
	fprintf(out,"mxi_auxsupsorttab+%d;\n\n\n", -listsortcdlb );
}


static  void  prt_indexingtabs(){
	int i, nl = 1;
	long ix, bound;
	SortSq  sqv;

	fprintf(out,"static  long  mxi_auxnumbertab[%d];\n", 
		-(IDENT_SORTCD) + 1 - classsortcdlb  );
	fprintf(out,"long  *mxi_numbertab =  mxi_auxnumbertab+%d;\n\n",
		-(IDENT_SORTCD) );

	fprintf(out,"long  mxi_offsettab[%d];\n\n", -listsortcdlb+1 );

	fprintf(out,"typedef  struct{\n\t\t\tshort  ccd;\n");
	fprintf(out,"\t\t\tlong   offs;\n\t\t}  ScdOffsPair;\n\n");

	for( i = NODE_SORTCD+1 ; i <= -listsortcdlb ; i++ ){
		fprintf(out,"static  ScdOffsPair  cop%d[] = {", i );
		sqv = supsortstab[i];
		while( sqv != NULL ){
			if( sqv->first > NODE_SORTCD )
				fprintf(out,"{%d,0L},", sqv->first);
			sqv = sqv->rest;
		}
		fprintf(out,"};\n");
	}
	bound =  number(_ClassProd_);
	for( ix = 1 ; ix <= bound ; ix++ ){
		fprintf(out,"static  ScdOffsPair  cop%d[] = {", ix-listsortcdlb );
		sqv = etop( subsorts(element(ix,_ClassProd_)) );
		while( sqv != NULL ){
			if( sqv->first <= TERM_SORTCD )
				fprintf(out,"{%d,0L},", -(sqv->first) );
			sqv = sqv->rest;
		}
		fprintf(out,"{0,0L}};\n");
	}
	fprintf(out,"\n");
	fprintf(out,"ScdOffsPair *mxi_coffsettab[%d] = {\n",
		 1 - classsortcdlb  );
	fprintf(out,"0L,0L,0L,\n");
	for( i = NODE_SORTCD+1 ; i <= -classsortcdlb ; i++ ){
		fprintf(out,"cop%d,", i );
		if( nl++ == 10 ){	nl = 1;		fprintf(out,"\n");}
	}
	fprintf(out,"};\n\n");
}

#define INDENT(i) {int _z;for(_z=1;_z<=i;_z++)fprintf(out,"\t");}

static  ELEMENT  endofpredef;




static  void  prt_heap_fcts( FILE *out, int heapsize )
{
	fprintf(out,"\n/* Auxiliary functions for correct evaluation order */\n\n");

	fprintf(out,"typedef struct {\n\tELEMENT point,node;\n\tint ind;\n} HEAP_ITEM;\n\n");
	fprintf(out,"static HEAP_ITEM mxz_heap[%d];\n\n",heapsize);
	fprintf(out,"static int mxz_count[%d];\n",heapsize);
	fprintf(out,"static int mxz_number[%d];\n\n",heapsize);

	fprintf(out,"static int mxz_gt( HEAP_ITEM *p, HEAP_ITEM *q )\n{\n");
	fprintf(out,"int x = p->point, y = q->point;\n");
	fprintf(out,"return (x==mxs_nil(_c,0)) || (y!=mxs_nil(_c,0) && x > y);\n}\n\n");

	fprintf(out,"static int mxz_lt( HEAP_ITEM *p, HEAP_ITEM *q )\n{\n");
	fprintf(out,"int x = p->point, y = q->point;\n");
	fprintf(out,"return (x==mxs_nil(_c,0)) || (y!=mxs_nil(_c,0) && x < y);\n}\n\n");

	fprintf(out,"static void mxz_sift_backw( int j, int r )\n{\n");
	fprintf(out,"HEAP_ITEM x = mxz_heap[j];\n\n");
	fprintf(out,"\twhile((j<<=1)<=r) {\n");
	fprintf(out,"\t\tif(j<r) if( mxz_lt(&mxz_heap[j],&mxz_heap[j+1])) j++;\n");
	fprintf(out,"\t\tif( !mxz_lt(&x,&mxz_heap[j])) break;\n");
	fprintf(out,"\t\tmxz_heap[j>>1] = mxz_heap[j];\n\t}\n");
	fprintf(out,"\tmxz_heap[j>>1] = x;\n}\n\n");

	fprintf(out,"static void mxz_sift_forw( int j, int r )\n{\n");
	fprintf(out,"HEAP_ITEM x = mxz_heap[j];\n\n");
	fprintf(out,"\twhile((j<<=1)<=r) {\n");
	fprintf(out,"\t\tif(j<r) if( mxz_gt(&mxz_heap[j],&mxz_heap[j+1])) j++;\n");
	fprintf(out,"\t\tif( !mxz_gt(&x,&mxz_heap[j])) break;\n");
	fprintf(out,"\t\tmxz_heap[j>>1] = mxz_heap[j];\n\t}\n");
	fprintf(out,"\tmxz_heap[j>>1] = x;\n}\n\n");

/***  defines for heap manipulation *******************/

	fprintf(out,"#define mxz_HIF(i)       mxz_heap[i].ind=i\n");
	fprintf(out,"#define mxz_HPB(i)       mxz_heap[i].point=mxs_before(_c,0,mxz_heap[i].node)\n");
	fprintf(out,"#define mxz_HPA(i)       mxz_heap[i].point=mxs_after(_c,0,mxz_heap[i].node)\n");
	fprintf(out,"#define mxz_NVE(j,i,S)   mxz_heap[j].node=mxs_element(_c,0,mxz_count[i],S)\n");
	fprintf(out,"#define mxz_NRE(j,i,S)   mxz_heap[j].node=rev_element(mxz_count[i],S)\n");
	fprintf(out,"#define mxz_NIL(i)       mxz_heap[i].point=mxs_nil(_c,0)\n");

	fprintf(out,"#define mxz_FIRST(i,S)   ((mxz_count[i] = 1) > (mxz_number[i] = mxs_number(_c,0,S)))\n");
	fprintf(out,"#define mxz_LAST(i,S)    ((mxz_count[i] = mxs_number(_c,0,S)) < 1)\n");
	fprintf(out,"#define mxz_INC(i)       ((++mxz_count[i]) > mxz_number[i])\n");
	fprintf(out,"#define mxz_DEC(i)       ((--mxz_count[i]) < 1)\n\n");


	fprintf(out,"#define first_forw_bef(S,i)\\\n");
	fprintf(out,"mxz_FIRST(i,S) ? mxz_NIL(i) : (mxz_NVE(i,i,S),mxz_HPB(i),mxz_HIF(i))\n\n");

	fprintf(out,"#define first_backw_bef(S,i)\\\n");
	fprintf(out,"mxz_LAST(i,S)  ? mxz_NIL(i) : (mxz_NVE(i,i,S),mxz_HPB(i),mxz_HIF(i))\n\n");

	fprintf(out,"#define next_forw_bef(S,i)\\\n");
	fprintf(out,"mxz_INC(i)   ? mxz_NIL(1) : (mxz_NVE(1,i,S),mxz_HPB(1))\n\n");

	fprintf(out,"#define next_backw_bef(S,i)\\\n");
	fprintf(out,"mxz_DEC(i)   ? mxz_NIL(1) : (mxz_NVE(1,i,S),mxz_HPB(1))\n\n");


	fprintf(out,"#define first_forw_aft(S,i)\\\n");
	fprintf(out,"mxz_FIRST(i,S) ? mxz_NIL(i) : (mxz_NRE(i,i,S),mxz_HPA(i),mxz_HIF(i))\n\n");

	fprintf(out,"#define first_backw_aft(S,i)\\\n");
	fprintf(out,"mxz_LAST(i,S)  ? mxz_NIL(i) : (mxz_NRE(i,i,S),mxz_HPA(i),mxz_HIF(i))\n\n");

	fprintf(out,"#define next_forw_aft(S,i)\\\n");
	fprintf(out,"mxz_INC(i)   ? mxz_NIL(1) : (mxz_NRE(1,i,S),mxz_HPA(1))\n\n");

	fprintf(out,"#define next_backw_aft(S,i)\\\n");
	fprintf(out,"mxz_DEC(i)   ? mxz_NIL(1) : (mxz_NRE(1,i,S),mxz_HPA(1))\n\n");


	fprintf(out,"static void nextnode_forw_bef() {\n");
	fprintf(out,"ELEMENT P = mxz_heap[1].point;\n");
	fprintf(out,"do{ if(++P == mxz_lastpoint ) { mxz_NIL(1); return; }\n");
	fprintf(out,"  } while( P != mxs_before(_c,0,mxs_node(_c,0,P)));\n");
	fprintf(out,"mxz_heap[1].point=P;\nmxz_heap[1].node=mxs_node(_c,0,P);\n}\n\n");

	fprintf(out,"static void nextnode_forw_aft() {\n");
	fprintf(out,"ELEMENT P = mxz_heap[1].point;\n");
	fprintf(out,"if( P == mxz_lastpoint ) { mxz_NIL(1); return; }\n");
	fprintf(out,"do { P++; } while( P != mxs_after(_c,0,mxs_node(_c,0,P)));\n");
	fprintf(out,"mxz_heap[1].point=P;\nmxz_heap[1].node=mxs_node(_c,0,P);\n}\n\n");

	fprintf(out,"static void nextnode_backw_aft() {\n");
	fprintf(out,"ELEMENT P = mxz_heap[1].point;\n");
	fprintf(out,"do{ if(--P == mxz_firstpoint ) { mxz_NIL(1); return; }\n");
	fprintf(out,"  } while( P != mxs_after(_c,0,mxs_node(_c,0,P)));\n");
	fprintf(out,"mxz_heap[1].point=P;\nmxz_heap[1].node=mxs_node(_c,0,P);\n}\n\n");

	fprintf(out,"static void nextnode_backw_bef() {\n");
	fprintf(out,"ELEMENT P = mxz_heap[1].point;\n");
	fprintf(out,"if( P == mxz_firstpoint ) { mxz_NIL(1); return; }\n");
	fprintf(out,"do { P--; } while( P != mxs_before(_c,0,mxs_node(_c,0,P)) );\n");
	fprintf(out,"mxz_heap[1].point=P;\nmxz_heap[1].node=mxs_node(_c,0,P);\n}\n\n");

	fprintf(out,"#define firstnode_forw_bef(i)  (mxz_heap[i].point=mxz_firstpoint,mxz_heap[i].node=mxs_root(_c,0))\n\n");
	fprintf(out,"#define firstnode_backw_aft(i) (mxz_heap[i].point=mxz_lastpoint,mxz_heap[i].node=mxs_root(_c,0))\n\n");
	fprintf(out,"#define firstnode_forw_aft(i)  (firstnode_forw_bef(1),nextnode_forw_aft(),mxz_heap[i]=mxz_heap[1])\n\n");
	fprintf(out,"#define firstnode_backw_bef(i) (firstnode_backw_aft(1),nextnode_backw_bef(),mxz_heap[i]=mxz_heap[1])\n\n");
}


static  void  prt_stack_fcts( FILE *out )
{
	fprintf(out,"static ELEMENT *enum_stack, **rev_element_tab;\n");
	fprintf(out,"static int      enum_topelem;\n");
	fprintf(out,"static int      enum_index;\n\n");

	fprintf(out,"#define rev_element(i,sort) rev_element_tab[(sort)&0xffff][i]\n\n");

	fprintf(out,"void mxz_init_revindex( ELEMENT sort )\n{\nint i,bound;\n");
	fprintf(out,"ELEMENT *P;\n\n");
	fprintf(out,"\tif(rev_element_tab[sort & 0xffff] != NULL) return;\n");
	fprintf(out,"\tP = rev_element_tab[sort & 0xffff] = (ELEMENT *)calloc((1+mxs_number(_c,0,sort)),sizeof(ELEMENT));\n");
	fprintf(out,"\tif( P == 0L ){\n");
	fprintf(out,"\t\tfprintf(stderr,\"\\n***** Error: Cannot allocate rev_element_tab table \\n\");\n");
	fprintf(out,"\t\texit( EXIT_FAILURE );\n\t}\n");

	fprintf(out,"\tenum_index = 1;\n");
	fprintf(out,"\tenum_topelem = -1;\n");
	fprintf(out,"\tbound = mxs_number(_c,0,sort);\n\n");

	fprintf(out,"\tfor(i=1;i<=bound;i++) {\n");
	fprintf(out,"\t\t    if( enum_topelem >= 0 ) goto L2;\n");
	fprintf(out,"\t\tL1: enum_stack[++enum_topelem] = mxs_element(_c,0,enum_index++,sort);\n");
	fprintf(out,"\t\tL2: if(enum_index > bound) goto L3;\n");
	fprintf(out,"\t\t    if(mxs_desc(_c,0,mxs_element(_c,0,enum_index,sort),enum_stack[enum_topelem])) goto L1;\n");
	fprintf(out,"\t\tL3: P[i] = enum_stack[enum_topelem--];\n");
	fprintf(out,"\t}\n");
	fprintf(out,"}\n\n");
}



/**  CODE GENERATION  for EXTENDED PATTERN CLASS **/

/*  auxiliary function for generation of treewalk function - sequences  */
static void genc_pat_route( ELEMENT path ){

/* generates : treewalk ( mxv_anchor ); */

 int j,k,parth = 0;
 

          for(j = 1; j <= numsubterms(path) ; j++){
              switch(sort(subterm(j,path)))
                    {
                     case _Fath  :  fprintf(out,"mxs_fath(_c,0,");
                                    parth++;
         			    break;

                     case _Son   :  fprintf(out,"mxs_son(_c,0,%d,",etoi(subterm(1,subterm(j,path))));
                                    parth++;
				    break;

                     case _Lbroth : for(k = 1; k <= etoi(subterm(1,subterm(j,path))); k++){
                                       fprintf(out,"mxs_lbroth(_c,0,");
                                       parth++;
                                    }
				    break;
		     case _Rbroth : for(k = 1; k <= etoi(subterm(1,subterm(j,path))); k++){
                                       fprintf(out,"mxs_rbroth(_c,0,");
                                       parth++;
                                    }
				    break;

                     default :  assert( 1 == 0 );
                    }

           }

           fprintf(out,"mxv_anchor");

           /* close parentheses */
           for(j = 1; j <= parth; j++)
              fprintf(out,")");

           fprintf(out,";\n");

}


static  void  genc_pat_check( ELEMENT pat, char *plabel, int indent ){

        ELEMENT bound_names = search_bound_names( pat );
        ELEMENT free_items  = search_free_items( pat );
        ELEMENT anchor = pat_anchor(fath(pat));
        ELEMENT cur_bn,cur_fi,path;

        int i;

/* first check bound names */

        for(i = 1; i <= numsubterms(bound_names) ; i++){

        cur_bn = fath(subterm(i,bound_names));

        /* skip anchor unless SortPos or SubPattPos are specified and TopPosition (no Position-Check) */
        if( anchor == cur_bn && sort(son(1,cur_bn)) == _Blank_ 
            && sort(son(2,cur_bn)) == _Blank_ && sort(fath(cur_bn)) != _ItemList_ )
           continue;

        path = att_path( /*anchor,*/ cur_bn );

        if (path == nil()){
           fprintf(stderr,"\n***** Error: pattern contains no path to bound name");
           fprintf(stderr,"\n***** node : %dN",index(subterm(i,bound_names),_Node));
	   exit( EXIT_FAILURE );   
	}


        INDENT(indent)
        fprintf(out,"mxv_IR = ");
           genc_pat_route( path );
        
           /* nil - check (skip in case of anchor) */
 
           if( cur_bn != anchor ){
            INDENT(indent)
            fprintf(out,"if( mxv_IR == mxs_nil(_c,0) ) goto %s;\n", plabel );
           }

           /* check position in ItemList */
           if( abs_itempos(cur_bn) == nil() ){
             /* not TopPosition and no absolute position */

             /* check left */
             INDENT(indent)
             fprintf(out,"if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,%d,mxs_fath(_c,0,mxv_IR))) ) goto %s;\n", lmin_itempos(cur_bn) ,plabel );


             /* check right */
             INDENT(indent)
             fprintf(out,"if( mxs_before(_c,0,mxs_son(_c,0,%d,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto %s;\n", rmin_itempos(cur_bn) ,plabel );

           }

           else{

             if( abs_itempos(cur_bn) != 0 ){
               /* not TopPosition and absolute position */
               INDENT(indent)
               fprintf(out,"if( mxv_IR != mxs_son(_c,0,%d,mxs_fath(_c,0,mxv_IR)) ) goto %s;\n", abs_itempos(cur_bn) ,plabel );

             }
         
           }
    
           /* numsons - check (unless SubPatternPos unspecified) */

           if( sort(lbroth(subterm(i,bound_names))) != _Blank_ ){
      
            if( numberofastrks( lbroth(subterm(i,bound_names)) ) > 0 && num_items( cur_bn ) > 0 ){
              INDENT(indent)
              fprintf(out,"if( mxs_numsons(_c,0, mxv_IR ) < %d ) goto %s;\n", num_items( cur_bn ), plabel );
            }
            if( numberofastrks( lbroth(subterm(i,bound_names)) ) == 0 ){
              INDENT(indent)
              fprintf(out,"if( mxs_numsons(_c,0, mxv_IR ) != %d ) goto %s;\n", num_items( cur_bn ), plabel );
            }

           }

           /* sort - check (unless SortPos unspecified) */
	   
           if( sort(son(1,cur_bn)) != _Blank_ ){
              INDENT(indent)
              fprintf(out,"if( !mxs_is(_c,0,mxv_IR,");
	      prtsortconst( son(1,cur_bn) );
	      fprintf(out,") ) goto %s;\n", plabel );
           }


           /* name - check (unless anchor) */
           
           if( cur_bn != anchor ){

		INDENT(indent)
		fprintf(out,"if( mxv_IR != %s ) goto %s;\n",etoa(cgen_name(subterm(i,bound_names))), plabel );
           }

        } /* check bound names */



/* now check free items and bind free names  */
        for(i = 1; i<= numsubterms(free_items); i++){

        cur_fi = subterm(i,free_items);

        path = att_path( /*anchor,*/ cur_fi );

        if (path == nil()){
           fprintf(stderr,"\n***** Error: pattern contains no path to free item");
           fprintf(stderr,"\n***** node : %dN",index(cur_fi,_Node));
	   exit( EXIT_FAILURE );
	}

        /* named Pattern ? */
        if( sort(son(3,cur_fi)) != _Blank_ ){  

		INDENT(indent)
		fprintf(out,"%s = ",etoa(cgen_name(son(3,cur_fi))));
		genc_pat_route( path );
		INDENT(indent)
		fprintf(out,"mxv_IR = %s;\n",etoa(cgen_name(son(3,cur_fi))));
        }
        else{
		INDENT(indent)
		fprintf(out,"mxv_IR = ");       
		genc_pat_route( path );
        }

           /* nil - check ( in case of "fath" in path ) ; -> depth-first traversal */

           if( sort(subterm(1,path)) == _Fath ){
            INDENT(indent)
            fprintf(out,"if( mxv_IR == mxs_nil(_c,0) ) goto %s;\n", plabel );
           }
           
           /* check position in ItemList */
           if( abs_itempos(cur_fi) == nil() ){
             /* not TopPosition and no absolute position */

             /* check left */
             INDENT(indent)
             fprintf(out,"if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,%d,mxs_fath(_c,0,mxv_IR))) ) goto %s;\n", lmin_itempos(cur_fi) ,plabel );


             /* check right */
             INDENT(indent)
             fprintf(out,"if( mxs_before(_c,0,mxs_son(_c,0,%d,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto %s;\n", rmin_itempos(cur_fi) ,plabel );

           }

           else{

             if( abs_itempos(cur_fi) != 0 ){
               /* not TopPosition and absolute position */
               INDENT(indent)
               fprintf(out,"if( mxv_IR != mxs_son(_c,0,%d,mxs_fath(_c,0,mxv_IR)) ) goto %s;\n", abs_itempos(cur_fi) ,plabel );

             }
         
           }
    
    
           /* numsons - check (unless SubPatternPos unspecified) */
    
           if( sort(son(2,cur_fi)) != _Blank_ ){

            if( numberofastrks( son(2,cur_fi) ) > 0 && num_items( cur_fi ) > 0 ){
              INDENT(indent)
              fprintf(out,"if( mxs_numsons(_c,0, mxv_IR ) < %d ) goto %s;\n", num_items( cur_fi ), plabel );
            }
            if( numberofastrks( son(2,cur_fi) ) == 0 ){
              INDENT(indent)
              fprintf(out,"if( mxs_numsons(_c,0, mxv_IR ) != %d ) goto %s;\n", num_items( cur_fi ), plabel );
            }

           }

           
           /* sort - check (unless SortPos unspecified) */
	   
           if( sort(son(1,cur_fi)) != _Blank_ ){
              INDENT(indent)
              fprintf(out,"if( !mxs_is(_c,0,mxv_IR,");
	      prtsortconst( son(1,cur_fi) );
	      fprintf(out,") ) goto %s;\n", plabel );
           }

        } /* check free items and bind free names */

}



/****************** Code generation for MAX-expressions **********************/

static void genc_addpar( ELEMENT C, ELEMENT D ) { /* C is the caller, D is the called function */

	if( is(C,_FctOrAtt_) && is(D,_Function_) 
	   && FCT_ATT_WAITL(eval_strategy(D)) ) {

		if( eval_groupnr(C)==eval_groupnr(D) ) {

			if( is(C,_Attribute_) ) {
				fprintf(out,",(EVALFCT)mxe_%s,mxv_par",IDSTR(son(1,C)));
			} else {
				fprintf(out,",mxw_evf,mxw_par");
			}
		} else {
			fprintf(out,",0L,0");
		}
	} else if(  ( C == nil() )  &&  is(D,_Function_) 
	   && FCT_ATT_WAITL(eval_strategy(D)) ) {  /* call in condition */
	  	fprintf(out,",0L,0");
       }
}

void  genc_top( ELEMENT );

void  genc_list( ELEMENT explist ){
	int i, listleng =  numsons(explist);

	if(  listleng > 0 ){
		for( i=1 ; i<= listleng ; i++ ){
			fprintf(out,",");
			genc_top( son(i,explist) );
		}
	}
	genc_addpar( encl_fctoratt(explist), fath(decl(lbroth(explist))) );
	fprintf(out,")");
}

void  genc_top( ELEMENT tn ){
	switch( sort(tn) ){
	case _Name_:
	case _IfExpr_:
	case _LetExpr_:
		fprintf(out,"%s",etoa(cgen_name(tn)));
		break;
	case _CharConst_:
		fprintf(out,"mxs_ctoe(_c,0,'%c')", etoc(term(son(1,tn))) );
		break;
	case _IntConst_:
		fprintf(out,"mxs_itoe(_c,0,%d)", etoi(term(son(1,tn))) );
		break;
	case _StringConst_:
		fprintf(out,"mxs_atoe(_c,0,\"%s\")", etoa(term(son(1,tn))) );
		break;
	case _SortConst_:
		prtsortconst( son(1,tn) );
		break;
	case _FuncAppl_:
		if( maybe_wait(tn)==true() ){
			fprintf(out,"mxv_a%d", index(tn,_FuncAppl_) );
		} else {
			fprintf(out,"mxs_%s(_m,%d", IDSTR(son(1,tn)), LINE(son(1,tn)) );
			genc_list( son(2,tn) );
		}
		break;
	case _PredAppl_:
		fprintf(out,"mxs_%s(_m,%d", IDSTR(son(1,tn)), LINE(son(1,tn)) );
		genc_list( son(2,tn) );
		break;
	case _StringExpr_:
		fprintf(out,"mxi_string_conc(_m,%d,%d", LINE(tn), numsons(son(1,tn)) );
		genc_list( son(1,tn) );
		break;
	case _Or_:
		fprintf(out,"(");
		genc_top( son(1,tn) );
		fprintf(out,"||");
		genc_top( son(2,tn) );
 		fprintf(out,")");
		break;
	case _And_:
		fprintf(out,"(");
		genc_top( son(1,tn) );
		fprintf(out,"&&");
		genc_top( son(2,tn) );
 		fprintf(out,")");
		break;
	case _Impl_:
		fprintf(out,"( ! ");
		genc_top( son(1,tn) );
		fprintf(out,"||");
		genc_top( son(2,tn) );
 		fprintf(out,")");
		break;
	case _Neg_:
		fprintf(out,"( ! ");
		genc_top( son(1,tn) );
 		fprintf(out,")");
		break;
	case _DynUndef_:
		fprintf(out,"/*??*/ mxs_nil(_c,0)");
		break;
	default :
		fprintf(stderr,"\n**** Error: in genc_top\n");
	}
}


static  void  genc_att_seq( ELEMENT tn, int indent ){
	int bound, i, strategy;
	long applix;
	ELEMENT Z, EA, Called;
	ELEMENT parsortn;

	EA = encl_fctoratt( tn );
	applix =  index(tn,_FuncAppl_);
	strategy = eval_strategy( EA );

	Called = fath(decl(son(1,tn)));

	if( is( Called,_Function_) ) {
		INDENT(indent)
		fprintf(out,"mxv_a%d = ",applix);
		fprintf(out,"mxs_%s(_m,%d",IDSTR(son(1,tn)),LINE(son(1,tn)) );
		genc_list( son(2,tn) );
		fprintf(out,";\n");

		if( WAITL(strategy)) {
			INDENT(indent)
			fprintf(out,"if( mxv_a%d==MAXUNDEF ) return", applix );
			if( is(EA,_Function_) ) fprintf(out," MAXUNDEF");
			fprintf(out,";\n");
		}
	} else { /** attribute access **/
		INDENT(indent)
		fprintf(out,"mxv_ax = ");
		genc_top( son(1,son(2,tn)) );      /* code for actual parameter */
		fprintf(out,";\n");

		INDENT(indent)
		fprintf(out,"mxv_a%d = ",applix);

/***** confer comment "The waitlist-bit..." in  "attr_group_conv" in max_extrn.c ***/

		if( EA==Called && is_trivial_finegroup(EA)==true() && maybe_same_node(appl_order(tn))
			&& !WAITL(strategy) && STRAT(strategy) ) {
			fprintf(out,"( mxv_ax == mxv_par ) ? mxs_nil(_c,0) : ");
		}

		fprintf(out,"mxs_%s(_m,%d,mxv_ax",IDSTR(son(1,tn)),LINE(son(1,tn)) );
		genc_addpar( EA, Called );
		fprintf(out,");\n");

		if( WAITL(strategy) ) {

			Z = intres_collect(tn);
			bound = (PEVAL(strategy)) ? numsubterms(Z) : 0;

			INDENT(indent)
			fprintf(out,"if( mxv_a%d==MAXUNDEF ){%s\n", applix, bound?" ELEMENT *P;":"" );
			INDENT(indent+1)

			if( is(EA,_Attribute_) ) { /* caller is an attribute */

				fprintf(out,"%sinsAttInst((EVALFCT)mxe_%s,mxv_par,",bound?"P = ":"",
					IDSTR(son(1,encl_fctoratt(tn))));
			} else {
				fprintf(out,"%sinsAttInst(mxw_evf,mxw_par,",bound?"P = ":"" );
			}

			if( PEVAL_OPT ) {
				fprintf(out,"%d,",applix);
			}
			fprintf(out,"mxw_%s,",IDSTR(son(1,tn)) );
			parsortn =  son(1,son(2, fath(decl(son(1,tn))) ));

			fprintf(out,"mxs_index(_c,0,mxv_ax,");
			prtsortconst( parsortn );
			fprintf(out,"));\n",bound);

			for(i=1;i<=bound;i++) {
				INDENT(indent+1)
				fprintf(out,"P[%d] = %s;\n", i-1, etoa(cgen_name(subterm(i,Z))));
			}

			INDENT(indent+1) fprintf(out,"return");
			if( is(EA,_Function_) ) fprintf(out," MAXUNDEF");
			fprintf(out,";\n");

			INDENT(indent)   fprintf(out,"}\n");
			if(!FCT_ATT_MIX(strategy)) {
				INDENT(indent)
				fprintf(out,"Lz%d:;\n",applix);
			}
		}
	}
}


void  genc_intres( ELEMENT, int );

static  void  genc_subces( ELEMENT subcexprs, int indent ){
	int i, listleng =  numsubterms(subcexprs);
	for( i=1 ; i<= listleng ; i++ ){
		genc_intres(subterm(i,subcexprs), indent);
	}
}

void  genc_intres( ELEMENT subcexprv, int indent ){

	if( is( subcexprv,_LetExpr_)  ){
		INDENT(indent-1)
		fprintf(out,"{  /* LetExpr */\n");

		genc_subces(sces1_let(subcexprv),indent+1);

		INDENT(indent)
		fprintf(out,"%s_l%d = ", IDSTR(son(1,subcexprv)),index(subcexprv,_LetExpr_) );
		genc_top( son(2,subcexprv) );
		fprintf(out,";\n");

		genc_subces(sces2_let(subcexprv),indent+1);

		INDENT(indent)
		fprintf(out,"mxv_l%d = ", index(subcexprv,_LetExpr_));
		genc_top( son(3,subcexprv) );
		fprintf(out,";\n");
		INDENT(indent-1)
		fprintf(out,"}\n");
	}

	if( is( son(1,subcexprv),_FormulaCaseList_)  ){
		ELEMENT  fcasen =  son(1,son(1,subcexprv));		
		char labelstr[20];
		sprintf(labelstr,"L%d", index( subcexprv,_IfExpr_) );

		INDENT(indent-1)
		fprintf(out,"{  /* FormulaCaseList */\n");

		do {
			genc_subces( sces1_fcase(fcasen), indent );

			INDENT(indent)
			fprintf(out,"if( ");
			genc_top( son(1,fcasen));
			fprintf(out," ){\n");

			genc_subces( sces2_fcase(fcasen), indent+1 );

			INDENT(indent+1)
			fprintf(out,"mxv_i%d = ", index( subcexprv,_IfExpr_) );
			genc_top( son(2,fcasen));
			fprintf(out,";\n");

			INDENT(indent+1)
			fprintf(out,"goto %s;\n", labelstr );

			INDENT(indent)
			fprintf(out,"}\n");

			fcasen =  rbroth( fcasen );
		} while(  fcasen != nil()  );

		genc_subces( sces_if(subcexprv), indent );

		INDENT(indent)
		fprintf(out,"mxv_i%d = ", index( subcexprv,_IfExpr_) );
		genc_top( son(2,subcexprv) );
		fprintf(out,";\n");

		INDENT(indent)
		fprintf(out,"%s: ;\n", labelstr);
		INDENT(indent-1)
		fprintf(out,"}\n");
	}

	if( is( son(1,subcexprv),_PatternCaseList_)  ){
		ELEMENT  pcasen    =  son(1,son(1,subcexprv));		
		char iflabelstr[20];
		sprintf(iflabelstr,"L%d", index( subcexprv,_IfExpr_) );
		INDENT(indent-1)
		fprintf(out,"{  /* PatternCaseList */\n");

		do {
			/* if pattern doesn't match, goto patlabelstr */
			char patlabelstr[20];
			sprintf(patlabelstr,"Lp%d", index( pcasen,_PatternCase_) );
			INDENT(indent)
			fprintf(out,"{\n");

			INDENT(indent+1)
			fprintf(out,"ELEMENT mxv_anchor, mxv_IR;\n");
			/** mxv_anchor : contains anchor  mxv_IR : used for intermediate results **/

			INDENT(indent+1)
			fprintf(out,"mxv_anchor = %s;\n",etoa(cgen_name(son(3,pat_anchor(pcasen)))));
			
			/* code for pattern matching */
			genc_pat_check( son(1,pcasen), patlabelstr, indent+1 );

			genc_subces( sces_pcase(pcasen), indent+1 );

			INDENT(indent+1)
			fprintf(out,"mxv_i%d = ", index( subcexprv,_IfExpr_) );
			genc_top( son(2,pcasen));
			fprintf(out,";\n");

			INDENT(indent+1)

			fprintf(out,"goto %s;\n", iflabelstr );
			INDENT(indent)
			fprintf(out,"}\n");

			INDENT(indent)
			fprintf(out,"%s: ;\n", patlabelstr);

			pcasen    =  rbroth( pcasen );
		} while(  pcasen != nil()  );

		genc_subces( sces_if(subcexprv), indent );
		INDENT(indent+1)
		fprintf(out,"mxv_i%d = ", index( subcexprv,_IfExpr_) );
		genc_top( son(2,subcexprv));
		fprintf(out,";\n");

		INDENT(indent)
		fprintf(out,"%s: ;\n", iflabelstr);
		INDENT(indent-1)
		fprintf(out,"}\n");
	}

	if( is( subcexprv,_FuncAppl_)  ){
		INDENT(indent-1)
		fprintf(out,"{  /* Attribute access */\n");
		genc_subces(sces_attacc(subcexprv),indent+1);

		genc_att_seq( subcexprv, indent);
		INDENT(indent-1)
		fprintf(out,"}\n");
	}

	if( is( subcexprv,_Function_) || is( subcexprv,_Predicate_) || is(subcexprv,_DynFunc_) ){
		genc_subces(sces_appl(subcexprv),indent+1);
		fprintf(out,"\treturn ");
		genc_top(son(-1,subcexprv));
		fprintf(out,";\n");

	}
	if( is( subcexprv,_Attribute_)  ){
		int strategy = eval_strategy(subcexprv);

		genc_subces(sces_appl(subcexprv),indent+1);

		fprintf(out,"\tmxv_ax = mxs_index(_c,0,%s,", IDSTR(son(1,son(3,subcexprv)))  );
		prtsortconst( son(1,son(2,subcexprv)) );
		fprintf(out,");\n\t");

		if( WAITL(strategy) && PEVAL(strategy)) fprintf(out,"mxv_res = ");
		fprintf(out,"mxa_%s[ mxv_ax ] = ", IDSTR(son(1,subcexprv)) );
		genc_top( son(5,subcexprv) );
		fprintf(out,";\n");
	}

	if(  is( subcexprv,_Condition_)  ){

		genc_subces( sces1_cond(subcexprv), indent);
		INDENT(indent)
		fprintf(out,"if( !(  ");
		genc_top( son(2,subcexprv) );
		fprintf(out," )  ){\n");

		INDENT(indent+1)
		fprintf(out,"mxv_c0 = 0L;\n");
		genc_subces( sces2_cond(subcexprv), indent+1 );

		INDENT(indent+1)
		fprintf(out,"mxv_errstr =  ");
		genc_top( son(3,subcexprv));
		fprintf(out,";\n");

		INDENT(indent+1);
		fprintf(out,"fprintf(stderr,\"%%s\", mxs_etoa(_c,0,mxv_errstr) );\n");
		INDENT(indent);
		fprintf(out,"}\n");
	}
}


static  void  genc_cnd_pat( ELEMENT patn, ELEMENT cndn, char* loopend, int indentp );

static  void  genc_cnd_itl( ELEMENT itln, ELEMENT cndn, char* loopend, int indentp ){
	char loopendvar[20];
	char terminationstr[20];
	int  indent =   indentp;
	int  absposition, relposition, i;
	long patix =  index( fath(itln),_Pattern_);
	ELEMENT itn, itnforreinit;
	ELEMENT firstasterisk, lastasterisk;

	strcpy( loopendvar, loopend );
	INDENT(indent)
	if( numberofastrks(itln)==0 ){
		fprintf(out,"if( mxs_numsons(_c,0,mxv_c%d)!=%d ) %s;\n", 
										patix, numsons(itln), loopendvar );
	} else {
		fprintf(out,"if( mxs_numsons(_c,0,mxv_c%d) < %d ) %s;\n",
					patix, numsons(itln) - numberofastrks(itln), loopendvar );
	}
	/*  the following initializes all subpatterns from the right up to the  */
	/*  rightmost asterisk, i.e. all subpatterns if there is no '*'         */
	itn = son(-1,itln);
	absposition = 0;
	relposition = -1;
	while(  itn!=nil()  &&  ! is( itn,_Asterisk_)  ){
		ELEMENT  lastpatn;
		absposition--;
		if( relposition >= 0 )  relposition++;
		if(  is( itn,_Pattern_)  ){
			INDENT(indent)
			fprintf(out,"mxv_c%d = ", index( itn,_Pattern_) );
			if(  relposition == -1  ){
				fprintf(out,"mxs_son(_c,0,%d,mxv_c%d);\n", absposition, patix );
				relposition = 0;
			} else {
				for( i=1; i<=relposition; i++ )  	fprintf(out,"mxs_lbroth(_c,0,");
				fprintf(out,"mxv_c%d", index( lastpatn,_Pattern_) );
				for( i=1; i<=relposition; i++ )		fprintf(out,")");
				fprintf(out,";\n");
				relposition = 0;
			}
			lastpatn = itn;
		}
		itn =  lbroth(itn);
	}
	/*  the following generates the code for the subpatterns starting at the      */
	/*  left hand side; and the beginning of loops if there is more than one '*'  */
	if(  numberofastrks(itln) >= 1  ){
		ELEMENT  lastastrk =  itn;

		if(  numberofastrks(itln) > 1  ){ /*  preparations for the loop termination  */
			ELEMENT  lastitem  =  rbroth( next_left_pat(lastastrk) );
			if(  lastitem == lastastrk  ){
				lastitem =  rbroth( lastitem );
			}  /*  now lastitem is positioned to the termination element  */

			if(  lastitem == nil()  ){
				sprintf( terminationstr, "mxs_nil(_c,0)" );
			} else if(  is( lastitem,_Pattern_)  ){
				sprintf( terminationstr, "mxv_cbl%d", index( lastitem,_Pattern_) );
			} else {  /*  is( lastitem,_Blank_)  */
				sprintf( terminationstr, "mxv_cbl%d", index( lastitem,_Blank_) );
				INDENT(indent)
				fprintf(out,"%s = ", terminationstr );
				relposition = 1;  /*  the following initializes the end variable  */
				itn = rbroth(lastitem);
				while(  itn!=nil()  &&  ! is( itn,_Pattern_) ){
					if(  is( itn,_Blank_)  )	relposition++;			
					itn = rbroth(itn);
				}
				if(  itn!=nil()  ){
					fprintf(out,"mxs_son(_c,0,%d,mxv_c%d);\n", -relposition, patix );
				} else {
					for( i=1; i<=relposition; i++ )  	fprintf(out,"mxs_lbroth(_c,0,");
					fprintf(out,"mxv_c%d", index( itn,_Pattern_) );
					for( i=1; i<=relposition; i++ )		fprintf(out,")");
					fprintf(out,";\n");
				}
			}
		}
		itn = son(1,itln);
		while(  ! eq(itn,lastastrk)  ){
			if(  is( itn,_Pattern_)  ){
				INDENT(indent)			
				fprintf(out,"mxv_c%d = ", index( itn,_Pattern_) );
				if(  is( patnpos(itn),_AbsPosition )  ){
					fprintf(out,"mxs_son(_c,0,%d,mxv_c%d);\n",
										subterm(1,patnpos(itn)), patix );
				} else {
					relposition =  subterm(1,patnpos(itn));
					for( i=1; i<=relposition; i++ )  	fprintf(out,"mxs_rbroth(_c,0,");
					fprintf(out,"mxv_c%d", index( next_left_pat(itn),_Pattern_) );
					for( i=1; i<=relposition; i++ )		fprintf(out,")");
					fprintf(out,";\n");
				}
			}
			itn =  rbroth(itn);
		}
		/*  the following generates the header for the loops; they have the form :    */
		/*  do{  "CHECK" ;  "INCREMENT subpattern variables"; }while( "TEST" )        */
		if(  numberofastrks(itln) > 1  ){ 
			itn = son(1,itln);
			while(  ! eq(itn,lastastrk)  ){
				if(  is( itn,_Asterisk_)  ){
					INDENT(indent); indent++;			
					fprintf(out,"do {\n" );
				}
				itn =  rbroth(itn);
			}
			sprintf( loopendvar, "goto CL%d", index( itln,_ItemList_) );
		}
	}
	/*  the following generates the loop body  */
	genc_cnd_pat( next_pat_for_codegen(fath(itln)), cndn, loopendvar, indent ); 


	/*  the following generates the increments of the loop variables and the loop test  */
	if(  numberofastrks(itln) > 1  ){
		INDENT(indent);
		fprintf(out,"CL%d: ;\n", index( itln,_ItemList_) );

		itn =  son(1,itln);
		while(  ! is( itn,_Asterisk_) ){
			itn = rbroth(itn);
		}
		firstasterisk =  itn;
		itn =  son(-1,itln);
		while(  ! is( itn,_Asterisk_) ){
			itn = lbroth(itn);
		}
		lastasterisk =  itn;
		do{
			itnforreinit =  itn;
			itn = lbroth(itn);
			while(  ! is( itn,_Asterisk_) ){
				if(  is( itn,_Pattern_)  ){
					INDENT(indent);
					fprintf(out,"mxv_c%d = mxs_rbroth(_c,0,mxv_c%d);\n",
						index( itn,_Pattern_), index( itn,_Pattern_) );
				}
				itn = lbroth(itn);
			}
			/* Code for reinitialization */
			while(  itnforreinit != lastasterisk  ){
				int  relposition, i;
				if(  is( itnforreinit,_Pattern_)  ){
					INDENT(indent)			
					fprintf(out,"mxv_c%d = ", index( itnforreinit,_Pattern_) );
					relposition =  subterm(1,patnpos(itnforreinit));
					for( i=1; i<=relposition; i++ )  	fprintf(out,"mxs_rbroth(_c,0,");
					fprintf(out,"mxv_c%d", index( next_left_pat(itnforreinit),_Pattern_) );
					for( i=1; i<=relposition; i++ )		fprintf(out,")");
					fprintf(out,";\n");
				}
				itnforreinit = rbroth(itnforreinit);
			}
			indent--; INDENT(indent);
			fprintf(out,"} while( mxv_c%d != %s );\n",
					index( next_left_pat(lastasterisk),_Pattern_), terminationstr );

		} while(  itn != firstasterisk  );
	}
}


static  void  genc_cnd_pat( ELEMENT patn, ELEMENT cndn, char* loopend, int indentp ){
	ELEMENT  itlv;
	long  patix;
	char loopendvar[20];
	int   indent =  indentp;

	if(  eq( patn, nil() )  ){
		genc_intres( cndn, indent);
		return;
	}

	patix  =  index( patn,_Pattern_);
	if(  is( fath(patn),_PatternList_)  ){
		strcpy( loopendvar, "continue" );
		INDENT(indent);
		fprintf(out,"for(mxv_cix%d=1;mxv_cix%d<=mxv_cbd%d;mxv_cix%d++){\n", 
			patix,patix,patix,patix);
		indent++; INDENT(indent);
		fprintf(out,"mxv_c%d = mxs_element(_c,0,mxv_cix%d,", patix, patix );
		prtsortconst( son(1,patn) );
		fprintf(out,");\n");
	} else {
		strcpy( loopendvar, loopend );
		if(  is( son(1,patn),_SortId_)  ){
			INDENT(indent);
			fprintf(out,"if( !mxs_is(_c,0,mxv_c%d,", patix );
			prtsortconst( son(1,patn) );
			fprintf(out,") ) %s;\n", loopendvar );
		}
	}
	if(  is( son(3,patn),_Name_)  ){
		INDENT(indent);
		fprintf(out,"%s_p%d = mxv_c%d;\n", IDSTR(son(3,patn)), index(patn,_Pattern_), patix );
	}
	itlv =  son(2,patn);
	if(  is( itlv,_ItemList_)  ){
		genc_cnd_itl( itlv, cndn, loopendvar, indent );
	} else {
		genc_cnd_pat( next_pat_for_codegen(patn), cndn, loopendvar, indent ); 
	}
	if(  is( fath(patn),_PatternList_)  ){
		indent--; INDENT(indent);
		fprintf(out,"}\n");
	}
}


static  void  genc_cnd_aux( ELEMENT tn ){
	ELEMENT nodev = son(1,tn);
	while(  nodev != nil()  ){
		genc_cnd_aux( nodev );
		nodev =  rbroth(nodev);
	}
	if(  is( tn,_Pattern_)  ){
		fprintf(out," mxv_c%d,", index(tn,_Pattern_) );
		if(  is( son(3,tn),_Name_)  ){
			fprintf(out," %s,", etoa(cgen_name(son(3,tn))));
		}
	}
	if(  is( tn,_Blank_) &&  is( lbroth(tn),_Asterisk_)  ){
		fprintf(out," mxv_cbl%d,", index(tn,_Blank_) );
	}
}


static  void  genc_att_aux( ELEMENT tn ){
	ELEMENT nodev = son(1,tn);
	while(  nodev != nil()  ){
		genc_att_aux( nodev );
		nodev =  rbroth(nodev);
	}
	if(  is( tn,_FuncAppl_)  &&  maybe_wait(tn)==true() ){
		fprintf(out," %s,", etoa(cgen_name(tn)) );
	}
	if(  is( tn,_LetExpr_) ) {
		fprintf(out," %s,", etoa(cgen_name(tn)) );
		fprintf(out," %s,", etoa(cgen_name(son(1,tn))) );
	}
	if(  is( tn,_IfExpr_) ) {
		fprintf(out," %s,", etoa(cgen_name(tn)) );

		if( is( son(1,tn),_PatternCaseList_) ) {
			int i,j, bound2,bound = numsons(son(1,tn));
			for(i=1;i<=bound;i++) {
				ELEMENT list = search_free_items( son(1,son(i,son(1,tn))) );
				bound2 = numsubterms(list);
				for(j=1;j<=bound2;j++) {
					ELEMENT NAME = son(3,subterm(j,list));
					if( is(NAME,_Name_) )
						fprintf(out," %s,",etoa(cgen_name(NAME)) );
				}
			}
		}
	}
}


static  void aux_prt_lokvar( ELEMENT selem, int count ){
	if( count==0 ) {
		fprintf(out,"ELEMENT %s",etoa(selem));
	} else {
		fprintf(out,", %s",etoa(selem));
	}
}

static  int genc_fct_aux( ELEMENT tn, int count ){
	ELEMENT nodev = son(1,tn);

	while(  nodev != nil()  ){
		count = genc_fct_aux( nodev, count );
		nodev = rbroth(nodev);
	}
	if(  is( tn,_FuncAppl_)  &&  maybe_wait(tn)==true() ){
		aux_prt_lokvar(cgen_name(tn), count++ );
	}
	if(  is( tn,_LetExpr_) ) {
		aux_prt_lokvar(cgen_name(tn), count++ );
		aux_prt_lokvar(cgen_name(son(1,tn)), count++ );
	}
	if(  is( tn,_IfExpr_) ) {
		aux_prt_lokvar(cgen_name(tn), count++ );

		if( is( son(1,tn),_PatternCaseList_) ) {
			int i,j, bound2,bound = numsons(son(1,tn));
			for(i=1;i<=bound;i++) {
				ELEMENT list = search_free_items( son(1,son(i,son(1,tn))) );
				bound2 = numsubterms(list);
				for(j=1;j<=bound2;j++) {
					ELEMENT NAME = son(3,subterm(j,list));
					if( is(NAME,_Name_) )
						aux_prt_lokvar(cgen_name(NAME), count++ );
				}
			}
		}
	}
return count;
}


static  int  genc_att_aux_case( ELEMENT tn, int count ){
	int i,bound;
	ELEMENT Z,nodev = son(1,tn);

	while(  nodev != nil()  ){
		count = genc_att_aux_case( nodev, count );
		nodev =  rbroth(nodev);
	}
	if(  is( tn,_FuncAppl_)  &&  maybe_wait(tn)==true() ){
		if( count==0 ) {
			fprintf(out,"\n\tswitch(state) {\n");
		}
		fprintf(out,"\t\tcase %d :\n", index(tn,_FuncAppl_) );

		Z = intres_collect(tn);

		bound = numsubterms(Z);
		for(i=1;i<=bound;i++) {
			fprintf(out,"\t\t\t%s = mxv_waitpar[%d];\n",etoa(cgen_name(subterm(i,Z))),i-1);
		}
		fprintf(out,"\t\t\t%s = mxv_attvalue;\n",etoa(cgen_name(tn)) );
		fprintf(out,"\t\t\tgoto Lz%d;\n",index(tn,_FuncAppl_));
		count++;
	}
return count;
}

void  prt_propagation( char *declname, int maxwaitpar, int eval_strategy ) {
	fprintf(out,"\n\t/* Code for propagation */\n");
	fprintf(out,"\tmxv_waitsq = mxw_%s[ mxv_ax ];\n",declname);
	fprintf(out,"\tmxw_%s[ mxv_ax ] = NULL;\n",declname);
	fprintf(out,"\twhile( mxv_waitsq != NULL ){\n");

	if( PEVAL(eval_strategy) ) {
		fprintf(out,"\t\t(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode");
		fprintf(out,", mxv_res, mxv_waitsq->state, ");
		if( maxwaitpar) fprintf(out,"&mxv_waitsq->intres_array[0]);\n");
		else		fprintf(out,"NULL);\n");
	} else {
		fprintf(out,"\t\t(*((EVALFCT1)mxv_waitsq->attevalfct))(mxv_waitsq->attnode);\n");
	}
	fprintf(out,"\t\tmxv_wsq    = mxv_waitsq;\n");
	fprintf(out,"\t\tmxv_waitsq = mxv_waitsq->rest;\n");
	fprintf(out,"\t\tfree(mxv_wsq);\n");
	fprintf(out,"\t}\n");
}


void  prt_globdecls( int maxwaitpar ){
	ELEMENT  decln;
	ELEMENT  GL, AIL;
	long     declx;
	char 	*declname;
	int      bound, bound2, bound3, i, j, strategy, parnum;

	fprintf(out,"/* The declaration for externals  */\n");

	bound =  number(_FuncDecl_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_FuncDecl_);
		if(  bef( endofpredef, before(decln) )  ){
			declname =  IDSTR( son(1,decln) );
			fprintf(out,"extern ELEMENT %s(", declname );
			parnum =  numsons(son(2,decln));
			if( parnum==0 ){
				fprintf(out,");\n#define mxs_%s(f,l)  %s()\n",declname,declname );
			} else {
				ELEMENT parsortn =  son(1,son(2,decln));
				fprintf(out,"ELEMENT");
				for( i=2 ; i <= parnum ; i++)  fprintf(out,",ELEMENT");
				fprintf(out,");\n");
				fprintf(out,"static ELEMENT mxs_%s(char *f,int l,", declname );
				fprintf(out,"ELEMENT p1");
				for( i=2 ; i <= parnum ; i++)  fprintf(out,",ELEMENT p%d",i);
				fprintf(out,"){\n\t");
				for( i=1 ; i <= parnum ; i++)  fprintf(out,"IFNIL(p%d) ",i);
				fprintf(out,"\n\t");
				for( i=1 ; i <= parnum ; i++){
					fprintf(out,"IS(p%d,", i);
					prtsortconst( parsortn );
					fprintf(out,",f,l,\"%s\",%d) ", declname,i );
					parsortn = rbroth( parsortn );
				}
				fprintf(out,"\n\treturn %s(p1", declname);
				for( i=2 ; i <= parnum ; i++)  fprintf(out,",p%d",i);
				fprintf(out,");\n}\n");
			}
		}
	}
	fprintf(out,"\n\n");
	bound =  number(_PredDecl_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_PredDecl_);
		if(  bef( endofpredef, before(decln) )  ){
			declname =  IDSTR( son(1,decln) );
			fprintf(out,"extern long %s(", declname );
			parnum =  numsons(son(2,decln));
			if( parnum==0 ){
				fprintf(out,");\n#define mxs_%s(f,l)  %s()\n",declname,declname );
			} else {
				ELEMENT parsortn =  son(1,son(2,decln));
				fprintf(out,"ELEMENT");
				for( i=2 ; i <= parnum ; i++)  fprintf(out,",ELEMENT");
				fprintf(out,");\n");
				fprintf(out,"static ELEMENT mxs_%s(char *f,int l,", declname );
				fprintf(out,"ELEMENT p1");
				for( i=2 ; i <= parnum ; i++)  fprintf(out,",ELEMENT p%d",i);
				fprintf(out,"){\n\t");
				for( i=1 ; i <= parnum ; i++){
					fprintf(out,"ISORNIL(p%d,", i);
					prtsortconst( parsortn );
					fprintf(out,",f,l,\"%s\",%d) ", declname,i );
					parsortn = rbroth( parsortn );
				}
				fprintf(out,"\n\treturn %s(p1", declname);
				for( i=2 ; i <= parnum ; i++)  fprintf(out,",p%d",i);
				fprintf(out,");\n}\n");
			}
		}
	}
	fprintf(out,"\n\n");
	bound =  number(_AttrDecl_) ;
	for( declx = 1; declx <= bound; declx++ ){
		ELEMENT parsortn;
		decln    =  element(declx,_AttrDecl_);
		declname =  IDSTR( son(1,decln) );
		parsortn =  son(1,son(2,decln));
		fprintf(out,"extern long init_%s( void );\n", declname );
		fprintf(out,"extern long free_%s( void );\n", declname );
		fprintf(out,"extern ELEMENT %s( ELEMENT );\n", declname );
		fprintf(out,"static ELEMENT mxs_%s(char *f,int l,ELEMENT p1){\n\t", declname );
		fprintf(out,"IFNIL(p1)  ",i);
		fprintf(out,"IS(p1,");
		prtsortconst( parsortn );
		fprintf(out,",f,l,\"%s\",1) ", declname );
		fprintf(out,"\n\treturn %s(p1);\n}\n", declname);
	}
	fprintf(out,"\n\n");
/*  print declarations for the defined functions  */
	bound =  number(_Function_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_Function_);
		declname =  IDSTR( son(1,decln) );
		fprintf(out,"ELEMENT  mxs_%s(char*,int", declname );
		parnum =  numsons(son(2,decln));
		if( parnum > 0 ){
			for( i=1 ; i <= parnum ; i++)  fprintf(out,",ELEMENT");
		}
		fprintf(out,"%s);\n" , FCT_ATT_WAITL(eval_strategy(decln)) ? ",EVALFCT,ELEMENT" : "" );
	}
	fprintf(out,"\n\n");
/*  print declarations for the defined predicates  */
	bound =  number(_Predicate_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_Predicate_);
		declname =  IDSTR( son(1,decln) );
		fprintf(out,"long  mxs_%s(char*,int", declname );
		parnum =  numsons(son(2,decln));
		if( parnum > 0 ){
			for( i=1 ; i <= parnum ; i++)  fprintf(out,",ELEMENT");
		}
		fprintf(out,");\n");
	}
	fprintf(out,"\n\n");

/*#tc  print internal access functions for the defined attributes  */
	bound =  number(_Attribute_) ;
	for( declx = 1; declx <= bound; declx++ ){
		ELEMENT parsortn;
		strategy = eval_strategy(element(declx,_Attribute_));

		decln    =  element(declx,_Attribute_);
		declname =  IDSTR( son(1,decln) );
		parsortn =  son(1,son(2,decln));
		fprintf(out,"static ELEMENT   *mxa_%s;\n", declname );

		if( WAITL( strategy ))
			fprintf(out,"static AttInstSq *mxw_%s;\n", declname );

		fprintf(out,"ELEMENT  mxs_%s( char *f, int l, ELEMENT p ){\n", declname );

		if(att_nilcheck[declx][1])	
		
 			fprintf(out,"\tIFNIL(p)");

		if(att_sortcheck[declx][1])
                {

  			fprintf(out," IS(p,");
			prtsortconst( parsortn );
			fprintf(out,",f,l,\"%s\",1)\n", declname);

		}
		fprintf(out,"\treturn mxa_%s[mxs_index(_c,0,p,", declname);
		prtsortconst( parsortn );
		fprintf(out,")];\n}\n" );
	}
	fprintf(out,"\n");

/*#tc  print external access functions for the defined attributes  */
	bound =  number(_Attribute_) ;
	for( declx = 1; declx <= bound; declx++ ){
		ELEMENT parsortn;
		strategy = eval_strategy(element(declx,_Attribute_));

		decln    =  element(declx,_Attribute_);
		declname =  IDSTR( son(1,decln) );
		parsortn =  son(1,son(2,decln));
		/*  fprintf(out,"static ELEMENT   *mxa_%s;\n", declname ); 
		    not needed as already declared with internal attr_access */

		if( WAITL( strategy ))
			fprintf(out,"static AttInstSq *mxw_%s;\n", declname );

		fprintf(out,"ELEMENT  mxx_%s( char *f, int l, ELEMENT p ){\n", declname );
		fprintf(out,"\tIFNIL(p)");
  		fprintf(out," IS(p,");
		prtsortconst( parsortn );
		fprintf(out,",f,l,\"%s\",1)\n", declname);
		fprintf(out,"\treturn mxa_%s[mxs_index(_c,0,p,", declname);
		prtsortconst( parsortn );
		fprintf(out,")];\n}\n" );
	}
	fprintf(out,"\n");

	fprintf(out,"\n\n");

/*#tc  print internal definitions for the defined functions  */
	bound =  number(_Function_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_Function_);
		declname =  IDSTR( son(1,decln) );
		fprintf(out,"ELEMENT  mxs_%s(char *f, int l", declname );
		parnum =  numsons(son(2,decln));
		if( parnum > 0 ){
			ELEMENT parnmln =  son(3,decln);
			for( i=1 ; i <= parnum ; i++)
				fprintf(out,",ELEMENT %s", IDSTR(son(i,parnmln)) );
		}

		if( FCT_ATT_WAITL(eval_strategy(decln)) ) {
			fprintf(out,",EVALFCT mxw_evf, ELEMENT mxw_par){\n");
			if( genc_fct_aux( son(5,decln), 0 ) == 0 ) {
				fprintf(out,"ELEMENT mxv_ax;\n");
			} else {
				fprintf(out,", mxv_ax;\n");
			}
		} else {
			fprintf(out,"){\n");
			if( genc_fct_aux( son(5,decln), 0 ) != 0 ) {
				fprintf(out,";\n");
			}
		}

		if( parnum > 0 ){
			ELEMENT parname =  son(1,son(3,decln));
			do{
				if(fct_nilcheck[declx][par_pos(parname,1)])

					fprintf(out," IFNIL(%s)", IDSTR(parname) );

				parname= rbroth( parname );

			} while(  parname != nil()  );
			fprintf(out,"\n");
		}
		if( parnum > 0 ){
			ELEMENT parname =  son(1,son(3,decln));
			ELEMENT parsort =  son(1,son(2,decln));
			i = 1;
			do{
				if(fct_sortcheck[declx][par_pos(parname,1)]){
					fprintf(out," IS(%s,", IDSTR(parname) );
					prtsortconst( parsort );
					fprintf(out,",f,l,\"%s\",%d)", declname, i++ );
				}

				parname= rbroth( parname );
				parsort= rbroth( parsort );
			} while(  parname != nil()  );
			fprintf(out,"\n");
		}
		genc_intres(decln,1);

		fprintf(out,"}\n\n");
	}
	fprintf(out,"\n\n");


/*#tc  print external definitions for the defined functions  */
	bound =  number(_Function_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_Function_);
		declname =  IDSTR( son(1,decln) );
		fprintf(out,"ELEMENT  mxx_%s(char *f, int l", declname );
		parnum =  numsons(son(2,decln));
		if( parnum > 0 ){
			ELEMENT parnmln =  son(3,decln);
			for( i=1 ; i <= parnum ; i++)
				fprintf(out,",ELEMENT %s", IDSTR(son(i,parnmln)) );
		}

		if( FCT_ATT_WAITL(eval_strategy(decln)) ) {
			fprintf(out,",EVALFCT mxw_evf, ELEMENT mxw_par){\n");
			if( genc_fct_aux( son(5,decln), 0 ) == 0 ) {
				fprintf(out,"ELEMENT mxv_ax;\n");
			} else {
				fprintf(out,", mxv_ax;\n");
			}
		} else {
			fprintf(out,"){\n");
			if( genc_fct_aux( son(5,decln), 0 ) != 0 ) {
				fprintf(out,";\n");
			}
		}

		if( parnum > 0 ){
			ELEMENT parname =  son(1,son(3,decln));
			do{
				fprintf(out," IFNIL(%s)", IDSTR(parname) );
				parname= rbroth( parname );
			} while(  parname != nil()  );
			fprintf(out,"\n");
		}
		if( parnum > 0 ){
			ELEMENT parname =  son(1,son(3,decln));
			ELEMENT parsort =  son(1,son(2,decln));
			i = 1;
			do{
				fprintf(out," IS(%s,", IDSTR(parname) );
				prtsortconst( parsort );
				fprintf(out,",f,l,\"%s\",%d)", declname, i++ );
				parname= rbroth( parname );
				parsort= rbroth( parsort );
			} while(  parname != nil()  );
			fprintf(out,"\n");
		}
		genc_intres(decln,1);

		fprintf(out,"}\n\n");
	}
	fprintf(out,"\n\n");

/*  print bodies for the defined predicates  */
	bound =  number(_Predicate_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_Predicate_);
		declname =  IDSTR( son(1,decln) );
		fprintf(out,"long  mxs_%s(char *f, int l", declname );
		parnum =  numsons(son(2,decln));
		if( parnum > 0 ){
			ELEMENT parnmln =  son(3,decln);
			for( i=1 ; i <= parnum ; i++)
				fprintf(out,",ELEMENT %s", IDSTR(son(i,parnmln)) );
		}
		fprintf(out,"){\n");

		if( genc_fct_aux( son(4,decln), 0 ) != 0 ) {
			fprintf(out,";\n");
		}

		if( parnum > 0 ){
			ELEMENT parname =  son(1,son(3,decln));
			ELEMENT parsort =  son(1,son(2,decln));
			i = 1;
			do{
				fprintf(out," ISORNIL(%s,", IDSTR(parname) );
				prtsortconst( parsort );
				fprintf(out,",f,l,\"%s\",%d)", declname, i++ );
				parname= rbroth( parname );
				parsort= rbroth( parsort );
			} while(  parname != nil()  );
			fprintf(out,"\n");
		}
		genc_intres(decln,1);
		fprintf(out,"}\n\n");
	}
	fprintf(out,"\n\n");
/*  print evaluation bodies for the defined attributes  */

	bound =  number(_FuAtList_);
	for( declx = 1; declx <= bound; declx++ ) {

		GL = attr_list_info(element(declx,_FuAtList_));
		bound2 = numsubterms(GL);
		for(i=1;i<=bound2;i++)  {   /* loop for the evaluation groups */
			AIL = subterm(i,GL);
			bound3 = numsubterms(AIL);

			for(j=1;j<=bound3;j++)
				{
				decln    =  subterm(j,AIL);
				if(!is(decln,_Attribute_)) continue;

				strategy = eval_strategy(decln);

				declname = IDSTR(son(1,decln));

				fprintf(out,"static  void  mxe_%s( ", declname );
				fprintf(out,"ELEMENT %s",IDSTR(son(1,son(3,decln))) );

				if( WAITL(strategy) ) {
				  if( PEVAL(strategy) ) {
					fprintf(out,", ELEMENT mxv_attvalue, int state, ELEMENT *mxv_waitpar ){\n\tELEMENT ");
					genc_att_aux( son(5,decln) );
					fprintf(out,"\n\t\tmxv_ax, mxv_res, mxv_par = %s;\n", IDSTR(son(1,son(3,decln))));
					fprintf(out,"\tAttInstSq mxv_waitsq, mxv_wsq;\n");
					if( genc_att_aux_case(son(5,decln),0) ) fprintf(out,"\t}\n");
				  } else {
					fprintf(out," ){\n\tELEMENT ");
					genc_att_aux( son(5,decln) );
					fprintf(out,"\n\t\tmxv_ax, mxv_par = %s;\n", IDSTR(son(1,son(3,decln))));
					fprintf(out,"\tAttInstSq mxv_waitsq, mxv_wsq;\n");
				  }
				  genc_intres(decln,1);
				  prt_propagation(declname,maxwaitpar,strategy);

				} else {
					fprintf(out," ){\n\tELEMENT ");
					genc_att_aux( son(5,decln) );
					fprintf(out,"\n\t\tmxv_ax, mxv_par = %s;\n", IDSTR(son(1,son(3,decln))));
					genc_intres(decln,1);
				}

				fprintf(out,"}\n\n");
			} /* endfor bound3 */
		} /* endfor bound2 */
	}
	fprintf(out,"\n\n");

/*  print evaluation procedures for conditions  */
	bound =  number(_Condition_) ;
	for( declx = 1; declx <= bound; declx++ ){
		ELEMENT  patn;
		long  patix, patll;
		decln    =  element(declx,_Condition_);

		fprintf(out,"static  long  mxc_%d( void ){\n", declx );

		fprintf(out,"\tELEMENT ");
		genc_cnd_aux( son(1,decln) );
		genc_att_aux( son(2,decln) );
		genc_att_aux( son(3,decln) );
		fprintf(out," mxv_c0 = 1L;\n");


		patll =  numsons( son(1,decln) );
		if(  patll > 0  ){
			patn = son( 1, son(1,decln) );
			patix =  index( patn,_Pattern_);
			fprintf(out,"\tlong mxv_cix%d,mxv_cbd%d", patix, patix );
			patn = rbroth(patn);
			while(  patn != nil()  ){
				patix =  index( patn,_Pattern_);
				fprintf(out,", mxv_cix%d,mxv_cbd%d", patix, patix );
				patn = rbroth(patn);
			}
			fprintf(out,";\n");
			patn = son( 1, son(1,decln) );
			do{
				patix =  index( patn,_Pattern_);
				fprintf(out,"\tmxv_cbd%d = mxs_number(_c,0,", patix );
				prtsortconst( son(1,patn) );
				fprintf(out,");\n");
				patn = rbroth(patn);
			} while(  patn != nil()  );
		}

		genc_cnd_pat( son(1,son(1,decln) ), decln, "", 1 );
		fprintf(out,"\n\treturn mxv_c0;\n}\n\n");
	}
	fprintf(out,"\n");
}


static void reserv_attvalue( ELEMENT AIL, int bound ) {
	char *declname;
	int j, wait, strategy;
	ELEMENT decln;

	for(j=1;j<=bound;j++) {
		decln = subterm(j,AIL);
		if(!is(decln,_Attribute_)) continue;

		strategy = eval_strategy(decln);
		wait     = WAITL(strategy);
		declname = IDSTR(son(1,decln));

		fprintf(out,"\tmxa_%s = (ELEMENT*)   calloc( mxn_%s+1, sizeof(ELEMENT) );\n",declname,declname );
		if( wait )  fprintf(out,"\tmxw_%s = (AttInstSq*) calloc( mxn_%s+1, sizeof(AttInstSq) );\n",declname,declname );
		fprintf(out,"\tif( mxa_%s==0L",declname);
		if( wait ) fprintf(out," || mxw_%s==0L",declname);
		fprintf(out," ){\n");

		fprintf(out,"\t\tfprintf(stderr,\"\\n***** Error: Cannot allocate attribute %s\\n\");\n",declname );
		fprintf(out,"\t\texit( EXIT_FAILURE );\n\t}\n");
		if( wait ) fprintf(out,"\tfor( ix=1; ix<=mxn_%s; ix++ )  mxa_%s[ix] = MAXUNDEF;\n", declname, declname );
	}
}


static ELEMENT Defidnode_insert( ELEMENT L, ELEMENT n ) {
	int pcd = prodcd(fath(n));

	if( pcd==POINT_SORTCD || pcd==NIL_SORTCD ) return L;
	if( L == DefIdNodeList()) return appfront(n,DefIdNodeList());
	if( subterm(1,L) < n )   return appfront(subterm(1,L),Defidnode_insert(back(L),n));
	if( subterm(1,L) > n )   return appfront(n,L);

return L;
}


static ELEMENT Defidnodelist_union( ELEMENT L1, ELEMENT L2 ) {
	if( L1==AllNodes() || L2==AllNodes() ) return AllNodes();
	if( L1 == DefIdNodeList() ) return L2;
return Defidnodelist_union( back(L1), Defidnode_insert( L2, subterm(1,L1)) );
}


void prt_evalset( ELEMENT AFL ) {
	int i, stra, setsize = numsubterms(AFL);
	ELEMENT N;
	char *attname;

	if( setsize > 1 ) {
		fprintf(out,"\t\t{ /* start evaluation with waitlist */\n");
		for(i=1;i<=setsize;i++) {
			N = subterm(i,AFL);
			if( is(N,_Attribute_)) {
				fprintf(out,"\t\t\tlong mxs_ind%d = mxs_index(_c,0,mxz_heap[1].node,",i);
				prtsortconst( son(1,son(2,N)) );
				fprintf(out,");\n");
			}
		}
		for(i=1;i<=setsize;i++) {
			N = subterm(i,AFL);
			if( is(N,_Attribute_)) {
				fprintf(out,"\t\t\tmxa_%s[mxs_ind%d] = MAXUNDEF;\n",IDSTR(son(1,N)),i);
			}
		}
	}

	for(i=1;i<=setsize;i++) {
		N = subterm(i,AFL);
		if( is(N,_Attribute_)) {
			stra = eval_strategy(N);
			fprintf(out,"\t\t\tmxe_%s(mxz_heap[1].node",IDSTR(son(1,N)));
			if( PEVAL(stra) ) fprintf(out,",0,0,NULL");
			fprintf(out,");\n");
		}
	}
	if( setsize > 1 ) {
		for(i=1;i<=setsize;i++) {
			N = subterm(i,AFL);
			attname = IDSTR(son(1,N));

			if( !is(N,_Attribute_)) continue;

#ifdef CYCLES_ALLOWED
			fprintf(out,"\t\t\tif( mxa_%s[mxs_ind%d] == MAXUNDEF) mxa_%s[mxs_ind%d] = mxs_nil(_c,0);\n",
				attname,i,attname,i);
#else
			fprintf(out,"\t\t\tif( mxa_%s[mxs_ind%d]==MAXUNDEF ){\n", attname, i );
			fprintf(out,"\t\t\t\tfprintf(stderr,\"\\n***** Error: Definition of attribute %s is cyclic\\n\");\n", attname );
			fprintf(out,"\t\t\t\treturn 0L;\n" );
			fprintf(out,"\t\t\t}\n" );
#endif
		}
		fprintf(out,"\t\t}\n");
	}
}

static long mxz_elem( ELEMENT BSI, ELEMENT PL ) {
	int bound,i;

	if( PL ==AllNodes() ) return P_TRUE;
	if( BSI==AllNodes() ) return P_FALSE;

	bound = numsubterms( PL );
	for(i=1;i<=bound;i++)  if( BSI == subterm(i,PL) ) return 1;

	return P_FALSE;
}


void prt_init_heap( ELEMENT PL, int nodeS, int offset, int gesanz, char *dirstr, char *aftbefstr ) {
	int j,bound;
	int siftlimit = gesanz>>1;

	if( nodeS ) {
		fprintf(out,"\tfirstnode_%s_%s(%d);",dirstr,aftbefstr,1+offset);
		if(1+offset <= siftlimit) fprintf(out,"\tmxz_sift_%s(%d,%d);\n",dirstr,1+offset,gesanz);
		else fprintf(out,"\n");
	} else {
		bound = numsubterms(PL);
		for(j=bound;j>=1;j--) {
			fprintf(out,"\tfirst_%s_%s(_%s_,%d);",dirstr,aftbefstr,IDSTR(subterm(j,PL)),j+offset);
			if(j+offset <= siftlimit) fprintf(out,"\tmxz_sift_%s(%d,%d);\n",dirstr,j+offset,gesanz);
			else fprintf(out,"\n");
		}
	}
}


void prt_finegroupeval( ELEMENT AIL, ELEMENT sortid, int aftbef ) {
	ELEMENT AFL;
	int i,fnr,bound;

	AFL = FuAtNodeList();
	fnr = 1;
	bound = numsubterms(AIL);

	for(i=1;i<=bound;i++) {
		ELEMENT N = subterm(i,AIL);

		if( eval_aftbef(N)==aftbef && mxz_elem(sortid,eval_sortlist(N))  ) {

			if( eval_finegroup(N) > fnr ) {
				if( AFL != FuAtNodeList() ) prt_evalset( AFL );
				AFL = FuAtNodeList();
				fnr = eval_finegroup(N);
			}
			AFL = appback( AFL, subterm(i,AIL) );
		}
	}
	if( AFL != FuAtNodeList() ) prt_evalset( AFL );
}



void prt_choose_heap( ELEMENT AIL, ELEMENT PL, int nodeS, int offset, int gesanz, char *dirstr, char *aftbefstr, int aftbef ) {
	int j, bound;

	if( nodeS ) {
		if( gesanz != 1) fprintf(out,"\tcase %d:\n",1+offset);

		bound=numsubterms(PL);
		if( bound ) fprintf(out,"\t\tswitch(sort(mxz_heap[1].node)) {\n");
		for(j=1;j<=bound;j++) {
			fprintf(out,"\t\tcase _%s_:\n",IDSTR(subterm(j,PL)));
			prt_finegroupeval( AIL, subterm(j,PL), aftbef );
			fprintf(out,"\t\tbreak;\n");
		}
		if( bound ) fprintf(out,"\t\tdefault :\n");
		prt_finegroupeval( AIL, AllNodes(), aftbef );
		if( bound ) fprintf(out,"\t\t}\n");

		fprintf(out,"\tnextnode_%s_%s();",dirstr,aftbefstr);
		if( gesanz != 1) fprintf(out,"\tmxz_sift_%s(1,%d);\tbreak;",dirstr,gesanz);
		fprintf(out,"\n");
	} else {
		bound = numsubterms(PL);
		for(j=1;j<=bound;j++) {
			if( gesanz != 1) fprintf(out,"\tcase %d:\n",j+offset);

			prt_finegroupeval( AIL, subterm(j,PL), aftbef );

			fprintf(out,"\t\tnext_%s_%s(_%s_,%d);",dirstr,aftbefstr,IDSTR(subterm(j,PL)),j+offset);
			if( gesanz != 1) fprintf(out,"\tmxz_sift_%s(1,%d);\tbreak;",dirstr,gesanz);
			fprintf(out,"\n");
		}
	}
}

void prt_groupeval( ELEMENT AIL, int strategy ) {
	ELEMENT PLA, PLB;
	int i, bound, gesanz, befanz, nodeA, nodeB, attcount;
	char *dirstr = FORWARD(strategy) ? "forw" : "backw";

	PLA = PLB = DefIdNodeList();
	bound = numsubterms( AIL );

	nodeA = nodeB = 0;

	attcount = 0;
	for(i=1;i<=bound;i++) {
		if(is(subterm(i,AIL),_Attribute_)) attcount++;
	}
	if(attcount==0) return;

	for(i=1;i<=bound;i++) {
		ELEMENT N = subterm(i,AIL);
		if(!is(N,_Attribute_)) continue;

		if(eval_aftbef(N)==BEFORE) {
			if( eval_sortlist(N)==AllNodes() ) nodeB = 1;
			else PLB = Defidnodelist_union( eval_sortlist(N), PLB);
		} else {
			if( eval_sortlist(N)==AllNodes() ) nodeA = 1;
			else PLA = Defidnodelist_union( eval_sortlist(N), PLA );
		}

	}

	befanz =  ( nodeB ) ? 1 : numsubterms(PLB);
	gesanz = (( nodeA ) ? 1 : numsubterms(PLA)) + befanz;

	prt_init_heap( PLA, nodeA, befanz, gesanz, dirstr, "aft" );
	prt_init_heap( PLB, nodeB, 0,      gesanz, dirstr, "bef" );

	fprintf(out,"\twhile(mxz_heap[1].point!=mxs_nil(_c,0)) {\n");
	if( gesanz != 1) fprintf(out,"\tswitch(mxz_heap[1].ind) {\n");

	prt_choose_heap( AIL, PLB, nodeB, 0,      gesanz, dirstr, "bef", BEFORE );
	prt_choose_heap( AIL, PLA, nodeA, befanz, gesanz, dirstr, "aft", AFTER );

	if( gesanz != 1) fprintf(out,"\t}} /* endswitch, endwhile */\n\n");
	else fprintf(out,"\t} /* endwhile */\n\n");
}


void  prt_strucconstr( ELEMENT stacksortlist ){
	ELEMENT locdecln, GL, AIL;
	int strategy;
	long  i, j, bound, bound2;
	ELEMENT decln;
	long  declx;
	char *declname;

	fprintf(out,"long  mxi_atteval( void ){\n");
	fprintf(out,"\tlong mxv_correct = 1;\n");
	fprintf(out,"\tlong ix;\n");

	bound =  number(_Attribute_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_Attribute_);
		declname =  IDSTR( son(1,decln) );
		fprintf(out,"\tlong mxn_%s = mxs_number(_c,0,", declname );
		prtsortconst( son(1,son(2,decln)) );
		fprintf(out,");\n");
	}

	if( stacksortlist != DefIdNodeList() ) {

		fprintf(out,"\tlong mxn, mxz_stacksize = 0;\n\n");
		fprintf(out,"\textern SORTCDT mxi_list_sortcd_lb;\n\n");
		fprintf(out,"\trev_element_tab = (ELEMENT **)  calloc((1-mxi_list_sortcd_lb),sizeof(ELEMENT *));\n");
		fprintf(out,"\tif( rev_element_tab == 0L ){\n");
		fprintf(out,"\t\tfprintf(stderr,\"\\n***** Error: Cannot allocate rev_element_tab table \\n\");\n");
		fprintf(out,"\t\texit( EXIT_FAILURE );\n");
		fprintf(out,"\t}\n");
		fprintf(out,"\tfor(ix=0; ix <= -mxi_list_sortcd_lb ;ix++) rev_element_tab[ix] = NULL;\n\n");

		bound = numsubterms( stacksortlist );
		for(i=1;i<=bound;i++) {
			char *sort = IDSTR(subterm(i,stacksortlist));
			fprintf(out,"\tmxn = mxs_number(_c,0,_%s_);\n",sort);
			fprintf(out,"\tif(mxn > mxz_stacksize) mxz_stacksize = mxn;\n");
		}

		fprintf(out,"\n\tenum_stack = (ELEMENT *)calloc( 1+mxz_stacksize, sizeof(ELEMENT));\n");
		fprintf(out,"\tif(enum_stack == 0L) {\n");
		fprintf(out,"\t\tfprintf(stderr,\"\\n***** Error: Cannot allocate Stack \\n\");\n");
		fprintf(out,"\t\texit( EXIT_FAILURE );\n");
		fprintf(out,"\t}\n");

		for(i=1;i<=bound;i++) {
			char *sort = IDSTR(subterm(i,stacksortlist));
			fprintf(out,"\tmxz_init_revindex(_%s_);\n",sort);
		}

		fprintf(out,"\tfree(enum_stack);\n");

	} /* endif( stack_needed ) */

	fprintf(out,"\n\tmxz_firstpoint = mxs_before(_c,0,mxs_root(_c,0));\n");
	fprintf(out,"\tmxz_lastpoint = mxs_after(_c,0,mxs_root(_c,0));\n\n");

	locdecln = son( 1, son( 3, element(1,_Structure_) ));
	while( !eq(locdecln,nil())  ){
		switch( sort(locdecln) ){
		case _PredList_:
		case _PredDecl_:
		case _FuncDecl_:
			break;
		case _FuAtList_:

		fprintf(out,"\t/*** Evaluation of FuAtList ind=%d */\n",index(locdecln,_FuAtList_));
		GL = attr_list_info(locdecln);
		bound = numsubterms(GL);
		for(i=1;i<=bound;i++) {
		    AIL = subterm(i,GL);

		    strategy = eval_strategy(subterm(1,AIL));

		    fprintf(out,"\t/*** Evaluation of group %d strategy %d */\n",i,strategy);
		    bound2 = numsubterms(AIL);
		    reserv_attvalue( AIL, bound2 );

		    switch( STRAT(strategy) ) {
		    case WAITSTR : /* evaluation with waitlist */
			for(j=1;j<=bound2;j++) {
				decln     = subterm(j,AIL);
				if(!is(decln,_Attribute_)) continue;
				declname =  IDSTR(son(1,decln));

				fprintf(out,"\tfor( ix=1; ix<=mxn_%s; ix++ )",declname);
				fprintf(out,"  mxe_%s( mxs_element(_c,0,ix,",declname );
				prtsortconst( son(1,son(2,decln)) );

				if( PEVAL(strategy) )
					fprintf(out,"),0,0,NULL);\n");
				else	fprintf(out,"));\n");


			}
			for(j=1;j<=bound2;j++) {
				decln     = subterm(j,AIL);
				if(!is(decln,_Attribute_)) continue;
				declname =  IDSTR(son(1,subterm(j,AIL)));

				fprintf(out,"\tfor( ix=1; ix<=mxn_%s; ix++ ){\n", declname );
#ifdef CYCLES_ALLOWED
				fprintf(out,"\t\tif( mxa_%s[ ix ] == MAXUNDEF )  mxa_%s[ix] = mxs_nil(_c,0);\n\t}\n",declname, declname );
#else
				fprintf(out,"\t\tif( mxa_%s[ix]==MAXUNDEF ){\n", declname );
				fprintf(out,"\t\t\tfprintf(stderr,\"\\n***** Error: Definition of attribute %s is cyclic\\n\");\n", declname );
				fprintf(out,"\t\t\treturn 0L;\n" );
				fprintf(out,"\t\t}\n\t}\n" );
#endif
				fprintf(out,"\tfree(mxw_%s);\n", declname );
			}
		    break;

		    case HEAPSTR: /* Evaluation with Heap */
			prt_groupeval( AIL, strategy );
		    break;

		    case ENUMSTR: /* Direct enumeration */
			decln     = subterm(1,AIL);
			if(is(decln,_Attribute_)) {
				declname =  IDSTR(son(1,decln));

				if(FORWARD(strategy))	fprintf(out,"\tfor( ix=1; ix<=mxn_%s; ix++ )  ",declname);
				else			fprintf(out,"\tfor( ix=mxn_%s; ix>=1; ix-- )  ",declname);

				if(eval_aftbef(decln)==2)	fprintf(out,"mxe_%s( mxs_element(_c,0,ix,",declname );
				else				fprintf(out,"mxe_%s( rev_element(ix,",declname );

				prtsortconst( son(1,son(2,decln)) );
				fprintf(out,") );\n" );
			}
		    break;
		    } /* end switch */
		} /* End of loop for the groups */

		break;
		case _AttrDecl_:{
			fprintf(out,"\n\tmxv_correct = init_%s() && mxv_correct;\n\n", IDSTR(son(1,locdecln))  );
			fprintf(out,"\n\tif( ! mxv_correct ) return 0L;\n\n" );
			break;
		}
		case _CondList_:
			decln     = son(1,locdecln );
			while( decln != nil()  ){
				fprintf(out,"\n\tmxv_correct = mxc_%d() && mxv_correct;", index( decln,_Condition_) );
				decln =  rbroth(decln);
			}
			fprintf(out,"\n\tif( ! mxv_correct ) return 0L;\n\n" );
			break;
		case _DynFunc_:
		case _DynSemInput_:
			break;
		default:
			fprintf(stderr,"\n**** Error: in prt_strucconstr\n"); break;
		}
		locdecln = rbroth(locdecln);
	}
	fprintf(out,"\treturn mxv_correct;\n}\n\n" );
}


static  long  init_endofpredef( void ){
	ELEMENT  lastpredecl =  fath( subterm( 1, idtodecls(stoid(atoe("number"))) ) );
 	endofpredef = after( lastpredecl );
	return 1;
}

extern  void  header_gen( FILE*, char*, int );


static ELEMENT intlist_insert( ELEMENT L, int n ) {
	if( L == IntList())    return appfront(n,IntList());
	if( subterm(1,L) < n ) return appfront(subterm(1,L),intlist_insert(back(L),n));
	if( subterm(1,L) > n ) return appfront(n,L);

return L;
}


void  source_gen( FILE *outp, char *filenm ){
	int i, j, k, bound, bound2, bound3, max_heapsize, maxwaitpar, comp;
	ELEMENT GL, ANL, waitparnumlist, stacksortlist;

	out = outp;
	filename = filenm;

	header_gen( out, "mxs_", 0 );
	tupelsortcdlb =  MIN_PREDECL_SORTCD - number(_TupelProd_);
	listsortcdlb  =  tupelsortcdlb - number(_ListProd_);
	classsortcdlb =  listsortcdlb - number(_ClassProd_);
	init_endofpredef();

	waitparnumlist = intlist_insert(IntList(),0);

	bound = number(_FuncAppl_);
	for(i=1;i<=bound;i++) {
		ELEMENT FA = element(i,_FuncAppl_);
		ELEMENT EA = encl_fctoratt(FA);
		int strategy = eval_strategy(EA);

		if( maybe_wait(FA)==true() && is( EA,_FctOrAtt_)
			&& !FCT_ATT_MIX(strategy) && WAITL(strategy) ) {
			waitparnumlist = intlist_insert(waitparnumlist,numsubterms(intres_collect(FA)));
		}
	}
	maxwaitpar = subterm(-1,waitparnumlist);

	prt_stdpart( maxwaitpar );
	prt_listtoelemtab();
	prt_classtosorttab();
	init_supsorts();
	prt_supsorttab();
	prt_indexingtabs();

	fprintf(out,"static ELEMENT mxz_firstpoint, mxz_lastpoint;\n");

	/*** Computation of the heapsize ***/

	max_heapsize = 0;

	bound2 = number(_FuAtList_);
	for(k=1;k<=bound2;k++) {
		GL = attr_list_info(element(k,_FuAtList_));
		bound = numsubterms(GL);
		for(i=1;i<=bound;i++) {
			ANL = subterm(i,GL);
			if( STRAT(eval_strategy(subterm(1,ANL))) == HEAPSTR ) {
				ELEMENT PLA=DefIdNodeList(), PLB = DefIdNodeList();
				int nodeA=0, nodeB=0;

				bound3 = numsubterms(ANL);
				for(j=1;j<=bound3;j++) {
					ELEMENT N = subterm(j,ANL);
					if(eval_aftbef(N)==BEFORE) {
						if( eval_sortlist(N)==AllNodes() ) nodeB = 1;
						else PLB = Defidnodelist_union( eval_sortlist(N), PLB);
					} else {
						if( eval_sortlist(N)==AllNodes() ) nodeA = 1;
						else PLA = Defidnodelist_union( eval_sortlist(N), PLA );
					}
				}
				comp = (( nodeA ) ? 1 : numsubterms(PLA)) + (( nodeB ) ? 1 : numsubterms(PLB));
				if( comp > max_heapsize ) max_heapsize = comp;
			}
		}
  	}
	if(max_heapsize==0)	prt_heap_fcts( out, 2 );
	else			prt_heap_fcts( out, max_heapsize+1 );

	/*** For which sorts is a stack needed ? ***/

	stacksortlist = DefIdNodeList();
	bound = number(_Attribute_);
	for(i=1;i<=bound;i++) {
		ELEMENT N = element(i,_Attribute_);

		if( eval_aftbef(N) == AFTER && is( eval_sortlist(N),_DefIdNodeList ) ) {
			stacksortlist = Defidnodelist_union( eval_sortlist(N), stacksortlist );
		}
	}
	if( stacksortlist != DefIdNodeList() ) prt_stack_fcts( out );

	prt_globdecls( maxwaitpar );

	if(  number(_Structure_) == 1 )	{
		prt_strucconstr( stacksortlist );
	} else {
		fprintf(out,"long  mxi_atteval( void ){ return 1L; }\n");
	}
	fprintf(out,"\n");
}

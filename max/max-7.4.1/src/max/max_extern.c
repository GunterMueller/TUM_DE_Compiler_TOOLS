#include <stdio.h>
#include <stdlib.h>

#include "max_spec.h"
#include "max_global.h"

#define  P_TRUE  1 
#define  P_FALSE 0

#define  WAITSTR     0
#define  HEAPSTR     1
#define  ENUMSTR     2

#define  FCT_ATT_MIX(N)  ((eval_strategy(N)&16)==16)

extern void mxi_prterrm(char*,int,char*,char*);
static char mxi_errmstr[] = "0th parameter is of wrong sort";
static void comp_errm(char *filenm, int ln, char *fctnm, int parno){
	mxi_errmstr[0] = (char)(parno)+'0';
	mxi_prterrm(filenm,ln,fctnm,mxi_errmstr);
}

#define IFNIL(e) {if(e==NIL) return NIL;}
#define IS(e,t,f,l,fct,i)  {if(!mxi_is(f,l,e,t)){comp_errm(f,l,fct,i);return NIL;}}


/* add, sub, neg are strict with respect to nil() */
  

ELEMENT add( ELEMENT o1, ELEMENT o2 ){	
           if ( o1 == nil() || o2 == nil() ) return nil();
           else return itoe(o1+o2);
}
ELEMENT sub( ELEMENT o1, ELEMENT o2 ){
           if ( o1 == nil() || o2 == nil() ) return nil();
           else	return itoe(o1-o2);
}
ELEMENT neg( ELEMENT o1 ){
           if ( o1 == nil() ) return nil();
           else		      return itoe( -o1 );
}



long    lt(  ELEMENT o1, ELEMENT o2 ){
           return (long)(o1<o2);
}
long    le(  ELEMENT o1, ELEMENT o2 ){
	   return (long)(o1<=o2);
}


ELEMENT s( ELEMENT inp ){
	char st[20];
	sprintf(st,"%d", term(inp) );
	return  atoe(st);
}

/******************************************************************/
/*  ATT  idtodecls ( Ident ) DefIdNodeList                        */
/*  yields for each Ident the list of the corresponding DefId@'s  */
static  ELEMENT *decltab;          /*=-=   Ident  -->  DefIdNodeList   =-=*/

long  init_idtodecls( void ){
	ELEMENT  defidn, idv;
	long	 defidx, idx, bound; 

	decltab  = (ELEMENT*) calloc( number(_Ident)+1, sizeof(ELEMENT) );
	if( decltab == 0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate idtodecl table \n");
		exit( EXIT_FAILURE );
	}
	bound =  number(_DefId_);
	for( defidx = 1; defidx <= bound ; defidx++ ){
		defidn =  element(defidx,_DefId_);
		idv =  term( son(1,defidn) );
		idx =  index(idv,_Ident);
		if( decltab[ idx ] ){
			decltab[ idx ] =  appback( decltab[idx], defidn ) ;
		} else {
			decltab[ idx ] =  appback( DefIdNodeList(), defidn ) ;
		}
	}
	return 1L;
}

long  free_idtodecls( void ){
	return 1L;
}

ELEMENT idtodecls( ELEMENT idv ){
	IFNIL( idv ) IS(idv,_Ident,__FILE__,__LINE__,"idtodecls",1)
	return  decltab[ index( idv,_Ident) ];
}

 
/*************************************************************************/
/*  ATT  subsorts ( ClassProd@ ) SortCdList                              */
/*  yields for each ClassProd@ the list of the corresponding sort codes  */

static ELEMENT *subsortstab;	/*=-=   ClassProd@  -->  SortCdList   =-=*/

SortSq  appSortSq( SORTCDT ccd, SortSq seq){ 
	SortSq sqv = (SortSq) malloc( sizeof(struct SortSqElem) );
	sqv->first = ccd;
	sqv->rest  = seq;
	return sqv;
}

static  SortSq  sorted_ins( SORTCDT toins, SortSq list ){
	if( list == NULL ){
		return  appSortSq( toins, NULL );
	} else if( toins > list->first ){
		return  appSortSq( toins, list );
	} else if( toins == list->first ){
		return  list ;
	} else {
		list->rest =  sorted_ins( toins, list->rest );
		return  list ;
	}
}

long  init_subsorts( void ) {
	int bound, bound2, i, j, cpoint, cnil, cterm, pcd;
	SortSq list;
	ELEMENT L;

	bound = number(_ClassProd_);
	subsortstab  = (ELEMENT*) calloc( bound+1, sizeof(ELEMENT) );
	if( subsortstab == 0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute subsorts\n");
		exit( EXIT_FAILURE );
	}

	for(j=1;j<=bound;j++) {
		ELEMENT P = element(j,_ClassProd_);

		list = NULL;
		L = term_basesorts( son(1,son(2,P)) );
		bound2 = numsubterms(L);
		cpoint = cnil = cterm = 0;
		for(i=1;i<=bound2;i++) {
			pcd = prodcd(fath(subterm(i,L)));
			switch(pcd) {
				case POINT_SORTCD : cpoint = 1; break;
				case NIL_SORTCD   : cnil = 1; break;
				case TERM_SORTCD  : cterm = 1; break;
				default : list = sorted_ins( pcd, list );
			}		
		}
		if( cterm ) list = sorted_ins( TERM_SORTCD, NULL );
		if( cnil  ) list = sorted_ins( NIL_SORTCD,  list );
		if( cpoint) list = sorted_ins( POINT_SORTCD,list );

		L = node_basesorts( son(1,son(2,P)) );
		if( L == AllNodes() ) list = sorted_ins( NODE_SORTCD, list );
		else {
			bound2 = numsubterms(L);
			for(i=1;i<=bound2;i++) list = sorted_ins( -prodcd(fath(subterm(i,L))), list );
		}
		subsortstab[j] = ptoe(list);
	}

/*  After contraction, subsortstab yields for a user defined class sort C  */
/*  the list of all ground sorts being a subsort of C except in the        */
/*  cases: if Node is a subsort, it returns the node sort code instead of  */
/*  the list of all node ground sorts; and if Term is a subsort, corresp.  */
/*  subsortstab is accesssed by the negated class code.                    */

return 1;
}


long  free_subsorts( void ){
	return 1L;
}


ELEMENT subsorts( ELEMENT cp ){
	IFNIL( cp ) IS(cp,_ClassProd_,__FILE__,__LINE__,"subsorts",1)
	return  subsortstab[ index( cp, _ClassProd_ ) ];
}



/***************************************************************************************
  ATT pat_anchor( PatternCase@ PC ) Item@
  (used for extended pattern class)

  checks if there is a bound name in PC, which is in strong relationship
  with all free items and all bound names of this pattern

  ATT att_path( Item@ ) Relationship

  yields the path from the anchor to each item in a pattern

****************************************************************************************/

static  ELEMENT *att_pathtab;		/*=-=  Item@  ->  Relationship  =-=*/

long  init_att_path( void ){
	int i,bound;

	bound = number(_Item_);
	att_pathtab  = (ELEMENT*) calloc( bound+1, sizeof(ELEMENT) );
	if( att_pathtab == 0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate att_path table \n");
		exit( EXIT_FAILURE );
	}

	for(i=1;i<=bound;i++) att_pathtab[i] = nil();

return 1L;
}



static  ELEMENT *pat_anchortab;          /*=-=   PatternCase@ ->   Item@   =-=*/

long  init_pat_anchor( void ){
	long pcase,b,f,g,num_bn, bound, num_fi;
	ELEMENT blist,flist,pc, lpath;
	unsigned is_anchor;

	pat_anchortab  = (ELEMENT*) calloc( number(_PatternCase_)+1, sizeof(ELEMENT) );
	if( pat_anchortab == 0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate pat_anchor table \n");
		exit( EXIT_FAILURE );
	}


	bound =  number(_PatternCase_);
	for( pcase = 1; pcase <= bound ; pcase++ ){

	   pc  =  element(pcase,_PatternCase_);

           /* num_bn may be zero */
           is_anchor = P_FALSE;

	   blist = search_bound_names( son(1,pc) );
	   num_bn = numsubterms( blist );

           for(b=1;b<=num_bn;b++){
        
              is_anchor = P_TRUE;

              /* check, if all free items are reachable from anchor */
	      flist = search_free_items( son(1,pc) );
	      num_fi = numsubterms(flist);

              for(f=1;f<=num_fi;f++){
		lpath = path( fath(subterm(b,blist)), subterm(f,flist));
                 if( lpath == nil() ){
                   is_anchor = P_FALSE;
                   break;
                 }
		  else { ELEMENT xx = subterm(f,flist);
			att_pathtab[ index(xx,_Item_) ] = lpath;
		  }
              }

              if (is_anchor) {
                 /* now check, if all bound names are reachable from anchor */ 
                 for(g=1;g<=num_bn;g++){
		    lpath = path( fath(subterm(b,blist)), fath(subterm(g,blist)));
                    if( lpath == nil() ){
                      is_anchor = P_FALSE;
                      break;
                    }
		    else {
			ELEMENT xx = fath(subterm(g,blist));
			att_pathtab[ index( xx,_Item_) ] = lpath;
		    }
                 }

                 if (is_anchor) {
                    pat_anchortab[pcase] = fath(subterm(b,blist));   /* anchor exists */
                    break;
                 }
              }

          }

          if(!is_anchor)
            pat_anchortab[pcase] = nil();

       }
	
       return 1L;
}


long  free_pat_anchor( void ){
	return 1L;
}

ELEMENT att_path( ELEMENT it ){
	IFNIL( it ) IS(it,_Item_,__FILE__,__LINE__,"att_path",1)
	return  att_pathtab[ index( it, _Item_ ) ];
}

ELEMENT pat_anchor( ELEMENT pc ){
	IFNIL( pc ) IS(pc,_PatternCase_,__FILE__,__LINE__,"pat_anchor",1)
	return  pat_anchortab[ index( pc, _PatternCase_ ) ];
}


/*****************************************************/
/***  Additional Functions For Dependency Analysis ***/
/*****************************************************/

#define ORDER(i)     dep_arrays[ind][i]
#define FINEORDER(i) dep_arrays[ind][size+(i)]
#define AB_MASK(i)   dep_arrays[ind][2*size+(i)]

#define AB 1
#define AA 2
#define BB 3
#define ID 4
#define BA 5
#define NO 8


#define AFTER  1
#define BEFORE 2
#define AFTBEF 3

#define AB_MASK_DEFAULT 0x33
#define SAME_NODE_BIT   0x100

#define DEP_ARRAY(matrix,size,x,y) matrix[(x)*size+(y)]


static int *intarr_alloc( int size, int def_val )
{
int i, *p = (int *)calloc(size,sizeof(ELEMENT));

	if(p==0L) {
		mxi_prterrm(__FILE__,__LINE__,"intarr_alloc",
			"Cannot allocate arrays for dependency graph");
		exit( EXIT_FAILURE );
	} else {
		if( def_val )  for(i=0;i<size;i++)  p[i]=def_val;
	}

return p;
}

/*****************************************************************/
/*  short *matrix_short( int size )                              */
/*  yields for each FuAtList@ the matrix for dependency analysis */

static short *matrix_short( int size ) {
	short *M = (short *)calloc( size*size, sizeof(short));
	if( M==0L ) {
		mxi_prterrm(__FILE__,__LINE__,"matrix_short",
			"Cannot allocate arrays for dependency graph");
		exit( EXIT_FAILURE );
	}
return M;
}


/************** auxiliary functions for computation of eval_groupnr */

static void enter_dep_matrix( ELEMENT N, int size, short *matrix ) {
	int bound, sonnr, i;
	ELEMENT Alist = appl_list(N);

	bound = numsubterms(Alist);
	sonnr = son_nr(N);

	for(i=1;i<=bound;i++)
		DEP_ARRAY(matrix,size,relacc_nr(subterm(i,Alist))-1,sonnr-1) = 1;
}



static void warshall_short( int size, short *matrix )
{
int i,j,k;

	for(k=0;k<size;k++)
	for(i=0;i<size;i++)
	for(j=0;j<size;j++)
		DEP_ARRAY(matrix,size,i,j) |=
			(DEP_ARRAY(matrix,size,i,k) & DEP_ARRAY(matrix,size,k,j));
}


static int calc_order( int size, short *matrix, int mask, ELEMENT *res, int nextnum ) {
	int *pclass = intarr_alloc(3*size,0);
	int *pclinv = pclass + size;
	int *cl_ord = pclass + 2*size;
	ELEMENT IL;
	int i, j, count, oldnum;

/* Phase 1 : computation of the evaluation groups */

	for(count=i=0;i<size;i++) pclass[i] = -1;

	for(i=0;i<size;i++) if(pclass[i]==-1) {
		pclinv[ pclass[i] = count++ ] = i;
		for(j=i+1;j<size;j++)
			if( DEP_ARRAY(matrix,size,i,j) & DEP_ARRAY(matrix,size,j,i) & mask )
				pclass[j]=pclass[i];
	}

/* Phase 2 : numbering of the groups, beginning from nextnum */

	for(i=0;i<count;i++) cl_ord[i] = 0;

	do { oldnum = nextnum;
	     for(i=0;i<count;i++)
		if(cl_ord[i]==0) {
		    for(j=0;j<count;j++)
			if( cl_ord[j]==0 && i!=j &&
				(mask & DEP_ARRAY(matrix,size,pclinv[j],pclinv[i])) )
				break;

		    if(j==count) cl_ord[i] = nextnum++ ;
		}
	} while(nextnum != oldnum);

/* Phase 3 : assignments to the result list */

	IL = IntList();
	for(i=0;i<size;i++) {
		IL = appback( IL, cl_ord[pclass[i]] );
	}
	*res = IL;

	free(pclass);

return nextnum;
}


/****************************************************************/
/*  ATT  eval_groupnr    ( FctOrAtt@ ) Int                      */
/*  yields for each FctOrAtt@ the number of its group   	*/

/*  ATT  eval_prev_grnum ( FuAtList@ ) Int                      */
/*  yields the number of earlier evaluated attributes

/*  ATT  group_index     ( FctOrAtt@ ) Int                      */
/*  yields the index of an attribute inside the evaluation group*/

/*  ATT  eval_group      ( FctOrAtt@ ) FuAtNodeList             */
/*  yields the Attribute@-nodes of the evaluation group		*/

/*  ATT  attr_list_groups( FuAtList@ )   FuAtListInfo           */
/*  yields the ordered list of the evaluation groups		*/


static ELEMENT *mxa_eval_groupnr;    /*=-=   FctOrAtt@  -->  Int          =-=*/
static ELEMENT *mxa_eval_prev_grnum; /*=-=   FuAtList@  -->  Int          =-=*/

static ELEMENT *mxa_group_index;     /*=-=   FctOrAtt@  -->  Int          =-=*/
static ELEMENT *mxa_eval_group;      /*=-=   FctOrAtt@  -->  FuAtNodeList =-=*/
static ELEMENT *mxa_attr_list_groups;/*=-=   FuAtList@  -->  FuAtListInfo =-=*/


ELEMENT  eval_groupnr( ELEMENT p ){
	IFNIL( p ) IS(p,_FctOrAtt_,__FILE__,__LINE__,"eval_groupnr",1)
	return mxa_eval_groupnr[index(p,_FctOrAtt_)];
}

ELEMENT  eval_group( ELEMENT p ){
	IFNIL( p ) IS(p,_FctOrAtt_,__FILE__,__LINE__,"eval_group",1)
	return mxa_eval_group[index(p,_FctOrAtt_)];
}

ELEMENT  eval_prev_grnum( ELEMENT p ){
	IFNIL( p ) IS(p,_FuAtList_,__FILE__,__LINE__,"eval_prev_grnum",1)
	return mxa_eval_prev_grnum[index(p,_FuAtList_)];
}

ELEMENT  group_index( ELEMENT p ){
	IFNIL( p ) IS(p,_FctOrAtt_,__FILE__,__LINE__,"group_index",1)
	return mxa_group_index[index(p,_FctOrAtt_)];
}

ELEMENT  attr_list_groups( ELEMENT p ){
	IFNIL( p ) IS(p,_FuAtList_,__FILE__,__LINE__,"attr_list_groups",1)
	return mxa_attr_list_groups[index(p,_FuAtList_)];
}


long init_eval_groupnr( void ) {
	int i, j, bound, size, nextnum;
	short *matrix;
	ELEMENT IL;

	bound = number(_FctOrAtt_);
	mxa_eval_groupnr = (ELEMENT *)calloc( bound+1, sizeof(ELEMENT));
	if( mxa_eval_groupnr==0L ) {
		mxi_prterrm(__FILE__,__LINE__,"init_eval_groupnr",
			"Cannot allocate attribute eval_groupnr\n");
		exit( EXIT_FAILURE );
	}

	bound = number(_FuAtList_);
	mxa_eval_prev_grnum = (ELEMENT *)calloc( bound+1, sizeof(ELEMENT));
	if( mxa_eval_prev_grnum==0L ) {
		mxi_prterrm(__FILE__,__LINE__,"init_eval_groupnr",
			"Cannot allocate attribute eval_prev_grnum\n");
		exit( EXIT_FAILURE );
	}

	nextnum = 1;

	for(i=1;i<=bound;i++) {
		ELEMENT AL = element(i,_FuAtList_);

		mxa_eval_prev_grnum[i] = nextnum-1;

		size = numsons( AL );
		matrix = matrix_short( size );
		for(j=1;j<=size;j++)
			enter_dep_matrix(son(j,AL),size,matrix);

		warshall_short(size,matrix);
		nextnum = calc_order(size,matrix,1,&IL,nextnum);
		/*  IL is IntList of the eval_groupnr's */

		for(j=1;j<=size;j++) {
			mxa_eval_groupnr[index(son(j,AL),_FctOrAtt_)] = subterm(j,IL);
		}

		free(matrix);
	}

return 1;
}


long init_eval_group( void ) {
	/* initialisation together with init_group_index */
return 1;
}

long init_eval_prev_grnum( void ) {
	/* initialisation together with init_eval_groupnr */
return 1;
}

long init_attr_list_groups( void ) {
	/* initialisation together with init_group_index */
return 1;
}


long init_group_index( void ) {
	int i, bound, j, k, size, attindex, count;
	ELEMENT ANL, AGL;

	bound = number(_FctOrAtt_);
	mxa_group_index = (ELEMENT *)calloc( bound+1, sizeof(ELEMENT));
	if( mxa_group_index==0L ) {
		mxi_prterrm(__FILE__,__LINE__,"init_group_index",
			"Cannot allocate attribute group_index\n");
		exit( EXIT_FAILURE );
	}
	mxa_eval_group = (ELEMENT *)calloc( bound+1, sizeof(ELEMENT));
	if( mxa_eval_group==0L ) {
		mxi_prterrm(__FILE__,__LINE__,"init_eval_group",
			"Cannot allocate attribute eval_group\n");
		exit( EXIT_FAILURE );
	}

	bound = number(_FuAtList_);
	mxa_attr_list_groups = (ELEMENT *)calloc( bound+1, sizeof(ELEMENT));
	if( mxa_attr_list_groups==0L ) {
		mxi_prterrm(__FILE__,__LINE__,"init_attr_list_groups",
			"Cannot allocate attribute attr_list_groups\n");
		exit( EXIT_FAILURE );
	}

	for(i=1;i<=bound;i++) {
		ELEMENT AL = element(i,_FuAtList_);
		size = numsons( AL );

		AGL = FuAtListInfo();

		for(k=1+eval_prev_grnum(AL),count=0;count<size;k++) { /* collection of group k */
			attindex = 0;

			ANL = FuAtNodeList();
			for(j=1;j<=size;j++) {
				ELEMENT ATT = son(j,AL);
				if( eval_groupnr(ATT)==k ) {
					mxa_group_index[index(son(j,AL),_FctOrAtt_)] = attindex++;
					ANL = appback( ANL, ATT );
					count++;
				}
			}
			for(j=1;j<=size;j++) {
				if( eval_groupnr(son(j,AL))==k ) {
					mxa_eval_group[index(son(j,AL),_FctOrAtt_)] = ANL;
				}
			}
			if(ANL!=FuAtNodeList()) AGL = appback( AGL, ANL );
		}
		mxa_attr_list_groups[i] = AGL;
	}

return 1;
}


long free_eval_groupnr( void ){
	return 1L;
}
long free_eval_group( void ){
	return 1L;
}
long free_eval_prev_grnum( void ){
	return 1L;
}
long free_group_index( void ){
	return 1L;
}
long free_attr_list_groups( void ){
	return 1L;
}

/*** auxiliary arrays and functions for computation of tree orders *********/

ELEMENT init_matrix( int size ){
ELEMENT *P;
int i, bound;

	P = (ELEMENT *)malloc(4*size*size*sizeof(ELEMENT));
	if( P==0L ) {
		mxi_prterrm(__FILE__,__LINE__,"init_matrix",
			"Cannot allocate arrays for dependency graph");
		exit( EXIT_FAILURE );
	}
	bound = 4*size*size;
	for(i=0;i<bound;i++) {
		P[i] = OrValue();
	}
return ptoe(P);
}


static void enter_flist( int ind, ELEMENT N, ELEMENT L, ELEMENT *M, int size ) {
int from, to, bound, i;
ELEMENT EL, T;

	from = ind;
	ind += (size>>1);

	if( L==nil() ) {
		M[from*size + ind] = nil();
		return;
	}

	EL = FList();
	bound = numsubterms(L);

	for(i=1;i<=bound;i++) {
		T = subterm(i,L);
		if( is(T,_RelevAcc)
			&& eval_groupnr(N)==eval_groupnr(son(subterm(1,T),fath(N))) ) {
			to = group_index(son(subterm(1,T),fath(N)));

			M[from*size + to] = TW_or( M[from*size + to], EL );

			from = to + (size>>1);
			EL = FList();

		} else if(is(T,_FValue) || is(T,_FClosure)) {

			EL = appback(EL,T);

		} else fprintf(stderr,"**** enter_flist : wrong sort of FList-subterm\n");

	}
	M[from*size + ind] = TW_or( M[from*size + ind], EL );
}


static void aux_enter_att( int ind, ELEMENT N, ELEMENT L, ELEMENT T, ELEMENT *M, int size ){

ELEMENT Nextel, Rest;

	if(T==FList()) {
		enter_flist(ind,N,L,M,size);
		return;
	}

	while( is(T,_FList) && T!=FList() && is(subterm(1,T),_FList) ) {
		T = conc(subterm(1,T),back(T));
	}

/* assertion : FList has no first subterm of sort FList */

	Nextel = (is(T,_FList)) ? subterm(1,T) : T;
	Rest   = (is(T,_FList)) ? back(T)      : FList();

/* Nextel is of sort FValue, FClosure, OrValue */
/* Rest is a FList, maybe the empty list */

	if( Nextel==OrValue() ) return;
	else if(is(Nextel,_OrValue)) {
		aux_enter_att(ind,N,L,TW_conc(subterm(1,Nextel),Rest),M,size);
		aux_enter_att(ind,N,L,TW_conc(   back(Nextel)  ,Rest),M,size);
	}
	else if(is(Nextel,_FClosure) || is(Nextel,_FValue)) {
		aux_enter_att(ind,N,appback(L,Nextel),Rest,M,size);
	}
	else fprintf(stderr,
		"**** internal error in aux_enter_att : wrong sort of Nextel %lx\n",
		sort(Nextel));
}



ELEMENT enter_attribute( int ind, ELEMENT N, ELEMENT M, int size ) {
	ELEMENT T = valueterm(son(-1,N));

	if(T==nil())	enter_flist( ind, N, nil(), etop(M), 2*size);
	else		aux_enter_att( ind, N, FList(), T, etop(M), 2*size);

return M;
}


ELEMENT mat_lookup( ELEMENT M_maxelem, int size, int ind ) {
	ELEMENT *M = etop(M_maxelem);

return M[ind*2*size + size+ind];
}


ELEMENT warshall_value( ELEMENT M_maxelem, int halfsize ) {
ELEMENT S,*M = etop(M_maxelem);
int i,j,k, size = 2*halfsize;

	for(k=0;k<size;k++) {

		S = TW_closure(M[k*size+k]);

		for(i=0;i<size;i++) if(i!=k) {
			for(j=0;j<size;j++) if(j!=k) {

				M[i*size+j] = TW_or( M[i*size+j],
					TW_conc(M[i*size+k],TW_conc(S,M[k*size+j]))
					);

			}
		}

		i=k;
		for(j=0;j<size;j++) if(j!=k) {
			M[i*size+j] = TW_conc( S, M[i*size+j] );
		}

		j=k;
		for(i=0;i<size;i++) if(i!=k) {
			M[i*size+j] = TW_conc( M[i*size+j], S );
		}

		i=j=k;
			M[i*size+j] = S;
	}

return M_maxelem;
}


static int ord_conc_arr[6][6] = {
  { NO,NO,NO,NO,NO,NO }, /* NO */
  { NO,AB,AA,AB,AB,AA }, /* AB */
  { NO,AB,AA,NO,AA,NO }, /* AA */
  { NO,BB,BA,BB,BB,BA }, /* BB */
  { NO,AB,AA,BB,ID,BA }, /* ID */
  { NO,BB,BA,NO,BA,NO }  /* BA */
};

static int ord_or_arr[6][6] = {
  { NO,NO,NO,NO,NO,NO }, /* NO */
  { NO,AB,AA,BB,ID,BA }, /* AB */
  { NO,AA,AA,BA,AA,BA }, /* AA */
  { NO,BB,BA,BB,BB,BA }, /* BB */
  { NO,ID,AA,BB,ID,BA }, /* ID */
  { NO,BA,BA,BA,BA,BA }  /* BA */
};


#define SAME_NODE_MASK 0x88
#define LRV(x) (((x)>>4)&0x7)
#define LRR(x) ((x)&0x7)


static int ord_or(int x, int y)
{
int lrv = ord_or_arr[LRV(x)][LRV(y)];
int lrr = ord_or_arr[LRR(x)][LRR(y)];

return (lrv<<4) | lrr;
}

static int ord_conc(int x, int y)
{
int lrv = ord_conc_arr[LRV(x)][LRV(y)];
int lrr = ord_conc_arr[LRR(y)][LRR(x)];

return (lrv<<4) | lrr;
}



ELEMENT OrdOp_or(ELEMENT x,ELEMENT y)
{
return (SAME_NODE_MASK & (x | y) ) | ord_or(x,y) ;
}

ELEMENT OrdOp_conc(ELEMENT x,ELEMENT y) /* concatenation of the relations */
{
return (SAME_NODE_MASK & (x & y) ) | ord_conc(x,y) ;
}

ELEMENT OrdOp_closure(ELEMENT x)  /* closure operation */
{
return OrdOp_or( OrdOp_conc(x,x), Ord_ident() );
}


long    maybe_same_node(ELEMENT x)
{
return (x & SAME_NODE_MASK)==SAME_NODE_MASK ;
}


/****************************************************************************************/
/*  ATT  eval_finegroup( FctOrAtt@ ) Int						*/
/*  yields for each FctOrAtt@ the number of the finegroup in its evaluation group	*/

/*  ATT  eval_aftbef   ( FctOrAtt@ ) Int						*/
/*  contains for each FctOrAtt@, if it's associated to the before- or after-Point	*/

/*  ATT  eval_strategy ( FctOrAtt@ ) Int						*/
/*  yields for each FctOrAtt@ its evaluation strategy					*/

/*  ATT  eval_sortlist ( FctOrAtt@ ) DefIdNodeInfo					*/
/*  yields for each FctOrAtt@ a list of basis sorts, which must be enumerated		*/


static  ELEMENT *mxa_eval_finegroup,
		*mxa_eval_aftbef,
		*mxa_eval_strategy,  /*=-=  FctOrAtt@  -->  Int   =-=*/
		*mxa_is_trivial_finegroup;
static  ELEMENT *mxa_eval_sortlist;  /*=-=  FctOrAtt@  -->  DefIdNodeInfo =-=*/


long init_eval_finegroup() {
	mxa_eval_finegroup = (ELEMENT *)calloc( number(_FctOrAtt_)+1, sizeof(ELEMENT));
	if( mxa_eval_finegroup == 0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate attribute eval_finegroup\n");
		exit( EXIT_FAILURE );
	}
return 1L;
}

long init_eval_aftbef()  {
	int i, bound = number(_FctOrAtt_);

	mxa_eval_aftbef = (ELEMENT *)calloc( bound+1, sizeof(ELEMENT));
	if( mxa_eval_aftbef == 0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate attribute eval_aftbef\n");
		exit( EXIT_FAILURE );
	}
	for(i=1;i<=bound;i++) mxa_eval_aftbef[i] = AB_MASK_DEFAULT;

return 1L;
}

long init_is_trivial_finegroup()  {
	mxa_is_trivial_finegroup = (ELEMENT *)calloc( number(_FctOrAtt_)+1, sizeof(ELEMENT));
	if( mxa_is_trivial_finegroup == 0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate attribute is_trivial_finegroup\n");
		exit( EXIT_FAILURE );
	}
return 1L;
}

long init_eval_sortlist() {
	mxa_eval_sortlist = (ELEMENT *)calloc( number(_FctOrAtt_)+1, sizeof(ELEMENT));
	if( mxa_eval_sortlist == 0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate attribute eval_sortlist\n");
		exit( EXIT_FAILURE );
	}
return 1L;
}

long init_eval_strategy()  {
	mxa_eval_strategy = (ELEMENT *)calloc( number(_FctOrAtt_)+1, sizeof(ELEMENT));
	if( mxa_eval_strategy == 0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate attribute eval_strategy\n");
		exit( EXIT_FAILURE );
	}
return 1L;
}


ELEMENT  eval_finegroup( ELEMENT p ){
	IFNIL( p ) IS(p,_FctOrAtt_,__FILE__,__LINE__,"eval_finegroup",1)
	return mxa_eval_finegroup[index(p,_FctOrAtt_)];
}

ELEMENT  eval_aftbef( ELEMENT p ){
	IFNIL( p ) IS(p,_FctOrAtt_,__FILE__,__LINE__,"eval_aftbef",1)
	return mxa_eval_aftbef[index(p,_FctOrAtt_)];
}

ELEMENT  is_trivial_finegroup( ELEMENT p ){
	IFNIL( p ) IS(p,_FctOrAtt_,__FILE__,__LINE__,"eval_aftbef",1)
	return mxa_is_trivial_finegroup[index(p,_FctOrAtt_)];
}

ELEMENT  eval_sortlist( ELEMENT p ){
	IFNIL( p ) IS(p,_FctOrAtt_,__FILE__,__LINE__,"eval_sortlist",1)
	return mxa_eval_sortlist[index(p,_FctOrAtt_)];
}

ELEMENT  eval_strategy( ELEMENT p ){
	IFNIL( p ) IS(p,_FctOrAtt_,__FILE__,__LINE__,"eval_strategy",1)
	return mxa_eval_strategy[index(p,_FctOrAtt_)];
}

long free_eval_finegroup( void ){
	return 1L;
}

long free_eval_aftbef( void ){
	return 1L;
}

long free_is_trivial_finegroup( void ){
	return 1L;
}

long free_eval_sortlist( void ){
	return 1L;
}

long free_eval_strategy( void ){
	return 1L;
}

/*******************************************************************/
/** auxiliary functions for the computation of attr_list_info ******/
/*******************************************************************/

static void enter_dep_aftbef( ELEMENT N, int size, short *matrix, ELEMENT *ab_mask ) {
	int i, bound, api, ord, gri;
	ELEMENT FuncApplNode, Alist;

	Alist = appl_relacc_list(N);
	bound = numsubterms(Alist);
	gri = group_index(N);

	for(i=1;i<=bound;i++)
	{
		FuncApplNode = subterm(i,Alist);

		api = group_index(fath(decl(son(1,FuncApplNode))));
		ord = appl_order(FuncApplNode);

		if(maybe_same_node(ord)) DEP_ARRAY(matrix,size,api,gri) |= SAME_NODE_BIT;


		switch( (ord) & 0x7 )
		{
		case 0 :ab_mask[api] &= ~AFTBEF;
			ab_mask[gri] &= ~AFTBEF;
			break;

		case AA:ab_mask[gri] &= ~BEFORE;
			break;

		case BB:ab_mask[api] &= ~AFTER;
			break;

		case ID:DEP_ARRAY(matrix,size,api,gri) |= (1);
			break;

		case BA:ab_mask[api] &= ~AFTER;
			ab_mask[gri] &= ~BEFORE;
			break;
		}

		switch( (ord>>4) & 0x7 )
		{
		case 0 :ab_mask[gri] &= ~(AFTBEF<<4);
			ab_mask[api] &= ~(AFTBEF<<4);
			break;

		case AA:ab_mask[api] &= ~(BEFORE<<4);
			break;

		case BB:ab_mask[gri] &= ~(AFTER<<4);
			break;

		case ID:DEP_ARRAY(matrix,size,gri,api) |= (1<<4);
			break;

		case BA:ab_mask[gri] &= ~(AFTER<<4);
			ab_mask[api] &= ~(BEFORE<<4);
			break;
		}
	}
}



static void attr_group_conv( ELEMENT GL )
{
ELEMENT N, declnode;
int i, j, bound, bound2, forw, backw, attnum, allnodevalued,
	group_parteval, group_strategy, group_waitlist,
	parteval, strategy, waitlist, direction, fctattmix,
	lastfnr, nextfnr, fnr, abm, abmnew, sortlist;

/* List of found strategies for tree traversal */
/* 0 : no strategy found */
/* 1 : several base sorts - heap necessary */
/* 2 : direct enumeration */

	bound = numsubterms(GL);

	forw = 0;
	backw = 0;
	attnum = 0;
	allnodevalued = 1;

	for(i=1;i<=bound;i++) {
		ELEMENT A = subterm(i,GL);
		ELEMENT sorte = son(1,son(2,A));

		if( is(A,_Attribute_) ) {
			N = A; /* N is used below, if there is only one attribute */
			attnum++;
			abm = eval_aftbef(A);
			if( abm & 0x3 ) forw++;
			if( abm & 0x30) backw++;
		}
		if(is(sorte,_TermSortId_) && idtos(term(son(1,sorte)))!=atoe("Node")) {
			allnodevalued = 0;
		}
	}

	if( attnum ) { /* attributes are in the list */

		if( allnodevalued==0 || (forw < attnum && backw < attnum) || (max_options.onr&2)==0 ) {
			group_strategy = WAITSTR; /* no strategy possible */

			direction = (forw < backw && allnodevalued==1 ) ? 8 : 0;
			fctattmix = (attnum < bound) ? 16 : 0;
			group_parteval = ( fctattmix==0 && (max_options.onr&1)==1 ) ? 4 : 0;
			group_waitlist = 32;

		} else { /* strategy found */

			direction = (forw < backw ) ? 8 : 0;
			fctattmix = (attnum < bound) ? 16 : 0;
			group_parteval = ( fctattmix==0 && (max_options.onr&1)==1 ) ? 4 : 0;
			group_waitlist = 0; /* will maybe set in the finegroup */

			if( attnum==1 ) { /* there is only one attribute (uses N) */

				if(	appl_relacc_list(N)==ApplList()  ||
					( !is( fath(decl(son(1,son(2,N)))),_ClassProd_) &&
					  is(son(1,son(2,N)),_NodeSortId_) ) )
					group_strategy = ENUMSTR;
				else	group_strategy = HEAPSTR;

			} else { /* several attributes */
				group_strategy = HEAPSTR;
			}
		}

	} else { /* no attribute in the list */
		group_parteval = group_strategy = group_waitlist = direction = fctattmix = 0;
	}


/* End of strategy computation for the evaluation group */

	fnr = -1;
	nextfnr = eval_finegroup(subterm(1,GL));

	for(i=1;i<=bound;i++)
	{	int attix;

		N = subterm(i,GL);
		attix = index(N,_FctOrAtt_);

		lastfnr = fnr;
		fnr = nextfnr;
		nextfnr = (i==bound) ? -1 : eval_finegroup(subterm(i+1,GL));	

		abm = eval_aftbef(N);

		abmnew = (direction==8) ? ((abm>>4) & 0x3) : (abm & 0x3);
		if(abmnew==AFTBEF) abmnew=BEFORE;

		mxa_eval_aftbef         [attix] = abmnew;
		mxa_is_trivial_finegroup[attix] = btoe( lastfnr!=fnr && fnr!=nextfnr );

		waitlist = (mxa_is_trivial_finegroup[attix]==true()) ? group_waitlist : 32;

/***	The waitlist-bit is set iff at least 2 functions/attributes are in the same finegroup.
		If it is not set, code that checks an self-access to the attribute instance
		has to be generated.
***/

		parteval = ( waitlist==0 ) ? 0 : group_parteval;

		declnode = decl(son(1,son(2,N)));

		if( is(son(1,son(2,N)),_TermSortId_) ) {
			sortlist = AllNodes();
		} else if( is(fath(declnode),_ClassProd_) && ( group_strategy == HEAPSTR ) ) {
								/* enumerate several subsorts */
			sortlist = node_basesorts( son(1,son(2,N)));
			bound2 = numsubterms(sortlist);
			for(j=1;j<=bound2;j++) {
				if( prodcd(fath(subterm(j,sortlist)))==TERM_SORTCD ) {
					sortlist = AllNodes();
					break;
				}
			}
		} else {
			if( declnode==nil() ) sortlist=nil();
			else sortlist = appback(DefIdNodeList(),declnode);
		}

/***		if evaluation has to take place at all nodes, direct enumeration of 'element(i,_Node)'
		yields a non-sorted order of the nodes. --> choose enumeration with heap
***/

		strategy = (group_strategy == ENUMSTR && sortlist == AllNodes())
				? HEAPSTR : group_strategy;

		mxa_eval_sortlist[index(N,_FctOrAtt_)] = sortlist;
		mxa_eval_strategy[index(N,_FctOrAtt_)] = strategy + parteval + direction + fctattmix + waitlist;

	} /* endfor */

}



static ELEMENT aftbefsearch( int size, short *matrix, ELEMENT *AB_MASK, ELEMENT ANL ) {

/* return-value : new ordered ANL */

	int i, j, lastnum;
	ELEMENT FINEORDER, FGL;

	warshall_short(size,matrix);

	lastnum = calc_order(size,matrix,SAME_NODE_BIT,&FINEORDER,1);
	for(i=0;i<size;i++) mxa_eval_finegroup[index(subterm(i+1,ANL),_FctOrAtt_)] = subterm(i+1,FINEORDER);

/* restrictions for after/before - values */

	for(i=0;i<size;i++) {
		switch( (AB_MASK[i]) & 0x7 ) {
			case AFTER : /* only after => sonnr after -> y after */
			for(j=0;j<size;j++) if(DEP_ARRAY(matrix,size,i,j)&(1)) AB_MASK[j] &=~BEFORE;
			break;

			case BEFORE: /* only after => y before -> sonnr before */
			for(j=0;j<size;j++) if(DEP_ARRAY(matrix,size,j,i)&(1)) AB_MASK[j] &=~AFTER;
			break;
		}
		switch( (AB_MASK[i]>>4) & 0x7 ) {
			case AFTER : /* only after => sonnr after -> y after */
			for(j=0;j<size;j++) if(DEP_ARRAY(matrix,size,i,j)&(1<<4)) AB_MASK[j] &=~(BEFORE<<4);
			break;

			case BEFORE: /* only after => y before -> sonnr before */
			for(j=0;j<size;j++) if(DEP_ARRAY(matrix,size,j,i)&(1<<4)) AB_MASK[j] &=~(AFTER<<4);
			break;
		}
	}

	FGL = FuAtNodeList();
	for(j=1;j<lastnum;j++) {
		for(i=0;i<size;i++) {
			if(subterm(i+1,FINEORDER)==j) {
				FGL = appback( FGL, subterm(i+1,ANL) );
				mxa_eval_aftbef[index(subterm(i+1,ANL),_FctOrAtt_)] = AB_MASK[i];
			}
		}
	}
	attr_group_conv(FGL);

return FGL;
}


/************************************************************************/
/*  ATT  attr_list_info( FuAtList@  ) FuAtListInfo			*/
/*  yields for each FuAtList@ the list of its evaluation groups		*/

static ELEMENT *mxa_attr_list_info;	/*=-=   FuAtList@  -->  FuAtListInfo   =-=*/


long init_attr_list_info() {
	int i, j, k, bound, bound2, size;
	ELEMENT AL, ALG, ALI, ANL;
	short *matrix;

	ELEMENT *ab_mask = (ELEMENT *)intarr_alloc(number(_FctOrAtt_),0);

	bound = number(_FuAtList_);
	mxa_attr_list_info = (ELEMENT *)calloc( bound+1, sizeof(ELEMENT));
	if( mxa_attr_list_info == 0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate attribute attr_list_info\n");
		exit( EXIT_FAILURE );
	}


	for(i=1;i<=bound;i++) {
		AL = element(i,_FuAtList_);
		ALG = attr_list_groups(AL);
		bound2 = numsubterms(ALG);
		ALI = FuAtListInfo();

		for(j=1;j<=bound2;j++) {  /* group inside the FuAtList i */
			ANL = subterm(j,ALG);
			size = numsubterms(ANL);
			matrix = etop(subterm(j,attr_list_matlist(AL)));

			/* ANL is the list of Attribute@ in the group */

			for(k=size*size-1;k>=0;k--) matrix[k] = 0;

			for(k=0;k<size;k++) ab_mask[k] = AB_MASK_DEFAULT;
			for(k=1;k<=size;k++) {
				enter_dep_aftbef(subterm(k,ANL),size,matrix,ab_mask);
			}
			ALI = appback( ALI, aftbefsearch(size,matrix,ab_mask,ANL));
		}
		mxa_attr_list_info[i] = ALI;
	}
	free(ab_mask);

return 1L;
}

ELEMENT  attr_list_info( ELEMENT p ){
	IFNIL( p ) IS(p,_FuAtList_,__FILE__,__LINE__,"attr_list_info",1)
	return mxa_attr_list_info[index(p,_FuAtList_)];
}

long free_attr_list_info( void ){
	return 1L;
}


ELEMENT aux_itoa( int i ) {
char st[12];
	sprintf(st,"%d",i);
return atoe(st); /* allocates new memory */
}


long no_strategy_found( ELEMENT N ) {

return ((eval_strategy(N) & 3)==0);
}


static ELEMENT intreslist_insert( ELEMENT L, int n ) {
	if( L == IntResList()) return appfront(n,IntResList());
	if( subterm(1,L) < n ) return appfront(subterm(1,L),intreslist_insert(back(L),n));
	if( subterm(1,L) > n ) return appfront(n,L);

return L;
}

ELEMENT intres_union( ELEMENT X, ELEMENT Y, ELEMENT Z ) {
int i, bound;

	bound = numsubterms( X );
	for(i=1;i<=bound;i++) {
		Y = intreslist_insert( Y, subterm(i,X) );
	}
	bound = numsubterms( Z );
	for(i=1;i<=bound;i++) {
		Y = intreslist_insert( Y, subterm(i,Z) );
	}

return Y;
}

/* end of file */

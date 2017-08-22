#include <stdio.h>
#include <stdlib.h>

#include "max_spec.h"
#include "max_global.h"

extern ELEMENT eval_strategy( ELEMENT );

static FILE *out;

static char *universename = "ELEMENT";
static char *prefix       = "";
static char flag;

static char h1text []  =
"/*=-= The following definitions up to the ***-line aren't relevant for  =-=*/\n"
"/*=-= users; they constitute the interface to  max_std                  =-=*/\n"
"\n"
"typedef long         mxi_ELEMENT;\n"
"extern  long         mxi_conv_error;\n"
"extern  mxi_ELEMENT  mxi_btoe( char*, int, long );\n"
"extern  long         mxi_etob( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_ctoe( char*, int, char );\n"
"extern  char         mxi_etoc( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_itoe( char*, int, long );\n"
"extern  long         mxi_etoi( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_ptoe( char*, int, void*);\n"
"extern  void*        mxi_etop( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_atoe( char*, int, char*);\n"
"extern  char*        mxi_etoa( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_stoid( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_idtos( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_sort( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_number( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_index( char*, int, mxi_ELEMENT, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_element( char*, int, mxi_ELEMENT, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_numsubterms( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_subterm( char*, int, mxi_ELEMENT, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_front( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_back( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_appfront( char*, int, mxi_ELEMENT, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_appback( char*, int, mxi_ELEMENT, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_conc( char*, int, mxi_ELEMENT, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_tc(char*,int,char*,int,int,...);\n"
"extern  mxi_ELEMENT  mxi_fath  ( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_lbroth( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_rbroth( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_term( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_numsons( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_son( char*, int, mxi_ELEMENT, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_before( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_after( char*, int, mxi_ELEMENT );\n"
"extern  mxi_ELEMENT  mxi_node( char*, int, mxi_ELEMENT );\n"
"extern  long         mxi_is( char*, int, mxi_ELEMENT, mxi_ELEMENT );\n"
"extern  long         mxi_eq( char*, int, mxi_ELEMENT, mxi_ELEMENT );\n"
"extern  long         mxi_init( char*, int, int, mxi_ELEMENT );\n"
"extern  long         mxi_free( char*, int );\n"
"\n"
"/***************************************************************************/\n"
"\n"
"/*  The C-type for all elements of the MAX-universe including  nil :       */\n"
;

static  void  prt_predef( void ){
	char *fl, *flc;
	if( flag ){
		fl  = "";
		flc = "__FILE__,__LINE__,";
	} else {
		fl  = "f,l,";
		flc = "f,l,";
	}
	fprintf(out,"/***************************************************************************/\n");
	if (!strcmp(prefix,""))
	  fprintf(out,"/*  Predefined functions without the chosen prefix (the browser needs them)*/\n");
	else
	  fprintf(out,"/*  Predefined functions with the chosen prefix                            */\n");
	fprintf(out,"/***************************************************************************/\n");
fprintf(out,"/*  The following functions convert C-values to corresponding MAX-elements */\n");
fprintf(out,"/*  in case of an error, the functions set the global variable conv_error  */\n");
fprintf(out,"/*  to 0 and yield  nil.                                                   */\n");
fprintf(out,"#define  %sconv_error          mxi_conv_error        \n", prefix,fl,flc);
fprintf(out,"#define  %sbtoe(%sBOOLVAL)       mxi_btoe(%sBOOLVAL)\n",	 prefix,fl,flc);
fprintf(out,"#define  %sctoe(%sCHARVAL)       mxi_ctoe(%sCHARVAL)\n", prefix,fl,flc);
fprintf(out,"#define  %sitoe(%sINTVAL)        mxi_itoe(%sINTVAL)\n", prefix,fl,flc);
fprintf(out,"#define  %satoe(%sSTRVAL)        mxi_atoe(%sSTRVAL)\n", prefix,fl,flc);
fprintf(out,"#define  %sptoe(%sPOINTVAL)      mxi_ptoe(%sPOINTVAL)\n", prefix,fl,flc);
fprintf(out,"\n");
fprintf(out,"/*  The following functions convert MAX-elements to corresponding C-values */\n");
fprintf(out,"/*  in case of an error, the functions set the global variable conv_error  */\n");
fprintf(out,"/*  to 0 and yield  0, '\\0', 0, the empty string or NULL.                 */\n");
fprintf(out,"#define  %setob(%sBOOLELEM)      mxi_etob(%sBOOLELEM)\n", prefix,fl,flc);
fprintf(out,"#define  %setoc(%sCHARELEM)      mxi_etoc(%sCHARELEM)\n", prefix,fl,flc);
fprintf(out,"#define  %setoi(%sINTELEM)       mxi_etoi(%sINTELEM)\n", prefix,fl,flc);
fprintf(out,"#define  %setoa(%sSTRELEM)       mxi_etoa(%sSTRELEM)\n", prefix,fl,flc);
fprintf(out,"#define  %setop(%sREFELEM)       mxi_etop(%sREFELEM)\n", prefix,fl,flc);
fprintf(out,"\n");
fprintf(out,"/*  stoid  enters a string into sort  Ident  containing a finite set of    */\n");
fprintf(out,"/*  hash-coded strings;  idtos  returns the string of an identifier        */\n");
fprintf(out,"#define  %sstoid(%sSTRING)       mxi_stoid(%sSTRING)\n", prefix,fl,flc);
fprintf(out,"#define  %sidtos(%sIDENT)        mxi_idtos(%sIDENT)\n", prefix,fl,flc);
fprintf(out,"\n");
fprintf(out,"/*  sort  returns the sort constant of a defined element; otherwise exits. */\n");
fprintf(out,"#define  %ssort(%sELEM)          mxi_sort(%sELEM)\n", prefix,fl,flc);
fprintf(out,"#define  %sindex(%sELEM,SORT)    mxi_index(%sELEM,SORT)\n", prefix,fl,flc);
fprintf(out,"#define  %selement(%sINDEX,SORT) mxi_element(%sINDEX,SORT)\n", prefix,fl,flc);
fprintf(out,"#define  %snumber(%sSORT)        mxi_number(%sSORT)\n", prefix,fl,flc);
fprintf(out,"\n");
fprintf(out,"/*  The following functions provide the inspection of the tree structure; */\n");
fprintf(out,"/*  if their obvious meaning is not defined, they return  nil :           */\n");
fprintf(out,"#define  %sfath(%sNODE)          mxi_fath(%sNODE)\n", prefix,fl,flc);
fprintf(out,"#define  %slbroth(%sNODE)        mxi_lbroth(%sNODE)\n", prefix,fl,flc);
fprintf(out,"#define  %srbroth(%sNODE)        mxi_rbroth(%sNODE)\n", prefix,fl,flc);
fprintf(out,"#define  %sson(%sITH,NODE)       mxi_son(%sITH,NODE)\n", prefix,fl,flc);
fprintf(out,"#define  %snumsons(%sNODE)       mxi_numsons(%sNODE)\n", prefix,fl,flc);
fprintf(out,"\n");
fprintf(out,"/*  subterm(i,t)  returns the ith subterm of term t;  numsubterms(t)      */\n");
fprintf(out,"/*  returns the number of subterms t; both functions exit on failure      */\n");
fprintf(out,"#define  %ssubterm(%sITH,TERM)   mxi_subterm(%sITH,TERM)\n", prefix,fl,flc);
fprintf(out,"#define  %snumsubterms(%sTERM)   mxi_numsubterms(%sTERM)\n", prefix,fl,flc);
fprintf(out,"\n");
fprintf(out,"/*  The following functions provide the polymorphic handling of lists;    */\n");
fprintf(out,"/*  they exit on failure :                                                */\n");
fprintf(out,"#define  %sfront(%sLIST)         mxi_front(%sLIST)\n", prefix,fl,flc);
fprintf(out,"#define  %sback(%sLIST)          mxi_back(%sLIST)\n", prefix,fl,flc);
fprintf(out,"#define  %sappfront(%sELEM,LIST) mxi_appfront(%sELEM,LIST)\n", prefix,fl,flc);
fprintf(out,"#define  %sappback(%sLIST,ELEM)  mxi_appback(%sLIST,ELEM)\n", prefix,fl,flc);
fprintf(out,"#define  %sconc(%sLIST1,LIST2)   mxi_conc(%sLIST1,LIST2)\n", prefix,fl,flc);
fprintf(out,"\n");
fprintf(out,"/*  The following functions relate nodes to the corresponding terms and   */\n");
fprintf(out,"/*  points; they exit on failure :                                        */\n");
fprintf(out,"#define  %sterm(%sNODE)          mxi_term(%sNODE)\n", prefix,fl,flc);
fprintf(out,"#define  %sbefore(%sNODE)        mxi_before(%sNODE)\n", prefix,fl,flc);
fprintf(out,"#define  %safter(%sNODE)         mxi_after(%sNODE)\n", prefix,fl,flc);
fprintf(out,"#define  %snode(%sPOINT)         mxi_node(%sPOINT)\n", prefix,fl,flc);
fprintf(out,"\n");
fprintf(out,"/*  eq  is the equality predicate;  is  tests whether an element is in    */\n");
fprintf(out,"/*  the given sort;  desc  tests whether node1 is the desendant of node2; */\n");
fprintf(out,"/*  bef  and  aft  establish the linear order on  points :                */\n");
fprintf(out,"#define  %seq(%sELEM1,ELEM2)     mxi_eq(%sELEM1,ELEM2)\n", prefix,fl,flc);
fprintf(out,"#define  %sis(%sELEM,SORT)       mxi_is(%sELEM,SORT)\n", prefix,fl,flc);
fprintf(out,"#define  %sdesc(%sN1,N2)         (%sbefore(%sN1)>%sbefore(%sN2) && %safter(%sN1)<%safter(%sN2))\n",
													prefix,fl,prefix,fl,prefix,fl,prefix,fl,prefix,fl);
fprintf(out,"#define  %sbef(%sP1,P2)          (%sis(%sP1,_Point) && %sis(%sP2,_Point) && P1<P2)\n",
													prefix,fl,prefix,fl,prefix,fl);
fprintf(out,"#define  %saft(%sP1,P2)          (%sis(%sP1,_Point) && %sis(%sP2,_Point) && P1>P2)\n",
													prefix,fl,prefix,fl,prefix,fl);
fprintf(out,"\n");
}

#define  IDSTR(idn)  etoa(idtos(term(son(1,idn))))

static  long  mk_sortconstant( long scd ){
	return class_code(SORTCONST_CL,(short)scd);
}

static  void  prt_sortconstants( void ){
	ELEMENT  prodn;
	long     prodx;
	SORTCDT  prodcdv;
	char    *prodname;
	int      bound;

	bound =  number(_Production_);
	for( prodx = 1; prodx <= bound ; prodx++ ){
		prodn    =  element(prodx,_Production_);
		prodname = 	etoa(idtos( term( son(1,son(1,prodn)) ) ));
		prodcdv  =  prodcd(prodn);
		fprintf(out,"#define  _%s \t\t %dL\t/* %d */\n",
			prodname, mk_sortconstant(prodcdv), prodcdv );
		if( prodcdv < TERM_SORTCD ){
			fprintf(out,"#define  _%s_\t\t %dL\t/* %d */\n", prodname,
				mk_sortconstant(-prodcdv), -prodcdv );
		}
	}
	fprintf(out,"\n");
}


static  void  prt_constructors( void ){
	ELEMENT  prodn;
	long     prodx;
	char    *consname;
	int      bound;

	fprintf(out,"/* The constructors for  tupels  and  empty lists                         */\n");
	
	bound =  number(_TupelProd_) ;
	for( prodx = 1; prodx <= bound; prodx++ ){
		prodn    =  element(prodx,_TupelProd_);
		consname =  etoa(idtos( term( son(1,son(1,prodn)) ) ));
		fprintf(out,"#define  %s%s(", prefix, consname );
		if( numsons(son(2,prodn))==0 ){
			if( ! flag )  fprintf(out,"f,l");
			fprintf(out,")\t\t %dL\n", class_code(DEFCONST_CL,prodcd(prodn)) );
		} else {
			int     parnum = 1;
			ELEMENT useidnd =  son( 1, son(2,prodn) );
			if( ! flag )  fprintf(out,"f,l,");
			fprintf(out,"P%d", parnum++);
			useidnd = rbroth( useidnd );
			while(  useidnd != nil()  ){
				fprintf(out,",P%d", parnum++);
				useidnd = rbroth( useidnd );
			}
			useidnd =  son( 1, son(2,prodn) );
			if( ! flag ){
				fprintf(out,")\t\tmxi_tc(f,l,\"%s\",%d,%d",
										consname, parnum-1, prodcd(prodn) );
			} else {
				fprintf(out,")\t\tmxi_tc(__FILE__,__LINE__,\"%s\",%d,%d",
										consname, parnum-1, prodcd(prodn) );
			}
			parnum = 1;
			do {
				int sortcd =  prodcd( fath( decl(useidnd) ) );
				if( is( useidnd,_NodeSortId_)  )  sortcd = -sortcd;
				fprintf(out,",%d,P%d", sortcd, parnum++);
				useidnd = rbroth( useidnd );
			} while(  useidnd != nil()  );
			fprintf(out,")\n");
		}
	}
	bound =  number(_ListProd_) ;
	for( prodx = 1; prodx <= bound; prodx++ ){
		prodn    =  element(prodx,_ListProd_);
		consname =  etoa(idtos( term( son(1,son(1,prodn)) ) ));
		if( ! flag ){
			fprintf(out,"#define  %s%s(f,l)\t\t%dL\n", prefix,
						consname, class_code(DEFCONST_CL,prodcd(prodn)));
		} else {
			fprintf(out,"#define  %s%s()\t\t%dL\n", prefix,
						consname, class_code(DEFCONST_CL,prodcd(prodn)));
		}
	}
	fprintf(out,"\n");
}

static char fctatt_rek_params[] = ",EVALFCT,ELEMENT";

static  void  prt_others( void ){
	long     strucx;
	ELEMENT  decln;
	long     declx;
	char 	*declname;
	int      i, bound, parnum;

	fprintf(out,"/* The constructors and destructors for tree structures                    */\n");
	for( strucx = 1; strucx <= number(_Structure_); strucx++ ){
		ELEMENT  strucel   =  element(strucx,_Structure_);
		char    *strucname =  etoa(idtos( term( son(1,son(1,strucel)) ) ));
		SORTCDT  rootcd    =  prodcd( fath( decl(son(2,strucel)) ) );
		fprintf(out,"#define %s%s%s(TERM)\t\tmxi_init(__FILE__,__LINE__,%d,TERM)\n",
											prefix, "init_", strucname, rootcd );
		fprintf(out,"#define %s%s%s()\t\t\tmxi_free(__FILE__,__LINE__)\n",
											prefix, "free_", strucname );
	}
	fprintf(out,"\n");
	fprintf(out,"/* The declarations for defined functions, predicates, and attributes     */\n");
/*  print declarations for the defined functions  */

	fprintf(out,"typedef void (*EVALFCT1)( ELEMENT );\n");
	fprintf(out,"typedef void (*EVALFCT)( ELEMENT, ELEMENT, int, ELEMENT * );\n");

	bound =  number(_Function_) ;
	for( declx = 1; declx <= bound; declx++ ){
		int fa_code, addpar;

		decln    =  element(declx,_Function_);
		fa_code = eval_strategy(decln);
		addpar = ((fa_code&16)==16) && ((fa_code&3)==0);

		declname =  IDSTR( son(1,decln) );
		fprintf(out,"extern ELEMENT  mxx_%s(char*,int", declname );
		parnum =  numsons(son(2,decln));
		if( parnum > 0 ){
			for( i=1 ; i <= parnum ; i++)  fprintf(out,",ELEMENT");
		}
		fprintf(out,"%s);\n", (addpar) ? fctatt_rek_params : "");
		fprintf(out,"#define %s%s(", prefix, declname );
		if( parnum > 0 ){
			fprintf(out,"p1");
			for( i=2 ; i <= parnum ; i++)  fprintf(out,",p%d",i);
		}
		fprintf(out,")\t\tmxx_%s(__FILE__,__LINE__", declname );
		if( parnum > 0 ){
			for( i=1 ; i <= parnum ; i++)  fprintf(out,",p%d",i);
		}
		fprintf(out,"%s)\n", (addpar) ? ",0L,0" : "");
	}


/*  print declarations for the defined predicates  */
	bound =  number(_Predicate_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_Predicate_);
		declname =  IDSTR( son(1,decln) );
		fprintf(out,"extern long     mxs_%s(char*,int", declname );
		parnum =  numsons(son(2,decln));
		if( parnum > 0 ){
			for( i=1 ; i <= parnum ; i++)  fprintf(out,",ELEMENT");
		}
		fprintf(out,");\n");
		fprintf(out,"#define %s%s(", prefix, declname );
		if( parnum > 0 ){
			fprintf(out,"p1");
			for( i=2 ; i <= parnum ; i++)  fprintf(out,",p%d",i);
		}
		fprintf(out,")\t\tmxs_%s(__FILE__,__LINE__,", declname );
		if( parnum > 0 ){
			fprintf(out,"p1");
			for( i=2 ; i <= parnum ; i++)  fprintf(out,",p%d",i);
		}
		fprintf(out,")\n");
	}
/*  print access functions for the defined attributes  */
	bound =  number(_Attribute_) ;
	for( declx = 1; declx <= bound; declx++ ){
		int fa_code, addpar;

		decln    =  element(declx,_Attribute_);
		fa_code = eval_strategy(decln);
		addpar = ((fa_code&16)==16) && ((fa_code&3)==0);

		declname =  IDSTR( son(1,decln) );
		fprintf(out,"extern ELEMENT  mxx_%s(char*,int,ELEMENT", declname );

		fprintf(out,"%s);\n", (addpar) ? fctatt_rek_params : "" );

		fprintf(out,"#define %s%s(p)\t\tmxx_%s(__FILE__,__LINE__,p%s)\n",
			prefix, declname, declname, (addpar) ? ",0L,0" : "" );
	}
	fprintf(out,"\n");
}

extern void dyn_defines( FILE * );

void  header_gen( FILE *outp, char *prfx, int flg ){
	char *fl;

	out = outp;
	prefix = prfx;
	flag = flg;
	if( flag )
	  fl  = "";
	else 
	  fl  = "f,l";
	fprintf(out,"%s",h1text);
	fprintf(out,"#define  %s            mxi_ELEMENT\n\n",universename); 
	prt_predef();
	fprintf(out,"/*  The predefined constants are :                                        */\n");
	fprintf(out,"#define  %sminimalInt(%s)   %dL\n",   prefix, fl, MINIMALINT );
	fprintf(out,"#define  %smaximalInt(%s)   %dL\n\n", prefix, fl, MAXIMALINT );
	fprintf(out,"#define  %sroot(%s)         %dL\n",   prefix, fl, ROOT );
	fprintf(out,"#define  %strue(%s)         %dL\n",   prefix, fl, MAXTRUE );
	fprintf(out,"#define  %sfalse(%s)        %dL\n",   prefix, fl, MAXFALSE );
	fprintf(out,"#define  %snil(%s)          %dL\n",   prefix, fl, NIL );
	fprintf(out,"/*  The sort constants :                                                  */\n");
	prt_sortconstants();
	prt_constructors();
	if( flag )  prt_others();

	dyn_defines( out );
}




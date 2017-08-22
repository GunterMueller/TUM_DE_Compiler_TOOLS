#include <stdio.h>
#include <stdlib.h>
#include "max_spec.h"
#include "max_global.h"

void  genc_top( ELEMENT );
void  genc_list( ELEMENT );
void  genc_intres( ELEMENT, int );
void  prtsortconst( ELEMENT );


static FILE *out;


void gen_dynhash() {
	int i,j, bound, bound2;

	fprintf(out,"long  dynhash( int num, ... ) {\n");
	fprintf(out,"\tint i;\n");
	fprintf(out,"\tva_list ap;\n");
	fprintf(out,"\tunsigned long high, low, x, hcode = 1;\n");
	fprintf(out,"\tva_start( ap, num );\n");
	fprintf(out,"\tfor(i=1;i<=num;i++) {\n");
	fprintf(out,"\t\tx = va_arg( ap, ELEMENT );\n");

	fprintf(out,"\t\thigh = x>>16;\n");
	fprintf(out,"\t\tlow = x & 0xffff;\n");

	fprintf(out,"\t\thcode = (hcode * 43 + low ) %% HASHTABSIZE;\n");
	fprintf(out,"\t\thcode = (hcode * 43 + high) %% HASHTABSIZE;\n");
	fprintf(out,"\t}\n");
	fprintf(out,"\tva_end( ap );\n");
	fprintf(out,"return hcode;\n");
	fprintf(out,"}\n\n");

	fprintf(out,"#define HASHMEMSIZE 10000\n");
	fprintf(out,"static int hash_memptr = HASHMEMSIZE;\n");
	fprintf(out,"static ELEMENT *hash_mem;\n\n");
	fprintf(out,"static ELEMENT *hash_alloc( int num ) {\n");

	fprintf(out,"\tif( (hash_memptr += num) > HASHMEMSIZE) {\n");
	fprintf(out,"\t\thash_mem = (ELEMENT *)calloc( HASHMEMSIZE, sizeof(ELEMENT) );\n");
	fprintf(out,"\t\tif( hash_mem == 0L ) {\n");
	fprintf(out,"\t\t\tfprintf(stderr,\"*** no memory for hashtable available\\n\");\n");
	fprintf(out,"\t\t\texit( EXIT_FAILURE );\n");

	fprintf(out,"\t\t}\n");
	fprintf(out,"\t\thash_memptr = num;\n");
	fprintf(out,"\t}\n");
	fprintf(out,"return &hash_mem[hash_memptr-num];\n");
	fprintf(out,"}\n\n");

	fprintf(out,"static int enter( int hnumb, DYNH_ENTRY *hashtable, int dynind, int num, ... ) {\n");
	fprintf(out,"int i, coll = 1;\n");
	fprintf(out,"int tabindex =  hnumb ;\n");
	fprintf(out,"ELEMENT *P, EL, EP[50];\n");
	fprintf(out,"\tva_list ap;\n");
	fprintf(out,"\tva_start( ap, num );\n");
	fprintf(out,"\tif(num==1) EL = va_arg( ap, ELEMENT );\n");
	fprintf(out,"\telse for(i=0;i<num;i++) EP[i] = va_arg( ap, ELEMENT );\n");

	fprintf(out,"  do {\n");
	fprintf(out,"\tif(hashtable[tabindex].elem == MAXUNDEF ) {\n");
	fprintf(out,"\t\thashtable[tabindex].elem = EL;\n");
	fprintf(out,"\t\thashtable[tabindex].attr = dynind;\n");
	fprintf(out,"\t\thashtable[tabindex].numb = num;\n");


	fprintf(out,"\t\tswitch( dynind ) {\n");
	bound = number(_DynFunc_);
	for(j=1;j<=bound;j++) {
		ELEMENT N = element(j,_DynFunc_);
		bound2 = numsons(son(2,N));
		if( bound2 ) {
			fprintf(out,"\t\t\tcase %d: ",j);
			if(bound2 > 1) {
				fprintf(out,"\n\t\t\t{\n\t\t\t\tP = hash_alloc( num );\n");
				fprintf(out,"\t\t\t\tfor(i=0;i<num;i++) P[i] = EP[i];\n");
				fprintf(out,"\t\t\t\thashtable[tabindex].elem = mxs_ptoe(_c,0,P);\n");

				fprintf(out,"\t\t\t\thashtable[tabindex].value = mxd_init_%s(_c,0",etoa(idtos(term(son(1,son(1,N))))));
				for(i=1;i<=bound2;i++) fprintf(out,",P[%d]",i-1);
				fprintf(out,");\n");
				fprintf(out,"\t\t\t}\n");
			} else {
				fprintf(out,"hashtable[tabindex].value = mxd_init_%s(_c,0",etoa(idtos(term(son(1,son(1,N))))));
				if(bound2==1) fprintf(out,",EL");
				fprintf(out,");\n");
			}
			fprintf(out,"\t\t\tbreak;\n");
		}
	}
	fprintf(out,"\t\t}\n");

	fprintf(out,"\t\treturn tabindex;\n");
	fprintf(out,"\t}\n");


	fprintf(out,"\tif( num == 1 && hashtable[tabindex].numb == 1 && hashtable[tabindex].attr == dynind \n"); 
	fprintf(out,"\t\t&& mxs_eq(_c,0,hashtable[tabindex].elem,EL) ) {\n");
	fprintf(out,"\t\treturn tabindex;\n");
	fprintf(out,"\t}\n");

	fprintf(out,"\tif( num != 1 && hashtable[tabindex].numb == num && hashtable[tabindex].attr == dynind ) {\n");
	fprintf(out,"\t\tint comp=1;\n");

	fprintf(out,"\t\tELEMENT *Q = (ELEMENT*)mxs_etop(_c,0,hashtable[tabindex].elem);\n\n");
	fprintf(out,"\t\tfor(i=0;i<num;i++) {\n");
	fprintf(out,"\t\t\tif( !mxs_eq(_c,0,EP[i],Q[i]) ) comp=0;\n");
	fprintf(out,"\t\t}\n");
	fprintf(out,"\t\tif(comp) return tabindex;\n");
	fprintf(out,"\t}\n");

	fprintf(out,"\ttabindex =  (tabindex + coll) %% HASHTABSIZE ;\n");
	fprintf(out,"\tcoll += 2 ;\n");

	fprintf(out,"  } while( tabindex != hnumb );\n");
	fprintf(out,"return (-1);\n}\n\n");

	fprintf(out,"static int dynerr_count = 0;\n\n");

	fprintf(out,"static void dyn_error( char *file, int line ) {\n");
	fprintf(out,"\tfprintf(stderr,\"*** sort of update in \\\"%%s\\\", line %%d is incorrect !\\n\",file,line);\n");

	fprintf(out,"\tif( ++dynerr_count == 10 ) {\n");
	fprintf(out,"\t\tfprintf(stderr,\"*** too many errors in dynamic semantic !\\n\");\n");
	fprintf(out,"\t\texit( EXIT_FAILURE );\n");
	fprintf(out,"\t}\n}\n\n");
}


static void blanks( int n ){
	while( n-- > 0 ) fprintf(out,"\t");
}

ELEMENT DNL_insert( ELEMENT DNL, ELEMENT N ) {
	if(numsubterms(DNL)==0) return appback(DNL,N);
	if(subterm(1,DNL)==N) return DNL;
	if(subterm(1,DNL) > N) return appfront(N,DNL);
return appfront(subterm(1,DNL),DNL_insert(back(DNL),N));
}

long case_elem( ELEMENT EL, ELEMENT SET ) {
	int i, bound;
	bound = numsubterms(SET);
	for(i=1;i<=bound;i++) if(EL==subterm(i,SET)) return 1L;

return 0L;
}

void gen_guards_UL( ELEMENT, int );

long contains_term( ELEMENT TB ) {
	int i, bound;

	bound = numsubterms(TB);
	for(i=1;i<=bound;i++) {
		if(atoe("Term")==idtos(term(son(1,subterm(i,TB))))) return 1L;
	}
return 0L;
}

void gen_guards_case( ELEMENT UR, int indent ) { /* UR is CaseRule */
	int i, j, bound, bound2;

	ELEMENT CL = son(2,UR), EL = son(3,UR), TB, NB, CO, TUL, NUL;
	ELEMENT CTL = CaseTripelList(), DNL;

	blanks(indent);
	fprintf(out,"switch(");
	genc_top(son(1,UR));
	fprintf(out,") {\n");

	TUL = NUL = UListNodeList();

	bound = numsons(CL);
	for(i=1;i<=bound;i++) {
		ELEMENT C = son(i,CL);
		CO = son(1,C);

		switch(sort(CO)) { /* CO is CaseConst@ */
		case _SortConst_:
			NB = node_basesorts(son(1,CO));
			if(NB==AllNodes()) {
				NB = DefIdNodeList();
				NUL = appback(NUL,son(2,C));
			}
			TB = term_basesorts(son(1,CO));
			if(contains_term(TB)) {
				TUL = appback(TUL,son(2,C));
			}
			CTL= appback(CTL,CaseTripel(TB,NB,son(2,C)));
			break;
		case _CharConst_:
			blanks(indent); fprintf(out,"  case '%c' :\n",etoc(term(son(1,CO))));
			gen_guards_UL(son(2,C),indent+1);
			blanks(indent); fprintf(out,"\tbreak;\n");
			break;
		case _IntConst_:
			blanks(indent); fprintf(out,"  case %d :\n",etoi(term(son(1,CO))));
			gen_guards_UL(son(2,C),indent+1);
			blanks(indent); fprintf(out,"\tbreak;\n");
			break;
		}
	}
	DNL = DefIdNodeList();
	bound = numsubterms(CTL);
	for(i=1;i<=bound;i++) {
		bound2 = numsubterms(subterm(1,subterm(i,CTL)));
		for(j=1;j<=bound2;j++) {
			ELEMENT D = subterm(j,subterm(1,subterm(i,CTL)));
			if(atoe("Term")!=idtos(term(son(1,D))))	 DNL = DNL_insert( DNL, D );
		}
	}
	bound = numsubterms(DNL);
	for(i=1;i<=bound;i++) {
		blanks(indent);
		fprintf(out,"  case _%s :\n",etoa(idtos(subterm(1,term(subterm(i,DNL))))));
		bound2 = numsubterms(CTL);
		for(j=1;j<=bound2;j++) {
			if(case_elem(subterm(i,DNL),subterm(1,subterm(j,CTL)))) {
				gen_guards_UL(subterm(3,subterm(j,CTL)),indent+1);
			}
		}
		blanks(indent); fprintf(out,"\tbreak;\n");
	}

	DNL = DefIdNodeList();
	bound = numsubterms(CTL);
	for(i=1;i<=bound;i++) {
		bound2 = numsubterms(subterm(2,subterm(i,CTL)));
		for(j=1;j<=bound2;j++) {
			DNL = DNL_insert( DNL, subterm(j,subterm(2,subterm(i,CTL))));
		}
	}
	bound = numsubterms(DNL);
	for(i=1;i<=bound;i++) {
		blanks(indent);
		fprintf(out,"  case _%s_ :\n",etoa(idtos(subterm(1,term(subterm(i,DNL))))));
		bound2 = numsubterms(CTL);
		for(j=1;j<=bound2;j++) {
			if(case_elem(subterm(i,DNL),subterm(2,subterm(j,CTL)))) {
				gen_guards_UL(subterm(3,subterm(j,CTL)),indent+1);
			}
		}
		blanks(indent); fprintf(out,"\tbreak;\n");
	}



	if(numsons(EL)) { /* else-branch */
		blanks(indent); fprintf(out,"  default:\n");
		gen_guards_UL(EL,indent+1);
	}
	blanks(indent);
	fprintf(out,"}\n");

	if(TUL!=UListNodeList()) { /* Updates for all terms */
		blanks(indent);
		fprintf(out,"i = ");
		genc_top(son(1,UR));
		fprintf(out,";\n");
		blanks(indent);
		fprintf(out,"sortcd = i; classcd = (i>>24)&0xff;\n");

		blanks(indent);
		fprintf(out,"if( classcd==SORTCONST_CL && sortcd <= TERM_SORTCD) {\n");
		bound = numsubterms(TUL);
		for(i=1;i<=bound;i++) {
			gen_guards_UL(subterm(i,TUL),indent+1);
		}
		blanks(indent);
		fprintf(out,"}\n");
	}

	if(NUL!=UListNodeList()) { /* Updates for all nodes */
		blanks(indent);
		fprintf(out,"i = ");
		genc_top(son(1,UR));
		fprintf(out,";\n");
		blanks(indent);
		fprintf(out,"sortcd = i; classcd = (i>>24)&0xff;\n");

		blanks(indent);
		fprintf(out,"if( classcd==SORTCONST_CL && sortcd >= NODE_SORTCD) {\n");
		bound = numsubterms(NUL);
		for(i=1;i<=bound;i++) {
			gen_guards_UL(subterm(i,NUL),indent+1);
		}
		blanks(indent);
		fprintf(out,"}\n");
	}
}

void gen_guards_UR( ELEMENT UR, int indent ) { /* UR is UpdateOrRule */

	switch(sort(UR)) {
		case _IfRule_:
			blanks(indent); fprintf(out,"if( ");

			genc_top( son(1,UR) );

			fprintf(out," )\n");
			blanks(indent); fprintf(out,"{\n");
			gen_guards_UL(son(2,UR),indent+1);
			if( numsons(son(3,UR)) ) {
				blanks(indent); fprintf(out,"} else {\n");
				gen_guards_UL(son(3,UR),indent+1);
			}
			blanks(indent); fprintf(out,"}\n");
			break;

		case _CaseRule_:
			gen_guards_case( UR, indent );
			break;

		case _Update_:
			blanks(indent); fprintf(out,"updlhs[updnum] = mxd_adr_%s(_m,%d",
				etoa(idtos(term(son(1,son(1,son(1,UR)))))), term(son(2,son(1,son(1,UR)))) );
			genc_list( son(2,son(1,UR)) );

			fprintf(out,";\n");

			blanks(indent); fprintf(out,"updrhs[updnum++] = ");
			genc_top(son(2,UR));
			fprintf(out,";\n");

			break;

	}
}

void gen_guards_UL( ELEMENT UL, int indent ) { /* UL is RuleList */
	int i, bound;
	bound = numsons(UL);
	for(i=1;i<=bound;i++) gen_guards_UR(son(i,UL),indent);
}


void gen_dynadr( ELEMENT N ) { /* sort(N) = _DynFunc_ */
	ELEMENT SL;
	int i, bound;

	SL = son(2,N);

	if( (numsons(SL)==1 && !is_enumerable(son(1,SL)) ) || numsons(SL)>1 ) fprintf(out,"int tabind;\n");

	bound = numsons(SL);
	for(i=1;i<=bound;i++) {
		ELEMENT S2 = son(i,SL);
		ELEMENT S3 = son(i,son(3,N));

		fprintf(out,"\tif( !mxs_is(_c,0,%s,_%s%c)) {\n",etoa(idtos(term(son(1,S3)))),
			etoa(idtos(term(son(1,S2)))),is(S2,_NodeSortId_)?'_':' ' );

		fprintf(out,"\t\tdyn_error( file, line );\n");
		fprintf(out,"\t\tmxd_dummy = mxs_nil(_c,0);\n");
		fprintf(out,"\t\treturn &mxd_dummy;\n\t}\n");
	}

	if(numsons(SL)==0) {
		fprintf(out,"return &mxd_data_%s;\n",etoa(idtos(term(son(1,son(1,N))))));
	} else if(numsons(SL)==1 && is_enumerable(son(1,SL)) ) {
		fprintf(out,"/* wie Attribut */\n");
		fprintf(out,"return &mxd_data_%s[ mxs_index(_c,0,%s,_%s%c) ];\n",
			etoa(idtos(term(son(1,son(1,N))))),etoa(idtos(term(son(1,son(1,son(3,N)))))),
			etoa(idtos(term(son(1,son(1,son(2,N)))))),is(son(1,son(2,N)),_NodeSortId_)?'_':' ' );

	} else {
		fprintf(out,"/* Hashtabelle */\n");

		bound = numsons(SL);
		fprintf(out,"\ttabind = enter( dynhash( %d",bound);

		for(i=1;i<=bound;i++) {
			fprintf(out,", mxd_key(%s)",etoa(idtos(term(son(1,son(i,son(3,N)))))));
		}

		fprintf(out," ), mxd_hashtab, %d, %d",index(N,_DynFunc_),bound);
		for(i=1;i<=bound;i++) fprintf(out,", %s",etoa(idtos(term(son(1,son(i,son(3,N)))))));
		fprintf(out," );\n");


		fprintf(out,"\tif( tabind==-1 ) {\n");
		fprintf(out,"\t\tfprintf(stderr,\"*** Dyn. hashtable full !\\n\");\n");
		fprintf(out,"\t\texit(EXIT_FAILURE);\n");
		fprintf(out,"\t}\n");

		fprintf(out,"return &mxd_hashtab[tabind].value;\n");
	}
}

void gen_dyndata( void ) {
	int i, bound;

	fprintf(out,"ELEMENT mxd_dummy;\n\n");

	bound = number(_DynSemInput_);
	for(i=1;i<=bound;i++) {
		char *s = etoa(idtos(term(son(1,son(1,element(i,_DynSemInput_))))));
		fprintf(out,"ELEMENT mxd_data_%s;\n",s);
	}

	bound = number(_DynFunc_);
	for(i=1;i<=bound;i++) {
		ELEMENT N  = element(i,_DynFunc_);
		ELEMENT NL = son(3,N);
		int bound2 = numsons(NL);
		char *s    = etoa(idtos(term(son(1,son(1,N)))));

		if(bound2==0) { /* wie globale Variable */
			fprintf(out,"ELEMENT mxd_data_%s;\n",s);
		}
		if(bound2==1 && is_enumerable(son(1,son(2,N))) ) { /* wie Attribut */
			fprintf(out,"ELEMENT *mxd_data_%s;\n",s);
		}
	}
	fprintf(out,"\n");
}

static  void aux_prt_lokvar( ELEMENT selem, int count ){
	if( count==0 ) {
		fprintf(out,"ELEMENT %s",etoa(selem));
	} else {
		fprintf(out,", %s",etoa(selem));
	}
}

static  int genc_dynfct_aux( ELEMENT tn, int count ){
	ELEMENT nodev = son(1,tn);

	while(  nodev != nil()  ){
		count = genc_dynfct_aux( nodev, count );
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

void gen_init_dynsem() {
	int declx, bound, i, parnum;
	ELEMENT decln;
	char *declname;

	bound =  number(_DynFunc_) ;
	for( declx = 1; declx <= bound; declx++ ){
		decln    =  element(declx,_DynFunc_);
		declname =  etoa(idtos(term(son(1,son(1,decln)))));
		fprintf(out,"ELEMENT  mxd_init_%s(", declname );
		parnum =  numsons(son(2,decln));


		if( parnum > 0 ){
			ELEMENT parnmln =  son(3,decln);
			fprintf(out," char *mxd_f, int mxd_l,");
			for( i=1 ; i <= parnum ; i++)
				fprintf(out,"%cELEMENT %s", (i==1)?' ':',',
					etoa(idtos(term(son(1,son(i,parnmln))))));
		}
		fprintf(out," ){\n");

		if( genc_dynfct_aux( son(5,decln),0 ) ) fprintf(out,";\n");

		if( parnum > 0 ){
			ELEMENT parname =  son(1,son(3,decln));
			do{
				fprintf(out," IFNIL(%s)", etoa(idtos(term(son(1,parname)))) );
				parname= rbroth( parname );
			} while(  parname != nil()  );
			fprintf(out,"\n");
		}
		if( parnum > 0 ){
			ELEMENT parname =  son(1,son(3,decln));
			ELEMENT parsort =  son(1,son(2,decln));
			i = 1;
			do{
				fprintf(out," IS(%s,", etoa(idtos(term(son(1,parname)))) );
				prtsortconst( parsort );
				fprintf(out,",mxd_f,mxd_l,\"%s\",%d)", declname, i++ );
				parname= rbroth( parname );
				parsort= rbroth( parsort );
			} while(  parname != nil()  );
			fprintf(out,"\n");
		}
		genc_intres(decln,1);

		fprintf(out,"}\n\n");
	}
	fprintf(out,"\n\n");


 	fprintf(out,"#define HASHTABSIZE   32233\n");
	fprintf(out,"typedef struct {\n");
	fprintf(out,"\tELEMENT elem, value;\n");
	fprintf(out,"\tshort attr,numb;\n");
	fprintf(out,"} DYNH_ENTRY;\n\n");
	fprintf(out,"DYNH_ENTRY mxd_hashtab[HASHTABSIZE];\n\n");

	fprintf(out,"ELEMENT  mxd_NILVAL;\n\n");

	fprintf(out,"ELEMENT mxd_key( ELEMENT T ) {\n");
	fprintf(out,"\twhile( mxs_numsubterms(_c,0,T)!=0 ) T=mxs_subterm(_c,0,1,T);\n");
	fprintf(out,"\treturn T;\n");
	fprintf(out,"}\n");


	fprintf(out,"\nvoid  init_dyninput() {\n");
	fprintf(out,"\tint i, bound;\n\n");
	fprintf(out,"\tmxd_NILVAL = mxs_nil(_c,0);\n\n");
	fprintf(out,"\tfor(i=0;i<HASHTABSIZE;i++) mxd_hashtab[i].elem = MAXUNDEF;\n\n");


	bound = number(_DynSemInput_);
	for(i=1;i<=bound;i++) {
		char *s = etoa(idtos(term(son(1,son(1,element(i,_DynSemInput_))))));
		fprintf(out,"\tmxd_data_%s = mxs_nil(_c,0);\n",s);
	}

	bound = number(_DynFunc_);
	for(i=1;i<=bound;i++) {
		ELEMENT NL;
		int bound2;
		ELEMENT N = element(i,_DynFunc_);
		char *s;
		NL = son(3,N);
		bound2 = numsons(NL);

		if(bound2==0) { /* wie globale Variable */
			s = etoa(idtos(term(son(1,son(1,N)))));
			fprintf(out,"\tmxd_data_%s = mxd_init_%s();\n",s,s);
		}
		if(bound2==1 && is_enumerable(son(1,son(2,N))) ) { /* wie Attribut */
			char check = is(son(1,son(2,N)),_NodeSortId_)?'_':' ';
			char *s2 = etoa(idtos(term(son(1,son(1,son(2,N))))));
			s = etoa(idtos(term(son(1,son(1,N)))));

			fprintf(out,"\n\tmxd_data_%s = calloc( mxs_number(_c,0,_%s%c)+1, sizeof(ELEMENT) );\n",s,s2, check );
			fprintf(out,"\tif( mxd_data_%s == 0L ) {\n",s);
			fprintf(out,"\t\tfprintf(stderr,\"*** couldn't allocate space for %s\\n\");\n",s);
			fprintf(out,"\t\texit( EXIT_FAILURE );\n");
			fprintf(out,"\t}\n");

			fprintf(out,"\tbound = mxs_number(_c,0,_%s%c);\n",s2,check);
			fprintf(out,"\tfor(i=1;i<=bound;i++) {\n\t\tmxd_data_%s[i] = ",s);
			fprintf(out,"mxd_init_%s(__FILE__,__LINE__,mxs_element(_c,0,i,_%s%c));\n\t}\n",s,s2,check);
		}
	}
	fprintf(out,"}\n\n");
}

void dyn_defines( FILE *out ) {
	int i, j, bound, bound2;

	fprintf(out,"extern   void init_dyninput( void );\n");
	fprintf(out,"extern   void eval_dynsem( void );\n");
	fprintf(out,"extern   ELEMENT mxd_dummy;\n");

	fprintf(out,"#define SORTCONST_CL 0xE4\n");
	fprintf(out,"#define NODE_SORTCD  2\n");
	fprintf(out,"#define TERM_SORTCD -2\n");

	bound = number(_DynSemInput_);
	for(i=1;i<=bound;i++) {
		char *s = etoa(idtos(term(son(1,son(1,element(i,_DynSemInput_))))));
		fprintf(out,"extern   ELEMENT mxd_data_%s;\n",s);
		fprintf(out,"#define  mxs_%s(f,l) mxd_data_%s\n",s,s);
		fprintf(out,"#define  %s mxd_data_%s\n",s,s);
	}

	bound = number(_DynFunc_);
	for(i=1;i<=bound;i++) {
		ELEMENT SN, N = element(i,_DynFunc_);
		char *s = etoa(idtos(term(son(1,son(1,N)))));
		SN = son(3,N);

		if(numsons(SN)==0) {
			fprintf(out,"extern   ELEMENT mxd_data_%s;\n",s);
			fprintf(out,"#define  mxs_%s(f,l) mxd_data_%s\n",s,s);
			fprintf(out,"#define  %s          mxd_data_%s\n",s,s);
			fprintf(out,"#define  mxd_adr_%s(f,l) &mxd_data_%s\n",s,s);
			fprintf(out,"#define  mxd_upd_%s(f,l) &mxd_data_%s\n",s,s);
		} else {
			fprintf(out,"extern   ELEMENT *mxd_adr_%s( char *, int",s);
			bound2 = numsons(SN);
			for(j=1;j<=bound2;j++) fprintf(out,", ELEMENT");
			fprintf(out," );\n");

			fprintf(out,"#define  mxs_%s( mxd_f, mxd_l",s);
			for(j=1;j<=bound2;j++) fprintf(out,", %s",etoa(idtos(term(son(1,son(j,SN))))));
			fprintf(out," ) ");

			fprintf(out,"(*mxd_adr_%s( mxd_f, mxd_l",s);

			for(j=1;j<=bound2;j++) fprintf(out,", %s",etoa(idtos(term(son(1,son(j,SN))))));

			fprintf(out,"))\n");

			fprintf(out,"#define  %s( %s",s,etoa(idtos(term(son(1,son(1,SN))))));
			for(j=2;j<=bound2;j++) fprintf(out,", %s",etoa(idtos(term(son(1,son(j,SN))))));

			fprintf(out," ) mxs_%s(__FILE__,__LINE__",s);
			for(j=1;j<=bound2;j++) fprintf(out,", %s",etoa(idtos(term(son(1,son(j,SN))))));
			fprintf(out," )\n");
		}
	}
}


void dynsem_gen( FILE *cout ) {
	int i, bound, j, bound2;

	if(number(_Rule_)==0) return;

	out = cout;

	printf("+++ generating code for dynamic semantics\n");

	fprintf(out,"\n\n/* Code for dynamic semantics */\n\n");

	gen_dyndata();
	gen_init_dynsem();
	gen_dynhash();

	bound = number(_DynFunc_);
	for(i=1;i<=bound;i++) {
		ELEMENT N = element(i,_DynFunc_);
		ELEMENT NL = son(3,N);
		bound2 = numsons(NL);

		if(bound2==0) continue;

		fprintf(out,"ELEMENT  *mxd_adr_%s( char *file, int line ",
			etoa(idtos(term(son(1,son(1,element(i,_DynFunc_)))))) );

		for(j=1;j<=bound2;j++) {
			fprintf(out,", ELEMENT %s",etoa(idtos(term(son(1,son(j,NL))))));
		}
		fprintf(out," ) {\n");

		gen_dynadr(element(i,_DynFunc_));

		fprintf(out,"}\n\n");
	}

	fprintf(out,"void eval_dynsem( ) {\n");
	fprintf(out,"\tlong  i, updnum;\n");
	fprintf(out,"\tshort sortcd,classcd;\n");
	bound = number(_Update_);
	fprintf(out,"\tELEMENT *updlhs[%d];\n",bound);
	fprintf(out,"\tELEMENT  updrhs[%d];\n\n",bound);

	fprintf(out,"  do {\n");

	fprintf(out,"\tupdnum = 0;\n");

	bound = number(_RuleList_);
	for(i=1;i<=bound;i++) gen_guards_UL(element(i,_RuleList_), 1 );

	fprintf(out,"\n\tfor(i=0;i<updnum;i++) {\n");
	fprintf(out,"\t\t*updlhs[i] = updrhs[i];\n");
	fprintf(out,"\t}\n");

/*	fprintf(out,"\tprintf(\"Step : %%d rules applied\\n\",updnum);\n");  */
	fprintf(out,"  } while(updnum);\n");
	fprintf(out,"}\n\n");
}

/* Ende */

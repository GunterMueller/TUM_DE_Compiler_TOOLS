#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef Solaris
#include <strings.h>
#endif

#include "max_spec.h"
#include "max.h"

extern struct OPT   max_options;

static FILE    *out;  /* actual output file */
static ELEMENT SemTokenList, TokenList, CharList, PreDeclProdList, ReachableProdList;

#define  PREDECL_CLASSPROD  1  /* number of predeclared ClassProd */

#ifndef MAXPATHNAME
#define MAXPATHNAME  ""
#endif

static  int pars_mode;

#define TMPSTRLEN 500
static  char tmpstr[TMPSTRLEN];


#define HOST_SUN 1
#define HOST_HP  2

int get_hosttype() { /* yields 0 for unknown host */
	int ht;
	char *s;

	s = getenv("HOSTTYPE");
	if(s==0L) s = getenv("HOST");

	ht=0;
	if(s[0]=='s' && s[1]=='u' && s[2]=='n')	ht=HOST_SUN;
	else if(s[0]=='h' && s[1]=='p')		ht=HOST_HP;

return ht;
}

/*** external attributes *********************/

static ELEMENT	LPcodes = LsideList(),
		TPcodes = LsideList(),
		CPcodes = LsideList();

static ELEMENT	LPrside = LPinfoListlist(),
		TPrside = RsideList(),
		CPrside = CPinfoListlist();

void mxy_enterlp( ELEMENT S, ELEMENT X ) {
	LPcodes = appback( LPcodes, X );
	LPrside = appback( LPrside, S );
}

ELEMENT mxy_entercp( ELEMENT L, ELEMENT X, ELEMENT pid ) { /* X is Parsinfo, L is CPlist */
ELEMENT ID, R = SortIdList();
int i, bound;

	CPcodes = appback( CPcodes, X );
	CPrside = appback( CPrside, L );

	bound = numsubterms(L)-1;
	for(i=1;i<=bound;i++) {
		R = appback( R, subterm(2,subterm(i,L)) );
	}
	ID = subterm(2,subterm(bound+1,L));
	if( pid != subterm(1,ID) ) {
		R = appback( R, ID );
	}
	if( numsubterms(R)==0 ) {
		fprintf(stderr,"*** ClassProd for \"%s\" has an empty right side!\n",etoa(idtos(pid)));
		exit( EXIT_FAILURE );
	}
return R;
}

ELEMENT mxy_entertp( ELEMENT L, ELEMENT X ) {
int	i, bound;
ELEMENT R = SortIdList();
ELEMENT T = TermSortId(stoid(atoe("Int")),0,0);

	TPcodes = appback( TPcodes, X );
	TPrside = appback( TPrside, L );

	bound = numsubterms(L);
	for(i=1;i<=bound;i++) {
		ELEMENT Y = subterm(i,L);
		switch(sort(Y)) {
			case _TermSortId :
			case _NodeSortId :
				R = appback(R,Y);
			break;
			case _Parsline :
			case _Parscol :
				R = appback(R,T);
			break;
		}
	}
return R;
}

/*********************************************/

static ELEMENT *parscodetab;

long init_parscode( void ) {
int i, k, bound;

	parscodetab = (ELEMENT *)calloc( number(_Production_)+1, sizeof(ELEMENT) );
	if( parscodetab==0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate parscode table \n");
		exit( EXIT_FAILURE );
	}

	bound = number(_Production_);
	for(i=1;i<=bound;i++) {
		ELEMENT N = element(i,_Production_);

		switch(sort(N)) {
		  case _TupelProd_:
			parscodetab[i] = subterm(index(N,_TupelProd_),TPcodes);
			break;
		  case _ListProd_:
			parscodetab[i] = subterm(index(N,_ListProd_),LPcodes);
			break;
		  case _ClassProd_:
			k = index(N,_ClassProd_) - PREDECL_CLASSPROD;
			parscodetab[i] = (k>0) ? subterm(k,CPcodes) : Parsno();
			break;
		  case _PredeclProd_:
			parscodetab[i] = nil();
			break;
		}
	}

return 1L;
}

long  free_parscode( void ){
	return 1L;
}

ELEMENT parscode( ELEMENT N ){
	return  parscodetab[ index( N,_Production_) ];
}

/*********************************************/

static ELEMENT *LPsepsymbolstab;

long init_LPsepsymbols( void ) {
int i, bound;
ELEMENT L;

	LPsepsymbolstab = (ELEMENT *)calloc( number(_ListProd_)+1, sizeof(ELEMENT) );
	if( LPsepsymbolstab==0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate LPsepsymbols table \n");
		exit( EXIT_FAILURE );
	}

	bound = number(_ListProd_);
	for(i=1;i<=bound;i++) {
		L = subterm(i,LPrside);
		LPsepsymbolstab[i] = (L==LPinfolist()) ? appback(LPinfolist(),ParsStern(atoe(""))) : L;
	}
return 1L;
}

long  free_LPsepsymbols( void ) {
	return 1L;
}

ELEMENT LPsepsymbols( ELEMENT N ) {
	return LPsepsymbolstab[ index(N,_ListProd_) ];
}

/*********************************************/

static ELEMENT *TPconcrSyntaxtab;

long init_TPconcrSyntax( void ) {
int i, bound;

	TPconcrSyntaxtab = (ELEMENT *)calloc( number(_TupelProd_)+1, sizeof(ELEMENT) );
	if( TPconcrSyntaxtab==0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate TPconcrSyntax table \n");
		exit( EXIT_FAILURE );
	}

	bound = number(_TupelProd_);
	for(i=1;i<=bound;i++) {
		TPconcrSyntaxtab[i] = subterm(i,TPrside);
	}
return 1L;
}

ELEMENT TPconcrSyntax( ELEMENT N ) {
	return TPconcrSyntaxtab[ index(N,_TupelProd_) ];
}

long  free_TPconcrSyntax( void ) {
	return 1L;
}

/*********************************************/

static ELEMENT *CPrsideinfotab;

long init_CPrsideinfo( void ) {
int i, bound;

	CPrsideinfotab = (ELEMENT *)calloc( number(_ClassProd_)+1, sizeof(ELEMENT) );
	if( CPrsideinfotab==0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate CPrsideinfo table \n");
		exit( EXIT_FAILURE );
	}
	bound = number(_ClassProd_);
	for(i=1;i<=PREDECL_CLASSPROD;i++) {
		CPrsideinfotab[i] = nil();
	}
	for(i=1+PREDECL_CLASSPROD;i<=bound;i++) {
		CPrsideinfotab[i] = subterm(i-PREDECL_CLASSPROD,CPrside);
	}
return 1L;
}

ELEMENT CPrsideinfo( ELEMENT N ) {
	return CPrsideinfotab[ index(N,_ClassProd_) ];
}

long free_CPrsideinfo( void ) {
	return 1L;
}

/*********************************************/

static ELEMENT *ExchangeTripeltab;

static void aux_init_ExTripel( ELEMENT N, ELEMENT T ) {
int i, bound;
ELEMENT X;

	switch(sort(N)) {
		case _TupelProd_:
			X = parscode(N);
			if( X==Parsleft() || X==Parsright() ) {
				ExchangeTripeltab[index(N,_TupelProd_)] = T;
			}
		break;
		case _ClassProd_:
			bound = numsons(son(2,N));
			for(i=1;i<=bound;i++) {
				aux_init_ExTripel(fath(decl(son(i,son(2,N)))),T);
			}
		break;
	}
}

long init_ExchangeTripel( void ) {
int i, j, bound, bound2;
ELEMENT N, id1, id2, id3;

	ExchangeTripeltab = (ELEMENT *)calloc( number(_TupelProd_)+1, sizeof(ELEMENT) );
	if( ExchangeTripeltab==0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate ExchangeTripel table \n");
		exit( EXIT_FAILURE );
	}

	bound = number(_TupelProd_);
	for(i=1;i<=bound;i++) {
		ExchangeTripeltab[i] = nil();
	}


	/** Init mit den wirklichen Werten **/

	bound = number(_ClassProd_);
	for(i=1;i<=bound;i++) {
		N = element(i,_ClassProd_);
		if( !is(parscode(N),_Parsprio) ) continue;

		bound2 = numsons(son(2,N));
		for(j=1;j<bound2;j++) {
			id1 = term(son(1,son(1,N)));
			id2 = term(son(1,son(j,son(2,N))));
			id3 = term(son(1,son(j+1,son(2,N))));
			aux_init_ExTripel( fath(decl(son(j,son(2,N)))), IdentTripel( id1,id2,id3 ));
		}
		id1 = term(son(1,son(1,N)));
		id2 = term(son(1,son(j,son(2,N))));
		id3 = term(son(1,son(1,N)));
		aux_init_ExTripel( fath(decl(son(j,son(2,N)))), IdentTripel( id1,id2,id3 ));
	}


return 1L;
}

ELEMENT ExchangeTripel( ELEMENT N ) {
	return ExchangeTripeltab[ index(N,_TupelProd_) ];
}

long  free_ExchangeTripel( void ) {
	return 1L;
}

/*********************************************/

static ELEMENT *ExtraRuletab;

long init_ExtraRule( void ) {
int i, j, bound, bound2;
ELEMENT N;

	ExtraRuletab = (ELEMENT *)calloc( number(_Production_)+1, sizeof(ELEMENT) );
	if( ExtraRuletab==0L ) {
		fprintf(stderr,"\n***** Error: Cannot allocate ExtraRule table \n");
		exit( EXIT_FAILURE );
	}

	bound = number(_Production_);
	for(i=1;i<=bound;i++) {
		ExtraRuletab[i] = nil();
	}
	bound = number(_ClassProd_);
	for(i=1;i<=bound;i++) {
		N = element(i,_ClassProd_);
		if( !is(parscode(N),_Parsprio) ) continue;

		bound2 = numsons(son(2,N));
		for(j=1;j<bound2;j++) { /* nur bis zum vorletzten Sohn */
			ExtraRuletab[index(fath(decl(son(j,son(2,N)))),_Production_)]
			 = term(son(1,son(j+1,son(2,N))));
		}
		ExtraRuletab[index(fath(decl(son(bound2,son(2,N)))),_Production_)] = N;
	}

return 1L;
}

ELEMENT ExtraRule( ELEMENT N ) {
	return ExtraRuletab[ index(N,_Production_) ];
}

long  free_ExtraRule( void ) {
	return 1L;
}

/*****************************************************/

static long elem( ELEMENT E, ELEMENT L ) { /* tests, if E is a subterm of L */
int i, bound;

	bound = numsubterms(L);
	for(i=1;i<=bound;i++) {
		if(E==subterm(i,L)) return 1L;
	}
return 0L;
}


/************************/

static void grsym_in_parstree( ELEMENT P ) { /* yields all possible sorts in the syntaxtree */
int i,bound;

  if( is(P,_PredeclProd_) ) {

	if( !elem(P,PreDeclProdList)) PreDeclProdList = appback( PreDeclProdList, P);
  } else {
	if( (parscode(P) != Parsno() || (pars_mode & SYN_ABSTRACT)) && !elem(P,ReachableProdList) ) {
		ReachableProdList = appback(ReachableProdList,P);
		switch(sort(P)) {
			case _ListProd_ :
				grsym_in_parstree( fath(decl(son(2,P))) );
				break;
			case _TupelProd_:
				bound = numsons(son(2,P));
				for(i=1;i<=bound;i++) {
					grsym_in_parstree( fath(decl(son(i,son(2,P)))) );
				}
				break;
			case _ClassProd_:
				bound = numsons(son(2,P));
				for(i=1;i<=bound;i++) {
					grsym_in_parstree( fath(decl(son(i,son(2,P)))) );
				}
				break;

		}
	}
  }
}


static void init_grammarsymbols( void ) {
ELEMENT X;
int i, bound;
static  int initialized = 0;

	if( initialized ) return;
	initialized = 1;

	ReachableProdList = ProdNodeList();
	PreDeclProdList = ProdNodeList();

	grsym_in_parstree( fath(decl(son(2,element(1,_Structure_)))) );

	if( pars_mode & SYN_CONCRETE ) {
		bound = number(_Production_);
		for(i=1;i<=bound;i++) {
			X = element(i,_Production_);
			if( parscode(X)==Parsaux() )  grsym_in_parstree( X );
		}
	}
}


static void addstring( char *s, int seminfo ) {
ELEMENT ide;

	if(seminfo) {
		ide = stoid(atoe(s));
		if(!elem(ide,SemTokenList)) SemTokenList = appback(SemTokenList,ide);
	} else
	switch(strlen(s)) {
		case 0: break;
		case 1: ide = ctoe(s[0]);
			if( !elem(ide,CharList)) CharList = appback(CharList,ide);
			break;
		default :
			ide = stoid(atoe(s));
			if(!elem(ide,TokenList)) TokenList = appback(TokenList,ide);
			break;
	}
}


static void addtoken( char *t ) {
int i;
char *s;

	if( strlen(t)>=TMPSTRLEN-1 ) {
		fprintf(stderr,"+++ Token too long !\n");
		exit( EXIT_FAILURE );
	}
	strcpy(tmpstr,t);

	for(s=tmpstr;*s!=0 && *s!='\'';s++) ;
	if(*s==0) return; else s++;

	/* s zeigt aufs erste Tokenzeichen */

	for(i=0;s[i]!=0 && s[i]!='\'';i++) ;
	if(s[i]==0) return; else i++;

	/* s ist Token */

	s[i-1] = 0;
	addstring(s,0);
	s[i-1] = '\'';

	addtoken( &s[i] );
}


static void init_aux_lists( void ) {
int i, bound, j, bound2;
ELEMENT P, N;

	TokenList = IdentList();
	SemTokenList = IdentList();
	CharList = CharList();

/*** collects all tokens and single characters ***/

    if( pars_mode & SYN_CONCRETE ) {
	bound = numsubterms(ReachableProdList);
	for(i=1;i<=bound;i++) {
		N = subterm(i,ReachableProdList);
		switch(sort(N)) {
		  case _TupelProd_ :
			P = TPconcrSyntax(N);
			bound2 = numsubterms(P);
			for(j=1;j<=bound2;j++) {
				if(is(subterm(j,P),_String)) {
					addstring(etoa(subterm(j,P)),
						(j<bound2 && subterm(j+1,P)==Parspos())
					);
				}
			}
			break;
		  case _ListProd_ :
			P = LPsepsymbols(N);
			bound2 = numsubterms(P);
			for(j=1;j<=bound2;j++) {
				addstring(etoa(subterm(1,subterm(j,P))),0);
			}
			break;
		  case _ClassProd_ :
			P = CPrsideinfo(N);
			bound2 = numsubterms(P);
			for(j=1;j<=bound2;j++) {
				int k, bound3;
				ELEMENT Q = subterm(j,P);
				bound3 = numsubterms(subterm(1,Q));
				for(k=1;k<=bound3;k++) addstring(etoa(subterm(k,subterm(1,Q))),0);
				bound3 = numsubterms(subterm(3,Q));
				for(k=1;k<=bound3;k++) addstring(etoa(subterm(k,subterm(3,Q))),0);
			}
		  break;
		}
	}

	bound = number(_Production_);
	for(i=1;i<=bound;i++) {
		N = parscode(element(i,_Production_));
		if( is(N,_Parsrule) || is(N,_Parsaddrule) ) {
			bound2 = numsubterms(subterm(1,N));
			for(j=1;j<=bound2;j++) {
				addtoken(etoa(subterm(j,subterm(1,N))));
			}
		}
	}
    }

/*** round braces and colon for abstract syntax ***/

	if( pars_mode & SYN_ABSTRACT ) {
	 	P = ctoe('(');	if( !elem(P,CharList)) CharList = appback(CharList,P);
		P = ctoe(')');	if( !elem(P,CharList)) CharList = appback(CharList,P);
		P = ctoe(',');	if( !elem(P,CharList)) CharList = appback(CharList,P);
	}
}


/*** Generation of the LEX-Datei ***/

static void lexprintf( char *s ) {

	while(*s) {
		if(*s != '\\') fprintf(out,"%c",*s);
		else {
			s++;
			if(*s != 0 ) fprintf(out,"%c",*s);
			else break;
		}
		s++;
	}
}


static void mxy_lexgen( void ) {
int i, bound;
char *s, tmp[2], c;
ELEMENT ide;

	printf("+++ generating the lex-file\n");

	fprintf(out,"%%{\n#define TABLENGTH 3\n\n");
	fprintf(out,"int   line = 1 ;\n");
	fprintf(out,"int column = 0 ;\n\n");
	fprintf(out,"%%}\n");

	fprintf(out,"%%%%\n\n");
	fprintf(out,"[ ]*\t{ column += yyleng; }\n");
	fprintf(out,"\\n\t{ line++; column = 0; }\n");
	fprintf(out,"\\t\t{ column += TABLENGTH; }\n");

/*** different sorts of tokens ***/

	if( pars_mode & SYN_ABSTRACT ) {
		bound = numsubterms(ReachableProdList);
		for(i=1;i<=bound;i++) {
			ide = term(son(1,son(1,subterm(i,ReachableProdList))));
			s = etoa(idtos(ide));
			fprintf(out,"%s/\\(\t{ column += yyleng; return(TOK%d); }\n",
				s,index(ide,_Ident));
		}
	}

/* all tokens with several characters ***/

	bound = numsubterms(TokenList);
	for(i=1;i<=bound;i++) {
		ide = subterm(i,TokenList);

		if( elem(ide,SemTokenList) ) continue;

		s = etoa(idtos(ide));
		if( s[0]==0 ) continue;
		if( s[0]=='\\' && s[1]=='\\' ) {
			lexprintf(&s[2]);
			fprintf(out,"\t{ column += yyleng;  return(TOK%d); }\n",index(ide,_Ident));
		} else {
			fprintf(out,"\"");
			lexprintf(s);
			fprintf(out,"\"\t{ column += yyleng;  return(TOK%d); }\n",index(ide,_Ident));
		}
	}

	bound = numsubterms(SemTokenList);
	for(i=1;i<=bound;i++) {
		ide = subterm(i,SemTokenList);
		s = etoa(idtos(ide));
		if( s[0]==0 ) continue;
		if( s[0]=='\\' && s[1]=='\\' ) {
			lexprintf(&s[2]);
		} else {
			fprintf(out,"\"");
			lexprintf(s);
			fprintf(out,"\"");
		}
		fprintf(out,"\t{\t\n");
		fprintf(out,"\t\tyylval.lc.l = itoe( line );\n");
		fprintf(out,"\t\tyylval.lc.c = itoe( column );\n");
		fprintf(out,"\t\tcolumn += yyleng;\n");
		fprintf(out,"\t\treturn(TOK%d); }\n",index(ide,_Ident));
	}

/* alle single characters ***/

	bound = numsubterms(CharList);
	for(i=1;i<=bound;i++) {
		c = etoc(subterm(i,CharList));
		tmp[0]=c;
		tmp[1]=0;

		if( elem(stoid(atoe(tmp)),SemTokenList) ) continue;

		fprintf(out,"\"%c\"\t{ column += yyleng;  return('%s%c'); }\n",
			c,(c=='\'')?"\\":"",c);
	}


/*** predefined characters ***/


	bound = numsubterms( PreDeclProdList );
	for(i=bound;i>=1;i--) {
		s = etoa(idtos(term(son(1,son(1,subterm(i,PreDeclProdList))))));

		if(!strcmp(s,"Char")) {
		 fprintf(out,"\n'[a-zA-Z0-9 !@#$%%^&*\\[\\]\\\\{}|()_\\-+=~`\":;<>,.?/]' {\n");
		 fprintf(out,"\tyylval.vlc.v = ctoe((char)yytext[1]);\n");
		 fprintf(out,"\tyylval.vlc.l = itoe(line);\n");
		 fprintf(out,"\tyylval.vlc.c = itoe(column+1);\n");
		 fprintf(out,"\tcolumn += yyleng;\n");
		 fprintf(out,"\treturn(CharNt); }\n\n");
		}
		else if(!strcmp(s,"Int")) {
		 fprintf(out,"-?[0-9][0-9]* {\n");
		 fprintf(out,"\tyylval.vlc.v = itoe(atoi((char*)yytext));\n");
		 fprintf(out,"\tyylval.vlc.l = itoe(line);\n");
		 fprintf(out,"\tyylval.vlc.c = itoe(column+1);\n");
		 fprintf(out,"\tcolumn += yyleng;\n");
		 fprintf(out,"\treturn(IntNt); }\n\n");
		}
		else if(!strcmp(s,"String")) {
		 fprintf(out,"\\\"([a-zA-Z0-9 !@#$%%^&*\\[\\]{}|()_\\-+=~`':;<>,.?/]|\\\\n|\\\\\\\"|\\\\\\\\)*\\\" {\n");
		 fprintf(out,"\tchar *c = (char*)yytext;\n");
		 fprintf(out,"\twhile( *(c++) != '\\0' );\n");
		 fprintf(out,"\tc[-2] = '\\0';\n");
		 fprintf(out,"\tyylval.vlc.v = atoe((char*)yytext+1);\n");
		 fprintf(out,"\tyylval.vlc.l = itoe(line);\n");
		 fprintf(out,"\tyylval.vlc.c = itoe(column+1);\n");
		 fprintf(out,"\tcolumn += yyleng;\n");
		 fprintf(out,"\treturn(StringNt); }\n\n");
		}
		else if(!strcmp(s,"Ident")) {
		 fprintf(out,"[a-zA-Z][a-zA-Z0-9_]* {\n");
		 fprintf(out,"\tyylval.vlc.v = stoid(atoe((char*)yytext));\n");
		 fprintf(out,"\tyylval.vlc.l = itoe(line);\n");
		 fprintf(out,"\tyylval.vlc.c = itoe(column+1);\n");
		 fprintf(out,"\tcolumn += yyleng;\n");
		 fprintf(out,"\treturn(IdentNt); }\n\n");
		}
		else if(!strcmp(s,"Bool")) {
		 fprintf(out,"\"true\" {\n");
		 fprintf(out,"\tyylval.vlc.v = btoe(1);\n");
		 fprintf(out,"\tyylval.vlc.l = itoe(line);\n");
		 fprintf(out,"\tyylval.vlc.c = itoe(column+1);\n");
		 fprintf(out,"\tcolumn += yyleng;\n");
		 fprintf(out,"\treturn(BoolNt); }\n\n");

		 fprintf(out,"\"false\" {\n");
		 fprintf(out,"\tyylval.vlc.v = btoe(0);\n");
		 fprintf(out,"\tyylval.vlc.l = itoe(line);\n");
		 fprintf(out,"\tyylval.vlc.c = itoe(column+1);\n");
		 fprintf(out,"\tcolumn += yyleng;\n");
		 fprintf(out,"\treturn(BoolNt); }\n\n");
		}
		else fprintf(stderr,"+++ error : Nonterminal \"%s\" not allowed in concrete syntax !\n",s);
	}


/* comments */

	fprintf(out,"\"/*\"\t{\tchar c1, c2 = '+';\n");
	fprintf(out,"\t\tcolumn += yyleng;\n");
	fprintf(out,"\t\twhile( 1 ){\n");
	fprintf(out,"\t\t\tc1 = c2;\n");
	fprintf(out,"\t\t\tc2 = input();\n");
	fprintf(out,"\t\t\tif( c2 == '\\0' ){\n");
	fprintf(out,"\t\t\t\tunput(c2);\n");
	fprintf(out,"\t\t\t\tfprintf(stderr,\"max: input file ends with unterminated comment\\n\");\n");
	fprintf(out,"\t\t\t\tbreak;\n");
	fprintf(out,"\t\t\t}\n");
	fprintf(out,"\t\t\tif( c1 == '*' && c2 == '/' ){\n");
	fprintf(out,"\t\t\t\tcolumn++;\n");
	fprintf(out,"\t\t\t\tbreak;\n");
	fprintf(out,"\t\t\t}\n");
	fprintf(out,"\t\t\tif( c2 == '\\n' ){\n");
	fprintf(out,"\t\t\t\tline++; column = 0;\n");
	fprintf(out,"\t\t\t} else {\n");
	fprintf(out,"\t\t\t\tcolumn++;\n");
	fprintf(out,"\t\t\t}\n");
	fprintf(out,"\t\t}\n");
	fprintf(out,"\t}\n\n");

	fprintf(out,"\"//\"\t{\tchar c2 = '+';\n");
	fprintf(out,"\t\tcolumn += yyleng;\n");
	fprintf(out,"\t\twhile( 1 ){\n");
	fprintf(out,"\t\t\tc2 = input();\n");
	fprintf(out,"\t\t\tif( c2 == '\\0' ){\n");
	fprintf(out,"\t\t\t\tunput(c2);\n");
	fprintf(out,"\t\t\t\tfprintf(stderr,\"max: input file ends with unterminated comment\\n\");\n");
	fprintf(out,"\t\t\t\tbreak;\n");
	fprintf(out,"\t\t\t}\n");
	fprintf(out,"\t\t\tif( c2 == '\\n' ){\n");
	fprintf(out,"\t\t\t\tline++; column = 0;\n");
	fprintf(out,"\t\t\t\tbreak;\n");
	fprintf(out,"\t\t\t} else {\n");
	fprintf(out,"\t\t\t\tcolumn++;\n");
	fprintf(out,"\t\t\t}\n");
	fprintf(out,"\t\t}\n");
	fprintf(out,"\t}\n\n");

	fprintf(out,".\t{ return(ERRORSYM); }\n");
}


static void yacctoken_print( FILE *out, int i ) {
static int count = 0;

	if((count++&3)==0) fprintf(out,"\n%%token");
	fprintf(out," TOK%d",i);
}

static void yacctoken_semprint( FILE *out, int i ) {
static int count = 0;

	if((count++&3)==0) fprintf(out,"\n%%token<lc>");
	fprintf(out," TOK%d",i);
}

static void yaccnont_print( FILE *out, char *s, char *t, int j, int k ) {
static int count = 0;

	if((count++&3)==0) fprintf(out,"\n%%type<t>");
	fprintf(out,s,t,j,k);
}


/*** printing the yacc-rules of the productions ***/

static void mxy_yaccrule( ELEMENT L, FILE *out ) {
int i, j, bound;
char *s;

	bound = numsubterms(L);
	for(j=1;j<=bound;j++) {
		s = etoa(subterm(j,L));
		for(;;) {
			for(;*s!=0 && *s!='\'';s++) if(*s!='\\') fprintf(out,"%c",*s);
			if(*s==0) break; else s++;

			/* s points to the first token character */

			for(i=0;s[i]!=0 && s[i]!='\'';i++) ;
			if(s[i]==0) break; else i++;

			/* s is token */

			s[i-1] = 0;

			if(strlen(s)==1) {
				fprintf(out," '%c' ",s[0]);
			} else if(strlen(s) >= 2) {
				fprintf(out," TOK%d ",index(stoid(atoe(s)),_Ident) );
			}
			s[i-1] = '\'';
			s += i;
		}
		fprintf(out,"\n");
	}
}

static int print_string( ELEMENT N ) {
	char *s = etoa(N);
	int ind = index(stoid(N),_Ident);

	if(strlen(s)>1) {
		fprintf(out,"TOK%d ",ind);
		return 1;
	} else if(strlen(s)==1) {
		fprintf(out,"'%s%c' ",s[0]=='\''?"\\":"",s[0]);
		return 1;
	}
return 0;
}

static void additional_rule( ELEMENT N ) {
ELEMENT X, Y, Z;
int count, i, bound;

	Z = ExtraRule(N);

	if( is(Z,_Ident)) {
		fprintf(out,"|\t%sNt\n\t{ $$ = $1; }\n",etoa(idtos(Z)));

	} else if( is(Z,_ClassProd_)) {
		Y = parscode(Z);
		if(is(Y,_Parsprio)) {
		    X = subterm(-1,CPrsideinfo(Z));

		    if( term(son(1,son(1,Z)))==subterm(1,subterm(2,X)) ) {

			fprintf(out,"|\t");
			count = 0;
			bound=numsubterms(subterm(1,X));
			for(i=1;i<=bound;i++)
				count += print_string(subterm(i,subterm(1,X)));

			fprintf(out,"%sNt ",etoa(idtos(subterm(1,subterm(2,X)))));

			bound=numsubterms(subterm(3,X));
			for(i=1;i<=bound;i++)
				print_string(subterm(i,subterm(3,X)));

			fprintf(out,"\n\t{ $$ = $%d; }\n",1+count);
		    }
		}
	}
	X = parscode(N);
	if( is(X,_Parsaddrule) )  mxy_yaccrule( subterm(1,X), out );
}


static void LPout( ELEMENT N ) {
char *s, *s1, *s2;
int ind, i, bound;
ELEMENT L;

	ind = index(N,_ListProd_);
	s  = etoa(id(son(1,son(2,N))));
	s2 = etoa(id(son(1,son(1,N))));

	L = LPsepsymbols( N );

	if( pars_mode & SYN_ABSTRACT ) {
		L = appback( LPinfolist(), subterm(1,L) );
		fprintf(out,"%sSeq%d :\n",s,ind);
		fprintf(out,"\t%sNt\n",s);
		fprintf(out,"\t{ $$ = appback( %s(), $1 ); }\n",s2);

		fprintf(out,"|\t%sSeq%d  ',' %sNt\n",s,ind,s);
		fprintf(out,"\t{ $$ = appback( $1, $3 ); }\n;\n");
	}


	bound = numsubterms(L);
	for(i=1;i<=bound;i++) {
	  s1 = etoa(subterm(1,subterm(i,L)));

		if( i==1 )
			fprintf(out,"%sNt :\n",s2);
		else	fprintf(out,"%sNt%d :\n",s2,i);

	  if( pars_mode & SYN_CONCRETE ) {

		fprintf(out,"\t%sSeq%d_%d\n",s,ind,i);
		fprintf(out,"\t{ $$ = $1; }\n");

		if( is(subterm(i,L),_ParsStern)) {
			fprintf(out,"|\n\t{ $$ = %s(); }\n",s2);
		}
		additional_rule(N);
	  }


	  if( pars_mode & SYN_ABSTRACT ) {

		fprintf(out,"\tTOK%d '(' %sSeq%d ')'\n",
			index(term(son(1,son(1,N))),_Ident),s,ind);

		fprintf(out,"\t{ $$ = $3; }\n");

		if( is(subterm(i,L),_ParsStern) ) {
			fprintf(out,"|\tTOK%d '(' ')'\n",index(term(son(1,son(1,N))),_Ident));
			fprintf(out,"\t{ $$ = %s(); }\n",s2);
		}
	  }
	  fprintf(out,";\n");

	/** end of output of XNt **/

	  if( pars_mode & SYN_CONCRETE ) { /** output of XSeq1_1 a**/

		fprintf(out,"%sSeq%d_%d :\n",s,ind,i);
		fprintf(out,"\t%sNt\n",s);
		fprintf(out,"\t{ $$ = appback( %s(), $1 ); }\n",s2);

		fprintf(out,"|\t%sSeq%d_%d  ",s,ind,i);
		if(strlen(s1)>1) {
			fprintf(out,"TOK%d ",index(stoid(atoe(s1)),_Ident));

		} else if(strlen(s1)==1) {
			fprintf(out,"'%s%c' ",s1[0]=='\''?"\\":"",s1[0]);
		}
		fprintf(out,"%sNt\n",s);
		fprintf(out,"\t{ $$ = appback( $1, $%c ); }\n;\n",strlen(s1)==0?'2':'3');
	  }
	}
}

static void CPout( ELEMENT N ) {
int j, bound, count, i, bound2, count2;
ELEMENT X, P, L;
char *s = etoa(id(son(1,son(1,N))));

	fprintf(out,"%sNt :\n",s);

	L = CPrsideinfo( N );

	if(is(parscode(N),_Parsprio) && ( pars_mode & SYN_CONCRETE )) bound=1;
	else bound = numsons(son(2,N));

	count = 0;
	for(j=1;j<=bound;j++) {
		P = decl(son(j,son(2,N)));
		X = subterm(j,L);

		if( parscode(fath(P))!=Parsno() || (pars_mode & SYN_ABSTRACT)) {

			fprintf(out,"%s\t",(count++==0)?"":"|");
			count2 = 0;

			if( pars_mode & SYN_CONCRETE )
			  for(bound2=numsubterms(subterm(1,X)),i=1;i<=bound2;i++)
				count2 += print_string(subterm(i,subterm(1,X)));

			fprintf(out," %sNt ",etoa(id(son(1,P))));

			if( pars_mode & SYN_CONCRETE )
			  for(bound2=numsubterms(subterm(3,X)),i=1;i<=bound2;i++)
				print_string(subterm(i,subterm(3,X)));

			fprintf(out,"\n\t{ $$ = $%d%s; }\n", 1+count2, is(fath(P),_PredeclProd_)?".v":"" );
		}
	}
	if( count==0 ) {
		fprintf(stderr,"*** error: Nonterminal %s cannot occur in the syntax tree\n",s);
		fprintf(stderr,"           Please declare class-production %s as #ignore !\n",s);
	}

	if( pars_mode & SYN_CONCRETE ) additional_rule(N);
	fprintf(out,";\n");
}

static int isnorekpos( int j, ELEMENT L, ELEMENT id0, ELEMENT X ) {
int i, bound, count;

	count=0;
	bound = numsubterms(L);
	for(i=1;i<=bound;i++) {
		if(is(subterm(i,L),_SortId) && subterm(1,subterm(i,L))==id0) {
			count++;

		}
	}
	if(count<2) return 0L; /* only one possibility -> recursion allowed */

	if(X==Parsright()) {
		bound = numsubterms(L);
		for(i=1;i<=bound;i++) { /* search for leftmost appearance */
			if(is(subterm(i,L),_SortId) && subterm(1,subterm(i,L))==id0) {
				return (i==j);
			}
		}
	} else {
		bound = numsubterms(L);
		for(i=bound;i>=1;i--) { /* search for rightmost appearance */
			if(is(subterm(i,L),_SortId) && subterm(1,subterm(i,L))==id0) {
				return (i==j);
			}
		}
	}
return 0L;
}

static void TPout( ELEMENT N ) {
int i, j, bound, offs, replace, last_marked, marked;
ELEMENT F, L, E, X, RT, id0, id1, id2, id3;
char c, *s, *s1;

	fprintf(out,"%sNt :\n",etoa(id(son(1,son(1,N)))));

    if( pars_mode & SYN_CONCRETE ) {

	L = TPconcrSyntax(N);
	X = parscode(N);

	replace = ( X==Parsleft() || X==Parsright() );

	if( replace ) {
		RT = ExchangeTripel( N );
		id1 = subterm(1,RT);
		id2 = subterm(2,RT);
		id3 = subterm(3,RT);
	}

	last_marked = 0;
	i=0;
	bound = numsubterms(L);
	c = '\t';
	s = etoa(idtos(term(son(1,son(1,N)))));

	for(j=1;j<=bound;j++) {
		E = subterm(j,L);

		switch(sort(E)) {
		case _Parsnr:
			fprintf(stderr,"*** warning: ignoring #%d (%d. item of tuple production %s)\n",
				subterm(1,E),j,s);
		break;
		case _Parspos:
			fprintf(stderr,"*** warning: ignoring #mark (%d. item of tuple production %s)\n",j,s);
		break;
		case _Parsline:
		case _Parscol:
		break;
		case _String:
			if( strlen(etoa(E))==0 ) {
				fprintf(stderr,"*** warning: ignoring \"\" (%d. item of tuple production %s)\n",j,s);
				break;
			}
			marked = (j<bound) && (subterm(j+1,L)==Parspos());
			i++;
			if( marked ) last_marked = i;

			s1 = etoa(E);
			if( elem(stoid(E),SemTokenList) || strlen(s1)!=1 ) {
				fprintf(out,"%cTOK%d",c,index(stoid(E),_Ident));
			} else  fprintf(out,"%c'%s%c'",c,(s1[0]=='\'')?"\\":"",s1[0]);
			c = ' ';

			if( marked ) j++;
		break;
		case _TermSortId:
		case _NodeSortId:
			F = nil();
			i++;

			id0 = subterm(1,E); /* auszugebender Ident */
			if(replace && (id0==id1)) {
				if(isnorekpos(j,L,id0,X)) id0=id3;
				else id0=id2;
			}
			fprintf(out,"%c%sNt",c,etoa(idtos(id0)));
			c = ' ';

			if((j<bound) && is(subterm(j+1,L),_Parspos)) F = subterm(j+1,L);
			if((j<bound) && is(subterm(j+1,L),_Parsnr )) F = subterm(j+1,L);

			switch(sort(F)) {
			 case _Parspos:
				last_marked = i;
			 break;
			 case _Parsnr :
				if(subterm(1,F)!=1) fprintf(out,"%d",subterm(1,F));
			 break;
			}

			if( F != nil() ) j++;
		break;
		}
	}

	fprintf(out,"\n\t{ $$ = %s(",s);

	last_marked = 0;
	i=0;
	offs = 0;
	c = ' ';

	for(j=1;j<=bound;j++) {
		E = subterm(j,L);

		switch(sort(E)) {
		case _Parsnr:
		case _Parspos:
		break;
		case _Parsline:
			offs++;
			if( last_marked==0 ) {
				fprintf(out,"%citoe(line)",c);
			} else {
				fprintf(out,"%c$%d.l",c,last_marked);
			}
			c = ',';
		break;
		case _Parscol:
			offs++;
			if( last_marked==0 ) {
				fprintf(out,"%citoe(col)",c);
			} else {
				fprintf(out,"%c$%d.c",c,last_marked);
			}
			c = ',';
		break;
		case _String:
			i++;
			if( strlen(etoa(E))==0 ) break;

			if( (j<bound) && (subterm(j+1,L)==Parspos()) ) {
				last_marked = i;
				j++;
			}
		break;
		case _TermSortId:
		case _NodeSortId:
			i++;

			if((j<bound) && is(subterm(j+1,L),_Parspos)) { last_marked = i; j++; }
			if((j<bound) && is(subterm(j+1,L),_Parsnr )) { j++; }

			fprintf(out,"%c$%d",c,i);
			c = ',';
			if(is(fath(decl(son(++offs,son(2,N)))),_PredeclProd_)) fprintf(out,".v");
		break;
		}
	}
	fprintf(out," );  }\n");
	additional_rule(N);
    }


	if( pars_mode & SYN_ABSTRACT ) {
		fprintf(out,"\tTOK%d '(' ",index(term(son(1,son(1,N))),_Ident));

		bound = numsons(son(2,N));
		for(j=1;j<=bound;j++) {
			E = decl(son(j,son(2,N)));
			fprintf(out,"%sNt %s",etoa(id(son(1,E))),(j==bound)?"":"',' ");
		}
		fprintf(out,"')'\n\t{ $$ = %s( ",etoa(id(son(1,son(1,N)))));
		bound = numsons(son(2,N));
		for(j=1;j<=bound;j++) {
			fprintf(out," %s$%d",(j==1)?"":",",1+2*j);
		}
		fprintf(out," ); }\n");
	}
	fprintf(out,";\n");
}



static void mxy_yaccgen( char *filename ) {
int i, bound, j, bound2;
ELEMENT N, X, L;

	printf("+++ generating the yacc-file\n");

	fprintf(out,"%%{\n");

	filename[strlen(filename)-1] = 'h';
	fprintf(out,"#include \"%s\"\n",filename);

	fprintf(out,"extern  line, column;\n\n");
	fprintf(out,"static  ELEMENT  syntaxtree = nil();\n");
	fprintf(out,"extern  ELEMENT  add_predeclarations( ELEMENT );\n\n");

	fprintf(out,"%%}\n\n");

	fprintf(out,"%%union {\n");
	fprintf(out,"\tELEMENT t;\n");
	fprintf(out,"\tstruct{\n");
	fprintf(out,"\t\tELEMENT v;\n");
	fprintf(out,"\t\tELEMENT l;\n");
	fprintf(out,"\t\tELEMENT c;\n");
	fprintf(out,"\t} vlc;\n");
	fprintf(out,"\tstruct{\n");
	fprintf(out,"\t\tELEMENT l;\n");
	fprintf(out,"\t\tELEMENT c;\n");
	fprintf(out,"\t} lc;\n");
	fprintf(out,"}\n");

/*** output of the tokens ***/

	fprintf(out,"\n%%token<vlc>");

	bound = numsubterms( PreDeclProdList );
	for(i=1;i<=bound;i++) {
		fprintf(out," %sNt",etoa(idtos(term(son(1,son(1,subterm(i,PreDeclProdList)))))));
	}
	fprintf(out," ERRORSYM\n");

	bound = numsubterms(SemTokenList);
	for(i=1;i<=bound;i++) {
		ELEMENT ide = subterm(i,SemTokenList);
		yacctoken_semprint(out,index(ide,_Ident));
	}

	bound = numsubterms(TokenList);
	for(i=1;i<=bound;i++) {
		ELEMENT ide = subterm(i,TokenList);
		if( elem(ide,SemTokenList) ) continue;
		yacctoken_print(out,index(ide,_Ident));
	}
	if( pars_mode & SYN_ABSTRACT ) {
		bound = numsubterms(ReachableProdList);
		for(i=1;i<=bound;i++) {
			N = subterm(i,ReachableProdList);
			yacctoken_print(out,index(term(son(1,son(1,N))),_Ident));
		}
	}

	bound = numsubterms(ReachableProdList);
	for(i=1;i<=bound;i++) {
		N = subterm(i,ReachableProdList);
		yaccnont_print(out," %sNt",etoa(id(son(1,son(1,N)))),0,0);
	}



	bound = number(_ListProd_);
	for(i=1;i<=bound;i++) {
		N = element(i,_ListProd_);
		if(!elem(N,ReachableProdList)) continue;

		L = LPsepsymbols(N);

		if( (pars_mode & SYN_CONCRETE)==0 ) bound2=1;
		else bound2 = numsubterms(L);

		for(j=2;j<=bound2;j++) {
			yaccnont_print(out," %sNt%d",etoa(id(son(1,son(1,N)))),j,0);

		}
	}

	if( pars_mode & SYN_CONCRETE ) {
	bound = number(_ListProd_);
		for(i=1;i<=bound;i++) {
			N = element(i,_ListProd_);
			if(!elem(N,ReachableProdList)) continue;
			L = LPsepsymbols(N);
			bound2 = numsubterms(L);
			for(j=1;j<=bound2;j++) {
				yaccnont_print(out," %sSeq%d_%d",etoa(id(son(1,son(2,N)))),i,j);
			}
		}
	}

	if( pars_mode & SYN_ABSTRACT ) {
		bound = number(_ListProd_);
		for(i=1;i<=bound;i++) {
			N = element(i,_ListProd_);
			if(!elem(N,ReachableProdList)) continue;
			yaccnont_print(out," %sSeq%d",etoa(id(son(1,son(2,N)))),i,0);
		}
	}
	yaccnont_print(out," %s","Syntaxtree",0,0);

	fprintf(out,"\n\n%%start Syntaxtree\n\n%%%%\n");

	fprintf(out,"Syntaxtree:\n");
	fprintf(out,"\t%sNt\n",etoa(id(son(1,son(2,element(1,_Structure_))))));
	fprintf(out,"\t{ syntaxtree = add_predeclarations( $1 ); }\n;\n");

/*** output of the productions ***/

	bound = numsubterms(ReachableProdList);
	for(i=1;i<=bound;i++) {
		N = subterm(i,ReachableProdList);
		X = parscode(N);
		if( is(X,_Parsrule) && (pars_mode & SYN_CONCRETE) ) {
			fprintf(out,"%sNt :\n",etoa(id(son(1,son(1,N)))));
			mxy_yaccrule( subterm(1,X), out );
			fprintf(out,";\n");
		} else {
			switch(sort(N)) {
			  case _ListProd_  :	LPout( N );	break;
			  case _TupelProd_ :	TPout( N );	break;
			  case _ClassProd_ :	CPout( N );	break;
			}
		}
	}


/*** output of the other declarations ***/

	fprintf(out,"%%%%\n");

	fprintf(out,"#include \"lex.yy.c\"\n");
	fprintf(out,"#include <stdio.h>\n\n");
	fprintf(out,"int yyerror( char *s ){\n");
	fprintf(out,"\tfprintf( stderr, \"**** Line %%d, column %%d: %%s\\n\",line,column,s );\n");
	fprintf(out,"\treturn 1;\n");
	fprintf(out,"}\n\n");
	fprintf(out,"#ifndef yywrap\n");
	fprintf(out,"int yywrap(){return(1);}\n");
	fprintf(out,"#endif\n\n");
	fprintf(out,"int yyparse();\n\n");
	fprintf(out,"ELEMENT  yyread( FILE *file ){\n");
	fprintf(out,"\tyyin = file;\n");
	fprintf(out,"\tif( yyparse() )\n");
	fprintf(out,"\t\treturn nil();\n");
	fprintf(out,"\telse\n");
	fprintf(out,"\t\treturn syntaxtree;\n");
	fprintf(out,"}\n");
}


/*** creates scanner and parser ***/


void parser_gen( FILE *lout, FILE *yout, int par_pars_mode, char *filename ) {

	pars_mode = par_pars_mode;
	init_grammarsymbols();
	init_aux_lists();

	out = lout;
	mxy_lexgen();
	out = yout;
	mxy_yaccgen( filename );
}


/*** creates the frame with the main program ***/


void frame_gen( FILE *out, char *NAME ) {
	int i, bound;
	char *s;
	ELEMENT P;

	init_grammarsymbols();

	printf("+++ generating the frame\n");

	fprintf(out,"#include <stdio.h>\n");
	fprintf(out,"#include <stdlib.h>\n");
	fprintf(out,"#include <string.h>\n\n");
	fprintf(out,"#include \"%s_spec.h\"\n\n",NAME);
	fprintf(out,"extern  long  yyread( FILE* );\n\n");
	fprintf(out,"static  void  treeprint( ELEMENT, int );\n\n");
	fprintf(out,"extern  long  waitlist_count;\n");
	if ( max_options.bro ) {
	   fprintf(out,"void  Bim_Viewer( ELEMENT, int, char * [] );\n");
	}
	fprintf(out,"int main(int argc,char *argv[]){\n");
	fprintf(out,"\tchar *filename = NULL;\n");
	fprintf(out,"\tFILE *fileptr;\n");
	fprintf(out,"\tint i;\n");
	fprintf(out,"\tELEMENT elem;\n\n");

	fprintf(out,"/* evaluation of the options */\n\n");

	fprintf(out,"\tfor(i=1;i<argc;i++) {\n");
	fprintf(out,"\t\tchar *s = argv[i];\n");
	fprintf(out,"\t\tif( s[0] != '-' ) {\n");
	fprintf(out,"\t\t\tfilename = s;\n");
	fprintf(out,"\t\t}\n");
	fprintf(out,"\t}\n\n");

	fprintf(out,"/* testing of the correctness of the options */\n\n");

	fprintf(out,"\tif( filename==NULL ) {\n");
	fprintf(out,"\t\tfprintf(stdout,\"Usage: %s <filename>\\n\");\n",NAME);
	fprintf(out,"\t\treturn EXIT_FAILURE;\n");
	fprintf(out,"\t}\n\n");

	fprintf(out,"/* reading and parsing of the given specification */\n\n");

	fprintf(out,"\tfprintf(stdout,\"+++ reading\\n\");\n");
	fprintf(out,"\tif( !( fileptr = fopen(filename,\"r\") ) ){\n");
	fprintf(out,"\t\tfprintf(stdout,\"%s: Can't open file %%s for input\\n\",filename);\n",NAME);
	fprintf(out,"\t\treturn EXIT_FAILURE;\n");
	fprintf(out,"\t}\n");
	fprintf(out,"\tif( (elem = yyread( fileptr )) == nil() ){\n");
	fprintf(out,"\t\tfprintf(stdout,\"%s: fatal read error: exit\\n\",filename);\n",NAME);
	fprintf(out,"\t\treturn EXIT_FAILURE;\n");
	fprintf(out,"\t}\n\n");

	fprintf(out,"/* attribute-evaluation and user-defined actions */\n\n");

	fprintf(out,"\tfprintf(stdout,\"+++ analysing\\n\");\n\n");
	fprintf(out,"\tif( init_%s( elem ) ){\n",NAME);
	if( max_options.bro ) {
	   fprintf(out,"\t\tBim_Viewer( root( ), argc, argv );\n");
	}
	fprintf(out,"\t\tfprintf(stdout,\"+++ %%d elements in the waiting list\\n\",waitlist_count);\n");

	fprintf(out,"\t\ttreeprint( root(), 0 );\n");

	if( number(_Rule_) != 0 ) {
		fprintf(out,"\t\t/* calling evaluation of dynamic semantic */\n");
		fprintf(out,"\t\tinit_dyninput();\n\n");
		fprintf(out,"\t\t/* user, set your input values HERE ( Syntax : <Inputname> = <Value>;)*/\n\n");
		fprintf(out,"\t\teval_dynsem();\n\n");
		fprintf(out,"\t\t/* user, your output values have been computed */\n");
	}

	fprintf(out,"\t}\n");
	fprintf(out,"}\n\n");

	fprintf(out,"/* function for addition of the predeclared entities */\n\n");

	fprintf(out,"ELEMENT add_predeclarations( ELEMENT T ) {\n");
	fprintf(out,"return T;\n");
	fprintf(out,"}\n\n");

	fprintf(out,"/* printing of the abstract syntax tree */\n\n");

	fprintf(out,"void  blanks( int n ){\n");
	fprintf(out,"\twhile( n-- > 0 ) printf(\"  \");\n");
	fprintf(out,"}\n\n");

	fprintf(out,"static  void  treeprint( ELEMENT n, int indent ){\n");
	fprintf(out,"\tELEMENT  termv = term(n);\n\n");
	fprintf(out,"\tblanks(indent);\n");
	fprintf(out,"\tswitch( sort(termv) ){\n\n");

	fprintf(out,"\t/* predeclared sorts */\n\n");

	fprintf(out,"\tcase _Ident:\n");
	fprintf(out,"\t\tprintf(\"Ident \\\"%%s\\\"\\n\",etoa(idtos(termv)) ); break;\n");

	fprintf(out,"\tcase _Int:\n");
	fprintf(out,"\t\tprintf(\"Int %%d\\n\",etoi(termv) ); break;\n");

	fprintf(out,"\tcase _Bool:\n");
	fprintf(out,"\t\tif(etob(termv))\t{ printf(\"true\\n\"); break; }\n");
	fprintf(out,"\t\telse\t\t{ printf(\"false\\n\"); break; }\n");

	fprintf(out,"\tcase _Char:\n");
	fprintf(out,"\t\tprintf(\"Char '%%c'\\n\",etoc(termv) ); break;\n");

	fprintf(out,"\tcase _String:\n");
	fprintf(out,"\t\tprintf(\"String \\\"%%s\\\"\\n\",etoa(termv) ); break;\n\n");

	fprintf(out,"\t/* other base sorts */\n\n");

	bound = numsubterms(ReachableProdList);
	for(i=1;i<=bound;i++) {
		P = subterm(i,ReachableProdList);
		if( is(P,_ClassProd_) ) continue; /* ClassProd@ don't occur in the syntax tree */

		s = etoa(idtos(term(son(1,son(1,P)))));
		fprintf(out,"\tcase _%s:\tprintf(\"%s %%d\\n\",n-root()); break;\n",s,s);
	}

	fprintf(out,"\n\tdefault: printf(\"*** sort not in print list ***\\n\"); break;\n");

	fprintf(out,"\t}\n");
	fprintf(out,"\tn = son(1,n);\n");
	fprintf(out,"\twhile( n != nil() ){\n");
	fprintf(out,"\t\ttreeprint(n,indent+1);\n");
	fprintf(out,"\t\tn = rbroth(n);\n");
	fprintf(out,"\t}\n");
	fprintf(out,"}\n\n");
	fprintf(out,"/* end of file */\n");
}


void makefile_gen( FILE *out, char *lang ) {

	int ht = get_hosttype();

	printf("+++ generating the Makefile\n");

	if(ht==0) {
		printf("+++ warning : hosttype could not be determined\n");
		printf("              please check entries in Makefile\n");
	}

	fprintf(out,"# Anpassungen an die Rechnerplattform\n\n");

	switch(ht) {
	case HOST_SUN :
		fprintf(out,"CC        = acc\n");
		fprintf(out,"INCLUDES  =\n");
		fprintf(out,"DEFINES   =\n");
		fprintf(out,"DEBUG     = -g\n");
		fprintf(out,"CFLAGS    = $(INCLUDES) $(DEFINES) $(DEBUG)\n");
		fprintf(out,"YACC      = yacc -v\n");
		fprintf(out,"LEX       = lex\n");
		fprintf(out,"NAME      = %s\n",lang);
		fprintf(out,"MAXOPTS   =\n");
		fprintf(out,"MAXPATH   = %s\n",MAXPATHNAME);
	break;
	case HOST_HP :
		fprintf(out,"CC        = cc -Aa\n");
		fprintf(out,"INCLUDES  =\n");
		fprintf(out,"DEFINES   = -DSECONDBITSET\n");
		fprintf(out,"DEBUG     = -g\n");
		fprintf(out,"CFLAGS    = $(INCLUDES) $(DEFINES) $(DEBUG)\n");
		fprintf(out,"YACC      = yacc -v\n");
		fprintf(out,"LEX       = lex\n");
		fprintf(out,"NAME      = %s\n",lang);
		fprintf(out,"MAXOPTS   =\n");
		fprintf(out,"MAXPATH   = %s\n",MAXPATHNAME);
	break;
	default :
		fprintf(out,"CC        = cc /* Ansi-C-Compiler*/\n");
		fprintf(out,"INCLUDES  =\n");
		fprintf(out,"DEFINES   =\n");
		fprintf(out,"DEBUG     =-g\n");
		fprintf(out,"CFLAGS    = $(INCLUDES) $(DEFINES) $(DEBUG)\n");
		fprintf(out,"YACC      = yacc -v\n");
		fprintf(out,"LEX       = lex\n");
		fprintf(out,"NAME      = %s\n",lang);
		fprintf(out,"MAXOPTS   =\n");
		fprintf(out,"MAXPATH   = %s\n",MAXPATHNAME);
	break;
	}

	fprintf(out,"\n\n$(NAME) : y.tab.o $(MAXPATH)/obj/max_std.o $(NAME).o $(NAME)_spec.o");
	fprintf(out,"\n\t$(CC) $(CFLAGS) -o $(NAME) y.tab.o $(MAXPATH)/obj/max_std.o $(NAME).o $(NAME)_spec.o");

	fprintf(out,"\n\ny.tab.o : y.tab.c lex.yy.c $(NAME)_spec.h");
	fprintf(out,"\n\t$(CC) $(INCLUDES) $(DEFINES) -g -c y.tab.c");

	fprintf(out,"\n\ny.tab.c: $(NAME)_spec.y");
	fprintf(out,"\n\t$(YACC) $(YACCOPTS) $(NAME)_spec.y");

	fprintf(out,"\n\nlex.yy.c: $(NAME)_spec.l");
	fprintf(out,"\n\t$(LEX) $(NAME)_spec.l");

	fprintf(out,"\n\n$(NAME)_spec.o :  $(NAME)_spec.c");
	fprintf(out,"\n\t$(CC) $(CFLAGS) -c $(NAME)_spec.c");

	fprintf(out,"\n\n$(NAME)_spec.c $(NAME)_spec.h $(NAME)_spec.l $(NAME)_spec.y : $(NAME)_spec.m");
	fprintf(out,"\n\t$(MAXPATH)/bin/max $(MAXOPTS) $(NAME)_spec.m");

	fprintf(out,"\n\n$(NAME).o :  $(NAME).c  $(NAME)_spec.h");
	fprintf(out,"\n\t$(CC) $(CFLAGS) -c $(NAME).c");

	fprintf(out,"\n\nclean :");
	fprintf(out,"\n\trm -rf *.o y.tab.c lex.yy.c core $(NAME) $(NAME)_spec.[ylhcg] y.output\n\n");

}


/*** End ***/

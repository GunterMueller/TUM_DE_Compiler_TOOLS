
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "max_spec.h"
#include "max.h"

struct OPT   max_options;

typedef long Boolean;
extern Boolean ** att_sortcheck;
extern Boolean ** att_nilcheck;
extern Boolean ** fct_sortcheck;
extern Boolean ** fct_nilcheck;


void  Bim_Viewer( ELEMENT, int, char * [] );

#ifdef NO_BROWSER
void  Bim_Viewer( ELEMENT N, int argc, char *argv[] ) {}
#endif

/**********  brief description of the options

Option : -O<onr>

Optimisation of the attribute evaluation

onr = 0 : without strategy, no partial evaluation
      1 : without strategy, with partial evaluation
      2 : with strategy, no partial evaluation
      3 : with strategy and partial evaluation
-------------

Option : -p

printing of the estimated Value-terms of the functions and attributes
-------------

Option : -t

printing of the syntax tree
-------------

Option : -b

calling browser
-------------

Option : -ya -yc

creating scanner and parser for abstract/concrete syntax
-------------

Option : -f

creating frame-main-program
-------------

Option : -m

creating Makefile
-------------

Option : -warn

print type checking warnings  
_____________


Option : -notc

no type checking 
_____________


**********/

extern  ELEMENT  yyread( FILE* );
extern  void  header_gen( FILE*, char*, int );
extern  void  grphif_gen( FILE*, char* );
extern  void  source_gen( FILE*, char* );
extern  void  frame_gen ( FILE*, char* );
extern  void  parser_gen( FILE*, FILE*, int, char* );
extern  void  makefile_gen( FILE*, char* );
extern  void  dynsem_gen( FILE* );

void  treeprint( ELEMENT, int );
static  void  valueprint( ELEMENT, int, ELEMENT );

static  FILE  *cout, *hout, *gout, *fout, *lout, *yout, *mout;


int main(int argc,char *argv[]){
	char   *filename = NULL;
	FILE   *fileptr;
	ELEMENT elem;
	int 	leng, i;
	char	*lang, *framename;

	fprintf(stdout,"MAX Version 7.2 - TU Muenchen\n");

	/* Default-options */
	max_options.onr = 3;
	max_options.pro = 0;
	max_options.trp = 0;
	max_options.bro = 0;
	max_options.frame = 0;
	max_options.pars  = 0;
	max_options.make  = 0;
        max_options.warn = 0;
        max_options.tc = 1;

	for(i=1;i<argc;i++) {
		char *s = argv[i];
		if( s[0] != '-' ) {
			filename = s;
		} else
		switch( s[1] ) {
			case 'O' :
			if( '0'<=s[2] && s[2]<='3' )
				max_options.onr = s[2]-'0';
			break;
			case 'p' :
				max_options.pro = 1;
			break;
			case 't' :
				max_options.trp = 1;
			break;
			case 'b' :
				max_options.bro = 1;
			break;
			case 'f' :
				max_options.frame = 1;
			break;
			case 'm' :
				max_options.make = 1;
			break;
			case 'y' :
				switch(s[2]) {
				case 'a': max_options.pars = SYN_ABSTRACT; break;
				case 'c': max_options.pars = SYN_CONCRETE; break;
				}
			break;

                        case 'n' :
				if(!strcmp(s,"-notc"))  
                               
                                   	 max_options.tc  = 0;
                       
				if(!strcmp(s,"-warn")) 

					max_options.warn = 1; 

			break;
		}
	}

	if( filename==NULL ) {
		fprintf(stderr,"Usage: max <spec file> [-O[0123]] [-p] [-t] [-b] [-ya] [-yc] [-f] [-m] [-notc] [-warn]\n");
		return EXIT_FAILURE;
	}

        leng = strlen(filename);
	if( leng<3 || filename[leng-2] != '.'  ||  filename[leng-1] != 'm' ){
		fprintf(stderr,"max: Specification file does not end with \".m\"\n");
		return EXIT_FAILURE;
	}
	if( !( fileptr = fopen(filename,"r") ) ){
		fprintf(stderr,"max: Can't open file %s for input\n",filename);
		return EXIT_FAILURE;
	}

	elem = yyread( fileptr );

	if( elem == nil() ){
		fprintf(stderr,"max: fatal read error: exit\n",filename);
		return EXIT_FAILURE;
	}

	fprintf(stdout,"+++ analysing\n", max_options.onr );

	if(  init_max( elem )  ){ /* now the syntax structure can be accessed  */


		if(!max_options.tc) {

			int i,j,numpar;

                     	att_sortcheck = (Boolean **) calloc(number(_Attribute_) + 1,sizeof(Boolean*));

 			if(!att_sortcheck)
 			{
                        	fprintf(stderr,"\n***** Error: Cannot allocate att_sortcheck");
                                exit( EXIT_FAILURE );
                        }   

                        att_nilcheck = (Boolean **) calloc(number(_Attribute_) + 1,sizeof(Boolean*));

                        if(!att_nilcheck)
                        {
                             	fprintf(stderr,"\n***** Error: Cannot allocate att_nilcheck");
                                exit( EXIT_FAILURE );
                        }   

 			for(i = 1; i <= number(_Attribute_); i++)
 			{
   				numpar = etoi(numsons(son(2,element(i,_Attribute_)))) + 1;

   				att_sortcheck[i] = (Boolean *) calloc(numpar,sizeof(Boolean));

   				if(!att_sortcheck[i])
   				{
     					fprintf(stderr,"\n***** Error: Cannot allocate att_sortcheck");
     					exit( EXIT_FAILURE );
   				}   

   				for(j = 1; j < numpar; j++)

      					att_sortcheck[i][j] = MAXTRUE;


   				att_nilcheck[i] = (Boolean *) calloc(numpar,sizeof(Boolean));


   				if(!att_nilcheck[i])
   				{
     					fprintf(stderr,"\n***** Error: Cannot allocate att_nilcheck");
     					exit( EXIT_FAILURE );
   				}   

   				for(j = 1; j < numpar; j++)

     					att_nilcheck[i][j] = MAXTRUE;

 			}

 			fct_sortcheck = (Boolean **) calloc(number(_Function_) + 1,sizeof(Boolean*));

 			if(!fct_sortcheck)
 			{
   				fprintf(stderr,"\n***** Error: Cannot allocate fct_sortcheck");
   				exit( EXIT_FAILURE );
 			}   

 			fct_nilcheck = (Boolean **) calloc(number(_Function_) + 1,sizeof(Boolean*));

 			if(!fct_nilcheck)
 			{
   				fprintf(stderr,"\n***** Error: Cannot allocate fct_nilcheck");
   				exit( EXIT_FAILURE );
 			}   

 			for(i = 1; i <= number(_Function_); i++)
 			{
   				numpar = etoi(numsons(son(2,element(i,_Function_)))) + 1;

   				fct_sortcheck[i] = (Boolean *) calloc(numpar,sizeof(Boolean));

 				if(!fct_sortcheck[i])
 				{
  					fprintf(stderr,"\n***** Error: Cannot allocate fct_sortcheck");
 					exit( EXIT_FAILURE );
  				}   

  				for(j = 1; j < numpar; j++)

   					fct_sortcheck[i][j] = MAXTRUE;


   				fct_nilcheck[i] = (Boolean *) calloc(numpar,sizeof(Boolean));

  				if(!fct_nilcheck[i])
  				{
   					fprintf(stderr,"\n***** Error: Cannot allocate fct_nilcheck");
   					exit( EXIT_FAILURE );
  				}   

  				for(j = 1; j < numpar; j++)

    					fct_nilcheck[i][j] = MAXTRUE;
			}


		}

		if( max_options.trp ) {
			fprintf(stdout,"+++ analyzed syntax tree :\n");
			treeprint( root(), 0 );
		}

		if( max_options.pro ) {
			int fct_ind, att_ind, fctnum, attnum;

			fprintf(stdout,"+++ Estimated values of the functions and attributes :");

			fct_ind = 1; fctnum = number(_Function_);
			att_ind = 1; attnum = number(_Attribute_);
			for( ; fct_ind <= fctnum || att_ind <= attnum ; ) {
				int which;
				ELEMENT F,A;

				if( fct_ind > fctnum ) {
					A = element(att_ind,_Attribute_);
					which = 1;
				} else if( att_ind > attnum ) {
					F = element(fct_ind,_Function_);
					which = 0;
				} else {
					F = element(fct_ind,_Function_);
					A = element(att_ind,_Attribute_);
					which = bef( before(A), before(F) );
				}
				if( which ) { /* print Attribute A */
					if(lbroth(A)==nil()) printf("\n+++ AttrList\n");
					printf("Attribute \"%s\"\n",etoa(idtos(term(son(1,son(1,A))))));
					valueprint( result_value(A), 1, A );
					att_ind++;

				} else {      /* print Function F */
					if(lbroth(F)==nil()) printf("\n+++ FuncList\n");
					printf("Function  \"%s\"\n",etoa(idtos(term(son(1,son(1,F))))));
					valueprint( result_value(F), 1, F );
					fct_ind++;
				}
			}
		}

		if(max_options.tc)
  		{
                	fprintf(stdout,"+++ type checking");
                	fprintf(stdout,"   ( syntax tree has %d nodes, %d expr nodes )\n", 
						number(_Node), number(_Expr_) );
                	typecheck();
		}

		filename[leng-1] = 'h';
		if( !( hout = fopen(filename,"w") ) ){
			fprintf(stderr,"max: Can't open file %s for output\n",filename);
			return EXIT_FAILURE;
		}
		filename[leng-1] = 'c';
		if( !( cout = fopen(filename,"w") ) ){
			fprintf(stderr,"max: Can't open file %s for output\n",filename);
			return EXIT_FAILURE;
		}
		filename[leng-1] = 'g';
		if( !( gout = fopen(filename,"w") ) ){
			fprintf(stderr,"max: Can't open file %s for output\n",filename);
			return EXIT_FAILURE;
		}

		fprintf(stdout,"+++ generating  ( syntax tree has %d nodes )\n", number(_Node) );

		if( number(_Structure_) != 0 )
			lang = etoa(idtos(term(son(1,son(1,element(1,_Structure_))))));
		else	lang = "unnamed";


		if( max_options.frame ) {
			if( number(_Structure_) != 0 ) {
				framename = (char *)malloc(strlen(lang)+3);
				if( framename==0L ) {
					fprintf(stderr,"*** Cannot allocate space for string\n");
					exit(EXIT_FAILURE);
				}

				sprintf(framename,"%s.c",lang);
				if( !( fout = fopen(framename,"w") ) ) {
					fprintf(stderr,"max: Can't open file %s for output\n",framename);
					exit(EXIT_FAILURE);
				}

				frame_gen( fout, lang );
				fclose(fout);
			} else {
				printf("+++ creation of a frame requires a STRUC\n");
			}
		}

		if( max_options.make ) {
			if( !( mout = fopen("Makefile","w") ) ){
				fprintf(stderr,"max: Can't open Makefile for output\n");
				return EXIT_FAILURE;
			}
			makefile_gen( mout, lang );
			fclose(mout);
		}

		if( max_options.pars ) {
			if( number(_Structure_) != 0 ) {
				filename[leng-1] = 'l';
				if( !( lout = fopen(filename,"w") ) ){
					fprintf(stderr,"max: Can't open file %s for output\n",filename);
					return EXIT_FAILURE;
				}
				filename[leng-1] = 'y';
				if( !( yout = fopen(filename,"w") ) ){
					fprintf(stderr,"max: Can't open file %s for output\n",filename);
					return EXIT_FAILURE;
				}

				parser_gen( lout, yout, max_options.pars, filename );

				fclose(lout);
				fclose(yout);
			} else {
				printf("+++ creation of a parser requires a STRUC\n");
			}
		}

		header_gen(hout, "", 1 ); 
		grphif_gen(gout, "" ); 
		filename[leng-2] = '\0';
		source_gen(cout,filename);

		fclose(hout);
		fclose(gout);

		dynsem_gen(cout);

		fclose(cout);


		if( max_options.bro ) Bim_Viewer( root( ), argc, argv );

		return EXIT_SUCCESS;
	}
	return  EXIT_FAILURE;
}



#if defined(__STDC__) && ! defined(apollo)
#define DEFID(N)   DefId( stoid(atoe(#N)), itoe(0), itoe(0) )
#define SORTID(N)  TermSortId( stoid(atoe(#N)), itoe(0), itoe(0) )
#else
#define DEFID(N)   DefId( stoid(atoe("N")), itoe(0), itoe(0) )
#define SORTID(N)  TermSortId( stoid(atoe("N")), itoe(0), itoe(0) )
#endif

    
#define UPARL(C)      appback( SortIdList(), SORTID(C) )
#define BPARL(C1,C2)  appback( appback(SortIdList(),SORTID(C1)), SORTID(C2) )

ELEMENT  predeclared_entities( void ){
	ELEMENT entl;
	entl = appback( ProdList(), PredeclProd( DEFID(Point) )  );
	entl = appback( entl, PredeclProd( DEFID(Node) )  );
	entl = appback( entl, PredeclProd( DEFID(nil) )  );
	entl = appback( entl, PredeclProd( DEFID(Term) )  );
	entl = appback( entl, PredeclProd( DEFID(NodeSort) )  );
	entl = appback( entl, PredeclProd( DEFID(PredeclSort) )  );
	entl = appback( entl, PredeclProd( DEFID(ClassSort) )  );
	entl = appback( entl, PredeclProd( DEFID(TupelSort) )  );
	entl = appback( entl, PredeclProd( DEFID(ListSort) )  );
	entl = appback( entl, PredeclProd( DEFID(Ident) )  );
	entl = appback( entl, PredeclProd( DEFID(Bool) )  );
	entl = appback( entl, PredeclProd( DEFID(Char) )  );
	entl = appback( entl, PredeclProd( DEFID(Int) )  );
	entl = appback( entl, PredeclProd( DEFID(String) )  );
	entl = appback( entl, PredeclProd( DEFID(Reference) )  );

	entl = appback( entl, ClassProd( DEFID(Element), appback(BPARL(Point,Node),SORTID(Term)) )  );
	entl = appback( Specification(), entl );

	entl = appback( entl, PredDecl( DEFID(eq),   BPARL(Element,Element) ) );
	entl = appback( entl, PredDecl( DEFID(is),   BPARL(Element,Element) ) );
	entl = appback( entl, PredDecl( DEFID(desc), BPARL(Node,Node) )       );
	entl = appback( entl, PredDecl( DEFID(bef),  BPARL(Point,Point) )     );
	entl = appback( entl, PredDecl( DEFID(aft),  BPARL(Point,Point) )     );

	entl = appback( entl, FuncDecl( DEFID(true),	SortIdList(),	SORTID(Bool) )  );
	entl = appback( entl, FuncDecl( DEFID(false),	SortIdList(),	SORTID(Bool) )  );
	entl = appback( entl, FuncDecl( DEFID(root), 	SortIdList(),	SORTID(Node) )  );
	entl = appback( entl, FuncDecl( DEFID(fath),	UPARL(Node),	SORTID(Node) )  );
	entl = appback( entl, FuncDecl( DEFID(rbroth),	UPARL(Node),	SORTID(Node) )  );
	entl = appback( entl, FuncDecl( DEFID(lbroth),	UPARL(Node),	SORTID(Node) )  );
	entl = appback( entl, FuncDecl( DEFID(son),	BPARL(Int,Node),	SORTID(Element) )  );
	entl = appback( entl, FuncDecl( DEFID(numsons),	UPARL(Node),    SORTID(Element) )  );
	entl = appback( entl, FuncDecl( DEFID(front),	UPARL(Term),    SORTID(Term) )  );
	entl = appback( entl, FuncDecl( DEFID(back),	UPARL(Term),    SORTID(Term) )  );
	entl = appback( entl, FuncDecl( DEFID(appfront),BPARL(Element,Term),	SORTID(Term) )  );
	entl = appback( entl, FuncDecl( DEFID(appback), BPARL(Term,Element),	SORTID(Term) )  );
	entl = appback( entl, FuncDecl( DEFID(conc),	BPARL(Term,Term),	SORTID(Term) )  );
	entl = appback( entl, FuncDecl( DEFID(subterm),	BPARL(Int,Element),	SORTID(Element) )  );
	entl = appback( entl, FuncDecl( DEFID(numsubterms), UPARL(Element), SORTID(Element) )  );
	entl = appback( entl, FuncDecl( DEFID(term),	UPARL(Node),	SORTID(Element) )  );
	entl = appback( entl, FuncDecl( DEFID(before),	UPARL(Node),	SORTID(Point) )  );
	entl = appback( entl, FuncDecl( DEFID(after),	UPARL(Node),	SORTID(Point) )  );
	entl = appback( entl, FuncDecl( DEFID(node),	UPARL(Point),	SORTID(Node)  )  );
	entl = appback( entl, FuncDecl( DEFID(idtos),	UPARL(Ident),	SORTID(String))  );
	entl = appback( entl, FuncDecl( DEFID(sort),	UPARL(Element),	SORTID(Element)   )  );
	entl = appback( entl, FuncDecl( DEFID(index),	BPARL(Element,Element),	SORTID(Int) )  );
	entl = appback( entl, FuncDecl( DEFID(element),	BPARL(Int,Element),	SORTID(Element) )  );
	entl = appback( entl, FuncDecl( DEFID(number),	UPARL(Element),	SORTID(Int) )  );

	return entl;
}

void  blanks( int n ){
	while( n-- > 0 )	printf("  ");
}



static  void  valueprint( ELEMENT n, int indent, ELEMENT FA ) {
	int i;

	blanks(indent);
	if(n == nil() || n == _nil) printf("NIL()\n"); else
	switch( sort(n)) {
	case _TWfath:   printf("TWfath()\n");		break;
	case _TWson:    printf("TWson(%d)\n",subterm(1,n));break;
	case _TWrbroth: printf("TWrbroth()\n");		break;
	case _TWlbroth: printf("TWlbroth()\n");		break;
	case _RelevAcc:	n = son(1,son(subterm(1,n),fath(FA)));
			printf("DefId \"%s\"\n",etoa(idtos(term(son(1,n)))) );
			break;
	case _OrValue:  printf("OrValue (%d subterms)\n",numsubterms(n));
			for(i=1;i<=numsubterms(n);i++)
				valueprint(subterm(i,n),indent+1,FA);
			break;

	case _FList:    printf("FList (%d subterms)\n",numsubterms(n));
			for(i=1;i<=numsubterms(n);i++)
				valueprint(subterm(i,n),indent+1,FA);
			break;

	case _FClosure:	printf("FClosure\n");
			valueprint(subterm(1,n),indent+1,FA); break;

	case _DefId_:	printf("DefId \"%s\"\n",etoa(idtos(term(son(1,n)))) );
			break;
	}
}


void  treeprint( ELEMENT n, int indent ){
	ELEMENT  termv = term(n);

	blanks(indent);
	switch( sort(termv) ){
	case _Ident:		printf("\"%s\"\n", etoa(idtos(termv)) ); break;
	case _Int:		printf("%d  %d\n", etoi(termv),n-root()); break;
	case _Bool:		if( etob(termv) ){
							printf("true\n");  break;
						} else {
							printf("false\n"); break;
						}
	case _String:		printf("\"%s\"\n", etoa(termv) );        break;
	case _Node:		printf("Node %d\n",n-root()); break;
	case _Point:		printf("Point %d\n",n-root()); break;
	case _Specification:	printf("Specification %d\n",n-root()); break;
	case _ProdList:		printf("ProdList %d\n",n-root()); break;
	case _ListProd:		printf("ListProd %d\n",n-root()); break;
	case _TupelProd:	printf("TupelProd %d\n",n-root()); break;
	case _ClassProd:	printf("ClassProd %d\n",n-root()); break;
	case _PredeclProd:	printf("PredeclProd %d\n",n-root()); break;
	case _SortIdList:	printf("SortIdList %d\n",n-root()); break;
	case _PredDecl:		printf("PredDecl %d\n",n-root()); break;
	case _FuncDecl:		printf("FuncDecl %d\n",n-root()); break;
	case _Structure:	printf("Structure %d\n",n-root()); break;
	case _LocalDeclList:	printf("LocalDeclList %d\n",n-root()); break;
	case _PredList:		printf("PredList %d\n",n-root()); break;
	case _FuAtList:		printf("FuAtList %d\n",n-root()); break;
	case _CondList:		printf("CondList %d\n",n-root()); break;
	case _Predicate:	printf("Predicate %d\n",n-root()); break;
	case _Function:		printf("Function %d\n",n-root()); break;
	case _Attribute:	printf("Attribute %d\n", n-root()); break;
	case _Condition:	printf("Condition %d\n",n-root()); break;
	case _PatternList:	printf("PatternList %d\n",n-root()); break;
	case _AttrDecl:		printf("AttrDecl %d\n",n-root()); break;
	case _ExprList:		printf("ExprList %d\n",n-root()); break;
	case _SortConst:	printf("SortConst %d\n",n-root()); break;
	case _FuncAppl:		printf("FuncAppl %d\n",n-root()); break;
	case _IfExpr:		printf("IfExpr %d\n",n-root()); break;
	case _LetExpr:		printf("LetExpr %d\n",n-root()); break;
	case _StringExpr:	printf("StringExpr %d\n",n-root()); break;
	case _PatternCaseList:	printf("PatternCaseList %d\n",n-root()); break;
	case _FormulaCaseList:	printf("FormulaCaseList %d\n",n-root()); break;
	case _PatternCase:	printf("PatternCase %d\n",n-root()); break;
	case _FormulaCase:	printf("FormulaCase %d\n",n-root()); break;
	case _PredAppl:		printf("PredAppl %d\n",n-root()); break;
	case _Or:		printf("Or %d\n",n-root()); break;
	case _And:		printf("And %d\n",n-root()); break;
	case _Impl:		printf("Impl %d\n",n-root()); break;
	case _Neg:		printf("Neg %d\n",n-root()); break;
	case _Pattern:		printf("Pattern %d\n",n-root()); break;
	case _ItemList:		printf("ItemList %d\n",n-root()); break;
	case _DefId:		printf("DefId %d\n",n-root()); break;
	case _TermSortId:	printf("TermSortId %d\n",n-root()); break;
	case _NodeSortId:	printf("nodeSortId %d\n",n-root()); break;
	case _ApplId:		printf("ApplId %d\n",n-root()); break;
	case _Name:		printf("Name %d\n",n-root()); break;
	case _NameList:		printf("ParamList %d\n",n-root()); break;
	case _Blank:		printf("Blank %d\n",n-root()); break;
	case _Asterisk:		printf("Asterisk %d\n",n-root()); break;
	case _DefIdNodeList:	printf("DefIdNodeList %d\n",n-root()); break;
	default:		printf("***** sort not in print list *****\n"); break;
	}      
	n = son(1,n);
	while( n != nil() ){
		treeprint(n,indent+1);
		n = rbroth(n);
	}
}





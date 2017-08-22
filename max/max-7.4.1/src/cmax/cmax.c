/*****************************************************************************

  cmax.c

  C-code for Constraint MAX preprocessor

  part of CMAX V2.1.X sources

  (c) Copyright 1996-1998 by Aurel Huber, TU Muenchen, Germany

  Last update: 31 Mar 1998

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdmax_spec.h"

#include "main.h"

/**** Definitions for main.c ****/

char *switches[] = {		/* the provided switches on the command line */
	"nocode", "debug",
	"verbosecode", "nosrcpos", ""   
	};

char *options[] = {
	"o",			/* the user can choose an output filename
	                           for the generated MAX file with the -o
	                           option */
	""
};

int main_flags = 0;

char *browser_switch = "browser";  /* the browser is not really supported!*/

void usage(void){
	fprintf(stderr,
		"usage: cmax [options] file1 file2 ... \n"
		"  options are:\n"
		"    -nocode           produce no code\n"
		"    -debug            print debugging information\n"
                "    -verbosecode      generate messages giving information\n"
		"                         about constraints\n"
                "    -nosrcpos         generate no additional source code\n"
                "                          information in MAX-code\n"
                "    -o outfile        use <outfile>.m as output filename\n"
	);
}

void user_init(void){
  fprintf(stdout, "CMAX Constraint MAX preprocessor Version 2.1.0\n");
  fprintf(stdout, "(c) 1996-1998 by Aurel Huber, TU Muenchen, Germany\n");
}

void user_exit(void){
  if (ErrorCounter){
    fprintf(stderr, "There were %d error(s).\n", ErrorCounter);
    fprintf(stderr, "CMAX exit status: 1\n");
  }
  else {
    fprintf(stderr, "CMAX exit status: 0 = OK\n");
  }
}

ELEMENT max_init_fct (ELEMENT tree) {
  return init_cmax(tree);
}

void max_dyninit_fct (void) {  /* no dynamic semantics in cmax! */
  /*
    init_dyninput();
    eval_dynsem();
  */
}

/******************************************************************/

/*
  The following function collects nodes in a subtree of the syntaxtree
  of sort S and returns them as a list.
  Useful for instance for collecting used identifiers in an Expression.
*/

ELEMENT /*NodeList*/ collect_occurences(ELEMENT /*Node*/ N, ELEMENT /*Sort*/ S)
{
  long i,n; ELEMENT res=NodeList(),curr;

  n = number(S);
  for (i=1; i<=n; i++) {
    curr=element(i,S);
    if (desc(curr, N) || eq(curr,N))
      res=appback(res,curr);
  }
  return res;
}

/*
  strtoid makes the function stoid (string to ident) available within
  a MAX specification.
*/
      
ELEMENT strtoid (ELEMENT E) {
	return stoid(E);
}

/*
  sortof returns the sort of an Element as a string.
  Just used for debugging purposes.
*/

ELEMENT sortof (ELEMENT E) {
	return itos((long) sort(E));
}

/*
  ctos is needed to ouput MAC character constants
*/

ELEMENT ctos (ELEMENT E) {
  char c[2];
  
  c[0] = etoc (E);
  c[1] = '\0';
  
  return atoe(c);
}

/*
  The following stuff is just needed for the parser and
  has been taken and adapted from max_pars.y
*/

#if defined(__STDC__) && ! defined(apollo)
#define DEFID(N)   DefId( stoid(atoe(#N)), itoe(0), itoe(0), atoe("?") )
#define SORTID(N)  TermSortId( stoid(atoe(#N)), itoe(0), itoe(0), atoe("?") )
#else
#define DEFID(N)   DefId( stoid(atoe("N")), itoe(0), itoe(0), atoe("?" )
#define SORTID(N)  TermSortId( stoid(atoe("N")), itoe(0), itoe(0) atoe("?"))
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

    entl = appback( entl, FuncDecl( DEFID(true),    SortIdList(),   SORTID(Bool) )  );
    entl = appback( entl, FuncDecl( DEFID(false),   SortIdList(),   SORTID(Bool) )  );
    entl = appback( entl, FuncDecl( DEFID(root),    SortIdList(),   SORTID(Node) )  );
    entl = appback( entl, FuncDecl( DEFID(fath),    UPARL(Node),    SORTID(Node) )  );
    entl = appback( entl, FuncDecl( DEFID(rbroth),  UPARL(Node),    SORTID(Node) )  );
    entl = appback( entl, FuncDecl( DEFID(lbroth),  UPARL(Node),    SORTID(Node) )  );
    entl = appback( entl, FuncDecl( DEFID(son), BPARL(Int,Node),    SORTID(Element) )  );
    entl = appback( entl, FuncDecl( DEFID(numsons), UPARL(Node),    SORTID(Element) )  );
    entl = appback( entl, FuncDecl( DEFID(front),   UPARL(Term),    SORTID(Term) )  );
    entl = appback( entl, FuncDecl( DEFID(back),    UPARL(Term),    SORTID(Term) )  );
    entl = appback( entl, FuncDecl( DEFID(appfront),BPARL(Element,Term),    SORTID(Term) )  );
    entl = appback( entl, FuncDecl( DEFID(appback), BPARL(Term,Element),    SORTID(Term) )  );
    entl = appback( entl, FuncDecl( DEFID(conc),    BPARL(Term,Term),   SORTID(Term) )  );
    entl = appback( entl, FuncDecl( DEFID(subterm), BPARL(Int,Element), SORTID(Element) )  );
    entl = appback( entl, FuncDecl( DEFID(numsubterms), UPARL(Element), SORTID(Element) )  );
    entl = appback( entl, FuncDecl( DEFID(term),    UPARL(Node),    SORTID(Element) )  );
    entl = appback( entl, FuncDecl( DEFID(before),  UPARL(Node),    SORTID(Point) )  );
    entl = appback( entl, FuncDecl( DEFID(after),   UPARL(Node),    SORTID(Point) )  );
    entl = appback( entl, FuncDecl( DEFID(node),    UPARL(Point),   SORTID(Node)  )  );
    entl = appback( entl, FuncDecl( DEFID(idtos),   UPARL(Ident),   SORTID(String))  );
    entl = appback( entl, FuncDecl( DEFID(sort),    UPARL(Element), SORTID(Element)   )  );
    entl = appback( entl, FuncDecl( DEFID(index),   BPARL(Element,Element), SORTID(Int) )  );
    entl = appback( entl, FuncDecl( DEFID(element), BPARL(Int,Element), SORTID(Element) )  );
    entl = appback( entl, FuncDecl( DEFID(number),  UPARL(Element), SORTID(Int) )  );

    return entl;
}

/*
  The following is a workaround for a bug in the MAX-system:
  sometimes in the C Code generated by MAX is a call to the function
  'sort' which is undefined as the header file with the macro definition
  is not included. So we define a global function here.   
*/
 
#undef sort

ELEMENT sort(ELEMENT E)
{
  return mxi_sort(__FILE__,__LINE__,E);
}


/* end of file */




















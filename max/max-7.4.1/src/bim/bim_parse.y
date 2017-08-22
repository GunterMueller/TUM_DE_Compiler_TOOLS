%{
#include <string.h>
#include "bim_sem.h"

#define YYSTYPE char *

extern char * yytext;
%}

%token SORTSECT
%token ATTRSECT
%token TUPLESECT
%token LISTSECT
%token NL
%token IDENT
%token LBRACE
%token RBRACE

%%

 root: SORTSECT NL sortdefs TUPLESECT NL tupledefs LISTSECT NL listdefs ATTRSECT NL attrdefs {  }
;

 sortdefs: 
   | sortdefs sortident subsortlist NL { add_classsort( $2 ); }
;
 tupledefs:
   | tupledefs sortident subsortlist NL { add_tupleprod( $2 ); }
;
listdefs:
   | listdefs sortident subsortlist NL { add_listprod( $2 ); }
;

 subsortlist: { $$ = sublist_buffer; sublist_buffer[ 0 ] = 0; }
   | subsortlist sortident { $$ = sem_sublist( $1, $2 ); }
;
 sortident: IDENT { $$ = strdup( yytext ); }
;

 attrdefs:
   | attrdefs rsort aname LBRACE asort RBRACE NL { add_attr( $5, $3, $2 ); }
;

 rsort: IDENT { $$ = strdup( yytext ); }
;
 aname: IDENT { $$ = strdup( yytext ); }
;
 asort: IDENT { $$ = strdup( yytext ); }
;

%%

#ifndef yywrap
int yywrap(){return(1);}
#endif


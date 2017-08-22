terminals
 1 IDENT       { sem }
 2 INTCONST    { sem }
 3 ZUWSY
 4 BEGINSY
 5 COMMA
 6 ENDSY
 7 TYP         { sem }
 8 SEMIC
 9 BOOLCONST   { sem }
10 RELOP       { sem }
11 EKAUF
12 EKZU
13 EQUAL
14 ADDOP       { sem }
15 MULOP       { sem }
16 RKAUF       
17 RKZU
18 IFSY
19 THENSY
20 ELSESY
21 FISY
22 WHILESY
23 DOSY
24 ODSY
25 CONSTSY
26 LEAVESY
27 COLON
28 ARRAYSY
29 CALLSY
30 RETURNSY    { sem }
31 PROCSY
32 VARSY
33 STRCONST    { sem }
34 READSY
35 WRITESY
36 NEWLINSY
37 PROGSY
38 BAR
39 TYPESY
40 ISSY
41 FUNCSY
42 PARALL

axiom PROG

rules

PROG      ->   PROGSY  IDENT   BLOCK.
BLOCK     ->   BEGINSY DECLIST STATLIST  ENDSY .
DECLIST   ->   DECL  SEMIC  DECLIST ;
               DECL  PARALL DECLIST ;
               empty .
DECL      ->   CONSTDL ;
               VARDECL ;
	       TYPEDECL;
               PROCDECL.
{ ********************* }
{ ******** NEU ******** }
{ ********************* }
TYPEDECL  ->   TYPESY IDENT EQUAL CONSTR_SEQ.
CONSTR_SEQ ->  CONSTR ; 
               CONSTR BAR CONSTR_SEQ.
CONSTR    ->   IDENT RKAUF RKZU; 
               IDENT RKAUF TYP_SEL_SEQ RKZU.
TYP_SEL_SEQ -> TYPE IDENT; 
               TYPE IDENT COMMA TYP_SEL_SEQ.
TYPE      ->   TYP ; 
               IDENT.
{ ********************* }
CONSTDL   -> CONSTDL  COMMA  CONSTDEC ;
             CONSTSY  CONSTDEC .
CONSTDEC  -> IDENT  EQUAL  CONSTANT  ;
             IDENT  EQUAL  ADDOP  INTCONST.
CONSTANT  -> INTCONST;
             BOOLCONST.
VARDECL   -> VARSY TYPE IDLIST ;
             ARRAYSY  INTCONST TYP  IDLIST.
IDLIST    -> IDENT COMMA  IDLIST;
             IDENT.
PROCDECL  -> PROCSY IDENT FORMPARL SEMIC BLOCK;
             { *** NEU ***}
             FUNCSY IDENT FORMPARL COLON TYPE SEMIC BLOCK.
FORMPARL  -> RKAUF  PARLIST  RKZU ;
             empty .
PARLIST   -> PAR  SEMIC  PARLIST ;
             PAR  .
PAR       -> TYPE  IDLIST ;
             VARSY VARDECL .
STATLIST  -> STAT  SEMIC  STATLIST;
             STAT .
STAT      -> empty;
             READSY  RKAUF  VARLIST  RKZU ;
             WRITESY  RKAUF  OUTLIST  RKZU;
             RETURNSY;
             { *** NEU *** }
             RETURNSY RELOREXP;
             WHILESY  COND  DOSY  STATLIST  ODSY ;
             IFSY COND  THENSY  STATLIST  FPART ;
             CALLSY  IDENT  AKTPARL ;
             VARIABLE  ZUWSY  RELOREXP .
VARLIST   -> VARIABLE COMMA  VARLIST;
             VARIABLE .
OUTLIST   -> OUTEXPR  COMMA OUTLIST ;
             OUTEXPR .
OUTEXPR   -> EXPR ;
             STRCONST ;
             NEWLINSY .
FPART     -> ELSESY  STATLIST  FISY ;
             FISY .
RELOREXP  -> EXPR ;
             RELATION .
AKTPARL   -> RKAUF  EXPRL  RKZU;
             EMPTY .
EXPRL     -> RELOREXP  COMMA  EXPRL ;
             RELOREXP .
RELATION  -> { *** NEU *** }
             EXPR ISSY IDENT;
             EXPR EQUAL EXPR ;
             EXPR RELOP EXPR .
COND      -> RELATION ;
             EXPR .
EXPR      -> EXPR ADDOP TERM ;
             ADDOP TERM ;
             TERM .
TERM      -> TERM  MULOP FACT ;
             FACT .
FACT      -> { *** NEU *** }
             IDENT RKAUF EXPRL RKZU; { Funktion oder Konstruktion 
                                                oder Selektion }
             VARIABLE ;
             CONSTANT.
VARIABLE  -> IDENT;                  { einfache Variable }
             IDENT EKAUF EXPR EKZU.  { Arrayzugriff      }

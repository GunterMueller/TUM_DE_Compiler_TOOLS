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
37 SPECSY
38 PROGSY

actions

   Proganf      Progend
   Blockanf     Blockend
   Pushrel
   Enterconst   Enterconsta
   Skalarvar   Arrayvar
   Enterid
   Incpst      Decpst
   Procdesc
   Enterpar
   Entermarke   Delmarke
   C_leave      C_return
   C_call       C_assign
   C_equal      C_relop
   C_addop      C_unadd
   C_mulop      O_array
   Konstdesc    Arraydim
   Bdecl
   O_var        O_konst
   G_intconst   G_boolconst
   Push_indvar
   Valpar       Varpar
   Outint       Outstr    Outnewl
   Readint
   C_relexp     C_cond
   C_param
   Parl
   Endprocdecl
   Fp_1         Fp_2    Fp_else
   C_od        C_while
   C_if
   Blockstat

axiom PROG

rules

PROG      -> PROGSY  IDENT  Proganf   BLOCK  Progend.
BLOCK     -> BEGINSY  Blockanf DECLIST  Blockstat STATLIST  ENDSY Blockend.
DECLIST   -> DECL  SEMIC  DECLIST ;
             empty .
DECL      -> CONSTDL ;
             Bdecl VARDECL ;
             PROCDECL .
CONSTDL   -> CONSTDL  COMMA  CONSTDEC ;
             CONSTSY  CONSTDEC .
CONSTDEC  -> IDENT  Konstdesc  EQUAL  CONSTANT  Enterconst;
             IDENT  Konstdesc  EQUAL  ADDOP  Pushrel  INTCONST  Enterconsta.
CONSTANT  -> INTCONST G_intconst;
             BOOLCONST G_boolconst.
VARDECL   -> TYP  Skalarvar  IDLIST ;
             ARRAYSY  INTCONST  Arraydim  TYP  Arrayvar  IDLIST.
IDLIST    -> IDENT  Enterid  COMMA  IDLIST;
             IDENT  Enterid .
PROCDECL  -> PROCSY  IDENT  Procdesc  FORMPARL  SEMIC  BLOCK  Endprocdecl ;
             SPECSY  IDENT  Procdesc  FORMPARL Endprocdecl.
FORMPARL  -> RKAUF  PARLIST  RKZU ;
             empty .
PARLIST   -> PAR  SEMIC  PARLIST ;
             PAR  .
PAR       -> TYP  Valpar IDLIST ;
             VARSY  Varpar VARDECL .
STATLIST  -> STAT  SEMIC  STATLIST;
             STAT .
STAT      -> READSY  RKAUF  VARLIST  RKZU ;
             WRITESY  RKAUF  OUTLIST  RKZU;
             IDENT  Entermarke  COLON  BEGINSY  STATLIST  ENDSY  Delmarke ;
             LEAVESY  IDENT  C_leave ;
             RETURNSY  C_return ;
             WHILESY  C_while COND  DOSY  STATLIST  ODSY C_od;
             IFSY C_if  COND  THENSY  STATLIST  FPART ;
             CALLSY  IDENT  Parl  AKTPARL  C_call;
             VARIABLE  ZUWSY  RELOREXP C_assign .
VARLIST   -> VARIABLE  Readint COMMA  VARLIST;
             VARIABLE Readint .
OUTLIST   -> OUTEXPR  COMMA OUTLIST ;
             OUTEXPR .
OUTEXPR   -> EXPR Outint;
             STRCONST Outstr;
             NEWLINSY Outnewl.
FPART     -> ELSESY  Fp_else  STATLIST  FISY Fp_1;
             FISY Fp_2.
RELOREXP  -> EXPR  ;
             RELATION C_relexp.
AKTPARL   -> RKAUF  EXPRL  RKZU;
             EMPTY .
EXPRL     -> RELOREXP  C_param  COMMA  EXPRL ;
             RELOREXP  C_param .
RELATION  -> EXPR  EQUAL  EXPR C_equal ;
             EXPR  RELOP  Pushrel  EXPR C_relop .
COND      -> RELATION ;
             EXPR C_cond .
EXPR      -> EXPR  ADDOP  Pushrel  TERM  C_addop;
             ADDOP  Pushrel  TERM  C_unadd;
             TERM .
TERM      -> TERM  MULOP  Pushrel  FACT C_mulop;
             FACT .
FACT      -> RKAUF  EXPR  RKZU ;
             VARIABLE ;
             CONSTANT O_konst .
VARIABLE  -> IDENT O_var;
             IDENT  Pushrel  EKAUF  EXPR  EKZU  O_array.

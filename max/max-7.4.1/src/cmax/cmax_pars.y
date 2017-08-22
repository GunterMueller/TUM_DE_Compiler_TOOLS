/***************************************************************************

  cmax_pars.y

  yacc parser specification for CMAX Constraint MAX preprocessor

  part of CMAX V2.1.0 sources

  (c) Copyright 1996-1998 by Aurel Huber, TU Muenchen, Germany

  Last update: 27 Mar 1998

 **************************************************************************/

 
%{
#include "stdmax_spec.h"
extern line;
static ELEMENT  syntaxtree = nil();
extern ELEMENT  predeclared_entities( void );
%}

%union { 
	ELEMENT  o;
	struct{
		ELEMENT  v;
		ELEMENT  l;
		ELEMENT  c;
		ELEMENT  f;
	}      vlcf;
}

%token<vlcf> PARSnr
%token      PARSline PARScol PARSno PARSleft PARSright PARSrule
%token      PARSprio PARSaux PARSaddrule PARSpos
%token      PRD  FCT  ATT  STRUC  CND  LET  ELSE  APC  AT
%token      ORSYM   ANDSYM   IMPLSYM    EQSYM     SEPSYM  
%token<vlcf> IDENT   CHARCONST  INTCONST  STRINGCONST 
%token<vlcf> SORTCONST   ERRORSYM  APO  IF CONCSYM APPSYM CONSSYM
%token      RULES DYN THEN FI ASSIGN UNDEF IN CASE IS END
%token      LATTICE ASSERT ASSN LEQSYM GEQSYM VARSYM FOR CIMPLSYM

%type<o>  GlobalDeclSeq GlobalDeclNt ProdSeq ProductionNt
%type<o>  SortIdSeq SubClassSeq SepSortIdSeq PatternSeq		
%type<o>  SortIdNt NodeSortIdNt TermSortIdNt
%type<o>  LocalDeclSeq LocalDeclNt PredSeq		
%type<o>  FuAtSeq CondSeq PredicateNt		
%type<o>  FunctionNt AttributeNt ConditionNt ExprSeq		
%type<o>  ExprNt StringExprSeq CaseSeq PatternCaseSeq		
%type<o>  FormulaCaseSeq FormulaNt OrFormulaNt AndFormulaNt		
%type<o>  NegFormulaNt PrimFormulaNt PatternNt ItemSeq		
%type<o>  ItemNt SubPatternsNt ParamSeq SortIdSeq2
%type<o>  PNT LPINFO StringList FuncApplNt
%type<o>  DynFuncNt RuleListNt RuleNt DynSemInputNt
%type<o>  UpdateListNt UpdateOrRuleNt UpdateNt CaseConstNt
%type<o>  CaseIsListNt CaseIsNt
%type<o>  LatticeDefNt AssertionNt AssnDefNt ConstraintNt
%type<o>  LatticeDefSeq AssertionSeq AssnDefSeq
%type<o>  VarDeclNt VarDeclSeq
%type<o>  AssnNt AssnSeq AssnSeq1
%type<o>  DefIdNt ApplIdNt NameNt
%type<o>  ListExprNt

%left CONCSYM APPSYM
%right CONSSYM

%start SpecificationNt

%%
SpecificationNt :
	GlobalDeclSeq 
	{	syntaxtree = $1; }
;  
GlobalDeclSeq :
	GlobalDeclNt
    {	$$ = appback( predeclared_entities(), $1 ); }
|	GlobalDeclSeq  GlobalDeclNt
    {	$$ = appback( $1, $2 ); }
|	GlobalDeclSeq  SEPSYM  GlobalDeclNt
    {	$$ = appback( $1, $3 ); }
;
GlobalDeclNt :
	ProdSeq
	{	$$ = $1; }
|	PRD  DefIdNt '['  SepSortIdSeq  ']' 
	{	$$ = PredDecl( $2, $4 ); }
|	PRD  DefIdNt  '['  ']' 
	{	$$ = PredDecl( $2, SortIdList() ); }
|	FCT  DefIdNt  '('  SepSortIdSeq  ')'  SortIdNt
	{	$$ = FuncDecl( $2, $4, $6 ); }
|	FCT  DefIdNt  '('  ')'  SortIdNt
	{	$$ = FuncDecl( $2, SortIdList(), $5 ); }
|	STRUC DefIdNt '['  IDENT ']'  '{'  LocalDeclSeq  '}' 
	{	$$ = Structure( $2, TermSortId($4.v,$4.l,$4.c,$4.f), $7); }
|	STRUC DefIdNt '['  IDENT ']'  
	{	$$ = Structure( $2, TermSortId($4.v,$4.l,$4.c,$4.f),
		                LocalDeclList()); }
|	RULES  RuleListNt
	{	$$ = $2; }
;
RuleListNt :
	RuleNt
	{	$$ = appback( RuleList(), $1 ); }
|	RuleListNt  RuleNt
	{	$$ = appback( $1, $2 ); }
;
DynFuncNt :
	DYN  DefIdNt  '('  ParamSeq  ')'  SortIdNt  ':'  ExprNt
	{	$$ = DynFunc( $2, subterm(1,$4), subterm(2,$4), $6, $8 ); }
|	DYN  DefIdNt  '('  ')'  SortIdNt  ':'  ExprNt
	{	$$ = DynFunc( $2, SortIdList(), NameList(), $5, $7 ); }
;
DynSemInputNt :
	IN  DefIdNt '(' ')' SortIdNt
	{	$$ = DynSemInput( $2, SortIdList(), $5 ); }
;
RuleNt :
	IF  FormulaNt  THEN  UpdateListNt  FI
	{	$$ = IfRule( $2, $4, UpdateList() ); }
|	IF  FormulaNt  THEN  UpdateListNt  ELSE  UpdateListNt  FI
	{	$$ = IfRule( $2, $4, $6 ); }
|	CASE  ExprNt  CaseIsListNt  END
	{	$$ = CaseRule( $2, $3, UpdateList()); }
|	CASE  ExprNt  CaseIsListNt  ELSE  UpdateListNt  END
	{	$$ = CaseRule( $2, $3, $5 ); }
;
UpdateListNt :

	{	$$ = UpdateList(); }
|	UpdateListNt UpdateOrRuleNt
	{	$$ = appback( $1, $2 ); }
;
UpdateOrRuleNt :
	UpdateNt
	{	$$ = $1; }
|	RuleNt
	{	$$ = $1; }
;
UpdateNt :
	FuncApplNt  ASSIGN  ExprNt
	{	$$ = Update( $1, $3 ); }
;
CaseIsListNt :
	CaseIsNt
	{	$$ = appback( CaseIsList(), $1 ); }
|	CaseIsListNt  CaseIsNt
	{	$$ = appback( $1, $2 ); }
;
CaseIsNt :
	IS  CaseConstNt  THEN  UpdateListNt
	{	$$ = CaseIs( $2, $4 ); }
;
FuncApplNt :
	ApplIdNt  '('  ')'
	{	$$ = FuncAppl( $1, ExprList() ); }
|	ApplIdNt  '('  ExprSeq  ')'
	{	$$ = FuncAppl( $1, $3 ); }
|	ExprNt  '.'  ApplIdNt
	{	$$ = FuncAppl( $3, appback(ExprList(),$1) ); }
;
ProdSeq :
	ProductionNt
	{	$$ = appback( ProdList(), $1 ); }
|	ProdSeq ProductionNt
	{	$$ = appback( $1, $2 ); }
;
ProductionNt:
	DefIdNt PNT '*'  SortIdNt  LPINFO
	{	$$ = ListProd( $1, $4 ); /*mxy_enterlp( $5, $2 );*/ }
|	DefIdNt PNT '('  SortIdSeq ')' 
	{	$$ = TupelProd( $1,
			SILfromRSI($4) /*mxy_entertp( $4, $2 )*/ ); }
|	DefIdNt PNT '='  SubClassSeq
	{	$$ = ClassProd( $1, SILfromCPIL($4) 
                         /*mxy_entercp( $4, $2, $1.v )*/ ); }
|	DefIdNt PARSprio '=' SortIdSeq2  '|' STRINGCONST SortIdNt StringList
	{	$$ = ClassProd( $1,
		SILfromCPIL( appback( $4, CPinfo( appback( StringList(), $6.v), $7, $8 )) )
		/*mxy_entercp( appback( $4, CPinfo( appback( StringList(), $6.v), $7, $8 )),
		             Parsprio(), $1.v )*/
		     ); }
;
SortIdSeq2:
	SortIdNt
	{	$$ = appback( CPinfoList(), CPinfo( StringList(), $1, StringList() ) ); }
|	SortIdSeq2 '|' SortIdNt
	{	$$ = appback( $1, CPinfo( StringList(), $3, StringList() ) ); }
;
PNT :
	PARSrule APO  StringList  APC
	{ $$ = Parsrule($3); }
|	PARSaddrule APO  StringList  APC
	{ $$ = Parsaddrule($3); }
|	PARSleft
	{ $$ = Parsleft(); }
|	PARSright
	{ $$ = Parsright(); }
|	PARSno
	{ $$ = Parsno(); }
|	PARSaux
	{ $$ = Parsaux(); }
|
	{ $$ = itoe(0); }
;
LPINFO :

	{	$$ = LPinfolist(); }
|	LPINFO '*' STRINGCONST
	{	$$ = appback( $1,ParsStern( $3.v )); }
|	LPINFO '+' STRINGCONST
	{	$$ = appback( $1,ParsPlus( $3.v )); }
;
SortIdSeq :

	{	$$ = RsideInfo(); }
|	SortIdSeq SortIdNt
	{	$$ = appback( $1, $2 ); }
|	SortIdSeq STRINGCONST
	{	$$ = appback( $1, $2.v ); }
|	SortIdSeq PARSnr
	{	$$ = appback( $1, Parsnr($2.v) ); }
|	SortIdSeq PARSline
	{	$$ = appback( $1, Parsline() ); }
|	SortIdSeq PARScol
	{	$$ = appback( $1, Parscol() ); }
|	SortIdSeq PARSpos
	{	$$ = appback( $1, Parspos() ); }
;
StringList:

	{	$$ = StringList(); }
|	StringList  STRINGCONST
	{	$$ = appback( $1, $2.v ); }
;
SubClassSeq: 
	StringList SortIdNt StringList
	{	$$ = appback( CPinfoList(), CPinfo( $1, $2, $3 ) ); }
|	SubClassSeq '|'  StringList SortIdNt StringList
	{	$$ = appback( $1, CPinfo( $3, $4, $5 ) ); }
;
SepSortIdSeq: 
	SortIdNt
	{	$$ = appback( SortIdList(), $1 ); }
|	SepSortIdSeq ','  SortIdNt
	{	$$ = appback( $1, $3 ); }
;
TermSortIdNt :
	IDENT
	{	$$ = TermSortId($1.v,$1.l,$1.c,$1.f);}
;
NodeSortIdNt :
	IDENT AT
	{	$$ = NodeSortId($1.v,$1.l,$1.c,$1.f); }
;
SortIdNt :
	TermSortIdNt
	{	$$ = $1; }
|	NodeSortIdNt
	{	$$ = $1; }
;
LocalDeclSeq :
	LocalDeclNt
	{	$$ = appback( LocalDeclList(), $1 ); }
|	LocalDeclSeq  LocalDeclNt
	{	$$ = appback( $1, $2 ); }
|	LocalDeclSeq  SEPSYM  LocalDeclNt
	{	$$ = appback( $1, $3 ); }
|	LocalDeclSeq  DynFuncNt
	{	$$ = appback( $1, $2); }
|	LocalDeclSeq  DynSemInputNt
	{	$$ = appback( $1, $2); }
;
LocalDeclNt :
	PredSeq
	{	$$ = $1; }
|	FuAtSeq
	{	$$ = $1; }
|	CondSeq
	{	$$ = $1; }
|	PRD  DefIdNt  '['  SepSortIdSeq  ']' 
	{	$$ = PredDecl( $2, $4 ); }
|	PRD  DefIdNt  '['  ']' 
	{	$$ = PredDecl( $2, SortIdList() ); }
|	FCT  DefIdNt  '('  SepSortIdSeq  ')'  SortIdNt
	{	$$ = FuncDecl( $2, $4, $6 ); }
|	FCT  DefIdNt  '('  ')'  SortIdNt
	{	$$ = FuncDecl( $2, SortIdList(), $5 ); }
|	ATT  DefIdNt  '('  SepSortIdSeq  ')'  SortIdNt
	{	$$ = AttrDecl( $2, $4, $6 ); }
|	LatticeDefSeq
	{	$$ = $1; }
|	VarDeclSeq
	{	$$ = $1; }

|	AssertionSeq
	{	$$ = $1; }
|	AssnDefSeq
	{	$$ = $1; }
;
PredSeq :
	PredicateNt
	{	$$ = appback(PredList(),$1); }
|	PredSeq  PredicateNt
	{	$$ = appback( $1, $2 ); }
;
FuAtSeq :
	FunctionNt
	{	$$ = appback(FuAtList(),$1); }
|	FuAtSeq  FunctionNt
	{	$$ = appback( $1, $2 ); }
|	AttributeNt
	{	$$ = appback(FuAtList(),$1); }
|	FuAtSeq  AttributeNt
	{	$$ = appback( $1, $2 ); }
;
CondSeq :
	ConditionNt
	{	$$ = appback(CondList(),$1); }
|	CondSeq  ConditionNt
	{	$$ = appback( $1, $2 ); }
;
LatticeDefSeq :
	LatticeDefNt
	{	$$ = appback(LatticeDefList(), $1); }
|	LatticeDefSeq LatticeDefNt
	{	$$ = appback( $1, $2 ); }
;
VarDeclSeq :
	VarDeclNt
	{	$$ = appback(VarDeclList(), $1); }
|	VarDeclSeq VarDeclNt
	{	$$ = appback( $1, $2 ); }
;
AssnDefSeq :
	AssnDefNt
	{	$$ = appback(AssnDefList(), $1); }
|	AssnDefSeq AssnDefNt
	{	$$ = appback( $1, $2 ); }
;
PredicateNt :
	PRD  DefIdNt  '['  ParamSeq  ']'   ':'  FormulaNt
	{	$$ = Predicate( $2, subterm(1,$4), subterm(2,$4), $7 ); }
|	PRD  DefIdNt  '['  ']'   ':'  FormulaNt
	{	$$ = Predicate( $2, SortIdList(), NameList(), $6 ); }
;
FunctionNt :
	FCT  DefIdNt  '('  ParamSeq  ')'  SortIdNt  ':'  ExprNt
	{	$$ = Function( $2, subterm(1,$4),
			subterm(2,$4), $6, $8 ); }
|	FCT  DefIdNt  '('  ')'  SortIdNt  ':'  ExprNt
	{	$$ = Function( $2, SortIdList(), NameList(), $5, $7 ); }
;
AttributeNt :
	ATT  DefIdNt  '('  ParamSeq  ')'  SortIdNt  ':'  ExprNt
	{	$$ = Attribute( $2, subterm(1,$4), subterm(2,$4), $6, $8 ); }
;
ParamSeq :
	SortIdNt  NameNt  
	{	$$ = ParTup( appback( SortIdList(), $1 ), 
                     appback( NameList(),   $2 )   ); }
|	ParamSeq  ','  SortIdNt  NameNt
	{	$$ = ParTup( appback( subterm(1,$1), $3 ), 
                     appback( subterm(2,$1), $4 )  ); }
;
ConditionNt :
	CND  PatternSeq ':'  FormulaNt  '|'  ExprNt
	{ $$ = Condition($2,$4,$6); }
|	CND  FormulaNt  '|'  ExprNt
	{ $$ = Condition(PatternList(),$2,$4); }
|	CND  PatternSeq ':'  FormulaNt
	{ $$ = Condition($2,$4,atoe("")); }
|	CND  FormulaNt
	{ $$ = Condition(PatternList(),$2,atoe("")); }
;
VarDeclNt :
	VARSYM LEQSYM DefIdNt  '('  ParamSeq  ')'  SortIdNt  ':'  ExprNt
	{	$$ = VarDecl($3, subterm(1, $5),
			subterm(2, $5), $7, $9, Leq() ); }
|	VARSYM GEQSYM DefIdNt  '('  ParamSeq  ')'  SortIdNt  ':'  ExprNt
	{	$$ = VarDecl($3, subterm(1, $5),
			subterm(2, $5), $7, $9, Geq() ); }
;
LatticeDefNt :
	LATTICE  DefIdNt '=' '(' SortIdNt ',' ApplIdNt ','
	ApplIdNt ',' ApplIdNt ')'
	{	$$ = LatticeDef( $2, $5, $7, $9, $11 ); }
; 
AssertionSeq :
	AssertionNt
	{	$$ = appback(AssertionList(), $1 ); }
|	AssertionSeq AssertionNt
	{	$$ = appback($1, $2); }
;
AssertionNt :
	ASSERT AssnSeq END
	{	$$ = Assertion($2); }
;
AssnDefNt :
	ASSN  DefIdNt  '('  ParamSeq  ')' ':' AssnSeq END
	{	$$ = AssnDef( $2, subterm(1, $4), subterm(2, $4), $7); }
|	ASSN  DefIdNt  '('  ')' ':' AssnSeq END
	{	$$ = AssnDef( $2, SortIdList(), NameList(), $6 ); }
;

AssnSeq :
	AssnNt
	{	$$ = appback(AssnList(), $1); }
|	AssnSeq ';' AssnNt
	{	$$ = appback($1, $3); }
AssnSeq1 :
	AssnNt
	{	$$ = appback(AssnList(), $1); }
|	AssnSeq1 END
	{	$$ = $1; }
;
AssnNt :
	FOR PatternNt ':' AssnSeq END
	{	$$ = PatternAssn($2, $4); }
|	IF FormulaNt THEN AssnSeq ELSE AssnSeq FI
	{	$$ = IfAssn($2, $4, $6); }
|	IF FormulaNt THEN AssnSeq FI
	{	$$ = IfAssn($2, $4, AssnList()); }
|	LET NameNt EQSYM ExprNt ':' AssnSeq
	{	$$ = LetAssn($2, $4, $6); }
|	ApplIdNt '(' ExprSeq ')'
	{	$$ = DefAssnAppl($1, $3); }
|	ApplIdNt '(' ')'
	{	$$ = DefAssnAppl($1, ExprList()); }
|	ConstraintNt
	{	$$ = $1; }
;
ConstraintNt :
	ExprNt  LEQSYM FuncApplNt
	{	$$ = LeqConstr( $1, $3 ); }
|	ExprNt  GEQSYM  FuncApplNt
	{	$$ = GeqConstr( $1, $3 ); }
|	FormulaNt CIMPLSYM ConstraintNt
	{	$$ = CondConstr( $1, $3 ); }
;
PatternSeq :
	PatternNt
	{	$$ = appback( PatternList(), $1 ); }
|	PatternSeq  ','  PatternNt
	{	$$ = appback( $1, $3 ); }
;
ExprSeq :
	ExprNt
	{	$$ = appback( ExprList(), $1 ); }
|	ExprSeq  ','  ExprNt
	{	$$ = appback( $1, $3 ); }
;
CaseConstNt :
	CHARCONST
        {       $$ =  CharConst($1.v,$1.l,$1.c,$1.f); }
|	INTCONST
        {       $$ =  IntConst($1.v,$1.l,$1.c,$1.f); }
|	'-' INTCONST
        {       $$ =  IntConst(-($2.v),$2.l,$2.c,$2.f); }
|	SORTCONST
	{	$$ = SortConst( TermSortId($1.v,$1.l,$1.c,$1.f) ); }
|	SORTCONST AT
	{	$$ = SortConst( NodeSortId($1.v,$1.l,$1.c,$1.f) ); }
;
ExprNt :
	CaseConstNt
	{	$$ =  $1; }
|	STRINGCONST
        {       $$ =  StringConst($1.v,$1.l,$1.c,$1.f); }
|	NameNt
	{	$$ =  $1; }
|	APO  StringExprSeq  APC
	{	$$ =  StringExpr($2,$1.l,$1.c,$1.f); }
|	FuncApplNt
	{	$$ = $1; }
|	IF  CaseSeq  ELSE  ExprNt
	{	$$ = IfExpr( $2, $4, $1.l, $1.c, $1.f); }
|	LET  NameNt  EQSYM  ExprNt  ':'  ExprNt
	{	$$ = LetExpr( $2, $4, $6 ); }
|	UNDEF
	{	$$ = DynUndef(); }
|	ListExprNt		/* added on 26 Mar 1998 */
	{	$$ = $1; }
|	ExprNt CONCSYM ExprNt   /* added on 26 Mar 1998 */
	{	$$ = FuncAppl(ApplId(stoid(atoe("conc")), $2.l, $2.c, $2.f),
                              appback(appback(ExprList(), $1), $3)
                             );
        }
|	ExprNt APPSYM ExprNt	/* added on 27 Mar 1998 */
	{	$$ = FuncAppl(ApplId(stoid(atoe("appback")), $2.l, $2.c, $2.f),
                              appback(appback(ExprList(), $1), $3)
                             );
	}
|	ExprNt CONSSYM ExprNt	/* added on 27 Mar 1998 */
	{	$$ = FuncAppl(ApplId(stoid(atoe("appfront")),$2.l,$2.c,$2.f),
                              appback(appback(ExprList(), $1), $3)
                             );
	}
|	'(' ExprNt ')'		/* added on 1 Apr 1998 */
	{	$$ = $2; }
;

ListExprNt :
	'[' ApplIdNt ']'
	{ $$ = FuncAppl ($2, ExprList()); }
|	'[' ApplIdNt ExprSeq ']'
	{ $$ = _build_listexpr($2, FuncAppl($2, ExprList()), $3); }
;
   
StringExprSeq :
	ExprNt
	{	$$ = appback( SExprList(), $1 ); }
|   StringExprSeq   ExprNt
	{	$$ = appback( $1, $2 ); }
;
CaseSeq :
	PatternCaseSeq
	{	$$ =  $1; }
|	FormulaCaseSeq
	{	$$ =  $1; }
;
PatternCaseSeq :
	PatternNt  ':'  ExprNt
	{	$$ =  appback( PatternCaseList(), PatternCase($1,$3) ); }
|	PatternCaseSeq  '|'  PatternNt  ':'  ExprNt
	{	$$ =  appback( $1, PatternCase($3,$5) ); }
;
FormulaCaseSeq :
	FormulaNt  ':'  ExprNt
	{	$$ =  appback( FormulaCaseList(), FormulaCase($1,$3) ); }
|	FormulaCaseSeq  '|'  FormulaNt  ':'  ExprNt
	{	$$ =  appback( $1, FormulaCase($3,$5) ); }
;
FormulaNt :
	OrFormulaNt  IMPLSYM  FormulaNt
	{	$$ =  Impl($1,$3); }
|	OrFormulaNt
	{	$$ =  $1; }
;
OrFormulaNt :
	AndFormulaNt  ORSYM  OrFormulaNt
	{	$$ =  Or($1,$3); }
|	AndFormulaNt
	{	$$ =  $1; }
;
AndFormulaNt :
	NegFormulaNt  ANDSYM  AndFormulaNt
	{	$$ =  And($1,$3); }
|	NegFormulaNt
	{	$$ =  $1; }
;
NegFormulaNt :
	'!'  PrimFormulaNt
	{	$$ =  Neg($2); }
|	PrimFormulaNt
	{	$$ =  $1; }
;
PrimFormulaNt :
	IDENT '['  ExprSeq  ']'
	{	$$ = PredAppl( ApplId($1.v,$1.l,$1.c,$1.f), $3 ); }
|	IDENT '['  ']'
	{	$$ = PredAppl( ApplId($1.v,$1.l,$1.c,$1.f), ExprList() ); }
|	ExprNt  '='  ExprNt
	{	$$ = PredAppl( ApplId(stoid(atoe("eq")),itoe(0),itoe(0),
                                      atoe("?")),
		        appback( appback( ExprList(),$1), $3)  ); }
|	ExprNt  '#'  ExprNt
	{	$$ = Neg( PredAppl(
                            ApplId(stoid(atoe("eq")),itoe(0),itoe(0),
                                   atoe("?")),
			    appback( appback( ExprList(),$1), $3)  ) ); }
|	'{'  FormulaNt  '}'
	{	$$ =  $2; }
;
PatternNt :
	NameNt 
	{	$$ =  Pattern( Blank(itoe(line)), Blank(itoe(line)), $1 ); }
|	NodeSortIdNt 
	{	$$ =  Pattern( $1, Blank(itoe(line)),Blank(itoe(line)) ); } 
|	SortIdNt   NameNt
	{	$$ =  Pattern( $1, Blank(itoe(line)), $2 ); }
|	SubPatternsNt 
	{	$$ =  Pattern( Blank(itoe(line)), $1, Blank(itoe(line)) ); }
|	SubPatternsNt  NameNt
	{	$$ =  Pattern( Blank(itoe(line)), $1, $2 ); }
|	NodeSortIdNt  SubPatternsNt
	{	$$ =  Pattern( $1, $2, Blank(itoe(line)) ); }
|	NodeSortIdNt  SubPatternsNt  NameNt
	{	$$ =  Pattern( $1, $2, $3 ); }
;
SubPatternsNt :
	'<'  '>'
	{	$$ =  ItemList(); }
|	'<'  ItemSeq  '>'
	{	$$ =  $2; }
;
ItemSeq :
	ItemNt
	{	$$ = appback( ItemList(), $1 ); }
|	ItemSeq  ','  ItemNt
	{	$$ = appback( $1, $3 ); }
;
ItemNt :
	'*'
	{	$$ = Asterisk(); }
|	'_'
	{	$$ = Blank(itoe(line)); }
|	PatternNt
	{	$$ =  $1; }
;

DefIdNt :
	IDENT  { $$ = DefId($1.v, $1.l, $1.c,$1.f); }
;
ApplIdNt :
	IDENT  { $$ = ApplId($1.v, $1.l, $1.c,$1.f); }
;
NameNt :
	IDENT  { $$ = Name($1.v, $1.l, $1.c,$1.f); }
;
	
%%

static ELEMENT _build_listexpr(ELEMENT applid,
                               ELEMENT listexpr, ELEMENT exprseq) {
  if (eq(numsubterms(exprseq), itoe(0)))
    return listexpr;
  else
    return _build_listexpr(
               applid,
               FuncAppl(ApplId(stoid(atoe("appback")), subterm(-3, applid),
                               subterm(-2, applid), subterm(-1, applid)
                              ),
                        appback(appback(ExprList(), listexpr), 
                                subterm(1, exprseq)
                               )
                       ),
               back(exprseq)
           );
}

static ELEMENT ctrue(){
  return FuncAppl( ApplId(stoid(atoe("true")),itoe(0),itoe(0),atoe("?")),
         ExprList() );
}

static ELEMENT cfalse(){
  return FuncAppl( ApplId(stoid(atoe("false")),itoe(0),itoe(0),atoe("?")),
                   ExprList() );
}

ELEMENT cAnd( ELEMENT LOP, ELEMENT ROP ){
  ELEMENT ifclause =
    IfExpr( appfront( FormulaCase( Neg(LOP), cfalse()) , FormulaCaseList()), 
	   IfExpr( appfront( FormulaCase( ROP, ctrue()), FormulaCaseList()), 
			    cfalse() , itoe(0), itoe(0),atoe("?") ),
           itoe(0), itoe(0), atoe("?") );
  return PredAppl( ApplId(stoid(atoe("eq")),itoe(0),itoe(0),atoe("?")),
	     appback( appback( ExprList(), ctrue()), ifclause)  );
}

ELEMENT cOr( ELEMENT LOP, ELEMENT ROP ){
  ELEMENT ifclause =
    IfExpr( appfront( FormulaCase( LOP, ctrue()) , FormulaCaseList()), 
	   IfExpr( appfront( FormulaCase( ROP, ctrue()), FormulaCaseList()), 
			    cfalse(), itoe(0), itoe(0), atoe("?") ) ,
           itoe(0), itoe(0), atoe("?") );
  return PredAppl( ApplId(stoid(atoe("eq")),itoe(0),itoe(0),atoe("?")),
	     appback( appback( ExprList(), ctrue()), ifclause)  ); 
}

#include "lex.yy.c" 
#include <stdio.h> 

static parserrorflag = 0;

int yyerror( char *s ){
	fprintf( stderr, "**** File %s, Line %d, column %d: %s\n",
                 file, line,column,s );
	parserrorflag = 1;
	return 1;
}

#ifndef yywrap
int yywrap(){return(1);}
#endif

int yyparse();

ELEMENT  yyread( FILE *file ){
	yyin = file;
	yyparse();
        if( parserrorflag ) 
           return nil();
        return syntaxtree;
}










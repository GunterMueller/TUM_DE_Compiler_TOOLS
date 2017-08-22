
%{
#include "max_spec.h"
extern int line;
extern char *file;
static ELEMENT  syntaxtree = nil();
extern ELEMENT  predeclared_entities( void );

ELEMENT cAnd( ELEMENT, ELEMENT);
ELEMENT cOr( ELEMENT, ELEMENT );

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
%token<vlcf> SORTCONST   ERRORSYM  APO  IF   
%token      RULES DYN THEN FI ASSIGN UNDEF IN CASE IS END

%type<o>	GlobalDeclSeq	GlobalDeclNt	ProdSeq		ProductionNt
%type<o>	SortIdSeq	SubClassSeq     SepSortIdSeq	PatternSeq		
%type<o>	SortIdNt	LocalDeclSeq	LocalDeclNt	PredSeq		
%type<o>	FuAtSeq		CondSeq		PredicateNt		
%type<o>	FunctionNt	AttributeNt	ConditionNt	ExprSeq		
%type<o>	ExprNt		StringExprSeq	CaseSeq		PatternCaseSeq		
%type<o>	FormulaCaseSeq	FormulaNt	OrFormulaNt	AndFormulaNt		
%type<o>	NegFormulaNt	PrimFormulaNt	PatternNt	ItemSeq		
%type<o>	ItemNt		SubPatternsNt   ParamSeq	SortIdSeq2
%type<o>	PNT		LPINFO		StringList	FuncApplNt
%type<o>	DynFuncNt	RuleListNt	RuleNt		DynSemInputNt
%type<o>	UpdateListNt	UpdateOrRuleNt	UpdateNt	CaseConstNt
%type<o>	CaseIsListNt	CaseIsNt

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
|	PRD  IDENT  '['  SepSortIdSeq  ']' 
	{	$$ = PredDecl( DefId($2.v,$2.l,$2.c,$2.f), $4 ); }
|	PRD  IDENT  '['  ']' 
	{	$$ = PredDecl( DefId($2.v,$2.l,$2.c,$2.f), SortIdList() ); }
|	FCT  IDENT  '('  SepSortIdSeq  ')'  SortIdNt
	{	$$ = FuncDecl( DefId($2.v,$2.l,$2.c,$2.f), $4, $6 ); }
|	FCT  IDENT  '('  ')'  SortIdNt
	{	$$ = FuncDecl( DefId($2.v,$2.l,$2.c,$2.f), SortIdList(), $5 ); }
|	STRUC IDENT '['  IDENT ']'  '{'  LocalDeclSeq  '}' 
	{	$$ = Structure( DefId($2.v,$2.l,$2.c,$2.f), TermSortId($4.v,$4.l,$4.c,$4.f), $7); }
|	STRUC IDENT '['  IDENT ']'  
	{	$$ = Structure( DefId($2.v,$2.l,$2.c,$2.f), TermSortId($4.v,$4.l,$4.c,$4.f), LocalDeclList()); }
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
	DYN  IDENT  '('  ParamSeq  ')'  SortIdNt  ':'  ExprNt
	{	$$ = DynFunc( DefId($2.v,$2.l,$2.c,$2.f), subterm(1,$4), subterm(2,$4), $6, $8 ); }
|	DYN  IDENT  '('  ')'  SortIdNt  ':'  ExprNt
	{	$$ = DynFunc( DefId($2.v,$2.l,$2.c,$2.f), SortIdList(), NameList(), $5, $7 ); }
;
DynSemInputNt :
	IN  IDENT '(' ')' SortIdNt
	{	$$ = DynSemInput( DefId($2.v,$2.l,$2.c,$2.f), SortIdList(), $5 ); }
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
	IDENT  '('  ')'
	{	$$ = FuncAppl( ApplId($1.v,$1.l,$1.c,$1.f), ExprList() ); }
|	IDENT  '('  ExprSeq  ')'
	{	$$ = FuncAppl( ApplId($1.v,$1.l,$1.c,$1.f), $3 ); }
|	ExprNt  '.'  IDENT
	{	$$ = FuncAppl( ApplId($3.v,$3.l,$3.c,$3.f), appback(ExprList(),$1) ); }
;
ProdSeq :
	ProductionNt
	{	$$ = appback( ProdList(), $1 ); }
|	ProdSeq ProductionNt
	{	$$ = appback( $1, $2 ); }
;
ProductionNt:
	IDENT PNT '*'  SortIdNt  LPINFO
	{	$$ = ListProd( DefId($1.v,$1.l,$1.c,$1.f), $4 ); mxy_enterlp( $5, $2 ); }
|	IDENT PNT '('  SortIdSeq ')' 
	{	$$ = TupelProd( DefId($1.v,$1.l,$1.c,$1.f), mxy_entertp( $4, $2 ) ); }
|	IDENT PNT '='  SubClassSeq
	{	$$ = ClassProd( DefId($1.v,$1.l,$1.c,$1.f), mxy_entercp( $4, $2, $1.v ) ); }
|	IDENT PARSprio '=' SortIdSeq2  '|' STRINGCONST SortIdNt StringList
	{	$$ = ClassProd( DefId($1.v,$1.l,$1.c,$1.f),
		mxy_entercp( appback( $4, CPinfo( appback( StringList(), $6.v), $7, $8 )), Parsprio(), $1.v )); }
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
SortIdNt :
	IDENT
	{	$$ = TermSortId($1.v,$1.l,$1.c,$1.f); }
|	IDENT AT
	{	$$ = NodeSortId($1.v,$1.l,$1.c,$1.f); }
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
|	PRD  IDENT  '['  SepSortIdSeq  ']' 
	{	$$ = PredDecl( DefId($2.v,$2.l,$2.c,$2.f), $4 ); }
|	PRD  IDENT  '['  ']' 
	{	$$ = PredDecl( DefId($2.v,$2.l,$2.c,$2.f), SortIdList() ); }
|	FCT  IDENT  '('  SepSortIdSeq  ')'  SortIdNt
	{	$$ = FuncDecl( DefId($2.v,$2.l,$2.c,$2.f), $4, $6 ); }
|	FCT  IDENT  '('  ')'  SortIdNt
	{	$$ = FuncDecl( DefId($2.v,$2.l,$2.c,$2.f), SortIdList(), $5 ); }
|	ATT  IDENT  '('  SepSortIdSeq  ')'  SortIdNt
	{	$$ = AttrDecl( DefId($2.v,$2.l,$2.c,$2.f), $4, $6 ); }
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
PredicateNt :
	PRD  IDENT  '['  ParamSeq  ']'   ':'  FormulaNt
	{	$$ = Predicate( DefId($2.v,$2.l,$2.c,$2.f), subterm(1,$4), subterm(2,$4), $7 ); }
|	PRD  IDENT  '['  ']'   ':'  FormulaNt
	{	$$ = Predicate( DefId($2.v,$2.l,$2.c,$2.f), SortIdList(), NameList(), $6 ); }
;
FunctionNt :
	FCT  IDENT  '('  ParamSeq  ')'  SortIdNt  ':'  ExprNt
	{	$$ = Function( DefId($2.v,$2.l,$2.c,$2.f), subterm(1,$4), subterm(2,$4), $6, $8 ); }
|	FCT  IDENT  '('  ')'  SortIdNt  ':'  ExprNt
	{	$$ = Function( DefId($2.v,$2.l,$2.c,$2.f), SortIdList(), NameList(), $5, $7 ); }
;
AttributeNt :
	ATT  IDENT  '('  ParamSeq  ')'  SortIdNt  ':'  ExprNt
	{	$$ = Attribute( DefId($2.v,$2.l,$2.c,$2.f), subterm(1,$4), subterm(2,$4), $6, $8 ); }
;
ParamSeq :
	SortIdNt  IDENT  
	{	$$ = ParTup( appback( SortIdList(), $1 ), 
                     appback( NameList(),   Name($2.v,$2.l,$2.c,$2.f) )   ); }
|	ParamSeq  ','  SortIdNt  IDENT
	{	$$ = ParTup( appback( subterm(1,$1), $3 ), 
                     appback( subterm(2,$1), Name($4.v,$4.l,$4.c,$4.f) )  ); }
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
|	IDENT
	{	$$ =  Name($1.v,$1.l,$1.c,$1.f); }
|	APO  StringExprSeq  APC
	{	$$ =  StringExpr($2,$1.l,$1.c,$1.f); }
|	FuncApplNt
	{	$$ = $1; }
|	IF  CaseSeq  ELSE  ExprNt
	{	$$ = IfExpr( $2, $4, $1.l, $1.c,$1.f); }
|	LET  IDENT  EQSYM  ExprNt  ':'  ExprNt
	{	$$ = LetExpr( Name($2.v,$2.l,$2.c,$2.f), $4, $6 ); }
|	UNDEF
	{	$$ = DynUndef(); }
;
StringExprSeq :
	ExprNt
	{	$$ = appback( ExprList(), $1 ); }
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
	{	$$ =  cOr($1,$3); }
|	AndFormulaNt
	{	$$ =  $1; }
;
AndFormulaNt :
	NegFormulaNt  ANDSYM  AndFormulaNt
	{	$$ =  cAnd($1,$3); }
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
	{	$$ = PredAppl( ApplId(stoid(atoe("eq")),itoe(0),itoe(0),atoe(file)),
						appback( appback( ExprList(),$1), $3)  ); }
|	ExprNt  '#'  ExprNt
	{	$$ = Neg( PredAppl( ApplId(stoid(atoe("eq")),itoe(0),itoe(0),atoe(file)),
							appback( appback( ExprList(),$1), $3)  ) ); }
|	'{'  FormulaNt  '}'
	{	$$ =  $2; }
;
PatternNt :
	IDENT 
	{	$$ =  Pattern( Blank(itoe(line),atoe(file)), Blank(itoe(line),atoe(file)), Name($1.v,$1.l,$1.c,$1.f) ); }
|	IDENT AT 
	{	$$ =  Pattern( NodeSortId($1.v,$1.l,$1.c,$1.f), Blank(itoe(line),atoe(file)),Blank(itoe(line),atoe(file)) ); } 
|	SortIdNt   IDENT
	{	$$ =  Pattern( $1, Blank(itoe(line),atoe(file)), Name($2.v,$2.l,$2.c,$2.f) ); }
|	SubPatternsNt 
	{	$$ =  Pattern( Blank(itoe(line),atoe(file)), $1, Blank(itoe(line),atoe(file)) ); }
|	SubPatternsNt  IDENT
	{	$$ =  Pattern( Blank(itoe(line),atoe(file)), $1, Name($2.v,$2.l,$2.c,$2.f) ); }
|	IDENT AT  SubPatternsNt
	{	$$ =  Pattern( NodeSortId($1.v,$1.l,$1.c,$1.f), $3, Blank(itoe(line),atoe(file)) ); }
|	IDENT AT  SubPatternsNt  IDENT
	{	$$ =  Pattern( NodeSortId($1.v,$1.l,$1.c,$1.f), $3, Name($4.v,$4.l,$4.c,$4.f) ); }
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
	{	$$ = Blank(itoe(line),atoe(file)); }
|	PatternNt
	{	$$ =  $1; }
;
%%

static ELEMENT ctrue(){
  return FuncAppl( ApplId(stoid(atoe("true")),itoe(0),itoe(0),atoe("unknown")), ExprList() );
}

static ELEMENT cfalse(){
  return FuncAppl( ApplId(stoid(atoe("false")),itoe(0),itoe(0),atoe("unknown")), ExprList() );
}

ELEMENT cAnd( ELEMENT LOP, ELEMENT ROP ){
  ELEMENT ifclause =
    IfExpr( appfront( FormulaCase( Neg(LOP), cfalse()) , FormulaCaseList()), 
	   IfExpr( appfront( FormulaCase( ROP, ctrue()), FormulaCaseList()), 
			    cfalse() , itoe(0), itoe(0), atoe("unknown")), itoe(0), itoe(0), atoe("unknown") );
  return PredAppl( ApplId(stoid(atoe("eq")),itoe(0),itoe(0),atoe("unknown")),
	     appback( appback( ExprList(), ctrue()), ifclause)  );
}

ELEMENT cOr( ELEMENT LOP, ELEMENT ROP ){
  ELEMENT ifclause =
    IfExpr( appfront( FormulaCase( LOP, ctrue()) , FormulaCaseList()), 
	   IfExpr( appfront( FormulaCase( ROP, ctrue()), FormulaCaseList()), 
			    cfalse(), itoe(0), itoe(0), atoe("unknown") ) , itoe(0), itoe(0),atoe("unknown") );
  return PredAppl( ApplId(stoid(atoe("eq")),itoe(0),itoe(0), atoe("unknown")),
	     appback( appback( ExprList(), ctrue()), ifclause)  ); 
}

#include "max_scan.c" 
#include <stdio.h> 

static parserrorflag = 0;

int yyerror( char *s ){
	fprintf( stderr, "**** File %s, Line %d, Column %d: %s\n",file,line,column,s );
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




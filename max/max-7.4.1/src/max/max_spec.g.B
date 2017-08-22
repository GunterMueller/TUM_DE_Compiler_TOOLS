%SORTS
Specification
ProdList
SortIdList
LocalDeclList
PredList
FuAtList
CondList
PatternList
ExprList
PatternCaseList
FormulaCaseList
ItemList
NameList
DefIdNodeList
CompExprNodeList
NameNList
ItemNList
Relationship
SortIdNList
ExprNList
OrValue
FList
ApplList
FuAtListInfo
FuAtNodeList
IntResList
IntList
RefList
ProdNodeList
IdentList
CharList
RsideInfo
RsideList
LsideList
LPinfoListlist
LPinfolist
StringList
CPinfoList
CPinfoListlist
RuleList
CaseIsList
UpdateList
UListNodeList
CaseTripelList
ListProd
TupelProd
ClassProd
PredeclProd
PredDecl
FuncDecl
Structure
Predicate
Function
Attribute
Condition
AttrDecl
CharConst
IntConst
StringConst
SortConst
FuncAppl
IfExpr
LetExpr
StringExpr
PatternCase
FormulaCase
PredAppl
Or
And
Impl
Neg
Pattern
DefId
TermSortId
NodeSortId
ApplId
Name
Blank
Asterisk
ParTup
NameDepthTup
RelPosition
AbsPosition
TopPosition
Fath
Lbroth
Rbroth
Son
SonTC
FClosure
TWson
TWfath
TWrbroth
TWlbroth
RelevAcc
AllNodes
Parsnr
Parsline
Parscol
Parspos
Parsprio
Parsrule
Parsaddrule
Parsno
Parsleft
Parsright
Parsaux
ParsStern
ParsPlus
IdentTripel
CPinfo
DynFunc
IfRule
CaseRule
CaseIs
Update
DynUndef
DynSemInput
CaseTripel
Element Point Node Term
GlobalDecl ProdList PredDecl FuncDecl Structure RuleList
Production ListProd TupelProd ClassProd PredeclProd
LocalDecl PredList FuAtList CondList PredDecl FuncDecl AttrDecl DynFunc DynSemInput
Expr Constant Name FuncAppl ComposedExpr StringExpr DynUndef
Constant CharConst IntConst StringConst SortConst
ComposedExpr IfExpr LetExpr
CaseList PatternCaseList FormulaCaseList
Formula PredAppl Or And Impl Neg
SortPos SortId Blank
SubPatternPos ItemList Blank
NamePos Name Blank
Item Pattern Blank Asterisk
UsedId SortId ApplId
SortId TermSortId NodeSortId
Declaration PredDecl FuncDecl AttrDecl
Definition Production Predicate Function Attribute
DefWithoutProd Predicate Function Attribute
ApplyEntity Predicate Function Attribute DynFunc DynSemInput
Scope ApplyEntity Condition PatternCase LetExpr
SortCdList Reference
Section ApplyEntity Condition ComposedExpr
Case PatternCase FormulaCase
ItemPosition RelPosition AbsPosition TopPosition
Relative Fath Son SonTC Lbroth Rbroth
MetaSort Reference
IfCase PatternCase FormulaCase
Value OrValue FList FClosure FValue
FValue DefId TWfath TWson TWrbroth TWlbroth RelevAcc
FctOrAtt Function Attribute
FctOrAttDecl Function Attribute FuncDecl AttrDecl
OrderTup Int
BinOp Or And Impl
DefIdNodeInfo DefIdNodeList AllNodes
IntResExpr ComposedExpr FuncAppl ApplyEntity Condition
IntResOrName IntResExpr Name
Rside SortId String Parsnr Parsline Parscol Parspos
Lside Parsrule Parsaddrule Parsno Parsaux Parsleft Parsright Parsprio Int
LPinfo ParsStern ParsPlus
Rule IfRule CaseRule
CaseConst CharConst IntConst SortConst
UpdateOrRule Update Rule
Point
Node
nil
Term
NodeSort
PredeclSort
ClassSort
TupelSort
ListSort
Ident
Bool
Char
Int
String
Reference
%TUPLES
ListProd DefId SortId
TupelProd DefId SortIdList
ClassProd DefId SortIdList
PredeclProd DefId
PredDecl DefId SortIdList
FuncDecl DefId SortIdList SortId
Structure DefId TermSortId LocalDeclList
Predicate DefId SortIdList NameList Formula
Function DefId SortIdList NameList SortId Expr
Attribute DefId SortIdList NameList SortId Expr
Condition PatternList Formula Expr
AttrDecl DefId SortIdList SortId
CharConst Char Int Int String
IntConst Int Int Int String
StringConst String Int Int String
SortConst SortId
FuncAppl ApplId ExprList
IfExpr CaseList Expr Int Int String
LetExpr Name Expr Expr
StringExpr ExprList Int Int String
PatternCase Pattern Expr
FormulaCase Formula Expr
PredAppl ApplId ExprList
Or Formula Formula
And Formula Formula
Impl Formula Formula
Neg Formula
Pattern SortPos SubPatternPos NamePos
DefId Ident Int Int String
TermSortId Ident Int Int String
NodeSortId Ident Int Int String
ApplId Ident Int Int String
Name Ident Int Int String
Blank Int String
Asterisk
ParTup SortIdList NameList
NameDepthTup Name@ Int
RelPosition Int
AbsPosition Int
TopPosition
Fath
Lbroth Int
Rbroth Int
Son Int
SonTC Int Int Int Int Int
FClosure Value
TWson Int
TWfath
TWrbroth
TWlbroth
RelevAcc Int
AllNodes
Parsnr Int
Parsline
Parscol
Parspos
Parsprio
Parsrule StringList
Parsaddrule StringList
Parsno
Parsleft
Parsright
Parsaux
ParsStern String
ParsPlus String
IdentTripel Ident Ident Ident
CPinfo StringList SortId StringList
DynFunc DefId SortIdList NameList SortId Expr
IfRule Formula UpdateList UpdateList
CaseRule Expr CaseIsList UpdateList
CaseIs CaseConst UpdateList
Update FuncAppl Expr
DynUndef
DynSemInput DefId SortIdList SortId
CaseTripel DefIdNodeList DefIdNodeList UpdateList@
%LISTS
Specification GlobalDecl
ProdList Production
SortIdList SortId
LocalDeclList LocalDecl
PredList Predicate
FuAtList FctOrAtt
CondList Condition
PatternList Pattern
ExprList Expr
PatternCaseList PatternCase
FormulaCaseList FormulaCase
ItemList Item
NameList Name
DefIdNodeList DefId@
CompExprNodeList ComposedExpr@
NameNList Name@
ItemNList Item@
Relationship Relative
SortIdNList SortId@
ExprNList Expr@
OrValue Value
FList Value
ApplList FuncAppl@
FuAtListInfo FuAtNodeList
FuAtNodeList FctOrAtt@
IntResList IntResOrName@
IntList Int
RefList Reference
ProdNodeList Production@
IdentList Ident
CharList Char
RsideInfo Rside
RsideList RsideInfo
LsideList Lside
LPinfoListlist LPinfolist
LPinfolist LPinfo
StringList String
CPinfoList CPinfo
CPinfoListlist CPinfoList
RuleList Rule
CaseIsList CaseIs
UpdateList UpdateOrRule
UListNodeList UpdateList@
CaseTripelList CaseTripel
%ATTRIBUTES
DefIdNodeList term_basesorts( NodeSortId@ )
DefIdNodeList term_basesorts( TermSortId@ )
DefIdNodeList node_basesorts( NodeSortId@ )
DefIdNodeList node_basesorts( TermSortId@ )
Scope@ encl_scope( LetExpr@ )
Scope@ encl_scope( PatternCase@ )
Scope@ encl_scope( Condition@ )
Scope@ encl_scope( DynSemInput@ )
Scope@ encl_scope( DynFunc@ )
Scope@ encl_scope( Attribute@ )
Scope@ encl_scope( Function@ )
Scope@ encl_scope( Predicate@ )
Name@ bind_pos( Name@ )
Int numberofastrks( ItemList@ )
Int predeclprodcd( PredeclProd@ )
Int tupelprodcd( TupelProd@ )
Int listprodcd( ListProd@ )
Int classprodcd( ClassProd@ )
ItemPosition patnpos( Pattern@ )
Int num_items( Pattern@ )
ExprList@ args( FuncAppl@ )
ExprNList caseexpr( FormulaCase@ )
ExprNList caseexpr( PatternCase@ )
ExprNList allexpr( IfExpr@ )
PatternCase@ encl_patterncase( Specification@ )
PatternCase@ encl_patterncase( ProdList@ )
PatternCase@ encl_patterncase( SortIdList@ )
PatternCase@ encl_patterncase( LocalDeclList@ )
PatternCase@ encl_patterncase( PredList@ )
PatternCase@ encl_patterncase( FuAtList@ )
PatternCase@ encl_patterncase( CondList@ )
PatternCase@ encl_patterncase( PatternList@ )
PatternCase@ encl_patterncase( ExprList@ )
PatternCase@ encl_patterncase( PatternCaseList@ )
PatternCase@ encl_patterncase( FormulaCaseList@ )
PatternCase@ encl_patterncase( ItemList@ )
PatternCase@ encl_patterncase( NameList@ )
PatternCase@ encl_patterncase( DefIdNodeList@ )
PatternCase@ encl_patterncase( CompExprNodeList@ )
PatternCase@ encl_patterncase( NameNList@ )
PatternCase@ encl_patterncase( ItemNList@ )
PatternCase@ encl_patterncase( Relationship@ )
PatternCase@ encl_patterncase( SortIdNList@ )
PatternCase@ encl_patterncase( ExprNList@ )
PatternCase@ encl_patterncase( OrValue@ )
PatternCase@ encl_patterncase( FList@ )
PatternCase@ encl_patterncase( ApplList@ )
PatternCase@ encl_patterncase( FuAtListInfo@ )
PatternCase@ encl_patterncase( FuAtNodeList@ )
PatternCase@ encl_patterncase( IntResList@ )
PatternCase@ encl_patterncase( IntList@ )
PatternCase@ encl_patterncase( RefList@ )
PatternCase@ encl_patterncase( ProdNodeList@ )
PatternCase@ encl_patterncase( IdentList@ )
PatternCase@ encl_patterncase( CharList@ )
PatternCase@ encl_patterncase( RsideInfo@ )
PatternCase@ encl_patterncase( RsideList@ )
PatternCase@ encl_patterncase( LsideList@ )
PatternCase@ encl_patterncase( LPinfoListlist@ )
PatternCase@ encl_patterncase( LPinfolist@ )
PatternCase@ encl_patterncase( StringList@ )
PatternCase@ encl_patterncase( CPinfoList@ )
PatternCase@ encl_patterncase( CPinfoListlist@ )
PatternCase@ encl_patterncase( RuleList@ )
PatternCase@ encl_patterncase( CaseIsList@ )
PatternCase@ encl_patterncase( UpdateList@ )
PatternCase@ encl_patterncase( UListNodeList@ )
PatternCase@ encl_patterncase( CaseTripelList@ )
PatternCase@ encl_patterncase( ListProd@ )
PatternCase@ encl_patterncase( TupelProd@ )
PatternCase@ encl_patterncase( ClassProd@ )
PatternCase@ encl_patterncase( PredeclProd@ )
PatternCase@ encl_patterncase( PredDecl@ )
PatternCase@ encl_patterncase( FuncDecl@ )
PatternCase@ encl_patterncase( Structure@ )
PatternCase@ encl_patterncase( Predicate@ )
PatternCase@ encl_patterncase( Function@ )
PatternCase@ encl_patterncase( Attribute@ )
PatternCase@ encl_patterncase( Condition@ )
PatternCase@ encl_patterncase( AttrDecl@ )
PatternCase@ encl_patterncase( CharConst@ )
PatternCase@ encl_patterncase( IntConst@ )
PatternCase@ encl_patterncase( StringConst@ )
PatternCase@ encl_patterncase( SortConst@ )
PatternCase@ encl_patterncase( FuncAppl@ )
PatternCase@ encl_patterncase( IfExpr@ )
PatternCase@ encl_patterncase( LetExpr@ )
PatternCase@ encl_patterncase( StringExpr@ )
PatternCase@ encl_patterncase( PatternCase@ )
PatternCase@ encl_patterncase( FormulaCase@ )
PatternCase@ encl_patterncase( PredAppl@ )
PatternCase@ encl_patterncase( Or@ )
PatternCase@ encl_patterncase( And@ )
PatternCase@ encl_patterncase( Impl@ )
PatternCase@ encl_patterncase( Neg@ )
PatternCase@ encl_patterncase( Pattern@ )
PatternCase@ encl_patterncase( DefId@ )
PatternCase@ encl_patterncase( TermSortId@ )
PatternCase@ encl_patterncase( NodeSortId@ )
PatternCase@ encl_patterncase( ApplId@ )
PatternCase@ encl_patterncase( Name@ )
PatternCase@ encl_patterncase( Blank@ )
PatternCase@ encl_patterncase( Asterisk@ )
PatternCase@ encl_patterncase( ParTup@ )
PatternCase@ encl_patterncase( NameDepthTup@ )
PatternCase@ encl_patterncase( RelPosition@ )
PatternCase@ encl_patterncase( AbsPosition@ )
PatternCase@ encl_patterncase( TopPosition@ )
PatternCase@ encl_patterncase( Fath@ )
PatternCase@ encl_patterncase( Lbroth@ )
PatternCase@ encl_patterncase( Rbroth@ )
PatternCase@ encl_patterncase( Son@ )
PatternCase@ encl_patterncase( SonTC@ )
PatternCase@ encl_patterncase( FClosure@ )
PatternCase@ encl_patterncase( TWson@ )
PatternCase@ encl_patterncase( TWfath@ )
PatternCase@ encl_patterncase( TWrbroth@ )
PatternCase@ encl_patterncase( TWlbroth@ )
PatternCase@ encl_patterncase( RelevAcc@ )
PatternCase@ encl_patterncase( AllNodes@ )
PatternCase@ encl_patterncase( Parsnr@ )
PatternCase@ encl_patterncase( Parsline@ )
PatternCase@ encl_patterncase( Parscol@ )
PatternCase@ encl_patterncase( Parspos@ )
PatternCase@ encl_patterncase( Parsprio@ )
PatternCase@ encl_patterncase( Parsrule@ )
PatternCase@ encl_patterncase( Parsaddrule@ )
PatternCase@ encl_patterncase( Parsno@ )
PatternCase@ encl_patterncase( Parsleft@ )
PatternCase@ encl_patterncase( Parsright@ )
PatternCase@ encl_patterncase( Parsaux@ )
PatternCase@ encl_patterncase( ParsStern@ )
PatternCase@ encl_patterncase( ParsPlus@ )
PatternCase@ encl_patterncase( IdentTripel@ )
PatternCase@ encl_patterncase( CPinfo@ )
PatternCase@ encl_patterncase( DynFunc@ )
PatternCase@ encl_patterncase( IfRule@ )
PatternCase@ encl_patterncase( CaseRule@ )
PatternCase@ encl_patterncase( CaseIs@ )
PatternCase@ encl_patterncase( Update@ )
PatternCase@ encl_patterncase( DynUndef@ )
PatternCase@ encl_patterncase( DynSemInput@ )
PatternCase@ encl_patterncase( CaseTripel@ )
PatternCase@ encl_patterncase( NodeSort@ )
PatternCase@ encl_patterncase( PredeclSort@ )
PatternCase@ encl_patterncase( ClassSort@ )
PatternCase@ encl_patterncase( TupelSort@ )
PatternCase@ encl_patterncase( ListSort@ )
PatternCase@ encl_patterncase( Ident@ )
PatternCase@ encl_patterncase( Bool@ )
PatternCase@ encl_patterncase( Char@ )
PatternCase@ encl_patterncase( Int@ )
PatternCase@ encl_patterncase( String@ )
PatternCase@ encl_patterncase( Reference@ )
Pattern@ top_pattern( Specification@ )
Pattern@ top_pattern( ProdList@ )
Pattern@ top_pattern( SortIdList@ )
Pattern@ top_pattern( LocalDeclList@ )
Pattern@ top_pattern( PredList@ )
Pattern@ top_pattern( FuAtList@ )
Pattern@ top_pattern( CondList@ )
Pattern@ top_pattern( PatternList@ )
Pattern@ top_pattern( ExprList@ )
Pattern@ top_pattern( PatternCaseList@ )
Pattern@ top_pattern( FormulaCaseList@ )
Pattern@ top_pattern( ItemList@ )
Pattern@ top_pattern( NameList@ )
Pattern@ top_pattern( DefIdNodeList@ )
Pattern@ top_pattern( CompExprNodeList@ )
Pattern@ top_pattern( NameNList@ )
Pattern@ top_pattern( ItemNList@ )
Pattern@ top_pattern( Relationship@ )
Pattern@ top_pattern( SortIdNList@ )
Pattern@ top_pattern( ExprNList@ )
Pattern@ top_pattern( OrValue@ )
Pattern@ top_pattern( FList@ )
Pattern@ top_pattern( ApplList@ )
Pattern@ top_pattern( FuAtListInfo@ )
Pattern@ top_pattern( FuAtNodeList@ )
Pattern@ top_pattern( IntResList@ )
Pattern@ top_pattern( IntList@ )
Pattern@ top_pattern( RefList@ )
Pattern@ top_pattern( ProdNodeList@ )
Pattern@ top_pattern( IdentList@ )
Pattern@ top_pattern( CharList@ )
Pattern@ top_pattern( RsideInfo@ )
Pattern@ top_pattern( RsideList@ )
Pattern@ top_pattern( LsideList@ )
Pattern@ top_pattern( LPinfoListlist@ )
Pattern@ top_pattern( LPinfolist@ )
Pattern@ top_pattern( StringList@ )
Pattern@ top_pattern( CPinfoList@ )
Pattern@ top_pattern( CPinfoListlist@ )
Pattern@ top_pattern( RuleList@ )
Pattern@ top_pattern( CaseIsList@ )
Pattern@ top_pattern( UpdateList@ )
Pattern@ top_pattern( UListNodeList@ )
Pattern@ top_pattern( CaseTripelList@ )
Pattern@ top_pattern( ListProd@ )
Pattern@ top_pattern( TupelProd@ )
Pattern@ top_pattern( ClassProd@ )
Pattern@ top_pattern( PredeclProd@ )
Pattern@ top_pattern( PredDecl@ )
Pattern@ top_pattern( FuncDecl@ )
Pattern@ top_pattern( Structure@ )
Pattern@ top_pattern( Predicate@ )
Pattern@ top_pattern( Function@ )
Pattern@ top_pattern( Attribute@ )
Pattern@ top_pattern( Condition@ )
Pattern@ top_pattern( AttrDecl@ )
Pattern@ top_pattern( CharConst@ )
Pattern@ top_pattern( IntConst@ )
Pattern@ top_pattern( StringConst@ )
Pattern@ top_pattern( SortConst@ )
Pattern@ top_pattern( FuncAppl@ )
Pattern@ top_pattern( IfExpr@ )
Pattern@ top_pattern( LetExpr@ )
Pattern@ top_pattern( StringExpr@ )
Pattern@ top_pattern( PatternCase@ )
Pattern@ top_pattern( FormulaCase@ )
Pattern@ top_pattern( PredAppl@ )
Pattern@ top_pattern( Or@ )
Pattern@ top_pattern( And@ )
Pattern@ top_pattern( Impl@ )
Pattern@ top_pattern( Neg@ )
Pattern@ top_pattern( Pattern@ )
Pattern@ top_pattern( DefId@ )
Pattern@ top_pattern( TermSortId@ )
Pattern@ top_pattern( NodeSortId@ )
Pattern@ top_pattern( ApplId@ )
Pattern@ top_pattern( Name@ )
Pattern@ top_pattern( Blank@ )
Pattern@ top_pattern( Asterisk@ )
Pattern@ top_pattern( ParTup@ )
Pattern@ top_pattern( NameDepthTup@ )
Pattern@ top_pattern( RelPosition@ )
Pattern@ top_pattern( AbsPosition@ )
Pattern@ top_pattern( TopPosition@ )
Pattern@ top_pattern( Fath@ )
Pattern@ top_pattern( Lbroth@ )
Pattern@ top_pattern( Rbroth@ )
Pattern@ top_pattern( Son@ )
Pattern@ top_pattern( SonTC@ )
Pattern@ top_pattern( FClosure@ )
Pattern@ top_pattern( TWson@ )
Pattern@ top_pattern( TWfath@ )
Pattern@ top_pattern( TWrbroth@ )
Pattern@ top_pattern( TWlbroth@ )
Pattern@ top_pattern( RelevAcc@ )
Pattern@ top_pattern( AllNodes@ )
Pattern@ top_pattern( Parsnr@ )
Pattern@ top_pattern( Parsline@ )
Pattern@ top_pattern( Parscol@ )
Pattern@ top_pattern( Parspos@ )
Pattern@ top_pattern( Parsprio@ )
Pattern@ top_pattern( Parsrule@ )
Pattern@ top_pattern( Parsaddrule@ )
Pattern@ top_pattern( Parsno@ )
Pattern@ top_pattern( Parsleft@ )
Pattern@ top_pattern( Parsright@ )
Pattern@ top_pattern( Parsaux@ )
Pattern@ top_pattern( ParsStern@ )
Pattern@ top_pattern( ParsPlus@ )
Pattern@ top_pattern( IdentTripel@ )
Pattern@ top_pattern( CPinfo@ )
Pattern@ top_pattern( DynFunc@ )
Pattern@ top_pattern( IfRule@ )
Pattern@ top_pattern( CaseRule@ )
Pattern@ top_pattern( CaseIs@ )
Pattern@ top_pattern( Update@ )
Pattern@ top_pattern( DynUndef@ )
Pattern@ top_pattern( DynSemInput@ )
Pattern@ top_pattern( CaseTripel@ )
Pattern@ top_pattern( NodeSort@ )
Pattern@ top_pattern( PredeclSort@ )
Pattern@ top_pattern( ClassSort@ )
Pattern@ top_pattern( TupelSort@ )
Pattern@ top_pattern( ListSort@ )
Pattern@ top_pattern( Ident@ )
Pattern@ top_pattern( Bool@ )
Pattern@ top_pattern( Char@ )
Pattern@ top_pattern( Int@ )
Pattern@ top_pattern( String@ )
Pattern@ top_pattern( Reference@ )
Int son_nr( Attribute@ )
Int son_nr( Function@ )
Int relacc_nr( FuncAppl@ )
ApplList appl_list_formula( Neg@ )
ApplList appl_list_formula( Impl@ )
ApplList appl_list_formula( And@ )
ApplList appl_list_formula( Or@ )
ApplList appl_list_formula( PredAppl@ )
ApplList appl_list_case( FormulaCase@ )
ApplList appl_list_case( PatternCase@ )
ApplList appl_list_expr( DynUndef@ )
ApplList appl_list_expr( StringExpr@ )
ApplList appl_list_expr( LetExpr@ )
ApplList appl_list_expr( IfExpr@ )
ApplList appl_list_expr( FuncAppl@ )
ApplList appl_list_expr( Name@ )
ApplList appl_list_expr( SortConst@ )
ApplList appl_list_expr( StringConst@ )
ApplList appl_list_expr( IntConst@ )
ApplList appl_list_expr( CharConst@ )
ApplList appl_list( Attribute@ )
ApplList appl_list( Function@ )
Value def_value( DefId@ )
Int node_parnr( AttrDecl@ )
Int node_parnr( FuncDecl@ )
Int node_parnr( Attribute@ )
Int node_parnr( Function@ )
Value appl_value( FuncAppl@ )
Expr@ nodepar_expr( FuncAppl@ )
Value valueterm_list( FormulaCase@ )
Value valueterm_list( PatternCase@ )
Value valueterm( DynUndef@ )
Value valueterm( StringExpr@ )
Value valueterm( LetExpr@ )
Value valueterm( IfExpr@ )
Value valueterm( FuncAppl@ )
Value valueterm( Name@ )
Value valueterm( SortConst@ )
Value valueterm( StringConst@ )
Value valueterm( IntConst@ )
Value valueterm( CharConst@ )
RefList attr_list_matlist( FuAtList@ )
Value result_value( Attribute@ )
Value result_value( Function@ )
Bool is_relev_att_access( FuncAppl@ )
OrderTup appl_order( FuncAppl@ )
ApplList appl_relacc_list( Attribute@ )
ApplList appl_relacc_list( Function@ )
Bool maybe_wait( FuncAppl@ )
String cgen_name( Name@ )
String cgen_name( Condition@ )
String cgen_name( DynSemInput@ )
String cgen_name( DynFunc@ )
String cgen_name( Attribute@ )
String cgen_name( Function@ )
String cgen_name( Predicate@ )
String cgen_name( FuncAppl@ )
String cgen_name( LetExpr@ )
String cgen_name( IfExpr@ )
IntResList sces_appl( DynSemInput@ )
IntResList sces_appl( DynFunc@ )
IntResList sces_appl( Attribute@ )
IntResList sces_appl( Function@ )
IntResList sces_appl( Predicate@ )
IntResList sces1_cond( Condition@ )
IntResList sces2_cond( Condition@ )
IntResList sces1_let( LetExpr@ )
IntResList sces2_let( LetExpr@ )
IntResList sces_if( IfExpr@ )
IntResList sces1_fcase( FormulaCase@ )
IntResList sces2_fcase( FormulaCase@ )
IntResList sces_pcase( PatternCase@ )
IntResList sces_attacc( FuncAppl@ )
IntResList lokvar_need( Attribute@ )
IntResList lokvar_need( Function@ )
IntResList intres_collect( Condition@ )
IntResList intres_collect( DynSemInput@ )
IntResList intres_collect( DynFunc@ )
IntResList intres_collect( Attribute@ )
IntResList intres_collect( Function@ )
IntResList intres_collect( Predicate@ )
IntResList intres_collect( FuncAppl@ )
IntResList intres_collect( LetExpr@ )
IntResList intres_collect( IfExpr@ )
Lside parscode( PredeclProd@ )
Lside parscode( ClassProd@ )
Lside parscode( TupelProd@ )
Lside parscode( ListProd@ )
LPinfolist LPsepsymbols( ListProd@ )
RsideList TPconcrSyntax( TupelProd@ )
CPinfo CPrsideinfo( ClassProd@ )
DefIdNodeList idtodecls( Ident )
IdentTripel ExchangeTripel( TupelProd@ )
Element ExtraRule( PredeclProd@ )
Element ExtraRule( ClassProd@ )
Element ExtraRule( TupelProd@ )
Element ExtraRule( ListProd@ )
SortCdList subsorts( ClassProd@ )
Relationship att_path( Asterisk@ )
Relationship att_path( Blank@ )
Relationship att_path( Pattern@ )
Item@ pat_anchor( PatternCase@ )
Int eval_groupnr( Attribute@ )
Int eval_groupnr( Function@ )
Int eval_prev_grnum( FuAtList@ )
Int group_index( Attribute@ )
Int group_index( Function@ )
FuAtNodeList eval_group( Attribute@ )
FuAtNodeList eval_group( Function@ )
FuAtListInfo attr_list_groups( FuAtList@ )
Int eval_finegroup( Attribute@ )
Int eval_finegroup( Function@ )
Int eval_aftbef( Attribute@ )
Int eval_aftbef( Function@ )
Bool is_trivial_finegroup( Attribute@ )
Bool is_trivial_finegroup( Function@ )
Int eval_strategy( Attribute@ )
Int eval_strategy( Function@ )
DefIdNodeInfo eval_sortlist( Attribute@ )
DefIdNodeInfo eval_sortlist( Function@ )
FuAtListInfo attr_list_info( FuAtList@ )

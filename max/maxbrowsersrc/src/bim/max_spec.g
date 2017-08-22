>%SORTS
Specification
ProdList
SortIdList
LocalDeclList
PredList
FuncList
AttrList
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
OrValue
FList
ApplList
AttrListInfo
AttrNodeList
IntResList
IntList
RefList
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
FStern
TWson
TWfath
TWrbroth
TWlbroth
RelevAcc
AllNodes
Element Point Node Term
GlobalDecl ProdList PredDecl FuncDecl Structure
Production ListProd TupelProd ClassProd PredeclProd
LocalDecl PredList FuncList AttrList CondList PredDecl FuncDecl AttrDecl
Expr Constant Name FuncAppl ComposedExpr StringExpr
Constant Char Int String SortConst
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
ApplyEntity Predicate Function Attribute
Scope ApplyEntity Condition PatternCase LetExpr
SortCdList Reference
Section ApplyEntity Condition ComposedExpr
Case PatternCase FormulaCase
ItemPosition RelPosition AbsPosition TopPosition
Relative Fath Son Lbroth Rbroth
Value OrValue FList FStern FValue
FValue DefId TWfath TWson TWrbroth TWlbroth RelevAcc
FctOrAtt Function Attribute
FctOrAttDecl Function Attribute FuncDecl AttrDecl
FAList FuncList AttrList
OrderTup Int
BinOp Or And Impl
DefIdNodeInfo DefIdNodeList AllNodes
IntResExpr ComposedExpr FuncAppl ApplyEntity Condition
IntResOrName IntResExpr Name
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
SortConst SortId
FuncAppl ApplId ExprList
IfExpr CaseList Expr
LetExpr Name Expr Expr
StringExpr ExprList Int
PatternCase Pattern Expr
FormulaCase Formula Expr
PredAppl ApplId ExprList
Or Formula Formula
And Formula Formula
Impl Formula Formula
Neg Formula
Pattern SortPos SubPatternPos NamePos
DefId Ident Int Int
TermSortId Ident Int Int
NodeSortId Ident Int Int
ApplId Ident Int Int
Name Ident Int Int
Blank Int
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
FStern Value
TWson Int
TWfath
TWrbroth
TWlbroth
RelevAcc Int
AllNodes
%LISTS
Specification GlobalDecl
ProdList Production
SortIdList SortId
LocalDeclList LocalDecl
PredList Predicate
FuncList Function
AttrList Attribute
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
OrValue Value
FList Value
ApplList FuncAppl@
AttrListInfo AttrNodeList
AttrNodeList FctOrAtt@
IntResList IntResOrName@
IntList Int
RefList Reference
%ATTRIBUTES
DefIdNodeList term_basesorts( SortId@ )
DefIdNodeList node_basesorts( SortId@ )
Scope@ encl_scope( Scope@ )
Name@ bind_pos( Name@ )
Int numberofastrks( ItemList@ )
Int predeclprodcd( PredeclProd@ )
Int tupelprodcd( TupelProd@ )
Int listprodcd( ListProd@ )
Int classprodcd( ClassProd@ )
ItemPosition patnpos( Pattern@ )
Int num_items( Pattern@ )
Int son_nr( FctOrAtt@ )
Int relacc_nr( FuncAppl@ )
ApplList appl_list_formula( Formula@ )
ApplList appl_list_case( Case@ )
ApplList appl_list_expr( Expr@ )
ApplList appl_list( FctOrAtt@ )
Value def_value( DefId@ )
Int node_parnr( FctOrAttDecl@ )
Value appl_value( FuncAppl@ )
Expr@ nodepar_expr( FuncAppl@ )
Value valueterm_list( Case@ )
Value valueterm( Expr@ )
RefList attr_list_matlist( FAList@ )
Value result_value( FctOrAtt@ )
OrderTup appl_order( FuncAppl@ )
ApplList appl_relacc_list( Attribute@ )
String cgen_name( IntResOrName@ )
IntResList sces_appl( ApplyEntity@ )
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
IntResList intres_collect( IntResExpr@ )
DefIdNodeList idtodecls( Ident )
SortCdList subsorts( ClassProd@ )
Relationship att_path( Item@ )
Item@ pat_anchor( PatternCase@ )
Int eval_groupnr( FctOrAtt@ )
Int eval_prev_grnum( FAList@ )
Int group_index( FctOrAtt@ )
AttrNodeList eval_group( FctOrAtt@ )
AttrListInfo attr_list_groups( FAList@ )
Int eval_finegroup( Attribute@ )
Int eval_aftbef( Attribute@ )
Int eval_strategy( Attribute@ )

DefIdNodeInfo eval_sortlist( Attribute@ )
AttrListInfo attr_list_info( AttrList@ )
Bool maybe_wait( FuncAppl@ )

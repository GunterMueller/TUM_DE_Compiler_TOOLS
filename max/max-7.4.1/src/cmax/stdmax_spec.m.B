#line 1 "cmax_spec.cm"
Specification$22,1,"cmax_spec.cm"$ * GlobalDecl$22,21,"cmax_spec.cm"$
GlobalDecl$23,1,"cmax_spec.cm"$ = ProdList$23,21,"cmax_spec.cm"$|PredDecl$23,34,"cmax_spec.cm"$|FuncDecl$23,47,"cmax_spec.cm"$|Structure$23,60,"cmax_spec.cm"$|RuleList$24,21,"cmax_spec.cm"$|MaxCodeText$24,34,"cmax_spec.cm"$
ProdList$26,1,"cmax_spec.cm"$ * Production$26,21,"cmax_spec.cm"$
Production$27,1,"cmax_spec.cm"$ = ListProd$27,21,"cmax_spec.cm"$|TupelProd$27,34,"cmax_spec.cm"$|ClassProd$27,47,"cmax_spec.cm"$|PredeclProd$27,60,"cmax_spec.cm"$
ListProd$28,1,"cmax_spec.cm"$ ( DefId$28,21,"cmax_spec.cm"$ SortId$28,28,"cmax_spec.cm"$ )
TupelProd$29,1,"cmax_spec.cm"$ ( DefId$29,21,"cmax_spec.cm"$ SortIdList$29,28,"cmax_spec.cm"$ )
ClassProd$30,1,"cmax_spec.cm"$ ( DefId$30,21,"cmax_spec.cm"$ SortIdList$30,28,"cmax_spec.cm"$ )
PredeclProd$31,1,"cmax_spec.cm"$ ( DefId$31,21,"cmax_spec.cm"$ )
SortIdList$32,1,"cmax_spec.cm"$ * SortId$32,21,"cmax_spec.cm"$
PredDecl$34,1,"cmax_spec.cm"$ ( DefId$34,21,"cmax_spec.cm"$ SortIdList$34,28,"cmax_spec.cm"$ )
FuncDecl$35,1,"cmax_spec.cm"$ ( DefId$35,21,"cmax_spec.cm"$ SortIdList$35,28,"cmax_spec.cm"$ SortId$35,40,"cmax_spec.cm"$ )
Structure$36,1,"cmax_spec.cm"$ ( DefId$36,21,"cmax_spec.cm"$ TermSortId$36,28,"cmax_spec.cm"$ LocalDeclList$36,40,"cmax_spec.cm"$ )
LocalDeclList$37,1,"cmax_spec.cm"$ * LocalDecl$37,21,"cmax_spec.cm"$
LocalDecl$38,1,"cmax_spec.cm"$ = PredList$38,21,"cmax_spec.cm"$|FuAtList$38,34,"cmax_spec.cm"$|CondList$38,47,"cmax_spec.cm"$|PredDecl$39,21,"cmax_spec.cm"$|FuncDecl$39,34,"cmax_spec.cm"$|AttrDecl$39,47,"cmax_spec.cm"$|DynFunc$40,21,"cmax_spec.cm"$|DynSemInput$40,34,"cmax_spec.cm"$|LatticeDefList$41,21,"cmax_spec.cm"$|VarDeclList$42,21,"cmax_spec.cm"$|AssertionList$42,36,"cmax_spec.cm"$|AssnDefList$43,21,"cmax_spec.cm"$|MaxCodeText$44,21,"cmax_spec.cm"$
MaxCodeText$46,1,"cmax_spec.cm"$ ( String$46,21,"cmax_spec.cm"$ )
PredList$48,1,"cmax_spec.cm"$ * Predicate$48,21,"cmax_spec.cm"$
FuAtList$49,1,"cmax_spec.cm"$ * FctOrAtt$49,21,"cmax_spec.cm"$
CondList$50,1,"cmax_spec.cm"$ * Condition$50,21,"cmax_spec.cm"$
Predicate$51,1,"cmax_spec.cm"$ ( DefId$51,21,"cmax_spec.cm"$ SortIdList$51,28,"cmax_spec.cm"$ NameList$51,40,"cmax_spec.cm"$ Formula$51,50,"cmax_spec.cm"$ )
Function$52,1,"cmax_spec.cm"$ ( DefId$52,21,"cmax_spec.cm"$ SortIdList$52,28,"cmax_spec.cm"$ NameList$52,40,"cmax_spec.cm"$ SortId$52,50,"cmax_spec.cm"$ Expr$52,58,"cmax_spec.cm"$ )
Attribute$53,1,"cmax_spec.cm"$ ( DefId$53,21,"cmax_spec.cm"$ SortIdList$53,28,"cmax_spec.cm"$ NameList$53,40,"cmax_spec.cm"$ SortId$53,50,"cmax_spec.cm"$ Expr$53,58,"cmax_spec.cm"$ )
Condition$54,1,"cmax_spec.cm"$ ( PatternList$54,21,"cmax_spec.cm"$ Formula$54,34,"cmax_spec.cm"$ Expr$54,43,"cmax_spec.cm"$ )
PatternList$55,1,"cmax_spec.cm"$ * Pattern$55,21,"cmax_spec.cm"$
AttrDecl$56,1,"cmax_spec.cm"$ ( DefId$56,21,"cmax_spec.cm"$ SortIdList$56,28,"cmax_spec.cm"$ SortId$56,40,"cmax_spec.cm"$ )
LatticeDefList$58,1,"cmax_spec.cm"$ * LatticeDef$58,21,"cmax_spec.cm"$
VarDeclList$59,1,"cmax_spec.cm"$ * VarDecl$59,21,"cmax_spec.cm"$
AssertionList$60,1,"cmax_spec.cm"$ * Assertion$60,21,"cmax_spec.cm"$
AssnDefList$61,1,"cmax_spec.cm"$ * AssnDef$61,21,"cmax_spec.cm"$
LatticeDef$62,1,"cmax_spec.cm"$ ( DefId$62,21,"cmax_spec.cm"$ SortId$62,28,"cmax_spec.cm"$ ApplId$62,36,"cmax_spec.cm"$ ApplId$62,44,"cmax_spec.cm"$ ApplId$62,51,"cmax_spec.cm"$ )
VarDecl$63,1,"cmax_spec.cm"$ ( DefId$63,21,"cmax_spec.cm"$ SortIdList$63,28,"cmax_spec.cm"$ NameList$63,40,"cmax_spec.cm"$ SortId$63,50,"cmax_spec.cm"$ Expr$63,58,"cmax_spec.cm"$ LeqOrGeq$64,21,"cmax_spec.cm"$ )
LeqOrGeq$65,1,"cmax_spec.cm"$ = Leq$65,21,"cmax_spec.cm"$|Geq$65,27,"cmax_spec.cm"$
Leq$66,1,"cmax_spec.cm"$ (  )
Geq$66,7,"cmax_spec.cm"$ (  )
Assertion$67,1,"cmax_spec.cm"$ ( AssnList$67,21,"cmax_spec.cm"$ )
Assn$68,1,"cmax_spec.cm"$ = Constraint$68,21,"cmax_spec.cm"$|PatternAssn$68,34,"cmax_spec.cm"$|IfAssn$68,48,"cmax_spec.cm"$|DefAssnAppl$68,57,"cmax_spec.cm"$|LetAssn$69,23,"cmax_spec.cm"$
Constraint$70,1,"cmax_spec.cm"$ = BasicConstr$70,21,"cmax_spec.cm"$|CondConstr$70,35,"cmax_spec.cm"$
BasicConstr$71,1,"cmax_spec.cm"$ = LeqConstr$71,21,"cmax_spec.cm"$|GeqConstr$71,33,"cmax_spec.cm"$
LeqConstr$72,1,"cmax_spec.cm"$ ( Expr$72,21,"cmax_spec.cm"$ VarExpr$72,27,"cmax_spec.cm"$ )
GeqConstr$73,1,"cmax_spec.cm"$ ( Expr$73,21,"cmax_spec.cm"$ VarExpr$73,27,"cmax_spec.cm"$ )
CondConstr$74,1,"cmax_spec.cm"$ ( Formula$74,21,"cmax_spec.cm"$ Constraint$74,30,"cmax_spec.cm"$ )
PatternAssn$75,1,"cmax_spec.cm"$ ( Pattern$75,21,"cmax_spec.cm"$ AssnList$75,30,"cmax_spec.cm"$ )
IfAssn$76,1,"cmax_spec.cm"$ ( Formula$76,21,"cmax_spec.cm"$ AssnList$76,30,"cmax_spec.cm"$ AssnList$76,40,"cmax_spec.cm"$ )
LetAssn$77,1,"cmax_spec.cm"$ ( Name$77,21,"cmax_spec.cm"$ Expr$77,27,"cmax_spec.cm"$ AssnList$77,33,"cmax_spec.cm"$ )
DefAssnAppl$78,1,"cmax_spec.cm"$ ( ApplId$78,21,"cmax_spec.cm"$ ExprList$78,29,"cmax_spec.cm"$ )
AssnDef$79,1,"cmax_spec.cm"$ ( DefId$79,21,"cmax_spec.cm"$ SortIdList$79,28,"cmax_spec.cm"$ NameList$79,40,"cmax_spec.cm"$ AssnList$79,50,"cmax_spec.cm"$ )
AssnList$80,1,"cmax_spec.cm"$ * Assn$80,21,"cmax_spec.cm"$
ExprList$82,1,"cmax_spec.cm"$ * Expr$82,22,"cmax_spec.cm"$
SExprList$83,1,"cmax_spec.cm"$ * Expr$83,22,"cmax_spec.cm"$
Expr$87,1,"cmax_spec.cm"$ = Constant$87,22,"cmax_spec.cm"$|Name$87,34,"cmax_spec.cm"$|FuncAppl$87,43,"cmax_spec.cm"$|ComposedExpr$87,55,"cmax_spec.cm"$|StringExpr$88,22,"cmax_spec.cm"$|DynUndef$88,35,"cmax_spec.cm"$
VarExpr$89,1,"cmax_spec.cm"$ = FuncAppl$89,22,"cmax_spec.cm"$
Constant$91,1,"cmax_spec.cm"$ = CharConst$91,22,"cmax_spec.cm"$|IntConst$91,37,"cmax_spec.cm"$|StringConst$91,51,"cmax_spec.cm"$|SortConst$91,68,"cmax_spec.cm"$
ComposedExpr$92,1,"cmax_spec.cm"$ = IfExpr$92,22,"cmax_spec.cm"$|LetExpr$92,34,"cmax_spec.cm"$
CharConst$93,1,"cmax_spec.cm"$ ( Char$93,22,"cmax_spec.cm"$ Int$93,28,"cmax_spec.cm"$ Int$93,33,"cmax_spec.cm"$ String$93,38,"cmax_spec.cm"$ )
IntConst$94,1,"cmax_spec.cm"$ ( Int$94,22,"cmax_spec.cm"$ Int$94,27,"cmax_spec.cm"$ Int$94,32,"cmax_spec.cm"$ String$94,37,"cmax_spec.cm"$ )
StringConst$95,1,"cmax_spec.cm"$ ( String$95,22,"cmax_spec.cm"$ Int$95,30,"cmax_spec.cm"$ Int$95,35,"cmax_spec.cm"$ String$95,40,"cmax_spec.cm"$ )
SortConst$96,1,"cmax_spec.cm"$ ( SortId$96,22,"cmax_spec.cm"$ )
FuncAppl$97,1,"cmax_spec.cm"$ ( ApplId$97,22,"cmax_spec.cm"$ ExprList$97,30,"cmax_spec.cm"$ )
IfExpr$98,1,"cmax_spec.cm"$ ( CaseList$98,22,"cmax_spec.cm"$ Expr$98,33,"cmax_spec.cm"$ Int$98,39,"cmax_spec.cm"$ Int$98,44,"cmax_spec.cm"$ String$98,49,"cmax_spec.cm"$ )
LetExpr$99,1,"cmax_spec.cm"$ ( Name$99,22,"cmax_spec.cm"$ Expr$99,28,"cmax_spec.cm"$ Expr$99,34,"cmax_spec.cm"$ )
StringExpr$100,1,"cmax_spec.cm"$ ( SExprList$100,22,"cmax_spec.cm"$ Int$100,33,"cmax_spec.cm"$ Int$100,38,"cmax_spec.cm"$ String$100,43,"cmax_spec.cm"$ )
CaseList$101,1,"cmax_spec.cm"$ = PatternCaseList$101,22,"cmax_spec.cm"$|FormulaCaseList$101,42,"cmax_spec.cm"$
PatternCaseList$102,1,"cmax_spec.cm"$ * PatternCase$102,22,"cmax_spec.cm"$
FormulaCaseList$103,1,"cmax_spec.cm"$ * FormulaCase$103,22,"cmax_spec.cm"$
PatternCase$104,1,"cmax_spec.cm"$ ( Pattern$104,22,"cmax_spec.cm"$ Expr$104,31,"cmax_spec.cm"$ )
FormulaCase$105,1,"cmax_spec.cm"$ ( Formula$105,22,"cmax_spec.cm"$ Expr$105,31,"cmax_spec.cm"$ )
Formula$107,1,"cmax_spec.cm"$ = PredAppl$107,22,"cmax_spec.cm"$|Or$107,35,"cmax_spec.cm"$|And$107,42,"cmax_spec.cm"$|Impl$107,50,"cmax_spec.cm"$|Neg$107,59,"cmax_spec.cm"$
PredAppl$108,1,"cmax_spec.cm"$ ( ApplId$108,22,"cmax_spec.cm"$ ExprList$108,30,"cmax_spec.cm"$ )
Or$109,1,"cmax_spec.cm"$ ( Formula$109,22,"cmax_spec.cm"$ Formula$109,32,"cmax_spec.cm"$ )
And$110,1,"cmax_spec.cm"$ ( Formula$110,22,"cmax_spec.cm"$ Formula$110,32,"cmax_spec.cm"$ )
Impl$111,1,"cmax_spec.cm"$ ( Formula$111,22,"cmax_spec.cm"$ Formula$111,32,"cmax_spec.cm"$ )
Neg$112,1,"cmax_spec.cm"$ ( Formula$112,22,"cmax_spec.cm"$ )
Pattern$114,1,"cmax_spec.cm"$ ( SortPos$114,22,"cmax_spec.cm"$ SubPatternPos$114,31,"cmax_spec.cm"$ NamePos$114,46,"cmax_spec.cm"$ )
SortPos$115,1,"cmax_spec.cm"$ = SortId$115,22,"cmax_spec.cm"$|Blank$115,34,"cmax_spec.cm"$
SubPatternPos$116,1,"cmax_spec.cm"$ = ItemList$116,22,"cmax_spec.cm"$|Blank$116,34,"cmax_spec.cm"$
NamePos$117,1,"cmax_spec.cm"$ = Name$117,22,"cmax_spec.cm"$|Blank$117,34,"cmax_spec.cm"$
ItemList$118,1,"cmax_spec.cm"$ * Item$118,22,"cmax_spec.cm"$
Item$119,1,"cmax_spec.cm"$ = Pattern$119,22,"cmax_spec.cm"$|Blank$119,34,"cmax_spec.cm"$|Asterisk$119,44,"cmax_spec.cm"$
DefId$121,1,"cmax_spec.cm"$ ( Ident$121,22,"cmax_spec.cm"$ Int$121,29,"cmax_spec.cm"$ Int$121,34,"cmax_spec.cm"$ String$121,39,"cmax_spec.cm"$ )
UsedId$122,1,"cmax_spec.cm"$ = SortId$122,22,"cmax_spec.cm"$|ApplId$122,37,"cmax_spec.cm"$
SortId$123,1,"cmax_spec.cm"$ = TermSortId$123,22,"cmax_spec.cm"$|NodeSortId$123,37,"cmax_spec.cm"$
TermSortId$124,1,"cmax_spec.cm"$ ( Ident$124,22,"cmax_spec.cm"$ Int$124,29,"cmax_spec.cm"$ Int$124,34,"cmax_spec.cm"$ String$124,39,"cmax_spec.cm"$ )
NodeSortId$125,1,"cmax_spec.cm"$ ( Ident$125,22,"cmax_spec.cm"$ Int$125,29,"cmax_spec.cm"$ Int$125,34,"cmax_spec.cm"$ String$125,39,"cmax_spec.cm"$ )
ApplId$126,1,"cmax_spec.cm"$ ( Ident$126,22,"cmax_spec.cm"$ Int$126,29,"cmax_spec.cm"$ Int$126,34,"cmax_spec.cm"$ String$126,39,"cmax_spec.cm"$ )
Name$127,1,"cmax_spec.cm"$ ( Ident$127,22,"cmax_spec.cm"$ Int$127,29,"cmax_spec.cm"$ Int$127,34,"cmax_spec.cm"$ String$127,39,"cmax_spec.cm"$ )
NameList$128,1,"cmax_spec.cm"$ * Name$128,22,"cmax_spec.cm"$
Blank$129,1,"cmax_spec.cm"$ ( Int$129,22,"cmax_spec.cm"$ )
Asterisk$130,1,"cmax_spec.cm"$ (  )
Declaration$144,1,"cmax_spec.cm"$ = PredDecl$144,22,"cmax_spec.cm"$|FuncDecl$144,37,"cmax_spec.cm"$|AttrDecl$144,51,"cmax_spec.cm"$
Definition$145,1,"cmax_spec.cm"$ = Function$145,22,"cmax_spec.cm"$|Attribute$145,35,"cmax_spec.cm"$|Predicate$145,49,"cmax_spec.cm"$|Production$145,63,"cmax_spec.cm"$|AssnDef$146,21,"cmax_spec.cm"$|LatticeDef$146,33,"cmax_spec.cm"$
DeclNode$147,1,"cmax_spec.cm"$ = Declaration$147,22,"cmax_spec.cm"$|Definition$147,38,"cmax_spec.cm"$
DeclForConstraints$148,1,"cmax_spec.cm"$ = VarDecl$148,22,"cmax_spec.cm"$|LatticeDef$148,32,"cmax_spec.cm"$|Assertion$148,45,"cmax_spec.cm"$|AssnDef$148,57,"cmax_spec.cm"$
DeclList$149,1,"cmax_spec.cm"$ = PredList$149,22,"cmax_spec.cm"$|FuAtList$149,33,"cmax_spec.cm"$|AssnDefList$149,44,"cmax_spec.cm"$|ProdList$149,58,"cmax_spec.cm"$|LatticeDefList$150,22,"cmax_spec.cm"$|VarDeclList$150,39,"cmax_spec.cm"$|RuleList$150,53,"cmax_spec.cm"$|CondList$151,21,"cmax_spec.cm"$|AssertionList$151,33,"cmax_spec.cm"$|Specification$151,49,"cmax_spec.cm"$|LocalDeclList$151,65,"cmax_spec.cm"$
DeclListForConstraints$153,1,"cmax_spec.cm"$ = AssnDefList$153,26,"cmax_spec.cm"$|LatticeDefList$154,10,"cmax_spec.cm"$|VarDeclList$154,27,"cmax_spec.cm"$|AssertionList$154,41,"cmax_spec.cm"$
ProdNodeList$160,1,"cmax_spec.cm"$ * Production$160,16,"cmax_spec.cm"$@
IdentList$161,1,"cmax_spec.cm"$ * Ident$161,16,"cmax_spec.cm"$
CharList$162,1,"cmax_spec.cm"$ * Char$162,16,"cmax_spec.cm"$
Rside$164,1,"cmax_spec.cm"$ = SortId$164,16,"cmax_spec.cm"$|String$164,25,"cmax_spec.cm"$|Parsnr$164,34,"cmax_spec.cm"$|Parsline$164,43,"cmax_spec.cm"$|Parscol$164,54,"cmax_spec.cm"$|Parspos$164,64,"cmax_spec.cm"$
Parsnr$165,1,"cmax_spec.cm"$ ( Int$165,16,"cmax_spec.cm"$ )
Parsline$166,1,"cmax_spec.cm"$ (  )
Parscol$167,1,"cmax_spec.cm"$ (  )
Parspos$168,1,"cmax_spec.cm"$ (  )
RsideInfo$169,1,"cmax_spec.cm"$ * Rside$169,16,"cmax_spec.cm"$
RsideList$170,1,"cmax_spec.cm"$ * RsideInfo$170,16,"cmax_spec.cm"$
Lside$172,1,"cmax_spec.cm"$ = Parsrule$172,16,"cmax_spec.cm"$|Parsaddrule$172,27,"cmax_spec.cm"$|Parsno$172,41,"cmax_spec.cm"$|Parsaux$172,50,"cmax_spec.cm"$|Parsleft$173,16,"cmax_spec.cm"$|Parsright$173,27,"cmax_spec.cm"$|Parsprio$173,39,"cmax_spec.cm"$|Int$173,50,"cmax_spec.cm"$
LsideList$174,1,"cmax_spec.cm"$ * Lside$174,16,"cmax_spec.cm"$
Parsprio$176,1,"cmax_spec.cm"$ (  )
Parsrule$177,1,"cmax_spec.cm"$ ( StringList$177,16,"cmax_spec.cm"$ )
Parsaddrule$178,1,"cmax_spec.cm"$ ( StringList$178,16,"cmax_spec.cm"$ )
Parsno$179,1,"cmax_spec.cm"$ (  )
Parsleft$180,1,"cmax_spec.cm"$ (  )
Parsright$181,1,"cmax_spec.cm"$ (  )
Parsaux$182,1,"cmax_spec.cm"$ (  )
LPinfoListlist$184,1,"cmax_spec.cm"$ * LPinfolist$184,18,"cmax_spec.cm"$
LPinfolist$185,1,"cmax_spec.cm"$ * LPinfo$185,18,"cmax_spec.cm"$
LPinfo$186,1,"cmax_spec.cm"$ = ParsStern$186,18,"cmax_spec.cm"$|ParsPlus$186,30,"cmax_spec.cm"$
ParsStern$187,1,"cmax_spec.cm"$ ( String$187,18,"cmax_spec.cm"$ )
ParsPlus$188,1,"cmax_spec.cm"$ ( String$188,18,"cmax_spec.cm"$ )
IdentTripel$190,1,"cmax_spec.cm"$ ( Ident$190,18,"cmax_spec.cm"$ Ident$190,24,"cmax_spec.cm"$ Ident$190,30,"cmax_spec.cm"$ )
StringList$193,1,"cmax_spec.cm"$ * String$193,18,"cmax_spec.cm"$
CPinfo$194,1,"cmax_spec.cm"$ ( StringList$194,18,"cmax_spec.cm"$ SortId$194,29,"cmax_spec.cm"$ StringList$194,36,"cmax_spec.cm"$ )
CPinfoList$195,1,"cmax_spec.cm"$ * CPinfo$195,18,"cmax_spec.cm"$
CPinfoListlist$196,1,"cmax_spec.cm"$ * CPinfoList$196,18,"cmax_spec.cm"$
ParTup$198,1,"cmax_spec.cm"$ ( SortIdList$198,22,"cmax_spec.cm"$ NameList$198,34,"cmax_spec.cm"$ )
ActivationCode$204,1,"cmax_spec.cm"$ * ActivationCodeElem$204,22,"cmax_spec.cm"$
ActivationCodeElem$205,1,"cmax_spec.cm"$ = AC_Cond$205,22,"cmax_spec.cm"$|AC_For_Sorts$205,32,"cmax_spec.cm"$|AC_For_Rbroths$205,47,"cmax_spec.cm"$|AC_Block$206,24,"cmax_spec.cm"$|AC_Bind$206,35,"cmax_spec.cm"$|AC_Test$206,45,"cmax_spec.cm"$|AC_Stmt$206,55,"cmax_spec.cm"$
AC_Cond$210,1,"cmax_spec.cm"$ ( AC_Expr$210,19,"cmax_spec.cm"$ ActivationCode$210,27,"cmax_spec.cm"$ ActivationCode$210,42,"cmax_spec.cm"$ Int$210,57,"cmax_spec.cm"$ )
AC_For_Sorts$211,1,"cmax_spec.cm"$ ( AC_Ref$211,19,"cmax_spec.cm"$ SortIdList$211,27,"cmax_spec.cm"$ ActivationCode$211,38,"cmax_spec.cm"$ Int$211,53,"cmax_spec.cm"$ )
AC_For_Rbroths$212,1,"cmax_spec.cm"$ ( AC_Ref$212,20,"cmax_spec.cm"$ AC_Expr$212,28,"cmax_spec.cm"$ ActivationCode$212,37,"cmax_spec.cm"$ Int$212,52,"cmax_spec.cm"$ )
AC_Block$213,1,"cmax_spec.cm"$ ( Set$213,19,"cmax_spec.cm"$ ActivationCode$213,23,"cmax_spec.cm"$ Int$213,38,"cmax_spec.cm"$ )
AC_Bind$214,1,"cmax_spec.cm"$ ( AC_Ref$214,19,"cmax_spec.cm"$ AC_Expr$214,27,"cmax_spec.cm"$ )
AC_Test$215,1,"cmax_spec.cm"$ ( AC_Expr$215,19,"cmax_spec.cm"$ )
AC_Stmt$217,1,"cmax_spec.cm"$ ( String$217,19,"cmax_spec.cm"$ )
AC_Ref$218,1,"cmax_spec.cm"$ ( String$218,19,"cmax_spec.cm"$ )
AC_Expr$219,1,"cmax_spec.cm"$ ( String$219,19,"cmax_spec.cm"$ )
DynFunc$225,1,"cmax_spec.cm"$ ( DefId$225,19,"cmax_spec.cm"$ SortIdList$225,26,"cmax_spec.cm"$ NameList$225,38,"cmax_spec.cm"$ SortId$225,48,"cmax_spec.cm"$ Expr$225,56,"cmax_spec.cm"$ )
RuleList$227,1,"cmax_spec.cm"$ * Rule$227,19,"cmax_spec.cm"$
Rule$228,1,"cmax_spec.cm"$ = IfRule$228,19,"cmax_spec.cm"$|CaseRule$228,28,"cmax_spec.cm"$
IfRule$229,1,"cmax_spec.cm"$ ( Formula$229,19,"cmax_spec.cm"$ UpdateList$229,28,"cmax_spec.cm"$ UpdateList$229,40,"cmax_spec.cm"$ )
CaseRule$231,1,"cmax_spec.cm"$ ( Expr$231,19,"cmax_spec.cm"$ CaseIsList$231,25,"cmax_spec.cm"$ UpdateList$231,37,"cmax_spec.cm"$ )
CaseIsList$232,1,"cmax_spec.cm"$ * CaseIs$232,19,"cmax_spec.cm"$
CaseIs$233,1,"cmax_spec.cm"$ ( CaseConst$233,19,"cmax_spec.cm"$ UpdateList$233,29,"cmax_spec.cm"$ )
CaseConst$234,1,"cmax_spec.cm"$ = CharConst$234,19,"cmax_spec.cm"$|IntConst$234,31,"cmax_spec.cm"$|SortConst$234,42,"cmax_spec.cm"$
UpdateList$236,1,"cmax_spec.cm"$ * UpdateOrRule$236,19,"cmax_spec.cm"$
UpdateOrRule$237,1,"cmax_spec.cm"$ = Update$237,19,"cmax_spec.cm"$|Rule$237,30,"cmax_spec.cm"$
Update$238,1,"cmax_spec.cm"$ ( FuncAppl$238,19,"cmax_spec.cm"$ Expr$238,29,"cmax_spec.cm"$ )
UListNodeList$240,1,"cmax_spec.cm"$ * UpdateList$240,19,"cmax_spec.cm"$@
DynUndef$242,1,"cmax_spec.cm"$ (  )
DynSemInput$243,1,"cmax_spec.cm"$ ( DefId$243,19,"cmax_spec.cm"$ SortIdList$243,26,"cmax_spec.cm"$ SortId$243,38,"cmax_spec.cm"$ )
FctOrAtt$249,1,"cmax_spec.cm"$ = Function$249,13,"cmax_spec.cm"$|Attribute$249,24,"cmax_spec.cm"$
NodeList$251,1,"cmax_spec.cm"$ * Node$251,18,"cmax_spec.cm"$
Set$253,1,"cmax_spec.cm"$ * Element$253,18,"cmax_spec.cm"$
FCT out$266,5,"cmax_spec.cm"$(String$266,10,"cmax_spec.cm"$) Bool$266,18,"cmax_spec.cm"$
FCT openFile$268,5,"cmax_spec.cm"$(String$268,15,"cmax_spec.cm"$, String$268,23,"cmax_spec.cm"$) Int$268,31,"cmax_spec.cm"$
FCT writeToFile$271,5,"cmax_spec.cm"$(Int$271,18,"cmax_spec.cm"$, String$271,23,"cmax_spec.cm"$) Bool$271,31,"cmax_spec.cm"$
FCT closeFile$274,5,"cmax_spec.cm"$(Int$274,16,"cmax_spec.cm"$) Bool$274,21,"cmax_spec.cm"$
FCT inputFilePath$276,5,"cmax_spec.cm"$() String$276,22,"cmax_spec.cm"$
FCT inputFileName$280,5,"cmax_spec.cm"$() String$280,22,"cmax_spec.cm"$
FCT error$286,5,"cmax_spec.cm"$() Bool$286,13,"cmax_spec.cm"$
FCT nrOfErrors$287,5,"cmax_spec.cm"$() Int$287,18,"cmax_spec.cm"$
FCT checkOption$293,5,"cmax_spec.cm"$(String$293,18,"cmax_spec.cm"$) Bool$293,26,"cmax_spec.cm"$
FCT getOption$294,5,"cmax_spec.cm"$(String$294,16,"cmax_spec.cm"$) Bool$294,24,"cmax_spec.cm"$
FCT startTimer$301,5,"cmax_spec.cm"$() Bool$301,19,"cmax_spec.cm"$
FCT readTimer$302,5,"cmax_spec.cm"$() Int$302,18,"cmax_spec.cm"$
FCT itos$308,5,"cmax_spec.cm"$(Int$308,11,"cmax_spec.cm"$) String$308,16,"cmax_spec.cm"$
FCT succ$309,5,"cmax_spec.cm"$(Int$309,11,"cmax_spec.cm"$) Int$309,16,"cmax_spec.cm"$
FCT prev$310,5,"cmax_spec.cm"$(Int$310,11,"cmax_spec.cm"$) Int$310,16,"cmax_spec.cm"$
FCT max$311,5,"cmax_spec.cm"$(Int$311,10,"cmax_spec.cm"$, Int$311,15,"cmax_spec.cm"$) Int$311,20,"cmax_spec.cm"$
FCT add$312,5,"cmax_spec.cm"$(Int$312,10,"cmax_spec.cm"$, Int$312,15,"cmax_spec.cm"$) Int$312,20,"cmax_spec.cm"$
FCT sub$313,5,"cmax_spec.cm"$(Int$313,10,"cmax_spec.cm"$, Int$313,15,"cmax_spec.cm"$) Int$313,20,"cmax_spec.cm"$
FCT mult$314,5,"cmax_spec.cm"$(Int$314,11,"cmax_spec.cm"$, Int$314,16,"cmax_spec.cm"$) Int$314,21,"cmax_spec.cm"$
FCT divide$315,5,"cmax_spec.cm"$(Int$315,13,"cmax_spec.cm"$, Int$315,18,"cmax_spec.cm"$) Int$315,23,"cmax_spec.cm"$
FCT greater$316,5,"cmax_spec.cm"$(Int$316,14,"cmax_spec.cm"$, Int$316,19,"cmax_spec.cm"$) Bool$316,24,"cmax_spec.cm"$
FCT greatereq$317,5,"cmax_spec.cm"$(Int$317,16,"cmax_spec.cm"$, Int$317,21,"cmax_spec.cm"$) Bool$317,26,"cmax_spec.cm"$
FCT less$318,5,"cmax_spec.cm"$(Int$318,11,"cmax_spec.cm"$, Int$318,16,"cmax_spec.cm"$) Bool$318,21,"cmax_spec.cm"$
FCT lesseq$319,5,"cmax_spec.cm"$(Int$319,13,"cmax_spec.cm"$, Int$319,18,"cmax_spec.cm"$) Bool$319,23,"cmax_spec.cm"$
FCT ctos$323,5,"cmax_spec.cm"$(Char$323,11,"cmax_spec.cm"$) String$323,17,"cmax_spec.cm"$
FCT strtoid$325,5,"cmax_spec.cm"$(String$325,14,"cmax_spec.cm"$) Ident$325,22,"cmax_spec.cm"$
FCT sortof$326,5,"cmax_spec.cm"$(Element$326,13,"cmax_spec.cm"$) String$326,22,"cmax_spec.cm"$
FCT collect_occurences$328,5,"cmax_spec.cm"$(Node$328,24,"cmax_spec.cm"$, Element$328,30,"cmax_spec.cm"$) NodeList$328,47,"cmax_spec.cm"$
FCT get_var_value__(Element) Element
FCT init_var__(Element) Element
FCT activate_constrs__() Element
FCT solve__() Element
FCT sync__(Element, Element) Element
STRUC cmax$335,7,"cmax_spec.cm"$[Specification$335,14,"cmax_spec.cm"$] {
ATT Decl_sync__( Node N) Element:
  LET H1==IF <*,N1> N: Decl_sync__(N1)
          ELSE true():
  LET H2==IF <*,N1,N,*>: Decl_sync__(N1)
          ELSE true():
  LET H3==IF is[N, _UsedId$507,11,"cmax_spec.cm"$@]: Decl(N)
          ELSE true():
  sync__( sync__( H1, H2 ), H3 )
ATT used_attributes_PTR__$0,0,"?"$ ( Node$659,26,"cmax_spec.cm"$ N$659,31,"cmax_spec.cm"$ ) Element$0,0,"?"$ :
    init_var__$0,0,"?"$(Set$659,42,"cmax_spec.cm"$())
ATT used_attributes_PTR___sync__( Node N) Element:
  LET H1==IF <*,N1> N: used_attributes_PTR___sync__(N1)
          ELSE true():
  LET H2==IF <*,N1,N,*>: used_attributes_PTR___sync__(N1)
          ELSE true():
  LET H3==IF is[N, _Node$659,26,"cmax_spec.cm"$]: used_attributes_PTR__(N)
          ELSE true():
  sync__( sync__( H1, H2 ), H3 )
ATT used_attributes(Node$659,26,"cmax_spec.cm"$ N) Set:
  LET H==CSSYNC__(N):
  get_var_value__(used_attributes_PTR__(N))
ATT attrs_used_in_assns_PTR__$0,0,"?"$ ( Structure$715,29,"cmax_spec.cm"$@ S$715,40,"cmax_spec.cm"$ ) Element$0,0,"?"$ :
    init_var__$0,0,"?"$(Set$715,49,"cmax_spec.cm"$())
ATT attrs_used_in_assns_PTR___sync__( Node N) Element:
  LET H1==IF <*,N1> N: attrs_used_in_assns_PTR___sync__(N1)
          ELSE true():
  LET H2==IF <*,N1,N,*>: attrs_used_in_assns_PTR___sync__(N1)
          ELSE true():
  LET H3==IF is[N, _Structure$715,29,"cmax_spec.cm"$@]: attrs_used_in_assns_PTR__(N)
          ELSE true():
  sync__( sync__( H1, H2 ), H3 )
ATT attrs_used_in_assns(Structure$715,29,"cmax_spec.cm"$@ N) Set:
  LET H==CSSYNC__(N):
  get_var_value__(attrs_used_in_assns_PTR__(N))
ATT CSSYNC__( Node N) Element:
  IF N=root():
    LET H==sync_all__(N):
    LET H==activate_constrs__():
    solve__()
  ELSE CSSYNC__( fath (N) )
ATT sync_all__(Specification@ N) Bool:
  LET H==true():
  LET H==sync__(H, Decl_sync__(N)):
  LET H==sync__(H, used_attributes_PTR___sync__(N)):
  LET H==sync__(H, attrs_used_in_assns_PTR___sync__(N)):
  H
FCT SILfromCPIL$345,5,"cmax_spec.cm"$ ( CPinfoList$345,18,"cmax_spec.cm"$ CPIL$345,29,"cmax_spec.cm"$ ) SortIdList$345,35,"cmax_spec.cm"$ :
    IF$346,5,"cmax_spec.cm"$ eq$0,0,"?"$[0$346,6,"cmax_spec.cm"$, numsubterms$346,13,"cmax_spec.cm"$(CPIL$346,8,"cmax_spec.cm"$)]:
        SortIdList$347,5,"cmax_spec.cm"$()
    ELSE
        appfront$349,5,"cmax_spec.cm"$(subterm$349,14,"cmax_spec.cm"$(2$349,22,"cmax_spec.cm"$, subterm$349,25,"cmax_spec.cm"$(1$349,33,"cmax_spec.cm"$, CPIL$349,36,"cmax_spec.cm"$)), SILfromCPIL$349,44,"cmax_spec.cm"$(back$349,61,"cmax_spec.cm"$(CPIL$349,56,"cmax_spec.cm"$)))
FCT SILfromRSI$351,5,"cmax_spec.cm"$ ( RsideInfo$351,17,"cmax_spec.cm"$ RI$351,27,"cmax_spec.cm"$ ) SortIdList$351,31,"cmax_spec.cm"$ :
    IF$352,5,"cmax_spec.cm"$ eq$0,0,"?"$[0$352,6,"cmax_spec.cm"$, numsubterms$352,11,"cmax_spec.cm"$(RI$352,8,"cmax_spec.cm"$)]:
        SortIdList$353,5,"cmax_spec.cm"$()
    ELSE
        LET REST$355,9,"cmax_spec.cm"$ ==
            SILfromRSI$355,17,"cmax_spec.cm"$(back$355,32,"cmax_spec.cm"$(RI$355,29,"cmax_spec.cm"$))
        :
            IF$356,7,"cmax_spec.cm"$ is$356,8,"cmax_spec.cm"$[subterm$356,11,"cmax_spec.cm"$(1$356,19,"cmax_spec.cm"$, RI$356,22,"cmax_spec.cm"$), _SortId$356,27,"cmax_spec.cm"$]:
                appfront$357,7,"cmax_spec.cm"$(subterm$357,16,"cmax_spec.cm"$(1$357,24,"cmax_spec.cm"$, RI$357,27,"cmax_spec.cm"$), REST$357,32,"cmax_spec.cm"$)
            ELSE
                REST$359,7,"cmax_spec.cm"$

FCT idtos1$363,5,"cmax_spec.cm"$ ( Ident$363,13,"cmax_spec.cm"$ I$363,19,"cmax_spec.cm"$ ) String$363,22,"cmax_spec.cm"$ :
    idtos$363,30,"cmax_spec.cm"$(I$363,36,"cmax_spec.cm"$)
FCT lineOfId$365,5,"cmax_spec.cm"$ ( Node$365,15,"cmax_spec.cm"$ N$365,20,"cmax_spec.cm"$ ) Int$365,23,"cmax_spec.cm"$ :
    term$365,38,"cmax_spec.cm"$(son$365,28,"cmax_spec.cm"$(2$365,32,"cmax_spec.cm"$, N$365,35,"cmax_spec.cm"$))
FCT fileOfId$366,5,"cmax_spec.cm"$ ( Node$366,15,"cmax_spec.cm"$ N$366,20,"cmax_spec.cm"$ ) Int$366,23,"cmax_spec.cm"$ :
    term$366,38,"cmax_spec.cm"$(son$366,28,"cmax_spec.cm"$(4$366,32,"cmax_spec.cm"$, N$366,35,"cmax_spec.cm"$))
FCT fst$368,5,"cmax_spec.cm"$ ( Node$368,9,"cmax_spec.cm"$ N$368,14,"cmax_spec.cm"$ ) Node$368,17,"cmax_spec.cm"$ :
    son$368,23,"cmax_spec.cm"$(1$368,27,"cmax_spec.cm"$, N$368,30,"cmax_spec.cm"$)
FCT snd$369,5,"cmax_spec.cm"$ ( Node$369,9,"cmax_spec.cm"$ N$369,14,"cmax_spec.cm"$ ) Node$369,17,"cmax_spec.cm"$ :
    son$369,23,"cmax_spec.cm"$(2$369,27,"cmax_spec.cm"$, N$369,30,"cmax_spec.cm"$)
FCT thd$370,5,"cmax_spec.cm"$ ( Node$370,9,"cmax_spec.cm"$ N$370,14,"cmax_spec.cm"$ ) Node$370,17,"cmax_spec.cm"$ :
    son$370,23,"cmax_spec.cm"$(3$370,27,"cmax_spec.cm"$, N$370,30,"cmax_spec.cm"$)
FCT last$371,5,"cmax_spec.cm"$ ( Node$371,10,"cmax_spec.cm"$ N$371,15,"cmax_spec.cm"$ ) Node$371,18,"cmax_spec.cm"$ :
    son$371,24,"cmax_spec.cm"$(-1$371,28,"cmax_spec.cm"$, N$371,32,"cmax_spec.cm"$)
FCT idToStr$373,5,"cmax_spec.cm"$ ( Node$373,14,"cmax_spec.cm"$ N$373,19,"cmax_spec.cm"$ ) String$373,22,"cmax_spec.cm"$ :
    idtos$373,41,"cmax_spec.cm"$(term$373,36,"cmax_spec.cm"$(fst$373,32,"cmax_spec.cm"$(N$373,30,"cmax_spec.cm"$)))
FCT debug$381,5,"cmax_spec.cm"$ ( String$381,12,"cmax_spec.cm"$ S$381,19,"cmax_spec.cm"$ ) Bool$381,22,"cmax_spec.cm"$ :
    IF$382,5,"cmax_spec.cm"$ eq$0,0,"?"$[checkOption$382,6,"cmax_spec.cm"$("debug"$382,18,"cmax_spec.cm"$), true$382,27,"cmax_spec.cm"$()]:
        out$383,5,"cmax_spec.cm"$(S$383,9,"cmax_spec.cm"$)
    ELSE
        true$385,5,"cmax_spec.cm"$()
FCT info$387,5,"cmax_spec.cm"$ ( String$387,12,"cmax_spec.cm"$ S$387,19,"cmax_spec.cm"$ ) Bool$387,23,"cmax_spec.cm"$ :
    IF$388,5,"cmax_spec.cm"$ eq$0,0,"?"$[checkOption$388,6,"cmax_spec.cm"$("silent"$388,18,"cmax_spec.cm"$), true$388,28,"cmax_spec.cm"$()]:
        true$389,5,"cmax_spec.cm"$()
    ELSE
        out$391,5,"cmax_spec.cm"$(S$391,9,"cmax_spec.cm"$)
FCT lookup_node_in_list$393,5,"cmax_spec.cm"$ ( Node$393,25,"cmax_spec.cm"$ N$393,30,"cmax_spec.cm"$, NodeList$393,33,"cmax_spec.cm"$ NL$393,42,"cmax_spec.cm"$ ) Int$393,46,"cmax_spec.cm"$ :
    IF$394,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$394,9,"cmax_spec.cm"$(NL$394,6,"cmax_spec.cm"$), 0$394,21,"cmax_spec.cm"$]:
        0$394,24,"cmax_spec.cm"$
    ELSE
        IF$396,7,"cmax_spec.cm"$ eq$0,0,"?"$[N$396,8,"cmax_spec.cm"$, subterm$396,10,"cmax_spec.cm"$(1$396,18,"cmax_spec.cm"$, NL$396,21,"cmax_spec.cm"$)]:
            1$396,26,"cmax_spec.cm"$
        ELSE
            succ$397,10,"cmax_spec.cm"$(lookup_node_in_list$397,17,"cmax_spec.cm"$(N$397,37,"cmax_spec.cm"$, back$397,43,"cmax_spec.cm"$(NL$397,40,"cmax_spec.cm"$)))
FCT iselem$401,5,"cmax_spec.cm"$ ( Element$401,12,"cmax_spec.cm"$ E$401,20,"cmax_spec.cm"$, Set$401,23,"cmax_spec.cm"$ S$401,27,"cmax_spec.cm"$ ) Bool$401,30,"cmax_spec.cm"$ :
    IF$402,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$402,6,"cmax_spec.cm"$(S$402,18,"cmax_spec.cm"$), 0$402,21,"cmax_spec.cm"$]:
        false$402,24,"cmax_spec.cm"$()
    ELSE
        IF$404,7,"cmax_spec.cm"$ eq$0,0,"?"$[subterm$404,8,"cmax_spec.cm"$(1$404,16,"cmax_spec.cm"$, S$404,19,"cmax_spec.cm"$), E$404,22,"cmax_spec.cm"$]:
            true$404,25,"cmax_spec.cm"$()
        ELSE
            iselem$405,10,"cmax_spec.cm"$(E$405,17,"cmax_spec.cm"$, back$405,22,"cmax_spec.cm"$(S$405,20,"cmax_spec.cm"$))
FCT union$409,5,"cmax_spec.cm"$ ( Set$409,11,"cmax_spec.cm"$ S1$409,15,"cmax_spec.cm"$, Set$409,19,"cmax_spec.cm"$ S2$409,23,"cmax_spec.cm"$ ) Set$409,27,"cmax_spec.cm"$ :
    IF$410,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$410,9,"cmax_spec.cm"$(S1$410,6,"cmax_spec.cm"$), 0$410,21,"cmax_spec.cm"$]:
        S2$410,24,"cmax_spec.cm"$
    ELSE
        LET E$412,9,"cmax_spec.cm"$ ==
            subterm$412,12,"cmax_spec.cm"$(1$412,20,"cmax_spec.cm"$, S1$412,23,"cmax_spec.cm"$)
        :
            LET H$413,9,"cmax_spec.cm"$ ==
                union$413,12,"cmax_spec.cm"$(back$413,21,"cmax_spec.cm"$(S1$413,18,"cmax_spec.cm"$), S2$413,27,"cmax_spec.cm"$)
            :
                IF$414,7,"cmax_spec.cm"$ eq$0,0,"?"$[iselem$414,8,"cmax_spec.cm"$(E$414,15,"cmax_spec.cm"$, S2$414,18,"cmax_spec.cm"$), true$414,22,"cmax_spec.cm"$()]:
                    H$414,30,"cmax_spec.cm"$
                ELSE
                    appfront$415,10,"cmax_spec.cm"$(E$415,19,"cmax_spec.cm"$, H$415,22,"cmax_spec.cm"$)


FCT intersection$417,5,"cmax_spec.cm"$ ( Set$417,18,"cmax_spec.cm"$ S1$417,22,"cmax_spec.cm"$, Set$417,26,"cmax_spec.cm"$ S2$417,30,"cmax_spec.cm"$ ) Set$417,34,"cmax_spec.cm"$ :
    IF$418,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$418,9,"cmax_spec.cm"$(S1$418,6,"cmax_spec.cm"$), 0$418,21,"cmax_spec.cm"$]:
        S2$418,24,"cmax_spec.cm"$
    ELSE
        LET E$420,9,"cmax_spec.cm"$ ==
            subterm$420,12,"cmax_spec.cm"$(1$420,20,"cmax_spec.cm"$, S1$420,23,"cmax_spec.cm"$)
        :
            LET H$421,9,"cmax_spec.cm"$ ==
                intersection$421,12,"cmax_spec.cm"$(back$421,28,"cmax_spec.cm"$(S1$421,25,"cmax_spec.cm"$), S2$421,34,"cmax_spec.cm"$)
            :
                IF$422,7,"cmax_spec.cm"$ eq$0,0,"?"$[iselem$422,8,"cmax_spec.cm"$(E$422,15,"cmax_spec.cm"$, S2$422,18,"cmax_spec.cm"$), false$422,22,"cmax_spec.cm"$()]:
                    H$422,31,"cmax_spec.cm"$
                ELSE
                    appfront$423,10,"cmax_spec.cm"$(E$423,19,"cmax_spec.cm"$, H$423,22,"cmax_spec.cm"$)


FCT setminus$425,5,"cmax_spec.cm"$ ( Set$425,14,"cmax_spec.cm"$ S1$425,18,"cmax_spec.cm"$, Set$425,22,"cmax_spec.cm"$ S2$425,26,"cmax_spec.cm"$ ) Set$425,30,"cmax_spec.cm"$ :
    IF$426,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$426,9,"cmax_spec.cm"$(S1$426,6,"cmax_spec.cm"$), 0$426,21,"cmax_spec.cm"$]:
        S1$426,24,"cmax_spec.cm"$
    ELSE
        LET REST$428,9,"cmax_spec.cm"$ ==
            setminus$428,15,"cmax_spec.cm"$(back$428,27,"cmax_spec.cm"$(S1$428,24,"cmax_spec.cm"$), S2$428,33,"cmax_spec.cm"$)
        :
            LET FST$429,9,"cmax_spec.cm"$ ==
                subterm$429,14,"cmax_spec.cm"$(1$429,22,"cmax_spec.cm"$, S1$429,25,"cmax_spec.cm"$)
            :
                IF$430,7,"cmax_spec.cm"$ eq$0,0,"?"$[iselem$430,8,"cmax_spec.cm"$(FST$430,15,"cmax_spec.cm"$, S2$430,20,"cmax_spec.cm"$), true$430,24,"cmax_spec.cm"$()]:
                    REST$431,7,"cmax_spec.cm"$
                ELSE
                    appfront$433,7,"cmax_spec.cm"$(FST$433,16,"cmax_spec.cm"$, REST$433,21,"cmax_spec.cm"$)


FCT issubset$435,5,"cmax_spec.cm"$ ( Set$435,14,"cmax_spec.cm"$ S1$435,18,"cmax_spec.cm"$, Set$435,22,"cmax_spec.cm"$ S2$435,26,"cmax_spec.cm"$ ) Bool$435,30,"cmax_spec.cm"$ :
    IF$436,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$436,9,"cmax_spec.cm"$(S1$436,6,"cmax_spec.cm"$), 0$436,21,"cmax_spec.cm"$]:
        true$436,24,"cmax_spec.cm"$()
    ELSE
        LET E$438,9,"cmax_spec.cm"$ ==
            subterm$438,12,"cmax_spec.cm"$(1$438,20,"cmax_spec.cm"$, S1$438,23,"cmax_spec.cm"$)
        :
            IF$439,7,"cmax_spec.cm"$ eq$0,0,"?"$[iselem$439,8,"cmax_spec.cm"$(E$439,15,"cmax_spec.cm"$, S2$439,18,"cmax_spec.cm"$), false$439,22,"cmax_spec.cm"$()]:
                false$439,31,"cmax_spec.cm"$()
            ELSE
                issubset$440,10,"cmax_spec.cm"$(back$440,22,"cmax_spec.cm"$(S1$440,19,"cmax_spec.cm"$), S2$440,28,"cmax_spec.cm"$)

ATT enclDecl$448,5,"cmax_spec.cm"$ ( Node$448,15,"cmax_spec.cm"$ N$448,20,"cmax_spec.cm"$ ) LocalDecl$448,23,"cmax_spec.cm"$@ :
    IF$449,5,"cmax_spec.cm"$ LocalDecl$449,6,"cmax_spec.cm"$@ N$449,17,"cmax_spec.cm"$:
        N$449,20,"cmax_spec.cm"$
    ELSE
        enclDecl$450,15,"cmax_spec.cm"$(fath$450,10,"cmax_spec.cm"$(N$450,8,"cmax_spec.cm"$))
ATT enclStructure$452,5,"cmax_spec.cm"$ ( Node$452,20,"cmax_spec.cm"$ N$452,25,"cmax_spec.cm"$ ) Structure$452,28,"cmax_spec.cm"$@ :
    IF$453,5,"cmax_spec.cm"$ Structure$453,6,"cmax_spec.cm"$@ N$453,17,"cmax_spec.cm"$:
        N$453,20,"cmax_spec.cm"$
    ELSE
        enclStructure$454,15,"cmax_spec.cm"$(fath$454,10,"cmax_spec.cm"$(N$454,8,"cmax_spec.cm"$))
ATT enclAssn$456,5,"cmax_spec.cm"$ ( Node$456,15,"cmax_spec.cm"$ N$456,20,"cmax_spec.cm"$ ) Assn$456,23,"cmax_spec.cm"$@ :
    IF$457,5,"cmax_spec.cm"$ Assn$457,6,"cmax_spec.cm"$@ N$457,12,"cmax_spec.cm"$:
        N$457,15,"cmax_spec.cm"$
    ELSE
        enclAssn$458,15,"cmax_spec.cm"$(fath$458,10,"cmax_spec.cm"$(N$458,8,"cmax_spec.cm"$))
ATT enclAssertionOrAssnDef$460,5,"cmax_spec.cm"$ ( Node$460,29,"cmax_spec.cm"$ N$460,34,"cmax_spec.cm"$ ) Node$460,37,"cmax_spec.cm"$ :
    IF$461,5,"cmax_spec.cm"$ Assertion$461,6,"cmax_spec.cm"$@ N$461,17,"cmax_spec.cm"$:
        N$461,20,"cmax_spec.cm"$
    | AssnDef$462,6,"cmax_spec.cm"$@ N$462,17,"cmax_spec.cm"$ :
        N$462,20,"cmax_spec.cm"$
    ELSE
        enclAssertionOrAssnDef$463,15,"cmax_spec.cm"$(fath$463,10,"cmax_spec.cm"$(N$463,8,"cmax_spec.cm"$))
ATT enclAssnList$465,5,"cmax_spec.cm"$ ( Node$465,19,"cmax_spec.cm"$ N$465,24,"cmax_spec.cm"$ ) AssnList$465,27,"cmax_spec.cm"$@ :
    IF$466,5,"cmax_spec.cm"$ AssnList$466,6,"cmax_spec.cm"$@ N$466,16,"cmax_spec.cm"$:
        N$466,19,"cmax_spec.cm"$
    ELSE
        enclAssnList$467,15,"cmax_spec.cm"$(fath$467,10,"cmax_spec.cm"$(N$467,8,"cmax_spec.cm"$))
ATT enclPattern$469,5,"cmax_spec.cm"$ ( Node$469,18,"cmax_spec.cm"$ N$469,23,"cmax_spec.cm"$ ) Pattern$469,26,"cmax_spec.cm"$@ :
    IF$470,5,"cmax_spec.cm"$ Pattern$470,6,"cmax_spec.cm"$@ N$470,15,"cmax_spec.cm"$:
        N$470,18,"cmax_spec.cm"$
    ELSE
        enclPattern$471,15,"cmax_spec.cm"$(fath$471,10,"cmax_spec.cm"$(N$471,8,"cmax_spec.cm"$))
FCT is_leq_var$477,5,"cmax_spec.cm"$ ( VarDecl$477,17,"cmax_spec.cm"$@ VD$477,26,"cmax_spec.cm"$ ) Bool$477,30,"cmax_spec.cm"$ :
    IF$477,38,"cmax_spec.cm"$ is$477,39,"cmax_spec.cm"$[last$477,45,"cmax_spec.cm"$(VD$477,42,"cmax_spec.cm"$), _Leq$477,51,"cmax_spec.cm"$@]:
        true$477,59,"cmax_spec.cm"$()
    ELSE
        false$477,71,"cmax_spec.cm"$()
FCT is_geq_var$478,5,"cmax_spec.cm"$ ( VarDecl$478,17,"cmax_spec.cm"$@ VD$478,26,"cmax_spec.cm"$ ) Bool$478,30,"cmax_spec.cm"$ :
    IF$478,38,"cmax_spec.cm"$ is$478,39,"cmax_spec.cm"$[last$478,45,"cmax_spec.cm"$(VD$478,42,"cmax_spec.cm"$), _Geq$478,51,"cmax_spec.cm"$@]:
        true$478,59,"cmax_spec.cm"$()
    ELSE
        false$478,71,"cmax_spec.cm"$()
FCT lattice_sort$487,5,"cmax_spec.cm"$ ( LatticeDef$487,19,"cmax_spec.cm"$@ LD$487,31,"cmax_spec.cm"$ ) Ident$487,35,"cmax_spec.cm"$ :
    term$488,18,"cmax_spec.cm"$(fst$488,14,"cmax_spec.cm"$(son$488,3,"cmax_spec.cm"$(2$488,7,"cmax_spec.cm"$, LD$488,10,"cmax_spec.cm"$)))
FCT lattice_meet$490,5,"cmax_spec.cm"$ ( LatticeDef$490,19,"cmax_spec.cm"$@ LD$490,31,"cmax_spec.cm"$ ) Ident$490,35,"cmax_spec.cm"$ :
    term$491,18,"cmax_spec.cm"$(fst$491,14,"cmax_spec.cm"$(son$491,3,"cmax_spec.cm"$(3$491,7,"cmax_spec.cm"$, LD$491,10,"cmax_spec.cm"$)))
FCT lattice_join$493,5,"cmax_spec.cm"$ ( LatticeDef$493,19,"cmax_spec.cm"$@ LD$493,31,"cmax_spec.cm"$ ) Ident$493,35,"cmax_spec.cm"$ :
    term$494,18,"cmax_spec.cm"$(fst$494,14,"cmax_spec.cm"$(son$494,3,"cmax_spec.cm"$(4$494,7,"cmax_spec.cm"$, LD$494,10,"cmax_spec.cm"$)))
FCT lattice_leq$496,5,"cmax_spec.cm"$ ( LatticeDef$496,18,"cmax_spec.cm"$@ LD$496,30,"cmax_spec.cm"$ ) Ident$496,34,"cmax_spec.cm"$ :
    term$497,18,"cmax_spec.cm"$(fst$497,14,"cmax_spec.cm"$(son$497,3,"cmax_spec.cm"$(5$497,7,"cmax_spec.cm"$, LD$497,10,"cmax_spec.cm"$)))
FCT lattice_leq_update$499,5,"cmax_spec.cm"$ ( LatticeDef$499,25,"cmax_spec.cm"$@ LD$499,37,"cmax_spec.cm"$ ) Ident$499,41,"cmax_spec.cm"$ :
    nil$499,48,"cmax_spec.cm"$()
FCT lattice_geq_update$501,5,"cmax_spec.cm"$ ( LatticeDef$501,25,"cmax_spec.cm"$@ LD$501,37,"cmax_spec.cm"$ ) Ident$501,41,"cmax_spec.cm"$ :
    nil$501,48,"cmax_spec.cm"$()
ATT Decl$507,5,"cmax_spec.cm"$ ( UsedId$507,11,"cmax_spec.cm"$@ I$507,19,"cmax_spec.cm"$ ) DeclNode$507,22,"cmax_spec.cm"$@ :
    IF$508,5,"cmax_spec.cm"$ ApplId$508,6,"cmax_spec.cm"$@ I$508,14,"cmax_spec.cm"$:
        LET H$509,9,"cmax_spec.cm"$ ==
            lookup$509,13,"cmax_spec.cm"$(I$509,21,"cmax_spec.cm"$, fst$509,45,"cmax_spec.cm"$(thd$509,41,"cmax_spec.cm"$(enclStructure$509,27,"cmax_spec.cm"$(I$509,25,"cmax_spec.cm"$))))
        :
            IF$510,7,"cmax_spec.cm"$ ! eq$0,0,"?"$[H$510,8,"cmax_spec.cm"$, nil$510,10,"cmax_spec.cm"$()]:
                H$510,17,"cmax_spec.cm"$
            ELSE
                lookup$511,10,"cmax_spec.cm"$(I$511,18,"cmax_spec.cm"$, fst$511,29,"cmax_spec.cm"$(root$511,22,"cmax_spec.cm"$()))

    ELSE
        LET H$513,9,"cmax_spec.cm"$ ==
            lookup$513,12,"cmax_spec.cm"$(I$513,21,"cmax_spec.cm"$, fst$513,31,"cmax_spec.cm"$(root$513,24,"cmax_spec.cm"$()))
        :
            IF$514,7,"cmax_spec.cm"$ ! eq$0,0,"?"$[H$514,8,"cmax_spec.cm"$, nil$514,10,"cmax_spec.cm"$()]:
                H$514,17,"cmax_spec.cm"$
            ELSE
                lookup$516,7,"cmax_spec.cm"$(I$516,14,"cmax_spec.cm"$, fst$516,37,"cmax_spec.cm"$(thd$516,33,"cmax_spec.cm"$(enclStructure$516,19,"cmax_spec.cm"$(I$516,17,"cmax_spec.cm"$))))

FCT lookup$518,5,"cmax_spec.cm"$ ( UsedId$518,13,"cmax_spec.cm"$@ I$518,21,"cmax_spec.cm"$, Node$518,24,"cmax_spec.cm"$ LD$518,29,"cmax_spec.cm"$ ) DeclNode$518,33,"cmax_spec.cm"$@ :
    IF$525,5,"cmax_spec.cm"$ is$525,6,"cmax_spec.cm"$[LD$525,9,"cmax_spec.cm"$, _DeclList$525,13,"cmax_spec.cm"$@]:
        LET H$526,9,"cmax_spec.cm"$ ==
            lookup$526,14,"cmax_spec.cm"$(I$526,23,"cmax_spec.cm"$, fst$526,29,"cmax_spec.cm"$(LD$526,26,"cmax_spec.cm"$))
        :
            IF$527,7,"cmax_spec.cm"$ ! eq$0,0,"?"$[H$527,8,"cmax_spec.cm"$, nil$527,10,"cmax_spec.cm"$()]:
                H$527,17,"cmax_spec.cm"$
            ELSE
                lookup$528,10,"cmax_spec.cm"$(I$528,19,"cmax_spec.cm"$, rbroth$528,26,"cmax_spec.cm"$(LD$528,23,"cmax_spec.cm"$))

    ELSE
        IF$530,7,"cmax_spec.cm"$ eq$0,0,"?"$[term$530,14,"cmax_spec.cm"$(fst$530,10,"cmax_spec.cm"$(I$530,8,"cmax_spec.cm"$)), term$530,32,"cmax_spec.cm"$(fst$530,28,"cmax_spec.cm"$(fst$530,24,"cmax_spec.cm"$(LD$530,21,"cmax_spec.cm"$)))]:
            LD$530,39,"cmax_spec.cm"$
        ELSE
            lookup$532,10,"cmax_spec.cm"$(I$532,19,"cmax_spec.cm"$, rbroth$532,26,"cmax_spec.cm"$(LD$532,23,"cmax_spec.cm"$))
FCT nnl_to_identset$543,5,"cmax_spec.cm"$ ( NodeList$543,22,"cmax_spec.cm"$ NL$543,31,"cmax_spec.cm"$ ) Set$543,35,"cmax_spec.cm"$ :
    IF$544,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$544,9,"cmax_spec.cm"$(NL$544,6,"cmax_spec.cm"$), 0$544,21,"cmax_spec.cm"$]:
        Set$544,24,"cmax_spec.cm"$()
    ELSE
        LET REST$546,9,"cmax_spec.cm"$ ==
            nnl_to_identset$546,15,"cmax_spec.cm"$(back$546,34,"cmax_spec.cm"$(NL$546,31,"cmax_spec.cm"$))
        :
            LET FST$547,9,"cmax_spec.cm"$ ==
                subterm$547,14,"cmax_spec.cm"$(1$547,22,"cmax_spec.cm"$, NL$547,25,"cmax_spec.cm"$)
            :
                IF$548,7,"cmax_spec.cm"$ Name$548,8,"cmax_spec.cm"$@< ID$548,14,"cmax_spec.cm"$,*>FST$548,20,"cmax_spec.cm"$:
                    LET FSTSET$549,11,"cmax_spec.cm"$ ==
                        appback$549,19,"cmax_spec.cm"$(Set$549,27,"cmax_spec.cm"$(), term$549,37,"cmax_spec.cm"$(ID$549,34,"cmax_spec.cm"$))
                    :
                        union$550,7,"cmax_spec.cm"$(FSTSET$550,13,"cmax_spec.cm"$, REST$550,21,"cmax_spec.cm"$)

                ELSE
                    LET O$552,11,"cmax_spec.cm"$ ==
                        out$552,14,"cmax_spec.cm"$(`$552,19,"cmax_spec.cm"$ "internal error in nnl_to_identset: "$552,19,"cmax_spec.cm"$ "not applied to list of Name@-nodes!\n"$553,19,"cmax_spec.cm"$  ')
                    :
                        nil$554,7,"cmax_spec.cm"$()



ATT names_in_pattern$560,5,"cmax_spec.cm"$ ( Pattern$560,22,"cmax_spec.cm"$@ P$560,31,"cmax_spec.cm"$ ) Set$560,34,"cmax_spec.cm"$ :
    nnl_to_identset$561,3,"cmax_spec.cm"$(collect_occurences$561,20,"cmax_spec.cm"$(P$561,39,"cmax_spec.cm"$, _Name$561,42,"cmax_spec.cm"$@))
ATT names_in_constraint$563,5,"cmax_spec.cm"$ ( Constraint$563,25,"cmax_spec.cm"$@ C$563,37,"cmax_spec.cm"$ ) Set$563,40,"cmax_spec.cm"$ :
    nnl_to_identset$564,3,"cmax_spec.cm"$(collect_occurences$564,20,"cmax_spec.cm"$(C$564,39,"cmax_spec.cm"$, _Name$564,42,"cmax_spec.cm"$@))
ATT bound_names$570,5,"cmax_spec.cm"$ ( Node$570,17,"cmax_spec.cm"$ N$570,22,"cmax_spec.cm"$ ) Set$570,25,"cmax_spec.cm"$ :
    IF$571,5,"cmax_spec.cm"$ AssnList$571,6,"cmax_spec.cm"$@<*, N$571,18,"cmax_spec.cm"$,*>AL$571,23,"cmax_spec.cm"$:
        bound_names$572,8,"cmax_spec.cm"$(AL$572,5,"cmax_spec.cm"$)
    | AssnList$573,6,"cmax_spec.cm"$@ N$573,16,"cmax_spec.cm"$ :
        IF$574,7,"cmax_spec.cm"$ Assertion$574,8,"cmax_spec.cm"$@< N$574,19,"cmax_spec.cm"$>:
            Set$575,7,"cmax_spec.cm"$()
        | AssnDef$576,8,"cmax_spec.cm"$@<_,_, PL$576,21,"cmax_spec.cm"$, N$576,24,"cmax_spec.cm"$> :
            nnl_to_identset$577,7,"cmax_spec.cm"$(collect_occurences$577,23,"cmax_spec.cm"$(PL$577,42,"cmax_spec.cm"$, _Name$577,46,"cmax_spec.cm"$@))
| PatternAssn$578,8,"cmax_spec.cm"$@< P$578,21,"cmax_spec.cm"$, N$578,23,"cmax_spec.cm"$>A$578,26,"cmax_spec.cm"$ :
    union$579,7,"cmax_spec.cm"$(names_in_pattern$579,13,"cmax_spec.cm"$(P$579,30,"cmax_spec.cm"$), bound_names$579,34,"cmax_spec.cm"$(A$579,46,"cmax_spec.cm"$))
| IfAssn$580,8,"cmax_spec.cm"$@<_, N$580,18,"cmax_spec.cm"$,_>A$580,23,"cmax_spec.cm"$ :
    bound_names$581,7,"cmax_spec.cm"$(A$581,19,"cmax_spec.cm"$)
| IfAssn$582,8,"cmax_spec.cm"$@<_,_, N$582,20,"cmax_spec.cm"$>A$582,23,"cmax_spec.cm"$ :
    bound_names$583,7,"cmax_spec.cm"$(A$583,19,"cmax_spec.cm"$)
| LetAssn$584,8,"cmax_spec.cm"$@<< ID$584,18,"cmax_spec.cm"$,*>,_, N$584,26,"cmax_spec.cm"$>A$584,29,"cmax_spec.cm"$ :
    LET S$585,11,"cmax_spec.cm"$ ==
        appback$585,14,"cmax_spec.cm"$(Set$585,22,"cmax_spec.cm"$(), term$585,32,"cmax_spec.cm"$(ID$585,29,"cmax_spec.cm"$))
    :
        union$586,7,"cmax_spec.cm"$(S$586,13,"cmax_spec.cm"$, bound_names$586,16,"cmax_spec.cm"$(A$586,28,"cmax_spec.cm"$))

        ELSE
            LET O$588,11,"cmax_spec.cm"$ ==
                out$588,14,"cmax_spec.cm"$(`$588,19,"cmax_spec.cm"$ "internal error in bound_names: "$588,19,"cmax_spec.cm"$ "unknown occurence of AssnList@!\n"$589,19,"cmax_spec.cm"$  ')
            :
                nil$590,7,"cmax_spec.cm"$()

    ELSE
        bound_names$591,23,"cmax_spec.cm"$(enclAssnList$591,10,"cmax_spec.cm"$(N$591,8,"cmax_spec.cm"$))
ATT free_pattern_names$597,5,"cmax_spec.cm"$ ( PatternAssn$597,24,"cmax_spec.cm"$@ PA$597,37,"cmax_spec.cm"$ ) Set$597,41,"cmax_spec.cm"$ :
    setminus$598,3,"cmax_spec.cm"$(names_in_pattern$598,12,"cmax_spec.cm"$(fst$598,32,"cmax_spec.cm"$(PA$598,29,"cmax_spec.cm"$)), bound_names$598,38,"cmax_spec.cm"$(PA$598,50,"cmax_spec.cm"$))
ATT StrucAssertions$611,5,"cmax_spec.cm"$ ( Structure$611,21,"cmax_spec.cm"$@ S$611,32,"cmax_spec.cm"$ ) NodeList$611,35,"cmax_spec.cm"$ :
    collect_occurences$612,3,"cmax_spec.cm"$(S$612,22,"cmax_spec.cm"$, _Assertion$612,25,"cmax_spec.cm"$@)
ATT assertion_nr$614,5,"cmax_spec.cm"$ ( Assertion$614,18,"cmax_spec.cm"$@ A$614,29,"cmax_spec.cm"$ ) Int$614,32,"cmax_spec.cm"$ :
    lookup_node_in_list$615,3,"cmax_spec.cm"$(A$615,23,"cmax_spec.cm"$, StrucAssertions$615,42,"cmax_spec.cm"$(enclStructure$615,28,"cmax_spec.cm"$(A$615,26,"cmax_spec.cm"$)))
ATT StrucAssns$617,5,"cmax_spec.cm"$ ( Structure$617,16,"cmax_spec.cm"$@ S$617,27,"cmax_spec.cm"$ ) NodeList$617,30,"cmax_spec.cm"$ :
    collect_occurences$617,40,"cmax_spec.cm"$(S$617,59,"cmax_spec.cm"$, _Assn$617,62,"cmax_spec.cm"$@)
ATT assn_nr$619,5,"cmax_spec.cm"$ ( Assn$619,13,"cmax_spec.cm"$@ A$619,19,"cmax_spec.cm"$ ) Int$619,22,"cmax_spec.cm"$ :
    lookup_node_in_list$620,3,"cmax_spec.cm"$(A$620,23,"cmax_spec.cm"$, StrucAssns$620,42,"cmax_spec.cm"$(enclStructure$620,28,"cmax_spec.cm"$(A$620,26,"cmax_spec.cm"$)))
ATT unnamed_pattern_items$628,5,"cmax_spec.cm"$ ( Pattern$628,27,"cmax_spec.cm"$@ P$628,36,"cmax_spec.cm"$ ) NodeList$628,39,"cmax_spec.cm"$ :
    unnamed_items_filter$629,3,"cmax_spec.cm"$(collect_occurences$629,24,"cmax_spec.cm"$(P$629,43,"cmax_spec.cm"$, _Item$629,46,"cmax_spec.cm"$@))
FCT unnamed_items_filter$631,5,"cmax_spec.cm"$ ( NodeList$631,26,"cmax_spec.cm"$ NL$631,35,"cmax_spec.cm"$ ) NodeList$631,39,"cmax_spec.cm"$ :
    IF$632,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$632,9,"cmax_spec.cm"$(NL$632,6,"cmax_spec.cm"$), 0$632,21,"cmax_spec.cm"$]:
        NL$632,24,"cmax_spec.cm"$
    ELSE
        LET REST$634,9,"cmax_spec.cm"$ ==
            unnamed_items_filter$634,15,"cmax_spec.cm"$(back$634,39,"cmax_spec.cm"$(NL$634,36,"cmax_spec.cm"$))
        :
            LET FST$635,9,"cmax_spec.cm"$ ==
                subterm$635,14,"cmax_spec.cm"$(1$635,22,"cmax_spec.cm"$, NL$635,25,"cmax_spec.cm"$)
            :
                IF$636,7,"cmax_spec.cm"$ Pattern$636,8,"cmax_spec.cm"$@<_,_,Blank$636,21,"cmax_spec.cm"$@ >FST$636,29,"cmax_spec.cm"$:
                    appfront$636,34,"cmax_spec.cm"$(FST$636,43,"cmax_spec.cm"$, REST$636,48,"cmax_spec.cm"$)
                | ItemList$637,8,"cmax_spec.cm"$@<*,Blank$637,20,"cmax_spec.cm"$@ FST$637,27,"cmax_spec.cm"$,*> :
                    appfront$637,35,"cmax_spec.cm"$(FST$637,44,"cmax_spec.cm"$, REST$637,49,"cmax_spec.cm"$)
                ELSE
                    REST$638,10,"cmax_spec.cm"$


ATT tmp_idents$640,5,"cmax_spec.cm"$ ( Pattern$640,16,"cmax_spec.cm"$@ P$640,25,"cmax_spec.cm"$ ) Set$640,28,"cmax_spec.cm"$ :
    tmp_idents_sub$641,3,"cmax_spec.cm"$(unnamed_pattern_items$641,18,"cmax_spec.cm"$(P$641,40,"cmax_spec.cm"$))
FCT tmp_idents_sub$643,5,"cmax_spec.cm"$ ( NodeList$643,20,"cmax_spec.cm"$ NL$643,29,"cmax_spec.cm"$ ) Set$643,33,"cmax_spec.cm"$ :
    IF$644,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$644,9,"cmax_spec.cm"$(NL$644,6,"cmax_spec.cm"$), 0$644,21,"cmax_spec.cm"$]:
        Set$644,24,"cmax_spec.cm"$()
    ELSE
        LET REST$646,9,"cmax_spec.cm"$ ==
            tmp_idents_sub$646,15,"cmax_spec.cm"$(back$646,33,"cmax_spec.cm"$(NL$646,30,"cmax_spec.cm"$))
        :
            LET FST$647,9,"cmax_spec.cm"$ ==
                subterm$647,14,"cmax_spec.cm"$(1$647,22,"cmax_spec.cm"$, NL$647,25,"cmax_spec.cm"$)
            :
                LET ID$648,9,"cmax_spec.cm"$ ==
                    `$648,14,"cmax_spec.cm"$ "__tmp_"$648,14,"cmax_spec.cm"$ itos$648,41,"cmax_spec.cm"$(index$648,23,"cmax_spec.cm"$(FST$648,29,"cmax_spec.cm"$, _Node$648,34,"cmax_spec.cm"$))  '
                :
                    appfront$649,5,"cmax_spec.cm"$(strtoid$649,17,"cmax_spec.cm"$(ID$649,14,"cmax_spec.cm"$), REST$649,26,"cmax_spec.cm"$)



ATT all_vars$726,5,"cmax_spec.cm"$ ( Structure$726,15,"cmax_spec.cm"$@ S$726,26,"cmax_spec.cm"$ ) NodeList$726,29,"cmax_spec.cm"$ :
    collect_occurences$727,3,"cmax_spec.cm"$(S$727,22,"cmax_spec.cm"$, _VarDecl$727,25,"cmax_spec.cm"$@)
FCT varPtrId$761,5,"cmax_spec.cm"$ ( Ident$761,15,"cmax_spec.cm"$ I$761,21,"cmax_spec.cm"$ ) Ident$761,24,"cmax_spec.cm"$ :
    strtoid$761,32,"cmax_spec.cm"$(`$761,41,"cmax_spec.cm"$ idtos$761,43,"cmax_spec.cm"$(I$761,41,"cmax_spec.cm"$) "_PTR__"$761,49,"cmax_spec.cm"$  ')
FCT syncAttId$762,5,"cmax_spec.cm"$ (  ) Ident$762,17,"cmax_spec.cm"$ :
    strtoid$762,32,"cmax_spec.cm"$("CSSYNC__"$762,40,"cmax_spec.cm"$)
FCT attSyncAllAttId$763,5,"cmax_spec.cm"$ (  ) Ident$763,23,"cmax_spec.cm"$ :
    strtoid$763,32,"cmax_spec.cm"$("sync_all__"$763,40,"cmax_spec.cm"$)
FCT attSyncAttId$764,5,"cmax_spec.cm"$ ( Ident$764,18,"cmax_spec.cm"$ I$764,24,"cmax_spec.cm"$ ) Ident$764,27,"cmax_spec.cm"$ :
    strtoid$764,34,"cmax_spec.cm"$(`$764,43,"cmax_spec.cm"$ idtos$764,45,"cmax_spec.cm"$(I$764,43,"cmax_spec.cm"$) "_sync__"$764,51,"cmax_spec.cm"$  ')
FCT initFctId$767,5,"cmax_spec.cm"$ (  ) Ident$767,17,"cmax_spec.cm"$ :
    strtoid$767,32,"cmax_spec.cm"$("init_var__"$767,40,"cmax_spec.cm"$)
FCT getVarFctId$768,5,"cmax_spec.cm"$ (  ) Ident$768,19,"cmax_spec.cm"$ :
    strtoid$768,32,"cmax_spec.cm"$("get_var_value__"$768,40,"cmax_spec.cm"$)
FCT activateFctId$769,5,"cmax_spec.cm"$ (  ) Ident$769,21,"cmax_spec.cm"$ :
    strtoid$769,32,"cmax_spec.cm"$("activate_constrs__"$769,40,"cmax_spec.cm"$)
FCT solveFctId$770,5,"cmax_spec.cm"$ ( Ident$770,16,"cmax_spec.cm"$ I$770,22,"cmax_spec.cm"$ ) Ident$770,25,"cmax_spec.cm"$ :
    strtoid$770,32,"cmax_spec.cm"$(`$770,41,"cmax_spec.cm"$ "solve__"$770,41,"cmax_spec.cm"$  ')
FCT localSolveFctId$771,5,"cmax_spec.cm"$ (  ) Ident$771,23,"cmax_spec.cm"$ :
    strtoid$771,32,"cmax_spec.cm"$("sm__"$771,40,"cmax_spec.cm"$)
FCT syncFctId$772,5,"cmax_spec.cm"$ (  ) Ident$772,17,"cmax_spec.cm"$ :
    strtoid$772,32,"cmax_spec.cm"$("sync__"$772,40,"cmax_spec.cm"$)
FCT maxSpecId$775,5,"cmax_spec.cm"$ (  ) String$775,17,"cmax_spec.cm"$ :
    LET F$776,7,"cmax_spec.cm"$ ==
        getOption$776,10,"cmax_spec.cm"$("o"$776,20,"cmax_spec.cm"$)
    :
        IF$777,5,"cmax_spec.cm"$ eq$0,0,"?"$[F$777,6,"cmax_spec.cm"$, ""$777,8,"cmax_spec.cm"$]:
            "stdmax_spec"$778,5,"cmax_spec.cm"$
        ELSE
            F$779,8,"cmax_spec.cm"$

ATT MAXCodeForConstraints$785,5,"cmax_spec.cm"$ ( Node$785,28,"cmax_spec.cm"$ N$785,33,"cmax_spec.cm"$ ) LocalDeclList$785,36,"cmax_spec.cm"$ :
    IF$786,5,"cmax_spec.cm"$ Structure$786,6,"cmax_spec.cm"$@<< STRUCID$786,19,"cmax_spec.cm"$,*>,< I$786,31,"cmax_spec.cm"$,*>,< LD$786,37,"cmax_spec.cm"$,*>>N$786,44,"cmax_spec.cm"$:
        LET H$787,9,"cmax_spec.cm"$ ==
            MAXCodeForConstraintsL$787,15,"cmax_spec.cm"$(LD$787,12,"cmax_spec.cm"$)
        :
            LET SYNCATT$788,9,"cmax_spec.cm"$ ==
                MaxCodeText$788,18,"cmax_spec.cm"$(`$788,31,"cmax_spec.cm"$ "ATT "$789,7,"cmax_spec.cm"$ idtos$789,26,"cmax_spec.cm"$(syncAttId$789,14,"cmax_spec.cm"$()) "( Node N) Element:\n"$789,32,"cmax_spec.cm"$ "  IF N=root():\n"$790,7,"cmax_spec.cm"$ "    LET H=="$791,7,"cmax_spec.cm"$ idtos$791,39,"cmax_spec.cm"$(attSyncAllAttId$791,21,"cmax_spec.cm"$()) "(N):\n"$791,45,"cmax_spec.cm"$ "    LET H=="$792,7,"cmax_spec.cm"$ idtos$792,37,"cmax_spec.cm"$(activateFctId$792,21,"cmax_spec.cm"$()) "():\n"$792,43,"cmax_spec.cm"$ "    "$793,7,"cmax_spec.cm"$ idtos$793,39,"cmax_spec.cm"$(solveFctId$793,14,"cmax_spec.cm"$(term$793,33,"cmax_spec.cm"$(STRUCID$793,25,"cmax_spec.cm"$))) "()\n"$793,45,"cmax_spec.cm"$ "  ELSE "$794,7,"cmax_spec.cm"$ idtos$794,29,"cmax_spec.cm"$(syncAttId$794,17,"cmax_spec.cm"$()) "( fath (N) )\n"$794,35,"cmax_spec.cm"$  ')
            :
                LET H$796,9,"cmax_spec.cm"$ ==
                    appback$796,12,"cmax_spec.cm"$(H$796,20,"cmax_spec.cm"$, SYNCATT$796,23,"cmax_spec.cm"$)
                :
                    LET SYNCATT1$798,9,"cmax_spec.cm"$ ==
                        LocalDeclList$798,19,"cmax_spec.cm"$()
                    :
                        LET SYNCATT1$799,9,"cmax_spec.cm"$ ==
                            appback$799,19,"cmax_spec.cm"$(SYNCATT1$799,27,"cmax_spec.cm"$, MaxCodeText$799,37,"cmax_spec.cm"$(`$799,50,"cmax_spec.cm"$ "ATT "$800,7,"cmax_spec.cm"$ idtos$800,32,"cmax_spec.cm"$(attSyncAllAttId$800,14,"cmax_spec.cm"$()) "("$800,38,"cmax_spec.cm"$ idtos$800,49,"cmax_spec.cm"$(term$800,44,"cmax_spec.cm"$(I$800,42,"cmax_spec.cm"$)) "@ N) Bool:\n"$800,55,"cmax_spec.cm"$ "  LET H==true():\n"$801,7,"cmax_spec.cm"$  '))
                        :
                            LET SYNCATT1$803,9,"cmax_spec.cm"$ ==
                                conc$803,19,"cmax_spec.cm"$(SYNCATT1$803,24,"cmax_spec.cm"$, att_sync_max_code$803,34,"cmax_spec.cm"$(attrs_used_in_assns$803,52,"cmax_spec.cm"$(N$803,72,"cmax_spec.cm"$)))
                            :
                                LET SYNCATT1$804,9,"cmax_spec.cm"$ ==
                                    conc$804,19,"cmax_spec.cm"$(SYNCATT1$804,24,"cmax_spec.cm"$, att_sync_max_code1$804,34,"cmax_spec.cm"$(all_vars$804,53,"cmax_spec.cm"$(N$804,62,"cmax_spec.cm"$)))
                                :
                                    LET SYNCATT1$805,9,"cmax_spec.cm"$ ==
                                        appback$805,19,"cmax_spec.cm"$(SYNCATT1$805,27,"cmax_spec.cm"$, MaxCodeText$805,37,"cmax_spec.cm"$("  H\n"$805,49,"cmax_spec.cm"$))
                                    :
                                        conc$806,5,"cmax_spec.cm"$(H$806,10,"cmax_spec.cm"$, SYNCATT1$806,13,"cmax_spec.cm"$)








    | DeclList$807,5,"cmax_spec.cm"$@< D$807,15,"cmax_spec.cm"$,*>N$807,20,"cmax_spec.cm"$ :
        MAXCodeForConstraintsL$807,25,"cmax_spec.cm"$(D$807,23,"cmax_spec.cm"$)
| DeclForConstraints$808,5,"cmax_spec.cm"$@ N$808,25,"cmax_spec.cm"$ :
    LET H$809,9,"cmax_spec.cm"$ ==
        MAXCodeForConstraintsSub$809,14,"cmax_spec.cm"$(N$809,12,"cmax_spec.cm"$)
    :
        H$810,7,"cmax_spec.cm"$

| Attribute$811,5,"cmax_spec.cm"$@< ID$811,16,"cmax_spec.cm"$,< SID$811,20,"cmax_spec.cm"$,*>,_,_,_>N$811,34,"cmax_spec.cm"$ :
    LET STRUCT$812,9,"cmax_spec.cm"$ ==
        enclStructure$812,18,"cmax_spec.cm"$(N$812,33,"cmax_spec.cm"$)
    :
        IF$813,7,"cmax_spec.cm"$ eq$0,0,"?"$[iselem$813,8,"cmax_spec.cm"$(N$813,17,"cmax_spec.cm"$, attrs_used_in_assns$813,20,"cmax_spec.cm"$(STRUCT$813,41,"cmax_spec.cm"$)), true$813,51,"cmax_spec.cm"$()]:
            LET ID1$814,11,"cmax_spec.cm"$ ==
                idtos$814,42,"cmax_spec.cm"$(attSyncAttId$814,16,"cmax_spec.cm"$(term$814,36,"cmax_spec.cm"$(fst$814,32,"cmax_spec.cm"$(ID$814,29,"cmax_spec.cm"$))))
            :
                LET ID2$815,11,"cmax_spec.cm"$ ==
                    `$815,17,"cmax_spec.cm"$ "_"$815,17,"cmax_spec.cm"$ codeForIdent$815,21,"cmax_spec.cm"$(term$815,38,"cmax_spec.cm"$(SID$815,34,"cmax_spec.cm"$))  '
                :
                    LET O$816,11,"cmax_spec.cm"$ ==
                        IF$817,11,"cmax_spec.cm"$ ! is$817,13,"cmax_spec.cm"$[ID2$817,16,"cmax_spec.cm"$, _String$817,21,"cmax_spec.cm"$]:
                            debug$817,31,"cmax_spec.cm"$(`$817,38,"cmax_spec.cm"$ "MaxCodeForConstraints: "$817,38,"cmax_spec.cm"$ "error in string conc.!\n"$818,32,"cmax_spec.cm"$  ')
                        ELSE
                            true$819,14,"cmax_spec.cm"$()
                    :
                        LET ATTR$821,11,"cmax_spec.cm"$ ==
                            MaxCodeText$821,17,"cmax_spec.cm"$(`$821,30,"cmax_spec.cm"$ "ATT "$822,9,"cmax_spec.cm"$ ID1$822,16,"cmax_spec.cm"$ "( Node N) Element:\n"$822,20,"cmax_spec.cm"$ "  LET H1==IF <*,N1> N: "$823,9,"cmax_spec.cm"$ ID1$823,35,"cmax_spec.cm"$ "(N1)\n"$823,39,"cmax_spec.cm"$ "          ELSE true():\n"$824,9,"cmax_spec.cm"$ "  LET H2==IF <*,N1,N,*>: "$825,9,"cmax_spec.cm"$ ID1$825,37,"cmax_spec.cm"$ "(N1)\n"$825,41,"cmax_spec.cm"$ "          ELSE true():\n"$826,9,"cmax_spec.cm"$ "  LET H3==IF is[N, _"$827,9,"cmax_spec.cm"$ codeForIdent$827,32,"cmax_spec.cm"$(term$827,49,"cmax_spec.cm"$(SID$827,45,"cmax_spec.cm"$)) "]: "$827,55,"cmax_spec.cm"$ idtos$828,39,"cmax_spec.cm"$(term$828,34,"cmax_spec.cm"$(fst$828,30,"cmax_spec.cm"$(ID$828,27,"cmax_spec.cm"$))) "(N)\n"$828,45,"cmax_spec.cm"$ "          ELSE true():\n"$829,9,"cmax_spec.cm"$ "  "$830,9,"cmax_spec.cm"$ idtos$830,26,"cmax_spec.cm"$(syncFctId$830,14,"cmax_spec.cm"$()) "( "$830,32,"cmax_spec.cm"$ idtos$830,49,"cmax_spec.cm"$(syncFctId$830,37,"cmax_spec.cm"$()) "( H1, H2 ), H3 )\n"$830,55,"cmax_spec.cm"$  ')
                        :
                            appback$832,7,"cmax_spec.cm"$(LocalDeclList$832,17,"cmax_spec.cm"$(), ATTR$832,34,"cmax_spec.cm"$)




        ELSE
            LocalDeclList$833,10,"cmax_spec.cm"$()

    ELSE
        LocalDeclList$835,5,"cmax_spec.cm"$()
FCT MAXCodeForConstraintsL$837,5,"cmax_spec.cm"$ ( Node$837,29,"cmax_spec.cm"$ N$837,34,"cmax_spec.cm"$ ) LocalDeclList$837,37,"cmax_spec.cm"$ :
    LET H$838,7,"cmax_spec.cm"$ ==
        MAXCodeForConstraints$838,12,"cmax_spec.cm"$(N$838,10,"cmax_spec.cm"$)
    :
        IF$839,5,"cmax_spec.cm"$ <*, N$839,9,"cmax_spec.cm"$, NEXT$839,11,"cmax_spec.cm"$,*>:
            conc$839,20,"cmax_spec.cm"$(H$839,25,"cmax_spec.cm"$, MAXCodeForConstraintsL$839,33,"cmax_spec.cm"$(NEXT$839,28,"cmax_spec.cm"$))
        ELSE
            H$840,8,"cmax_spec.cm"$

FCT att_sync_max_code$842,5,"cmax_spec.cm"$ ( Set$842,23,"cmax_spec.cm"$ ATTRS$842,27,"cmax_spec.cm"$ ) LocalDeclList$842,34,"cmax_spec.cm"$ :
    IF$843,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$843,12,"cmax_spec.cm"$(ATTRS$843,6,"cmax_spec.cm"$), 0$843,24,"cmax_spec.cm"$]:
        LocalDeclList$843,27,"cmax_spec.cm"$()
    ELSE
        LET ID$845,9,"cmax_spec.cm"$ ==
            idtos$845,58,"cmax_spec.cm"$(attSyncAttId$845,13,"cmax_spec.cm"$(term$845,52,"cmax_spec.cm"$(fst$845,48,"cmax_spec.cm"$(fst$845,44,"cmax_spec.cm"$(subterm$845,26,"cmax_spec.cm"$(1$845,34,"cmax_spec.cm"$, ATTRS$845,37,"cmax_spec.cm"$))))))
        :
            LET H$846,9,"cmax_spec.cm"$ ==
                MaxCodeText$846,12,"cmax_spec.cm"$(`$846,25,"cmax_spec.cm"$ "  LET H=="$846,25,"cmax_spec.cm"$ idtos$846,49,"cmax_spec.cm"$(syncFctId$846,37,"cmax_spec.cm"$()) "(H, "$846,55,"cmax_spec.cm"$ ID$846,62,"cmax_spec.cm"$ "(N)):\n"$846,65,"cmax_spec.cm"$  ')
            :
                appfront$847,5,"cmax_spec.cm"$(H$847,14,"cmax_spec.cm"$, att_sync_max_code$847,17,"cmax_spec.cm"$(back$847,41,"cmax_spec.cm"$(ATTRS$847,35,"cmax_spec.cm"$)))


FCT att_sync_max_code1$849,5,"cmax_spec.cm"$ ( NodeList$849,24,"cmax_spec.cm"$ NL$849,33,"cmax_spec.cm"$ ) LocalDeclList$849,37,"cmax_spec.cm"$ :
    IF$850,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$850,9,"cmax_spec.cm"$(NL$850,6,"cmax_spec.cm"$), 0$850,21,"cmax_spec.cm"$]:
        LocalDeclList$850,24,"cmax_spec.cm"$()
    ELSE
        LET ID$852,9,"cmax_spec.cm"$ ==
            idtos$852,65,"cmax_spec.cm"$(attSyncAttId$852,13,"cmax_spec.cm"$(varPtrId$852,26,"cmax_spec.cm"$(term$852,58,"cmax_spec.cm"$(fst$852,54,"cmax_spec.cm"$(fst$852,50,"cmax_spec.cm"$(subterm$852,35,"cmax_spec.cm"$(1$852,43,"cmax_spec.cm"$, NL$852,46,"cmax_spec.cm"$)))))))
        :
            LET H$853,9,"cmax_spec.cm"$ ==
                MaxCodeText$853,12,"cmax_spec.cm"$(`$853,25,"cmax_spec.cm"$ "  LET H=="$853,25,"cmax_spec.cm"$ idtos$853,49,"cmax_spec.cm"$(syncFctId$853,37,"cmax_spec.cm"$()) "(H, "$853,55,"cmax_spec.cm"$ ID$853,62,"cmax_spec.cm"$ "(N)):\n"$853,65,"cmax_spec.cm"$  ')
            :
                appfront$854,5,"cmax_spec.cm"$(H$854,14,"cmax_spec.cm"$, att_sync_max_code1$854,17,"cmax_spec.cm"$(back$854,39,"cmax_spec.cm"$(NL$854,36,"cmax_spec.cm"$)))


FCT MAXCodeForConstraintsSub$856,5,"cmax_spec.cm"$ ( DeclForConstraints$856,32,"cmax_spec.cm"$@ LD$856,52,"cmax_spec.cm"$ ) LocalDeclList$856,57,"cmax_spec.cm"$ :
    IF$857,5,"cmax_spec.cm"$ VarDecl$857,6,"cmax_spec.cm"$@< I$857,16,"cmax_spec.cm"$,< SID$857,20,"cmax_spec.cm"$,*>SIDL$857,27,"cmax_spec.cm"$,< N$857,34,"cmax_spec.cm"$,*>NL$857,39,"cmax_spec.cm"$, LATT$857,42,"cmax_spec.cm"$, E$857,47,"cmax_spec.cm"$,_>LD$857,52,"cmax_spec.cm"$:
        LET EXPR$858,9,"cmax_spec.cm"$ ==
            LET INITFCTID$859,11,"cmax_spec.cm"$ ==
                ApplId$859,24,"cmax_spec.cm"$(initFctId$859,31,"cmax_spec.cm"$(), 0$859,44,"cmax_spec.cm"$, 0$859,47,"cmax_spec.cm"$, "?"$859,50,"cmax_spec.cm"$)
            :
                FuncAppl$860,7,"cmax_spec.cm"$(INITFCTID$860,18,"cmax_spec.cm"$, appback$860,29,"cmax_spec.cm"$(ExprList$860,37,"cmax_spec.cm"$(), term$860,51,"cmax_spec.cm"$(E$860,49,"cmax_spec.cm"$)))

        :
            LET H$861,9,"cmax_spec.cm"$ ==
                LocalDeclList$861,12,"cmax_spec.cm"$()
            :
                LET H$862,9,"cmax_spec.cm"$ ==
                    appback$862,12,"cmax_spec.cm"$(H$862,20,"cmax_spec.cm"$, appback$863,7,"cmax_spec.cm"$(FuAtList$863,15,"cmax_spec.cm"$(), Attribute$864,9,"cmax_spec.cm"$(DefId$864,20,"cmax_spec.cm"$(varPtrId$864,28,"cmax_spec.cm"$(term$864,43,"cmax_spec.cm"$(fst$864,39,"cmax_spec.cm"$(I$864,37,"cmax_spec.cm"$))), 0$864,50,"cmax_spec.cm"$, 0$864,53,"cmax_spec.cm"$, "?"$864,56,"cmax_spec.cm"$), term$864,68,"cmax_spec.cm"$(SIDL$864,63,"cmax_spec.cm"$), term$865,14,"cmax_spec.cm"$(NL$865,11,"cmax_spec.cm"$), TermSortId$865,20,"cmax_spec.cm"$(strtoid$865,33,"cmax_spec.cm"$("Element"$865,41,"cmax_spec.cm"$), 0$865,53,"cmax_spec.cm"$, 0$865,56,"cmax_spec.cm"$, "?"$865,59,"cmax_spec.cm"$), EXPR$865,66,"cmax_spec.cm"$)))
                :
                    LET ID1$869,9,"cmax_spec.cm"$ ==
                        idtos$869,49,"cmax_spec.cm"$(attSyncAttId$869,14,"cmax_spec.cm"$(varPtrId$869,27,"cmax_spec.cm"$(term$869,42,"cmax_spec.cm"$(fst$869,38,"cmax_spec.cm"$(I$869,36,"cmax_spec.cm"$)))))
                    :
                        LET ID2$870,9,"cmax_spec.cm"$ ==
                            idtos$870,35,"cmax_spec.cm"$(varPtrId$870,14,"cmax_spec.cm"$(term$870,29,"cmax_spec.cm"$(fst$870,25,"cmax_spec.cm"$(I$870,23,"cmax_spec.cm"$))))
                        :
                            LET H$871,9,"cmax_spec.cm"$ ==
                                appback$871,12,"cmax_spec.cm"$(H$871,20,"cmax_spec.cm"$, MaxCodeText$871,23,"cmax_spec.cm"$(`$871,36,"cmax_spec.cm"$ "ATT "$872,7,"cmax_spec.cm"$ ID1$872,14,"cmax_spec.cm"$ "( Node N) Element:\n"$872,18,"cmax_spec.cm"$ "  LET H1==IF <*,N1> N: "$873,7,"cmax_spec.cm"$ ID1$873,33,"cmax_spec.cm"$ "(N1)\n"$873,37,"cmax_spec.cm"$ "          ELSE true():\n"$874,7,"cmax_spec.cm"$ "  LET H2==IF <*,N1,N,*>: "$875,7,"cmax_spec.cm"$ ID1$875,35,"cmax_spec.cm"$ "(N1)\n"$875,39,"cmax_spec.cm"$ "          ELSE true():\n"$876,7,"cmax_spec.cm"$ "  LET H3==IF is[N, _"$877,7,"cmax_spec.cm"$ codeForIdent$877,30,"cmax_spec.cm"$(term$877,47,"cmax_spec.cm"$(SID$877,43,"cmax_spec.cm"$)) "]: "$877,53,"cmax_spec.cm"$ ID2$877,59,"cmax_spec.cm"$ "(N)\n"$877,63,"cmax_spec.cm"$ "          ELSE true():\n"$878,7,"cmax_spec.cm"$ "  "$879,7,"cmax_spec.cm"$ idtos$879,24,"cmax_spec.cm"$(syncFctId$879,12,"cmax_spec.cm"$()) "( "$879,30,"cmax_spec.cm"$ idtos$879,47,"cmax_spec.cm"$(syncFctId$879,35,"cmax_spec.cm"$()) "( H1, H2 ), H3 )\n"$879,53,"cmax_spec.cm"$  '))
                            :
                                LET H$881,9,"cmax_spec.cm"$ ==
                                    appback$881,12,"cmax_spec.cm"$(H$881,20,"cmax_spec.cm"$, MaxCodeText$881,23,"cmax_spec.cm"$(`$881,36,"cmax_spec.cm"$ "ATT "$882,7,"cmax_spec.cm"$ idToStr$882,16,"cmax_spec.cm"$(I$882,14,"cmax_spec.cm"$) "("$882,24,"cmax_spec.cm"$ codeForIdent$882,28,"cmax_spec.cm"$(term$882,45,"cmax_spec.cm"$(SID$882,41,"cmax_spec.cm"$)) " N) "$882,51,"cmax_spec.cm"$ idtos$883,43,"cmax_spec.cm"$(lattice_sort$883,15,"cmax_spec.cm"$(Decl$883,30,"cmax_spec.cm"$(LATT$883,35,"cmax_spec.cm"$))) ":\n"$883,49,"cmax_spec.cm"$ "  LET H=="$884,7,"cmax_spec.cm"$ idtos$884,31,"cmax_spec.cm"$(syncAttId$884,19,"cmax_spec.cm"$()) "(N):\n"$884,37,"cmax_spec.cm"$ "  "$885,7,"cmax_spec.cm"$ idtos$885,26,"cmax_spec.cm"$(getVarFctId$885,12,"cmax_spec.cm"$()) "("$885,32,"cmax_spec.cm"$ idtos$886,35,"cmax_spec.cm"$(varPtrId$886,14,"cmax_spec.cm"$(term$886,29,"cmax_spec.cm"$(fst$886,25,"cmax_spec.cm"$(I$886,23,"cmax_spec.cm"$)))) "(N))\n"$886,41,"cmax_spec.cm"$  '))
                                :
                                    H$888,5,"cmax_spec.cm"$







    ELSE
        LocalDeclList$890,5,"cmax_spec.cm"$()
FCT cfunc_decls$892,5,"cmax_spec.cm"$ ( Structure$892,17,"cmax_spec.cm"$@ S$892,28,"cmax_spec.cm"$ ) Specification$892,31,"cmax_spec.cm"$ :
    LET RES$893,7,"cmax_spec.cm"$ ==
        Specification$893,12,"cmax_spec.cm"$()
    :
        LET RES$894,7,"cmax_spec.cm"$ ==
            appback$894,12,"cmax_spec.cm"$(RES$894,20,"cmax_spec.cm"$, MaxCodeText$894,25,"cmax_spec.cm"$(`$894,38,"cmax_spec.cm"$ "FCT "$895,5,"cmax_spec.cm"$ idtos$895,26,"cmax_spec.cm"$(getVarFctId$895,12,"cmax_spec.cm"$()) "(Element) Element\n"$895,32,"cmax_spec.cm"$ "FCT "$896,5,"cmax_spec.cm"$ idtos$896,24,"cmax_spec.cm"$(initFctId$896,12,"cmax_spec.cm"$()) "(Element) Element\n"$896,30,"cmax_spec.cm"$ "FCT "$897,5,"cmax_spec.cm"$ idtos$897,28,"cmax_spec.cm"$(activateFctId$897,12,"cmax_spec.cm"$()) "() Element\n"$897,34,"cmax_spec.cm"$ "FCT "$898,5,"cmax_spec.cm"$ idtos$898,39,"cmax_spec.cm"$(solveFctId$898,12,"cmax_spec.cm"$(term$898,33,"cmax_spec.cm"$(fst$898,29,"cmax_spec.cm"$(fst$898,25,"cmax_spec.cm"$(S$898,23,"cmax_spec.cm"$))))) "() Element\n"$898,45,"cmax_spec.cm"$ "FCT "$899,5,"cmax_spec.cm"$ idtos$899,24,"cmax_spec.cm"$(syncFctId$899,12,"cmax_spec.cm"$()) "(Element, Element) Element\n"$899,30,"cmax_spec.cm"$  '))
        :
            RES$901,3,"cmax_spec.cm"$


ATT genMAXCode$903,5,"cmax_spec.cm"$ ( Specification$903,17,"cmax_spec.cm"$@ S$903,32,"cmax_spec.cm"$ ) Specification$903,35,"cmax_spec.cm"$ :
    IF$904,5,"cmax_spec.cm"$ <>S$904,9,"cmax_spec.cm"$:
        Specification$904,12,"cmax_spec.cm"$()
    ELSE
        collectGlobalDecls$904,33,"cmax_spec.cm"$(fst$904,55,"cmax_spec.cm"$(S$904,53,"cmax_spec.cm"$))
FCT collectGlobalDecls$906,5,"cmax_spec.cm"$ ( GlobalDecl$906,25,"cmax_spec.cm"$@ GD$906,37,"cmax_spec.cm"$ ) Specification$906,41,"cmax_spec.cm"$ :
    LET FRONT$907,7,"cmax_spec.cm"$ ==
        IF$908,7,"cmax_spec.cm"$ Structure$908,8,"cmax_spec.cm"$@< ID$908,19,"cmax_spec.cm"$, SID$908,22,"cmax_spec.cm"$,_>GD$908,29,"cmax_spec.cm"$:
            appback$908,33,"cmax_spec.cm"$(cfunc_decls$908,41,"cmax_spec.cm"$(GD$908,53,"cmax_spec.cm"$), makeNewStruc$908,58,"cmax_spec.cm"$(GD$908,71,"cmax_spec.cm"$))
        ELSE
            appback$909,33,"cmax_spec.cm"$(Specification$909,41,"cmax_spec.cm"$(), term$909,61,"cmax_spec.cm"$(GD$909,58,"cmax_spec.cm"$))
    :
        IF$911,5,"cmax_spec.cm"$ <*, GD$911,9,"cmax_spec.cm"$, NEXT$911,12,"cmax_spec.cm"$,*>:
            LET REST$912,9,"cmax_spec.cm"$ ==
                collectGlobalDecls$912,15,"cmax_spec.cm"$(NEXT$912,34,"cmax_spec.cm"$)
            :
                conc$913,5,"cmax_spec.cm"$(FRONT$913,12,"cmax_spec.cm"$, REST$913,19,"cmax_spec.cm"$)

        ELSE
            FRONT$915,5,"cmax_spec.cm"$

FCT makeNewStruc$917,5,"cmax_spec.cm"$ ( Structure$917,19,"cmax_spec.cm"$@ S$917,30,"cmax_spec.cm"$ ) Structure$917,33,"cmax_spec.cm"$ :
    LET H$918,7,"cmax_spec.cm"$ ==
        IF$919,7,"cmax_spec.cm"$ <_,_,< LD$919,14,"cmax_spec.cm"$,*>>S$919,21,"cmax_spec.cm"$:
            collectLocalDecls$919,24,"cmax_spec.cm"$(LD$919,44,"cmax_spec.cm"$)
        ELSE
            LocalDeclList$920,24,"cmax_spec.cm"$()
    :
        LET NEWS$922,7,"cmax_spec.cm"$ ==
            Structure$922,13,"cmax_spec.cm"$(term$922,31,"cmax_spec.cm"$(fst$922,27,"cmax_spec.cm"$(S$922,25,"cmax_spec.cm"$)), term$922,43,"cmax_spec.cm"$(snd$922,39,"cmax_spec.cm"$(S$922,37,"cmax_spec.cm"$)), conc$923,14,"cmax_spec.cm"$(MAXCodeForConstraints$923,23,"cmax_spec.cm"$(S$923,21,"cmax_spec.cm"$), H$923,47,"cmax_spec.cm"$))
        :
            LET O$924,7,"cmax_spec.cm"$ ==
                IF$925,7,"cmax_spec.cm"$ eq$0,0,"?"$[NEWS$925,8,"cmax_spec.cm"$, nil$925,13,"cmax_spec.cm"$()]:
                    debug$925,20,"cmax_spec.cm"$("makeNewStruc: Structure is nil!\n"$925,26,"cmax_spec.cm"$)
                ELSE
                    true$926,10,"cmax_spec.cm"$()
            :
                NEWS$928,3,"cmax_spec.cm"$



FCT collectLocalDecls$930,5,"cmax_spec.cm"$ ( LocalDecl$930,25,"cmax_spec.cm"$@ LD$930,36,"cmax_spec.cm"$ ) LocalDeclList$930,41,"cmax_spec.cm"$ :
    LET H$931,7,"cmax_spec.cm"$ ==
        IF$932,7,"cmax_spec.cm"$ DeclListForConstraints$932,8,"cmax_spec.cm"$@ LD$932,32,"cmax_spec.cm"$:
            LocalDeclList$933,7,"cmax_spec.cm"$()
        ELSE
            appback$935,7,"cmax_spec.cm"$(LocalDeclList$935,16,"cmax_spec.cm"$(), term$935,36,"cmax_spec.cm"$(LD$935,33,"cmax_spec.cm"$))
    :
        IF$937,7,"cmax_spec.cm"$ <*, LD$937,11,"cmax_spec.cm"$, NEXT$937,14,"cmax_spec.cm"$,*>:
            conc$937,24,"cmax_spec.cm"$(H$937,31,"cmax_spec.cm"$, collectLocalDecls$937,34,"cmax_spec.cm"$(NEXT$937,53,"cmax_spec.cm"$))
        ELSE
            H$938,24,"cmax_spec.cm"$

FCT gen_C_all$945,5,"cmax_spec.cm"$ ( Node$945,17,"cmax_spec.cm"$ N$945,22,"cmax_spec.cm"$, Int$945,25,"cmax_spec.cm"$ FH$945,29,"cmax_spec.cm"$ ) Bool$945,34,"cmax_spec.cm"$ :
    IF$946,5,"cmax_spec.cm"$ Structure$946,6,"cmax_spec.cm"$@< I$946,17,"cmax_spec.cm"$,_, DECLS$946,21,"cmax_spec.cm"$>N$946,28,"cmax_spec.cm"$:
        LET VERBOSEDECL$947,9,"cmax_spec.cm"$ ==
            IF$948,9,"cmax_spec.cm"$ eq$0,0,"?"$[checkOption$948,10,"cmax_spec.cm"$("verbosecode"$948,22,"cmax_spec.cm"$), true$948,37,"cmax_spec.cm"$()]:
                "int Verbose = 1;"$949,9,"cmax_spec.cm"$
            ELSE
                "int Verbose = 0;"$951,9,"cmax_spec.cm"$
        :
            LET O$953,9,"cmax_spec.cm"$ ==
                writeToFile$953,12,"cmax_spec.cm"$(FH$953,24,"cmax_spec.cm"$, `$954,10,"cmax_spec.cm"$ "/* C-Code generated by cmax */\n\n"$954,10,"cmax_spec.cm"$ "#include \""$956,10,"cmax_spec.cm"$ maxSpecId$956,24,"cmax_spec.cm"$() ".h\" \n"$956,36,"cmax_spec.cm"$ "#include <stdio.h>\n"$957,10,"cmax_spec.cm"$ "#include <stdlib.h>\n"$958,10,"cmax_spec.cm"$ "#include \"solver.h\"\n\n"$959,10,"cmax_spec.cm"$ "#define SORTERROR(e,a) fprintf(stderr, \\\n"$961,10,"cmax_spec.cm"$ "         \"Error in usage of assn definition \" #a \\\n"$962,10,"cmax_spec.cm"$ "         \": argument \" #e \" is of wrong sort!\\n \") \n"$963,10,"cmax_spec.cm"$ "#define IS(e,s,a)  if (!is(e,s)) {SORTERROR(e,a); return; }\n"$964,10,"cmax_spec.cm"$ "#define ISNIL(e)     if (eq(e, nil())) return;\n\n"$965,10,"cmax_spec.cm"$ VERBOSEDECL$967,10,"cmax_spec.cm"$ "\n\n"$967,22,"cmax_spec.cm"$ "ELEMENT sync__(ELEMENT e1, ELEMENT e2){return btoe(1);}\n"$969,10,"cmax_spec.cm"$  ')
            :
                LET O$972,9,"cmax_spec.cm"$ ==
                    gen_C_lists$972,12,"cmax_spec.cm"$(fst$972,30,"cmax_spec.cm"$(DECLS$972,24,"cmax_spec.cm"$), FH$972,35,"cmax_spec.cm"$)
                :
                    LET O$973,9,"cmax_spec.cm"$ ==
                        writeToFile$973,12,"cmax_spec.cm"$(FH$973,24,"cmax_spec.cm"$, `$974,10,"cmax_spec.cm"$ "ELEMENT "$974,10,"cmax_spec.cm"$ idtos$974,37,"cmax_spec.cm"$(activateFctId$974,21,"cmax_spec.cm"$()) "(void)\n"$974,43,"cmax_spec.cm"$ "{\n"$975,10,"cmax_spec.cm"$ "    if (Verbose) fprintf(stderr,\"activating constraints \");\n"$976,10,"cmax_spec.cm"$  ')
                    :
                        LET O$979,9,"cmax_spec.cm"$ ==
                            gen_C_call_funcs$979,12,"cmax_spec.cm"$(FH$979,29,"cmax_spec.cm"$, idtos$979,49,"cmax_spec.cm"$(activateFctId$979,33,"cmax_spec.cm"$()), numsubterms$980,47,"cmax_spec.cm"$(StrucAssertions$980,31,"cmax_spec.cm"$(N$980,29,"cmax_spec.cm"$)), 1$980,60,"cmax_spec.cm"$)
                        :
                            LET O$982,9,"cmax_spec.cm"$ ==
                                writeToFile$982,12,"cmax_spec.cm"$(FH$982,24,"cmax_spec.cm"$, `$982,28,"cmax_spec.cm"$ "    if (Verbose) fprintf(stderr,\"... done\\n\");\n"$983,10,"cmax_spec.cm"$ "    return btoe(1);\n"$984,10,"cmax_spec.cm"$ "}\n"$985,10,"cmax_spec.cm"$  ')
                            :
                                O$988,5,"cmax_spec.cm"$






    | DeclList$989,5,"cmax_spec.cm"$@< FST$989,15,"cmax_spec.cm"$,*>N$989,22,"cmax_spec.cm"$ :
        gen_C_lists$989,25,"cmax_spec.cm"$(FST$989,37,"cmax_spec.cm"$, FH$989,42,"cmax_spec.cm"$)
| AssnList$990,5,"cmax_spec.cm"$@ N$990,15,"cmax_spec.cm"$ :
    gen_C_lists$991,5,"cmax_spec.cm"$(fst$991,19,"cmax_spec.cm"$(N$991,17,"cmax_spec.cm"$), FH$991,24,"cmax_spec.cm"$)
| Assn$992,5,"cmax_spec.cm"$@ N$992,11,"cmax_spec.cm"$ :
    LET NR$993,9,"cmax_spec.cm"$ ==
        assn_nr$993,15,"cmax_spec.cm"$(N$993,13,"cmax_spec.cm"$)
    :
        IF$994,7,"cmax_spec.cm"$ Constraint$994,8,"cmax_spec.cm"$@ N$994,20,"cmax_spec.cm"$:
            LET O$996,11,"cmax_spec.cm"$ ==
                writeToFile$996,14,"cmax_spec.cm"$(FH$996,26,"cmax_spec.cm"$, `$997,12,"cmax_spec.cm"$ "static int "$997,12,"cmax_spec.cm"$ idtos$997,44,"cmax_spec.cm"$(localSolveFctId$997,26,"cmax_spec.cm"$()) "_"$997,50,"cmax_spec.cm"$ itos$997,57,"cmax_spec.cm"$(NR$997,54,"cmax_spec.cm"$) " (ELEMENT __args[])\n"$998,46,"cmax_spec.cm"$ "{\n"$999,12,"cmax_spec.cm"$  ')
            :
                LET O$1002,11,"cmax_spec.cm"$ ==
                    gen_C_define_list$1002,14,"cmax_spec.cm"$(names_in_constraint$1002,32,"cmax_spec.cm"$(N$1002,52,"cmax_spec.cm"$), "__args"$1002,56,"cmax_spec.cm"$, 0$1002,66,"cmax_spec.cm"$, FH$1002,69,"cmax_spec.cm"$)
                :
                    LET O$1003,11,"cmax_spec.cm"$ ==
                        writeToFile$1003,14,"cmax_spec.cm"$(FH$1003,26,"cmax_spec.cm"$, "    int __update=0; ELEMENT __vptr,__v,__e; ELEMENT *__vptr1;\n"$1004,9,"cmax_spec.cm"$)
                    :
                        LET O$1005,11,"cmax_spec.cm"$ ==
                            gen_C_constraint$1005,14,"cmax_spec.cm"$(N$1005,31,"cmax_spec.cm"$, FH$1005,34,"cmax_spec.cm"$, "    "$1005,38,"cmax_spec.cm"$)
                        :
                            LET O$1006,11,"cmax_spec.cm"$ ==
                                writeToFile$1006,14,"cmax_spec.cm"$(FH$1006,26,"cmax_spec.cm"$, "    return __update;\n"$1006,30,"cmax_spec.cm"$)
                            :
                                LET O$1007,11,"cmax_spec.cm"$ ==
                                    gen_C_undef_list$1007,14,"cmax_spec.cm"$(names_in_constraint$1007,31,"cmax_spec.cm"$(N$1007,51,"cmax_spec.cm"$), 0$1007,55,"cmax_spec.cm"$, FH$1007,58,"cmax_spec.cm"$)
                                :
                                    LET O$1008,11,"cmax_spec.cm"$ ==
                                        writeToFile$1008,14,"cmax_spec.cm"$(FH$1008,26,"cmax_spec.cm"$, `$1009,12,"cmax_spec.cm"$ "}\n"$1009,12,"cmax_spec.cm"$  ')
                                    :
                                        O$1012,7,"cmax_spec.cm"$







        | PatternAssn$1013,8,"cmax_spec.cm"$@< P$1013,21,"cmax_spec.cm"$, AL$1013,23,"cmax_spec.cm"$>N$1013,27,"cmax_spec.cm"$ :
            gen_C_all$1013,30,"cmax_spec.cm"$(AL$1013,40,"cmax_spec.cm"$, FH$1013,44,"cmax_spec.cm"$)
| IfAssn$1014,8,"cmax_spec.cm"$@< F$1014,16,"cmax_spec.cm"$, AL1$1014,18,"cmax_spec.cm"$, AL2$1014,22,"cmax_spec.cm"$>N$1014,27,"cmax_spec.cm"$ :
    LET O$1015,11,"cmax_spec.cm"$ ==
        gen_C_all$1015,14,"cmax_spec.cm"$(AL1$1015,24,"cmax_spec.cm"$, FH$1015,29,"cmax_spec.cm"$)
    :
        gen_C_all$1016,7,"cmax_spec.cm"$(AL2$1016,17,"cmax_spec.cm"$, FH$1016,22,"cmax_spec.cm"$)

| LetAssn$1017,8,"cmax_spec.cm"$@<_,_, AL$1017,21,"cmax_spec.cm"$>N$1017,25,"cmax_spec.cm"$ :
    gen_C_all$1017,28,"cmax_spec.cm"$(AL$1017,38,"cmax_spec.cm"$, FH$1017,42,"cmax_spec.cm"$)
        ELSE
            true$1018,10,"cmax_spec.cm"$()

| Assertion$1019,6,"cmax_spec.cm"$@< AL$1019,17,"cmax_spec.cm"$>N$1019,21,"cmax_spec.cm"$ :
    LET O$1023,9,"cmax_spec.cm"$ ==
        gen_C_all$1023,12,"cmax_spec.cm"$(AL$1023,22,"cmax_spec.cm"$, FH$1023,26,"cmax_spec.cm"$)
    :
        LET NR$1027,9,"cmax_spec.cm"$ ==
            assertion_nr$1027,15,"cmax_spec.cm"$(N$1027,13,"cmax_spec.cm"$)
        :
            LET O$1028,9,"cmax_spec.cm"$ ==
                writeToFile$1028,12,"cmax_spec.cm"$(FH$1028,24,"cmax_spec.cm"$, `$1029,10,"cmax_spec.cm"$ "static void "$1029,10,"cmax_spec.cm"$ idtos$1029,41,"cmax_spec.cm"$(activateFctId$1029,25,"cmax_spec.cm"$()) "_"$1029,47,"cmax_spec.cm"$ itos$1029,54,"cmax_spec.cm"$(NR$1029,51,"cmax_spec.cm"$) "(void)\n"$1029,59,"cmax_spec.cm"$ "{\n"$1030,10,"cmax_spec.cm"$  ')
            :
                LET O$1031,9,"cmax_spec.cm"$ ==
                    gen_C_activation_assertion$1031,12,"cmax_spec.cm"$(N$1031,39,"cmax_spec.cm"$, FH$1031,42,"cmax_spec.cm"$)
                :
                    LET O$1032,9,"cmax_spec.cm"$ ==
                        writeToFile$1032,12,"cmax_spec.cm"$(FH$1032,24,"cmax_spec.cm"$, `$1033,11,"cmax_spec.cm"$ "}\n"$1033,11,"cmax_spec.cm"$  ')
                    :
                        O$1036,5,"cmax_spec.cm"$





| VarDecl$1037,5,"cmax_spec.cm"$@<< I$1037,15,"cmax_spec.cm"$,*>,_,_,_,_,_>N$1037,31,"cmax_spec.cm"$ :
    LET O$1038,9,"cmax_spec.cm"$ ==
        writeToFile$1038,12,"cmax_spec.cm"$(FH$1038,24,"cmax_spec.cm"$, `$1038,28,"cmax_spec.cm"$ "#undef "$1039,9,"cmax_spec.cm"$ idtos$1039,26,"cmax_spec.cm"$(term$1039,21,"cmax_spec.cm"$(I$1039,19,"cmax_spec.cm"$)) "/* non-synchronizing and strict variable "$1039,32,"cmax_spec.cm"$ "access */\n"$1040,60,"cmax_spec.cm"$ "#define mxs_"$1041,9,"cmax_spec.cm"$ idtos$1041,31,"cmax_spec.cm"$(term$1041,26,"cmax_spec.cm"$(I$1041,24,"cmax_spec.cm"$)) "(f,l,a) (!eq("$1041,37,"cmax_spec.cm"$ idtos$1041,70,"cmax_spec.cm"$(varPtrId$1041,53,"cmax_spec.cm"$(term$1041,64,"cmax_spec.cm"$(I$1041,62,"cmax_spec.cm"$))) "(a),nil()) ? ( (Variable*)mxi_etop(f,l,"$1042,26,"cmax_spec.cm"$ idtos$1043,43,"cmax_spec.cm"$(varPtrId$1043,26,"cmax_spec.cm"$(term$1043,37,"cmax_spec.cm"$(I$1043,35,"cmax_spec.cm"$))) "(a) ) ) -> value : nil() )\n"$1043,49,"cmax_spec.cm"$ "#define "$1044,9,"cmax_spec.cm"$ idtos$1044,27,"cmax_spec.cm"$(term$1044,22,"cmax_spec.cm"$(I$1044,20,"cmax_spec.cm"$)) "(a) (mxs_"$1044,33,"cmax_spec.cm"$ idtos$1044,52,"cmax_spec.cm"$(term$1044,47,"cmax_spec.cm"$(I$1044,45,"cmax_spec.cm"$)) "(__FILE__,__LINE__,a))\n"$1045,31,"cmax_spec.cm"$  ')
    :
        O$1047,5,"cmax_spec.cm"$

| AssnDef$1048,5,"cmax_spec.cm"$@< ID$1048,14,"cmax_spec.cm"$, SIDL$1048,18,"cmax_spec.cm"$, NL$1048,24,"cmax_spec.cm"$, AL$1048,28,"cmax_spec.cm"$>N$1048,32,"cmax_spec.cm"$ :
    LET O$1052,9,"cmax_spec.cm"$ ==
        gen_C_all$1052,12,"cmax_spec.cm"$(AL$1052,22,"cmax_spec.cm"$, FH$1052,26,"cmax_spec.cm"$)
    :
        LET O$1056,9,"cmax_spec.cm"$ ==
            writeToFile$1056,12,"cmax_spec.cm"$(FH$1056,24,"cmax_spec.cm"$, `$1057,10,"cmax_spec.cm"$ "void "$1057,10,"cmax_spec.cm"$ idToStr$1057,21,"cmax_spec.cm"$(ID$1057,18,"cmax_spec.cm"$) "("$1057,29,"cmax_spec.cm"$ namelist_to_cparlist$1057,33,"cmax_spec.cm"$(term$1057,57,"cmax_spec.cm"$(NL$1057,54,"cmax_spec.cm"$)) ")\n"$1057,63,"cmax_spec.cm"$ "{\n"$1058,10,"cmax_spec.cm"$ assndef_sorttests$1059,10,"cmax_spec.cm"$(N$1059,28,"cmax_spec.cm"$, SIDL$1059,31,"cmax_spec.cm"$, NL$1059,37,"cmax_spec.cm"$)  ')
        :
            LET O$1062,9,"cmax_spec.cm"$ ==
                gen_C_activation_assndef$1062,12,"cmax_spec.cm"$(N$1062,37,"cmax_spec.cm"$, FH$1062,40,"cmax_spec.cm"$)
            :
                LET O$1063,9,"cmax_spec.cm"$ ==
                    writeToFile$1063,12,"cmax_spec.cm"$(FH$1063,24,"cmax_spec.cm"$, "}\n"$1064,10,"cmax_spec.cm"$)
                :
                    O$1066,5,"cmax_spec.cm"$




    ELSE
        true$1068,5,"cmax_spec.cm"$()
FCT assndef_sorttests$1070,5,"cmax_spec.cm"$ ( AssnDef$1070,23,"cmax_spec.cm"$@ A$1070,32,"cmax_spec.cm"$, SortIdList$1070,35,"cmax_spec.cm"$@ SIDL$1070,47,"cmax_spec.cm"$, NameList$1070,53,"cmax_spec.cm"$@ NL$1070,63,"cmax_spec.cm"$ ) String$1070,67,"cmax_spec.cm"$ :
    IF$1071,5,"cmax_spec.cm"$ <>SIDL$1071,9,"cmax_spec.cm"$:
        ""$1071,15,"cmax_spec.cm"$
    ELSE
        assndef_sorttests_sub$1072,8,"cmax_spec.cm"$(A$1072,30,"cmax_spec.cm"$, fst$1072,38,"cmax_spec.cm"$(SIDL$1072,33,"cmax_spec.cm"$), fst$1072,46,"cmax_spec.cm"$(NL$1072,43,"cmax_spec.cm"$))
FCT assndef_sorttests_sub$1074,5,"cmax_spec.cm"$ ( AssnDef$1074,27,"cmax_spec.cm"$@ A$1074,36,"cmax_spec.cm"$, SortId$1074,39,"cmax_spec.cm"$@ SID$1074,47,"cmax_spec.cm"$, Name$1074,52,"cmax_spec.cm"$@ N$1074,58,"cmax_spec.cm"$ ) String$1074,61,"cmax_spec.cm"$ :
    LET H$1075,7,"cmax_spec.cm"$ ==
        `$1075,11,"cmax_spec.cm"$ "ISNIL("$1075,11,"cmax_spec.cm"$ idToStr$1075,22,"cmax_spec.cm"$(N$1075,20,"cmax_spec.cm"$) ") IS("$1075,30,"cmax_spec.cm"$ idToStr$1075,40,"cmax_spec.cm"$(N$1075,38,"cmax_spec.cm"$) ", "$1075,48,"cmax_spec.cm"$ sortid_to_csortid$1076,16,"cmax_spec.cm"$(SID$1076,34,"cmax_spec.cm"$) ", "$1076,39,"cmax_spec.cm"$ idToStr$1077,22,"cmax_spec.cm"$(fst$1077,18,"cmax_spec.cm"$(A$1077,16,"cmax_spec.cm"$)) ")\n"$1077,30,"cmax_spec.cm"$  '
    :
        IF$1078,5,"cmax_spec.cm"$ ! eq$0,0,"?"$[rbroth$1078,10,"cmax_spec.cm"$(SID$1078,6,"cmax_spec.cm"$), nil$1078,17,"cmax_spec.cm"$()]:
            `$1078,25,"cmax_spec.cm"$ H$1078,25,"cmax_spec.cm"$ assndef_sorttests_sub$1078,27,"cmax_spec.cm"$(A$1078,49,"cmax_spec.cm"$, rbroth$1078,56,"cmax_spec.cm"$(SID$1078,52,"cmax_spec.cm"$), rbroth$1078,66,"cmax_spec.cm"$(N$1078,64,"cmax_spec.cm"$))  '
        ELSE
            H$1079,8,"cmax_spec.cm"$

FCT sortid_to_csortid$1081,5,"cmax_spec.cm"$ ( SortId$1081,23,"cmax_spec.cm"$@ SID$1081,31,"cmax_spec.cm"$ ) String$1081,36,"cmax_spec.cm"$ :
    IF$1082,5,"cmax_spec.cm"$ is$1082,6,"cmax_spec.cm"$[SID$1082,9,"cmax_spec.cm"$, _NodeSortId$1082,14,"cmax_spec.cm"$@]:
        `$1082,30,"cmax_spec.cm"$ "_"$1082,30,"cmax_spec.cm"$ idToStr$1082,38,"cmax_spec.cm"$(SID$1082,34,"cmax_spec.cm"$) "_"$1082,46,"cmax_spec.cm"$  '
    ELSE
        `$1083,9,"cmax_spec.cm"$ "_"$1083,9,"cmax_spec.cm"$ idToStr$1083,17,"cmax_spec.cm"$(SID$1083,13,"cmax_spec.cm"$)  '
FCT gen_C_lists$1085,5,"cmax_spec.cm"$ ( Node$1085,18,"cmax_spec.cm"$ N$1085,23,"cmax_spec.cm"$, Int$1085,26,"cmax_spec.cm"$ FH$1085,30,"cmax_spec.cm"$ ) Bool$1085,34,"cmax_spec.cm"$ :
    LET H$1086,7,"cmax_spec.cm"$ ==
        gen_C_all$1086,10,"cmax_spec.cm"$(N$1086,20,"cmax_spec.cm"$, FH$1086,23,"cmax_spec.cm"$)
    :
        IF$1087,5,"cmax_spec.cm"$ <*, N$1087,9,"cmax_spec.cm"$, NEXT$1087,11,"cmax_spec.cm"$,*>:
            gen_C_lists$1088,5,"cmax_spec.cm"$(NEXT$1088,17,"cmax_spec.cm"$, FH$1088,23,"cmax_spec.cm"$)
        ELSE
            H$1090,5,"cmax_spec.cm"$

FCT namelist_to_cparlist$1092,5,"cmax_spec.cm"$ ( NameList$1092,26,"cmax_spec.cm"$ NL$1092,35,"cmax_spec.cm"$ ) String$1092,39,"cmax_spec.cm"$ :
    IF$1093,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1093,9,"cmax_spec.cm"$(NL$1093,6,"cmax_spec.cm"$), 0$1093,21,"cmax_spec.cm"$]:
        " "$1093,24,"cmax_spec.cm"$
    ELSE
        LET FST$1095,10,"cmax_spec.cm"$ ==
            `$1095,16,"cmax_spec.cm"$ "ELEMENT "$1095,16,"cmax_spec.cm"$ idtos$1095,54,"cmax_spec.cm"$(subterm$1095,27,"cmax_spec.cm"$(1$1095,35,"cmax_spec.cm"$, subterm$1095,38,"cmax_spec.cm"$(1$1095,46,"cmax_spec.cm"$, NL$1095,49,"cmax_spec.cm"$)))  '
        :
            IF$1096,8,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1096,12,"cmax_spec.cm"$(NL$1096,9,"cmax_spec.cm"$), 1$1096,24,"cmax_spec.cm"$]:
                FST$1096,27,"cmax_spec.cm"$
            ELSE
                `$1097,12,"cmax_spec.cm"$ FST$1097,12,"cmax_spec.cm"$ ", "$1097,16,"cmax_spec.cm"$ namelist_to_cparlist$1097,21,"cmax_spec.cm"$(back$1097,45,"cmax_spec.cm"$(NL$1097,42,"cmax_spec.cm"$))  '

ATT activation_code_assertion$1103,5,"cmax_spec.cm"$ ( Assertion$1103,32,"cmax_spec.cm"$@ A$1103,43,"cmax_spec.cm"$ ) ActivationCode$1103,46,"cmax_spec.cm"$ :
    LET PC$1104,7,"cmax_spec.cm"$ ==
        AC_Block$1104,11,"cmax_spec.cm"$(Set$1104,20,"cmax_spec.cm"$(), activation_code_assnlist$1104,27,"cmax_spec.cm"$(fst$1104,54,"cmax_spec.cm"$(A$1104,52,"cmax_spec.cm"$)), index$1104,60,"cmax_spec.cm"$(A$1104,66,"cmax_spec.cm"$, _Node$1104,69,"cmax_spec.cm"$))
    :
        appback$1105,3,"cmax_spec.cm"$(ActivationCode$1105,11,"cmax_spec.cm"$(), PC$1105,29,"cmax_spec.cm"$)

ATT activation_code_assndef$1107,5,"cmax_spec.cm"$ ( AssnDef$1107,30,"cmax_spec.cm"$@ AD$1107,39,"cmax_spec.cm"$ ) ActivationCode$1107,43,"cmax_spec.cm"$ :
    LET PC$1108,7,"cmax_spec.cm"$ ==
        AC_Block$1108,11,"cmax_spec.cm"$(Set$1108,20,"cmax_spec.cm"$(), activation_code_assnlist$1108,27,"cmax_spec.cm"$(last$1108,55,"cmax_spec.cm"$(AD$1108,52,"cmax_spec.cm"$)), index$1108,62,"cmax_spec.cm"$(AD$1108,68,"cmax_spec.cm"$, _Node$1108,72,"cmax_spec.cm"$))
    :
        appback$1109,3,"cmax_spec.cm"$(ActivationCode$1109,11,"cmax_spec.cm"$(), PC$1109,29,"cmax_spec.cm"$)

ATT activation_code_assnlist$1111,5,"cmax_spec.cm"$ ( AssnList$1111,31,"cmax_spec.cm"$@ AL$1111,41,"cmax_spec.cm"$ ) ActivationCode$1111,45,"cmax_spec.cm"$ :
    IF$1112,5,"cmax_spec.cm"$ < FSTASSN$1112,7,"cmax_spec.cm"$,*>AL$1112,18,"cmax_spec.cm"$:
        activation_code_assnlist_sub$1113,5,"cmax_spec.cm"$(FSTASSN$1113,34,"cmax_spec.cm"$)
    ELSE
        ActivationCode$1114,8,"cmax_spec.cm"$()
FCT activation_code_assnlist_sub$1116,5,"cmax_spec.cm"$ ( Assn$1116,34,"cmax_spec.cm"$@ A$1116,40,"cmax_spec.cm"$ ) ActivationCode$1116,43,"cmax_spec.cm"$ :
    LET REST$1117,7,"cmax_spec.cm"$ ==
        IF$1118,7,"cmax_spec.cm"$ <*, A$1118,11,"cmax_spec.cm"$, A1$1118,13,"cmax_spec.cm"$,*>:
            activation_code_assnlist_sub$1118,20,"cmax_spec.cm"$(A1$1118,49,"cmax_spec.cm"$)
        ELSE
            ActivationCode$1119,10,"cmax_spec.cm"$()
    :
        LET O$1121,7,"cmax_spec.cm"$ ==
            IF$1122,7,"cmax_spec.cm"$ ! is$1122,9,"cmax_spec.cm"$[activation_code$1122,14,"cmax_spec.cm"$(A$1122,12,"cmax_spec.cm"$), _ActivationCode$1122,31,"cmax_spec.cm"$]:
                debug$1123,7,"cmax_spec.cm"$(`$1123,14,"cmax_spec.cm"$ "activation_code_assnlist_sub: act. code has"$1123,14,"cmax_spec.cm"$ "sort:"$1124,14,"cmax_spec.cm"$ sortof$1124,22,"cmax_spec.cm"$(activation_code$1124,31,"cmax_spec.cm"$(A$1124,29,"cmax_spec.cm"$)) "!\n"$1124,48,"cmax_spec.cm"$  ')
            ELSE
                true$1125,10,"cmax_spec.cm"$()
        :
            LET O$1126,7,"cmax_spec.cm"$ ==
                IF$1127,7,"cmax_spec.cm"$ ! is$1127,9,"cmax_spec.cm"$[REST$1127,12,"cmax_spec.cm"$, _ActivationCode$1127,18,"cmax_spec.cm"$]:
                    debug$1128,7,"cmax_spec.cm"$(`$1128,14,"cmax_spec.cm"$ "activation_code_assnlist_sub: REST has"$1128,14,"cmax_spec.cm"$ "sort:"$1129,14,"cmax_spec.cm"$ sortof$1129,22,"cmax_spec.cm"$(REST$1129,29,"cmax_spec.cm"$) "!\n"$1129,35,"cmax_spec.cm"$  ')
                ELSE
                    true$1130,10,"cmax_spec.cm"$()
            :
                conc$1131,3,"cmax_spec.cm"$(activation_code$1131,10,"cmax_spec.cm"$(A$1131,8,"cmax_spec.cm"$), REST$1131,27,"cmax_spec.cm"$)



ATT activation_statements$1133,5,"cmax_spec.cm"$ ( Constraint$1133,27,"cmax_spec.cm"$@ A$1133,39,"cmax_spec.cm"$ ) ActivationCode$1133,42,"cmax_spec.cm"$ :
    LET NR$1134,7,"cmax_spec.cm"$ ==
        assn_nr$1134,13,"cmax_spec.cm"$(A$1134,11,"cmax_spec.cm"$)
    :
        LET NAMED$1135,7,"cmax_spec.cm"$ ==
            names_in_constraint$1135,14,"cmax_spec.cm"$(A$1135,34,"cmax_spec.cm"$)
        :
            LET STMTS$1136,7,"cmax_spec.cm"$ ==
                ActivationCode$1136,14,"cmax_spec.cm"$()
            :
                LET STMTS$1137,7,"cmax_spec.cm"$ ==
                    appback$1137,14,"cmax_spec.cm"$(STMTS$1137,22,"cmax_spec.cm"$, AC_Stmt$1137,29,"cmax_spec.cm"$(`$1138,6,"cmax_spec.cm"$ "__add_constraint("$1138,6,"cmax_spec.cm"$ idtos$1139,27,"cmax_spec.cm"$(localSolveFctId$1139,9,"cmax_spec.cm"$()) "_"$1139,33,"cmax_spec.cm"$ itos$1139,40,"cmax_spec.cm"$(NR$1139,37,"cmax_spec.cm"$) ", NULL, "$1140,5,"cmax_spec.cm"$ itos$1140,34,"cmax_spec.cm"$(numsubterms$1140,22,"cmax_spec.cm"$(NAMED$1140,16,"cmax_spec.cm"$)) ", "$1140,39,"cmax_spec.cm"$ constr_arglist$1140,44,"cmax_spec.cm"$(NAMED$1140,59,"cmax_spec.cm"$) ");"$1140,66,"cmax_spec.cm"$  '))
                :
                    STMTS$1142,3,"cmax_spec.cm"$




FCT constr_arglist$1144,5,"cmax_spec.cm"$ ( Set$1144,20,"cmax_spec.cm"$ S$1144,24,"cmax_spec.cm"$ ) String$1144,27,"cmax_spec.cm"$ :
    IF$1145,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1145,8,"cmax_spec.cm"$(S$1145,6,"cmax_spec.cm"$), 0$1145,20,"cmax_spec.cm"$]:
        " "$1145,23,"cmax_spec.cm"$
    | eq$0,0,"?"$[numsubterms$1146,8,"cmax_spec.cm"$(S$1146,6,"cmax_spec.cm"$), 1$1146,20,"cmax_spec.cm"$] :
        idtos$1147,19,"cmax_spec.cm"$(subterm$1147,5,"cmax_spec.cm"$(1$1147,13,"cmax_spec.cm"$, S$1147,16,"cmax_spec.cm"$))
    ELSE
        `$1149,6,"cmax_spec.cm"$ idtos$1149,20,"cmax_spec.cm"$(subterm$1149,6,"cmax_spec.cm"$(1$1149,14,"cmax_spec.cm"$, S$1149,17,"cmax_spec.cm"$)) ", "$1149,26,"cmax_spec.cm"$ constr_arglist$1149,31,"cmax_spec.cm"$(back$1149,48,"cmax_spec.cm"$(S$1149,46,"cmax_spec.cm"$))  '
ATT activation_code$1151,5,"cmax_spec.cm"$ ( Assn$1151,22,"cmax_spec.cm"$@ A$1151,28,"cmax_spec.cm"$ ) ActivationCode$1151,31,"cmax_spec.cm"$ :
    IF$1152,5,"cmax_spec.cm"$ PatternAssn$1152,6,"cmax_spec.cm"$@< P$1152,19,"cmax_spec.cm"$, AL$1152,21,"cmax_spec.cm"$>A$1152,25,"cmax_spec.cm"$:
        LET FN$1153,9,"cmax_spec.cm"$ ==
            free_pattern_names$1153,13,"cmax_spec.cm"$(A$1153,32,"cmax_spec.cm"$)
        :
            LET TN$1154,9,"cmax_spec.cm"$ ==
                tmp_idents$1154,13,"cmax_spec.cm"$(P$1154,24,"cmax_spec.cm"$)
            :
                LET H$1155,9,"cmax_spec.cm"$ ==
                    ActivationCode$1155,12,"cmax_spec.cm"$()
                :
                    appback$1156,5,"cmax_spec.cm"$(H$1156,13,"cmax_spec.cm"$, AC_Block$1156,16,"cmax_spec.cm"$(conc$1156,25,"cmax_spec.cm"$(FN$1156,30,"cmax_spec.cm"$, TN$1156,34,"cmax_spec.cm"$), pattern_code$1157,25,"cmax_spec.cm"$(P$1157,39,"cmax_spec.cm"$, activation_code_assnlist$1157,42,"cmax_spec.cm"$(AL$1157,67,"cmax_spec.cm"$)), index$1158,25,"cmax_spec.cm"$(A$1158,31,"cmax_spec.cm"$, _Node$1158,34,"cmax_spec.cm"$)))



    | IfAssn$1159,6,"cmax_spec.cm"$@< F$1159,14,"cmax_spec.cm"$, AL1$1159,16,"cmax_spec.cm"$, AL2$1159,20,"cmax_spec.cm"$>A$1159,25,"cmax_spec.cm"$ :
        appback$1160,5,"cmax_spec.cm"$(ActivationCode$1160,13,"cmax_spec.cm"$(), AC_Cond$1160,31,"cmax_spec.cm"$(AC_Expr$1160,40,"cmax_spec.cm"$(formula_to_cexpr$1160,48,"cmax_spec.cm"$(F$1160,65,"cmax_spec.cm"$)), activation_code_assnlist$1161,37,"cmax_spec.cm"$(AL1$1161,62,"cmax_spec.cm"$), activation_code_assnlist$1162,37,"cmax_spec.cm"$(AL2$1162,62,"cmax_spec.cm"$), index$1163,37,"cmax_spec.cm"$(A$1163,43,"cmax_spec.cm"$, _Node$1163,46,"cmax_spec.cm"$)))
| LetAssn$1164,6,"cmax_spec.cm"$@< I$1164,15,"cmax_spec.cm"$, E$1164,17,"cmax_spec.cm"$, AL$1164,19,"cmax_spec.cm"$>A$1164,23,"cmax_spec.cm"$ :
    LET PC$1165,9,"cmax_spec.cm"$ ==
        ActivationCode$1165,13,"cmax_spec.cm"$()
    :
        LET PC$1166,9,"cmax_spec.cm"$ ==
            appback$1166,13,"cmax_spec.cm"$(PC$1166,21,"cmax_spec.cm"$, AC_Bind$1166,25,"cmax_spec.cm"$(AC_Ref$1166,34,"cmax_spec.cm"$(idToStr$1166,41,"cmax_spec.cm"$(I$1166,49,"cmax_spec.cm"$)), AC_Expr$1167,33,"cmax_spec.cm"$(expr_to_cexpr$1167,41,"cmax_spec.cm"$(E$1167,55,"cmax_spec.cm"$))))
        :
            LET PC$1168,9,"cmax_spec.cm"$ ==
                conc$1168,13,"cmax_spec.cm"$(PC$1168,18,"cmax_spec.cm"$, activation_code_assnlist$1168,22,"cmax_spec.cm"$(AL$1168,47,"cmax_spec.cm"$))
            :
                appback$1169,5,"cmax_spec.cm"$(ActivationCode$1169,13,"cmax_spec.cm"$(), AC_Block$1169,31,"cmax_spec.cm"$(appback$1169,40,"cmax_spec.cm"$(Set$1169,48,"cmax_spec.cm"$(), term$1169,61,"cmax_spec.cm"$(fst$1169,57,"cmax_spec.cm"$(I$1169,55,"cmax_spec.cm"$))), PC$1170,31,"cmax_spec.cm"$, index$1170,35,"cmax_spec.cm"$(A$1170,41,"cmax_spec.cm"$, _Node$1170,44,"cmax_spec.cm"$)))



| DefAssnAppl$1171,6,"cmax_spec.cm"$@< ID$1171,19,"cmax_spec.cm"$, EL$1171,22,"cmax_spec.cm"$>A$1171,26,"cmax_spec.cm"$ :
    appback$1172,5,"cmax_spec.cm"$(ActivationCode$1172,13,"cmax_spec.cm"$(), AC_Stmt$1173,6,"cmax_spec.cm"$(`$1173,15,"cmax_spec.cm"$ "{extern void "$1173,15,"cmax_spec.cm"$ idToStr$1173,34,"cmax_spec.cm"$(ID$1173,31,"cmax_spec.cm"$) "(); "$1173,42,"cmax_spec.cm"$ idToStr$1174,19,"cmax_spec.cm"$(ID$1174,16,"cmax_spec.cm"$) "("$1174,27,"cmax_spec.cm"$ exprlist_to_carglist$1174,31,"cmax_spec.cm"$(EL$1174,52,"cmax_spec.cm"$) ");}"$1174,56,"cmax_spec.cm"$  '))
| Constraint$1176,6,"cmax_spec.cm"$@ A$1176,18,"cmax_spec.cm"$ :
    activation_statements$1177,5,"cmax_spec.cm"$(A$1177,27,"cmax_spec.cm"$)
    ELSE
        nil$1178,8,"cmax_spec.cm"$()
FCT rest_code$1180,5,"cmax_spec.cm"$ ( Item$1180,15,"cmax_spec.cm"$@ N$1180,21,"cmax_spec.cm"$, ActivationCode$1180,24,"cmax_spec.cm"$ RC$1180,39,"cmax_spec.cm"$ ) ActivationCode$1180,43,"cmax_spec.cm"$ :
    LET N1$1181,7,"cmax_spec.cm"$ ==
        IF$1182,7,"cmax_spec.cm"$ Pattern$1182,8,"cmax_spec.cm"$@<_,ItemList$1182,19,"cmax_spec.cm"$@< FST$1182,29,"cmax_spec.cm"$,*>,_>N$1182,39,"cmax_spec.cm"$:
            FST$1183,7,"cmax_spec.cm"$
        ELSE
            next_rbroth$1185,7,"cmax_spec.cm"$(N$1185,19,"cmax_spec.cm"$)
    :
        IF$1187,5,"cmax_spec.cm"$ ! eq$0,0,"?"$[N1$1187,6,"cmax_spec.cm"$, nil$1187,9,"cmax_spec.cm"$()]:
            pattern_code$1188,5,"cmax_spec.cm"$(N1$1188,18,"cmax_spec.cm"$, RC$1188,22,"cmax_spec.cm"$)
        ELSE
            RC$1190,5,"cmax_spec.cm"$

FCT pattern_code$1192,5,"cmax_spec.cm"$ ( Item$1192,18,"cmax_spec.cm"$@ I$1192,24,"cmax_spec.cm"$, ActivationCode$1192,27,"cmax_spec.cm"$ RC$1192,42,"cmax_spec.cm"$ ) ActivationCode$1192,46,"cmax_spec.cm"$ :
    IF$1193,5,"cmax_spec.cm"$ ! is$1193,7,"cmax_spec.cm"$[fath$1193,11,"cmax_spec.cm"$(I$1193,17,"cmax_spec.cm"$), _ItemList$1193,21,"cmax_spec.cm"$@]:
        LET SP$1194,9,"cmax_spec.cm"$ ==
            son$1194,13,"cmax_spec.cm"$(2$1194,17,"cmax_spec.cm"$, I$1194,20,"cmax_spec.cm"$)
        :
            LET B$1195,9,"cmax_spec.cm"$ ==
                bound_subpattern$1195,12,"cmax_spec.cm"$(I$1195,29,"cmax_spec.cm"$)
            :
                IF$1196,7,"cmax_spec.cm"$ eq$0,0,"?"$[is_bound_item$1196,10,"cmax_spec.cm"$(I$1196,8,"cmax_spec.cm"$), true$1196,24,"cmax_spec.cm"$()]:
                    conc$1197,7,"cmax_spec.cm"$(item_sorttest$1197,12,"cmax_spec.cm"$(I$1197,26,"cmax_spec.cm"$), rest_code$1197,30,"cmax_spec.cm"$(I$1197,40,"cmax_spec.cm"$, RC$1197,43,"cmax_spec.cm"$))
                | ! eq$0,0,"?"$[B$1198,7,"cmax_spec.cm"$, nil$1198,9,"cmax_spec.cm"$()] :
                    LET PC$1199,11,"cmax_spec.cm"$ ==
                        ActivationCode$1199,15,"cmax_spec.cm"$()
                    :
                        LET PC$1200,11,"cmax_spec.cm"$ ==
                            appback$1200,15,"cmax_spec.cm"$(PC$1200,23,"cmax_spec.cm"$, AC_Bind$1200,27,"cmax_spec.cm"$(AC_Ref$1200,35,"cmax_spec.cm"$(item_element$1200,42,"cmax_spec.cm"$(I$1200,55,"cmax_spec.cm"$)), AC_Expr$1201,9,"cmax_spec.cm"$(fath_expr$1202,14,"cmax_spec.cm"$(subpattern_level$1202,24,"cmax_spec.cm"$(B$1202,41,"cmax_spec.cm"$, I$1202,44,"cmax_spec.cm"$), item_element$1202,48,"cmax_spec.cm"$(B$1202,61,"cmax_spec.cm"$)))))
                        :
                            LET PC$1203,11,"cmax_spec.cm"$ ==
                                conc$1203,15,"cmax_spec.cm"$(PC$1203,20,"cmax_spec.cm"$, item_sorttest$1203,24,"cmax_spec.cm"$(I$1203,38,"cmax_spec.cm"$))
                            :
                                conc$1204,7,"cmax_spec.cm"$(PC$1204,12,"cmax_spec.cm"$, rest_code$1204,16,"cmax_spec.cm"$(I$1204,26,"cmax_spec.cm"$, RC$1204,29,"cmax_spec.cm"$))



                ELSE
                    LET M$1206,11,"cmax_spec.cm"$ ==
                        possible_sorts$1206,14,"cmax_spec.cm"$(I$1206,29,"cmax_spec.cm"$)
                    :
                        LET PC$1207,11,"cmax_spec.cm"$ ==
                            ActivationCode$1207,15,"cmax_spec.cm"$()
                        :
                            LET PC$1208,11,"cmax_spec.cm"$ ==
                                appback$1208,15,"cmax_spec.cm"$(PC$1208,23,"cmax_spec.cm"$, AC_For_Sorts$1208,27,"cmax_spec.cm"$(AC_Ref$1208,41,"cmax_spec.cm"$(item_element$1208,48,"cmax_spec.cm"$(I$1208,61,"cmax_spec.cm"$)), M$1208,66,"cmax_spec.cm"$, rest_code$1209,9,"cmax_spec.cm"$(I$1209,19,"cmax_spec.cm"$, RC$1209,22,"cmax_spec.cm"$), index$1209,27,"cmax_spec.cm"$(I$1209,33,"cmax_spec.cm"$, _Node$1209,36,"cmax_spec.cm"$)))
                            :
                                LET O$1210,11,"cmax_spec.cm"$ ==
                                    IF$1211,11,"cmax_spec.cm"$ eq$0,0,"?"$[PC$1211,12,"cmax_spec.cm"$, nil$1211,15,"cmax_spec.cm"$()]:
                                        LET O$1212,15,"cmax_spec.cm"$ ==
                                            debug$1212,18,"cmax_spec.cm"$("pattern_code: top pattern, for sorts:"$1212,24,"cmax_spec.cm"$)
                                        :
                                            outMAXCode$1213,11,"cmax_spec.cm"$(term$1213,24,"cmax_spec.cm"$(I$1213,22,"cmax_spec.cm"$))

                                    ELSE
                                        true$1214,14,"cmax_spec.cm"$()
                                :
                                    PC$1216,7,"cmax_spec.cm"$






    ELSE
        IF$1218,7,"cmax_spec.cm"$ is$1218,8,"cmax_spec.cm"$[I$1218,11,"cmax_spec.cm"$, _Asterisk$1218,14,"cmax_spec.cm"$@]:
            rest_code$1219,7,"cmax_spec.cm"$(I$1219,17,"cmax_spec.cm"$, RC$1219,20,"cmax_spec.cm"$)
        | eq$0,0,"?"$[is_bound_item$1220,9,"cmax_spec.cm"$(I$1220,7,"cmax_spec.cm"$), true$1220,23,"cmax_spec.cm"$()] :
            LET I1$1224,11,"cmax_spec.cm"$ ==
                next_item_no_ast$1224,15,"cmax_spec.cm"$(I$1224,32,"cmax_spec.cm"$)
            :
                IF$1225,9,"cmax_spec.cm"$ ! eq$0,0,"?"$[I1$1225,10,"cmax_spec.cm"$, nil$1225,13,"cmax_spec.cm"$()]:
                    LET PC$1226,13,"cmax_spec.cm"$ ==
                        ActivationCode$1226,17,"cmax_spec.cm"$()
                    :
                        LET PC$1227,13,"cmax_spec.cm"$ ==
                            appback$1227,17,"cmax_spec.cm"$(PC$1227,25,"cmax_spec.cm"$, AC_Test$1227,29,"cmax_spec.cm"$(AC_Expr$1227,37,"cmax_spec.cm"$(`$1227,46,"cmax_spec.cm"$ "eq(fath("$1228,11,"cmax_spec.cm"$ item_element$1228,22,"cmax_spec.cm"$(I$1228,35,"cmax_spec.cm"$) "),"$1228,38,"cmax_spec.cm"$ item_element$1228,55,"cmax_spec.cm"$(fath$1228,50,"cmax_spec.cm"$(fath$1228,45,"cmax_spec.cm"$(I$1228,43,"cmax_spec.cm"$))) ") && "$1228,68,"cmax_spec.cm"$ "bef(after("$1229,11,"cmax_spec.cm"$ item_element$1229,24,"cmax_spec.cm"$(I1$1229,37,"cmax_spec.cm"$) "),after("$1229,41,"cmax_spec.cm"$ item_element$1229,52,"cmax_spec.cm"$(I$1229,65,"cmax_spec.cm"$) "))"$1229,68,"cmax_spec.cm"$  ')))
                        :
                            LET PC$1232,13,"cmax_spec.cm"$ ==
                                conc$1232,42,"cmax_spec.cm"$(conc$1232,22,"cmax_spec.cm"$(PC$1232,17,"cmax_spec.cm"$, item_sorttest$1232,23,"cmax_spec.cm"$(I$1232,37,"cmax_spec.cm"$)), item_boundtest$1232,43,"cmax_spec.cm"$(I$1232,58,"cmax_spec.cm"$))
                            :
                                conc$1233,9,"cmax_spec.cm"$(PC$1233,14,"cmax_spec.cm"$, rest_code$1233,18,"cmax_spec.cm"$(I$1233,28,"cmax_spec.cm"$, RC$1233,31,"cmax_spec.cm"$))



                ELSE
                    LET PC$1235,13,"cmax_spec.cm"$ ==
                        ActivationCode$1235,17,"cmax_spec.cm"$()
                    :
                        LET PC$1236,13,"cmax_spec.cm"$ ==
                            appback$1236,17,"cmax_spec.cm"$(PC$1236,25,"cmax_spec.cm"$, AC_Test$1236,29,"cmax_spec.cm"$(AC_Expr$1236,37,"cmax_spec.cm"$(`$1236,46,"cmax_spec.cm"$ "eq(fath("$1237,11,"cmax_spec.cm"$ item_element$1237,22,"cmax_spec.cm"$(I$1237,35,"cmax_spec.cm"$) "),"$1237,38,"cmax_spec.cm"$ item_element$1237,55,"cmax_spec.cm"$(fath$1237,50,"cmax_spec.cm"$(fath$1237,45,"cmax_spec.cm"$(I$1237,43,"cmax_spec.cm"$))) ")"$1237,68,"cmax_spec.cm"$  ')))
                        :
                            LET PC$1239,13,"cmax_spec.cm"$ ==
                                conc$1239,17,"cmax_spec.cm"$(PC$1239,22,"cmax_spec.cm"$, item_sorttest$1239,26,"cmax_spec.cm"$(I$1239,40,"cmax_spec.cm"$))
                            :
                                conc$1240,9,"cmax_spec.cm"$(conc$1240,14,"cmax_spec.cm"$(PC$1240,19,"cmax_spec.cm"$, rest_code$1240,23,"cmax_spec.cm"$(I$1240,33,"cmax_spec.cm"$, RC$1240,36,"cmax_spec.cm"$)), item_boundtest$1240,42,"cmax_spec.cm"$(I$1240,57,"cmax_spec.cm"$))




        ELSE
            IF$1246,9,"cmax_spec.cm"$ < I$1246,11,"cmax_spec.cm"$,*>:
                LET PC$1247,13,"cmax_spec.cm"$ ==
                    ActivationCode$1247,17,"cmax_spec.cm"$()
                :
                    LET PC$1248,13,"cmax_spec.cm"$ ==
                        appback$1248,17,"cmax_spec.cm"$(PC$1248,25,"cmax_spec.cm"$, AC_Bind$1248,29,"cmax_spec.cm"$(AC_Ref$1248,37,"cmax_spec.cm"$(item_element$1248,44,"cmax_spec.cm"$(I$1248,57,"cmax_spec.cm"$)), AC_Expr$1249,11,"cmax_spec.cm"$(`$1249,20,"cmax_spec.cm"$ "son(1,"$1249,20,"cmax_spec.cm"$ item_element$1249,41,"cmax_spec.cm"$(fath$1249,36,"cmax_spec.cm"$(fath$1249,31,"cmax_spec.cm"$(I$1249,29,"cmax_spec.cm"$))) ")"$1249,54,"cmax_spec.cm"$  ')))
                    :
                        LET PC$1251,13,"cmax_spec.cm"$ ==
                            conc$1251,17,"cmax_spec.cm"$(conc$1251,22,"cmax_spec.cm"$(PC$1251,27,"cmax_spec.cm"$, item_sorttest$1251,31,"cmax_spec.cm"$(I$1251,45,"cmax_spec.cm"$)), item_boundtest2$1251,50,"cmax_spec.cm"$(I$1251,66,"cmax_spec.cm"$))
                        :
                            conc$1252,9,"cmax_spec.cm"$(PC$1252,14,"cmax_spec.cm"$, rest_code$1252,18,"cmax_spec.cm"$(I$1252,28,"cmax_spec.cm"$, RC$1252,31,"cmax_spec.cm"$))



            ELSE
                LET I1$1254,13,"cmax_spec.cm"$ ==
                    lbroth$1254,19,"cmax_spec.cm"$(I$1254,17,"cmax_spec.cm"$)
                :
                    IF$1255,11,"cmax_spec.cm"$ ! is$1255,13,"cmax_spec.cm"$[I1$1255,16,"cmax_spec.cm"$, _Asterisk$1255,20,"cmax_spec.cm"$@]:
                        LET PC$1256,15,"cmax_spec.cm"$ ==
                            ActivationCode$1256,19,"cmax_spec.cm"$()
                        :
                            LET PC$1257,15,"cmax_spec.cm"$ ==
                                appback$1257,19,"cmax_spec.cm"$(PC$1257,27,"cmax_spec.cm"$, AC_Bind$1257,31,"cmax_spec.cm"$(AC_Ref$1257,39,"cmax_spec.cm"$(item_element$1257,46,"cmax_spec.cm"$(I$1257,59,"cmax_spec.cm"$)), AC_Expr$1258,13,"cmax_spec.cm"$(`$1258,22,"cmax_spec.cm"$ "rbroth("$1258,22,"cmax_spec.cm"$ item_element$1258,35,"cmax_spec.cm"$(I1$1258,32,"cmax_spec.cm"$) ")"$1258,48,"cmax_spec.cm"$  ')))
                            :
                                LET PC$1259,15,"cmax_spec.cm"$ ==
                                    conc$1259,19,"cmax_spec.cm"$(conc$1259,24,"cmax_spec.cm"$(PC$1259,29,"cmax_spec.cm"$, item_sorttest$1259,33,"cmax_spec.cm"$(I$1259,47,"cmax_spec.cm"$)), item_boundtest2$1259,52,"cmax_spec.cm"$(I$1259,68,"cmax_spec.cm"$))
                                :
                                    conc$1260,11,"cmax_spec.cm"$(PC$1260,16,"cmax_spec.cm"$, rest_code$1260,20,"cmax_spec.cm"$(I$1260,30,"cmax_spec.cm"$, RC$1260,33,"cmax_spec.cm"$))



                    ELSE
                        LET I2$1262,15,"cmax_spec.cm"$ ==
                            next_item_no_ast$1262,19,"cmax_spec.cm"$(I1$1262,36,"cmax_spec.cm"$)
                        :
                            IF$1263,13,"cmax_spec.cm"$ ! eq$0,0,"?"$[I2$1263,14,"cmax_spec.cm"$, nil$1263,17,"cmax_spec.cm"$()]:
                                LET PC$1264,17,"cmax_spec.cm"$ ==
                                    ActivationCode$1264,21,"cmax_spec.cm"$()
                                :
                                    LET PC$1265,17,"cmax_spec.cm"$ ==
                                        appback$1265,21,"cmax_spec.cm"$(PC$1265,29,"cmax_spec.cm"$, mk_AC_For_Rbroth$1265,33,"cmax_spec.cm"$(I$1265,50,"cmax_spec.cm"$, I2$1265,53,"cmax_spec.cm"$, RC$1265,57,"cmax_spec.cm"$))
                                    :
                                        PC$1266,13,"cmax_spec.cm"$


                            ELSE
                                LET PC$1268,17,"cmax_spec.cm"$ ==
                                    ActivationCode$1268,21,"cmax_spec.cm"$()
                                :
                                    LET PC$1269,17,"cmax_spec.cm"$ ==
                                        appback$1269,21,"cmax_spec.cm"$(PC$1269,29,"cmax_spec.cm"$, mk_AC_For_First$1269,33,"cmax_spec.cm"$(I$1269,49,"cmax_spec.cm"$, RC$1269,52,"cmax_spec.cm"$))
                                    :
                                        PC$1270,13,"cmax_spec.cm"$




FCT mk_AC_For_First$1272,5,"cmax_spec.cm"$ ( Item$1272,21,"cmax_spec.cm"$@ I$1272,27,"cmax_spec.cm"$, ActivationCode$1272,30,"cmax_spec.cm"$ RC$1272,45,"cmax_spec.cm"$ ) AC_For_Rbroths$1272,49,"cmax_spec.cm"$ :
    AC_For_Rbroths$1273,3,"cmax_spec.cm"$(AC_Ref$1273,18,"cmax_spec.cm"$(item_element$1273,25,"cmax_spec.cm"$(I$1273,38,"cmax_spec.cm"$)), AC_Expr$1274,16,"cmax_spec.cm"$(`$1274,25,"cmax_spec.cm"$ "son(1, "$1274,25,"cmax_spec.cm"$ item_element$1274,35,"cmax_spec.cm"$(fath$1274,55,"cmax_spec.cm"$(fath$1274,50,"cmax_spec.cm"$(I$1274,48,"cmax_spec.cm"$))) " )"$1274,60,"cmax_spec.cm"$  '), conc$1275,16,"cmax_spec.cm"$(conc$1275,21,"cmax_spec.cm"$(item_sorttest$1275,26,"cmax_spec.cm"$(I$1275,40,"cmax_spec.cm"$), item_boundtest2$1275,44,"cmax_spec.cm"$(I$1275,60,"cmax_spec.cm"$)), rest_code$1276,21,"cmax_spec.cm"$(I$1276,31,"cmax_spec.cm"$, RC$1276,34,"cmax_spec.cm"$)), index$1277,16,"cmax_spec.cm"$(I$1277,22,"cmax_spec.cm"$, _Node$1277,25,"cmax_spec.cm"$))
FCT mk_AC_For_Rbroth$1279,5,"cmax_spec.cm"$ ( Item$1279,22,"cmax_spec.cm"$@ I$1279,28,"cmax_spec.cm"$, Item$1279,31,"cmax_spec.cm"$@ I2$1279,37,"cmax_spec.cm"$, ActivationCode$1279,41,"cmax_spec.cm"$ RC$1279,56,"cmax_spec.cm"$ ) AC_For_Rbroths$1279,60,"cmax_spec.cm"$ :
    AC_For_Rbroths$1280,3,"cmax_spec.cm"$(AC_Ref$1280,18,"cmax_spec.cm"$(item_element$1280,25,"cmax_spec.cm"$(I$1280,38,"cmax_spec.cm"$)), AC_Expr$1281,17,"cmax_spec.cm"$(`$1281,26,"cmax_spec.cm"$ "rbroth("$1281,26,"cmax_spec.cm"$ item_element$1281,36,"cmax_spec.cm"$(I2$1281,49,"cmax_spec.cm"$) " )"$1281,52,"cmax_spec.cm"$  '), conc$1282,17,"cmax_spec.cm"$(conc$1282,22,"cmax_spec.cm"$(item_sorttest$1282,27,"cmax_spec.cm"$(I$1282,41,"cmax_spec.cm"$), item_boundtest2$1282,45,"cmax_spec.cm"$(I$1282,61,"cmax_spec.cm"$)), rest_code$1283,22,"cmax_spec.cm"$(I$1283,32,"cmax_spec.cm"$, RC$1283,35,"cmax_spec.cm"$)), index$1284,17,"cmax_spec.cm"$(I$1284,23,"cmax_spec.cm"$, _Node$1284,26,"cmax_spec.cm"$))
FCT item_sorttest$1286,5,"cmax_spec.cm"$ ( Item$1286,19,"cmax_spec.cm"$@ I$1286,25,"cmax_spec.cm"$ ) ActivationCode$1286,28,"cmax_spec.cm"$ :
    IF$1287,5,"cmax_spec.cm"$ Pattern$1287,6,"cmax_spec.cm"$@<SortId$1287,15,"cmax_spec.cm"$@ SID$1287,23,"cmax_spec.cm"$,_,_>I$1287,32,"cmax_spec.cm"$:
        LET SORT$1288,9,"cmax_spec.cm"$ ==
            `$1288,16,"cmax_spec.cm"$ "_"$1288,16,"cmax_spec.cm"$ idToStr$1288,24,"cmax_spec.cm"$(SID$1288,20,"cmax_spec.cm"$)  '
        :
            LET SORT$1289,9,"cmax_spec.cm"$ ==
                IF$1289,17,"cmax_spec.cm"$ is$1289,18,"cmax_spec.cm"$[SID$1289,21,"cmax_spec.cm"$, _NodeSortId$1289,26,"cmax_spec.cm"$@]:
                    `$1289,42,"cmax_spec.cm"$ SORT$1289,42,"cmax_spec.cm"$ "_"$1289,47,"cmax_spec.cm"$  '
                ELSE
                    SORT$1289,57,"cmax_spec.cm"$
            :
                LET TEST$1290,9,"cmax_spec.cm"$ ==
                    AC_Test$1290,15,"cmax_spec.cm"$(AC_Expr$1290,24,"cmax_spec.cm"$(`$1291,9,"cmax_spec.cm"$ "is("$1291,9,"cmax_spec.cm"$ item_element$1291,15,"cmax_spec.cm"$(I$1291,28,"cmax_spec.cm"$) ", "$1291,31,"cmax_spec.cm"$ SORT$1291,36,"cmax_spec.cm"$ ")"$1291,41,"cmax_spec.cm"$  '))
                :
                    appback$1292,5,"cmax_spec.cm"$(ActivationCode$1292,13,"cmax_spec.cm"$(), TEST$1292,31,"cmax_spec.cm"$)



    ELSE
        ActivationCode$1293,8,"cmax_spec.cm"$()
FCT item_boundtest$1295,5,"cmax_spec.cm"$ ( Item$1295,20,"cmax_spec.cm"$@ I$1295,26,"cmax_spec.cm"$ ) ActivationCode$1295,29,"cmax_spec.cm"$ :
    LET A$1296,7,"cmax_spec.cm"$ ==
        ActivationCode$1296,10,"cmax_spec.cm"$()
    :
        LET A1$1297,7,"cmax_spec.cm"$ ==
            IF$1297,13,"cmax_spec.cm"$ ItemList$1297,14,"cmax_spec.cm"$@< I$1297,24,"cmax_spec.cm"$,*>:
                appback$1298,13,"cmax_spec.cm"$(A$1298,21,"cmax_spec.cm"$, AC_Test$1299,15,"cmax_spec.cm"$(AC_Expr$1299,24,"cmax_spec.cm"$(`$1299,33,"cmax_spec.cm"$ "eq(lbroth("$1299,33,"cmax_spec.cm"$ item_element$1299,46,"cmax_spec.cm"$(I$1299,59,"cmax_spec.cm"$) "), nil())"$1299,62,"cmax_spec.cm"$  ')))
            ELSE
                A$1300,16,"cmax_spec.cm"$
        :
            conc$1301,3,"cmax_spec.cm"$(A1$1301,8,"cmax_spec.cm"$, item_boundtest2$1301,12,"cmax_spec.cm"$(I$1301,28,"cmax_spec.cm"$))


FCT item_boundtest2$1303,5,"cmax_spec.cm"$ ( Item$1303,21,"cmax_spec.cm"$@ I$1303,27,"cmax_spec.cm"$ ) ActivationCode$1303,30,"cmax_spec.cm"$ :
    LET A$1304,7,"cmax_spec.cm"$ ==
        ActivationCode$1304,10,"cmax_spec.cm"$()
    :
        IF$1305,5,"cmax_spec.cm"$ ItemList$1305,6,"cmax_spec.cm"$@<*, I$1305,18,"cmax_spec.cm"$>:
            appback$1306,5,"cmax_spec.cm"$(A$1306,13,"cmax_spec.cm"$, AC_Test$1306,16,"cmax_spec.cm"$(AC_Expr$1306,25,"cmax_spec.cm"$(`$1306,34,"cmax_spec.cm"$ "eq(rbroth("$1306,34,"cmax_spec.cm"$ item_element$1306,47,"cmax_spec.cm"$(I$1306,60,"cmax_spec.cm"$) "), nil())"$1306,63,"cmax_spec.cm"$  ')))
        ELSE
            A$1307,8,"cmax_spec.cm"$

FCT enclAssertion$1310,5,"cmax_spec.cm"$ ( Node$1310,19,"cmax_spec.cm"$ N$1310,24,"cmax_spec.cm"$ ) Assertion$1310,27,"cmax_spec.cm"$@ :
    IF$1311,5,"cmax_spec.cm"$ Assertion$1311,6,"cmax_spec.cm"$@ N$1311,17,"cmax_spec.cm"$:
        N$1311,20,"cmax_spec.cm"$
    ELSE
        enclAssertion$1312,15,"cmax_spec.cm"$(fath$1312,10,"cmax_spec.cm"$(N$1312,8,"cmax_spec.cm"$))
FCT item_element$1314,5,"cmax_spec.cm"$ ( Item$1314,18,"cmax_spec.cm"$@ I$1314,24,"cmax_spec.cm"$ ) String$1314,27,"cmax_spec.cm"$ :
    IF$1315,5,"cmax_spec.cm"$ Pattern$1315,6,"cmax_spec.cm"$@<_,_,Name$1315,19,"cmax_spec.cm"$@ N$1315,25,"cmax_spec.cm"$>I$1315,28,"cmax_spec.cm"$:
        idtos$1315,44,"cmax_spec.cm"$(term$1315,39,"cmax_spec.cm"$(fst$1315,35,"cmax_spec.cm"$(N$1315,33,"cmax_spec.cm"$)))
    | Pattern$1316,6,"cmax_spec.cm"$@<_,_,Blank$1316,19,"cmax_spec.cm"$@ >I$1316,27,"cmax_spec.cm"$ :
        `$1316,34,"cmax_spec.cm"$ "__tmp_"$1316,34,"cmax_spec.cm"$ itos$1316,59,"cmax_spec.cm"$(index$1316,43,"cmax_spec.cm"$(I$1316,49,"cmax_spec.cm"$, _Node$1316,52,"cmax_spec.cm"$))  '
| Blank$1317,6,"cmax_spec.cm"$@ I$1317,13,"cmax_spec.cm"$ :
    `$1317,34,"cmax_spec.cm"$ "__tmp_"$1317,34,"cmax_spec.cm"$ itos$1317,59,"cmax_spec.cm"$(index$1317,43,"cmax_spec.cm"$(I$1317,49,"cmax_spec.cm"$, _Node$1317,52,"cmax_spec.cm"$))  '
    ELSE
        LET O$1319,9,"cmax_spec.cm"$ ==
            debug$1319,12,"cmax_spec.cm"$("item_element: unknown item:"$1319,18,"cmax_spec.cm"$)
        :
            LET O$1320,9,"cmax_spec.cm"$ ==
                outMAXCode$1320,12,"cmax_spec.cm"$(term$1320,25,"cmax_spec.cm"$(I$1320,23,"cmax_spec.cm"$))
            :
                LET O$1321,9,"cmax_spec.cm"$ ==
                    debug$1321,12,"cmax_spec.cm"$("\n"$1321,18,"cmax_spec.cm"$)
                :
                    nil$1322,5,"cmax_spec.cm"$()



FCT is_bound_item$1324,5,"cmax_spec.cm"$ ( Item$1324,19,"cmax_spec.cm"$@ I$1324,25,"cmax_spec.cm"$ ) Bool$1324,28,"cmax_spec.cm"$ :
    IF$1325,5,"cmax_spec.cm"$ Pattern$1325,6,"cmax_spec.cm"$@<_,_,Name$1325,19,"cmax_spec.cm"$@ N$1325,25,"cmax_spec.cm"$>I$1325,28,"cmax_spec.cm"$:
        iselem$1326,5,"cmax_spec.cm"$(term$1326,18,"cmax_spec.cm"$(fst$1326,14,"cmax_spec.cm"$(N$1326,12,"cmax_spec.cm"$)), bound_names$1326,35,"cmax_spec.cm"$(enclAssn$1326,26,"cmax_spec.cm"$(I$1326,24,"cmax_spec.cm"$)))
    ELSE
        false$1327,8,"cmax_spec.cm"$()
FCT bound_subpattern$1329,5,"cmax_spec.cm"$ ( Pattern$1329,22,"cmax_spec.cm"$@ P$1329,31,"cmax_spec.cm"$ ) Item$1329,34,"cmax_spec.cm"$@ :
    IF$1330,5,"cmax_spec.cm"$ <_,<Item$1330,10,"cmax_spec.cm"$@ FST$1330,17,"cmax_spec.cm"$,*>,_>P$1330,27,"cmax_spec.cm"$:
        bound_subpattern1$1333,5,"cmax_spec.cm"$(FST$1333,23,"cmax_spec.cm"$)
    ELSE
        nil$1334,8,"cmax_spec.cm"$()
FCT bound_subpattern1$1336,5,"cmax_spec.cm"$ ( Item$1336,23,"cmax_spec.cm"$@ I$1336,29,"cmax_spec.cm"$ ) Item$1336,32,"cmax_spec.cm"$@ :
    IF$1337,5,"cmax_spec.cm"$ eq$0,0,"?"$[is_bound_item$1337,8,"cmax_spec.cm"$(I$1337,6,"cmax_spec.cm"$), true$1337,22,"cmax_spec.cm"$()]:
        I$1337,30,"cmax_spec.cm"$
    ELSE
        LET BELOW$1339,9,"cmax_spec.cm"$ ==
            IF$1340,9,"cmax_spec.cm"$ Pattern$1340,10,"cmax_spec.cm"$@<_,<Item$1340,22,"cmax_spec.cm"$@ FST$1340,28,"cmax_spec.cm"$,*>,_>I$1340,38,"cmax_spec.cm"$:
                bound_subpattern1$1340,41,"cmax_spec.cm"$(FST$1340,59,"cmax_spec.cm"$)
            ELSE
                nil$1341,12,"cmax_spec.cm"$()
        :
            IF$1343,7,"cmax_spec.cm"$ ItemList$1343,8,"cmax_spec.cm"$@<*, I$1343,20,"cmax_spec.cm"$, I1$1343,22,"cmax_spec.cm"$,*>:
                LET RIGHT$1344,11,"cmax_spec.cm"$ ==
                    bound_subpattern1$1344,18,"cmax_spec.cm"$(I1$1344,36,"cmax_spec.cm"$)
                :
                    IF$1345,9,"cmax_spec.cm"$ ! eq$0,0,"?"$[RIGHT$1345,10,"cmax_spec.cm"$, nil$1345,16,"cmax_spec.cm"$()]:
                        RIGHT$1345,23,"cmax_spec.cm"$
                    ELSE
                        BELOW$1346,12,"cmax_spec.cm"$

            ELSE
                BELOW$1348,7,"cmax_spec.cm"$

FCT subpattern_level$1350,5,"cmax_spec.cm"$ ( Item$1350,22,"cmax_spec.cm"$@ I1$1350,28,"cmax_spec.cm"$, Item$1350,32,"cmax_spec.cm"$@ I2$1350,38,"cmax_spec.cm"$ ) Int$1350,42,"cmax_spec.cm"$ :
    IF$1351,5,"cmax_spec.cm"$ eq$0,0,"?"$[I1$1351,6,"cmax_spec.cm"$, I2$1351,9,"cmax_spec.cm"$]:
        0$1351,13,"cmax_spec.cm"$
    ELSE
        succ$1352,43,"cmax_spec.cm"$(subpattern_level$1352,8,"cmax_spec.cm"$(fath$1352,33,"cmax_spec.cm"$(fath$1352,28,"cmax_spec.cm"$(I1$1352,25,"cmax_spec.cm"$)), I2$1352,39,"cmax_spec.cm"$))
FCT possible_sorts$1354,5,"cmax_spec.cm"$ ( Item$1354,20,"cmax_spec.cm"$@ I$1354,26,"cmax_spec.cm"$ ) SortIdList$1354,29,"cmax_spec.cm"$ :
    IF$1355,5,"cmax_spec.cm"$ Pattern$1355,6,"cmax_spec.cm"$@<SortId$1355,15,"cmax_spec.cm"$@ SID$1355,23,"cmax_spec.cm"$,_,_>I$1355,32,"cmax_spec.cm"$:
        appback$1356,5,"cmax_spec.cm"$(SortIdList$1356,13,"cmax_spec.cm"$(), term$1356,31,"cmax_spec.cm"$(SID$1356,27,"cmax_spec.cm"$))
    ELSE
        appback$1358,5,"cmax_spec.cm"$(SortIdList$1358,13,"cmax_spec.cm"$(), TermSortId$1358,27,"cmax_spec.cm"$(strtoid$1358,38,"cmax_spec.cm"$("Node"$1358,46,"cmax_spec.cm"$), 0$1358,55,"cmax_spec.cm"$, 0$1358,58,"cmax_spec.cm"$, "?"$1358,61,"cmax_spec.cm"$))
FCT next_rbroth$1360,5,"cmax_spec.cm"$ ( Node$1360,17,"cmax_spec.cm"$ N$1360,22,"cmax_spec.cm"$ ) Node$1360,25,"cmax_spec.cm"$ :
    IF$1361,5,"cmax_spec.cm"$ ItemList$1361,6,"cmax_spec.cm"$@<*, N$1361,19,"cmax_spec.cm"$, N1$1361,21,"cmax_spec.cm"$,*>:
        N1$1361,28,"cmax_spec.cm"$
    | <_,ItemList$1362,8,"cmax_spec.cm"$@<*, N$1362,20,"cmax_spec.cm"$>,_>N1$1362,26,"cmax_spec.cm"$ :
        next_rbroth$1362,30,"cmax_spec.cm"$(N1$1362,42,"cmax_spec.cm"$)
    ELSE
        nil$1363,8,"cmax_spec.cm"$()
FCT next_item_no_ast$1365,5,"cmax_spec.cm"$ ( Item$1365,22,"cmax_spec.cm"$@ I$1365,28,"cmax_spec.cm"$ ) Item$1365,31,"cmax_spec.cm"$@ :
    IF$1366,5,"cmax_spec.cm"$ ItemList$1366,6,"cmax_spec.cm"$@<*, I1$1366,19,"cmax_spec.cm"$, I$1366,22,"cmax_spec.cm"$,*>:
        IF$1367,7,"cmax_spec.cm"$ Asterisk$1367,8,"cmax_spec.cm"$@ I1$1367,18,"cmax_spec.cm"$:
            next_item_no_ast$1367,22,"cmax_spec.cm"$(I1$1367,39,"cmax_spec.cm"$)
        ELSE
            I1$1368,10,"cmax_spec.cm"$
    ELSE
        nil$1369,8,"cmax_spec.cm"$()
FCT fath_expr$1371,5,"cmax_spec.cm"$ ( Int$1371,15,"cmax_spec.cm"$ N$1371,19,"cmax_spec.cm"$, String$1371,22,"cmax_spec.cm"$ S$1371,29,"cmax_spec.cm"$ ) String$1371,32,"cmax_spec.cm"$ :
    IF$1372,5,"cmax_spec.cm"$ eq$0,0,"?"$[N$1372,6,"cmax_spec.cm"$, 0$1372,8,"cmax_spec.cm"$]:
        S$1372,11,"cmax_spec.cm"$
    ELSE
        `$1373,9,"cmax_spec.cm"$ "fath("$1373,9,"cmax_spec.cm"$ fath_expr$1373,17,"cmax_spec.cm"$(prev$1373,29,"cmax_spec.cm"$(N$1373,27,"cmax_spec.cm"$), S$1373,35,"cmax_spec.cm"$) ")"$1373,38,"cmax_spec.cm"$  '
FCT formula_to_cexpr$1375,5,"cmax_spec.cm"$ ( Formula$1375,22,"cmax_spec.cm"$@ F$1375,31,"cmax_spec.cm"$ ) String$1375,34,"cmax_spec.cm"$ :
    IF$1376,5,"cmax_spec.cm"$ Neg$1376,6,"cmax_spec.cm"$@< F1$1376,11,"cmax_spec.cm"$>F$1376,15,"cmax_spec.cm"$:
        `$1377,6,"cmax_spec.cm"$ "!("$1377,6,"cmax_spec.cm"$ formula_to_cexpr$1377,11,"cmax_spec.cm"$(F1$1377,28,"cmax_spec.cm"$) ")"$1377,32,"cmax_spec.cm"$  '
    | Or$1378,5,"cmax_spec.cm"$@< F1$1378,9,"cmax_spec.cm"$, F2$1378,12,"cmax_spec.cm"$>F$1378,16,"cmax_spec.cm"$ :
        `$1379,6,"cmax_spec.cm"$ "("$1379,6,"cmax_spec.cm"$ formula_to_cexpr$1379,10,"cmax_spec.cm"$(F1$1379,27,"cmax_spec.cm"$) ")||("$1379,31,"cmax_spec.cm"$ formula_to_cexpr$1380,10,"cmax_spec.cm"$(F2$1380,27,"cmax_spec.cm"$) ")"$1380,31,"cmax_spec.cm"$  '
| And$1381,5,"cmax_spec.cm"$@< F1$1381,10,"cmax_spec.cm"$, F2$1381,13,"cmax_spec.cm"$>F$1381,17,"cmax_spec.cm"$ :
    `$1382,6,"cmax_spec.cm"$ "("$1382,6,"cmax_spec.cm"$ formula_to_cexpr$1382,10,"cmax_spec.cm"$(F1$1382,27,"cmax_spec.cm"$) ")&&("$1382,31,"cmax_spec.cm"$ formula_to_cexpr$1383,10,"cmax_spec.cm"$(F2$1383,27,"cmax_spec.cm"$) ")"$1383,31,"cmax_spec.cm"$  '
| Impl$1384,5,"cmax_spec.cm"$@< F1$1384,11,"cmax_spec.cm"$, F2$1384,14,"cmax_spec.cm"$>F$1384,18,"cmax_spec.cm"$ :
    `$1385,6,"cmax_spec.cm"$ "!("$1385,6,"cmax_spec.cm"$ formula_to_cexpr$1385,11,"cmax_spec.cm"$(F1$1385,28,"cmax_spec.cm"$) ")"$1385,32,"cmax_spec.cm"$ " || ("$1385,36,"cmax_spec.cm"$ formula_to_cexpr$1386,10,"cmax_spec.cm"$(subterm$1386,27,"cmax_spec.cm"$(2$1386,35,"cmax_spec.cm"$, F$1386,37,"cmax_spec.cm"$)) ")"$1386,41,"cmax_spec.cm"$  '
| PredAppl$1387,5,"cmax_spec.cm"$@< ID$1387,15,"cmax_spec.cm"$, EL$1387,18,"cmax_spec.cm"$>F$1387,21,"cmax_spec.cm"$ :
    LET ARGS$1388,9,"cmax_spec.cm"$ ==
        exprlist_to_carglist$1388,15,"cmax_spec.cm"$(EL$1388,36,"cmax_spec.cm"$)
    :
        `$1389,6,"cmax_spec.cm"$ idToStr$1389,9,"cmax_spec.cm"$(ID$1389,6,"cmax_spec.cm"$) "("$1389,17,"cmax_spec.cm"$ ARGS$1389,21,"cmax_spec.cm"$ ")"$1389,26,"cmax_spec.cm"$  '

    ELSE
        LET O$1391,9,"cmax_spec.cm"$ ==
            out$1391,12,"cmax_spec.cm"$("internal error in formula_to_cexpr: unknown formula!\n"$1391,16,"cmax_spec.cm"$)
        :
            "<??>"$1392,5,"cmax_spec.cm"$

FCT expr_to_cexpr$1397,5,"cmax_spec.cm"$ ( Expr$1397,19,"cmax_spec.cm"$@ E$1397,25,"cmax_spec.cm"$ ) String$1397,28,"cmax_spec.cm"$ :
    IF$1398,5,"cmax_spec.cm"$ CharConst$1398,6,"cmax_spec.cm"$@< C$1398,17,"cmax_spec.cm"$,*>E$1398,22,"cmax_spec.cm"$:
        `$1398,26,"cmax_spec.cm"$ "'"$1398,26,"cmax_spec.cm"$ ctos$1398,30,"cmax_spec.cm"$(term$1398,37,"cmax_spec.cm"$(C$1398,35,"cmax_spec.cm"$)) "'"$1398,43,"cmax_spec.cm"$  '
    | IntConst$1399,5,"cmax_spec.cm"$@< I$1399,15,"cmax_spec.cm"$,*>E$1399,20,"cmax_spec.cm"$ :
        `$1399,24,"cmax_spec.cm"$ "itoe("$1399,24,"cmax_spec.cm"$ itos$1399,39,"cmax_spec.cm"$(term$1399,34,"cmax_spec.cm"$(I$1399,32,"cmax_spec.cm"$)) ")"$1399,44,"cmax_spec.cm"$  '
| StringConst$1400,5,"cmax_spec.cm"$@< S$1400,18,"cmax_spec.cm"$,*>E$1400,23,"cmax_spec.cm"$ :
    `$1400,27,"cmax_spec.cm"$ "atoe(\""$1400,27,"cmax_spec.cm"$ term$1400,39,"cmax_spec.cm"$(S$1400,37,"cmax_spec.cm"$) "\")"$1400,44,"cmax_spec.cm"$  '
| SortConst$1401,5,"cmax_spec.cm"$@< ID$1401,16,"cmax_spec.cm"$,*>E$1401,22,"cmax_spec.cm"$ :
    LET R$1402,9,"cmax_spec.cm"$ ==
        `$1402,13,"cmax_spec.cm"$ "_"$1402,13,"cmax_spec.cm"$ idToStr$1402,20,"cmax_spec.cm"$(ID$1402,17,"cmax_spec.cm"$)  '
    :
        IF$1403,7,"cmax_spec.cm"$ is$1403,8,"cmax_spec.cm"$[ID$1403,11,"cmax_spec.cm"$, _NodeSortId$1403,15,"cmax_spec.cm"$@]:
            `$1403,31,"cmax_spec.cm"$ R$1403,31,"cmax_spec.cm"$ "_"$1403,33,"cmax_spec.cm"$  '
        ELSE
            R$1403,43,"cmax_spec.cm"$

| Name$1404,5,"cmax_spec.cm"$@< ID$1404,11,"cmax_spec.cm"$,*>E$1404,17,"cmax_spec.cm"$ :
    idToStr$1404,22,"cmax_spec.cm"$(E$1404,20,"cmax_spec.cm"$)
| FuncAppl$1405,5,"cmax_spec.cm"$@< ID$1405,15,"cmax_spec.cm"$, EL$1405,18,"cmax_spec.cm"$>E$1405,22,"cmax_spec.cm"$ :
    LET H$1406,9,"cmax_spec.cm"$ ==
        IF$1406,14,"cmax_spec.cm"$ eq$0,0,"?"$[is_external_fuat$1406,15,"cmax_spec.cm"$(ID$1406,32,"cmax_spec.cm"$), true$1406,36,"cmax_spec.cm"$()] || is$1406,46,"cmax_spec.cm"$[Decl$1406,52,"cmax_spec.cm"$(ID$1406,49,"cmax_spec.cm"$), _Production$1406,58,"cmax_spec.cm"$@]:
            true$1406,73,"cmax_spec.cm"$()
        ELSE
            false$1407,17,"cmax_spec.cm"$()
    :
        LET FID$1409,9,"cmax_spec.cm"$ ==
            IF$1409,16,"cmax_spec.cm"$ eq$0,0,"?"$[H$1409,17,"cmax_spec.cm"$, true$1409,19,"cmax_spec.cm"$()]:
                idToStr$1409,30,"cmax_spec.cm"$(ID$1409,27,"cmax_spec.cm"$)
            ELSE
                IF$1411,18,"cmax_spec.cm"$ eq$0,0,"?"$[is_predefined_func$1411,19,"cmax_spec.cm"$(ID$1411,38,"cmax_spec.cm"$), false$1411,42,"cmax_spec.cm"$()]:
                    `$1411,52,"cmax_spec.cm"$ "mxs_"$1411,52,"cmax_spec.cm"$ idToStr$1411,62,"cmax_spec.cm"$(ID$1411,59,"cmax_spec.cm"$)  '
                ELSE
                    `$1412,22,"cmax_spec.cm"$ "mxi_"$1412,22,"cmax_spec.cm"$ idToStr$1412,32,"cmax_spec.cm"$(ID$1412,29,"cmax_spec.cm"$)  '
        :
            LET SCP$1413,9,"cmax_spec.cm"$ ==
                IF$1413,16,"cmax_spec.cm"$ eq$0,0,"?"$[H$1413,17,"cmax_spec.cm"$, false$1413,19,"cmax_spec.cm"$()]:
                    `$1413,29,"cmax_spec.cm"$ "\""$1413,29,"cmax_spec.cm"$ inputFileName$1413,34,"cmax_spec.cm"$() "\", "$1413,50,"cmax_spec.cm"$ itos$1413,70,"cmax_spec.cm"$(lineOfId$1413,57,"cmax_spec.cm"$(ID$1413,66,"cmax_spec.cm"$))  '
                ELSE
                    " "$1414,19,"cmax_spec.cm"$
            :
                LET SCP$1415,9,"cmax_spec.cm"$ ==
                    IF$1415,16,"cmax_spec.cm"$ ! eq$0,0,"?"$[0$1415,17,"cmax_spec.cm"$, numsons$1415,22,"cmax_spec.cm"$(EL$1415,19,"cmax_spec.cm"$)] && eq$0,0,"?"$[H$1415,33,"cmax_spec.cm"$, false$1415,35,"cmax_spec.cm"$()]:
                        `$1415,45,"cmax_spec.cm"$ SCP$1415,45,"cmax_spec.cm"$ ", "$1415,49,"cmax_spec.cm"$  '
                    ELSE
                        SCP$1415,60,"cmax_spec.cm"$
                :
                    LET ARGS$1416,9,"cmax_spec.cm"$ ==
                        exprlist_to_carglist$1416,15,"cmax_spec.cm"$(EL$1416,36,"cmax_spec.cm"$)
                    :
                        `$1417,6,"cmax_spec.cm"$ FID$1417,6,"cmax_spec.cm"$ "("$1417,10,"cmax_spec.cm"$ SCP$1417,14,"cmax_spec.cm"$ ARGS$1417,19,"cmax_spec.cm"$ ")"$1417,24,"cmax_spec.cm"$  '





    ELSE
        LET O$1419,9,"cmax_spec.cm"$ ==
            out$1419,12,"cmax_spec.cm"$("internal error in expr_to_cexpr: unsupported type of Expr!\n"$1419,16,"cmax_spec.cm"$)
        :
            "<??>"$1420,5,"cmax_spec.cm"$

ATT is_external_fuat$1422,5,"cmax_spec.cm"$ ( ApplId$1422,23,"cmax_spec.cm"$@ ID$1422,31,"cmax_spec.cm"$ ) Bool$1422,35,"cmax_spec.cm"$ :
    LET S$1424,7,"cmax_spec.cm"$ ==
        idToStr$1424,13,"cmax_spec.cm"$(ID$1424,10,"cmax_spec.cm"$)
    :
        IF$1425,5,"cmax_spec.cm"$ eq$0,0,"?"$[S$1425,6,"cmax_spec.cm"$, "nil"$1425,8,"cmax_spec.cm"$] || eq$0,0,"?"$[S$1425,17,"cmax_spec.cm"$, "true"$1425,19,"cmax_spec.cm"$] || eq$0,0,"?"$[S$1425,29,"cmax_spec.cm"$, "false"$1425,31,"cmax_spec.cm"$] || eq$0,0,"?"$[S$1425,42,"cmax_spec.cm"$, "root"$1425,44,"cmax_spec.cm"$] || eq$0,0,"?"$[S$1426,9,"cmax_spec.cm"$, "minimalInt"$1426,11,"cmax_spec.cm"$] || eq$0,0,"?"$[S$1426,27,"cmax_spec.cm"$, "maximalInt"$1426,29,"cmax_spec.cm"$]:
            true$1426,44,"cmax_spec.cm"$()
        ELSE
            LET D$1428,9,"cmax_spec.cm"$ ==
                Decl$1428,15,"cmax_spec.cm"$(ID$1428,12,"cmax_spec.cm"$)
            :
                IF$1429,7,"cmax_spec.cm"$ is$1429,8,"cmax_spec.cm"$[D$1429,11,"cmax_spec.cm"$, _FuncDecl$1429,14,"cmax_spec.cm"$@] || is$1429,29,"cmax_spec.cm"$[D$1429,32,"cmax_spec.cm"$, _AttrDecl$1429,35,"cmax_spec.cm"$@]:
                    IF$1430,9,"cmax_spec.cm"$ eq$0,0,"?"$[is_predefined_decl$1430,10,"cmax_spec.cm"$(D$1430,29,"cmax_spec.cm"$), false$1430,32,"cmax_spec.cm"$()]:
                        true$1430,41,"cmax_spec.cm"$()
                    ELSE
                        false$1430,53,"cmax_spec.cm"$()
                ELSE
                    false$1431,10,"cmax_spec.cm"$()


ATT is_predefined_func$1433,5,"cmax_spec.cm"$ ( ApplId$1433,25,"cmax_spec.cm"$@ ID$1433,33,"cmax_spec.cm"$ ) Bool$1433,37,"cmax_spec.cm"$ :
    is_predefined_decl$1434,3,"cmax_spec.cm"$(Decl$1434,25,"cmax_spec.cm"$(ID$1434,22,"cmax_spec.cm"$))
FCT is_predefined_decl$1436,5,"cmax_spec.cm"$ ( Node$1436,24,"cmax_spec.cm"$ N$1436,29,"cmax_spec.cm"$ ) Bool$1436,32,"cmax_spec.cm"$ :
    IF$1437,5,"cmax_spec.cm"$ eq$0,0,"?"$[fath$1437,8,"cmax_spec.cm"$(N$1437,6,"cmax_spec.cm"$), root$1437,13,"cmax_spec.cm"$()]:
        lesseq$1438,5,"cmax_spec.cm"$(numson$1438,14,"cmax_spec.cm"$(N$1438,12,"cmax_spec.cm"$), 30$1438,22,"cmax_spec.cm"$)
    ELSE
        false$1439,8,"cmax_spec.cm"$()
FCT numson$1441,5,"cmax_spec.cm"$ ( Node$1441,12,"cmax_spec.cm"$ N$1441,17,"cmax_spec.cm"$ ) Int$1441,20,"cmax_spec.cm"$ :
    IF$1442,5,"cmax_spec.cm"$ eq$0,0,"?"$[lbroth$1442,8,"cmax_spec.cm"$(N$1442,6,"cmax_spec.cm"$), nil$1442,15,"cmax_spec.cm"$()]:
        1$1442,22,"cmax_spec.cm"$
    ELSE
        succ$1443,25,"cmax_spec.cm"$(numson$1443,8,"cmax_spec.cm"$(lbroth$1443,17,"cmax_spec.cm"$(N$1443,15,"cmax_spec.cm"$)))
FCT exprlist_to_carglist$1445,5,"cmax_spec.cm"$ ( ExprList$1445,26,"cmax_spec.cm"$@ EL$1445,36,"cmax_spec.cm"$ ) String$1445,40,"cmax_spec.cm"$ :
    IF$1446,5,"cmax_spec.cm"$ < E$1446,7,"cmax_spec.cm"$,*>EL$1446,12,"cmax_spec.cm"$:
        exprlist_to_carglist_sub$1447,5,"cmax_spec.cm"$(E$1447,30,"cmax_spec.cm"$)
    ELSE
        ""$1448,8,"cmax_spec.cm"$
FCT exprlist_to_carglist_sub$1450,5,"cmax_spec.cm"$ ( Expr$1450,30,"cmax_spec.cm"$@ E$1450,36,"cmax_spec.cm"$ ) String$1450,39,"cmax_spec.cm"$ :
    LET H$1451,7,"cmax_spec.cm"$ ==
        expr_to_cexpr$1451,12,"cmax_spec.cm"$(E$1451,10,"cmax_spec.cm"$)
    :
        IF$1452,5,"cmax_spec.cm"$ <*, E$1452,9,"cmax_spec.cm"$>:
            H$1452,13,"cmax_spec.cm"$
        ELSE
            `$1453,9,"cmax_spec.cm"$ H$1453,9,"cmax_spec.cm"$ ", "$1453,11,"cmax_spec.cm"$ exprlist_to_carglist_sub$1453,16,"cmax_spec.cm"$(rbroth$1453,43,"cmax_spec.cm"$(E$1453,41,"cmax_spec.cm"$))  '

FCT gen_C_activation_assertion$1455,5,"cmax_spec.cm"$ ( Assertion$1455,32,"cmax_spec.cm"$@ A$1455,43,"cmax_spec.cm"$, Int$1455,46,"cmax_spec.cm"$ FH$1455,50,"cmax_spec.cm"$ ) Bool$1455,54,"cmax_spec.cm"$ :
    write_ActivationCode$1456,3,"cmax_spec.cm"$(activation_code_assertion$1456,24,"cmax_spec.cm"$(A$1456,50,"cmax_spec.cm"$), FH$1456,54,"cmax_spec.cm"$)
FCT gen_C_activation_assndef$1458,5,"cmax_spec.cm"$ ( AssnDef$1458,30,"cmax_spec.cm"$@ A$1458,39,"cmax_spec.cm"$, Int$1458,42,"cmax_spec.cm"$ FH$1458,46,"cmax_spec.cm"$ ) Bool$1458,50,"cmax_spec.cm"$ :
    write_ActivationCode$1459,3,"cmax_spec.cm"$(activation_code_assndef$1459,24,"cmax_spec.cm"$(A$1459,48,"cmax_spec.cm"$), FH$1459,52,"cmax_spec.cm"$)
FCT write_ActivationCode$1461,5,"cmax_spec.cm"$ ( ActivationCode$1461,26,"cmax_spec.cm"$ PC$1461,41,"cmax_spec.cm"$, Int$1461,45,"cmax_spec.cm"$ FH$1461,49,"cmax_spec.cm"$ ) Bool$1461,53,"cmax_spec.cm"$ :
    write_AC_sub$1462,3,"cmax_spec.cm"$(PC$1462,16,"cmax_spec.cm"$, 0$1462,20,"cmax_spec.cm"$, -1$1462,23,"cmax_spec.cm"$, FH$1462,27,"cmax_spec.cm"$)
FCT write_AC_sub$1464,5,"cmax_spec.cm"$ ( ActivationCode$1464,18,"cmax_spec.cm"$ PC$1464,33,"cmax_spec.cm"$, Int$1464,37,"cmax_spec.cm"$ LEVEL$1464,41,"cmax_spec.cm"$, Int$1464,48,"cmax_spec.cm"$ EXITID$1464,52,"cmax_spec.cm"$, Int$1464,60,"cmax_spec.cm"$ FH$1464,64,"cmax_spec.cm"$ ) Bool$1464,68,"cmax_spec.cm"$ :
    IF$1465,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1465,9,"cmax_spec.cm"$(PC$1465,6,"cmax_spec.cm"$), 0$1465,21,"cmax_spec.cm"$]:
        true$1465,24,"cmax_spec.cm"$()
    ELSE
        LET FRONT$1467,9,"cmax_spec.cm"$ ==
            LET FST$1468,11,"cmax_spec.cm"$ ==
                subterm$1468,16,"cmax_spec.cm"$(1$1468,24,"cmax_spec.cm"$, PC$1468,27,"cmax_spec.cm"$)
            :
                IF$1469,9,"cmax_spec.cm"$ is$1469,10,"cmax_spec.cm"$[FST$1469,13,"cmax_spec.cm"$, _AC_Stmt$1469,18,"cmax_spec.cm"$]:
                    writeToFile$1470,9,"cmax_spec.cm"$(FH$1470,21,"cmax_spec.cm"$, `$1470,26,"cmax_spec.cm"$ "    "$1470,26,"cmax_spec.cm"$ subterm$1470,33,"cmax_spec.cm"$(1$1470,41,"cmax_spec.cm"$, FST$1470,44,"cmax_spec.cm"$) "\n"$1470,49,"cmax_spec.cm"$  ')
                | is$1471,9,"cmax_spec.cm"$[FST$1471,12,"cmax_spec.cm"$, _AC_Bind$1471,17,"cmax_spec.cm"$] :
                    writeToFile$1472,9,"cmax_spec.cm"$(FH$1472,21,"cmax_spec.cm"$, `$1472,26,"cmax_spec.cm"$ "    "$1472,26,"cmax_spec.cm"$ subterm$1472,33,"cmax_spec.cm"$(1$1472,41,"cmax_spec.cm"$, subterm$1472,44,"cmax_spec.cm"$(1$1472,52,"cmax_spec.cm"$, FST$1472,55,"cmax_spec.cm"$)) " = "$1473,29,"cmax_spec.cm"$ subterm$1473,35,"cmax_spec.cm"$(1$1473,43,"cmax_spec.cm"$, subterm$1473,46,"cmax_spec.cm"$(2$1473,54,"cmax_spec.cm"$, FST$1473,57,"cmax_spec.cm"$)) ";\n"$1473,64,"cmax_spec.cm"$  ')
| is$1474,9,"cmax_spec.cm"$[FST$1474,12,"cmax_spec.cm"$, _AC_Test$1474,17,"cmax_spec.cm"$] :
    writeToFile$1475,9,"cmax_spec.cm"$(FH$1475,21,"cmax_spec.cm"$, `$1475,26,"cmax_spec.cm"$ "    if (!("$1475,26,"cmax_spec.cm"$ subterm$1475,39,"cmax_spec.cm"$(1$1475,47,"cmax_spec.cm"$, subterm$1475,50,"cmax_spec.cm"$(1$1475,58,"cmax_spec.cm"$, FST$1475,61,"cmax_spec.cm"$)) ")) "$1475,68,"cmax_spec.cm"$ "goto __END_"$1476,34,"cmax_spec.cm"$ itos$1476,55,"cmax_spec.cm"$(EXITID$1476,48,"cmax_spec.cm"$) ";\n"$1476,60,"cmax_spec.cm"$  ')
| is$1477,9,"cmax_spec.cm"$[FST$1477,12,"cmax_spec.cm"$, _AC_Cond$1477,17,"cmax_spec.cm"$] :
    LET O$1478,13,"cmax_spec.cm"$ ==
        writeToFile$1478,16,"cmax_spec.cm"$(FH$1478,28,"cmax_spec.cm"$, `$1478,33,"cmax_spec.cm"$ "    if ("$1479,13,"cmax_spec.cm"$ subterm$1479,24,"cmax_spec.cm"$(1$1479,32,"cmax_spec.cm"$, subterm$1479,35,"cmax_spec.cm"$(1$1479,43,"cmax_spec.cm"$, FST$1479,46,"cmax_spec.cm"$)) "){\n"$1479,52,"cmax_spec.cm"$  ')
    :
        LET O$1481,13,"cmax_spec.cm"$ ==
            write_AC_sub$1481,16,"cmax_spec.cm"$(subterm$1481,29,"cmax_spec.cm"$(2$1481,37,"cmax_spec.cm"$, FST$1481,40,"cmax_spec.cm"$), succ$1481,52,"cmax_spec.cm"$(LEVEL$1481,46,"cmax_spec.cm"$), subterm$1481,58,"cmax_spec.cm"$(4$1481,66,"cmax_spec.cm"$, FST$1481,69,"cmax_spec.cm"$), FH$1481,75,"cmax_spec.cm"$)
        :
            LET O$1482,13,"cmax_spec.cm"$ ==
                writeToFile$1482,16,"cmax_spec.cm"$(FH$1482,28,"cmax_spec.cm"$, `$1482,33,"cmax_spec.cm"$ "    }\n"$1483,13,"cmax_spec.cm"$ "    else {\n"$1484,13,"cmax_spec.cm"$  ')
            :
                LET O$1486,13,"cmax_spec.cm"$ ==
                    write_AC_sub$1486,16,"cmax_spec.cm"$(subterm$1486,29,"cmax_spec.cm"$(3$1486,37,"cmax_spec.cm"$, FST$1486,40,"cmax_spec.cm"$), succ$1486,52,"cmax_spec.cm"$(LEVEL$1486,46,"cmax_spec.cm"$), subterm$1486,58,"cmax_spec.cm"$(4$1486,66,"cmax_spec.cm"$, FST$1486,69,"cmax_spec.cm"$), FH$1486,75,"cmax_spec.cm"$)
                :
                    LET O$1487,13,"cmax_spec.cm"$ ==
                        writeToFile$1487,16,"cmax_spec.cm"$(FH$1487,28,"cmax_spec.cm"$, `$1487,33,"cmax_spec.cm"$ "    }\n"$1488,13,"cmax_spec.cm"$ "    __END_"$1489,13,"cmax_spec.cm"$ itos$1489,42,"cmax_spec.cm"$(subterm$1489,26,"cmax_spec.cm"$(4$1489,34,"cmax_spec.cm"$, FST$1489,37,"cmax_spec.cm"$)) ": ;\n"$1489,47,"cmax_spec.cm"$  ')
                    :
                        O$1491,9,"cmax_spec.cm"$





| is$1492,9,"cmax_spec.cm"$[FST$1492,12,"cmax_spec.cm"$, _AC_For_Rbroths$1492,17,"cmax_spec.cm"$] :
    LET V$1493,13,"cmax_spec.cm"$ ==
        subterm$1493,16,"cmax_spec.cm"$(1$1493,24,"cmax_spec.cm"$, subterm$1493,27,"cmax_spec.cm"$(1$1493,35,"cmax_spec.cm"$, FST$1493,38,"cmax_spec.cm"$))
    :
        LET O$1494,13,"cmax_spec.cm"$ ==
            writeToFile$1494,16,"cmax_spec.cm"$(FH$1494,28,"cmax_spec.cm"$, `$1494,33,"cmax_spec.cm"$ "for("$1495,13,"cmax_spec.cm"$ V$1495,20,"cmax_spec.cm"$ " = "$1495,22,"cmax_spec.cm"$ subterm$1495,28,"cmax_spec.cm"$(1$1495,36,"cmax_spec.cm"$, subterm$1495,39,"cmax_spec.cm"$(2$1495,47,"cmax_spec.cm"$, FST$1495,50,"cmax_spec.cm"$)) "; !eq(nil(),"$1496,20,"cmax_spec.cm"$ V$1496,35,"cmax_spec.cm"$ "); "$1496,37,"cmax_spec.cm"$ V$1497,15,"cmax_spec.cm"$ " = rbroth("$1497,17,"cmax_spec.cm"$ V$1497,30,"cmax_spec.cm"$ ")) {\n"$1497,32,"cmax_spec.cm"$  ')
        :
            LET O$1499,13,"cmax_spec.cm"$ ==
                write_AC_sub$1499,16,"cmax_spec.cm"$(subterm$1499,29,"cmax_spec.cm"$(3$1499,37,"cmax_spec.cm"$, FST$1499,40,"cmax_spec.cm"$), succ$1499,52,"cmax_spec.cm"$(LEVEL$1499,46,"cmax_spec.cm"$), subterm$1499,58,"cmax_spec.cm"$(4$1499,66,"cmax_spec.cm"$, FST$1499,69,"cmax_spec.cm"$), FH$1499,75,"cmax_spec.cm"$)
            :
                LET O$1500,13,"cmax_spec.cm"$ ==
                    writeToFile$1500,16,"cmax_spec.cm"$(FH$1500,28,"cmax_spec.cm"$, `$1500,32,"cmax_spec.cm"$ "__END_"$1501,13,"cmax_spec.cm"$ itos$1501,38,"cmax_spec.cm"$(subterm$1501,22,"cmax_spec.cm"$(4$1501,30,"cmax_spec.cm"$, FST$1501,33,"cmax_spec.cm"$)) ": ;\n"$1501,43,"cmax_spec.cm"$ "    }\n"$1502,13,"cmax_spec.cm"$  ')
                :
                    O$1504,9,"cmax_spec.cm"$




| is$1505,9,"cmax_spec.cm"$[FST$1505,12,"cmax_spec.cm"$, _AC_For_Sorts$1505,17,"cmax_spec.cm"$] :
    IF$1506,11,"cmax_spec.cm"$ ! eq$0,0,"?"$[1$1506,12,"cmax_spec.cm"$, numsubterms$1506,14,"cmax_spec.cm"$(subterm$1506,26,"cmax_spec.cm"$(2$1506,34,"cmax_spec.cm"$, FST$1506,37,"cmax_spec.cm"$))]:
        LET LI$1507,15,"cmax_spec.cm"$ ==
            itos$1507,25,"cmax_spec.cm"$(LEVEL$1507,19,"cmax_spec.cm"$)
        :
            LET SARRAY$1508,15,"cmax_spec.cm"$ ==
                sortidlist_to_carray$1508,23,"cmax_spec.cm"$(subterm$1508,44,"cmax_spec.cm"$(2$1508,52,"cmax_spec.cm"$, FST$1508,55,"cmax_spec.cm"$))
            :
                LET O$1509,15,"cmax_spec.cm"$ ==
                    writeToFile$1509,18,"cmax_spec.cm"$(FH$1509,30,"cmax_spec.cm"$, `$1510,14,"cmax_spec.cm"$ "    {ELEMENT __sarray_"$1510,14,"cmax_spec.cm"$ LI$1510,39,"cmax_spec.cm"$ "[] = {"$1510,42,"cmax_spec.cm"$ SARRAY$1510,51,"cmax_spec.cm"$ "};\n"$1510,58,"cmax_spec.cm"$ "    ELEMENT __sort_"$1511,14,"cmax_spec.cm"$ LI$1511,36,"cmax_spec.cm"$ ";\n"$1511,39,"cmax_spec.cm"$ "    long __sindex_"$1512,14,"cmax_spec.cm"$ LI$1512,35,"cmax_spec.cm"$ "=0;\n"$1512,38,"cmax_spec.cm"$ "    long __index_"$1513,14,"cmax_spec.cm"$ LI$1513,34,"cmax_spec.cm"$ ";\n"$1513,37,"cmax_spec.cm"$ "    long __number_"$1514,14,"cmax_spec.cm"$ LI$1514,35,"cmax_spec.cm"$ ";\n"$1514,38,"cmax_spec.cm"$ "    for(__sindex_"$1515,14,"cmax_spec.cm"$ LI$1515,34,"cmax_spec.cm"$ "=0; __sindex_"$1515,37,"cmax_spec.cm"$ LI$1515,53,"cmax_spec.cm"$ "<"$1515,56,"cmax_spec.cm"$ itos$1516,50,"cmax_spec.cm"$(numsubterms$1516,21,"cmax_spec.cm"$(subterm$1516,33,"cmax_spec.cm"$(2$1516,41,"cmax_spec.cm"$, FST$1516,44,"cmax_spec.cm"$))) "; __sindex_"$1516,55,"cmax_spec.cm"$ LI$1516,69,"cmax_spec.cm"$ "++){\n"$1516,72,"cmax_spec.cm"$ "    __sort_"$1517,14,"cmax_spec.cm"$ LI$1517,28,"cmax_spec.cm"$ " = __sarray_"$1517,31,"cmax_spec.cm"$ LI$1517,46,"cmax_spec.cm"$ "[__sindex_"$1517,49,"cmax_spec.cm"$ LI$1517,62,"cmax_spec.cm"$ "];\n"$1517,65,"cmax_spec.cm"$ "    __number_"$1518,14,"cmax_spec.cm"$ LI$1518,30,"cmax_spec.cm"$ "=number(__sort_"$1518,33,"cmax_spec.cm"$ itos$1518,57,"cmax_spec.cm"$(LEVEL$1518,51,"cmax_spec.cm"$) ");\n"$1518,62,"cmax_spec.cm"$ "    for(__index_"$1519,14,"cmax_spec.cm"$ LI$1519,33,"cmax_spec.cm"$ "=1; __index_"$1519,36,"cmax_spec.cm"$ LI$1519,51,"cmax_spec.cm"$ "<= __number_"$1519,54,"cmax_spec.cm"$ LI$1519,69,"cmax_spec.cm"$ "; __index_"$1520,21,"cmax_spec.cm"$ LI$1520,34,"cmax_spec.cm"$ "++) {\n"$1520,37,"cmax_spec.cm"$ "    "$1521,14,"cmax_spec.cm"$ subterm$1521,21,"cmax_spec.cm"$(1$1521,29,"cmax_spec.cm"$, subterm$1521,32,"cmax_spec.cm"$(1$1521,40,"cmax_spec.cm"$, FST$1521,43,"cmax_spec.cm"$)) " = element(__index_"$1522,20,"cmax_spec.cm"$ LI$1522,42,"cmax_spec.cm"$ ", __sort_"$1522,45,"cmax_spec.cm"$ LI$1522,57,"cmax_spec.cm"$ ");\n"$1522,60,"cmax_spec.cm"$  ')
                :
                    LET O$1524,15,"cmax_spec.cm"$ ==
                        write_AC_sub$1524,18,"cmax_spec.cm"$(subterm$1524,31,"cmax_spec.cm"$(3$1524,39,"cmax_spec.cm"$, FST$1524,42,"cmax_spec.cm"$), succ$1524,54,"cmax_spec.cm"$(LEVEL$1524,48,"cmax_spec.cm"$), subterm$1524,60,"cmax_spec.cm"$(4$1524,68,"cmax_spec.cm"$, FST$1524,71,"cmax_spec.cm"$), FH$1524,77,"cmax_spec.cm"$)
                    :
                        LET O$1525,15,"cmax_spec.cm"$ ==
                            writeToFile$1525,18,"cmax_spec.cm"$(FH$1525,30,"cmax_spec.cm"$, `$1525,34,"cmax_spec.cm"$ "__END_"$1526,13,"cmax_spec.cm"$ itos$1526,38,"cmax_spec.cm"$(subterm$1526,22,"cmax_spec.cm"$(4$1526,30,"cmax_spec.cm"$, FST$1526,33,"cmax_spec.cm"$)) ": ;\n"$1526,43,"cmax_spec.cm"$ "    }\n"$1527,13,"cmax_spec.cm"$ "    }\n"$1528,13,"cmax_spec.cm"$ "    }\n"$1529,13,"cmax_spec.cm"$  ')
                        :
                            O$1531,11,"cmax_spec.cm"$





    ELSE
        LET LI$1533,15,"cmax_spec.cm"$ ==
            itos$1533,25,"cmax_spec.cm"$(LEVEL$1533,19,"cmax_spec.cm"$)
        :
            LET SARRAY$1534,15,"cmax_spec.cm"$ ==
                sortidlist_to_carray$1534,23,"cmax_spec.cm"$(subterm$1534,44,"cmax_spec.cm"$(2$1534,52,"cmax_spec.cm"$, FST$1534,55,"cmax_spec.cm"$))
            :
                LET O$1535,15,"cmax_spec.cm"$ ==
                    writeToFile$1535,18,"cmax_spec.cm"$(FH$1535,30,"cmax_spec.cm"$, `$1536,14,"cmax_spec.cm"$ "    {long __index_"$1536,14,"cmax_spec.cm"$ LI$1536,35,"cmax_spec.cm"$ ";\n"$1536,38,"cmax_spec.cm"$ "    long __number_"$1537,14,"cmax_spec.cm"$ LI$1537,35,"cmax_spec.cm"$ "=number("$1537,38,"cmax_spec.cm"$ SARRAY$1537,49,"cmax_spec.cm"$ ");\n"$1537,56,"cmax_spec.cm"$ "    for(__index_"$1538,14,"cmax_spec.cm"$ LI$1538,33,"cmax_spec.cm"$ "=1; __index_"$1538,36,"cmax_spec.cm"$ LI$1538,51,"cmax_spec.cm"$ "<= __number_"$1538,54,"cmax_spec.cm"$ LI$1538,69,"cmax_spec.cm"$ "; __index_"$1539,21,"cmax_spec.cm"$ LI$1539,34,"cmax_spec.cm"$ "++) {\n"$1539,37,"cmax_spec.cm"$ "    "$1540,14,"cmax_spec.cm"$ subterm$1540,21,"cmax_spec.cm"$(1$1540,29,"cmax_spec.cm"$, subterm$1540,32,"cmax_spec.cm"$(1$1540,40,"cmax_spec.cm"$, FST$1540,43,"cmax_spec.cm"$)) " = element(__index_"$1541,20,"cmax_spec.cm"$ LI$1541,42,"cmax_spec.cm"$ ", "$1541,45,"cmax_spec.cm"$ SARRAY$1541,50,"cmax_spec.cm"$ ");\n"$1541,57,"cmax_spec.cm"$  ')
                :
                    LET O$1543,15,"cmax_spec.cm"$ ==
                        write_AC_sub$1543,18,"cmax_spec.cm"$(subterm$1543,31,"cmax_spec.cm"$(3$1543,39,"cmax_spec.cm"$, FST$1543,42,"cmax_spec.cm"$), succ$1543,54,"cmax_spec.cm"$(LEVEL$1543,48,"cmax_spec.cm"$), subterm$1543,60,"cmax_spec.cm"$(4$1543,68,"cmax_spec.cm"$, FST$1543,71,"cmax_spec.cm"$), FH$1543,77,"cmax_spec.cm"$)
                    :
                        LET O$1544,15,"cmax_spec.cm"$ ==
                            writeToFile$1544,18,"cmax_spec.cm"$(FH$1544,30,"cmax_spec.cm"$, `$1544,34,"cmax_spec.cm"$ "__END_"$1545,13,"cmax_spec.cm"$ itos$1545,38,"cmax_spec.cm"$(subterm$1545,22,"cmax_spec.cm"$(4$1545,30,"cmax_spec.cm"$, FST$1545,33,"cmax_spec.cm"$)) ": ;\n"$1545,43,"cmax_spec.cm"$ "    }\n"$1546,13,"cmax_spec.cm"$ "    }\n"$1547,13,"cmax_spec.cm"$  ')
                        :
                            O$1549,11,"cmax_spec.cm"$





| is$1550,9,"cmax_spec.cm"$[FST$1550,12,"cmax_spec.cm"$, _AC_Block$1550,17,"cmax_spec.cm"$] :
    LET O$1551,13,"cmax_spec.cm"$ ==
        writeToFile$1551,16,"cmax_spec.cm"$(FH$1551,28,"cmax_spec.cm"$, "{ "$1551,32,"cmax_spec.cm"$)
    :
        LET O$1552,13,"cmax_spec.cm"$ ==
            gen_C_namedecls$1552,16,"cmax_spec.cm"$(subterm$1552,32,"cmax_spec.cm"$(1$1552,40,"cmax_spec.cm"$, FST$1552,43,"cmax_spec.cm"$), FH$1552,49,"cmax_spec.cm"$)
        :
            LET O$1553,13,"cmax_spec.cm"$ ==
                write_AC_sub$1553,16,"cmax_spec.cm"$(subterm$1553,29,"cmax_spec.cm"$(2$1553,37,"cmax_spec.cm"$, FST$1553,40,"cmax_spec.cm"$), succ$1553,52,"cmax_spec.cm"$(LEVEL$1553,46,"cmax_spec.cm"$), subterm$1553,58,"cmax_spec.cm"$(3$1553,66,"cmax_spec.cm"$, FST$1553,69,"cmax_spec.cm"$), FH$1553,75,"cmax_spec.cm"$)
            :
                LET O$1554,13,"cmax_spec.cm"$ ==
                    writeToFile$1554,16,"cmax_spec.cm"$(FH$1554,28,"cmax_spec.cm"$, `$1554,33,"cmax_spec.cm"$ "__END_"$1554,33,"cmax_spec.cm"$ itos$1554,58,"cmax_spec.cm"$(subterm$1554,42,"cmax_spec.cm"$(3$1554,50,"cmax_spec.cm"$, FST$1554,53,"cmax_spec.cm"$)) ": ;\n"$1554,63,"cmax_spec.cm"$  ')
                :
                    LET O$1555,13,"cmax_spec.cm"$ ==
                        writeToFile$1555,16,"cmax_spec.cm"$(FH$1555,28,"cmax_spec.cm"$, "}\n"$1555,32,"cmax_spec.cm"$)
                    :
                        O$1556,9,"cmax_spec.cm"$





                ELSE
                    LET O$1558,13,"cmax_spec.cm"$ ==
                        out$1558,16,"cmax_spec.cm"$("internal error in write_AC_sub: unknown  PC Element!\n"$1558,20,"cmax_spec.cm"$)
                    :
                        LET O$1559,13,"cmax_spec.cm"$ ==
                            out$1559,16,"cmax_spec.cm"$(`$1559,21,"cmax_spec.cm"$ sortof$1559,21,"cmax_spec.cm"$(FST$1559,28,"cmax_spec.cm"$) "\n"$1559,33,"cmax_spec.cm"$  ')
                        :
                            true$1560,9,"cmax_spec.cm"$()



        :
            write_AC_sub$1562,5,"cmax_spec.cm"$(back$1562,21,"cmax_spec.cm"$(PC$1562,18,"cmax_spec.cm"$), LEVEL$1562,27,"cmax_spec.cm"$, EXITID$1562,34,"cmax_spec.cm"$, FH$1562,42,"cmax_spec.cm"$)

FCT sortidlist_to_carray$1564,5,"cmax_spec.cm"$ ( SortIdList$1564,26,"cmax_spec.cm"$ SIDL$1564,37,"cmax_spec.cm"$ ) String$1564,43,"cmax_spec.cm"$ :
    IF$1565,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1565,11,"cmax_spec.cm"$(SIDL$1565,6,"cmax_spec.cm"$), 0$1565,23,"cmax_spec.cm"$]:
        ""$1565,26,"cmax_spec.cm"$
    ELSE
        LET FST$1567,9,"cmax_spec.cm"$ ==
            `$1567,15,"cmax_spec.cm"$ "_"$1567,15,"cmax_spec.cm"$ idtos$1567,49,"cmax_spec.cm"$(subterm$1567,19,"cmax_spec.cm"$(1$1567,27,"cmax_spec.cm"$, subterm$1567,31,"cmax_spec.cm"$(1$1567,39,"cmax_spec.cm"$, SIDL$1567,42,"cmax_spec.cm"$)))  '
        :
            LET FST1$1568,9,"cmax_spec.cm"$ ==
                IF$1568,17,"cmax_spec.cm"$ is$1568,18,"cmax_spec.cm"$[subterm$1568,21,"cmax_spec.cm"$(1$1568,29,"cmax_spec.cm"$, SIDL$1568,32,"cmax_spec.cm"$), _NodeSortId$1568,40,"cmax_spec.cm"$]:
                    `$1568,55,"cmax_spec.cm"$ FST$1568,55,"cmax_spec.cm"$ "_"$1568,59,"cmax_spec.cm"$  '
                ELSE
                    FST$1568,70,"cmax_spec.cm"$
            :
                IF$1569,7,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1569,13,"cmax_spec.cm"$(SIDL$1569,8,"cmax_spec.cm"$), 1$1569,25,"cmax_spec.cm"$]:
                    FST1$1570,7,"cmax_spec.cm"$
                ELSE
                    `$1572,8,"cmax_spec.cm"$ FST1$1572,8,"cmax_spec.cm"$ ","$1572,13,"cmax_spec.cm"$ sortidlist_to_carray$1572,17,"cmax_spec.cm"$(back$1572,43,"cmax_spec.cm"$(SIDL$1572,38,"cmax_spec.cm"$))  '


FCT gen_C_define_list$1574,5,"cmax_spec.cm"$ ( Set$1574,23,"cmax_spec.cm"$ NL$1574,27,"cmax_spec.cm"$, String$1574,31,"cmax_spec.cm"$ ARRAY$1574,38,"cmax_spec.cm"$, Int$1574,45,"cmax_spec.cm"$ I$1574,49,"cmax_spec.cm"$, Int$1574,52,"cmax_spec.cm"$ FH$1574,56,"cmax_spec.cm"$ ) Bool$1574,60,"cmax_spec.cm"$ :
    IF$1575,5,"cmax_spec.cm"$ eq$0,0,"?"$[less$1575,6,"cmax_spec.cm"$(I$1575,11,"cmax_spec.cm"$, numsubterms$1575,17,"cmax_spec.cm"$(NL$1575,14,"cmax_spec.cm"$)), true$1575,30,"cmax_spec.cm"$()]:
        LET ELEM$1576,9,"cmax_spec.cm"$ ==
            subterm$1576,15,"cmax_spec.cm"$(succ$1576,25,"cmax_spec.cm"$(I$1576,23,"cmax_spec.cm"$), NL$1576,31,"cmax_spec.cm"$)
        :
            LET O$1577,9,"cmax_spec.cm"$ ==
                writeToFile$1577,12,"cmax_spec.cm"$(FH$1577,24,"cmax_spec.cm"$, `$1577,29,"cmax_spec.cm"$ "#define "$1577,29,"cmax_spec.cm"$ idtos$1577,45,"cmax_spec.cm"$(ELEM$1577,40,"cmax_spec.cm"$) " "$1577,52,"cmax_spec.cm"$ ARRAY$1578,29,"cmax_spec.cm"$ "["$1578,35,"cmax_spec.cm"$ itos$1578,41,"cmax_spec.cm"$(I$1578,39,"cmax_spec.cm"$) "]\n"$1578,46,"cmax_spec.cm"$  ')
            :
                gen_C_define_list$1579,5,"cmax_spec.cm"$(NL$1579,23,"cmax_spec.cm"$, ARRAY$1579,27,"cmax_spec.cm"$, succ$1579,36,"cmax_spec.cm"$(I$1579,34,"cmax_spec.cm"$), FH$1579,42,"cmax_spec.cm"$)


    ELSE
        true$1580,8,"cmax_spec.cm"$()
FCT gen_C_undef_list$1582,5,"cmax_spec.cm"$ ( Set$1582,23,"cmax_spec.cm"$ NL$1582,27,"cmax_spec.cm"$, Int$1582,31,"cmax_spec.cm"$ I$1582,35,"cmax_spec.cm"$, Int$1582,38,"cmax_spec.cm"$ FH$1582,42,"cmax_spec.cm"$ ) Bool$1582,46,"cmax_spec.cm"$ :
    IF$1583,5,"cmax_spec.cm"$ eq$0,0,"?"$[less$1583,6,"cmax_spec.cm"$(I$1583,11,"cmax_spec.cm"$, numsubterms$1583,17,"cmax_spec.cm"$(NL$1583,14,"cmax_spec.cm"$)), true$1583,30,"cmax_spec.cm"$()]:
        LET ELEM$1584,9,"cmax_spec.cm"$ ==
            subterm$1584,15,"cmax_spec.cm"$(succ$1584,25,"cmax_spec.cm"$(I$1584,23,"cmax_spec.cm"$), NL$1584,31,"cmax_spec.cm"$)
        :
            LET O$1585,9,"cmax_spec.cm"$ ==
                writeToFile$1585,12,"cmax_spec.cm"$(FH$1585,24,"cmax_spec.cm"$, `$1585,29,"cmax_spec.cm"$ "#undef "$1585,29,"cmax_spec.cm"$ idtos$1585,44,"cmax_spec.cm"$(ELEM$1585,39,"cmax_spec.cm"$) "\n"$1585,50,"cmax_spec.cm"$  ')
            :
                gen_C_undef_list$1586,5,"cmax_spec.cm"$(NL$1586,22,"cmax_spec.cm"$, succ$1586,28,"cmax_spec.cm"$(I$1586,26,"cmax_spec.cm"$), FH$1586,34,"cmax_spec.cm"$)


    ELSE
        true$1587,8,"cmax_spec.cm"$()
FCT gen_C_namedecls$1589,5,"cmax_spec.cm"$ ( Set$1589,22,"cmax_spec.cm"$ S$1589,26,"cmax_spec.cm"$, Int$1589,29,"cmax_spec.cm"$ FH$1589,33,"cmax_spec.cm"$ ) Bool$1589,37,"cmax_spec.cm"$ :
    IF$1590,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1590,8,"cmax_spec.cm"$(S$1590,6,"cmax_spec.cm"$), 0$1590,20,"cmax_spec.cm"$]:
        writeToFile$1591,5,"cmax_spec.cm"$(FH$1591,17,"cmax_spec.cm"$, "\n"$1591,21,"cmax_spec.cm"$)
    ELSE
        LET O$1593,9,"cmax_spec.cm"$ ==
            writeToFile$1593,12,"cmax_spec.cm"$(FH$1593,24,"cmax_spec.cm"$, "ELEMENT "$1593,28,"cmax_spec.cm"$)
        :
            gen_C_namedecls_sub$1594,5,"cmax_spec.cm"$(S$1594,25,"cmax_spec.cm"$, FH$1594,28,"cmax_spec.cm"$)

FCT gen_C_namedecls_sub$1596,5,"cmax_spec.cm"$ ( Set$1596,26,"cmax_spec.cm"$ S$1596,30,"cmax_spec.cm"$, Int$1596,33,"cmax_spec.cm"$ FH$1596,37,"cmax_spec.cm"$ ) Bool$1596,41,"cmax_spec.cm"$ :
    LET O$1597,7,"cmax_spec.cm"$ ==
        writeToFile$1597,10,"cmax_spec.cm"$(FH$1597,22,"cmax_spec.cm"$, idtos$1597,40,"cmax_spec.cm"$(subterm$1597,26,"cmax_spec.cm"$(1$1597,34,"cmax_spec.cm"$, S$1597,37,"cmax_spec.cm"$)))
    :
        IF$1598,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1598,8,"cmax_spec.cm"$(S$1598,6,"cmax_spec.cm"$), 1$1598,20,"cmax_spec.cm"$]:
            writeToFile$1599,5,"cmax_spec.cm"$(FH$1599,17,"cmax_spec.cm"$, ";\n"$1599,21,"cmax_spec.cm"$)
        ELSE
            LET O$1601,9,"cmax_spec.cm"$ ==
                writeToFile$1601,12,"cmax_spec.cm"$(FH$1601,24,"cmax_spec.cm"$, ","$1601,28,"cmax_spec.cm"$)
            :
                gen_C_namedecls_sub$1602,5,"cmax_spec.cm"$(back$1602,27,"cmax_spec.cm"$(S$1602,25,"cmax_spec.cm"$), FH$1602,33,"cmax_spec.cm"$)


FCT gen_C_constraint$1604,5,"cmax_spec.cm"$ ( Constraint$1604,23,"cmax_spec.cm"$@ CE$1604,35,"cmax_spec.cm"$, Int$1604,39,"cmax_spec.cm"$ FH$1604,43,"cmax_spec.cm"$, String$1604,47,"cmax_spec.cm"$ PF$1604,54,"cmax_spec.cm"$ ) Bool$1604,58,"cmax_spec.cm"$ :
    IF$1605,5,"cmax_spec.cm"$ CondConstr$1605,6,"cmax_spec.cm"$@< F$1605,18,"cmax_spec.cm"$, C$1605,20,"cmax_spec.cm"$>CE$1605,23,"cmax_spec.cm"$:
        LET O$1606,9,"cmax_spec.cm"$ ==
            writeToFile$1606,12,"cmax_spec.cm"$(FH$1606,24,"cmax_spec.cm"$, `$1606,29,"cmax_spec.cm"$ PF$1606,29,"cmax_spec.cm"$ "if ("$1606,32,"cmax_spec.cm"$ formula_to_cexpr$1606,39,"cmax_spec.cm"$(F$1606,56,"cmax_spec.cm"$) ") {\n"$1606,59,"cmax_spec.cm"$  ')
        :
            LET O$1607,9,"cmax_spec.cm"$ ==
                gen_C_constraint$1607,12,"cmax_spec.cm"$(C$1607,30,"cmax_spec.cm"$, FH$1607,33,"cmax_spec.cm"$, `$1607,38,"cmax_spec.cm"$ PF$1607,38,"cmax_spec.cm"$ "  "$1607,41,"cmax_spec.cm"$  ')
            :
                LET O$1608,9,"cmax_spec.cm"$ ==
                    writeToFile$1608,12,"cmax_spec.cm"$(FH$1608,24,"cmax_spec.cm"$, `$1608,29,"cmax_spec.cm"$ PF$1608,29,"cmax_spec.cm"$ "}\n"$1608,32,"cmax_spec.cm"$  ')
                :
                    O$1609,5,"cmax_spec.cm"$



    | BasicConstr$1610,5,"cmax_spec.cm"$@< E$1610,18,"cmax_spec.cm"$,<< I$1610,22,"cmax_spec.cm"$,*>ID$1610,27,"cmax_spec.cm"$, EL$1610,30,"cmax_spec.cm"$>VE$1610,34,"cmax_spec.cm"$>CE$1610,38,"cmax_spec.cm"$ :
        LET LATT$1611,9,"cmax_spec.cm"$ ==
            Decl$1611,31,"cmax_spec.cm"$(son$1611,15,"cmax_spec.cm"$(4$1611,19,"cmax_spec.cm"$, Decl$1611,25,"cmax_spec.cm"$(ID$1611,22,"cmax_spec.cm"$)))
        :
            LET O$1612,9,"cmax_spec.cm"$ ==
                IF$1613,9,"cmax_spec.cm"$ eq$0,0,"?"$[LATT$1613,10,"cmax_spec.cm"$, nil$1613,15,"cmax_spec.cm"$()]:
                    LET O$1614,13,"cmax_spec.cm"$ ==
                        outMAXCode$1614,16,"cmax_spec.cm"$(term$1614,35,"cmax_spec.cm"$(Decl$1614,30,"cmax_spec.cm"$(ID$1614,27,"cmax_spec.cm"$)))
                    :
                        LET O$1614,46,"cmax_spec.cm"$ ==
                            debug$1614,49,"cmax_spec.cm"$("\n"$1614,55,"cmax_spec.cm"$)
                        :
                            LET O$1615,13,"cmax_spec.cm"$ ==
                                outMAXCode$1615,16,"cmax_spec.cm"$(term$1615,43,"cmax_spec.cm"$(son$1615,27,"cmax_spec.cm"$(4$1615,31,"cmax_spec.cm"$, Decl$1615,37,"cmax_spec.cm"$(ID$1615,34,"cmax_spec.cm"$))))
                            :
                                LET O$1615,54,"cmax_spec.cm"$ ==
                                    debug$1615,57,"cmax_spec.cm"$("\n"$1615,63,"cmax_spec.cm"$)
                                :
                                    true$1616,9,"cmax_spec.cm"$()




                ELSE
                    true$1617,12,"cmax_spec.cm"$()
            :
                LET USER_DEF_UPDATECODE$1618,9,"cmax_spec.cm"$ ==
                    IF$1619,9,"cmax_spec.cm"$ LeqConstr$1619,10,"cmax_spec.cm"$@ CE$1619,21,"cmax_spec.cm"$:
                        `$1619,26,"cmax_spec.cm"$ idtos1$1619,51,"cmax_spec.cm"$(lattice_leq_update$1619,26,"cmax_spec.cm"$(LATT$1619,45,"cmax_spec.cm"$)) "(__e, __vptr)"$1619,58,"cmax_spec.cm"$  '
                    ELSE
                        `$1620,26,"cmax_spec.cm"$ idtos1$1620,51,"cmax_spec.cm"$(lattice_geq_update$1620,26,"cmax_spec.cm"$(LATT$1620,45,"cmax_spec.cm"$)) "(__e, __vptr)"$1620,58,"cmax_spec.cm"$  '
                :
                    LET UPDATECODE$1622,9,"cmax_spec.cm"$ ==
                        IF$1623,9,"cmax_spec.cm"$ ! eq$0,0,"?"$[USER_DEF_UPDATECODE$1623,10,"cmax_spec.cm"$, nil$1623,30,"cmax_spec.cm"$()]:
                            USER_DEF_UPDATECODE$1624,9,"cmax_spec.cm"$
                        ELSE
                            LET TEST$1626,13,"cmax_spec.cm"$ ==
                                IF$1627,13,"cmax_spec.cm"$ LeqConstr$1627,14,"cmax_spec.cm"$@ CE$1627,25,"cmax_spec.cm"$:
                                    `$1628,14,"cmax_spec.cm"$ "!eq("$1628,14,"cmax_spec.cm"$ idtos$1628,39,"cmax_spec.cm"$(lattice_leq$1628,21,"cmax_spec.cm"$(LATT$1628,33,"cmax_spec.cm"$)) "(__e,__v),true())"$1628,45,"cmax_spec.cm"$  '
                                ELSE
                                    `$1630,14,"cmax_spec.cm"$ "!eq("$1630,14,"cmax_spec.cm"$ idtos$1630,39,"cmax_spec.cm"$(lattice_leq$1630,21,"cmax_spec.cm"$(LATT$1630,33,"cmax_spec.cm"$)) "(__v,__e),true())"$1630,45,"cmax_spec.cm"$  '
                            :
                                LET OP$1632,13,"cmax_spec.cm"$ ==
                                    IF$1633,13,"cmax_spec.cm"$ LeqConstr$1633,14,"cmax_spec.cm"$@ CE$1633,25,"cmax_spec.cm"$:
                                        `$1633,30,"cmax_spec.cm"$ idtos$1633,49,"cmax_spec.cm"$(lattice_join$1633,30,"cmax_spec.cm"$(LATT$1633,43,"cmax_spec.cm"$)) "(__e,__v)"$1633,55,"cmax_spec.cm"$  '
                                    ELSE
                                        `$1634,30,"cmax_spec.cm"$ idtos$1634,49,"cmax_spec.cm"$(lattice_meet$1634,30,"cmax_spec.cm"$(LATT$1634,43,"cmax_spec.cm"$)) "(__e,__v)"$1634,55,"cmax_spec.cm"$  '
                                :
                                    LET O$1636,13,"cmax_spec.cm"$ ==
                                        IF$1637,13,"cmax_spec.cm"$ eq$0,0,"?"$[OP$1637,14,"cmax_spec.cm"$, nil$1637,17,"cmax_spec.cm"$()]:
                                            LET O$1638,17,"cmax_spec.cm"$ ==
                                                debug$1638,20,"cmax_spec.cm"$("gen_C_constraint: OP is nil\n"$1638,26,"cmax_spec.cm"$)
                                            :
                                                O$1638,60,"cmax_spec.cm"$

                                        ELSE
                                            true$1639,16,"cmax_spec.cm"$()
                                    :
                                        LET O$1641,13,"cmax_spec.cm"$ ==
                                            IF$1642,13,"cmax_spec.cm"$ eq$0,0,"?"$[TEST$1642,14,"cmax_spec.cm"$, nil$1642,19,"cmax_spec.cm"$()]:
                                                LET O$1643,17,"cmax_spec.cm"$ ==
                                                    debug$1643,20,"cmax_spec.cm"$("gen_C_constraint: TEST is nil\n"$1643,26,"cmax_spec.cm"$)
                                                :
                                                    O$1643,62,"cmax_spec.cm"$

                                            ELSE
                                                true$1644,16,"cmax_spec.cm"$()
                                        :
                                            `$1646,10,"cmax_spec.cm"$ PF$1647,9,"cmax_spec.cm"$ "__v= __vptr1 != NULL ? *__vptr1 : nil();\n"$1647,12,"cmax_spec.cm"$ PF$1648,9,"cmax_spec.cm"$ "if (("$1648,12,"cmax_spec.cm"$ TEST$1648,20,"cmax_spec.cm"$ ") && __vptr1 != NULL){ *__vptr1="$1648,25,"cmax_spec.cm"$ OP$1649,54,"cmax_spec.cm"$ "; __update=1; }\n"$1649,57,"cmax_spec.cm"$  '




                    :
                        LET O$1652,9,"cmax_spec.cm"$ ==
                            writeToFile$1652,12,"cmax_spec.cm"$(FH$1652,24,"cmax_spec.cm"$, `$1653,8,"cmax_spec.cm"$ PF$1653,8,"cmax_spec.cm"$ "__e="$1653,11,"cmax_spec.cm"$ expr_to_cexpr$1653,18,"cmax_spec.cm"$(E$1653,32,"cmax_spec.cm"$) ";\n"$1653,35,"cmax_spec.cm"$ PF$1654,8,"cmax_spec.cm"$ "__vptr="$1654,11,"cmax_spec.cm"$ idtos$1654,38,"cmax_spec.cm"$(varPtrId$1654,21,"cmax_spec.cm"$(term$1654,32,"cmax_spec.cm"$(I$1654,30,"cmax_spec.cm"$))) "("$1654,44,"cmax_spec.cm"$ exprlist_to_carglist$1655,37,"cmax_spec.cm"$(EL$1655,58,"cmax_spec.cm"$) ");\n"$1655,62,"cmax_spec.cm"$ PF$1656,8,"cmax_spec.cm"$ "__vptr1= !eq(__vptr, nil()) ? etop(__vptr) : NULL; \n"$1656,11,"cmax_spec.cm"$ UPDATECODE$1657,8,"cmax_spec.cm"$  ')
                        :
                            O$1659,5,"cmax_spec.cm"$





    ELSE
        out$1661,5,"cmax_spec.cm"$(`$1661,10,"cmax_spec.cm"$ "gen_C_ConstrExpr: unknown constraint "$1661,10,"cmax_spec.cm"$ sortof$1661,50,"cmax_spec.cm"$(CE$1661,57,"cmax_spec.cm"$) "!\n"$1661,61,"cmax_spec.cm"$  ')
FCT gen_C_constraint_sub$1663,6,"cmax_spec.cm"$ ( Constraint$1663,27,"cmax_spec.cm"$@ CE$1663,39,"cmax_spec.cm"$, Int$1663,43,"cmax_spec.cm"$ FH$1663,47,"cmax_spec.cm"$, String$1663,52,"cmax_spec.cm"$ PF$1663,59,"cmax_spec.cm"$ ) Bool$1663,63,"cmax_spec.cm"$ :
    LET O$1664,7,"cmax_spec.cm"$ ==
        gen_C_constraint$1664,10,"cmax_spec.cm"$(CE$1664,27,"cmax_spec.cm"$, FH$1664,31,"cmax_spec.cm"$, PF$1664,35,"cmax_spec.cm"$)
    :
        IF$1665,5,"cmax_spec.cm"$ ! eq$0,0,"?"$[rbroth$1665,10,"cmax_spec.cm"$(CE$1665,7,"cmax_spec.cm"$), nil$1665,19,"cmax_spec.cm"$()]:
            gen_C_constraint_sub$1666,5,"cmax_spec.cm"$(rbroth$1666,29,"cmax_spec.cm"$(CE$1666,26,"cmax_spec.cm"$), FH$1666,37,"cmax_spec.cm"$, PF$1666,42,"cmax_spec.cm"$)
        ELSE
            O$1667,9,"cmax_spec.cm"$

FCT gen_C_call_funcs$1669,5,"cmax_spec.cm"$ ( Int$1669,22,"cmax_spec.cm"$ FH$1669,26,"cmax_spec.cm"$, String$1669,30,"cmax_spec.cm"$ FNAME$1669,37,"cmax_spec.cm"$, Int$1669,44,"cmax_spec.cm"$ NR$1669,48,"cmax_spec.cm"$, Int$1669,52,"cmax_spec.cm"$ I$1669,56,"cmax_spec.cm"$ ) Bool$1669,59,"cmax_spec.cm"$ :
    IF$1670,5,"cmax_spec.cm"$ eq$0,0,"?"$[lesseq$1670,6,"cmax_spec.cm"$(I$1670,13,"cmax_spec.cm"$, NR$1670,16,"cmax_spec.cm"$), true$1670,20,"cmax_spec.cm"$()]:
        LET O$1671,9,"cmax_spec.cm"$ ==
            writeToFile$1671,12,"cmax_spec.cm"$(FH$1671,24,"cmax_spec.cm"$, `$1671,29,"cmax_spec.cm"$ "    "$1671,29,"cmax_spec.cm"$ FNAME$1671,36,"cmax_spec.cm"$ "_"$1671,42,"cmax_spec.cm"$ itos$1671,48,"cmax_spec.cm"$(I$1671,46,"cmax_spec.cm"$) "();\n"$1671,53,"cmax_spec.cm"$  ')
        :
            gen_C_call_funcs$1672,5,"cmax_spec.cm"$(FH$1672,22,"cmax_spec.cm"$, FNAME$1672,26,"cmax_spec.cm"$, NR$1672,33,"cmax_spec.cm"$, succ$1672,39,"cmax_spec.cm"$(I$1672,37,"cmax_spec.cm"$))

    ELSE
        true$1674,5,"cmax_spec.cm"$()
ATT CodeGenCtrl$1680,5,"cmax_spec.cm"$ ( Specification$1680,18,"cmax_spec.cm"$@ S$1680,33,"cmax_spec.cm"$ ) Bool$1680,36,"cmax_spec.cm"$ :
    LET O1$1681,7,"cmax_spec.cm"$ ==
        outputMAXFile$1681,11,"cmax_spec.cm"$(root$1681,25,"cmax_spec.cm"$())
    :
        codeGenCtrlSub$1682,3,"cmax_spec.cm"$(fst$1682,20,"cmax_spec.cm"$(S$1682,18,"cmax_spec.cm"$))

FCT codeGenCtrlSub$1684,5,"cmax_spec.cm"$ ( GlobalDecl$1684,20,"cmax_spec.cm"$@ GD$1684,32,"cmax_spec.cm"$ ) Bool$1684,36,"cmax_spec.cm"$ :
    IF$1685,5,"cmax_spec.cm"$ Structure$1685,6,"cmax_spec.cm"$@ GD$1685,17,"cmax_spec.cm"$:
        LET H$1686,9,"cmax_spec.cm"$ ==
            outputCFile$1686,12,"cmax_spec.cm"$(GD$1686,25,"cmax_spec.cm"$)
        :
            codeGenCtrlSub$1687,5,"cmax_spec.cm"$(rbroth$1687,24,"cmax_spec.cm"$(GD$1687,21,"cmax_spec.cm"$))

    ELSE
        codeGenCtrlSub$1689,5,"cmax_spec.cm"$(rbroth$1689,24,"cmax_spec.cm"$(GD$1689,21,"cmax_spec.cm"$))
FCT outputMAXFile$1691,5,"cmax_spec.cm"$ ( Node$1691,20,"cmax_spec.cm"$ N$1691,25,"cmax_spec.cm"$ ) Bool$1691,28,"cmax_spec.cm"$ :
    IF$1692,5,"cmax_spec.cm"$ eq$0,0,"?"$[checkOption$1692,6,"cmax_spec.cm"$("nocode"$1692,18,"cmax_spec.cm"$), false$1692,28,"cmax_spec.cm"$()]:
        LET FILENAME$1693,9,"cmax_spec.cm"$ ==
            `$1693,22,"cmax_spec.cm"$ inputFilePath$1693,22,"cmax_spec.cm"$() "/"$1693,38,"cmax_spec.cm"$ maxSpecId$1693,42,"cmax_spec.cm"$() ".m"$1693,54,"cmax_spec.cm"$  '
        :
            LET HANDLE$1694,9,"cmax_spec.cm"$ ==
                openFile$1694,19,"cmax_spec.cm"$(FILENAME$1694,28,"cmax_spec.cm"$, "w"$1694,38,"cmax_spec.cm"$)
            :
                IF$1695,7,"cmax_spec.cm"$ eq$0,0,"?"$[greatereq$1695,8,"cmax_spec.cm"$(HANDLE$1695,18,"cmax_spec.cm"$, 0$1695,26,"cmax_spec.cm"$), true$1695,29,"cmax_spec.cm"$()]:
                    LET H$1696,11,"cmax_spec.cm"$ ==
                        LET O$1697,13,"cmax_spec.cm"$ ==
                            IF$1697,18,"cmax_spec.cm"$ eq$0,0,"?"$[checkOption$1697,19,"cmax_spec.cm"$("nosrcpos"$1697,31,"cmax_spec.cm"$), true$1697,43,"cmax_spec.cm"$()]:
                                true$1697,51,"cmax_spec.cm"$()
                            ELSE
                                writeToFile$1698,21,"cmax_spec.cm"$(HANDLE$1698,33,"cmax_spec.cm"$, `$1698,42,"cmax_spec.cm"$ "#line 1 \""$1698,42,"cmax_spec.cm"$ inputFileName$1698,55,"cmax_spec.cm"$() "\"\n"$1699,42,"cmax_spec.cm"$  ')
                        :
                            LET MAXCODE$1701,13,"cmax_spec.cm"$ ==
                                remove_predecls$1701,24,"cmax_spec.cm"$(genMAXCode$1701,47,"cmax_spec.cm"$(root$1701,40,"cmax_spec.cm"$()))
                            :
                                outputMAXCode$1702,9,"cmax_spec.cm"$(MAXCODE$1702,23,"cmax_spec.cm"$, ""$1702,32,"cmax_spec.cm"$, HANDLE$1702,36,"cmax_spec.cm"$)


                    :
                        LET H$1704,11,"cmax_spec.cm"$ ==
                            closeFile$1704,14,"cmax_spec.cm"$(HANDLE$1704,24,"cmax_spec.cm"$)
                        :
                            info$1705,7,"cmax_spec.cm"$(`$1705,13,"cmax_spec.cm"$ "File "$1705,13,"cmax_spec.cm"$ FILENAME$1705,21,"cmax_spec.cm"$ " written.\n"$1705,30,"cmax_spec.cm"$  ')


                ELSE
                    out$1707,7,"cmax_spec.cm"$(`$1707,12,"cmax_spec.cm"$ "error: cannot write file "$1707,12,"cmax_spec.cm"$ FILENAME$1707,40,"cmax_spec.cm"$ "!\n"$1707,49,"cmax_spec.cm"$  ')


    ELSE
        true$1709,5,"cmax_spec.cm"$()
FCT remove_predecls$1711,5,"cmax_spec.cm"$ ( Specification$1711,21,"cmax_spec.cm"$ S$1711,35,"cmax_spec.cm"$ ) Specification$1711,38,"cmax_spec.cm"$ :
    remove_predecls_sub$1712,3,"cmax_spec.cm"$(S$1712,23,"cmax_spec.cm"$, 30$1712,26,"cmax_spec.cm"$)
FCT remove_predecls_sub$1714,5,"cmax_spec.cm"$ ( Specification$1714,25,"cmax_spec.cm"$ S$1714,39,"cmax_spec.cm"$, Int$1714,42,"cmax_spec.cm"$ NR$1714,46,"cmax_spec.cm"$ ) Specification$1714,50,"cmax_spec.cm"$ :
    IF$1715,5,"cmax_spec.cm"$ eq$0,0,"?"$[NR$1715,6,"cmax_spec.cm"$, 0$1715,9,"cmax_spec.cm"$]:
        S$1715,12,"cmax_spec.cm"$
    ELSE
        remove_predecls_sub$1716,8,"cmax_spec.cm"$(back$1716,30,"cmax_spec.cm"$(S$1716,28,"cmax_spec.cm"$), prev$1716,39,"cmax_spec.cm"$(NR$1716,36,"cmax_spec.cm"$))
FCT outMAXCode$1718,5,"cmax_spec.cm"$ ( Term$1718,16,"cmax_spec.cm"$ T$1718,21,"cmax_spec.cm"$ ) Bool$1718,24,"cmax_spec.cm"$ :
    IF$1719,5,"cmax_spec.cm"$ eq$0,0,"?"$[checkOption$1719,6,"cmax_spec.cm"$("debug"$1719,18,"cmax_spec.cm"$), true$1719,27,"cmax_spec.cm"$()]:
        outputMAXCode$1720,5,"cmax_spec.cm"$(T$1720,19,"cmax_spec.cm"$, ""$1720,22,"cmax_spec.cm"$, 1$1720,26,"cmax_spec.cm"$)
    ELSE
        true$1722,5,"cmax_spec.cm"$()
FCT outputMAXCode$1724,5,"cmax_spec.cm"$ ( Term$1724,21,"cmax_spec.cm"$ D$1724,26,"cmax_spec.cm"$, String$1724,29,"cmax_spec.cm"$ PF$1724,36,"cmax_spec.cm"$, Int$1724,40,"cmax_spec.cm"$ HANDLE$1724,44,"cmax_spec.cm"$ ) Bool$1724,53,"cmax_spec.cm"$ :
    IF$1727,5,"cmax_spec.cm"$ is$1727,6,"cmax_spec.cm"$[D$1727,9,"cmax_spec.cm"$, _DeclList$1727,12,"cmax_spec.cm"$]:
        IF$1728,7,"cmax_spec.cm"$ ! eq$0,0,"?"$[0$1728,8,"cmax_spec.cm"$, numsubterms$1728,12,"cmax_spec.cm"$(D$1728,10,"cmax_spec.cm"$)]:
            LET O$1729,11,"cmax_spec.cm"$ ==
                outputMAXCode$1729,14,"cmax_spec.cm"$(subterm$1729,29,"cmax_spec.cm"$(1$1729,37,"cmax_spec.cm"$, D$1729,40,"cmax_spec.cm"$), ""$1729,44,"cmax_spec.cm"$, HANDLE$1729,48,"cmax_spec.cm"$)
            :
                outputMAXCode$1730,7,"cmax_spec.cm"$(back$1730,24,"cmax_spec.cm"$(D$1730,22,"cmax_spec.cm"$), ""$1730,30,"cmax_spec.cm"$, HANDLE$1730,34,"cmax_spec.cm"$)

        ELSE
            true$1732,7,"cmax_spec.cm"$()
    | is$1736,5,"cmax_spec.cm"$[D$1736,8,"cmax_spec.cm"$, _PredDecl$1736,11,"cmax_spec.cm"$] :
        LET ID$1737,9,"cmax_spec.cm"$ ==
            subterm$1737,13,"cmax_spec.cm"$(1$1737,21,"cmax_spec.cm"$, D$1737,24,"cmax_spec.cm"$)
        :
            LET SIDL$1738,11,"cmax_spec.cm"$ ==
                subterm$1738,17,"cmax_spec.cm"$(2$1738,25,"cmax_spec.cm"$, D$1738,28,"cmax_spec.cm"$)
            :
                writeToFile$1739,7,"cmax_spec.cm"$(HANDLE$1739,20,"cmax_spec.cm"$, `$1739,29,"cmax_spec.cm"$ "PRD "$1739,29,"cmax_spec.cm"$ codeForIdent$1739,39,"cmax_spec.cm"$(ID$1739,36,"cmax_spec.cm"$) "["$1739,52,"cmax_spec.cm"$ codeForSortIdList$1740,9,"cmax_spec.cm"$(SIDL$1740,27,"cmax_spec.cm"$, ", "$1740,33,"cmax_spec.cm"$) "]\n"$1740,39,"cmax_spec.cm"$  ')


| is$1741,5,"cmax_spec.cm"$[D$1741,8,"cmax_spec.cm"$, _FuncDecl$1741,11,"cmax_spec.cm"$] :
    LET ID$1742,9,"cmax_spec.cm"$ ==
        subterm$1742,13,"cmax_spec.cm"$(1$1742,21,"cmax_spec.cm"$, D$1742,24,"cmax_spec.cm"$)
    :
        LET SIDL$1743,11,"cmax_spec.cm"$ ==
            subterm$1743,17,"cmax_spec.cm"$(2$1743,25,"cmax_spec.cm"$, D$1743,28,"cmax_spec.cm"$)
        :
            LET SID$1744,11,"cmax_spec.cm"$ ==
                subterm$1744,16,"cmax_spec.cm"$(3$1744,24,"cmax_spec.cm"$, D$1744,27,"cmax_spec.cm"$)
            :
                writeToFile$1745,7,"cmax_spec.cm"$(HANDLE$1745,20,"cmax_spec.cm"$, `$1745,29,"cmax_spec.cm"$ "FCT "$1745,29,"cmax_spec.cm"$ codeForIdent$1745,39,"cmax_spec.cm"$(ID$1745,36,"cmax_spec.cm"$) "("$1745,52,"cmax_spec.cm"$ codeForSortIdList$1746,9,"cmax_spec.cm"$(SIDL$1746,27,"cmax_spec.cm"$, ", "$1746,33,"cmax_spec.cm"$) ") "$1746,39,"cmax_spec.cm"$ codeForIdent$1747,13,"cmax_spec.cm"$(SID$1747,9,"cmax_spec.cm"$) "\n"$1747,26,"cmax_spec.cm"$  ')



| is$1748,5,"cmax_spec.cm"$[D$1748,8,"cmax_spec.cm"$, _AttrDecl$1748,11,"cmax_spec.cm"$] :
    LET ID$1749,9,"cmax_spec.cm"$ ==
        subterm$1749,13,"cmax_spec.cm"$(1$1749,21,"cmax_spec.cm"$, D$1749,24,"cmax_spec.cm"$)
    :
        LET SIDL$1750,9,"cmax_spec.cm"$ ==
            subterm$1750,15,"cmax_spec.cm"$(2$1750,23,"cmax_spec.cm"$, D$1750,26,"cmax_spec.cm"$)
        :
            LET SID$1751,9,"cmax_spec.cm"$ ==
                subterm$1751,14,"cmax_spec.cm"$(3$1751,22,"cmax_spec.cm"$, D$1751,25,"cmax_spec.cm"$)
            :
                writeToFile$1752,5,"cmax_spec.cm"$(HANDLE$1752,18,"cmax_spec.cm"$, `$1752,27,"cmax_spec.cm"$ "ATT "$1752,27,"cmax_spec.cm"$ codeForIdent$1752,37,"cmax_spec.cm"$(ID$1752,34,"cmax_spec.cm"$) "("$1752,50,"cmax_spec.cm"$ codeForSortIdList$1753,7,"cmax_spec.cm"$(SIDL$1753,25,"cmax_spec.cm"$, ", "$1753,31,"cmax_spec.cm"$) ") "$1753,37,"cmax_spec.cm"$ codeForIdent$1754,11,"cmax_spec.cm"$(SID$1754,7,"cmax_spec.cm"$) "\n"$1754,24,"cmax_spec.cm"$  ')



| is$1755,5,"cmax_spec.cm"$[D$1755,8,"cmax_spec.cm"$, _Structure$1755,11,"cmax_spec.cm"$] :
    LET ID$1756,9,"cmax_spec.cm"$ ==
        subterm$1756,13,"cmax_spec.cm"$(1$1756,21,"cmax_spec.cm"$, D$1756,24,"cmax_spec.cm"$)
    :
        LET TSID$1757,9,"cmax_spec.cm"$ ==
            subterm$1757,15,"cmax_spec.cm"$(2$1757,23,"cmax_spec.cm"$, D$1757,26,"cmax_spec.cm"$)
        :
            LET LDL$1758,9,"cmax_spec.cm"$ ==
                subterm$1758,14,"cmax_spec.cm"$(3$1758,22,"cmax_spec.cm"$, D$1758,25,"cmax_spec.cm"$)
            :
                LET O1$1759,9,"cmax_spec.cm"$ ==
                    writeToFile$1760,5,"cmax_spec.cm"$(HANDLE$1760,18,"cmax_spec.cm"$, `$1760,27,"cmax_spec.cm"$ "STRUC "$1760,27,"cmax_spec.cm"$ codeForIdent$1760,39,"cmax_spec.cm"$(ID$1760,36,"cmax_spec.cm"$) "["$1760,52,"cmax_spec.cm"$ codeForIdent$1761,12,"cmax_spec.cm"$(TSID$1761,7,"cmax_spec.cm"$) "] {\n"$1761,25,"cmax_spec.cm"$  ')
                :
                    LET O2$1762,9,"cmax_spec.cm"$ ==
                        outputMAXCode$1763,5,"cmax_spec.cm"$(LDL$1763,20,"cmax_spec.cm"$, ""$1763,25,"cmax_spec.cm"$, HANDLE$1763,29,"cmax_spec.cm"$)
                    :
                        writeToFile$1764,5,"cmax_spec.cm"$(HANDLE$1764,18,"cmax_spec.cm"$, "}\n"$1764,26,"cmax_spec.cm"$)





| is$1765,5,"cmax_spec.cm"$[D$1765,8,"cmax_spec.cm"$, _ListProd$1765,11,"cmax_spec.cm"$] :
    LET ID$1766,9,"cmax_spec.cm"$ ==
        subterm$1766,13,"cmax_spec.cm"$(1$1766,21,"cmax_spec.cm"$, D$1766,24,"cmax_spec.cm"$)
    :
        LET SID$1767,9,"cmax_spec.cm"$ ==
            subterm$1767,14,"cmax_spec.cm"$(2$1767,22,"cmax_spec.cm"$, D$1767,25,"cmax_spec.cm"$)
        :
            writeToFile$1768,5,"cmax_spec.cm"$(HANDLE$1768,18,"cmax_spec.cm"$, `$1768,27,"cmax_spec.cm"$ codeForIdent$1768,30,"cmax_spec.cm"$(ID$1768,27,"cmax_spec.cm"$) " * "$1768,43,"cmax_spec.cm"$ codeForIdent$1768,53,"cmax_spec.cm"$(SID$1768,49,"cmax_spec.cm"$) "\n"$1769,17,"cmax_spec.cm"$  ')


| is$1770,5,"cmax_spec.cm"$[D$1770,8,"cmax_spec.cm"$, _TupelProd$1770,11,"cmax_spec.cm"$] :
    LET ID$1771,9,"cmax_spec.cm"$ ==
        subterm$1771,13,"cmax_spec.cm"$(1$1771,21,"cmax_spec.cm"$, D$1771,24,"cmax_spec.cm"$)
    :
        LET SIDL$1772,9,"cmax_spec.cm"$ ==
            subterm$1772,15,"cmax_spec.cm"$(2$1772,23,"cmax_spec.cm"$, D$1772,26,"cmax_spec.cm"$)
        :
            writeToFile$1773,5,"cmax_spec.cm"$(HANDLE$1773,18,"cmax_spec.cm"$, `$1773,27,"cmax_spec.cm"$ codeForIdent$1773,30,"cmax_spec.cm"$(ID$1773,27,"cmax_spec.cm"$) " ( "$1773,43,"cmax_spec.cm"$ codeForSortIdList$1774,7,"cmax_spec.cm"$(SIDL$1774,26,"cmax_spec.cm"$, " "$1774,32,"cmax_spec.cm"$) " )\n"$1774,37,"cmax_spec.cm"$  ')


| is$1775,5,"cmax_spec.cm"$[D$1775,8,"cmax_spec.cm"$, _ClassProd$1775,11,"cmax_spec.cm"$] :
    LET ID$1776,9,"cmax_spec.cm"$ ==
        subterm$1776,13,"cmax_spec.cm"$(1$1776,21,"cmax_spec.cm"$, D$1776,24,"cmax_spec.cm"$)
    :
        LET SIDL$1777,9,"cmax_spec.cm"$ ==
            subterm$1777,15,"cmax_spec.cm"$(2$1777,23,"cmax_spec.cm"$, D$1777,26,"cmax_spec.cm"$)
        :
            writeToFile$1778,5,"cmax_spec.cm"$(HANDLE$1778,18,"cmax_spec.cm"$, `$1778,27,"cmax_spec.cm"$ codeForIdent$1778,30,"cmax_spec.cm"$(ID$1778,27,"cmax_spec.cm"$) " = "$1778,43,"cmax_spec.cm"$ codeForSortIdList$1779,7,"cmax_spec.cm"$(SIDL$1779,26,"cmax_spec.cm"$, "|"$1779,32,"cmax_spec.cm"$) "\n"$1779,37,"cmax_spec.cm"$  ')


| is$1780,5,"cmax_spec.cm"$[D$1780,8,"cmax_spec.cm"$, _PredeclProd$1780,11,"cmax_spec.cm"$] :
    true$1780,26,"cmax_spec.cm"$()
| is$1784,5,"cmax_spec.cm"$[D$1784,8,"cmax_spec.cm"$, _Predicate$1784,11,"cmax_spec.cm"$] :
    LET ID$1785,9,"cmax_spec.cm"$ ==
        subterm$1785,13,"cmax_spec.cm"$(1$1785,21,"cmax_spec.cm"$, D$1785,24,"cmax_spec.cm"$)
    :
        LET SIDL$1786,9,"cmax_spec.cm"$ ==
            subterm$1786,15,"cmax_spec.cm"$(2$1786,23,"cmax_spec.cm"$, D$1786,26,"cmax_spec.cm"$)
        :
            LET NL$1787,9,"cmax_spec.cm"$ ==
                subterm$1787,13,"cmax_spec.cm"$(3$1787,21,"cmax_spec.cm"$, D$1787,24,"cmax_spec.cm"$)
            :
                LET F$1788,9,"cmax_spec.cm"$ ==
                    subterm$1788,12,"cmax_spec.cm"$(4$1788,20,"cmax_spec.cm"$, D$1788,23,"cmax_spec.cm"$)
                :
                    LET O1$1789,9,"cmax_spec.cm"$ ==
                        writeToFile$1789,13,"cmax_spec.cm"$(HANDLE$1789,26,"cmax_spec.cm"$, `$1789,35,"cmax_spec.cm"$ "PRD "$1789,36,"cmax_spec.cm"$ codeForIdent$1789,46,"cmax_spec.cm"$(ID$1789,43,"cmax_spec.cm"$) " [ "$1789,59,"cmax_spec.cm"$ codeForParList$1790,7,"cmax_spec.cm"$(SIDL$1790,22,"cmax_spec.cm"$, NL$1790,28,"cmax_spec.cm"$) " ] :\n"$1790,32,"cmax_spec.cm"$  ')
                    :
                        LET O2$1791,9,"cmax_spec.cm"$ ==
                            outputMAXCode$1791,13,"cmax_spec.cm"$(F$1791,27,"cmax_spec.cm"$, "    "$1791,30,"cmax_spec.cm"$, HANDLE$1791,38,"cmax_spec.cm"$)
                        :
                            writeToFile$1792,5,"cmax_spec.cm"$(HANDLE$1792,17,"cmax_spec.cm"$, "\n"$1792,25,"cmax_spec.cm"$)






| is$1793,5,"cmax_spec.cm"$[D$1793,8,"cmax_spec.cm"$, _Function$1793,11,"cmax_spec.cm"$] :
    LET ID$1794,9,"cmax_spec.cm"$ ==
        subterm$1794,13,"cmax_spec.cm"$(1$1794,21,"cmax_spec.cm"$, D$1794,24,"cmax_spec.cm"$)
    :
        LET SIDL$1795,9,"cmax_spec.cm"$ ==
            subterm$1795,15,"cmax_spec.cm"$(2$1795,23,"cmax_spec.cm"$, D$1795,26,"cmax_spec.cm"$)
        :
            LET NL$1796,9,"cmax_spec.cm"$ ==
                subterm$1796,13,"cmax_spec.cm"$(3$1796,21,"cmax_spec.cm"$, D$1796,24,"cmax_spec.cm"$)
            :
                LET SID$1797,9,"cmax_spec.cm"$ ==
                    subterm$1797,14,"cmax_spec.cm"$(4$1797,22,"cmax_spec.cm"$, D$1797,25,"cmax_spec.cm"$)
                :
                    LET E$1798,9,"cmax_spec.cm"$ ==
                        subterm$1798,12,"cmax_spec.cm"$(5$1798,20,"cmax_spec.cm"$, D$1798,23,"cmax_spec.cm"$)
                    :
                        LET O1$1799,9,"cmax_spec.cm"$ ==
                            writeToFile$1799,13,"cmax_spec.cm"$(HANDLE$1799,26,"cmax_spec.cm"$, `$1799,35,"cmax_spec.cm"$ "FCT "$1799,35,"cmax_spec.cm"$ codeForIdent$1799,45,"cmax_spec.cm"$(ID$1799,42,"cmax_spec.cm"$) " ( "$1799,58,"cmax_spec.cm"$ codeForParList$1800,7,"cmax_spec.cm"$(SIDL$1800,22,"cmax_spec.cm"$, NL$1800,28,"cmax_spec.cm"$) " ) "$1800,32,"cmax_spec.cm"$ codeForIdent$1800,42,"cmax_spec.cm"$(SID$1800,38,"cmax_spec.cm"$) " :\n"$1801,7,"cmax_spec.cm"$  ')
                        :
                            LET O2$1802,9,"cmax_spec.cm"$ ==
                                outputMAXCode$1802,13,"cmax_spec.cm"$(E$1802,27,"cmax_spec.cm"$, "    "$1802,30,"cmax_spec.cm"$, HANDLE$1802,38,"cmax_spec.cm"$)
                            :
                                writeToFile$1803,5,"cmax_spec.cm"$(HANDLE$1803,17,"cmax_spec.cm"$, "\n"$1803,25,"cmax_spec.cm"$)







| is$1804,5,"cmax_spec.cm"$[D$1804,8,"cmax_spec.cm"$, _Attribute$1804,11,"cmax_spec.cm"$] :
    LET ID$1805,9,"cmax_spec.cm"$ ==
        subterm$1805,13,"cmax_spec.cm"$(1$1805,21,"cmax_spec.cm"$, D$1805,24,"cmax_spec.cm"$)
    :
        LET SIDL$1806,9,"cmax_spec.cm"$ ==
            subterm$1806,15,"cmax_spec.cm"$(2$1806,23,"cmax_spec.cm"$, D$1806,26,"cmax_spec.cm"$)
        :
            LET NL$1807,9,"cmax_spec.cm"$ ==
                subterm$1807,13,"cmax_spec.cm"$(3$1807,21,"cmax_spec.cm"$, D$1807,24,"cmax_spec.cm"$)
            :
                LET SID$1808,9,"cmax_spec.cm"$ ==
                    subterm$1808,14,"cmax_spec.cm"$(4$1808,22,"cmax_spec.cm"$, D$1808,25,"cmax_spec.cm"$)
                :
                    LET E$1809,9,"cmax_spec.cm"$ ==
                        subterm$1809,12,"cmax_spec.cm"$(5$1809,20,"cmax_spec.cm"$, D$1809,23,"cmax_spec.cm"$)
                    :
                        LET O1$1810,9,"cmax_spec.cm"$ ==
                            writeToFile$1810,13,"cmax_spec.cm"$(HANDLE$1810,26,"cmax_spec.cm"$, `$1810,35,"cmax_spec.cm"$ "ATT "$1810,35,"cmax_spec.cm"$ codeForIdent$1810,45,"cmax_spec.cm"$(ID$1810,42,"cmax_spec.cm"$) " ( "$1810,58,"cmax_spec.cm"$ codeForParList$1811,7,"cmax_spec.cm"$(SIDL$1811,22,"cmax_spec.cm"$, NL$1811,28,"cmax_spec.cm"$) " ) "$1811,32,"cmax_spec.cm"$ codeForIdent$1811,42,"cmax_spec.cm"$(SID$1811,38,"cmax_spec.cm"$) " :\n"$1812,7,"cmax_spec.cm"$  ')
                        :
                            LET O2$1813,9,"cmax_spec.cm"$ ==
                                outputMAXCode$1813,13,"cmax_spec.cm"$(E$1813,27,"cmax_spec.cm"$, "    "$1813,30,"cmax_spec.cm"$, HANDLE$1813,38,"cmax_spec.cm"$)
                            :
                                writeToFile$1814,5,"cmax_spec.cm"$(HANDLE$1814,17,"cmax_spec.cm"$, "\n"$1814,25,"cmax_spec.cm"$)







| is$1815,5,"cmax_spec.cm"$[D$1815,8,"cmax_spec.cm"$, _DynFunc$1815,11,"cmax_spec.cm"$] :
    LET ID$1816,9,"cmax_spec.cm"$ ==
        subterm$1816,13,"cmax_spec.cm"$(1$1816,21,"cmax_spec.cm"$, D$1816,24,"cmax_spec.cm"$)
    :
        LET SIDL$1817,9,"cmax_spec.cm"$ ==
            subterm$1817,15,"cmax_spec.cm"$(2$1817,23,"cmax_spec.cm"$, D$1817,26,"cmax_spec.cm"$)
        :
            LET NL$1818,9,"cmax_spec.cm"$ ==
                subterm$1818,13,"cmax_spec.cm"$(3$1818,21,"cmax_spec.cm"$, D$1818,24,"cmax_spec.cm"$)
            :
                LET SID$1819,9,"cmax_spec.cm"$ ==
                    subterm$1819,14,"cmax_spec.cm"$(4$1819,22,"cmax_spec.cm"$, D$1819,25,"cmax_spec.cm"$)
                :
                    LET E$1820,9,"cmax_spec.cm"$ ==
                        subterm$1820,12,"cmax_spec.cm"$(5$1820,20,"cmax_spec.cm"$, D$1820,23,"cmax_spec.cm"$)
                    :
                        LET O1$1821,9,"cmax_spec.cm"$ ==
                            writeToFile$1821,13,"cmax_spec.cm"$(HANDLE$1821,26,"cmax_spec.cm"$, `$1821,35,"cmax_spec.cm"$ "DYN "$1821,35,"cmax_spec.cm"$ codeForIdent$1821,45,"cmax_spec.cm"$(ID$1821,42,"cmax_spec.cm"$) " ( "$1821,58,"cmax_spec.cm"$ codeForParList$1822,7,"cmax_spec.cm"$(SIDL$1822,22,"cmax_spec.cm"$, NL$1822,28,"cmax_spec.cm"$) " ) "$1822,32,"cmax_spec.cm"$ codeForIdent$1822,42,"cmax_spec.cm"$(SID$1822,38,"cmax_spec.cm"$) " :\n"$1823,7,"cmax_spec.cm"$  ')
                        :
                            LET O2$1824,9,"cmax_spec.cm"$ ==
                                outputMAXCode$1824,13,"cmax_spec.cm"$(E$1824,27,"cmax_spec.cm"$, "    "$1824,30,"cmax_spec.cm"$, HANDLE$1824,38,"cmax_spec.cm"$)
                            :
                                writeToFile$1825,5,"cmax_spec.cm"$(HANDLE$1825,17,"cmax_spec.cm"$, "\n"$1825,25,"cmax_spec.cm"$)







| is$1826,5,"cmax_spec.cm"$[D$1826,8,"cmax_spec.cm"$, _Condition$1826,11,"cmax_spec.cm"$] :
    LET PL$1827,9,"cmax_spec.cm"$ ==
        subterm$1827,13,"cmax_spec.cm"$(1$1827,21,"cmax_spec.cm"$, D$1827,24,"cmax_spec.cm"$)
    :
        LET F$1828,9,"cmax_spec.cm"$ ==
            subterm$1828,12,"cmax_spec.cm"$(2$1828,20,"cmax_spec.cm"$, D$1828,23,"cmax_spec.cm"$)
        :
            LET E$1829,9,"cmax_spec.cm"$ ==
                subterm$1829,12,"cmax_spec.cm"$(3$1829,20,"cmax_spec.cm"$, D$1829,23,"cmax_spec.cm"$)
            :
                LET O1$1830,9,"cmax_spec.cm"$ ==
                    writeToFile$1830,13,"cmax_spec.cm"$(HANDLE$1830,26,"cmax_spec.cm"$, "CND "$1831,14,"cmax_spec.cm"$)
                :
                    LET O2$1832,9,"cmax_spec.cm"$ ==
                        outputMAXCode$1832,13,"cmax_spec.cm"$(PL$1832,28,"cmax_spec.cm"$, ""$1832,32,"cmax_spec.cm"$, HANDLE$1832,36,"cmax_spec.cm"$)
                    :
                        LET O3$1833,9,"cmax_spec.cm"$ ==
                            writeToFile$1833,13,"cmax_spec.cm"$(HANDLE$1833,25,"cmax_spec.cm"$, ":\n"$1833,33,"cmax_spec.cm"$)
                        :
                            LET O4$1834,9,"cmax_spec.cm"$ ==
                                outputMAXCode$1834,13,"cmax_spec.cm"$(F$1834,27,"cmax_spec.cm"$, "    "$1834,30,"cmax_spec.cm"$, HANDLE$1834,38,"cmax_spec.cm"$)
                            :
                                LET O5$1835,9,"cmax_spec.cm"$ ==
                                    writeToFile$1835,13,"cmax_spec.cm"$(HANDLE$1835,26,"cmax_spec.cm"$, "\n    |\n"$1835,34,"cmax_spec.cm"$)
                                :
                                    LET O6$1836,9,"cmax_spec.cm"$ ==
                                        outputMAXCode$1836,13,"cmax_spec.cm"$(E$1836,27,"cmax_spec.cm"$, "    "$1836,30,"cmax_spec.cm"$, HANDLE$1836,38,"cmax_spec.cm"$)
                                    :
                                        writeToFile$1837,5,"cmax_spec.cm"$(HANDLE$1837,18,"cmax_spec.cm"$, "\n"$1837,26,"cmax_spec.cm"$)









| is$1838,5,"cmax_spec.cm"$[D$1838,8,"cmax_spec.cm"$, _PatternList$1838,11,"cmax_spec.cm"$] :
    IF$1839,7,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1839,10,"cmax_spec.cm"$(D$1839,8,"cmax_spec.cm"$), 0$1839,24,"cmax_spec.cm"$]:
        true$1840,7,"cmax_spec.cm"$()
    ELSE
        LET O1$1842,11,"cmax_spec.cm"$ ==
            outputMAXCode$1842,15,"cmax_spec.cm"$(subterm$1842,29,"cmax_spec.cm"$(1$1842,37,"cmax_spec.cm"$, D$1842,40,"cmax_spec.cm"$), PF$1842,44,"cmax_spec.cm"$, HANDLE$1842,48,"cmax_spec.cm"$)
        :
            IF$1843,9,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1843,12,"cmax_spec.cm"$(D$1843,10,"cmax_spec.cm"$), 1$1843,26,"cmax_spec.cm"$]:
                true$1844,9,"cmax_spec.cm"$()
            ELSE
                LET O2$1846,13,"cmax_spec.cm"$ ==
                    writeToFile$1846,17,"cmax_spec.cm"$(HANDLE$1846,29,"cmax_spec.cm"$, " , "$1846,37,"cmax_spec.cm"$)
                :
                    outputMAXCode$1847,9,"cmax_spec.cm"$(back$1847,25,"cmax_spec.cm"$(D$1847,23,"cmax_spec.cm"$), ""$1847,31,"cmax_spec.cm"$, HANDLE$1847,35,"cmax_spec.cm"$)


| is$1848,5,"cmax_spec.cm"$[D$1848,8,"cmax_spec.cm"$, _MaxCodeText$1848,11,"cmax_spec.cm"$] :
    writeToFile$1849,5,"cmax_spec.cm"$(HANDLE$1849,17,"cmax_spec.cm"$, subterm$1849,25,"cmax_spec.cm"$(1$1849,33,"cmax_spec.cm"$, D$1849,36,"cmax_spec.cm"$))
| is$1853,5,"cmax_spec.cm"$[D$1853,8,"cmax_spec.cm"$, _CharConst$1853,11,"cmax_spec.cm"$] :
    LET O$1854,9,"cmax_spec.cm"$ ==
        writeToFile$1854,12,"cmax_spec.cm"$(HANDLE$1854,24,"cmax_spec.cm"$, `$1854,33,"cmax_spec.cm"$ PF$1854,33,"cmax_spec.cm"$ "'"$1854,36,"cmax_spec.cm"$ ctos$1854,40,"cmax_spec.cm"$(subterm$1854,45,"cmax_spec.cm"$(1$1854,53,"cmax_spec.cm"$, D$1854,56,"cmax_spec.cm"$)) "'"$1854,60,"cmax_spec.cm"$  ')
    :
        writeToFile$1855,5,"cmax_spec.cm"$(HANDLE$1855,17,"cmax_spec.cm"$, `$1855,26,"cmax_spec.cm"$ scp1$1855,26,"cmax_spec.cm"$(subterm$1855,31,"cmax_spec.cm"$(-3$1855,39,"cmax_spec.cm"$, D$1855,43,"cmax_spec.cm"$), subterm$1855,47,"cmax_spec.cm"$(-2$1855,55,"cmax_spec.cm"$, D$1855,59,"cmax_spec.cm"$), subterm$1856,39,"cmax_spec.cm"$(-1$1856,47,"cmax_spec.cm"$, D$1856,51,"cmax_spec.cm"$))  ')

| is$1857,5,"cmax_spec.cm"$[D$1857,8,"cmax_spec.cm"$, _IntConst$1857,11,"cmax_spec.cm"$] :
    LET O$1858,9,"cmax_spec.cm"$ ==
        writeToFile$1858,12,"cmax_spec.cm"$(HANDLE$1858,24,"cmax_spec.cm"$, `$1858,33,"cmax_spec.cm"$ PF$1858,33,"cmax_spec.cm"$ itos$1858,50,"cmax_spec.cm"$(subterm$1858,36,"cmax_spec.cm"$(1$1858,44,"cmax_spec.cm"$, D$1858,47,"cmax_spec.cm"$))  ')
    :
        writeToFile$1859,5,"cmax_spec.cm"$(HANDLE$1859,17,"cmax_spec.cm"$, `$1859,26,"cmax_spec.cm"$ scp1$1859,26,"cmax_spec.cm"$(subterm$1859,31,"cmax_spec.cm"$(-3$1859,39,"cmax_spec.cm"$, D$1859,43,"cmax_spec.cm"$), subterm$1859,47,"cmax_spec.cm"$(-2$1859,55,"cmax_spec.cm"$, D$1859,59,"cmax_spec.cm"$), subterm$1860,39,"cmax_spec.cm"$(-1$1860,47,"cmax_spec.cm"$, D$1860,51,"cmax_spec.cm"$))  ')

| is$1861,5,"cmax_spec.cm"$[D$1861,8,"cmax_spec.cm"$, _StringConst$1861,11,"cmax_spec.cm"$] :
    LET O$1862,9,"cmax_spec.cm"$ ==
        writeToFile$1862,12,"cmax_spec.cm"$(HANDLE$1862,24,"cmax_spec.cm"$, `$1862,33,"cmax_spec.cm"$ PF$1862,33,"cmax_spec.cm"$ "\""$1862,36,"cmax_spec.cm"$ subterm$1862,41,"cmax_spec.cm"$(1$1862,49,"cmax_spec.cm"$, D$1862,52,"cmax_spec.cm"$) "\""$1862,55,"cmax_spec.cm"$  ')
    :
        writeToFile$1863,5,"cmax_spec.cm"$(HANDLE$1863,17,"cmax_spec.cm"$, `$1863,26,"cmax_spec.cm"$ scp1$1863,26,"cmax_spec.cm"$(subterm$1863,31,"cmax_spec.cm"$(-3$1863,39,"cmax_spec.cm"$, D$1863,43,"cmax_spec.cm"$), subterm$1863,47,"cmax_spec.cm"$(-2$1863,55,"cmax_spec.cm"$, D$1863,59,"cmax_spec.cm"$), subterm$1864,39,"cmax_spec.cm"$(-1$1864,47,"cmax_spec.cm"$, D$1864,51,"cmax_spec.cm"$))  ')

| is$1865,5,"cmax_spec.cm"$[D$1865,8,"cmax_spec.cm"$, _SortConst$1865,11,"cmax_spec.cm"$] :
    writeToFile$1866,5,"cmax_spec.cm"$(HANDLE$1866,17,"cmax_spec.cm"$, `$1866,26,"cmax_spec.cm"$ PF$1866,26,"cmax_spec.cm"$ "_"$1866,29,"cmax_spec.cm"$ codeForIdent$1866,47,"cmax_spec.cm"$(subterm$1866,33,"cmax_spec.cm"$(1$1866,41,"cmax_spec.cm"$, D$1866,44,"cmax_spec.cm"$))  ')
| is$1867,5,"cmax_spec.cm"$[D$1867,8,"cmax_spec.cm"$, _Name$1867,11,"cmax_spec.cm"$] :
    writeToFile$1868,5,"cmax_spec.cm"$(HANDLE$1868,17,"cmax_spec.cm"$, `$1868,26,"cmax_spec.cm"$ PF$1868,26,"cmax_spec.cm"$ codeForIdent$1868,29,"cmax_spec.cm"$(D$1868,42,"cmax_spec.cm"$)  ')
| is$1869,5,"cmax_spec.cm"$[D$1869,8,"cmax_spec.cm"$, _FuncAppl$1869,11,"cmax_spec.cm"$] :
    LET O1$1870,9,"cmax_spec.cm"$ ==
        writeToFile$1870,13,"cmax_spec.cm"$(HANDLE$1870,25,"cmax_spec.cm"$, `$1871,26,"cmax_spec.cm"$ PF$1871,26,"cmax_spec.cm"$ codeForIdent$1871,29,"cmax_spec.cm"$(subterm$1871,42,"cmax_spec.cm"$(1$1871,50,"cmax_spec.cm"$, D$1871,53,"cmax_spec.cm"$)) "("$1871,57,"cmax_spec.cm"$  ')
    :
        LET O2$1872,9,"cmax_spec.cm"$ ==
            outputMAXCode$1872,13,"cmax_spec.cm"$(subterm$1872,27,"cmax_spec.cm"$(2$1872,35,"cmax_spec.cm"$, D$1872,38,"cmax_spec.cm"$), ""$1872,42,"cmax_spec.cm"$, HANDLE$1872,46,"cmax_spec.cm"$)
        :
            writeToFile$1873,5,"cmax_spec.cm"$(HANDLE$1873,17,"cmax_spec.cm"$, ")"$1873,25,"cmax_spec.cm"$)


| is$1874,5,"cmax_spec.cm"$[D$1874,8,"cmax_spec.cm"$, _ExprList$1874,11,"cmax_spec.cm"$] :
    IF$1875,7,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1875,10,"cmax_spec.cm"$(D$1875,8,"cmax_spec.cm"$), 0$1875,24,"cmax_spec.cm"$]:
        true$1875,27,"cmax_spec.cm"$()
    | eq$0,0,"?"$[numsubterms$1876,9,"cmax_spec.cm"$(D$1876,7,"cmax_spec.cm"$), 1$1876,23,"cmax_spec.cm"$] :
        outputMAXCode$1876,26,"cmax_spec.cm"$(subterm$1876,40,"cmax_spec.cm"$(1$1876,48,"cmax_spec.cm"$, D$1876,51,"cmax_spec.cm"$), ""$1876,55,"cmax_spec.cm"$, HANDLE$1876,59,"cmax_spec.cm"$)
    ELSE
        LET O1$1878,11,"cmax_spec.cm"$ ==
            outputMAXCode$1878,15,"cmax_spec.cm"$(subterm$1878,29,"cmax_spec.cm"$(1$1878,37,"cmax_spec.cm"$, D$1878,40,"cmax_spec.cm"$), ""$1878,44,"cmax_spec.cm"$, HANDLE$1878,48,"cmax_spec.cm"$)
        :
            LET O2$1879,11,"cmax_spec.cm"$ ==
                writeToFile$1879,15,"cmax_spec.cm"$(HANDLE$1879,27,"cmax_spec.cm"$, ", "$1879,35,"cmax_spec.cm"$)
            :
                outputMAXCode$1880,7,"cmax_spec.cm"$(back$1880,23,"cmax_spec.cm"$(D$1880,21,"cmax_spec.cm"$), ""$1880,29,"cmax_spec.cm"$, HANDLE$1880,33,"cmax_spec.cm"$)


| is$1881,5,"cmax_spec.cm"$[D$1881,8,"cmax_spec.cm"$, _IfExpr$1881,11,"cmax_spec.cm"$] :
    LET FC$1882,9,"cmax_spec.cm"$ ==
        subterm$1882,13,"cmax_spec.cm"$(1$1882,21,"cmax_spec.cm"$, subterm$1882,24,"cmax_spec.cm"$(1$1882,32,"cmax_spec.cm"$, D$1882,35,"cmax_spec.cm"$))
    :
        LET O1$1883,9,"cmax_spec.cm"$ ==
            writeToFile$1883,13,"cmax_spec.cm"$(HANDLE$1883,25,"cmax_spec.cm"$, `$1883,34,"cmax_spec.cm"$ PF$1883,34,"cmax_spec.cm"$ "IF"$1883,37,"cmax_spec.cm"$  ')
        :
            LET O11$1884,9,"cmax_spec.cm"$ ==
                writeToFile$1884,14,"cmax_spec.cm"$(HANDLE$1884,26,"cmax_spec.cm"$, `$1884,35,"cmax_spec.cm"$ scp1$1884,35,"cmax_spec.cm"$(subterm$1884,40,"cmax_spec.cm"$(3$1884,48,"cmax_spec.cm"$, D$1884,51,"cmax_spec.cm"$), subterm$1884,55,"cmax_spec.cm"$(4$1884,63,"cmax_spec.cm"$, D$1884,66,"cmax_spec.cm"$), subterm$1885,39,"cmax_spec.cm"$(5$1885,47,"cmax_spec.cm"$, D$1885,50,"cmax_spec.cm"$)) " "$1885,54,"cmax_spec.cm"$  ')
            :
                LET O2$1886,9,"cmax_spec.cm"$ ==
                    outputMAXCode$1886,13,"cmax_spec.cm"$(subterm$1886,27,"cmax_spec.cm"$(1$1886,35,"cmax_spec.cm"$, FC$1886,38,"cmax_spec.cm"$), ""$1886,43,"cmax_spec.cm"$, HANDLE$1886,47,"cmax_spec.cm"$)
                :
                    LET O3$1887,9,"cmax_spec.cm"$ ==
                        writeToFile$1887,13,"cmax_spec.cm"$(HANDLE$1887,25,"cmax_spec.cm"$, ":\n"$1887,33,"cmax_spec.cm"$)
                    :
                        LET O4$1888,9,"cmax_spec.cm"$ ==
                            outputMAXCode$1888,13,"cmax_spec.cm"$(subterm$1888,27,"cmax_spec.cm"$(2$1888,35,"cmax_spec.cm"$, FC$1888,38,"cmax_spec.cm"$), `$1888,44,"cmax_spec.cm"$ PF$1888,44,"cmax_spec.cm"$ "    "$1888,47,"cmax_spec.cm"$  ', HANDLE$1888,56,"cmax_spec.cm"$)
                        :
                            LET O5$1889,9,"cmax_spec.cm"$ ==
                                writeToFile$1889,13,"cmax_spec.cm"$(HANDLE$1889,25,"cmax_spec.cm"$, "\n"$1889,33,"cmax_spec.cm"$)
                            :
                                LET O6$1890,9,"cmax_spec.cm"$ ==
                                    outputMAXCode$1890,13,"cmax_spec.cm"$(back$1890,41,"cmax_spec.cm"$(subterm$1890,27,"cmax_spec.cm"$(1$1890,35,"cmax_spec.cm"$, D$1890,38,"cmax_spec.cm"$)), PF$1890,47,"cmax_spec.cm"$, HANDLE$1890,51,"cmax_spec.cm"$)
                                :
                                    LET O7$1891,9,"cmax_spec.cm"$ ==
                                        writeToFile$1891,13,"cmax_spec.cm"$(HANDLE$1891,25,"cmax_spec.cm"$, `$1891,34,"cmax_spec.cm"$ PF$1891,34,"cmax_spec.cm"$ "ELSE\n"$1891,37,"cmax_spec.cm"$  ')
                                    :
                                        outputMAXCode$1892,5,"cmax_spec.cm"$(subterm$1892,20,"cmax_spec.cm"$(2$1892,28,"cmax_spec.cm"$, D$1892,31,"cmax_spec.cm"$), `$1892,36,"cmax_spec.cm"$ PF$1892,36,"cmax_spec.cm"$ "    "$1892,39,"cmax_spec.cm"$  ', HANDLE$1892,48,"cmax_spec.cm"$)









| is$1893,5,"cmax_spec.cm"$[D$1893,8,"cmax_spec.cm"$, _CaseList$1893,11,"cmax_spec.cm"$] :
    IF$1894,7,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1894,10,"cmax_spec.cm"$(D$1894,8,"cmax_spec.cm"$), 0$1894,22,"cmax_spec.cm"$]:
        true$1894,25,"cmax_spec.cm"$()
    ELSE
        LET C$1896,11,"cmax_spec.cm"$ ==
            subterm$1896,14,"cmax_spec.cm"$(1$1896,22,"cmax_spec.cm"$, D$1896,25,"cmax_spec.cm"$)
        :
            LET O1$1897,11,"cmax_spec.cm"$ ==
                writeToFile$1897,15,"cmax_spec.cm"$(HANDLE$1897,27,"cmax_spec.cm"$, `$1897,36,"cmax_spec.cm"$ PF$1897,36,"cmax_spec.cm"$ "| "$1897,39,"cmax_spec.cm"$  ')
            :
                LET O2$1898,11,"cmax_spec.cm"$ ==
                    outputMAXCode$1898,15,"cmax_spec.cm"$(subterm$1898,29,"cmax_spec.cm"$(1$1898,37,"cmax_spec.cm"$, C$1898,40,"cmax_spec.cm"$), ""$1898,44,"cmax_spec.cm"$, HANDLE$1898,48,"cmax_spec.cm"$)
                :
                    LET O3$1899,11,"cmax_spec.cm"$ ==
                        writeToFile$1899,15,"cmax_spec.cm"$(HANDLE$1899,28,"cmax_spec.cm"$, " :\n"$1899,36,"cmax_spec.cm"$)
                    :
                        LET O4$1900,11,"cmax_spec.cm"$ ==
                            outputMAXCode$1900,15,"cmax_spec.cm"$(subterm$1900,29,"cmax_spec.cm"$(2$1900,37,"cmax_spec.cm"$, C$1900,40,"cmax_spec.cm"$), `$1900,45,"cmax_spec.cm"$ PF$1900,45,"cmax_spec.cm"$ "    "$1900,48,"cmax_spec.cm"$  ', HANDLE$1900,57,"cmax_spec.cm"$)
                        :
                            LET O5$1901,11,"cmax_spec.cm"$ ==
                                writeToFile$1901,15,"cmax_spec.cm"$(HANDLE$1901,27,"cmax_spec.cm"$, "\n"$1901,35,"cmax_spec.cm"$)
                            :
                                outputMAXCode$1902,7,"cmax_spec.cm"$(back$1902,23,"cmax_spec.cm"$(D$1902,21,"cmax_spec.cm"$), ""$1902,29,"cmax_spec.cm"$, HANDLE$1902,33,"cmax_spec.cm"$)






| is$1903,5,"cmax_spec.cm"$[D$1903,8,"cmax_spec.cm"$, _Pattern$1903,11,"cmax_spec.cm"$] :
    LET SP$1904,9,"cmax_spec.cm"$ ==
        subterm$1904,13,"cmax_spec.cm"$(2$1904,21,"cmax_spec.cm"$, D$1904,24,"cmax_spec.cm"$)
    :
        IF$1905,7,"cmax_spec.cm"$ is$1905,8,"cmax_spec.cm"$[SP$1905,11,"cmax_spec.cm"$, _Blank$1905,15,"cmax_spec.cm"$]:
            LET O1$1906,11,"cmax_spec.cm"$ ==
                outputMAXCode$1906,15,"cmax_spec.cm"$(subterm$1906,29,"cmax_spec.cm"$(1$1906,37,"cmax_spec.cm"$, D$1906,40,"cmax_spec.cm"$), PF$1906,44,"cmax_spec.cm"$, HANDLE$1906,48,"cmax_spec.cm"$)
            :
                LET O2$1907,11,"cmax_spec.cm"$ ==
                    writeToFile$1907,15,"cmax_spec.cm"$(HANDLE$1907,27,"cmax_spec.cm"$, " "$1907,35,"cmax_spec.cm"$)
                :
                    outputMAXCode$1908,7,"cmax_spec.cm"$(subterm$1908,21,"cmax_spec.cm"$(3$1908,29,"cmax_spec.cm"$, D$1908,32,"cmax_spec.cm"$), ""$1908,36,"cmax_spec.cm"$, HANDLE$1908,40,"cmax_spec.cm"$)


        ELSE
            LET O1$1910,11,"cmax_spec.cm"$ ==
                outputMAXCode$1910,15,"cmax_spec.cm"$(subterm$1910,29,"cmax_spec.cm"$(1$1910,37,"cmax_spec.cm"$, D$1910,40,"cmax_spec.cm"$), PF$1910,44,"cmax_spec.cm"$, HANDLE$1910,48,"cmax_spec.cm"$)
            :
                LET O2$1911,11,"cmax_spec.cm"$ ==
                    writeToFile$1911,15,"cmax_spec.cm"$(HANDLE$1911,27,"cmax_spec.cm"$, "<"$1911,35,"cmax_spec.cm"$)
                :
                    LET O3$1912,11,"cmax_spec.cm"$ ==
                        outputMAXCode$1912,15,"cmax_spec.cm"$(SP$1912,29,"cmax_spec.cm"$, ""$1912,33,"cmax_spec.cm"$, HANDLE$1912,37,"cmax_spec.cm"$)
                    :
                        LET O4$1913,11,"cmax_spec.cm"$ ==
                            writeToFile$1913,15,"cmax_spec.cm"$(HANDLE$1913,27,"cmax_spec.cm"$, ">"$1913,35,"cmax_spec.cm"$)
                        :
                            outputMAXCode$1914,7,"cmax_spec.cm"$(subterm$1914,21,"cmax_spec.cm"$(3$1914,29,"cmax_spec.cm"$, D$1914,32,"cmax_spec.cm"$), ""$1914,36,"cmax_spec.cm"$, HANDLE$1914,40,"cmax_spec.cm"$)





| is$1915,5,"cmax_spec.cm"$[D$1915,8,"cmax_spec.cm"$, _SortId$1915,11,"cmax_spec.cm"$] :
    writeToFile$1915,21,"cmax_spec.cm"$(HANDLE$1915,33,"cmax_spec.cm"$, `$1915,42,"cmax_spec.cm"$ PF$1915,42,"cmax_spec.cm"$ codeForIdent$1915,45,"cmax_spec.cm"$(D$1915,58,"cmax_spec.cm"$)  ')
| is$1916,5,"cmax_spec.cm"$[D$1916,8,"cmax_spec.cm"$, _Blank$1916,11,"cmax_spec.cm"$] :
    true$1916,20,"cmax_spec.cm"$()
| is$1917,5,"cmax_spec.cm"$[D$1917,8,"cmax_spec.cm"$, _ItemList$1917,11,"cmax_spec.cm"$] :
    IF$1918,7,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1918,10,"cmax_spec.cm"$(D$1918,8,"cmax_spec.cm"$), 0$1918,22,"cmax_spec.cm"$]:
        true$1918,25,"cmax_spec.cm"$()
    | eq$0,0,"?"$[numsubterms$1919,9,"cmax_spec.cm"$(D$1919,7,"cmax_spec.cm"$), 1$1919,21,"cmax_spec.cm"$] :
        LET FST$1920,11,"cmax_spec.cm"$ ==
            subterm$1920,16,"cmax_spec.cm"$(1$1920,24,"cmax_spec.cm"$, D$1920,27,"cmax_spec.cm"$)
        :
            IF$1921,9,"cmax_spec.cm"$ is$1921,10,"cmax_spec.cm"$[FST$1921,13,"cmax_spec.cm"$, _Blank$1921,18,"cmax_spec.cm"$]:
                writeToFile$1921,27,"cmax_spec.cm"$(HANDLE$1921,39,"cmax_spec.cm"$, "_"$1921,47,"cmax_spec.cm"$)
            ELSE
                outputMAXCode$1922,12,"cmax_spec.cm"$(FST$1922,26,"cmax_spec.cm"$, PF$1922,31,"cmax_spec.cm"$, HANDLE$1922,35,"cmax_spec.cm"$)

    ELSE
        LET FST$1924,11,"cmax_spec.cm"$ ==
            subterm$1924,16,"cmax_spec.cm"$(1$1924,24,"cmax_spec.cm"$, D$1924,27,"cmax_spec.cm"$)
        :
            LET O1$1925,11,"cmax_spec.cm"$ ==
                IF$1926,9,"cmax_spec.cm"$ is$1926,10,"cmax_spec.cm"$[FST$1926,13,"cmax_spec.cm"$, _Blank$1926,18,"cmax_spec.cm"$]:
                    writeToFile$1927,9,"cmax_spec.cm"$(HANDLE$1927,21,"cmax_spec.cm"$, "_"$1927,29,"cmax_spec.cm"$)
                ELSE
                    outputMAXCode$1929,9,"cmax_spec.cm"$(FST$1929,23,"cmax_spec.cm"$, PF$1929,28,"cmax_spec.cm"$, HANDLE$1929,32,"cmax_spec.cm"$)
            :
                LET O2$1931,11,"cmax_spec.cm"$ ==
                    writeToFile$1931,15,"cmax_spec.cm"$(HANDLE$1931,27,"cmax_spec.cm"$, ","$1931,35,"cmax_spec.cm"$)
                :
                    outputMAXCode$1932,7,"cmax_spec.cm"$(back$1932,23,"cmax_spec.cm"$(D$1932,21,"cmax_spec.cm"$), PF$1932,29,"cmax_spec.cm"$, HANDLE$1932,33,"cmax_spec.cm"$)



| is$1933,5,"cmax_spec.cm"$[D$1933,8,"cmax_spec.cm"$, _Asterisk$1933,11,"cmax_spec.cm"$] :
    writeToFile$1934,5,"cmax_spec.cm"$(HANDLE$1934,17,"cmax_spec.cm"$, "*"$1934,25,"cmax_spec.cm"$)
| is$1935,5,"cmax_spec.cm"$[D$1935,8,"cmax_spec.cm"$, _PredAppl$1935,11,"cmax_spec.cm"$] :
    LET O1$1936,9,"cmax_spec.cm"$ ==
        writeToFile$1936,13,"cmax_spec.cm"$(HANDLE$1936,25,"cmax_spec.cm"$, `$1936,34,"cmax_spec.cm"$ PF$1936,34,"cmax_spec.cm"$ codeForIdent$1936,51,"cmax_spec.cm"$(subterm$1936,37,"cmax_spec.cm"$(1$1936,45,"cmax_spec.cm"$, D$1936,48,"cmax_spec.cm"$)) "["$1936,64,"cmax_spec.cm"$  ')
    :
        LET O2$1937,9,"cmax_spec.cm"$ ==
            outputMAXCode$1937,13,"cmax_spec.cm"$(subterm$1937,27,"cmax_spec.cm"$(2$1937,35,"cmax_spec.cm"$, D$1937,38,"cmax_spec.cm"$), ""$1937,42,"cmax_spec.cm"$, HANDLE$1937,46,"cmax_spec.cm"$)
        :
            writeToFile$1938,5,"cmax_spec.cm"$(HANDLE$1938,17,"cmax_spec.cm"$, "]"$1938,25,"cmax_spec.cm"$)


| is$1939,5,"cmax_spec.cm"$[D$1939,8,"cmax_spec.cm"$, _Or$1939,11,"cmax_spec.cm"$] :
    LET O1$1940,9,"cmax_spec.cm"$ ==
        outputMAXCode$1940,13,"cmax_spec.cm"$(subterm$1940,27,"cmax_spec.cm"$(1$1940,35,"cmax_spec.cm"$, D$1940,38,"cmax_spec.cm"$), PF$1940,42,"cmax_spec.cm"$, HANDLE$1940,46,"cmax_spec.cm"$)
    :
        LET O2$1941,9,"cmax_spec.cm"$ ==
            writeToFile$1941,13,"cmax_spec.cm"$(HANDLE$1941,25,"cmax_spec.cm"$, " || "$1941,33,"cmax_spec.cm"$)
        :
            outputMAXCode$1942,5,"cmax_spec.cm"$(subterm$1942,19,"cmax_spec.cm"$(2$1942,27,"cmax_spec.cm"$, D$1942,30,"cmax_spec.cm"$), ""$1942,34,"cmax_spec.cm"$, HANDLE$1942,38,"cmax_spec.cm"$)


| is$1943,5,"cmax_spec.cm"$[D$1943,8,"cmax_spec.cm"$, _And$1943,11,"cmax_spec.cm"$] :
    LET O1$1944,9,"cmax_spec.cm"$ ==
        outputMAXCode$1944,13,"cmax_spec.cm"$(subterm$1944,27,"cmax_spec.cm"$(1$1944,35,"cmax_spec.cm"$, D$1944,38,"cmax_spec.cm"$), PF$1944,42,"cmax_spec.cm"$, HANDLE$1944,46,"cmax_spec.cm"$)
    :
        LET O2$1945,9,"cmax_spec.cm"$ ==
            writeToFile$1945,13,"cmax_spec.cm"$(HANDLE$1945,25,"cmax_spec.cm"$, " && "$1945,33,"cmax_spec.cm"$)
        :
            outputMAXCode$1946,5,"cmax_spec.cm"$(subterm$1946,19,"cmax_spec.cm"$(2$1946,27,"cmax_spec.cm"$, D$1946,30,"cmax_spec.cm"$), ""$1946,34,"cmax_spec.cm"$, HANDLE$1946,38,"cmax_spec.cm"$)


| is$1947,5,"cmax_spec.cm"$[D$1947,8,"cmax_spec.cm"$, _Impl$1947,11,"cmax_spec.cm"$] :
    LET O1$1948,9,"cmax_spec.cm"$ ==
        outputMAXCode$1948,13,"cmax_spec.cm"$(subterm$1948,27,"cmax_spec.cm"$(1$1948,35,"cmax_spec.cm"$, D$1948,38,"cmax_spec.cm"$), PF$1948,42,"cmax_spec.cm"$, HANDLE$1948,46,"cmax_spec.cm"$)
    :
        LET O2$1949,9,"cmax_spec.cm"$ ==
            writeToFile$1949,13,"cmax_spec.cm"$(HANDLE$1949,25,"cmax_spec.cm"$, " -> "$1949,33,"cmax_spec.cm"$)
        :
            outputMAXCode$1950,5,"cmax_spec.cm"$(subterm$1950,19,"cmax_spec.cm"$(2$1950,27,"cmax_spec.cm"$, D$1950,30,"cmax_spec.cm"$), ""$1950,34,"cmax_spec.cm"$, HANDLE$1950,38,"cmax_spec.cm"$)


| is$1951,5,"cmax_spec.cm"$[D$1951,8,"cmax_spec.cm"$, _Neg$1951,11,"cmax_spec.cm"$] :
    LET O1$1952,9,"cmax_spec.cm"$ ==
        writeToFile$1952,13,"cmax_spec.cm"$(HANDLE$1952,25,"cmax_spec.cm"$, `$1952,34,"cmax_spec.cm"$ PF$1952,34,"cmax_spec.cm"$ "! "$1952,37,"cmax_spec.cm"$  ')
    :
        outputMAXCode$1953,5,"cmax_spec.cm"$(subterm$1953,19,"cmax_spec.cm"$(1$1953,27,"cmax_spec.cm"$, D$1953,30,"cmax_spec.cm"$), ""$1953,34,"cmax_spec.cm"$, HANDLE$1953,38,"cmax_spec.cm"$)

| is$1954,5,"cmax_spec.cm"$[D$1954,8,"cmax_spec.cm"$, _LetExpr$1954,11,"cmax_spec.cm"$] :
    LET O1$1955,9,"cmax_spec.cm"$ ==
        writeToFile$1955,13,"cmax_spec.cm"$(HANDLE$1955,25,"cmax_spec.cm"$, `$1955,34,"cmax_spec.cm"$ PF$1955,34,"cmax_spec.cm"$ "LET "$1955,37,"cmax_spec.cm"$ codeForIdent$1955,44,"cmax_spec.cm"$(subterm$1955,57,"cmax_spec.cm"$(1$1955,65,"cmax_spec.cm"$, D$1955,68,"cmax_spec.cm"$)) " ==\n"$1956,34,"cmax_spec.cm"$  ')
    :
        LET O2$1957,9,"cmax_spec.cm"$ ==
            outputMAXCode$1957,13,"cmax_spec.cm"$(subterm$1957,27,"cmax_spec.cm"$(2$1957,35,"cmax_spec.cm"$, D$1957,38,"cmax_spec.cm"$), `$1957,43,"cmax_spec.cm"$ PF$1957,43,"cmax_spec.cm"$ "    "$1957,46,"cmax_spec.cm"$  ', HANDLE$1957,55,"cmax_spec.cm"$)
        :
            LET O3$1958,9,"cmax_spec.cm"$ ==
                writeToFile$1958,13,"cmax_spec.cm"$(HANDLE$1958,25,"cmax_spec.cm"$, `$1958,34,"cmax_spec.cm"$ "\n"$1958,34,"cmax_spec.cm"$ PF$1958,39,"cmax_spec.cm"$ ":\n"$1958,42,"cmax_spec.cm"$  ')
            :
                LET O4$1959,9,"cmax_spec.cm"$ ==
                    outputMAXCode$1959,13,"cmax_spec.cm"$(subterm$1959,27,"cmax_spec.cm"$(3$1959,35,"cmax_spec.cm"$, D$1959,38,"cmax_spec.cm"$), `$1959,43,"cmax_spec.cm"$ PF$1959,43,"cmax_spec.cm"$ "    "$1959,46,"cmax_spec.cm"$  ', HANDLE$1959,55,"cmax_spec.cm"$)
                :
                    writeToFile$1960,5,"cmax_spec.cm"$(HANDLE$1960,17,"cmax_spec.cm"$, "\n"$1960,25,"cmax_spec.cm"$)




| is$1961,5,"cmax_spec.cm"$[D$1961,8,"cmax_spec.cm"$, _StringExpr$1961,11,"cmax_spec.cm"$] :
    LET O1$1962,9,"cmax_spec.cm"$ ==
        writeToFile$1962,13,"cmax_spec.cm"$(HANDLE$1962,25,"cmax_spec.cm"$, `$1962,34,"cmax_spec.cm"$ PF$1962,34,"cmax_spec.cm"$ "`"$1962,37,"cmax_spec.cm"$  ')
    :
        LET O11$1963,9,"cmax_spec.cm"$ ==
            writeToFile$1963,14,"cmax_spec.cm"$(HANDLE$1963,26,"cmax_spec.cm"$, `$1963,35,"cmax_spec.cm"$ scp1$1963,35,"cmax_spec.cm"$(subterm$1963,40,"cmax_spec.cm"$(-3$1963,48,"cmax_spec.cm"$, D$1963,52,"cmax_spec.cm"$), subterm$1963,56,"cmax_spec.cm"$(-2$1963,64,"cmax_spec.cm"$, D$1963,68,"cmax_spec.cm"$), subterm$1964,39,"cmax_spec.cm"$(-1$1964,47,"cmax_spec.cm"$, D$1964,51,"cmax_spec.cm"$)) " "$1964,55,"cmax_spec.cm"$  ')
        :
            LET O2$1965,9,"cmax_spec.cm"$ ==
                outputMAXCode$1965,13,"cmax_spec.cm"$(subterm$1965,27,"cmax_spec.cm"$(1$1965,35,"cmax_spec.cm"$, D$1965,38,"cmax_spec.cm"$), ""$1965,42,"cmax_spec.cm"$, HANDLE$1965,46,"cmax_spec.cm"$)
            :
                writeToFile$1966,5,"cmax_spec.cm"$(HANDLE$1966,17,"cmax_spec.cm"$, " '"$1966,25,"cmax_spec.cm"$)



| is$1967,5,"cmax_spec.cm"$[D$1967,8,"cmax_spec.cm"$, _SExprList$1967,11,"cmax_spec.cm"$] :
    IF$1968,7,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$1968,10,"cmax_spec.cm"$(D$1968,8,"cmax_spec.cm"$), 0$1968,24,"cmax_spec.cm"$]:
        true$1968,27,"cmax_spec.cm"$()
    ELSE
        LET O1$1970,11,"cmax_spec.cm"$ ==
            outputMAXCode$1970,15,"cmax_spec.cm"$(subterm$1970,29,"cmax_spec.cm"$(1$1970,37,"cmax_spec.cm"$, D$1970,40,"cmax_spec.cm"$), ""$1970,44,"cmax_spec.cm"$, HANDLE$1970,48,"cmax_spec.cm"$)
        :
            LET O2$1971,11,"cmax_spec.cm"$ ==
                writeToFile$1971,15,"cmax_spec.cm"$(HANDLE$1971,27,"cmax_spec.cm"$, " "$1971,35,"cmax_spec.cm"$)
            :
                outputMAXCode$1972,7,"cmax_spec.cm"$(back$1972,23,"cmax_spec.cm"$(D$1972,21,"cmax_spec.cm"$), ""$1972,29,"cmax_spec.cm"$, HANDLE$1972,33,"cmax_spec.cm"$)


| is$1973,5,"cmax_spec.cm"$[D$1973,8,"cmax_spec.cm"$, _DynUndef$1973,11,"cmax_spec.cm"$] :
    writeToFile$1974,5,"cmax_spec.cm"$(HANDLE$1974,17,"cmax_spec.cm"$, `$1974,26,"cmax_spec.cm"$ PF$1974,26,"cmax_spec.cm"$ "??"$1974,29,"cmax_spec.cm"$  ')
| is$1978,5,"cmax_spec.cm"$[D$1978,8,"cmax_spec.cm"$, _IfRule$1978,11,"cmax_spec.cm"$] :
    LET C$1979,9,"cmax_spec.cm"$ ==
        subterm$1979,12,"cmax_spec.cm"$(1$1979,20,"cmax_spec.cm"$, D$1979,23,"cmax_spec.cm"$)
    :
        LET R1$1980,9,"cmax_spec.cm"$ ==
            subterm$1980,13,"cmax_spec.cm"$(2$1980,21,"cmax_spec.cm"$, D$1980,24,"cmax_spec.cm"$)
        :
            LET R2$1981,9,"cmax_spec.cm"$ ==
                subterm$1981,13,"cmax_spec.cm"$(3$1981,21,"cmax_spec.cm"$, D$1981,24,"cmax_spec.cm"$)
            :
                LET O$1982,9,"cmax_spec.cm"$ ==
                    writeToFile$1982,12,"cmax_spec.cm"$(HANDLE$1982,24,"cmax_spec.cm"$, `$1982,33,"cmax_spec.cm"$ PF$1982,33,"cmax_spec.cm"$ "IF "$1982,36,"cmax_spec.cm"$  ')
                :
                    LET O$1983,9,"cmax_spec.cm"$ ==
                        outputMAXCode$1983,12,"cmax_spec.cm"$(C$1983,26,"cmax_spec.cm"$, ""$1983,29,"cmax_spec.cm"$, HANDLE$1983,33,"cmax_spec.cm"$)
                    :
                        LET O$1984,9,"cmax_spec.cm"$ ==
                            writeToFile$1984,12,"cmax_spec.cm"$(HANDLE$1984,24,"cmax_spec.cm"$, "THEN\n"$1984,32,"cmax_spec.cm"$)
                        :
                            LET O$1985,9,"cmax_spec.cm"$ ==
                                outputMAXCode$1985,12,"cmax_spec.cm"$(R1$1985,26,"cmax_spec.cm"$, `$1985,31,"cmax_spec.cm"$ PF$1985,31,"cmax_spec.cm"$ "    "$1985,34,"cmax_spec.cm"$  ', HANDLE$1985,43,"cmax_spec.cm"$)
                            :
                                LET O$1986,9,"cmax_spec.cm"$ ==
                                    IF$1986,14,"cmax_spec.cm"$ ! eq$0,0,"?"$[0$1986,15,"cmax_spec.cm"$, numsubterms$1986,20,"cmax_spec.cm"$(R2$1986,17,"cmax_spec.cm"$)]:
                                        LET O$1987,18,"cmax_spec.cm"$ ==
                                            writeToFile$1987,21,"cmax_spec.cm"$(HANDLE$1987,33,"cmax_spec.cm"$, `$1987,42,"cmax_spec.cm"$ PF$1987,42,"cmax_spec.cm"$ "ELSE\n"$1987,45,"cmax_spec.cm"$  ')
                                        :
                                            outputMAXCode$1988,14,"cmax_spec.cm"$(R2$1988,28,"cmax_spec.cm"$, `$1988,33,"cmax_spec.cm"$ PF$1988,33,"cmax_spec.cm"$ "    "$1988,36,"cmax_spec.cm"$  ', HANDLE$1988,45,"cmax_spec.cm"$)

                                    ELSE
                                        true$1989,17,"cmax_spec.cm"$()
                                :
                                    writeToFile$1990,5,"cmax_spec.cm"$(HANDLE$1990,17,"cmax_spec.cm"$, `$1990,26,"cmax_spec.cm"$ PF$1990,26,"cmax_spec.cm"$ "FI\n"$1990,29,"cmax_spec.cm"$  ')








| is$1991,5,"cmax_spec.cm"$[D$1991,8,"cmax_spec.cm"$, _CaseRule$1991,11,"cmax_spec.cm"$] :
    LET E$1992,9,"cmax_spec.cm"$ ==
        subterm$1992,12,"cmax_spec.cm"$(1$1992,20,"cmax_spec.cm"$, D$1992,23,"cmax_spec.cm"$)
    :
        LET CIL$1993,9,"cmax_spec.cm"$ ==
            subterm$1993,14,"cmax_spec.cm"$(2$1993,22,"cmax_spec.cm"$, D$1993,25,"cmax_spec.cm"$)
        :
            LET R$1994,9,"cmax_spec.cm"$ ==
                subterm$1994,12,"cmax_spec.cm"$(2$1994,20,"cmax_spec.cm"$, D$1994,23,"cmax_spec.cm"$)
            :
                LET O$1995,9,"cmax_spec.cm"$ ==
                    writeToFile$1995,12,"cmax_spec.cm"$(HANDLE$1995,24,"cmax_spec.cm"$, `$1995,33,"cmax_spec.cm"$ PF$1995,33,"cmax_spec.cm"$ "CASE "$1995,36,"cmax_spec.cm"$  ')
                :
                    LET O$1996,9,"cmax_spec.cm"$ ==
                        outputMAXCode$1996,12,"cmax_spec.cm"$(E$1996,26,"cmax_spec.cm"$, ""$1996,29,"cmax_spec.cm"$, HANDLE$1996,33,"cmax_spec.cm"$)
                    :
                        LET O$1997,9,"cmax_spec.cm"$ ==
                            writeToFile$1997,12,"cmax_spec.cm"$(HANDLE$1997,24,"cmax_spec.cm"$, "\n"$1997,32,"cmax_spec.cm"$)
                        :
                            LET O$1998,9,"cmax_spec.cm"$ ==
                                outputMAXCode$1998,12,"cmax_spec.cm"$(CIL$1998,26,"cmax_spec.cm"$, PF$1998,31,"cmax_spec.cm"$, HANDLE$1998,35,"cmax_spec.cm"$)
                            :
                                IF$1999,7,"cmax_spec.cm"$ ! eq$0,0,"?"$[0$1999,8,"cmax_spec.cm"$, numsubterms$1999,12,"cmax_spec.cm"$(R$1999,10,"cmax_spec.cm"$)]:
                                    LET O$2000,11,"cmax_spec.cm"$ ==
                                        writeToFile$2000,14,"cmax_spec.cm"$(HANDLE$2000,26,"cmax_spec.cm"$, `$2000,35,"cmax_spec.cm"$ PF$2000,35,"cmax_spec.cm"$ "ELSE\n"$2000,38,"cmax_spec.cm"$  ')
                                    :
                                        outputMAXCode$2001,7,"cmax_spec.cm"$(R$2001,21,"cmax_spec.cm"$, `$2001,25,"cmax_spec.cm"$ PF$2001,25,"cmax_spec.cm"$ "    "$2001,28,"cmax_spec.cm"$  ', HANDLE$2001,37,"cmax_spec.cm"$)

                                ELSE
                                    true$2003,7,"cmax_spec.cm"$()







| is$2004,5,"cmax_spec.cm"$[D$2004,8,"cmax_spec.cm"$, _UpdateList$2004,11,"cmax_spec.cm"$] || is$2004,27,"cmax_spec.cm"$[D$2004,30,"cmax_spec.cm"$, _CaseIsList$2004,33,"cmax_spec.cm"$] :
    IF$2005,7,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$2005,10,"cmax_spec.cm"$(D$2005,8,"cmax_spec.cm"$), 0$2005,22,"cmax_spec.cm"$]:
        true$2005,25,"cmax_spec.cm"$()
    ELSE
        LET O$2007,11,"cmax_spec.cm"$ ==
            outputMAXCode$2007,14,"cmax_spec.cm"$(subterm$2007,28,"cmax_spec.cm"$(1$2007,36,"cmax_spec.cm"$, D$2007,39,"cmax_spec.cm"$), PF$2007,43,"cmax_spec.cm"$, HANDLE$2007,47,"cmax_spec.cm"$)
        :
            outputMAXCode$2008,7,"cmax_spec.cm"$(back$2008,21,"cmax_spec.cm"$(D$2008,26,"cmax_spec.cm"$), PF$2008,30,"cmax_spec.cm"$, HANDLE$2008,34,"cmax_spec.cm"$)

| is$2009,5,"cmax_spec.cm"$[D$2009,8,"cmax_spec.cm"$, _Update$2009,11,"cmax_spec.cm"$] :
    LET O$2010,9,"cmax_spec.cm"$ ==
        outputMAXCode$2010,12,"cmax_spec.cm"$(subterm$2010,26,"cmax_spec.cm"$(1$2010,34,"cmax_spec.cm"$, D$2010,37,"cmax_spec.cm"$), PF$2010,41,"cmax_spec.cm"$, HANDLE$2010,45,"cmax_spec.cm"$)
    :
        LET O$2011,9,"cmax_spec.cm"$ ==
            writeToFile$2011,12,"cmax_spec.cm"$(HANDLE$2011,24,"cmax_spec.cm"$, " := "$2011,32,"cmax_spec.cm"$)
        :
            LET O$2012,9,"cmax_spec.cm"$ ==
                outputMAXCode$2012,12,"cmax_spec.cm"$(subterm$2012,26,"cmax_spec.cm"$(2$2012,34,"cmax_spec.cm"$, D$2012,37,"cmax_spec.cm"$), ""$2012,41,"cmax_spec.cm"$, HANDLE$2012,45,"cmax_spec.cm"$)
            :
                writeToFile$2013,5,"cmax_spec.cm"$(HANDLE$2013,17,"cmax_spec.cm"$, "\n"$2013,25,"cmax_spec.cm"$)



| is$2014,5,"cmax_spec.cm"$[D$2014,8,"cmax_spec.cm"$, _CaseIs$2014,11,"cmax_spec.cm"$] :
    LET O$2015,9,"cmax_spec.cm"$ ==
        writeToFile$2015,12,"cmax_spec.cm"$(HANDLE$2015,24,"cmax_spec.cm"$, `$2015,33,"cmax_spec.cm"$ PF$2015,33,"cmax_spec.cm"$ "IS "$2015,36,"cmax_spec.cm"$  ')
    :
        LET O$2016,9,"cmax_spec.cm"$ ==
            outputMAXCode$2016,12,"cmax_spec.cm"$(subterm$2016,26,"cmax_spec.cm"$(1$2016,34,"cmax_spec.cm"$, D$2016,37,"cmax_spec.cm"$), ""$2016,41,"cmax_spec.cm"$, HANDLE$2016,45,"cmax_spec.cm"$)
        :
            LET O$2017,9,"cmax_spec.cm"$ ==
                writeToFile$2017,12,"cmax_spec.cm"$(HANDLE$2017,24,"cmax_spec.cm"$, " :\n"$2017,32,"cmax_spec.cm"$)
            :
                outputMAXCode$2018,5,"cmax_spec.cm"$(subterm$2018,19,"cmax_spec.cm"$(2$2018,27,"cmax_spec.cm"$, D$2018,30,"cmax_spec.cm"$), `$2018,35,"cmax_spec.cm"$ PF$2018,35,"cmax_spec.cm"$ "    "$2018,38,"cmax_spec.cm"$  ', HANDLE$2018,47,"cmax_spec.cm"$)



    ELSE
        out$2021,5,"cmax_spec.cm"$(`$2021,10,"cmax_spec.cm"$ "internal error in outputMAXCode: \n"$2021,10,"cmax_spec.cm"$ "    unknown sort "$2022,22,"cmax_spec.cm"$ sortof$2022,42,"cmax_spec.cm"$(D$2022,49,"cmax_spec.cm"$) "!\n"$2022,52,"cmax_spec.cm"$  ')
FCT outputCFile$2024,5,"cmax_spec.cm"$ ( Structure$2024,19,"cmax_spec.cm"$@ S$2024,30,"cmax_spec.cm"$ ) Bool$2024,33,"cmax_spec.cm"$ :
    IF$2027,5,"cmax_spec.cm"$ eq$0,0,"?"$[checkOption$2027,6,"cmax_spec.cm"$("nocode"$2027,18,"cmax_spec.cm"$), false$2027,28,"cmax_spec.cm"$()]:
        LET FILENAME$2028,9,"cmax_spec.cm"$ ==
            `$2028,22,"cmax_spec.cm"$ inputFilePath$2028,22,"cmax_spec.cm"$() "/"$2028,38,"cmax_spec.cm"$ idtos$2028,57,"cmax_spec.cm"$(term$2028,52,"cmax_spec.cm"$(fst$2028,48,"cmax_spec.cm"$(fst$2028,44,"cmax_spec.cm"$(S$2028,42,"cmax_spec.cm"$)))) "_solver.c"$2028,63,"cmax_spec.cm"$  '
        :
            LET HANDLE$2029,9,"cmax_spec.cm"$ ==
                openFile$2029,19,"cmax_spec.cm"$(FILENAME$2029,28,"cmax_spec.cm"$, "w"$2029,38,"cmax_spec.cm"$)
            :
                IF$2030,7,"cmax_spec.cm"$ eq$0,0,"?"$[greatereq$2030,8,"cmax_spec.cm"$(HANDLE$2030,18,"cmax_spec.cm"$, 0$2030,26,"cmax_spec.cm"$), true$2030,29,"cmax_spec.cm"$()]:
                    LET H1$2032,11,"cmax_spec.cm"$ ==
                        gen_C_all$2033,9,"cmax_spec.cm"$(S$2033,19,"cmax_spec.cm"$, HANDLE$2033,22,"cmax_spec.cm"$)
                    :
                        LET H2$2035,11,"cmax_spec.cm"$ ==
                            info$2035,15,"cmax_spec.cm"$(`$2035,21,"cmax_spec.cm"$ "File "$2035,21,"cmax_spec.cm"$ FILENAME$2035,29,"cmax_spec.cm"$ " written.\n"$2035,38,"cmax_spec.cm"$  ')
                        :
                            closeFile$2036,7,"cmax_spec.cm"$(HANDLE$2036,17,"cmax_spec.cm"$)


                ELSE
                    out$2038,7,"cmax_spec.cm"$("error: cannot open output file!\n"$2038,11,"cmax_spec.cm"$)


    ELSE
        true$2040,5,"cmax_spec.cm"$()
FCT codeForIdent$2047,5,"cmax_spec.cm"$ ( Term$2047,19,"cmax_spec.cm"$ T$2047,24,"cmax_spec.cm"$ ) String$2047,27,"cmax_spec.cm"$ :
    LET I$2050,7,"cmax_spec.cm"$ ==
        subterm$2050,10,"cmax_spec.cm"$(1$2050,18,"cmax_spec.cm"$, T$2050,21,"cmax_spec.cm"$)
    :
        LET LINE$2051,7,"cmax_spec.cm"$ ==
            subterm$2051,13,"cmax_spec.cm"$(2$2051,21,"cmax_spec.cm"$, T$2051,24,"cmax_spec.cm"$)
        :
            LET COL$2052,7,"cmax_spec.cm"$ ==
                subterm$2052,12,"cmax_spec.cm"$(3$2052,20,"cmax_spec.cm"$, T$2052,23,"cmax_spec.cm"$)
            :
                LET FILE$2053,7,"cmax_spec.cm"$ ==
                    subterm$2053,13,"cmax_spec.cm"$(4$2053,21,"cmax_spec.cm"$, T$2053,24,"cmax_spec.cm"$)
                :
                    LET H$2054,7,"cmax_spec.cm"$ ==
                        IF$2055,5,"cmax_spec.cm"$ eq$0,0,"?"$[checkOption$2055,6,"cmax_spec.cm"$("nosrcpos"$2055,18,"cmax_spec.cm"$), true$2055,30,"cmax_spec.cm"$()]:
                            idtos$2056,7,"cmax_spec.cm"$(I$2056,5,"cmax_spec.cm"$)
                        ELSE
                            `$2058,6,"cmax_spec.cm"$ idtos$2058,8,"cmax_spec.cm"$(I$2058,6,"cmax_spec.cm"$) scp$2058,14,"cmax_spec.cm"$(T$2058,18,"cmax_spec.cm"$)  '
                    :
                        IF$2060,5,"cmax_spec.cm"$ is$2060,6,"cmax_spec.cm"$[T$2060,9,"cmax_spec.cm"$, _NodeSortId$2060,12,"cmax_spec.cm"$]:
                            `$2061,6,"cmax_spec.cm"$ H$2061,6,"cmax_spec.cm"$ "@"$2061,8,"cmax_spec.cm"$  '
                        ELSE
                            H$2063,5,"cmax_spec.cm"$





FCT scp$2065,5,"cmax_spec.cm"$ ( Term$2065,11,"cmax_spec.cm"$ T$2065,16,"cmax_spec.cm"$ ) String$2065,19,"cmax_spec.cm"$ :
    LET L$2066,7,"cmax_spec.cm"$ ==
        subterm$2066,10,"cmax_spec.cm"$(2$2066,18,"cmax_spec.cm"$, T$2066,21,"cmax_spec.cm"$)
    :
        LET C$2067,7,"cmax_spec.cm"$ ==
            subterm$2067,10,"cmax_spec.cm"$(3$2067,18,"cmax_spec.cm"$, T$2067,21,"cmax_spec.cm"$)
        :
            LET F$2068,7,"cmax_spec.cm"$ ==
                subterm$2068,10,"cmax_spec.cm"$(4$2068,18,"cmax_spec.cm"$, T$2068,21,"cmax_spec.cm"$)
            :
                scp1$2069,3,"cmax_spec.cm"$(L$2069,8,"cmax_spec.cm"$, C$2069,10,"cmax_spec.cm"$, F$2069,12,"cmax_spec.cm"$)



FCT scp1$2071,5,"cmax_spec.cm"$ ( Int$2071,12,"cmax_spec.cm"$ L$2071,16,"cmax_spec.cm"$, Int$2071,19,"cmax_spec.cm"$ C$2071,23,"cmax_spec.cm"$, String$2071,26,"cmax_spec.cm"$ F$2071,33,"cmax_spec.cm"$ ) String$2071,36,"cmax_spec.cm"$ :
    `$2072,4,"cmax_spec.cm"$ "$"$2072,4,"cmax_spec.cm"$ itos$2072,10,"cmax_spec.cm"$(L$2072,8,"cmax_spec.cm"$) ","$2072,15,"cmax_spec.cm"$ itos$2072,21,"cmax_spec.cm"$(C$2072,19,"cmax_spec.cm"$) ",\""$2072,26,"cmax_spec.cm"$ F$2072,32,"cmax_spec.cm"$ "\"$"$2072,34,"cmax_spec.cm"$  '
FCT codeForSortIdList$2074,5,"cmax_spec.cm"$ ( SortIdList$2074,24,"cmax_spec.cm"$ SIDL$2074,35,"cmax_spec.cm"$, String$2074,41,"cmax_spec.cm"$ SEP$2074,48,"cmax_spec.cm"$ ) String$2074,53,"cmax_spec.cm"$ :
    IF$2075,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$2075,11,"cmax_spec.cm"$(SIDL$2075,6,"cmax_spec.cm"$), 0$2075,25,"cmax_spec.cm"$]:
        ""$2075,28,"cmax_spec.cm"$
    ELSE
        LET SID$2077,9,"cmax_spec.cm"$ ==
            subterm$2077,14,"cmax_spec.cm"$(1$2077,22,"cmax_spec.cm"$, SIDL$2077,25,"cmax_spec.cm"$)
        :
            LET I$2078,9,"cmax_spec.cm"$ ==
                codeForIdent$2078,16,"cmax_spec.cm"$(SID$2078,12,"cmax_spec.cm"$)
            :
                LET REST$2079,9,"cmax_spec.cm"$ ==
                    back$2079,20,"cmax_spec.cm"$(SIDL$2079,15,"cmax_spec.cm"$)
                :
                    IF$2080,7,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$2080,13,"cmax_spec.cm"$(REST$2080,8,"cmax_spec.cm"$), 0$2080,27,"cmax_spec.cm"$]:
                        I$2081,7,"cmax_spec.cm"$
                    ELSE
                        `$2083,8,"cmax_spec.cm"$ I$2083,8,"cmax_spec.cm"$ SEP$2083,10,"cmax_spec.cm"$ codeForSortIdList$2083,14,"cmax_spec.cm"$(REST$2083,32,"cmax_spec.cm"$, SEP$2083,38,"cmax_spec.cm"$)  '



FCT codeForParList$2085,5,"cmax_spec.cm"$ ( SortIdList$2085,21,"cmax_spec.cm"$ SIDL$2085,32,"cmax_spec.cm"$, NameList$2085,38,"cmax_spec.cm"$ NL$2085,47,"cmax_spec.cm"$ ) String$2085,51,"cmax_spec.cm"$ :
    IF$2086,5,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$2086,11,"cmax_spec.cm"$(SIDL$2086,6,"cmax_spec.cm"$), numsubterms$2086,28,"cmax_spec.cm"$(NL$2086,25,"cmax_spec.cm"$)]:
        IF$2087,7,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$2087,13,"cmax_spec.cm"$(SIDL$2087,8,"cmax_spec.cm"$), 0$2087,27,"cmax_spec.cm"$]:
            ""$2088,7,"cmax_spec.cm"$
        ELSE
            LET SID$2090,11,"cmax_spec.cm"$ ==
                subterm$2090,16,"cmax_spec.cm"$(1$2090,24,"cmax_spec.cm"$, SIDL$2090,27,"cmax_spec.cm"$)
            :
                LET N$2091,11,"cmax_spec.cm"$ ==
                    subterm$2091,14,"cmax_spec.cm"$(1$2091,22,"cmax_spec.cm"$, NL$2091,25,"cmax_spec.cm"$)
                :
                    LET S1$2092,11,"cmax_spec.cm"$ ==
                        codeForIdent$2092,19,"cmax_spec.cm"$(SID$2092,15,"cmax_spec.cm"$)
                    :
                        LET S2$2093,11,"cmax_spec.cm"$ ==
                            codeForIdent$2093,17,"cmax_spec.cm"$(N$2093,15,"cmax_spec.cm"$)
                        :
                            IF$2094,9,"cmax_spec.cm"$ eq$0,0,"?"$[numsubterms$2094,20,"cmax_spec.cm"$(back$2094,15,"cmax_spec.cm"$(SIDL$2094,10,"cmax_spec.cm"$)), 0$2094,34,"cmax_spec.cm"$]:
                                `$2095,10,"cmax_spec.cm"$ S1$2095,10,"cmax_spec.cm"$ " "$2095,13,"cmax_spec.cm"$ S2$2095,17,"cmax_spec.cm"$  '
                            ELSE
                                `$2097,10,"cmax_spec.cm"$ S1$2097,10,"cmax_spec.cm"$ " "$2097,13,"cmax_spec.cm"$ S2$2097,17,"cmax_spec.cm"$ ", "$2097,20,"cmax_spec.cm"$ codeForParList$2098,10,"cmax_spec.cm"$(back$2098,30,"cmax_spec.cm"$(SIDL$2098,25,"cmax_spec.cm"$), back$2098,39,"cmax_spec.cm"$(NL$2098,36,"cmax_spec.cm"$))  '




    ELSE
        LET O$2100,9,"cmax_spec.cm"$ ==
            out$2100,12,"cmax_spec.cm"$(`$2100,17,"cmax_spec.cm"$ "internal error in FCT codeForParList: lists have "$2100,17,"cmax_spec.cm"$ "not the same length!\n"$2101,11,"cmax_spec.cm"$  ')
        :
            ""$2102,7,"cmax_spec.cm"$

FCT scpinfo1$2108,5,"cmax_spec.cm"$ ( Node$2108,14,"cmax_spec.cm"$ ID$2108,19,"cmax_spec.cm"$ ) String$2108,23,"cmax_spec.cm"$ :
    `$2109,4,"cmax_spec.cm"$ "       \n(file: "$2109,4,"cmax_spec.cm"$ fileOfId$2109,26,"cmax_spec.cm"$(ID$2109,23,"cmax_spec.cm"$) " / line: "$2109,35,"cmax_spec.cm"$ itos$2109,59,"cmax_spec.cm"$(lineOfId$2109,50,"cmax_spec.cm"$(ID$2109,47,"cmax_spec.cm"$)) ")\n"$2109,64,"cmax_spec.cm"$  '
FCT scpinfo2$2111,5,"cmax_spec.cm"$ ( Node$2111,14,"cmax_spec.cm"$ ID$2111,19,"cmax_spec.cm"$ ) String$2111,23,"cmax_spec.cm"$ :
    `$2112,4,"cmax_spec.cm"$ "       \n(ident: "$2112,4,"cmax_spec.cm"$ idToStr$2112,27,"cmax_spec.cm"$(ID$2112,24,"cmax_spec.cm"$) " / file: "$2112,35,"cmax_spec.cm"$ fileOfId$2112,50,"cmax_spec.cm"$(ID$2112,47,"cmax_spec.cm"$) " / line: "$2113,4,"cmax_spec.cm"$ itos$2113,28,"cmax_spec.cm"$(lineOfId$2113,19,"cmax_spec.cm"$(ID$2113,16,"cmax_spec.cm"$)) ")\n"$2113,33,"cmax_spec.cm"$  '
CND VarDecl$2116,5,"cmax_spec.cm"$@< ID$2116,14,"cmax_spec.cm"$, SIDL$2116,17,"cmax_spec.cm"$, NL$2116,22,"cmax_spec.cm"$,_,_,_>:
    eq$0,0,"?"$[numsons$2117,8,"cmax_spec.cm"$(SIDL$2117,3,"cmax_spec.cm"$), 1$2117,16,"cmax_spec.cm"$]
    |
    LET E$2118,9,"cmax_spec.cm"$ ==
        error$2118,12,"cmax_spec.cm"$()
    :
        `$2119,6,"cmax_spec.cm"$ "error: Variable can only be assigned to single nodesort "$2119,6,"cmax_spec.cm"$ scpinfo2$2120,6,"cmax_spec.cm"$(ID$2120,15,"cmax_spec.cm"$)  '

CND VarDecl$2122,5,"cmax_spec.cm"$@< ID$2122,14,"cmax_spec.cm"$,< SID$2122,19,"cmax_spec.cm"$,*>,_,_,_,_>:
    is$2123,3,"cmax_spec.cm"$[SID$2123,6,"cmax_spec.cm"$, _NodeSortId$2123,11,"cmax_spec.cm"$@] || eq$0,0,"?"$[idToStr$2123,32,"cmax_spec.cm"$(SID$2123,28,"cmax_spec.cm"$), "Node"$2123,40,"cmax_spec.cm"$]
    |
    LET E$2124,9,"cmax_spec.cm"$ ==
        error$2124,12,"cmax_spec.cm"$()
    :
        `$2125,6,"cmax_spec.cm"$ "error: given sort is not a node sort"$2125,6,"cmax_spec.cm"$ scpinfo2$2125,45,"cmax_spec.cm"$(SID$2125,54,"cmax_spec.cm"$)  '

CND Name$2127,5,"cmax_spec.cm"$@< I$2127,12,"cmax_spec.cm"$,*>N$2127,17,"cmax_spec.cm"$:
    ! eq$0,0,"?"$[enclAssnList$2127,22,"cmax_spec.cm"$(N$2127,20,"cmax_spec.cm"$), nil$2127,37,"cmax_spec.cm"$()] && eq$0,0,"?"$[enclPattern$2127,48,"cmax_spec.cm"$(N$2127,46,"cmax_spec.cm"$), nil$2127,62,"cmax_spec.cm"$()] && ! is$2128,24,"cmax_spec.cm"$[fath$2128,29,"cmax_spec.cm"$(N$2128,27,"cmax_spec.cm"$), _LetAssn$2128,35,"cmax_spec.cm"$@] -> eq$0,0,"?"$[iselem$2129,20,"cmax_spec.cm"$(term$2129,29,"cmax_spec.cm"$(I$2129,27,"cmax_spec.cm"$), bound_names$2129,50,"cmax_spec.cm"$(enclAssnList$2129,37,"cmax_spec.cm"$(N$2129,35,"cmax_spec.cm"$))), true$2129,63,"cmax_spec.cm"$()]
    |
    LET E$2130,9,"cmax_spec.cm"$ ==
        error$2130,12,"cmax_spec.cm"$()
    :
        `$2131,6,"cmax_spec.cm"$ "error: undeclared identifier "$2131,6,"cmax_spec.cm"$ scpinfo2$2132,6,"cmax_spec.cm"$(N$2132,15,"cmax_spec.cm"$)  '

CND LeqConstr$2139,5,"cmax_spec.cm"$@<_,< I$2139,19,"cmax_spec.cm"$,_>VE$2139,24,"cmax_spec.cm"$>:
    is$2139,29,"cmax_spec.cm"$[Decl$2139,34,"cmax_spec.cm"$(I$2139,32,"cmax_spec.cm"$), _VarDecl$2139,40,"cmax_spec.cm"$@]
    |
    LET E$2140,9,"cmax_spec.cm"$ ==
        error$2140,12,"cmax_spec.cm"$()
    :
        `$2141,6,"cmax_spec.cm"$ "error: right-hand-side of <= constraint is no variable "$2141,6,"cmax_spec.cm"$ scpinfo2$2142,6,"cmax_spec.cm"$(I$2142,15,"cmax_spec.cm"$)  '

CND GeqConstr$2144,5,"cmax_spec.cm"$@<_,< I$2144,19,"cmax_spec.cm"$,_>VE$2144,24,"cmax_spec.cm"$>:
    is$2144,29,"cmax_spec.cm"$[Decl$2144,34,"cmax_spec.cm"$(I$2144,32,"cmax_spec.cm"$), _VarDecl$2144,40,"cmax_spec.cm"$@]
    |
    LET E$2145,9,"cmax_spec.cm"$ ==
        error$2145,12,"cmax_spec.cm"$()
    :
        `$2146,6,"cmax_spec.cm"$ "error: right-hand-side of >= constraint is no variable "$2146,6,"cmax_spec.cm"$ scpinfo2$2147,6,"cmax_spec.cm"$(I$2147,15,"cmax_spec.cm"$)  '

CND LeqConstr$2154,5,"cmax_spec.cm"$@<_,< I$2154,19,"cmax_spec.cm"$,_>VE$2154,24,"cmax_spec.cm"$>:
    is$2154,29,"cmax_spec.cm"$[Decl$2154,34,"cmax_spec.cm"$(I$2154,32,"cmax_spec.cm"$), _VarDecl$2154,40,"cmax_spec.cm"$@] -> eq$0,0,"?"$[is_leq_var$2154,54,"cmax_spec.cm"$(Decl$2154,67,"cmax_spec.cm"$(I$2154,65,"cmax_spec.cm"$)), true$2154,73,"cmax_spec.cm"$()]
    |
    LET E$2155,9,"cmax_spec.cm"$ ==
        error$2155,12,"cmax_spec.cm"$()
    :
        `$2156,6,"cmax_spec.cm"$ "error: <= constraint cannot be used with this variable "$2156,6,"cmax_spec.cm"$ scpinfo2$2157,6,"cmax_spec.cm"$(I$2157,15,"cmax_spec.cm"$)  '

CND GeqConstr$2159,5,"cmax_spec.cm"$@<_,< I$2159,19,"cmax_spec.cm"$,_>VE$2159,24,"cmax_spec.cm"$>:
    is$2159,29,"cmax_spec.cm"$[Decl$2159,34,"cmax_spec.cm"$(I$2159,32,"cmax_spec.cm"$), _VarDecl$2159,40,"cmax_spec.cm"$@] -> eq$0,0,"?"$[is_geq_var$2159,54,"cmax_spec.cm"$(Decl$2159,67,"cmax_spec.cm"$(I$2159,65,"cmax_spec.cm"$)), true$2159,73,"cmax_spec.cm"$()]
    |
    LET E$2160,9,"cmax_spec.cm"$ ==
        error$2160,12,"cmax_spec.cm"$()
    :
        `$2161,6,"cmax_spec.cm"$ "error: >= constraint cannot be used with this variable "$2161,6,"cmax_spec.cm"$ scpinfo2$2162,6,"cmax_spec.cm"$(I$2162,15,"cmax_spec.cm"$)  '

CND UsedId$2164,5,"cmax_spec.cm"$@ I$2164,13,"cmax_spec.cm"$:
    ! eq$0,0,"?"$[Decl$2164,18,"cmax_spec.cm"$(I$2164,16,"cmax_spec.cm"$), nil$2164,23,"cmax_spec.cm"$()]
    |
    LET E$2165,9,"cmax_spec.cm"$ ==
        error$2165,12,"cmax_spec.cm"$()
    :
        `$2166,6,"cmax_spec.cm"$ "error: Identifier not declared"$2166,6,"cmax_spec.cm"$ scpinfo2$2166,39,"cmax_spec.cm"$(I$2166,48,"cmax_spec.cm"$)  '

CND DefAssnAppl$2168,5,"cmax_spec.cm"$@< ID$2168,18,"cmax_spec.cm"$, EL$2168,21,"cmax_spec.cm"$>A$2168,25,"cmax_spec.cm"$:
    eq$0,0,"?"$[numsons$2168,31,"cmax_spec.cm"$(EL$2168,28,"cmax_spec.cm"$), numsons$2168,51,"cmax_spec.cm"$(thd$2168,47,"cmax_spec.cm"$(Decl$2168,42,"cmax_spec.cm"$(ID$2168,39,"cmax_spec.cm"$)))]
    |
    LET E$2169,9,"cmax_spec.cm"$ ==
        error$2169,12,"cmax_spec.cm"$()
    :
        `$2170,6,"cmax_spec.cm"$ "error: Application of user defined Assertion with "$2170,6,"cmax_spec.cm"$ "wrong nr. of arguments"$2171,6,"cmax_spec.cm"$ scpinfo2$2171,31,"cmax_spec.cm"$(ID$2171,40,"cmax_spec.cm"$)  '

CND FuncAppl$2173,5,"cmax_spec.cm"$@< ID$2173,15,"cmax_spec.cm"$, EL$2173,18,"cmax_spec.cm"$>:
    is$2173,23,"cmax_spec.cm"$[Decl$2173,29,"cmax_spec.cm"$(ID$2173,26,"cmax_spec.cm"$), _FctOrAtt$2173,34,"cmax_spec.cm"$@] -> eq$0,0,"?"$[numsons$2173,52,"cmax_spec.cm"$(EL$2173,49,"cmax_spec.cm"$), numsons$2173,72,"cmax_spec.cm"$(snd$2173,68,"cmax_spec.cm"$(Decl$2173,63,"cmax_spec.cm"$(ID$2173,60,"cmax_spec.cm"$)))]
    |
    LET E$2174,9,"cmax_spec.cm"$ ==
        error$2174,12,"cmax_spec.cm"$()
    :
        `$2175,6,"cmax_spec.cm"$ "error: identifier used with "$2175,6,"cmax_spec.cm"$ "wrong number of arguments"$2176,6,"cmax_spec.cm"$ scpinfo2$2176,34,"cmax_spec.cm"$(ID$2176,43,"cmax_spec.cm"$)  '

CND FuncAppl$2178,5,"cmax_spec.cm"$@< ID$2178,15,"cmax_spec.cm"$, EL$2178,18,"cmax_spec.cm"$>:
    is$2178,23,"cmax_spec.cm"$[Decl$2178,29,"cmax_spec.cm"$(ID$2178,26,"cmax_spec.cm"$), _TupelProd$2178,34,"cmax_spec.cm"$@] -> eq$0,0,"?"$[numsons$2178,53,"cmax_spec.cm"$(EL$2178,50,"cmax_spec.cm"$), numsons$2178,73,"cmax_spec.cm"$(snd$2178,69,"cmax_spec.cm"$(Decl$2178,64,"cmax_spec.cm"$(ID$2178,61,"cmax_spec.cm"$)))]
    |
    LET E$2179,9,"cmax_spec.cm"$ ==
        error$2179,12,"cmax_spec.cm"$()
    :
        `$2180,6,"cmax_spec.cm"$ "error: constructor used with "$2180,6,"cmax_spec.cm"$ "wrong number of arguments"$2181,6,"cmax_spec.cm"$ scpinfo2$2181,34,"cmax_spec.cm"$(ID$2181,43,"cmax_spec.cm"$)  '

CND FuncAppl$2183,5,"cmax_spec.cm"$@< ID$2183,15,"cmax_spec.cm"$, EL$2183,18,"cmax_spec.cm"$>:
    is$2183,23,"cmax_spec.cm"$[Decl$2183,29,"cmax_spec.cm"$(ID$2183,26,"cmax_spec.cm"$), _ListProd$2183,34,"cmax_spec.cm"$@] -> eq$0,0,"?"$[numsons$2183,52,"cmax_spec.cm"$(EL$2183,49,"cmax_spec.cm"$), 0$2183,60,"cmax_spec.cm"$]
    |
    LET E$2184,9,"cmax_spec.cm"$ ==
        error$2184,12,"cmax_spec.cm"$()
    :
        `$2185,6,"cmax_spec.cm"$ "error: no arguments allowed for list constructor"$2185,6,"cmax_spec.cm"$ scpinfo2$2185,57,"cmax_spec.cm"$(ID$2185,66,"cmax_spec.cm"$)  '

}

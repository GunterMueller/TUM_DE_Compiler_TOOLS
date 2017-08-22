/*=-= The following definitions up to the ***-line aren't relevant for  =-=*/
/*=-= users; they constitute the interface to  max_std                  =-=*/

typedef long         mxi_ELEMENT;
extern  long         mxi_conv_error;
extern  mxi_ELEMENT  mxi_btoe( char*, int, long );
extern  long         mxi_etob( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_ctoe( char*, int, char );
extern  char         mxi_etoc( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_itoe( char*, int, int );
extern  long         mxi_etoi( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_ptoe( char*, int, void*);
extern  void*        mxi_etop( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_atoe( char*, int, char*);
extern  char*        mxi_etoa( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_stoid( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_idtos( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_sort( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_number( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_index( char*, int, mxi_ELEMENT, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_element( char*, int, mxi_ELEMENT, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_numsubterms( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_subterm( char*, int, mxi_ELEMENT, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_front( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_back( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_appfront( char*, int, mxi_ELEMENT, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_appback( char*, int, mxi_ELEMENT, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_conc( char*, int, mxi_ELEMENT, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_tc(char*,int,char*,int,int,...);
extern  mxi_ELEMENT  mxi_fath  ( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_lbroth( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_rbroth( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_term( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_numsons( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_son( char*, int, mxi_ELEMENT, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_before( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_after( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_node( char*, int, mxi_ELEMENT );
extern  long         mxi_is( char*, int, mxi_ELEMENT, mxi_ELEMENT );
extern  long         mxi_eq( char*, int, mxi_ELEMENT, mxi_ELEMENT );
extern  long         mxi_init( char*, int, int, mxi_ELEMENT );
extern  long         mxi_free( char*, int );

/***************************************************************************/

/*  The C-type for all elements of the MAX-universe including  nil :       */
#define  ELEMENT            mxi_ELEMENT

/*  The following functions convert C-values to corresponding MAX-elements */
/*  in case of an error, the functions set the global variable conv_error  */
/*  to 0 and yield  nil.                                                   */
#define  conv_error          mxi_conv_error        
#define  btoe(BOOLVAL)       mxi_btoe(__FILE__,__LINE__,BOOLVAL)
#define  ctoe(CHARVAL)       mxi_ctoe(__FILE__,__LINE__,CHARVAL)
#define  itoe(INTVAL)        mxi_itoe(__FILE__,__LINE__,INTVAL)
#define  atoe(STRVAL)        mxi_atoe(__FILE__,__LINE__,STRVAL)
#define  ptoe(POINTVAL)      mxi_ptoe(__FILE__,__LINE__,POINTVAL)

/*  The following functions convert MAX-elements to corresponding C-values */
/*  in case of an error, the functions set the global variable conv_error  */
/*  to 0 and yield  0, '\0', 0, the empty string or NULL.                 */
#define  etob(BOOLELEM)      mxi_etob(__FILE__,__LINE__,BOOLELEM)
#define  etoc(CHARELEM)      mxi_etoc(__FILE__,__LINE__,CHARELEM)
#define  etoi(INTELEM)       mxi_etoi(__FILE__,__LINE__,INTELEM)
#define  etoa(STRELEM)       mxi_etoa(__FILE__,__LINE__,STRELEM)
#define  etop(REFELEM)       mxi_etop(__FILE__,__LINE__,REFELEM)

/*  stoid  enters a string into sort  Ident  containing a finite set of    */
/*  hash-coded strings;  idtos  returns the string of an identifier        */
#define  stoid(STRING)       mxi_stoid(__FILE__,__LINE__,STRING)
#define  idtos(IDENT)        mxi_idtos(__FILE__,__LINE__,IDENT)

/*  sort  returns the sort constant of a defined element; otherwise exits. */
#define  sort(ELEM)          mxi_sort(__FILE__,__LINE__,ELEM)
#define  index(ELEM,SORT)    mxi_index(__FILE__,__LINE__,ELEM,SORT)
#define  element(INDEX,SORT) mxi_element(__FILE__,__LINE__,INDEX,SORT)
#define  number(SORT)        mxi_number(__FILE__,__LINE__,SORT)

/*  The following functions provide the inspection of the tree structure; */
/*  if their obvious meaning is not defined, they return  nil :           */
#define  fath(NODE)          mxi_fath(__FILE__,__LINE__,NODE)
#define  lbroth(NODE)        mxi_lbroth(__FILE__,__LINE__,NODE)
#define  rbroth(NODE)        mxi_rbroth(__FILE__,__LINE__,NODE)
#define  son(ITH,NODE)       mxi_son(__FILE__,__LINE__,ITH,NODE)
#define  numsons(NODE)       mxi_numsons(__FILE__,__LINE__,NODE)

/*  subterm(i,t)  returns the ith subterm of term t;  numsubterms(t)      */
/*  returns the number of subterms t; both functions exit on failure      */
#define  subterm(ITH,TERM)   mxi_subterm(__FILE__,__LINE__,ITH,TERM)
#define  numsubterms(TERM)   mxi_numsubterms(__FILE__,__LINE__,TERM)

/*  The following functions provide the polymorphic handling of lists;    */
/*  they exit on failure :                                                */
#define  front(LIST)         mxi_front(__FILE__,__LINE__,LIST)
#define  back(LIST)          mxi_back(__FILE__,__LINE__,LIST)
#define  appfront(ELEM,LIST) mxi_appfront(__FILE__,__LINE__,ELEM,LIST)
#define  appback(LIST,ELEM)  mxi_appback(__FILE__,__LINE__,LIST,ELEM)
#define  conc(LIST1,LIST2)   mxi_conc(__FILE__,__LINE__,LIST1,LIST2)

/*  The following functions relate nodes to the corresponding terms and   */
/*  points; they exit on failure :                                        */
#define  term(NODE)          mxi_term(__FILE__,__LINE__,NODE)
#define  before(NODE)        mxi_before(__FILE__,__LINE__,NODE)
#define  after(NODE)         mxi_after(__FILE__,__LINE__,NODE)
#define  node(POINT)         mxi_node(__FILE__,__LINE__,POINT)

/*  eq  is the equality predicate;  is  tests whether an element is in    */
/*  the given sort;  desc  tests whether node1 is the desendant of node2; */
/*  bef  and  aft  establish the linear order on  points :                */
#define  eq(ELEM1,ELEM2)     mxi_eq(__FILE__,__LINE__,ELEM1,ELEM2)
#define  is(ELEM,SORT)       mxi_is(__FILE__,__LINE__,ELEM,SORT)
#define  desc(N1,N2)         (before(N1)>before(N2) && after(N1)<after(N2))
#define  bef(P1,P2)          (is(P1,_Point) && is(P2,_Point) && P1<P2)
#define  aft(P1,P2)          (is(P1,_Point) && is(P2,_Point) && P1>P2)

/*  The predefined constants are :                                        */
#define  minimalInt()   -16777216L
#define  maximalInt()   16777215L

#define  root()         -939524095L
#define  true()         -268435455L
#define  false()        -268435456L
#define  nil()          -536805377L
/*  The sort constants :                                                  */
#define  _Specification 		 -469696563L	/* -51 */
#define  _Specification_		 -469761997L	/* 51 */
#define  _ProdList 		 -469696564L	/* -52 */
#define  _ProdList_		 -469761996L	/* 52 */
#define  _SortIdList 		 -469696565L	/* -53 */
#define  _SortIdList_		 -469761995L	/* 53 */
#define  _LocalDeclList 		 -469696566L	/* -54 */
#define  _LocalDeclList_		 -469761994L	/* 54 */
#define  _PredList 		 -469696567L	/* -55 */
#define  _PredList_		 -469761993L	/* 55 */
#define  _FuncList 		 -469696568L	/* -56 */
#define  _FuncList_		 -469761992L	/* 56 */
#define  _AttrList 		 -469696569L	/* -57 */
#define  _AttrList_		 -469761991L	/* 57 */
#define  _CondList 		 -469696570L	/* -58 */
#define  _CondList_		 -469761990L	/* 58 */
#define  _PatternList 		 -469696571L	/* -59 */
#define  _PatternList_		 -469761989L	/* 59 */
#define  _ExprList 		 -469696572L	/* -60 */
#define  _ExprList_		 -469761988L	/* 60 */
#define  _PatternCaseList 		 -469696573L	/* -61 */
#define  _PatternCaseList_		 -469761987L	/* 61 */
#define  _FormulaCaseList 		 -469696574L	/* -62 */
#define  _FormulaCaseList_		 -469761986L	/* 62 */
#define  _ItemList 		 -469696575L	/* -63 */
#define  _ItemList_		 -469761985L	/* 63 */
#define  _NameList 		 -469696576L	/* -64 */
#define  _NameList_		 -469761984L	/* 64 */
#define  _DefIdNodeList 		 -469696577L	/* -65 */
#define  _DefIdNodeList_		 -469761983L	/* 65 */
#define  _CompExprNodeList 		 -469696578L	/* -66 */
#define  _CompExprNodeList_		 -469761982L	/* 66 */
#define  _ListProd 		 -469696526L	/* -14 */
#define  _ListProd_		 -469762034L	/* 14 */
#define  _TupelProd 		 -469696527L	/* -15 */
#define  _TupelProd_		 -469762033L	/* 15 */
#define  _ClassProd 		 -469696528L	/* -16 */
#define  _ClassProd_		 -469762032L	/* 16 */
#define  _PredeclProd 		 -469696529L	/* -17 */
#define  _PredeclProd_		 -469762031L	/* 17 */
#define  _PredDecl 		 -469696530L	/* -18 */
#define  _PredDecl_		 -469762030L	/* 18 */
#define  _FuncDecl 		 -469696531L	/* -19 */
#define  _FuncDecl_		 -469762029L	/* 19 */
#define  _Structure 		 -469696532L	/* -20 */
#define  _Structure_		 -469762028L	/* 20 */
#define  _Predicate 		 -469696533L	/* -21 */
#define  _Predicate_		 -469762027L	/* 21 */
#define  _Function 		 -469696534L	/* -22 */
#define  _Function_		 -469762026L	/* 22 */
#define  _Attribute 		 -469696535L	/* -23 */
#define  _Attribute_		 -469762025L	/* 23 */
#define  _Condition 		 -469696536L	/* -24 */
#define  _Condition_		 -469762024L	/* 24 */
#define  _AttrDecl 		 -469696537L	/* -25 */
#define  _AttrDecl_		 -469762023L	/* 25 */
#define  _SortConst 		 -469696538L	/* -26 */
#define  _SortConst_		 -469762022L	/* 26 */
#define  _FuncAppl 		 -469696539L	/* -27 */
#define  _FuncAppl_		 -469762021L	/* 27 */
#define  _IfExpr 		 -469696540L	/* -28 */
#define  _IfExpr_		 -469762020L	/* 28 */
#define  _LetExpr 		 -469696541L	/* -29 */
#define  _LetExpr_		 -469762019L	/* 29 */
#define  _StringExpr 		 -469696542L	/* -30 */
#define  _StringExpr_		 -469762018L	/* 30 */
#define  _PatternCase 		 -469696543L	/* -31 */
#define  _PatternCase_		 -469762017L	/* 31 */
#define  _FormulaCase 		 -469696544L	/* -32 */
#define  _FormulaCase_		 -469762016L	/* 32 */
#define  _PredAppl 		 -469696545L	/* -33 */
#define  _PredAppl_		 -469762015L	/* 33 */
#define  _Or 		 -469696546L	/* -34 */
#define  _Or_		 -469762014L	/* 34 */
#define  _And 		 -469696547L	/* -35 */
#define  _And_		 -469762013L	/* 35 */
#define  _Impl 		 -469696548L	/* -36 */
#define  _Impl_		 -469762012L	/* 36 */
#define  _Neg 		 -469696549L	/* -37 */
#define  _Neg_		 -469762011L	/* 37 */
#define  _Pattern 		 -469696550L	/* -38 */
#define  _Pattern_		 -469762010L	/* 38 */
#define  _DefId 		 -469696551L	/* -39 */
#define  _DefId_		 -469762009L	/* 39 */
#define  _TermSortId 		 -469696552L	/* -40 */
#define  _TermSortId_		 -469762008L	/* 40 */
#define  _NodeSortId 		 -469696553L	/* -41 */
#define  _NodeSortId_		 -469762007L	/* 41 */
#define  _ApplId 		 -469696554L	/* -42 */
#define  _ApplId_		 -469762006L	/* 42 */
#define  _Name 		 -469696555L	/* -43 */
#define  _Name_		 -469762005L	/* 43 */
#define  _Blank 		 -469696556L	/* -44 */
#define  _Blank_		 -469762004L	/* 44 */
#define  _Asterisk 		 -469696557L	/* -45 */
#define  _Asterisk_		 -469762003L	/* 45 */
#define  _ParTup 		 -469696558L	/* -46 */
#define  _ParTup_		 -469762002L	/* 46 */
#define  _NameDepthTup 		 -469696559L	/* -47 */
#define  _NameDepthTup_		 -469762001L	/* 47 */
#define  _RelPosition 		 -469696560L	/* -48 */
#define  _RelPosition_		 -469762000L	/* 48 */
#define  _AbsPosition 		 -469696561L	/* -49 */
#define  _AbsPosition_		 -469761999L	/* 49 */
#define  _TopPosition 		 -469696562L	/* -50 */
#define  _TopPosition_		 -469761998L	/* 50 */
#define  _Element 		 -469696579L	/* -67 */
#define  _Element_		 -469761981L	/* 67 */
#define  _GlobalDecl 		 -469696580L	/* -68 */
#define  _GlobalDecl_		 -469761980L	/* 68 */
#define  _Production 		 -469696581L	/* -69 */
#define  _Production_		 -469761979L	/* 69 */
#define  _LocalDecl 		 -469696582L	/* -70 */
#define  _LocalDecl_		 -469761978L	/* 70 */
#define  _Expr 		 -469696583L	/* -71 */
#define  _Expr_		 -469761977L	/* 71 */
#define  _Constant 		 -469696584L	/* -72 */
#define  _Constant_		 -469761976L	/* 72 */
#define  _ComposedExpr 		 -469696585L	/* -73 */
#define  _ComposedExpr_		 -469761975L	/* 73 */
#define  _CaseList 		 -469696586L	/* -74 */
#define  _CaseList_		 -469761974L	/* 74 */
#define  _Formula 		 -469696587L	/* -75 */
#define  _Formula_		 -469761973L	/* 75 */
#define  _SortPos 		 -469696588L	/* -76 */
#define  _SortPos_		 -469761972L	/* 76 */
#define  _SubPatternPos 		 -469696589L	/* -77 */
#define  _SubPatternPos_		 -469761971L	/* 77 */
#define  _NamePos 		 -469696590L	/* -78 */
#define  _NamePos_		 -469761970L	/* 78 */
#define  _Item 		 -469696591L	/* -79 */
#define  _Item_		 -469761969L	/* 79 */
#define  _UsedId 		 -469696592L	/* -80 */
#define  _UsedId_		 -469761968L	/* 80 */
#define  _SortId 		 -469696593L	/* -81 */
#define  _SortId_		 -469761967L	/* 81 */
#define  _Declaration 		 -469696594L	/* -82 */
#define  _Declaration_		 -469761966L	/* 82 */
#define  _Definition 		 -469696595L	/* -83 */
#define  _Definition_		 -469761965L	/* 83 */
#define  _ApplyEntity 		 -469696596L	/* -84 */
#define  _ApplyEntity_		 -469761964L	/* 84 */
#define  _Scope 		 -469696597L	/* -85 */
#define  _Scope_		 -469761963L	/* 85 */
#define  _SortCdList 		 -469696598L	/* -86 */
#define  _SortCdList_		 -469761962L	/* 86 */
#define  _Section 		 -469696599L	/* -87 */
#define  _Section_		 -469761961L	/* 87 */
#define  _Case 		 -469696600L	/* -88 */
#define  _Case_		 -469761960L	/* 88 */
#define  _ItemPosition 		 -469696601L	/* -89 */
#define  _ItemPosition_		 -469761959L	/* 89 */
#define  _Point 		 -469762047L	/* 1 */
#define  _Node 		 -469762046L	/* 2 */
#define  _nil 		 -469696513L	/* -1 */
#define  _Term 		 -469696514L	/* -2 */
#define  _NodeSort 		 -469696515L	/* -3 */
#define  _NodeSort_		 -469762045L	/* 3 */
#define  _PredeclSort 		 -469696516L	/* -4 */
#define  _PredeclSort_		 -469762044L	/* 4 */
#define  _ClassSort 		 -469696517L	/* -5 */
#define  _ClassSort_		 -469762043L	/* 5 */
#define  _TupelSort 		 -469696518L	/* -6 */
#define  _TupelSort_		 -469762042L	/* 6 */
#define  _ListSort 		 -469696519L	/* -7 */
#define  _ListSort_		 -469762041L	/* 7 */
#define  _Ident 		 -469696520L	/* -8 */
#define  _Ident_		 -469762040L	/* 8 */
#define  _Bool 		 -469696521L	/* -9 */
#define  _Bool_		 -469762039L	/* 9 */
#define  _Char 		 -469696522L	/* -10 */
#define  _Char_		 -469762038L	/* 10 */
#define  _Int 		 -469696523L	/* -11 */
#define  _Int_		 -469762037L	/* 11 */
#define  _String 		 -469696524L	/* -12 */
#define  _String_		 -469762036L	/* 12 */
#define  _Reference 		 -469696525L	/* -13 */
#define  _Reference_		 -469762035L	/* 13 */

/* The constructors for  tupels  and  empty lists                         */
#define  ListProd(P1,P2)		mxi_tc(__FILE__,__LINE__,"ListProd",2,-14,-39,P1,-81,P2)
#define  TupelProd(P1,P2)		mxi_tc(__FILE__,__LINE__,"TupelProd",2,-15,-39,P1,-53,P2)
#define  ClassProd(P1,P2)		mxi_tc(__FILE__,__LINE__,"ClassProd",2,-16,-39,P1,-53,P2)
#define  PredeclProd(P1)		mxi_tc(__FILE__,__LINE__,"PredeclProd",1,-17,-39,P1)
#define  PredDecl(P1,P2)		mxi_tc(__FILE__,__LINE__,"PredDecl",2,-18,-39,P1,-53,P2)
#define  FuncDecl(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"FuncDecl",3,-19,-39,P1,-53,P2,-81,P3)
#define  Structure(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"Structure",3,-20,-39,P1,-40,P2,-54,P3)
#define  Predicate(P1,P2,P3,P4)		mxi_tc(__FILE__,__LINE__,"Predicate",4,-21,-39,P1,-53,P2,-64,P3,-75,P4)
#define  Function(P1,P2,P3,P4,P5)		mxi_tc(__FILE__,__LINE__,"Function",5,-22,-39,P1,-53,P2,-64,P3,-81,P4,-71,P5)
#define  Attribute(P1,P2,P3,P4,P5)		mxi_tc(__FILE__,__LINE__,"Attribute",5,-23,-39,P1,-53,P2,-64,P3,-81,P4,-71,P5)
#define  Condition(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"Condition",3,-24,-59,P1,-75,P2,-71,P3)
#define  AttrDecl(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"AttrDecl",3,-25,-39,P1,-53,P2,-81,P3)
#define  SortConst(P1)		mxi_tc(__FILE__,__LINE__,"SortConst",1,-26,-81,P1)
#define  FuncAppl(P1,P2)		mxi_tc(__FILE__,__LINE__,"FuncAppl",2,-27,-42,P1,-60,P2)
#define  IfExpr(P1,P2)		mxi_tc(__FILE__,__LINE__,"IfExpr",2,-28,-74,P1,-71,P2)
#define  LetExpr(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"LetExpr",3,-29,-43,P1,-71,P2,-71,P3)
#define  StringExpr(P1,P2)		mxi_tc(__FILE__,__LINE__,"StringExpr",2,-30,-60,P1,-11,P2)
#define  PatternCase(P1,P2)		mxi_tc(__FILE__,__LINE__,"PatternCase",2,-31,-38,P1,-71,P2)
#define  FormulaCase(P1,P2)		mxi_tc(__FILE__,__LINE__,"FormulaCase",2,-32,-75,P1,-71,P2)
#define  PredAppl(P1,P2)		mxi_tc(__FILE__,__LINE__,"PredAppl",2,-33,-42,P1,-60,P2)
#define  Or(P1,P2)		mxi_tc(__FILE__,__LINE__,"Or",2,-34,-75,P1,-75,P2)
#define  And(P1,P2)		mxi_tc(__FILE__,__LINE__,"And",2,-35,-75,P1,-75,P2)
#define  Impl(P1,P2)		mxi_tc(__FILE__,__LINE__,"Impl",2,-36,-75,P1,-75,P2)
#define  Neg(P1)		mxi_tc(__FILE__,__LINE__,"Neg",1,-37,-75,P1)
#define  Pattern(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"Pattern",3,-38,-76,P1,-77,P2,-78,P3)
#define  DefId(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"DefId",3,-39,-8,P1,-11,P2,-11,P3)
#define  TermSortId(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"TermSortId",3,-40,-8,P1,-11,P2,-11,P3)
#define  NodeSortId(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"NodeSortId",3,-41,-8,P1,-11,P2,-11,P3)
#define  ApplId(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"ApplId",3,-42,-8,P1,-11,P2,-11,P3)
#define  Name(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"Name",3,-43,-8,P1,-11,P2,-11,P3)
#define  Blank(P1)		mxi_tc(__FILE__,__LINE__,"Blank",1,-44,-11,P1)
#define  Asterisk()		 -536805421L
#define  ParTup(P1,P2)		mxi_tc(__FILE__,__LINE__,"ParTup",2,-46,-53,P1,-64,P2)
#define  NameDepthTup(P1,P2)		mxi_tc(__FILE__,__LINE__,"NameDepthTup",2,-47,43,P1,-11,P2)
#define  RelPosition(P1)		mxi_tc(__FILE__,__LINE__,"RelPosition",1,-48,-11,P1)
#define  AbsPosition(P1)		mxi_tc(__FILE__,__LINE__,"AbsPosition",1,-49,-11,P1)
#define  TopPosition()		 -536805426L
#define  Specification()		-536805427L
#define  ProdList()		-536805428L
#define  SortIdList()		-536805429L
#define  LocalDeclList()		-536805430L
#define  PredList()		-536805431L
#define  FuncList()		-536805432L
#define  AttrList()		-536805433L
#define  CondList()		-536805434L
#define  PatternList()		-536805435L
#define  ExprList()		-536805436L
#define  PatternCaseList()		-536805437L
#define  FormulaCaseList()		-536805438L
#define  ItemList()		-536805439L
#define  NameList()		-536805440L
#define  DefIdNodeList()		-536805441L
#define  CompExprNodeList()		-536805442L

/* The constructors and destructors for tree structures                    */
#define init_max(TERM)		mxi_init(__FILE__,__LINE__,-51,TERM)
#define free_max()			mxi_free(__FILE__,__LINE__)

/* The declarations for defined functions, predicates, and attributes     */
extern ELEMENT  mxs_id(char*,int,ELEMENT);
#define id(p1)		mxs_id(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_patlineno(char*,int,ELEMENT);
#define patlineno(p1)		mxs_patlineno(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_decl(char*,int,ELEMENT);
#define decl(p1)		mxs_decl(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_scope(char*,int,ELEMENT);
#define scope(p1)		mxs_scope(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_lookup_params(char*,int,ELEMENT,ELEMENT);
#define lookup_params(p1,p2)		mxs_lookup_params(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_lookup_item(char*,int,ELEMENT,ELEMENT);
#define lookup_item(p1,p2)		mxs_lookup_item(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_lookup_items(char*,int,ELEMENT,ELEMENT);
#define lookup_items(p1,p2)		mxs_lookup_items(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_lookup_cond(char*,int,ELEMENT,ELEMENT);
#define lookup_cond(p1,p2)		mxs_lookup_cond(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_lookup(char*,int,ELEMENT,ELEMENT);
#define lookup(p1,p2)		mxs_lookup(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_search_bound_name_rec(char*,int,ELEMENT,ELEMENT);
#define search_bound_name_rec(p1,p2)		mxs_search_bound_name_rec(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_search_bound_name(char*,int,ELEMENT,ELEMENT);
#define search_bound_name(p1,p2)		mxs_search_bound_name(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_countastrks(char*,int,ELEMENT,ELEMENT);
#define countastrks(p1,p2)		mxs_countastrks(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_smallestlistprodcd(char*,int);
#define smallestlistprodcd()		mxs_smallestlistprodcd(__FILE__,__LINE__)
extern ELEMENT  mxs_prodcd(char*,int,ELEMENT);
#define prodcd(p1)		mxs_prodcd(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_list_compexprs(char*,int,ELEMENT,ELEMENT);
#define list_compexprs(p1,p2)		mxs_list_compexprs(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_compexprs(char*,int,ELEMENT);
#define compexprs(p1)		mxs_compexprs(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_max2(char*,int,ELEMENT,ELEMENT);
#define max2(p1,p2)		mxs_max2(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_aux_need_case(char*,int,ELEMENT);
#define aux_need_case(p1)		mxs_aux_need_case(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_aux_need_cases(char*,int,ELEMENT);
#define aux_need_cases(p1)		mxs_aux_need_cases(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_encl_sces(char*,int,ELEMENT);
#define encl_sces(p1)		mxs_encl_sces(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_position(char*,int,ELEMENT,ELEMENT);
#define position(p1,p2)		mxs_position(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_next_left_pat(char*,int,ELEMENT);
#define next_left_pat(p1)		mxs_next_left_pat(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_patnposition(char*,int,ELEMENT,ELEMENT);
#define patnposition(p1,p2)		mxs_patnposition(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_next_pat_for_codegen(char*,int,ELEMENT);
#define next_pat_for_codegen(p1)		mxs_next_pat_for_codegen(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_next_pat_upthetree(char*,int,ELEMENT);
#define next_pat_upthetree(p1)		mxs_next_pat_upthetree(__FILE__,__LINE__,p1)
extern long     mxs_in(char*,int,ELEMENT,ELEMENT,ELEMENT);
#define in(p1,p2,p3)		mxs_in(__FILE__,__LINE__,p1,p2,p3)
extern long     mxs_ex_pattern_inbetween(char*,int,ELEMENT,ELEMENT);
#define ex_pattern_inbetween(p1,p2)		mxs_ex_pattern_inbetween(__FILE__,__LINE__,p1,p2)
extern long     mxs_is_relev_att_access(char*,int,ELEMENT);
#define is_relev_att_access(p1)		mxs_is_relev_att_access(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_encl_scope(char*,int,ELEMENT);
#define encl_scope(p)		mxs_encl_scope(__FILE__,__LINE__,p)
extern ELEMENT  mxs_bind_pos(char*,int,ELEMENT);
#define bind_pos(p)		mxs_bind_pos(__FILE__,__LINE__,p)
extern ELEMENT  mxs_pat_anchor(char*,int,ELEMENT);
#define pat_anchor(p)		mxs_pat_anchor(__FILE__,__LINE__,p)
extern ELEMENT  mxs_numberofastrks(char*,int,ELEMENT);
#define numberofastrks(p)		mxs_numberofastrks(__FILE__,__LINE__,p)
extern ELEMENT  mxs_predeclprodcd(char*,int,ELEMENT);
#define predeclprodcd(p)		mxs_predeclprodcd(__FILE__,__LINE__,p)
extern ELEMENT  mxs_tupelprodcd(char*,int,ELEMENT);
#define tupelprodcd(p)		mxs_tupelprodcd(__FILE__,__LINE__,p)
extern ELEMENT  mxs_listprodcd(char*,int,ELEMENT);
#define listprodcd(p)		mxs_listprodcd(__FILE__,__LINE__,p)
extern ELEMENT  mxs_classprodcd(char*,int,ELEMENT);
#define classprodcd(p)		mxs_classprodcd(__FILE__,__LINE__,p)
extern ELEMENT  mxs_sces_appl(char*,int,ELEMENT);
#define sces_appl(p)		mxs_sces_appl(__FILE__,__LINE__,p)
extern ELEMENT  mxs_sces1_cond(char*,int,ELEMENT);
#define sces1_cond(p)		mxs_sces1_cond(__FILE__,__LINE__,p)
extern ELEMENT  mxs_sces2_cond(char*,int,ELEMENT);
#define sces2_cond(p)		mxs_sces2_cond(__FILE__,__LINE__,p)
extern ELEMENT  mxs_sces1_let(char*,int,ELEMENT);
#define sces1_let(p)		mxs_sces1_let(__FILE__,__LINE__,p)
extern ELEMENT  mxs_sces2_let(char*,int,ELEMENT);
#define sces2_let(p)		mxs_sces2_let(__FILE__,__LINE__,p)
extern ELEMENT  mxs_sces_if(char*,int,ELEMENT);
#define sces_if(p)		mxs_sces_if(__FILE__,__LINE__,p)
extern ELEMENT  mxs_sces1_fcase(char*,int,ELEMENT);
#define sces1_fcase(p)		mxs_sces1_fcase(__FILE__,__LINE__,p)
extern ELEMENT  mxs_sces2_fcase(char*,int,ELEMENT);
#define sces2_fcase(p)		mxs_sces2_fcase(__FILE__,__LINE__,p)
extern ELEMENT  mxs_sces_pcase(char*,int,ELEMENT);
#define sces_pcase(p)		mxs_sces_pcase(__FILE__,__LINE__,p)
extern ELEMENT  mxs_aux_need(char*,int,ELEMENT);
#define aux_need(p)		mxs_aux_need(__FILE__,__LINE__,p)
extern ELEMENT  mxs_res_var_no(char*,int,ELEMENT);
#define res_var_no(p)		mxs_res_var_no(__FILE__,__LINE__,p)
extern ELEMENT  mxs_patnpos(char*,int,ELEMENT);
#define patnpos(p)		mxs_patnpos(__FILE__,__LINE__,p)


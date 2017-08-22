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
#define  mxs_conv_error          mxi_conv_error        
#define  mxs_btoe(f,l,BOOLVAL)       mxi_btoe(f,l,BOOLVAL)
#define  mxs_ctoe(f,l,CHARVAL)       mxi_ctoe(f,l,CHARVAL)
#define  mxs_itoe(f,l,INTVAL)        mxi_itoe(f,l,INTVAL)
#define  mxs_atoe(f,l,STRVAL)        mxi_atoe(f,l,STRVAL)
#define  mxs_ptoe(f,l,POINTVAL)      mxi_ptoe(f,l,POINTVAL)

/*  The following functions convert MAX-elements to corresponding C-values */
/*  in case of an error, the functions set the global variable conv_error  */
/*  to 0 and yield  0, '\0', 0, the empty string or NULL.                 */
#define  mxs_etob(f,l,BOOLELEM)      mxi_etob(f,l,BOOLELEM)
#define  mxs_etocf,l,(CHARELEM)      mxi_etoc(f,l,CHARELEM)
#define  mxs_etoi(f,l,INTELEM)       mxi_etoi(f,l,INTELEM)
#define  mxs_etoa(f,l,STRELEM)       mxi_etoa(f,l,STRELEM)
#define  mxs_etop(f,l,REFELEM)       mxi_etop(f,l,REFELEM)

/*  stoid  enters a string into sort  Ident  containing a finite set of    */
/*  hash-coded strings;  idtos  returns the string of an identifier        */
#define  mxs_stoid(f,l,STRING)       mxi_stoid(f,l,STRING)
#define  mxs_idtos(f,l,IDENT)        mxi_idtos(f,l,IDENT)

/*  sort  returns the sort constant of a defined element; otherwise exits. */
#define  mxs_sort(f,l,ELEM)          mxi_sort(f,l,ELEM)
#define  mxs_index(f,l,ELEM,SORT)    mxi_index(f,l,ELEM,SORT)
#define  mxs_element(f,l,INDEX,SORT) mxi_element(f,l,INDEX,SORT)
#define  mxs_number(f,l,SORT)        mxi_number(f,l,SORT)

/*  The following functions provide the inspection of the tree structure; */
/*  if their obvious meaning is not defined, they return  nil :           */
#define  mxs_fath(f,l,NODE)          mxi_fath(f,l,NODE)
#define  mxs_lbroth(f,l,NODE)        mxi_lbroth(f,l,NODE)
#define  mxs_rbroth(f,l,NODE)        mxi_rbroth(f,l,NODE)
#define  mxs_son(f,l,ITH,NODE)       mxi_son(f,l,ITH,NODE)
#define  mxs_numsons(f,l,NODE)       mxi_numsons(f,l,NODE)

/*  subterm(i,t)  returns the ith subterm of term t;  numsubterms(t)      */
/*  returns the number of subterms t; both functions exit on failure      */
#define  mxs_subterm(f,l,ITH,TERM)   mxi_subterm(f,l,ITH,TERM)
#define  mxs_numsubterms(f,l,TERM)   mxi_numsubterms(f,l,TERM)

/*  The following functions provide the polymorphic handling of lists;    */
/*  they exit on failure :                                                */
#define  mxs_front(f,l,LIST)         mxi_front(f,l,LIST)
#define  mxs_back(f,l,LIST)          mxi_back(f,l,LIST)
#define  mxs_appfront(f,l,ELEM,LIST) mxi_appfront(f,l,ELEM,LIST)
#define  mxs_appback(f,l,LIST,ELEM)  mxi_appback(f,l,LIST,ELEM)
#define  mxs_conc(f,l,LIST1,LIST2)   mxi_conc(f,l,LIST1,LIST2)

/*  The following functions relate nodes to the corresponding terms and   */
/*  points; they exit on failure :                                        */
#define  mxs_term(f,l,NODE)          mxi_term(f,l,NODE)
#define  mxs_before(f,l,NODE)        mxi_before(f,l,NODE)
#define  mxs_after(f,l,NODE)         mxi_after(f,l,NODE)
#define  mxs_node(f,l,POINT)         mxi_node(f,l,POINT)

/*  eq  is the equality predicate;  is  tests whether an element is in    */
/*  the given sort;  desc  tests whether node1 is the desendant of node2; */
/*  bef  and  aft  establish the linear order on  points :                */
#define  mxs_eq(f,l,ELEM1,ELEM2)     mxi_eq(f,l,ELEM1,ELEM2)
#define  mxs_is(f,l,ELEM,SORT)       mxi_is(f,l,ELEM,SORT)
#define  mxs_desc(f,l,N1,N2)         (mxs_before(f,l,N1)>mxs_before(f,l,N2) && mxs_after(f,l,N1)<mxs_after(f,l,N2))
#define  mxs_bef(f,l,P1,P2)          (mxs_is(f,l,P1,_Point) && mxs_is(f,l,P2,_Point) && P1<P2)
#define  mxs_aft(f,l,P1,P2)          (mxs_is(f,l,P1,_Point) && mxs_is(f,l,P2,_Point) && P1>P2)

/*  The predefined constants are :                                        */
#define  mxs_minimalInt(f,l)   -16777216L
#define  mxs_maximalInt(f,l)   16777215L

#define  mxs_root(f,l)         -939524095L
#define  mxs_true(f,l)         -268435455L
#define  mxs_false(f,l)        -268435456L
#define  mxs_nil(f,l)          -536805377L
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
#define  mxs_ListProd(f,l,P1,P2)		mxi_tc(f,l,"ListProd",2,-14,-39,P1,-81,P2)
#define  mxs_TupelProd(f,l,P1,P2)		mxi_tc(f,l,"TupelProd",2,-15,-39,P1,-53,P2)
#define  mxs_ClassProd(f,l,P1,P2)		mxi_tc(f,l,"ClassProd",2,-16,-39,P1,-53,P2)
#define  mxs_PredeclProd(f,l,P1)		mxi_tc(f,l,"PredeclProd",1,-17,-39,P1)
#define  mxs_PredDecl(f,l,P1,P2)		mxi_tc(f,l,"PredDecl",2,-18,-39,P1,-53,P2)
#define  mxs_FuncDecl(f,l,P1,P2,P3)		mxi_tc(f,l,"FuncDecl",3,-19,-39,P1,-53,P2,-81,P3)
#define  mxs_Structure(f,l,P1,P2,P3)		mxi_tc(f,l,"Structure",3,-20,-39,P1,-40,P2,-54,P3)
#define  mxs_Predicate(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"Predicate",4,-21,-39,P1,-53,P2,-64,P3,-75,P4)
#define  mxs_Function(f,l,P1,P2,P3,P4,P5)		mxi_tc(f,l,"Function",5,-22,-39,P1,-53,P2,-64,P3,-81,P4,-71,P5)
#define  mxs_Attribute(f,l,P1,P2,P3,P4,P5)		mxi_tc(f,l,"Attribute",5,-23,-39,P1,-53,P2,-64,P3,-81,P4,-71,P5)
#define  mxs_Condition(f,l,P1,P2,P3)		mxi_tc(f,l,"Condition",3,-24,-59,P1,-75,P2,-71,P3)
#define  mxs_AttrDecl(f,l,P1,P2,P3)		mxi_tc(f,l,"AttrDecl",3,-25,-39,P1,-53,P2,-81,P3)
#define  mxs_SortConst(f,l,P1)		mxi_tc(f,l,"SortConst",1,-26,-81,P1)
#define  mxs_FuncAppl(f,l,P1,P2)		mxi_tc(f,l,"FuncAppl",2,-27,-42,P1,-60,P2)
#define  mxs_IfExpr(f,l,P1,P2)		mxi_tc(f,l,"IfExpr",2,-28,-74,P1,-71,P2)
#define  mxs_LetExpr(f,l,P1,P2,P3)		mxi_tc(f,l,"LetExpr",3,-29,-43,P1,-71,P2,-71,P3)
#define  mxs_StringExpr(f,l,P1,P2)		mxi_tc(f,l,"StringExpr",2,-30,-60,P1,-11,P2)
#define  mxs_PatternCase(f,l,P1,P2)		mxi_tc(f,l,"PatternCase",2,-31,-38,P1,-71,P2)
#define  mxs_FormulaCase(f,l,P1,P2)		mxi_tc(f,l,"FormulaCase",2,-32,-75,P1,-71,P2)
#define  mxs_PredAppl(f,l,P1,P2)		mxi_tc(f,l,"PredAppl",2,-33,-42,P1,-60,P2)
#define  mxs_Or(f,l,P1,P2)		mxi_tc(f,l,"Or",2,-34,-75,P1,-75,P2)
#define  mxs_And(f,l,P1,P2)		mxi_tc(f,l,"And",2,-35,-75,P1,-75,P2)
#define  mxs_Impl(f,l,P1,P2)		mxi_tc(f,l,"Impl",2,-36,-75,P1,-75,P2)
#define  mxs_Neg(f,l,P1)		mxi_tc(f,l,"Neg",1,-37,-75,P1)
#define  mxs_Pattern(f,l,P1,P2,P3)		mxi_tc(f,l,"Pattern",3,-38,-76,P1,-77,P2,-78,P3)
#define  mxs_DefId(f,l,P1,P2,P3)		mxi_tc(f,l,"DefId",3,-39,-8,P1,-11,P2,-11,P3)
#define  mxs_TermSortId(f,l,P1,P2,P3)		mxi_tc(f,l,"TermSortId",3,-40,-8,P1,-11,P2,-11,P3)
#define  mxs_NodeSortId(f,l,P1,P2,P3)		mxi_tc(f,l,"NodeSortId",3,-41,-8,P1,-11,P2,-11,P3)
#define  mxs_ApplId(f,l,P1,P2,P3)		mxi_tc(f,l,"ApplId",3,-42,-8,P1,-11,P2,-11,P3)
#define  mxs_Name(f,l,P1,P2,P3)		mxi_tc(f,l,"Name",3,-43,-8,P1,-11,P2,-11,P3)
#define  mxs_Blank(f,l,P1)		mxi_tc(f,l,"Blank",1,-44,-11,P1)
#define  mxs_Asterisk(f,l)		 -536805421L
#define  mxs_ParTup(f,l,P1,P2)		mxi_tc(f,l,"ParTup",2,-46,-53,P1,-64,P2)
#define  mxs_NameDepthTup(f,l,P1,P2)		mxi_tc(f,l,"NameDepthTup",2,-47,43,P1,-11,P2)
#define  mxs_RelPosition(f,l,P1)		mxi_tc(f,l,"RelPosition",1,-48,-11,P1)
#define  mxs_AbsPosition(f,l,P1)		mxi_tc(f,l,"AbsPosition",1,-49,-11,P1)
#define  mxs_TopPosition(f,l)		 -536805426L
#define  mxs_Specification(f,l)		-536805427L
#define  mxs_ProdList(f,l)		-536805428L
#define  mxs_SortIdList(f,l)		-536805429L
#define  mxs_LocalDeclList(f,l)		-536805430L
#define  mxs_PredList(f,l)		-536805431L
#define  mxs_FuncList(f,l)		-536805432L
#define  mxs_AttrList(f,l)		-536805433L
#define  mxs_CondList(f,l)		-536805434L
#define  mxs_PatternList(f,l)		-536805435L
#define  mxs_ExprList(f,l)		-536805436L
#define  mxs_PatternCaseList(f,l)		-536805437L
#define  mxs_FormulaCaseList(f,l)		-536805438L
#define  mxs_ItemList(f,l)		-536805439L
#define  mxs_NameList(f,l)		-536805440L
#define  mxs_DefIdNodeList(f,l)		-536805441L
#define  mxs_CompExprNodeList(f,l)		-536805442L


#include <stdio.h>
#include <stdlib.h>
extern mxi_ELEMENT mxi_string_conc( char*, int, long,...);
static mxi_ELEMENT mxv_errstr;
FILE *errfile = stderr;
extern void mxi_prterrm(char*,int,char*,char*);
static char *mxi_errmstr= "0th parameter is of wrong sort";
static void comp_errm(char *filenm, int ln, char *fctnm, int parno){
	mxi_errmstr[0] = (char)(parno+48);
	mxi_prterrm(filenm,ln,fctnm,mxi_errmstr);
}

static  char *_c = "max_spec.c";
static  char *_m = "max_spec.m";
#define SORTCDT  short
#define IFNIL(e) {if(e==mxs_nil(_c,0)) return mxs_nil(_c,0);}
#define IS(e,t,l,f,i)  {if(!mxs_is(_c,0,e,t)){comp_errm(_m,l,f,i);return mxs_nil(_c,0);}}
#define ISORNIL(e,t,l,f,i)  {if(!mxs_is(_c,0,e,t)&&e!=mxs_nil(_c,0)){comp_errm(_m,l,f,i);return mxs_nil(_c,0);}}


typedef struct AttInstElem{
	void     (*attevalfct)(ELEMENT);
	ELEMENT  attnode;
	struct AttInstElem *rest;
} *AttInstSq;

static  void  insAttInst( void (*attevalfct)(ELEMENT), ELEMENT attnode, AttInstSq* undefatt, long undefattix ){
	AttInstSq  waitlist  = (AttInstSq) malloc( sizeof(struct AttInstElem) );
	if( waitlist == 0L ){
		fprintf(stderr,"***** Error: Cannot allocate wait list element\n");
		exit( EXIT_FAILURE );
	}
	waitlist->attevalfct = attevalfct;
	waitlist->attnode    = attnode;
	waitlist->rest       = undefatt[undefattix];
	undefatt[undefattix] = waitlist;
}


SORTCDT   mxi_tupel_sortcd_lb  = -50;
SORTCDT   mxi_list_sortcd_lb   = -66;
SORTCDT   mxi_class_sortcd_lb  = -89;


static  SORTCDT  mxi_auxlisttoelemtab[17] = {
73,39,-43,-79,-32,-31,-71,-38,-24,-23,-22,-21,-70,-81,-69,-68,0};

SORTCDT  *mxi_listtoelemtab = mxi_auxlisttoelemtab+66;


static  SORTCDT subsort_67[] = {2,1,-2,0};
static  SORTCDT subsort_68[] = {-18,-19,-20,-52,0};
static  SORTCDT subsort_69[] = {-14,-15,-16,-17,0};
static  SORTCDT subsort_70[] = {-18,-19,-25,-55,-56,-57,-58,0};
static  SORTCDT subsort_71[] = {-10,-11,-12,-26,-27,-28,-29,-30,-43,0};
static  SORTCDT subsort_72[] = {-10,-11,-12,-26,0};
static  SORTCDT subsort_73[] = {-28,-29,0};
static  SORTCDT subsort_74[] = {-61,-62,0};
static  SORTCDT subsort_75[] = {-33,-34,-35,-36,-37,0};
static  SORTCDT subsort_76[] = {-40,-41,-44,0};
static  SORTCDT subsort_77[] = {-44,-63,0};
static  SORTCDT subsort_78[] = {-43,-44,0};
static  SORTCDT subsort_79[] = {-38,-44,-45,0};
static  SORTCDT subsort_80[] = {-40,-41,-42,0};
static  SORTCDT subsort_81[] = {-40,-41,0};
static  SORTCDT subsort_82[] = {-18,-19,-25,0};
static  SORTCDT subsort_83[] = {-14,-15,-16,-17,-21,-22,-23,0};
static  SORTCDT subsort_84[] = {-21,-22,-23,0};
static  SORTCDT subsort_85[] = {-21,-22,-23,-24,-29,-31,0};
static  SORTCDT subsort_86[] = {-13,0};
static  SORTCDT subsort_87[] = {-21,-22,-23,-24,-28,-29,0};
static  SORTCDT subsort_88[] = {-31,-32,0};
static  SORTCDT subsort_89[] = {-48,-49,-50,0};

static  SORTCDT  *mxi_auxclasstosorttab[24] = { 0L,
subsort_89,subsort_88,subsort_87,subsort_86,subsort_85,
subsort_84,subsort_83,subsort_82,subsort_81,subsort_80,
subsort_79,subsort_78,subsort_77,subsort_76,subsort_75,
subsort_74,subsort_73,subsort_72,subsort_71,subsort_70,
subsort_69,subsort_68,subsort_67,};

SORTCDT  **mxi_classtosorttab = mxi_auxclasstosorttab+90;


static  SORTCDT supsort_66[] = {-67,-2,0};
static  SORTCDT supsort_65[] = {-67,-2,0};
static  SORTCDT supsort_64[] = {-67,-2,0};
static  SORTCDT supsort_63[] = {-77,-67,-2,0};
static  SORTCDT supsort_62[] = {-74,-67,-2,0};
static  SORTCDT supsort_61[] = {-74,-67,-2,0};
static  SORTCDT supsort_60[] = {-67,-2,0};
static  SORTCDT supsort_59[] = {-67,-2,0};
static  SORTCDT supsort_58[] = {-70,-67,-2,0};
static  SORTCDT supsort_57[] = {-70,-67,-2,0};
static  SORTCDT supsort_56[] = {-70,-67,-2,0};
static  SORTCDT supsort_55[] = {-70,-67,-2,0};
static  SORTCDT supsort_54[] = {-67,-2,0};
static  SORTCDT supsort_53[] = {-67,-2,0};
static  SORTCDT supsort_52[] = {-68,-67,-2,0};
static  SORTCDT supsort_51[] = {-67,-2,0};
static  SORTCDT supsort_50[] = {-89,-67,-2,0};
static  SORTCDT supsort_49[] = {-89,-67,-2,0};
static  SORTCDT supsort_48[] = {-89,-67,-2,0};
static  SORTCDT supsort_47[] = {-67,-2,0};
static  SORTCDT supsort_46[] = {-67,-2,0};
static  SORTCDT supsort_45[] = {-79,-67,-2,0};
static  SORTCDT supsort_44[] = {-79,-78,-77,-76,-67,-2,0};
static  SORTCDT supsort_43[] = {-78,-71,-67,-2,0};
static  SORTCDT supsort_42[] = {-80,-67,-2,0};
static  SORTCDT supsort_41[] = {-81,-80,-76,-67,-2,0};
static  SORTCDT supsort_40[] = {-81,-80,-76,-67,-2,0};
static  SORTCDT supsort_39[] = {-67,-2,0};
static  SORTCDT supsort_38[] = {-79,-67,-2,0};
static  SORTCDT supsort_37[] = {-75,-67,-2,0};
static  SORTCDT supsort_36[] = {-75,-67,-2,0};
static  SORTCDT supsort_35[] = {-75,-67,-2,0};
static  SORTCDT supsort_34[] = {-75,-67,-2,0};
static  SORTCDT supsort_33[] = {-75,-67,-2,0};
static  SORTCDT supsort_32[] = {-88,-67,-2,0};
static  SORTCDT supsort_31[] = {-88,-85,-67,-2,0};
static  SORTCDT supsort_30[] = {-71,-67,-2,0};
static  SORTCDT supsort_29[] = {-87,-85,-73,-71,-67,-2,0};
static  SORTCDT supsort_28[] = {-87,-73,-71,-67,-2,0};
static  SORTCDT supsort_27[] = {-71,-67,-2,0};
static  SORTCDT supsort_26[] = {-72,-71,-67,-2,0};
static  SORTCDT supsort_25[] = {-82,-70,-67,-2,0};
static  SORTCDT supsort_24[] = {-87,-85,-67,-2,0};
static  SORTCDT supsort_23[] = {-87,-85,-84,-83,-67,-2,0};
static  SORTCDT supsort_22[] = {-87,-85,-84,-83,-67,-2,0};
static  SORTCDT supsort_21[] = {-87,-85,-84,-83,-67,-2,0};
static  SORTCDT supsort_20[] = {-68,-67,-2,0};
static  SORTCDT supsort_19[] = {-82,-70,-68,-67,-2,0};
static  SORTCDT supsort_18[] = {-82,-70,-68,-67,-2,0};
static  SORTCDT supsort_17[] = {-83,-69,-67,-2,0};
static  SORTCDT supsort_16[] = {-83,-69,-67,-2,0};
static  SORTCDT supsort_15[] = {-83,-69,-67,-2,0};
static  SORTCDT supsort_14[] = {-83,-69,-67,-2,0};
static  SORTCDT supsort_13[] = {-86,-67,-2,0};
static  SORTCDT supsort_12[] = {-72,-71,-67,-2,0};
static  SORTCDT supsort_11[] = {-72,-71,-67,-2,0};
static  SORTCDT supsort_10[] = {-72,-71,-67,-2,0};
static  SORTCDT supsort_9[] = {-67,-2,0};
static  SORTCDT supsort_8[] = {-67,-2,0};
static  SORTCDT supsort_7[] = {-67,-2,0};
static  SORTCDT supsort_6[] = {-67,-2,0};
static  SORTCDT supsort_5[] = {-67,-2,0};
static  SORTCDT supsort_4[] = {-67,-2,0};
static  SORTCDT supsort_3[] = {-67,-2,0};
static  SORTCDT supsort_2[] = {0};
static  SORTCDT supsort_1[] = {0};
static  SORTCDT supsort0[] = {0};
static  SORTCDT supsort1[] = {-67,0};
static  SORTCDT supsort2[] = {0};
static  SORTCDT supsort3[] = {67,-67,2,0};
static  SORTCDT supsort4[] = {67,-67,2,0};
static  SORTCDT supsort5[] = {67,-67,2,0};
static  SORTCDT supsort6[] = {67,-67,2,0};
static  SORTCDT supsort7[] = {67,-67,2,0};
static  SORTCDT supsort8[] = {67,-67,2,0};
static  SORTCDT supsort9[] = {67,-67,2,0};
static  SORTCDT supsort10[] = {72,71,67,-67,2,0};
static  SORTCDT supsort11[] = {72,71,67,-67,2,0};
static  SORTCDT supsort12[] = {72,71,67,-67,2,0};
static  SORTCDT supsort13[] = {86,67,-67,2,0};
static  SORTCDT supsort14[] = {83,69,67,-67,2,0};
static  SORTCDT supsort15[] = {83,69,67,-67,2,0};
static  SORTCDT supsort16[] = {83,69,67,-67,2,0};
static  SORTCDT supsort17[] = {83,69,67,-67,2,0};
static  SORTCDT supsort18[] = {82,70,68,67,-67,2,0};
static  SORTCDT supsort19[] = {82,70,68,67,-67,2,0};
static  SORTCDT supsort20[] = {68,67,-67,2,0};
static  SORTCDT supsort21[] = {87,85,84,83,67,-67,2,0};
static  SORTCDT supsort22[] = {87,85,84,83,67,-67,2,0};
static  SORTCDT supsort23[] = {87,85,84,83,67,-67,2,0};
static  SORTCDT supsort24[] = {87,85,67,-67,2,0};
static  SORTCDT supsort25[] = {82,70,67,-67,2,0};
static  SORTCDT supsort26[] = {72,71,67,-67,2,0};
static  SORTCDT supsort27[] = {71,67,-67,2,0};
static  SORTCDT supsort28[] = {87,73,71,67,-67,2,0};
static  SORTCDT supsort29[] = {87,85,73,71,67,-67,2,0};
static  SORTCDT supsort30[] = {71,67,-67,2,0};
static  SORTCDT supsort31[] = {88,85,67,-67,2,0};
static  SORTCDT supsort32[] = {88,67,-67,2,0};
static  SORTCDT supsort33[] = {75,67,-67,2,0};
static  SORTCDT supsort34[] = {75,67,-67,2,0};
static  SORTCDT supsort35[] = {75,67,-67,2,0};
static  SORTCDT supsort36[] = {75,67,-67,2,0};
static  SORTCDT supsort37[] = {75,67,-67,2,0};
static  SORTCDT supsort38[] = {79,67,-67,2,0};
static  SORTCDT supsort39[] = {67,-67,2,0};
static  SORTCDT supsort40[] = {81,80,76,67,-67,2,0};
static  SORTCDT supsort41[] = {81,80,76,67,-67,2,0};
static  SORTCDT supsort42[] = {80,67,-67,2,0};
static  SORTCDT supsort43[] = {78,71,67,-67,2,0};
static  SORTCDT supsort44[] = {79,78,77,76,67,-67,2,0};
static  SORTCDT supsort45[] = {79,67,-67,2,0};
static  SORTCDT supsort46[] = {67,-67,2,0};
static  SORTCDT supsort47[] = {67,-67,2,0};
static  SORTCDT supsort48[] = {89,67,-67,2,0};
static  SORTCDT supsort49[] = {89,67,-67,2,0};
static  SORTCDT supsort50[] = {89,67,-67,2,0};
static  SORTCDT supsort51[] = {67,-67,2,0};
static  SORTCDT supsort52[] = {68,67,-67,2,0};
static  SORTCDT supsort53[] = {67,-67,2,0};
static  SORTCDT supsort54[] = {67,-67,2,0};
static  SORTCDT supsort55[] = {70,67,-67,2,0};
static  SORTCDT supsort56[] = {70,67,-67,2,0};
static  SORTCDT supsort57[] = {70,67,-67,2,0};
static  SORTCDT supsort58[] = {70,67,-67,2,0};
static  SORTCDT supsort59[] = {67,-67,2,0};
static  SORTCDT supsort60[] = {67,-67,2,0};
static  SORTCDT supsort61[] = {74,67,-67,2,0};
static  SORTCDT supsort62[] = {74,67,-67,2,0};
static  SORTCDT supsort63[] = {77,67,-67,2,0};
static  SORTCDT supsort64[] = {67,-67,2,0};
static  SORTCDT supsort65[] = {67,-67,2,0};
static  SORTCDT supsort66[] = {67,-67,2,0};

static  SORTCDT  *mxi_auxsupsorttab[133] = {
supsort_66,supsort_65,supsort_64,supsort_63,supsort_62,
supsort_61,supsort_60,supsort_59,supsort_58,supsort_57,
supsort_56,supsort_55,supsort_54,supsort_53,supsort_52,
supsort_51,supsort_50,supsort_49,supsort_48,supsort_47,
supsort_46,supsort_45,supsort_44,supsort_43,supsort_42,
supsort_41,supsort_40,supsort_39,supsort_38,supsort_37,
supsort_36,supsort_35,supsort_34,supsort_33,supsort_32,
supsort_31,supsort_30,supsort_29,supsort_28,supsort_27,
supsort_26,supsort_25,supsort_24,supsort_23,supsort_22,
supsort_21,supsort_20,supsort_19,supsort_18,supsort_17,
supsort_16,supsort_15,supsort_14,supsort_13,supsort_12,
supsort_11,supsort_10,supsort_9,supsort_8,supsort_7,
supsort_6,supsort_5,supsort_4,supsort_3,supsort_2,
supsort_1,supsort0,supsort1,supsort2,supsort3,
supsort4,supsort5,supsort6,supsort7,supsort8,
supsort9,supsort10,supsort11,supsort12,supsort13,
supsort14,supsort15,supsort16,supsort17,supsort18,
supsort19,supsort20,supsort21,supsort22,supsort23,
supsort24,supsort25,supsort26,supsort27,supsort28,
supsort29,supsort30,supsort31,supsort32,supsort33,
supsort34,supsort35,supsort36,supsort37,supsort38,
supsort39,supsort40,supsort41,supsort42,supsort43,
supsort44,supsort45,supsort46,supsort47,supsort48,
supsort49,supsort50,supsort51,supsort52,supsort53,
supsort54,supsort55,supsort56,supsort57,supsort58,
supsort59,supsort60,supsort61,supsort62,supsort63,
supsort64,supsort65,supsort66,};

SORTCDT  **mxi_supsorttab = mxi_auxsupsorttab+66;


static  long  mxi_auxnumbertab[98];
long  *mxi_numbertab =  mxi_auxnumbertab+8;

long  mxi_offsettab[67];

typedef  struct{
			short  ccd;
			long   offs;
		}  ScdOffsPair;

static  ScdOffsPair  cop3[] = {{67,0L},};
static  ScdOffsPair  cop4[] = {{67,0L},};
static  ScdOffsPair  cop5[] = {{67,0L},};
static  ScdOffsPair  cop6[] = {{67,0L},};
static  ScdOffsPair  cop7[] = {{67,0L},};
static  ScdOffsPair  cop8[] = {{67,0L},};
static  ScdOffsPair  cop9[] = {{67,0L},};
static  ScdOffsPair  cop10[] = {{72,0L},{71,0L},{67,0L},};
static  ScdOffsPair  cop11[] = {{72,0L},{71,0L},{67,0L},};
static  ScdOffsPair  cop12[] = {{72,0L},{71,0L},{67,0L},};
static  ScdOffsPair  cop13[] = {{86,0L},{67,0L},};
static  ScdOffsPair  cop14[] = {{83,0L},{69,0L},{67,0L},};
static  ScdOffsPair  cop15[] = {{83,0L},{69,0L},{67,0L},};
static  ScdOffsPair  cop16[] = {{83,0L},{69,0L},{67,0L},};
static  ScdOffsPair  cop17[] = {{83,0L},{69,0L},{67,0L},};
static  ScdOffsPair  cop18[] = {{82,0L},{70,0L},{68,0L},{67,0L},};
static  ScdOffsPair  cop19[] = {{82,0L},{70,0L},{68,0L},{67,0L},};
static  ScdOffsPair  cop20[] = {{68,0L},{67,0L},};
static  ScdOffsPair  cop21[] = {{87,0L},{85,0L},{84,0L},{83,0L},{67,0L},};
static  ScdOffsPair  cop22[] = {{87,0L},{85,0L},{84,0L},{83,0L},{67,0L},};
static  ScdOffsPair  cop23[] = {{87,0L},{85,0L},{84,0L},{83,0L},{67,0L},};
static  ScdOffsPair  cop24[] = {{87,0L},{85,0L},{67,0L},};
static  ScdOffsPair  cop25[] = {{82,0L},{70,0L},{67,0L},};
static  ScdOffsPair  cop26[] = {{72,0L},{71,0L},{67,0L},};
static  ScdOffsPair  cop27[] = {{71,0L},{67,0L},};
static  ScdOffsPair  cop28[] = {{87,0L},{73,0L},{71,0L},{67,0L},};
static  ScdOffsPair  cop29[] = {{87,0L},{85,0L},{73,0L},{71,0L},{67,0L},};
static  ScdOffsPair  cop30[] = {{71,0L},{67,0L},};
static  ScdOffsPair  cop31[] = {{88,0L},{85,0L},{67,0L},};
static  ScdOffsPair  cop32[] = {{88,0L},{67,0L},};
static  ScdOffsPair  cop33[] = {{75,0L},{67,0L},};
static  ScdOffsPair  cop34[] = {{75,0L},{67,0L},};
static  ScdOffsPair  cop35[] = {{75,0L},{67,0L},};
static  ScdOffsPair  cop36[] = {{75,0L},{67,0L},};
static  ScdOffsPair  cop37[] = {{75,0L},{67,0L},};
static  ScdOffsPair  cop38[] = {{79,0L},{67,0L},};
static  ScdOffsPair  cop39[] = {{67,0L},};
static  ScdOffsPair  cop40[] = {{81,0L},{80,0L},{76,0L},{67,0L},};
static  ScdOffsPair  cop41[] = {{81,0L},{80,0L},{76,0L},{67,0L},};
static  ScdOffsPair  cop42[] = {{80,0L},{67,0L},};
static  ScdOffsPair  cop43[] = {{78,0L},{71,0L},{67,0L},};
static  ScdOffsPair  cop44[] = {{79,0L},{78,0L},{77,0L},{76,0L},{67,0L},};
static  ScdOffsPair  cop45[] = {{79,0L},{67,0L},};
static  ScdOffsPair  cop46[] = {{67,0L},};
static  ScdOffsPair  cop47[] = {{67,0L},};
static  ScdOffsPair  cop48[] = {{89,0L},{67,0L},};
static  ScdOffsPair  cop49[] = {{89,0L},{67,0L},};
static  ScdOffsPair  cop50[] = {{89,0L},{67,0L},};
static  ScdOffsPair  cop51[] = {{67,0L},};
static  ScdOffsPair  cop52[] = {{68,0L},{67,0L},};
static  ScdOffsPair  cop53[] = {{67,0L},};
static  ScdOffsPair  cop54[] = {{67,0L},};
static  ScdOffsPair  cop55[] = {{70,0L},{67,0L},};
static  ScdOffsPair  cop56[] = {{70,0L},{67,0L},};
static  ScdOffsPair  cop57[] = {{70,0L},{67,0L},};
static  ScdOffsPair  cop58[] = {{70,0L},{67,0L},};
static  ScdOffsPair  cop59[] = {{67,0L},};
static  ScdOffsPair  cop60[] = {{67,0L},};
static  ScdOffsPair  cop61[] = {{74,0L},{67,0L},};
static  ScdOffsPair  cop62[] = {{74,0L},{67,0L},};
static  ScdOffsPair  cop63[] = {{77,0L},{67,0L},};
static  ScdOffsPair  cop64[] = {{67,0L},};
static  ScdOffsPair  cop65[] = {{67,0L},};
static  ScdOffsPair  cop66[] = {{67,0L},};
static  ScdOffsPair  cop67[] = {{2,0L},{0,0L}};
static  ScdOffsPair  cop68[] = {{18,0L},{19,0L},{20,0L},{52,0L},{0,0L}};
static  ScdOffsPair  cop69[] = {{14,0L},{15,0L},{16,0L},{17,0L},{0,0L}};
static  ScdOffsPair  cop70[] = {{18,0L},{19,0L},{25,0L},{55,0L},{56,0L},{57,0L},{58,0L},{0,0L}};
static  ScdOffsPair  cop71[] = {{10,0L},{11,0L},{12,0L},{26,0L},{27,0L},{28,0L},{29,0L},{30,0L},{43,0L},{0,0L}};
static  ScdOffsPair  cop72[] = {{10,0L},{11,0L},{12,0L},{26,0L},{0,0L}};
static  ScdOffsPair  cop73[] = {{28,0L},{29,0L},{0,0L}};
static  ScdOffsPair  cop74[] = {{61,0L},{62,0L},{0,0L}};
static  ScdOffsPair  cop75[] = {{33,0L},{34,0L},{35,0L},{36,0L},{37,0L},{0,0L}};
static  ScdOffsPair  cop76[] = {{40,0L},{41,0L},{44,0L},{0,0L}};
static  ScdOffsPair  cop77[] = {{44,0L},{63,0L},{0,0L}};
static  ScdOffsPair  cop78[] = {{43,0L},{44,0L},{0,0L}};
static  ScdOffsPair  cop79[] = {{38,0L},{44,0L},{45,0L},{0,0L}};
static  ScdOffsPair  cop80[] = {{40,0L},{41,0L},{42,0L},{0,0L}};
static  ScdOffsPair  cop81[] = {{40,0L},{41,0L},{0,0L}};
static  ScdOffsPair  cop82[] = {{18,0L},{19,0L},{25,0L},{0,0L}};
static  ScdOffsPair  cop83[] = {{14,0L},{15,0L},{16,0L},{17,0L},{21,0L},{22,0L},{23,0L},{0,0L}};
static  ScdOffsPair  cop84[] = {{21,0L},{22,0L},{23,0L},{0,0L}};
static  ScdOffsPair  cop85[] = {{21,0L},{22,0L},{23,0L},{24,0L},{29,0L},{31,0L},{0,0L}};
static  ScdOffsPair  cop86[] = {{13,0L},{0,0L}};
static  ScdOffsPair  cop87[] = {{21,0L},{22,0L},{23,0L},{24,0L},{28,0L},{29,0L},{0,0L}};
static  ScdOffsPair  cop88[] = {{31,0L},{32,0L},{0,0L}};
static  ScdOffsPair  cop89[] = {{48,0L},{49,0L},{50,0L},{0,0L}};

ScdOffsPair *mxi_coffsettab[90] = {
0L,0L,0L,
cop3,cop4,cop5,cop6,cop7,cop8,cop9,cop10,cop11,cop12,
cop13,cop14,cop15,cop16,cop17,cop18,cop19,cop20,cop21,cop22,
cop23,cop24,cop25,cop26,cop27,cop28,cop29,cop30,cop31,cop32,
cop33,cop34,cop35,cop36,cop37,cop38,cop39,cop40,cop41,cop42,
cop43,cop44,cop45,cop46,cop47,cop48,cop49,cop50,cop51,cop52,
cop53,cop54,cop55,cop56,cop57,cop58,cop59,cop60,cop61,cop62,
cop63,cop64,cop65,cop66,cop67,cop68,cop69,cop70,cop71,cop72,
cop73,cop74,cop75,cop76,cop77,cop78,cop79,cop80,cop81,cop82,
cop83,cop84,cop85,cop86,cop87,cop88,cop89,};

/* The declaration for externals  */
extern ELEMENT add(ELEMENT,ELEMENT);
static ELEMENT mxs_add(char *f,int l,ELEMENT p1,ELEMENT p2){
	IFNIL(p1) IFNIL(p2) 
	IS(p1,_Int,l,"add",1) IS(p2,_Int,l,"add",2) 
	return add(p1,p2);
}
extern ELEMENT sub(ELEMENT,ELEMENT);
static ELEMENT mxs_sub(char *f,int l,ELEMENT p1,ELEMENT p2){
	IFNIL(p1) IFNIL(p2) 
	IS(p1,_Int,l,"sub",1) IS(p2,_Int,l,"sub",2) 
	return sub(p1,p2);
}
extern ELEMENT neg(ELEMENT);
static ELEMENT mxs_neg(char *f,int l,ELEMENT p1){
	IFNIL(p1) 
	IS(p1,_Int,l,"neg",1) 
	return neg(p1);
}
extern ELEMENT s(ELEMENT);
static ELEMENT mxs_s(char *f,int l,ELEMENT p1){
	IFNIL(p1) 
	IS(p1,_Int_,l,"s",1) 
	return s(p1);
}


extern long lt(ELEMENT,ELEMENT);
static ELEMENT mxs_lt(char *f,int l,ELEMENT p1,ELEMENT p2){
	ISORNIL(p1,_Int,l,"lt",1) ISORNIL(p2,_Int,l,"lt",2) 
	return lt(p1,p2);
}
extern long le(ELEMENT,ELEMENT);
static ELEMENT mxs_le(char *f,int l,ELEMENT p1,ELEMENT p2){
	ISORNIL(p1,_Int,l,"le",1) ISORNIL(p2,_Int,l,"le",2) 
	return le(p1,p2);
}


extern long init_idtodecls( void );
extern long free_idtodecls( void );
extern ELEMENT idtodecls( ELEMENT );
static ELEMENT mxs_idtodecls(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_Ident,l,"idtodecls",1) 
	return idtodecls(p1);
}
extern long init_subsorts( void );
extern long free_subsorts( void );
extern ELEMENT subsorts( ELEMENT );
static ELEMENT mxs_subsorts(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_ClassProd_,l,"subsorts",1) 
	return subsorts(p1);
}


ELEMENT  mxs_id(char*,int,ELEMENT);
ELEMENT  mxs_patlineno(char*,int,ELEMENT);
ELEMENT  mxs_decl(char*,int,ELEMENT);
ELEMENT  mxs_scope(char*,int,ELEMENT);
ELEMENT  mxs_lookup_params(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_lookup_item(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_lookup_items(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_lookup_cond(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_lookup(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_search_bound_name_rec(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_search_bound_name(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_countastrks(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_smallestlistprodcd(char*,int);
ELEMENT  mxs_prodcd(char*,int,ELEMENT);
ELEMENT  mxs_list_compexprs(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_compexprs(char*,int,ELEMENT);
ELEMENT  mxs_max2(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_aux_need_case(char*,int,ELEMENT);
ELEMENT  mxs_aux_need_cases(char*,int,ELEMENT);
ELEMENT  mxs_encl_sces(char*,int,ELEMENT);
ELEMENT  mxs_position(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_next_left_pat(char*,int,ELEMENT);
ELEMENT  mxs_patnposition(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_next_pat_for_codegen(char*,int,ELEMENT);
ELEMENT  mxs_next_pat_upthetree(char*,int,ELEMENT);


long  mxs_in(char*,int,ELEMENT,ELEMENT,ELEMENT);
long  mxs_ex_pattern_inbetween(char*,int,ELEMENT,ELEMENT);
long  mxs_is_relev_att_access(char*,int,ELEMENT);


static ELEMENT   *mxa_encl_scope;
static AttInstSq *mxw_encl_scope;
ELEMENT  mxs_encl_scope( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Scope_,l,"encl_scope",1)
	return mxa_encl_scope[mxs_index(_c,0,p,_Scope_)];
}
static ELEMENT   *mxa_bind_pos;
static AttInstSq *mxw_bind_pos;
ELEMENT  mxs_bind_pos( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Name_,l,"bind_pos",1)
	return mxa_bind_pos[mxs_index(_c,0,p,_Name_)];
}
static ELEMENT   *mxa_pat_anchor;
static AttInstSq *mxw_pat_anchor;
ELEMENT  mxs_pat_anchor( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_PatternCase_,l,"pat_anchor",1)
	return mxa_pat_anchor[mxs_index(_c,0,p,_PatternCase_)];
}
static ELEMENT   *mxa_numberofastrks;
static AttInstSq *mxw_numberofastrks;
ELEMENT  mxs_numberofastrks( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ItemList_,l,"numberofastrks",1)
	return mxa_numberofastrks[mxs_index(_c,0,p,_ItemList_)];
}
static ELEMENT   *mxa_predeclprodcd;
static AttInstSq *mxw_predeclprodcd;
ELEMENT  mxs_predeclprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_PredeclProd_,l,"predeclprodcd",1)
	return mxa_predeclprodcd[mxs_index(_c,0,p,_PredeclProd_)];
}
static ELEMENT   *mxa_tupelprodcd;
static AttInstSq *mxw_tupelprodcd;
ELEMENT  mxs_tupelprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_TupelProd_,l,"tupelprodcd",1)
	return mxa_tupelprodcd[mxs_index(_c,0,p,_TupelProd_)];
}
static ELEMENT   *mxa_listprodcd;
static AttInstSq *mxw_listprodcd;
ELEMENT  mxs_listprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ListProd_,l,"listprodcd",1)
	return mxa_listprodcd[mxs_index(_c,0,p,_ListProd_)];
}
static ELEMENT   *mxa_classprodcd;
static AttInstSq *mxw_classprodcd;
ELEMENT  mxs_classprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ClassProd_,l,"classprodcd",1)
	return mxa_classprodcd[mxs_index(_c,0,p,_ClassProd_)];
}
static ELEMENT   *mxa_sces_appl;
static AttInstSq *mxw_sces_appl;
ELEMENT  mxs_sces_appl( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ApplyEntity_,l,"sces_appl",1)
	return mxa_sces_appl[mxs_index(_c,0,p,_ApplyEntity_)];
}
static ELEMENT   *mxa_sces1_cond;
static AttInstSq *mxw_sces1_cond;
ELEMENT  mxs_sces1_cond( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Condition_,l,"sces1_cond",1)
	return mxa_sces1_cond[mxs_index(_c,0,p,_Condition_)];
}
static ELEMENT   *mxa_sces2_cond;
static AttInstSq *mxw_sces2_cond;
ELEMENT  mxs_sces2_cond( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Condition_,l,"sces2_cond",1)
	return mxa_sces2_cond[mxs_index(_c,0,p,_Condition_)];
}
static ELEMENT   *mxa_sces1_let;
static AttInstSq *mxw_sces1_let;
ELEMENT  mxs_sces1_let( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_LetExpr_,l,"sces1_let",1)
	return mxa_sces1_let[mxs_index(_c,0,p,_LetExpr_)];
}
static ELEMENT   *mxa_sces2_let;
static AttInstSq *mxw_sces2_let;
ELEMENT  mxs_sces2_let( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_LetExpr_,l,"sces2_let",1)
	return mxa_sces2_let[mxs_index(_c,0,p,_LetExpr_)];
}
static ELEMENT   *mxa_sces_if;
static AttInstSq *mxw_sces_if;
ELEMENT  mxs_sces_if( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IfExpr_,l,"sces_if",1)
	return mxa_sces_if[mxs_index(_c,0,p,_IfExpr_)];
}
static ELEMENT   *mxa_sces1_fcase;
static AttInstSq *mxw_sces1_fcase;
ELEMENT  mxs_sces1_fcase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FormulaCase_,l,"sces1_fcase",1)
	return mxa_sces1_fcase[mxs_index(_c,0,p,_FormulaCase_)];
}
static ELEMENT   *mxa_sces2_fcase;
static AttInstSq *mxw_sces2_fcase;
ELEMENT  mxs_sces2_fcase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FormulaCase_,l,"sces2_fcase",1)
	return mxa_sces2_fcase[mxs_index(_c,0,p,_FormulaCase_)];
}
static ELEMENT   *mxa_sces_pcase;
static AttInstSq *mxw_sces_pcase;
ELEMENT  mxs_sces_pcase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_PatternCase_,l,"sces_pcase",1)
	return mxa_sces_pcase[mxs_index(_c,0,p,_PatternCase_)];
}
static ELEMENT   *mxa_aux_need;
static AttInstSq *mxw_aux_need;
ELEMENT  mxs_aux_need( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Section_,l,"aux_need",1)
	return mxa_aux_need[mxs_index(_c,0,p,_Section_)];
}
static ELEMENT   *mxa_res_var_no;
static AttInstSq *mxw_res_var_no;
ELEMENT  mxs_res_var_no( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ComposedExpr_,l,"res_var_no",1)
	return mxa_res_var_no[mxs_index(_c,0,p,_ComposedExpr_)];
}
static ELEMENT   *mxa_patnpos;
static AttInstSq *mxw_patnpos;
ELEMENT  mxs_patnpos( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Pattern_,l,"patnpos",1)
	return mxa_patnpos[mxs_index(_c,0,p,_Pattern_)];
}



ELEMENT  mxs_id(char *f, int l,ELEMENT ID){
 IFNIL(ID)
 IS(ID,_Ident_,l,"id",1)
	return mxs_idtos(_m,165,mxs_term(_m,165,ID));
}

ELEMENT  mxs_patlineno(char *f, int l,ELEMENT PN){
	ELEMENT mxv_0_1;
 IFNIL(PN)
 IS(PN,_Pattern_,l,"patlineno",1)
	{
		{
			ELEMENT mxv_p0, L, mxv_p1, mxv_p2, mxv_p3;
			mxv_p0 = PN;
						if( mxv_p0 != PN ) goto Lp1;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp1;
			mxv_p1 = mxs_son(_c,0,1,mxv_p0);
			if( !mxs_is(_c,0,mxv_p1,_Blank_) ) goto Lp1;
			if( mxs_numsons(_c,0,mxv_p1)!=1 ) goto Lp1;
			mxv_p2 = mxs_son(_c,0,1,mxv_p1);
						L = mxv_p2;
			mxv_0_1 = L;
			goto L1;
		}
		Lp1: ;
		mxv_0_1 = mxs_son(_m,167,mxs_itoe(_c,0,2),mxs_son(_m,167,mxs_itoe(_c,0,1),PN));
		L1: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_decl(char *f, int l,ELEMENT UID){
 IFNIL(UID)
 IS(UID,_UsedId_,l,"decl",1)
	return mxs_subterm(_m,196,mxs_itoe(_c,0,1),mxs_idtodecls(_m,196,mxs_term(_m,196,mxs_son(_m,196,mxs_itoe(_c,0,1),UID))));
}

ELEMENT  mxs_scope(char *f, int l,ELEMENT N){
	ELEMENT mxv_0_1;
 IFNIL(N)
 IS(N,_Node,l,"scope",1)
	{
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = N;
			if( !mxs_is(_c,0,mxv_p0,_Scope_) ) goto Lp2;
			if( mxv_p0 != N ) goto Lp2;
			mxv_0_1 = N;
			goto L4;
		}
		Lp2: ;
		{
			ELEMENT mxv_p0, L, mxv_p1, mxv_p2;
			mxv_p0 = mxs_fath(_c,0,N);
			if( mxv_p0==mxs_nil(_c,0) ) goto Lp3;
			if( !mxs_is(_c,0,mxv_p0,_LetExpr_) ) goto Lp3;
			L = mxv_p0;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp3;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
						if( mxv_p1 != N ) goto Lp3;
			mxv_0_1 = mxs_scope(_m,236,mxs_fath(_m,236,L));
			goto L4;
		}
		Lp3: ;
		mxv_0_1 = mxs_scope(_m,237,mxs_fath(_m,237,N));
		L4: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_lookup_params(char *f, int l,ELEMENT ID,ELEMENT N){
	ELEMENT mxv_0_1;
 IFNIL(ID) IFNIL(N)
 IS(ID,_Ident,l,"lookup_params",1) IS(N,_Name_,l,"lookup_params",2)
	{
		ELEMENT mxv_1_1;
		{
			ELEMENT mxv_p0, IDN, mxv_p1, mxv_p2;
			mxv_p0 = N;
			if( !mxs_is(_c,0,mxv_p0,_Name_) ) goto Lp6;
			if( mxv_p0 != N ) goto Lp6;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp6;
			mxv_p1 = mxs_son(_c,0,1,mxv_p0);
						IDN = mxv_p1;
			{
				if( mxs_eq(_m,0,ID,mxs_term(_m,248,IDN)) ){
					mxv_1_1 = N;
					goto L7;
				}
				mxv_1_1 = mxs_lookup_params(_m,249,ID,mxs_rbroth(_m,249,N));
				L7: ;
			}
			mxv_0_1 = mxv_1_1;
			goto L6;
		}
		Lp6: ;
		mxv_0_1 = mxs_nil(_m,250);
		L6: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_lookup_item(char *f, int l,ELEMENT ID,ELEMENT IT){
	ELEMENT mxv_0_1;
 IFNIL(ID) IFNIL(IT)
 IS(ID,_Ident,l,"lookup_item",1) IS(IT,_Item_,l,"lookup_item",2)
	{
		ELEMENT mxv_1_1;
		{
			ELEMENT mxv_p0, ILP, IDN, N, mxv_p1, mxv_p2, mxv_p3;
			mxv_p0 = IT;
			if( !mxs_is(_c,0,mxv_p0,_Pattern_) ) goto Lp7;
			if( mxv_p0 != IT ) goto Lp7;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp7;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
						ILP = mxv_p1;
			mxv_p1 = mxs_rbroth(_c,0,mxv_p1);
						N = mxv_p1;
			if( mxs_numsons(_c,0,mxv_p1)!=3 ) goto Lp7;
			mxv_p2 = mxs_son(_c,0,1,mxv_p1);
						IDN = mxv_p2;
			{
				if( mxs_eq(_m,0,ID,mxs_term(_m,255,IDN)) ){
					mxv_1_1 = N;
					goto L9;
				}
				if( mxs_is(_m,256,ILP,_ItemList_) ){
					mxv_1_1 = mxs_lookup_items(_m,256,ID,mxs_son(_m,256,mxs_itoe(_c,0,1),ILP));
					goto L9;
				}
				mxv_1_1 = mxs_nil(_m,257);
				L9: ;
			}
			mxv_0_1 = mxv_1_1;
			goto L8;
		}
		Lp7: ;
		{
			ELEMENT mxv_p0, IT1, mxv_p1, mxv_p2, mxv_p3;
			mxv_p0 = IT;
			if( !mxs_is(_c,0,mxv_p0,_Pattern_) ) goto Lp8;
			if( mxv_p0 != IT ) goto Lp8;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp8;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
			if( !mxs_is(_c,0,mxv_p1,_ItemList_) ) goto Lp8;
			if( mxs_numsons(_c,0,mxv_p1)<1 ) goto Lp8;
			mxv_p2 = mxs_son(_c,0,1,mxv_p1);
						IT1 = mxv_p2;
			mxv_p1 = mxs_rbroth(_c,0,mxv_p1);
			if( !mxs_is(_c,0,mxv_p1,_Blank_) ) goto Lp8;
			mxv_0_1 = mxs_lookup_items(_m,258,ID,IT1);
			goto L8;
		}
		Lp8: ;
		mxv_0_1 = mxs_nil(_m,259);
		L8: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_lookup_items(char *f, int l,ELEMENT ID,ELEMENT IT){
	ELEMENT mxv_0_1;
 IFNIL(ID) IFNIL(IT)
 IS(ID,_Ident,l,"lookup_items",1) IS(IT,_Item_,l,"lookup_items",2)
	{
		ELEMENT mxv_1_1;
		ELEMENT N;
		N = mxs_lookup_item(_m,263,ID,IT);
		{
			if( ( ! mxs_eq(_m,0,N,mxs_nil(_m,264))) ){
				mxv_1_1 = N;
				goto L10;
			}
			mxv_1_1 = mxs_lookup_items(_m,265,ID,mxs_rbroth(_m,265,IT));
			L10: ;
		}
		mxv_0_1 = mxv_1_1;
	}
	return mxv_0_1;
}

ELEMENT  mxs_lookup_cond(char *f, int l,ELEMENT ID,ELEMENT PAT){
	ELEMENT mxv_0_1;
 IFNIL(ID) IFNIL(PAT)
 IS(ID,_Ident,l,"lookup_cond",1) IS(PAT,_Pattern_,l,"lookup_cond",2)
	{
		ELEMENT mxv_1_1;
		ELEMENT N;
		N = mxs_lookup_item(_m,269,ID,PAT);
		{
			if( ( ! mxs_eq(_m,0,N,mxs_nil(_m,270))) ){
				mxv_1_1 = N;
				goto L11;
			}
			mxv_1_1 = mxs_lookup_cond(_m,271,ID,mxs_rbroth(_m,271,PAT));
			L11: ;
		}
		mxv_0_1 = mxv_1_1;
	}
	return mxv_0_1;
}

ELEMENT  mxs_lookup(char *f, int l,ELEMENT ID,ELEMENT S){
	ELEMENT mxv_0_1;
 IFNIL(ID) IFNIL(S)
 IS(ID,_Ident,l,"lookup",1) IS(S,_Scope_,l,"lookup",2)
	{
		ELEMENT mxv_1_1;
		{
			ELEMENT mxv_p0, NID, N, mxv_p1, mxv_p2, mxv_p3;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_LetExpr_) ) goto Lp9;
			if( mxv_p0 != S ) goto Lp9;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp9;
			mxv_p1 = mxs_son(_c,0,1,mxv_p0);
						N = mxv_p1;
			if( mxs_numsons(_c,0,mxv_p1)!=3 ) goto Lp9;
			mxv_p2 = mxs_son(_c,0,1,mxv_p1);
						NID = mxv_p2;
			{
				if( mxs_eq(_m,0,mxs_term(_m,276,NID),ID) ){
					mxv_1_1 = N;
					goto L13;
				}
				mxv_1_1 = mxs_lookup(_m,276,ID,mxs_encl_scope(_m,276,S));
				L13: ;
			}
			mxv_0_1 = mxv_1_1;
			goto L12;
		}
		Lp9: ;
		{
			ELEMENT mxv_p0, PAR, mxv_p1, mxv_p2, mxv_p3;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_ApplyEntity_) ) goto Lp10;
			if( mxv_p0 != S ) goto Lp10;
			if( mxs_numsons(_c,0,mxv_p0)<3 ) goto Lp10;
			mxv_p1 = mxs_son(_c,0,3,mxv_p0);
						if( mxs_numsons(_c,0,mxv_p1)<1 ) goto Lp10;
			mxv_p2 = mxs_son(_c,0,1,mxv_p1);
						PAR = mxv_p2;
			mxv_0_1 = mxs_lookup_params(_m,277,ID,PAR);
			goto L12;
		}
		Lp10: ;
		{
			ELEMENT mxv_p0, PAT, mxv_p1, mxv_p2, mxv_p3;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_Condition_) ) goto Lp11;
			if( mxv_p0 != S ) goto Lp11;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp11;
			mxv_p1 = mxs_son(_c,0,1,mxv_p0);
						if( mxs_numsons(_c,0,mxv_p1)<1 ) goto Lp11;
			mxv_p2 = mxs_son(_c,0,1,mxv_p1);
						PAT = mxv_p2;
			mxv_0_1 = mxs_lookup_cond(_m,278,ID,PAT);
			goto L12;
		}
		Lp11: ;
		{
			ELEMENT mxv_p0, PAT, mxv_p1, mxv_p2;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_PatternCase_) ) goto Lp12;
			if( mxv_p0 != S ) goto Lp12;
			if( mxs_numsons(_c,0,mxv_p0)!=2 ) goto Lp12;
			mxv_p1 = mxs_son(_c,0,1,mxv_p0);
						PAT = mxv_p1;
			{
				ELEMENT mxv_2_1;
				ELEMENT L;
				L = mxs_lookup(_m,280,ID,mxs_encl_scope(_m,280,S));
				{
					if( ( ! mxs_eq(_m,0,L,mxs_nil(_m,281))) ){
						mxv_2_1 = L;
						goto L14;
					}
					mxv_2_1 = mxs_lookup_item(_m,282,ID,PAT);
					L14: ;
				}
				mxv_1_1 = mxv_2_1;
			}
			mxv_0_1 = mxv_1_1;
			goto L12;
		}
		Lp12: ;
		mxv_0_1 = mxs_nil(_m,283);
		L12: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_search_bound_name_rec(char *f, int l,ELEMENT IT,ELEMENT dpth){
	ELEMENT mxv_0_1;
 IFNIL(IT) IFNIL(dpth)
 IS(IT,_Item_,l,"search_bound_name_rec",1) IS(dpth,_Int,l,"search_bound_name_rec",2)
	{
		ELEMENT mxv_1_1;
		ELEMENT ND;
		ND = mxs_search_bound_name(_m,319,IT,dpth);
		{
			ELEMENT mxv_2_1;
			ELEMENT NDR;
			NDR = mxs_search_bound_name_rec(_m,320,mxs_rbroth(_m,320,IT),dpth);
			{
				if( mxs_eq(_m,0,ND,mxs_nil(_m,321)) ){
					mxv_2_1 = NDR;
					goto L17;
				}
				if( mxs_eq(_m,0,NDR,mxs_nil(_m,322)) ){
					mxv_2_1 = ND;
					goto L17;
				}
				if( mxs_lt(_m,323,mxs_subterm(_m,323,mxs_itoe(_c,0,2),ND),mxs_subterm(_m,323,mxs_itoe(_c,0,2),NDR)) ){
					mxv_2_1 = ND;
					goto L17;
				}
				mxv_2_1 = NDR;
				L17: ;
			}
			mxv_1_1 = mxv_2_1;
		}
		mxv_0_1 = mxv_1_1;
	}
	return mxv_0_1;
}

ELEMENT  mxs_search_bound_name(char *f, int l,ELEMENT IT,ELEMENT dpth){
	ELEMENT mxv_0_1;
 IFNIL(IT) IFNIL(dpth)
 IS(IT,_Item_,l,"search_bound_name",1) IS(dpth,_Int,l,"search_bound_name",2)
	{
		ELEMENT mxv_1_1;
		{
			ELEMENT mxv_p0, ITL, N, mxv_p1, mxv_p2;
			mxv_p0 = IT;
			if( !mxs_is(_c,0,mxv_p0,_Pattern_) ) goto Lp13;
			if( mxv_p0 != IT ) goto Lp13;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp13;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
						ITL = mxv_p1;
			mxv_p1 = mxs_rbroth(_c,0,mxv_p1);
						N = mxv_p1;
			{
				ELEMENT mxv_2_1;
				if( (mxs_is(_m,328,N,_Name_)&&( ! mxs_eq(_m,0,mxs_bind_pos(_m,328,N),N))) ){
					mxv_1_1 = mxs_NameDepthTup(_m,328,N,dpth);
					goto L19;
				}
				{
					{
						ELEMENT mxv_p0, IT1, mxv_p1, mxv_p2;
						mxv_p0 = ITL;
						if( !mxs_is(_c,0,mxv_p0,_ItemList_) ) goto Lp14;
						if( mxv_p0 != ITL ) goto Lp14;
						if( mxs_numsons(_c,0,mxv_p0)<1 ) goto Lp14;
						mxv_p1 = mxs_son(_c,0,1,mxv_p0);
												IT1 = mxv_p1;
						mxv_2_1 = mxs_search_bound_name_rec(_m,329,IT1,mxs_add(_m,329,dpth,mxs_itoe(_c,0,1)));
						goto L20;
					}
					Lp14: ;
					mxv_2_1 = mxs_nil(_m,330);
					L20: ;
				}
				mxv_1_1 = mxv_2_1;
				L19: ;
			}
			mxv_0_1 = mxv_1_1;
			goto L18;
		}
		Lp13: ;
		mxv_0_1 = mxs_nil(_m,331);
		L18: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_countastrks(char *f, int l,ELEMENT ITL,ELEMENT sum){
	ELEMENT mxv_0_1;
 IFNIL(ITL) IFNIL(sum)
 IS(ITL,_ItemList,l,"countastrks",1) IS(sum,_Int,l,"countastrks",2)
	{
		if( mxs_eq(_m,0,ITL,mxs_ItemList(_m,339)) ){
			mxv_0_1 = sum;
			goto L21;
		}
		if( mxs_is(_m,340,mxs_subterm(_m,340,mxs_itoe(_c,0,1),ITL),_Asterisk) ){
			mxv_0_1 = mxs_countastrks(_m,340,mxs_back(_m,340,ITL),mxs_add(_m,340,sum,mxs_itoe(_c,0,1)));
			goto L21;
		}
		mxv_0_1 = mxs_countastrks(_m,341,mxs_back(_m,341,ITL),sum);
		L21: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_smallestlistprodcd(char *f, int l){
	return mxs_neg(_m,423,mxs_add(_m,423,mxs_number(_m,423,_ListProd_),mxs_add(_m,424,mxs_number(_m,424,_TupelProd_),mxs_sub(_m,424,mxs_number(_m,424,_PredeclProd_),mxs_itoe(_c,0,2)))));
}

ELEMENT  mxs_prodcd(char *f, int l,ELEMENT PN){
	ELEMENT mxv_0_1;
 IFNIL(PN)
 IS(PN,_Production_,l,"prodcd",1)
	{
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = PN;
			if( !mxs_is(_c,0,mxv_p0,_PredeclProd_) ) goto Lp16;
			if( mxv_p0 != PN ) goto Lp16;
			mxv_0_1 = mxs_predeclprodcd(_m,431,PN);
			goto L24;
		}
		Lp16: ;
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = PN;
			if( !mxs_is(_c,0,mxv_p0,_ClassProd_) ) goto Lp17;
			if( mxv_p0 != PN ) goto Lp17;
			mxv_0_1 = mxs_classprodcd(_m,432,PN);
			goto L24;
		}
		Lp17: ;
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = PN;
			if( !mxs_is(_c,0,mxv_p0,_TupelProd_) ) goto Lp18;
			if( mxv_p0 != PN ) goto Lp18;
			mxv_0_1 = mxs_tupelprodcd(_m,433,PN);
			goto L24;
		}
		Lp18: ;
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = PN;
			if( !mxs_is(_c,0,mxv_p0,_ListProd_) ) goto Lp19;
			if( mxv_p0 != PN ) goto Lp19;
			mxv_0_1 = mxs_listprodcd(_m,434,PN);
			goto L24;
		}
		Lp19: ;
		mxv_0_1 = mxs_nil(_m,435);
		L24: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_list_compexprs(char *f, int l,ELEMENT N,ELEMENT CL){
	ELEMENT mxv_0_1;
 IFNIL(N) IFNIL(CL)
 IS(N,_Node,l,"list_compexprs",1) IS(CL,_CompExprNodeList,l,"list_compexprs",2)
	{
		if( mxs_eq(_m,0,mxs_rbroth(_m,452,N),mxs_nil(_m,452)) ){
			mxv_0_1 = mxs_conc(_m,452,CL,mxs_compexprs(_m,452,N));
			goto L25;
		}
		mxv_0_1 = mxs_list_compexprs(_m,453,mxs_rbroth(_m,453,N),mxs_conc(_m,453,CL,mxs_compexprs(_m,453,N)));
		L25: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_compexprs(char *f, int l,ELEMENT N){
	ELEMENT mxv_0_1;
 IFNIL(N)
 IS(N,_Node,l,"compexprs",1)
	{
		if( mxs_is(_m,456,N,_ComposedExpr_) ){
			mxv_0_1 = mxs_appback(_m,456,mxs_CompExprNodeList(_m,456),N);
			goto L26;
		}
		if( mxs_eq(_m,0,mxs_numsons(_m,457,N),mxs_itoe(_c,0,0)) ){
			mxv_0_1 = mxs_CompExprNodeList(_m,457);
			goto L26;
		}
		mxv_0_1 = mxs_list_compexprs(_m,458,mxs_son(_m,458,mxs_itoe(_c,0,1),N),mxs_CompExprNodeList(_m,458));
		L26: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_max2(char *f, int l,ELEMENT m,ELEMENT n){
	ELEMENT mxv_0_1;
 IFNIL(m) IFNIL(n)
 IS(m,_Int,l,"max2",1) IS(n,_Int,l,"max2",2)
	{
		if( mxs_lt(_m,471,m,n) ){
			mxv_0_1 = n;
			goto L27;
		}
		mxv_0_1 = m;
		L27: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_aux_need_case(char *f, int l,ELEMENT C){
	ELEMENT mxv_0_1;
 IFNIL(C)
 IS(C,_Case_,l,"aux_need_case",1)
	{
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = C;
			if( !mxs_is(_c,0,mxv_p0,_PatternCase_) ) goto Lp20;
			if( mxv_p0 != C ) goto Lp20;
			mxv_0_1 = mxs_numsubterms(_m,474,mxs_sces_pcase(_m,474,C));
			goto L28;
		}
		Lp20: ;
		mxv_0_1 = mxs_max2(_m,475,mxs_numsubterms(_m,475,mxs_sces1_fcase(_m,475,C)),mxs_numsubterms(_m,475,mxs_sces2_fcase(_m,475,C)));
		L28: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_aux_need_cases(char *f, int l,ELEMENT C){
	ELEMENT mxv_0_1;
 IFNIL(C)
 IS(C,_Case_,l,"aux_need_cases",1)
	{
		if( mxs_eq(_m,0,mxs_rbroth(_m,478,C),mxs_nil(_m,478)) ){
			mxv_0_1 = mxs_aux_need_case(_m,478,C);
			goto L29;
		}
		mxv_0_1 = mxs_max2(_m,479,mxs_aux_need_case(_m,479,C),mxs_aux_need_cases(_m,479,mxs_rbroth(_m,479,C)));
		L29: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_encl_sces(char *f, int l,ELEMENT N){
	ELEMENT mxv_0_1;
 IFNIL(N)
 IS(N,_Node,l,"encl_sces",1)
	{
		{
			ELEMENT mxv_p0, A, mxv_p1, mxv_p2;
			mxv_p0 = mxs_fath(_c,0,N);
			if( mxv_p0==mxs_nil(_c,0) ) goto Lp26;
			if( !mxs_is(_c,0,mxv_p0,_ApplyEntity_) ) goto Lp26;
			A = mxv_p0;
			if( mxs_numsons(_c,0,mxv_p0)<1 ) goto Lp26;
			mxv_p1 = mxs_son(_c,0,-1,mxv_p0);
						if( mxv_p1 != N ) goto Lp26;
			mxv_0_1 = mxs_sces_appl(_m,494,A);
			goto L31;
		}
		Lp26: ;
		{
			ELEMENT mxv_p0, C, mxv_p1, mxv_p2;
			mxv_p0 = mxs_fath(_c,0,N);
			if( mxv_p0==mxs_nil(_c,0) ) goto Lp27;
			if( !mxs_is(_c,0,mxv_p0,_Condition_) ) goto Lp27;
			C = mxv_p0;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp27;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
						if( mxv_p1 != N ) goto Lp27;
			mxv_0_1 = mxs_sces1_cond(_m,495,C);
			goto L31;
		}
		Lp27: ;
		{
			ELEMENT mxv_p0, C, mxv_p1, mxv_p2;
			mxv_p0 = mxs_fath(_c,0,N);
			if( mxv_p0==mxs_nil(_c,0) ) goto Lp28;
			if( !mxs_is(_c,0,mxv_p0,_Condition_) ) goto Lp28;
			C = mxv_p0;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp28;
			mxv_p1 = mxs_son(_c,0,3,mxv_p0);
						if( mxv_p1 != N ) goto Lp28;
			mxv_0_1 = mxs_sces2_cond(_m,496,C);
			goto L31;
		}
		Lp28: ;
		{
			ELEMENT mxv_p0, L, mxv_p1, mxv_p2;
			mxv_p0 = mxs_fath(_c,0,N);
			if( mxv_p0==mxs_nil(_c,0) ) goto Lp29;
			if( !mxs_is(_c,0,mxv_p0,_LetExpr_) ) goto Lp29;
			L = mxv_p0;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp29;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
						if( mxv_p1 != N ) goto Lp29;
			mxv_0_1 = mxs_sces1_let(_m,497,L);
			goto L31;
		}
		Lp29: ;
		{
			ELEMENT mxv_p0, L, mxv_p1, mxv_p2;
			mxv_p0 = mxs_fath(_c,0,N);
			if( mxv_p0==mxs_nil(_c,0) ) goto Lp30;
			if( !mxs_is(_c,0,mxv_p0,_LetExpr_) ) goto Lp30;
			L = mxv_p0;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp30;
			mxv_p1 = mxs_son(_c,0,3,mxv_p0);
						if( mxv_p1 != N ) goto Lp30;
			mxv_0_1 = mxs_sces2_let(_m,498,L);
			goto L31;
		}
		Lp30: ;
		{
			ELEMENT mxv_p0, I, mxv_p1, mxv_p2;
			mxv_p0 = mxs_fath(_c,0,N);
			if( mxv_p0==mxs_nil(_c,0) ) goto Lp31;
			if( !mxs_is(_c,0,mxv_p0,_IfExpr_) ) goto Lp31;
			I = mxv_p0;
			if( mxs_numsons(_c,0,mxv_p0)!=2 ) goto Lp31;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
						if( mxv_p1 != N ) goto Lp31;
			mxv_0_1 = mxs_sces_if(_m,499,I);
			goto L31;
		}
		Lp31: ;
		{
			ELEMENT mxv_p0, F, mxv_p1, mxv_p2;
			mxv_p0 = mxs_fath(_c,0,N);
			if( mxv_p0==mxs_nil(_c,0) ) goto Lp32;
			if( !mxs_is(_c,0,mxv_p0,_FormulaCase_) ) goto Lp32;
			F = mxv_p0;
			if( mxs_numsons(_c,0,mxv_p0)!=2 ) goto Lp32;
			mxv_p1 = mxs_son(_c,0,1,mxv_p0);
						if( mxv_p1 != N ) goto Lp32;
			mxv_0_1 = mxs_sces1_fcase(_m,500,F);
			goto L31;
		}
		Lp32: ;
		{
			ELEMENT mxv_p0, F, mxv_p1, mxv_p2;
			mxv_p0 = mxs_fath(_c,0,N);
			if( mxv_p0==mxs_nil(_c,0) ) goto Lp33;
			if( !mxs_is(_c,0,mxv_p0,_FormulaCase_) ) goto Lp33;
			F = mxv_p0;
			if( mxs_numsons(_c,0,mxv_p0)!=2 ) goto Lp33;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
						if( mxv_p1 != N ) goto Lp33;
			mxv_0_1 = mxs_sces2_fcase(_m,501,F);
			goto L31;
		}
		Lp33: ;
		{
			ELEMENT mxv_p0, P, mxv_p1, mxv_p2;
			mxv_p0 = mxs_fath(_c,0,N);
			if( mxv_p0==mxs_nil(_c,0) ) goto Lp34;
			if( !mxs_is(_c,0,mxv_p0,_PatternCase_) ) goto Lp34;
			P = mxv_p0;
			if( mxs_numsons(_c,0,mxv_p0)!=2 ) goto Lp34;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
						if( mxv_p1 != N ) goto Lp34;
			mxv_0_1 = mxs_sces_pcase(_m,502,P);
			goto L31;
		}
		Lp34: ;
		mxv_0_1 = mxs_encl_sces(_m,503,mxs_fath(_m,503,N));
		L31: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_position(char *f, int l,ELEMENT elem,ELEMENT list){
	ELEMENT mxv_0_1;
 IFNIL(elem) IFNIL(list)
 IS(elem,_Element,l,"position",1) IS(list,_Term,l,"position",2)
	{
		if( mxs_eq(_m,0,mxs_subterm(_m,507,mxs_itoe(_c,0,1),list),elem) ){
			mxv_0_1 = mxs_itoe(_c,0,1);
			goto L32;
		}
		mxv_0_1 = mxs_add(_m,508,mxs_position(_m,508,elem,mxs_back(_m,508,list)),mxs_itoe(_c,0,1));
		L32: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_next_left_pat(char *f, int l,ELEMENT IT){
	ELEMENT mxv_0_1;
 IFNIL(IT)
 IS(IT,_Item_,l,"next_left_pat",1)
	{
		ELEMENT mxv_1_1;
		ELEMENT LIT;
		LIT = mxs_lbroth(_m,522,IT);
		{
			{
				ELEMENT mxv_p0, mxv_p1;
				mxv_p0 = LIT;
				if( !mxs_is(_c,0,mxv_p0,_Blank_) ) goto Lp35;
				if( mxv_p0 != LIT ) goto Lp35;
				mxv_1_1 = mxs_next_left_pat(_m,523,LIT);
				goto L33;
			}
			Lp35: ;
			{
				ELEMENT mxv_p0, mxv_p1;
				mxv_p0 = LIT;
				if( !mxs_is(_c,0,mxv_p0,_Asterisk_) ) goto Lp36;
				if( mxv_p0 != LIT ) goto Lp36;
				mxv_1_1 = mxs_next_left_pat(_m,524,LIT);
				goto L33;
			}
			Lp36: ;
			{
				ELEMENT mxv_p0, mxv_p1;
				mxv_p0 = LIT;
				if( !mxs_is(_c,0,mxv_p0,_Pattern_) ) goto Lp37;
				if( mxv_p0 != LIT ) goto Lp37;
				mxv_1_1 = LIT;
				goto L33;
			}
			Lp37: ;
			mxv_1_1 = mxs_nil(_m,526);
			L33: ;
		}
		mxv_0_1 = mxv_1_1;
	}
	return mxv_0_1;
}

ELEMENT  mxs_patnposition(char *f, int l,ELEMENT IT,ELEMENT dist){
	ELEMENT mxv_0_1;
 IFNIL(IT) IFNIL(dist)
 IS(IT,_Item_,l,"patnposition",1) IS(dist,_Int,l,"patnposition",2)
	{
		ELEMENT mxv_1_1;
		ELEMENT LIT;
		LIT = mxs_lbroth(_m,530,IT);
		{
			{
				ELEMENT mxv_p0, mxv_p1;
				mxv_p0 = LIT;
				if( !mxs_is(_c,0,mxv_p0,_Blank_) ) goto Lp38;
				if( mxv_p0 != LIT ) goto Lp38;
				mxv_1_1 = mxs_patnposition(_m,531,LIT,mxs_add(_m,531,dist,mxs_itoe(_c,0,1)));
				goto L34;
			}
			Lp38: ;
			{
				ELEMENT mxv_p0, mxv_p1;
				mxv_p0 = LIT;
				if( !mxs_is(_c,0,mxv_p0,_Asterisk_) ) goto Lp39;
				if( mxv_p0 != LIT ) goto Lp39;
				mxv_1_1 = mxs_patnposition(_m,532,LIT,dist);
				goto L34;
			}
			Lp39: ;
			{
				ELEMENT mxv_p0, mxv_p1;
				mxv_p0 = LIT;
				if( !mxs_is(_c,0,mxv_p0,_Pattern_) ) goto Lp40;
				if( mxv_p0 != LIT ) goto Lp40;
				mxv_1_1 = dist;
				goto L34;
			}
			Lp40: ;
			mxv_1_1 = dist;
			L34: ;
		}
		mxv_0_1 = mxv_1_1;
	}
	return mxv_0_1;
}

ELEMENT  mxs_next_pat_for_codegen(char *f, int l,ELEMENT PN){
	ELEMENT mxv_0_1;
 IFNIL(PN)
 IS(PN,_Pattern_,l,"next_pat_for_codegen",1)
	{
		ELEMENT mxv_1_1;
		{
			ELEMENT mxv_p0, SPN, mxv_p1, mxv_p2, mxv_p3;
			mxv_p0 = PN;
						if( mxv_p0 != PN ) goto Lp41;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp41;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
			if( !mxs_is(_c,0,mxv_p1,_ItemList_) ) goto Lp41;
			if( mxs_numsons(_c,0,mxv_p1)<1 ) goto Lp41;
			mxv_p2 = mxs_son(_c,0,-1,mxv_p1);
			if( !mxs_is(_c,0,mxv_p2,_Pattern_) ) goto Lp41;
			SPN = mxv_p2;
			mxv_0_1 = SPN;
			goto L36;
		}
		Lp41: ;
		{
			ELEMENT mxv_p0, IT, mxv_p1, mxv_p2, mxv_p3;
			mxv_p0 = PN;
						if( mxv_p0 != PN ) goto Lp42;
			if( mxs_numsons(_c,0,mxv_p0)!=3 ) goto Lp42;
			mxv_p1 = mxs_son(_c,0,2,mxv_p0);
			if( !mxs_is(_c,0,mxv_p1,_ItemList_) ) goto Lp42;
			if( mxs_numsons(_c,0,mxv_p1)<1 ) goto Lp42;
			mxv_p2 = mxs_son(_c,0,-1,mxv_p1);
						IT = mxv_p2;
			{
				ELEMENT mxv_2_1;
				ELEMENT NLP;
				NLP = mxs_next_left_pat(_m,546,IT);
				{
					if( ( ! mxs_eq(_m,0,NLP,mxs_nil(_m,547))) ){
						mxv_2_1 = NLP;
						goto L37;
					}
					mxv_2_1 = mxs_next_pat_upthetree(_m,547,PN);
					L37: ;
				}
				mxv_1_1 = mxv_2_1;
			}
			mxv_0_1 = mxv_1_1;
			goto L36;
		}
		Lp42: ;
		mxv_0_1 = mxs_next_pat_upthetree(_m,548,PN);
		L36: ;
	}
	return mxv_0_1;
}

ELEMENT  mxs_next_pat_upthetree(char *f, int l,ELEMENT PN){
	ELEMENT mxv_0_1;
 IFNIL(PN)
 IS(PN,_Pattern_,l,"next_pat_upthetree",1)
	{
		if( mxs_is(_m,552,mxs_patnpos(_m,552,PN),_TopPosition) ){
			mxv_0_1 = mxs_rbroth(_m,552,PN);
			goto L38;
		}
		if( mxs_is(_m,553,mxs_patnpos(_m,553,PN),_AbsPosition) ){
			mxv_0_1 = mxs_next_pat_upthetree(_m,553,mxs_fath(_m,553,mxs_fath(_m,553,PN)));
			goto L38;
		}
		mxv_0_1 = mxs_next_left_pat(_m,554,PN);
		L38: ;
	}
	return mxv_0_1;
}



long  mxs_in(char *f, int l,ELEMENT N,ELEMENT lb,ELEMENT ub){
 ISORNIL(N,_Node,l,"in",1) ISORNIL(lb,_Point,l,"in",2) ISORNIL(ub,_Point,l,"in",3)
	return ((mxs_bef(_m,170,lb,mxs_before(_m,170,N))||mxs_eq(_m,0,lb,mxs_before(_m,170,N)))&&(mxs_bef(_m,171,mxs_after(_m,171,N),ub)||mxs_eq(_m,0,ub,mxs_after(_m,171,N))));
}

long  mxs_ex_pattern_inbetween(char *f, int l,ELEMENT IT1,ELEMENT IT2){
 ISORNIL(IT1,_Item_,l,"ex_pattern_inbetween",1) ISORNIL(IT2,_Item_,l,"ex_pattern_inbetween",2)
	return (mxs_is(_m,347,IT1,_Pattern_)||(( ! mxs_eq(_m,0,IT1,IT2))&&(mxs_is(_m,348,IT1,_Blank_)&&mxs_ex_pattern_inbetween(_m,348,mxs_rbroth(_m,348,IT1),IT2))));
}

long  mxs_is_relev_att_access(char *f, int l,ELEMENT FA){
 ISORNIL(FA,_FuncAppl_,l,"is_relev_att_access",1)
	return (mxs_is(_m,517,mxs_fath(_m,517,mxs_decl(_m,517,mxs_son(_m,517,mxs_itoe(_c,0,1),FA))),_Attribute_)&&mxs_desc(_m,518,FA,mxs_fath(_m,518,mxs_fath(_m,518,mxs_decl(_m,518,mxs_son(_m,518,mxs_itoe(_c,0,1),FA))))));
}



static  void  mxe_encl_scope( ELEMENT S ){
	ELEMENT mxv_0_1;
	ELEMENT mxv_ax,mxv_par = S;
	AttInstSq mxv_waitsq, mxv_wsq;
	{
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_LetExpr_) ) goto Lp4;
			if( mxv_p0 != S ) goto Lp4;
			mxv_0_1 = mxs_scope(_m,240,mxs_fath(_m,240,S));
			goto L5;
		}
		Lp4: ;
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_PatternCase_) ) goto Lp5;
			if( mxv_p0 != S ) goto Lp5;
			mxv_0_1 = mxs_scope(_m,241,mxs_fath(_m,241,S));
			goto L5;
		}
		Lp5: ;
		mxv_0_1 = mxs_nil(_m,242);
		L5: ;
	}
	mxv_ax = mxs_index(_c,0,S,_Scope_);
	mxa_encl_scope[ mxv_ax ] = mxv_0_1;
/*  Code for Propagation  */
	mxv_waitsq = mxw_encl_scope[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_bind_pos( ELEMENT N ){
	ELEMENT mxv_0_1;
	ELEMENT mxv_ax,mxv_par = N;
	AttInstSq mxv_waitsq, mxv_wsq;
	{
		ELEMENT mxv_1_1;
		if( mxs_is(_m,305,mxs_fath(_m,305,N),_NameList_) ){
			mxv_0_1 = N;
			goto L15;
		}
		if( (mxs_is(_m,306,mxs_fath(_m,306,N),_LetExpr_)&&mxs_eq(_m,0,mxs_son(_m,306,mxs_itoe(_c,0,1),mxs_fath(_m,306,N)),N)) ){
			mxv_0_1 = N;
			goto L15;
		}
		if( (mxs_is(_m,307,mxs_scope(_m,307,N),_Condition_)&&mxs_desc(_m,307,N,mxs_son(_m,307,mxs_itoe(_c,0,1),mxs_scope(_m,307,N)))) ){
			mxv_0_1 = N;
			goto L15;
		}
		if( mxs_is(_m,308,mxs_fath(_m,308,N),_Pattern_) ){
			{
				ELEMENT mxv_2_1;
				ELEMENT BDP;
				BDP = mxs_lookup(_m,309,mxs_term(_m,309,mxs_son(_m,309,mxs_itoe(_c,0,1),N)),mxs_encl_scope(_m,309,mxs_scope(_m,309,N)));
				{
					if( mxs_eq(_m,0,BDP,mxs_nil(_m,310)) ){
						mxv_2_1 = N;
						goto L16;
					}
					mxv_2_1 = BDP;
					L16: ;
				}
				mxv_1_1 = mxv_2_1;
			}
			mxv_0_1 = mxv_1_1;
			goto L15;
		}
		mxv_0_1 = mxs_lookup(_m,311,mxs_term(_m,311,mxs_son(_m,311,mxs_itoe(_c,0,1),N)),mxs_scope(_m,311,N));
		L15: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Name_);
	mxa_bind_pos[ mxv_ax ] = mxv_0_1;
/*  Code for Propagation  */
	mxv_waitsq = mxw_bind_pos[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_pat_anchor( ELEMENT PCN ){
	ELEMENT mxv_ax,mxv_par = PCN;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,PCN,_PatternCase_);
	mxa_pat_anchor[ mxv_ax ] = mxs_search_bound_name(_m,335,mxs_son(_m,335,mxs_itoe(_c,0,1),PCN),mxs_itoe(_c,0,0));
/*  Code for Propagation  */
	mxv_waitsq = mxw_pat_anchor[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_numberofastrks( ELEMENT ITL ){
	ELEMENT mxv_ax,mxv_par = ITL;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,ITL,_ItemList_);
	mxa_numberofastrks[ mxv_ax ] = mxs_countastrks(_m,343,mxs_term(_m,343,ITL),mxs_itoe(_c,0,0));
/*  Code for Propagation  */
	mxv_waitsq = mxw_numberofastrks[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_predeclprodcd( ELEMENT PP ){
	ELEMENT mxv_0_1;
	ELEMENT mxv_ax,mxv_par = PP;
	AttInstSq mxv_waitsq, mxv_wsq;
	{
		ELEMENT mxv_1_1;
		{
			ELEMENT mxv_p0, ID, mxv_p1, mxv_p2, mxv_p3;
			mxv_p0 = PP;
			if( !mxs_is(_c,0,mxv_p0,_PredeclProd_) ) goto Lp15;
			if( mxv_p0 != PP ) goto Lp15;
			if( mxs_numsons(_c,0,mxv_p0)!=1 ) goto Lp15;
			mxv_p1 = mxs_son(_c,0,1,mxv_p0);
						if( mxs_numsons(_c,0,mxv_p1)!=3 ) goto Lp15;
			mxv_p2 = mxs_son(_c,0,1,mxv_p1);
						ID = mxv_p2;
			{
				if( mxs_eq(_m,0,mxs_id(_m,397,ID),mxs_atoe(_c,0,"Node")) ){
					mxv_1_1 = mxs_itoe(_c,0,2);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,398,ID),mxs_atoe(_c,0,"Point")) ){
					mxv_1_1 = mxs_itoe(_c,0,1);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,399,ID),mxs_atoe(_c,0,"nil")) ){
					mxv_1_1 = mxs_itoe(_c,0,-1);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,400,ID),mxs_atoe(_c,0,"Term")) ){
					mxv_1_1 = mxs_itoe(_c,0,-2);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,401,ID),mxs_atoe(_c,0,"NodeSort")) ){
					mxv_1_1 = mxs_itoe(_c,0,-3);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,402,ID),mxs_atoe(_c,0,"PredeclSort")) ){
					mxv_1_1 = mxs_itoe(_c,0,-4);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,403,ID),mxs_atoe(_c,0,"ClassSort")) ){
					mxv_1_1 = mxs_itoe(_c,0,-5);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,404,ID),mxs_atoe(_c,0,"TupelSort")) ){
					mxv_1_1 = mxs_itoe(_c,0,-6);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,405,ID),mxs_atoe(_c,0,"ListSort")) ){
					mxv_1_1 = mxs_itoe(_c,0,-7);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,406,ID),mxs_atoe(_c,0,"Ident")) ){
					mxv_1_1 = mxs_itoe(_c,0,-8);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,407,ID),mxs_atoe(_c,0,"Bool")) ){
					mxv_1_1 = mxs_itoe(_c,0,-9);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,408,ID),mxs_atoe(_c,0,"Char")) ){
					mxv_1_1 = mxs_itoe(_c,0,-10);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,409,ID),mxs_atoe(_c,0,"Int")) ){
					mxv_1_1 = mxs_itoe(_c,0,-11);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,410,ID),mxs_atoe(_c,0,"String")) ){
					mxv_1_1 = mxs_itoe(_c,0,-12);
					goto L23;
				}
				if( mxs_eq(_m,0,mxs_id(_m,411,ID),mxs_atoe(_c,0,"Reference")) ){
					mxv_1_1 = mxs_itoe(_c,0,-13);
					goto L23;
				}
				mxv_1_1 = mxs_nil(_m,412);
				L23: ;
			}
			mxv_0_1 = mxv_1_1;
			goto L22;
		}
		Lp15: ;
		mxv_0_1 = mxs_nil(_m,413);
		L22: ;
	}
	mxv_ax = mxs_index(_c,0,PP,_PredeclProd_);
	mxa_predeclprodcd[ mxv_ax ] = mxv_0_1;
/*  Code for Propagation  */
	mxv_waitsq = mxw_predeclprodcd[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_tupelprodcd( ELEMENT TP ){
	ELEMENT mxv_ax,mxv_par = TP;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,TP,_TupelProd_);
	mxa_tupelprodcd[ mxv_ax ] = mxs_neg(_m,416,mxs_add(_m,416,mxs_index(_m,416,TP,_TupelProd_),mxs_sub(_m,416,mxs_number(_m,416,_PredeclProd_),mxs_itoe(_c,0,2))));
/*  Code for Propagation  */
	mxv_waitsq = mxw_tupelprodcd[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_listprodcd( ELEMENT LP ){
	ELEMENT mxv_ax,mxv_par = LP;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,LP,_ListProd_);
	mxa_listprodcd[ mxv_ax ] = mxs_neg(_m,419,mxs_add(_m,419,mxs_index(_m,419,LP,_ListProd_),mxs_add(_m,420,mxs_number(_m,420,_TupelProd_),mxs_sub(_m,420,mxs_number(_m,420,_PredeclProd_),mxs_itoe(_c,0,2)))));
/*  Code for Propagation  */
	mxv_waitsq = mxw_listprodcd[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_classprodcd( ELEMENT CP ){
	ELEMENT mxv_ax,mxv_par = CP;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,CP,_ClassProd_);
	mxa_classprodcd[ mxv_ax ] = mxs_sub(_m,427,mxs_smallestlistprodcd(_m,427),mxs_index(_m,427,CP,_ClassProd_));
/*  Code for Propagation  */
	mxv_waitsq = mxw_classprodcd[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_sces_appl( ELEMENT A ){
	ELEMENT mxv_ax,mxv_par = A;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,A,_ApplyEntity_);
	mxa_sces_appl[ mxv_ax ] = mxs_compexprs(_m,460,mxs_son(_m,460,mxs_itoe(_c,0,-1),A));
/*  Code for Propagation  */
	mxv_waitsq = mxw_sces_appl[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_sces1_cond( ELEMENT C ){
	ELEMENT mxv_ax,mxv_par = C;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,C,_Condition_);
	mxa_sces1_cond[ mxv_ax ] = mxs_compexprs(_m,461,mxs_son(_m,461,mxs_itoe(_c,0,2),C));
/*  Code for Propagation  */
	mxv_waitsq = mxw_sces1_cond[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_sces2_cond( ELEMENT C ){
	ELEMENT mxv_ax,mxv_par = C;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,C,_Condition_);
	mxa_sces2_cond[ mxv_ax ] = mxs_compexprs(_m,462,mxs_son(_m,462,mxs_itoe(_c,0,3),C));
/*  Code for Propagation  */
	mxv_waitsq = mxw_sces2_cond[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_sces1_let( ELEMENT L ){
	ELEMENT mxv_ax,mxv_par = L;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,L,_LetExpr_);
	mxa_sces1_let[ mxv_ax ] = mxs_compexprs(_m,463,mxs_son(_m,463,mxs_itoe(_c,0,2),L));
/*  Code for Propagation  */
	mxv_waitsq = mxw_sces1_let[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_sces2_let( ELEMENT L ){
	ELEMENT mxv_ax,mxv_par = L;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,L,_LetExpr_);
	mxa_sces2_let[ mxv_ax ] = mxs_compexprs(_m,464,mxs_son(_m,464,mxs_itoe(_c,0,3),L));
/*  Code for Propagation  */
	mxv_waitsq = mxw_sces2_let[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_sces_if( ELEMENT I ){
	ELEMENT mxv_ax,mxv_par = I;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,I,_IfExpr_);
	mxa_sces_if[ mxv_ax ] = mxs_compexprs(_m,465,mxs_son(_m,465,mxs_itoe(_c,0,2),I));
/*  Code for Propagation  */
	mxv_waitsq = mxw_sces_if[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_sces1_fcase( ELEMENT F ){
	ELEMENT mxv_ax,mxv_par = F;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,F,_FormulaCase_);
	mxa_sces1_fcase[ mxv_ax ] = mxs_compexprs(_m,466,mxs_son(_m,466,mxs_itoe(_c,0,1),F));
/*  Code for Propagation  */
	mxv_waitsq = mxw_sces1_fcase[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_sces2_fcase( ELEMENT F ){
	ELEMENT mxv_ax,mxv_par = F;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,F,_FormulaCase_);
	mxa_sces2_fcase[ mxv_ax ] = mxs_compexprs(_m,467,mxs_son(_m,467,mxs_itoe(_c,0,2),F));
/*  Code for Propagation  */
	mxv_waitsq = mxw_sces2_fcase[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_sces_pcase( ELEMENT P ){
	ELEMENT mxv_ax,mxv_par = P;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,P,_PatternCase_);
	mxa_sces_pcase[ mxv_ax ] = mxs_compexprs(_m,468,mxs_son(_m,468,mxs_itoe(_c,0,2),P));
/*  Code for Propagation  */
	mxv_waitsq = mxw_sces_pcase[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_aux_need( ELEMENT S ){
	ELEMENT mxv_0_1;
	ELEMENT mxv_ax,mxv_par = S;
	AttInstSq mxv_waitsq, mxv_wsq;
	{
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_ApplyEntity_) ) goto Lp21;
			if( mxv_p0 != S ) goto Lp21;
			mxv_0_1 = mxs_numsubterms(_m,484,mxs_sces_appl(_m,484,S));
			goto L30;
		}
		Lp21: ;
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_Condition_) ) goto Lp22;
			if( mxv_p0 != S ) goto Lp22;
			mxv_0_1 = mxs_max2(_m,485,mxs_numsubterms(_m,485,mxs_sces1_cond(_m,485,S)),mxs_numsubterms(_m,485,mxs_sces2_cond(_m,485,S)));
			goto L30;
		}
		Lp22: ;
		{
			ELEMENT mxv_p0, mxv_p1;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_LetExpr_) ) goto Lp23;
			if( mxv_p0 != S ) goto Lp23;
			mxv_0_1 = mxs_max2(_m,486,mxs_numsubterms(_m,486,mxs_sces1_let(_m,486,S)),mxs_numsubterms(_m,486,mxs_sces2_let(_m,486,S)));
			goto L30;
		}
		Lp23: ;
		{
			ELEMENT mxv_p0, mxv_p1, mxv_p2;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_IfExpr_) ) goto Lp24;
			if( mxv_p0 != S ) goto Lp24;
			if( mxs_numsons(_c,0,mxv_p0)!=2 ) goto Lp24;
			mxv_p1 = mxs_son(_c,0,1,mxv_p0);
						if( mxs_numsons(_c,0,mxv_p1)!=0 ) goto Lp24;
			mxv_0_1 = mxs_numsubterms(_m,487,mxs_sces_if(_m,487,S));
			goto L30;
		}
		Lp24: ;
		{
			ELEMENT mxv_p0, CAS, mxv_p1, mxv_p2, mxv_p3;
			mxv_p0 = S;
			if( !mxs_is(_c,0,mxv_p0,_IfExpr_) ) goto Lp25;
			if( mxv_p0 != S ) goto Lp25;
			if( mxs_numsons(_c,0,mxv_p0)!=2 ) goto Lp25;
			mxv_p1 = mxs_son(_c,0,1,mxv_p0);
						if( mxs_numsons(_c,0,mxv_p1)<1 ) goto Lp25;
			mxv_p2 = mxs_son(_c,0,1,mxv_p1);
						CAS = mxv_p2;
			mxv_0_1 = mxs_max2(_m,489,mxs_aux_need_cases(_m,489,CAS),mxs_numsubterms(_m,489,mxs_sces_if(_m,489,S)));
			goto L30;
		}
		Lp25: ;
		mxv_0_1 = mxs_nil(_m,490);
		L30: ;
	}
	mxv_ax = mxs_index(_c,0,S,_Section_);
	mxa_aux_need[ mxv_ax ] = mxv_0_1;
/*  Code for Propagation  */
	mxv_waitsq = mxw_aux_need[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_res_var_no( ELEMENT C ){
	ELEMENT mxv_ax,mxv_par = C;
	AttInstSq mxv_waitsq, mxv_wsq;
	mxv_ax = mxs_index(_c,0,C,_ComposedExpr_);
	mxa_res_var_no[ mxv_ax ] = mxs_position(_m,511,C,mxs_encl_sces(_m,511,C));
/*  Code for Propagation  */
	mxv_waitsq = mxw_res_var_no[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}

static  void  mxe_patnpos( ELEMENT PN ){
	ELEMENT mxv_0_1;
	ELEMENT mxv_ax,mxv_par = PN;
	AttInstSq mxv_waitsq, mxv_wsq;
	{
		if( ( ! mxs_is(_m,538,mxs_fath(_m,538,PN),_ItemList_)) ){
			mxv_0_1 = mxs_TopPosition(_m,538);
			goto L35;
		}
		if( mxs_eq(_m,0,mxs_next_left_pat(_m,539,PN),mxs_nil(_m,539)) ){
			mxv_0_1 = mxs_AbsPosition(_m,539,mxs_patnposition(_m,539,PN,mxs_itoe(_c,0,1)));
			goto L35;
		}
		mxv_0_1 = mxs_RelPosition(_m,540,mxs_patnposition(_m,540,PN,mxs_itoe(_c,0,1)));
		L35: ;
	}
	mxv_ax = mxs_index(_c,0,PN,_Pattern_);
	mxa_patnpos[ mxv_ax ] = mxv_0_1;
/*  Code for Propagation  */
	mxv_waitsq = mxw_patnpos[ mxv_ax ];
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}

}



static  long  mxc_1( void ){
	ELEMENT mxv_c5, ID, mxv_c6, L, mxv_c7, C, mxv_c4, mxv_c0 = 1L;
	long mxv_cix4,mxv_cbd4;
	mxv_cbd4 = mxs_number(_c,0,_NodeSortId_);
	for(mxv_cix4=1;mxv_cix4<=mxv_cbd4;mxv_cix4++){
		mxv_c4 = mxs_element(_c,0,mxv_cix4,_NodeSortId_);
		if( mxs_numsons(_c,0,mxv_c4)!=3 ) continue;
		mxv_c7 = mxs_son(_c,0,-1,mxv_c4);
		mxv_c6 = mxs_lbroth(_c,0,mxv_c7);
		mxv_c5 = mxs_lbroth(_c,0,mxv_c6);
		C = mxv_c7;
		L = mxv_c6;
		ID = mxv_c5;
		if( !(  (( ! mxs_eq(_m,0,mxs_id(_m,174,ID),mxs_atoe(_c,0,"Node")))&&(( ! mxs_eq(_m,0,mxs_id(_m,174,ID),mxs_atoe(_c,0,"Point")))&&(( ! mxs_eq(_m,0,mxs_id(_m,175,ID),mxs_atoe(_c,0,"Term")))&&( ! mxs_eq(_m,0,mxs_id(_m,175,ID),mxs_atoe(_c,0,"nil")))))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,177,8,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,176,L),mxs_atoe(_c,0,", column "),mxs_s(_m,176,C),mxs_atoe(_c,0,": \""),mxs_id(_m,176,ID),mxs_atoe(_c,0,"\" not allowed with\n"),mxs_atoe(_c,0,"       node symbol @ \n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_2( void ){
	ELEMENT mxv_c9, ID, mxv_c10, L, mxv_c11, C, mxv_c8, mxv_c0 = 1L;
	ELEMENT mxv_0_1;
	long mxv_cix8,mxv_cbd8;
	mxv_cbd8 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix8=1;mxv_cix8<=mxv_cbd8;mxv_cix8++){
		mxv_c8 = mxs_element(_c,0,mxv_cix8,_UsedId_);
		if( mxs_numsons(_c,0,mxv_c8)!=3 ) continue;
		mxv_c11 = mxs_son(_c,0,-1,mxv_c8);
		mxv_c10 = mxs_lbroth(_c,0,mxv_c11);
		mxv_c9 = mxs_lbroth(_c,0,mxv_c10);
		C = mxv_c11;
		L = mxv_c10;
		ID = mxv_c9;
		if( !(  mxs_eq(_m,0,mxs_numsubterms(_m,184,mxs_idtodecls(_m,184,mxs_term(_m,184,ID))),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
			{
				if( mxs_eq(_m,0,mxs_numsubterms(_m,185,mxs_idtodecls(_m,185,mxs_term(_m,185,ID))),mxs_itoe(_c,0,0)) ){
					mxv_0_1 = mxi_string_conc(_m,187,8,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,186,L),mxs_atoe(_c,0,", column "),mxs_s(_m,186,C),mxs_atoe(_c,0,":"),mxs_atoe(_c,0,"  identifier \""),mxs_id(_m,187,ID),mxs_atoe(_c,0,"\" not declared\n"));
					goto L2;
				}
				mxv_0_1 = mxs_atoe(_c,0,"");
				L2: ;
			}
			mxv_errstr =  mxv_0_1;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_3( void ){
	ELEMENT mxv_c13, ID, mxv_c14, L, mxv_c15, C, mxv_c12, mxv_c0 = 1L;
	ELEMENT mxv_0_1;
	long mxv_cix12,mxv_cbd12;
	mxv_cbd12 = mxs_number(_c,0,_DefId_);
	for(mxv_cix12=1;mxv_cix12<=mxv_cbd12;mxv_cix12++){
		mxv_c12 = mxs_element(_c,0,mxv_cix12,_DefId_);
		if( mxs_numsons(_c,0,mxv_c12)!=3 ) continue;
		mxv_c15 = mxs_son(_c,0,-1,mxv_c12);
		mxv_c14 = mxs_lbroth(_c,0,mxv_c15);
		mxv_c13 = mxs_lbroth(_c,0,mxv_c14);
		C = mxv_c15;
		L = mxv_c14;
		ID = mxv_c13;
		if( !(  mxs_eq(_m,0,mxs_numsubterms(_m,190,mxs_idtodecls(_m,190,mxs_term(_m,190,ID))),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
			{
				if( ( ! mxs_eq(_m,0,mxs_numsubterms(_m,191,mxs_idtodecls(_m,191,mxs_term(_m,191,ID))),mxs_itoe(_c,0,1))) ){
					mxv_0_1 = mxi_string_conc(_m,193,8,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,192,L),mxs_atoe(_c,0,", column "),mxs_s(_m,192,C),mxs_atoe(_c,0,":"),mxs_atoe(_c,0,"  identifier \""),mxs_id(_m,193,ID),mxs_atoe(_c,0,"\" multiple declared\n"));
					goto L3;
				}
				mxv_0_1 = mxs_atoe(_c,0,"");
				L3: ;
			}
			mxv_errstr =  mxv_0_1;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_4( void ){
	ELEMENT mxv_c17, ID, mxv_c18, L, mxv_c19, C, mxv_c16, UID, mxv_c0 = 1L;
	long mxv_cix16,mxv_cbd16;
	mxv_cbd16 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix16=1;mxv_cix16<=mxv_cbd16;mxv_cix16++){
		mxv_c16 = mxs_element(_c,0,mxv_cix16,_UsedId_);
		UID = mxv_c16;
		if( mxs_numsons(_c,0,mxv_c16)!=3 ) continue;
		mxv_c19 = mxs_son(_c,0,-1,mxv_c16);
		mxv_c18 = mxs_lbroth(_c,0,mxv_c19);
		mxv_c17 = mxs_lbroth(_c,0,mxv_c18);
		C = mxv_c19;
		L = mxv_c18;
		ID = mxv_c17;
		if( !(  ( ! mxs_is(_m,200,mxs_fath(_m,200,mxs_decl(_m,200,UID)),_Declaration_)||mxs_in(_m,201,UID,mxs_after(_m,201,mxs_fath(_m,201,mxs_decl(_m,201,UID))),mxs_after(_m,201,mxs_fath(_m,201,mxs_fath(_m,201,mxs_decl(_m,201,UID)))))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,204,12,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,202,L),mxs_atoe(_c,0,", column "),mxs_s(_m,202,C),mxs_atoe(_c,0,": \""),mxs_id(_m,202,ID),mxs_atoe(_c,0,"\" used outside scope\n"),mxs_atoe(_c,0,"       declaration is line "),mxs_s(_m,203,mxs_son(_m,203,mxs_itoe(_c,0,2),mxs_decl(_m,203,UID))),mxs_atoe(_c,0,", column "),mxs_s(_m,204,mxs_son(_m,204,mxs_itoe(_c,0,3),mxs_decl(_m,204,UID))),mxs_atoe(_c,0,"\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_5( void ){
	ELEMENT mxv_c21, ID, mxv_c22, L, mxv_c23, C, mxv_c20, UID, mxv_c0 = 1L;
	long mxv_cix20,mxv_cbd20;
	mxv_cbd20 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix20=1;mxv_cix20<=mxv_cbd20;mxv_cix20++){
		mxv_c20 = mxs_element(_c,0,mxv_cix20,_UsedId_);
		UID = mxv_c20;
		if( mxs_numsons(_c,0,mxv_c20)!=3 ) continue;
		mxv_c23 = mxs_son(_c,0,-1,mxv_c20);
		mxv_c22 = mxs_lbroth(_c,0,mxv_c23);
		mxv_c21 = mxs_lbroth(_c,0,mxv_c22);
		C = mxv_c23;
		L = mxv_c22;
		ID = mxv_c21;
		if( !(  ( ! mxs_is(_m,207,mxs_fath(_m,207,mxs_decl(_m,207,UID)),_Definition_)||mxs_in(_m,208,UID,mxs_before(_m,208,mxs_fath(_m,208,mxs_fath(_m,208,mxs_decl(_m,208,UID)))),mxs_after(_m,208,mxs_fath(_m,208,mxs_fath(_m,208,mxs_fath(_m,208,mxs_decl(_m,208,UID))))))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,211,12,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,209,L),mxs_atoe(_c,0,", column "),mxs_s(_m,209,C),mxs_atoe(_c,0,": \""),mxs_id(_m,209,ID),mxs_atoe(_c,0,"\" used outside scope\n"),mxs_atoe(_c,0,"       declaration is line "),mxs_s(_m,210,mxs_son(_m,210,mxs_itoe(_c,0,2),mxs_decl(_m,210,UID))),mxs_atoe(_c,0,", column "),mxs_s(_m,211,mxs_son(_m,211,mxs_itoe(_c,0,3),mxs_decl(_m,211,UID))),mxs_atoe(_c,0,"\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_6( void ){
	ELEMENT mxv_c27, PID1, mxv_c28, L1, mxv_c29, C1, mxv_c26, mxv_c31, PID2, mxv_c32, L2, mxv_c33, C2, mxv_c30, mxv_c25, mxv_c24, mxv_c0 = 1L;
	long mxv_cix24,mxv_cbd24;
	mxv_cbd24 = mxs_number(_c,0,_ApplyEntity_);
	for(mxv_cix24=1;mxv_cix24<=mxv_cbd24;mxv_cix24++){
		mxv_c24 = mxs_element(_c,0,mxv_cix24,_ApplyEntity_);
		if( mxs_numsons(_c,0,mxv_c24) < 3 ) continue;
		mxv_c25 = mxs_son(_c,0,3,mxv_c24);
		if( mxs_numsons(_c,0,mxv_c25) < 2 ) continue;
		mxv_c26 = mxs_son(_c,0,1,mxv_c25);
		mxv_c30 = mxs_rbroth(_c,0,mxv_c26);
		do {
			do {
				if( mxs_numsons(_c,0,mxv_c30)!=3 ) goto CL9;
				mxv_c33 = mxs_son(_c,0,-1,mxv_c30);
				mxv_c32 = mxs_lbroth(_c,0,mxv_c33);
				mxv_c31 = mxs_lbroth(_c,0,mxv_c32);
				C2 = mxv_c33;
				L2 = mxv_c32;
				PID2 = mxv_c31;
				if( mxs_numsons(_c,0,mxv_c26)!=3 ) goto CL9;
				mxv_c29 = mxs_son(_c,0,-1,mxv_c26);
				mxv_c28 = mxs_lbroth(_c,0,mxv_c29);
				mxv_c27 = mxs_lbroth(_c,0,mxv_c28);
				C1 = mxv_c29;
				L1 = mxv_c28;
				PID1 = mxv_c27;
				if( !(  ( ! mxs_eq(_m,0,mxs_term(_m,215,PID1),mxs_term(_m,215,PID2))) )  ){
					mxv_c0 = 0L;
					mxv_errstr =  mxi_string_conc(_m,217,10,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,216,L1),mxs_atoe(_c,0,"/"),mxs_s(_m,216,L2),mxs_atoe(_c,0,", column "),mxs_s(_m,216,C1),mxs_atoe(_c,0,"/"),mxs_s(_m,216,C2),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"parameters have same identifier\n"));
					fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
				}
				CL9: ;
				mxv_c30 = mxs_rbroth(_c,0,mxv_c30);
			} while( mxv_c30 != mxs_nil(_c,0) );
			mxv_c26 = mxs_rbroth(_c,0,mxv_c26);
			mxv_c30 = mxs_rbroth(_c,0,mxv_c26);
		} while( mxv_c30 != mxs_nil(_c,0) );
	}

	return mxv_c0;
}

static  long  mxc_7( void ){
	ELEMENT mxv_c36, L, mxv_c37, C, mxv_c35, mxv_c38, PARAML, mxv_c34, mxv_c0 = 1L;
	long mxv_cix34,mxv_cbd34;
	mxv_cbd34 = mxs_number(_c,0,_AttrDecl_);
	for(mxv_cix34=1;mxv_cix34<=mxv_cbd34;mxv_cix34++){
		mxv_c34 = mxs_element(_c,0,mxv_cix34,_AttrDecl_);
		if( mxs_numsons(_c,0,mxv_c34) < 2 ) continue;
		mxv_c35 = mxs_son(_c,0,1,mxv_c34);
		mxv_c38 = mxs_rbroth(_c,0,mxv_c35);
		PARAML = mxv_c38;
		if( mxs_numsons(_c,0,mxv_c35)!=3 ) continue;
		mxv_c37 = mxs_son(_c,0,-1,mxv_c35);
		mxv_c36 = mxs_lbroth(_c,0,mxv_c37);
		C = mxv_c37;
		L = mxv_c36;
		if( !(  mxs_eq(_m,0,mxs_numsons(_m,220,PARAML),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,221,5,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,221,L),mxs_atoe(_c,0,", column "),mxs_s(_m,221,C),mxs_atoe(_c,0,":  attribute must have arity 1\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_8( void ){
	ELEMENT mxv_c41, L, mxv_c42, C, mxv_c40, mxv_c43, PARAML, mxv_c39, mxv_c0 = 1L;
	long mxv_cix39,mxv_cbd39;
	mxv_cbd39 = mxs_number(_c,0,_Attribute_);
	for(mxv_cix39=1;mxv_cix39<=mxv_cbd39;mxv_cix39++){
		mxv_c39 = mxs_element(_c,0,mxv_cix39,_Attribute_);
		if( mxs_numsons(_c,0,mxv_c39) < 2 ) continue;
		mxv_c40 = mxs_son(_c,0,1,mxv_c39);
		mxv_c43 = mxs_rbroth(_c,0,mxv_c40);
		PARAML = mxv_c43;
		if( mxs_numsons(_c,0,mxv_c40)!=3 ) continue;
		mxv_c42 = mxs_son(_c,0,-1,mxv_c40);
		mxv_c41 = mxs_lbroth(_c,0,mxv_c42);
		C = mxv_c42;
		L = mxv_c41;
		if( !(  mxs_eq(_m,0,mxs_numsons(_m,224,PARAML),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,225,5,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,225,L),mxs_atoe(_c,0,", column "),mxs_s(_m,225,C),mxs_atoe(_c,0,":  attribute must have arity 1\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_9( void ){
	ELEMENT mxv_c47, ID, mxv_c48, L, mxv_c49, C, mxv_c46, mxv_c45, mxv_c44, mxv_c0 = 1L;
	long mxv_cix44,mxv_cbd44;
	mxv_cbd44 = mxs_number(_c,0,_Attribute_);
	for(mxv_cix44=1;mxv_cix44<=mxv_cbd44;mxv_cix44++){
		mxv_c44 = mxs_element(_c,0,mxv_cix44,_Attribute_);
		if( mxs_numsons(_c,0,mxv_c44) < 2 ) continue;
		mxv_c45 = mxs_son(_c,0,2,mxv_c44);
		if( mxs_numsons(_c,0,mxv_c45)!=1 ) continue;
		mxv_c46 = mxs_son(_c,0,-1,mxv_c45);
		if( !mxs_is(_c,0,mxv_c46,_TermSortId_) ) continue;
		if( mxs_numsons(_c,0,mxv_c46)!=3 ) continue;
		mxv_c49 = mxs_son(_c,0,-1,mxv_c46);
		mxv_c48 = mxs_lbroth(_c,0,mxv_c49);
		mxv_c47 = mxs_lbroth(_c,0,mxv_c48);
		C = mxv_c49;
		L = mxv_c48;
		ID = mxv_c47;
		if( !(  (mxs_eq(_m,0,mxs_id(_m,229,ID),mxs_atoe(_c,0,"Node"))||(mxs_eq(_m,0,mxs_id(_m,229,ID),mxs_atoe(_c,0,"Point"))||mxs_eq(_m,0,mxs_id(_m,229,ID),mxs_atoe(_c,0,"Ident")))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,230,5,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,230,L),mxs_atoe(_c,0,", column "),mxs_s(_m,230,C),mxs_atoe(_c,0,":  attribute sort not enumerable\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_10( void ){
	ELEMENT mxv_c78, ID, mxv_c79, L, mxv_c80, C, mxv_c77, N, mxv_c76, mxv_c0 = 1L;
	ELEMENT mxv_0_1;
	long mxv_cix76,mxv_cbd76;
	mxv_cbd76 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix76=1;mxv_cix76<=mxv_cbd76;mxv_cix76++){
		mxv_c76 = mxs_element(_c,0,mxv_cix76,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c76)!=3 ) continue;
		mxv_c77 = mxs_son(_c,0,-1,mxv_c76);
		if( !mxs_is(_c,0,mxv_c77,_Name_) ) continue;
		N = mxv_c77;
		if( mxs_numsons(_c,0,mxv_c77)!=3 ) continue;
		mxv_c80 = mxs_son(_c,0,-1,mxv_c77);
		mxv_c79 = mxs_lbroth(_c,0,mxv_c80);
		mxv_c78 = mxs_lbroth(_c,0,mxv_c79);
		C = mxv_c80;
		L = mxv_c79;
		ID = mxv_c78;
		if( !(  ( ! (mxs_is(_m,288,mxs_scope(_m,288,N),_Condition_)&&mxs_desc(_m,288,N,mxs_son(_m,288,mxs_itoe(_c,0,1),mxs_scope(_m,288,N))))||mxs_eq(_m,0,mxs_lookup_cond(_m,289,mxs_term(_m,289,ID),mxs_son(_m,289,mxs_itoe(_c,0,1),mxs_son(_m,289,mxs_itoe(_c,0,1),mxs_scope(_m,289,N)))),N)) )  ){
			mxv_c0 = 0L;
			{
				ELEMENT M;
				M = mxs_lookup_cond(_m,290,mxs_term(_m,290,ID),mxs_son(_m,290,mxs_itoe(_c,0,1),mxs_son(_m,290,mxs_itoe(_c,0,1),mxs_scope(_m,290,N))));
				mxv_0_1 = mxi_string_conc(_m,292,12,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,291,L),mxs_atoe(_c,0,"/"),mxs_s(_m,291,mxs_son(_m,291,mxs_itoe(_c,0,2),M)),mxs_atoe(_c,0,", column "),mxs_s(_m,291,C),mxs_atoe(_c,0,"/"),mxs_s(_m,291,mxs_son(_m,291,mxs_itoe(_c,0,3),M)),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"multiple binding of identifier \""),mxs_id(_m,292,ID),mxs_atoe(_c,0,"\"\n"));
			}
			mxv_errstr =  mxv_0_1;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_11( void ){
	ELEMENT mxv_c83, ID, mxv_c84, L, mxv_c85, C, mxv_c82, N, mxv_c81, mxv_c0 = 1L;
	ELEMENT mxv_0_1;
	long mxv_cix81,mxv_cbd81;
	mxv_cbd81 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix81=1;mxv_cix81<=mxv_cbd81;mxv_cix81++){
		mxv_c81 = mxs_element(_c,0,mxv_cix81,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c81)!=3 ) continue;
		mxv_c82 = mxs_son(_c,0,-1,mxv_c81);
		if( !mxs_is(_c,0,mxv_c82,_Name_) ) continue;
		N = mxv_c82;
		if( mxs_numsons(_c,0,mxv_c82)!=3 ) continue;
		mxv_c85 = mxs_son(_c,0,-1,mxv_c82);
		mxv_c84 = mxs_lbroth(_c,0,mxv_c85);
		mxv_c83 = mxs_lbroth(_c,0,mxv_c84);
		C = mxv_c85;
		L = mxv_c84;
		ID = mxv_c83;
		if( !(  ( ! mxs_is(_m,296,mxs_scope(_m,296,N),_PatternCase_)||mxs_eq(_m,0,mxs_lookup_item(_m,297,mxs_term(_m,297,ID),mxs_son(_m,297,mxs_itoe(_c,0,1),mxs_scope(_m,297,N))),N)) )  ){
			mxv_c0 = 0L;
			{
				ELEMENT M;
				M = mxs_lookup_item(_m,298,mxs_term(_m,298,ID),mxs_son(_m,298,mxs_itoe(_c,0,1),mxs_scope(_m,298,N)));
				mxv_0_1 = mxi_string_conc(_m,300,12,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,299,L),mxs_atoe(_c,0,"/"),mxs_s(_m,299,mxs_son(_m,299,mxs_itoe(_c,0,2),M)),mxs_atoe(_c,0,", column "),mxs_s(_m,299,C),mxs_atoe(_c,0,"/"),mxs_s(_m,299,mxs_son(_m,299,mxs_itoe(_c,0,3),M)),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"multiple binding of identifier \""),mxs_id(_m,300,ID),mxs_atoe(_c,0,"\"\n"));
			}
			mxv_errstr =  mxv_0_1;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_12( void ){
	ELEMENT mxv_c87, ID, mxv_c88, L, mxv_c89, C, mxv_c86, N, mxv_c0 = 1L;
	long mxv_cix86,mxv_cbd86;
	mxv_cbd86 = mxs_number(_c,0,_Name_);
	for(mxv_cix86=1;mxv_cix86<=mxv_cbd86;mxv_cix86++){
		mxv_c86 = mxs_element(_c,0,mxv_cix86,_Name_);
		N = mxv_c86;
		if( mxs_numsons(_c,0,mxv_c86)!=3 ) continue;
		mxv_c89 = mxs_son(_c,0,-1,mxv_c86);
		mxv_c88 = mxs_lbroth(_c,0,mxv_c89);
		mxv_c87 = mxs_lbroth(_c,0,mxv_c88);
		C = mxv_c89;
		L = mxv_c88;
		ID = mxv_c87;
		if( !(  ( ! mxs_eq(_m,0,mxs_bind_pos(_m,314,N),mxs_nil(_m,314))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,315,7,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,315,L),mxs_atoe(_c,0,", column "),mxs_s(_m,315,C),mxs_atoe(_c,0,": \""),mxs_id(_m,315,ID),mxs_atoe(_c,0,"\" not declared\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_13( void ){
	ELEMENT mxv_c98, L, mxv_c97, B, mxv_c96, mxv_c95, mxv_c0 = 1L;
	long mxv_cix95,mxv_cbd95;
	mxv_cbd95 = mxs_number(_c,0,_PatternList_);
	for(mxv_cix95=1;mxv_cix95<=mxv_cbd95;mxv_cix95++){
		mxv_c95 = mxs_element(_c,0,mxv_cix95,_PatternList_);
		if( mxs_numsons(_c,0,mxv_c95) < 1 ) continue;
		mxv_c96 = mxs_son(_c,0,1,mxv_c95);
		do {
			if( mxs_numsons(_c,0,mxv_c96)!=3 ) goto CL39;
			mxv_c97 = mxs_son(_c,0,-3,mxv_c96);
			if( !mxs_is(_c,0,mxv_c97,_Blank_) ) goto CL39;
			B = mxv_c97;
			if( mxs_numsons(_c,0,mxv_c97)!=1 ) goto CL39;
			mxv_c98 = mxs_son(_c,0,-1,mxv_c97);
			L = mxv_c98;
			if( !(  mxs_eq(_m,0,mxs_true(_m,352),mxs_false(_m,352)) )  ){
				mxv_c0 = 0L;
				mxv_errstr =  mxi_string_conc(_m,353,3,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,353,L),mxs_atoe(_c,0,": outermost pattern may not be omitted\n"));
				fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
			}
			CL39: ;
			mxv_c96 = mxs_rbroth(_c,0,mxv_c96);
		} while( mxv_c96 != mxs_nil(_c,0) );
	}

	return mxv_c0;
}

static  long  mxc_14( void ){
	ELEMENT mxv_c101, ID, mxv_c102, L, mxv_c103, C, mxv_c100, mxv_c99, mxv_c0 = 1L;
	long mxv_cix99,mxv_cbd99;
	mxv_cbd99 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix99=1;mxv_cix99<=mxv_cbd99;mxv_cix99++){
		mxv_c99 = mxs_element(_c,0,mxv_cix99,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c99)!=3 ) continue;
		mxv_c100 = mxs_son(_c,0,-3,mxv_c99);
		if( !mxs_is(_c,0,mxv_c100,_TermSortId_) ) continue;
		if( mxs_numsons(_c,0,mxv_c100)!=3 ) continue;
		mxv_c103 = mxs_son(_c,0,-1,mxv_c100);
		mxv_c102 = mxs_lbroth(_c,0,mxv_c103);
		mxv_c101 = mxs_lbroth(_c,0,mxv_c102);
		C = mxv_c103;
		L = mxv_c102;
		ID = mxv_c101;
		if( !(  (mxs_eq(_m,0,mxs_id(_m,357,ID),mxs_atoe(_c,0,"Node"))||(mxs_eq(_m,0,mxs_id(_m,357,ID),mxs_atoe(_c,0,"Point"))||mxs_eq(_m,0,mxs_id(_m,357,ID),mxs_atoe(_c,0,"Ident")))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,358,5,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,358,L),mxs_atoe(_c,0,", column "),mxs_s(_m,358,C),mxs_atoe(_c,0,":  pattern sort must be enumerable\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_15( void ){
	ELEMENT mxv_c106, ID, mxv_c107, L, mxv_c108, C, mxv_c105, mxv_c109, mxv_c104, mxv_c0 = 1L;
	long mxv_cix104,mxv_cbd104;
	mxv_cbd104 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix104=1;mxv_cix104<=mxv_cbd104;mxv_cix104++){
		mxv_c104 = mxs_element(_c,0,mxv_cix104,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c104)!=3 ) continue;
		mxv_c109 = mxs_son(_c,0,-2,mxv_c104);
		mxv_c105 = mxs_lbroth(_c,0,mxv_c109);
		if( !mxs_is(_c,0,mxv_c109,_ItemList_) ) continue;
		if( !mxs_is(_c,0,mxv_c105,_TermSortId_) ) continue;
		if( mxs_numsons(_c,0,mxv_c105)!=3 ) continue;
		mxv_c108 = mxs_son(_c,0,-1,mxv_c105);
		mxv_c107 = mxs_lbroth(_c,0,mxv_c108);
		mxv_c106 = mxs_lbroth(_c,0,mxv_c107);
		C = mxv_c108;
		L = mxv_c107;
		ID = mxv_c106;
		if( !(  mxs_eq(_m,0,mxs_id(_m,361,ID),mxs_atoe(_c,0,"Node")) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,363,6,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,362,L),mxs_atoe(_c,0,", column "),mxs_s(_m,362,C),mxs_atoe(_c,0,":  no subpattern for ident and point "),mxs_atoe(_c,0,"allowed\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_16( void ){
	ELEMENT mxv_c112, ID, mxv_c113, L, mxv_c114, C, mxv_c111, UID, mxv_c115, ITL, mxv_c110, mxv_c0 = 1L;
	long mxv_cix110,mxv_cbd110;
	mxv_cbd110 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix110=1;mxv_cix110<=mxv_cbd110;mxv_cix110++){
		mxv_c110 = mxs_element(_c,0,mxv_cix110,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c110)!=3 ) continue;
		mxv_c115 = mxs_son(_c,0,-2,mxv_c110);
		mxv_c111 = mxs_lbroth(_c,0,mxv_c115);
		if( !mxs_is(_c,0,mxv_c115,_ItemList_) ) continue;
		ITL = mxv_c115;
		if( !mxs_is(_c,0,mxv_c111,_NodeSortId_) ) continue;
		UID = mxv_c111;
		if( mxs_numsons(_c,0,mxv_c111)!=3 ) continue;
		mxv_c114 = mxs_son(_c,0,-1,mxv_c111);
		mxv_c113 = mxs_lbroth(_c,0,mxv_c114);
		mxv_c112 = mxs_lbroth(_c,0,mxv_c113);
		C = mxv_c114;
		L = mxv_c113;
		ID = mxv_c112;
		if( !(  ( ! mxs_is(_m,367,mxs_fath(_m,367,mxs_decl(_m,367,UID)),_TupelProd_)||(( ! mxs_eq(_m,0,mxs_numberofastrks(_m,369,ITL),mxs_itoe(_c,0,0))||mxs_eq(_m,0,mxs_numsons(_m,370,mxs_son(_m,370,mxs_itoe(_c,0,2),mxs_fath(_m,370,mxs_decl(_m,370,UID)))),mxs_numsons(_m,370,ITL)))&&( ! mxs_lt(_m,371,mxs_itoe(_c,0,0),mxs_numberofastrks(_m,371,ITL))||mxs_le(_m,372,mxs_sub(_m,372,mxs_numsons(_m,372,ITL),mxs_numberofastrks(_m,372,ITL)),mxs_numsons(_m,373,mxs_son(_m,373,mxs_itoe(_c,0,2),mxs_fath(_m,373,mxs_decl(_m,373,UID)))))))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,376,6,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,375,L),mxs_atoe(_c,0,", column "),mxs_s(_m,375,C),mxs_atoe(_c,0,":  pattern for tupel node sort never "),mxs_atoe(_c,0,"matches\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_17( void ){
	ELEMENT mxv_c116, PC, mxv_c0 = 1L;
	long mxv_cix116,mxv_cbd116;
	mxv_cbd116 = mxs_number(_c,0,_PatternCase_);
	for(mxv_cix116=1;mxv_cix116<=mxv_cbd116;mxv_cix116++){
		mxv_c116 = mxs_element(_c,0,mxv_cix116,_PatternCase_);
		PC = mxv_c116;
		if( !(  ( ! mxs_eq(_m,0,mxs_pat_anchor(_m,379,PC),mxs_nil(_m,379))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,381,4,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,380,mxs_patlineno(_m,380,mxs_son(_m,380,mxs_itoe(_c,0,1),PC))),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"pattern does not contain a bound identifier\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_18( void ){
	ELEMENT mxv_c118, mxv_c119, mxv_c117, ITL, mxv_c0 = 1L;
	long mxv_cix117,mxv_cbd117;
	mxv_cbd117 = mxs_number(_c,0,_ItemList_);
	for(mxv_cix117=1;mxv_cix117<=mxv_cbd117;mxv_cix117++){
		mxv_c117 = mxs_element(_c,0,mxv_cix117,_ItemList_);
		ITL = mxv_c117;
		if( mxs_numsons(_c,0,mxv_c117) < 2 ) continue;
		mxv_c118 = mxs_son(_c,0,1,mxv_c117);
		mxv_c119 = mxs_rbroth(_c,0,mxv_c118);
		do {
			do {
				if( !mxs_is(_c,0,mxv_c119,_Asterisk_) ) goto CL48;
				if( !mxs_is(_c,0,mxv_c118,_Asterisk_) ) goto CL48;
				if( !(  ( ! mxs_is(_m,384,mxs_scope(_m,384,ITL),_PatternCase_)) )  ){
					mxv_c0 = 0L;
					mxv_errstr =  mxi_string_conc(_m,386,4,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,385,mxs_patlineno(_m,385,mxs_fath(_m,385,ITL))),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"conditional pattern contains two asterisks\n"));
					fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
				}
				CL48: ;
				mxv_c119 = mxs_rbroth(_c,0,mxv_c119);
			} while( mxv_c119 != mxs_nil(_c,0) );
			mxv_c118 = mxs_rbroth(_c,0,mxv_c118);
			mxv_c119 = mxs_rbroth(_c,0,mxv_c118);
		} while( mxv_c119 != mxs_nil(_c,0) );
	}

	return mxv_c0;
}

static  long  mxc_19( void ){
	ELEMENT mxv_c121, A1, mxv_c122, A2, mxv_c120, ITL, mxv_c0 = 1L;
	long mxv_cix120,mxv_cbd120;
	mxv_cbd120 = mxs_number(_c,0,_ItemList_);
	for(mxv_cix120=1;mxv_cix120<=mxv_cbd120;mxv_cix120++){
		mxv_c120 = mxs_element(_c,0,mxv_cix120,_ItemList_);
		ITL = mxv_c120;
		if( mxs_numsons(_c,0,mxv_c120) < 2 ) continue;
		mxv_c121 = mxs_son(_c,0,1,mxv_c120);
		mxv_c122 = mxs_rbroth(_c,0,mxv_c121);
		do {
			do {
				if( !mxs_is(_c,0,mxv_c122,_Asterisk_) ) goto CL49;
				A2 = mxv_c122;
				if( !mxs_is(_c,0,mxv_c121,_Asterisk_) ) goto CL49;
				A1 = mxv_c121;
				if( !(  mxs_ex_pattern_inbetween(_m,390,mxs_rbroth(_m,390,A1),A2) )  ){
					mxv_c0 = 0L;
					mxv_errstr =  mxi_string_conc(_m,392,4,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,391,mxs_patlineno(_m,391,mxs_fath(_m,391,ITL))),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"two asterisks must enclose a pattern\n"));
					fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
				}
				CL49: ;
				mxv_c122 = mxs_rbroth(_c,0,mxv_c122);
			} while( mxv_c122 != mxs_nil(_c,0) );
			mxv_c121 = mxs_rbroth(_c,0,mxv_c121);
			mxv_c122 = mxs_rbroth(_c,0,mxv_c121);
		} while( mxv_c122 != mxs_nil(_c,0) );
	}

	return mxv_c0;
}

static  long  mxc_20( void ){
	ELEMENT mxv_c132, ID, mxv_c133, L, mxv_c134, C, mxv_c131, mxv_c130, CP, mxv_c0 = 1L;
	long mxv_cix130,mxv_cbd130;
	mxv_cbd130 = mxs_number(_c,0,_ClassProd_);
	for(mxv_cix130=1;mxv_cix130<=mxv_cbd130;mxv_cix130++){
		mxv_c130 = mxs_element(_c,0,mxv_cix130,_ClassProd_);
		CP = mxv_c130;
		if( mxs_numsons(_c,0,mxv_c130)!=2 ) continue;
		mxv_c131 = mxs_son(_c,0,-2,mxv_c130);
		if( mxs_numsons(_c,0,mxv_c131)!=3 ) continue;
		mxv_c134 = mxs_son(_c,0,-1,mxv_c131);
		mxv_c133 = mxs_lbroth(_c,0,mxv_c134);
		mxv_c132 = mxs_lbroth(_c,0,mxv_c133);
		C = mxv_c134;
		L = mxv_c133;
		ID = mxv_c132;
		if( !(  ( ! mxs_eq(_m,0,mxs_subsorts(_m,442,CP),mxs_nil(_m,442))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,443,7,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,443,L),mxs_atoe(_c,0,", column "),mxs_s(_m,443,C),mxs_atoe(_c,0,": class \""),mxs_id(_m,443,ID),mxs_atoe(_c,0,"\" is circular\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}


long  mxi_atteval( void ){
	long mxv_correct = 1;
	long ix;
	long mxn_encl_scope = mxs_number(_c,0,_Scope_);
	long mxn_bind_pos = mxs_number(_c,0,_Name_);
	long mxn_pat_anchor = mxs_number(_c,0,_PatternCase_);
	long mxn_numberofastrks = mxs_number(_c,0,_ItemList_);
	long mxn_predeclprodcd = mxs_number(_c,0,_PredeclProd_);
	long mxn_tupelprodcd = mxs_number(_c,0,_TupelProd_);
	long mxn_listprodcd = mxs_number(_c,0,_ListProd_);
	long mxn_classprodcd = mxs_number(_c,0,_ClassProd_);
	long mxn_sces_appl = mxs_number(_c,0,_ApplyEntity_);
	long mxn_sces1_cond = mxs_number(_c,0,_Condition_);
	long mxn_sces2_cond = mxs_number(_c,0,_Condition_);
	long mxn_sces1_let = mxs_number(_c,0,_LetExpr_);
	long mxn_sces2_let = mxs_number(_c,0,_LetExpr_);
	long mxn_sces_if = mxs_number(_c,0,_IfExpr_);
	long mxn_sces1_fcase = mxs_number(_c,0,_FormulaCase_);
	long mxn_sces2_fcase = mxs_number(_c,0,_FormulaCase_);
	long mxn_sces_pcase = mxs_number(_c,0,_PatternCase_);
	long mxn_aux_need = mxs_number(_c,0,_Section_);
	long mxn_res_var_no = mxs_number(_c,0,_ComposedExpr_);
	long mxn_patnpos = mxs_number(_c,0,_Pattern_);


	mxv_correct = mxc_1() && mxv_correct;
	if( ! mxv_correct ) return 0L;


	mxv_correct = init_idtodecls() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = mxc_2() && mxv_correct;
	mxv_correct = mxc_3() && mxv_correct;
	if( ! mxv_correct ) return 0L;


	mxv_correct = mxc_4() && mxv_correct;
	mxv_correct = mxc_5() && mxv_correct;
	mxv_correct = mxc_6() && mxv_correct;
	mxv_correct = mxc_7() && mxv_correct;
	mxv_correct = mxc_8() && mxv_correct;
	mxv_correct = mxc_9() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	mxa_encl_scope = (ELEMENT*)   calloc( mxn_encl_scope+1, sizeof(ELEMENT) );
	mxw_encl_scope = (AttInstSq*) calloc( mxn_encl_scope+1, sizeof(AttInstSq) );
	if( mxa_encl_scope==0L || mxw_encl_scope==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute encl_scope\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_encl_scope; ix++ )  mxa_encl_scope[ix] = -335544320L;
	for( ix=1; ix<=mxn_encl_scope; ix++ )  mxe_encl_scope( mxs_element(_c,0,ix,_Scope_) );
	for( ix=1; ix<=mxn_encl_scope; ix++ ){
		if( mxa_encl_scope[ ix ] == -335544320L )  mxa_encl_scope[ix] = mxs_nil(_c,0);
	}
	free(mxw_encl_scope);

	mxv_correct = mxc_10() && mxv_correct;
	mxv_correct = mxc_11() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	mxa_bind_pos = (ELEMENT*)   calloc( mxn_bind_pos+1, sizeof(ELEMENT) );
	mxw_bind_pos = (AttInstSq*) calloc( mxn_bind_pos+1, sizeof(AttInstSq) );
	if( mxa_bind_pos==0L || mxw_bind_pos==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute bind_pos\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_bind_pos; ix++ )  mxa_bind_pos[ix] = -335544320L;
	for( ix=1; ix<=mxn_bind_pos; ix++ )  mxe_bind_pos( mxs_element(_c,0,ix,_Name_) );
	for( ix=1; ix<=mxn_bind_pos; ix++ ){
		if( mxa_bind_pos[ ix ] == -335544320L )  mxa_bind_pos[ix] = mxs_nil(_c,0);
	}
	free(mxw_bind_pos);

	mxv_correct = mxc_12() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	mxa_pat_anchor = (ELEMENT*)   calloc( mxn_pat_anchor+1, sizeof(ELEMENT) );
	mxw_pat_anchor = (AttInstSq*) calloc( mxn_pat_anchor+1, sizeof(AttInstSq) );
	if( mxa_pat_anchor==0L || mxw_pat_anchor==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute pat_anchor\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_pat_anchor; ix++ )  mxa_pat_anchor[ix] = -335544320L;
	for( ix=1; ix<=mxn_pat_anchor; ix++ )  mxe_pat_anchor( mxs_element(_c,0,ix,_PatternCase_) );
	for( ix=1; ix<=mxn_pat_anchor; ix++ ){
		if( mxa_pat_anchor[ ix ] == -335544320L )  mxa_pat_anchor[ix] = mxs_nil(_c,0);
	}
	free(mxw_pat_anchor);
	mxa_numberofastrks = (ELEMENT*)   calloc( mxn_numberofastrks+1, sizeof(ELEMENT) );
	mxw_numberofastrks = (AttInstSq*) calloc( mxn_numberofastrks+1, sizeof(AttInstSq) );
	if( mxa_numberofastrks==0L || mxw_numberofastrks==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute numberofastrks\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_numberofastrks; ix++ )  mxa_numberofastrks[ix] = -335544320L;
	for( ix=1; ix<=mxn_numberofastrks; ix++ )  mxe_numberofastrks( mxs_element(_c,0,ix,_ItemList_) );
	for( ix=1; ix<=mxn_numberofastrks; ix++ ){
		if( mxa_numberofastrks[ ix ] == -335544320L )  mxa_numberofastrks[ix] = mxs_nil(_c,0);
	}
	free(mxw_numberofastrks);

	mxv_correct = mxc_13() && mxv_correct;
	mxv_correct = mxc_14() && mxv_correct;
	mxv_correct = mxc_15() && mxv_correct;
	mxv_correct = mxc_16() && mxv_correct;
	mxv_correct = mxc_17() && mxv_correct;
	mxv_correct = mxc_18() && mxv_correct;
	mxv_correct = mxc_19() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	mxa_predeclprodcd = (ELEMENT*)   calloc( mxn_predeclprodcd+1, sizeof(ELEMENT) );
	mxw_predeclprodcd = (AttInstSq*) calloc( mxn_predeclprodcd+1, sizeof(AttInstSq) );
	if( mxa_predeclprodcd==0L || mxw_predeclprodcd==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute predeclprodcd\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_predeclprodcd; ix++ )  mxa_predeclprodcd[ix] = -335544320L;
	mxa_tupelprodcd = (ELEMENT*)   calloc( mxn_tupelprodcd+1, sizeof(ELEMENT) );
	mxw_tupelprodcd = (AttInstSq*) calloc( mxn_tupelprodcd+1, sizeof(AttInstSq) );
	if( mxa_tupelprodcd==0L || mxw_tupelprodcd==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute tupelprodcd\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_tupelprodcd; ix++ )  mxa_tupelprodcd[ix] = -335544320L;
	mxa_listprodcd = (ELEMENT*)   calloc( mxn_listprodcd+1, sizeof(ELEMENT) );
	mxw_listprodcd = (AttInstSq*) calloc( mxn_listprodcd+1, sizeof(AttInstSq) );
	if( mxa_listprodcd==0L || mxw_listprodcd==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute listprodcd\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_listprodcd; ix++ )  mxa_listprodcd[ix] = -335544320L;
	for( ix=1; ix<=mxn_predeclprodcd; ix++ )  mxe_predeclprodcd( mxs_element(_c,0,ix,_PredeclProd_) );
	for( ix=1; ix<=mxn_tupelprodcd; ix++ )  mxe_tupelprodcd( mxs_element(_c,0,ix,_TupelProd_) );
	for( ix=1; ix<=mxn_listprodcd; ix++ )  mxe_listprodcd( mxs_element(_c,0,ix,_ListProd_) );
	for( ix=1; ix<=mxn_predeclprodcd; ix++ ){
		if( mxa_predeclprodcd[ ix ] == -335544320L )  mxa_predeclprodcd[ix] = mxs_nil(_c,0);
	}
	free(mxw_predeclprodcd);
	for( ix=1; ix<=mxn_tupelprodcd; ix++ ){
		if( mxa_tupelprodcd[ ix ] == -335544320L )  mxa_tupelprodcd[ix] = mxs_nil(_c,0);
	}
	free(mxw_tupelprodcd);
	for( ix=1; ix<=mxn_listprodcd; ix++ ){
		if( mxa_listprodcd[ ix ] == -335544320L )  mxa_listprodcd[ix] = mxs_nil(_c,0);
	}
	free(mxw_listprodcd);
	mxa_classprodcd = (ELEMENT*)   calloc( mxn_classprodcd+1, sizeof(ELEMENT) );
	mxw_classprodcd = (AttInstSq*) calloc( mxn_classprodcd+1, sizeof(AttInstSq) );
	if( mxa_classprodcd==0L || mxw_classprodcd==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute classprodcd\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_classprodcd; ix++ )  mxa_classprodcd[ix] = -335544320L;
	for( ix=1; ix<=mxn_classprodcd; ix++ )  mxe_classprodcd( mxs_element(_c,0,ix,_ClassProd_) );
	for( ix=1; ix<=mxn_classprodcd; ix++ ){
		if( mxa_classprodcd[ ix ] == -335544320L )  mxa_classprodcd[ix] = mxs_nil(_c,0);
	}
	free(mxw_classprodcd);

	mxv_correct = init_subsorts() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = mxc_20() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	mxa_sces_appl = (ELEMENT*)   calloc( mxn_sces_appl+1, sizeof(ELEMENT) );
	mxw_sces_appl = (AttInstSq*) calloc( mxn_sces_appl+1, sizeof(AttInstSq) );
	if( mxa_sces_appl==0L || mxw_sces_appl==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces_appl\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces_appl; ix++ )  mxa_sces_appl[ix] = -335544320L;
	mxa_sces1_cond = (ELEMENT*)   calloc( mxn_sces1_cond+1, sizeof(ELEMENT) );
	mxw_sces1_cond = (AttInstSq*) calloc( mxn_sces1_cond+1, sizeof(AttInstSq) );
	if( mxa_sces1_cond==0L || mxw_sces1_cond==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces1_cond\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces1_cond; ix++ )  mxa_sces1_cond[ix] = -335544320L;
	mxa_sces2_cond = (ELEMENT*)   calloc( mxn_sces2_cond+1, sizeof(ELEMENT) );
	mxw_sces2_cond = (AttInstSq*) calloc( mxn_sces2_cond+1, sizeof(AttInstSq) );
	if( mxa_sces2_cond==0L || mxw_sces2_cond==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces2_cond\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces2_cond; ix++ )  mxa_sces2_cond[ix] = -335544320L;
	mxa_sces1_let = (ELEMENT*)   calloc( mxn_sces1_let+1, sizeof(ELEMENT) );
	mxw_sces1_let = (AttInstSq*) calloc( mxn_sces1_let+1, sizeof(AttInstSq) );
	if( mxa_sces1_let==0L || mxw_sces1_let==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces1_let\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces1_let; ix++ )  mxa_sces1_let[ix] = -335544320L;
	mxa_sces2_let = (ELEMENT*)   calloc( mxn_sces2_let+1, sizeof(ELEMENT) );
	mxw_sces2_let = (AttInstSq*) calloc( mxn_sces2_let+1, sizeof(AttInstSq) );
	if( mxa_sces2_let==0L || mxw_sces2_let==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces2_let\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces2_let; ix++ )  mxa_sces2_let[ix] = -335544320L;
	mxa_sces_if = (ELEMENT*)   calloc( mxn_sces_if+1, sizeof(ELEMENT) );
	mxw_sces_if = (AttInstSq*) calloc( mxn_sces_if+1, sizeof(AttInstSq) );
	if( mxa_sces_if==0L || mxw_sces_if==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces_if\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces_if; ix++ )  mxa_sces_if[ix] = -335544320L;
	mxa_sces1_fcase = (ELEMENT*)   calloc( mxn_sces1_fcase+1, sizeof(ELEMENT) );
	mxw_sces1_fcase = (AttInstSq*) calloc( mxn_sces1_fcase+1, sizeof(AttInstSq) );
	if( mxa_sces1_fcase==0L || mxw_sces1_fcase==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces1_fcase\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces1_fcase; ix++ )  mxa_sces1_fcase[ix] = -335544320L;
	mxa_sces2_fcase = (ELEMENT*)   calloc( mxn_sces2_fcase+1, sizeof(ELEMENT) );
	mxw_sces2_fcase = (AttInstSq*) calloc( mxn_sces2_fcase+1, sizeof(AttInstSq) );
	if( mxa_sces2_fcase==0L || mxw_sces2_fcase==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces2_fcase\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces2_fcase; ix++ )  mxa_sces2_fcase[ix] = -335544320L;
	mxa_sces_pcase = (ELEMENT*)   calloc( mxn_sces_pcase+1, sizeof(ELEMENT) );
	mxw_sces_pcase = (AttInstSq*) calloc( mxn_sces_pcase+1, sizeof(AttInstSq) );
	if( mxa_sces_pcase==0L || mxw_sces_pcase==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces_pcase\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces_pcase; ix++ )  mxa_sces_pcase[ix] = -335544320L;
	for( ix=1; ix<=mxn_sces_appl; ix++ )  mxe_sces_appl( mxs_element(_c,0,ix,_ApplyEntity_) );
	for( ix=1; ix<=mxn_sces1_cond; ix++ )  mxe_sces1_cond( mxs_element(_c,0,ix,_Condition_) );
	for( ix=1; ix<=mxn_sces2_cond; ix++ )  mxe_sces2_cond( mxs_element(_c,0,ix,_Condition_) );
	for( ix=1; ix<=mxn_sces1_let; ix++ )  mxe_sces1_let( mxs_element(_c,0,ix,_LetExpr_) );
	for( ix=1; ix<=mxn_sces2_let; ix++ )  mxe_sces2_let( mxs_element(_c,0,ix,_LetExpr_) );
	for( ix=1; ix<=mxn_sces_if; ix++ )  mxe_sces_if( mxs_element(_c,0,ix,_IfExpr_) );
	for( ix=1; ix<=mxn_sces1_fcase; ix++ )  mxe_sces1_fcase( mxs_element(_c,0,ix,_FormulaCase_) );
	for( ix=1; ix<=mxn_sces2_fcase; ix++ )  mxe_sces2_fcase( mxs_element(_c,0,ix,_FormulaCase_) );
	for( ix=1; ix<=mxn_sces_pcase; ix++ )  mxe_sces_pcase( mxs_element(_c,0,ix,_PatternCase_) );
	for( ix=1; ix<=mxn_sces_appl; ix++ ){
		if( mxa_sces_appl[ ix ] == -335544320L )  mxa_sces_appl[ix] = mxs_nil(_c,0);
	}
	free(mxw_sces_appl);
	for( ix=1; ix<=mxn_sces1_cond; ix++ ){
		if( mxa_sces1_cond[ ix ] == -335544320L )  mxa_sces1_cond[ix] = mxs_nil(_c,0);
	}
	free(mxw_sces1_cond);
	for( ix=1; ix<=mxn_sces2_cond; ix++ ){
		if( mxa_sces2_cond[ ix ] == -335544320L )  mxa_sces2_cond[ix] = mxs_nil(_c,0);
	}
	free(mxw_sces2_cond);
	for( ix=1; ix<=mxn_sces1_let; ix++ ){
		if( mxa_sces1_let[ ix ] == -335544320L )  mxa_sces1_let[ix] = mxs_nil(_c,0);
	}
	free(mxw_sces1_let);
	for( ix=1; ix<=mxn_sces2_let; ix++ ){
		if( mxa_sces2_let[ ix ] == -335544320L )  mxa_sces2_let[ix] = mxs_nil(_c,0);
	}
	free(mxw_sces2_let);
	for( ix=1; ix<=mxn_sces_if; ix++ ){
		if( mxa_sces_if[ ix ] == -335544320L )  mxa_sces_if[ix] = mxs_nil(_c,0);
	}
	free(mxw_sces_if);
	for( ix=1; ix<=mxn_sces1_fcase; ix++ ){
		if( mxa_sces1_fcase[ ix ] == -335544320L )  mxa_sces1_fcase[ix] = mxs_nil(_c,0);
	}
	free(mxw_sces1_fcase);
	for( ix=1; ix<=mxn_sces2_fcase; ix++ ){
		if( mxa_sces2_fcase[ ix ] == -335544320L )  mxa_sces2_fcase[ix] = mxs_nil(_c,0);
	}
	free(mxw_sces2_fcase);
	for( ix=1; ix<=mxn_sces_pcase; ix++ ){
		if( mxa_sces_pcase[ ix ] == -335544320L )  mxa_sces_pcase[ix] = mxs_nil(_c,0);
	}
	free(mxw_sces_pcase);
	mxa_aux_need = (ELEMENT*)   calloc( mxn_aux_need+1, sizeof(ELEMENT) );
	mxw_aux_need = (AttInstSq*) calloc( mxn_aux_need+1, sizeof(AttInstSq) );
	if( mxa_aux_need==0L || mxw_aux_need==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute aux_need\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_aux_need; ix++ )  mxa_aux_need[ix] = -335544320L;
	for( ix=1; ix<=mxn_aux_need; ix++ )  mxe_aux_need( mxs_element(_c,0,ix,_Section_) );
	for( ix=1; ix<=mxn_aux_need; ix++ ){
		if( mxa_aux_need[ ix ] == -335544320L )  mxa_aux_need[ix] = mxs_nil(_c,0);
	}
	free(mxw_aux_need);
	mxa_res_var_no = (ELEMENT*)   calloc( mxn_res_var_no+1, sizeof(ELEMENT) );
	mxw_res_var_no = (AttInstSq*) calloc( mxn_res_var_no+1, sizeof(AttInstSq) );
	if( mxa_res_var_no==0L || mxw_res_var_no==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute res_var_no\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_res_var_no; ix++ )  mxa_res_var_no[ix] = -335544320L;
	for( ix=1; ix<=mxn_res_var_no; ix++ )  mxe_res_var_no( mxs_element(_c,0,ix,_ComposedExpr_) );
	for( ix=1; ix<=mxn_res_var_no; ix++ ){
		if( mxa_res_var_no[ ix ] == -335544320L )  mxa_res_var_no[ix] = mxs_nil(_c,0);
	}
	free(mxw_res_var_no);
	mxa_patnpos = (ELEMENT*)   calloc( mxn_patnpos+1, sizeof(ELEMENT) );
	mxw_patnpos = (AttInstSq*) calloc( mxn_patnpos+1, sizeof(AttInstSq) );
	if( mxa_patnpos==0L || mxw_patnpos==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute patnpos\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_patnpos; ix++ )  mxa_patnpos[ix] = -335544320L;
	for( ix=1; ix<=mxn_patnpos; ix++ )  mxe_patnpos( mxs_element(_c,0,ix,_Pattern_) );
	for( ix=1; ix<=mxn_patnpos; ix++ ){
		if( mxa_patnpos[ ix ] == -335544320L )  mxa_patnpos[ix] = mxs_nil(_c,0);
	}
	free(mxw_patnpos);
	return mxv_correct;
}



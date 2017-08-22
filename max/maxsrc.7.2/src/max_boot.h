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
#define  _Specification 		 -469696601L	/* -89 */
#define  _Specification_		 -469761959L	/* 89 */
#define  _ProdList 		 -469696602L	/* -90 */
#define  _ProdList_		 -469761958L	/* 90 */
#define  _SortIdList 		 -469696603L	/* -91 */
#define  _SortIdList_		 -469761957L	/* 91 */
#define  _LocalDeclList 		 -469696604L	/* -92 */
#define  _LocalDeclList_		 -469761956L	/* 92 */
#define  _PredList 		 -469696605L	/* -93 */
#define  _PredList_		 -469761955L	/* 93 */
#define  _FuAtList 		 -469696606L	/* -94 */
#define  _FuAtList_		 -469761954L	/* 94 */
#define  _CondList 		 -469696607L	/* -95 */
#define  _CondList_		 -469761953L	/* 95 */
#define  _PatternList 		 -469696608L	/* -96 */
#define  _PatternList_		 -469761952L	/* 96 */
#define  _ExprList 		 -469696609L	/* -97 */
#define  _ExprList_		 -469761951L	/* 97 */
#define  _PatternCaseList 		 -469696610L	/* -98 */
#define  _PatternCaseList_		 -469761950L	/* 98 */
#define  _FormulaCaseList 		 -469696611L	/* -99 */
#define  _FormulaCaseList_		 -469761949L	/* 99 */
#define  _ItemList 		 -469696612L	/* -100 */
#define  _ItemList_		 -469761948L	/* 100 */
#define  _NameList 		 -469696613L	/* -101 */
#define  _NameList_		 -469761947L	/* 101 */
#define  _DefIdNodeList 		 -469696614L	/* -102 */
#define  _DefIdNodeList_		 -469761946L	/* 102 */
#define  _CompExprNodeList 		 -469696615L	/* -103 */
#define  _CompExprNodeList_		 -469761945L	/* 103 */
#define  _NameNList 		 -469696616L	/* -104 */
#define  _NameNList_		 -469761944L	/* 104 */
#define  _ItemNList 		 -469696617L	/* -105 */
#define  _ItemNList_		 -469761943L	/* 105 */
#define  _Relationship 		 -469696618L	/* -106 */
#define  _Relationship_		 -469761942L	/* 106 */
#define  _SortIdNList 		 -469696619L	/* -107 */
#define  _SortIdNList_		 -469761941L	/* 107 */
#define  _ExprNList 		 -469696620L	/* -108 */
#define  _ExprNList_		 -469761940L	/* 108 */
#define  _OrValue 		 -469696621L	/* -109 */
#define  _OrValue_		 -469761939L	/* 109 */
#define  _FList 		 -469696622L	/* -110 */
#define  _FList_		 -469761938L	/* 110 */
#define  _ApplList 		 -469696623L	/* -111 */
#define  _ApplList_		 -469761937L	/* 111 */
#define  _FuAtListInfo 		 -469696624L	/* -112 */
#define  _FuAtListInfo_		 -469761936L	/* 112 */
#define  _FuAtNodeList 		 -469696625L	/* -113 */
#define  _FuAtNodeList_		 -469761935L	/* 113 */
#define  _IntResList 		 -469696626L	/* -114 */
#define  _IntResList_		 -469761934L	/* 114 */
#define  _IntList 		 -469696627L	/* -115 */
#define  _IntList_		 -469761933L	/* 115 */
#define  _RefList 		 -469696628L	/* -116 */
#define  _RefList_		 -469761932L	/* 116 */
#define  _ProdNodeList 		 -469696629L	/* -117 */
#define  _ProdNodeList_		 -469761931L	/* 117 */
#define  _IdentList 		 -469696630L	/* -118 */
#define  _IdentList_		 -469761930L	/* 118 */
#define  _CharList 		 -469696631L	/* -119 */
#define  _CharList_		 -469761929L	/* 119 */
#define  _RsideInfo 		 -469696632L	/* -120 */
#define  _RsideInfo_		 -469761928L	/* 120 */
#define  _RsideList 		 -469696633L	/* -121 */
#define  _RsideList_		 -469761927L	/* 121 */
#define  _LsideList 		 -469696634L	/* -122 */
#define  _LsideList_		 -469761926L	/* 122 */
#define  _LPinfoListlist 		 -469696635L	/* -123 */
#define  _LPinfoListlist_		 -469761925L	/* 123 */
#define  _LPinfolist 		 -469696636L	/* -124 */
#define  _LPinfolist_		 -469761924L	/* 124 */
#define  _StringList 		 -469696637L	/* -125 */
#define  _StringList_		 -469761923L	/* 125 */
#define  _CPinfoList 		 -469696638L	/* -126 */
#define  _CPinfoList_		 -469761922L	/* 126 */
#define  _CPinfoListlist 		 -469696639L	/* -127 */
#define  _CPinfoListlist_		 -469761921L	/* 127 */
#define  _RuleList 		 -469696640L	/* -128 */
#define  _RuleList_		 -469761920L	/* 128 */
#define  _CaseIsList 		 -469696641L	/* -129 */
#define  _CaseIsList_		 -469761919L	/* 129 */
#define  _UpdateList 		 -469696642L	/* -130 */
#define  _UpdateList_		 -469761918L	/* 130 */
#define  _UListNodeList 		 -469696643L	/* -131 */
#define  _UListNodeList_		 -469761917L	/* 131 */
#define  _CaseTripelList 		 -469696644L	/* -132 */
#define  _CaseTripelList_		 -469761916L	/* 132 */
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
#define  _CharConst 		 -469696538L	/* -26 */
#define  _CharConst_		 -469762022L	/* 26 */
#define  _IntConst 		 -469696539L	/* -27 */
#define  _IntConst_		 -469762021L	/* 27 */
#define  _StringConst 		 -469696540L	/* -28 */
#define  _StringConst_		 -469762020L	/* 28 */
#define  _SortConst 		 -469696541L	/* -29 */
#define  _SortConst_		 -469762019L	/* 29 */
#define  _FuncAppl 		 -469696542L	/* -30 */
#define  _FuncAppl_		 -469762018L	/* 30 */
#define  _IfExpr 		 -469696543L	/* -31 */
#define  _IfExpr_		 -469762017L	/* 31 */
#define  _LetExpr 		 -469696544L	/* -32 */
#define  _LetExpr_		 -469762016L	/* 32 */
#define  _StringExpr 		 -469696545L	/* -33 */
#define  _StringExpr_		 -469762015L	/* 33 */
#define  _PatternCase 		 -469696546L	/* -34 */
#define  _PatternCase_		 -469762014L	/* 34 */
#define  _FormulaCase 		 -469696547L	/* -35 */
#define  _FormulaCase_		 -469762013L	/* 35 */
#define  _PredAppl 		 -469696548L	/* -36 */
#define  _PredAppl_		 -469762012L	/* 36 */
#define  _Or 		 -469696549L	/* -37 */
#define  _Or_		 -469762011L	/* 37 */
#define  _And 		 -469696550L	/* -38 */
#define  _And_		 -469762010L	/* 38 */
#define  _Impl 		 -469696551L	/* -39 */
#define  _Impl_		 -469762009L	/* 39 */
#define  _Neg 		 -469696552L	/* -40 */
#define  _Neg_		 -469762008L	/* 40 */
#define  _Pattern 		 -469696553L	/* -41 */
#define  _Pattern_		 -469762007L	/* 41 */
#define  _DefId 		 -469696554L	/* -42 */
#define  _DefId_		 -469762006L	/* 42 */
#define  _TermSortId 		 -469696555L	/* -43 */
#define  _TermSortId_		 -469762005L	/* 43 */
#define  _NodeSortId 		 -469696556L	/* -44 */
#define  _NodeSortId_		 -469762004L	/* 44 */
#define  _ApplId 		 -469696557L	/* -45 */
#define  _ApplId_		 -469762003L	/* 45 */
#define  _Name 		 -469696558L	/* -46 */
#define  _Name_		 -469762002L	/* 46 */
#define  _Blank 		 -469696559L	/* -47 */
#define  _Blank_		 -469762001L	/* 47 */
#define  _Asterisk 		 -469696560L	/* -48 */
#define  _Asterisk_		 -469762000L	/* 48 */
#define  _ParTup 		 -469696561L	/* -49 */
#define  _ParTup_		 -469761999L	/* 49 */
#define  _NameDepthTup 		 -469696562L	/* -50 */
#define  _NameDepthTup_		 -469761998L	/* 50 */
#define  _RelPosition 		 -469696563L	/* -51 */
#define  _RelPosition_		 -469761997L	/* 51 */
#define  _AbsPosition 		 -469696564L	/* -52 */
#define  _AbsPosition_		 -469761996L	/* 52 */
#define  _TopPosition 		 -469696565L	/* -53 */
#define  _TopPosition_		 -469761995L	/* 53 */
#define  _Fath 		 -469696566L	/* -54 */
#define  _Fath_		 -469761994L	/* 54 */
#define  _Lbroth 		 -469696567L	/* -55 */
#define  _Lbroth_		 -469761993L	/* 55 */
#define  _Rbroth 		 -469696568L	/* -56 */
#define  _Rbroth_		 -469761992L	/* 56 */
#define  _Son 		 -469696569L	/* -57 */
#define  _Son_		 -469761991L	/* 57 */
#define  _SonTC 		 -469696570L	/* -58 */
#define  _SonTC_		 -469761990L	/* 58 */
#define  _FClosure 		 -469696571L	/* -59 */
#define  _FClosure_		 -469761989L	/* 59 */
#define  _TWson 		 -469696572L	/* -60 */
#define  _TWson_		 -469761988L	/* 60 */
#define  _TWfath 		 -469696573L	/* -61 */
#define  _TWfath_		 -469761987L	/* 61 */
#define  _TWrbroth 		 -469696574L	/* -62 */
#define  _TWrbroth_		 -469761986L	/* 62 */
#define  _TWlbroth 		 -469696575L	/* -63 */
#define  _TWlbroth_		 -469761985L	/* 63 */
#define  _RelevAcc 		 -469696576L	/* -64 */
#define  _RelevAcc_		 -469761984L	/* 64 */
#define  _AllNodes 		 -469696577L	/* -65 */
#define  _AllNodes_		 -469761983L	/* 65 */
#define  _Parsnr 		 -469696578L	/* -66 */
#define  _Parsnr_		 -469761982L	/* 66 */
#define  _Parsline 		 -469696579L	/* -67 */
#define  _Parsline_		 -469761981L	/* 67 */
#define  _Parscol 		 -469696580L	/* -68 */
#define  _Parscol_		 -469761980L	/* 68 */
#define  _Parspos 		 -469696581L	/* -69 */
#define  _Parspos_		 -469761979L	/* 69 */
#define  _Parsprio 		 -469696582L	/* -70 */
#define  _Parsprio_		 -469761978L	/* 70 */
#define  _Parsrule 		 -469696583L	/* -71 */
#define  _Parsrule_		 -469761977L	/* 71 */
#define  _Parsaddrule 		 -469696584L	/* -72 */
#define  _Parsaddrule_		 -469761976L	/* 72 */
#define  _Parsno 		 -469696585L	/* -73 */
#define  _Parsno_		 -469761975L	/* 73 */
#define  _Parsleft 		 -469696586L	/* -74 */
#define  _Parsleft_		 -469761974L	/* 74 */
#define  _Parsright 		 -469696587L	/* -75 */
#define  _Parsright_		 -469761973L	/* 75 */
#define  _Parsaux 		 -469696588L	/* -76 */
#define  _Parsaux_		 -469761972L	/* 76 */
#define  _ParsStern 		 -469696589L	/* -77 */
#define  _ParsStern_		 -469761971L	/* 77 */
#define  _ParsPlus 		 -469696590L	/* -78 */
#define  _ParsPlus_		 -469761970L	/* 78 */
#define  _IdentTripel 		 -469696591L	/* -79 */
#define  _IdentTripel_		 -469761969L	/* 79 */
#define  _CPinfo 		 -469696592L	/* -80 */
#define  _CPinfo_		 -469761968L	/* 80 */
#define  _DynFunc 		 -469696593L	/* -81 */
#define  _DynFunc_		 -469761967L	/* 81 */
#define  _IfRule 		 -469696594L	/* -82 */
#define  _IfRule_		 -469761966L	/* 82 */
#define  _CaseRule 		 -469696595L	/* -83 */
#define  _CaseRule_		 -469761965L	/* 83 */
#define  _CaseIs 		 -469696596L	/* -84 */
#define  _CaseIs_		 -469761964L	/* 84 */
#define  _Update 		 -469696597L	/* -85 */
#define  _Update_		 -469761963L	/* 85 */
#define  _DynUndef 		 -469696598L	/* -86 */
#define  _DynUndef_		 -469761962L	/* 86 */
#define  _DynSemInput 		 -469696599L	/* -87 */
#define  _DynSemInput_		 -469761961L	/* 87 */
#define  _CaseTripel 		 -469696600L	/* -88 */
#define  _CaseTripel_		 -469761960L	/* 88 */
#define  _Element 		 -469696645L	/* -133 */
#define  _Element_		 -469761915L	/* 133 */
#define  _GlobalDecl 		 -469696646L	/* -134 */
#define  _GlobalDecl_		 -469761914L	/* 134 */
#define  _Production 		 -469696647L	/* -135 */
#define  _Production_		 -469761913L	/* 135 */
#define  _LocalDecl 		 -469696648L	/* -136 */
#define  _LocalDecl_		 -469761912L	/* 136 */
#define  _Expr 		 -469696649L	/* -137 */
#define  _Expr_		 -469761911L	/* 137 */
#define  _Constant 		 -469696650L	/* -138 */
#define  _Constant_		 -469761910L	/* 138 */
#define  _ComposedExpr 		 -469696651L	/* -139 */
#define  _ComposedExpr_		 -469761909L	/* 139 */
#define  _CaseList 		 -469696652L	/* -140 */
#define  _CaseList_		 -469761908L	/* 140 */
#define  _Formula 		 -469696653L	/* -141 */
#define  _Formula_		 -469761907L	/* 141 */
#define  _SortPos 		 -469696654L	/* -142 */
#define  _SortPos_		 -469761906L	/* 142 */
#define  _SubPatternPos 		 -469696655L	/* -143 */
#define  _SubPatternPos_		 -469761905L	/* 143 */
#define  _NamePos 		 -469696656L	/* -144 */
#define  _NamePos_		 -469761904L	/* 144 */
#define  _Item 		 -469696657L	/* -145 */
#define  _Item_		 -469761903L	/* 145 */
#define  _UsedId 		 -469696658L	/* -146 */
#define  _UsedId_		 -469761902L	/* 146 */
#define  _SortId 		 -469696659L	/* -147 */
#define  _SortId_		 -469761901L	/* 147 */
#define  _Declaration 		 -469696660L	/* -148 */
#define  _Declaration_		 -469761900L	/* 148 */
#define  _Definition 		 -469696661L	/* -149 */
#define  _Definition_		 -469761899L	/* 149 */
#define  _DefWithoutProd 		 -469696662L	/* -150 */
#define  _DefWithoutProd_		 -469761898L	/* 150 */
#define  _ApplyEntity 		 -469696663L	/* -151 */
#define  _ApplyEntity_		 -469761897L	/* 151 */
#define  _Scope 		 -469696664L	/* -152 */
#define  _Scope_		 -469761896L	/* 152 */
#define  _SortCdList 		 -469696665L	/* -153 */
#define  _SortCdList_		 -469761895L	/* 153 */
#define  _Section 		 -469696666L	/* -154 */
#define  _Section_		 -469761894L	/* 154 */
#define  _Case 		 -469696667L	/* -155 */
#define  _Case_		 -469761893L	/* 155 */
#define  _ItemPosition 		 -469696668L	/* -156 */
#define  _ItemPosition_		 -469761892L	/* 156 */
#define  _Relative 		 -469696669L	/* -157 */
#define  _Relative_		 -469761891L	/* 157 */
#define  _MetaSort 		 -469696670L	/* -158 */
#define  _MetaSort_		 -469761890L	/* 158 */
#define  _IfCase 		 -469696671L	/* -159 */
#define  _IfCase_		 -469761889L	/* 159 */
#define  _Value 		 -469696672L	/* -160 */
#define  _Value_		 -469761888L	/* 160 */
#define  _FValue 		 -469696673L	/* -161 */
#define  _FValue_		 -469761887L	/* 161 */
#define  _FctOrAtt 		 -469696674L	/* -162 */
#define  _FctOrAtt_		 -469761886L	/* 162 */
#define  _FctOrAttDecl 		 -469696675L	/* -163 */
#define  _FctOrAttDecl_		 -469761885L	/* 163 */
#define  _OrderTup 		 -469696676L	/* -164 */
#define  _OrderTup_		 -469761884L	/* 164 */
#define  _BinOp 		 -469696677L	/* -165 */
#define  _BinOp_		 -469761883L	/* 165 */
#define  _DefIdNodeInfo 		 -469696678L	/* -166 */
#define  _DefIdNodeInfo_		 -469761882L	/* 166 */
#define  _IntResExpr 		 -469696679L	/* -167 */
#define  _IntResExpr_		 -469761881L	/* 167 */
#define  _IntResOrName 		 -469696680L	/* -168 */
#define  _IntResOrName_		 -469761880L	/* 168 */
#define  _Rside 		 -469696681L	/* -169 */
#define  _Rside_		 -469761879L	/* 169 */
#define  _Lside 		 -469696682L	/* -170 */
#define  _Lside_		 -469761878L	/* 170 */
#define  _LPinfo 		 -469696683L	/* -171 */
#define  _LPinfo_		 -469761877L	/* 171 */
#define  _Rule 		 -469696684L	/* -172 */
#define  _Rule_		 -469761876L	/* 172 */
#define  _CaseConst 		 -469696685L	/* -173 */
#define  _CaseConst_		 -469761875L	/* 173 */
#define  _UpdateOrRule 		 -469696686L	/* -174 */
#define  _UpdateOrRule_		 -469761874L	/* 174 */
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
#define  ListProd(P1,P2)		mxi_tc(__FILE__,__LINE__,"ListProd",2,-14,-42,P1,-147,P2)
#define  TupelProd(P1,P2)		mxi_tc(__FILE__,__LINE__,"TupelProd",2,-15,-42,P1,-91,P2)
#define  ClassProd(P1,P2)		mxi_tc(__FILE__,__LINE__,"ClassProd",2,-16,-42,P1,-91,P2)
#define  PredeclProd(P1)		mxi_tc(__FILE__,__LINE__,"PredeclProd",1,-17,-42,P1)
#define  PredDecl(P1,P2)		mxi_tc(__FILE__,__LINE__,"PredDecl",2,-18,-42,P1,-91,P2)
#define  FuncDecl(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"FuncDecl",3,-19,-42,P1,-91,P2,-147,P3)
#define  Structure(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"Structure",3,-20,-42,P1,-43,P2,-92,P3)
#define  Predicate(P1,P2,P3,P4)		mxi_tc(__FILE__,__LINE__,"Predicate",4,-21,-42,P1,-91,P2,-101,P3,-141,P4)
#define  Function(P1,P2,P3,P4,P5)		mxi_tc(__FILE__,__LINE__,"Function",5,-22,-42,P1,-91,P2,-101,P3,-147,P4,-137,P5)
#define  Attribute(P1,P2,P3,P4,P5)		mxi_tc(__FILE__,__LINE__,"Attribute",5,-23,-42,P1,-91,P2,-101,P3,-147,P4,-137,P5)
#define  Condition(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"Condition",3,-24,-96,P1,-141,P2,-137,P3)
#define  AttrDecl(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"AttrDecl",3,-25,-42,P1,-91,P2,-147,P3)
#define  CharConst(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"CharConst",3,-26,-10,P1,-11,P2,-11,P3)
#define  IntConst(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"IntConst",3,-27,-11,P1,-11,P2,-11,P3)
#define  StringConst(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"StringConst",3,-28,-12,P1,-11,P2,-11,P3)
#define  SortConst(P1)		mxi_tc(__FILE__,__LINE__,"SortConst",1,-29,-147,P1)
#define  FuncAppl(P1,P2)		mxi_tc(__FILE__,__LINE__,"FuncAppl",2,-30,-45,P1,-97,P2)
#define  IfExpr(P1,P2,P3,P4)		mxi_tc(__FILE__,__LINE__,"IfExpr",4,-31,-140,P1,-137,P2,-11,P3,-11,P4)
#define  LetExpr(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"LetExpr",3,-32,-46,P1,-137,P2,-137,P3)
#define  StringExpr(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"StringExpr",3,-33,-97,P1,-11,P2,-11,P3)
#define  PatternCase(P1,P2)		mxi_tc(__FILE__,__LINE__,"PatternCase",2,-34,-41,P1,-137,P2)
#define  FormulaCase(P1,P2)		mxi_tc(__FILE__,__LINE__,"FormulaCase",2,-35,-141,P1,-137,P2)
#define  PredAppl(P1,P2)		mxi_tc(__FILE__,__LINE__,"PredAppl",2,-36,-45,P1,-97,P2)
#define  Or(P1,P2)		mxi_tc(__FILE__,__LINE__,"Or",2,-37,-141,P1,-141,P2)
#define  And(P1,P2)		mxi_tc(__FILE__,__LINE__,"And",2,-38,-141,P1,-141,P2)
#define  Impl(P1,P2)		mxi_tc(__FILE__,__LINE__,"Impl",2,-39,-141,P1,-141,P2)
#define  Neg(P1)		mxi_tc(__FILE__,__LINE__,"Neg",1,-40,-141,P1)
#define  Pattern(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"Pattern",3,-41,-142,P1,-143,P2,-144,P3)
#define  DefId(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"DefId",3,-42,-8,P1,-11,P2,-11,P3)
#define  TermSortId(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"TermSortId",3,-43,-8,P1,-11,P2,-11,P3)
#define  NodeSortId(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"NodeSortId",3,-44,-8,P1,-11,P2,-11,P3)
#define  ApplId(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"ApplId",3,-45,-8,P1,-11,P2,-11,P3)
#define  Name(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"Name",3,-46,-8,P1,-11,P2,-11,P3)
#define  Blank(P1)		mxi_tc(__FILE__,__LINE__,"Blank",1,-47,-11,P1)
#define  Asterisk()		 -536805424L
#define  ParTup(P1,P2)		mxi_tc(__FILE__,__LINE__,"ParTup",2,-49,-91,P1,-101,P2)
#define  NameDepthTup(P1,P2)		mxi_tc(__FILE__,__LINE__,"NameDepthTup",2,-50,46,P1,-11,P2)
#define  RelPosition(P1)		mxi_tc(__FILE__,__LINE__,"RelPosition",1,-51,-11,P1)
#define  AbsPosition(P1)		mxi_tc(__FILE__,__LINE__,"AbsPosition",1,-52,-11,P1)
#define  TopPosition()		 -536805429L
#define  Fath()		 -536805430L
#define  Lbroth(P1)		mxi_tc(__FILE__,__LINE__,"Lbroth",1,-55,-11,P1)
#define  Rbroth(P1)		mxi_tc(__FILE__,__LINE__,"Rbroth",1,-56,-11,P1)
#define  Son(P1)		mxi_tc(__FILE__,__LINE__,"Son",1,-57,-11,P1)
#define  SonTC(P1,P2,P3,P4,P5)		mxi_tc(__FILE__,__LINE__,"SonTC",5,-58,-11,P1,-11,P2,-11,P3,-11,P4,-11,P5)
#define  FClosure(P1)		mxi_tc(__FILE__,__LINE__,"FClosure",1,-59,-160,P1)
#define  TWson(P1)		mxi_tc(__FILE__,__LINE__,"TWson",1,-60,-11,P1)
#define  TWfath()		 -536805437L
#define  TWrbroth()		 -536805438L
#define  TWlbroth()		 -536805439L
#define  RelevAcc(P1)		mxi_tc(__FILE__,__LINE__,"RelevAcc",1,-64,-11,P1)
#define  AllNodes()		 -536805441L
#define  Parsnr(P1)		mxi_tc(__FILE__,__LINE__,"Parsnr",1,-66,-11,P1)
#define  Parsline()		 -536805443L
#define  Parscol()		 -536805444L
#define  Parspos()		 -536805445L
#define  Parsprio()		 -536805446L
#define  Parsrule(P1)		mxi_tc(__FILE__,__LINE__,"Parsrule",1,-71,-125,P1)
#define  Parsaddrule(P1)		mxi_tc(__FILE__,__LINE__,"Parsaddrule",1,-72,-125,P1)
#define  Parsno()		 -536805449L
#define  Parsleft()		 -536805450L
#define  Parsright()		 -536805451L
#define  Parsaux()		 -536805452L
#define  ParsStern(P1)		mxi_tc(__FILE__,__LINE__,"ParsStern",1,-77,-12,P1)
#define  ParsPlus(P1)		mxi_tc(__FILE__,__LINE__,"ParsPlus",1,-78,-12,P1)
#define  IdentTripel(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"IdentTripel",3,-79,-8,P1,-8,P2,-8,P3)
#define  CPinfo(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"CPinfo",3,-80,-125,P1,-147,P2,-125,P3)
#define  DynFunc(P1,P2,P3,P4,P5)		mxi_tc(__FILE__,__LINE__,"DynFunc",5,-81,-42,P1,-91,P2,-101,P3,-147,P4,-137,P5)
#define  IfRule(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"IfRule",3,-82,-141,P1,-130,P2,-130,P3)
#define  CaseRule(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"CaseRule",3,-83,-137,P1,-129,P2,-130,P3)
#define  CaseIs(P1,P2)		mxi_tc(__FILE__,__LINE__,"CaseIs",2,-84,-173,P1,-130,P2)
#define  Update(P1,P2)		mxi_tc(__FILE__,__LINE__,"Update",2,-85,-30,P1,-137,P2)
#define  DynUndef()		 -536805462L
#define  DynSemInput(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"DynSemInput",3,-87,-42,P1,-91,P2,-147,P3)
#define  CaseTripel(P1,P2,P3)		mxi_tc(__FILE__,__LINE__,"CaseTripel",3,-88,-102,P1,-102,P2,130,P3)
#define  Specification()		-536805465L
#define  ProdList()		-536805466L
#define  SortIdList()		-536805467L
#define  LocalDeclList()		-536805468L
#define  PredList()		-536805469L
#define  FuAtList()		-536805470L
#define  CondList()		-536805471L
#define  PatternList()		-536805472L
#define  ExprList()		-536805473L
#define  PatternCaseList()		-536805474L
#define  FormulaCaseList()		-536805475L
#define  ItemList()		-536805476L
#define  NameList()		-536805477L
#define  DefIdNodeList()		-536805478L
#define  CompExprNodeList()		-536805479L
#define  NameNList()		-536805480L
#define  ItemNList()		-536805481L
#define  Relationship()		-536805482L
#define  SortIdNList()		-536805483L
#define  ExprNList()		-536805484L
#define  OrValue()		-536805485L
#define  FList()		-536805486L
#define  ApplList()		-536805487L
#define  FuAtListInfo()		-536805488L
#define  FuAtNodeList()		-536805489L
#define  IntResList()		-536805490L
#define  IntList()		-536805491L
#define  RefList()		-536805492L
#define  ProdNodeList()		-536805493L
#define  IdentList()		-536805494L
#define  CharList()		-536805495L
#define  RsideInfo()		-536805496L
#define  RsideList()		-536805497L
#define  LsideList()		-536805498L
#define  LPinfoListlist()		-536805499L
#define  LPinfolist()		-536805500L
#define  StringList()		-536805501L
#define  CPinfoList()		-536805502L
#define  CPinfoListlist()		-536805503L
#define  RuleList()		-536805504L
#define  CaseIsList()		-536805505L
#define  UpdateList()		-536805506L
#define  UListNodeList()		-536805507L
#define  CaseTripelList()		-536805508L

/* The constructors and destructors for tree structures                    */
#define init_max(TERM)		mxi_init(__FILE__,__LINE__,-89,TERM)
#define free_max()			mxi_free(__FILE__,__LINE__)

/* The declarations for defined functions, predicates, and attributes     */
typedef void (*EVALFCT1)( ELEMENT );
typedef void (*EVALFCT)( ELEMENT, ELEMENT, int, ELEMENT * );
extern ELEMENT  mxs_encl_dynfunc(char*,int,ELEMENT);
#define encl_dynfunc(p1)		mxs_encl_dynfunc(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_id(char*,int,ELEMENT);
#define id(p1)		mxs_id(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_patlineno(char*,int,ELEMENT);
#define patlineno(p1)		mxs_patlineno(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_decl(char*,int,ELEMENT);
#define decl(p1)		mxs_decl(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_sort_union(char*,int,ELEMENT,ELEMENT);
#define sort_union(p1,p2)		mxs_sort_union(__FILE__,__LINE__,p1,p2)
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
extern ELEMENT  mxs_countastrks(char*,int,ELEMENT,ELEMENT);
#define countastrks(p1,p2)		mxs_countastrks(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_smallestlistprodcd(char*,int);
#define smallestlistprodcd()		mxs_smallestlistprodcd(__FILE__,__LINE__)
extern ELEMENT  mxs_prodcd(char*,int,ELEMENT);
#define prodcd(p1)		mxs_prodcd(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_next_left_pat(char*,int,ELEMENT);
#define next_left_pat(p1)		mxs_next_left_pat(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_patnposition(char*,int,ELEMENT,ELEMENT);
#define patnposition(p1,p2)		mxs_patnposition(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_next_pat_for_codegen(char*,int,ELEMENT);
#define next_pat_for_codegen(p1)		mxs_next_pat_for_codegen(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_next_pat_upthetree(char*,int,ELEMENT);
#define next_pat_upthetree(p1)		mxs_next_pat_upthetree(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_pat_absoff_pos(char*,int,ELEMENT);
#define pat_absoff_pos(p1)		mxs_pat_absoff_pos(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_pat_reloff_pos(char*,int,ELEMENT,ELEMENT);
#define pat_reloff_pos(p1,p2)		mxs_pat_reloff_pos(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_pat_absoff_neg(char*,int,ELEMENT);
#define pat_absoff_neg(p1)		mxs_pat_absoff_neg(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_pat_reloff_neg(char*,int,ELEMENT,ELEMENT);
#define pat_reloff_neg(p1,p2)		mxs_pat_reloff_neg(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_pat_absoff(char*,int,ELEMENT);
#define pat_absoff(p1)		mxs_pat_absoff(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_pat_reloff(char*,int,ELEMENT,ELEMENT);
#define pat_reloff(p1,p2)		mxs_pat_reloff(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_abs_itempos(char*,int,ELEMENT);
#define abs_itempos(p1)		mxs_abs_itempos(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_lmin_itempos(char*,int,ELEMENT);
#define lmin_itempos(p1)		mxs_lmin_itempos(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_rmin_itempos(char*,int,ELEMENT);
#define rmin_itempos(p1)		mxs_rmin_itempos(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_path(char*,int,ELEMENT,ELEMENT);
#define path(p1,p2)		mxs_path(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_search_bound_names_rec(char*,int,ELEMENT);
#define search_bound_names_rec(p1)		mxs_search_bound_names_rec(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_search_bound_names(char*,int,ELEMENT);
#define search_bound_names(p1)		mxs_search_bound_names(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_search_free_items_rec(char*,int,ELEMENT);
#define search_free_items_rec(p1)		mxs_search_free_items_rec(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_search_free_items(char*,int,ELEMENT);
#define search_free_items(p1)		mxs_search_free_items(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_search_blanks_rec(char*,int,ELEMENT);
#define search_blanks_rec(p1)		mxs_search_blanks_rec(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_search_blanks(char*,int,ELEMENT);
#define search_blanks(p1)		mxs_search_blanks(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_search_free_p_names_rec(char*,int,ELEMENT,ELEMENT);
#define search_free_p_names_rec(p1,p2)		mxs_search_free_p_names_rec(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_search_free_p_names(char*,int,ELEMENT,ELEMENT);
#define search_free_p_names(p1,p2)		mxs_search_free_p_names(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_search_bound_p_names_rec(char*,int,ELEMENT,ELEMENT);
#define search_bound_p_names_rec(p1,p2)		mxs_search_bound_p_names_rec(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_search_bound_p_names(char*,int,ELEMENT,ELEMENT);
#define search_bound_p_names(p1,p2)		mxs_search_bound_p_names(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_search_patt_names(char*,int,ELEMENT,ELEMENT);
#define search_patt_names(p1,p2)		mxs_search_patt_names(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_search_patt_sorts_rec(char*,int,ELEMENT);
#define search_patt_sorts_rec(p1)		mxs_search_patt_sorts_rec(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_search_patt_sorts(char*,int,ELEMENT);
#define search_patt_sorts(p1)		mxs_search_patt_sorts(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_search_name_in_patt_rec(char*,int,ELEMENT,ELEMENT);
#define search_name_in_patt_rec(p1,p2)		mxs_search_name_in_patt_rec(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_search_name_in_patt(char*,int,ELEMENT,ELEMENT);
#define search_name_in_patt(p1,p2)		mxs_search_name_in_patt(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_latest_bindpos(char*,int,ELEMENT,ELEMENT);
#define latest_bindpos(p1,p2)		mxs_latest_bindpos(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_par_pos(char*,int,ELEMENT,ELEMENT);
#define par_pos(p1,p2)		mxs_par_pos(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_corresp_parsort(char*,int,ELEMENT);
#define corresp_parsort(p1)		mxs_corresp_parsort(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_actpar_pos(char*,int,ELEMENT,ELEMENT);
#define actpar_pos(p1,p2)		mxs_actpar_pos(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_univ_path(char*,int,ELEMENT,ELEMENT);
#define univ_path(p1,p2)		mxs_univ_path(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_mk_enl(char*,int,ELEMENT);
#define mk_enl(p1)		mxs_mk_enl(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_dep_expr(char*,int,ELEMENT);
#define dep_expr(p1)		mxs_dep_expr(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_lineof(char*,int,ELEMENT);
#define lineof(p1)		mxs_lineof(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_colof(char*,int,ELEMENT);
#define colof(p1)		mxs_colof(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_TW_identabb(char*,int);
#define TW_identabb()		mxs_TW_identabb(__FILE__,__LINE__)
extern ELEMENT  mxs_TW_emptyset(char*,int);
#define TW_emptyset()		mxs_TW_emptyset(__FILE__,__LINE__)
extern ELEMENT  mxs_TW_or(char*,int,ELEMENT,ELEMENT);
#define TW_or(p1,p2)		mxs_TW_or(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_delete_id(char*,int,ELEMENT);
#define delete_id(p1)		mxs_delete_id(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_TW_closure(char*,int,ELEMENT);
#define TW_closure(p1)		mxs_TW_closure(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_TW_conc(char*,int,ELEMENT,ELEMENT);
#define TW_conc(p1,p2)		mxs_TW_conc(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_node_parnr_fct(char*,int,ELEMENT);
#define node_parnr_fct(p1)		mxs_node_parnr_fct(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_encl_patcase(char*,int,ELEMENT);
#define encl_patcase(p1)		mxs_encl_patcase(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_pat_son_pos_nr(char*,int,ELEMENT);
#define pat_son_pos_nr(p1)		mxs_pat_son_pos_nr(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_pat_son_neg_nr(char*,int,ELEMENT);
#define pat_son_neg_nr(p1)		mxs_pat_son_neg_nr(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_pat_son_nr(char*,int,ELEMENT);
#define pat_son_nr(p1)		mxs_pat_son_nr(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_pat_way(char*,int,ELEMENT,ELEMENT);
#define pat_way(p1,p2)		mxs_pat_way(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_enter_attrgroup(char*,int,ELEMENT,ELEMENT,ELEMENT);
#define enter_attrgroup(p1,p2,p3)		mxs_enter_attrgroup(__FILE__,__LINE__,p1,p2,p3)
extern ELEMENT  mxs_enter_attrgroup_list(char*,int,ELEMENT,ELEMENT,ELEMENT);
#define enter_attrgroup_list(p1,p2,p3)		mxs_enter_attrgroup_list(__FILE__,__LINE__,p1,p2,p3)
extern ELEMENT  mxs_simplify_closure(char*,int,ELEMENT);
#define simplify_closure(p1)		mxs_simplify_closure(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_normal_tw(char*,int,ELEMENT,ELEMENT,ELEMENT);
#define normal_tw(p1,p2,p3)		mxs_normal_tw(__FILE__,__LINE__,p1,p2,p3)
extern ELEMENT  mxs_normal_closure(char*,int,ELEMENT,ELEMENT);
#define normal_closure(p1,p2)		mxs_normal_closure(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_normalform(char*,int,ELEMENT,ELEMENT,ELEMENT);
#define normalform(p1,p2,p3)		mxs_normalform(__FILE__,__LINE__,p1,p2,p3)
extern ELEMENT  mxs_Ord_fath(char*,int);
#define Ord_fath()		mxs_Ord_fath(__FILE__,__LINE__)
extern ELEMENT  mxs_Ord_son(char*,int);
#define Ord_son()		mxs_Ord_son(__FILE__,__LINE__)
extern ELEMENT  mxs_Ord_rbroth(char*,int);
#define Ord_rbroth()		mxs_Ord_rbroth(__FILE__,__LINE__)
extern ELEMENT  mxs_Ord_lbroth(char*,int);
#define Ord_lbroth()		mxs_Ord_lbroth(__FILE__,__LINE__)
extern ELEMENT  mxs_Ord_ident(char*,int);
#define Ord_ident()		mxs_Ord_ident(__FILE__,__LINE__)
extern ELEMENT  mxs_Ord_neutral(char*,int);
#define Ord_neutral()		mxs_Ord_neutral(__FILE__,__LINE__)
extern ELEMENT  mxs_Ord_nothing(char*,int);
#define Ord_nothing()		mxs_Ord_nothing(__FILE__,__LINE__)
extern ELEMENT  mxs_val_order(char*,int,ELEMENT);
#define val_order(p1)		mxs_val_order(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_contains_attr(char*,int,ELEMENT);
#define contains_attr(p1)		mxs_contains_attr(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_encl_fctoratt(char*,int,ELEMENT);
#define encl_fctoratt(p1)		mxs_encl_fctoratt(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_filter_relev_acc(char*,int,ELEMENT);
#define filter_relev_acc(p1)		mxs_filter_relev_acc(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_list_intresexprs(char*,int,ELEMENT);
#define list_intresexprs(p1)		mxs_list_intresexprs(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_intresexprs(char*,int,ELEMENT);
#define intresexprs(p1)		mxs_intresexprs(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_encl_part_intres(char*,int,ELEMENT);
#define encl_part_intres(p1)		mxs_encl_part_intres(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_aux_var_need(char*,int,ELEMENT,ELEMENT);
#define aux_var_need(p1,p2)		mxs_aux_var_need(__FILE__,__LINE__,p1,p2)
extern ELEMENT  mxs_aux_intres_left(char*,int,ELEMENT,ELEMENT,ELEMENT);
#define aux_intres_left(p1,p2,p3)		mxs_aux_intres_left(__FILE__,__LINE__,p1,p2,p3)
extern ELEMENT  mxs_aux_intres_right(char*,int,ELEMENT,ELEMENT,ELEMENT,ELEMENT,ELEMENT);
#define aux_intres_right(p1,p2,p3,p4,p5)		mxs_aux_intres_right(__FILE__,__LINE__,p1,p2,p3,p4,p5)
extern long     mxs_in(char*,int,ELEMENT,ELEMENT,ELEMENT);
#define in(p1,p2,p3)		mxs_in(__FILE__,__LINE__,p1,p2,p3)
extern long     mxs_is_enumerable(char*,int,ELEMENT);
#define is_enumerable(p1)		mxs_is_enumerable(__FILE__,__LINE__,p1)
extern long     mxs_ex_pattern_inbetween(char*,int,ELEMENT,ELEMENT);
#define ex_pattern_inbetween(p1,p2)		mxs_ex_pattern_inbetween(__FILE__,__LINE__,p1,p2)
extern long     mxs_is_node(char*,int,ELEMENT);
#define is_node(p1)		mxs_is_node(__FILE__,__LINE__,p1)
extern long     mxs_simplification(char*,int,ELEMENT,ELEMENT);
#define simplification(p1,p2)		mxs_simplification(__FILE__,__LINE__,p1,p2)
extern long     mxs_is_intres(char*,int,ELEMENT);
#define is_intres(p1)		mxs_is_intres(__FILE__,__LINE__,p1)
extern ELEMENT  mxs_term_basesorts(char*,int,ELEMENT);
#define term_basesorts(p)		mxs_term_basesorts(__FILE__,__LINE__,p)
extern ELEMENT  mxs_node_basesorts(char*,int,ELEMENT);
#define node_basesorts(p)		mxs_node_basesorts(__FILE__,__LINE__,p)
extern ELEMENT  mxs_encl_scope(char*,int,ELEMENT);
#define encl_scope(p)		mxs_encl_scope(__FILE__,__LINE__,p)
extern ELEMENT  mxs_bind_pos(char*,int,ELEMENT);
#define bind_pos(p)		mxs_bind_pos(__FILE__,__LINE__,p)
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
extern ELEMENT  mxs_patnpos(char*,int,ELEMENT);
#define patnpos(p)		mxs_patnpos(__FILE__,__LINE__,p)
extern ELEMENT  mxs_num_items(char*,int,ELEMENT);
#define num_items(p)		mxs_num_items(__FILE__,__LINE__,p)
extern ELEMENT  mxs_args(char*,int,ELEMENT);
#define args(p)		mxs_args(__FILE__,__LINE__,p)
extern ELEMENT  mxs_caseexpr(char*,int,ELEMENT);
#define caseexpr(p)		mxs_caseexpr(__FILE__,__LINE__,p)
extern ELEMENT  mxs_allexpr(char*,int,ELEMENT);
#define allexpr(p)		mxs_allexpr(__FILE__,__LINE__,p)
extern ELEMENT  mxs_encl_patterncase(char*,int,ELEMENT);
#define encl_patterncase(p)		mxs_encl_patterncase(__FILE__,__LINE__,p)
extern ELEMENT  mxs_top_pattern(char*,int,ELEMENT);
#define top_pattern(p)		mxs_top_pattern(__FILE__,__LINE__,p)
extern ELEMENT  mxs_son_nr(char*,int,ELEMENT);
#define son_nr(p)		mxs_son_nr(__FILE__,__LINE__,p)
extern ELEMENT  mxs_relacc_nr(char*,int,ELEMENT);
#define relacc_nr(p)		mxs_relacc_nr(__FILE__,__LINE__,p)
extern ELEMENT  mxs_appl_list_formula(char*,int,ELEMENT);
#define appl_list_formula(p)		mxs_appl_list_formula(__FILE__,__LINE__,p)
extern ELEMENT  mxs_appl_list_case(char*,int,ELEMENT);
#define appl_list_case(p)		mxs_appl_list_case(__FILE__,__LINE__,p)
extern ELEMENT  mxs_appl_list_expr(char*,int,ELEMENT);
#define appl_list_expr(p)		mxs_appl_list_expr(__FILE__,__LINE__,p)
extern ELEMENT  mxs_appl_list(char*,int,ELEMENT);
#define appl_list(p)		mxs_appl_list(__FILE__,__LINE__,p)
extern ELEMENT  mxs_def_value(char*,int,ELEMENT);
#define def_value(p)		mxs_def_value(__FILE__,__LINE__,p)
extern ELEMENT  mxs_node_parnr(char*,int,ELEMENT);
#define node_parnr(p)		mxs_node_parnr(__FILE__,__LINE__,p)
extern ELEMENT  mxs_appl_value(char*,int,ELEMENT);
#define appl_value(p)		mxs_appl_value(__FILE__,__LINE__,p)
extern ELEMENT  mxs_nodepar_expr(char*,int,ELEMENT);
#define nodepar_expr(p)		mxs_nodepar_expr(__FILE__,__LINE__,p)
extern ELEMENT  mxs_valueterm_list(char*,int,ELEMENT);
#define valueterm_list(p)		mxs_valueterm_list(__FILE__,__LINE__,p)
extern ELEMENT  mxs_valueterm(char*,int,ELEMENT);
#define valueterm(p)		mxs_valueterm(__FILE__,__LINE__,p)
extern ELEMENT  mxs_attr_list_matlist(char*,int,ELEMENT);
#define attr_list_matlist(p)		mxs_attr_list_matlist(__FILE__,__LINE__,p)
extern ELEMENT  mxs_result_value(char*,int,ELEMENT);
#define result_value(p)		mxs_result_value(__FILE__,__LINE__,p)
extern ELEMENT  mxs_is_relev_att_access(char*,int,ELEMENT);
#define is_relev_att_access(p)		mxs_is_relev_att_access(__FILE__,__LINE__,p)
extern ELEMENT  mxs_appl_order(char*,int,ELEMENT);
#define appl_order(p)		mxs_appl_order(__FILE__,__LINE__,p)
extern ELEMENT  mxs_appl_relacc_list(char*,int,ELEMENT);
#define appl_relacc_list(p)		mxs_appl_relacc_list(__FILE__,__LINE__,p)
extern ELEMENT  mxs_maybe_wait(char*,int,ELEMENT);
#define maybe_wait(p)		mxs_maybe_wait(__FILE__,__LINE__,p)
extern ELEMENT  mxs_cgen_name(char*,int,ELEMENT);
#define cgen_name(p)		mxs_cgen_name(__FILE__,__LINE__,p)
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
extern ELEMENT  mxs_sces_attacc(char*,int,ELEMENT);
#define sces_attacc(p)		mxs_sces_attacc(__FILE__,__LINE__,p)
extern ELEMENT  mxs_lokvar_need(char*,int,ELEMENT);
#define lokvar_need(p)		mxs_lokvar_need(__FILE__,__LINE__,p)
extern ELEMENT  mxs_intres_collect(char*,int,ELEMENT);
#define intres_collect(p)		mxs_intres_collect(__FILE__,__LINE__,p)

extern   void init_dyninput( void );
extern   void eval_dynsem( void );
extern   ELEMENT mxd_dummy;
#define SORTCONST_CL 0xE4
#define NODE_SORTCD  2
#define TERM_SORTCD -2

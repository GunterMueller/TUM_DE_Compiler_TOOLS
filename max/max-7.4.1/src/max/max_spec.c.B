/*=-= The following definitions up to the ***-line aren't relevant for  =-=*/
/*=-= users; they constitute the interface to  max_std                  =-=*/

typedef long         mxi_ELEMENT;
extern  long         mxi_conv_error;
extern  mxi_ELEMENT  mxi_btoe( char*, int, long );
extern  long         mxi_etob( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_ctoe( char*, int, char );
extern  char         mxi_etoc( char*, int, mxi_ELEMENT );
extern  mxi_ELEMENT  mxi_itoe( char*, int, long );
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
#define  mxs_etoc(f,l,CHARELEM)      mxi_etoc(f,l,CHARELEM)
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
#define  mxs_ListProd(f,l,P1,P2)		mxi_tc(f,l,"ListProd",2,-14,-42,P1,-147,P2)
#define  mxs_TupelProd(f,l,P1,P2)		mxi_tc(f,l,"TupelProd",2,-15,-42,P1,-91,P2)
#define  mxs_ClassProd(f,l,P1,P2)		mxi_tc(f,l,"ClassProd",2,-16,-42,P1,-91,P2)
#define  mxs_PredeclProd(f,l,P1)		mxi_tc(f,l,"PredeclProd",1,-17,-42,P1)
#define  mxs_PredDecl(f,l,P1,P2)		mxi_tc(f,l,"PredDecl",2,-18,-42,P1,-91,P2)
#define  mxs_FuncDecl(f,l,P1,P2,P3)		mxi_tc(f,l,"FuncDecl",3,-19,-42,P1,-91,P2,-147,P3)
#define  mxs_Structure(f,l,P1,P2,P3)		mxi_tc(f,l,"Structure",3,-20,-42,P1,-43,P2,-92,P3)
#define  mxs_Predicate(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"Predicate",4,-21,-42,P1,-91,P2,-101,P3,-141,P4)
#define  mxs_Function(f,l,P1,P2,P3,P4,P5)		mxi_tc(f,l,"Function",5,-22,-42,P1,-91,P2,-101,P3,-147,P4,-137,P5)
#define  mxs_Attribute(f,l,P1,P2,P3,P4,P5)		mxi_tc(f,l,"Attribute",5,-23,-42,P1,-91,P2,-101,P3,-147,P4,-137,P5)
#define  mxs_Condition(f,l,P1,P2,P3)		mxi_tc(f,l,"Condition",3,-24,-96,P1,-141,P2,-137,P3)
#define  mxs_AttrDecl(f,l,P1,P2,P3)		mxi_tc(f,l,"AttrDecl",3,-25,-42,P1,-91,P2,-147,P3)
#define  mxs_CharConst(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"CharConst",4,-26,-10,P1,-11,P2,-11,P3,-12,P4)
#define  mxs_IntConst(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"IntConst",4,-27,-11,P1,-11,P2,-11,P3,-12,P4)
#define  mxs_StringConst(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"StringConst",4,-28,-12,P1,-11,P2,-11,P3,-12,P4)
#define  mxs_SortConst(f,l,P1)		mxi_tc(f,l,"SortConst",1,-29,-147,P1)
#define  mxs_FuncAppl(f,l,P1,P2)		mxi_tc(f,l,"FuncAppl",2,-30,-45,P1,-97,P2)
#define  mxs_IfExpr(f,l,P1,P2,P3,P4,P5)		mxi_tc(f,l,"IfExpr",5,-31,-140,P1,-137,P2,-11,P3,-11,P4,-12,P5)
#define  mxs_LetExpr(f,l,P1,P2,P3)		mxi_tc(f,l,"LetExpr",3,-32,-46,P1,-137,P2,-137,P3)
#define  mxs_StringExpr(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"StringExpr",4,-33,-97,P1,-11,P2,-11,P3,-12,P4)
#define  mxs_PatternCase(f,l,P1,P2)		mxi_tc(f,l,"PatternCase",2,-34,-41,P1,-137,P2)
#define  mxs_FormulaCase(f,l,P1,P2)		mxi_tc(f,l,"FormulaCase",2,-35,-141,P1,-137,P2)
#define  mxs_PredAppl(f,l,P1,P2)		mxi_tc(f,l,"PredAppl",2,-36,-45,P1,-97,P2)
#define  mxs_Or(f,l,P1,P2)		mxi_tc(f,l,"Or",2,-37,-141,P1,-141,P2)
#define  mxs_And(f,l,P1,P2)		mxi_tc(f,l,"And",2,-38,-141,P1,-141,P2)
#define  mxs_Impl(f,l,P1,P2)		mxi_tc(f,l,"Impl",2,-39,-141,P1,-141,P2)
#define  mxs_Neg(f,l,P1)		mxi_tc(f,l,"Neg",1,-40,-141,P1)
#define  mxs_Pattern(f,l,P1,P2,P3)		mxi_tc(f,l,"Pattern",3,-41,-142,P1,-143,P2,-144,P3)
#define  mxs_DefId(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"DefId",4,-42,-8,P1,-11,P2,-11,P3,-12,P4)
#define  mxs_TermSortId(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"TermSortId",4,-43,-8,P1,-11,P2,-11,P3,-12,P4)
#define  mxs_NodeSortId(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"NodeSortId",4,-44,-8,P1,-11,P2,-11,P3,-12,P4)
#define  mxs_ApplId(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"ApplId",4,-45,-8,P1,-11,P2,-11,P3,-12,P4)
#define  mxs_Name(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"Name",4,-46,-8,P1,-11,P2,-11,P3,-12,P4)
#define  mxs_Blank(f,l,P1,P2)		mxi_tc(f,l,"Blank",2,-47,-11,P1,-12,P2)
#define  mxs_Asterisk(f,l)		 -536805424L
#define  mxs_ParTup(f,l,P1,P2)		mxi_tc(f,l,"ParTup",2,-49,-91,P1,-101,P2)
#define  mxs_NameDepthTup(f,l,P1,P2)		mxi_tc(f,l,"NameDepthTup",2,-50,46,P1,-11,P2)
#define  mxs_RelPosition(f,l,P1)		mxi_tc(f,l,"RelPosition",1,-51,-11,P1)
#define  mxs_AbsPosition(f,l,P1)		mxi_tc(f,l,"AbsPosition",1,-52,-11,P1)
#define  mxs_TopPosition(f,l)		 -536805429L
#define  mxs_Fath(f,l)		 -536805430L
#define  mxs_Lbroth(f,l,P1)		mxi_tc(f,l,"Lbroth",1,-55,-11,P1)
#define  mxs_Rbroth(f,l,P1)		mxi_tc(f,l,"Rbroth",1,-56,-11,P1)
#define  mxs_Son(f,l,P1)		mxi_tc(f,l,"Son",1,-57,-11,P1)
#define  mxs_SonTC(f,l,P1,P2,P3,P4,P5)		mxi_tc(f,l,"SonTC",5,-58,-11,P1,-11,P2,-11,P3,-11,P4,-11,P5)
#define  mxs_FClosure(f,l,P1)		mxi_tc(f,l,"FClosure",1,-59,-160,P1)
#define  mxs_TWson(f,l,P1)		mxi_tc(f,l,"TWson",1,-60,-11,P1)
#define  mxs_TWfath(f,l)		 -536805437L
#define  mxs_TWrbroth(f,l)		 -536805438L
#define  mxs_TWlbroth(f,l)		 -536805439L
#define  mxs_RelevAcc(f,l,P1)		mxi_tc(f,l,"RelevAcc",1,-64,-11,P1)
#define  mxs_AllNodes(f,l)		 -536805441L
#define  mxs_Parsnr(f,l,P1)		mxi_tc(f,l,"Parsnr",1,-66,-11,P1)
#define  mxs_Parsline(f,l)		 -536805443L
#define  mxs_Parscol(f,l)		 -536805444L
#define  mxs_Parspos(f,l)		 -536805445L
#define  mxs_Parsprio(f,l)		 -536805446L
#define  mxs_Parsrule(f,l,P1)		mxi_tc(f,l,"Parsrule",1,-71,-125,P1)
#define  mxs_Parsaddrule(f,l,P1)		mxi_tc(f,l,"Parsaddrule",1,-72,-125,P1)
#define  mxs_Parsno(f,l)		 -536805449L
#define  mxs_Parsleft(f,l)		 -536805450L
#define  mxs_Parsright(f,l)		 -536805451L
#define  mxs_Parsaux(f,l)		 -536805452L
#define  mxs_ParsStern(f,l,P1)		mxi_tc(f,l,"ParsStern",1,-77,-12,P1)
#define  mxs_ParsPlus(f,l,P1)		mxi_tc(f,l,"ParsPlus",1,-78,-12,P1)
#define  mxs_IdentTripel(f,l,P1,P2,P3)		mxi_tc(f,l,"IdentTripel",3,-79,-8,P1,-8,P2,-8,P3)
#define  mxs_CPinfo(f,l,P1,P2,P3)		mxi_tc(f,l,"CPinfo",3,-80,-125,P1,-147,P2,-125,P3)
#define  mxs_DynFunc(f,l,P1,P2,P3,P4,P5)		mxi_tc(f,l,"DynFunc",5,-81,-42,P1,-91,P2,-101,P3,-147,P4,-137,P5)
#define  mxs_IfRule(f,l,P1,P2,P3)		mxi_tc(f,l,"IfRule",3,-82,-141,P1,-130,P2,-130,P3)
#define  mxs_CaseRule(f,l,P1,P2,P3)		mxi_tc(f,l,"CaseRule",3,-83,-137,P1,-129,P2,-130,P3)
#define  mxs_CaseIs(f,l,P1,P2)		mxi_tc(f,l,"CaseIs",2,-84,-173,P1,-130,P2)
#define  mxs_Update(f,l,P1,P2)		mxi_tc(f,l,"Update",2,-85,-30,P1,-137,P2)
#define  mxs_DynUndef(f,l)		 -536805462L
#define  mxs_DynSemInput(f,l,P1,P2,P3)		mxi_tc(f,l,"DynSemInput",3,-87,-42,P1,-91,P2,-147,P3)
#define  mxs_CaseTripel(f,l,P1,P2,P3)		mxi_tc(f,l,"CaseTripel",3,-88,-102,P1,-102,P2,130,P3)
#define  mxs_Specification(f,l)		-536805465L
#define  mxs_ProdList(f,l)		-536805466L
#define  mxs_SortIdList(f,l)		-536805467L
#define  mxs_LocalDeclList(f,l)		-536805468L
#define  mxs_PredList(f,l)		-536805469L
#define  mxs_FuAtList(f,l)		-536805470L
#define  mxs_CondList(f,l)		-536805471L
#define  mxs_PatternList(f,l)		-536805472L
#define  mxs_ExprList(f,l)		-536805473L
#define  mxs_PatternCaseList(f,l)		-536805474L
#define  mxs_FormulaCaseList(f,l)		-536805475L
#define  mxs_ItemList(f,l)		-536805476L
#define  mxs_NameList(f,l)		-536805477L
#define  mxs_DefIdNodeList(f,l)		-536805478L
#define  mxs_CompExprNodeList(f,l)		-536805479L
#define  mxs_NameNList(f,l)		-536805480L
#define  mxs_ItemNList(f,l)		-536805481L
#define  mxs_Relationship(f,l)		-536805482L
#define  mxs_SortIdNList(f,l)		-536805483L
#define  mxs_ExprNList(f,l)		-536805484L
#define  mxs_OrValue(f,l)		-536805485L
#define  mxs_FList(f,l)		-536805486L
#define  mxs_ApplList(f,l)		-536805487L
#define  mxs_FuAtListInfo(f,l)		-536805488L
#define  mxs_FuAtNodeList(f,l)		-536805489L
#define  mxs_IntResList(f,l)		-536805490L
#define  mxs_IntList(f,l)		-536805491L
#define  mxs_RefList(f,l)		-536805492L
#define  mxs_ProdNodeList(f,l)		-536805493L
#define  mxs_IdentList(f,l)		-536805494L
#define  mxs_CharList(f,l)		-536805495L
#define  mxs_RsideInfo(f,l)		-536805496L
#define  mxs_RsideList(f,l)		-536805497L
#define  mxs_LsideList(f,l)		-536805498L
#define  mxs_LPinfoListlist(f,l)		-536805499L
#define  mxs_LPinfolist(f,l)		-536805500L
#define  mxs_StringList(f,l)		-536805501L
#define  mxs_CPinfoList(f,l)		-536805502L
#define  mxs_CPinfoListlist(f,l)		-536805503L
#define  mxs_RuleList(f,l)		-536805504L
#define  mxs_CaseIsList(f,l)		-536805505L
#define  mxs_UpdateList(f,l)		-536805506L
#define  mxs_UListNodeList(f,l)		-536805507L
#define  mxs_CaseTripelList(f,l)		-536805508L

extern   void init_dyninput( void );
extern   void eval_dynsem( void );
extern   ELEMENT mxd_dummy;
#define SORTCONST_CL 0xE4
#define NODE_SORTCD  2
#define TERM_SORTCD -2

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
extern mxi_ELEMENT mxi_string_conc( char*, int, long,...);
static mxi_ELEMENT mxv_errstr;
FILE *errfile = stderr;
extern void mxi_prterrm(char*,int,char*,char*);
static char mxi_errmstr[] = "0th parameter is of wrong sort";
void comp_errm(char *filenm, int ln, char *fctnm, int parno){
	mxi_errmstr[0] = (char)(parno)+'0';
	mxi_prterrm(filenm,ln,fctnm,mxi_errmstr);
}

static  char *_c = "max_spec.c";
static  char *_m = "max_spec.m";
#define SORTCDT  short
#define MAXUNDEF -335544320L
#define IFNIL(e) {if(e==mxs_nil(_c,0)) return mxs_nil(_c,0);}
#define IS(e,t,f,l,fct,i)  {if(!mxs_is(_c,0,e,t)){comp_errm(f,l,fct,i);return mxs_nil(_c,0);}}
#define ISORNIL(e,t,f,l,fct,i)  {if(!mxs_is(_c,0,e,t)&&e!=mxs_nil(_c,0)){comp_errm(f,l,fct,i);return mxs_nil(_c,0);}}


typedef void (*EVALFCT1)( ELEMENT );
typedef void (*EVALFCT)( ELEMENT, ELEMENT, int, ELEMENT * );
typedef struct AttInstElem{
	EVALFCT attevalfct;
	ELEMENT  attnode;
	struct AttInstElem *rest;
	int state;
	ELEMENT intres_array[2];
} *AttInstSq;

long waitlist_count = 0;
static ELEMENT *insAttInst( EVALFCT attevalfct, ELEMENT attnode, int state,
	AttInstSq* undefatt, long undefattix ) {
	AttInstSq  waitlist  = (AttInstSq) malloc( sizeof(struct AttInstElem) );
	waitlist_count++;
	if( waitlist == 0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate wait list element\n");
		exit( EXIT_FAILURE );
	}
	waitlist->attevalfct = attevalfct;
	waitlist->attnode    = attnode;
	waitlist->state      = state;
	waitlist->rest       = undefatt[undefattix];
	undefatt[undefattix] = waitlist;
return &waitlist->intres_array[0];
}

SORTCDT   mxi_tupel_sortcd_lb  = -88;
SORTCDT   mxi_list_sortcd_lb   = -132;
SORTCDT   mxi_class_sortcd_lb  = -174;


static  SORTCDT  mxi_auxlisttoelemtab[45] = {
-88,130,-174,-84,-172,-126,-80,-12,-171,-124,-170,-120,-169,-10,-8,135,-13,-11,168,162,-113,30,-160,-160,137,147,-157,145,46,139,42,-46,-145,-35,-34,-137,-41,-24,-162,-21,-136,-147,-135,-134,0};

SORTCDT  *mxi_listtoelemtab = mxi_auxlisttoelemtab+132;


static  SORTCDT subsort_133[] = {2,1,-2,0};
static  SORTCDT subsort_134[] = {-18,-19,-20,-90,-128,0};
static  SORTCDT subsort_135[] = {-14,-15,-16,-17,0};
static  SORTCDT subsort_136[] = {-18,-19,-25,-81,-87,-93,-94,-95,0};
static  SORTCDT subsort_137[] = {-26,-27,-28,-29,-30,-31,-32,-33,-46,-86,0};
static  SORTCDT subsort_138[] = {-26,-27,-28,-29,0};
static  SORTCDT subsort_139[] = {-31,-32,0};
static  SORTCDT subsort_140[] = {-98,-99,0};
static  SORTCDT subsort_141[] = {-36,-37,-38,-39,-40,0};
static  SORTCDT subsort_142[] = {-43,-44,-47,0};
static  SORTCDT subsort_143[] = {-47,-100,0};
static  SORTCDT subsort_144[] = {-46,-47,0};
static  SORTCDT subsort_145[] = {-41,-47,-48,0};
static  SORTCDT subsort_146[] = {-43,-44,-45,0};
static  SORTCDT subsort_147[] = {-43,-44,0};
static  SORTCDT subsort_148[] = {-18,-19,-25,0};
static  SORTCDT subsort_149[] = {-14,-15,-16,-17,-21,-22,-23,0};
static  SORTCDT subsort_150[] = {-21,-22,-23,0};
static  SORTCDT subsort_151[] = {-21,-22,-23,-81,-87,0};
static  SORTCDT subsort_152[] = {-21,-22,-23,-24,-32,-34,-81,-87,0};
static  SORTCDT subsort_153[] = {-13,0};
static  SORTCDT subsort_154[] = {-21,-22,-23,-24,-31,-32,-81,-87,0};
static  SORTCDT subsort_155[] = {-34,-35,0};
static  SORTCDT subsort_156[] = {-51,-52,-53,0};
static  SORTCDT subsort_157[] = {-54,-55,-56,-57,-58,0};
static  SORTCDT subsort_158[] = {-13,0};
static  SORTCDT subsort_159[] = {-34,-35,0};
static  SORTCDT subsort_160[] = {42,-59,-60,-61,-62,-63,-64,-109,-110,0};
static  SORTCDT subsort_161[] = {42,-60,-61,-62,-63,-64,0};
static  SORTCDT subsort_162[] = {-22,-23,0};
static  SORTCDT subsort_163[] = {-19,-22,-23,-25,0};
static  SORTCDT subsort_164[] = {-11,0};
static  SORTCDT subsort_165[] = {-37,-38,-39,0};
static  SORTCDT subsort_166[] = {-65,-102,0};
static  SORTCDT subsort_167[] = {-21,-22,-23,-24,-30,-31,-32,-81,-87,0};
static  SORTCDT subsort_168[] = {-21,-22,-23,-24,-30,-31,-32,-46,-81,-87,0};
static  SORTCDT subsort_169[] = {-12,-43,-44,-66,-67,-68,-69,0};
static  SORTCDT subsort_170[] = {-11,-70,-71,-72,-73,-74,-75,-76,0};
static  SORTCDT subsort_171[] = {-77,-78,0};
static  SORTCDT subsort_172[] = {-82,-83,0};
static  SORTCDT subsort_173[] = {-26,-27,-29,0};
static  SORTCDT subsort_174[] = {-82,-83,-85,0};

static  SORTCDT  *mxi_auxclasstosorttab[43] = { 0L,
subsort_174,subsort_173,subsort_172,subsort_171,subsort_170,
subsort_169,subsort_168,subsort_167,subsort_166,subsort_165,
subsort_164,subsort_163,subsort_162,subsort_161,subsort_160,
subsort_159,subsort_158,subsort_157,subsort_156,subsort_155,
subsort_154,subsort_153,subsort_152,subsort_151,subsort_150,
subsort_149,subsort_148,subsort_147,subsort_146,subsort_145,
subsort_144,subsort_143,subsort_142,subsort_141,subsort_140,
subsort_139,subsort_138,subsort_137,subsort_136,subsort_135,
subsort_134,subsort_133,};

SORTCDT  **mxi_classtosorttab = mxi_auxclasstosorttab+175;


static  SORTCDT supsort_132[] = {-133,-2,0};
static  SORTCDT supsort_131[] = {-133,-2,0};
static  SORTCDT supsort_130[] = {-133,-2,0};
static  SORTCDT supsort_129[] = {-133,-2,0};
static  SORTCDT supsort_128[] = {-134,-133,-2,0};
static  SORTCDT supsort_127[] = {-133,-2,0};
static  SORTCDT supsort_126[] = {-133,-2,0};
static  SORTCDT supsort_125[] = {-133,-2,0};
static  SORTCDT supsort_124[] = {-133,-2,0};
static  SORTCDT supsort_123[] = {-133,-2,0};
static  SORTCDT supsort_122[] = {-133,-2,0};
static  SORTCDT supsort_121[] = {-133,-2,0};
static  SORTCDT supsort_120[] = {-133,-2,0};
static  SORTCDT supsort_119[] = {-133,-2,0};
static  SORTCDT supsort_118[] = {-133,-2,0};
static  SORTCDT supsort_117[] = {-133,-2,0};
static  SORTCDT supsort_116[] = {-133,-2,0};
static  SORTCDT supsort_115[] = {-133,-2,0};
static  SORTCDT supsort_114[] = {-133,-2,0};
static  SORTCDT supsort_113[] = {-133,-2,0};
static  SORTCDT supsort_112[] = {-133,-2,0};
static  SORTCDT supsort_111[] = {-133,-2,0};
static  SORTCDT supsort_110[] = {-160,-133,-2,0};
static  SORTCDT supsort_109[] = {-160,-133,-2,0};
static  SORTCDT supsort_108[] = {-133,-2,0};
static  SORTCDT supsort_107[] = {-133,-2,0};
static  SORTCDT supsort_106[] = {-133,-2,0};
static  SORTCDT supsort_105[] = {-133,-2,0};
static  SORTCDT supsort_104[] = {-133,-2,0};
static  SORTCDT supsort_103[] = {-133,-2,0};
static  SORTCDT supsort_102[] = {-166,-133,-2,0};
static  SORTCDT supsort_101[] = {-133,-2,0};
static  SORTCDT supsort_100[] = {-143,-133,-2,0};
static  SORTCDT supsort_99[] = {-140,-133,-2,0};
static  SORTCDT supsort_98[] = {-140,-133,-2,0};
static  SORTCDT supsort_97[] = {-133,-2,0};
static  SORTCDT supsort_96[] = {-133,-2,0};
static  SORTCDT supsort_95[] = {-136,-133,-2,0};
static  SORTCDT supsort_94[] = {-136,-133,-2,0};
static  SORTCDT supsort_93[] = {-136,-133,-2,0};
static  SORTCDT supsort_92[] = {-133,-2,0};
static  SORTCDT supsort_91[] = {-133,-2,0};
static  SORTCDT supsort_90[] = {-134,-133,-2,0};
static  SORTCDT supsort_89[] = {-133,-2,0};
static  SORTCDT supsort_88[] = {-133,-2,0};
static  SORTCDT supsort_87[] = {-168,-167,-154,-152,-151,-136,-133,-2,0};
static  SORTCDT supsort_86[] = {-137,-133,-2,0};
static  SORTCDT supsort_85[] = {-174,-133,-2,0};
static  SORTCDT supsort_84[] = {-133,-2,0};
static  SORTCDT supsort_83[] = {-174,-172,-133,-2,0};
static  SORTCDT supsort_82[] = {-174,-172,-133,-2,0};
static  SORTCDT supsort_81[] = {-168,-167,-154,-152,-151,-136,-133,-2,0};
static  SORTCDT supsort_80[] = {-133,-2,0};
static  SORTCDT supsort_79[] = {-133,-2,0};
static  SORTCDT supsort_78[] = {-171,-133,-2,0};
static  SORTCDT supsort_77[] = {-171,-133,-2,0};
static  SORTCDT supsort_76[] = {-170,-133,-2,0};
static  SORTCDT supsort_75[] = {-170,-133,-2,0};
static  SORTCDT supsort_74[] = {-170,-133,-2,0};
static  SORTCDT supsort_73[] = {-170,-133,-2,0};
static  SORTCDT supsort_72[] = {-170,-133,-2,0};
static  SORTCDT supsort_71[] = {-170,-133,-2,0};
static  SORTCDT supsort_70[] = {-170,-133,-2,0};
static  SORTCDT supsort_69[] = {-169,-133,-2,0};
static  SORTCDT supsort_68[] = {-169,-133,-2,0};
static  SORTCDT supsort_67[] = {-169,-133,-2,0};
static  SORTCDT supsort_66[] = {-169,-133,-2,0};
static  SORTCDT supsort_65[] = {-166,-133,-2,0};
static  SORTCDT supsort_64[] = {-161,-160,-133,-2,0};
static  SORTCDT supsort_63[] = {-161,-160,-133,-2,0};
static  SORTCDT supsort_62[] = {-161,-160,-133,-2,0};
static  SORTCDT supsort_61[] = {-161,-160,-133,-2,0};
static  SORTCDT supsort_60[] = {-161,-160,-133,-2,0};
static  SORTCDT supsort_59[] = {-160,-133,-2,0};
static  SORTCDT supsort_58[] = {-157,-133,-2,0};
static  SORTCDT supsort_57[] = {-157,-133,-2,0};
static  SORTCDT supsort_56[] = {-157,-133,-2,0};
static  SORTCDT supsort_55[] = {-157,-133,-2,0};
static  SORTCDT supsort_54[] = {-157,-133,-2,0};
static  SORTCDT supsort_53[] = {-156,-133,-2,0};
static  SORTCDT supsort_52[] = {-156,-133,-2,0};
static  SORTCDT supsort_51[] = {-156,-133,-2,0};
static  SORTCDT supsort_50[] = {-133,-2,0};
static  SORTCDT supsort_49[] = {-133,-2,0};
static  SORTCDT supsort_48[] = {-145,-133,-2,0};
static  SORTCDT supsort_47[] = {-145,-144,-143,-142,-133,-2,0};
static  SORTCDT supsort_46[] = {-168,-144,-137,-133,-2,0};
static  SORTCDT supsort_45[] = {-146,-133,-2,0};
static  SORTCDT supsort_44[] = {-169,-147,-146,-142,-133,-2,0};
static  SORTCDT supsort_43[] = {-169,-147,-146,-142,-133,-2,0};
static  SORTCDT supsort_42[] = {-133,-2,0};
static  SORTCDT supsort_41[] = {-145,-133,-2,0};
static  SORTCDT supsort_40[] = {-141,-133,-2,0};
static  SORTCDT supsort_39[] = {-165,-141,-133,-2,0};
static  SORTCDT supsort_38[] = {-165,-141,-133,-2,0};
static  SORTCDT supsort_37[] = {-165,-141,-133,-2,0};
static  SORTCDT supsort_36[] = {-141,-133,-2,0};
static  SORTCDT supsort_35[] = {-159,-155,-133,-2,0};
static  SORTCDT supsort_34[] = {-159,-155,-152,-133,-2,0};
static  SORTCDT supsort_33[] = {-137,-133,-2,0};
static  SORTCDT supsort_32[] = {-168,-167,-154,-152,-139,-137,-133,-2,0};
static  SORTCDT supsort_31[] = {-168,-167,-154,-139,-137,-133,-2,0};
static  SORTCDT supsort_30[] = {-168,-167,-137,-133,-2,0};
static  SORTCDT supsort_29[] = {-173,-138,-137,-133,-2,0};
static  SORTCDT supsort_28[] = {-138,-137,-133,-2,0};
static  SORTCDT supsort_27[] = {-173,-138,-137,-133,-2,0};
static  SORTCDT supsort_26[] = {-173,-138,-137,-133,-2,0};
static  SORTCDT supsort_25[] = {-163,-148,-136,-133,-2,0};
static  SORTCDT supsort_24[] = {-168,-167,-154,-152,-133,-2,0};
static  SORTCDT supsort_23[] = {-168,-167,-163,-162,-154,-152,-151,-150,-149,-133,-2,0};
static  SORTCDT supsort_22[] = {-168,-167,-163,-162,-154,-152,-151,-150,-149,-133,-2,0};
static  SORTCDT supsort_21[] = {-168,-167,-154,-152,-151,-150,-149,-133,-2,0};
static  SORTCDT supsort_20[] = {-134,-133,-2,0};
static  SORTCDT supsort_19[] = {-163,-148,-136,-134,-133,-2,0};
static  SORTCDT supsort_18[] = {-148,-136,-134,-133,-2,0};
static  SORTCDT supsort_17[] = {-149,-135,-133,-2,0};
static  SORTCDT supsort_16[] = {-149,-135,-133,-2,0};
static  SORTCDT supsort_15[] = {-149,-135,-133,-2,0};
static  SORTCDT supsort_14[] = {-149,-135,-133,-2,0};
static  SORTCDT supsort_13[] = {-158,-153,-133,-2,0};
static  SORTCDT supsort_12[] = {-169,-133,-2,0};
static  SORTCDT supsort_11[] = {-170,-164,-133,-2,0};
static  SORTCDT supsort_10[] = {-133,-2,0};
static  SORTCDT supsort_9[] = {-133,-2,0};
static  SORTCDT supsort_8[] = {-133,-2,0};
static  SORTCDT supsort_7[] = {-133,-2,0};
static  SORTCDT supsort_6[] = {-133,-2,0};
static  SORTCDT supsort_5[] = {-133,-2,0};
static  SORTCDT supsort_4[] = {-133,-2,0};
static  SORTCDT supsort_3[] = {-133,-2,0};
static  SORTCDT supsort_2[] = {0};
static  SORTCDT supsort_1[] = {0};
static  SORTCDT supsort0[] = {0};
static  SORTCDT supsort1[] = {-133,0};
static  SORTCDT supsort2[] = {0};
static  SORTCDT supsort3[] = {133,-133,2,0};
static  SORTCDT supsort4[] = {133,-133,2,0};
static  SORTCDT supsort5[] = {133,-133,2,0};
static  SORTCDT supsort6[] = {133,-133,2,0};
static  SORTCDT supsort7[] = {133,-133,2,0};
static  SORTCDT supsort8[] = {133,-133,2,0};
static  SORTCDT supsort9[] = {133,-133,2,0};
static  SORTCDT supsort10[] = {133,-133,2,0};
static  SORTCDT supsort11[] = {170,164,133,-133,2,0};
static  SORTCDT supsort12[] = {169,133,-133,2,0};
static  SORTCDT supsort13[] = {158,153,133,-133,2,0};
static  SORTCDT supsort14[] = {149,135,133,-133,2,0};
static  SORTCDT supsort15[] = {149,135,133,-133,2,0};
static  SORTCDT supsort16[] = {149,135,133,-133,2,0};
static  SORTCDT supsort17[] = {149,135,133,-133,2,0};
static  SORTCDT supsort18[] = {148,136,134,133,-133,2,0};
static  SORTCDT supsort19[] = {163,148,136,134,133,-133,2,0};
static  SORTCDT supsort20[] = {134,133,-133,2,0};
static  SORTCDT supsort21[] = {168,167,154,152,151,150,149,133,-133,2,0};
static  SORTCDT supsort22[] = {168,167,163,162,154,152,151,150,149,133,-133,2,0};
static  SORTCDT supsort23[] = {168,167,163,162,154,152,151,150,149,133,-133,2,0};
static  SORTCDT supsort24[] = {168,167,154,152,133,-133,2,0};
static  SORTCDT supsort25[] = {163,148,136,133,-133,2,0};
static  SORTCDT supsort26[] = {173,138,137,133,-133,2,0};
static  SORTCDT supsort27[] = {173,138,137,133,-133,2,0};
static  SORTCDT supsort28[] = {138,137,133,-133,2,0};
static  SORTCDT supsort29[] = {173,138,137,133,-133,2,0};
static  SORTCDT supsort30[] = {168,167,137,133,-133,2,0};
static  SORTCDT supsort31[] = {168,167,154,139,137,133,-133,2,0};
static  SORTCDT supsort32[] = {168,167,154,152,139,137,133,-133,2,0};
static  SORTCDT supsort33[] = {137,133,-133,2,0};
static  SORTCDT supsort34[] = {159,155,152,133,-133,2,0};
static  SORTCDT supsort35[] = {159,155,133,-133,2,0};
static  SORTCDT supsort36[] = {141,133,-133,2,0};
static  SORTCDT supsort37[] = {165,141,133,-133,2,0};
static  SORTCDT supsort38[] = {165,141,133,-133,2,0};
static  SORTCDT supsort39[] = {165,141,133,-133,2,0};
static  SORTCDT supsort40[] = {141,133,-133,2,0};
static  SORTCDT supsort41[] = {145,133,-133,2,0};
static  SORTCDT supsort42[] = {-161,-160,133,-133,2,0};
static  SORTCDT supsort43[] = {169,147,146,142,133,-133,2,0};
static  SORTCDT supsort44[] = {169,147,146,142,133,-133,2,0};
static  SORTCDT supsort45[] = {146,133,-133,2,0};
static  SORTCDT supsort46[] = {168,144,137,133,-133,2,0};
static  SORTCDT supsort47[] = {145,144,143,142,133,-133,2,0};
static  SORTCDT supsort48[] = {145,133,-133,2,0};
static  SORTCDT supsort49[] = {133,-133,2,0};
static  SORTCDT supsort50[] = {133,-133,2,0};
static  SORTCDT supsort51[] = {156,133,-133,2,0};
static  SORTCDT supsort52[] = {156,133,-133,2,0};
static  SORTCDT supsort53[] = {156,133,-133,2,0};
static  SORTCDT supsort54[] = {157,133,-133,2,0};
static  SORTCDT supsort55[] = {157,133,-133,2,0};
static  SORTCDT supsort56[] = {157,133,-133,2,0};
static  SORTCDT supsort57[] = {157,133,-133,2,0};
static  SORTCDT supsort58[] = {157,133,-133,2,0};
static  SORTCDT supsort59[] = {160,133,-133,2,0};
static  SORTCDT supsort60[] = {161,160,133,-133,2,0};
static  SORTCDT supsort61[] = {161,160,133,-133,2,0};
static  SORTCDT supsort62[] = {161,160,133,-133,2,0};
static  SORTCDT supsort63[] = {161,160,133,-133,2,0};
static  SORTCDT supsort64[] = {161,160,133,-133,2,0};
static  SORTCDT supsort65[] = {166,133,-133,2,0};
static  SORTCDT supsort66[] = {169,133,-133,2,0};
static  SORTCDT supsort67[] = {169,133,-133,2,0};
static  SORTCDT supsort68[] = {169,133,-133,2,0};
static  SORTCDT supsort69[] = {169,133,-133,2,0};
static  SORTCDT supsort70[] = {170,133,-133,2,0};
static  SORTCDT supsort71[] = {170,133,-133,2,0};
static  SORTCDT supsort72[] = {170,133,-133,2,0};
static  SORTCDT supsort73[] = {170,133,-133,2,0};
static  SORTCDT supsort74[] = {170,133,-133,2,0};
static  SORTCDT supsort75[] = {170,133,-133,2,0};
static  SORTCDT supsort76[] = {170,133,-133,2,0};
static  SORTCDT supsort77[] = {171,133,-133,2,0};
static  SORTCDT supsort78[] = {171,133,-133,2,0};
static  SORTCDT supsort79[] = {133,-133,2,0};
static  SORTCDT supsort80[] = {133,-133,2,0};
static  SORTCDT supsort81[] = {168,167,154,152,151,136,133,-133,2,0};
static  SORTCDT supsort82[] = {174,172,133,-133,2,0};
static  SORTCDT supsort83[] = {174,172,133,-133,2,0};
static  SORTCDT supsort84[] = {133,-133,2,0};
static  SORTCDT supsort85[] = {174,133,-133,2,0};
static  SORTCDT supsort86[] = {137,133,-133,2,0};
static  SORTCDT supsort87[] = {168,167,154,152,151,136,133,-133,2,0};
static  SORTCDT supsort88[] = {133,-133,2,0};
static  SORTCDT supsort89[] = {133,-133,2,0};
static  SORTCDT supsort90[] = {134,133,-133,2,0};
static  SORTCDT supsort91[] = {133,-133,2,0};
static  SORTCDT supsort92[] = {133,-133,2,0};
static  SORTCDT supsort93[] = {136,133,-133,2,0};
static  SORTCDT supsort94[] = {136,133,-133,2,0};
static  SORTCDT supsort95[] = {136,133,-133,2,0};
static  SORTCDT supsort96[] = {133,-133,2,0};
static  SORTCDT supsort97[] = {133,-133,2,0};
static  SORTCDT supsort98[] = {140,133,-133,2,0};
static  SORTCDT supsort99[] = {140,133,-133,2,0};
static  SORTCDT supsort100[] = {143,133,-133,2,0};
static  SORTCDT supsort101[] = {133,-133,2,0};
static  SORTCDT supsort102[] = {166,133,-133,2,0};
static  SORTCDT supsort103[] = {133,-133,2,0};
static  SORTCDT supsort104[] = {133,-133,2,0};
static  SORTCDT supsort105[] = {133,-133,2,0};
static  SORTCDT supsort106[] = {133,-133,2,0};
static  SORTCDT supsort107[] = {133,-133,2,0};
static  SORTCDT supsort108[] = {133,-133,2,0};
static  SORTCDT supsort109[] = {160,133,-133,2,0};
static  SORTCDT supsort110[] = {160,133,-133,2,0};
static  SORTCDT supsort111[] = {133,-133,2,0};
static  SORTCDT supsort112[] = {133,-133,2,0};
static  SORTCDT supsort113[] = {133,-133,2,0};
static  SORTCDT supsort114[] = {133,-133,2,0};
static  SORTCDT supsort115[] = {133,-133,2,0};
static  SORTCDT supsort116[] = {133,-133,2,0};
static  SORTCDT supsort117[] = {133,-133,2,0};
static  SORTCDT supsort118[] = {133,-133,2,0};
static  SORTCDT supsort119[] = {133,-133,2,0};
static  SORTCDT supsort120[] = {133,-133,2,0};
static  SORTCDT supsort121[] = {133,-133,2,0};
static  SORTCDT supsort122[] = {133,-133,2,0};
static  SORTCDT supsort123[] = {133,-133,2,0};
static  SORTCDT supsort124[] = {133,-133,2,0};
static  SORTCDT supsort125[] = {133,-133,2,0};
static  SORTCDT supsort126[] = {133,-133,2,0};
static  SORTCDT supsort127[] = {133,-133,2,0};
static  SORTCDT supsort128[] = {134,133,-133,2,0};
static  SORTCDT supsort129[] = {133,-133,2,0};
static  SORTCDT supsort130[] = {133,-133,2,0};
static  SORTCDT supsort131[] = {133,-133,2,0};
static  SORTCDT supsort132[] = {133,-133,2,0};

static  SORTCDT  *mxi_auxsupsorttab[265] = {
supsort_132,supsort_131,supsort_130,supsort_129,supsort_128,
supsort_127,supsort_126,supsort_125,supsort_124,supsort_123,
supsort_122,supsort_121,supsort_120,supsort_119,supsort_118,
supsort_117,supsort_116,supsort_115,supsort_114,supsort_113,
supsort_112,supsort_111,supsort_110,supsort_109,supsort_108,
supsort_107,supsort_106,supsort_105,supsort_104,supsort_103,
supsort_102,supsort_101,supsort_100,supsort_99,supsort_98,
supsort_97,supsort_96,supsort_95,supsort_94,supsort_93,
supsort_92,supsort_91,supsort_90,supsort_89,supsort_88,
supsort_87,supsort_86,supsort_85,supsort_84,supsort_83,
supsort_82,supsort_81,supsort_80,supsort_79,supsort_78,
supsort_77,supsort_76,supsort_75,supsort_74,supsort_73,
supsort_72,supsort_71,supsort_70,supsort_69,supsort_68,
supsort_67,supsort_66,supsort_65,supsort_64,supsort_63,
supsort_62,supsort_61,supsort_60,supsort_59,supsort_58,
supsort_57,supsort_56,supsort_55,supsort_54,supsort_53,
supsort_52,supsort_51,supsort_50,supsort_49,supsort_48,
supsort_47,supsort_46,supsort_45,supsort_44,supsort_43,
supsort_42,supsort_41,supsort_40,supsort_39,supsort_38,
supsort_37,supsort_36,supsort_35,supsort_34,supsort_33,
supsort_32,supsort_31,supsort_30,supsort_29,supsort_28,
supsort_27,supsort_26,supsort_25,supsort_24,supsort_23,
supsort_22,supsort_21,supsort_20,supsort_19,supsort_18,
supsort_17,supsort_16,supsort_15,supsort_14,supsort_13,
supsort_12,supsort_11,supsort_10,supsort_9,supsort_8,
supsort_7,supsort_6,supsort_5,supsort_4,supsort_3,
supsort_2,supsort_1,supsort0,supsort1,supsort2,
supsort3,supsort4,supsort5,supsort6,supsort7,
supsort8,supsort9,supsort10,supsort11,supsort12,
supsort13,supsort14,supsort15,supsort16,supsort17,
supsort18,supsort19,supsort20,supsort21,supsort22,
supsort23,supsort24,supsort25,supsort26,supsort27,
supsort28,supsort29,supsort30,supsort31,supsort32,
supsort33,supsort34,supsort35,supsort36,supsort37,
supsort38,supsort39,supsort40,supsort41,supsort42,
supsort43,supsort44,supsort45,supsort46,supsort47,
supsort48,supsort49,supsort50,supsort51,supsort52,
supsort53,supsort54,supsort55,supsort56,supsort57,
supsort58,supsort59,supsort60,supsort61,supsort62,
supsort63,supsort64,supsort65,supsort66,supsort67,
supsort68,supsort69,supsort70,supsort71,supsort72,
supsort73,supsort74,supsort75,supsort76,supsort77,
supsort78,supsort79,supsort80,supsort81,supsort82,
supsort83,supsort84,supsort85,supsort86,supsort87,
supsort88,supsort89,supsort90,supsort91,supsort92,
supsort93,supsort94,supsort95,supsort96,supsort97,
supsort98,supsort99,supsort100,supsort101,supsort102,
supsort103,supsort104,supsort105,supsort106,supsort107,
supsort108,supsort109,supsort110,supsort111,supsort112,
supsort113,supsort114,supsort115,supsort116,supsort117,
supsort118,supsort119,supsort120,supsort121,supsort122,
supsort123,supsort124,supsort125,supsort126,supsort127,
supsort128,supsort129,supsort130,supsort131,supsort132,
};

SORTCDT  **mxi_supsorttab = mxi_auxsupsorttab+132;


static  long  mxi_auxnumbertab[183];
long  *mxi_numbertab =  mxi_auxnumbertab+8;

long  mxi_offsettab[133];

typedef  struct{
			short  ccd;
			long   offs;
		}  ScdOffsPair;

static  ScdOffsPair  cop3[] = {{133,0L},};
static  ScdOffsPair  cop4[] = {{133,0L},};
static  ScdOffsPair  cop5[] = {{133,0L},};
static  ScdOffsPair  cop6[] = {{133,0L},};
static  ScdOffsPair  cop7[] = {{133,0L},};
static  ScdOffsPair  cop8[] = {{133,0L},};
static  ScdOffsPair  cop9[] = {{133,0L},};
static  ScdOffsPair  cop10[] = {{133,0L},};
static  ScdOffsPair  cop11[] = {{170,0L},{164,0L},{133,0L},};
static  ScdOffsPair  cop12[] = {{169,0L},{133,0L},};
static  ScdOffsPair  cop13[] = {{158,0L},{153,0L},{133,0L},};
static  ScdOffsPair  cop14[] = {{149,0L},{135,0L},{133,0L},};
static  ScdOffsPair  cop15[] = {{149,0L},{135,0L},{133,0L},};
static  ScdOffsPair  cop16[] = {{149,0L},{135,0L},{133,0L},};
static  ScdOffsPair  cop17[] = {{149,0L},{135,0L},{133,0L},};
static  ScdOffsPair  cop18[] = {{148,0L},{136,0L},{134,0L},{133,0L},};
static  ScdOffsPair  cop19[] = {{163,0L},{148,0L},{136,0L},{134,0L},{133,0L},};
static  ScdOffsPair  cop20[] = {{134,0L},{133,0L},};
static  ScdOffsPair  cop21[] = {{168,0L},{167,0L},{154,0L},{152,0L},{151,0L},{150,0L},{149,0L},{133,0L},};
static  ScdOffsPair  cop22[] = {{168,0L},{167,0L},{163,0L},{162,0L},{154,0L},{152,0L},{151,0L},{150,0L},{149,0L},{133,0L},};
static  ScdOffsPair  cop23[] = {{168,0L},{167,0L},{163,0L},{162,0L},{154,0L},{152,0L},{151,0L},{150,0L},{149,0L},{133,0L},};
static  ScdOffsPair  cop24[] = {{168,0L},{167,0L},{154,0L},{152,0L},{133,0L},};
static  ScdOffsPair  cop25[] = {{163,0L},{148,0L},{136,0L},{133,0L},};
static  ScdOffsPair  cop26[] = {{173,0L},{138,0L},{137,0L},{133,0L},};
static  ScdOffsPair  cop27[] = {{173,0L},{138,0L},{137,0L},{133,0L},};
static  ScdOffsPair  cop28[] = {{138,0L},{137,0L},{133,0L},};
static  ScdOffsPair  cop29[] = {{173,0L},{138,0L},{137,0L},{133,0L},};
static  ScdOffsPair  cop30[] = {{168,0L},{167,0L},{137,0L},{133,0L},};
static  ScdOffsPair  cop31[] = {{168,0L},{167,0L},{154,0L},{139,0L},{137,0L},{133,0L},};
static  ScdOffsPair  cop32[] = {{168,0L},{167,0L},{154,0L},{152,0L},{139,0L},{137,0L},{133,0L},};
static  ScdOffsPair  cop33[] = {{137,0L},{133,0L},};
static  ScdOffsPair  cop34[] = {{159,0L},{155,0L},{152,0L},{133,0L},};
static  ScdOffsPair  cop35[] = {{159,0L},{155,0L},{133,0L},};
static  ScdOffsPair  cop36[] = {{141,0L},{133,0L},};
static  ScdOffsPair  cop37[] = {{165,0L},{141,0L},{133,0L},};
static  ScdOffsPair  cop38[] = {{165,0L},{141,0L},{133,0L},};
static  ScdOffsPair  cop39[] = {{165,0L},{141,0L},{133,0L},};
static  ScdOffsPair  cop40[] = {{141,0L},{133,0L},};
static  ScdOffsPair  cop41[] = {{145,0L},{133,0L},};
static  ScdOffsPair  cop42[] = {{133,0L},};
static  ScdOffsPair  cop43[] = {{169,0L},{147,0L},{146,0L},{142,0L},{133,0L},};
static  ScdOffsPair  cop44[] = {{169,0L},{147,0L},{146,0L},{142,0L},{133,0L},};
static  ScdOffsPair  cop45[] = {{146,0L},{133,0L},};
static  ScdOffsPair  cop46[] = {{168,0L},{144,0L},{137,0L},{133,0L},};
static  ScdOffsPair  cop47[] = {{145,0L},{144,0L},{143,0L},{142,0L},{133,0L},};
static  ScdOffsPair  cop48[] = {{145,0L},{133,0L},};
static  ScdOffsPair  cop49[] = {{133,0L},};
static  ScdOffsPair  cop50[] = {{133,0L},};
static  ScdOffsPair  cop51[] = {{156,0L},{133,0L},};
static  ScdOffsPair  cop52[] = {{156,0L},{133,0L},};
static  ScdOffsPair  cop53[] = {{156,0L},{133,0L},};
static  ScdOffsPair  cop54[] = {{157,0L},{133,0L},};
static  ScdOffsPair  cop55[] = {{157,0L},{133,0L},};
static  ScdOffsPair  cop56[] = {{157,0L},{133,0L},};
static  ScdOffsPair  cop57[] = {{157,0L},{133,0L},};
static  ScdOffsPair  cop58[] = {{157,0L},{133,0L},};
static  ScdOffsPair  cop59[] = {{160,0L},{133,0L},};
static  ScdOffsPair  cop60[] = {{161,0L},{160,0L},{133,0L},};
static  ScdOffsPair  cop61[] = {{161,0L},{160,0L},{133,0L},};
static  ScdOffsPair  cop62[] = {{161,0L},{160,0L},{133,0L},};
static  ScdOffsPair  cop63[] = {{161,0L},{160,0L},{133,0L},};
static  ScdOffsPair  cop64[] = {{161,0L},{160,0L},{133,0L},};
static  ScdOffsPair  cop65[] = {{166,0L},{133,0L},};
static  ScdOffsPair  cop66[] = {{169,0L},{133,0L},};
static  ScdOffsPair  cop67[] = {{169,0L},{133,0L},};
static  ScdOffsPair  cop68[] = {{169,0L},{133,0L},};
static  ScdOffsPair  cop69[] = {{169,0L},{133,0L},};
static  ScdOffsPair  cop70[] = {{170,0L},{133,0L},};
static  ScdOffsPair  cop71[] = {{170,0L},{133,0L},};
static  ScdOffsPair  cop72[] = {{170,0L},{133,0L},};
static  ScdOffsPair  cop73[] = {{170,0L},{133,0L},};
static  ScdOffsPair  cop74[] = {{170,0L},{133,0L},};
static  ScdOffsPair  cop75[] = {{170,0L},{133,0L},};
static  ScdOffsPair  cop76[] = {{170,0L},{133,0L},};
static  ScdOffsPair  cop77[] = {{171,0L},{133,0L},};
static  ScdOffsPair  cop78[] = {{171,0L},{133,0L},};
static  ScdOffsPair  cop79[] = {{133,0L},};
static  ScdOffsPair  cop80[] = {{133,0L},};
static  ScdOffsPair  cop81[] = {{168,0L},{167,0L},{154,0L},{152,0L},{151,0L},{136,0L},{133,0L},};
static  ScdOffsPair  cop82[] = {{174,0L},{172,0L},{133,0L},};
static  ScdOffsPair  cop83[] = {{174,0L},{172,0L},{133,0L},};
static  ScdOffsPair  cop84[] = {{133,0L},};
static  ScdOffsPair  cop85[] = {{174,0L},{133,0L},};
static  ScdOffsPair  cop86[] = {{137,0L},{133,0L},};
static  ScdOffsPair  cop87[] = {{168,0L},{167,0L},{154,0L},{152,0L},{151,0L},{136,0L},{133,0L},};
static  ScdOffsPair  cop88[] = {{133,0L},};
static  ScdOffsPair  cop89[] = {{133,0L},};
static  ScdOffsPair  cop90[] = {{134,0L},{133,0L},};
static  ScdOffsPair  cop91[] = {{133,0L},};
static  ScdOffsPair  cop92[] = {{133,0L},};
static  ScdOffsPair  cop93[] = {{136,0L},{133,0L},};
static  ScdOffsPair  cop94[] = {{136,0L},{133,0L},};
static  ScdOffsPair  cop95[] = {{136,0L},{133,0L},};
static  ScdOffsPair  cop96[] = {{133,0L},};
static  ScdOffsPair  cop97[] = {{133,0L},};
static  ScdOffsPair  cop98[] = {{140,0L},{133,0L},};
static  ScdOffsPair  cop99[] = {{140,0L},{133,0L},};
static  ScdOffsPair  cop100[] = {{143,0L},{133,0L},};
static  ScdOffsPair  cop101[] = {{133,0L},};
static  ScdOffsPair  cop102[] = {{166,0L},{133,0L},};
static  ScdOffsPair  cop103[] = {{133,0L},};
static  ScdOffsPair  cop104[] = {{133,0L},};
static  ScdOffsPair  cop105[] = {{133,0L},};
static  ScdOffsPair  cop106[] = {{133,0L},};
static  ScdOffsPair  cop107[] = {{133,0L},};
static  ScdOffsPair  cop108[] = {{133,0L},};
static  ScdOffsPair  cop109[] = {{160,0L},{133,0L},};
static  ScdOffsPair  cop110[] = {{160,0L},{133,0L},};
static  ScdOffsPair  cop111[] = {{133,0L},};
static  ScdOffsPair  cop112[] = {{133,0L},};
static  ScdOffsPair  cop113[] = {{133,0L},};
static  ScdOffsPair  cop114[] = {{133,0L},};
static  ScdOffsPair  cop115[] = {{133,0L},};
static  ScdOffsPair  cop116[] = {{133,0L},};
static  ScdOffsPair  cop117[] = {{133,0L},};
static  ScdOffsPair  cop118[] = {{133,0L},};
static  ScdOffsPair  cop119[] = {{133,0L},};
static  ScdOffsPair  cop120[] = {{133,0L},};
static  ScdOffsPair  cop121[] = {{133,0L},};
static  ScdOffsPair  cop122[] = {{133,0L},};
static  ScdOffsPair  cop123[] = {{133,0L},};
static  ScdOffsPair  cop124[] = {{133,0L},};
static  ScdOffsPair  cop125[] = {{133,0L},};
static  ScdOffsPair  cop126[] = {{133,0L},};
static  ScdOffsPair  cop127[] = {{133,0L},};
static  ScdOffsPair  cop128[] = {{134,0L},{133,0L},};
static  ScdOffsPair  cop129[] = {{133,0L},};
static  ScdOffsPair  cop130[] = {{133,0L},};
static  ScdOffsPair  cop131[] = {{133,0L},};
static  ScdOffsPair  cop132[] = {{133,0L},};
static  ScdOffsPair  cop133[] = {{2,0L},{0,0L}};
static  ScdOffsPair  cop134[] = {{18,0L},{19,0L},{20,0L},{90,0L},{128,0L},{0,0L}};
static  ScdOffsPair  cop135[] = {{14,0L},{15,0L},{16,0L},{17,0L},{0,0L}};
static  ScdOffsPair  cop136[] = {{18,0L},{19,0L},{25,0L},{81,0L},{87,0L},{93,0L},{94,0L},{95,0L},{0,0L}};
static  ScdOffsPair  cop137[] = {{26,0L},{27,0L},{28,0L},{29,0L},{30,0L},{31,0L},{32,0L},{33,0L},{46,0L},{86,0L},{0,0L}};
static  ScdOffsPair  cop138[] = {{26,0L},{27,0L},{28,0L},{29,0L},{0,0L}};
static  ScdOffsPair  cop139[] = {{31,0L},{32,0L},{0,0L}};
static  ScdOffsPair  cop140[] = {{98,0L},{99,0L},{0,0L}};
static  ScdOffsPair  cop141[] = {{36,0L},{37,0L},{38,0L},{39,0L},{40,0L},{0,0L}};
static  ScdOffsPair  cop142[] = {{43,0L},{44,0L},{47,0L},{0,0L}};
static  ScdOffsPair  cop143[] = {{47,0L},{100,0L},{0,0L}};
static  ScdOffsPair  cop144[] = {{46,0L},{47,0L},{0,0L}};
static  ScdOffsPair  cop145[] = {{41,0L},{47,0L},{48,0L},{0,0L}};
static  ScdOffsPair  cop146[] = {{43,0L},{44,0L},{45,0L},{0,0L}};
static  ScdOffsPair  cop147[] = {{43,0L},{44,0L},{0,0L}};
static  ScdOffsPair  cop148[] = {{18,0L},{19,0L},{25,0L},{0,0L}};
static  ScdOffsPair  cop149[] = {{14,0L},{15,0L},{16,0L},{17,0L},{21,0L},{22,0L},{23,0L},{0,0L}};
static  ScdOffsPair  cop150[] = {{21,0L},{22,0L},{23,0L},{0,0L}};
static  ScdOffsPair  cop151[] = {{21,0L},{22,0L},{23,0L},{81,0L},{87,0L},{0,0L}};
static  ScdOffsPair  cop152[] = {{21,0L},{22,0L},{23,0L},{24,0L},{32,0L},{34,0L},{81,0L},{87,0L},{0,0L}};
static  ScdOffsPair  cop153[] = {{13,0L},{0,0L}};
static  ScdOffsPair  cop154[] = {{21,0L},{22,0L},{23,0L},{24,0L},{31,0L},{32,0L},{81,0L},{87,0L},{0,0L}};
static  ScdOffsPair  cop155[] = {{34,0L},{35,0L},{0,0L}};
static  ScdOffsPair  cop156[] = {{51,0L},{52,0L},{53,0L},{0,0L}};
static  ScdOffsPair  cop157[] = {{54,0L},{55,0L},{56,0L},{57,0L},{58,0L},{0,0L}};
static  ScdOffsPair  cop158[] = {{13,0L},{0,0L}};
static  ScdOffsPair  cop159[] = {{34,0L},{35,0L},{0,0L}};
static  ScdOffsPair  cop160[] = {{59,0L},{60,0L},{61,0L},{62,0L},{63,0L},{64,0L},{109,0L},{110,0L},{0,0L}};
static  ScdOffsPair  cop161[] = {{60,0L},{61,0L},{62,0L},{63,0L},{64,0L},{0,0L}};
static  ScdOffsPair  cop162[] = {{22,0L},{23,0L},{0,0L}};
static  ScdOffsPair  cop163[] = {{19,0L},{22,0L},{23,0L},{25,0L},{0,0L}};
static  ScdOffsPair  cop164[] = {{11,0L},{0,0L}};
static  ScdOffsPair  cop165[] = {{37,0L},{38,0L},{39,0L},{0,0L}};
static  ScdOffsPair  cop166[] = {{65,0L},{102,0L},{0,0L}};
static  ScdOffsPair  cop167[] = {{21,0L},{22,0L},{23,0L},{24,0L},{30,0L},{31,0L},{32,0L},{81,0L},{87,0L},{0,0L}};
static  ScdOffsPair  cop168[] = {{21,0L},{22,0L},{23,0L},{24,0L},{30,0L},{31,0L},{32,0L},{46,0L},{81,0L},{87,0L},{0,0L}};
static  ScdOffsPair  cop169[] = {{12,0L},{43,0L},{44,0L},{66,0L},{67,0L},{68,0L},{69,0L},{0,0L}};
static  ScdOffsPair  cop170[] = {{11,0L},{70,0L},{71,0L},{72,0L},{73,0L},{74,0L},{75,0L},{76,0L},{0,0L}};
static  ScdOffsPair  cop171[] = {{77,0L},{78,0L},{0,0L}};
static  ScdOffsPair  cop172[] = {{82,0L},{83,0L},{0,0L}};
static  ScdOffsPair  cop173[] = {{26,0L},{27,0L},{29,0L},{0,0L}};
static  ScdOffsPair  cop174[] = {{82,0L},{83,0L},{85,0L},{0,0L}};

ScdOffsPair *mxi_coffsettab[175] = {
0L,0L,0L,
cop3,cop4,cop5,cop6,cop7,cop8,cop9,cop10,cop11,cop12,
cop13,cop14,cop15,cop16,cop17,cop18,cop19,cop20,cop21,cop22,
cop23,cop24,cop25,cop26,cop27,cop28,cop29,cop30,cop31,cop32,
cop33,cop34,cop35,cop36,cop37,cop38,cop39,cop40,cop41,cop42,
cop43,cop44,cop45,cop46,cop47,cop48,cop49,cop50,cop51,cop52,
cop53,cop54,cop55,cop56,cop57,cop58,cop59,cop60,cop61,cop62,
cop63,cop64,cop65,cop66,cop67,cop68,cop69,cop70,cop71,cop72,
cop73,cop74,cop75,cop76,cop77,cop78,cop79,cop80,cop81,cop82,
cop83,cop84,cop85,cop86,cop87,cop88,cop89,cop90,cop91,cop92,
cop93,cop94,cop95,cop96,cop97,cop98,cop99,cop100,cop101,cop102,
cop103,cop104,cop105,cop106,cop107,cop108,cop109,cop110,cop111,cop112,
cop113,cop114,cop115,cop116,cop117,cop118,cop119,cop120,cop121,cop122,
cop123,cop124,cop125,cop126,cop127,cop128,cop129,cop130,cop131,cop132,
cop133,cop134,cop135,cop136,cop137,cop138,cop139,cop140,cop141,cop142,
cop143,cop144,cop145,cop146,cop147,cop148,cop149,cop150,cop151,cop152,
cop153,cop154,cop155,cop156,cop157,cop158,cop159,cop160,cop161,cop162,
cop163,cop164,cop165,cop166,cop167,cop168,cop169,cop170,cop171,cop172,
cop173,cop174,};

static ELEMENT mxz_firstpoint, mxz_lastpoint;

/* Auxiliary functions for correct evaluation order */

typedef struct {
	ELEMENT point,node;
	int ind;
} HEAP_ITEM;

static HEAP_ITEM mxz_heap[18];

static int mxz_count[18];
static int mxz_number[18];

static int mxz_gt( HEAP_ITEM *p, HEAP_ITEM *q )
{
int x = p->point, y = q->point;
return (x==mxs_nil(_c,0)) || (y!=mxs_nil(_c,0) && x > y);
}

static int mxz_lt( HEAP_ITEM *p, HEAP_ITEM *q )
{
int x = p->point, y = q->point;
return (x==mxs_nil(_c,0)) || (y!=mxs_nil(_c,0) && x < y);
}

static void mxz_sift_backw( int j, int r )
{
HEAP_ITEM x = mxz_heap[j];

	while((j<<=1)<=r) {
		if(j<r) if( mxz_lt(&mxz_heap[j],&mxz_heap[j+1])) j++;
		if( !mxz_lt(&x,&mxz_heap[j])) break;
		mxz_heap[j>>1] = mxz_heap[j];
	}
	mxz_heap[j>>1] = x;
}

static void mxz_sift_forw( int j, int r )
{
HEAP_ITEM x = mxz_heap[j];

	while((j<<=1)<=r) {
		if(j<r) if( mxz_gt(&mxz_heap[j],&mxz_heap[j+1])) j++;
		if( !mxz_gt(&x,&mxz_heap[j])) break;
		mxz_heap[j>>1] = mxz_heap[j];
	}
	mxz_heap[j>>1] = x;
}

#define mxz_HIF(i)       mxz_heap[i].ind=i
#define mxz_HPB(i)       mxz_heap[i].point=mxs_before(_c,0,mxz_heap[i].node)
#define mxz_HPA(i)       mxz_heap[i].point=mxs_after(_c,0,mxz_heap[i].node)
#define mxz_NVE(j,i,S)   mxz_heap[j].node=mxs_element(_c,0,mxz_count[i],S)
#define mxz_NRE(j,i,S)   mxz_heap[j].node=rev_element(mxz_count[i],S)
#define mxz_NIL(i)       mxz_heap[i].point=mxs_nil(_c,0)
#define mxz_FIRST(i,S)   ((mxz_count[i] = 1) > (mxz_number[i] = mxs_number(_c,0,S)))
#define mxz_LAST(i,S)    ((mxz_count[i] = mxs_number(_c,0,S)) < 1)
#define mxz_INC(i)       ((++mxz_count[i]) > mxz_number[i])
#define mxz_DEC(i)       ((--mxz_count[i]) < 1)

#define first_forw_bef(S,i)\
mxz_FIRST(i,S) ? mxz_NIL(i) : (mxz_NVE(i,i,S),mxz_HPB(i),mxz_HIF(i))

#define first_backw_bef(S,i)\
mxz_LAST(i,S)  ? mxz_NIL(i) : (mxz_NVE(i,i,S),mxz_HPB(i),mxz_HIF(i))

#define next_forw_bef(S,i)\
mxz_INC(i)   ? mxz_NIL(1) : (mxz_NVE(1,i,S),mxz_HPB(1))

#define next_backw_bef(S,i)\
mxz_DEC(i)   ? mxz_NIL(1) : (mxz_NVE(1,i,S),mxz_HPB(1))

#define first_forw_aft(S,i)\
mxz_FIRST(i,S) ? mxz_NIL(i) : (mxz_NRE(i,i,S),mxz_HPA(i),mxz_HIF(i))

#define first_backw_aft(S,i)\
mxz_LAST(i,S)  ? mxz_NIL(i) : (mxz_NRE(i,i,S),mxz_HPA(i),mxz_HIF(i))

#define next_forw_aft(S,i)\
mxz_INC(i)   ? mxz_NIL(1) : (mxz_NRE(1,i,S),mxz_HPA(1))

#define next_backw_aft(S,i)\
mxz_DEC(i)   ? mxz_NIL(1) : (mxz_NRE(1,i,S),mxz_HPA(1))

static void nextnode_forw_bef() {
ELEMENT P = mxz_heap[1].point;
do{ if(++P == mxz_lastpoint ) { mxz_NIL(1); return; }
  } while( P != mxs_before(_c,0,mxs_node(_c,0,P)));
mxz_heap[1].point=P;
mxz_heap[1].node=mxs_node(_c,0,P);
}

static void nextnode_forw_aft() {
ELEMENT P = mxz_heap[1].point;
if( P == mxz_lastpoint ) { mxz_NIL(1); return; }
do { P++; } while( P != mxs_after(_c,0,mxs_node(_c,0,P)));
mxz_heap[1].point=P;
mxz_heap[1].node=mxs_node(_c,0,P);
}

static void nextnode_backw_aft() {
ELEMENT P = mxz_heap[1].point;
do{ if(--P == mxz_firstpoint ) { mxz_NIL(1); return; }
  } while( P != mxs_after(_c,0,mxs_node(_c,0,P)));
mxz_heap[1].point=P;
mxz_heap[1].node=mxs_node(_c,0,P);
}

static void nextnode_backw_bef() {
ELEMENT P = mxz_heap[1].point;
if( P == mxz_firstpoint ) { mxz_NIL(1); return; }
do { P--; } while( P != mxs_before(_c,0,mxs_node(_c,0,P)) );
mxz_heap[1].point=P;
mxz_heap[1].node=mxs_node(_c,0,P);
}

#define firstnode_forw_bef(i)  (mxz_heap[i].point=mxz_firstpoint,mxz_heap[i].node=mxs_root(_c,0))

#define firstnode_backw_aft(i) (mxz_heap[i].point=mxz_lastpoint,mxz_heap[i].node=mxs_root(_c,0))

#define firstnode_forw_aft(i)  (firstnode_forw_bef(1),nextnode_forw_aft(),mxz_heap[i]=mxz_heap[1])

#define firstnode_backw_bef(i) (firstnode_backw_aft(1),nextnode_backw_bef(),mxz_heap[i]=mxz_heap[1])

static ELEMENT *enum_stack, **rev_element_tab;
static int      enum_topelem;
static int      enum_index;

#define rev_element(i,sort) rev_element_tab[(sort)&0xffff][i]

void mxz_init_revindex( ELEMENT sort )
{
int i,bound;
ELEMENT *P;

	if(rev_element_tab[sort & 0xffff] != NULL) return;
	P = rev_element_tab[sort & 0xffff] = (ELEMENT *)calloc((1+mxs_number(_c,0,sort)),sizeof(ELEMENT));
	if( P == 0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate rev_element_tab table \n");
		exit( EXIT_FAILURE );
	}
	enum_index = 1;
	enum_topelem = -1;
	bound = mxs_number(_c,0,sort);

	for(i=1;i<=bound;i++) {
		    if( enum_topelem >= 0 ) goto L2;
		L1: enum_stack[++enum_topelem] = mxs_element(_c,0,enum_index++,sort);
		L2: if(enum_index > bound) goto L3;
		    if(mxs_desc(_c,0,mxs_element(_c,0,enum_index,sort),enum_stack[enum_topelem])) goto L1;
		L3: P[i] = enum_stack[enum_topelem--];
	}
}

/* The declaration for externals  */
extern ELEMENT add(ELEMENT,ELEMENT);
static ELEMENT mxs_add(char *f,int l,ELEMENT p1,ELEMENT p2){
	IFNIL(p1) IFNIL(p2) 
	IS(p1,_Int,f,l,"add",1) IS(p2,_Int,f,l,"add",2) 
	return add(p1,p2);
}
extern ELEMENT sub(ELEMENT,ELEMENT);
static ELEMENT mxs_sub(char *f,int l,ELEMENT p1,ELEMENT p2){
	IFNIL(p1) IFNIL(p2) 
	IS(p1,_Int,f,l,"sub",1) IS(p2,_Int,f,l,"sub",2) 
	return sub(p1,p2);
}
extern ELEMENT neg(ELEMENT);
static ELEMENT mxs_neg(char *f,int l,ELEMENT p1){
	IFNIL(p1) 
	IS(p1,_Int,f,l,"neg",1) 
	return neg(p1);
}
extern ELEMENT s(ELEMENT);
static ELEMENT mxs_s(char *f,int l,ELEMENT p1){
	IFNIL(p1) 
	IS(p1,_Int_,f,l,"s",1) 
	return s(p1);
}
extern ELEMENT init_matrix(ELEMENT);
static ELEMENT mxs_init_matrix(char *f,int l,ELEMENT p1){
	IFNIL(p1) 
	IS(p1,_Int,f,l,"init_matrix",1) 
	return init_matrix(p1);
}
extern ELEMENT enter_attribute(ELEMENT,ELEMENT,ELEMENT,ELEMENT);
static ELEMENT mxs_enter_attribute(char *f,int l,ELEMENT p1,ELEMENT p2,ELEMENT p3,ELEMENT p4){
	IFNIL(p1) IFNIL(p2) IFNIL(p3) IFNIL(p4) 
	IS(p1,_Int,f,l,"enter_attribute",1) IS(p2,_FctOrAtt_,f,l,"enter_attribute",2) IS(p3,_Reference,f,l,"enter_attribute",3) IS(p4,_Int,f,l,"enter_attribute",4) 
	return enter_attribute(p1,p2,p3,p4);
}
extern ELEMENT warshall_value(ELEMENT,ELEMENT);
static ELEMENT mxs_warshall_value(char *f,int l,ELEMENT p1,ELEMENT p2){
	IFNIL(p1) IFNIL(p2) 
	IS(p1,_Reference,f,l,"warshall_value",1) IS(p2,_Int,f,l,"warshall_value",2) 
	return warshall_value(p1,p2);
}
extern ELEMENT mat_lookup(ELEMENT,ELEMENT,ELEMENT);
static ELEMENT mxs_mat_lookup(char *f,int l,ELEMENT p1,ELEMENT p2,ELEMENT p3){
	IFNIL(p1) IFNIL(p2) IFNIL(p3) 
	IS(p1,_Reference,f,l,"mat_lookup",1) IS(p2,_Int,f,l,"mat_lookup",2) IS(p3,_Int,f,l,"mat_lookup",3) 
	return mat_lookup(p1,p2,p3);
}
extern ELEMENT OrdOp_or(ELEMENT,ELEMENT);
static ELEMENT mxs_OrdOp_or(char *f,int l,ELEMENT p1,ELEMENT p2){
	IFNIL(p1) IFNIL(p2) 
	IS(p1,_OrderTup,f,l,"OrdOp_or",1) IS(p2,_OrderTup,f,l,"OrdOp_or",2) 
	return OrdOp_or(p1,p2);
}
extern ELEMENT OrdOp_conc(ELEMENT,ELEMENT);
static ELEMENT mxs_OrdOp_conc(char *f,int l,ELEMENT p1,ELEMENT p2){
	IFNIL(p1) IFNIL(p2) 
	IS(p1,_OrderTup,f,l,"OrdOp_conc",1) IS(p2,_OrderTup,f,l,"OrdOp_conc",2) 
	return OrdOp_conc(p1,p2);
}
extern ELEMENT OrdOp_closure(ELEMENT);
static ELEMENT mxs_OrdOp_closure(char *f,int l,ELEMENT p1){
	IFNIL(p1) 
	IS(p1,_OrderTup,f,l,"OrdOp_closure",1) 
	return OrdOp_closure(p1);
}
extern ELEMENT aux_itoa(ELEMENT);
static ELEMENT mxs_aux_itoa(char *f,int l,ELEMENT p1){
	IFNIL(p1) 
	IS(p1,_Int,f,l,"aux_itoa",1) 
	return aux_itoa(p1);
}
extern ELEMENT intres_union(ELEMENT,ELEMENT,ELEMENT);
static ELEMENT mxs_intres_union(char *f,int l,ELEMENT p1,ELEMENT p2,ELEMENT p3){
	IFNIL(p1) IFNIL(p2) IFNIL(p3) 
	IS(p1,_IntResList,f,l,"intres_union",1) IS(p2,_IntResList,f,l,"intres_union",2) IS(p3,_IntResList,f,l,"intres_union",3) 
	return intres_union(p1,p2,p3);
}


extern long lt(ELEMENT,ELEMENT);
static ELEMENT mxs_lt(char *f,int l,ELEMENT p1,ELEMENT p2){
	ISORNIL(p1,_Int,f,l,"lt",1) ISORNIL(p2,_Int,f,l,"lt",2) 
	return lt(p1,p2);
}
extern long le(ELEMENT,ELEMENT);
static ELEMENT mxs_le(char *f,int l,ELEMENT p1,ELEMENT p2){
	ISORNIL(p1,_Int,f,l,"le",1) ISORNIL(p2,_Int,f,l,"le",2) 
	return le(p1,p2);
}
extern long maybe_same_node(ELEMENT);
static ELEMENT mxs_maybe_same_node(char *f,int l,ELEMENT p1){
	ISORNIL(p1,_OrderTup,f,l,"maybe_same_node",1) 
	return maybe_same_node(p1);
}
extern long no_strategy_found(ELEMENT);
static ELEMENT mxs_no_strategy_found(char *f,int l,ELEMENT p1){
	ISORNIL(p1,_FctOrAtt_,f,l,"no_strategy_found",1) 
	return no_strategy_found(p1);
}


extern long init_parscode( void );
extern long free_parscode( void );
extern ELEMENT parscode( ELEMENT );
static ELEMENT mxs_parscode(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_Production_,f,l,"parscode",1) 
	return parscode(p1);
}
extern long init_LPsepsymbols( void );
extern long free_LPsepsymbols( void );
extern ELEMENT LPsepsymbols( ELEMENT );
static ELEMENT mxs_LPsepsymbols(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_ListProd_,f,l,"LPsepsymbols",1) 
	return LPsepsymbols(p1);
}
extern long init_TPconcrSyntax( void );
extern long free_TPconcrSyntax( void );
extern ELEMENT TPconcrSyntax( ELEMENT );
static ELEMENT mxs_TPconcrSyntax(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_TupelProd_,f,l,"TPconcrSyntax",1) 
	return TPconcrSyntax(p1);
}
extern long init_CPrsideinfo( void );
extern long free_CPrsideinfo( void );
extern ELEMENT CPrsideinfo( ELEMENT );
static ELEMENT mxs_CPrsideinfo(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_ClassProd_,f,l,"CPrsideinfo",1) 
	return CPrsideinfo(p1);
}
extern long init_idtodecls( void );
extern long free_idtodecls( void );
extern ELEMENT idtodecls( ELEMENT );
static ELEMENT mxs_idtodecls(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_Ident,f,l,"idtodecls",1) 
	return idtodecls(p1);
}
extern long init_ExchangeTripel( void );
extern long free_ExchangeTripel( void );
extern ELEMENT ExchangeTripel( ELEMENT );
static ELEMENT mxs_ExchangeTripel(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_TupelProd_,f,l,"ExchangeTripel",1) 
	return ExchangeTripel(p1);
}
extern long init_ExtraRule( void );
extern long free_ExtraRule( void );
extern ELEMENT ExtraRule( ELEMENT );
static ELEMENT mxs_ExtraRule(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_Production_,f,l,"ExtraRule",1) 
	return ExtraRule(p1);
}
extern long init_subsorts( void );
extern long free_subsorts( void );
extern ELEMENT subsorts( ELEMENT );
static ELEMENT mxs_subsorts(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_ClassProd_,f,l,"subsorts",1) 
	return subsorts(p1);
}
extern long init_att_path( void );
extern long free_att_path( void );
extern ELEMENT att_path( ELEMENT );
static ELEMENT mxs_att_path(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_Item_,f,l,"att_path",1) 
	return att_path(p1);
}
extern long init_pat_anchor( void );
extern long free_pat_anchor( void );
extern ELEMENT pat_anchor( ELEMENT );
static ELEMENT mxs_pat_anchor(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_PatternCase_,f,l,"pat_anchor",1) 
	return pat_anchor(p1);
}
extern long init_eval_groupnr( void );
extern long free_eval_groupnr( void );
extern ELEMENT eval_groupnr( ELEMENT );
static ELEMENT mxs_eval_groupnr(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FctOrAtt_,f,l,"eval_groupnr",1) 
	return eval_groupnr(p1);
}
extern long init_eval_prev_grnum( void );
extern long free_eval_prev_grnum( void );
extern ELEMENT eval_prev_grnum( ELEMENT );
static ELEMENT mxs_eval_prev_grnum(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FuAtList_,f,l,"eval_prev_grnum",1) 
	return eval_prev_grnum(p1);
}
extern long init_group_index( void );
extern long free_group_index( void );
extern ELEMENT group_index( ELEMENT );
static ELEMENT mxs_group_index(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FctOrAtt_,f,l,"group_index",1) 
	return group_index(p1);
}
extern long init_eval_group( void );
extern long free_eval_group( void );
extern ELEMENT eval_group( ELEMENT );
static ELEMENT mxs_eval_group(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FctOrAtt_,f,l,"eval_group",1) 
	return eval_group(p1);
}
extern long init_attr_list_groups( void );
extern long free_attr_list_groups( void );
extern ELEMENT attr_list_groups( ELEMENT );
static ELEMENT mxs_attr_list_groups(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FuAtList_,f,l,"attr_list_groups",1) 
	return attr_list_groups(p1);
}
extern long init_eval_finegroup( void );
extern long free_eval_finegroup( void );
extern ELEMENT eval_finegroup( ELEMENT );
static ELEMENT mxs_eval_finegroup(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FctOrAtt_,f,l,"eval_finegroup",1) 
	return eval_finegroup(p1);
}
extern long init_eval_aftbef( void );
extern long free_eval_aftbef( void );
extern ELEMENT eval_aftbef( ELEMENT );
static ELEMENT mxs_eval_aftbef(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FctOrAtt_,f,l,"eval_aftbef",1) 
	return eval_aftbef(p1);
}
extern long init_is_trivial_finegroup( void );
extern long free_is_trivial_finegroup( void );
extern ELEMENT is_trivial_finegroup( ELEMENT );
static ELEMENT mxs_is_trivial_finegroup(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FctOrAtt_,f,l,"is_trivial_finegroup",1) 
	return is_trivial_finegroup(p1);
}
extern long init_eval_strategy( void );
extern long free_eval_strategy( void );
extern ELEMENT eval_strategy( ELEMENT );
static ELEMENT mxs_eval_strategy(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FctOrAtt_,f,l,"eval_strategy",1) 
	return eval_strategy(p1);
}
extern long init_eval_sortlist( void );
extern long free_eval_sortlist( void );
extern ELEMENT eval_sortlist( ELEMENT );
static ELEMENT mxs_eval_sortlist(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FctOrAtt_,f,l,"eval_sortlist",1) 
	return eval_sortlist(p1);
}
extern long init_attr_list_info( void );
extern long free_attr_list_info( void );
extern ELEMENT attr_list_info( ELEMENT );
static ELEMENT mxs_attr_list_info(char *f,int l,ELEMENT p1){
	IFNIL(p1)  IS(p1,_FuAtList_,f,l,"attr_list_info",1) 
	return attr_list_info(p1);
}


ELEMENT  mxs_encl_dynfunc(char*,int,ELEMENT);
ELEMENT  mxs_ss(char*,int,ELEMENT);
ELEMENT  mxs_id(char*,int,ELEMENT);
ELEMENT  mxs_patlineno(char*,int,ELEMENT);
ELEMENT  mxs_patfilename(char*,int,ELEMENT);
ELEMENT  mxs_decl(char*,int,ELEMENT);
ELEMENT  mxs_sort_union(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_scope(char*,int,ELEMENT);
ELEMENT  mxs_lookup_params(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_lookup_item(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_lookup_items(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_lookup_cond(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_lookup(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_countastrks(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_smallestlistprodcd(char*,int);
ELEMENT  mxs_prodcd(char*,int,ELEMENT);
ELEMENT  mxs_next_left_pat(char*,int,ELEMENT);
ELEMENT  mxs_patnposition(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_next_pat_for_codegen(char*,int,ELEMENT);
ELEMENT  mxs_next_pat_upthetree(char*,int,ELEMENT);
ELEMENT  mxs_pat_absoff_pos(char*,int,ELEMENT);
ELEMENT  mxs_pat_reloff_pos(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_pat_absoff_neg(char*,int,ELEMENT);
ELEMENT  mxs_pat_reloff_neg(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_pat_absoff(char*,int,ELEMENT);
ELEMENT  mxs_pat_reloff(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_abs_itempos(char*,int,ELEMENT);
ELEMENT  mxs_lmin_itempos(char*,int,ELEMENT);
ELEMENT  mxs_rmin_itempos(char*,int,ELEMENT);
ELEMENT  mxs_path(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_search_bound_names_rec(char*,int,ELEMENT);
ELEMENT  mxs_search_bound_names(char*,int,ELEMENT);
ELEMENT  mxs_search_free_items_rec(char*,int,ELEMENT);
ELEMENT  mxs_search_free_items(char*,int,ELEMENT);
ELEMENT  mxs_search_blanks_rec(char*,int,ELEMENT);
ELEMENT  mxs_search_blanks(char*,int,ELEMENT);
ELEMENT  mxs_search_free_p_names_rec(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_search_free_p_names(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_search_bound_p_names_rec(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_search_bound_p_names(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_search_patt_names(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_search_patt_sorts_rec(char*,int,ELEMENT);
ELEMENT  mxs_search_patt_sorts(char*,int,ELEMENT);
ELEMENT  mxs_search_name_in_patt_rec(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_search_name_in_patt(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_latest_bindpos(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_par_pos(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_corresp_parsort(char*,int,ELEMENT);
ELEMENT  mxs_actpar_pos(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_univ_path(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_mk_enl(char*,int,ELEMENT);
ELEMENT  mxs_dep_expr(char*,int,ELEMENT);
ELEMENT  mxs_lineof(char*,int,ELEMENT);
ELEMENT  mxs_colof(char*,int,ELEMENT);
ELEMENT  mxs_TW_identabb(char*,int);
ELEMENT  mxs_TW_emptyset(char*,int);
ELEMENT  mxs_TW_or(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_delete_id(char*,int,ELEMENT);
ELEMENT  mxs_TW_closure(char*,int,ELEMENT);
ELEMENT  mxs_TW_conc(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_node_parnr_fct(char*,int,ELEMENT);
ELEMENT  mxs_encl_patcase(char*,int,ELEMENT);
ELEMENT  mxs_pat_son_pos_nr(char*,int,ELEMENT);
ELEMENT  mxs_pat_son_neg_nr(char*,int,ELEMENT);
ELEMENT  mxs_pat_son_nr(char*,int,ELEMENT);
ELEMENT  mxs_pat_way(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_enter_attrgroup(char*,int,ELEMENT,ELEMENT,ELEMENT);
ELEMENT  mxs_enter_attrgroup_list(char*,int,ELEMENT,ELEMENT,ELEMENT);
ELEMENT  mxs_simplify_closure(char*,int,ELEMENT);
ELEMENT  mxs_normal_tw(char*,int,ELEMENT,ELEMENT,ELEMENT);
ELEMENT  mxs_normal_closure(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_normalform(char*,int,ELEMENT,ELEMENT,ELEMENT);
ELEMENT  mxs_Ord_fath(char*,int);
ELEMENT  mxs_Ord_son(char*,int);
ELEMENT  mxs_Ord_rbroth(char*,int);
ELEMENT  mxs_Ord_lbroth(char*,int);
ELEMENT  mxs_Ord_ident(char*,int);
ELEMENT  mxs_Ord_neutral(char*,int);
ELEMENT  mxs_Ord_nothing(char*,int);
ELEMENT  mxs_val_order(char*,int,ELEMENT);
ELEMENT  mxs_contains_attr(char*,int,ELEMENT);
ELEMENT  mxs_encl_fctoratt(char*,int,ELEMENT);
ELEMENT  mxs_filter_relev_acc(char*,int,ELEMENT);
ELEMENT  mxs_list_intresexprs(char*,int,ELEMENT);
ELEMENT  mxs_intresexprs(char*,int,ELEMENT);
ELEMENT  mxs_encl_part_intres(char*,int,ELEMENT);
ELEMENT  mxs_aux_var_need(char*,int,ELEMENT,ELEMENT);
ELEMENT  mxs_aux_intres_left(char*,int,ELEMENT,ELEMENT,ELEMENT);
ELEMENT  mxs_aux_intres_right(char*,int,ELEMENT,ELEMENT,ELEMENT,ELEMENT,ELEMENT);


long  mxs_in(char*,int,ELEMENT,ELEMENT,ELEMENT);
long  mxs_is_enumerable(char*,int,ELEMENT);
long  mxs_ex_pattern_inbetween(char*,int,ELEMENT,ELEMENT);
long  mxs_is_node(char*,int,ELEMENT);
long  mxs_simplification(char*,int,ELEMENT,ELEMENT);
long  mxs_is_intres(char*,int,ELEMENT);


static ELEMENT   *mxa_term_basesorts;
static AttInstSq *mxw_term_basesorts;
ELEMENT  mxs_term_basesorts( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_term_basesorts[mxs_index(_c,0,p,_SortId_)];
}
static ELEMENT   *mxa_node_basesorts;
static AttInstSq *mxw_node_basesorts;
ELEMENT  mxs_node_basesorts( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_node_basesorts[mxs_index(_c,0,p,_SortId_)];
}
static ELEMENT   *mxa_encl_scope;
ELEMENT  mxs_encl_scope( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_encl_scope[mxs_index(_c,0,p,_Scope_)];
}
static ELEMENT   *mxa_bind_pos;
ELEMENT  mxs_bind_pos( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Name_,f,l,"bind_pos",1)
	return mxa_bind_pos[mxs_index(_c,0,p,_Name_)];
}
static ELEMENT   *mxa_numberofastrks;
ELEMENT  mxs_numberofastrks( char *f, int l, ELEMENT p ){
 IS(p,_ItemList_,f,l,"numberofastrks",1)
	return mxa_numberofastrks[mxs_index(_c,0,p,_ItemList_)];
}
static ELEMENT   *mxa_predeclprodcd;
ELEMENT  mxs_predeclprodcd( char *f, int l, ELEMENT p ){
	return mxa_predeclprodcd[mxs_index(_c,0,p,_PredeclProd_)];
}
static ELEMENT   *mxa_tupelprodcd;
ELEMENT  mxs_tupelprodcd( char *f, int l, ELEMENT p ){
	return mxa_tupelprodcd[mxs_index(_c,0,p,_TupelProd_)];
}
static ELEMENT   *mxa_listprodcd;
ELEMENT  mxs_listprodcd( char *f, int l, ELEMENT p ){
	return mxa_listprodcd[mxs_index(_c,0,p,_ListProd_)];
}
static ELEMENT   *mxa_classprodcd;
ELEMENT  mxs_classprodcd( char *f, int l, ELEMENT p ){
	return mxa_classprodcd[mxs_index(_c,0,p,_ClassProd_)];
}
static ELEMENT   *mxa_patnpos;
ELEMENT  mxs_patnpos( char *f, int l, ELEMENT p ){
	return mxa_patnpos[mxs_index(_c,0,p,_Pattern_)];
}
static ELEMENT   *mxa_num_items;
ELEMENT  mxs_num_items( char *f, int l, ELEMENT p ){
 IS(p,_Pattern_,f,l,"num_items",1)
	return mxa_num_items[mxs_index(_c,0,p,_Pattern_)];
}
static ELEMENT   *mxa_args;
ELEMENT  mxs_args( char *f, int l, ELEMENT p ){
	return mxa_args[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_caseexpr;
ELEMENT  mxs_caseexpr( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_caseexpr[mxs_index(_c,0,p,_IfCase_)];
}
static ELEMENT   *mxa_allexpr;
ELEMENT  mxs_allexpr( char *f, int l, ELEMENT p ){
	return mxa_allexpr[mxs_index(_c,0,p,_IfExpr_)];
}
static ELEMENT   *mxa_encl_patterncase;
ELEMENT  mxs_encl_patterncase( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_encl_patterncase[mxs_index(_c,0,p,_Node)];
}
static ELEMENT   *mxa_top_pattern;
ELEMENT  mxs_top_pattern( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_top_pattern[mxs_index(_c,0,p,_Node)];
}
static ELEMENT   *mxa_son_nr;
ELEMENT  mxs_son_nr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"son_nr",1)
	return mxa_son_nr[mxs_index(_c,0,p,_FctOrAtt_)];
}
static ELEMENT   *mxa_relacc_nr;
ELEMENT  mxs_relacc_nr( char *f, int l, ELEMENT p ){
	return mxa_relacc_nr[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_appl_list_formula;
ELEMENT  mxs_appl_list_formula( char *f, int l, ELEMENT p ){
	return mxa_appl_list_formula[mxs_index(_c,0,p,_Formula_)];
}
static ELEMENT   *mxa_appl_list_case;
ELEMENT  mxs_appl_list_case( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_appl_list_case[mxs_index(_c,0,p,_Case_)];
}
static ELEMENT   *mxa_appl_list_expr;
ELEMENT  mxs_appl_list_expr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Expr_,f,l,"appl_list_expr",1)
	return mxa_appl_list_expr[mxs_index(_c,0,p,_Expr_)];
}
static ELEMENT   *mxa_appl_list;
ELEMENT  mxs_appl_list( char *f, int l, ELEMENT p ){
	return mxa_appl_list[mxs_index(_c,0,p,_FctOrAtt_)];
}
static ELEMENT   *mxa_def_value;
ELEMENT  mxs_def_value( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_def_value[mxs_index(_c,0,p,_DefId_)];
}
static ELEMENT   *mxa_node_parnr;
ELEMENT  mxs_node_parnr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAttDecl_,f,l,"node_parnr",1)
	return mxa_node_parnr[mxs_index(_c,0,p,_FctOrAttDecl_)];
}
static ELEMENT   *mxa_appl_value;
ELEMENT  mxs_appl_value( char *f, int l, ELEMENT p ){
	return mxa_appl_value[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_nodepar_expr;
ELEMENT  mxs_nodepar_expr( char *f, int l, ELEMENT p ){
	return mxa_nodepar_expr[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_valueterm_list;
static AttInstSq *mxw_valueterm_list;
ELEMENT  mxs_valueterm_list( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_valueterm_list[mxs_index(_c,0,p,_Case_)];
}
static ELEMENT   *mxa_valueterm;
static AttInstSq *mxw_valueterm;
ELEMENT  mxs_valueterm( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Expr_,f,l,"valueterm",1)
	return mxa_valueterm[mxs_index(_c,0,p,_Expr_)];
}
static ELEMENT   *mxa_attr_list_matlist;
ELEMENT  mxs_attr_list_matlist( char *f, int l, ELEMENT p ){
	return mxa_attr_list_matlist[mxs_index(_c,0,p,_FuAtList_)];
}
static ELEMENT   *mxa_result_value;
ELEMENT  mxs_result_value( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"result_value",1)
	return mxa_result_value[mxs_index(_c,0,p,_FctOrAtt_)];
}
static ELEMENT   *mxa_is_relev_att_access;
ELEMENT  mxs_is_relev_att_access( char *f, int l, ELEMENT p ){
	return mxa_is_relev_att_access[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_appl_order;
ELEMENT  mxs_appl_order( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_appl_order[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_appl_relacc_list;
ELEMENT  mxs_appl_relacc_list( char *f, int l, ELEMENT p ){
	return mxa_appl_relacc_list[mxs_index(_c,0,p,_FctOrAtt_)];
}
static ELEMENT   *mxa_maybe_wait;
ELEMENT  mxs_maybe_wait( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"maybe_wait",1)
	return mxa_maybe_wait[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_cgen_name;
static AttInstSq *mxw_cgen_name;
ELEMENT  mxs_cgen_name( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_cgen_name[mxs_index(_c,0,p,_IntResOrName_)];
}
static ELEMENT   *mxa_sces_appl;
ELEMENT  mxs_sces_appl( char *f, int l, ELEMENT p ){
	return mxa_sces_appl[mxs_index(_c,0,p,_ApplyEntity_)];
}
static ELEMENT   *mxa_sces1_cond;
ELEMENT  mxs_sces1_cond( char *f, int l, ELEMENT p ){
	return mxa_sces1_cond[mxs_index(_c,0,p,_Condition_)];
}
static ELEMENT   *mxa_sces2_cond;
ELEMENT  mxs_sces2_cond( char *f, int l, ELEMENT p ){
	return mxa_sces2_cond[mxs_index(_c,0,p,_Condition_)];
}
static ELEMENT   *mxa_sces1_let;
ELEMENT  mxs_sces1_let( char *f, int l, ELEMENT p ){
	return mxa_sces1_let[mxs_index(_c,0,p,_LetExpr_)];
}
static ELEMENT   *mxa_sces2_let;
ELEMENT  mxs_sces2_let( char *f, int l, ELEMENT p ){
	return mxa_sces2_let[mxs_index(_c,0,p,_LetExpr_)];
}
static ELEMENT   *mxa_sces_if;
ELEMENT  mxs_sces_if( char *f, int l, ELEMENT p ){
	return mxa_sces_if[mxs_index(_c,0,p,_IfExpr_)];
}
static ELEMENT   *mxa_sces1_fcase;
ELEMENT  mxs_sces1_fcase( char *f, int l, ELEMENT p ){
	return mxa_sces1_fcase[mxs_index(_c,0,p,_FormulaCase_)];
}
static ELEMENT   *mxa_sces2_fcase;
ELEMENT  mxs_sces2_fcase( char *f, int l, ELEMENT p ){
	return mxa_sces2_fcase[mxs_index(_c,0,p,_FormulaCase_)];
}
static ELEMENT   *mxa_sces_pcase;
ELEMENT  mxs_sces_pcase( char *f, int l, ELEMENT p ){
	return mxa_sces_pcase[mxs_index(_c,0,p,_PatternCase_)];
}
static ELEMENT   *mxa_sces_attacc;
ELEMENT  mxs_sces_attacc( char *f, int l, ELEMENT p ){
	return mxa_sces_attacc[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_lokvar_need;
ELEMENT  mxs_lokvar_need( char *f, int l, ELEMENT p ){
	IFNIL(p)	return mxa_lokvar_need[mxs_index(_c,0,p,_FctOrAtt_)];
}
static ELEMENT   *mxa_intres_collect;
ELEMENT  mxs_intres_collect( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IntResExpr_,f,l,"intres_collect",1)
	return mxa_intres_collect[mxs_index(_c,0,p,_IntResExpr_)];
}

static AttInstSq *mxw_term_basesorts;
ELEMENT  mxx_term_basesorts( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_SortId_,f,l,"term_basesorts",1)
	return mxa_term_basesorts[mxs_index(_c,0,p,_SortId_)];
}
static AttInstSq *mxw_node_basesorts;
ELEMENT  mxx_node_basesorts( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_SortId_,f,l,"node_basesorts",1)
	return mxa_node_basesorts[mxs_index(_c,0,p,_SortId_)];
}
ELEMENT  mxx_encl_scope( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Scope_,f,l,"encl_scope",1)
	return mxa_encl_scope[mxs_index(_c,0,p,_Scope_)];
}
ELEMENT  mxx_bind_pos( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Name_,f,l,"bind_pos",1)
	return mxa_bind_pos[mxs_index(_c,0,p,_Name_)];
}
ELEMENT  mxx_numberofastrks( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ItemList_,f,l,"numberofastrks",1)
	return mxa_numberofastrks[mxs_index(_c,0,p,_ItemList_)];
}
ELEMENT  mxx_predeclprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_PredeclProd_,f,l,"predeclprodcd",1)
	return mxa_predeclprodcd[mxs_index(_c,0,p,_PredeclProd_)];
}
ELEMENT  mxx_tupelprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_TupelProd_,f,l,"tupelprodcd",1)
	return mxa_tupelprodcd[mxs_index(_c,0,p,_TupelProd_)];
}
ELEMENT  mxx_listprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ListProd_,f,l,"listprodcd",1)
	return mxa_listprodcd[mxs_index(_c,0,p,_ListProd_)];
}
ELEMENT  mxx_classprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ClassProd_,f,l,"classprodcd",1)
	return mxa_classprodcd[mxs_index(_c,0,p,_ClassProd_)];
}
ELEMENT  mxx_patnpos( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Pattern_,f,l,"patnpos",1)
	return mxa_patnpos[mxs_index(_c,0,p,_Pattern_)];
}
ELEMENT  mxx_num_items( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Pattern_,f,l,"num_items",1)
	return mxa_num_items[mxs_index(_c,0,p,_Pattern_)];
}
ELEMENT  mxx_args( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"args",1)
	return mxa_args[mxs_index(_c,0,p,_FuncAppl_)];
}
ELEMENT  mxx_caseexpr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IfCase_,f,l,"caseexpr",1)
	return mxa_caseexpr[mxs_index(_c,0,p,_IfCase_)];
}
ELEMENT  mxx_allexpr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IfExpr_,f,l,"allexpr",1)
	return mxa_allexpr[mxs_index(_c,0,p,_IfExpr_)];
}
ELEMENT  mxx_encl_patterncase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Node,f,l,"encl_patterncase",1)
	return mxa_encl_patterncase[mxs_index(_c,0,p,_Node)];
}
ELEMENT  mxx_top_pattern( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Node,f,l,"top_pattern",1)
	return mxa_top_pattern[mxs_index(_c,0,p,_Node)];
}
ELEMENT  mxx_son_nr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"son_nr",1)
	return mxa_son_nr[mxs_index(_c,0,p,_FctOrAtt_)];
}
ELEMENT  mxx_relacc_nr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"relacc_nr",1)
	return mxa_relacc_nr[mxs_index(_c,0,p,_FuncAppl_)];
}
ELEMENT  mxx_appl_list_formula( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Formula_,f,l,"appl_list_formula",1)
	return mxa_appl_list_formula[mxs_index(_c,0,p,_Formula_)];
}
ELEMENT  mxx_appl_list_case( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Case_,f,l,"appl_list_case",1)
	return mxa_appl_list_case[mxs_index(_c,0,p,_Case_)];
}
ELEMENT  mxx_appl_list_expr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Expr_,f,l,"appl_list_expr",1)
	return mxa_appl_list_expr[mxs_index(_c,0,p,_Expr_)];
}
ELEMENT  mxx_appl_list( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"appl_list",1)
	return mxa_appl_list[mxs_index(_c,0,p,_FctOrAtt_)];
}
ELEMENT  mxx_def_value( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_DefId_,f,l,"def_value",1)
	return mxa_def_value[mxs_index(_c,0,p,_DefId_)];
}
ELEMENT  mxx_node_parnr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAttDecl_,f,l,"node_parnr",1)
	return mxa_node_parnr[mxs_index(_c,0,p,_FctOrAttDecl_)];
}
ELEMENT  mxx_appl_value( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"appl_value",1)
	return mxa_appl_value[mxs_index(_c,0,p,_FuncAppl_)];
}
ELEMENT  mxx_nodepar_expr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"nodepar_expr",1)
	return mxa_nodepar_expr[mxs_index(_c,0,p,_FuncAppl_)];
}
static AttInstSq *mxw_valueterm_list;
ELEMENT  mxx_valueterm_list( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Case_,f,l,"valueterm_list",1)
	return mxa_valueterm_list[mxs_index(_c,0,p,_Case_)];
}
static AttInstSq *mxw_valueterm;
ELEMENT  mxx_valueterm( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Expr_,f,l,"valueterm",1)
	return mxa_valueterm[mxs_index(_c,0,p,_Expr_)];
}
ELEMENT  mxx_attr_list_matlist( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuAtList_,f,l,"attr_list_matlist",1)
	return mxa_attr_list_matlist[mxs_index(_c,0,p,_FuAtList_)];
}
ELEMENT  mxx_result_value( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"result_value",1)
	return mxa_result_value[mxs_index(_c,0,p,_FctOrAtt_)];
}
ELEMENT  mxx_is_relev_att_access( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"is_relev_att_access",1)
	return mxa_is_relev_att_access[mxs_index(_c,0,p,_FuncAppl_)];
}
ELEMENT  mxx_appl_order( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"appl_order",1)
	return mxa_appl_order[mxs_index(_c,0,p,_FuncAppl_)];
}
ELEMENT  mxx_appl_relacc_list( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"appl_relacc_list",1)
	return mxa_appl_relacc_list[mxs_index(_c,0,p,_FctOrAtt_)];
}
ELEMENT  mxx_maybe_wait( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"maybe_wait",1)
	return mxa_maybe_wait[mxs_index(_c,0,p,_FuncAppl_)];
}
static AttInstSq *mxw_cgen_name;
ELEMENT  mxx_cgen_name( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IntResOrName_,f,l,"cgen_name",1)
	return mxa_cgen_name[mxs_index(_c,0,p,_IntResOrName_)];
}
ELEMENT  mxx_sces_appl( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ApplyEntity_,f,l,"sces_appl",1)
	return mxa_sces_appl[mxs_index(_c,0,p,_ApplyEntity_)];
}
ELEMENT  mxx_sces1_cond( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Condition_,f,l,"sces1_cond",1)
	return mxa_sces1_cond[mxs_index(_c,0,p,_Condition_)];
}
ELEMENT  mxx_sces2_cond( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Condition_,f,l,"sces2_cond",1)
	return mxa_sces2_cond[mxs_index(_c,0,p,_Condition_)];
}
ELEMENT  mxx_sces1_let( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_LetExpr_,f,l,"sces1_let",1)
	return mxa_sces1_let[mxs_index(_c,0,p,_LetExpr_)];
}
ELEMENT  mxx_sces2_let( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_LetExpr_,f,l,"sces2_let",1)
	return mxa_sces2_let[mxs_index(_c,0,p,_LetExpr_)];
}
ELEMENT  mxx_sces_if( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IfExpr_,f,l,"sces_if",1)
	return mxa_sces_if[mxs_index(_c,0,p,_IfExpr_)];
}
ELEMENT  mxx_sces1_fcase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FormulaCase_,f,l,"sces1_fcase",1)
	return mxa_sces1_fcase[mxs_index(_c,0,p,_FormulaCase_)];
}
ELEMENT  mxx_sces2_fcase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FormulaCase_,f,l,"sces2_fcase",1)
	return mxa_sces2_fcase[mxs_index(_c,0,p,_FormulaCase_)];
}
ELEMENT  mxx_sces_pcase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_PatternCase_,f,l,"sces_pcase",1)
	return mxa_sces_pcase[mxs_index(_c,0,p,_PatternCase_)];
}
ELEMENT  mxx_sces_attacc( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"sces_attacc",1)
	return mxa_sces_attacc[mxs_index(_c,0,p,_FuncAppl_)];
}
ELEMENT  mxx_lokvar_need( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"lokvar_need",1)
	return mxa_lokvar_need[mxs_index(_c,0,p,_FctOrAtt_)];
}
ELEMENT  mxx_intres_collect( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IntResExpr_,f,l,"intres_collect",1)
	return mxa_intres_collect[mxs_index(_c,0,p,_IntResExpr_)];
}



ELEMENT  mxs_encl_dynfunc(char *f, int l,ELEMENT N){
ELEMENT mxv_i1;
 IFNIL(N)

	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_DynFunc_) ) goto Lp1;
			mxv_i1 = N;
			goto L1;
		}
		Lp1: ;
			mxv_i1 = mxs_encl_dynfunc(_m,302,mxs_fath(_m,302,N));
		L1: ;
	}
	return mxv_i1;
}

ELEMENT  mxs_ss(char *f, int l,ELEMENT Str){
 IFNIL(Str)

	return mxs_term(_m,317,Str);
}

ELEMENT  mxs_id(char *f, int l,ELEMENT ID){
 IFNIL(ID)

	return mxs_idtos(_m,319,mxs_term(_m,319,ID));
}

ELEMENT  mxs_patlineno(char *f, int l,ELEMENT PN){
ELEMENT mxv_i2, L_p5;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp2;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp2;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp2;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp2;
			L_p5 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = L_p5;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp2;
			mxv_i2 = L_p5;
			goto L2;
		}
		Lp2: ;
			mxv_i2 = mxs_son(_m,321,mxs_itoe(_c,0,2),mxs_son(_m,321,mxs_itoe(_c,0,1),PN));
		L2: ;
	}
	return mxv_i2;
}

ELEMENT  mxs_patfilename(char *f, int l,ELEMENT PN){
ELEMENT mxv_i3, F_p8;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp3;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp3;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp3;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp3;
			F_p8 = mxs_son(_c,0,2,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = F_p8;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp3;
			mxv_i3 = F_p8;
			goto L3;
		}
		Lp3: ;
			mxv_i3 = mxs_son(_m,323,mxs_itoe(_c,0,4),mxs_son(_m,323,mxs_itoe(_c,0,1),PN));
		L3: ;
	}
	return mxv_i3;
}

ELEMENT  mxs_decl(char *f, int l,ELEMENT UID){


	return mxs_subterm(_m,352,mxs_itoe(_c,0,1),mxs_idtodecls(_m,352,mxs_term(_m,352,mxs_son(_m,352,mxs_itoe(_c,0,1),UID))));
}

ELEMENT  mxs_sort_union(char *f, int l,ELEMENT X,ELEMENT Y){
ELEMENT mxv_i25, mxv_i24, mxv_i23;
 IFNIL(X) IFNIL(Y)

	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,X,mxs_AllNodes(_m,375)) ){
			mxv_i24 = mxs_true(_m,0);
			goto L24;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,Y,mxs_AllNodes(_m,375)) ){
			mxv_i25 = mxs_true(_m,0);
			goto L25;
		}
		mxv_i25 = mxs_false(_m,0);
		L25: ;
	}
		mxv_i24 = mxv_i25;
		L24: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i24) ){
			mxv_i23 = mxs_AllNodes(_m,375);
			goto L23;
		}
		mxv_i23 = mxs_conc(_m,376,X,Y);
		L23: ;
	}
	return mxv_i23;
}

ELEMENT  mxs_scope(char *f, int l,ELEMENT N){
ELEMENT mxv_i49, L_p107;
 IFNIL(N)

	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Scope_) ) goto Lp8;
			mxv_i49 = N;
			goto L49;
		}
		Lp8: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp9;
			L_p107 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = L_p107;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp9;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp9;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp9;
			mxv_i49 = mxs_scope(_m,458,mxs_fath(_m,458,L_p107));
			goto L49;
		}
		Lp9: ;
			mxv_i49 = mxs_scope(_m,459,mxs_fath(_m,459,N));
		L49: ;
	}
	return mxv_i49;
}

ELEMENT  mxs_lookup_params(char *f, int l,ELEMENT ID,ELEMENT N){
ELEMENT mxv_i52, mxv_i51, IDN_p112;
 IFNIL(N)
 IS(N,_Name_,f,l,"lookup_params",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 4 ) goto Lp12;
			if( !mxs_is(_c,0,mxv_IR,_Name_) ) goto Lp12;
			IDN_p112 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = IDN_p112;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp12;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,ID,mxs_term(_m,469,IDN_p112)) ){
				mxv_i52 = N;
				goto L52;
			}
			mxv_i52 = mxs_lookup_params(_m,470,ID,mxs_rbroth(_m,470,N));
			L52: ;
		}
			mxv_i51 = mxv_i52;
			goto L51;
		}
		Lp12: ;
			mxv_i51 = mxs_nil(_m,471);
		L51: ;
	}
	return mxv_i51;
}

ELEMENT  mxs_lookup_item(char *f, int l,ELEMENT ID,ELEMENT IT){
ELEMENT mxv_i54, mxv_i53, ILP_p114, N_p115, IDN_p116, IT1_p119;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"lookup_item",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp13;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp13;
			ILP_p114 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ILP_p114;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp13;
			N_p115 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p115;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp13;
			if( mxs_numsons(_c,0, mxv_IR ) != 4 ) goto Lp13;
			IDN_p116 = mxs_son(_c,0,1,mxs_son(_c,0,3,mxv_anchor));
			mxv_IR = IDN_p116;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp13;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,ID,mxs_term(_m,476,IDN_p116)) ){
				mxv_i54 = N_p115;
				goto L54;
			}
			if( mxs_is(_m,477,ILP_p114,_ItemList_) ){
				mxv_i54 = mxs_lookup_items(_m,477,ID,mxs_son(_m,477,mxs_itoe(_c,0,1),ILP_p114));
				goto L54;
			}
			mxv_i54 = mxs_nil(_m,478);
			L54: ;
		}
			mxv_i53 = mxv_i54;
			goto L53;
		}
		Lp13: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp14;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp14;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp14;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp14;
			if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp14;
			IT1_p119 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = IT1_p119;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp14;
			mxv_IR = mxs_son(_c,0,3,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp14;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp14;
			mxv_i53 = mxs_lookup_items(_m,479,ID,IT1_p119);
			goto L53;
		}
		Lp14: ;
			mxv_i53 = mxs_nil(_m,480);
		L53: ;
	}
	return mxv_i53;
}

ELEMENT  mxs_lookup_items(char *f, int l,ELEMENT ID,ELEMENT IT){
ELEMENT mxv_i55, mxv_l5, N_l5;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"lookup_items",1)
	{  /* LetExpr */
		N_l5 = mxs_lookup_item(_m,484,ID,IT);
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,N_l5,mxs_nil(_m,485))) ){
				mxv_i55 = N_l5;
				goto L55;
			}
			mxv_i55 = mxs_lookup_items(_m,486,ID,mxs_rbroth(_m,486,IT));
			L55: ;
		}
		mxv_l5 = mxv_i55;
	}
	return mxv_l5;
}

ELEMENT  mxs_lookup_cond(char *f, int l,ELEMENT ID,ELEMENT PAT){
ELEMENT mxv_i56, mxv_l6, N_l6;
 IFNIL(PAT)
 IS(PAT,_Pattern_,f,l,"lookup_cond",1)
	{  /* LetExpr */
		N_l6 = mxs_lookup_item(_m,490,ID,PAT);
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,N_l6,mxs_nil(_m,491))) ){
				mxv_i56 = N_l6;
				goto L56;
			}
			mxv_i56 = mxs_lookup_cond(_m,492,ID,mxs_rbroth(_m,492,PAT));
			L56: ;
		}
		mxv_l6 = mxv_i56;
	}
	return mxv_l6;
}

ELEMENT  mxs_lookup(char *f, int l,ELEMENT ID,ELEMENT S){
ELEMENT mxv_i58, mxv_i59, mxv_l7, L_l7, mxv_i57, N_p122, NID_p123, PAR_p126, PAT_p129, PAT_p131;
 IFNIL(S)

	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp15;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp15;
			N_p122 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = N_p122;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp15;
			if( mxs_numsons(_c,0, mxv_IR ) != 4 ) goto Lp15;
			NID_p123 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = NID_p123;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp15;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_term(_m,497,NID_p123),ID) ){
				mxv_i58 = N_p122;
				goto L58;
			}
			mxv_i58 = mxs_lookup(_m,497,ID,mxs_encl_scope(_m,497,S));
			L58: ;
		}
			mxv_i57 = mxv_i58;
			goto L57;
		}
		Lp15: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 3 ) goto Lp16;
			if( !mxs_is(_c,0,mxv_IR,_ApplyEntity_) ) goto Lp16;
			mxv_IR = mxs_son(_c,0,3,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp16;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp16;
			PAR_p126 = mxs_son(_c,0,1,mxs_son(_c,0,3,mxv_anchor));
			mxv_IR = PAR_p126;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp16;
			mxv_i57 = mxs_lookup_params(_m,498,ID,PAR_p126);
			goto L57;
		}
		Lp16: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp17;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp17;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp17;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp17;
			PAT_p129 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = PAT_p129;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp17;
			mxv_i57 = mxs_lookup_cond(_m,499,ID,PAT_p129);
			goto L57;
		}
		Lp17: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp18;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp18;
			PAT_p131 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = PAT_p131;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp18;
		{  /* LetExpr */
			L_l7 = mxs_lookup(_m,501,ID,mxs_encl_scope(_m,501,S));
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,L_l7,mxs_nil(_m,502))) ){
					mxv_i59 = L_l7;
					goto L59;
				}
				mxv_i59 = mxs_lookup_item(_m,503,ID,PAT_p131);
				L59: ;
			}
			mxv_l7 = mxv_i59;
		}
			mxv_i57 = mxv_l7;
			goto L57;
		}
		Lp18: ;
			mxv_i57 = mxs_nil(_m,504);
		L57: ;
	}
	return mxv_i57;
}

ELEMENT  mxs_countastrks(char *f, int l,ELEMENT ITL,ELEMENT sum){
ELEMENT mxv_i68;
 IFNIL(ITL) IFNIL(sum)

	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,ITL,mxs_ItemList(_m,540)) ){
			mxv_i68 = sum;
			goto L68;
		}
		if( mxs_is(_m,541,mxs_subterm(_m,541,mxs_itoe(_c,0,1),ITL),_Asterisk) ){
			mxv_i68 = mxs_countastrks(_m,541,mxs_back(_m,541,ITL),mxs_add(_m,541,sum,mxs_itoe(_c,0,1)));
			goto L68;
		}
		mxv_i68 = mxs_countastrks(_m,542,mxs_back(_m,542,ITL),sum);
		L68: ;
	}
	return mxv_i68;
}

ELEMENT  mxs_smallestlistprodcd(char *f, int l){
	return mxs_neg(_m,614,mxs_add(_m,614,mxs_number(_m,614,_ListProd_),mxs_add(_m,615,mxs_number(_m,615,_TupelProd_),mxs_sub(_m,615,mxs_number(_m,615,_PredeclProd_),mxs_itoe(_c,0,2)))));
}

ELEMENT  mxs_prodcd(char *f, int l,ELEMENT PN){
ELEMENT mxv_i83;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_PredeclProd_) ) goto Lp20;
			mxv_i83 = mxs_predeclprodcd(_m,622,PN);
			goto L83;
		}
		Lp20: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp21;
			mxv_i83 = mxs_classprodcd(_m,623,PN);
			goto L83;
		}
		Lp21: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_TupelProd_) ) goto Lp22;
			mxv_i83 = mxs_tupelprodcd(_m,624,PN);
			goto L83;
		}
		Lp22: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_ListProd_) ) goto Lp23;
			mxv_i83 = mxs_listprodcd(_m,625,PN);
			goto L83;
		}
		Lp23: ;
			mxv_i83 = mxs_nil(_m,626);
		L83: ;
	}
	return mxv_i83;
}

ELEMENT  mxs_next_left_pat(char *f, int l,ELEMENT IT){
ELEMENT mxv_i84, mxv_l11, LIT_l11;
 IFNIL(IT)

	{  /* LetExpr */
		LIT_l11 = mxs_lbroth(_m,638,IT);
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l11;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp24;
				mxv_i84 = mxs_next_left_pat(_m,639,LIT_l11);
				goto L84;
			}
			Lp24: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l11;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp25;
				mxv_i84 = mxs_next_left_pat(_m,640,LIT_l11);
				goto L84;
			}
			Lp25: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l11;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp26;
				mxv_i84 = LIT_l11;
				goto L84;
			}
			Lp26: ;
				mxv_i84 = mxs_nil(_m,642);
			L84: ;
		}
		mxv_l11 = mxv_i84;
	}
	return mxv_l11;
}

ELEMENT  mxs_patnposition(char *f, int l,ELEMENT IT,ELEMENT dist){
ELEMENT mxv_i85, mxv_l12, LIT_l12;
 IFNIL(dist)

	{  /* LetExpr */
		LIT_l12 = mxs_lbroth(_m,646,IT);
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l12;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp27;
				mxv_i85 = mxs_patnposition(_m,647,LIT_l12,mxs_add(_m,647,dist,mxs_itoe(_c,0,1)));
				goto L85;
			}
			Lp27: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l12;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp28;
				mxv_i85 = mxs_patnposition(_m,648,LIT_l12,dist);
				goto L85;
			}
			Lp28: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l12;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp29;
				mxv_i85 = dist;
				goto L85;
			}
			Lp29: ;
				mxv_i85 = dist;
			L85: ;
		}
		mxv_l12 = mxv_i85;
	}
	return mxv_l12;
}

ELEMENT  mxs_next_pat_for_codegen(char *f, int l,ELEMENT PN){
ELEMENT mxv_i88, mxv_l13, NLP_l13, mxv_i87, SPN_p192, IT_p195;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp30;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp30;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp30;
			if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp30;
			SPN_p192 = mxs_son(_c,0,-1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = SPN_p192;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp30;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp30;
			mxv_i87 = SPN_p192;
			goto L87;
		}
		Lp30: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp31;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp31;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp31;
			if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp31;
			IT_p195 = mxs_son(_c,0,-1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = IT_p195;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp31;
		{  /* LetExpr */
			NLP_l13 = mxs_next_left_pat(_m,662,IT_p195);
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,NLP_l13,mxs_nil(_m,663))) ){
					mxv_i88 = NLP_l13;
					goto L88;
				}
				mxv_i88 = mxs_next_pat_upthetree(_m,663,PN);
				L88: ;
			}
			mxv_l13 = mxv_i88;
		}
			mxv_i87 = mxv_l13;
			goto L87;
		}
		Lp31: ;
			mxv_i87 = mxs_next_pat_upthetree(_m,664,PN);
		L87: ;
	}
	return mxv_i87;
}

ELEMENT  mxs_next_pat_upthetree(char *f, int l,ELEMENT PN){
ELEMENT mxv_i89;

 IS(PN,_Pattern_,f,l,"next_pat_upthetree",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,668,mxs_patnpos(_m,668,PN),_TopPosition) ){
			mxv_i89 = mxs_rbroth(_m,668,PN);
			goto L89;
		}
		if( mxs_is(_m,669,mxs_patnpos(_m,669,PN),_AbsPosition) ){
			mxv_i89 = mxs_next_pat_upthetree(_m,669,mxs_fath(_m,669,mxs_fath(_m,669,PN)));
			goto L89;
		}
		mxv_i89 = mxs_next_left_pat(_m,670,PN);
		L89: ;
	}
	return mxv_i89;
}

ELEMENT  mxs_pat_absoff_pos(char *f, int l,ELEMENT N){
ELEMENT mxv_i90;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_absoff_pos",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,679,N),mxs_nil(_m,679)) ){
			mxv_i90 = mxs_itoe(_c,0,1);
			goto L90;
		}
		if( mxs_is(_m,680,mxs_lbroth(_m,680,N),_Asterisk_) ){
			mxv_i90 = mxs_nil(_m,680);
			goto L90;
		}
		mxv_i90 = mxs_add(_m,681,mxs_pat_absoff_pos(_m,681,mxs_lbroth(_m,681,N)),mxs_itoe(_c,0,1));
		L90: ;
	}
	return mxv_i90;
}

ELEMENT  mxs_pat_reloff_pos(char *f, int l,ELEMENT N,ELEMENT target){
ELEMENT mxv_i91;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_reloff_pos",1)
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,685,mxs_fath(_m,685,N),_ItemList_)) ){
			mxv_i91 = mxs_nil(_m,685);
			goto L91;
		}
		if( mxs_is(_m,686,mxs_lbroth(_m,686,N),_Asterisk_) ){
			mxv_i91 = mxs_nil(_m,686);
			goto L91;
		}
		if( mxs_eq(_m,0,mxs_lbroth(_m,687,N),target) ){
			mxv_i91 = mxs_itoe(_c,0,1);
			goto L91;
		}
		mxv_i91 = mxs_add(_m,688,mxs_pat_reloff_pos(_m,688,mxs_lbroth(_m,688,N),target),mxs_itoe(_c,0,1));
		L91: ;
	}
	return mxv_i91;
}

ELEMENT  mxs_pat_absoff_neg(char *f, int l,ELEMENT N){
ELEMENT mxv_i92;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_absoff_neg",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,695,N),mxs_nil(_m,695)) ){
			mxv_i92 = mxs_itoe(_c,0,-1);
			goto L92;
		}
		if( mxs_is(_m,696,mxs_rbroth(_m,696,N),_Asterisk_) ){
			mxv_i92 = mxs_nil(_m,696);
			goto L92;
		}
		mxv_i92 = mxs_sub(_m,697,mxs_pat_absoff_neg(_m,697,mxs_rbroth(_m,697,N)),mxs_itoe(_c,0,1));
		L92: ;
	}
	return mxv_i92;
}

ELEMENT  mxs_pat_reloff_neg(char *f, int l,ELEMENT N,ELEMENT target){
ELEMENT mxv_i93;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_reloff_neg",1)
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,701,mxs_fath(_m,701,N),_ItemList_)) ){
			mxv_i93 = mxs_nil(_m,701);
			goto L93;
		}
		if( mxs_is(_m,702,mxs_rbroth(_m,702,N),_Asterisk_) ){
			mxv_i93 = mxs_nil(_m,702);
			goto L93;
		}
		if( mxs_eq(_m,0,mxs_rbroth(_m,703,N),target) ){
			mxv_i93 = mxs_itoe(_c,0,-1);
			goto L93;
		}
		mxv_i93 = mxs_sub(_m,704,mxs_pat_reloff_neg(_m,704,mxs_rbroth(_m,704,N),target),mxs_itoe(_c,0,1));
		L93: ;
	}
	return mxv_i93;
}

ELEMENT  mxs_pat_absoff(char *f, int l,ELEMENT N){
ELEMENT mxv_i94, mxv_l14, X_l14;


	{  /* LetExpr */
		X_l14 = mxs_pat_absoff_pos(_m,711,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,X_l14,mxs_nil(_m,712)) ){
				mxv_i94 = mxs_pat_absoff_neg(_m,712,N);
				goto L94;
			}
			mxv_i94 = X_l14;
			L94: ;
		}
		mxv_l14 = mxv_i94;
	}
	return mxv_l14;
}

ELEMENT  mxs_pat_reloff(char *f, int l,ELEMENT N,ELEMENT target){
ELEMENT mxv_i95, mxv_l15, X_l15;


	{  /* LetExpr */
		X_l15 = mxs_pat_reloff_pos(_m,716,N,target);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,X_l15,mxs_nil(_m,717)) ){
				mxv_i95 = mxs_pat_reloff_neg(_m,717,N,target);
				goto L95;
			}
			mxv_i95 = X_l15;
			L95: ;
		}
		mxv_l15 = mxv_i95;
	}
	return mxv_l15;
}

ELEMENT  mxs_abs_itempos(char *f, int l,ELEMENT N){
ELEMENT mxv_i96;


	{  /* FormulaCaseList */
		if( mxs_is(_m,725,mxs_fath(_m,725,N),_ItemList_) ){
			mxv_i96 = mxs_pat_absoff(_m,725,N);
			goto L96;
		}
		mxv_i96 = mxs_itoe(_c,0,0);
		L96: ;
	}
	return mxv_i96;
}

ELEMENT  mxs_lmin_itempos(char *f, int l,ELEMENT N){
ELEMENT mxv_i99, mxv_i98, mxv_i97;
 IFNIL(N)
 IS(N,_Item_,f,l,"lmin_itempos",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_lbroth(_m,729,N),mxs_nil(_m,729))) ){
			mxv_i98 = mxs_false(_m,0);
			goto L98;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,729,N,_Asterisk_)) ){
			mxv_i99 = mxs_true(_m,0);
			goto L99;
		}
		mxv_i99 = mxs_false(_m,0);
		L99: ;
	}
		mxv_i98 = mxv_i99;
		L98: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i98) ){
			mxv_i97 = mxs_itoe(_c,0,1);
			goto L97;
		}
		if( mxs_eq(_m,0,mxs_lbroth(_m,730,N),mxs_nil(_m,730)) ){
			mxv_i97 = mxs_itoe(_c,0,0);
			goto L97;
		}
		if( mxs_is(_m,731,N,_Asterisk_) ){
			mxv_i97 = mxs_lmin_itempos(_m,731,mxs_lbroth(_m,731,N));
			goto L97;
		}
		mxv_i97 = mxs_add(_m,732,mxs_lmin_itempos(_m,732,mxs_lbroth(_m,732,N)),mxs_itoe(_c,0,1));
		L97: ;
	}
	return mxv_i97;
}

ELEMENT  mxs_rmin_itempos(char *f, int l,ELEMENT N){
ELEMENT mxv_i102, mxv_i101, mxv_i100;
 IFNIL(N)
 IS(N,_Item_,f,l,"rmin_itempos",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_rbroth(_m,735,N),mxs_nil(_m,735))) ){
			mxv_i101 = mxs_false(_m,0);
			goto L101;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,735,N,_Asterisk_)) ){
			mxv_i102 = mxs_true(_m,0);
			goto L102;
		}
		mxv_i102 = mxs_false(_m,0);
		L102: ;
	}
		mxv_i101 = mxv_i102;
		L101: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i101) ){
			mxv_i100 = mxs_itoe(_c,0,-1);
			goto L100;
		}
		if( mxs_eq(_m,0,mxs_rbroth(_m,736,N),mxs_nil(_m,736)) ){
			mxv_i100 = mxs_itoe(_c,0,0);
			goto L100;
		}
		if( mxs_is(_m,737,N,_Asterisk_) ){
			mxv_i100 = mxs_rmin_itempos(_m,737,mxs_rbroth(_m,737,N));
			goto L100;
		}
		mxv_i100 = mxs_sub(_m,738,mxs_rmin_itempos(_m,738,mxs_rbroth(_m,738,N)),mxs_itoe(_c,0,1));
		L100: ;
	}
	return mxv_i100;
}

ELEMENT  mxs_path(char *f, int l,ELEMENT V,ELEMENT N){
ELEMENT mxv_i105, mxv_i104, mxv_l17, VR_l17, mxv_i106, mxv_i103, mxv_l16, VA_l16;

 IS(V,_Item_,f,l,"path",1) IS(N,_Item_,f,l,"path",2)
	{  /* LetExpr */
		VA_l16 = mxs_pat_absoff(_m,747,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_fath(_m,748,V),mxs_fath(_m,748,N)) ){
			{  /* LetExpr */
				VR_l17 = mxs_pat_reloff(_m,749,V,N);
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,V,N) ){
						mxv_i104 = mxs_Relationship(_m,750);
						goto L104;
					}
					if( ( ! mxs_eq(_m,0,VR_l17,mxs_nil(_m,751))) ){
					{  /* FormulaCaseList */
						if( mxs_lt(_m,752,mxs_itoe(_c,0,0),VR_l17) ){
							mxv_i105 = mxs_appfront(_m,752,mxs_Lbroth(_m,752,VR_l17),mxs_Relationship(_m,752));
							goto L105;
						}
						mxv_i105 = mxs_appfront(_m,753,mxs_Rbroth(_m,753,mxs_neg(_m,753,VR_l17)),mxs_Relationship(_m,753));
						L105: ;
					}
						mxv_i104 = mxv_i105;
						goto L104;
					}
					if( ( ! mxs_eq(_m,0,VA_l16,mxs_nil(_m,755))) ){
						mxv_i104 = mxs_appfront(_m,755,mxs_Son(_m,755,VA_l16),mxs_appfront(_m,755,mxs_Fath(_m,755),mxs_Relationship(_m,755)));
						goto L104;
					}
					mxv_i104 = mxs_nil(_m,756);
					L104: ;
				}
				mxv_l17 = mxv_i104;
			}
				mxv_i103 = mxv_l17;
				goto L103;
			}
			if( mxs_desc(_m,758,V,mxs_fath(_m,758,mxs_fath(_m,758,N))) ){
				mxv_i103 = mxs_appback(_m,758,mxs_path(_m,758,mxs_fath(_m,758,mxs_fath(_m,758,V)),N),mxs_Fath(_m,758));
				goto L103;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,VA_l16,mxs_nil(_m,760))) ){
				mxv_i106 = mxs_appfront(_m,760,mxs_Son(_m,760,VA_l16),mxs_path(_m,760,V,mxs_fath(_m,760,mxs_fath(_m,760,N))));
				goto L106;
			}
			mxv_i106 = mxs_nil(_m,761);
			L106: ;
		}
			mxv_i103 = mxv_i106;
			L103: ;
		}
		mxv_l16 = mxv_i103;
	}
	return mxv_l16;
}

ELEMENT  mxs_search_bound_names_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_i107;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_bound_names_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,765,IT),mxs_nil(_m,765)) ){
			mxv_i107 = mxs_search_bound_names(_m,765,IT);
			goto L107;
		}
		mxv_i107 = mxs_conc(_m,766,mxs_search_bound_names(_m,766,IT),mxs_search_bound_names_rec(_m,766,mxs_rbroth(_m,766,IT)));
		L107: ;
	}
	return mxv_i107;
}

ELEMENT  mxs_search_bound_names(char *f, int l,ELEMENT IT){
ELEMENT mxv_i109, IT1_p200, mxv_i112, mxv_i111, mxv_i110, mxv_l18, BNL_l18, mxv_i108, ITL_p197, N_p198;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp32;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp32;
			ITL_p197 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p197;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp32;
			N_p198 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p198;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp32;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p197;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp33;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp33;
					IT1_p200 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p200;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp33;
					mxv_i109 = mxs_search_bound_names_rec(_m,771,IT1_p200);
					goto L109;
				}
				Lp33: ;
					mxv_i109 = mxs_NameNList(_m,772);
				L109: ;
			}
			BNL_l18 = mxv_i109;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,774,N_p198,_Name_)) ){
					mxv_i111 = mxs_false(_m,0);
					goto L111;
				}
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,mxs_bind_pos(_m,774,N_p198),N_p198)) ){
					mxv_i112 = mxs_true(_m,0);
					goto L112;
				}
				mxv_i112 = mxs_false(_m,0);
				L112: ;
			}
				mxv_i111 = mxv_i112;
				L111: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i111) ){
					mxv_i110 = mxs_appfront(_m,774,N_p198,BNL_l18);
					goto L110;
				}
				mxv_i110 = BNL_l18;
				L110: ;
			}
			mxv_l18 = mxv_i110;
		}
			mxv_i108 = mxv_l18;
			goto L108;
		}
		Lp32: ;
			mxv_i108 = mxs_NameNList(_m,777);
		L108: ;
	}
	return mxv_i108;
}

ELEMENT  mxs_search_free_items_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_i113;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_free_items_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,781,IT),mxs_nil(_m,781)) ){
			mxv_i113 = mxs_search_free_items(_m,781,IT);
			goto L113;
		}
		mxv_i113 = mxs_conc(_m,782,mxs_search_free_items(_m,782,IT),mxs_search_free_items_rec(_m,782,mxs_rbroth(_m,782,IT)));
		L113: ;
	}
	return mxv_i113;
}

ELEMENT  mxs_search_free_items(char *f, int l,ELEMENT IT){
ELEMENT mxv_i115, IT1_p205, mxv_i119, mxv_i118, mxv_i120, mxv_i117, mxv_i116, mxv_l19, FIL_l19, mxv_i114, ITL_p202, N_p203;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp34;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp34;
			ITL_p202 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p202;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp34;
			N_p203 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p203;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp34;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p202;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp35;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp35;
					IT1_p205 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p205;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp35;
					mxv_i115 = mxs_search_free_items_rec(_m,787,IT1_p205);
					goto L115;
				}
				Lp35: ;
					mxv_i115 = mxs_ItemNList(_m,788);
				L115: ;
			}
			FIL_l19 = mxv_i115;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,790,N_p203,_Name_)) ){
					mxv_i118 = mxs_false(_m,0);
					goto L118;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_bind_pos(_m,790,N_p203),N_p203) ){
					mxv_i119 = mxs_true(_m,0);
					goto L119;
				}
				mxv_i119 = mxs_false(_m,0);
				L119: ;
			}
				mxv_i118 = mxv_i119;
				L118: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i118) ){
					mxv_i117 = mxs_true(_m,0);
					goto L117;
				}
			{  /* FormulaCaseList */
				if( mxs_is(_m,790,N_p203,_Blank_) ){
					mxv_i120 = mxs_true(_m,0);
					goto L120;
				}
				mxv_i120 = mxs_false(_m,0);
				L120: ;
			}
				mxv_i117 = mxv_i120;
				L117: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i117) ){
					mxv_i116 = mxs_appfront(_m,791,IT,FIL_l19);
					goto L116;
				}
				mxv_i116 = FIL_l19;
				L116: ;
			}
			mxv_l19 = mxv_i116;
		}
			mxv_i114 = mxv_l19;
			goto L114;
		}
		Lp34: ;
			mxv_i114 = mxs_ItemNList(_m,794);
		L114: ;
	}
	return mxv_i114;
}

ELEMENT  mxs_search_blanks_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_i121;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_blanks_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,798,IT),mxs_nil(_m,798)) ){
			mxv_i121 = mxs_search_blanks(_m,798,IT);
			goto L121;
		}
		mxv_i121 = mxs_conc(_m,799,mxs_search_blanks(_m,799,IT),mxs_search_blanks_rec(_m,799,mxs_rbroth(_m,799,IT)));
		L121: ;
	}
	return mxv_i121;
}

ELEMENT  mxs_search_blanks(char *f, int l,ELEMENT IT){
ELEMENT mxv_i123, IT1_p210, mxv_i122, ITL_p207, N_p208;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp36;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp36;
			ITL_p207 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p207;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp36;
			N_p208 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p208;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp36;
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = ITL_p207;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp37;
				if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp37;
				IT1_p210 = mxs_son(_c,0,1,mxv_anchor);
				mxv_IR = IT1_p210;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp37;
				mxv_i123 = mxs_search_blanks_rec(_m,804,IT1_p210);
				goto L123;
			}
			Lp37: ;
				mxv_i123 = mxs_ItemNList(_m,805);
			L123: ;
		}
			mxv_i122 = mxv_i123;
			goto L122;
		}
		Lp36: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp38;
			mxv_i122 = mxs_appback(_m,807,mxs_ItemNList(_m,807),IT);
			goto L122;
		}
		Lp38: ;
			mxv_i122 = mxs_ItemNList(_m,809);
		L122: ;
	}
	return mxv_i122;
}

ELEMENT  mxs_search_free_p_names_rec(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_i132;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_free_p_names_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,869,IT),mxs_nil(_m,869)) ){
			mxv_i132 = mxs_search_free_p_names(_m,869,IT,ID);
			goto L132;
		}
		mxv_i132 = mxs_conc(_m,870,mxs_search_free_p_names(_m,870,IT,ID),mxs_search_free_p_names_rec(_m,870,mxs_rbroth(_m,870,IT),ID));
		L132: ;
	}
	return mxv_i132;
}

ELEMENT  mxs_search_free_p_names(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_i134, IT1_p230, mxv_i139, mxv_i138, mxv_i137, mxv_i136, mxv_i135, mxv_l21, PNL_l21, mxv_i133, ITL_p227, N_p228;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp40;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp40;
			ITL_p227 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p227;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp40;
			N_p228 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p228;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp40;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p227;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp41;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp41;
					IT1_p230 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p230;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp41;
					mxv_i134 = mxs_search_free_p_names_rec(_m,875,IT1_p230,ID);
					goto L134;
				}
				Lp41: ;
					mxv_i134 = mxs_ExprNList(_m,876);
				L134: ;
			}
			PNL_l21 = mxv_i134;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,878,N_p228,_Name_)) ){
					mxv_i136 = mxs_false(_m,0);
					goto L136;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! ( ! mxs_eq(_m,0,ID,mxs_term(_m,878,mxs_son(_m,878,mxs_itoe(_c,0,1),N_p228))))) ){
					mxv_i138 = mxs_false(_m,0);
					goto L138;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_bind_pos(_m,878,N_p228),N_p228) ){
					mxv_i139 = mxs_true(_m,0);
					goto L139;
				}
				mxv_i139 = mxs_false(_m,0);
				L139: ;
			}
				mxv_i138 = mxv_i139;
				L138: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i138) ){
					mxv_i137 = mxs_true(_m,0);
					goto L137;
				}
				mxv_i137 = mxs_false(_m,0);
				L137: ;
			}
				mxv_i136 = mxv_i137;
				L136: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i136) ){
					mxv_i135 = mxs_appfront(_m,878,N_p228,PNL_l21);
					goto L135;
				}
				mxv_i135 = PNL_l21;
				L135: ;
			}
			mxv_l21 = mxv_i135;
		}
			mxv_i133 = mxv_l21;
			goto L133;
		}
		Lp40: ;
			mxv_i133 = mxs_ExprNList(_m,881);
		L133: ;
	}
	return mxv_i133;
}

ELEMENT  mxs_search_bound_p_names_rec(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_i140;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_bound_p_names_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,885,IT),mxs_nil(_m,885)) ){
			mxv_i140 = mxs_search_bound_p_names(_m,885,IT,ID);
			goto L140;
		}
		mxv_i140 = mxs_conc(_m,886,mxs_search_bound_p_names(_m,886,IT,ID),mxs_search_bound_p_names_rec(_m,886,mxs_rbroth(_m,886,IT),ID));
		L140: ;
	}
	return mxv_i140;
}

ELEMENT  mxs_search_bound_p_names(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_i142, IT1_p235, mxv_i147, mxv_i146, mxv_i145, mxv_i144, mxv_i143, mxv_l22, PNL_l22, mxv_i141, ITL_p232, N_p233;
 IFNIL(IT)

	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp42;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp42;
			ITL_p232 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p232;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp42;
			N_p233 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p233;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp42;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p232;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp43;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp43;
					IT1_p235 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p235;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp43;
					mxv_i142 = mxs_search_bound_p_names_rec(_m,891,IT1_p235,ID);
					goto L142;
				}
				Lp43: ;
					mxv_i142 = mxs_ExprNList(_m,892);
				L142: ;
			}
			PNL_l22 = mxv_i142;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,894,N_p233,_Name_)) ){
					mxv_i144 = mxs_false(_m,0);
					goto L144;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! ( ! mxs_eq(_m,0,ID,mxs_term(_m,894,mxs_son(_m,894,mxs_itoe(_c,0,1),N_p233))))) ){
					mxv_i146 = mxs_false(_m,0);
					goto L146;
				}
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,mxs_bind_pos(_m,894,N_p233),N_p233)) ){
					mxv_i147 = mxs_true(_m,0);
					goto L147;
				}
				mxv_i147 = mxs_false(_m,0);
				L147: ;
			}
				mxv_i146 = mxv_i147;
				L146: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i146) ){
					mxv_i145 = mxs_true(_m,0);
					goto L145;
				}
				mxv_i145 = mxs_false(_m,0);
				L145: ;
			}
				mxv_i144 = mxv_i145;
				L144: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i144) ){
					mxv_i143 = mxs_appfront(_m,894,N_p233,PNL_l22);
					goto L143;
				}
				mxv_i143 = PNL_l22;
				L143: ;
			}
			mxv_l22 = mxv_i143;
		}
			mxv_i141 = mxv_l22;
			goto L141;
		}
		Lp42: ;
			mxv_i141 = mxs_ExprNList(_m,897);
		L141: ;
	}
	return mxv_i141;
}

ELEMENT  mxs_search_patt_names(char *f, int l,ELEMENT IT,ELEMENT ID){


	return mxs_conc(_m,901,mxs_search_bound_p_names(_m,901,IT,ID),mxs_search_free_p_names(_m,901,IT,ID));
}

ELEMENT  mxs_search_patt_sorts_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_i148;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_patt_sorts_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,905,IT),mxs_nil(_m,905)) ){
			mxv_i148 = mxs_search_patt_sorts(_m,905,IT);
			goto L148;
		}
		mxv_i148 = mxs_conc(_m,906,mxs_search_patt_sorts(_m,906,IT),mxs_search_patt_sorts_rec(_m,906,mxs_rbroth(_m,906,IT)));
		L148: ;
	}
	return mxv_i148;
}

ELEMENT  mxs_search_patt_sorts(char *f, int l,ELEMENT IT){
ELEMENT mxv_i150, IT1_p240, mxv_i151, mxv_l23, BNL_l23, mxv_i149, SORT_p237, ITL_p238;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp44;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp44;
			SORT_p237 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = SORT_p237;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp44;
			ITL_p238 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p238;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp44;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p238;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp45;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp45;
					IT1_p240 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p240;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp45;
					mxv_i150 = mxs_search_patt_sorts_rec(_m,910,IT1_p240);
					goto L150;
				}
				Lp45: ;
					mxv_i150 = mxs_SortIdNList(_m,911);
				L150: ;
			}
			BNL_l23 = mxv_i150;
			{  /* FormulaCaseList */
				if( mxs_is(_m,913,SORT_p237,_SortId_) ){
					mxv_i151 = mxs_appfront(_m,913,SORT_p237,BNL_l23);
					goto L151;
				}
				mxv_i151 = BNL_l23;
				L151: ;
			}
			mxv_l23 = mxv_i151;
		}
			mxv_i149 = mxv_l23;
			goto L149;
		}
		Lp44: ;
			mxv_i149 = mxs_SortIdNList(_m,916);
		L149: ;
	}
	return mxv_i149;
}

ELEMENT  mxs_search_name_in_patt_rec(char *f, int l,ELEMENT IT,ELEMENT NA){
ELEMENT mxv_i152;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_name_in_patt_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,920,IT),mxs_nil(_m,920)) ){
			mxv_i152 = mxs_search_name_in_patt(_m,920,IT,NA);
			goto L152;
		}
		mxv_i152 = mxs_conc(_m,921,mxs_search_name_in_patt(_m,921,IT,NA),mxs_search_name_in_patt_rec(_m,921,mxs_rbroth(_m,921,IT),NA));
		L152: ;
	}
	return mxv_i152;
}

ELEMENT  mxs_search_name_in_patt(char *f, int l,ELEMENT IT,ELEMENT NA){
ELEMENT mxv_i154, IT1_p245, mxv_i157, mxv_i156, mxv_i155, mxv_l24, BNL_l24, mxv_i153, ITL_p242, N_p243;
 IFNIL(IT)

	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp46;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp46;
			ITL_p242 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p242;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp46;
			N_p243 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p243;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp46;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p242;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp47;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp47;
					IT1_p245 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p245;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp47;
					mxv_i154 = mxs_search_name_in_patt_rec(_m,926,IT1_p245,NA);
					goto L154;
				}
				Lp47: ;
					mxv_i154 = mxs_NameNList(_m,927);
				L154: ;
			}
			BNL_l24 = mxv_i154;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,929,N_p243,_Name_)) ){
					mxv_i156 = mxs_false(_m,0);
					goto L156;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_term(_m,929,mxs_son(_m,929,mxs_itoe(_c,0,1),N_p243)),NA) ){
					mxv_i157 = mxs_true(_m,0);
					goto L157;
				}
				mxv_i157 = mxs_false(_m,0);
				L157: ;
			}
				mxv_i156 = mxv_i157;
				L156: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i156) ){
					mxv_i155 = mxs_appfront(_m,929,N_p243,BNL_l24);
					goto L155;
				}
				mxv_i155 = BNL_l24;
				L155: ;
			}
			mxv_l24 = mxv_i155;
		}
			mxv_i153 = mxv_l24;
			goto L153;
		}
		Lp46: ;
			mxv_i153 = mxs_NameNList(_m,932);
		L153: ;
	}
	return mxv_i153;
}

ELEMENT  mxs_latest_bindpos(char *f, int l,ELEMENT N,ELEMENT NA){
ELEMENT mxv_i160, mxv_i159, mxv_i161, mxv_l26, LBP_l26, mxv_i158, mxv_l25, S_l25;
 IFNIL(N)

	{  /* LetExpr */
		S_l25 = mxs_encl_patterncase(_m,936,N);
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! ( ! mxs_eq(_m,0,S_l25,mxs_nil(_m,937)))) ){
				mxv_i159 = mxs_false(_m,0);
				goto L159;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_desc(_m,937,mxs_bind_pos(_m,937,NA),S_l25)) ){
				mxv_i160 = mxs_true(_m,0);
				goto L160;
			}
			mxv_i160 = mxs_false(_m,0);
			L160: ;
		}
			mxv_i159 = mxv_i160;
			L159: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i159) ){
			{  /* LetExpr */
				LBP_l26 = mxs_search_name_in_patt(_m,938,mxs_son(_m,938,mxs_itoe(_c,0,1),S_l25),mxs_term(_m,938,mxs_son(_m,938,mxs_itoe(_c,0,1),NA)));
				{  /* FormulaCaseList */
					if( ( ! mxs_eq(_m,0,LBP_l26,mxs_NameNList(_m,939))) ){
						mxv_i161 = mxs_subterm(_m,939,mxs_itoe(_c,0,1),LBP_l26);
						goto L161;
					}
					mxv_i161 = mxs_latest_bindpos(_m,940,mxs_fath(_m,940,S_l25),NA);
					L161: ;
				}
				mxv_l26 = mxv_i161;
			}
				mxv_i158 = mxv_l26;
				goto L158;
			}
			mxv_i158 = mxs_bind_pos(_m,941,NA);
			L158: ;
		}
		mxv_l25 = mxv_i158;
	}
	return mxv_l25;
}

ELEMENT  mxs_par_pos(char *f, int l,ELEMENT N,ELEMENT cnt){
ELEMENT mxv_i162;
 IFNIL(N) IFNIL(cnt)
 IS(N,_Name_,f,l,"par_pos",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,945,N),mxs_nil(_m,945)) ){
			mxv_i162 = cnt;
			goto L162;
		}
		mxv_i162 = mxs_par_pos(_m,946,mxs_lbroth(_m,946,N),mxs_add(_m,946,mxs_itoe(_c,0,1),cnt));
		L162: ;
	}
	return mxv_i162;
}

ELEMENT  mxs_corresp_parsort(char *f, int l,ELEMENT N){


	return mxs_son(_m,950,mxs_par_pos(_m,950,N,mxs_itoe(_c,0,1)),mxs_lbroth(_m,950,mxs_fath(_m,950,N)));
}

ELEMENT  mxs_actpar_pos(char *f, int l,ELEMENT N,ELEMENT cnt){
ELEMENT mxv_i163;
 IFNIL(N) IFNIL(cnt)
 IS(N,_Expr_,f,l,"actpar_pos",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,954,N),mxs_nil(_m,954)) ){
			mxv_i163 = cnt;
			goto L163;
		}
		mxv_i163 = mxs_actpar_pos(_m,955,mxs_lbroth(_m,955,N),mxs_add(_m,955,mxs_itoe(_c,0,1),cnt));
		L163: ;
	}
	return mxv_i163;
}

ELEMENT  mxs_univ_path(char *f, int l,ELEMENT V,ELEMENT N){
ELEMENT mxv_i166, mxv_i165, mxv_l28, VR_l28, mxv_i167, mxv_i164, mxv_l27, VA_l27;

 IS(V,_Item_,f,l,"univ_path",1) IS(N,_Item_,f,l,"univ_path",2)
	{  /* LetExpr */
		VA_l27 = mxs_pat_absoff(_m,959,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_fath(_m,960,V),mxs_fath(_m,960,N)) ){
			{  /* LetExpr */
				VR_l28 = mxs_pat_reloff(_m,961,V,N);
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,V,N) ){
						mxv_i165 = mxs_Relationship(_m,962);
						goto L165;
					}
					if( ( ! mxs_eq(_m,0,VR_l28,mxs_nil(_m,963))) ){
					{  /* FormulaCaseList */
						if( mxs_lt(_m,964,mxs_itoe(_c,0,0),VR_l28) ){
							mxv_i166 = mxs_appfront(_m,964,mxs_Lbroth(_m,964,VR_l28),mxs_Relationship(_m,964));
							goto L166;
						}
						mxv_i166 = mxs_appfront(_m,965,mxs_Rbroth(_m,965,mxs_neg(_m,965,VR_l28)),mxs_Relationship(_m,965));
						L166: ;
					}
						mxv_i165 = mxv_i166;
						goto L165;
					}
					if( ( ! mxs_eq(_m,0,VA_l27,mxs_nil(_m,967))) ){
						mxv_i165 = mxs_appfront(_m,967,mxs_SonTC(_m,967,VA_l27,mxs_lmin_itempos(_m,967,N),mxs_rmin_itempos(_m,967,N),mxs_num_items(_m,968,mxs_fath(_m,968,mxs_fath(_m,968,N))),mxs_numberofastrks(_m,968,mxs_fath(_m,968,N))),mxs_appfront(_m,969,mxs_Fath(_m,969),mxs_Relationship(_m,969)));
						goto L165;
					}
					mxv_i165 = mxs_appfront(_m,970,mxs_SonTC(_m,970,mxs_itoe(_c,0,0),mxs_lmin_itempos(_m,970,N),mxs_rmin_itempos(_m,970,N),mxs_num_items(_m,971,mxs_fath(_m,971,mxs_fath(_m,971,N))),mxs_numberofastrks(_m,971,mxs_fath(_m,971,N))),mxs_appfront(_m,972,mxs_Fath(_m,972),mxs_Relationship(_m,972)));
					L165: ;
				}
				mxv_l28 = mxv_i165;
			}
				mxv_i164 = mxv_l28;
				goto L164;
			}
			if( mxs_desc(_m,974,V,mxs_fath(_m,974,mxs_fath(_m,974,N))) ){
				mxv_i164 = mxs_appback(_m,974,mxs_univ_path(_m,974,mxs_fath(_m,974,mxs_fath(_m,974,V)),N),mxs_Fath(_m,974));
				goto L164;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,VA_l27,mxs_nil(_m,976))) ){
				mxv_i167 = mxs_appfront(_m,976,mxs_SonTC(_m,976,VA_l27,mxs_lmin_itempos(_m,976,N),mxs_rmin_itempos(_m,976,N),mxs_num_items(_m,977,mxs_fath(_m,977,mxs_fath(_m,977,N))),mxs_numberofastrks(_m,977,mxs_fath(_m,977,N))),mxs_univ_path(_m,978,V,mxs_fath(_m,978,mxs_fath(_m,978,N))));
				goto L167;
			}
			mxv_i167 = mxs_appfront(_m,979,mxs_SonTC(_m,979,mxs_itoe(_c,0,0),mxs_lmin_itempos(_m,979,N),mxs_rmin_itempos(_m,979,N),mxs_num_items(_m,980,mxs_fath(_m,980,mxs_fath(_m,980,N))),mxs_numberofastrks(_m,980,mxs_fath(_m,980,N))),mxs_univ_path(_m,981,V,mxs_fath(_m,981,mxs_fath(_m,981,N))));
			L167: ;
		}
			mxv_i164 = mxv_i167;
			L164: ;
		}
		mxv_l27 = mxv_i164;
	}
	return mxv_l27;
}

ELEMENT  mxs_mk_enl(char *f, int l,ELEMENT ARG){
ELEMENT mxv_i168;
 IFNIL(ARG)
 IS(ARG,_Expr_,f,l,"mk_enl",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,985,ARG),mxs_nil(_m,985)) ){
			mxv_i168 = mxs_appfront(_m,985,ARG,mxs_ExprNList(_m,985));
			goto L168;
		}
		mxv_i168 = mxs_appfront(_m,986,ARG,mxs_mk_enl(_m,986,mxs_rbroth(_m,986,ARG)));
		L168: ;
	}
	return mxv_i168;
}

ELEMENT  mxs_dep_expr(char *f, int l,ELEMENT E){
ELEMENT mxv_i171, mxv_i170, mxv_i172, mxv_i169;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Name_) ) goto Lp48;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_bind_pos(_m,991,E),E) ){
			{  /* FormulaCaseList */
				if( mxs_is(_m,993,mxs_fath(_m,993,E),_NameList_) ){
					mxv_i171 = mxs_ExprNList(_m,993);
					goto L171;
				}
				if( mxs_is(_m,994,mxs_fath(_m,994,E),_LetExpr_) ){
					mxv_i171 = mxs_appfront(_m,994,mxs_rbroth(_m,994,E),mxs_ExprNList(_m,994));
					goto L171;
				}
				mxv_i171 = mxs_search_bound_p_names(_m,995,mxs_top_pattern(_m,995,E),mxs_term(_m,995,mxs_son(_m,995,mxs_itoe(_c,0,1),E)));
				L171: ;
			}
				mxv_i170 = mxv_i171;
				goto L170;
			}
			mxv_i170 = mxs_appfront(_m,997,mxs_latest_bindpos(_m,997,E,E),mxs_ExprNList(_m,997));
			L170: ;
		}
			mxv_i169 = mxv_i170;
			goto L169;
		}
		Lp48: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp49;
			mxv_i169 = mxs_allexpr(_m,999,E);
			goto L169;
		}
		Lp49: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp50;
			mxv_i169 = mxs_appfront(_m,1001,mxs_son(_m,1001,mxs_itoe(_c,0,3),E),mxs_ExprNList(_m,1001));
			goto L169;
		}
		Lp50: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp51;
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,mxs_numsons(_m,1003,mxs_son(_m,1003,mxs_itoe(_c,0,2),E)),mxs_itoe(_c,0,0))) ){
				mxv_i172 = mxs_mk_enl(_m,1003,mxs_son(_m,1003,mxs_itoe(_c,0,1),mxs_son(_m,1003,mxs_itoe(_c,0,2),E)));
				goto L172;
			}
			mxv_i172 = mxs_ExprNList(_m,1004);
			L172: ;
		}
			mxv_i169 = mxv_i172;
			goto L169;
		}
		Lp51: ;
			mxv_i169 = mxs_ExprNList(_m,1006);
		L169: ;
	}
	return mxv_i169;
}

ELEMENT  mxs_lineof(char *f, int l,ELEMENT E){
ELEMENT mxv_i173;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_SortConst_) ) goto Lp52;
			mxv_i173 = mxs_term(_m,1010,mxs_son(_m,1010,mxs_itoe(_c,0,2),mxs_son(_m,1010,mxs_itoe(_c,0,1),E)));
			goto L173;
		}
		Lp52: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp53;
			mxv_i173 = mxs_term(_m,1011,mxs_son(_m,1011,mxs_itoe(_c,0,2),mxs_son(_m,1011,mxs_itoe(_c,0,1),E)));
			goto L173;
		}
		Lp53: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp54;
			mxv_i173 = mxs_term(_m,1012,mxs_son(_m,1012,mxs_itoe(_c,0,3),E));
			goto L173;
		}
		Lp54: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp55;
			mxv_i173 = mxs_lineof(_m,1013,mxs_son(_m,1013,mxs_itoe(_c,0,3),E));
			goto L173;
		}
		Lp55: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_StringExpr_) ) goto Lp56;
			mxv_i173 = mxs_term(_m,1014,mxs_son(_m,1014,mxs_itoe(_c,0,2),E));
			goto L173;
		}
		Lp56: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_DynUndef_) ) goto Lp57;
			mxv_i173 = mxs_itoe(_c,0,0);
			goto L173;
		}
		Lp57: ;
			mxv_i173 = mxs_term(_m,1016,mxs_son(_m,1016,mxs_itoe(_c,0,2),E));
		L173: ;
	}
	return mxv_i173;
}

ELEMENT  mxs_colof(char *f, int l,ELEMENT E){
ELEMENT mxv_i174;


	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_SortConst_) ) goto Lp58;
			mxv_i174 = mxs_term(_m,1020,mxs_son(_m,1020,mxs_itoe(_c,0,3),mxs_son(_m,1020,mxs_itoe(_c,0,1),E)));
			goto L174;
		}
		Lp58: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp59;
			mxv_i174 = mxs_term(_m,1021,mxs_son(_m,1021,mxs_itoe(_c,0,3),mxs_son(_m,1021,mxs_itoe(_c,0,1),E)));
			goto L174;
		}
		Lp59: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp60;
			mxv_i174 = mxs_term(_m,1022,mxs_son(_m,1022,mxs_itoe(_c,0,4),E));
			goto L174;
		}
		Lp60: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp61;
			mxv_i174 = mxs_colof(_m,1023,mxs_son(_m,1023,mxs_itoe(_c,0,3),E));
			goto L174;
		}
		Lp61: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_StringExpr_) ) goto Lp62;
			mxv_i174 = mxs_term(_m,1024,mxs_son(_m,1024,mxs_itoe(_c,0,3),E));
			goto L174;
		}
		Lp62: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_DynUndef_) ) goto Lp63;
			mxv_i174 = mxs_itoe(_c,0,0);
			goto L174;
		}
		Lp63: ;
			mxv_i174 = mxs_term(_m,1026,mxs_son(_m,1026,mxs_itoe(_c,0,3),E));
		L174: ;
	}
	return mxv_i174;
}

ELEMENT  mxs_TW_identabb(char *f, int l){
	return mxs_FList(_m,1036);
}

ELEMENT  mxs_TW_emptyset(char *f, int l){
	return mxs_OrValue(_m,1038);
}

ELEMENT  mxs_TW_or(char *f, int l,ELEMENT S,ELEMENT T){
ELEMENT mxv_i176, mxv_i178, mxv_i177, mxv_l29, S1_l29, mxv_i175;
 IFNIL(S) IFNIL(T)

	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,S,mxs_OrValue(_m,1041)) ){
			mxv_i175 = T;
			goto L175;
		}
		if( mxs_eq(_m,0,T,mxs_OrValue(_m,1042)) ){
			mxv_i175 = S;
			goto L175;
		}
	{  /* LetExpr */
		{  /* FormulaCaseList */
			if( mxs_is(_m,1044,S,_OrValue) ){
				mxv_i176 = S;
				goto L176;
			}
			mxv_i176 = mxs_appback(_m,1044,mxs_OrValue(_m,1044),S);
			L176: ;
		}
		S1_l29 = mxv_i176;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_subterm(_m,1045,mxs_itoe(_c,0,-1),S1_l29),T) ){
				mxv_i177 = S;
				goto L177;
			}
		{  /* FormulaCaseList */
			if( mxs_is(_m,1047,T,_OrValue) ){
				mxv_i178 = mxs_conc(_m,1047,S1_l29,T);
				goto L178;
			}
			mxv_i178 = mxs_appback(_m,1048,S1_l29,T);
			L178: ;
		}
			mxv_i177 = mxv_i178;
			L177: ;
		}
		mxv_l29 = mxv_i177;
	}
		mxv_i175 = mxv_l29;
		L175: ;
	}
	return mxv_i175;
}

ELEMENT  mxs_delete_id(char *f, int l,ELEMENT T){
ELEMENT mxv_i181, mxv_i180, mxv_i179;
 IFNIL(T)
 IS(T,_Value,f,l,"delete_id",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TW_identabb(_m,1051)) ){
			mxv_i180 = mxs_true(_m,0);
			goto L180;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TW_emptyset(_m,1051)) ){
			mxv_i181 = mxs_true(_m,0);
			goto L181;
		}
		mxv_i181 = mxs_false(_m,0);
		L181: ;
	}
		mxv_i180 = mxv_i181;
		L180: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i180) ){
			mxv_i179 = mxs_TW_emptyset(_m,1051);
			goto L179;
		}
		if( mxs_is(_m,1052,T,_OrValue) ){
			mxv_i179 = mxs_TW_or(_m,1052,mxs_delete_id(_m,1052,mxs_subterm(_m,1052,mxs_itoe(_c,0,1),T)),mxs_delete_id(_m,1052,mxs_back(_m,1052,T)));
			goto L179;
		}
		mxv_i179 = T;
		L179: ;
	}
	return mxv_i179;
}

ELEMENT  mxs_TW_closure(char *f, int l,ELEMENT T){
ELEMENT mxv_i182, mxv_l30, T1_l30;
 IFNIL(T)

	{  /* LetExpr */
		T1_l30 = mxs_delete_id(_m,1056,T);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T1_l30,mxs_TW_emptyset(_m,1057)) ){
				mxv_i182 = mxs_TW_identabb(_m,1057);
				goto L182;
			}
			if( mxs_is(_m,1058,T1_l30,_FClosure) ){
				mxv_i182 = T1_l30;
				goto L182;
			}
			mxv_i182 = mxs_FClosure(_m,1059,T1_l30);
			L182: ;
		}
		mxv_l30 = mxv_i182;
	}
	return mxv_l30;
}

ELEMENT  mxs_TW_conc(char *f, int l,ELEMENT S,ELEMENT T){
ELEMENT mxv_i185, mxv_i184, mxv_i186, mxv_i187, mxv_i188, mxv_l33, C_l33, mxv_l32, T1_l32, mxv_l31, S1_l31, mxv_i183;
 IFNIL(S) IFNIL(T)
 IS(S,_Value,f,l,"TW_conc",1) IS(T,_Value,f,l,"TW_conc",2)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,S,mxs_TW_emptyset(_m,1063)) ){
			mxv_i184 = mxs_true(_m,0);
			goto L184;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TW_emptyset(_m,1063)) ){
			mxv_i185 = mxs_true(_m,0);
			goto L185;
		}
		mxv_i185 = mxs_false(_m,0);
		L185: ;
	}
		mxv_i184 = mxv_i185;
		L184: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i184) ){
			mxv_i183 = mxs_TW_emptyset(_m,1063);
			goto L183;
		}
	{  /* LetExpr */
		{  /* FormulaCaseList */
			if( mxs_is(_m,1065,S,_FList) ){
				mxv_i186 = S;
				goto L186;
			}
			mxv_i186 = mxs_appfront(_m,1065,S,mxs_TW_identabb(_m,1065));
			L186: ;
		}
		S1_l31 = mxv_i186;
		{  /* LetExpr */
			{  /* FormulaCaseList */
				if( mxs_is(_m,1066,T,_FList) ){
					mxv_i187 = T;
					goto L187;
				}
				mxv_i187 = mxs_appfront(_m,1066,T,mxs_TW_identabb(_m,1066));
				L187: ;
			}
			T1_l32 = mxv_i187;
			{  /* LetExpr */
				C_l33 = mxs_conc(_m,1067,S1_l31,T1_l32);
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,mxs_numsubterms(_m,1068,C_l33),mxs_itoe(_c,0,1)) ){
						mxv_i188 = mxs_subterm(_m,1068,mxs_itoe(_c,0,1),C_l33);
						goto L188;
					}
					mxv_i188 = C_l33;
					L188: ;
				}
				mxv_l33 = mxv_i188;
			}
			mxv_l32 = mxv_l33;
		}
		mxv_l31 = mxv_l32;
	}
		mxv_i183 = mxv_l31;
		L183: ;
	}
	return mxv_i183;
}

ELEMENT  mxs_node_parnr_fct(char *f, int l,ELEMENT N){
ELEMENT mxv_i210;
 IFNIL(N)
 IS(N,_SortId_,f,l,"node_parnr_fct",1)
	{  /* FormulaCaseList */
		if( mxs_is_node(_m,1155,N) ){
			mxv_i210 = mxs_itoe(_c,0,1);
			goto L210;
		}
		if( mxs_is(_m,1156,mxs_rbroth(_m,1156,N),_SortId_) ){
			mxv_i210 = mxs_add(_m,1156,mxs_itoe(_c,0,1),mxs_node_parnr_fct(_m,1156,mxs_rbroth(_m,1156,N)));
			goto L210;
		}
		mxv_i210 = mxs_nil(_m,1157);
		L210: ;
	}
	return mxv_i210;
}

ELEMENT  mxs_encl_patcase(char *f, int l,ELEMENT N){
ELEMENT mxv_i217;
 IFNIL(N)

	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp77;
			mxv_i217 = N;
			goto L217;
		}
		Lp77: ;
			mxv_i217 = mxs_encl_patcase(_m,1186,mxs_fath(_m,1186,N));
		L217: ;
	}
	return mxv_i217;
}

ELEMENT  mxs_pat_son_pos_nr(char *f, int l,ELEMENT N){
ELEMENT mxv_i218;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_son_pos_nr",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,1190,N),mxs_nil(_m,1190)) ){
			mxv_i218 = mxs_itoe(_c,0,1);
			goto L218;
		}
		if( mxs_is(_m,1191,mxs_lbroth(_m,1191,N),_Asterisk_) ){
			mxv_i218 = mxs_itoe(_c,0,0);
			goto L218;
		}
		mxv_i218 = mxs_add(_m,1192,mxs_pat_son_pos_nr(_m,1192,mxs_lbroth(_m,1192,N)),mxs_itoe(_c,0,1));
		L218: ;
	}
	return mxv_i218;
}

ELEMENT  mxs_pat_son_neg_nr(char *f, int l,ELEMENT N){
ELEMENT mxv_i219;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_son_neg_nr",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,1195,N),mxs_nil(_m,1195)) ){
			mxv_i219 = mxs_itoe(_c,0,-1);
			goto L219;
		}
		if( mxs_is(_m,1196,mxs_rbroth(_m,1196,N),_Asterisk_) ){
			mxv_i219 = mxs_itoe(_c,0,0);
			goto L219;
		}
		mxv_i219 = mxs_sub(_m,1197,mxs_pat_son_neg_nr(_m,1197,mxs_rbroth(_m,1197,N)),mxs_itoe(_c,0,1));
		L219: ;
	}
	return mxv_i219;
}

ELEMENT  mxs_pat_son_nr(char *f, int l,ELEMENT N){
ELEMENT mxv_i221, mxv_i220, mxv_l40, X_l40;


	{  /* LetExpr */
		X_l40 = mxs_pat_son_pos_nr(_m,1200,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,X_l40,mxs_itoe(_c,0,1)) ){
				mxv_i220 = mxs_itoe(_c,0,1);
				goto L220;
			}
			if( mxs_eq(_m,0,X_l40,mxs_itoe(_c,0,0)) ){
				mxv_i220 = mxs_pat_son_neg_nr(_m,1202,N);
				goto L220;
			}
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_pat_son_neg_nr(_m,1203,N),mxs_itoe(_c,0,-1)) ){
				mxv_i221 = mxs_itoe(_c,0,-1);
				goto L221;
			}
			mxv_i221 = X_l40;
			L221: ;
		}
			mxv_i220 = mxv_i221;
			L220: ;
		}
		mxv_l40 = mxv_i220;
	}
	return mxv_l40;
}

ELEMENT  mxs_pat_way(char *f, int l,ELEMENT V,ELEMENT N){
ELEMENT mxv_i224, mxv_i225, mxv_i223, mxv_i222;
 IFNIL(V)
 IS(V,_Item_,f,l,"pat_way",1) IS(N,_Item_,f,l,"pat_way",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_fath(_m,1207,V),mxs_fath(_m,1207,N)) ){
		{  /* FormulaCaseList */
			if( mxs_bef(_m,1208,mxs_before(_m,1208,V),mxs_before(_m,1208,N)) ){
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = V;
					mxv_IR = mxv_anchor;
					if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp78;
					mxv_i224 = mxs_TW_conc(_m,1210,mxs_TW_closure(_m,1210,mxs_TWrbroth(_m,1210)),mxs_pat_way(_m,1210,mxs_rbroth(_m,1210,V),N));
					goto L224;
				}
				Lp78: ;
					mxv_i224 = mxs_TW_conc(_m,1211,mxs_pat_way(_m,1211,mxs_rbroth(_m,1211,V),N),mxs_TWrbroth(_m,1211));
				L224: ;
			}
				mxv_i223 = mxv_i224;
				goto L223;
			}
			if( mxs_aft(_m,1212,mxs_before(_m,1212,V),mxs_before(_m,1212,N)) ){
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = V;
					mxv_IR = mxv_anchor;
					if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp79;
					mxv_i225 = mxs_TW_conc(_m,1214,mxs_TW_closure(_m,1214,mxs_TWlbroth(_m,1214)),mxs_pat_way(_m,1214,mxs_lbroth(_m,1214,V),N));
					goto L225;
				}
				Lp79: ;
					mxv_i225 = mxs_TW_conc(_m,1215,mxs_pat_way(_m,1215,mxs_lbroth(_m,1215,V),N),mxs_TWlbroth(_m,1215));
				L225: ;
			}
				mxv_i223 = mxv_i225;
				goto L223;
			}
			mxv_i223 = mxs_TW_identabb(_m,1216);
			L223: ;
		}
			mxv_i222 = mxv_i223;
			goto L222;
		}
		if( mxs_desc(_m,1217,V,mxs_fath(_m,1217,mxs_fath(_m,1217,N))) ){
			mxv_i222 = mxs_TW_conc(_m,1217,mxs_TWfath(_m,1217),mxs_pat_way(_m,1217,mxs_fath(_m,1217,mxs_fath(_m,1217,V)),N));
			goto L222;
		}
		mxv_i222 = mxs_TW_conc(_m,1218,mxs_pat_way(_m,1218,V,mxs_fath(_m,1218,mxs_fath(_m,1218,N))),mxs_TWson(_m,1218,mxs_pat_son_nr(_m,1218,N)));
		L222: ;
	}
	return mxv_i222;
}

ELEMENT  mxs_enter_attrgroup(char *f, int l,ELEMENT J,ELEMENT ANL,ELEMENT M){
ELEMENT mxv_i231;
 IFNIL(J) IFNIL(ANL) IFNIL(M)

	{  /* FormulaCaseList */
		if( mxs_lt(_m,1255,mxs_numsubterms(_m,1255,ANL),J) ){
			mxv_i231 = mxs_warshall_value(_m,1255,M,mxs_numsubterms(_m,1255,ANL));
			goto L231;
		}
		mxv_i231 = mxs_enter_attrgroup(_m,1257,mxs_add(_m,1257,J,mxs_itoe(_c,0,1)),ANL,mxs_enter_attribute(_m,1258,mxs_sub(_m,1258,J,mxs_itoe(_c,0,1)),mxs_subterm(_m,1258,J,ANL),M,mxs_numsubterms(_m,1258,ANL)));
		L231: ;
	}
	return mxv_i231;
}

ELEMENT  mxs_enter_attrgroup_list(char *f, int l,ELEMENT I,ELEMENT ALI,ELEMENT ALM){
ELEMENT mxv_i232;
 IFNIL(I) IFNIL(ALI) IFNIL(ALM)

	{  /* FormulaCaseList */
		if( mxs_lt(_m,1262,mxs_numsubterms(_m,1262,ALI),I) ){
			mxv_i232 = ALM;
			goto L232;
		}
		mxv_i232 = mxs_enter_attrgroup_list(_m,1263,mxs_add(_m,1263,I,mxs_itoe(_c,0,1)),ALI,mxs_appback(_m,1264,ALM,mxs_enter_attrgroup(_m,1265,mxs_itoe(_c,0,1),mxs_subterm(_m,1265,I,ALI),mxs_init_matrix(_m,1266,mxs_numsubterms(_m,1266,mxs_subterm(_m,1266,I,ALI))))));
		L232: ;
	}
	return mxv_i232;
}

ELEMENT  mxs_simplify_closure(char *f, int l,ELEMENT T){
ELEMENT mxv_i235, mxv_i234, mxv_i237, mxv_i236, mxv_i241, mxv_i240, mxv_i245, mxv_i244, mxv_i248, mxv_i247, mxv_i246, mxv_i243, mxv_i242, mxv_i239, mxv_l45, X_l45, mxv_i238, mxv_l44, H_l44, mxv_l43, V_l43, mxv_i233;
 IFNIL(T)
 IS(T,_Value,f,l,"simplify_closure",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1291,T,_FList)) ){
			mxv_i234 = mxs_false(_m,0);
			goto L234;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_itoe(_c,0,1),mxs_numsubterms(_m,1291,T)) ){
			mxv_i235 = mxs_true(_m,0);
			goto L235;
		}
		mxv_i235 = mxs_false(_m,0);
		L235: ;
	}
		mxv_i234 = mxv_i235;
		L234: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i234) ){
			mxv_i233 = mxs_simplify_closure(_m,1291,mxs_subterm(_m,1291,mxs_itoe(_c,0,1),T));
			goto L233;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1292,T,_FList)) ){
			mxv_i236 = mxs_false(_m,0);
			goto L236;
		}
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1292,mxs_itoe(_c,0,1),mxs_numsubterms(_m,1292,T)) ){
			mxv_i237 = mxs_true(_m,0);
			goto L237;
		}
		mxv_i237 = mxs_false(_m,0);
		L237: ;
	}
		mxv_i236 = mxv_i237;
		L236: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i236) ){
		{  /* LetExpr */
			V_l43 = mxs_subterm(_m,1293,mxs_itoe(_c,0,1),T);
			{  /* LetExpr */
				H_l44 = mxs_subterm(_m,1294,mxs_itoe(_c,0,-1),T);
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1295,V_l43,_TWfath)) ){
						mxv_i240 = mxs_false(_m,0);
						goto L240;
					}
				{  /* FormulaCaseList */
					if( mxs_is(_m,1295,H_l44,_TWson) ){
						mxv_i241 = mxs_true(_m,0);
						goto L241;
					}
					mxv_i241 = mxs_false(_m,0);
					L241: ;
				}
					mxv_i240 = mxv_i241;
					L240: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i240) ){
						mxv_i239 = mxs_true(_m,0);
						goto L239;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1296,V_l43,_TWrbroth)) ){
						mxv_i244 = mxs_false(_m,0);
						goto L244;
					}
				{  /* FormulaCaseList */
					if( mxs_is(_m,1296,H_l44,_TWlbroth) ){
						mxv_i245 = mxs_true(_m,0);
						goto L245;
					}
					mxv_i245 = mxs_false(_m,0);
					L245: ;
				}
					mxv_i244 = mxv_i245;
					L244: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i244) ){
						mxv_i243 = mxs_true(_m,0);
						goto L243;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1297,V_l43,_TWlbroth)) ){
						mxv_i247 = mxs_false(_m,0);
						goto L247;
					}
				{  /* FormulaCaseList */
					if( mxs_is(_m,1297,H_l44,_TWrbroth) ){
						mxv_i248 = mxs_true(_m,0);
						goto L248;
					}
					mxv_i248 = mxs_false(_m,0);
					L248: ;
				}
					mxv_i247 = mxv_i248;
					L247: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i247) ){
						mxv_i246 = mxs_true(_m,0);
						goto L246;
					}
					mxv_i246 = mxs_false(_m,0);
					L246: ;
				}
					mxv_i243 = mxv_i246;
					L243: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i243) ){
						mxv_i242 = mxs_true(_m,0);
						goto L242;
					}
					mxv_i242 = mxs_false(_m,0);
					L242: ;
				}
					mxv_i239 = mxv_i242;
					L239: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i239) ){
					{  /* LetExpr */
						X_l45 = mxs_back(_m,1298,mxs_front(_m,1298,T));
						mxv_l45 = mxs_TW_or(_m,1299,mxs_TW_identabb(_m,1299),mxs_TW_conc(_m,1300,mxs_TW_conc(_m,1300,V_l43,X_l45),mxs_TW_conc(_m,1301,mxs_simplify_closure(_m,1301,X_l45),H_l44)));
					}
						mxv_i238 = mxv_l45;
						goto L238;
					}
					mxv_i238 = mxs_FClosure(_m,1303,T);
					L238: ;
				}
				mxv_l44 = mxv_i238;
			}
			mxv_l43 = mxv_l44;
		}
			mxv_i233 = mxv_l43;
			goto L233;
		}
		mxv_i233 = mxs_FClosure(_m,1304,T);
		L233: ;
	}
	return mxv_i233;
}

ELEMENT  mxs_normal_tw(char *f, int l,ELEMENT R,ELEMENT S,ELEMENT T){
ELEMENT mxv_i280, mxv_i283, mxv_i284, mxv_i282, mxv_l46, RN_l46, mxv_i281, mxv_i285, mxv_i286, mxv_i279;
 IFNIL(R) IFNIL(S)
 IS(T,_FValue,f,l,"normal_tw",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1316,S,_TWfath) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWson(_m,1317,mxs_itoe(_c,0,1))) ){
				mxv_i280 = mxs_appback(_m,1317,R,mxs_FClosure(_m,1317,mxs_TWlbroth(_m,1317)));
				goto L280;
			}
			mxv_i280 = mxs_appback(_m,1318,R,mxs_FClosure(_m,1318,mxs_TWrbroth(_m,1318)));
			L280: ;
		}
			mxv_i279 = mxv_i280;
			goto L279;
		}
		if( mxs_is(_m,1320,S,_TWson) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWfath(_m,1321)) ){
				mxv_i281 = mxs_FList(_m,1321);
				goto L281;
			}
		{  /* LetExpr */
			RN_l46 = mxs_subterm(_m,1323,mxs_itoe(_c,0,1),S);
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,T,mxs_TWrbroth(_m,1324)) ){
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,0)) ){
						mxv_i283 = mxs_appback(_m,1325,R,S);
						goto L283;
					}
					if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,-1)) ){
						mxv_i283 = mxs_TW_emptyset(_m,1326);
						goto L283;
					}
					mxv_i283 = mxs_appback(_m,1327,R,mxs_TWson(_m,1327,mxs_add(_m,1327,RN_l46,mxs_itoe(_c,0,1))));
					L283: ;
				}
					mxv_i282 = mxv_i283;
					goto L282;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,0)) ){
					mxv_i284 = mxs_appback(_m,1329,R,S);
					goto L284;
				}
				if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,1)) ){
					mxv_i284 = mxs_TW_emptyset(_m,1330);
					goto L284;
				}
				mxv_i284 = mxs_appback(_m,1331,R,mxs_TWson(_m,1331,mxs_sub(_m,1331,RN_l46,mxs_itoe(_c,0,1))));
				L284: ;
			}
				mxv_i282 = mxv_i284;
				L282: ;
			}
			mxv_l46 = mxv_i282;
		}
			mxv_i281 = mxv_l46;
			L281: ;
		}
			mxv_i279 = mxv_i281;
			goto L279;
		}
		if( mxs_is(_m,1333,S,_TWlbroth) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWrbroth(_m,1334)) ){
				mxv_i285 = R;
				goto L285;
			}
			mxv_i285 = mxs_appback(_m,1335,R,mxs_TWfath(_m,1335));
			L285: ;
		}
			mxv_i279 = mxv_i285;
			goto L279;
		}
		if( mxs_is(_m,1337,S,_TWrbroth) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWlbroth(_m,1338)) ){
				mxv_i286 = R;
				goto L286;
			}
			mxv_i286 = mxs_appback(_m,1339,R,mxs_TWfath(_m,1339));
			L286: ;
		}
			mxv_i279 = mxv_i286;
			goto L279;
		}
		if( mxs_is(_m,1341,S,_FClosure) ){
			mxv_i279 = mxs_appback(_m,1342,R,mxs_TWfath(_m,1342));
			goto L279;
		}
		mxv_i279 = mxs_nil(_m,1344);
		L279: ;
	}
	return mxv_i279;
}

ELEMENT  mxs_normal_closure(char *f, int l,ELEMENT R,ELEMENT T){
ELEMENT mxv_i288, mxv_i287;
 IFNIL(R) IFNIL(T)
 IS(T,_FClosure,f,l,"normal_closure",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,R,mxs_FList(_m,1348)) ){
			mxv_i287 = T;
			goto L287;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_subterm(_m,1350,mxs_itoe(_c,0,-1),R),mxs_subterm(_m,1350,mxs_itoe(_c,0,1),T)) ){
			mxv_i288 = mxs_TW_conc(_m,1350,mxs_normal_closure(_m,1350,mxs_front(_m,1350,R),T),mxs_subterm(_m,1350,mxs_itoe(_c,0,1),T));
			goto L288;
		}
		mxv_i288 = mxs_appback(_m,1351,R,T);
		L288: ;
	}
		mxv_i287 = mxv_i288;
		L287: ;
	}
	return mxv_i287;
}

ELEMENT  mxs_normalform(char *f, int l,ELEMENT R,ELEMENT T,ELEMENT N){
ELEMENT mxv_i294, mxv_i293, mxv_i295, mxv_i292, mxv_i291, mxv_l47, Z_l47, mxv_i290, mxv_i296, mxv_i300, mxv_i299, mxv_i301, mxv_i298, mxv_l48, N1_l48, mxv_i297, mxv_i302, mxv_l49, V_l49, mxv_i289;
 IFNIL(R) IFNIL(T) IFNIL(N)
 IS(R,_FList,f,l,"normalform",1) IS(T,_Value,f,l,"normalform",2) IS(N,_FuAtList_,f,l,"normalform",3)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1355,T,_DefId_) ){
			mxv_i289 = mxs_normalform(_m,1356,R,mxs_result_value(_m,1356,mxs_fath(_m,1356,T)),mxs_fath(_m,1356,mxs_fath(_m,1356,T)));
			goto L289;
		}
		if( mxs_is(_m,1358,T,_RelevAcc) ){
			mxv_i289 = mxs_normalform(_m,1359,R,mxs_result_value(_m,1359,mxs_son(_m,1359,mxs_subterm(_m,1359,mxs_itoe(_c,0,1),T),N)),N);
			goto L289;
		}
		if( mxs_is(_m,1361,T,_FValue) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,R,mxs_FList(_m,1362)) ){
				mxv_i290 = T;
				goto L290;
			}
		{  /* LetExpr */
			Z_l47 = mxs_subterm(_m,1364,mxs_itoe(_c,0,-1),R);
			{  /* FormulaCaseList */
				if( mxs_simplification(_m,1365,Z_l47,T) ){
					mxv_i291 = mxs_normal_tw(_m,1365,mxs_front(_m,1365,R),Z_l47,T);
					goto L291;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_lt(_m,1367,mxs_itoe(_c,0,1),mxs_numsubterms(_m,1367,R))) ){
					mxv_i293 = mxs_false(_m,0);
					goto L293;
				}
			{  /* FormulaCaseList */
				if( mxs_is(_m,1367,Z_l47,_FClosure) ){
					mxv_i294 = mxs_true(_m,0);
					goto L294;
				}
				mxv_i294 = mxs_false(_m,0);
				L294: ;
			}
				mxv_i293 = mxv_i294;
				L293: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i293) ){
				{  /* FormulaCaseList */
					if( mxs_simplification(_m,1368,mxs_subterm(_m,1368,mxs_itoe(_c,0,-2),R),T) ){
						mxv_i295 = mxs_TW_or(_m,1369,mxs_normal_tw(_m,1369,mxs_front(_m,1369,mxs_front(_m,1369,R)),mxs_subterm(_m,1369,mxs_itoe(_c,0,-2),R),T),mxs_normalform(_m,1370,mxs_appback(_m,1370,mxs_front(_m,1370,R),mxs_subterm(_m,1370,mxs_itoe(_c,0,1),Z_l47)),mxs_TW_conc(_m,1370,Z_l47,T),N));
						goto L295;
					}
					mxv_i295 = mxs_appback(_m,1372,R,T);
					L295: ;
				}
					mxv_i292 = mxv_i295;
					goto L292;
				}
				mxv_i292 = mxs_appback(_m,1373,R,T);
				L292: ;
			}
				mxv_i291 = mxv_i292;
				L291: ;
			}
			mxv_l47 = mxv_i291;
		}
			mxv_i290 = mxv_l47;
			L290: ;
		}
			mxv_i289 = mxv_i290;
			goto L289;
		}
		if( mxs_is(_m,1375,T,_OrValue) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1376,T),mxs_itoe(_c,0,0)) ){
				mxv_i296 = mxs_TW_emptyset(_m,1376);
				goto L296;
			}
			mxv_i296 = mxs_TW_or(_m,1377,mxs_normalform(_m,1377,R,mxs_subterm(_m,1377,mxs_itoe(_c,0,1),T),N),mxs_normalform(_m,1377,R,mxs_back(_m,1377,T),N));
			L296: ;
		}
			mxv_i289 = mxv_i296;
			goto L289;
		}
		if( mxs_is(_m,1379,T,_FList) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1380,T),mxs_itoe(_c,0,0)) ){
				mxv_i297 = R;
				goto L297;
			}
		{  /* LetExpr */
			N1_l48 = mxs_normalform(_m,1382,R,mxs_subterm(_m,1382,mxs_itoe(_c,0,1),T),N);
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,N1_l48,mxs_TW_emptyset(_m,1383)) ){
					mxv_i299 = mxs_true(_m,0);
					goto L299;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,N1_l48,mxs_nil(_m,1383)) ){
					mxv_i300 = mxs_true(_m,0);
					goto L300;
				}
				mxv_i300 = mxs_false(_m,0);
				L300: ;
			}
				mxv_i299 = mxv_i300;
				L299: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i299) ){
					mxv_i298 = N1_l48;
					goto L298;
				}
			{  /* FormulaCaseList */
				if( mxs_is(_m,1384,N1_l48,_FList) ){
					mxv_i301 = N1_l48;
					goto L301;
				}
				mxv_i301 = mxs_appback(_m,1385,mxs_FList(_m,1385),N1_l48);
				L301: ;
			}
				mxv_i298 = mxs_normalform(_m,1384,mxv_i301,mxs_back(_m,1385,T),N);
				L298: ;
			}
			mxv_l48 = mxv_i298;
		}
			mxv_i297 = mxv_l48;
			L297: ;
		}
			mxv_i289 = mxv_i297;
			goto L289;
		}
		if( mxs_is(_m,1387,T,_FClosure) ){
		{  /* LetExpr */
			V_l49 = mxs_simplify_closure(_m,1388,mxs_normalform(_m,1388,mxs_FList(_m,1388),mxs_subterm(_m,1388,mxs_itoe(_c,0,1),T),N));
			{  /* FormulaCaseList */
				if( mxs_is(_m,1389,V_l49,_FClosure) ){
					mxv_i302 = mxs_normal_closure(_m,1389,R,V_l49);
					goto L302;
				}
				mxv_i302 = mxs_normalform(_m,1390,R,V_l49,N);
				L302: ;
			}
			mxv_l49 = mxv_i302;
		}
			mxv_i289 = mxv_l49;
			goto L289;
		}
		mxv_i289 = mxs_nil(_m,1392);
		L289: ;
	}
	return mxv_i289;
}

ELEMENT  mxs_Ord_fath(char *f, int l){
	return mxs_itoe(_c,0,35);
}

ELEMENT  mxs_Ord_son(char *f, int l){
	return mxs_itoe(_c,0,50);
}

ELEMENT  mxs_Ord_rbroth(char *f, int l){
	return mxs_itoe(_c,0,16);
}

ELEMENT  mxs_Ord_lbroth(char *f, int l){
	return mxs_itoe(_c,0,1);
}

ELEMENT  mxs_Ord_ident(char *f, int l){
	return mxs_itoe(_c,0,204);
}

ELEMENT  mxs_Ord_neutral(char *f, int l){
	return mxs_itoe(_c,0,17);
}

ELEMENT  mxs_Ord_nothing(char *f, int l){
	return mxs_itoe(_c,0,136);
}

ELEMENT  mxs_val_order(char *f, int l,ELEMENT T){
ELEMENT mxv_i304, mxv_i305, mxv_i303;
 IFNIL(T)
 IS(T,_Value,f,l,"val_order",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1416,T,_TWson) ){
			mxv_i303 = mxs_Ord_son(_m,1416);
			goto L303;
		}
		if( mxs_is(_m,1417,T,_TWfath) ){
			mxv_i303 = mxs_Ord_fath(_m,1417);
			goto L303;
		}
		if( mxs_is(_m,1418,T,_TWrbroth) ){
			mxv_i303 = mxs_Ord_rbroth(_m,1418);
			goto L303;
		}
		if( mxs_is(_m,1419,T,_TWlbroth) ){
			mxv_i303 = mxs_Ord_lbroth(_m,1419);
			goto L303;
		}
		if( mxs_is(_m,1420,T,_FClosure) ){
			mxv_i303 = mxs_OrdOp_closure(_m,1420,mxs_val_order(_m,1420,mxs_subterm(_m,1420,mxs_itoe(_c,0,1),T)));
			goto L303;
		}
		if( mxs_is(_m,1421,T,_FList) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1422,T),mxs_itoe(_c,0,0)) ){
				mxv_i304 = mxs_Ord_ident(_m,1422);
				goto L304;
			}
			mxv_i304 = mxs_OrdOp_conc(_m,1423,mxs_val_order(_m,1423,mxs_subterm(_m,1423,mxs_itoe(_c,0,1),T)),mxs_val_order(_m,1423,mxs_back(_m,1423,T)));
			L304: ;
		}
			mxv_i303 = mxv_i304;
			goto L303;
		}
		if( mxs_is(_m,1424,T,_OrValue) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1425,T),mxs_itoe(_c,0,0)) ){
				mxv_i305 = mxs_Ord_neutral(_m,1425);
				goto L305;
			}
			mxv_i305 = mxs_OrdOp_or(_m,1426,mxs_val_order(_m,1426,mxs_subterm(_m,1426,mxs_itoe(_c,0,1),T)),mxs_val_order(_m,1426,mxs_back(_m,1426,T)));
			L305: ;
		}
			mxv_i303 = mxv_i305;
			goto L303;
		}
		mxv_i303 = mxs_Ord_nothing(_m,1428);
		L303: ;
	}
	return mxv_i303;
}

ELEMENT  mxs_contains_attr(char *f, int l,ELEMENT FAL){
ELEMENT mxv_i306;
 IFNIL(FAL)

	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,FAL,mxs_FuAtNodeList(_m,1439)) ){
			mxv_i306 = mxs_false(_m,1439);
			goto L306;
		}
		if( mxs_is(_m,1440,mxs_subterm(_m,1440,mxs_itoe(_c,0,1),FAL),_Attribute_) ){
			mxv_i306 = mxs_true(_m,1440);
			goto L306;
		}
		mxv_i306 = mxs_contains_attr(_m,1441,mxs_back(_m,1441,FAL));
		L306: ;
	}
	return mxv_i306;
}

ELEMENT  mxs_encl_fctoratt(char *f, int l,ELEMENT N){
ELEMENT mxv_i307;
 IFNIL(N)

	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp87;
			mxv_i307 = N;
			goto L307;
		}
		Lp87: ;
			mxv_i307 = mxs_encl_fctoratt(_m,1445,mxs_fath(_m,1445,N));
		L307: ;
	}
	return mxv_i307;
}

ELEMENT  mxs_filter_relev_acc(char *f, int l,ELEMENT AL){
ELEMENT mxv_i318, mxv_i317;
 IFNIL(AL)

	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,AL,mxs_ApplList(_m,1463)) ){
			mxv_i317 = mxs_ApplList(_m,1463);
			goto L317;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_appl_order(_m,1464,mxs_subterm(_m,1464,mxs_itoe(_c,0,1),AL)),mxs_Ord_neutral(_m,1464)) ){
			mxv_i318 = mxs_filter_relev_acc(_m,1464,mxs_back(_m,1464,AL));
			goto L318;
		}
		mxv_i318 = mxs_appfront(_m,1465,mxs_subterm(_m,1465,mxs_itoe(_c,0,1),AL),mxs_filter_relev_acc(_m,1465,mxs_back(_m,1465,AL)));
		L318: ;
	}
		mxv_i317 = mxv_i318;
		L317: ;
	}
	return mxv_i317;
}

ELEMENT  mxs_list_intresexprs(char *f, int l,ELEMENT N){
ELEMENT mxv_i348;
 IFNIL(N)

	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,1537,N),mxs_nil(_m,1537)) ){
			mxv_i348 = mxs_intresexprs(_m,1537,N);
			goto L348;
		}
		mxv_i348 = mxs_conc(_m,1538,mxs_intresexprs(_m,1538,N),mxs_list_intresexprs(_m,1538,mxs_rbroth(_m,1538,N)));
		L348: ;
	}
	return mxv_i348;
}

ELEMENT  mxs_intresexprs(char *f, int l,ELEMENT N){
ELEMENT mxv_i349;
 IFNIL(N)

	{  /* FormulaCaseList */
		if( mxs_is_intres(_m,1542,N) ){
			mxv_i349 = mxs_appback(_m,1542,mxs_IntResList(_m,1542),N);
			goto L349;
		}
		if( mxs_eq(_m,0,mxs_numsons(_m,1543,N),mxs_itoe(_c,0,0)) ){
			mxv_i349 = mxs_IntResList(_m,1543);
			goto L349;
		}
		mxv_i349 = mxs_list_intresexprs(_m,1544,mxs_son(_m,1544,mxs_itoe(_c,0,1),N));
		L349: ;
	}
	return mxv_i349;
}

ELEMENT  mxs_encl_part_intres(char *f, int l,ELEMENT N){
ELEMENT mxv_i352, mxv_i351, A_p333, C_p335, C_p337, L_p339, L_p341, I_p343, F_p345, F_p347, P_p349, F_p351;
 IFNIL(N)

	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp94;
			A_p333 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = A_p333;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp94;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp94;
			if( !mxs_is(_c,0,mxv_IR,_ApplyEntity_) ) goto Lp94;
			mxv_i351 = N;
			goto L351;
		}
		Lp94: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp95;
			C_p335 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = C_p335;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp95;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp95;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp95;
			mxv_i351 = N;
			goto L351;
		}
		Lp95: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp96;
			C_p337 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = C_p337;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp96;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp96;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp96;
			mxv_i351 = N;
			goto L351;
		}
		Lp96: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp97;
			L_p339 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = L_p339;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp97;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp97;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp97;
			mxv_i351 = N;
			goto L351;
		}
		Lp97: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp98;
			L_p341 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = L_p341;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp98;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp98;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp98;
			mxv_i351 = N;
			goto L351;
		}
		Lp98: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp99;
			I_p343 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = I_p343;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp99;
			if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp99;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp99;
			mxv_i351 = N;
			goto L351;
		}
		Lp99: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp100;
			F_p345 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = F_p345;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp100;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp100;
			if( !mxs_is(_c,0,mxv_IR,_FormulaCase_) ) goto Lp100;
			mxv_i351 = N;
			goto L351;
		}
		Lp100: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp101;
			F_p347 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = F_p347;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp101;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp101;
			if( !mxs_is(_c,0,mxv_IR,_FormulaCase_) ) goto Lp101;
			mxv_i351 = N;
			goto L351;
		}
		Lp101: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp102;
			P_p349 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = P_p349;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp102;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp102;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp102;
			mxv_i351 = N;
			goto L351;
		}
		Lp102: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp103;
			F_p351 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = F_p351;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp103;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp103;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp103;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_maybe_wait(_m,1571,F_p351),mxs_true(_m,1571)) ){
				mxv_i352 = N;
				goto L352;
			}
			mxv_i352 = mxs_encl_part_intres(_m,1571,F_p351);
			L352: ;
		}
			mxv_i351 = mxv_i352;
			goto L351;
		}
		Lp103: ;
			mxv_i351 = mxs_encl_part_intres(_m,1572,mxs_fath(_m,1572,N));
		L351: ;
	}
	return mxv_i351;
}

ELEMENT  mxs_aux_var_need(char *f, int l,ELEMENT I,ELEMENT V){
ELEMENT mxv_i357, mxv_i356, mxv_i355, mxv_i354, mxv_l55, N_l55, mxv_i353;
 IFNIL(I)

	{  /* FormulaCaseList */
		if( mxs_lt(_m,1579,mxs_number(_m,1579,_Name_),I) ){
			mxv_i353 = mxs_IntResList(_m,1579);
			goto L353;
		}
	{  /* LetExpr */
		N_l55 = mxs_element(_m,1581,I,_Name_);
		{  /* FormulaCaseList */
			if( mxs_desc(_m,1582,N_l55,V) ){
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! ( ! mxs_eq(_m,0,mxs_bind_pos(_m,1583,N_l55),N_l55))) ){
					mxv_i356 = mxs_false(_m,0);
					goto L356;
				}
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,1583,mxs_fath(_m,1583,mxs_bind_pos(_m,1583,N_l55)),_NameList_)) ){
					mxv_i357 = mxs_true(_m,0);
					goto L357;
				}
				mxv_i357 = mxs_false(_m,0);
				L357: ;
			}
				mxv_i356 = mxv_i357;
				L356: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i356) ){
					mxv_i355 = mxs_appfront(_m,1584,N_l55,mxs_aux_var_need(_m,1584,mxs_add(_m,1584,I,mxs_itoe(_c,0,1)),V));
					goto L355;
				}
				mxv_i355 = mxs_aux_var_need(_m,1585,mxs_add(_m,1585,I,mxs_itoe(_c,0,1)),V);
				L355: ;
			}
				mxv_i354 = mxv_i355;
				goto L354;
			}
			mxv_i354 = mxs_IntResList(_m,1586);
			L354: ;
		}
		mxv_l55 = mxv_i354;
	}
		mxv_i353 = mxv_l55;
		L353: ;
	}
	return mxv_i353;
}

ELEMENT  mxs_aux_intres_left(char *f, int l,ELEMENT N,ELEMENT I,ELEMENT Z){
ELEMENT mxv_i358;
 IFNIL(I) IFNIL(Z)

	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_subterm(_m,1590,I,Z),N) ){
			mxv_i358 = mxs_IntResList(_m,1590);
			goto L358;
		}
		mxv_i358 = mxs_appfront(_m,1591,mxs_subterm(_m,1591,I,Z),mxs_aux_intres_left(_m,1591,N,mxs_add(_m,1591,I,mxs_itoe(_c,0,1)),Z));
		L358: ;
	}
	return mxv_i358;
}

ELEMENT  mxs_aux_intres_right(char *f, int l,ELEMENT LCP,ELEMENT PL,ELEMENT PR,ELEMENT L,ELEMENT I){
ELEMENT mxv_i364, mxv_i363, mxv_i362, mxv_i361, mxv_i360, mxv_l56, N_l56, mxv_i359;
 IFNIL(PR) IFNIL(L) IFNIL(I)

	{  /* FormulaCaseList */
		if( mxs_lt(_m,1595,mxs_numsubterms(_m,1595,L),I) ){
			mxv_i359 = mxs_IntResList(_m,1595);
			goto L359;
		}
	{  /* LetExpr */
		N_l56 = mxs_subterm(_m,1597,I,L);
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! mxs_bef(_m,1598,PL,mxs_after(_m,1598,N_l56))) ){
				mxv_i361 = mxs_false(_m,0);
				goto L361;
			}
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! mxs_bef(_m,1598,mxs_after(_m,1598,N_l56),PR)) ){
				mxv_i363 = mxs_false(_m,0);
				goto L363;
			}
		{  /* FormulaCaseList */
			if( mxs_bef(_m,1598,mxs_after(_m,1598,mxs_bind_pos(_m,1598,N_l56)),LCP) ){
				mxv_i364 = mxs_true(_m,0);
				goto L364;
			}
			mxv_i364 = mxs_false(_m,0);
			L364: ;
		}
			mxv_i363 = mxv_i364;
			L363: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i363) ){
				mxv_i362 = mxs_true(_m,0);
				goto L362;
			}
			mxv_i362 = mxs_false(_m,0);
			L362: ;
		}
			mxv_i361 = mxv_i362;
			L361: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i361) ){
				mxv_i360 = mxs_appfront(_m,1599,N_l56,mxs_aux_intres_right(_m,1599,LCP,PL,PR,L,mxs_add(_m,1599,I,mxs_itoe(_c,0,1))));
				goto L360;
			}
			mxv_i360 = mxs_aux_intres_right(_m,1600,LCP,PL,PR,L,mxs_add(_m,1600,I,mxs_itoe(_c,0,1)));
			L360: ;
		}
		mxv_l56 = mxv_i360;
	}
		mxv_i359 = mxv_l56;
		L359: ;
	}
	return mxv_i359;
}



ELEMENT  mxx_encl_dynfunc(char *f, int l,ELEMENT N){
ELEMENT mxv_i1;
 IFNIL(N)
 IS(N,_Node,f,l,"encl_dynfunc",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_DynFunc_) ) goto Lp1;
			mxv_i1 = N;
			goto L1;
		}
		Lp1: ;
			mxv_i1 = mxs_encl_dynfunc(_m,302,mxs_fath(_m,302,N));
		L1: ;
	}
	return mxv_i1;
}

ELEMENT  mxx_ss(char *f, int l,ELEMENT Str){
 IFNIL(Str)
 IS(Str,_String_,f,l,"ss",1)
	return mxs_term(_m,317,Str);
}

ELEMENT  mxx_id(char *f, int l,ELEMENT ID){
 IFNIL(ID)
 IS(ID,_Ident_,f,l,"id",1)
	return mxs_idtos(_m,319,mxs_term(_m,319,ID));
}

ELEMENT  mxx_patlineno(char *f, int l,ELEMENT PN){
ELEMENT mxv_i2, L_p5;
 IFNIL(PN)
 IS(PN,_Pattern_,f,l,"patlineno",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp2;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp2;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp2;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp2;
			L_p5 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = L_p5;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp2;
			mxv_i2 = L_p5;
			goto L2;
		}
		Lp2: ;
			mxv_i2 = mxs_son(_m,321,mxs_itoe(_c,0,2),mxs_son(_m,321,mxs_itoe(_c,0,1),PN));
		L2: ;
	}
	return mxv_i2;
}

ELEMENT  mxx_patfilename(char *f, int l,ELEMENT PN){
ELEMENT mxv_i3, F_p8;
 IFNIL(PN)
 IS(PN,_Pattern_,f,l,"patfilename",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp3;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp3;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp3;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp3;
			F_p8 = mxs_son(_c,0,2,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = F_p8;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp3;
			mxv_i3 = F_p8;
			goto L3;
		}
		Lp3: ;
			mxv_i3 = mxs_son(_m,323,mxs_itoe(_c,0,4),mxs_son(_m,323,mxs_itoe(_c,0,1),PN));
		L3: ;
	}
	return mxv_i3;
}

ELEMENT  mxx_decl(char *f, int l,ELEMENT UID){
 IFNIL(UID)
 IS(UID,_UsedId_,f,l,"decl",1)
	return mxs_subterm(_m,352,mxs_itoe(_c,0,1),mxs_idtodecls(_m,352,mxs_term(_m,352,mxs_son(_m,352,mxs_itoe(_c,0,1),UID))));
}

ELEMENT  mxx_sort_union(char *f, int l,ELEMENT X,ELEMENT Y){
ELEMENT mxv_i25, mxv_i24, mxv_i23;
 IFNIL(X) IFNIL(Y)
 IS(X,_DefIdNodeInfo,f,l,"sort_union",1) IS(Y,_DefIdNodeInfo,f,l,"sort_union",2)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,X,mxs_AllNodes(_m,375)) ){
			mxv_i24 = mxs_true(_m,0);
			goto L24;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,Y,mxs_AllNodes(_m,375)) ){
			mxv_i25 = mxs_true(_m,0);
			goto L25;
		}
		mxv_i25 = mxs_false(_m,0);
		L25: ;
	}
		mxv_i24 = mxv_i25;
		L24: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i24) ){
			mxv_i23 = mxs_AllNodes(_m,375);
			goto L23;
		}
		mxv_i23 = mxs_conc(_m,376,X,Y);
		L23: ;
	}
	return mxv_i23;
}

ELEMENT  mxx_scope(char *f, int l,ELEMENT N){
ELEMENT mxv_i49, L_p107;
 IFNIL(N)
 IS(N,_Node,f,l,"scope",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Scope_) ) goto Lp8;
			mxv_i49 = N;
			goto L49;
		}
		Lp8: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp9;
			L_p107 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = L_p107;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp9;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp9;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp9;
			mxv_i49 = mxs_scope(_m,458,mxs_fath(_m,458,L_p107));
			goto L49;
		}
		Lp9: ;
			mxv_i49 = mxs_scope(_m,459,mxs_fath(_m,459,N));
		L49: ;
	}
	return mxv_i49;
}

ELEMENT  mxx_lookup_params(char *f, int l,ELEMENT ID,ELEMENT N){
ELEMENT mxv_i52, mxv_i51, IDN_p112;
 IFNIL(ID) IFNIL(N)
 IS(ID,_Ident,f,l,"lookup_params",1) IS(N,_Name_,f,l,"lookup_params",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 4 ) goto Lp12;
			if( !mxs_is(_c,0,mxv_IR,_Name_) ) goto Lp12;
			IDN_p112 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = IDN_p112;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp12;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,ID,mxs_term(_m,469,IDN_p112)) ){
				mxv_i52 = N;
				goto L52;
			}
			mxv_i52 = mxs_lookup_params(_m,470,ID,mxs_rbroth(_m,470,N));
			L52: ;
		}
			mxv_i51 = mxv_i52;
			goto L51;
		}
		Lp12: ;
			mxv_i51 = mxs_nil(_m,471);
		L51: ;
	}
	return mxv_i51;
}

ELEMENT  mxx_lookup_item(char *f, int l,ELEMENT ID,ELEMENT IT){
ELEMENT mxv_i54, mxv_i53, ILP_p114, N_p115, IDN_p116, IT1_p119;
 IFNIL(ID) IFNIL(IT)
 IS(ID,_Ident,f,l,"lookup_item",1) IS(IT,_Item_,f,l,"lookup_item",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp13;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp13;
			ILP_p114 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ILP_p114;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp13;
			N_p115 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p115;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp13;
			if( mxs_numsons(_c,0, mxv_IR ) != 4 ) goto Lp13;
			IDN_p116 = mxs_son(_c,0,1,mxs_son(_c,0,3,mxv_anchor));
			mxv_IR = IDN_p116;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp13;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,ID,mxs_term(_m,476,IDN_p116)) ){
				mxv_i54 = N_p115;
				goto L54;
			}
			if( mxs_is(_m,477,ILP_p114,_ItemList_) ){
				mxv_i54 = mxs_lookup_items(_m,477,ID,mxs_son(_m,477,mxs_itoe(_c,0,1),ILP_p114));
				goto L54;
			}
			mxv_i54 = mxs_nil(_m,478);
			L54: ;
		}
			mxv_i53 = mxv_i54;
			goto L53;
		}
		Lp13: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp14;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp14;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp14;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp14;
			if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp14;
			IT1_p119 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = IT1_p119;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp14;
			mxv_IR = mxs_son(_c,0,3,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp14;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp14;
			mxv_i53 = mxs_lookup_items(_m,479,ID,IT1_p119);
			goto L53;
		}
		Lp14: ;
			mxv_i53 = mxs_nil(_m,480);
		L53: ;
	}
	return mxv_i53;
}

ELEMENT  mxx_lookup_items(char *f, int l,ELEMENT ID,ELEMENT IT){
ELEMENT mxv_i55, mxv_l5, N_l5;
 IFNIL(ID) IFNIL(IT)
 IS(ID,_Ident,f,l,"lookup_items",1) IS(IT,_Item_,f,l,"lookup_items",2)
	{  /* LetExpr */
		N_l5 = mxs_lookup_item(_m,484,ID,IT);
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,N_l5,mxs_nil(_m,485))) ){
				mxv_i55 = N_l5;
				goto L55;
			}
			mxv_i55 = mxs_lookup_items(_m,486,ID,mxs_rbroth(_m,486,IT));
			L55: ;
		}
		mxv_l5 = mxv_i55;
	}
	return mxv_l5;
}

ELEMENT  mxx_lookup_cond(char *f, int l,ELEMENT ID,ELEMENT PAT){
ELEMENT mxv_i56, mxv_l6, N_l6;
 IFNIL(ID) IFNIL(PAT)
 IS(ID,_Ident,f,l,"lookup_cond",1) IS(PAT,_Pattern_,f,l,"lookup_cond",2)
	{  /* LetExpr */
		N_l6 = mxs_lookup_item(_m,490,ID,PAT);
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,N_l6,mxs_nil(_m,491))) ){
				mxv_i56 = N_l6;
				goto L56;
			}
			mxv_i56 = mxs_lookup_cond(_m,492,ID,mxs_rbroth(_m,492,PAT));
			L56: ;
		}
		mxv_l6 = mxv_i56;
	}
	return mxv_l6;
}

ELEMENT  mxx_lookup(char *f, int l,ELEMENT ID,ELEMENT S){
ELEMENT mxv_i58, mxv_i59, mxv_l7, L_l7, mxv_i57, N_p122, NID_p123, PAR_p126, PAT_p129, PAT_p131;
 IFNIL(ID) IFNIL(S)
 IS(ID,_Ident,f,l,"lookup",1) IS(S,_Scope_,f,l,"lookup",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp15;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp15;
			N_p122 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = N_p122;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp15;
			if( mxs_numsons(_c,0, mxv_IR ) != 4 ) goto Lp15;
			NID_p123 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = NID_p123;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp15;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_term(_m,497,NID_p123),ID) ){
				mxv_i58 = N_p122;
				goto L58;
			}
			mxv_i58 = mxs_lookup(_m,497,ID,mxs_encl_scope(_m,497,S));
			L58: ;
		}
			mxv_i57 = mxv_i58;
			goto L57;
		}
		Lp15: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 3 ) goto Lp16;
			if( !mxs_is(_c,0,mxv_IR,_ApplyEntity_) ) goto Lp16;
			mxv_IR = mxs_son(_c,0,3,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp16;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp16;
			PAR_p126 = mxs_son(_c,0,1,mxs_son(_c,0,3,mxv_anchor));
			mxv_IR = PAR_p126;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp16;
			mxv_i57 = mxs_lookup_params(_m,498,ID,PAR_p126);
			goto L57;
		}
		Lp16: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp17;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp17;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp17;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp17;
			PAT_p129 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = PAT_p129;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp17;
			mxv_i57 = mxs_lookup_cond(_m,499,ID,PAT_p129);
			goto L57;
		}
		Lp17: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp18;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp18;
			PAT_p131 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = PAT_p131;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp18;
		{  /* LetExpr */
			L_l7 = mxs_lookup(_m,501,ID,mxs_encl_scope(_m,501,S));
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,L_l7,mxs_nil(_m,502))) ){
					mxv_i59 = L_l7;
					goto L59;
				}
				mxv_i59 = mxs_lookup_item(_m,503,ID,PAT_p131);
				L59: ;
			}
			mxv_l7 = mxv_i59;
		}
			mxv_i57 = mxv_l7;
			goto L57;
		}
		Lp18: ;
			mxv_i57 = mxs_nil(_m,504);
		L57: ;
	}
	return mxv_i57;
}

ELEMENT  mxx_countastrks(char *f, int l,ELEMENT ITL,ELEMENT sum){
ELEMENT mxv_i68;
 IFNIL(ITL) IFNIL(sum)
 IS(ITL,_ItemList,f,l,"countastrks",1) IS(sum,_Int,f,l,"countastrks",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,ITL,mxs_ItemList(_m,540)) ){
			mxv_i68 = sum;
			goto L68;
		}
		if( mxs_is(_m,541,mxs_subterm(_m,541,mxs_itoe(_c,0,1),ITL),_Asterisk) ){
			mxv_i68 = mxs_countastrks(_m,541,mxs_back(_m,541,ITL),mxs_add(_m,541,sum,mxs_itoe(_c,0,1)));
			goto L68;
		}
		mxv_i68 = mxs_countastrks(_m,542,mxs_back(_m,542,ITL),sum);
		L68: ;
	}
	return mxv_i68;
}

ELEMENT  mxx_smallestlistprodcd(char *f, int l){
	return mxs_neg(_m,614,mxs_add(_m,614,mxs_number(_m,614,_ListProd_),mxs_add(_m,615,mxs_number(_m,615,_TupelProd_),mxs_sub(_m,615,mxs_number(_m,615,_PredeclProd_),mxs_itoe(_c,0,2)))));
}

ELEMENT  mxx_prodcd(char *f, int l,ELEMENT PN){
ELEMENT mxv_i83;
 IFNIL(PN)
 IS(PN,_Production_,f,l,"prodcd",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_PredeclProd_) ) goto Lp20;
			mxv_i83 = mxs_predeclprodcd(_m,622,PN);
			goto L83;
		}
		Lp20: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp21;
			mxv_i83 = mxs_classprodcd(_m,623,PN);
			goto L83;
		}
		Lp21: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_TupelProd_) ) goto Lp22;
			mxv_i83 = mxs_tupelprodcd(_m,624,PN);
			goto L83;
		}
		Lp22: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_ListProd_) ) goto Lp23;
			mxv_i83 = mxs_listprodcd(_m,625,PN);
			goto L83;
		}
		Lp23: ;
			mxv_i83 = mxs_nil(_m,626);
		L83: ;
	}
	return mxv_i83;
}

ELEMENT  mxx_next_left_pat(char *f, int l,ELEMENT IT){
ELEMENT mxv_i84, mxv_l11, LIT_l11;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"next_left_pat",1)
	{  /* LetExpr */
		LIT_l11 = mxs_lbroth(_m,638,IT);
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l11;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp24;
				mxv_i84 = mxs_next_left_pat(_m,639,LIT_l11);
				goto L84;
			}
			Lp24: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l11;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp25;
				mxv_i84 = mxs_next_left_pat(_m,640,LIT_l11);
				goto L84;
			}
			Lp25: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l11;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp26;
				mxv_i84 = LIT_l11;
				goto L84;
			}
			Lp26: ;
				mxv_i84 = mxs_nil(_m,642);
			L84: ;
		}
		mxv_l11 = mxv_i84;
	}
	return mxv_l11;
}

ELEMENT  mxx_patnposition(char *f, int l,ELEMENT IT,ELEMENT dist){
ELEMENT mxv_i85, mxv_l12, LIT_l12;
 IFNIL(IT) IFNIL(dist)
 IS(IT,_Item_,f,l,"patnposition",1) IS(dist,_Int,f,l,"patnposition",2)
	{  /* LetExpr */
		LIT_l12 = mxs_lbroth(_m,646,IT);
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l12;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp27;
				mxv_i85 = mxs_patnposition(_m,647,LIT_l12,mxs_add(_m,647,dist,mxs_itoe(_c,0,1)));
				goto L85;
			}
			Lp27: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l12;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp28;
				mxv_i85 = mxs_patnposition(_m,648,LIT_l12,dist);
				goto L85;
			}
			Lp28: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l12;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp29;
				mxv_i85 = dist;
				goto L85;
			}
			Lp29: ;
				mxv_i85 = dist;
			L85: ;
		}
		mxv_l12 = mxv_i85;
	}
	return mxv_l12;
}

ELEMENT  mxx_next_pat_for_codegen(char *f, int l,ELEMENT PN){
ELEMENT mxv_i88, mxv_l13, NLP_l13, mxv_i87, SPN_p192, IT_p195;
 IFNIL(PN)
 IS(PN,_Pattern_,f,l,"next_pat_for_codegen",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp30;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp30;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp30;
			if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp30;
			SPN_p192 = mxs_son(_c,0,-1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = SPN_p192;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp30;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp30;
			mxv_i87 = SPN_p192;
			goto L87;
		}
		Lp30: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp31;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp31;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp31;
			if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp31;
			IT_p195 = mxs_son(_c,0,-1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = IT_p195;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp31;
		{  /* LetExpr */
			NLP_l13 = mxs_next_left_pat(_m,662,IT_p195);
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,NLP_l13,mxs_nil(_m,663))) ){
					mxv_i88 = NLP_l13;
					goto L88;
				}
				mxv_i88 = mxs_next_pat_upthetree(_m,663,PN);
				L88: ;
			}
			mxv_l13 = mxv_i88;
		}
			mxv_i87 = mxv_l13;
			goto L87;
		}
		Lp31: ;
			mxv_i87 = mxs_next_pat_upthetree(_m,664,PN);
		L87: ;
	}
	return mxv_i87;
}

ELEMENT  mxx_next_pat_upthetree(char *f, int l,ELEMENT PN){
ELEMENT mxv_i89;
 IFNIL(PN)
 IS(PN,_Pattern_,f,l,"next_pat_upthetree",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,668,mxs_patnpos(_m,668,PN),_TopPosition) ){
			mxv_i89 = mxs_rbroth(_m,668,PN);
			goto L89;
		}
		if( mxs_is(_m,669,mxs_patnpos(_m,669,PN),_AbsPosition) ){
			mxv_i89 = mxs_next_pat_upthetree(_m,669,mxs_fath(_m,669,mxs_fath(_m,669,PN)));
			goto L89;
		}
		mxv_i89 = mxs_next_left_pat(_m,670,PN);
		L89: ;
	}
	return mxv_i89;
}

ELEMENT  mxx_pat_absoff_pos(char *f, int l,ELEMENT N){
ELEMENT mxv_i90;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_absoff_pos",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,679,N),mxs_nil(_m,679)) ){
			mxv_i90 = mxs_itoe(_c,0,1);
			goto L90;
		}
		if( mxs_is(_m,680,mxs_lbroth(_m,680,N),_Asterisk_) ){
			mxv_i90 = mxs_nil(_m,680);
			goto L90;
		}
		mxv_i90 = mxs_add(_m,681,mxs_pat_absoff_pos(_m,681,mxs_lbroth(_m,681,N)),mxs_itoe(_c,0,1));
		L90: ;
	}
	return mxv_i90;
}

ELEMENT  mxx_pat_reloff_pos(char *f, int l,ELEMENT N,ELEMENT target){
ELEMENT mxv_i91;
 IFNIL(N) IFNIL(target)
 IS(N,_Item_,f,l,"pat_reloff_pos",1) IS(target,_Item_,f,l,"pat_reloff_pos",2)
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,685,mxs_fath(_m,685,N),_ItemList_)) ){
			mxv_i91 = mxs_nil(_m,685);
			goto L91;
		}
		if( mxs_is(_m,686,mxs_lbroth(_m,686,N),_Asterisk_) ){
			mxv_i91 = mxs_nil(_m,686);
			goto L91;
		}
		if( mxs_eq(_m,0,mxs_lbroth(_m,687,N),target) ){
			mxv_i91 = mxs_itoe(_c,0,1);
			goto L91;
		}
		mxv_i91 = mxs_add(_m,688,mxs_pat_reloff_pos(_m,688,mxs_lbroth(_m,688,N),target),mxs_itoe(_c,0,1));
		L91: ;
	}
	return mxv_i91;
}

ELEMENT  mxx_pat_absoff_neg(char *f, int l,ELEMENT N){
ELEMENT mxv_i92;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_absoff_neg",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,695,N),mxs_nil(_m,695)) ){
			mxv_i92 = mxs_itoe(_c,0,-1);
			goto L92;
		}
		if( mxs_is(_m,696,mxs_rbroth(_m,696,N),_Asterisk_) ){
			mxv_i92 = mxs_nil(_m,696);
			goto L92;
		}
		mxv_i92 = mxs_sub(_m,697,mxs_pat_absoff_neg(_m,697,mxs_rbroth(_m,697,N)),mxs_itoe(_c,0,1));
		L92: ;
	}
	return mxv_i92;
}

ELEMENT  mxx_pat_reloff_neg(char *f, int l,ELEMENT N,ELEMENT target){
ELEMENT mxv_i93;
 IFNIL(N) IFNIL(target)
 IS(N,_Item_,f,l,"pat_reloff_neg",1) IS(target,_Item_,f,l,"pat_reloff_neg",2)
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,701,mxs_fath(_m,701,N),_ItemList_)) ){
			mxv_i93 = mxs_nil(_m,701);
			goto L93;
		}
		if( mxs_is(_m,702,mxs_rbroth(_m,702,N),_Asterisk_) ){
			mxv_i93 = mxs_nil(_m,702);
			goto L93;
		}
		if( mxs_eq(_m,0,mxs_rbroth(_m,703,N),target) ){
			mxv_i93 = mxs_itoe(_c,0,-1);
			goto L93;
		}
		mxv_i93 = mxs_sub(_m,704,mxs_pat_reloff_neg(_m,704,mxs_rbroth(_m,704,N),target),mxs_itoe(_c,0,1));
		L93: ;
	}
	return mxv_i93;
}

ELEMENT  mxx_pat_absoff(char *f, int l,ELEMENT N){
ELEMENT mxv_i94, mxv_l14, X_l14;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_absoff",1)
	{  /* LetExpr */
		X_l14 = mxs_pat_absoff_pos(_m,711,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,X_l14,mxs_nil(_m,712)) ){
				mxv_i94 = mxs_pat_absoff_neg(_m,712,N);
				goto L94;
			}
			mxv_i94 = X_l14;
			L94: ;
		}
		mxv_l14 = mxv_i94;
	}
	return mxv_l14;
}

ELEMENT  mxx_pat_reloff(char *f, int l,ELEMENT N,ELEMENT target){
ELEMENT mxv_i95, mxv_l15, X_l15;
 IFNIL(N) IFNIL(target)
 IS(N,_Item_,f,l,"pat_reloff",1) IS(target,_Item_,f,l,"pat_reloff",2)
	{  /* LetExpr */
		X_l15 = mxs_pat_reloff_pos(_m,716,N,target);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,X_l15,mxs_nil(_m,717)) ){
				mxv_i95 = mxs_pat_reloff_neg(_m,717,N,target);
				goto L95;
			}
			mxv_i95 = X_l15;
			L95: ;
		}
		mxv_l15 = mxv_i95;
	}
	return mxv_l15;
}

ELEMENT  mxx_abs_itempos(char *f, int l,ELEMENT N){
ELEMENT mxv_i96;
 IFNIL(N)
 IS(N,_Item_,f,l,"abs_itempos",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,725,mxs_fath(_m,725,N),_ItemList_) ){
			mxv_i96 = mxs_pat_absoff(_m,725,N);
			goto L96;
		}
		mxv_i96 = mxs_itoe(_c,0,0);
		L96: ;
	}
	return mxv_i96;
}

ELEMENT  mxx_lmin_itempos(char *f, int l,ELEMENT N){
ELEMENT mxv_i99, mxv_i98, mxv_i97;
 IFNIL(N)
 IS(N,_Item_,f,l,"lmin_itempos",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_lbroth(_m,729,N),mxs_nil(_m,729))) ){
			mxv_i98 = mxs_false(_m,0);
			goto L98;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,729,N,_Asterisk_)) ){
			mxv_i99 = mxs_true(_m,0);
			goto L99;
		}
		mxv_i99 = mxs_false(_m,0);
		L99: ;
	}
		mxv_i98 = mxv_i99;
		L98: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i98) ){
			mxv_i97 = mxs_itoe(_c,0,1);
			goto L97;
		}
		if( mxs_eq(_m,0,mxs_lbroth(_m,730,N),mxs_nil(_m,730)) ){
			mxv_i97 = mxs_itoe(_c,0,0);
			goto L97;
		}
		if( mxs_is(_m,731,N,_Asterisk_) ){
			mxv_i97 = mxs_lmin_itempos(_m,731,mxs_lbroth(_m,731,N));
			goto L97;
		}
		mxv_i97 = mxs_add(_m,732,mxs_lmin_itempos(_m,732,mxs_lbroth(_m,732,N)),mxs_itoe(_c,0,1));
		L97: ;
	}
	return mxv_i97;
}

ELEMENT  mxx_rmin_itempos(char *f, int l,ELEMENT N){
ELEMENT mxv_i102, mxv_i101, mxv_i100;
 IFNIL(N)
 IS(N,_Item_,f,l,"rmin_itempos",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_rbroth(_m,735,N),mxs_nil(_m,735))) ){
			mxv_i101 = mxs_false(_m,0);
			goto L101;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,735,N,_Asterisk_)) ){
			mxv_i102 = mxs_true(_m,0);
			goto L102;
		}
		mxv_i102 = mxs_false(_m,0);
		L102: ;
	}
		mxv_i101 = mxv_i102;
		L101: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i101) ){
			mxv_i100 = mxs_itoe(_c,0,-1);
			goto L100;
		}
		if( mxs_eq(_m,0,mxs_rbroth(_m,736,N),mxs_nil(_m,736)) ){
			mxv_i100 = mxs_itoe(_c,0,0);
			goto L100;
		}
		if( mxs_is(_m,737,N,_Asterisk_) ){
			mxv_i100 = mxs_rmin_itempos(_m,737,mxs_rbroth(_m,737,N));
			goto L100;
		}
		mxv_i100 = mxs_sub(_m,738,mxs_rmin_itempos(_m,738,mxs_rbroth(_m,738,N)),mxs_itoe(_c,0,1));
		L100: ;
	}
	return mxv_i100;
}

ELEMENT  mxx_path(char *f, int l,ELEMENT V,ELEMENT N){
ELEMENT mxv_i105, mxv_i104, mxv_l17, VR_l17, mxv_i106, mxv_i103, mxv_l16, VA_l16;
 IFNIL(V) IFNIL(N)
 IS(V,_Item_,f,l,"path",1) IS(N,_Item_,f,l,"path",2)
	{  /* LetExpr */
		VA_l16 = mxs_pat_absoff(_m,747,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_fath(_m,748,V),mxs_fath(_m,748,N)) ){
			{  /* LetExpr */
				VR_l17 = mxs_pat_reloff(_m,749,V,N);
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,V,N) ){
						mxv_i104 = mxs_Relationship(_m,750);
						goto L104;
					}
					if( ( ! mxs_eq(_m,0,VR_l17,mxs_nil(_m,751))) ){
					{  /* FormulaCaseList */
						if( mxs_lt(_m,752,mxs_itoe(_c,0,0),VR_l17) ){
							mxv_i105 = mxs_appfront(_m,752,mxs_Lbroth(_m,752,VR_l17),mxs_Relationship(_m,752));
							goto L105;
						}
						mxv_i105 = mxs_appfront(_m,753,mxs_Rbroth(_m,753,mxs_neg(_m,753,VR_l17)),mxs_Relationship(_m,753));
						L105: ;
					}
						mxv_i104 = mxv_i105;
						goto L104;
					}
					if( ( ! mxs_eq(_m,0,VA_l16,mxs_nil(_m,755))) ){
						mxv_i104 = mxs_appfront(_m,755,mxs_Son(_m,755,VA_l16),mxs_appfront(_m,755,mxs_Fath(_m,755),mxs_Relationship(_m,755)));
						goto L104;
					}
					mxv_i104 = mxs_nil(_m,756);
					L104: ;
				}
				mxv_l17 = mxv_i104;
			}
				mxv_i103 = mxv_l17;
				goto L103;
			}
			if( mxs_desc(_m,758,V,mxs_fath(_m,758,mxs_fath(_m,758,N))) ){
				mxv_i103 = mxs_appback(_m,758,mxs_path(_m,758,mxs_fath(_m,758,mxs_fath(_m,758,V)),N),mxs_Fath(_m,758));
				goto L103;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,VA_l16,mxs_nil(_m,760))) ){
				mxv_i106 = mxs_appfront(_m,760,mxs_Son(_m,760,VA_l16),mxs_path(_m,760,V,mxs_fath(_m,760,mxs_fath(_m,760,N))));
				goto L106;
			}
			mxv_i106 = mxs_nil(_m,761);
			L106: ;
		}
			mxv_i103 = mxv_i106;
			L103: ;
		}
		mxv_l16 = mxv_i103;
	}
	return mxv_l16;
}

ELEMENT  mxx_search_bound_names_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_i107;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_bound_names_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,765,IT),mxs_nil(_m,765)) ){
			mxv_i107 = mxs_search_bound_names(_m,765,IT);
			goto L107;
		}
		mxv_i107 = mxs_conc(_m,766,mxs_search_bound_names(_m,766,IT),mxs_search_bound_names_rec(_m,766,mxs_rbroth(_m,766,IT)));
		L107: ;
	}
	return mxv_i107;
}

ELEMENT  mxx_search_bound_names(char *f, int l,ELEMENT IT){
ELEMENT mxv_i109, IT1_p200, mxv_i112, mxv_i111, mxv_i110, mxv_l18, BNL_l18, mxv_i108, ITL_p197, N_p198;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_bound_names",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp32;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp32;
			ITL_p197 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p197;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp32;
			N_p198 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p198;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp32;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p197;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp33;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp33;
					IT1_p200 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p200;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp33;
					mxv_i109 = mxs_search_bound_names_rec(_m,771,IT1_p200);
					goto L109;
				}
				Lp33: ;
					mxv_i109 = mxs_NameNList(_m,772);
				L109: ;
			}
			BNL_l18 = mxv_i109;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,774,N_p198,_Name_)) ){
					mxv_i111 = mxs_false(_m,0);
					goto L111;
				}
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,mxs_bind_pos(_m,774,N_p198),N_p198)) ){
					mxv_i112 = mxs_true(_m,0);
					goto L112;
				}
				mxv_i112 = mxs_false(_m,0);
				L112: ;
			}
				mxv_i111 = mxv_i112;
				L111: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i111) ){
					mxv_i110 = mxs_appfront(_m,774,N_p198,BNL_l18);
					goto L110;
				}
				mxv_i110 = BNL_l18;
				L110: ;
			}
			mxv_l18 = mxv_i110;
		}
			mxv_i108 = mxv_l18;
			goto L108;
		}
		Lp32: ;
			mxv_i108 = mxs_NameNList(_m,777);
		L108: ;
	}
	return mxv_i108;
}

ELEMENT  mxx_search_free_items_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_i113;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_free_items_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,781,IT),mxs_nil(_m,781)) ){
			mxv_i113 = mxs_search_free_items(_m,781,IT);
			goto L113;
		}
		mxv_i113 = mxs_conc(_m,782,mxs_search_free_items(_m,782,IT),mxs_search_free_items_rec(_m,782,mxs_rbroth(_m,782,IT)));
		L113: ;
	}
	return mxv_i113;
}

ELEMENT  mxx_search_free_items(char *f, int l,ELEMENT IT){
ELEMENT mxv_i115, IT1_p205, mxv_i119, mxv_i118, mxv_i120, mxv_i117, mxv_i116, mxv_l19, FIL_l19, mxv_i114, ITL_p202, N_p203;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_free_items",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp34;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp34;
			ITL_p202 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p202;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp34;
			N_p203 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p203;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp34;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p202;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp35;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp35;
					IT1_p205 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p205;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp35;
					mxv_i115 = mxs_search_free_items_rec(_m,787,IT1_p205);
					goto L115;
				}
				Lp35: ;
					mxv_i115 = mxs_ItemNList(_m,788);
				L115: ;
			}
			FIL_l19 = mxv_i115;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,790,N_p203,_Name_)) ){
					mxv_i118 = mxs_false(_m,0);
					goto L118;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_bind_pos(_m,790,N_p203),N_p203) ){
					mxv_i119 = mxs_true(_m,0);
					goto L119;
				}
				mxv_i119 = mxs_false(_m,0);
				L119: ;
			}
				mxv_i118 = mxv_i119;
				L118: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i118) ){
					mxv_i117 = mxs_true(_m,0);
					goto L117;
				}
			{  /* FormulaCaseList */
				if( mxs_is(_m,790,N_p203,_Blank_) ){
					mxv_i120 = mxs_true(_m,0);
					goto L120;
				}
				mxv_i120 = mxs_false(_m,0);
				L120: ;
			}
				mxv_i117 = mxv_i120;
				L117: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i117) ){
					mxv_i116 = mxs_appfront(_m,791,IT,FIL_l19);
					goto L116;
				}
				mxv_i116 = FIL_l19;
				L116: ;
			}
			mxv_l19 = mxv_i116;
		}
			mxv_i114 = mxv_l19;
			goto L114;
		}
		Lp34: ;
			mxv_i114 = mxs_ItemNList(_m,794);
		L114: ;
	}
	return mxv_i114;
}

ELEMENT  mxx_search_blanks_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_i121;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_blanks_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,798,IT),mxs_nil(_m,798)) ){
			mxv_i121 = mxs_search_blanks(_m,798,IT);
			goto L121;
		}
		mxv_i121 = mxs_conc(_m,799,mxs_search_blanks(_m,799,IT),mxs_search_blanks_rec(_m,799,mxs_rbroth(_m,799,IT)));
		L121: ;
	}
	return mxv_i121;
}

ELEMENT  mxx_search_blanks(char *f, int l,ELEMENT IT){
ELEMENT mxv_i123, IT1_p210, mxv_i122, ITL_p207, N_p208;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_blanks",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp36;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp36;
			ITL_p207 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p207;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp36;
			N_p208 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p208;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp36;
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = ITL_p207;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp37;
				if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp37;
				IT1_p210 = mxs_son(_c,0,1,mxv_anchor);
				mxv_IR = IT1_p210;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp37;
				mxv_i123 = mxs_search_blanks_rec(_m,804,IT1_p210);
				goto L123;
			}
			Lp37: ;
				mxv_i123 = mxs_ItemNList(_m,805);
			L123: ;
		}
			mxv_i122 = mxv_i123;
			goto L122;
		}
		Lp36: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp38;
			mxv_i122 = mxs_appback(_m,807,mxs_ItemNList(_m,807),IT);
			goto L122;
		}
		Lp38: ;
			mxv_i122 = mxs_ItemNList(_m,809);
		L122: ;
	}
	return mxv_i122;
}

ELEMENT  mxx_search_free_p_names_rec(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_i132;
 IFNIL(IT) IFNIL(ID)
 IS(IT,_Item_,f,l,"search_free_p_names_rec",1) IS(ID,_Ident,f,l,"search_free_p_names_rec",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,869,IT),mxs_nil(_m,869)) ){
			mxv_i132 = mxs_search_free_p_names(_m,869,IT,ID);
			goto L132;
		}
		mxv_i132 = mxs_conc(_m,870,mxs_search_free_p_names(_m,870,IT,ID),mxs_search_free_p_names_rec(_m,870,mxs_rbroth(_m,870,IT),ID));
		L132: ;
	}
	return mxv_i132;
}

ELEMENT  mxx_search_free_p_names(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_i134, IT1_p230, mxv_i139, mxv_i138, mxv_i137, mxv_i136, mxv_i135, mxv_l21, PNL_l21, mxv_i133, ITL_p227, N_p228;
 IFNIL(IT) IFNIL(ID)
 IS(IT,_Item_,f,l,"search_free_p_names",1) IS(ID,_Ident,f,l,"search_free_p_names",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp40;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp40;
			ITL_p227 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p227;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp40;
			N_p228 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p228;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp40;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p227;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp41;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp41;
					IT1_p230 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p230;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp41;
					mxv_i134 = mxs_search_free_p_names_rec(_m,875,IT1_p230,ID);
					goto L134;
				}
				Lp41: ;
					mxv_i134 = mxs_ExprNList(_m,876);
				L134: ;
			}
			PNL_l21 = mxv_i134;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,878,N_p228,_Name_)) ){
					mxv_i136 = mxs_false(_m,0);
					goto L136;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! ( ! mxs_eq(_m,0,ID,mxs_term(_m,878,mxs_son(_m,878,mxs_itoe(_c,0,1),N_p228))))) ){
					mxv_i138 = mxs_false(_m,0);
					goto L138;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_bind_pos(_m,878,N_p228),N_p228) ){
					mxv_i139 = mxs_true(_m,0);
					goto L139;
				}
				mxv_i139 = mxs_false(_m,0);
				L139: ;
			}
				mxv_i138 = mxv_i139;
				L138: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i138) ){
					mxv_i137 = mxs_true(_m,0);
					goto L137;
				}
				mxv_i137 = mxs_false(_m,0);
				L137: ;
			}
				mxv_i136 = mxv_i137;
				L136: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i136) ){
					mxv_i135 = mxs_appfront(_m,878,N_p228,PNL_l21);
					goto L135;
				}
				mxv_i135 = PNL_l21;
				L135: ;
			}
			mxv_l21 = mxv_i135;
		}
			mxv_i133 = mxv_l21;
			goto L133;
		}
		Lp40: ;
			mxv_i133 = mxs_ExprNList(_m,881);
		L133: ;
	}
	return mxv_i133;
}

ELEMENT  mxx_search_bound_p_names_rec(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_i140;
 IFNIL(IT) IFNIL(ID)
 IS(IT,_Item_,f,l,"search_bound_p_names_rec",1) IS(ID,_Ident,f,l,"search_bound_p_names_rec",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,885,IT),mxs_nil(_m,885)) ){
			mxv_i140 = mxs_search_bound_p_names(_m,885,IT,ID);
			goto L140;
		}
		mxv_i140 = mxs_conc(_m,886,mxs_search_bound_p_names(_m,886,IT,ID),mxs_search_bound_p_names_rec(_m,886,mxs_rbroth(_m,886,IT),ID));
		L140: ;
	}
	return mxv_i140;
}

ELEMENT  mxx_search_bound_p_names(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_i142, IT1_p235, mxv_i147, mxv_i146, mxv_i145, mxv_i144, mxv_i143, mxv_l22, PNL_l22, mxv_i141, ITL_p232, N_p233;
 IFNIL(IT) IFNIL(ID)
 IS(IT,_Item_,f,l,"search_bound_p_names",1) IS(ID,_Ident,f,l,"search_bound_p_names",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp42;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp42;
			ITL_p232 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p232;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp42;
			N_p233 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p233;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp42;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p232;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp43;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp43;
					IT1_p235 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p235;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp43;
					mxv_i142 = mxs_search_bound_p_names_rec(_m,891,IT1_p235,ID);
					goto L142;
				}
				Lp43: ;
					mxv_i142 = mxs_ExprNList(_m,892);
				L142: ;
			}
			PNL_l22 = mxv_i142;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,894,N_p233,_Name_)) ){
					mxv_i144 = mxs_false(_m,0);
					goto L144;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! ( ! mxs_eq(_m,0,ID,mxs_term(_m,894,mxs_son(_m,894,mxs_itoe(_c,0,1),N_p233))))) ){
					mxv_i146 = mxs_false(_m,0);
					goto L146;
				}
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,mxs_bind_pos(_m,894,N_p233),N_p233)) ){
					mxv_i147 = mxs_true(_m,0);
					goto L147;
				}
				mxv_i147 = mxs_false(_m,0);
				L147: ;
			}
				mxv_i146 = mxv_i147;
				L146: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i146) ){
					mxv_i145 = mxs_true(_m,0);
					goto L145;
				}
				mxv_i145 = mxs_false(_m,0);
				L145: ;
			}
				mxv_i144 = mxv_i145;
				L144: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i144) ){
					mxv_i143 = mxs_appfront(_m,894,N_p233,PNL_l22);
					goto L143;
				}
				mxv_i143 = PNL_l22;
				L143: ;
			}
			mxv_l22 = mxv_i143;
		}
			mxv_i141 = mxv_l22;
			goto L141;
		}
		Lp42: ;
			mxv_i141 = mxs_ExprNList(_m,897);
		L141: ;
	}
	return mxv_i141;
}

ELEMENT  mxx_search_patt_names(char *f, int l,ELEMENT IT,ELEMENT ID){
 IFNIL(IT) IFNIL(ID)
 IS(IT,_Item_,f,l,"search_patt_names",1) IS(ID,_Ident,f,l,"search_patt_names",2)
	return mxs_conc(_m,901,mxs_search_bound_p_names(_m,901,IT,ID),mxs_search_free_p_names(_m,901,IT,ID));
}

ELEMENT  mxx_search_patt_sorts_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_i148;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_patt_sorts_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,905,IT),mxs_nil(_m,905)) ){
			mxv_i148 = mxs_search_patt_sorts(_m,905,IT);
			goto L148;
		}
		mxv_i148 = mxs_conc(_m,906,mxs_search_patt_sorts(_m,906,IT),mxs_search_patt_sorts_rec(_m,906,mxs_rbroth(_m,906,IT)));
		L148: ;
	}
	return mxv_i148;
}

ELEMENT  mxx_search_patt_sorts(char *f, int l,ELEMENT IT){
ELEMENT mxv_i150, IT1_p240, mxv_i151, mxv_l23, BNL_l23, mxv_i149, SORT_p237, ITL_p238;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_patt_sorts",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp44;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp44;
			SORT_p237 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = SORT_p237;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp44;
			ITL_p238 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p238;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp44;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p238;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp45;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp45;
					IT1_p240 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p240;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp45;
					mxv_i150 = mxs_search_patt_sorts_rec(_m,910,IT1_p240);
					goto L150;
				}
				Lp45: ;
					mxv_i150 = mxs_SortIdNList(_m,911);
				L150: ;
			}
			BNL_l23 = mxv_i150;
			{  /* FormulaCaseList */
				if( mxs_is(_m,913,SORT_p237,_SortId_) ){
					mxv_i151 = mxs_appfront(_m,913,SORT_p237,BNL_l23);
					goto L151;
				}
				mxv_i151 = BNL_l23;
				L151: ;
			}
			mxv_l23 = mxv_i151;
		}
			mxv_i149 = mxv_l23;
			goto L149;
		}
		Lp44: ;
			mxv_i149 = mxs_SortIdNList(_m,916);
		L149: ;
	}
	return mxv_i149;
}

ELEMENT  mxx_search_name_in_patt_rec(char *f, int l,ELEMENT IT,ELEMENT NA){
ELEMENT mxv_i152;
 IFNIL(IT) IFNIL(NA)
 IS(IT,_Item_,f,l,"search_name_in_patt_rec",1) IS(NA,_Ident,f,l,"search_name_in_patt_rec",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,920,IT),mxs_nil(_m,920)) ){
			mxv_i152 = mxs_search_name_in_patt(_m,920,IT,NA);
			goto L152;
		}
		mxv_i152 = mxs_conc(_m,921,mxs_search_name_in_patt(_m,921,IT,NA),mxs_search_name_in_patt_rec(_m,921,mxs_rbroth(_m,921,IT),NA));
		L152: ;
	}
	return mxv_i152;
}

ELEMENT  mxx_search_name_in_patt(char *f, int l,ELEMENT IT,ELEMENT NA){
ELEMENT mxv_i154, IT1_p245, mxv_i157, mxv_i156, mxv_i155, mxv_l24, BNL_l24, mxv_i153, ITL_p242, N_p243;
 IFNIL(IT) IFNIL(NA)
 IS(IT,_Item_,f,l,"search_name_in_patt",1) IS(NA,_Ident,f,l,"search_name_in_patt",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp46;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp46;
			ITL_p242 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p242;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp46;
			N_p243 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p243;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp46;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p242;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp47;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp47;
					IT1_p245 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p245;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp47;
					mxv_i154 = mxs_search_name_in_patt_rec(_m,926,IT1_p245,NA);
					goto L154;
				}
				Lp47: ;
					mxv_i154 = mxs_NameNList(_m,927);
				L154: ;
			}
			BNL_l24 = mxv_i154;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,929,N_p243,_Name_)) ){
					mxv_i156 = mxs_false(_m,0);
					goto L156;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_term(_m,929,mxs_son(_m,929,mxs_itoe(_c,0,1),N_p243)),NA) ){
					mxv_i157 = mxs_true(_m,0);
					goto L157;
				}
				mxv_i157 = mxs_false(_m,0);
				L157: ;
			}
				mxv_i156 = mxv_i157;
				L156: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i156) ){
					mxv_i155 = mxs_appfront(_m,929,N_p243,BNL_l24);
					goto L155;
				}
				mxv_i155 = BNL_l24;
				L155: ;
			}
			mxv_l24 = mxv_i155;
		}
			mxv_i153 = mxv_l24;
			goto L153;
		}
		Lp46: ;
			mxv_i153 = mxs_NameNList(_m,932);
		L153: ;
	}
	return mxv_i153;
}

ELEMENT  mxx_latest_bindpos(char *f, int l,ELEMENT N,ELEMENT NA){
ELEMENT mxv_i160, mxv_i159, mxv_i161, mxv_l26, LBP_l26, mxv_i158, mxv_l25, S_l25;
 IFNIL(N) IFNIL(NA)
 IS(N,_Node,f,l,"latest_bindpos",1) IS(NA,_Name_,f,l,"latest_bindpos",2)
	{  /* LetExpr */
		S_l25 = mxs_encl_patterncase(_m,936,N);
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! ( ! mxs_eq(_m,0,S_l25,mxs_nil(_m,937)))) ){
				mxv_i159 = mxs_false(_m,0);
				goto L159;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_desc(_m,937,mxs_bind_pos(_m,937,NA),S_l25)) ){
				mxv_i160 = mxs_true(_m,0);
				goto L160;
			}
			mxv_i160 = mxs_false(_m,0);
			L160: ;
		}
			mxv_i159 = mxv_i160;
			L159: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i159) ){
			{  /* LetExpr */
				LBP_l26 = mxs_search_name_in_patt(_m,938,mxs_son(_m,938,mxs_itoe(_c,0,1),S_l25),mxs_term(_m,938,mxs_son(_m,938,mxs_itoe(_c,0,1),NA)));
				{  /* FormulaCaseList */
					if( ( ! mxs_eq(_m,0,LBP_l26,mxs_NameNList(_m,939))) ){
						mxv_i161 = mxs_subterm(_m,939,mxs_itoe(_c,0,1),LBP_l26);
						goto L161;
					}
					mxv_i161 = mxs_latest_bindpos(_m,940,mxs_fath(_m,940,S_l25),NA);
					L161: ;
				}
				mxv_l26 = mxv_i161;
			}
				mxv_i158 = mxv_l26;
				goto L158;
			}
			mxv_i158 = mxs_bind_pos(_m,941,NA);
			L158: ;
		}
		mxv_l25 = mxv_i158;
	}
	return mxv_l25;
}

ELEMENT  mxx_par_pos(char *f, int l,ELEMENT N,ELEMENT cnt){
ELEMENT mxv_i162;
 IFNIL(N) IFNIL(cnt)
 IS(N,_Name_,f,l,"par_pos",1) IS(cnt,_Int,f,l,"par_pos",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,945,N),mxs_nil(_m,945)) ){
			mxv_i162 = cnt;
			goto L162;
		}
		mxv_i162 = mxs_par_pos(_m,946,mxs_lbroth(_m,946,N),mxs_add(_m,946,mxs_itoe(_c,0,1),cnt));
		L162: ;
	}
	return mxv_i162;
}

ELEMENT  mxx_corresp_parsort(char *f, int l,ELEMENT N){
 IFNIL(N)
 IS(N,_Name_,f,l,"corresp_parsort",1)
	return mxs_son(_m,950,mxs_par_pos(_m,950,N,mxs_itoe(_c,0,1)),mxs_lbroth(_m,950,mxs_fath(_m,950,N)));
}

ELEMENT  mxx_actpar_pos(char *f, int l,ELEMENT N,ELEMENT cnt){
ELEMENT mxv_i163;
 IFNIL(N) IFNIL(cnt)
 IS(N,_Expr_,f,l,"actpar_pos",1) IS(cnt,_Int,f,l,"actpar_pos",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,954,N),mxs_nil(_m,954)) ){
			mxv_i163 = cnt;
			goto L163;
		}
		mxv_i163 = mxs_actpar_pos(_m,955,mxs_lbroth(_m,955,N),mxs_add(_m,955,mxs_itoe(_c,0,1),cnt));
		L163: ;
	}
	return mxv_i163;
}

ELEMENT  mxx_univ_path(char *f, int l,ELEMENT V,ELEMENT N){
ELEMENT mxv_i166, mxv_i165, mxv_l28, VR_l28, mxv_i167, mxv_i164, mxv_l27, VA_l27;
 IFNIL(V) IFNIL(N)
 IS(V,_Item_,f,l,"univ_path",1) IS(N,_Item_,f,l,"univ_path",2)
	{  /* LetExpr */
		VA_l27 = mxs_pat_absoff(_m,959,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_fath(_m,960,V),mxs_fath(_m,960,N)) ){
			{  /* LetExpr */
				VR_l28 = mxs_pat_reloff(_m,961,V,N);
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,V,N) ){
						mxv_i165 = mxs_Relationship(_m,962);
						goto L165;
					}
					if( ( ! mxs_eq(_m,0,VR_l28,mxs_nil(_m,963))) ){
					{  /* FormulaCaseList */
						if( mxs_lt(_m,964,mxs_itoe(_c,0,0),VR_l28) ){
							mxv_i166 = mxs_appfront(_m,964,mxs_Lbroth(_m,964,VR_l28),mxs_Relationship(_m,964));
							goto L166;
						}
						mxv_i166 = mxs_appfront(_m,965,mxs_Rbroth(_m,965,mxs_neg(_m,965,VR_l28)),mxs_Relationship(_m,965));
						L166: ;
					}
						mxv_i165 = mxv_i166;
						goto L165;
					}
					if( ( ! mxs_eq(_m,0,VA_l27,mxs_nil(_m,967))) ){
						mxv_i165 = mxs_appfront(_m,967,mxs_SonTC(_m,967,VA_l27,mxs_lmin_itempos(_m,967,N),mxs_rmin_itempos(_m,967,N),mxs_num_items(_m,968,mxs_fath(_m,968,mxs_fath(_m,968,N))),mxs_numberofastrks(_m,968,mxs_fath(_m,968,N))),mxs_appfront(_m,969,mxs_Fath(_m,969),mxs_Relationship(_m,969)));
						goto L165;
					}
					mxv_i165 = mxs_appfront(_m,970,mxs_SonTC(_m,970,mxs_itoe(_c,0,0),mxs_lmin_itempos(_m,970,N),mxs_rmin_itempos(_m,970,N),mxs_num_items(_m,971,mxs_fath(_m,971,mxs_fath(_m,971,N))),mxs_numberofastrks(_m,971,mxs_fath(_m,971,N))),mxs_appfront(_m,972,mxs_Fath(_m,972),mxs_Relationship(_m,972)));
					L165: ;
				}
				mxv_l28 = mxv_i165;
			}
				mxv_i164 = mxv_l28;
				goto L164;
			}
			if( mxs_desc(_m,974,V,mxs_fath(_m,974,mxs_fath(_m,974,N))) ){
				mxv_i164 = mxs_appback(_m,974,mxs_univ_path(_m,974,mxs_fath(_m,974,mxs_fath(_m,974,V)),N),mxs_Fath(_m,974));
				goto L164;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,VA_l27,mxs_nil(_m,976))) ){
				mxv_i167 = mxs_appfront(_m,976,mxs_SonTC(_m,976,VA_l27,mxs_lmin_itempos(_m,976,N),mxs_rmin_itempos(_m,976,N),mxs_num_items(_m,977,mxs_fath(_m,977,mxs_fath(_m,977,N))),mxs_numberofastrks(_m,977,mxs_fath(_m,977,N))),mxs_univ_path(_m,978,V,mxs_fath(_m,978,mxs_fath(_m,978,N))));
				goto L167;
			}
			mxv_i167 = mxs_appfront(_m,979,mxs_SonTC(_m,979,mxs_itoe(_c,0,0),mxs_lmin_itempos(_m,979,N),mxs_rmin_itempos(_m,979,N),mxs_num_items(_m,980,mxs_fath(_m,980,mxs_fath(_m,980,N))),mxs_numberofastrks(_m,980,mxs_fath(_m,980,N))),mxs_univ_path(_m,981,V,mxs_fath(_m,981,mxs_fath(_m,981,N))));
			L167: ;
		}
			mxv_i164 = mxv_i167;
			L164: ;
		}
		mxv_l27 = mxv_i164;
	}
	return mxv_l27;
}

ELEMENT  mxx_mk_enl(char *f, int l,ELEMENT ARG){
ELEMENT mxv_i168;
 IFNIL(ARG)
 IS(ARG,_Expr_,f,l,"mk_enl",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,985,ARG),mxs_nil(_m,985)) ){
			mxv_i168 = mxs_appfront(_m,985,ARG,mxs_ExprNList(_m,985));
			goto L168;
		}
		mxv_i168 = mxs_appfront(_m,986,ARG,mxs_mk_enl(_m,986,mxs_rbroth(_m,986,ARG)));
		L168: ;
	}
	return mxv_i168;
}

ELEMENT  mxx_dep_expr(char *f, int l,ELEMENT E){
ELEMENT mxv_i171, mxv_i170, mxv_i172, mxv_i169;
 IFNIL(E)
 IS(E,_Expr_,f,l,"dep_expr",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Name_) ) goto Lp48;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_bind_pos(_m,991,E),E) ){
			{  /* FormulaCaseList */
				if( mxs_is(_m,993,mxs_fath(_m,993,E),_NameList_) ){
					mxv_i171 = mxs_ExprNList(_m,993);
					goto L171;
				}
				if( mxs_is(_m,994,mxs_fath(_m,994,E),_LetExpr_) ){
					mxv_i171 = mxs_appfront(_m,994,mxs_rbroth(_m,994,E),mxs_ExprNList(_m,994));
					goto L171;
				}
				mxv_i171 = mxs_search_bound_p_names(_m,995,mxs_top_pattern(_m,995,E),mxs_term(_m,995,mxs_son(_m,995,mxs_itoe(_c,0,1),E)));
				L171: ;
			}
				mxv_i170 = mxv_i171;
				goto L170;
			}
			mxv_i170 = mxs_appfront(_m,997,mxs_latest_bindpos(_m,997,E,E),mxs_ExprNList(_m,997));
			L170: ;
		}
			mxv_i169 = mxv_i170;
			goto L169;
		}
		Lp48: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp49;
			mxv_i169 = mxs_allexpr(_m,999,E);
			goto L169;
		}
		Lp49: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp50;
			mxv_i169 = mxs_appfront(_m,1001,mxs_son(_m,1001,mxs_itoe(_c,0,3),E),mxs_ExprNList(_m,1001));
			goto L169;
		}
		Lp50: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp51;
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,mxs_numsons(_m,1003,mxs_son(_m,1003,mxs_itoe(_c,0,2),E)),mxs_itoe(_c,0,0))) ){
				mxv_i172 = mxs_mk_enl(_m,1003,mxs_son(_m,1003,mxs_itoe(_c,0,1),mxs_son(_m,1003,mxs_itoe(_c,0,2),E)));
				goto L172;
			}
			mxv_i172 = mxs_ExprNList(_m,1004);
			L172: ;
		}
			mxv_i169 = mxv_i172;
			goto L169;
		}
		Lp51: ;
			mxv_i169 = mxs_ExprNList(_m,1006);
		L169: ;
	}
	return mxv_i169;
}

ELEMENT  mxx_lineof(char *f, int l,ELEMENT E){
ELEMENT mxv_i173;
 IFNIL(E)
 IS(E,_Expr_,f,l,"lineof",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_SortConst_) ) goto Lp52;
			mxv_i173 = mxs_term(_m,1010,mxs_son(_m,1010,mxs_itoe(_c,0,2),mxs_son(_m,1010,mxs_itoe(_c,0,1),E)));
			goto L173;
		}
		Lp52: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp53;
			mxv_i173 = mxs_term(_m,1011,mxs_son(_m,1011,mxs_itoe(_c,0,2),mxs_son(_m,1011,mxs_itoe(_c,0,1),E)));
			goto L173;
		}
		Lp53: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp54;
			mxv_i173 = mxs_term(_m,1012,mxs_son(_m,1012,mxs_itoe(_c,0,3),E));
			goto L173;
		}
		Lp54: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp55;
			mxv_i173 = mxs_lineof(_m,1013,mxs_son(_m,1013,mxs_itoe(_c,0,3),E));
			goto L173;
		}
		Lp55: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_StringExpr_) ) goto Lp56;
			mxv_i173 = mxs_term(_m,1014,mxs_son(_m,1014,mxs_itoe(_c,0,2),E));
			goto L173;
		}
		Lp56: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_DynUndef_) ) goto Lp57;
			mxv_i173 = mxs_itoe(_c,0,0);
			goto L173;
		}
		Lp57: ;
			mxv_i173 = mxs_term(_m,1016,mxs_son(_m,1016,mxs_itoe(_c,0,2),E));
		L173: ;
	}
	return mxv_i173;
}

ELEMENT  mxx_colof(char *f, int l,ELEMENT E){
ELEMENT mxv_i174;
 IFNIL(E)
 IS(E,_Expr_,f,l,"colof",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_SortConst_) ) goto Lp58;
			mxv_i174 = mxs_term(_m,1020,mxs_son(_m,1020,mxs_itoe(_c,0,3),mxs_son(_m,1020,mxs_itoe(_c,0,1),E)));
			goto L174;
		}
		Lp58: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp59;
			mxv_i174 = mxs_term(_m,1021,mxs_son(_m,1021,mxs_itoe(_c,0,3),mxs_son(_m,1021,mxs_itoe(_c,0,1),E)));
			goto L174;
		}
		Lp59: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp60;
			mxv_i174 = mxs_term(_m,1022,mxs_son(_m,1022,mxs_itoe(_c,0,4),E));
			goto L174;
		}
		Lp60: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp61;
			mxv_i174 = mxs_colof(_m,1023,mxs_son(_m,1023,mxs_itoe(_c,0,3),E));
			goto L174;
		}
		Lp61: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_StringExpr_) ) goto Lp62;
			mxv_i174 = mxs_term(_m,1024,mxs_son(_m,1024,mxs_itoe(_c,0,3),E));
			goto L174;
		}
		Lp62: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_DynUndef_) ) goto Lp63;
			mxv_i174 = mxs_itoe(_c,0,0);
			goto L174;
		}
		Lp63: ;
			mxv_i174 = mxs_term(_m,1026,mxs_son(_m,1026,mxs_itoe(_c,0,3),E));
		L174: ;
	}
	return mxv_i174;
}

ELEMENT  mxx_TW_identabb(char *f, int l){
	return mxs_FList(_m,1036);
}

ELEMENT  mxx_TW_emptyset(char *f, int l){
	return mxs_OrValue(_m,1038);
}

ELEMENT  mxx_TW_or(char *f, int l,ELEMENT S,ELEMENT T){
ELEMENT mxv_i176, mxv_i178, mxv_i177, mxv_l29, S1_l29, mxv_i175;
 IFNIL(S) IFNIL(T)
 IS(S,_Value,f,l,"TW_or",1) IS(T,_Value,f,l,"TW_or",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,S,mxs_OrValue(_m,1041)) ){
			mxv_i175 = T;
			goto L175;
		}
		if( mxs_eq(_m,0,T,mxs_OrValue(_m,1042)) ){
			mxv_i175 = S;
			goto L175;
		}
	{  /* LetExpr */
		{  /* FormulaCaseList */
			if( mxs_is(_m,1044,S,_OrValue) ){
				mxv_i176 = S;
				goto L176;
			}
			mxv_i176 = mxs_appback(_m,1044,mxs_OrValue(_m,1044),S);
			L176: ;
		}
		S1_l29 = mxv_i176;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_subterm(_m,1045,mxs_itoe(_c,0,-1),S1_l29),T) ){
				mxv_i177 = S;
				goto L177;
			}
		{  /* FormulaCaseList */
			if( mxs_is(_m,1047,T,_OrValue) ){
				mxv_i178 = mxs_conc(_m,1047,S1_l29,T);
				goto L178;
			}
			mxv_i178 = mxs_appback(_m,1048,S1_l29,T);
			L178: ;
		}
			mxv_i177 = mxv_i178;
			L177: ;
		}
		mxv_l29 = mxv_i177;
	}
		mxv_i175 = mxv_l29;
		L175: ;
	}
	return mxv_i175;
}

ELEMENT  mxx_delete_id(char *f, int l,ELEMENT T){
ELEMENT mxv_i181, mxv_i180, mxv_i179;
 IFNIL(T)
 IS(T,_Value,f,l,"delete_id",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TW_identabb(_m,1051)) ){
			mxv_i180 = mxs_true(_m,0);
			goto L180;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TW_emptyset(_m,1051)) ){
			mxv_i181 = mxs_true(_m,0);
			goto L181;
		}
		mxv_i181 = mxs_false(_m,0);
		L181: ;
	}
		mxv_i180 = mxv_i181;
		L180: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i180) ){
			mxv_i179 = mxs_TW_emptyset(_m,1051);
			goto L179;
		}
		if( mxs_is(_m,1052,T,_OrValue) ){
			mxv_i179 = mxs_TW_or(_m,1052,mxs_delete_id(_m,1052,mxs_subterm(_m,1052,mxs_itoe(_c,0,1),T)),mxs_delete_id(_m,1052,mxs_back(_m,1052,T)));
			goto L179;
		}
		mxv_i179 = T;
		L179: ;
	}
	return mxv_i179;
}

ELEMENT  mxx_TW_closure(char *f, int l,ELEMENT T){
ELEMENT mxv_i182, mxv_l30, T1_l30;
 IFNIL(T)
 IS(T,_Value,f,l,"TW_closure",1)
	{  /* LetExpr */
		T1_l30 = mxs_delete_id(_m,1056,T);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T1_l30,mxs_TW_emptyset(_m,1057)) ){
				mxv_i182 = mxs_TW_identabb(_m,1057);
				goto L182;
			}
			if( mxs_is(_m,1058,T1_l30,_FClosure) ){
				mxv_i182 = T1_l30;
				goto L182;
			}
			mxv_i182 = mxs_FClosure(_m,1059,T1_l30);
			L182: ;
		}
		mxv_l30 = mxv_i182;
	}
	return mxv_l30;
}

ELEMENT  mxx_TW_conc(char *f, int l,ELEMENT S,ELEMENT T){
ELEMENT mxv_i185, mxv_i184, mxv_i186, mxv_i187, mxv_i188, mxv_l33, C_l33, mxv_l32, T1_l32, mxv_l31, S1_l31, mxv_i183;
 IFNIL(S) IFNIL(T)
 IS(S,_Value,f,l,"TW_conc",1) IS(T,_Value,f,l,"TW_conc",2)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,S,mxs_TW_emptyset(_m,1063)) ){
			mxv_i184 = mxs_true(_m,0);
			goto L184;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TW_emptyset(_m,1063)) ){
			mxv_i185 = mxs_true(_m,0);
			goto L185;
		}
		mxv_i185 = mxs_false(_m,0);
		L185: ;
	}
		mxv_i184 = mxv_i185;
		L184: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i184) ){
			mxv_i183 = mxs_TW_emptyset(_m,1063);
			goto L183;
		}
	{  /* LetExpr */
		{  /* FormulaCaseList */
			if( mxs_is(_m,1065,S,_FList) ){
				mxv_i186 = S;
				goto L186;
			}
			mxv_i186 = mxs_appfront(_m,1065,S,mxs_TW_identabb(_m,1065));
			L186: ;
		}
		S1_l31 = mxv_i186;
		{  /* LetExpr */
			{  /* FormulaCaseList */
				if( mxs_is(_m,1066,T,_FList) ){
					mxv_i187 = T;
					goto L187;
				}
				mxv_i187 = mxs_appfront(_m,1066,T,mxs_TW_identabb(_m,1066));
				L187: ;
			}
			T1_l32 = mxv_i187;
			{  /* LetExpr */
				C_l33 = mxs_conc(_m,1067,S1_l31,T1_l32);
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,mxs_numsubterms(_m,1068,C_l33),mxs_itoe(_c,0,1)) ){
						mxv_i188 = mxs_subterm(_m,1068,mxs_itoe(_c,0,1),C_l33);
						goto L188;
					}
					mxv_i188 = C_l33;
					L188: ;
				}
				mxv_l33 = mxv_i188;
			}
			mxv_l32 = mxv_l33;
		}
		mxv_l31 = mxv_l32;
	}
		mxv_i183 = mxv_l31;
		L183: ;
	}
	return mxv_i183;
}

ELEMENT  mxx_node_parnr_fct(char *f, int l,ELEMENT N){
ELEMENT mxv_i210;
 IFNIL(N)
 IS(N,_SortId_,f,l,"node_parnr_fct",1)
	{  /* FormulaCaseList */
		if( mxs_is_node(_m,1155,N) ){
			mxv_i210 = mxs_itoe(_c,0,1);
			goto L210;
		}
		if( mxs_is(_m,1156,mxs_rbroth(_m,1156,N),_SortId_) ){
			mxv_i210 = mxs_add(_m,1156,mxs_itoe(_c,0,1),mxs_node_parnr_fct(_m,1156,mxs_rbroth(_m,1156,N)));
			goto L210;
		}
		mxv_i210 = mxs_nil(_m,1157);
		L210: ;
	}
	return mxv_i210;
}

ELEMENT  mxx_encl_patcase(char *f, int l,ELEMENT N){
ELEMENT mxv_i217;
 IFNIL(N)
 IS(N,_Node,f,l,"encl_patcase",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp77;
			mxv_i217 = N;
			goto L217;
		}
		Lp77: ;
			mxv_i217 = mxs_encl_patcase(_m,1186,mxs_fath(_m,1186,N));
		L217: ;
	}
	return mxv_i217;
}

ELEMENT  mxx_pat_son_pos_nr(char *f, int l,ELEMENT N){
ELEMENT mxv_i218;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_son_pos_nr",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,1190,N),mxs_nil(_m,1190)) ){
			mxv_i218 = mxs_itoe(_c,0,1);
			goto L218;
		}
		if( mxs_is(_m,1191,mxs_lbroth(_m,1191,N),_Asterisk_) ){
			mxv_i218 = mxs_itoe(_c,0,0);
			goto L218;
		}
		mxv_i218 = mxs_add(_m,1192,mxs_pat_son_pos_nr(_m,1192,mxs_lbroth(_m,1192,N)),mxs_itoe(_c,0,1));
		L218: ;
	}
	return mxv_i218;
}

ELEMENT  mxx_pat_son_neg_nr(char *f, int l,ELEMENT N){
ELEMENT mxv_i219;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_son_neg_nr",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,1195,N),mxs_nil(_m,1195)) ){
			mxv_i219 = mxs_itoe(_c,0,-1);
			goto L219;
		}
		if( mxs_is(_m,1196,mxs_rbroth(_m,1196,N),_Asterisk_) ){
			mxv_i219 = mxs_itoe(_c,0,0);
			goto L219;
		}
		mxv_i219 = mxs_sub(_m,1197,mxs_pat_son_neg_nr(_m,1197,mxs_rbroth(_m,1197,N)),mxs_itoe(_c,0,1));
		L219: ;
	}
	return mxv_i219;
}

ELEMENT  mxx_pat_son_nr(char *f, int l,ELEMENT N){
ELEMENT mxv_i221, mxv_i220, mxv_l40, X_l40;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_son_nr",1)
	{  /* LetExpr */
		X_l40 = mxs_pat_son_pos_nr(_m,1200,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,X_l40,mxs_itoe(_c,0,1)) ){
				mxv_i220 = mxs_itoe(_c,0,1);
				goto L220;
			}
			if( mxs_eq(_m,0,X_l40,mxs_itoe(_c,0,0)) ){
				mxv_i220 = mxs_pat_son_neg_nr(_m,1202,N);
				goto L220;
			}
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_pat_son_neg_nr(_m,1203,N),mxs_itoe(_c,0,-1)) ){
				mxv_i221 = mxs_itoe(_c,0,-1);
				goto L221;
			}
			mxv_i221 = X_l40;
			L221: ;
		}
			mxv_i220 = mxv_i221;
			L220: ;
		}
		mxv_l40 = mxv_i220;
	}
	return mxv_l40;
}

ELEMENT  mxx_pat_way(char *f, int l,ELEMENT V,ELEMENT N){
ELEMENT mxv_i224, mxv_i225, mxv_i223, mxv_i222;
 IFNIL(V) IFNIL(N)
 IS(V,_Item_,f,l,"pat_way",1) IS(N,_Item_,f,l,"pat_way",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_fath(_m,1207,V),mxs_fath(_m,1207,N)) ){
		{  /* FormulaCaseList */
			if( mxs_bef(_m,1208,mxs_before(_m,1208,V),mxs_before(_m,1208,N)) ){
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = V;
					mxv_IR = mxv_anchor;
					if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp78;
					mxv_i224 = mxs_TW_conc(_m,1210,mxs_TW_closure(_m,1210,mxs_TWrbroth(_m,1210)),mxs_pat_way(_m,1210,mxs_rbroth(_m,1210,V),N));
					goto L224;
				}
				Lp78: ;
					mxv_i224 = mxs_TW_conc(_m,1211,mxs_pat_way(_m,1211,mxs_rbroth(_m,1211,V),N),mxs_TWrbroth(_m,1211));
				L224: ;
			}
				mxv_i223 = mxv_i224;
				goto L223;
			}
			if( mxs_aft(_m,1212,mxs_before(_m,1212,V),mxs_before(_m,1212,N)) ){
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = V;
					mxv_IR = mxv_anchor;
					if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp79;
					mxv_i225 = mxs_TW_conc(_m,1214,mxs_TW_closure(_m,1214,mxs_TWlbroth(_m,1214)),mxs_pat_way(_m,1214,mxs_lbroth(_m,1214,V),N));
					goto L225;
				}
				Lp79: ;
					mxv_i225 = mxs_TW_conc(_m,1215,mxs_pat_way(_m,1215,mxs_lbroth(_m,1215,V),N),mxs_TWlbroth(_m,1215));
				L225: ;
			}
				mxv_i223 = mxv_i225;
				goto L223;
			}
			mxv_i223 = mxs_TW_identabb(_m,1216);
			L223: ;
		}
			mxv_i222 = mxv_i223;
			goto L222;
		}
		if( mxs_desc(_m,1217,V,mxs_fath(_m,1217,mxs_fath(_m,1217,N))) ){
			mxv_i222 = mxs_TW_conc(_m,1217,mxs_TWfath(_m,1217),mxs_pat_way(_m,1217,mxs_fath(_m,1217,mxs_fath(_m,1217,V)),N));
			goto L222;
		}
		mxv_i222 = mxs_TW_conc(_m,1218,mxs_pat_way(_m,1218,V,mxs_fath(_m,1218,mxs_fath(_m,1218,N))),mxs_TWson(_m,1218,mxs_pat_son_nr(_m,1218,N)));
		L222: ;
	}
	return mxv_i222;
}

ELEMENT  mxx_enter_attrgroup(char *f, int l,ELEMENT J,ELEMENT ANL,ELEMENT M){
ELEMENT mxv_i231;
 IFNIL(J) IFNIL(ANL) IFNIL(M)
 IS(J,_Int,f,l,"enter_attrgroup",1) IS(ANL,_FuAtNodeList,f,l,"enter_attrgroup",2) IS(M,_Reference,f,l,"enter_attrgroup",3)
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1255,mxs_numsubterms(_m,1255,ANL),J) ){
			mxv_i231 = mxs_warshall_value(_m,1255,M,mxs_numsubterms(_m,1255,ANL));
			goto L231;
		}
		mxv_i231 = mxs_enter_attrgroup(_m,1257,mxs_add(_m,1257,J,mxs_itoe(_c,0,1)),ANL,mxs_enter_attribute(_m,1258,mxs_sub(_m,1258,J,mxs_itoe(_c,0,1)),mxs_subterm(_m,1258,J,ANL),M,mxs_numsubterms(_m,1258,ANL)));
		L231: ;
	}
	return mxv_i231;
}

ELEMENT  mxx_enter_attrgroup_list(char *f, int l,ELEMENT I,ELEMENT ALI,ELEMENT ALM){
ELEMENT mxv_i232;
 IFNIL(I) IFNIL(ALI) IFNIL(ALM)
 IS(I,_Int,f,l,"enter_attrgroup_list",1) IS(ALI,_FuAtListInfo,f,l,"enter_attrgroup_list",2) IS(ALM,_RefList,f,l,"enter_attrgroup_list",3)
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1262,mxs_numsubterms(_m,1262,ALI),I) ){
			mxv_i232 = ALM;
			goto L232;
		}
		mxv_i232 = mxs_enter_attrgroup_list(_m,1263,mxs_add(_m,1263,I,mxs_itoe(_c,0,1)),ALI,mxs_appback(_m,1264,ALM,mxs_enter_attrgroup(_m,1265,mxs_itoe(_c,0,1),mxs_subterm(_m,1265,I,ALI),mxs_init_matrix(_m,1266,mxs_numsubterms(_m,1266,mxs_subterm(_m,1266,I,ALI))))));
		L232: ;
	}
	return mxv_i232;
}

ELEMENT  mxx_simplify_closure(char *f, int l,ELEMENT T){
ELEMENT mxv_i235, mxv_i234, mxv_i237, mxv_i236, mxv_i241, mxv_i240, mxv_i245, mxv_i244, mxv_i248, mxv_i247, mxv_i246, mxv_i243, mxv_i242, mxv_i239, mxv_l45, X_l45, mxv_i238, mxv_l44, H_l44, mxv_l43, V_l43, mxv_i233;
 IFNIL(T)
 IS(T,_Value,f,l,"simplify_closure",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1291,T,_FList)) ){
			mxv_i234 = mxs_false(_m,0);
			goto L234;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_itoe(_c,0,1),mxs_numsubterms(_m,1291,T)) ){
			mxv_i235 = mxs_true(_m,0);
			goto L235;
		}
		mxv_i235 = mxs_false(_m,0);
		L235: ;
	}
		mxv_i234 = mxv_i235;
		L234: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i234) ){
			mxv_i233 = mxs_simplify_closure(_m,1291,mxs_subterm(_m,1291,mxs_itoe(_c,0,1),T));
			goto L233;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1292,T,_FList)) ){
			mxv_i236 = mxs_false(_m,0);
			goto L236;
		}
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1292,mxs_itoe(_c,0,1),mxs_numsubterms(_m,1292,T)) ){
			mxv_i237 = mxs_true(_m,0);
			goto L237;
		}
		mxv_i237 = mxs_false(_m,0);
		L237: ;
	}
		mxv_i236 = mxv_i237;
		L236: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i236) ){
		{  /* LetExpr */
			V_l43 = mxs_subterm(_m,1293,mxs_itoe(_c,0,1),T);
			{  /* LetExpr */
				H_l44 = mxs_subterm(_m,1294,mxs_itoe(_c,0,-1),T);
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1295,V_l43,_TWfath)) ){
						mxv_i240 = mxs_false(_m,0);
						goto L240;
					}
				{  /* FormulaCaseList */
					if( mxs_is(_m,1295,H_l44,_TWson) ){
						mxv_i241 = mxs_true(_m,0);
						goto L241;
					}
					mxv_i241 = mxs_false(_m,0);
					L241: ;
				}
					mxv_i240 = mxv_i241;
					L240: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i240) ){
						mxv_i239 = mxs_true(_m,0);
						goto L239;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1296,V_l43,_TWrbroth)) ){
						mxv_i244 = mxs_false(_m,0);
						goto L244;
					}
				{  /* FormulaCaseList */
					if( mxs_is(_m,1296,H_l44,_TWlbroth) ){
						mxv_i245 = mxs_true(_m,0);
						goto L245;
					}
					mxv_i245 = mxs_false(_m,0);
					L245: ;
				}
					mxv_i244 = mxv_i245;
					L244: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i244) ){
						mxv_i243 = mxs_true(_m,0);
						goto L243;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1297,V_l43,_TWlbroth)) ){
						mxv_i247 = mxs_false(_m,0);
						goto L247;
					}
				{  /* FormulaCaseList */
					if( mxs_is(_m,1297,H_l44,_TWrbroth) ){
						mxv_i248 = mxs_true(_m,0);
						goto L248;
					}
					mxv_i248 = mxs_false(_m,0);
					L248: ;
				}
					mxv_i247 = mxv_i248;
					L247: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i247) ){
						mxv_i246 = mxs_true(_m,0);
						goto L246;
					}
					mxv_i246 = mxs_false(_m,0);
					L246: ;
				}
					mxv_i243 = mxv_i246;
					L243: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i243) ){
						mxv_i242 = mxs_true(_m,0);
						goto L242;
					}
					mxv_i242 = mxs_false(_m,0);
					L242: ;
				}
					mxv_i239 = mxv_i242;
					L239: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i239) ){
					{  /* LetExpr */
						X_l45 = mxs_back(_m,1298,mxs_front(_m,1298,T));
						mxv_l45 = mxs_TW_or(_m,1299,mxs_TW_identabb(_m,1299),mxs_TW_conc(_m,1300,mxs_TW_conc(_m,1300,V_l43,X_l45),mxs_TW_conc(_m,1301,mxs_simplify_closure(_m,1301,X_l45),H_l44)));
					}
						mxv_i238 = mxv_l45;
						goto L238;
					}
					mxv_i238 = mxs_FClosure(_m,1303,T);
					L238: ;
				}
				mxv_l44 = mxv_i238;
			}
			mxv_l43 = mxv_l44;
		}
			mxv_i233 = mxv_l43;
			goto L233;
		}
		mxv_i233 = mxs_FClosure(_m,1304,T);
		L233: ;
	}
	return mxv_i233;
}

ELEMENT  mxx_normal_tw(char *f, int l,ELEMENT R,ELEMENT S,ELEMENT T){
ELEMENT mxv_i280, mxv_i283, mxv_i284, mxv_i282, mxv_l46, RN_l46, mxv_i281, mxv_i285, mxv_i286, mxv_i279;
 IFNIL(R) IFNIL(S) IFNIL(T)
 IS(R,_FList,f,l,"normal_tw",1) IS(S,_Value,f,l,"normal_tw",2) IS(T,_FValue,f,l,"normal_tw",3)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1316,S,_TWfath) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWson(_m,1317,mxs_itoe(_c,0,1))) ){
				mxv_i280 = mxs_appback(_m,1317,R,mxs_FClosure(_m,1317,mxs_TWlbroth(_m,1317)));
				goto L280;
			}
			mxv_i280 = mxs_appback(_m,1318,R,mxs_FClosure(_m,1318,mxs_TWrbroth(_m,1318)));
			L280: ;
		}
			mxv_i279 = mxv_i280;
			goto L279;
		}
		if( mxs_is(_m,1320,S,_TWson) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWfath(_m,1321)) ){
				mxv_i281 = mxs_FList(_m,1321);
				goto L281;
			}
		{  /* LetExpr */
			RN_l46 = mxs_subterm(_m,1323,mxs_itoe(_c,0,1),S);
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,T,mxs_TWrbroth(_m,1324)) ){
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,0)) ){
						mxv_i283 = mxs_appback(_m,1325,R,S);
						goto L283;
					}
					if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,-1)) ){
						mxv_i283 = mxs_TW_emptyset(_m,1326);
						goto L283;
					}
					mxv_i283 = mxs_appback(_m,1327,R,mxs_TWson(_m,1327,mxs_add(_m,1327,RN_l46,mxs_itoe(_c,0,1))));
					L283: ;
				}
					mxv_i282 = mxv_i283;
					goto L282;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,0)) ){
					mxv_i284 = mxs_appback(_m,1329,R,S);
					goto L284;
				}
				if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,1)) ){
					mxv_i284 = mxs_TW_emptyset(_m,1330);
					goto L284;
				}
				mxv_i284 = mxs_appback(_m,1331,R,mxs_TWson(_m,1331,mxs_sub(_m,1331,RN_l46,mxs_itoe(_c,0,1))));
				L284: ;
			}
				mxv_i282 = mxv_i284;
				L282: ;
			}
			mxv_l46 = mxv_i282;
		}
			mxv_i281 = mxv_l46;
			L281: ;
		}
			mxv_i279 = mxv_i281;
			goto L279;
		}
		if( mxs_is(_m,1333,S,_TWlbroth) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWrbroth(_m,1334)) ){
				mxv_i285 = R;
				goto L285;
			}
			mxv_i285 = mxs_appback(_m,1335,R,mxs_TWfath(_m,1335));
			L285: ;
		}
			mxv_i279 = mxv_i285;
			goto L279;
		}
		if( mxs_is(_m,1337,S,_TWrbroth) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWlbroth(_m,1338)) ){
				mxv_i286 = R;
				goto L286;
			}
			mxv_i286 = mxs_appback(_m,1339,R,mxs_TWfath(_m,1339));
			L286: ;
		}
			mxv_i279 = mxv_i286;
			goto L279;
		}
		if( mxs_is(_m,1341,S,_FClosure) ){
			mxv_i279 = mxs_appback(_m,1342,R,mxs_TWfath(_m,1342));
			goto L279;
		}
		mxv_i279 = mxs_nil(_m,1344);
		L279: ;
	}
	return mxv_i279;
}

ELEMENT  mxx_normal_closure(char *f, int l,ELEMENT R,ELEMENT T){
ELEMENT mxv_i288, mxv_i287;
 IFNIL(R) IFNIL(T)
 IS(R,_FList,f,l,"normal_closure",1) IS(T,_FClosure,f,l,"normal_closure",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,R,mxs_FList(_m,1348)) ){
			mxv_i287 = T;
			goto L287;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_subterm(_m,1350,mxs_itoe(_c,0,-1),R),mxs_subterm(_m,1350,mxs_itoe(_c,0,1),T)) ){
			mxv_i288 = mxs_TW_conc(_m,1350,mxs_normal_closure(_m,1350,mxs_front(_m,1350,R),T),mxs_subterm(_m,1350,mxs_itoe(_c,0,1),T));
			goto L288;
		}
		mxv_i288 = mxs_appback(_m,1351,R,T);
		L288: ;
	}
		mxv_i287 = mxv_i288;
		L287: ;
	}
	return mxv_i287;
}

ELEMENT  mxx_normalform(char *f, int l,ELEMENT R,ELEMENT T,ELEMENT N){
ELEMENT mxv_i294, mxv_i293, mxv_i295, mxv_i292, mxv_i291, mxv_l47, Z_l47, mxv_i290, mxv_i296, mxv_i300, mxv_i299, mxv_i301, mxv_i298, mxv_l48, N1_l48, mxv_i297, mxv_i302, mxv_l49, V_l49, mxv_i289;
 IFNIL(R) IFNIL(T) IFNIL(N)
 IS(R,_FList,f,l,"normalform",1) IS(T,_Value,f,l,"normalform",2) IS(N,_FuAtList_,f,l,"normalform",3)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1355,T,_DefId_) ){
			mxv_i289 = mxs_normalform(_m,1356,R,mxs_result_value(_m,1356,mxs_fath(_m,1356,T)),mxs_fath(_m,1356,mxs_fath(_m,1356,T)));
			goto L289;
		}
		if( mxs_is(_m,1358,T,_RelevAcc) ){
			mxv_i289 = mxs_normalform(_m,1359,R,mxs_result_value(_m,1359,mxs_son(_m,1359,mxs_subterm(_m,1359,mxs_itoe(_c,0,1),T),N)),N);
			goto L289;
		}
		if( mxs_is(_m,1361,T,_FValue) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,R,mxs_FList(_m,1362)) ){
				mxv_i290 = T;
				goto L290;
			}
		{  /* LetExpr */
			Z_l47 = mxs_subterm(_m,1364,mxs_itoe(_c,0,-1),R);
			{  /* FormulaCaseList */
				if( mxs_simplification(_m,1365,Z_l47,T) ){
					mxv_i291 = mxs_normal_tw(_m,1365,mxs_front(_m,1365,R),Z_l47,T);
					goto L291;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_lt(_m,1367,mxs_itoe(_c,0,1),mxs_numsubterms(_m,1367,R))) ){
					mxv_i293 = mxs_false(_m,0);
					goto L293;
				}
			{  /* FormulaCaseList */
				if( mxs_is(_m,1367,Z_l47,_FClosure) ){
					mxv_i294 = mxs_true(_m,0);
					goto L294;
				}
				mxv_i294 = mxs_false(_m,0);
				L294: ;
			}
				mxv_i293 = mxv_i294;
				L293: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i293) ){
				{  /* FormulaCaseList */
					if( mxs_simplification(_m,1368,mxs_subterm(_m,1368,mxs_itoe(_c,0,-2),R),T) ){
						mxv_i295 = mxs_TW_or(_m,1369,mxs_normal_tw(_m,1369,mxs_front(_m,1369,mxs_front(_m,1369,R)),mxs_subterm(_m,1369,mxs_itoe(_c,0,-2),R),T),mxs_normalform(_m,1370,mxs_appback(_m,1370,mxs_front(_m,1370,R),mxs_subterm(_m,1370,mxs_itoe(_c,0,1),Z_l47)),mxs_TW_conc(_m,1370,Z_l47,T),N));
						goto L295;
					}
					mxv_i295 = mxs_appback(_m,1372,R,T);
					L295: ;
				}
					mxv_i292 = mxv_i295;
					goto L292;
				}
				mxv_i292 = mxs_appback(_m,1373,R,T);
				L292: ;
			}
				mxv_i291 = mxv_i292;
				L291: ;
			}
			mxv_l47 = mxv_i291;
		}
			mxv_i290 = mxv_l47;
			L290: ;
		}
			mxv_i289 = mxv_i290;
			goto L289;
		}
		if( mxs_is(_m,1375,T,_OrValue) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1376,T),mxs_itoe(_c,0,0)) ){
				mxv_i296 = mxs_TW_emptyset(_m,1376);
				goto L296;
			}
			mxv_i296 = mxs_TW_or(_m,1377,mxs_normalform(_m,1377,R,mxs_subterm(_m,1377,mxs_itoe(_c,0,1),T),N),mxs_normalform(_m,1377,R,mxs_back(_m,1377,T),N));
			L296: ;
		}
			mxv_i289 = mxv_i296;
			goto L289;
		}
		if( mxs_is(_m,1379,T,_FList) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1380,T),mxs_itoe(_c,0,0)) ){
				mxv_i297 = R;
				goto L297;
			}
		{  /* LetExpr */
			N1_l48 = mxs_normalform(_m,1382,R,mxs_subterm(_m,1382,mxs_itoe(_c,0,1),T),N);
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,N1_l48,mxs_TW_emptyset(_m,1383)) ){
					mxv_i299 = mxs_true(_m,0);
					goto L299;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,N1_l48,mxs_nil(_m,1383)) ){
					mxv_i300 = mxs_true(_m,0);
					goto L300;
				}
				mxv_i300 = mxs_false(_m,0);
				L300: ;
			}
				mxv_i299 = mxv_i300;
				L299: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i299) ){
					mxv_i298 = N1_l48;
					goto L298;
				}
			{  /* FormulaCaseList */
				if( mxs_is(_m,1384,N1_l48,_FList) ){
					mxv_i301 = N1_l48;
					goto L301;
				}
				mxv_i301 = mxs_appback(_m,1385,mxs_FList(_m,1385),N1_l48);
				L301: ;
			}
				mxv_i298 = mxs_normalform(_m,1384,mxv_i301,mxs_back(_m,1385,T),N);
				L298: ;
			}
			mxv_l48 = mxv_i298;
		}
			mxv_i297 = mxv_l48;
			L297: ;
		}
			mxv_i289 = mxv_i297;
			goto L289;
		}
		if( mxs_is(_m,1387,T,_FClosure) ){
		{  /* LetExpr */
			V_l49 = mxs_simplify_closure(_m,1388,mxs_normalform(_m,1388,mxs_FList(_m,1388),mxs_subterm(_m,1388,mxs_itoe(_c,0,1),T),N));
			{  /* FormulaCaseList */
				if( mxs_is(_m,1389,V_l49,_FClosure) ){
					mxv_i302 = mxs_normal_closure(_m,1389,R,V_l49);
					goto L302;
				}
				mxv_i302 = mxs_normalform(_m,1390,R,V_l49,N);
				L302: ;
			}
			mxv_l49 = mxv_i302;
		}
			mxv_i289 = mxv_l49;
			goto L289;
		}
		mxv_i289 = mxs_nil(_m,1392);
		L289: ;
	}
	return mxv_i289;
}

ELEMENT  mxx_Ord_fath(char *f, int l){
	return mxs_itoe(_c,0,35);
}

ELEMENT  mxx_Ord_son(char *f, int l){
	return mxs_itoe(_c,0,50);
}

ELEMENT  mxx_Ord_rbroth(char *f, int l){
	return mxs_itoe(_c,0,16);
}

ELEMENT  mxx_Ord_lbroth(char *f, int l){
	return mxs_itoe(_c,0,1);
}

ELEMENT  mxx_Ord_ident(char *f, int l){
	return mxs_itoe(_c,0,204);
}

ELEMENT  mxx_Ord_neutral(char *f, int l){
	return mxs_itoe(_c,0,17);
}

ELEMENT  mxx_Ord_nothing(char *f, int l){
	return mxs_itoe(_c,0,136);
}

ELEMENT  mxx_val_order(char *f, int l,ELEMENT T){
ELEMENT mxv_i304, mxv_i305, mxv_i303;
 IFNIL(T)
 IS(T,_Value,f,l,"val_order",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1416,T,_TWson) ){
			mxv_i303 = mxs_Ord_son(_m,1416);
			goto L303;
		}
		if( mxs_is(_m,1417,T,_TWfath) ){
			mxv_i303 = mxs_Ord_fath(_m,1417);
			goto L303;
		}
		if( mxs_is(_m,1418,T,_TWrbroth) ){
			mxv_i303 = mxs_Ord_rbroth(_m,1418);
			goto L303;
		}
		if( mxs_is(_m,1419,T,_TWlbroth) ){
			mxv_i303 = mxs_Ord_lbroth(_m,1419);
			goto L303;
		}
		if( mxs_is(_m,1420,T,_FClosure) ){
			mxv_i303 = mxs_OrdOp_closure(_m,1420,mxs_val_order(_m,1420,mxs_subterm(_m,1420,mxs_itoe(_c,0,1),T)));
			goto L303;
		}
		if( mxs_is(_m,1421,T,_FList) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1422,T),mxs_itoe(_c,0,0)) ){
				mxv_i304 = mxs_Ord_ident(_m,1422);
				goto L304;
			}
			mxv_i304 = mxs_OrdOp_conc(_m,1423,mxs_val_order(_m,1423,mxs_subterm(_m,1423,mxs_itoe(_c,0,1),T)),mxs_val_order(_m,1423,mxs_back(_m,1423,T)));
			L304: ;
		}
			mxv_i303 = mxv_i304;
			goto L303;
		}
		if( mxs_is(_m,1424,T,_OrValue) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1425,T),mxs_itoe(_c,0,0)) ){
				mxv_i305 = mxs_Ord_neutral(_m,1425);
				goto L305;
			}
			mxv_i305 = mxs_OrdOp_or(_m,1426,mxs_val_order(_m,1426,mxs_subterm(_m,1426,mxs_itoe(_c,0,1),T)),mxs_val_order(_m,1426,mxs_back(_m,1426,T)));
			L305: ;
		}
			mxv_i303 = mxv_i305;
			goto L303;
		}
		mxv_i303 = mxs_Ord_nothing(_m,1428);
		L303: ;
	}
	return mxv_i303;
}

ELEMENT  mxx_contains_attr(char *f, int l,ELEMENT FAL){
ELEMENT mxv_i306;
 IFNIL(FAL)
 IS(FAL,_FuAtNodeList,f,l,"contains_attr",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,FAL,mxs_FuAtNodeList(_m,1439)) ){
			mxv_i306 = mxs_false(_m,1439);
			goto L306;
		}
		if( mxs_is(_m,1440,mxs_subterm(_m,1440,mxs_itoe(_c,0,1),FAL),_Attribute_) ){
			mxv_i306 = mxs_true(_m,1440);
			goto L306;
		}
		mxv_i306 = mxs_contains_attr(_m,1441,mxs_back(_m,1441,FAL));
		L306: ;
	}
	return mxv_i306;
}

ELEMENT  mxx_encl_fctoratt(char *f, int l,ELEMENT N){
ELEMENT mxv_i307;
 IFNIL(N)
 IS(N,_Node,f,l,"encl_fctoratt",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp87;
			mxv_i307 = N;
			goto L307;
		}
		Lp87: ;
			mxv_i307 = mxs_encl_fctoratt(_m,1445,mxs_fath(_m,1445,N));
		L307: ;
	}
	return mxv_i307;
}

ELEMENT  mxx_filter_relev_acc(char *f, int l,ELEMENT AL){
ELEMENT mxv_i318, mxv_i317;
 IFNIL(AL)
 IS(AL,_ApplList,f,l,"filter_relev_acc",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,AL,mxs_ApplList(_m,1463)) ){
			mxv_i317 = mxs_ApplList(_m,1463);
			goto L317;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_appl_order(_m,1464,mxs_subterm(_m,1464,mxs_itoe(_c,0,1),AL)),mxs_Ord_neutral(_m,1464)) ){
			mxv_i318 = mxs_filter_relev_acc(_m,1464,mxs_back(_m,1464,AL));
			goto L318;
		}
		mxv_i318 = mxs_appfront(_m,1465,mxs_subterm(_m,1465,mxs_itoe(_c,0,1),AL),mxs_filter_relev_acc(_m,1465,mxs_back(_m,1465,AL)));
		L318: ;
	}
		mxv_i317 = mxv_i318;
		L317: ;
	}
	return mxv_i317;
}

ELEMENT  mxx_list_intresexprs(char *f, int l,ELEMENT N){
ELEMENT mxv_i348;
 IFNIL(N)
 IS(N,_Node,f,l,"list_intresexprs",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,1537,N),mxs_nil(_m,1537)) ){
			mxv_i348 = mxs_intresexprs(_m,1537,N);
			goto L348;
		}
		mxv_i348 = mxs_conc(_m,1538,mxs_intresexprs(_m,1538,N),mxs_list_intresexprs(_m,1538,mxs_rbroth(_m,1538,N)));
		L348: ;
	}
	return mxv_i348;
}

ELEMENT  mxx_intresexprs(char *f, int l,ELEMENT N){
ELEMENT mxv_i349;
 IFNIL(N)
 IS(N,_Node,f,l,"intresexprs",1)
	{  /* FormulaCaseList */
		if( mxs_is_intres(_m,1542,N) ){
			mxv_i349 = mxs_appback(_m,1542,mxs_IntResList(_m,1542),N);
			goto L349;
		}
		if( mxs_eq(_m,0,mxs_numsons(_m,1543,N),mxs_itoe(_c,0,0)) ){
			mxv_i349 = mxs_IntResList(_m,1543);
			goto L349;
		}
		mxv_i349 = mxs_list_intresexprs(_m,1544,mxs_son(_m,1544,mxs_itoe(_c,0,1),N));
		L349: ;
	}
	return mxv_i349;
}

ELEMENT  mxx_encl_part_intres(char *f, int l,ELEMENT N){
ELEMENT mxv_i352, mxv_i351, A_p333, C_p335, C_p337, L_p339, L_p341, I_p343, F_p345, F_p347, P_p349, F_p351;
 IFNIL(N)
 IS(N,_Node,f,l,"encl_part_intres",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp94;
			A_p333 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = A_p333;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp94;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp94;
			if( !mxs_is(_c,0,mxv_IR,_ApplyEntity_) ) goto Lp94;
			mxv_i351 = N;
			goto L351;
		}
		Lp94: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp95;
			C_p335 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = C_p335;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp95;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp95;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp95;
			mxv_i351 = N;
			goto L351;
		}
		Lp95: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp96;
			C_p337 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = C_p337;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp96;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp96;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp96;
			mxv_i351 = N;
			goto L351;
		}
		Lp96: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp97;
			L_p339 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = L_p339;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp97;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp97;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp97;
			mxv_i351 = N;
			goto L351;
		}
		Lp97: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp98;
			L_p341 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = L_p341;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp98;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp98;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp98;
			mxv_i351 = N;
			goto L351;
		}
		Lp98: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp99;
			I_p343 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = I_p343;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp99;
			if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp99;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp99;
			mxv_i351 = N;
			goto L351;
		}
		Lp99: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp100;
			F_p345 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = F_p345;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp100;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp100;
			if( !mxs_is(_c,0,mxv_IR,_FormulaCase_) ) goto Lp100;
			mxv_i351 = N;
			goto L351;
		}
		Lp100: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp101;
			F_p347 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = F_p347;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp101;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp101;
			if( !mxs_is(_c,0,mxv_IR,_FormulaCase_) ) goto Lp101;
			mxv_i351 = N;
			goto L351;
		}
		Lp101: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp102;
			P_p349 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = P_p349;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp102;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp102;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp102;
			mxv_i351 = N;
			goto L351;
		}
		Lp102: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp103;
			F_p351 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = F_p351;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp103;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp103;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp103;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_maybe_wait(_m,1571,F_p351),mxs_true(_m,1571)) ){
				mxv_i352 = N;
				goto L352;
			}
			mxv_i352 = mxs_encl_part_intres(_m,1571,F_p351);
			L352: ;
		}
			mxv_i351 = mxv_i352;
			goto L351;
		}
		Lp103: ;
			mxv_i351 = mxs_encl_part_intres(_m,1572,mxs_fath(_m,1572,N));
		L351: ;
	}
	return mxv_i351;
}

ELEMENT  mxx_aux_var_need(char *f, int l,ELEMENT I,ELEMENT V){
ELEMENT mxv_i357, mxv_i356, mxv_i355, mxv_i354, mxv_l55, N_l55, mxv_i353;
 IFNIL(I) IFNIL(V)
 IS(I,_Int,f,l,"aux_var_need",1) IS(V,_FctOrAtt_,f,l,"aux_var_need",2)
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1579,mxs_number(_m,1579,_Name_),I) ){
			mxv_i353 = mxs_IntResList(_m,1579);
			goto L353;
		}
	{  /* LetExpr */
		N_l55 = mxs_element(_m,1581,I,_Name_);
		{  /* FormulaCaseList */
			if( mxs_desc(_m,1582,N_l55,V) ){
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! ( ! mxs_eq(_m,0,mxs_bind_pos(_m,1583,N_l55),N_l55))) ){
					mxv_i356 = mxs_false(_m,0);
					goto L356;
				}
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,1583,mxs_fath(_m,1583,mxs_bind_pos(_m,1583,N_l55)),_NameList_)) ){
					mxv_i357 = mxs_true(_m,0);
					goto L357;
				}
				mxv_i357 = mxs_false(_m,0);
				L357: ;
			}
				mxv_i356 = mxv_i357;
				L356: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i356) ){
					mxv_i355 = mxs_appfront(_m,1584,N_l55,mxs_aux_var_need(_m,1584,mxs_add(_m,1584,I,mxs_itoe(_c,0,1)),V));
					goto L355;
				}
				mxv_i355 = mxs_aux_var_need(_m,1585,mxs_add(_m,1585,I,mxs_itoe(_c,0,1)),V);
				L355: ;
			}
				mxv_i354 = mxv_i355;
				goto L354;
			}
			mxv_i354 = mxs_IntResList(_m,1586);
			L354: ;
		}
		mxv_l55 = mxv_i354;
	}
		mxv_i353 = mxv_l55;
		L353: ;
	}
	return mxv_i353;
}

ELEMENT  mxx_aux_intres_left(char *f, int l,ELEMENT N,ELEMENT I,ELEMENT Z){
ELEMENT mxv_i358;
 IFNIL(N) IFNIL(I) IFNIL(Z)
 IS(N,_IntResExpr_,f,l,"aux_intres_left",1) IS(I,_Int,f,l,"aux_intres_left",2) IS(Z,_IntResList,f,l,"aux_intres_left",3)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_subterm(_m,1590,I,Z),N) ){
			mxv_i358 = mxs_IntResList(_m,1590);
			goto L358;
		}
		mxv_i358 = mxs_appfront(_m,1591,mxs_subterm(_m,1591,I,Z),mxs_aux_intres_left(_m,1591,N,mxs_add(_m,1591,I,mxs_itoe(_c,0,1)),Z));
		L358: ;
	}
	return mxv_i358;
}

ELEMENT  mxx_aux_intres_right(char *f, int l,ELEMENT LCP,ELEMENT PL,ELEMENT PR,ELEMENT L,ELEMENT I){
ELEMENT mxv_i364, mxv_i363, mxv_i362, mxv_i361, mxv_i360, mxv_l56, N_l56, mxv_i359;
 IFNIL(LCP) IFNIL(PL) IFNIL(PR) IFNIL(L) IFNIL(I)
 IS(LCP,_Point,f,l,"aux_intres_right",1) IS(PL,_Point,f,l,"aux_intres_right",2) IS(PR,_Point,f,l,"aux_intres_right",3) IS(L,_IntResList,f,l,"aux_intres_right",4) IS(I,_Int,f,l,"aux_intres_right",5)
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1595,mxs_numsubterms(_m,1595,L),I) ){
			mxv_i359 = mxs_IntResList(_m,1595);
			goto L359;
		}
	{  /* LetExpr */
		N_l56 = mxs_subterm(_m,1597,I,L);
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! mxs_bef(_m,1598,PL,mxs_after(_m,1598,N_l56))) ){
				mxv_i361 = mxs_false(_m,0);
				goto L361;
			}
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! mxs_bef(_m,1598,mxs_after(_m,1598,N_l56),PR)) ){
				mxv_i363 = mxs_false(_m,0);
				goto L363;
			}
		{  /* FormulaCaseList */
			if( mxs_bef(_m,1598,mxs_after(_m,1598,mxs_bind_pos(_m,1598,N_l56)),LCP) ){
				mxv_i364 = mxs_true(_m,0);
				goto L364;
			}
			mxv_i364 = mxs_false(_m,0);
			L364: ;
		}
			mxv_i363 = mxv_i364;
			L363: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i363) ){
				mxv_i362 = mxs_true(_m,0);
				goto L362;
			}
			mxv_i362 = mxs_false(_m,0);
			L362: ;
		}
			mxv_i361 = mxv_i362;
			L361: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i361) ){
				mxv_i360 = mxs_appfront(_m,1599,N_l56,mxs_aux_intres_right(_m,1599,LCP,PL,PR,L,mxs_add(_m,1599,I,mxs_itoe(_c,0,1))));
				goto L360;
			}
			mxv_i360 = mxs_aux_intres_right(_m,1600,LCP,PL,PR,L,mxs_add(_m,1600,I,mxs_itoe(_c,0,1)));
			L360: ;
		}
		mxv_l56 = mxv_i360;
	}
		mxv_i359 = mxv_l56;
		L359: ;
	}
	return mxv_i359;
}



long  mxs_in(char *f, int l,ELEMENT N,ELEMENT lb,ELEMENT ub){
ELEMENT mxv_i6, mxv_i5, mxv_i9, mxv_i8, mxv_i7, mxv_i4;
 ISORNIL(N,_Node,f,l,"in",1) ISORNIL(lb,_Point,f,l,"in",2) ISORNIL(ub,_Point,f,l,"in",3)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_bef(_m,326,lb,mxs_before(_m,326,N)) ){
			mxv_i5 = mxs_true(_m,0);
			goto L5;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,lb,mxs_before(_m,326,N)) ){
			mxv_i6 = mxs_true(_m,0);
			goto L6;
		}
		mxv_i6 = mxs_false(_m,0);
		L6: ;
	}
		mxv_i5 = mxv_i6;
		L5: ;
	}
		if( ( ! mxs_eq(_m,0,mxs_true(_m,0),mxv_i5)) ){
			mxv_i4 = mxs_false(_m,0);
			goto L4;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_bef(_m,327,mxs_after(_m,327,N),ub) ){
			mxv_i8 = mxs_true(_m,0);
			goto L8;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,ub,mxs_after(_m,327,N)) ){
			mxv_i9 = mxs_true(_m,0);
			goto L9;
		}
		mxv_i9 = mxs_false(_m,0);
		L9: ;
	}
		mxv_i8 = mxv_i9;
		L8: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i8) ){
			mxv_i7 = mxs_true(_m,0);
			goto L7;
		}
		mxv_i7 = mxs_false(_m,0);
		L7: ;
	}
		mxv_i4 = mxv_i7;
		L4: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i4);
}

long  mxs_is_enumerable(char *f, int l,ELEMENT N){
ELEMENT mxv_i38, mxv_i37, mxv_i36, mxv_i35, mxv_i34, mxv_i33;
 ISORNIL(N,_SortId_,f,l,"is_enumerable",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,439,N,_NodeSortId_) ){
			mxv_i33 = mxs_true(_m,0);
			goto L33;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,440,mxs_son(_m,440,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Node")) ){
			mxv_i35 = mxs_true(_m,0);
			goto L35;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,440,mxs_son(_m,440,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Point")) ){
			mxv_i37 = mxs_true(_m,0);
			goto L37;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,440,mxs_son(_m,440,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Ident")) ){
			mxv_i38 = mxs_true(_m,0);
			goto L38;
		}
		mxv_i38 = mxs_false(_m,0);
		L38: ;
	}
		mxv_i37 = mxv_i38;
		L37: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i37) ){
			mxv_i36 = mxs_true(_m,0);
			goto L36;
		}
		mxv_i36 = mxs_false(_m,0);
		L36: ;
	}
		mxv_i35 = mxv_i36;
		L35: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i35) ){
			mxv_i34 = mxs_true(_m,0);
			goto L34;
		}
		mxv_i34 = mxs_false(_m,0);
		L34: ;
	}
		mxv_i33 = mxv_i34;
		L33: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i33);
}

long  mxs_ex_pattern_inbetween(char *f, int l,ELEMENT IT1,ELEMENT IT2){
ELEMENT mxv_i74, mxv_i73, mxv_i72, mxv_i71, mxv_i70, mxv_i69;
 ISORNIL(IT1,_Item_,f,l,"ex_pattern_inbetween",1) ISORNIL(IT2,_Item_,f,l,"ex_pattern_inbetween",2)
	{  /* FormulaCaseList */
		if( mxs_is(_m,548,IT1,_Pattern_) ){
			mxv_i69 = mxs_true(_m,0);
			goto L69;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,IT1,IT2))) ){
			mxv_i71 = mxs_false(_m,0);
			goto L71;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,549,IT1,_Blank_)) ){
			mxv_i73 = mxs_false(_m,0);
			goto L73;
		}
	{  /* FormulaCaseList */
		if( mxs_ex_pattern_inbetween(_m,549,mxs_rbroth(_m,549,IT1),IT2) ){
			mxv_i74 = mxs_true(_m,0);
			goto L74;
		}
		mxv_i74 = mxs_false(_m,0);
		L74: ;
	}
		mxv_i73 = mxv_i74;
		L73: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i73) ){
			mxv_i72 = mxs_true(_m,0);
			goto L72;
		}
		mxv_i72 = mxs_false(_m,0);
		L72: ;
	}
		mxv_i71 = mxv_i72;
		L71: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i71) ){
			mxv_i70 = mxs_true(_m,0);
			goto L70;
		}
		mxv_i70 = mxs_false(_m,0);
		L70: ;
	}
		mxv_i69 = mxv_i70;
		L69: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i69);
}

long  mxs_is_node(char *f, int l,ELEMENT N){
ELEMENT mxv_i207, mxv_i206;
 ISORNIL(N,_SortId_,f,l,"is_node",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1139,N,_NodeSortId_) ){
			mxv_i206 = mxs_true(_m,0);
			goto L206;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,1139,mxs_son(_m,1139,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Node")) ){
			mxv_i207 = mxs_true(_m,0);
			goto L207;
		}
		mxv_i207 = mxs_false(_m,0);
		L207: ;
	}
		mxv_i206 = mxv_i207;
		L206: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i206);
}

long  mxs_simplification(char *f, int l,ELEMENT S,ELEMENT T){
ELEMENT mxv_i255, mxv_i254, mxv_i253, mxv_i252, mxv_i251, mxv_i250, mxv_i261, mxv_i260, mxv_i259, mxv_i258, mxv_i267, mxv_i266, mxv_i265, mxv_i264, mxv_i273, mxv_i272, mxv_i271, mxv_i270, mxv_i277, mxv_i276, mxv_i278, mxv_i275, mxv_i274, mxv_i269, mxv_i268, mxv_i263, mxv_i262, mxv_i257, mxv_i256, mxv_i249;
 ISORNIL(S,_Value,f,l,"simplification",1) ISORNIL(T,_FValue,f,l,"simplification",2)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1308,S,_TWson)) ){
			mxv_i250 = mxs_false(_m,0);
			goto L250;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWfath(_m,1308)) ){
			mxv_i252 = mxs_true(_m,0);
			goto L252;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWrbroth(_m,1308)) ){
			mxv_i254 = mxs_true(_m,0);
			goto L254;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWlbroth(_m,1308)) ){
			mxv_i255 = mxs_true(_m,0);
			goto L255;
		}
		mxv_i255 = mxs_false(_m,0);
		L255: ;
	}
		mxv_i254 = mxv_i255;
		L254: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i254) ){
			mxv_i253 = mxs_true(_m,0);
			goto L253;
		}
		mxv_i253 = mxs_false(_m,0);
		L253: ;
	}
		mxv_i252 = mxv_i253;
		L252: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i252) ){
			mxv_i251 = mxs_true(_m,0);
			goto L251;
		}
		mxv_i251 = mxs_false(_m,0);
		L251: ;
	}
		mxv_i250 = mxv_i251;
		L250: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i250) ){
			mxv_i249 = mxs_true(_m,0);
			goto L249;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,S,mxs_TWfath(_m,1309))) ){
			mxv_i258 = mxs_false(_m,0);
			goto L258;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWson(_m,1309,mxs_itoe(_c,0,1))) ){
			mxv_i260 = mxs_true(_m,0);
			goto L260;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWson(_m,1309,mxs_itoe(_c,0,-1))) ){
			mxv_i261 = mxs_true(_m,0);
			goto L261;
		}
		mxv_i261 = mxs_false(_m,0);
		L261: ;
	}
		mxv_i260 = mxv_i261;
		L260: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i260) ){
			mxv_i259 = mxs_true(_m,0);
			goto L259;
		}
		mxv_i259 = mxs_false(_m,0);
		L259: ;
	}
		mxv_i258 = mxv_i259;
		L258: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i258) ){
			mxv_i257 = mxs_true(_m,0);
			goto L257;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,S,mxs_TWlbroth(_m,1310))) ){
			mxv_i264 = mxs_false(_m,0);
			goto L264;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWfath(_m,1310)) ){
			mxv_i266 = mxs_true(_m,0);
			goto L266;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWrbroth(_m,1310)) ){
			mxv_i267 = mxs_true(_m,0);
			goto L267;
		}
		mxv_i267 = mxs_false(_m,0);
		L267: ;
	}
		mxv_i266 = mxv_i267;
		L266: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i266) ){
			mxv_i265 = mxs_true(_m,0);
			goto L265;
		}
		mxv_i265 = mxs_false(_m,0);
		L265: ;
	}
		mxv_i264 = mxv_i265;
		L264: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i264) ){
			mxv_i263 = mxs_true(_m,0);
			goto L263;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,S,mxs_TWrbroth(_m,1311))) ){
			mxv_i270 = mxs_false(_m,0);
			goto L270;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWfath(_m,1311)) ){
			mxv_i272 = mxs_true(_m,0);
			goto L272;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWlbroth(_m,1311)) ){
			mxv_i273 = mxs_true(_m,0);
			goto L273;
		}
		mxv_i273 = mxs_false(_m,0);
		L273: ;
	}
		mxv_i272 = mxv_i273;
		L272: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i272) ){
			mxv_i271 = mxs_true(_m,0);
			goto L271;
		}
		mxv_i271 = mxs_false(_m,0);
		L271: ;
	}
		mxv_i270 = mxv_i271;
		L270: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i270) ){
			mxv_i269 = mxs_true(_m,0);
			goto L269;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,S,mxs_FClosure(_m,1312,mxs_TWlbroth(_m,1312))) ){
			mxv_i276 = mxs_true(_m,0);
			goto L276;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,S,mxs_FClosure(_m,1312,mxs_TWrbroth(_m,1312))) ){
			mxv_i277 = mxs_true(_m,0);
			goto L277;
		}
		mxv_i277 = mxs_false(_m,0);
		L277: ;
	}
		mxv_i276 = mxv_i277;
		L276: ;
	}
		if( ( ! mxs_eq(_m,0,mxs_true(_m,0),mxv_i276)) ){
			mxv_i275 = mxs_false(_m,0);
			goto L275;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWfath(_m,1312)) ){
			mxv_i278 = mxs_true(_m,0);
			goto L278;
		}
		mxv_i278 = mxs_false(_m,0);
		L278: ;
	}
		mxv_i275 = mxv_i278;
		L275: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i275) ){
			mxv_i274 = mxs_true(_m,0);
			goto L274;
		}
		mxv_i274 = mxs_false(_m,0);
		L274: ;
	}
		mxv_i269 = mxv_i274;
		L269: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i269) ){
			mxv_i268 = mxs_true(_m,0);
			goto L268;
		}
		mxv_i268 = mxs_false(_m,0);
		L268: ;
	}
		mxv_i263 = mxv_i268;
		L263: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i263) ){
			mxv_i262 = mxs_true(_m,0);
			goto L262;
		}
		mxv_i262 = mxs_false(_m,0);
		L262: ;
	}
		mxv_i257 = mxv_i262;
		L257: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i257) ){
			mxv_i256 = mxs_true(_m,0);
			goto L256;
		}
		mxv_i256 = mxs_false(_m,0);
		L256: ;
	}
		mxv_i249 = mxv_i256;
		L249: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i249);
}

long  mxs_is_intres(char *f, int l,ELEMENT N){
ELEMENT mxv_i338, mxv_i337, mxv_i342, mxv_i341, mxv_i347, mxv_i346, mxv_i345, mxv_i344, mxv_i343, mxv_i340, mxv_i339, mxv_i336;
 ISORNIL(N,_Node,f,l,"is_intres",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1532,N,_FuncAppl_)) ){
			mxv_i337 = mxs_false(_m,0);
			goto L337;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_maybe_wait(_m,1532,N),mxs_true(_m,1532)) ){
			mxv_i338 = mxs_true(_m,0);
			goto L338;
		}
		mxv_i338 = mxs_false(_m,0);
		L338: ;
	}
		mxv_i337 = mxv_i338;
		L337: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i337) ){
			mxv_i336 = mxs_true(_m,0);
			goto L336;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_is(_m,1533,N,_FuncAppl_))) ){
			mxv_i341 = mxs_false(_m,0);
			goto L341;
		}
	{  /* FormulaCaseList */
		if( mxs_is(_m,1533,N,_IntResExpr_) ){
			mxv_i342 = mxs_true(_m,0);
			goto L342;
		}
		mxv_i342 = mxs_false(_m,0);
		L342: ;
	}
		mxv_i341 = mxv_i342;
		L341: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i341) ){
			mxv_i340 = mxs_true(_m,0);
			goto L340;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1534,N,_Name_)) ){
			mxv_i344 = mxs_false(_m,0);
			goto L344;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,mxs_bind_pos(_m,1534,N),N))) ){
			mxv_i346 = mxs_false(_m,0);
			goto L346;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1534,mxs_fath(_m,1534,mxs_bind_pos(_m,1534,N)),_NameList_)) ){
			mxv_i347 = mxs_true(_m,0);
			goto L347;
		}
		mxv_i347 = mxs_false(_m,0);
		L347: ;
	}
		mxv_i346 = mxv_i347;
		L346: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i346) ){
			mxv_i345 = mxs_true(_m,0);
			goto L345;
		}
		mxv_i345 = mxs_false(_m,0);
		L345: ;
	}
		mxv_i344 = mxv_i345;
		L344: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i344) ){
			mxv_i343 = mxs_true(_m,0);
			goto L343;
		}
		mxv_i343 = mxs_false(_m,0);
		L343: ;
	}
		mxv_i340 = mxv_i343;
		L340: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i340) ){
			mxv_i339 = mxs_true(_m,0);
			goto L339;
		}
		mxv_i339 = mxs_false(_m,0);
		L339: ;
	}
		mxv_i336 = mxv_i339;
		L336: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i336);
}



static  void  mxe_term_basesorts( ELEMENT N, ELEMENT mxv_attvalue, int state, ELEMENT *mxv_waitpar ){
	ELEMENT  mxv_a72, mxv_i18, R_p27, mxv_i21, mxv_i20, mxv_a82, mxv_i22, I_p31, mxv_l2, D_l2, mxv_i19, mxv_l1, RL_l1,
		mxv_ax, mxv_res, mxv_par = N;
	AttInstSq mxv_waitsq, mxv_wsq;

	switch(state) {
		case 72 :
			mxv_a72 = mxv_attvalue;
			goto Lz72;
		case 82 :
			RL_l1 = mxv_waitpar[0];
			mxv_a82 = mxv_attvalue;
			goto Lz82;
	}
	{  /* LetExpr */
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR))) ) goto Lp4;
				if( mxs_before(_c,0,mxs_son(_c,0,-2,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp4;
				mxv_IR = mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor));
				if( mxv_IR == mxs_nil(_c,0) ) goto Lp4;
				if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp4;
				if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp4;
				mxv_IR = mxs_fath(_c,0,mxv_anchor);
				if( mxv_IR == mxs_nil(_c,0) ) goto Lp4;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp4;
				if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp4;
				R_p27 = mxs_rbroth(_c,0,mxv_anchor);
				mxv_IR = R_p27;
				if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR))) ) goto Lp4;
				if( mxs_before(_c,0,mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp4;
			{  /* Attribute access */
				mxv_ax = R_p27;
				mxv_a72 = mxs_term_basesorts(_m,362,mxv_ax);
				if( mxv_a72==MAXUNDEF ){
					insAttInst((EVALFCT)mxe_term_basesorts,mxv_par,72,mxw_term_basesorts,mxs_index(_c,0,mxv_ax,_SortId_));
					return;
				}
				Lz72:;
			}
				mxv_i18 = mxv_a72;
				goto L18;
			}
			Lp4: ;
				mxv_i18 = mxs_DefIdNodeList(_m,362);
			L18: ;
		}
		RL_l1 = mxv_i18;
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! mxs_is(_m,364,N,_TermSortId_)) ){
				mxv_i20 = mxs_false(_m,0);
				goto L20;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,mxs_id(_m,364,mxs_son(_m,364,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Node"))) ){
				mxv_i21 = mxs_true(_m,0);
				goto L21;
			}
			mxv_i21 = mxs_false(_m,0);
			L21: ;
		}
			mxv_i20 = mxv_i21;
			L20: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i20) ){
			{  /* LetExpr */
				D_l2 = mxs_decl(_m,365,N);
				{  /* PatternCaseList */
					{
						ELEMENT mxv_anchor, mxv_IR;
						mxv_anchor = D_l2;
						mxv_IR = mxv_anchor;
						if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp5;
						mxv_IR = mxs_fath(_c,0,mxv_anchor);
						if( mxv_IR == mxs_nil(_c,0) ) goto Lp5;
						if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp5;
						if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp5;
						mxv_IR = mxs_rbroth(_c,0,mxv_anchor);
						if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp5;
						if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp5;
						I_p31 = mxs_son(_c,0,1,mxs_rbroth(_c,0,mxv_anchor));
						mxv_IR = I_p31;
						if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp5;
					{  /* Attribute access */
						mxv_ax = I_p31;
						mxv_a82 = mxs_term_basesorts(_m,366,mxv_ax);
						if( mxv_a82==MAXUNDEF ){ ELEMENT *P;
							P = insAttInst((EVALFCT)mxe_term_basesorts,mxv_par,82,mxw_term_basesorts,mxs_index(_c,0,mxv_ax,_SortId_));
							P[0] = RL_l1;
							return;
						}
						Lz82:;
					}
						mxv_i22 = mxs_conc(_m,366,RL_l1,mxv_a82);
						goto L22;
					}
					Lp5: ;
						mxv_i22 = mxs_appback(_m,367,RL_l1,D_l2);
					L22: ;
				}
				mxv_l2 = mxv_i22;
			}
				mxv_i19 = mxv_l2;
				goto L19;
			}
			mxv_i19 = RL_l1;
			L19: ;
		}
		mxv_l1 = mxv_i19;
	}
	mxv_ax = mxs_index(_c,0,N,_SortId_);
	mxv_res = mxa_term_basesorts[ mxv_ax ] = mxv_l1;

	/* Code for propagation */
	mxv_waitsq = mxw_term_basesorts[ mxv_ax ];
	mxw_term_basesorts[ mxv_ax ] = NULL;
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode, mxv_res, mxv_waitsq->state, &mxv_waitsq->intres_array[0]);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}
}

static  void  mxe_node_basesorts( ELEMENT N, ELEMENT mxv_attvalue, int state, ELEMENT *mxv_waitpar ){
	ELEMENT  mxv_a98, mxv_i26, R_p43, mxv_i29, mxv_i28, mxv_a110, mxv_i31, mxv_i32, mxv_i30, I_p47, mxv_l4, D_l4, mxv_i27, mxv_l3, RL_l3,
		mxv_ax, mxv_res, mxv_par = N;
	AttInstSq mxv_waitsq, mxv_wsq;

	switch(state) {
		case 98 :
			mxv_a98 = mxv_attvalue;
			goto Lz98;
		case 110 :
			RL_l3 = mxv_waitpar[0];
			mxv_a110 = mxv_attvalue;
			goto Lz110;
	}
	{  /* LetExpr */
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR))) ) goto Lp6;
				if( mxs_before(_c,0,mxs_son(_c,0,-2,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp6;
				mxv_IR = mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor));
				if( mxv_IR == mxs_nil(_c,0) ) goto Lp6;
				if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp6;
				if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp6;
				mxv_IR = mxs_fath(_c,0,mxv_anchor);
				if( mxv_IR == mxs_nil(_c,0) ) goto Lp6;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp6;
				if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp6;
				R_p43 = mxs_rbroth(_c,0,mxv_anchor);
				mxv_IR = R_p43;
				if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR))) ) goto Lp6;
				if( mxs_before(_c,0,mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp6;
			{  /* Attribute access */
				mxv_ax = R_p43;
				mxv_a98 = mxs_node_basesorts(_m,381,mxv_ax);
				if( mxv_a98==MAXUNDEF ){
					insAttInst((EVALFCT)mxe_node_basesorts,mxv_par,98,mxw_node_basesorts,mxs_index(_c,0,mxv_ax,_SortId_));
					return;
				}
				Lz98:;
			}
				mxv_i26 = mxv_a98;
				goto L26;
			}
			Lp6: ;
				mxv_i26 = mxs_DefIdNodeList(_m,381);
			L26: ;
		}
		RL_l3 = mxv_i26;
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,RL_l3,mxs_AllNodes(_m,382)) ){
				mxv_i28 = mxs_true(_m,0);
				goto L28;
			}
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_id(_m,382,mxs_son(_m,382,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Node")) ){
				mxv_i29 = mxs_true(_m,0);
				goto L29;
			}
			mxv_i29 = mxs_false(_m,0);
			L29: ;
		}
			mxv_i28 = mxv_i29;
			L28: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i28) ){
				mxv_i27 = mxs_AllNodes(_m,382);
				goto L27;
			}
		{  /* LetExpr */
			D_l4 = mxs_decl(_m,384,N);
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = D_l4;
					mxv_IR = mxv_anchor;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp7;
					mxv_IR = mxs_fath(_c,0,mxv_anchor);
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp7;
					if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp7;
					if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp7;
					mxv_IR = mxs_rbroth(_c,0,mxv_anchor);
					if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp7;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp7;
					I_p47 = mxs_son(_c,0,1,mxs_rbroth(_c,0,mxv_anchor));
					mxv_IR = I_p47;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp7;
				{  /* FormulaCaseList */
					if( mxs_is(_m,386,N,_TermSortId_) ){
					{  /* Attribute access */
						mxv_ax = I_p47;
						mxv_a110 = mxs_node_basesorts(_m,386,mxv_ax);
						if( mxv_a110==MAXUNDEF ){ ELEMENT *P;
							P = insAttInst((EVALFCT)mxe_node_basesorts,mxv_par,110,mxw_node_basesorts,mxs_index(_c,0,mxv_ax,_SortId_));
							P[0] = RL_l3;
							return;
						}
						Lz110:;
					}
						mxv_i31 = mxs_sort_union(_m,386,RL_l3,mxv_a110);
						goto L31;
					}
					mxv_i31 = mxs_sort_union(_m,387,RL_l3,mxs_term_basesorts(_m,387,I_p47));
					L31: ;
				}
					mxv_i30 = mxv_i31;
					goto L30;
				}
				Lp7: ;
			{  /* FormulaCaseList */
				if( mxs_is(_m,389,N,_TermSortId_) ){
					mxv_i32 = RL_l3;
					goto L32;
				}
				mxv_i32 = mxs_appback(_m,390,RL_l3,D_l4);
				L32: ;
			}
					mxv_i30 = mxv_i32;
				L30: ;
			}
			mxv_l4 = mxv_i30;
		}
			mxv_i27 = mxv_l4;
			L27: ;
		}
		mxv_l3 = mxv_i27;
	}
	mxv_ax = mxs_index(_c,0,N,_SortId_);
	mxv_res = mxa_node_basesorts[ mxv_ax ] = mxv_l3;

	/* Code for propagation */
	mxv_waitsq = mxw_node_basesorts[ mxv_ax ];
	mxw_node_basesorts[ mxv_ax ] = NULL;
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode, mxv_res, mxv_waitsq->state, &mxv_waitsq->intres_array[0]);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}
}

static  void  mxe_encl_scope( ELEMENT S ){
	ELEMENT  mxv_i50,
		mxv_ax, mxv_par = S;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp10;
			mxv_i50 = mxs_scope(_m,462,mxs_fath(_m,462,S));
			goto L50;
		}
		Lp10: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp11;
			mxv_i50 = mxs_scope(_m,463,mxs_fath(_m,463,S));
			goto L50;
		}
		Lp11: ;
			mxv_i50 = mxs_nil(_m,464);
		L50: ;
	}
	mxv_ax = mxs_index(_c,0,S,_Scope_);
	mxa_encl_scope[ mxv_ax ] = mxv_i50;
}

static  void  mxe_bind_pos( ELEMENT N ){
	ELEMENT  mxv_i64, mxv_i63, mxv_i66, mxv_i65, mxv_i67, mxv_l10, BDP_l10, mxv_i62,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
		if( mxs_is(_m,526,mxs_fath(_m,526,N),_NameList_) ){
			mxv_i62 = N;
			goto L62;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,527,mxs_fath(_m,527,N),_LetExpr_)) ){
			mxv_i63 = mxs_false(_m,0);
			goto L63;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_son(_m,527,mxs_itoe(_c,0,1),mxs_fath(_m,527,N)),N) ){
			mxv_i64 = mxs_true(_m,0);
			goto L64;
		}
		mxv_i64 = mxs_false(_m,0);
		L64: ;
	}
		mxv_i63 = mxv_i64;
		L63: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i63) ){
			mxv_i62 = N;
			goto L62;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,528,mxs_scope(_m,528,N),_Condition_)) ){
			mxv_i65 = mxs_false(_m,0);
			goto L65;
		}
	{  /* FormulaCaseList */
		if( mxs_desc(_m,528,N,mxs_son(_m,528,mxs_itoe(_c,0,1),mxs_scope(_m,528,N))) ){
			mxv_i66 = mxs_true(_m,0);
			goto L66;
		}
		mxv_i66 = mxs_false(_m,0);
		L66: ;
	}
		mxv_i65 = mxv_i66;
		L65: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i65) ){
			mxv_i62 = N;
			goto L62;
		}
		if( mxs_is(_m,529,mxs_fath(_m,529,N),_Pattern_) ){
		{  /* LetExpr */
			BDP_l10 = mxs_lookup(_m,530,mxs_term(_m,530,mxs_son(_m,530,mxs_itoe(_c,0,1),N)),mxs_encl_scope(_m,530,mxs_scope(_m,530,N)));
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,BDP_l10,mxs_nil(_m,531)) ){
					mxv_i67 = N;
					goto L67;
				}
				mxv_i67 = BDP_l10;
				L67: ;
			}
			mxv_l10 = mxv_i67;
		}
			mxv_i62 = mxv_l10;
			goto L62;
		}
		mxv_i62 = mxs_lookup(_m,532,mxs_term(_m,532,mxs_son(_m,532,mxs_itoe(_c,0,1),N)),mxs_scope(_m,532,N));
		L62: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Name_);
	mxa_bind_pos[ mxv_ax ] = mxv_i62;
}

static  void  mxe_numberofastrks( ELEMENT ITL ){
	ELEMENT 
		mxv_ax, mxv_par = ITL;
	mxv_ax = mxs_index(_c,0,ITL,_ItemList_);
	mxa_numberofastrks[ mxv_ax ] = mxs_countastrks(_m,544,mxs_term(_m,544,ITL),mxs_itoe(_c,0,0));
}

static  void  mxe_predeclprodcd( ELEMENT PP ){
	ELEMENT  mxv_i82, mxv_i81, ID_p179,
		mxv_ax, mxv_par = PP;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PP;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 1 ) goto Lp19;
			if( !mxs_is(_c,0,mxv_IR,_PredeclProd_) ) goto Lp19;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp19;
			if( mxs_numsons(_c,0, mxv_IR ) != 4 ) goto Lp19;
			ID_p179 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = ID_p179;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp19;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_id(_m,588,ID_p179),mxs_atoe(_c,0,"Node")) ){
				mxv_i82 = mxs_itoe(_c,0,2);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,589,ID_p179),mxs_atoe(_c,0,"Point")) ){
				mxv_i82 = mxs_itoe(_c,0,1);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,590,ID_p179),mxs_atoe(_c,0,"nil")) ){
				mxv_i82 = mxs_itoe(_c,0,-1);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,591,ID_p179),mxs_atoe(_c,0,"Term")) ){
				mxv_i82 = mxs_itoe(_c,0,-2);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,592,ID_p179),mxs_atoe(_c,0,"NodeSort")) ){
				mxv_i82 = mxs_itoe(_c,0,-3);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,593,ID_p179),mxs_atoe(_c,0,"PredeclSort")) ){
				mxv_i82 = mxs_itoe(_c,0,-4);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,594,ID_p179),mxs_atoe(_c,0,"ClassSort")) ){
				mxv_i82 = mxs_itoe(_c,0,-5);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,595,ID_p179),mxs_atoe(_c,0,"TupelSort")) ){
				mxv_i82 = mxs_itoe(_c,0,-6);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,596,ID_p179),mxs_atoe(_c,0,"ListSort")) ){
				mxv_i82 = mxs_itoe(_c,0,-7);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,597,ID_p179),mxs_atoe(_c,0,"Ident")) ){
				mxv_i82 = mxs_itoe(_c,0,-8);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,598,ID_p179),mxs_atoe(_c,0,"Bool")) ){
				mxv_i82 = mxs_itoe(_c,0,-9);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,599,ID_p179),mxs_atoe(_c,0,"Char")) ){
				mxv_i82 = mxs_itoe(_c,0,-10);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,600,ID_p179),mxs_atoe(_c,0,"Int")) ){
				mxv_i82 = mxs_itoe(_c,0,-11);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,601,ID_p179),mxs_atoe(_c,0,"String")) ){
				mxv_i82 = mxs_itoe(_c,0,-12);
				goto L82;
			}
			if( mxs_eq(_m,0,mxs_id(_m,602,ID_p179),mxs_atoe(_c,0,"Reference")) ){
				mxv_i82 = mxs_itoe(_c,0,-13);
				goto L82;
			}
			mxv_i82 = mxs_nil(_m,603);
			L82: ;
		}
			mxv_i81 = mxv_i82;
			goto L81;
		}
		Lp19: ;
			mxv_i81 = mxs_nil(_m,604);
		L81: ;
	}
	mxv_ax = mxs_index(_c,0,PP,_PredeclProd_);
	mxa_predeclprodcd[ mxv_ax ] = mxv_i81;
}

static  void  mxe_tupelprodcd( ELEMENT TP ){
	ELEMENT 
		mxv_ax, mxv_par = TP;
	mxv_ax = mxs_index(_c,0,TP,_TupelProd_);
	mxa_tupelprodcd[ mxv_ax ] = mxs_neg(_m,607,mxs_add(_m,607,mxs_index(_m,607,TP,_TupelProd_),mxs_sub(_m,607,mxs_number(_m,607,_PredeclProd_),mxs_itoe(_c,0,2))));
}

static  void  mxe_listprodcd( ELEMENT LP ){
	ELEMENT 
		mxv_ax, mxv_par = LP;
	mxv_ax = mxs_index(_c,0,LP,_ListProd_);
	mxa_listprodcd[ mxv_ax ] = mxs_neg(_m,610,mxs_add(_m,610,mxs_index(_m,610,LP,_ListProd_),mxs_add(_m,611,mxs_number(_m,611,_TupelProd_),mxs_sub(_m,611,mxs_number(_m,611,_PredeclProd_),mxs_itoe(_c,0,2)))));
}

static  void  mxe_classprodcd( ELEMENT CP ){
	ELEMENT 
		mxv_ax, mxv_par = CP;
	mxv_ax = mxs_index(_c,0,CP,_ClassProd_);
	mxa_classprodcd[ mxv_ax ] = mxs_sub(_m,618,mxs_smallestlistprodcd(_m,618),mxs_index(_m,618,CP,_ClassProd_));
}

static  void  mxe_patnpos( ELEMENT PN ){
	ELEMENT  mxv_i86,
		mxv_ax, mxv_par = PN;
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,654,mxs_fath(_m,654,PN),_ItemList_)) ){
			mxv_i86 = mxs_TopPosition(_m,654);
			goto L86;
		}
		if( mxs_eq(_m,0,mxs_next_left_pat(_m,655,PN),mxs_nil(_m,655)) ){
			mxv_i86 = mxs_AbsPosition(_m,655,mxs_patnposition(_m,655,PN,mxs_itoe(_c,0,1)));
			goto L86;
		}
		mxv_i86 = mxs_RelPosition(_m,656,mxs_patnposition(_m,656,PN,mxs_itoe(_c,0,1)));
		L86: ;
	}
	mxv_ax = mxs_index(_c,0,PN,_Pattern_);
	mxa_patnpos[ mxv_ax ] = mxv_i86;
}

static  void  mxe_num_items( ELEMENT P ){
	ELEMENT  mxv_i124, mxv_l20, NUM_IT_l20,
		mxv_ax, mxv_par = P;
	{  /* LetExpr */
		NUM_IT_l20 = mxs_numsons(_m,818,mxs_son(_m,818,mxs_itoe(_c,0,2),P));
		{  /* FormulaCaseList */
			if( ( ! mxs_is(_m,819,mxs_son(_m,819,mxs_itoe(_c,0,2),P),_Blank_)) ){
				mxv_i124 = mxs_sub(_m,819,NUM_IT_l20,mxs_numberofastrks(_m,819,mxs_son(_m,819,mxs_itoe(_c,0,2),P)));
				goto L124;
			}
			mxv_i124 = mxs_itoe(_c,0,0);
			L124: ;
		}
		mxv_l20 = mxv_i124;
	}
	mxv_ax = mxs_index(_c,0,P,_Pattern_);
	mxa_num_items[ mxv_ax ] = mxv_l20;
}

static  void  mxe_args( ELEMENT F ){
	ELEMENT 
		mxv_ax, mxv_par = F;
	mxv_ax = mxs_index(_c,0,F,_FuncAppl_);
	mxa_args[ mxv_ax ] = mxs_son(_m,846,mxs_itoe(_c,0,2),F);
}

static  void  mxe_caseexpr( ELEMENT C ){
	ELEMENT  mxv_i127,
		mxv_ax, mxv_par = C;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,850,C),mxs_nil(_m,850)) ){
			mxv_i127 = mxs_appback(_m,850,mxs_ExprNList(_m,850),mxs_son(_m,850,mxs_itoe(_c,0,2),C));
			goto L127;
		}
		mxv_i127 = mxs_appback(_m,851,mxs_caseexpr(_m,851,mxs_lbroth(_m,851,C)),mxs_son(_m,851,mxs_itoe(_c,0,2),C));
		L127: ;
	}
	mxv_ax = mxs_index(_c,0,C,_IfCase_);
	mxa_caseexpr[ mxv_ax ] = mxv_i127;
}

static  void  mxe_allexpr( ELEMENT I ){
	ELEMENT 
		mxv_ax, mxv_par = I;
	mxv_ax = mxs_index(_c,0,I,_IfExpr_);
	mxa_allexpr[ mxv_ax ] = mxs_appback(_m,855,mxs_caseexpr(_m,855,mxs_son(_m,855,mxs_itoe(_c,0,-1),mxs_son(_m,855,mxs_itoe(_c,0,1),I))),mxs_son(_m,855,mxs_itoe(_c,0,2),I));
}

static  void  mxe_encl_patterncase( ELEMENT N ){
	ELEMENT  mxv_i128,
		mxv_ax, mxv_par = N;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp39;
			mxv_i128 = N;
			goto L128;
		}
		Lp39: ;
			mxv_i128 = mxs_encl_patterncase(_m,860,mxs_fath(_m,860,N));
		L128: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Node);
	mxa_encl_patterncase[ mxv_ax ] = mxv_i128;
}

static  void  mxe_top_pattern( ELEMENT N ){
	ELEMENT  mxv_i131, mxv_i130, mxv_i129,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_is(_m,864,mxs_fath(_m,864,N),_PatternCase_) ){
			mxv_i130 = mxs_true(_m,0);
			goto L130;
		}
	{  /* FormulaCaseList */
		if( mxs_is(_m,864,mxs_fath(_m,864,mxs_fath(_m,864,N)),_Condition_) ){
			mxv_i131 = mxs_true(_m,0);
			goto L131;
		}
		mxv_i131 = mxs_false(_m,0);
		L131: ;
	}
		mxv_i130 = mxv_i131;
		L130: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i130) ){
			mxv_i129 = N;
			goto L129;
		}
		mxv_i129 = mxs_top_pattern(_m,865,mxs_fath(_m,865,N));
		L129: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Node);
	mxa_top_pattern[ mxv_ax ] = mxv_i129;
}

static  void  mxe_son_nr( ELEMENT N ){
	ELEMENT  mxv_i189,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,1076,N),mxs_nil(_m,1076)) ){
			mxv_i189 = mxs_itoe(_c,0,1);
			goto L189;
		}
		mxv_i189 = mxs_add(_m,1077,mxs_itoe(_c,0,1),mxs_son_nr(_m,1077,mxs_lbroth(_m,1077,N)));
		L189: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FctOrAtt_);
	mxa_son_nr[ mxv_ax ] = mxv_i189;
}

static  void  mxe_relacc_nr( ELEMENT N ){
	ELEMENT  mxv_i192, mxv_i191, mxv_i190, mxv_l34, F_l34,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		F_l34 = mxs_fath(_m,1081,mxs_decl(_m,1081,mxs_son(_m,1081,mxs_itoe(_c,0,1),N)));
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! mxs_is(_m,1082,F_l34,_FctOrAtt_)) ){
				mxv_i191 = mxs_false(_m,0);
				goto L191;
			}
		{  /* FormulaCaseList */
			if( mxs_desc(_m,1082,N,mxs_fath(_m,1082,F_l34)) ){
				mxv_i192 = mxs_true(_m,0);
				goto L192;
			}
			mxv_i192 = mxs_false(_m,0);
			L192: ;
		}
			mxv_i191 = mxv_i192;
			L191: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i191) ){
				mxv_i190 = mxs_son_nr(_m,1082,F_l34);
				goto L190;
			}
			mxv_i190 = mxs_nil(_m,1083);
			L190: ;
		}
		mxv_l34 = mxv_i190;
	}
	mxv_ax = mxs_index(_c,0,N,_FuncAppl_);
	mxa_relacc_nr[ mxv_ax ] = mxv_l34;
}

static  void  mxe_appl_list_formula( ELEMENT N ){
	ELEMENT  mxv_i193, E_p264, X_p266, Y_p267, X_p269,
		mxv_ax, mxv_par = N;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp64;
			if( !mxs_is(_c,0,mxv_IR,_PredAppl_) ) goto Lp64;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp64;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp64;
			E_p264 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = E_p264;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp64;
			mxv_i193 = mxs_appl_list_expr(_m,1087,E_p264);
			goto L193;
		}
		Lp64: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp65;
			if( !mxs_is(_c,0,mxv_IR,_BinOp_) ) goto Lp65;
			X_p266 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = X_p266;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp65;
			Y_p267 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = Y_p267;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp65;
			mxv_i193 = mxs_conc(_m,1088,mxs_appl_list_formula(_m,1088,X_p266),mxs_appl_list_formula(_m,1088,Y_p267));
			goto L193;
		}
		Lp65: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 1 ) goto Lp66;
			if( !mxs_is(_c,0,mxv_IR,_Neg_) ) goto Lp66;
			X_p269 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = X_p269;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp66;
			mxv_i193 = mxs_appl_list_formula(_m,1089,X_p269);
			goto L193;
		}
		Lp66: ;
			mxv_i193 = mxs_ApplList(_m,1090);
		L193: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Formula_);
	mxa_appl_list_formula[ mxv_ax ] = mxv_i193;
}

static  void  mxe_appl_list_case( ELEMENT N ){
	ELEMENT  mxv_i194, F_p271, E_p272, E_p274, mxv_i195, mxv_l35, AL_l35,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp67;
				if( !mxs_is(_c,0,mxv_IR,_FormulaCase_) ) goto Lp67;
				F_p271 = mxs_son(_c,0,1,mxv_anchor);
				mxv_IR = F_p271;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp67;
				E_p272 = mxs_son(_c,0,2,mxv_anchor);
				mxv_IR = E_p272;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp67;
				mxv_i194 = mxs_conc(_m,1095,mxs_appl_list_formula(_m,1095,F_p271),mxs_appl_list_expr(_m,1095,E_p272));
				goto L194;
			}
			Lp67: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp68;
				if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp68;
				E_p274 = mxs_son(_c,0,2,mxv_anchor);
				mxv_IR = E_p274;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp68;
				mxv_i194 = mxs_appl_list_expr(_m,1096,E_p274);
				goto L194;
			}
			Lp68: ;
				mxv_i194 = mxs_ApplList(_m,1097);
			L194: ;
		}
		AL_l35 = mxv_i194;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_rbroth(_m,1098,N),mxs_nil(_m,1098)) ){
				mxv_i195 = AL_l35;
				goto L195;
			}
			mxv_i195 = mxs_conc(_m,1098,AL_l35,mxs_appl_list_case(_m,1098,mxs_rbroth(_m,1098,N)));
			L195: ;
		}
		mxv_l35 = mxv_i195;
	}
	mxv_ax = mxs_index(_c,0,N,_Case_);
	mxa_appl_list_case[ mxv_ax ] = mxv_l35;
}

static  void  mxe_appl_list_expr( ELEMENT N ){
	ELEMENT  mxv_i197, mxv_i196, C_p277, E_p278, E_p280, E_p283, mxv_i204, mxv_i203, mxv_i202, mxv_i201, mxv_i200, mxv_i199, mxv_i198, mxv_l36, AL_l36,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp69;
				if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp69;
				mxv_IR = mxs_son(_c,0,1,mxv_anchor);
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp69;
				if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp69;
				C_p277 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
				mxv_IR = C_p277;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp69;
				E_p278 = mxs_son(_c,0,2,mxv_anchor);
				mxv_IR = E_p278;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp69;
				mxv_i196 = mxs_conc(_m,1103,mxs_appl_list_case(_m,1103,C_p277),mxs_appl_list_expr(_m,1103,E_p278));
				goto L196;
			}
			Lp69: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp70;
				if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp70;
				E_p280 = mxs_son(_c,0,2,mxv_anchor);
				mxv_IR = E_p280;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp70;
				mxv_i196 = mxs_appl_list_expr(_m,1104,E_p280);
				goto L196;
			}
			Lp70: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp71;
				if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp71;
				mxv_IR = mxs_son(_c,0,2,mxv_anchor);
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp71;
				if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp71;
				E_p283 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
				mxv_IR = E_p283;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp71;
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_relacc_nr(_m,1106,N),mxs_nil(_m,1106)) ){
					mxv_i197 = mxs_appl_list_expr(_m,1106,E_p283);
					goto L197;
				}
				mxv_i197 = mxs_appback(_m,1107,mxs_appl_list_expr(_m,1107,E_p283),N);
				L197: ;
			}
				mxv_i196 = mxv_i197;
				goto L196;
			}
			Lp71: ;
				mxv_i196 = mxs_ApplList(_m,1108);
			L196: ;
		}
		AL_l36 = mxv_i196;
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_rbroth(_m,1109,N),mxs_nil(_m,1109)) ){
				mxv_i199 = mxs_true(_m,0);
				goto L199;
			}
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( mxs_is(_m,1109,mxs_rbroth(_m,1109,N),_Int_) ){
				mxv_i201 = mxs_true(_m,0);
				goto L201;
			}
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( mxs_is(_m,1109,mxs_fath(_m,1109,N),_CaseRule_) ){
				mxv_i203 = mxs_true(_m,0);
				goto L203;
			}
		{  /* FormulaCaseList */
			if( mxs_is(_m,1109,mxs_fath(_m,1109,N),_CaseIs_) ){
				mxv_i204 = mxs_true(_m,0);
				goto L204;
			}
			mxv_i204 = mxs_false(_m,0);
			L204: ;
		}
			mxv_i203 = mxv_i204;
			L203: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i203) ){
				mxv_i202 = mxs_true(_m,0);
				goto L202;
			}
			mxv_i202 = mxs_false(_m,0);
			L202: ;
		}
			mxv_i201 = mxv_i202;
			L201: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i201) ){
				mxv_i200 = mxs_true(_m,0);
				goto L200;
			}
			mxv_i200 = mxs_false(_m,0);
			L200: ;
		}
			mxv_i199 = mxv_i200;
			L199: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i199) ){
				mxv_i198 = AL_l36;
				goto L198;
			}
			mxv_i198 = mxs_conc(_m,1110,AL_l36,mxs_appl_list_expr(_m,1110,mxs_rbroth(_m,1110,N)));
			L198: ;
		}
		mxv_l36 = mxv_i198;
	}
	mxv_ax = mxs_index(_c,0,N,_Expr_);
	mxa_appl_list_expr[ mxv_ax ] = mxv_l36;
}

static  void  mxe_appl_list( ELEMENT N ){
	ELEMENT  mxv_i205, E_p285,
		mxv_ax, mxv_par = N;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp72;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp72;
			E_p285 = mxs_son(_c,0,-1,mxv_anchor);
			mxv_IR = E_p285;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp72;
			mxv_i205 = mxs_appl_list_expr(_m,1114,E_p285);
			goto L205;
		}
		Lp72: ;
			mxv_i205 = mxs_ApplList(_m,1115);
		L205: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FctOrAtt_);
	mxa_appl_list[ mxv_ax ] = mxv_i205;
}

static  void  mxe_def_value( ELEMENT N ){
	ELEMENT  mxv_i209, mxv_i208, mxv_l37, I_l37,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		I_l37 = mxs_idtos(_m,1143,mxs_term(_m,1143,mxs_son(_m,1143,mxs_itoe(_c,0,1),N)));
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,I_l37,mxs_atoe(_c,0,"fath")) ){
				mxv_i208 = mxs_TWfath(_m,1144);
				goto L208;
			}
			if( mxs_eq(_m,0,I_l37,mxs_atoe(_c,0,"son")) ){
				mxv_i208 = mxs_TWson(_m,1145,mxs_itoe(_c,0,0));
				goto L208;
			}
			if( mxs_eq(_m,0,I_l37,mxs_atoe(_c,0,"rbroth")) ){
				mxv_i208 = mxs_TWrbroth(_m,1146);
				goto L208;
			}
			if( mxs_eq(_m,0,I_l37,mxs_atoe(_c,0,"lbroth")) ){
				mxv_i208 = mxs_TWlbroth(_m,1147);
				goto L208;
			}
			if( mxs_eq(_m,0,I_l37,mxs_atoe(_c,0,"nil")) ){
				mxv_i208 = mxs_TW_emptyset(_m,1148);
				goto L208;
			}
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp73;
				mxv_IR = mxs_fath(_c,0,mxv_anchor);
				if( mxv_IR == mxs_nil(_c,0) ) goto Lp73;
				if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp73;
				if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp73;
				mxv_i209 = N;
				goto L209;
			}
			Lp73: ;
				mxv_i209 = mxs_nil(_m,1150);
			L209: ;
		}
			mxv_i208 = mxv_i209;
			L208: ;
		}
		mxv_l37 = mxv_i208;
	}
	mxv_ax = mxs_index(_c,0,N,_DefId_);
	mxa_def_value[ mxv_ax ] = mxv_l37;
}

static  void  mxe_node_parnr( ELEMENT N ){
	ELEMENT  mxv_i211, SI_p293, SI_p296,
		mxv_ax, mxv_par = N;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp74;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp74;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp74;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp74;
			SI_p293 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = SI_p293;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp74;
			mxv_i211 = mxs_node_parnr_fct(_m,1160,SI_p293);
			goto L211;
		}
		Lp74: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp75;
			if( !mxs_is(_c,0,mxv_IR,_FuncDecl_) ) goto Lp75;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp75;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp75;
			SI_p296 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = SI_p296;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp75;
			mxv_i211 = mxs_node_parnr_fct(_m,1161,SI_p296);
			goto L211;
		}
		Lp75: ;
			mxv_i211 = mxs_nil(_m,1162);
		L211: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FctOrAttDecl_);
	mxa_node_parnr[ mxv_ax ] = mxv_i211;
}

static  void  mxe_appl_value( ELEMENT N ){
	ELEMENT  mxv_i214, SN_p299, mxv_i213, mxv_l38, F_l38, mxv_i212,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_relacc_nr(_m,1167,N),mxs_nil(_m,1167))) ){
			mxv_i212 = mxs_RelevAcc(_m,1167,mxs_relacc_nr(_m,1167,N));
			goto L212;
		}
	{  /* LetExpr */
		F_l38 = mxs_def_value(_m,1169,mxs_decl(_m,1169,mxs_son(_m,1169,mxs_itoe(_c,0,1),N)));
		{  /* FormulaCaseList */
			if( mxs_is(_m,1170,F_l38,_TWson) ){
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = N;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp76;
					if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp76;
					mxv_IR = mxs_son(_c,0,2,mxv_anchor);
					if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp76;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp76;
					SN_p299 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
					mxv_IR = SN_p299;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp76;
					if( !mxs_is(_c,0,mxv_IR,_IntConst_) ) goto Lp76;
					mxv_i214 = mxs_TWson(_m,1171,mxs_term(_m,1171,mxs_son(_m,1171,mxs_itoe(_c,0,1),SN_p299)));
					goto L214;
				}
				Lp76: ;
					mxv_i214 = F_l38;
				L214: ;
			}
				mxv_i213 = mxv_i214;
				goto L213;
			}
			mxv_i213 = F_l38;
			L213: ;
		}
		mxv_l38 = mxv_i213;
	}
		mxv_i212 = mxv_l38;
		L212: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FuncAppl_);
	mxa_appl_value[ mxv_ax ] = mxv_i212;
}

static  void  mxe_nodepar_expr( ELEMENT N ){
	ELEMENT  mxv_i216, mxv_i215, mxv_l39, F_l39,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		F_l39 = mxs_fath(_m,1176,mxs_decl(_m,1176,mxs_son(_m,1176,mxs_itoe(_c,0,1),N)));
		{  /* FormulaCaseList */
			if( mxs_is(_m,1177,F_l39,_FctOrAttDecl_) ){
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_node_parnr(_m,1178,F_l39),mxs_nil(_m,1178)) ){
					mxv_i216 = mxs_nil(_m,1178);
					goto L216;
				}
				mxv_i216 = mxs_son(_m,1178,mxs_node_parnr(_m,1178,F_l39),mxs_son(_m,1178,mxs_itoe(_c,0,2),N));
				L216: ;
			}
				mxv_i215 = mxv_i216;
				goto L215;
			}
			mxv_i215 = mxs_nil(_m,1179);
			L215: ;
		}
		mxv_l39 = mxv_i215;
	}
	mxv_ax = mxs_index(_c,0,N,_FuncAppl_);
	mxa_nodepar_expr[ mxv_ax ] = mxv_l39;
}

static  void  mxe_valueterm_list( ELEMENT C, ELEMENT mxv_attvalue, int state, ELEMENT *mxv_waitpar ){
	ELEMENT  mxv_a1174, mxv_a1177, mxv_a1179, mxv_i226,
		mxv_ax, mxv_res, mxv_par = C;
	AttInstSq mxv_waitsq, mxv_wsq;

	switch(state) {
		case 1174 :
			mxv_a1174 = mxv_attvalue;
			goto Lz1174;
		case 1177 :
			mxv_a1177 = mxv_attvalue;
			goto Lz1177;
		case 1179 :
			mxv_a1177 = mxv_waitpar[0];
			mxv_a1179 = mxv_attvalue;
			goto Lz1179;
	}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,1223,C),mxs_nil(_m,1223)) ){
		{  /* Attribute access */
			mxv_ax = mxs_son(_m,1223,mxs_itoe(_c,0,2),C);
			mxv_a1174 = mxs_valueterm(_m,1223,mxv_ax);
			if( mxv_a1174==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_valueterm_list,mxv_par,1174,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				return;
			}
			Lz1174:;
		}
			mxv_i226 = mxv_a1174;
			goto L226;
		}
	{  /* Attribute access */
		mxv_ax = mxs_rbroth(_m,1224,C);
		mxv_a1177 = mxs_valueterm_list(_m,1224,mxv_ax);
		if( mxv_a1177==MAXUNDEF ){
			insAttInst((EVALFCT)mxe_valueterm_list,mxv_par,1177,mxw_valueterm_list,mxs_index(_c,0,mxv_ax,_Case_));
			return;
		}
		Lz1177:;
	}
	{  /* Attribute access */
		mxv_ax = mxs_son(_m,1224,mxs_itoe(_c,0,2),C);
		mxv_a1179 = mxs_valueterm(_m,1224,mxv_ax);
		if( mxv_a1179==MAXUNDEF ){ ELEMENT *P;
			P = insAttInst((EVALFCT)mxe_valueterm_list,mxv_par,1179,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
			P[0] = mxv_a1177;
			return;
		}
		Lz1179:;
	}
		mxv_i226 = mxs_TW_or(_m,1224,mxv_a1177,mxv_a1179);
		L226: ;
	}
	mxv_ax = mxs_index(_c,0,C,_Case_);
	mxv_res = mxa_valueterm_list[ mxv_ax ] = mxv_i226;

	/* Code for propagation */
	mxv_waitsq = mxw_valueterm_list[ mxv_ax ];
	mxw_valueterm_list[ mxv_ax ] = NULL;
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode, mxv_res, mxv_waitsq->state, &mxv_waitsq->intres_array[0]);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}
}

static  void  mxe_valueterm( ELEMENT N, ELEMENT mxv_attvalue, int state, ELEMENT *mxv_waitpar ){
	ELEMENT  mxv_a1185, mxv_i228, mxv_a1189, mxv_a1190, mxv_a1191, mxv_a1192, mxv_i229, mxv_a1199, mxv_a1204, mxv_l41, A_l41, mxv_i230, mxv_a1207, mxv_i227, C_p306, EX_p307, E_p309, E_p312, F_p313, PAT_p316,
		mxv_ax, mxv_res, mxv_par = N;
	AttInstSq mxv_waitsq, mxv_wsq;

	switch(state) {
		case 1185 :
			mxv_a1185 = mxv_attvalue;
			goto Lz1185;
		case 1189 :
			EX_p307 = mxv_waitpar[0];
			mxv_a1189 = mxv_attvalue;
			goto Lz1189;
		case 1190 :
			mxv_a1189 = mxv_waitpar[0];
			mxv_a1190 = mxv_attvalue;
			goto Lz1190;
		case 1191 :
			mxv_a1191 = mxv_attvalue;
			goto Lz1191;
		case 1192 :
			mxv_a1192 = mxv_attvalue;
			goto Lz1192;
		case 1199 :
			mxv_a1199 = mxv_attvalue;
			goto Lz1199;
		case 1204 :
			A_l41 = mxv_waitpar[0];
			PAT_p316 = mxv_waitpar[1];
			mxv_a1204 = mxv_attvalue;
			goto Lz1204;
		case 1207 :
			mxv_a1207 = mxv_attvalue;
			goto Lz1207;
	}
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp80;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_appl_value(_m,1228,N),mxs_TW_emptyset(_m,1228)) ){
				mxv_i228 = mxs_TW_emptyset(_m,1228);
				goto L228;
			}
		{  /* Attribute access */
			mxv_ax = mxs_nodepar_expr(_m,1229,N);
			mxv_a1185 = mxs_valueterm(_m,1229,mxv_ax);
			if( mxv_a1185==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_valueterm,mxv_par,1185,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				return;
			}
			Lz1185:;
		}
			mxv_i228 = mxs_TW_conc(_m,1229,mxv_a1185,mxs_appl_value(_m,1229,N));
			L228: ;
		}
			mxv_i227 = mxv_i228;
			goto L227;
		}
		Lp80: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp81;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp81;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp81;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp81;
			C_p306 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = C_p306;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp81;
			EX_p307 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = EX_p307;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp81;
		{  /* Attribute access */
			mxv_ax = C_p306;
			mxv_a1189 = mxs_valueterm_list(_m,1230,mxv_ax);
			if( mxv_a1189==MAXUNDEF ){ ELEMENT *P;
				P = insAttInst((EVALFCT)mxe_valueterm,mxv_par,1189,mxw_valueterm_list,mxs_index(_c,0,mxv_ax,_Case_));
				P[0] = EX_p307;
				return;
			}
			Lz1189:;
		}
		{  /* Attribute access */
			mxv_ax = EX_p307;
			mxv_a1190 = mxs_valueterm(_m,1230,mxv_ax);
			if( mxv_a1190==MAXUNDEF ){ ELEMENT *P;
				P = insAttInst((EVALFCT)mxe_valueterm,mxv_par,1190,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				P[0] = mxv_a1189;
				return;
			}
			Lz1190:;
		}
			mxv_i227 = mxs_TW_or(_m,1230,mxv_a1189,mxv_a1190);
			goto L227;
		}
		Lp81: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp82;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp82;
			E_p309 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = E_p309;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp82;
		{  /* Attribute access */
			mxv_ax = E_p309;
			mxv_a1191 = mxs_valueterm(_m,1231,mxv_ax);
			if( mxv_a1191==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_valueterm,mxv_par,1191,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				return;
			}
			Lz1191:;
		}
			mxv_i227 = mxv_a1191;
			goto L227;
		}
		Lp82: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp83;
			mxv_IR = mxs_fath(_c,0,mxv_anchor);
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp83;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp83;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp83;
			E_p312 = mxs_rbroth(_c,0,mxv_anchor);
			mxv_IR = E_p312;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp83;
		{  /* Attribute access */
			mxv_ax = E_p312;
			mxv_a1192 = mxs_valueterm(_m,1232,mxv_ax);
			if( mxv_a1192==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_valueterm,mxv_par,1192,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				return;
			}
			Lz1192:;
		}
			mxv_i227 = mxv_a1192;
			goto L227;
		}
		Lp83: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR))) ) goto Lp84;
			if( mxs_before(_c,0,mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp84;
			F_p313 = mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor));
			mxv_IR = F_p313;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp84;
			if( mxs_numsons(_c,0, mxv_IR ) < 3 ) goto Lp84;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp84;
			mxv_IR = mxs_fath(_c,0,mxv_anchor);
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp84;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp84;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp84;
			if( !mxs_is(_c,0,mxv_IR,_NameList_) ) goto Lp84;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_son(_m,1235,mxs_node_parnr(_m,1235,F_p313),mxs_fath(_m,1235,N)),N) ){
				mxv_i229 = mxs_TW_identabb(_m,1235);
				goto L229;
			}
			mxv_i229 = mxs_nil(_m,1235);
			L229: ;
		}
			mxv_i227 = mxv_i229;
			goto L227;
		}
		Lp84: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp85;
			PAT_p316 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = PAT_p316;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp85;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp85;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp85;
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,mxs_bind_pos(_m,1238,N),N)) ){
			{  /* Attribute access */
				mxv_ax = mxs_bind_pos(_m,1238,N);
				mxv_a1199 = mxs_valueterm(_m,1238,mxv_ax);
				if( mxv_a1199==MAXUNDEF ){
					insAttInst((EVALFCT)mxe_valueterm,mxv_par,1199,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
					return;
				}
				Lz1199:;
			}
				mxv_i230 = mxv_a1199;
				goto L230;
			}
		{  /* LetExpr */
			A_l41 = mxs_pat_anchor(_m,1239,mxs_encl_patcase(_m,1239,N));
			{  /* Attribute access */
				mxv_ax = mxs_son(_m,1240,mxs_itoe(_c,0,3),A_l41);
				mxv_a1204 = mxs_valueterm(_m,1240,mxv_ax);
				if( mxv_a1204==MAXUNDEF ){ ELEMENT *P;
					P = insAttInst((EVALFCT)mxe_valueterm,mxv_par,1204,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
					P[0] = A_l41;
					P[1] = PAT_p316;
					return;
				}
				Lz1204:;
			}
			mxv_l41 = mxs_TW_conc(_m,1240,mxv_a1204,mxs_pat_way(_m,1240,A_l41,PAT_p316));
		}
			mxv_i230 = mxv_l41;
			L230: ;
		}
			mxv_i227 = mxv_i230;
			goto L227;
		}
		Lp85: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Name_) ) goto Lp86;
		{  /* Attribute access */
			mxv_ax = mxs_bind_pos(_m,1242,N);
			mxv_a1207 = mxs_valueterm(_m,1242,mxv_ax);
			if( mxv_a1207==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_valueterm,mxv_par,1207,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				return;
			}
			Lz1207:;
		}
			mxv_i227 = mxv_a1207;
			goto L227;
		}
		Lp86: ;
			mxv_i227 = mxs_nil(_m,1243);
		L227: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Expr_);
	mxv_res = mxa_valueterm[ mxv_ax ] = mxv_i227;

	/* Code for propagation */
	mxv_waitsq = mxw_valueterm[ mxv_ax ];
	mxw_valueterm[ mxv_ax ] = NULL;
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode, mxv_res, mxv_waitsq->state, &mxv_waitsq->intres_array[0]);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}
}

static  void  mxe_attr_list_matlist( ELEMENT N ){
	ELEMENT 
		mxv_ax, mxv_par = N;
	mxv_ax = mxs_index(_c,0,N,_FuAtList_);
	mxa_attr_list_matlist[ mxv_ax ] = mxs_enter_attrgroup_list(_m,1270,mxs_itoe(_c,0,1),mxs_attr_list_groups(_m,1270,N),mxs_RefList(_m,1270));
}

static  void  mxe_result_value( ELEMENT N ){
	ELEMENT  mxv_l42, subtnr_l42,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		subtnr_l42 = mxs_sub(_m,1277,mxs_eval_groupnr(_m,1277,N),mxs_eval_prev_grnum(_m,1277,mxs_fath(_m,1277,N)));
		mxv_l42 = mxs_mat_lookup(_m,1278,mxs_subterm(_m,1278,subtnr_l42,mxs_attr_list_matlist(_m,1278,mxs_fath(_m,1278,N))),mxs_numsubterms(_m,1279,mxs_eval_group(_m,1279,N)),mxs_group_index(_m,1279,N));
	}
	mxv_ax = mxs_index(_c,0,N,_FctOrAtt_);
	mxa_result_value[ mxv_ax ] = mxv_l42;
}

static  void  mxe_is_relev_att_access( ELEMENT FA ){
	ELEMENT  mxv_i314, mxv_i313, mxv_i312, mxv_i311, mxv_i310, mxv_i309, mxv_i308, mxv_l51, E_l51, mxv_l50, D_l50,
		mxv_ax, mxv_par = FA;
	{  /* LetExpr */
		D_l50 = mxs_fath(_m,1449,mxs_decl(_m,1449,mxs_son(_m,1449,mxs_itoe(_c,0,1),FA)));
		{  /* LetExpr */
			E_l51 = mxs_encl_fctoratt(_m,1450,FA);
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,1451,D_l50,_FctOrAtt_)) ){
					mxv_i309 = mxs_false(_m,0);
					goto L309;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,1451,E_l51,_FctOrAtt_)) ){
					mxv_i311 = mxs_false(_m,0);
					goto L311;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,mxs_eval_groupnr(_m,1451,D_l50),mxs_eval_groupnr(_m,1451,E_l51))) ){
					mxv_i313 = mxs_false(_m,0);
					goto L313;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_contains_attr(_m,1452,mxs_eval_group(_m,1452,E_l51)),mxs_true(_m,1452)) ){
					mxv_i314 = mxs_true(_m,0);
					goto L314;
				}
				mxv_i314 = mxs_false(_m,0);
				L314: ;
			}
				mxv_i313 = mxv_i314;
				L313: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i313) ){
					mxv_i312 = mxs_true(_m,0);
					goto L312;
				}
				mxv_i312 = mxs_false(_m,0);
				L312: ;
			}
				mxv_i311 = mxv_i312;
				L311: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i311) ){
					mxv_i310 = mxs_true(_m,0);
					goto L310;
				}
				mxv_i310 = mxs_false(_m,0);
				L310: ;
			}
				mxv_i309 = mxv_i310;
				L309: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i309) ){
					mxv_i308 = mxs_true(_m,1452);
					goto L308;
				}
				mxv_i308 = mxs_false(_m,1452);
				L308: ;
			}
			mxv_l51 = mxv_i308;
		}
		mxv_l50 = mxv_l51;
	}
	mxv_ax = mxs_index(_c,0,FA,_FuncAppl_);
	mxa_is_relev_att_access[ mxv_ax ] = mxv_l50;
}

static  void  mxe_appl_order( ELEMENT N ){
	ELEMENT  mxv_i316, mxv_l52, ORD_l52, mxv_i315,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_is_relev_att_access(_m,1455,N),mxs_true(_m,1455)) ){
		{  /* LetExpr */
			ORD_l52 = mxs_val_order(_m,1457,mxs_normalform(_m,1457,mxs_FList(_m,1457),mxs_valueterm(_m,1457,mxs_nodepar_expr(_m,1457,N)),mxs_fath(_m,1457,mxs_encl_fctoratt(_m,1457,N))));
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,ORD_l52,mxs_nil(_m,1458)) ){
					mxv_i316 = mxs_Ord_nothing(_m,1458);
					goto L316;
				}
				mxv_i316 = ORD_l52;
				L316: ;
			}
			mxv_l52 = mxv_i316;
		}
			mxv_i315 = mxv_l52;
			goto L315;
		}
		mxv_i315 = mxs_Ord_neutral(_m,1459);
		L315: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FuncAppl_);
	mxa_appl_order[ mxv_ax ] = mxv_i315;
}

static  void  mxe_appl_relacc_list( ELEMENT N ){
	ELEMENT 
		mxv_ax, mxv_par = N;
	mxv_ax = mxs_index(_c,0,N,_FctOrAtt_);
	mxa_appl_relacc_list[ mxv_ax ] = mxs_filter_relev_acc(_m,1468,mxs_appl_list(_m,1468,N));
}

static  void  mxe_maybe_wait( ELEMENT N ){
	ELEMENT  mxv_i327, mxv_i326, mxv_i325, mxv_i324, mxv_i332, mxv_i331, mxv_i330, mxv_i329, mxv_i328, mxv_i323, mxv_i322, mxv_i321, mxv_i320, mxv_l54, EA_l54, mxv_l53, FD_l53, mxv_i319,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_is_relev_att_access(_m,1490,N),mxs_true(_m,1490)) ){
		{  /* LetExpr */
			FD_l53 = mxs_fath(_m,1491,mxs_decl(_m,1491,mxs_son(_m,1491,mxs_itoe(_c,0,1),N)));
			{  /* LetExpr */
				EA_l54 = mxs_encl_fctoratt(_m,1492,N);
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( mxs_no_strategy_found(_m,1494,EA_l54) ){
						mxv_i321 = mxs_true(_m,0);
						goto L321;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_eq(_m,0,mxs_eval_finegroup(_m,1496,FD_l53),mxs_eval_finegroup(_m,1496,EA_l54))) ){
						mxv_i324 = mxs_false(_m,0);
						goto L324;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_eq(_m,0,mxs_eval_aftbef(_m,1497,FD_l53),mxs_eval_aftbef(_m,1497,EA_l54))) ){
						mxv_i326 = mxs_false(_m,0);
						goto L326;
					}
				{  /* FormulaCaseList */
					if( mxs_maybe_same_node(_m,1497,mxs_appl_order(_m,1497,N)) ){
						mxv_i327 = mxs_true(_m,0);
						goto L327;
					}
					mxv_i327 = mxs_false(_m,0);
					L327: ;
				}
					mxv_i326 = mxv_i327;
					L326: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i326) ){
						mxv_i325 = mxs_true(_m,0);
						goto L325;
					}
					mxv_i325 = mxs_false(_m,0);
					L325: ;
				}
					mxv_i324 = mxv_i325;
					L324: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i324) ){
						mxv_i323 = mxs_true(_m,0);
						goto L323;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1499,EA_l54,_FctOrAtt_)) ){
						mxv_i329 = mxs_false(_m,0);
						goto L329;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1499,FD_l53,_Function_)) ){
						mxv_i331 = mxs_false(_m,0);
						goto L331;
					}
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,mxs_eval_group(_m,1500,EA_l54),mxs_eval_group(_m,1500,FD_l53)) ){
						mxv_i332 = mxs_true(_m,0);
						goto L332;
					}
					mxv_i332 = mxs_false(_m,0);
					L332: ;
				}
					mxv_i331 = mxv_i332;
					L331: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i331) ){
						mxv_i330 = mxs_true(_m,0);
						goto L330;
					}
					mxv_i330 = mxs_false(_m,0);
					L330: ;
				}
					mxv_i329 = mxv_i330;
					L329: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i329) ){
						mxv_i328 = mxs_true(_m,0);
						goto L328;
					}
					mxv_i328 = mxs_false(_m,0);
					L328: ;
				}
					mxv_i323 = mxv_i328;
					L323: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i323) ){
						mxv_i322 = mxs_true(_m,0);
						goto L322;
					}
					mxv_i322 = mxs_false(_m,0);
					L322: ;
				}
					mxv_i321 = mxv_i322;
					L321: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i321) ){
						mxv_i320 = mxs_true(_m,1502);
						goto L320;
					}
					mxv_i320 = mxs_false(_m,1502);
					L320: ;
				}
				mxv_l54 = mxv_i320;
			}
			mxv_l53 = mxv_l54;
		}
			mxv_i319 = mxv_l53;
			goto L319;
		}
		mxv_i319 = mxs_false(_m,1503);
		L319: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FuncAppl_);
	mxa_maybe_wait[ mxv_ax ] = mxv_i319;
}

static  void  mxe_cgen_name( ELEMENT N, ELEMENT mxv_attvalue, int state, ELEMENT *mxv_waitpar ){
	ELEMENT  mxv_i335, L_p324, I_p326, P_p327, I_p329, mxv_a1589, mxv_i334, mxv_i333,
		mxv_ax, mxv_res, mxv_par = N;
	AttInstSq mxv_waitsq, mxv_wsq;

	switch(state) {
		case 1589 :
			mxv_a1589 = mxv_attvalue;
			goto Lz1589;
	}
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Name_) ) goto Lp88;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,N,mxs_bind_pos(_m,1520,N)) ){
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = N;
					mxv_IR = mxv_anchor;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp89;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp89;
					L_p324 = mxs_fath(_c,0,mxv_anchor);
					mxv_IR = L_p324;
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp89;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp89;
					if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp89;
					I_p326 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = I_p326;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp89;
					mxv_i335 = mxi_string_conc(_m,1521,3,mxs_id(_m,1521,I_p326),mxs_atoe(_c,0,"_l"),mxs_aux_itoa(_m,1521,mxs_index(_m,1521,L_p324,_LetExpr_)));
					goto L335;
				}
				Lp89: ;
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = N;
					mxv_IR = mxv_anchor;
					if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp90;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp90;
					P_p327 = mxs_fath(_c,0,mxv_anchor);
					mxv_IR = P_p327;
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp90;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp90;
					if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp90;
					I_p329 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = I_p329;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp90;
					mxv_i335 = mxi_string_conc(_m,1522,3,mxs_id(_m,1522,I_p329),mxs_atoe(_c,0,"_p"),mxs_aux_itoa(_m,1522,mxs_index(_m,1522,P_p327,_Pattern_)));
					goto L335;
				}
				Lp90: ;
					mxv_i335 = mxs_id(_m,1523,mxs_son(_m,1523,mxs_itoe(_c,0,1),N));
				L335: ;
			}
				mxv_i334 = mxv_i335;
				goto L334;
			}
		{  /* Attribute access */
			mxv_ax = mxs_bind_pos(_m,1524,N);
			mxv_a1589 = mxs_cgen_name(_m,1524,mxv_ax);
			if( mxv_a1589==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_cgen_name,mxv_par,1589,mxw_cgen_name,mxs_index(_c,0,mxv_ax,_IntResOrName_));
				return;
			}
			Lz1589:;
		}
			mxv_i334 = mxv_a1589;
			L334: ;
		}
			mxv_i333 = mxv_i334;
			goto L333;
		}
		Lp88: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp91;
			mxv_i333 = mxi_string_conc(_m,1525,2,mxs_atoe(_c,0,"mxv_a"),mxs_aux_itoa(_m,1525,mxs_index(_m,1525,N,_FuncAppl_)));
			goto L333;
		}
		Lp91: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp92;
			mxv_i333 = mxi_string_conc(_m,1526,2,mxs_atoe(_c,0,"mxv_l"),mxs_aux_itoa(_m,1526,mxs_index(_m,1526,N,_LetExpr_)));
			goto L333;
		}
		Lp92: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp93;
			mxv_i333 = mxi_string_conc(_m,1527,2,mxs_atoe(_c,0,"mxv_i"),mxs_aux_itoa(_m,1527,mxs_index(_m,1527,N,_IfExpr_)));
			goto L333;
		}
		Lp93: ;
			mxv_i333 = mxs_nil(_m,1528);
		L333: ;
	}
	mxv_ax = mxs_index(_c,0,N,_IntResOrName_);
	mxv_res = mxa_cgen_name[ mxv_ax ] = mxv_i333;

	/* Code for propagation */
	mxv_waitsq = mxw_cgen_name[ mxv_ax ];
	mxw_cgen_name[ mxv_ax ] = NULL;
	while( mxv_waitsq != NULL ){
		(*(mxv_waitsq->attevalfct))(mxv_waitsq->attnode, mxv_res, mxv_waitsq->state, &mxv_waitsq->intres_array[0]);
		mxv_wsq    = mxv_waitsq;
		mxv_waitsq = mxv_waitsq->rest;
		free(mxv_wsq);
	}
}

static  void  mxe_sces_appl( ELEMENT A ){
	ELEMENT 
		mxv_ax, mxv_par = A;
	mxv_ax = mxs_index(_c,0,A,_ApplyEntity_);
	mxa_sces_appl[ mxv_ax ] = mxs_intresexprs(_m,1547,mxs_son(_m,1547,mxs_itoe(_c,0,-1),A));
}

static  void  mxe_sces1_cond( ELEMENT C ){
	ELEMENT 
		mxv_ax, mxv_par = C;
	mxv_ax = mxs_index(_c,0,C,_Condition_);
	mxa_sces1_cond[ mxv_ax ] = mxs_intresexprs(_m,1548,mxs_son(_m,1548,mxs_itoe(_c,0,2),C));
}

static  void  mxe_sces2_cond( ELEMENT C ){
	ELEMENT 
		mxv_ax, mxv_par = C;
	mxv_ax = mxs_index(_c,0,C,_Condition_);
	mxa_sces2_cond[ mxv_ax ] = mxs_intresexprs(_m,1549,mxs_son(_m,1549,mxs_itoe(_c,0,3),C));
}

static  void  mxe_sces1_let( ELEMENT L ){
	ELEMENT 
		mxv_ax, mxv_par = L;
	mxv_ax = mxs_index(_c,0,L,_LetExpr_);
	mxa_sces1_let[ mxv_ax ] = mxs_intresexprs(_m,1550,mxs_son(_m,1550,mxs_itoe(_c,0,2),L));
}

static  void  mxe_sces2_let( ELEMENT L ){
	ELEMENT 
		mxv_ax, mxv_par = L;
	mxv_ax = mxs_index(_c,0,L,_LetExpr_);
	mxa_sces2_let[ mxv_ax ] = mxs_intresexprs(_m,1551,mxs_son(_m,1551,mxs_itoe(_c,0,3),L));
}

static  void  mxe_sces_if( ELEMENT I ){
	ELEMENT 
		mxv_ax, mxv_par = I;
	mxv_ax = mxs_index(_c,0,I,_IfExpr_);
	mxa_sces_if[ mxv_ax ] = mxs_intresexprs(_m,1552,mxs_son(_m,1552,mxs_itoe(_c,0,2),I));
}

static  void  mxe_sces1_fcase( ELEMENT F ){
	ELEMENT 
		mxv_ax, mxv_par = F;
	mxv_ax = mxs_index(_c,0,F,_FormulaCase_);
	mxa_sces1_fcase[ mxv_ax ] = mxs_intresexprs(_m,1553,mxs_son(_m,1553,mxs_itoe(_c,0,1),F));
}

static  void  mxe_sces2_fcase( ELEMENT F ){
	ELEMENT 
		mxv_ax, mxv_par = F;
	mxv_ax = mxs_index(_c,0,F,_FormulaCase_);
	mxa_sces2_fcase[ mxv_ax ] = mxs_intresexprs(_m,1554,mxs_son(_m,1554,mxs_itoe(_c,0,2),F));
}

static  void  mxe_sces_pcase( ELEMENT P ){
	ELEMENT 
		mxv_ax, mxv_par = P;
	mxv_ax = mxs_index(_c,0,P,_PatternCase_);
	mxa_sces_pcase[ mxv_ax ] = mxs_intresexprs(_m,1555,mxs_son(_m,1555,mxs_itoe(_c,0,2),P));
}

static  void  mxe_sces_attacc( ELEMENT FA ){
	ELEMENT  mxv_i350,
		mxv_ax, mxv_par = FA;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_maybe_wait(_m,1557,FA),mxs_true(_m,1557)) ){
			mxv_i350 = mxs_intresexprs(_m,1557,mxs_son(_m,1557,mxs_itoe(_c,0,2),FA));
			goto L350;
		}
		mxv_i350 = mxs_nil(_m,1557);
		L350: ;
	}
	mxv_ax = mxs_index(_c,0,FA,_FuncAppl_);
	mxa_sces_attacc[ mxv_ax ] = mxv_i350;
}

static  void  mxe_lokvar_need( ELEMENT N ){
	ELEMENT 
		mxv_ax, mxv_par = N;
	mxv_ax = mxs_index(_c,0,N,_FctOrAtt_);
	mxa_lokvar_need[ mxv_ax ] = mxs_aux_var_need(_m,1604,mxs_add(_m,1604,mxs_index(_m,1604,mxs_son(_m,1604,mxs_itoe(_c,0,1),mxs_son(_m,1604,mxs_itoe(_c,0,3),N)),_Name_),mxs_itoe(_c,0,1)),N);
}

static  void  mxe_intres_collect( ELEMENT N ){
	ELEMENT  mxv_i368, mxv_i367, mxv_i369, X_p358, X_p363, mxv_i370, mxv_i371, V_p367, X_p369, mxv_l60, LCP_l60, mxv_l59, EIR_l59, mxv_l58, RCL_l58, mxv_l57, PIR_l57, mxv_i366, mxv_i365,
		mxv_ax, mxv_par = N;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp104;
			mxv_i365 = mxs_IntResList(_m,1609);
			goto L365;
		}
		Lp104: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Predicate_) ) goto Lp105;
			mxv_i365 = mxs_nil(_m,1610);
			goto L365;
		}
		Lp105: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp106;
			mxv_i365 = mxs_nil(_m,1611);
			goto L365;
		}
		Lp106: ;
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1612,N,_FuncAppl_)) ){
			mxv_i367 = mxs_false(_m,0);
			goto L367;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_maybe_wait(_m,1612,N),mxs_false(_m,1612)) ){
			mxv_i368 = mxs_true(_m,0);
			goto L368;
		}
		mxv_i368 = mxs_false(_m,0);
		L368: ;
	}
		mxv_i367 = mxv_i368;
		L367: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i367) ){
			mxv_i366 = mxs_nil(_m,1612);
			goto L366;
		}
	{  /* LetExpr */
		PIR_l57 = mxs_encl_part_intres(_m,1614,N);
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = PIR_l57;
					mxv_IR = mxv_anchor;
					if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp107;
					mxv_IR = mxs_fath(_c,0,mxv_anchor);
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp107;
					if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp107;
					if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp107;
					X_p358 = mxs_rbroth(_c,0,mxv_anchor);
					mxv_IR = X_p358;
					if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp107;
					mxv_i369 = X_p358;
					goto L369;
				}
				Lp107: ;
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = PIR_l57;
					mxv_IR = mxv_anchor;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp108;
					mxv_IR = mxs_fath(_c,0,mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor)));
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp108;
					if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp108;
					if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp108;
					mxv_IR = mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor));
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp108;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp108;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp108;
					mxv_IR = mxs_fath(_c,0,mxv_anchor);
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp108;
					if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR))) ) goto Lp108;
					if( mxs_before(_c,0,mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp108;
					if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp108;
					if( !mxs_is(_c,0,mxv_IR,_FormulaCase_) ) goto Lp108;
					X_p363 = mxs_rbroth(_c,0,mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor)));
					mxv_IR = X_p363;
					if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp108;
					mxv_i369 = X_p363;
					goto L369;
				}
				Lp108: ;
					mxv_i369 = PIR_l57;
				L369: ;
			}
			RCL_l58 = mxv_i369;
			{  /* LetExpr */
				{  /* PatternCaseList */
					{
						ELEMENT mxv_anchor, mxv_IR;
						mxv_anchor = RCL_l58;
						mxv_IR = mxv_anchor;
						if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp109;
						mxv_IR = mxs_fath(_c,0,mxv_anchor);
						if( mxv_IR == mxs_nil(_c,0) ) goto Lp109;
						if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp109;
						if( !mxs_is(_c,0,mxv_IR,_Case_) ) goto Lp109;
						mxv_i370 = mxs_fath(_m,1621,mxs_fath(_m,1621,mxs_fath(_m,1621,RCL_l58)));
						goto L370;
					}
					Lp109: ;
						mxv_i370 = mxs_fath(_m,1622,RCL_l58);
					L370: ;
				}
				EIR_l59 = mxv_i370;
				{  /* LetExpr */
					{  /* PatternCaseList */
						{
							ELEMENT mxv_anchor, mxv_IR;
							mxv_anchor = PIR_l57;
							mxv_IR = mxv_anchor;
							if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp110;
							mxv_IR = mxs_fath(_c,0,mxv_anchor);
							if( mxv_IR == mxs_nil(_c,0) ) goto Lp110;
							if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp110;
							if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp110;
							V_p367 = mxs_lbroth(_c,0,mxv_anchor);
							mxv_IR = V_p367;
							if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp110;
							X_p369 = mxs_rbroth(_c,0,mxv_anchor);
							mxv_IR = X_p369;
							if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp110;
							mxv_i371 = mxs_before(_m,1624,V_p367);
							goto L371;
						}
						Lp110: ;
							mxv_i371 = mxs_before(_m,1625,N);
						L371: ;
					}
					LCP_l60 = mxv_i371;
					mxv_l60 = mxs_intres_union(_m,1627,mxs_aux_intres_left(_m,1628,N,mxs_itoe(_c,0,1),mxs_intresexprs(_m,1628,PIR_l57)),mxs_intres_collect(_m,1629,EIR_l59),mxs_aux_intres_right(_m,1630,LCP_l60,mxs_after(_m,1630,N),mxs_after(_m,1630,RCL_l58),mxs_lokvar_need(_m,1630,mxs_encl_fctoratt(_m,1630,EIR_l59)),mxs_itoe(_c,0,1)));
				}
				mxv_l59 = mxv_l60;
			}
			mxv_l58 = mxv_l59;
		}
		mxv_l57 = mxv_l58;
	}
		mxv_i366 = mxv_l57;
		L366: ;
	}
			mxv_i365 = mxv_i366;
		L365: ;
	}
	mxv_ax = mxs_index(_c,0,N,_IntResExpr_);
	mxa_intres_collect[ mxv_ax ] = mxv_i365;
}



static  long  mxc_1( void ){
	ELEMENT  mxv_c2, N_p2, mxv_c0 = 1L;
	long mxv_cix2,mxv_cbd2;
	mxv_cbd2 = mxs_number(_c,0,_DynUndef_);
	for(mxv_cix2=1;mxv_cix2<=mxv_cbd2;mxv_cix2++){
		mxv_c2 = mxs_element(_c,0,mxv_cix2,_DynUndef_);
		N_p2 = mxv_c2;
		if( !(  ( ! mxs_eq(_m,0,mxs_encl_dynfunc(_m,305,N_p2),mxs_nil(_m,305))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,305,1,mxs_atoe(_c,0,"***** ?? only allowed in dynamic functions\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_2( void ){
	ELEMENT  mxv_c10, ID_p10, mxv_c11, L_p11, mxv_c12, C_p12, mxv_c13, F_p13, mxv_c9, mxv_i15, mxv_i14, mxv_i13, mxv_i12, mxv_i11, mxv_i10, mxv_c0 = 1L;
	long mxv_cix9,mxv_cbd9;
	mxv_cbd9 = mxs_number(_c,0,_NodeSortId_);
	for(mxv_cix9=1;mxv_cix9<=mxv_cbd9;mxv_cix9++){
		mxv_c9 = mxs_element(_c,0,mxv_cix9,_NodeSortId_);
		if( mxs_numsons(_c,0,mxv_c9)!=4 ) continue;
		mxv_c13 = mxs_son(_c,0,-1,mxv_c9);
		mxv_c12 = mxs_lbroth(_c,0,mxv_c13);
		mxv_c11 = mxs_lbroth(_c,0,mxv_c12);
		mxv_c10 = mxs_lbroth(_c,0,mxv_c11);
		F_p13 = mxv_c13;
		C_p12 = mxv_c12;
		L_p11 = mxv_c11;
		ID_p10 = mxv_c10;
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,mxs_id(_m,330,ID_p10),mxs_atoe(_c,0,"Node")))) ){
			mxv_i10 = mxs_false(_m,0);
			goto L10;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,mxs_id(_m,330,ID_p10),mxs_atoe(_c,0,"Point")))) ){
			mxv_i12 = mxs_false(_m,0);
			goto L12;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,mxs_id(_m,331,ID_p10),mxs_atoe(_c,0,"Term")))) ){
			mxv_i14 = mxs_false(_m,0);
			goto L14;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_id(_m,331,ID_p10),mxs_atoe(_c,0,"nil"))) ){
			mxv_i15 = mxs_true(_m,0);
			goto L15;
		}
		mxv_i15 = mxs_false(_m,0);
		L15: ;
	}
		mxv_i14 = mxv_i15;
		L14: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i14) ){
			mxv_i13 = mxs_true(_m,0);
			goto L13;
		}
		mxv_i13 = mxs_false(_m,0);
		L13: ;
	}
		mxv_i12 = mxv_i13;
		L12: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i12) ){
			mxv_i11 = mxs_true(_m,0);
			goto L11;
		}
		mxv_i11 = mxs_false(_m,0);
		L11: ;
	}
		mxv_i10 = mxv_i11;
		L10: ;
	}
		if( !(  mxs_eq(_m,0,mxs_true(_m,0),mxv_i10) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,331,10,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,332,F_p13),mxs_atoe(_c,0,", Line "),mxs_s(_m,332,L_p11),mxs_atoe(_c,0,", Column "),mxs_s(_m,332,C_p12),mxs_atoe(_c,0,": \""),mxs_id(_m,332,ID_p10),mxs_atoe(_c,0,"\" not allowed with\n"),mxs_atoe(_c,0,"       node symbol @ \n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_3( void ){
	ELEMENT  mxv_c15, ID_p15, mxv_c16, L_p16, mxv_c17, C_p17, mxv_c18, F_p18, mxv_c14, mxv_i16, mxv_c0 = 1L;
	long mxv_cix14,mxv_cbd14;
	mxv_cbd14 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix14=1;mxv_cix14<=mxv_cbd14;mxv_cix14++){
		mxv_c14 = mxs_element(_c,0,mxv_cix14,_UsedId_);
		if( mxs_numsons(_c,0,mxv_c14)!=4 ) continue;
		mxv_c18 = mxs_son(_c,0,-1,mxv_c14);
		mxv_c17 = mxs_lbroth(_c,0,mxv_c18);
		mxv_c16 = mxs_lbroth(_c,0,mxv_c17);
		mxv_c15 = mxs_lbroth(_c,0,mxv_c16);
		F_p18 = mxv_c18;
		C_p17 = mxv_c17;
		L_p16 = mxv_c16;
		ID_p15 = mxv_c15;
		if( !(  mxs_eq(_m,0,mxs_numsubterms(_m,340,mxs_idtodecls(_m,340,mxs_term(_m,340,ID_p15))),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,341,mxs_idtodecls(_m,341,mxs_term(_m,341,ID_p15))),mxs_itoe(_c,0,0)) ){
				mxv_i16 = mxi_string_conc(_m,341,10,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,342,F_p18),mxs_atoe(_c,0,", Line "),mxs_s(_m,342,L_p16),mxs_atoe(_c,0,", Column "),mxs_s(_m,342,C_p17),mxs_atoe(_c,0,":"),mxs_atoe(_c,0,"  identifier \""),mxs_id(_m,343,ID_p15),mxs_atoe(_c,0,"\" not declared\n"));
				goto L16;
			}
			mxv_i16 = mxs_atoe(_c,0,"");
			L16: ;
		}
			mxv_errstr =  mxv_i16;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_4( void ){
	ELEMENT  mxv_c20, ID_p20, mxv_c21, L_p21, mxv_c22, C_p22, mxv_c23, F_p23, mxv_c19, mxv_i17, mxv_c0 = 1L;
	long mxv_cix19,mxv_cbd19;
	mxv_cbd19 = mxs_number(_c,0,_DefId_);
	for(mxv_cix19=1;mxv_cix19<=mxv_cbd19;mxv_cix19++){
		mxv_c19 = mxs_element(_c,0,mxv_cix19,_DefId_);
		if( mxs_numsons(_c,0,mxv_c19)!=4 ) continue;
		mxv_c23 = mxs_son(_c,0,-1,mxv_c19);
		mxv_c22 = mxs_lbroth(_c,0,mxv_c23);
		mxv_c21 = mxs_lbroth(_c,0,mxv_c22);
		mxv_c20 = mxs_lbroth(_c,0,mxv_c21);
		F_p23 = mxv_c23;
		C_p22 = mxv_c22;
		L_p21 = mxv_c21;
		ID_p20 = mxv_c20;
		if( !(  mxs_eq(_m,0,mxs_numsubterms(_m,346,mxs_idtodecls(_m,346,mxs_term(_m,346,ID_p20))),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,mxs_numsubterms(_m,347,mxs_idtodecls(_m,347,mxs_term(_m,347,ID_p20))),mxs_itoe(_c,0,1))) ){
				mxv_i17 = mxi_string_conc(_m,347,10,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,348,F_p23),mxs_atoe(_c,0,", Line "),mxs_s(_m,348,L_p21),mxs_atoe(_c,0,", Column "),mxs_s(_m,348,C_p22),mxs_atoe(_c,0,":"),mxs_atoe(_c,0,"  identifier \""),mxs_id(_m,349,ID_p20),mxs_atoe(_c,0,"\" multiple declared\n"));
				goto L17;
			}
			mxv_i17 = mxs_atoe(_c,0,"");
			L17: ;
		}
			mxv_errstr =  mxv_i17;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_5( void ){
	ELEMENT  mxv_c34, ID_p34, mxv_c35, L_p35, mxv_c36, C_p36, mxv_c37, F_p37, mxv_c33, mxv_c39, S_p39, mxv_c38, mxv_c32, mxv_c0 = 1L;
	long mxv_cix32,mxv_cbd32;
	mxv_cbd32 = mxs_number(_c,0,_ClassProd_);
	for(mxv_cix32=1;mxv_cix32<=mxv_cbd32;mxv_cix32++){
		mxv_c32 = mxs_element(_c,0,mxv_cix32,_ClassProd_);
		if( mxs_numsons(_c,0,mxv_c32)!=2 ) continue;
		mxv_c38 = mxs_son(_c,0,-1,mxv_c32);
		mxv_c33 = mxs_lbroth(_c,0,mxv_c38);
		if( mxs_numsons(_c,0,mxv_c38) < 1 ) continue;
		mxv_c39 = mxs_son(_c,0,1,mxv_c38);
		S_p39 = mxv_c39;
		if( mxs_numsons(_c,0,mxv_c33)!=4 ) continue;
		mxv_c37 = mxs_son(_c,0,-1,mxv_c33);
		mxv_c36 = mxs_lbroth(_c,0,mxv_c37);
		mxv_c35 = mxs_lbroth(_c,0,mxv_c36);
		mxv_c34 = mxs_lbroth(_c,0,mxv_c35);
		F_p37 = mxv_c37;
		C_p36 = mxv_c36;
		L_p35 = mxv_c35;
		ID_p34 = mxv_c34;
		if( !(  ( ! mxs_eq(_m,0,mxs_term_basesorts(_m,370,S_p39),mxs_nil(_m,370))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,370,9,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,371,F_p37),mxs_atoe(_c,0,", Line "),mxs_s(_m,371,L_p35),mxs_atoe(_c,0,", Column "),mxs_s(_m,371,C_p36),mxs_atoe(_c,0,": class \""),mxs_id(_m,371,ID_p34),mxs_atoe(_c,0,"\" is circular\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_6( void ){
	ELEMENT  mxv_c49, ID_p49, mxv_c50, L_p50, mxv_c51, C_p51, mxv_c52, F_p52, mxv_c48, UID_p48, mxv_c0 = 1L;
	long mxv_cix48,mxv_cbd48;
	mxv_cbd48 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix48=1;mxv_cix48<=mxv_cbd48;mxv_cix48++){
		mxv_c48 = mxs_element(_c,0,mxv_cix48,_UsedId_);
		UID_p48 = mxv_c48;
		if( mxs_numsons(_c,0,mxv_c48)!=4 ) continue;
		mxv_c52 = mxs_son(_c,0,-1,mxv_c48);
		mxv_c51 = mxs_lbroth(_c,0,mxv_c52);
		mxv_c50 = mxs_lbroth(_c,0,mxv_c51);
		mxv_c49 = mxs_lbroth(_c,0,mxv_c50);
		F_p52 = mxv_c52;
		C_p51 = mxv_c51;
		L_p50 = mxv_c50;
		ID_p49 = mxv_c49;
		if( !(  ( ! mxs_is(_m,395,mxs_fath(_m,395,mxs_decl(_m,395,UID_p48)),_Declaration_)||mxs_in(_m,396,UID_p48,mxs_after(_m,396,mxs_fath(_m,396,mxs_decl(_m,396,UID_p48))),mxs_after(_m,396,mxs_root(_m,396)))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,396,16,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,397,F_p52),mxs_atoe(_c,0,", Line "),mxs_s(_m,397,L_p50),mxs_atoe(_c,0,", Column "),mxs_s(_m,397,C_p51),mxs_atoe(_c,0,": \""),mxs_id(_m,397,ID_p49),mxs_atoe(_c,0,"\" used outside scope\n"),mxs_atoe(_c,0,"       Declaration is File "),mxs_ss(_m,398,mxs_son(_m,398,mxs_itoe(_c,0,4),mxs_decl(_m,398,UID_p48))),mxs_atoe(_c,0,", Line "),mxs_s(_m,398,mxs_son(_m,398,mxs_itoe(_c,0,2),mxs_decl(_m,398,UID_p48))),mxs_atoe(_c,0,", Column "),mxs_s(_m,399,mxs_son(_m,399,mxs_itoe(_c,0,3),mxs_decl(_m,399,UID_p48))),mxs_atoe(_c,0,"\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_7( void ){
	ELEMENT  mxv_c54, ID_p54, mxv_c55, L_p55, mxv_c56, C_p56, mxv_c57, F_p57, mxv_c53, UID_p53, mxv_c0 = 1L;
	long mxv_cix53,mxv_cbd53;
	mxv_cbd53 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix53=1;mxv_cix53<=mxv_cbd53;mxv_cix53++){
		mxv_c53 = mxs_element(_c,0,mxv_cix53,_UsedId_);
		UID_p53 = mxv_c53;
		if( mxs_numsons(_c,0,mxv_c53)!=4 ) continue;
		mxv_c57 = mxs_son(_c,0,-1,mxv_c53);
		mxv_c56 = mxs_lbroth(_c,0,mxv_c57);
		mxv_c55 = mxs_lbroth(_c,0,mxv_c56);
		mxv_c54 = mxs_lbroth(_c,0,mxv_c55);
		F_p57 = mxv_c57;
		C_p56 = mxv_c56;
		L_p55 = mxv_c55;
		ID_p54 = mxv_c54;
		if( !(  ( ! mxs_is(_m,402,mxs_fath(_m,402,mxs_decl(_m,402,UID_p53)),_Definition_)||mxs_in(_m,403,UID_p53,mxs_before(_m,403,mxs_fath(_m,403,mxs_fath(_m,403,mxs_decl(_m,403,UID_p53)))),mxs_after(_m,403,mxs_root(_m,403)))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,403,16,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,404,F_p57),mxs_atoe(_c,0,", Line "),mxs_s(_m,404,L_p55),mxs_atoe(_c,0,", Column "),mxs_s(_m,404,C_p56),mxs_atoe(_c,0,": \""),mxs_id(_m,404,ID_p54),mxs_atoe(_c,0,"\" used outside scope\n"),mxs_atoe(_c,0,"       Declaration is File "),mxs_ss(_m,405,mxs_son(_m,405,mxs_itoe(_c,0,4),mxs_decl(_m,405,UID_p53))),mxs_atoe(_c,0,", Line "),mxs_s(_m,405,mxs_son(_m,405,mxs_itoe(_c,0,2),mxs_decl(_m,405,UID_p53))),mxs_atoe(_c,0,", Column "),mxs_s(_m,406,mxs_son(_m,406,mxs_itoe(_c,0,3),mxs_decl(_m,406,UID_p53))),mxs_atoe(_c,0,"\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_8( void ){
	ELEMENT  mxv_c59, ID_p59, mxv_c60, L_p60, mxv_c61, C_p61, mxv_c62, F_p62, mxv_c58, UID_p58, mxv_c0 = 1L;
	long mxv_cix58,mxv_cbd58;
	mxv_cbd58 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix58=1;mxv_cix58<=mxv_cbd58;mxv_cix58++){
		mxv_c58 = mxs_element(_c,0,mxv_cix58,_UsedId_);
		UID_p58 = mxv_c58;
		if( mxs_numsons(_c,0,mxv_c58)!=4 ) continue;
		mxv_c62 = mxs_son(_c,0,-1,mxv_c58);
		mxv_c61 = mxs_lbroth(_c,0,mxv_c62);
		mxv_c60 = mxs_lbroth(_c,0,mxv_c61);
		mxv_c59 = mxs_lbroth(_c,0,mxv_c60);
		F_p62 = mxv_c62;
		C_p61 = mxv_c61;
		L_p60 = mxv_c60;
		ID_p59 = mxv_c59;
		if( !(  ( ! mxs_is(_m,410,mxs_fath(_m,410,mxs_decl(_m,410,UID_p58)),_DynFunc_)||mxs_in(_m,411,UID_p58,mxs_after(_m,411,mxs_fath(_m,411,mxs_fath(_m,411,mxs_fath(_m,411,mxs_decl(_m,411,UID_p58))))),mxs_after(_m,411,mxs_root(_m,411)))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,411,16,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,412,F_p62),mxs_atoe(_c,0,", Line "),mxs_s(_m,412,L_p60),mxs_atoe(_c,0,", Column "),mxs_s(_m,412,C_p61),mxs_atoe(_c,0,": \""),mxs_id(_m,412,ID_p59),mxs_atoe(_c,0,"\" used outside scope\n"),mxs_atoe(_c,0,"       Declaration is File "),mxs_ss(_m,413,mxs_son(_m,413,mxs_itoe(_c,0,4),mxs_decl(_m,413,UID_p58))),mxs_atoe(_c,0,", Line "),mxs_s(_m,413,mxs_son(_m,413,mxs_itoe(_c,0,2),mxs_decl(_m,413,UID_p58))),mxs_atoe(_c,0,", Column "),mxs_s(_m,414,mxs_son(_m,414,mxs_itoe(_c,0,3),mxs_decl(_m,414,UID_p58))),mxs_atoe(_c,0,"\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_9( void ){
	ELEMENT  mxv_c64, ID_p64, mxv_c65, L_p65, mxv_c66, C_p66, mxv_c67, F_p67, mxv_c63, UID_p63, mxv_c0 = 1L;
	long mxv_cix63,mxv_cbd63;
	mxv_cbd63 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix63=1;mxv_cix63<=mxv_cbd63;mxv_cix63++){
		mxv_c63 = mxs_element(_c,0,mxv_cix63,_UsedId_);
		UID_p63 = mxv_c63;
		if( mxs_numsons(_c,0,mxv_c63)!=4 ) continue;
		mxv_c67 = mxs_son(_c,0,-1,mxv_c63);
		mxv_c66 = mxs_lbroth(_c,0,mxv_c67);
		mxv_c65 = mxs_lbroth(_c,0,mxv_c66);
		mxv_c64 = mxs_lbroth(_c,0,mxv_c65);
		F_p67 = mxv_c67;
		C_p66 = mxv_c66;
		L_p65 = mxv_c65;
		ID_p64 = mxv_c64;
		if( !(  ( ! mxs_is(_m,416,mxs_fath(_m,416,mxs_decl(_m,416,UID_p63)),_DynSemInput_)||mxs_in(_m,417,UID_p63,mxs_after(_m,417,mxs_fath(_m,417,mxs_fath(_m,417,mxs_fath(_m,417,mxs_decl(_m,417,UID_p63))))),mxs_after(_m,417,mxs_root(_m,417)))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,417,16,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,418,F_p67),mxs_atoe(_c,0,", Line "),mxs_s(_m,418,L_p65),mxs_atoe(_c,0,", Column "),mxs_s(_m,418,C_p66),mxs_atoe(_c,0,": \""),mxs_id(_m,418,ID_p64),mxs_atoe(_c,0,"\" used outside scope\n"),mxs_atoe(_c,0,"       Declaration is File "),mxs_ss(_m,419,mxs_son(_m,419,mxs_itoe(_c,0,4),mxs_decl(_m,419,UID_p63))),mxs_atoe(_c,0,", Line "),mxs_s(_m,419,mxs_son(_m,419,mxs_itoe(_c,0,2),mxs_decl(_m,419,UID_p63))),mxs_atoe(_c,0,", Column "),mxs_s(_m,420,mxs_son(_m,420,mxs_itoe(_c,0,3),mxs_decl(_m,420,UID_p63))),mxs_atoe(_c,0,"\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_10( void ){
	ELEMENT  mxv_c71, PID1_p71, mxv_c72, L1_p72, mxv_c73, C1_p73, mxv_c74, F1_p74, mxv_c70, mxv_c76, PID2_p76, mxv_c77, L2_p77, mxv_c78, C2_p78, mxv_c79, F2_p79, mxv_c75, mxv_c69, mxv_c68, mxv_c0 = 1L;
	long mxv_cix68,mxv_cbd68;
	mxv_cbd68 = mxs_number(_c,0,_ApplyEntity_);
	for(mxv_cix68=1;mxv_cix68<=mxv_cbd68;mxv_cix68++){
		mxv_c68 = mxs_element(_c,0,mxv_cix68,_ApplyEntity_);
		if( mxs_numsons(_c,0,mxv_c68) < 3 ) continue;
		mxv_c69 = mxs_son(_c,0,3,mxv_c68);
		if( mxs_numsons(_c,0,mxv_c69) < 2 ) continue;
		mxv_c70 = mxs_son(_c,0,1,mxv_c69);
		mxv_c75 = mxs_rbroth(_c,0,mxv_c70);
		do {
			do {
				if( mxs_numsons(_c,0,mxv_c75)!=4 ) goto CL24;
				mxv_c79 = mxs_son(_c,0,-1,mxv_c75);
				mxv_c78 = mxs_lbroth(_c,0,mxv_c79);
				mxv_c77 = mxs_lbroth(_c,0,mxv_c78);
				mxv_c76 = mxs_lbroth(_c,0,mxv_c77);
				F2_p79 = mxv_c79;
				C2_p78 = mxv_c78;
				L2_p77 = mxv_c77;
				PID2_p76 = mxv_c76;
				if( mxs_numsons(_c,0,mxv_c70)!=4 ) goto CL24;
				mxv_c74 = mxs_son(_c,0,-1,mxv_c70);
				mxv_c73 = mxs_lbroth(_c,0,mxv_c74);
				mxv_c72 = mxs_lbroth(_c,0,mxv_c73);
				mxv_c71 = mxs_lbroth(_c,0,mxv_c72);
				F1_p74 = mxv_c74;
				C1_p73 = mxv_c73;
				L1_p72 = mxv_c72;
				PID1_p71 = mxv_c71;
				if( !(  ( ! mxs_eq(_m,0,mxs_term(_m,424,PID1_p71),mxs_term(_m,424,PID2_p76))) )  ){
					mxv_c0 = 0L;
					mxv_errstr =  mxi_string_conc(_m,424,14,mxs_atoe(_c,0,"*****  File "),F1_p74,mxs_atoe(_c,0,"/"),F2_p79,mxs_atoe(_c,0,", Line "),mxs_s(_m,425,L1_p72),mxs_atoe(_c,0,"/"),mxs_s(_m,425,L2_p77),mxs_atoe(_c,0,", Column "),mxs_s(_m,425,C1_p73),mxs_atoe(_c,0,"/"),mxs_s(_m,425,C2_p78),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"parameters have same identifier\n"));
					fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
				}
				CL24: ;
				mxv_c75 = mxs_rbroth(_c,0,mxv_c75);
			} while( mxv_c75 != mxs_nil(_c,0) );
			mxv_c70 = mxs_rbroth(_c,0,mxv_c70);
			mxv_c75 = mxs_rbroth(_c,0,mxv_c70);
		} while( mxv_c75 != mxs_nil(_c,0) );
	}

	return mxv_c0;
}

static  long  mxc_11( void ){
	ELEMENT  mxv_c82, L_p82, mxv_c83, C_p83, mxv_c84, F_p84, mxv_c81, mxv_c85, PARAML_p85, mxv_c80, mxv_c0 = 1L;
	long mxv_cix80,mxv_cbd80;
	mxv_cbd80 = mxs_number(_c,0,_AttrDecl_);
	for(mxv_cix80=1;mxv_cix80<=mxv_cbd80;mxv_cix80++){
		mxv_c80 = mxs_element(_c,0,mxv_cix80,_AttrDecl_);
		if( mxs_numsons(_c,0,mxv_c80) < 2 ) continue;
		mxv_c81 = mxs_son(_c,0,1,mxv_c80);
		mxv_c85 = mxs_rbroth(_c,0,mxv_c81);
		PARAML_p85 = mxv_c85;
		if( mxs_numsons(_c,0,mxv_c81)!=4 ) continue;
		mxv_c84 = mxs_son(_c,0,-1,mxv_c81);
		mxv_c83 = mxs_lbroth(_c,0,mxv_c84);
		mxv_c82 = mxs_lbroth(_c,0,mxv_c83);
		F_p84 = mxv_c84;
		C_p83 = mxv_c83;
		L_p82 = mxv_c82;
		if( !(  mxs_eq(_m,0,mxs_numsons(_m,429,PARAML_p85),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,429,7,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,430,F_p84),mxs_atoe(_c,0,", Line "),mxs_s(_m,430,L_p82),mxs_atoe(_c,0,", Column "),mxs_s(_m,430,C_p83),mxs_atoe(_c,0,":  attribute must have arity 1\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_12( void ){
	ELEMENT  mxv_c88, L_p88, mxv_c89, C_p89, mxv_c90, F_p90, mxv_c87, mxv_c91, PARAML_p91, mxv_c86, mxv_c0 = 1L;
	long mxv_cix86,mxv_cbd86;
	mxv_cbd86 = mxs_number(_c,0,_Attribute_);
	for(mxv_cix86=1;mxv_cix86<=mxv_cbd86;mxv_cix86++){
		mxv_c86 = mxs_element(_c,0,mxv_cix86,_Attribute_);
		if( mxs_numsons(_c,0,mxv_c86) < 2 ) continue;
		mxv_c87 = mxs_son(_c,0,1,mxv_c86);
		mxv_c91 = mxs_rbroth(_c,0,mxv_c87);
		PARAML_p91 = mxv_c91;
		if( mxs_numsons(_c,0,mxv_c87)!=4 ) continue;
		mxv_c90 = mxs_son(_c,0,-1,mxv_c87);
		mxv_c89 = mxs_lbroth(_c,0,mxv_c90);
		mxv_c88 = mxs_lbroth(_c,0,mxv_c89);
		F_p90 = mxv_c90;
		C_p89 = mxv_c89;
		L_p88 = mxv_c88;
		if( !(  mxs_eq(_m,0,mxs_numsons(_m,433,PARAML_p91),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,433,7,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,434,F_p90),mxs_atoe(_c,0,", Line "),mxs_s(_m,434,L_p88),mxs_atoe(_c,0,", Column "),mxs_s(_m,434,C_p89),mxs_atoe(_c,0,":  attribute must have arity 1\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_13( void ){
	ELEMENT  mxv_c95, ID_p95, mxv_c96, L_p96, mxv_c97, C_p97, mxv_c98, F_p98, mxv_c94, mxv_c93, mxv_c92, mxv_i42, mxv_i41, mxv_i40, mxv_i39, mxv_c0 = 1L;
	long mxv_cix92,mxv_cbd92;
	mxv_cbd92 = mxs_number(_c,0,_Attribute_);
	for(mxv_cix92=1;mxv_cix92<=mxv_cbd92;mxv_cix92++){
		mxv_c92 = mxs_element(_c,0,mxv_cix92,_Attribute_);
		if( mxs_numsons(_c,0,mxv_c92) < 2 ) continue;
		mxv_c93 = mxs_son(_c,0,2,mxv_c92);
		if( mxs_numsons(_c,0,mxv_c93)!=1 ) continue;
		mxv_c94 = mxs_son(_c,0,-1,mxv_c93);
		if( !mxs_is(_c,0,mxv_c94,_TermSortId_) ) continue;
		if( mxs_numsons(_c,0,mxv_c94)!=4 ) continue;
		mxv_c98 = mxs_son(_c,0,-1,mxv_c94);
		mxv_c97 = mxs_lbroth(_c,0,mxv_c98);
		mxv_c96 = mxs_lbroth(_c,0,mxv_c97);
		mxv_c95 = mxs_lbroth(_c,0,mxv_c96);
		F_p98 = mxv_c98;
		C_p97 = mxv_c97;
		L_p96 = mxv_c96;
		ID_p95 = mxv_c95;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,444,ID_p95),mxs_atoe(_c,0,"Node")) ){
			mxv_i39 = mxs_true(_m,0);
			goto L39;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,444,ID_p95),mxs_atoe(_c,0,"Point")) ){
			mxv_i41 = mxs_true(_m,0);
			goto L41;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,444,ID_p95),mxs_atoe(_c,0,"Ident")) ){
			mxv_i42 = mxs_true(_m,0);
			goto L42;
		}
		mxv_i42 = mxs_false(_m,0);
		L42: ;
	}
		mxv_i41 = mxv_i42;
		L41: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i41) ){
			mxv_i40 = mxs_true(_m,0);
			goto L40;
		}
		mxv_i40 = mxs_false(_m,0);
		L40: ;
	}
		mxv_i39 = mxv_i40;
		L39: ;
	}
		if( !(  mxs_eq(_m,0,mxs_true(_m,0),mxv_i39) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,444,7,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,445,F_p98),mxs_atoe(_c,0,", Line "),mxs_s(_m,445,L_p96),mxs_atoe(_c,0,", Column "),mxs_s(_m,445,C_p97),mxs_atoe(_c,0,":  attribute sort not enumerable\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_14( void ){
	ELEMENT  mxv_c101, ID_p101, mxv_c102, L_p102, mxv_c103, C_p103, mxv_c104, F_p104, mxv_c100, FID_p100, mxv_c105, EXPL_p105, mxv_c99, mxv_i48, mxv_i47, mxv_i46, mxv_i45, mxv_i44, mxv_i43, mxv_c0 = 1L;
	long mxv_cix99,mxv_cbd99;
	mxv_cbd99 = mxs_number(_c,0,_FuncAppl_);
	for(mxv_cix99=1;mxv_cix99<=mxv_cbd99;mxv_cix99++){
		mxv_c99 = mxs_element(_c,0,mxv_cix99,_FuncAppl_);
		if( mxs_numsons(_c,0,mxv_c99)!=2 ) continue;
		mxv_c105 = mxs_son(_c,0,-1,mxv_c99);
		mxv_c100 = mxs_lbroth(_c,0,mxv_c105);
		EXPL_p105 = mxv_c105;
		FID_p100 = mxv_c100;
		if( mxs_numsons(_c,0,mxv_c100)!=4 ) continue;
		mxv_c104 = mxs_son(_c,0,-1,mxv_c100);
		mxv_c103 = mxs_lbroth(_c,0,mxv_c104);
		mxv_c102 = mxs_lbroth(_c,0,mxv_c103);
		mxv_c101 = mxs_lbroth(_c,0,mxv_c102);
		F_p104 = mxv_c104;
		C_p103 = mxv_c103;
		L_p102 = mxv_c102;
		ID_p101 = mxv_c101;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_numsons(_m,448,EXPL_p105),mxs_numsons(_m,448,mxs_rbroth(_m,448,mxs_decl(_m,448,FID_p100)))) ){
			mxv_i43 = mxs_true(_m,0);
			goto L43;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_numsons(_m,449,EXPL_p105),mxs_itoe(_c,0,0))) ){
			mxv_i45 = mxs_false(_m,0);
			goto L45;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_is(_m,450,mxs_fath(_m,450,mxs_decl(_m,450,FID_p100)),_ListProd_) ){
			mxv_i47 = mxs_true(_m,0);
			goto L47;
		}
	{  /* FormulaCaseList */
		if( mxs_is(_m,451,mxs_fath(_m,451,mxs_decl(_m,451,FID_p100)),_PredeclProd_) ){
			mxv_i48 = mxs_true(_m,0);
			goto L48;
		}
		mxv_i48 = mxs_false(_m,0);
		L48: ;
	}
		mxv_i47 = mxv_i48;
		L47: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i47) ){
			mxv_i46 = mxs_true(_m,0);
			goto L46;
		}
		mxv_i46 = mxs_false(_m,0);
		L46: ;
	}
		mxv_i45 = mxv_i46;
		L45: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i45) ){
			mxv_i44 = mxs_true(_m,0);
			goto L44;
		}
		mxv_i44 = mxs_false(_m,0);
		L44: ;
	}
		mxv_i43 = mxv_i44;
		L43: ;
	}
		if( !(  mxs_eq(_m,0,mxs_true(_m,0),mxv_i43) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,451,9,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,452,F_p104),mxs_atoe(_c,0,", Line "),mxs_s(_m,452,L_p102),mxs_atoe(_c,0,", Column "),mxs_s(_m,452,C_p103),mxs_atoe(_c,0,": function \""),mxs_id(_m,452,ID_p101),mxs_atoe(_c,0,"\" used with wrong number of params\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_15( void ){
	ELEMENT  mxv_c134, ID_p134, mxv_c135, L_p135, mxv_c136, C_p136, mxv_c137, F_p137, mxv_c133, N_p133, mxv_c132, mxv_i61, mxv_i60, mxv_l8, M_l8, mxv_c0 = 1L;
	long mxv_cix132,mxv_cbd132;
	mxv_cbd132 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix132=1;mxv_cix132<=mxv_cbd132;mxv_cix132++){
		mxv_c132 = mxs_element(_c,0,mxv_cix132,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c132)!=3 ) continue;
		mxv_c133 = mxs_son(_c,0,-1,mxv_c132);
		if( !mxs_is(_c,0,mxv_c133,_Name_) ) continue;
		N_p133 = mxv_c133;
		if( mxs_numsons(_c,0,mxv_c133)!=4 ) continue;
		mxv_c137 = mxs_son(_c,0,-1,mxv_c133);
		mxv_c136 = mxs_lbroth(_c,0,mxv_c137);
		mxv_c135 = mxs_lbroth(_c,0,mxv_c136);
		mxv_c134 = mxs_lbroth(_c,0,mxv_c135);
		F_p137 = mxv_c137;
		C_p136 = mxv_c136;
		L_p135 = mxv_c135;
		ID_p134 = mxv_c134;
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,509,mxs_scope(_m,509,N_p133),_Condition_)) ){
			mxv_i60 = mxs_false(_m,0);
			goto L60;
		}
	{  /* FormulaCaseList */
		if( mxs_desc(_m,509,N_p133,mxs_son(_m,509,mxs_itoe(_c,0,1),mxs_scope(_m,509,N_p133))) ){
			mxv_i61 = mxs_true(_m,0);
			goto L61;
		}
		mxv_i61 = mxs_false(_m,0);
		L61: ;
	}
		mxv_i60 = mxv_i61;
		L60: ;
	}
		if( !(  ( ! mxs_eq(_m,0,mxs_true(_m,0),mxv_i60)||mxs_eq(_m,0,mxs_lookup_cond(_m,510,mxs_term(_m,510,ID_p134),mxs_son(_m,510,mxs_itoe(_c,0,1),mxs_son(_m,510,mxs_itoe(_c,0,1),mxs_scope(_m,510,N_p133)))),N_p133)) )  ){
			mxv_c0 = 0L;
		{  /* LetExpr */
			M_l8 = mxs_lookup_cond(_m,511,mxs_term(_m,511,ID_p134),mxs_son(_m,511,mxs_itoe(_c,0,1),mxs_son(_m,511,mxs_itoe(_c,0,1),mxs_scope(_m,511,N_p133))));
			mxv_l8 = mxi_string_conc(_m,511,14,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,512,F_p137),mxs_atoe(_c,0,", Line "),mxs_s(_m,512,L_p135),mxs_atoe(_c,0,"/"),mxs_s(_m,512,mxs_son(_m,512,mxs_itoe(_c,0,2),M_l8)),mxs_atoe(_c,0,", Column "),mxs_s(_m,512,C_p136),mxs_atoe(_c,0,"/"),mxs_s(_m,512,mxs_son(_m,512,mxs_itoe(_c,0,3),M_l8)),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"multiple binding of identifier \""),mxs_id(_m,513,ID_p134),mxs_atoe(_c,0,"\"\n"));
		}
			mxv_errstr =  mxv_l8;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_16( void ){
	ELEMENT  mxv_c140, ID_p140, mxv_c141, L_p141, mxv_c142, C_p142, mxv_c143, F_p143, mxv_c139, N_p139, mxv_c138, mxv_l9, M_l9, mxv_c0 = 1L;
	long mxv_cix138,mxv_cbd138;
	mxv_cbd138 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix138=1;mxv_cix138<=mxv_cbd138;mxv_cix138++){
		mxv_c138 = mxs_element(_c,0,mxv_cix138,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c138)!=3 ) continue;
		mxv_c139 = mxs_son(_c,0,-1,mxv_c138);
		if( !mxs_is(_c,0,mxv_c139,_Name_) ) continue;
		N_p139 = mxv_c139;
		if( mxs_numsons(_c,0,mxv_c139)!=4 ) continue;
		mxv_c143 = mxs_son(_c,0,-1,mxv_c139);
		mxv_c142 = mxs_lbroth(_c,0,mxv_c143);
		mxv_c141 = mxs_lbroth(_c,0,mxv_c142);
		mxv_c140 = mxs_lbroth(_c,0,mxv_c141);
		F_p143 = mxv_c143;
		C_p142 = mxv_c142;
		L_p141 = mxv_c141;
		ID_p140 = mxv_c140;
		if( !(  ( ! mxs_is(_m,517,mxs_scope(_m,517,N_p139),_PatternCase_)||mxs_eq(_m,0,mxs_lookup_item(_m,518,mxs_term(_m,518,ID_p140),mxs_son(_m,518,mxs_itoe(_c,0,1),mxs_scope(_m,518,N_p139))),N_p139)) )  ){
			mxv_c0 = 0L;
		{  /* LetExpr */
			M_l9 = mxs_lookup_item(_m,519,mxs_term(_m,519,ID_p140),mxs_son(_m,519,mxs_itoe(_c,0,1),mxs_scope(_m,519,N_p139)));
			mxv_l9 = mxi_string_conc(_m,519,14,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,520,F_p143),mxs_atoe(_c,0,", Line "),mxs_s(_m,520,L_p141),mxs_atoe(_c,0,"/"),mxs_s(_m,520,mxs_son(_m,520,mxs_itoe(_c,0,2),M_l9)),mxs_atoe(_c,0,", Column "),mxs_s(_m,520,C_p142),mxs_atoe(_c,0,"/"),mxs_s(_m,520,mxs_son(_m,520,mxs_itoe(_c,0,3),M_l9)),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"multiple binding of identifier \""),mxs_id(_m,521,ID_p140),mxs_atoe(_c,0,"\"\n"));
		}
			mxv_errstr =  mxv_l9;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_17( void ){
	ELEMENT  mxv_c145, ID_p145, mxv_c146, L_p146, mxv_c147, C_p147, mxv_c148, F_p148, mxv_c144, N_p144, mxv_c0 = 1L;
	long mxv_cix144,mxv_cbd144;
	mxv_cbd144 = mxs_number(_c,0,_Name_);
	for(mxv_cix144=1;mxv_cix144<=mxv_cbd144;mxv_cix144++){
		mxv_c144 = mxs_element(_c,0,mxv_cix144,_Name_);
		N_p144 = mxv_c144;
		if( mxs_numsons(_c,0,mxv_c144)!=4 ) continue;
		mxv_c148 = mxs_son(_c,0,-1,mxv_c144);
		mxv_c147 = mxs_lbroth(_c,0,mxv_c148);
		mxv_c146 = mxs_lbroth(_c,0,mxv_c147);
		mxv_c145 = mxs_lbroth(_c,0,mxv_c146);
		F_p148 = mxv_c148;
		C_p147 = mxv_c147;
		L_p146 = mxv_c146;
		ID_p145 = mxv_c145;
		if( !(  ( ! mxs_eq(_m,0,mxs_bind_pos(_m,535,N_p144),mxs_nil(_m,535))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,535,9,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,536,F_p148),mxs_atoe(_c,0,", Line "),mxs_s(_m,536,L_p146),mxs_atoe(_c,0,", Column "),mxs_s(_m,536,C_p147),mxs_atoe(_c,0,": \""),mxs_id(_m,536,ID_p145),mxs_atoe(_c,0,"\" not declared\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_18( void ){
	ELEMENT  mxv_c152, L_p152, mxv_c153, F_p153, mxv_c151, mxv_c150, mxv_c149, mxv_c0 = 1L;
	long mxv_cix149,mxv_cbd149;
	mxv_cbd149 = mxs_number(_c,0,_PatternList_);
	for(mxv_cix149=1;mxv_cix149<=mxv_cbd149;mxv_cix149++){
		mxv_c149 = mxs_element(_c,0,mxv_cix149,_PatternList_);
		if( mxs_numsons(_c,0,mxv_c149) < 1 ) continue;
		mxv_c150 = mxs_son(_c,0,1,mxv_c149);
		do {
			if( mxs_numsons(_c,0,mxv_c150)!=3 ) goto CL54;
			mxv_c151 = mxs_son(_c,0,-3,mxv_c150);
			if( !mxs_is(_c,0,mxv_c151,_Blank_) ) goto CL54;
			if( mxs_numsons(_c,0,mxv_c151)!=2 ) goto CL54;
			mxv_c153 = mxs_son(_c,0,-1,mxv_c151);
			mxv_c152 = mxs_lbroth(_c,0,mxv_c153);
			F_p153 = mxv_c153;
			L_p152 = mxv_c152;
			if( !(  mxs_eq(_m,0,mxs_true(_m,553),mxs_false(_m,553)) )  ){
				mxv_c0 = 0L;
				mxv_errstr =  mxi_string_conc(_m,553,5,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,554,F_p153),mxs_atoe(_c,0,", Line "),mxs_s(_m,554,L_p152),mxs_atoe(_c,0,": outermost pattern may not be omitted\n"));
				fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
			}
			CL54: ;
			mxv_c150 = mxs_rbroth(_c,0,mxv_c150);
		} while( mxv_c150 != mxs_nil(_c,0) );
	}

	return mxv_c0;
}

static  long  mxc_19( void ){
	ELEMENT  mxv_c156, ID_p156, mxv_c157, L_p157, mxv_c158, C_p158, mxv_c159, F_p159, mxv_c155, mxv_c154, mxv_i78, mxv_i77, mxv_i76, mxv_i75, mxv_c0 = 1L;
	long mxv_cix154,mxv_cbd154;
	mxv_cbd154 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix154=1;mxv_cix154<=mxv_cbd154;mxv_cix154++){
		mxv_c154 = mxs_element(_c,0,mxv_cix154,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c154)!=3 ) continue;
		mxv_c155 = mxs_son(_c,0,-3,mxv_c154);
		if( !mxs_is(_c,0,mxv_c155,_TermSortId_) ) continue;
		if( mxs_numsons(_c,0,mxv_c155)!=4 ) continue;
		mxv_c159 = mxs_son(_c,0,-1,mxv_c155);
		mxv_c158 = mxs_lbroth(_c,0,mxv_c159);
		mxv_c157 = mxs_lbroth(_c,0,mxv_c158);
		mxv_c156 = mxs_lbroth(_c,0,mxv_c157);
		F_p159 = mxv_c159;
		C_p158 = mxv_c158;
		L_p157 = mxv_c157;
		ID_p156 = mxv_c156;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,558,ID_p156),mxs_atoe(_c,0,"Node")) ){
			mxv_i75 = mxs_true(_m,0);
			goto L75;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,558,ID_p156),mxs_atoe(_c,0,"Point")) ){
			mxv_i77 = mxs_true(_m,0);
			goto L77;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,558,ID_p156),mxs_atoe(_c,0,"Ident")) ){
			mxv_i78 = mxs_true(_m,0);
			goto L78;
		}
		mxv_i78 = mxs_false(_m,0);
		L78: ;
	}
		mxv_i77 = mxv_i78;
		L77: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i77) ){
			mxv_i76 = mxs_true(_m,0);
			goto L76;
		}
		mxv_i76 = mxs_false(_m,0);
		L76: ;
	}
		mxv_i75 = mxv_i76;
		L75: ;
	}
		if( !(  mxs_eq(_m,0,mxs_true(_m,0),mxv_i75) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,558,7,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,559,F_p159),mxs_atoe(_c,0,", Line "),mxs_s(_m,559,L_p157),mxs_atoe(_c,0,", Column "),mxs_s(_m,559,C_p158),mxs_atoe(_c,0,":  pattern sort must be enumerable\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_20( void ){
	ELEMENT  mxv_c162, ID_p162, mxv_c163, L_p163, mxv_c164, C_p164, mxv_c165, F_p165, mxv_c161, mxv_c166, mxv_c160, mxv_c0 = 1L;
	long mxv_cix160,mxv_cbd160;
	mxv_cbd160 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix160=1;mxv_cix160<=mxv_cbd160;mxv_cix160++){
		mxv_c160 = mxs_element(_c,0,mxv_cix160,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c160)!=3 ) continue;
		mxv_c166 = mxs_son(_c,0,-2,mxv_c160);
		mxv_c161 = mxs_lbroth(_c,0,mxv_c166);
		if( !mxs_is(_c,0,mxv_c166,_ItemList_) ) continue;
		if( !mxs_is(_c,0,mxv_c161,_TermSortId_) ) continue;
		if( mxs_numsons(_c,0,mxv_c161)!=4 ) continue;
		mxv_c165 = mxs_son(_c,0,-1,mxv_c161);
		mxv_c164 = mxs_lbroth(_c,0,mxv_c165);
		mxv_c163 = mxs_lbroth(_c,0,mxv_c164);
		mxv_c162 = mxs_lbroth(_c,0,mxv_c163);
		F_p165 = mxv_c165;
		C_p164 = mxv_c164;
		L_p163 = mxv_c163;
		ID_p162 = mxv_c162;
		if( !(  mxs_eq(_m,0,mxs_id(_m,562,ID_p162),mxs_atoe(_c,0,"Node")) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,562,8,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,563,F_p165),mxs_atoe(_c,0,", Line "),mxs_s(_m,563,L_p163),mxs_atoe(_c,0,", Column "),mxs_s(_m,563,C_p164),mxs_atoe(_c,0,":  no subpattern for ident and point "),mxs_atoe(_c,0,"allowed\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_21( void ){
	ELEMENT  mxv_c169, ID_p169, mxv_c170, L_p170, mxv_c171, C_p171, mxv_c172, F_p172, mxv_c168, UID_p168, mxv_c173, ITL_p173, mxv_c167, mxv_i80, mxv_i79, mxv_c0 = 1L;
	long mxv_cix167,mxv_cbd167;
	mxv_cbd167 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix167=1;mxv_cix167<=mxv_cbd167;mxv_cix167++){
		mxv_c167 = mxs_element(_c,0,mxv_cix167,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c167)!=3 ) continue;
		mxv_c173 = mxs_son(_c,0,-2,mxv_c167);
		mxv_c168 = mxs_lbroth(_c,0,mxv_c173);
		if( !mxs_is(_c,0,mxv_c173,_ItemList_) ) continue;
		ITL_p173 = mxv_c173;
		if( !mxs_is(_c,0,mxv_c168,_NodeSortId_) ) continue;
		UID_p168 = mxv_c168;
		if( mxs_numsons(_c,0,mxv_c168)!=4 ) continue;
		mxv_c172 = mxs_son(_c,0,-1,mxv_c168);
		mxv_c171 = mxs_lbroth(_c,0,mxv_c172);
		mxv_c170 = mxs_lbroth(_c,0,mxv_c171);
		mxv_c169 = mxs_lbroth(_c,0,mxv_c170);
		F_p172 = mxv_c172;
		C_p171 = mxv_c171;
		L_p170 = mxv_c170;
		ID_p169 = mxv_c169;
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,mxs_numberofastrks(_m,570,ITL_p173),mxs_itoe(_c,0,0))||mxs_eq(_m,0,mxs_numsons(_m,571,mxs_son(_m,571,mxs_itoe(_c,0,2),mxs_fath(_m,571,mxs_decl(_m,571,UID_p168)))),mxs_numsons(_m,571,ITL_p173)))) ){
			mxv_i79 = mxs_false(_m,0);
			goto L79;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_lt(_m,572,mxs_itoe(_c,0,0),mxs_numberofastrks(_m,572,ITL_p173))||mxs_le(_m,573,mxs_sub(_m,573,mxs_numsons(_m,573,ITL_p173),mxs_numberofastrks(_m,573,ITL_p173)),mxs_numsons(_m,574,mxs_son(_m,574,mxs_itoe(_c,0,2),mxs_fath(_m,574,mxs_decl(_m,574,UID_p168)))))) ){
			mxv_i80 = mxs_true(_m,0);
			goto L80;
		}
		mxv_i80 = mxs_false(_m,0);
		L80: ;
	}
		mxv_i79 = mxv_i80;
		L79: ;
	}
		if( !(  ( ! mxs_is(_m,568,mxs_fath(_m,568,mxs_decl(_m,568,UID_p168)),_TupelProd_)||mxs_eq(_m,0,mxs_true(_m,0),mxv_i79)) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,574,8,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,576,F_p172),mxs_atoe(_c,0,", Line "),mxs_s(_m,576,L_p170),mxs_atoe(_c,0,", Column "),mxs_s(_m,576,C_p171),mxs_atoe(_c,0,":  pattern for tupel node sort never "),mxs_atoe(_c,0,"matches\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_22( void ){
	ELEMENT  mxv_c175, A1_p175, mxv_c176, A2_p176, mxv_c174, ITL_p174, mxv_c0 = 1L;
	long mxv_cix174,mxv_cbd174;
	mxv_cbd174 = mxs_number(_c,0,_ItemList_);
	for(mxv_cix174=1;mxv_cix174<=mxv_cbd174;mxv_cix174++){
		mxv_c174 = mxs_element(_c,0,mxv_cix174,_ItemList_);
		ITL_p174 = mxv_c174;
		if( mxs_numsons(_c,0,mxv_c174) < 2 ) continue;
		mxv_c175 = mxs_son(_c,0,1,mxv_c174);
		mxv_c176 = mxs_rbroth(_c,0,mxv_c175);
		do {
			do {
				if( !mxs_is(_c,0,mxv_c176,_Asterisk_) ) goto CL63;
				A2_p176 = mxv_c176;
				if( !mxs_is(_c,0,mxv_c175,_Asterisk_) ) goto CL63;
				A1_p175 = mxv_c175;
				if( !(  mxs_ex_pattern_inbetween(_m,581,mxs_rbroth(_m,581,A1_p175),A2_p176) )  ){
					mxv_c0 = 0L;
					mxv_errstr =  mxi_string_conc(_m,581,6,mxs_atoe(_c,0,"*****  File "),mxs_patfilename(_m,582,mxs_fath(_m,582,ITL_p174)),mxs_atoe(_c,0,", Line "),mxs_s(_m,582,mxs_patlineno(_m,582,mxs_fath(_m,582,ITL_p174))),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"two asterisks must enclose a pattern\n"));
					fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
				}
				CL63: ;
				mxv_c176 = mxs_rbroth(_c,0,mxv_c176);
			} while( mxv_c176 != mxs_nil(_c,0) );
			mxv_c175 = mxs_rbroth(_c,0,mxv_c175);
			mxv_c176 = mxs_rbroth(_c,0,mxv_c175);
		} while( mxv_c176 != mxs_nil(_c,0) );
	}

	return mxv_c0;
}

static  long  mxc_23( void ){
	ELEMENT  mxv_c212, PC_p212, mxv_c0 = 1L;
	long mxv_cix212,mxv_cbd212;
	mxv_cbd212 = mxs_number(_c,0,_PatternCase_);
	for(mxv_cix212=1;mxv_cix212<=mxv_cbd212;mxv_cix212++){
		mxv_c212 = mxs_element(_c,0,mxv_cix212,_PatternCase_);
		PC_p212 = mxv_c212;
		if( !(  ( ! mxs_eq(_m,0,mxs_pat_anchor(_m,822,PC_p212),mxs_nil(_m,822))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,822,6,mxs_atoe(_c,0,"*****  File "),mxs_patfilename(_m,823,mxs_son(_m,823,mxs_itoe(_c,0,1),PC_p212)),mxs_atoe(_c,0,", Line "),mxs_s(_m,823,mxs_patlineno(_m,823,mxs_son(_m,823,mxs_itoe(_c,0,1),PC_p212))),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"ambigous pattern\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_24( void ){
	ELEMENT  mxv_c215, L_p215, mxv_c216, C_p216, mxv_c217, F_p217, mxv_c214, ID_p214, mxv_c218, EL_p218, mxv_c213, mxv_c0 = 1L;
	long mxv_cix213,mxv_cbd213;
	mxv_cbd213 = mxs_number(_c,0,_FuncAppl_);
	for(mxv_cix213=1;mxv_cix213<=mxv_cbd213;mxv_cix213++){
		mxv_c213 = mxs_element(_c,0,mxv_cix213,_FuncAppl_);
		if( mxs_numsons(_c,0,mxv_c213)!=2 ) continue;
		mxv_c218 = mxs_son(_c,0,-1,mxv_c213);
		mxv_c214 = mxs_lbroth(_c,0,mxv_c218);
		EL_p218 = mxv_c218;
		ID_p214 = mxv_c214;
		if( mxs_numsons(_c,0,mxv_c214)!=4 ) continue;
		mxv_c217 = mxs_son(_c,0,-1,mxv_c214);
		mxv_c216 = mxs_lbroth(_c,0,mxv_c217);
		mxv_c215 = mxs_lbroth(_c,0,mxv_c216);
		F_p217 = mxv_c217;
		C_p216 = mxv_c216;
		L_p215 = mxv_c215;
		if( !(  ( ! mxs_is(_m,834,mxs_fath(_m,834,mxs_decl(_m,834,ID_p214)),_FctOrAttDecl_)||mxs_eq(_m,0,mxs_numsons(_m,835,EL_p218),mxs_numsons(_m,835,mxs_rbroth(_m,835,mxs_decl(_m,835,ID_p214))))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,835,8,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,836,F_p217),mxs_atoe(_c,0,", Line "),mxs_s(_m,836,L_p215),mxs_atoe(_c,0,", Column "),mxs_s(_m,836,C_p216),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"number of formal params doesn't match number of actual params\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_25( void ){
	ELEMENT  mxv_c221, L_p221, mxv_c222, C_p222, mxv_c223, F_p223, mxv_c220, ID_p220, mxv_c224, EL_p224, mxv_c219, mxv_i126, mxv_i125, mxv_c0 = 1L;
	long mxv_cix219,mxv_cbd219;
	mxv_cbd219 = mxs_number(_c,0,_PredAppl_);
	for(mxv_cix219=1;mxv_cix219<=mxv_cbd219;mxv_cix219++){
		mxv_c219 = mxs_element(_c,0,mxv_cix219,_PredAppl_);
		if( mxs_numsons(_c,0,mxv_c219)!=2 ) continue;
		mxv_c224 = mxs_son(_c,0,-1,mxv_c219);
		mxv_c220 = mxs_lbroth(_c,0,mxv_c224);
		EL_p224 = mxv_c224;
		ID_p220 = mxv_c220;
		if( mxs_numsons(_c,0,mxv_c220)!=4 ) continue;
		mxv_c223 = mxs_son(_c,0,-1,mxv_c220);
		mxv_c222 = mxs_lbroth(_c,0,mxv_c223);
		mxv_c221 = mxs_lbroth(_c,0,mxv_c222);
		F_p223 = mxv_c223;
		C_p222 = mxv_c222;
		L_p221 = mxv_c221;
	{  /* FormulaCaseList */
		if( mxs_is(_m,839,mxs_fath(_m,839,mxs_decl(_m,839,ID_p220)),_PredDecl_) ){
			mxv_i125 = mxs_true(_m,0);
			goto L125;
		}
	{  /* FormulaCaseList */
		if( mxs_is(_m,840,mxs_fath(_m,840,mxs_decl(_m,840,ID_p220)),_Predicate_) ){
			mxv_i126 = mxs_true(_m,0);
			goto L126;
		}
		mxv_i126 = mxs_false(_m,0);
		L126: ;
	}
		mxv_i125 = mxv_i126;
		L125: ;
	}
		if( !(  ( ! mxs_eq(_m,0,mxs_true(_m,0),mxv_i125)||mxs_eq(_m,0,mxs_numsons(_m,841,EL_p224),mxs_numsons(_m,841,mxs_rbroth(_m,841,mxs_decl(_m,841,ID_p220))))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,841,8,mxs_atoe(_c,0,"*****  File "),mxs_ss(_m,842,F_p223),mxs_atoe(_c,0,", Line "),mxs_s(_m,842,L_p221),mxs_atoe(_c,0,", Column "),mxs_s(_m,842,C_p222),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"number of formal params doesn't match number of actual params\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_26( void ){
	ELEMENT  mxv_c288, ID_p288, mxv_c287, mxv_c286, N_p286, mxv_c0 = 1L;
	long mxv_cix286,mxv_cbd286;
	mxv_cbd286 = mxs_number(_c,0,_FctOrAtt_);
	for(mxv_cix286=1;mxv_cix286<=mxv_cbd286;mxv_cix286++){
		mxv_c286 = mxs_element(_c,0,mxv_cix286,_FctOrAtt_);
		N_p286 = mxv_c286;
		if( mxs_numsons(_c,0,mxv_c286) < 1 ) continue;
		mxv_c287 = mxs_son(_c,0,1,mxv_c286);
		if( mxs_numsons(_c,0,mxv_c287) < 1 ) continue;
		mxv_c288 = mxs_son(_c,0,1,mxv_c287);
		ID_p288 = mxv_c288;
		if( !(  ( ! mxs_eq(_m,0,mxs_appl_list(_m,1117,N_p286),mxs_nil(_m,1117))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,1117,3,mxs_atoe(_c,0,"*****  internal error: appl_list of the Function/Attribute "),mxs_id(_m,1118,ID_p288),mxs_atoe(_c,0," is nil()\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_27( void ){
	ELEMENT  mxv_c322, ID_p322, mxv_c321, mxv_c320, N_p320, mxv_c0 = 1L;
	long mxv_cix320,mxv_cbd320;
	mxv_cbd320 = mxs_number(_c,0,_FctOrAtt_);
	for(mxv_cix320=1;mxv_cix320<=mxv_cbd320;mxv_cix320++){
		mxv_c320 = mxs_element(_c,0,mxv_cix320,_FctOrAtt_);
		N_p320 = mxv_c320;
		if( mxs_numsons(_c,0,mxv_c320) < 1 ) continue;
		mxv_c321 = mxs_son(_c,0,1,mxv_c320);
		if( mxs_numsons(_c,0,mxv_c321) < 1 ) continue;
		mxv_c322 = mxs_son(_c,0,1,mxv_c321);
		ID_p322 = mxv_c322;
		if( !(  ( ! mxs_eq(_m,0,mxs_appl_relacc_list(_m,1471,N_p320),mxs_nil(_m,1471))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,1471,3,mxs_atoe(_c,0,"***** internal error: Function/Attribute"),mxs_id(_m,1472,ID_p322),mxs_atoe(_c,0," : appl_relacc_list is nil\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}


long  mxi_atteval( void ){
	long mxv_correct = 1;
	long ix;
	long mxn_term_basesorts = mxs_number(_c,0,_SortId_);
	long mxn_node_basesorts = mxs_number(_c,0,_SortId_);
	long mxn_encl_scope = mxs_number(_c,0,_Scope_);
	long mxn_bind_pos = mxs_number(_c,0,_Name_);
	long mxn_numberofastrks = mxs_number(_c,0,_ItemList_);
	long mxn_predeclprodcd = mxs_number(_c,0,_PredeclProd_);
	long mxn_tupelprodcd = mxs_number(_c,0,_TupelProd_);
	long mxn_listprodcd = mxs_number(_c,0,_ListProd_);
	long mxn_classprodcd = mxs_number(_c,0,_ClassProd_);
	long mxn_patnpos = mxs_number(_c,0,_Pattern_);
	long mxn_num_items = mxs_number(_c,0,_Pattern_);
	long mxn_args = mxs_number(_c,0,_FuncAppl_);
	long mxn_caseexpr = mxs_number(_c,0,_IfCase_);
	long mxn_allexpr = mxs_number(_c,0,_IfExpr_);
	long mxn_encl_patterncase = mxs_number(_c,0,_Node);
	long mxn_top_pattern = mxs_number(_c,0,_Node);
	long mxn_son_nr = mxs_number(_c,0,_FctOrAtt_);
	long mxn_relacc_nr = mxs_number(_c,0,_FuncAppl_);
	long mxn_appl_list_formula = mxs_number(_c,0,_Formula_);
	long mxn_appl_list_case = mxs_number(_c,0,_Case_);
	long mxn_appl_list_expr = mxs_number(_c,0,_Expr_);
	long mxn_appl_list = mxs_number(_c,0,_FctOrAtt_);
	long mxn_def_value = mxs_number(_c,0,_DefId_);
	long mxn_node_parnr = mxs_number(_c,0,_FctOrAttDecl_);
	long mxn_appl_value = mxs_number(_c,0,_FuncAppl_);
	long mxn_nodepar_expr = mxs_number(_c,0,_FuncAppl_);
	long mxn_valueterm_list = mxs_number(_c,0,_Case_);
	long mxn_valueterm = mxs_number(_c,0,_Expr_);
	long mxn_attr_list_matlist = mxs_number(_c,0,_FuAtList_);
	long mxn_result_value = mxs_number(_c,0,_FctOrAtt_);
	long mxn_is_relev_att_access = mxs_number(_c,0,_FuncAppl_);
	long mxn_appl_order = mxs_number(_c,0,_FuncAppl_);
	long mxn_appl_relacc_list = mxs_number(_c,0,_FctOrAtt_);
	long mxn_maybe_wait = mxs_number(_c,0,_FuncAppl_);
	long mxn_cgen_name = mxs_number(_c,0,_IntResOrName_);
	long mxn_sces_appl = mxs_number(_c,0,_ApplyEntity_);
	long mxn_sces1_cond = mxs_number(_c,0,_Condition_);
	long mxn_sces2_cond = mxs_number(_c,0,_Condition_);
	long mxn_sces1_let = mxs_number(_c,0,_LetExpr_);
	long mxn_sces2_let = mxs_number(_c,0,_LetExpr_);
	long mxn_sces_if = mxs_number(_c,0,_IfExpr_);
	long mxn_sces1_fcase = mxs_number(_c,0,_FormulaCase_);
	long mxn_sces2_fcase = mxs_number(_c,0,_FormulaCase_);
	long mxn_sces_pcase = mxs_number(_c,0,_PatternCase_);
	long mxn_sces_attacc = mxs_number(_c,0,_FuncAppl_);
	long mxn_lokvar_need = mxs_number(_c,0,_FctOrAtt_);
	long mxn_intres_collect = mxs_number(_c,0,_IntResExpr_);
	long mxn, mxz_stacksize = 0;

	extern SORTCDT mxi_list_sortcd_lb;

	rev_element_tab = (ELEMENT **)  calloc((1-mxi_list_sortcd_lb),sizeof(ELEMENT *));
	if( rev_element_tab == 0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate rev_element_tab table \n");
		exit( EXIT_FAILURE );
	}
	for(ix=0; ix <= -mxi_list_sortcd_lb ;ix++) rev_element_tab[ix] = NULL;

	mxn = mxs_number(_c,0,_Predicate_);
	if(mxn > mxz_stacksize) mxz_stacksize = mxn;
	mxn = mxs_number(_c,0,_Function_);
	if(mxn > mxz_stacksize) mxz_stacksize = mxn;
	mxn = mxs_number(_c,0,_Attribute_);
	if(mxn > mxz_stacksize) mxz_stacksize = mxn;
	mxn = mxs_number(_c,0,_Condition_);
	if(mxn > mxz_stacksize) mxz_stacksize = mxn;
	mxn = mxs_number(_c,0,_FuncAppl_);
	if(mxn > mxz_stacksize) mxz_stacksize = mxn;
	mxn = mxs_number(_c,0,_IfExpr_);
	if(mxn > mxz_stacksize) mxz_stacksize = mxn;
	mxn = mxs_number(_c,0,_LetExpr_);
	if(mxn > mxz_stacksize) mxz_stacksize = mxn;
	mxn = mxs_number(_c,0,_DynFunc_);
	if(mxn > mxz_stacksize) mxz_stacksize = mxn;
	mxn = mxs_number(_c,0,_DynSemInput_);
	if(mxn > mxz_stacksize) mxz_stacksize = mxn;

	enum_stack = (ELEMENT *)calloc( 1+mxz_stacksize, sizeof(ELEMENT));
	if(enum_stack == 0L) {
		fprintf(stderr,"\n***** Error: Cannot allocate Stack \n");
		exit( EXIT_FAILURE );
	}
	mxz_init_revindex(_Predicate_);
	mxz_init_revindex(_Function_);
	mxz_init_revindex(_Attribute_);
	mxz_init_revindex(_Condition_);
	mxz_init_revindex(_FuncAppl_);
	mxz_init_revindex(_IfExpr_);
	mxz_init_revindex(_LetExpr_);
	mxz_init_revindex(_DynFunc_);
	mxz_init_revindex(_DynSemInput_);
	free(enum_stack);

	mxz_firstpoint = mxs_before(_c,0,mxs_root(_c,0));
	mxz_lastpoint = mxs_after(_c,0,mxs_root(_c,0));


	mxv_correct = init_parscode() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_LPsepsymbols() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_TPconcrSyntax() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_CPrsideinfo() && mxv_correct;


	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=1 */
	/*** Evaluation of group 1 strategy 0 */

	mxv_correct = mxc_1() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=2 */
	/*** Evaluation of group 1 strategy 0 */
	/*** Evaluation of group 2 strategy 0 */
	/*** Evaluation of group 3 strategy 0 */
	/*** Evaluation of group 4 strategy 0 */

	mxv_correct = mxc_2() && mxv_correct;
	if( ! mxv_correct ) return 0L;


	mxv_correct = init_idtodecls() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = mxc_3() && mxv_correct;
	mxv_correct = mxc_4() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=3 */
	/*** Evaluation of group 1 strategy 0 */

	mxv_correct = init_ExchangeTripel() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_ExtraRule() && mxv_correct;


	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=4 */
	/*** Evaluation of group 1 strategy 36 */
	mxa_term_basesorts = (ELEMENT*)   calloc( mxn_term_basesorts+1, sizeof(ELEMENT) );
	mxw_term_basesorts = (AttInstSq*) calloc( mxn_term_basesorts+1, sizeof(AttInstSq) );
	if( mxa_term_basesorts==0L || mxw_term_basesorts==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute term_basesorts\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_term_basesorts; ix++ )  mxa_term_basesorts[ix] = MAXUNDEF;
	for( ix=1; ix<=mxn_term_basesorts; ix++ )  mxe_term_basesorts( mxs_element(_c,0,ix,_SortId_),0,0,NULL);
	for( ix=1; ix<=mxn_term_basesorts; ix++ ){
		if( mxa_term_basesorts[ ix ] == MAXUNDEF )  mxa_term_basesorts[ix] = mxs_nil(_c,0);
	}
	free(mxw_term_basesorts);

	mxv_correct = mxc_5() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=5 */
	/*** Evaluation of group 1 strategy 0 */
	/*** Evaluation of group 2 strategy 36 */
	mxa_node_basesorts = (ELEMENT*)   calloc( mxn_node_basesorts+1, sizeof(ELEMENT) );
	mxw_node_basesorts = (AttInstSq*) calloc( mxn_node_basesorts+1, sizeof(AttInstSq) );
	if( mxa_node_basesorts==0L || mxw_node_basesorts==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute node_basesorts\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_node_basesorts; ix++ )  mxa_node_basesorts[ix] = MAXUNDEF;
	for( ix=1; ix<=mxn_node_basesorts; ix++ )  mxe_node_basesorts( mxs_element(_c,0,ix,_SortId_),0,0,NULL);
	for( ix=1; ix<=mxn_node_basesorts; ix++ ){
		if( mxa_node_basesorts[ ix ] == MAXUNDEF )  mxa_node_basesorts[ix] = mxs_nil(_c,0);
	}
	free(mxw_node_basesorts);

	mxv_correct = mxc_6() && mxv_correct;
	mxv_correct = mxc_7() && mxv_correct;
	mxv_correct = mxc_8() && mxv_correct;
	mxv_correct = mxc_9() && mxv_correct;
	mxv_correct = mxc_10() && mxv_correct;
	mxv_correct = mxc_11() && mxv_correct;
	mxv_correct = mxc_12() && mxv_correct;
	if( ! mxv_correct ) return 0L;


	mxv_correct = mxc_13() && mxv_correct;
	mxv_correct = mxc_14() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=6 */
	/*** Evaluation of group 1 strategy 0 */
	/*** Evaluation of group 2 strategy 2 */
	mxa_encl_scope = (ELEMENT*)   calloc( mxn_encl_scope+1, sizeof(ELEMENT) );
	if( mxa_encl_scope==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute encl_scope\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_encl_scope; ix++ )  mxe_encl_scope( mxs_element(_c,0,ix,_Scope_) );
	/*** Evaluation of group 3 strategy 0 */
	/*** Evaluation of group 4 strategy 0 */
	/*** Evaluation of group 5 strategy 0 */
	/*** Evaluation of group 6 strategy 0 */

	mxv_correct = mxc_15() && mxv_correct;
	mxv_correct = mxc_16() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=7 */
	/*** Evaluation of group 1 strategy 2 */
	mxa_bind_pos = (ELEMENT*)   calloc( mxn_bind_pos+1, sizeof(ELEMENT) );
	if( mxa_bind_pos==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute bind_pos\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_bind_pos; ix++ )  mxe_bind_pos( mxs_element(_c,0,ix,_Name_) );

	mxv_correct = mxc_17() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=8 */
	/*** Evaluation of group 1 strategy 0 */
	/*** Evaluation of group 2 strategy 2 */
	mxa_numberofastrks = (ELEMENT*)   calloc( mxn_numberofastrks+1, sizeof(ELEMENT) );
	if( mxa_numberofastrks==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute numberofastrks\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_numberofastrks; ix++ )  mxe_numberofastrks( mxs_element(_c,0,ix,_ItemList_) );

	mxv_correct = mxc_18() && mxv_correct;
	mxv_correct = mxc_19() && mxv_correct;
	mxv_correct = mxc_20() && mxv_correct;
	mxv_correct = mxc_21() && mxv_correct;
	mxv_correct = mxc_22() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=9 */
	/*** Evaluation of group 1 strategy 2 */
	mxa_predeclprodcd = (ELEMENT*)   calloc( mxn_predeclprodcd+1, sizeof(ELEMENT) );
	if( mxa_predeclprodcd==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute predeclprodcd\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_predeclprodcd; ix++ )  mxe_predeclprodcd( mxs_element(_c,0,ix,_PredeclProd_) );
	/*** Evaluation of group 2 strategy 2 */
	mxa_tupelprodcd = (ELEMENT*)   calloc( mxn_tupelprodcd+1, sizeof(ELEMENT) );
	if( mxa_tupelprodcd==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute tupelprodcd\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_tupelprodcd; ix++ )  mxe_tupelprodcd( mxs_element(_c,0,ix,_TupelProd_) );
	/*** Evaluation of group 3 strategy 2 */
	mxa_listprodcd = (ELEMENT*)   calloc( mxn_listprodcd+1, sizeof(ELEMENT) );
	if( mxa_listprodcd==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute listprodcd\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_listprodcd; ix++ )  mxe_listprodcd( mxs_element(_c,0,ix,_ListProd_) );
	/*** Evaluation of group 4 strategy 0 */
	/*** Evaluation of group 5 strategy 2 */
	mxa_classprodcd = (ELEMENT*)   calloc( mxn_classprodcd+1, sizeof(ELEMENT) );
	if( mxa_classprodcd==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute classprodcd\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_classprodcd; ix++ )  mxe_classprodcd( mxs_element(_c,0,ix,_ClassProd_) );
	/*** Evaluation of group 6 strategy 0 */

	mxv_correct = init_subsorts() && mxv_correct;


	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=10 */
	/*** Evaluation of group 1 strategy 0 */
	/*** Evaluation of group 2 strategy 0 */
	/*** Evaluation of group 3 strategy 2 */
	mxa_patnpos = (ELEMENT*)   calloc( mxn_patnpos+1, sizeof(ELEMENT) );
	if( mxa_patnpos==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute patnpos\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_patnpos; ix++ )  mxe_patnpos( mxs_element(_c,0,ix,_Pattern_) );
	/*** Evaluation of group 4 strategy 0 */
	/*** Evaluation of group 5 strategy 0 */
	/*** Evaluation of group 6 strategy 0 */
	/*** Evaluation of group 7 strategy 0 */
	/*** Evaluation of group 8 strategy 0 */
	/*** Evaluation of group 9 strategy 0 */
	/*** Evaluation of group 10 strategy 0 */
	/*** Evaluation of group 11 strategy 0 */
	/*** Evaluation of group 12 strategy 0 */
	/*** Evaluation of group 13 strategy 0 */
	/*** Evaluation of group 14 strategy 0 */
	/*** Evaluation of group 15 strategy 0 */
	/*** Evaluation of group 16 strategy 0 */
	/*** Evaluation of group 17 strategy 0 */
	/*** Evaluation of group 18 strategy 0 */

	mxv_correct = init_att_path() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_pat_anchor() && mxv_correct;


	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=11 */
	/*** Evaluation of group 1 strategy 2 */
	mxa_num_items = (ELEMENT*)   calloc( mxn_num_items+1, sizeof(ELEMENT) );
	if( mxa_num_items==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute num_items\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_num_items; ix++ )  mxe_num_items( mxs_element(_c,0,ix,_Pattern_) );

	mxv_correct = mxc_23() && mxv_correct;
	mxv_correct = mxc_24() && mxv_correct;
	mxv_correct = mxc_25() && mxv_correct;
	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=12 */
	/*** Evaluation of group 1 strategy 2 */
	mxa_args = (ELEMENT*)   calloc( mxn_args+1, sizeof(ELEMENT) );
	if( mxa_args==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute args\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_args; ix++ )  mxe_args( mxs_element(_c,0,ix,_FuncAppl_) );
	/*** Evaluation of group 2 strategy 1 */
	mxa_caseexpr = (ELEMENT*)   calloc( mxn_caseexpr+1, sizeof(ELEMENT) );
	if( mxa_caseexpr==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute caseexpr\n");
		exit( EXIT_FAILURE );
	}
	first_forw_bef(_FormulaCase_,2);
	first_forw_bef(_PatternCase_,1);	mxz_sift_forw(1,2);
	while(mxz_heap[1].point!=mxs_nil(_c,0)) {
	switch(mxz_heap[1].ind) {
	case 1:
			mxe_caseexpr(mxz_heap[1].node);
		next_forw_bef(_PatternCase_,1);	mxz_sift_forw(1,2);	break;
	case 2:
			mxe_caseexpr(mxz_heap[1].node);
		next_forw_bef(_FormulaCase_,2);	mxz_sift_forw(1,2);	break;
	}} /* endswitch, endwhile */

	/*** Evaluation of group 3 strategy 2 */
	mxa_allexpr = (ELEMENT*)   calloc( mxn_allexpr+1, sizeof(ELEMENT) );
	if( mxa_allexpr==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute allexpr\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_allexpr; ix++ )  mxe_allexpr( mxs_element(_c,0,ix,_IfExpr_) );
	/*** Evaluation of group 4 strategy 1 */
	mxa_encl_patterncase = (ELEMENT*)   calloc( mxn_encl_patterncase+1, sizeof(ELEMENT) );
	if( mxa_encl_patterncase==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute encl_patterncase\n");
		exit( EXIT_FAILURE );
	}
	firstnode_forw_bef(1);
	while(mxz_heap[1].point!=mxs_nil(_c,0)) {
			mxe_encl_patterncase(mxz_heap[1].node);
	nextnode_forw_bef();
	} /* endwhile */

	/*** Evaluation of group 5 strategy 1 */
	mxa_top_pattern = (ELEMENT*)   calloc( mxn_top_pattern+1, sizeof(ELEMENT) );
	if( mxa_top_pattern==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute top_pattern\n");
		exit( EXIT_FAILURE );
	}
	firstnode_forw_bef(1);
	while(mxz_heap[1].point!=mxs_nil(_c,0)) {
			mxe_top_pattern(mxz_heap[1].node);
	nextnode_forw_bef();
	} /* endwhile */

	/*** Evaluation of group 6 strategy 0 */
	/*** Evaluation of group 7 strategy 0 */
	/*** Evaluation of group 8 strategy 0 */
	/*** Evaluation of group 9 strategy 0 */
	/*** Evaluation of group 10 strategy 0 */
	/*** Evaluation of group 11 strategy 0 */
	/*** Evaluation of group 12 strategy 0 */
	/*** Evaluation of group 13 strategy 0 */
	/*** Evaluation of group 14 strategy 0 */
	/*** Evaluation of group 15 strategy 0 */
	/*** Evaluation of group 16 strategy 0 */
	/*** Evaluation of group 17 strategy 0 */
	/*** Evaluation of group 18 strategy 0 */
	/*** Evaluation of group 19 strategy 0 */
	/*** Evaluation of group 20 strategy 0 */
	/*** Evaluation of group 21 strategy 0 */
	/*** Evaluation of group 22 strategy 0 */
	/*** Evaluation of group 23 strategy 0 */
	/*** Evaluation of group 24 strategy 0 */
	/*** Evaluation of group 25 strategy 0 */
	/*** Evaluation of group 26 strategy 1 */
	mxa_son_nr = (ELEMENT*)   calloc( mxn_son_nr+1, sizeof(ELEMENT) );
	if( mxa_son_nr==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute son_nr\n");
		exit( EXIT_FAILURE );
	}
	first_forw_bef(_Attribute_,2);
	first_forw_bef(_Function_,1);	mxz_sift_forw(1,2);
	while(mxz_heap[1].point!=mxs_nil(_c,0)) {
	switch(mxz_heap[1].ind) {
	case 1:
			mxe_son_nr(mxz_heap[1].node);
		next_forw_bef(_Function_,1);	mxz_sift_forw(1,2);	break;
	case 2:
			mxe_son_nr(mxz_heap[1].node);
		next_forw_bef(_Attribute_,2);	mxz_sift_forw(1,2);	break;
	}} /* endswitch, endwhile */

	/*** Evaluation of group 27 strategy 2 */
	mxa_relacc_nr = (ELEMENT*)   calloc( mxn_relacc_nr+1, sizeof(ELEMENT) );
	if( mxa_relacc_nr==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute relacc_nr\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_relacc_nr; ix++ )  mxe_relacc_nr( mxs_element(_c,0,ix,_FuncAppl_) );
	/*** Evaluation of group 28 strategy 9 */
	mxa_appl_list_formula = (ELEMENT*)   calloc( mxn_appl_list_formula+1, sizeof(ELEMENT) );
	if( mxa_appl_list_formula==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute appl_list_formula\n");
		exit( EXIT_FAILURE );
	}
	mxa_appl_list_case = (ELEMENT*)   calloc( mxn_appl_list_case+1, sizeof(ELEMENT) );
	if( mxa_appl_list_case==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute appl_list_case\n");
		exit( EXIT_FAILURE );
	}
	mxa_appl_list_expr = (ELEMENT*)   calloc( mxn_appl_list_expr+1, sizeof(ELEMENT) );
	if( mxa_appl_list_expr==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute appl_list_expr\n");
		exit( EXIT_FAILURE );
	}
	first_backw_bef(_DynUndef_,17);
	first_backw_bef(_Name_,16);
	first_backw_bef(_Neg_,15);
	first_backw_bef(_Impl_,14);
	first_backw_bef(_And_,13);
	first_backw_bef(_Or_,12);
	first_backw_bef(_PredAppl_,11);
	first_backw_bef(_FormulaCase_,10);
	first_backw_bef(_PatternCase_,9);
	first_backw_bef(_StringExpr_,8);	mxz_sift_backw(8,17);
	first_backw_bef(_LetExpr_,7);	mxz_sift_backw(7,17);
	first_backw_bef(_IfExpr_,6);	mxz_sift_backw(6,17);
	first_backw_bef(_FuncAppl_,5);	mxz_sift_backw(5,17);
	first_backw_bef(_SortConst_,4);	mxz_sift_backw(4,17);
	first_backw_bef(_StringConst_,3);	mxz_sift_backw(3,17);
	first_backw_bef(_IntConst_,2);	mxz_sift_backw(2,17);
	first_backw_bef(_CharConst_,1);	mxz_sift_backw(1,17);
	while(mxz_heap[1].point!=mxs_nil(_c,0)) {
	switch(mxz_heap[1].ind) {
	case 1:
			mxe_appl_list_expr(mxz_heap[1].node);
		next_backw_bef(_CharConst_,1);	mxz_sift_backw(1,17);	break;
	case 2:
			mxe_appl_list_expr(mxz_heap[1].node);
		next_backw_bef(_IntConst_,2);	mxz_sift_backw(1,17);	break;
	case 3:
			mxe_appl_list_expr(mxz_heap[1].node);
		next_backw_bef(_StringConst_,3);	mxz_sift_backw(1,17);	break;
	case 4:
			mxe_appl_list_expr(mxz_heap[1].node);
		next_backw_bef(_SortConst_,4);	mxz_sift_backw(1,17);	break;
	case 5:
			mxe_appl_list_expr(mxz_heap[1].node);
		next_backw_bef(_FuncAppl_,5);	mxz_sift_backw(1,17);	break;
	case 6:
			mxe_appl_list_expr(mxz_heap[1].node);
		next_backw_bef(_IfExpr_,6);	mxz_sift_backw(1,17);	break;
	case 7:
			mxe_appl_list_expr(mxz_heap[1].node);
		next_backw_bef(_LetExpr_,7);	mxz_sift_backw(1,17);	break;
	case 8:
			mxe_appl_list_expr(mxz_heap[1].node);
		next_backw_bef(_StringExpr_,8);	mxz_sift_backw(1,17);	break;
	case 9:
			mxe_appl_list_case(mxz_heap[1].node);
		next_backw_bef(_PatternCase_,9);	mxz_sift_backw(1,17);	break;
	case 10:
			mxe_appl_list_case(mxz_heap[1].node);
		next_backw_bef(_FormulaCase_,10);	mxz_sift_backw(1,17);	break;
	case 11:
			mxe_appl_list_formula(mxz_heap[1].node);
		next_backw_bef(_PredAppl_,11);	mxz_sift_backw(1,17);	break;
	case 12:
			mxe_appl_list_formula(mxz_heap[1].node);
		next_backw_bef(_Or_,12);	mxz_sift_backw(1,17);	break;
	case 13:
			mxe_appl_list_formula(mxz_heap[1].node);
		next_backw_bef(_And_,13);	mxz_sift_backw(1,17);	break;
	case 14:
			mxe_appl_list_formula(mxz_heap[1].node);
		next_backw_bef(_Impl_,14);	mxz_sift_backw(1,17);	break;
	case 15:
			mxe_appl_list_formula(mxz_heap[1].node);
		next_backw_bef(_Neg_,15);	mxz_sift_backw(1,17);	break;
	case 16:
			mxe_appl_list_expr(mxz_heap[1].node);
		next_backw_bef(_Name_,16);	mxz_sift_backw(1,17);	break;
	case 17:
			mxe_appl_list_expr(mxz_heap[1].node);
		next_backw_bef(_DynUndef_,17);	mxz_sift_backw(1,17);	break;
	}} /* endswitch, endwhile */

	/*** Evaluation of group 29 strategy 2 */
	mxa_appl_list = (ELEMENT*)   calloc( mxn_appl_list+1, sizeof(ELEMENT) );
	if( mxa_appl_list==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute appl_list\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_appl_list; ix++ )  mxe_appl_list( mxs_element(_c,0,ix,_FctOrAtt_) );

	mxv_correct = mxc_26() && mxv_correct;
	if( ! mxv_correct ) return 0L;


	mxv_correct = init_eval_groupnr() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_eval_prev_grnum() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_group_index() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_eval_group() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_attr_list_groups() && mxv_correct;


	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=13 */
	/*** Evaluation of group 1 strategy 2 */
	mxa_def_value = (ELEMENT*)   calloc( mxn_def_value+1, sizeof(ELEMENT) );
	if( mxa_def_value==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute def_value\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_def_value; ix++ )  mxe_def_value( mxs_element(_c,0,ix,_DefId_) );
	/*** Evaluation of group 2 strategy 0 */
	/*** Evaluation of group 3 strategy 2 */
	mxa_node_parnr = (ELEMENT*)   calloc( mxn_node_parnr+1, sizeof(ELEMENT) );
	if( mxa_node_parnr==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute node_parnr\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_node_parnr; ix++ )  mxe_node_parnr( mxs_element(_c,0,ix,_FctOrAttDecl_) );
	/*** Evaluation of group 4 strategy 2 */
	mxa_appl_value = (ELEMENT*)   calloc( mxn_appl_value+1, sizeof(ELEMENT) );
	if( mxa_appl_value==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute appl_value\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_appl_value; ix++ )  mxe_appl_value( mxs_element(_c,0,ix,_FuncAppl_) );
	/*** Evaluation of group 5 strategy 2 */
	mxa_nodepar_expr = (ELEMENT*)   calloc( mxn_nodepar_expr+1, sizeof(ELEMENT) );
	if( mxa_nodepar_expr==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute nodepar_expr\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_nodepar_expr; ix++ )  mxe_nodepar_expr( mxs_element(_c,0,ix,_FuncAppl_) );
	/*** Evaluation of group 6 strategy 0 */
	/*** Evaluation of group 7 strategy 0 */
	/*** Evaluation of group 8 strategy 0 */
	/*** Evaluation of group 9 strategy 0 */
	/*** Evaluation of group 10 strategy 0 */
	/*** Evaluation of group 11 strategy 44 */
	mxa_valueterm_list = (ELEMENT*)   calloc( mxn_valueterm_list+1, sizeof(ELEMENT) );
	mxw_valueterm_list = (AttInstSq*) calloc( mxn_valueterm_list+1, sizeof(AttInstSq) );
	if( mxa_valueterm_list==0L || mxw_valueterm_list==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute valueterm_list\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_valueterm_list; ix++ )  mxa_valueterm_list[ix] = MAXUNDEF;
	mxa_valueterm = (ELEMENT*)   calloc( mxn_valueterm+1, sizeof(ELEMENT) );
	mxw_valueterm = (AttInstSq*) calloc( mxn_valueterm+1, sizeof(AttInstSq) );
	if( mxa_valueterm==0L || mxw_valueterm==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute valueterm\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_valueterm; ix++ )  mxa_valueterm[ix] = MAXUNDEF;
	for( ix=1; ix<=mxn_valueterm_list; ix++ )  mxe_valueterm_list( mxs_element(_c,0,ix,_Case_),0,0,NULL);
	for( ix=1; ix<=mxn_valueterm; ix++ )  mxe_valueterm( mxs_element(_c,0,ix,_Expr_),0,0,NULL);
	for( ix=1; ix<=mxn_valueterm_list; ix++ ){
		if( mxa_valueterm_list[ ix ] == MAXUNDEF )  mxa_valueterm_list[ix] = mxs_nil(_c,0);
	}
	free(mxw_valueterm_list);
	for( ix=1; ix<=mxn_valueterm; ix++ ){
		if( mxa_valueterm[ ix ] == MAXUNDEF )  mxa_valueterm[ix] = mxs_nil(_c,0);
	}
	free(mxw_valueterm);
	/*** Evaluation of FuAtList ind=14 */
	/*** Evaluation of group 1 strategy 0 */
	/*** Evaluation of group 2 strategy 0 */
	/*** Evaluation of group 3 strategy 2 */
	mxa_attr_list_matlist = (ELEMENT*)   calloc( mxn_attr_list_matlist+1, sizeof(ELEMENT) );
	if( mxa_attr_list_matlist==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute attr_list_matlist\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_attr_list_matlist; ix++ )  mxe_attr_list_matlist( mxs_element(_c,0,ix,_FuAtList_) );
	/*** Evaluation of FuAtList ind=15 */
	/*** Evaluation of group 1 strategy 2 */
	mxa_result_value = (ELEMENT*)   calloc( mxn_result_value+1, sizeof(ELEMENT) );
	if( mxa_result_value==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute result_value\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_result_value; ix++ )  mxe_result_value( mxs_element(_c,0,ix,_FctOrAtt_) );
	/*** Evaluation of group 2 strategy 0 */
	/*** Evaluation of FuAtList ind=16 */
	/*** Evaluation of group 1 strategy 0 */
	/*** Evaluation of group 2 strategy 0 */
	/*** Evaluation of group 3 strategy 0 */
	/*** Evaluation of FuAtList ind=17 */
	/*** Evaluation of group 1 strategy 0 */
	/*** Evaluation of group 2 strategy 0 */
	/*** Evaluation of group 3 strategy 0 */
	/*** Evaluation of group 4 strategy 0 */
	/*** Evaluation of group 5 strategy 0 */
	/*** Evaluation of group 6 strategy 0 */
	/*** Evaluation of group 7 strategy 0 */
	/*** Evaluation of group 8 strategy 0 */
	/*** Evaluation of group 9 strategy 0 */
	/*** Evaluation of group 10 strategy 0 */
	/*** Evaluation of group 11 strategy 2 */
	mxa_is_relev_att_access = (ELEMENT*)   calloc( mxn_is_relev_att_access+1, sizeof(ELEMENT) );
	if( mxa_is_relev_att_access==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute is_relev_att_access\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_is_relev_att_access; ix++ )  mxe_is_relev_att_access( mxs_element(_c,0,ix,_FuncAppl_) );
	/*** Evaluation of group 12 strategy 2 */
	mxa_appl_order = (ELEMENT*)   calloc( mxn_appl_order+1, sizeof(ELEMENT) );
	if( mxa_appl_order==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute appl_order\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_appl_order; ix++ )  mxe_appl_order( mxs_element(_c,0,ix,_FuncAppl_) );
	/*** Evaluation of group 13 strategy 0 */
	/*** Evaluation of group 14 strategy 2 */
	mxa_appl_relacc_list = (ELEMENT*)   calloc( mxn_appl_relacc_list+1, sizeof(ELEMENT) );
	if( mxa_appl_relacc_list==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute appl_relacc_list\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_appl_relacc_list; ix++ )  mxe_appl_relacc_list( mxs_element(_c,0,ix,_FctOrAtt_) );

	mxv_correct = mxc_27() && mxv_correct;
	if( ! mxv_correct ) return 0L;


	mxv_correct = init_eval_finegroup() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_eval_aftbef() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_is_trivial_finegroup() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_eval_strategy() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_eval_sortlist() && mxv_correct;


	if( ! mxv_correct ) return 0L;


	mxv_correct = init_attr_list_info() && mxv_correct;


	if( ! mxv_correct ) return 0L;

	/*** Evaluation of FuAtList ind=18 */
	/*** Evaluation of group 1 strategy 2 */
	mxa_maybe_wait = (ELEMENT*)   calloc( mxn_maybe_wait+1, sizeof(ELEMENT) );
	if( mxa_maybe_wait==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute maybe_wait\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_maybe_wait; ix++ )  mxe_maybe_wait( mxs_element(_c,0,ix,_FuncAppl_) );
	/*** Evaluation of FuAtList ind=19 */
	/*** Evaluation of group 1 strategy 36 */
	mxa_cgen_name = (ELEMENT*)   calloc( mxn_cgen_name+1, sizeof(ELEMENT) );
	mxw_cgen_name = (AttInstSq*) calloc( mxn_cgen_name+1, sizeof(AttInstSq) );
	if( mxa_cgen_name==0L || mxw_cgen_name==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute cgen_name\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_cgen_name; ix++ )  mxa_cgen_name[ix] = MAXUNDEF;
	for( ix=1; ix<=mxn_cgen_name; ix++ )  mxe_cgen_name( mxs_element(_c,0,ix,_IntResOrName_),0,0,NULL);
	for( ix=1; ix<=mxn_cgen_name; ix++ ){
		if( mxa_cgen_name[ ix ] == MAXUNDEF )  mxa_cgen_name[ix] = mxs_nil(_c,0);
	}
	free(mxw_cgen_name);
	/*** Evaluation of FuAtList ind=20 */
	/*** Evaluation of group 1 strategy 0 */
	/*** Evaluation of group 2 strategy 2 */
	mxa_sces_appl = (ELEMENT*)   calloc( mxn_sces_appl+1, sizeof(ELEMENT) );
	if( mxa_sces_appl==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces_appl\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces_appl; ix++ )  mxe_sces_appl( mxs_element(_c,0,ix,_ApplyEntity_) );
	/*** Evaluation of group 3 strategy 2 */
	mxa_sces1_cond = (ELEMENT*)   calloc( mxn_sces1_cond+1, sizeof(ELEMENT) );
	if( mxa_sces1_cond==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces1_cond\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces1_cond; ix++ )  mxe_sces1_cond( mxs_element(_c,0,ix,_Condition_) );
	/*** Evaluation of group 4 strategy 2 */
	mxa_sces2_cond = (ELEMENT*)   calloc( mxn_sces2_cond+1, sizeof(ELEMENT) );
	if( mxa_sces2_cond==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces2_cond\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces2_cond; ix++ )  mxe_sces2_cond( mxs_element(_c,0,ix,_Condition_) );
	/*** Evaluation of group 5 strategy 2 */
	mxa_sces1_let = (ELEMENT*)   calloc( mxn_sces1_let+1, sizeof(ELEMENT) );
	if( mxa_sces1_let==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces1_let\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces1_let; ix++ )  mxe_sces1_let( mxs_element(_c,0,ix,_LetExpr_) );
	/*** Evaluation of group 6 strategy 2 */
	mxa_sces2_let = (ELEMENT*)   calloc( mxn_sces2_let+1, sizeof(ELEMENT) );
	if( mxa_sces2_let==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces2_let\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces2_let; ix++ )  mxe_sces2_let( mxs_element(_c,0,ix,_LetExpr_) );
	/*** Evaluation of group 7 strategy 2 */
	mxa_sces_if = (ELEMENT*)   calloc( mxn_sces_if+1, sizeof(ELEMENT) );
	if( mxa_sces_if==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces_if\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces_if; ix++ )  mxe_sces_if( mxs_element(_c,0,ix,_IfExpr_) );
	/*** Evaluation of group 8 strategy 2 */
	mxa_sces1_fcase = (ELEMENT*)   calloc( mxn_sces1_fcase+1, sizeof(ELEMENT) );
	if( mxa_sces1_fcase==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces1_fcase\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces1_fcase; ix++ )  mxe_sces1_fcase( mxs_element(_c,0,ix,_FormulaCase_) );
	/*** Evaluation of group 9 strategy 2 */
	mxa_sces2_fcase = (ELEMENT*)   calloc( mxn_sces2_fcase+1, sizeof(ELEMENT) );
	if( mxa_sces2_fcase==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces2_fcase\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces2_fcase; ix++ )  mxe_sces2_fcase( mxs_element(_c,0,ix,_FormulaCase_) );
	/*** Evaluation of group 10 strategy 2 */
	mxa_sces_pcase = (ELEMENT*)   calloc( mxn_sces_pcase+1, sizeof(ELEMENT) );
	if( mxa_sces_pcase==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces_pcase\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces_pcase; ix++ )  mxe_sces_pcase( mxs_element(_c,0,ix,_PatternCase_) );
	/*** Evaluation of group 11 strategy 2 */
	mxa_sces_attacc = (ELEMENT*)   calloc( mxn_sces_attacc+1, sizeof(ELEMENT) );
	if( mxa_sces_attacc==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute sces_attacc\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_sces_attacc; ix++ )  mxe_sces_attacc( mxs_element(_c,0,ix,_FuncAppl_) );
	/*** Evaluation of group 12 strategy 0 */
	/*** Evaluation of group 13 strategy 0 */
	/*** Evaluation of group 14 strategy 0 */
	/*** Evaluation of group 15 strategy 0 */
	/*** Evaluation of group 16 strategy 2 */
	mxa_lokvar_need = (ELEMENT*)   calloc( mxn_lokvar_need+1, sizeof(ELEMENT) );
	if( mxa_lokvar_need==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute lokvar_need\n");
		exit( EXIT_FAILURE );
	}
	for( ix=1; ix<=mxn_lokvar_need; ix++ )  mxe_lokvar_need( mxs_element(_c,0,ix,_FctOrAtt_) );
	/*** Evaluation of FuAtList ind=21 */
	/*** Evaluation of group 1 strategy 9 */
	mxa_intres_collect = (ELEMENT*)   calloc( mxn_intres_collect+1, sizeof(ELEMENT) );
	if( mxa_intres_collect==0L ){
		fprintf(stderr,"\n***** Error: Cannot allocate attribute intres_collect\n");
		exit( EXIT_FAILURE );
	}
	first_backw_aft(_DynSemInput_,9);
	first_backw_aft(_DynFunc_,8);
	first_backw_aft(_LetExpr_,7);
	first_backw_aft(_IfExpr_,6);
	first_backw_aft(_FuncAppl_,5);
	first_backw_aft(_Condition_,4);	mxz_sift_backw(4,9);
	first_backw_aft(_Attribute_,3);	mxz_sift_backw(3,9);
	first_backw_aft(_Function_,2);	mxz_sift_backw(2,9);
	first_backw_aft(_Predicate_,1);	mxz_sift_backw(1,9);
	while(mxz_heap[1].point!=mxs_nil(_c,0)) {
	switch(mxz_heap[1].ind) {
	case 1:
			mxe_intres_collect(mxz_heap[1].node);
		next_backw_aft(_Predicate_,1);	mxz_sift_backw(1,9);	break;
	case 2:
			mxe_intres_collect(mxz_heap[1].node);
		next_backw_aft(_Function_,2);	mxz_sift_backw(1,9);	break;
	case 3:
			mxe_intres_collect(mxz_heap[1].node);
		next_backw_aft(_Attribute_,3);	mxz_sift_backw(1,9);	break;
	case 4:
			mxe_intres_collect(mxz_heap[1].node);
		next_backw_aft(_Condition_,4);	mxz_sift_backw(1,9);	break;
	case 5:
			mxe_intres_collect(mxz_heap[1].node);
		next_backw_aft(_FuncAppl_,5);	mxz_sift_backw(1,9);	break;
	case 6:
			mxe_intres_collect(mxz_heap[1].node);
		next_backw_aft(_IfExpr_,6);	mxz_sift_backw(1,9);	break;
	case 7:
			mxe_intres_collect(mxz_heap[1].node);
		next_backw_aft(_LetExpr_,7);	mxz_sift_backw(1,9);	break;
	case 8:
			mxe_intres_collect(mxz_heap[1].node);
		next_backw_aft(_DynFunc_,8);	mxz_sift_backw(1,9);	break;
	case 9:
			mxe_intres_collect(mxz_heap[1].node);
		next_backw_aft(_DynSemInput_,9);	mxz_sift_backw(1,9);	break;
	}} /* endswitch, endwhile */

	return mxv_correct;
}



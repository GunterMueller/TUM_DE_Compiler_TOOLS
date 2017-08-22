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
#define  mxs_CharConst(f,l,P1,P2,P3)		mxi_tc(f,l,"CharConst",3,-26,-10,P1,-11,P2,-11,P3)
#define  mxs_IntConst(f,l,P1,P2,P3)		mxi_tc(f,l,"IntConst",3,-27,-11,P1,-11,P2,-11,P3)
#define  mxs_StringConst(f,l,P1,P2,P3)		mxi_tc(f,l,"StringConst",3,-28,-12,P1,-11,P2,-11,P3)
#define  mxs_SortConst(f,l,P1)		mxi_tc(f,l,"SortConst",1,-29,-147,P1)
#define  mxs_FuncAppl(f,l,P1,P2)		mxi_tc(f,l,"FuncAppl",2,-30,-45,P1,-97,P2)
#define  mxs_IfExpr(f,l,P1,P2,P3,P4)		mxi_tc(f,l,"IfExpr",4,-31,-140,P1,-137,P2,-11,P3,-11,P4)
#define  mxs_LetExpr(f,l,P1,P2,P3)		mxi_tc(f,l,"LetExpr",3,-32,-46,P1,-137,P2,-137,P3)
#define  mxs_StringExpr(f,l,P1,P2,P3)		mxi_tc(f,l,"StringExpr",3,-33,-97,P1,-11,P2,-11,P3)
#define  mxs_PatternCase(f,l,P1,P2)		mxi_tc(f,l,"PatternCase",2,-34,-41,P1,-137,P2)
#define  mxs_FormulaCase(f,l,P1,P2)		mxi_tc(f,l,"FormulaCase",2,-35,-141,P1,-137,P2)
#define  mxs_PredAppl(f,l,P1,P2)		mxi_tc(f,l,"PredAppl",2,-36,-45,P1,-97,P2)
#define  mxs_Or(f,l,P1,P2)		mxi_tc(f,l,"Or",2,-37,-141,P1,-141,P2)
#define  mxs_And(f,l,P1,P2)		mxi_tc(f,l,"And",2,-38,-141,P1,-141,P2)
#define  mxs_Impl(f,l,P1,P2)		mxi_tc(f,l,"Impl",2,-39,-141,P1,-141,P2)
#define  mxs_Neg(f,l,P1)		mxi_tc(f,l,"Neg",1,-40,-141,P1)
#define  mxs_Pattern(f,l,P1,P2,P3)		mxi_tc(f,l,"Pattern",3,-41,-142,P1,-143,P2,-144,P3)
#define  mxs_DefId(f,l,P1,P2,P3)		mxi_tc(f,l,"DefId",3,-42,-8,P1,-11,P2,-11,P3)
#define  mxs_TermSortId(f,l,P1,P2,P3)		mxi_tc(f,l,"TermSortId",3,-43,-8,P1,-11,P2,-11,P3)
#define  mxs_NodeSortId(f,l,P1,P2,P3)		mxi_tc(f,l,"NodeSortId",3,-44,-8,P1,-11,P2,-11,P3)
#define  mxs_ApplId(f,l,P1,P2,P3)		mxi_tc(f,l,"ApplId",3,-45,-8,P1,-11,P2,-11,P3)
#define  mxs_Name(f,l,P1,P2,P3)		mxi_tc(f,l,"Name",3,-46,-8,P1,-11,P2,-11,P3)
#define  mxs_Blank(f,l,P1)		mxi_tc(f,l,"Blank",1,-47,-11,P1)
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
		fprintf(stderr,"***** Error: Cannot allocate wait list element\n");
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
ELEMENT  mxs_id(char*,int,ELEMENT);
ELEMENT  mxs_patlineno(char*,int,ELEMENT);
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
	IFNIL(p) IS(p,_SortId_,f,l,"term_basesorts",1)
	return mxa_term_basesorts[mxs_index(_c,0,p,_SortId_)];
}
static ELEMENT   *mxa_node_basesorts;
static AttInstSq *mxw_node_basesorts;
ELEMENT  mxs_node_basesorts( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_SortId_,f,l,"node_basesorts",1)
	return mxa_node_basesorts[mxs_index(_c,0,p,_SortId_)];
}
static ELEMENT   *mxa_encl_scope;
ELEMENT  mxs_encl_scope( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Scope_,f,l,"encl_scope",1)
	return mxa_encl_scope[mxs_index(_c,0,p,_Scope_)];
}
static ELEMENT   *mxa_bind_pos;
ELEMENT  mxs_bind_pos( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Name_,f,l,"bind_pos",1)
	return mxa_bind_pos[mxs_index(_c,0,p,_Name_)];
}
static ELEMENT   *mxa_numberofastrks;
ELEMENT  mxs_numberofastrks( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ItemList_,f,l,"numberofastrks",1)
	return mxa_numberofastrks[mxs_index(_c,0,p,_ItemList_)];
}
static ELEMENT   *mxa_predeclprodcd;
ELEMENT  mxs_predeclprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_PredeclProd_,f,l,"predeclprodcd",1)
	return mxa_predeclprodcd[mxs_index(_c,0,p,_PredeclProd_)];
}
static ELEMENT   *mxa_tupelprodcd;
ELEMENT  mxs_tupelprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_TupelProd_,f,l,"tupelprodcd",1)
	return mxa_tupelprodcd[mxs_index(_c,0,p,_TupelProd_)];
}
static ELEMENT   *mxa_listprodcd;
ELEMENT  mxs_listprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ListProd_,f,l,"listprodcd",1)
	return mxa_listprodcd[mxs_index(_c,0,p,_ListProd_)];
}
static ELEMENT   *mxa_classprodcd;
ELEMENT  mxs_classprodcd( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ClassProd_,f,l,"classprodcd",1)
	return mxa_classprodcd[mxs_index(_c,0,p,_ClassProd_)];
}
static ELEMENT   *mxa_patnpos;
ELEMENT  mxs_patnpos( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Pattern_,f,l,"patnpos",1)
	return mxa_patnpos[mxs_index(_c,0,p,_Pattern_)];
}
static ELEMENT   *mxa_num_items;
ELEMENT  mxs_num_items( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Pattern_,f,l,"num_items",1)
	return mxa_num_items[mxs_index(_c,0,p,_Pattern_)];
}
static ELEMENT   *mxa_args;
ELEMENT  mxs_args( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"args",1)
	return mxa_args[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_caseexpr;
ELEMENT  mxs_caseexpr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IfCase_,f,l,"caseexpr",1)
	return mxa_caseexpr[mxs_index(_c,0,p,_IfCase_)];
}
static ELEMENT   *mxa_allexpr;
ELEMENT  mxs_allexpr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IfExpr_,f,l,"allexpr",1)
	return mxa_allexpr[mxs_index(_c,0,p,_IfExpr_)];
}
static ELEMENT   *mxa_encl_patterncase;
ELEMENT  mxs_encl_patterncase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Node,f,l,"encl_patterncase",1)
	return mxa_encl_patterncase[mxs_index(_c,0,p,_Node)];
}
static ELEMENT   *mxa_top_pattern;
ELEMENT  mxs_top_pattern( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Node,f,l,"top_pattern",1)
	return mxa_top_pattern[mxs_index(_c,0,p,_Node)];
}
static ELEMENT   *mxa_son_nr;
ELEMENT  mxs_son_nr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"son_nr",1)
	return mxa_son_nr[mxs_index(_c,0,p,_FctOrAtt_)];
}
static ELEMENT   *mxa_relacc_nr;
ELEMENT  mxs_relacc_nr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"relacc_nr",1)
	return mxa_relacc_nr[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_appl_list_formula;
ELEMENT  mxs_appl_list_formula( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Formula_,f,l,"appl_list_formula",1)
	return mxa_appl_list_formula[mxs_index(_c,0,p,_Formula_)];
}
static ELEMENT   *mxa_appl_list_case;
ELEMENT  mxs_appl_list_case( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Case_,f,l,"appl_list_case",1)
	return mxa_appl_list_case[mxs_index(_c,0,p,_Case_)];
}
static ELEMENT   *mxa_appl_list_expr;
ELEMENT  mxs_appl_list_expr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Expr_,f,l,"appl_list_expr",1)
	return mxa_appl_list_expr[mxs_index(_c,0,p,_Expr_)];
}
static ELEMENT   *mxa_appl_list;
ELEMENT  mxs_appl_list( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"appl_list",1)
	return mxa_appl_list[mxs_index(_c,0,p,_FctOrAtt_)];
}
static ELEMENT   *mxa_def_value;
ELEMENT  mxs_def_value( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_DefId_,f,l,"def_value",1)
	return mxa_def_value[mxs_index(_c,0,p,_DefId_)];
}
static ELEMENT   *mxa_node_parnr;
ELEMENT  mxs_node_parnr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAttDecl_,f,l,"node_parnr",1)
	return mxa_node_parnr[mxs_index(_c,0,p,_FctOrAttDecl_)];
}
static ELEMENT   *mxa_appl_value;
ELEMENT  mxs_appl_value( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"appl_value",1)
	return mxa_appl_value[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_nodepar_expr;
ELEMENT  mxs_nodepar_expr( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"nodepar_expr",1)
	return mxa_nodepar_expr[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_valueterm_list;
static AttInstSq *mxw_valueterm_list;
ELEMENT  mxs_valueterm_list( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Case_,f,l,"valueterm_list",1)
	return mxa_valueterm_list[mxs_index(_c,0,p,_Case_)];
}
static ELEMENT   *mxa_valueterm;
static AttInstSq *mxw_valueterm;
ELEMENT  mxs_valueterm( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Expr_,f,l,"valueterm",1)
	return mxa_valueterm[mxs_index(_c,0,p,_Expr_)];
}
static ELEMENT   *mxa_attr_list_matlist;
ELEMENT  mxs_attr_list_matlist( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuAtList_,f,l,"attr_list_matlist",1)
	return mxa_attr_list_matlist[mxs_index(_c,0,p,_FuAtList_)];
}
static ELEMENT   *mxa_result_value;
ELEMENT  mxs_result_value( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"result_value",1)
	return mxa_result_value[mxs_index(_c,0,p,_FctOrAtt_)];
}
static ELEMENT   *mxa_is_relev_att_access;
ELEMENT  mxs_is_relev_att_access( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"is_relev_att_access",1)
	return mxa_is_relev_att_access[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_appl_order;
ELEMENT  mxs_appl_order( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"appl_order",1)
	return mxa_appl_order[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_appl_relacc_list;
ELEMENT  mxs_appl_relacc_list( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"appl_relacc_list",1)
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
	IFNIL(p) IS(p,_IntResOrName_,f,l,"cgen_name",1)
	return mxa_cgen_name[mxs_index(_c,0,p,_IntResOrName_)];
}
static ELEMENT   *mxa_sces_appl;
ELEMENT  mxs_sces_appl( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_ApplyEntity_,f,l,"sces_appl",1)
	return mxa_sces_appl[mxs_index(_c,0,p,_ApplyEntity_)];
}
static ELEMENT   *mxa_sces1_cond;
ELEMENT  mxs_sces1_cond( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Condition_,f,l,"sces1_cond",1)
	return mxa_sces1_cond[mxs_index(_c,0,p,_Condition_)];
}
static ELEMENT   *mxa_sces2_cond;
ELEMENT  mxs_sces2_cond( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_Condition_,f,l,"sces2_cond",1)
	return mxa_sces2_cond[mxs_index(_c,0,p,_Condition_)];
}
static ELEMENT   *mxa_sces1_let;
ELEMENT  mxs_sces1_let( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_LetExpr_,f,l,"sces1_let",1)
	return mxa_sces1_let[mxs_index(_c,0,p,_LetExpr_)];
}
static ELEMENT   *mxa_sces2_let;
ELEMENT  mxs_sces2_let( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_LetExpr_,f,l,"sces2_let",1)
	return mxa_sces2_let[mxs_index(_c,0,p,_LetExpr_)];
}
static ELEMENT   *mxa_sces_if;
ELEMENT  mxs_sces_if( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IfExpr_,f,l,"sces_if",1)
	return mxa_sces_if[mxs_index(_c,0,p,_IfExpr_)];
}
static ELEMENT   *mxa_sces1_fcase;
ELEMENT  mxs_sces1_fcase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FormulaCase_,f,l,"sces1_fcase",1)
	return mxa_sces1_fcase[mxs_index(_c,0,p,_FormulaCase_)];
}
static ELEMENT   *mxa_sces2_fcase;
ELEMENT  mxs_sces2_fcase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FormulaCase_,f,l,"sces2_fcase",1)
	return mxa_sces2_fcase[mxs_index(_c,0,p,_FormulaCase_)];
}
static ELEMENT   *mxa_sces_pcase;
ELEMENT  mxs_sces_pcase( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_PatternCase_,f,l,"sces_pcase",1)
	return mxa_sces_pcase[mxs_index(_c,0,p,_PatternCase_)];
}
static ELEMENT   *mxa_sces_attacc;
ELEMENT  mxs_sces_attacc( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FuncAppl_,f,l,"sces_attacc",1)
	return mxa_sces_attacc[mxs_index(_c,0,p,_FuncAppl_)];
}
static ELEMENT   *mxa_lokvar_need;
ELEMENT  mxs_lokvar_need( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_FctOrAtt_,f,l,"lokvar_need",1)
	return mxa_lokvar_need[mxs_index(_c,0,p,_FctOrAtt_)];
}
static ELEMENT   *mxa_intres_collect;
ELEMENT  mxs_intres_collect( char *f, int l, ELEMENT p ){
	IFNIL(p) IS(p,_IntResExpr_,f,l,"intres_collect",1)
	return mxa_intres_collect[mxs_index(_c,0,p,_IntResExpr_)];
}



ELEMENT  mxs_encl_dynfunc(char *f, int l,ELEMENT N){
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

ELEMENT  mxs_id(char *f, int l,ELEMENT ID){
 IFNIL(ID)
 IS(ID,_Ident_,f,l,"id",1)
	return mxs_idtos(_m,317,mxs_term(_m,317,ID));
}

ELEMENT  mxs_patlineno(char *f, int l,ELEMENT PN){
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
			if( mxs_numsons(_c,0, mxv_IR ) != 1 ) goto Lp2;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp2;
			L_p5 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = L_p5;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp2;
			mxv_i2 = L_p5;
			goto L2;
		}
		Lp2: ;
			mxv_i2 = mxs_son(_m,319,mxs_itoe(_c,0,2),mxs_son(_m,319,mxs_itoe(_c,0,1),PN));
		L2: ;
	}
	return mxv_i2;
}

ELEMENT  mxs_decl(char *f, int l,ELEMENT UID){
 IFNIL(UID)
 IS(UID,_UsedId_,f,l,"decl",1)
	return mxs_subterm(_m,348,mxs_itoe(_c,0,1),mxs_idtodecls(_m,348,mxs_term(_m,348,mxs_son(_m,348,mxs_itoe(_c,0,1),UID))));
}

ELEMENT  mxs_sort_union(char *f, int l,ELEMENT X,ELEMENT Y){
ELEMENT mxv_i24, mxv_i23, mxv_i22;
 IFNIL(X) IFNIL(Y)
 IS(X,_DefIdNodeInfo,f,l,"sort_union",1) IS(Y,_DefIdNodeInfo,f,l,"sort_union",2)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,X,mxs_AllNodes(_m,371)) ){
			mxv_i23 = mxs_true(_m,0);
			goto L23;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,Y,mxs_AllNodes(_m,371)) ){
			mxv_i24 = mxs_true(_m,0);
			goto L24;
		}
		mxv_i24 = mxs_false(_m,0);
		L24: ;
	}
		mxv_i23 = mxv_i24;
		L23: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i23) ){
			mxv_i22 = mxs_AllNodes(_m,371);
			goto L22;
		}
		mxv_i22 = mxs_conc(_m,372,X,Y);
		L22: ;
	}
	return mxv_i22;
}

ELEMENT  mxs_scope(char *f, int l,ELEMENT N){
ELEMENT mxv_a243, mxv_a245, mxv_i48, L_p90;
 IFNIL(N)
 IS(N,_Node,f,l,"scope",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Scope_) ) goto Lp7;
			mxv_i48 = N;
			goto L48;
		}
		Lp7: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp8;
			L_p90 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = L_p90;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp8;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp8;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp8;
		{  /* Attribute access */
			mxv_a243 = mxs_scope(_m,454,mxs_fath(_m,454,L_p90));
		}
			mxv_i48 = mxv_a243;
			goto L48;
		}
		Lp8: ;
	{  /* Attribute access */
		mxv_a245 = mxs_scope(_m,455,mxs_fath(_m,455,N));
	}
			mxv_i48 = mxv_a245;
		L48: ;
	}
	return mxv_i48;
}

ELEMENT  mxs_lookup_params(char *f, int l,ELEMENT ID,ELEMENT N){
ELEMENT mxv_a253, mxv_i51, mxv_i50, IDN_p95;
 IFNIL(ID) IFNIL(N)
 IS(ID,_Ident,f,l,"lookup_params",1) IS(N,_Name_,f,l,"lookup_params",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp11;
			if( !mxs_is(_c,0,mxv_IR,_Name_) ) goto Lp11;
			IDN_p95 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = IDN_p95;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp11;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,ID,mxs_term(_m,465,IDN_p95)) ){
				mxv_i51 = N;
				goto L51;
			}
		{  /* Attribute access */
			mxv_a253 = mxs_lookup_params(_m,466,ID,mxs_rbroth(_m,466,N));
		}
			mxv_i51 = mxv_a253;
			L51: ;
		}
			mxv_i50 = mxv_i51;
			goto L50;
		}
		Lp11: ;
			mxv_i50 = mxs_nil(_m,467);
		L50: ;
	}
	return mxv_i50;
}

ELEMENT  mxs_lookup_item(char *f, int l,ELEMENT ID,ELEMENT IT){
ELEMENT mxv_a257, mxv_i53, mxv_a260, mxv_i52, ILP_p97, N_p98, IDN_p99, IT1_p102;
 IFNIL(ID) IFNIL(IT)
 IS(ID,_Ident,f,l,"lookup_item",1) IS(IT,_Item_,f,l,"lookup_item",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp12;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp12;
			ILP_p97 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ILP_p97;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp12;
			N_p98 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p98;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp12;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp12;
			IDN_p99 = mxs_son(_c,0,1,mxs_son(_c,0,3,mxv_anchor));
			mxv_IR = IDN_p99;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp12;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,ID,mxs_term(_m,472,IDN_p99)) ){
				mxv_i53 = N_p98;
				goto L53;
			}
			if( mxs_is(_m,473,ILP_p97,_ItemList_) ){
			{  /* Attribute access */
				mxv_a257 = mxs_lookup_items(_m,473,ID,mxs_son(_m,473,mxs_itoe(_c,0,1),ILP_p97));
			}
				mxv_i53 = mxv_a257;
				goto L53;
			}
			mxv_i53 = mxs_nil(_m,474);
			L53: ;
		}
			mxv_i52 = mxv_i53;
			goto L52;
		}
		Lp12: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp13;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp13;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp13;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp13;
			if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp13;
			IT1_p102 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = IT1_p102;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp13;
			mxv_IR = mxs_son(_c,0,3,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp13;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp13;
		{  /* Attribute access */
			mxv_a260 = mxs_lookup_items(_m,475,ID,IT1_p102);
		}
			mxv_i52 = mxv_a260;
			goto L52;
		}
		Lp13: ;
			mxv_i52 = mxs_nil(_m,476);
		L52: ;
	}
	return mxv_i52;
}

ELEMENT  mxs_lookup_items(char *f, int l,ELEMENT ID,ELEMENT IT){
ELEMENT mxv_a262, mxv_a264, mxv_i54, mxv_l5, N_l5;
 IFNIL(ID) IFNIL(IT)
 IS(ID,_Ident,f,l,"lookup_items",1) IS(IT,_Item_,f,l,"lookup_items",2)
	{  /* LetExpr */
		{  /* Attribute access */
			mxv_a262 = mxs_lookup_item(_m,480,ID,IT);
		}
		N_l5 = mxv_a262;
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,N_l5,mxs_nil(_m,481))) ){
				mxv_i54 = N_l5;
				goto L54;
			}
		{  /* Attribute access */
			mxv_a264 = mxs_lookup_items(_m,482,ID,mxs_rbroth(_m,482,IT));
		}
			mxv_i54 = mxv_a264;
			L54: ;
		}
		mxv_l5 = mxv_i54;
	}
	return mxv_l5;
}

ELEMENT  mxs_lookup_cond(char *f, int l,ELEMENT ID,ELEMENT PAT){
ELEMENT mxv_a268, mxv_i55, mxv_l6, N_l6;
 IFNIL(ID) IFNIL(PAT)
 IS(ID,_Ident,f,l,"lookup_cond",1) IS(PAT,_Pattern_,f,l,"lookup_cond",2)
	{  /* LetExpr */
		N_l6 = mxs_lookup_item(_m,486,ID,PAT);
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,N_l6,mxs_nil(_m,487))) ){
				mxv_i55 = N_l6;
				goto L55;
			}
		{  /* Attribute access */
			mxv_a268 = mxs_lookup_cond(_m,488,ID,mxs_rbroth(_m,488,PAT));
		}
			mxv_i55 = mxv_a268;
			L55: ;
		}
		mxv_l6 = mxv_i55;
	}
	return mxv_l6;
}

ELEMENT  mxs_lookup(char *f, int l,ELEMENT ID,ELEMENT S){
ELEMENT mxv_a271, mxv_i57, mxv_a275, mxv_i58, mxv_l7, L_l7, mxv_i56, N_p105, NID_p106, PAR_p109, PAT_p112, PAT_p114;
 IFNIL(ID) IFNIL(S)
 IS(ID,_Ident,f,l,"lookup",1) IS(S,_Scope_,f,l,"lookup",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp14;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp14;
			N_p105 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = N_p105;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp14;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp14;
			NID_p106 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = NID_p106;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp14;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_term(_m,493,NID_p106),ID) ){
				mxv_i57 = N_p105;
				goto L57;
			}
		{  /* Attribute access */
			mxv_a271 = mxs_lookup(_m,493,ID,mxs_encl_scope(_m,493,S));
		}
			mxv_i57 = mxv_a271;
			L57: ;
		}
			mxv_i56 = mxv_i57;
			goto L56;
		}
		Lp14: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 3 ) goto Lp15;
			if( !mxs_is(_c,0,mxv_IR,_ApplyEntity_) ) goto Lp15;
			mxv_IR = mxs_son(_c,0,3,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp15;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp15;
			PAR_p109 = mxs_son(_c,0,1,mxs_son(_c,0,3,mxv_anchor));
			mxv_IR = PAR_p109;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp15;
			mxv_i56 = mxs_lookup_params(_m,494,ID,PAR_p109);
			goto L56;
		}
		Lp15: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp16;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp16;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp16;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp16;
			PAT_p112 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = PAT_p112;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp16;
			mxv_i56 = mxs_lookup_cond(_m,495,ID,PAT_p112);
			goto L56;
		}
		Lp16: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp17;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp17;
			PAT_p114 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = PAT_p114;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp17;
		{  /* LetExpr */
			{  /* Attribute access */
				mxv_a275 = mxs_lookup(_m,497,ID,mxs_encl_scope(_m,497,S));
			}
			L_l7 = mxv_a275;
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,L_l7,mxs_nil(_m,498))) ){
					mxv_i58 = L_l7;
					goto L58;
				}
				mxv_i58 = mxs_lookup_item(_m,499,ID,PAT_p114);
				L58: ;
			}
			mxv_l7 = mxv_i58;
		}
			mxv_i56 = mxv_l7;
			goto L56;
		}
		Lp17: ;
			mxv_i56 = mxs_nil(_m,500);
		L56: ;
	}
	return mxv_i56;
}

ELEMENT  mxs_countastrks(char *f, int l,ELEMENT ITL,ELEMENT sum){
ELEMENT mxv_a353, mxv_a356, mxv_i67;
 IFNIL(ITL) IFNIL(sum)
 IS(ITL,_ItemList,f,l,"countastrks",1) IS(sum,_Int,f,l,"countastrks",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,ITL,mxs_ItemList(_m,536)) ){
			mxv_i67 = sum;
			goto L67;
		}
		if( mxs_is(_m,537,mxs_subterm(_m,537,mxs_itoe(_c,0,1),ITL),_Asterisk) ){
		{  /* Attribute access */
			mxv_a353 = mxs_countastrks(_m,537,mxs_back(_m,537,ITL),mxs_add(_m,537,sum,mxs_itoe(_c,0,1)));
		}
			mxv_i67 = mxv_a353;
			goto L67;
		}
	{  /* Attribute access */
		mxv_a356 = mxs_countastrks(_m,538,mxs_back(_m,538,ITL),sum);
	}
		mxv_i67 = mxv_a356;
		L67: ;
	}
	return mxv_i67;
}

ELEMENT  mxs_smallestlistprodcd(char *f, int l){
	return mxs_neg(_m,610,mxs_add(_m,610,mxs_number(_m,610,_ListProd_),mxs_add(_m,611,mxs_number(_m,611,_TupelProd_),mxs_sub(_m,611,mxs_number(_m,611,_PredeclProd_),mxs_itoe(_c,0,2)))));
}

ELEMENT  mxs_prodcd(char *f, int l,ELEMENT PN){
ELEMENT mxv_i82;
 IFNIL(PN)
 IS(PN,_Production_,f,l,"prodcd",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_PredeclProd_) ) goto Lp19;
			mxv_i82 = mxs_predeclprodcd(_m,618,PN);
			goto L82;
		}
		Lp19: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp20;
			mxv_i82 = mxs_classprodcd(_m,619,PN);
			goto L82;
		}
		Lp20: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_TupelProd_) ) goto Lp21;
			mxv_i82 = mxs_tupelprodcd(_m,620,PN);
			goto L82;
		}
		Lp21: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_ListProd_) ) goto Lp22;
			mxv_i82 = mxs_listprodcd(_m,621,PN);
			goto L82;
		}
		Lp22: ;
			mxv_i82 = mxs_nil(_m,622);
		L82: ;
	}
	return mxv_i82;
}

ELEMENT  mxs_next_left_pat(char *f, int l,ELEMENT IT){
ELEMENT mxv_a463, mxv_a464, mxv_i83, mxv_l11, LIT_l11;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"next_left_pat",1)
	{  /* LetExpr */
		LIT_l11 = mxs_lbroth(_m,634,IT);
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l11;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp23;
			{  /* Attribute access */
				mxv_a463 = mxs_next_left_pat(_m,635,LIT_l11);
			}
				mxv_i83 = mxv_a463;
				goto L83;
			}
			Lp23: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l11;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp24;
			{  /* Attribute access */
				mxv_a464 = mxs_next_left_pat(_m,636,LIT_l11);
			}
				mxv_i83 = mxv_a464;
				goto L83;
			}
			Lp24: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l11;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp25;
				mxv_i83 = LIT_l11;
				goto L83;
			}
			Lp25: ;
				mxv_i83 = mxs_nil(_m,638);
			L83: ;
		}
		mxv_l11 = mxv_i83;
	}
	return mxv_l11;
}

ELEMENT  mxs_patnposition(char *f, int l,ELEMENT IT,ELEMENT dist){
ELEMENT mxv_a467, mxv_a469, mxv_i84, mxv_l12, LIT_l12;
 IFNIL(IT) IFNIL(dist)
 IS(IT,_Item_,f,l,"patnposition",1) IS(dist,_Int,f,l,"patnposition",2)
	{  /* LetExpr */
		LIT_l12 = mxs_lbroth(_m,642,IT);
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l12;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp26;
			{  /* Attribute access */
				mxv_a467 = mxs_patnposition(_m,643,LIT_l12,mxs_add(_m,643,dist,mxs_itoe(_c,0,1)));
			}
				mxv_i84 = mxv_a467;
				goto L84;
			}
			Lp26: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l12;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp27;
			{  /* Attribute access */
				mxv_a469 = mxs_patnposition(_m,644,LIT_l12,dist);
			}
				mxv_i84 = mxv_a469;
				goto L84;
			}
			Lp27: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = LIT_l12;
				mxv_IR = mxv_anchor;
				if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp28;
				mxv_i84 = dist;
				goto L84;
			}
			Lp28: ;
				mxv_i84 = dist;
			L84: ;
		}
		mxv_l12 = mxv_i84;
	}
	return mxv_l12;
}

ELEMENT  mxs_next_pat_for_codegen(char *f, int l,ELEMENT PN){
ELEMENT mxv_i87, mxv_l13, NLP_l13, mxv_i86, SPN_p168, IT_p171;
 IFNIL(PN)
 IS(PN,_Pattern_,f,l,"next_pat_for_codegen",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp29;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp29;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp29;
			if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp29;
			SPN_p168 = mxs_son(_c,0,-1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = SPN_p168;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp29;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp29;
			mxv_i86 = SPN_p168;
			goto L86;
		}
		Lp29: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PN;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp30;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp30;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp30;
			if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp30;
			IT_p171 = mxs_son(_c,0,-1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = IT_p171;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp30;
		{  /* LetExpr */
			NLP_l13 = mxs_next_left_pat(_m,658,IT_p171);
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,NLP_l13,mxs_nil(_m,659))) ){
					mxv_i87 = NLP_l13;
					goto L87;
				}
				mxv_i87 = mxs_next_pat_upthetree(_m,659,PN);
				L87: ;
			}
			mxv_l13 = mxv_i87;
		}
			mxv_i86 = mxv_l13;
			goto L86;
		}
		Lp30: ;
			mxv_i86 = mxs_next_pat_upthetree(_m,660,PN);
		L86: ;
	}
	return mxv_i86;
}

ELEMENT  mxs_next_pat_upthetree(char *f, int l,ELEMENT PN){
ELEMENT mxv_a485, mxv_i88;
 IFNIL(PN)
 IS(PN,_Pattern_,f,l,"next_pat_upthetree",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,664,mxs_patnpos(_m,664,PN),_TopPosition) ){
			mxv_i88 = mxs_rbroth(_m,664,PN);
			goto L88;
		}
		if( mxs_is(_m,665,mxs_patnpos(_m,665,PN),_AbsPosition) ){
		{  /* Attribute access */
			mxv_a485 = mxs_next_pat_upthetree(_m,665,mxs_fath(_m,665,mxs_fath(_m,665,PN)));
		}
			mxv_i88 = mxv_a485;
			goto L88;
		}
		mxv_i88 = mxs_next_left_pat(_m,666,PN);
		L88: ;
	}
	return mxv_i88;
}

ELEMENT  mxs_pat_absoff_pos(char *f, int l,ELEMENT N){
ELEMENT mxv_a494, mxv_i89;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_absoff_pos",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,675,N),mxs_nil(_m,675)) ){
			mxv_i89 = mxs_itoe(_c,0,1);
			goto L89;
		}
		if( mxs_is(_m,676,mxs_lbroth(_m,676,N),_Asterisk_) ){
			mxv_i89 = mxs_nil(_m,676);
			goto L89;
		}
	{  /* Attribute access */
		mxv_a494 = mxs_pat_absoff_pos(_m,677,mxs_lbroth(_m,677,N));
	}
		mxv_i89 = mxs_add(_m,677,mxv_a494,mxs_itoe(_c,0,1));
		L89: ;
	}
	return mxv_i89;
}

ELEMENT  mxs_pat_reloff_pos(char *f, int l,ELEMENT N,ELEMENT target){
ELEMENT mxv_a502, mxv_i90;
 IFNIL(N) IFNIL(target)
 IS(N,_Item_,f,l,"pat_reloff_pos",1) IS(target,_Item_,f,l,"pat_reloff_pos",2)
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,681,mxs_fath(_m,681,N),_ItemList_)) ){
			mxv_i90 = mxs_nil(_m,681);
			goto L90;
		}
		if( mxs_is(_m,682,mxs_lbroth(_m,682,N),_Asterisk_) ){
			mxv_i90 = mxs_nil(_m,682);
			goto L90;
		}
		if( mxs_eq(_m,0,mxs_lbroth(_m,683,N),target) ){
			mxv_i90 = mxs_itoe(_c,0,1);
			goto L90;
		}
	{  /* Attribute access */
		mxv_a502 = mxs_pat_reloff_pos(_m,684,mxs_lbroth(_m,684,N),target);
	}
		mxv_i90 = mxs_add(_m,684,mxv_a502,mxs_itoe(_c,0,1));
		L90: ;
	}
	return mxv_i90;
}

ELEMENT  mxs_pat_absoff_neg(char *f, int l,ELEMENT N){
ELEMENT mxv_a509, mxv_i91;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_absoff_neg",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,691,N),mxs_nil(_m,691)) ){
			mxv_i91 = mxs_itoe(_c,0,-1);
			goto L91;
		}
		if( mxs_is(_m,692,mxs_rbroth(_m,692,N),_Asterisk_) ){
			mxv_i91 = mxs_nil(_m,692);
			goto L91;
		}
	{  /* Attribute access */
		mxv_a509 = mxs_pat_absoff_neg(_m,693,mxs_rbroth(_m,693,N));
	}
		mxv_i91 = mxs_sub(_m,693,mxv_a509,mxs_itoe(_c,0,1));
		L91: ;
	}
	return mxv_i91;
}

ELEMENT  mxs_pat_reloff_neg(char *f, int l,ELEMENT N,ELEMENT target){
ELEMENT mxv_a517, mxv_i92;
 IFNIL(N) IFNIL(target)
 IS(N,_Item_,f,l,"pat_reloff_neg",1) IS(target,_Item_,f,l,"pat_reloff_neg",2)
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,697,mxs_fath(_m,697,N),_ItemList_)) ){
			mxv_i92 = mxs_nil(_m,697);
			goto L92;
		}
		if( mxs_is(_m,698,mxs_rbroth(_m,698,N),_Asterisk_) ){
			mxv_i92 = mxs_nil(_m,698);
			goto L92;
		}
		if( mxs_eq(_m,0,mxs_rbroth(_m,699,N),target) ){
			mxv_i92 = mxs_itoe(_c,0,-1);
			goto L92;
		}
	{  /* Attribute access */
		mxv_a517 = mxs_pat_reloff_neg(_m,700,mxs_rbroth(_m,700,N),target);
	}
		mxv_i92 = mxs_sub(_m,700,mxv_a517,mxs_itoe(_c,0,1));
		L92: ;
	}
	return mxv_i92;
}

ELEMENT  mxs_pat_absoff(char *f, int l,ELEMENT N){
ELEMENT mxv_i93, mxv_l14, X_l14;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_absoff",1)
	{  /* LetExpr */
		X_l14 = mxs_pat_absoff_pos(_m,707,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,X_l14,mxs_nil(_m,708)) ){
				mxv_i93 = mxs_pat_absoff_neg(_m,708,N);
				goto L93;
			}
			mxv_i93 = X_l14;
			L93: ;
		}
		mxv_l14 = mxv_i93;
	}
	return mxv_l14;
}

ELEMENT  mxs_pat_reloff(char *f, int l,ELEMENT N,ELEMENT target){
ELEMENT mxv_i94, mxv_l15, X_l15;
 IFNIL(N) IFNIL(target)
 IS(N,_Item_,f,l,"pat_reloff",1) IS(target,_Item_,f,l,"pat_reloff",2)
	{  /* LetExpr */
		X_l15 = mxs_pat_reloff_pos(_m,712,N,target);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,X_l15,mxs_nil(_m,713)) ){
				mxv_i94 = mxs_pat_reloff_neg(_m,713,N,target);
				goto L94;
			}
			mxv_i94 = X_l15;
			L94: ;
		}
		mxv_l15 = mxv_i94;
	}
	return mxv_l15;
}

ELEMENT  mxs_abs_itempos(char *f, int l,ELEMENT N){
ELEMENT mxv_i95;
 IFNIL(N)
 IS(N,_Item_,f,l,"abs_itempos",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,721,mxs_fath(_m,721,N),_ItemList_) ){
			mxv_i95 = mxs_pat_absoff(_m,721,N);
			goto L95;
		}
		mxv_i95 = mxs_itoe(_c,0,0);
		L95: ;
	}
	return mxv_i95;
}

ELEMENT  mxs_lmin_itempos(char *f, int l,ELEMENT N){
ELEMENT mxv_i98, mxv_i97, mxv_a535, mxv_a538, mxv_i96;
 IFNIL(N)
 IS(N,_Item_,f,l,"lmin_itempos",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_lbroth(_m,725,N),mxs_nil(_m,725))) ){
			mxv_i97 = mxs_false(_m,0);
			goto L97;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,725,N,_Asterisk_)) ){
			mxv_i98 = mxs_true(_m,0);
			goto L98;
		}
		mxv_i98 = mxs_false(_m,0);
		L98: ;
	}
		mxv_i97 = mxv_i98;
		L97: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i97) ){
			mxv_i96 = mxs_itoe(_c,0,1);
			goto L96;
		}
		if( mxs_eq(_m,0,mxs_lbroth(_m,726,N),mxs_nil(_m,726)) ){
			mxv_i96 = mxs_itoe(_c,0,0);
			goto L96;
		}
		if( mxs_is(_m,727,N,_Asterisk_) ){
		{  /* Attribute access */
			mxv_a535 = mxs_lmin_itempos(_m,727,mxs_lbroth(_m,727,N));
		}
			mxv_i96 = mxv_a535;
			goto L96;
		}
	{  /* Attribute access */
		mxv_a538 = mxs_lmin_itempos(_m,728,mxs_lbroth(_m,728,N));
	}
		mxv_i96 = mxs_add(_m,728,mxv_a538,mxs_itoe(_c,0,1));
		L96: ;
	}
	return mxv_i96;
}

ELEMENT  mxs_rmin_itempos(char *f, int l,ELEMENT N){
ELEMENT mxv_i101, mxv_i100, mxv_a548, mxv_a551, mxv_i99;
 IFNIL(N)
 IS(N,_Item_,f,l,"rmin_itempos",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_rbroth(_m,731,N),mxs_nil(_m,731))) ){
			mxv_i100 = mxs_false(_m,0);
			goto L100;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,731,N,_Asterisk_)) ){
			mxv_i101 = mxs_true(_m,0);
			goto L101;
		}
		mxv_i101 = mxs_false(_m,0);
		L101: ;
	}
		mxv_i100 = mxv_i101;
		L100: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i100) ){
			mxv_i99 = mxs_itoe(_c,0,-1);
			goto L99;
		}
		if( mxs_eq(_m,0,mxs_rbroth(_m,732,N),mxs_nil(_m,732)) ){
			mxv_i99 = mxs_itoe(_c,0,0);
			goto L99;
		}
		if( mxs_is(_m,733,N,_Asterisk_) ){
		{  /* Attribute access */
			mxv_a548 = mxs_rmin_itempos(_m,733,mxs_rbroth(_m,733,N));
		}
			mxv_i99 = mxv_a548;
			goto L99;
		}
	{  /* Attribute access */
		mxv_a551 = mxs_rmin_itempos(_m,734,mxs_rbroth(_m,734,N));
	}
		mxv_i99 = mxs_sub(_m,734,mxv_a551,mxs_itoe(_c,0,1));
		L99: ;
	}
	return mxv_i99;
}

ELEMENT  mxs_path(char *f, int l,ELEMENT V,ELEMENT N){
ELEMENT mxv_i104, mxv_i103, mxv_l17, VR_l17, mxv_a576, mxv_a583, mxv_i105, mxv_i102, mxv_l16, VA_l16;
 IFNIL(V) IFNIL(N)
 IS(V,_Item_,f,l,"path",1) IS(N,_Item_,f,l,"path",2)
	{  /* LetExpr */
		VA_l16 = mxs_pat_absoff(_m,743,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_fath(_m,744,V),mxs_fath(_m,744,N)) ){
			{  /* LetExpr */
				VR_l17 = mxs_pat_reloff(_m,745,V,N);
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,V,N) ){
						mxv_i103 = mxs_Relationship(_m,746);
						goto L103;
					}
					if( ( ! mxs_eq(_m,0,VR_l17,mxs_nil(_m,747))) ){
					{  /* FormulaCaseList */
						if( mxs_lt(_m,748,mxs_itoe(_c,0,0),VR_l17) ){
							mxv_i104 = mxs_appfront(_m,748,mxs_Lbroth(_m,748,VR_l17),mxs_Relationship(_m,748));
							goto L104;
						}
						mxv_i104 = mxs_appfront(_m,749,mxs_Rbroth(_m,749,mxs_neg(_m,749,VR_l17)),mxs_Relationship(_m,749));
						L104: ;
					}
						mxv_i103 = mxv_i104;
						goto L103;
					}
					if( ( ! mxs_eq(_m,0,VA_l16,mxs_nil(_m,751))) ){
						mxv_i103 = mxs_appfront(_m,751,mxs_Son(_m,751,VA_l16),mxs_appfront(_m,751,mxs_Fath(_m,751),mxs_Relationship(_m,751)));
						goto L103;
					}
					mxv_i103 = mxs_nil(_m,752);
					L103: ;
				}
				mxv_l17 = mxv_i103;
			}
				mxv_i102 = mxv_l17;
				goto L102;
			}
			if( mxs_desc(_m,754,V,mxs_fath(_m,754,mxs_fath(_m,754,N))) ){
			{  /* Attribute access */
				mxv_a576 = mxs_path(_m,754,mxs_fath(_m,754,mxs_fath(_m,754,V)),N);
			}
				mxv_i102 = mxs_appback(_m,754,mxv_a576,mxs_Fath(_m,754));
				goto L102;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,VA_l16,mxs_nil(_m,756))) ){
			{  /* Attribute access */
				mxv_a583 = mxs_path(_m,756,V,mxs_fath(_m,756,mxs_fath(_m,756,N)));
			}
				mxv_i105 = mxs_appfront(_m,756,mxs_Son(_m,756,VA_l16),mxv_a583);
				goto L105;
			}
			mxv_i105 = mxs_nil(_m,757);
			L105: ;
		}
			mxv_i102 = mxv_i105;
			L102: ;
		}
		mxv_l16 = mxv_i102;
	}
	return mxv_l16;
}

ELEMENT  mxs_search_bound_names_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_a589, mxv_a591, mxv_a592, mxv_i106;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_bound_names_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,761,IT),mxs_nil(_m,761)) ){
		{  /* Attribute access */
			mxv_a589 = mxs_search_bound_names(_m,761,IT);
		}
			mxv_i106 = mxv_a589;
			goto L106;
		}
	{  /* Attribute access */
		mxv_a591 = mxs_search_bound_names(_m,762,IT);
	}
	{  /* Attribute access */
		mxv_a592 = mxs_search_bound_names_rec(_m,762,mxs_rbroth(_m,762,IT));
	}
		mxv_i106 = mxs_conc(_m,762,mxv_a591,mxv_a592);
		L106: ;
	}
	return mxv_i106;
}

ELEMENT  mxs_search_bound_names(char *f, int l,ELEMENT IT){
ELEMENT mxv_a594, mxv_i108, IT1_p176, mxv_i111, mxv_i110, mxv_i109, mxv_l18, BNL_l18, mxv_i107, ITL_p173, N_p174;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_bound_names",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp31;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp31;
			ITL_p173 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p173;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp31;
			N_p174 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p174;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp31;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p173;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp32;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp32;
					IT1_p176 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p176;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp32;
				{  /* Attribute access */
					mxv_a594 = mxs_search_bound_names_rec(_m,767,IT1_p176);
				}
					mxv_i108 = mxv_a594;
					goto L108;
				}
				Lp32: ;
					mxv_i108 = mxs_NameNList(_m,768);
				L108: ;
			}
			BNL_l18 = mxv_i108;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,770,N_p174,_Name_)) ){
					mxv_i110 = mxs_false(_m,0);
					goto L110;
				}
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,mxs_bind_pos(_m,770,N_p174),N_p174)) ){
					mxv_i111 = mxs_true(_m,0);
					goto L111;
				}
				mxv_i111 = mxs_false(_m,0);
				L111: ;
			}
				mxv_i110 = mxv_i111;
				L110: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i110) ){
					mxv_i109 = mxs_appfront(_m,770,N_p174,BNL_l18);
					goto L109;
				}
				mxv_i109 = BNL_l18;
				L109: ;
			}
			mxv_l18 = mxv_i109;
		}
			mxv_i107 = mxv_l18;
			goto L107;
		}
		Lp31: ;
			mxv_i107 = mxs_NameNList(_m,773);
		L107: ;
	}
	return mxv_i107;
}

ELEMENT  mxs_search_free_items_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_a605, mxv_a607, mxv_a608, mxv_i112;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_free_items_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,777,IT),mxs_nil(_m,777)) ){
		{  /* Attribute access */
			mxv_a605 = mxs_search_free_items(_m,777,IT);
		}
			mxv_i112 = mxv_a605;
			goto L112;
		}
	{  /* Attribute access */
		mxv_a607 = mxs_search_free_items(_m,778,IT);
	}
	{  /* Attribute access */
		mxv_a608 = mxs_search_free_items_rec(_m,778,mxs_rbroth(_m,778,IT));
	}
		mxv_i112 = mxs_conc(_m,778,mxv_a607,mxv_a608);
		L112: ;
	}
	return mxv_i112;
}

ELEMENT  mxs_search_free_items(char *f, int l,ELEMENT IT){
ELEMENT mxv_a610, mxv_i114, IT1_p181, mxv_i118, mxv_i117, mxv_i119, mxv_i116, mxv_i115, mxv_l19, FIL_l19, mxv_i113, ITL_p178, N_p179;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_free_items",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp33;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp33;
			ITL_p178 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p178;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp33;
			N_p179 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p179;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp33;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p178;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp34;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp34;
					IT1_p181 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p181;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp34;
				{  /* Attribute access */
					mxv_a610 = mxs_search_free_items_rec(_m,783,IT1_p181);
				}
					mxv_i114 = mxv_a610;
					goto L114;
				}
				Lp34: ;
					mxv_i114 = mxs_ItemNList(_m,784);
				L114: ;
			}
			FIL_l19 = mxv_i114;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,786,N_p179,_Name_)) ){
					mxv_i117 = mxs_false(_m,0);
					goto L117;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_bind_pos(_m,786,N_p179),N_p179) ){
					mxv_i118 = mxs_true(_m,0);
					goto L118;
				}
				mxv_i118 = mxs_false(_m,0);
				L118: ;
			}
				mxv_i117 = mxv_i118;
				L117: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i117) ){
					mxv_i116 = mxs_true(_m,0);
					goto L116;
				}
			{  /* FormulaCaseList */
				if( mxs_is(_m,786,N_p179,_Blank_) ){
					mxv_i119 = mxs_true(_m,0);
					goto L119;
				}
				mxv_i119 = mxs_false(_m,0);
				L119: ;
			}
				mxv_i116 = mxv_i119;
				L116: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i116) ){
					mxv_i115 = mxs_appfront(_m,787,IT,FIL_l19);
					goto L115;
				}
				mxv_i115 = FIL_l19;
				L115: ;
			}
			mxv_l19 = mxv_i115;
		}
			mxv_i113 = mxv_l19;
			goto L113;
		}
		Lp33: ;
			mxv_i113 = mxs_ItemNList(_m,790);
		L113: ;
	}
	return mxv_i113;
}

ELEMENT  mxs_search_blanks_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_a625, mxv_a627, mxv_a628, mxv_i120;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_blanks_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,794,IT),mxs_nil(_m,794)) ){
		{  /* Attribute access */
			mxv_a625 = mxs_search_blanks(_m,794,IT);
		}
			mxv_i120 = mxv_a625;
			goto L120;
		}
	{  /* Attribute access */
		mxv_a627 = mxs_search_blanks(_m,795,IT);
	}
	{  /* Attribute access */
		mxv_a628 = mxs_search_blanks_rec(_m,795,mxs_rbroth(_m,795,IT));
	}
		mxv_i120 = mxs_conc(_m,795,mxv_a627,mxv_a628);
		L120: ;
	}
	return mxv_i120;
}

ELEMENT  mxs_search_blanks(char *f, int l,ELEMENT IT){
ELEMENT mxv_a630, mxv_i122, IT1_p186, mxv_i121, ITL_p183, N_p184;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_blanks",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp35;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp35;
			ITL_p183 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p183;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp35;
			N_p184 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p184;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp35;
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = ITL_p183;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp36;
				if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp36;
				IT1_p186 = mxs_son(_c,0,1,mxv_anchor);
				mxv_IR = IT1_p186;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp36;
			{  /* Attribute access */
				mxv_a630 = mxs_search_blanks_rec(_m,800,IT1_p186);
			}
				mxv_i122 = mxv_a630;
				goto L122;
			}
			Lp36: ;
				mxv_i122 = mxs_ItemNList(_m,801);
			L122: ;
		}
			mxv_i121 = mxv_i122;
			goto L121;
		}
		Lp35: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Blank_) ) goto Lp37;
			mxv_i121 = mxs_appback(_m,803,mxs_ItemNList(_m,803),IT);
			goto L121;
		}
		Lp37: ;
			mxv_i121 = mxs_ItemNList(_m,805);
		L121: ;
	}
	return mxv_i121;
}

ELEMENT  mxs_search_free_p_names_rec(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_a696, mxv_a698, mxv_a699, mxv_i131;
 IFNIL(IT) IFNIL(ID)
 IS(IT,_Item_,f,l,"search_free_p_names_rec",1) IS(ID,_Ident,f,l,"search_free_p_names_rec",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,865,IT),mxs_nil(_m,865)) ){
		{  /* Attribute access */
			mxv_a696 = mxs_search_free_p_names(_m,865,IT,ID);
		}
			mxv_i131 = mxv_a696;
			goto L131;
		}
	{  /* Attribute access */
		mxv_a698 = mxs_search_free_p_names(_m,866,IT,ID);
	}
	{  /* Attribute access */
		mxv_a699 = mxs_search_free_p_names_rec(_m,866,mxs_rbroth(_m,866,IT),ID);
	}
		mxv_i131 = mxs_conc(_m,866,mxv_a698,mxv_a699);
		L131: ;
	}
	return mxv_i131;
}

ELEMENT  mxs_search_free_p_names(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_a701, mxv_i133, IT1_p204, mxv_i138, mxv_i137, mxv_i136, mxv_i135, mxv_i134, mxv_l21, PNL_l21, mxv_i132, ITL_p201, N_p202;
 IFNIL(IT) IFNIL(ID)
 IS(IT,_Item_,f,l,"search_free_p_names",1) IS(ID,_Ident,f,l,"search_free_p_names",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp39;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp39;
			ITL_p201 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p201;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp39;
			N_p202 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p202;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp39;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p201;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp40;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp40;
					IT1_p204 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p204;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp40;
				{  /* Attribute access */
					mxv_a701 = mxs_search_free_p_names_rec(_m,871,IT1_p204,ID);
				}
					mxv_i133 = mxv_a701;
					goto L133;
				}
				Lp40: ;
					mxv_i133 = mxs_ExprNList(_m,872);
				L133: ;
			}
			PNL_l21 = mxv_i133;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,874,N_p202,_Name_)) ){
					mxv_i135 = mxs_false(_m,0);
					goto L135;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! ( ! mxs_eq(_m,0,ID,mxs_term(_m,874,mxs_son(_m,874,mxs_itoe(_c,0,1),N_p202))))) ){
					mxv_i137 = mxs_false(_m,0);
					goto L137;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_bind_pos(_m,874,N_p202),N_p202) ){
					mxv_i138 = mxs_true(_m,0);
					goto L138;
				}
				mxv_i138 = mxs_false(_m,0);
				L138: ;
			}
				mxv_i137 = mxv_i138;
				L137: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i137) ){
					mxv_i136 = mxs_true(_m,0);
					goto L136;
				}
				mxv_i136 = mxs_false(_m,0);
				L136: ;
			}
				mxv_i135 = mxv_i136;
				L135: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i135) ){
					mxv_i134 = mxs_appfront(_m,874,N_p202,PNL_l21);
					goto L134;
				}
				mxv_i134 = PNL_l21;
				L134: ;
			}
			mxv_l21 = mxv_i134;
		}
			mxv_i132 = mxv_l21;
			goto L132;
		}
		Lp39: ;
			mxv_i132 = mxs_ExprNList(_m,877);
		L132: ;
	}
	return mxv_i132;
}

ELEMENT  mxs_search_bound_p_names_rec(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_a718, mxv_a720, mxv_a721, mxv_i139;
 IFNIL(IT) IFNIL(ID)
 IS(IT,_Item_,f,l,"search_bound_p_names_rec",1) IS(ID,_Ident,f,l,"search_bound_p_names_rec",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,881,IT),mxs_nil(_m,881)) ){
		{  /* Attribute access */
			mxv_a718 = mxs_search_bound_p_names(_m,881,IT,ID);
		}
			mxv_i139 = mxv_a718;
			goto L139;
		}
	{  /* Attribute access */
		mxv_a720 = mxs_search_bound_p_names(_m,882,IT,ID);
	}
	{  /* Attribute access */
		mxv_a721 = mxs_search_bound_p_names_rec(_m,882,mxs_rbroth(_m,882,IT),ID);
	}
		mxv_i139 = mxs_conc(_m,882,mxv_a720,mxv_a721);
		L139: ;
	}
	return mxv_i139;
}

ELEMENT  mxs_search_bound_p_names(char *f, int l,ELEMENT IT,ELEMENT ID){
ELEMENT mxv_a723, mxv_i141, IT1_p209, mxv_i146, mxv_i145, mxv_i144, mxv_i143, mxv_i142, mxv_l22, PNL_l22, mxv_i140, ITL_p206, N_p207;
 IFNIL(IT) IFNIL(ID)
 IS(IT,_Item_,f,l,"search_bound_p_names",1) IS(ID,_Ident,f,l,"search_bound_p_names",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp41;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp41;
			ITL_p206 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p206;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp41;
			N_p207 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p207;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp41;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p206;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp42;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp42;
					IT1_p209 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p209;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp42;
				{  /* Attribute access */
					mxv_a723 = mxs_search_bound_p_names_rec(_m,887,IT1_p209,ID);
				}
					mxv_i141 = mxv_a723;
					goto L141;
				}
				Lp42: ;
					mxv_i141 = mxs_ExprNList(_m,888);
				L141: ;
			}
			PNL_l22 = mxv_i141;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,890,N_p207,_Name_)) ){
					mxv_i143 = mxs_false(_m,0);
					goto L143;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! ( ! mxs_eq(_m,0,ID,mxs_term(_m,890,mxs_son(_m,890,mxs_itoe(_c,0,1),N_p207))))) ){
					mxv_i145 = mxs_false(_m,0);
					goto L145;
				}
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,mxs_bind_pos(_m,890,N_p207),N_p207)) ){
					mxv_i146 = mxs_true(_m,0);
					goto L146;
				}
				mxv_i146 = mxs_false(_m,0);
				L146: ;
			}
				mxv_i145 = mxv_i146;
				L145: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i145) ){
					mxv_i144 = mxs_true(_m,0);
					goto L144;
				}
				mxv_i144 = mxs_false(_m,0);
				L144: ;
			}
				mxv_i143 = mxv_i144;
				L143: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i143) ){
					mxv_i142 = mxs_appfront(_m,890,N_p207,PNL_l22);
					goto L142;
				}
				mxv_i142 = PNL_l22;
				L142: ;
			}
			mxv_l22 = mxv_i142;
		}
			mxv_i140 = mxv_l22;
			goto L140;
		}
		Lp41: ;
			mxv_i140 = mxs_ExprNList(_m,893);
		L140: ;
	}
	return mxv_i140;
}

ELEMENT  mxs_search_patt_names(char *f, int l,ELEMENT IT,ELEMENT ID){
 IFNIL(IT) IFNIL(ID)
 IS(IT,_Item_,f,l,"search_patt_names",1) IS(ID,_Ident,f,l,"search_patt_names",2)
	return mxs_conc(_m,897,mxs_search_bound_p_names(_m,897,IT,ID),mxs_search_free_p_names(_m,897,IT,ID));
}

ELEMENT  mxs_search_patt_sorts_rec(char *f, int l,ELEMENT IT){
ELEMENT mxv_a743, mxv_a745, mxv_a746, mxv_i147;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_patt_sorts_rec",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,901,IT),mxs_nil(_m,901)) ){
		{  /* Attribute access */
			mxv_a743 = mxs_search_patt_sorts(_m,901,IT);
		}
			mxv_i147 = mxv_a743;
			goto L147;
		}
	{  /* Attribute access */
		mxv_a745 = mxs_search_patt_sorts(_m,902,IT);
	}
	{  /* Attribute access */
		mxv_a746 = mxs_search_patt_sorts_rec(_m,902,mxs_rbroth(_m,902,IT));
	}
		mxv_i147 = mxs_conc(_m,902,mxv_a745,mxv_a746);
		L147: ;
	}
	return mxv_i147;
}

ELEMENT  mxs_search_patt_sorts(char *f, int l,ELEMENT IT){
ELEMENT mxv_a748, mxv_i149, IT1_p214, mxv_i150, mxv_l23, BNL_l23, mxv_i148, SORT_p211, ITL_p212;
 IFNIL(IT)
 IS(IT,_Item_,f,l,"search_patt_sorts",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp43;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp43;
			SORT_p211 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = SORT_p211;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp43;
			ITL_p212 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p212;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp43;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p212;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp44;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp44;
					IT1_p214 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p214;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp44;
				{  /* Attribute access */
					mxv_a748 = mxs_search_patt_sorts_rec(_m,906,IT1_p214);
				}
					mxv_i149 = mxv_a748;
					goto L149;
				}
				Lp44: ;
					mxv_i149 = mxs_SortIdNList(_m,907);
				L149: ;
			}
			BNL_l23 = mxv_i149;
			{  /* FormulaCaseList */
				if( mxs_is(_m,909,SORT_p211,_SortId_) ){
					mxv_i150 = mxs_appfront(_m,909,SORT_p211,BNL_l23);
					goto L150;
				}
				mxv_i150 = BNL_l23;
				L150: ;
			}
			mxv_l23 = mxv_i150;
		}
			mxv_i148 = mxv_l23;
			goto L148;
		}
		Lp43: ;
			mxv_i148 = mxs_SortIdNList(_m,912);
		L148: ;
	}
	return mxv_i148;
}

ELEMENT  mxs_search_name_in_patt_rec(char *f, int l,ELEMENT IT,ELEMENT NA){
ELEMENT mxv_a754, mxv_a756, mxv_a757, mxv_i151;
 IFNIL(IT) IFNIL(NA)
 IS(IT,_Item_,f,l,"search_name_in_patt_rec",1) IS(NA,_Ident,f,l,"search_name_in_patt_rec",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,916,IT),mxs_nil(_m,916)) ){
		{  /* Attribute access */
			mxv_a754 = mxs_search_name_in_patt(_m,916,IT,NA);
		}
			mxv_i151 = mxv_a754;
			goto L151;
		}
	{  /* Attribute access */
		mxv_a756 = mxs_search_name_in_patt(_m,917,IT,NA);
	}
	{  /* Attribute access */
		mxv_a757 = mxs_search_name_in_patt_rec(_m,917,mxs_rbroth(_m,917,IT),NA);
	}
		mxv_i151 = mxs_conc(_m,917,mxv_a756,mxv_a757);
		L151: ;
	}
	return mxv_i151;
}

ELEMENT  mxs_search_name_in_patt(char *f, int l,ELEMENT IT,ELEMENT NA){
ELEMENT mxv_a759, mxv_i153, IT1_p219, mxv_i156, mxv_i155, mxv_i154, mxv_l24, BNL_l24, mxv_i152, ITL_p216, N_p217;
 IFNIL(IT) IFNIL(NA)
 IS(IT,_Item_,f,l,"search_name_in_patt",1) IS(NA,_Ident,f,l,"search_name_in_patt",2)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = IT;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp45;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp45;
			ITL_p216 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = ITL_p216;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp45;
			N_p217 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = N_p217;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp45;
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = ITL_p216;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp46;
					if( !mxs_is(_c,0,mxv_IR,_ItemList_) ) goto Lp46;
					IT1_p219 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = IT1_p219;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp46;
				{  /* Attribute access */
					mxv_a759 = mxs_search_name_in_patt_rec(_m,922,IT1_p219,NA);
				}
					mxv_i153 = mxv_a759;
					goto L153;
				}
				Lp46: ;
					mxv_i153 = mxs_NameNList(_m,923);
				L153: ;
			}
			BNL_l24 = mxv_i153;
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,925,N_p217,_Name_)) ){
					mxv_i155 = mxs_false(_m,0);
					goto L155;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_term(_m,925,mxs_son(_m,925,mxs_itoe(_c,0,1),N_p217)),NA) ){
					mxv_i156 = mxs_true(_m,0);
					goto L156;
				}
				mxv_i156 = mxs_false(_m,0);
				L156: ;
			}
				mxv_i155 = mxv_i156;
				L155: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i155) ){
					mxv_i154 = mxs_appfront(_m,925,N_p217,BNL_l24);
					goto L154;
				}
				mxv_i154 = BNL_l24;
				L154: ;
			}
			mxv_l24 = mxv_i154;
		}
			mxv_i152 = mxv_l24;
			goto L152;
		}
		Lp45: ;
			mxv_i152 = mxs_NameNList(_m,928);
		L152: ;
	}
	return mxv_i152;
}

ELEMENT  mxs_latest_bindpos(char *f, int l,ELEMENT N,ELEMENT NA){
ELEMENT mxv_i159, mxv_i158, mxv_a782, mxv_i160, mxv_l26, LBP_l26, mxv_i157, mxv_l25, S_l25;
 IFNIL(N) IFNIL(NA)
 IS(N,_Node,f,l,"latest_bindpos",1) IS(NA,_Name_,f,l,"latest_bindpos",2)
	{  /* LetExpr */
		S_l25 = mxs_encl_patterncase(_m,932,N);
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! ( ! mxs_eq(_m,0,S_l25,mxs_nil(_m,933)))) ){
				mxv_i158 = mxs_false(_m,0);
				goto L158;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_desc(_m,933,mxs_bind_pos(_m,933,NA),S_l25)) ){
				mxv_i159 = mxs_true(_m,0);
				goto L159;
			}
			mxv_i159 = mxs_false(_m,0);
			L159: ;
		}
			mxv_i158 = mxv_i159;
			L158: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i158) ){
			{  /* LetExpr */
				LBP_l26 = mxs_search_name_in_patt(_m,934,mxs_son(_m,934,mxs_itoe(_c,0,1),S_l25),mxs_term(_m,934,mxs_son(_m,934,mxs_itoe(_c,0,1),NA)));
				{  /* FormulaCaseList */
					if( ( ! mxs_eq(_m,0,LBP_l26,mxs_NameNList(_m,935))) ){
						mxv_i160 = mxs_subterm(_m,935,mxs_itoe(_c,0,1),LBP_l26);
						goto L160;
					}
				{  /* Attribute access */
					mxv_a782 = mxs_latest_bindpos(_m,936,mxs_fath(_m,936,S_l25),NA);
				}
					mxv_i160 = mxv_a782;
					L160: ;
				}
				mxv_l26 = mxv_i160;
			}
				mxv_i157 = mxv_l26;
				goto L157;
			}
			mxv_i157 = mxs_bind_pos(_m,937,NA);
			L157: ;
		}
		mxv_l25 = mxv_i157;
	}
	return mxv_l25;
}

ELEMENT  mxs_par_pos(char *f, int l,ELEMENT N,ELEMENT cnt){
ELEMENT mxv_a787, mxv_i161;
 IFNIL(N) IFNIL(cnt)
 IS(N,_Name_,f,l,"par_pos",1) IS(cnt,_Int,f,l,"par_pos",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,941,N),mxs_nil(_m,941)) ){
			mxv_i161 = cnt;
			goto L161;
		}
	{  /* Attribute access */
		mxv_a787 = mxs_par_pos(_m,942,mxs_lbroth(_m,942,N),mxs_add(_m,942,mxs_itoe(_c,0,1),cnt));
	}
		mxv_i161 = mxv_a787;
		L161: ;
	}
	return mxv_i161;
}

ELEMENT  mxs_corresp_parsort(char *f, int l,ELEMENT N){
 IFNIL(N)
 IS(N,_Name_,f,l,"corresp_parsort",1)
	return mxs_son(_m,946,mxs_par_pos(_m,946,N,mxs_itoe(_c,0,1)),mxs_lbroth(_m,946,mxs_fath(_m,946,N)));
}

ELEMENT  mxs_actpar_pos(char *f, int l,ELEMENT N,ELEMENT cnt){
ELEMENT mxv_a796, mxv_i162;
 IFNIL(N) IFNIL(cnt)
 IS(N,_Expr_,f,l,"actpar_pos",1) IS(cnt,_Int,f,l,"actpar_pos",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,950,N),mxs_nil(_m,950)) ){
			mxv_i162 = cnt;
			goto L162;
		}
	{  /* Attribute access */
		mxv_a796 = mxs_actpar_pos(_m,951,mxs_lbroth(_m,951,N),mxs_add(_m,951,mxs_itoe(_c,0,1),cnt));
	}
		mxv_i162 = mxv_a796;
		L162: ;
	}
	return mxv_i162;
}

ELEMENT  mxs_univ_path(char *f, int l,ELEMENT V,ELEMENT N){
ELEMENT mxv_i165, mxv_i164, mxv_l28, VR_l28, mxv_a840, mxv_a854, mxv_a866, mxv_i166, mxv_i163, mxv_l27, VA_l27;
 IFNIL(V) IFNIL(N)
 IS(V,_Item_,f,l,"univ_path",1) IS(N,_Item_,f,l,"univ_path",2)
	{  /* LetExpr */
		VA_l27 = mxs_pat_absoff(_m,955,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_fath(_m,956,V),mxs_fath(_m,956,N)) ){
			{  /* LetExpr */
				VR_l28 = mxs_pat_reloff(_m,957,V,N);
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,V,N) ){
						mxv_i164 = mxs_Relationship(_m,958);
						goto L164;
					}
					if( ( ! mxs_eq(_m,0,VR_l28,mxs_nil(_m,959))) ){
					{  /* FormulaCaseList */
						if( mxs_lt(_m,960,mxs_itoe(_c,0,0),VR_l28) ){
							mxv_i165 = mxs_appfront(_m,960,mxs_Lbroth(_m,960,VR_l28),mxs_Relationship(_m,960));
							goto L165;
						}
						mxv_i165 = mxs_appfront(_m,961,mxs_Rbroth(_m,961,mxs_neg(_m,961,VR_l28)),mxs_Relationship(_m,961));
						L165: ;
					}
						mxv_i164 = mxv_i165;
						goto L164;
					}
					if( ( ! mxs_eq(_m,0,VA_l27,mxs_nil(_m,963))) ){
						mxv_i164 = mxs_appfront(_m,963,mxs_SonTC(_m,963,VA_l27,mxs_lmin_itempos(_m,963,N),mxs_rmin_itempos(_m,963,N),mxs_num_items(_m,964,mxs_fath(_m,964,mxs_fath(_m,964,N))),mxs_numberofastrks(_m,964,mxs_fath(_m,964,N))),mxs_appfront(_m,965,mxs_Fath(_m,965),mxs_Relationship(_m,965)));
						goto L164;
					}
					mxv_i164 = mxs_appfront(_m,966,mxs_SonTC(_m,966,mxs_itoe(_c,0,0),mxs_lmin_itempos(_m,966,N),mxs_rmin_itempos(_m,966,N),mxs_num_items(_m,967,mxs_fath(_m,967,mxs_fath(_m,967,N))),mxs_numberofastrks(_m,967,mxs_fath(_m,967,N))),mxs_appfront(_m,968,mxs_Fath(_m,968),mxs_Relationship(_m,968)));
					L164: ;
				}
				mxv_l28 = mxv_i164;
			}
				mxv_i163 = mxv_l28;
				goto L163;
			}
			if( mxs_desc(_m,970,V,mxs_fath(_m,970,mxs_fath(_m,970,N))) ){
			{  /* Attribute access */
				mxv_a840 = mxs_univ_path(_m,970,mxs_fath(_m,970,mxs_fath(_m,970,V)),N);
			}
				mxv_i163 = mxs_appback(_m,970,mxv_a840,mxs_Fath(_m,970));
				goto L163;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,VA_l27,mxs_nil(_m,972))) ){
			{  /* Attribute access */
				mxv_a854 = mxs_univ_path(_m,974,V,mxs_fath(_m,974,mxs_fath(_m,974,N)));
			}
				mxv_i166 = mxs_appfront(_m,972,mxs_SonTC(_m,972,VA_l27,mxs_lmin_itempos(_m,972,N),mxs_rmin_itempos(_m,972,N),mxs_num_items(_m,973,mxs_fath(_m,973,mxs_fath(_m,973,N))),mxs_numberofastrks(_m,973,mxs_fath(_m,973,N))),mxv_a854);
				goto L166;
			}
		{  /* Attribute access */
			mxv_a866 = mxs_univ_path(_m,977,V,mxs_fath(_m,977,mxs_fath(_m,977,N)));
		}
			mxv_i166 = mxs_appfront(_m,975,mxs_SonTC(_m,975,mxs_itoe(_c,0,0),mxs_lmin_itempos(_m,975,N),mxs_rmin_itempos(_m,975,N),mxs_num_items(_m,976,mxs_fath(_m,976,mxs_fath(_m,976,N))),mxs_numberofastrks(_m,976,mxs_fath(_m,976,N))),mxv_a866);
			L166: ;
		}
			mxv_i163 = mxv_i166;
			L163: ;
		}
		mxv_l27 = mxv_i163;
	}
	return mxv_l27;
}

ELEMENT  mxs_mk_enl(char *f, int l,ELEMENT ARG){
ELEMENT mxv_a874, mxv_i167;
 IFNIL(ARG)
 IS(ARG,_Expr_,f,l,"mk_enl",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,981,ARG),mxs_nil(_m,981)) ){
			mxv_i167 = mxs_appfront(_m,981,ARG,mxs_ExprNList(_m,981));
			goto L167;
		}
	{  /* Attribute access */
		mxv_a874 = mxs_mk_enl(_m,982,mxs_rbroth(_m,982,ARG));
	}
		mxv_i167 = mxs_appfront(_m,982,ARG,mxv_a874);
		L167: ;
	}
	return mxv_i167;
}

ELEMENT  mxs_dep_expr(char *f, int l,ELEMENT E){
ELEMENT mxv_i170, mxv_i169, mxv_i171, mxv_i168;
 IFNIL(E)
 IS(E,_Expr_,f,l,"dep_expr",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Name_) ) goto Lp47;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_bind_pos(_m,987,E),E) ){
			{  /* FormulaCaseList */
				if( mxs_is(_m,989,mxs_fath(_m,989,E),_NameList_) ){
					mxv_i170 = mxs_ExprNList(_m,989);
					goto L170;
				}
				if( mxs_is(_m,990,mxs_fath(_m,990,E),_LetExpr_) ){
					mxv_i170 = mxs_appfront(_m,990,mxs_rbroth(_m,990,E),mxs_ExprNList(_m,990));
					goto L170;
				}
				mxv_i170 = mxs_search_bound_p_names(_m,991,mxs_top_pattern(_m,991,E),mxs_term(_m,991,mxs_son(_m,991,mxs_itoe(_c,0,1),E)));
				L170: ;
			}
				mxv_i169 = mxv_i170;
				goto L169;
			}
			mxv_i169 = mxs_appfront(_m,993,mxs_latest_bindpos(_m,993,E,E),mxs_ExprNList(_m,993));
			L169: ;
		}
			mxv_i168 = mxv_i169;
			goto L168;
		}
		Lp47: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp48;
			mxv_i168 = mxs_allexpr(_m,995,E);
			goto L168;
		}
		Lp48: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp49;
			mxv_i168 = mxs_appfront(_m,997,mxs_son(_m,997,mxs_itoe(_c,0,3),E),mxs_ExprNList(_m,997));
			goto L168;
		}
		Lp49: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp50;
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,mxs_numsons(_m,999,mxs_son(_m,999,mxs_itoe(_c,0,2),E)),mxs_itoe(_c,0,0))) ){
				mxv_i171 = mxs_mk_enl(_m,999,mxs_son(_m,999,mxs_itoe(_c,0,1),mxs_son(_m,999,mxs_itoe(_c,0,2),E)));
				goto L171;
			}
			mxv_i171 = mxs_ExprNList(_m,1000);
			L171: ;
		}
			mxv_i168 = mxv_i171;
			goto L168;
		}
		Lp50: ;
			mxv_i168 = mxs_ExprNList(_m,1002);
		L168: ;
	}
	return mxv_i168;
}

ELEMENT  mxs_lineof(char *f, int l,ELEMENT E){
ELEMENT mxv_a909, mxv_i172;
 IFNIL(E)
 IS(E,_Expr_,f,l,"lineof",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_SortConst_) ) goto Lp51;
			mxv_i172 = mxs_term(_m,1006,mxs_son(_m,1006,mxs_itoe(_c,0,2),mxs_son(_m,1006,mxs_itoe(_c,0,1),E)));
			goto L172;
		}
		Lp51: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp52;
			mxv_i172 = mxs_term(_m,1007,mxs_son(_m,1007,mxs_itoe(_c,0,2),mxs_son(_m,1007,mxs_itoe(_c,0,1),E)));
			goto L172;
		}
		Lp52: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp53;
			mxv_i172 = mxs_term(_m,1008,mxs_son(_m,1008,mxs_itoe(_c,0,3),E));
			goto L172;
		}
		Lp53: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp54;
		{  /* Attribute access */
			mxv_a909 = mxs_lineof(_m,1009,mxs_son(_m,1009,mxs_itoe(_c,0,3),E));
		}
			mxv_i172 = mxv_a909;
			goto L172;
		}
		Lp54: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_StringExpr_) ) goto Lp55;
			mxv_i172 = mxs_term(_m,1010,mxs_son(_m,1010,mxs_itoe(_c,0,2),E));
			goto L172;
		}
		Lp55: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_DynUndef_) ) goto Lp56;
			mxv_i172 = mxs_itoe(_c,0,0);
			goto L172;
		}
		Lp56: ;
			mxv_i172 = mxs_term(_m,1012,mxs_son(_m,1012,mxs_itoe(_c,0,2),E));
		L172: ;
	}
	return mxv_i172;
}

ELEMENT  mxs_colof(char *f, int l,ELEMENT E){
ELEMENT mxv_a923, mxv_i173;
 IFNIL(E)
 IS(E,_Expr_,f,l,"colof",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_SortConst_) ) goto Lp57;
			mxv_i173 = mxs_term(_m,1016,mxs_son(_m,1016,mxs_itoe(_c,0,3),mxs_son(_m,1016,mxs_itoe(_c,0,1),E)));
			goto L173;
		}
		Lp57: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp58;
			mxv_i173 = mxs_term(_m,1017,mxs_son(_m,1017,mxs_itoe(_c,0,3),mxs_son(_m,1017,mxs_itoe(_c,0,1),E)));
			goto L173;
		}
		Lp58: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp59;
			mxv_i173 = mxs_term(_m,1018,mxs_son(_m,1018,mxs_itoe(_c,0,4),E));
			goto L173;
		}
		Lp59: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp60;
		{  /* Attribute access */
			mxv_a923 = mxs_colof(_m,1019,mxs_son(_m,1019,mxs_itoe(_c,0,3),E));
		}
			mxv_i173 = mxv_a923;
			goto L173;
		}
		Lp60: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_StringExpr_) ) goto Lp61;
			mxv_i173 = mxs_term(_m,1020,mxs_son(_m,1020,mxs_itoe(_c,0,3),E));
			goto L173;
		}
		Lp61: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = E;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_DynUndef_) ) goto Lp62;
			mxv_i173 = mxs_itoe(_c,0,0);
			goto L173;
		}
		Lp62: ;
			mxv_i173 = mxs_term(_m,1022,mxs_son(_m,1022,mxs_itoe(_c,0,3),E));
		L173: ;
	}
	return mxv_i173;
}

ELEMENT  mxs_TW_identabb(char *f, int l){
	return mxs_FList(_m,1032);
}

ELEMENT  mxs_TW_emptyset(char *f, int l){
	return mxs_OrValue(_m,1034);
}

ELEMENT  mxs_TW_or(char *f, int l,ELEMENT S,ELEMENT T){
ELEMENT mxv_i175, mxv_i177, mxv_i176, mxv_l29, S1_l29, mxv_i174;
 IFNIL(S) IFNIL(T)
 IS(S,_Value,f,l,"TW_or",1) IS(T,_Value,f,l,"TW_or",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,S,mxs_OrValue(_m,1037)) ){
			mxv_i174 = T;
			goto L174;
		}
		if( mxs_eq(_m,0,T,mxs_OrValue(_m,1038)) ){
			mxv_i174 = S;
			goto L174;
		}
	{  /* LetExpr */
		{  /* FormulaCaseList */
			if( mxs_is(_m,1040,S,_OrValue) ){
				mxv_i175 = S;
				goto L175;
			}
			mxv_i175 = mxs_appback(_m,1040,mxs_OrValue(_m,1040),S);
			L175: ;
		}
		S1_l29 = mxv_i175;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_subterm(_m,1041,mxs_itoe(_c,0,-1),S1_l29),T) ){
				mxv_i176 = S;
				goto L176;
			}
		{  /* FormulaCaseList */
			if( mxs_is(_m,1043,T,_OrValue) ){
				mxv_i177 = mxs_conc(_m,1043,S1_l29,T);
				goto L177;
			}
			mxv_i177 = mxs_appback(_m,1044,S1_l29,T);
			L177: ;
		}
			mxv_i176 = mxv_i177;
			L176: ;
		}
		mxv_l29 = mxv_i176;
	}
		mxv_i174 = mxv_l29;
		L174: ;
	}
	return mxv_i174;
}

ELEMENT  mxs_delete_id(char *f, int l,ELEMENT T){
ELEMENT mxv_i180, mxv_i179, mxv_a946, mxv_a948, mxv_i178;
 IFNIL(T)
 IS(T,_Value,f,l,"delete_id",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TW_identabb(_m,1047)) ){
			mxv_i179 = mxs_true(_m,0);
			goto L179;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TW_emptyset(_m,1047)) ){
			mxv_i180 = mxs_true(_m,0);
			goto L180;
		}
		mxv_i180 = mxs_false(_m,0);
		L180: ;
	}
		mxv_i179 = mxv_i180;
		L179: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i179) ){
			mxv_i178 = mxs_TW_emptyset(_m,1047);
			goto L178;
		}
		if( mxs_is(_m,1048,T,_OrValue) ){
		{  /* Attribute access */
			mxv_a946 = mxs_delete_id(_m,1048,mxs_subterm(_m,1048,mxs_itoe(_c,0,1),T));
		}
		{  /* Attribute access */
			mxv_a948 = mxs_delete_id(_m,1048,mxs_back(_m,1048,T));
		}
			mxv_i178 = mxs_TW_or(_m,1048,mxv_a946,mxv_a948);
			goto L178;
		}
		mxv_i178 = T;
		L178: ;
	}
	return mxv_i178;
}

ELEMENT  mxs_TW_closure(char *f, int l,ELEMENT T){
ELEMENT mxv_i181, mxv_l30, T1_l30;
 IFNIL(T)
 IS(T,_Value,f,l,"TW_closure",1)
	{  /* LetExpr */
		T1_l30 = mxs_delete_id(_m,1052,T);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T1_l30,mxs_TW_emptyset(_m,1053)) ){
				mxv_i181 = mxs_TW_identabb(_m,1053);
				goto L181;
			}
			if( mxs_is(_m,1054,T1_l30,_FClosure) ){
				mxv_i181 = T1_l30;
				goto L181;
			}
			mxv_i181 = mxs_FClosure(_m,1055,T1_l30);
			L181: ;
		}
		mxv_l30 = mxv_i181;
	}
	return mxv_l30;
}

ELEMENT  mxs_TW_conc(char *f, int l,ELEMENT S,ELEMENT T){
ELEMENT mxv_i184, mxv_i183, mxv_i185, mxv_i186, mxv_i187, mxv_l33, C_l33, mxv_l32, T1_l32, mxv_l31, S1_l31, mxv_i182;
 IFNIL(S) IFNIL(T)
 IS(S,_Value,f,l,"TW_conc",1) IS(T,_Value,f,l,"TW_conc",2)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,S,mxs_TW_emptyset(_m,1059)) ){
			mxv_i183 = mxs_true(_m,0);
			goto L183;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TW_emptyset(_m,1059)) ){
			mxv_i184 = mxs_true(_m,0);
			goto L184;
		}
		mxv_i184 = mxs_false(_m,0);
		L184: ;
	}
		mxv_i183 = mxv_i184;
		L183: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i183) ){
			mxv_i182 = mxs_TW_emptyset(_m,1059);
			goto L182;
		}
	{  /* LetExpr */
		{  /* FormulaCaseList */
			if( mxs_is(_m,1061,S,_FList) ){
				mxv_i185 = S;
				goto L185;
			}
			mxv_i185 = mxs_appfront(_m,1061,S,mxs_TW_identabb(_m,1061));
			L185: ;
		}
		S1_l31 = mxv_i185;
		{  /* LetExpr */
			{  /* FormulaCaseList */
				if( mxs_is(_m,1062,T,_FList) ){
					mxv_i186 = T;
					goto L186;
				}
				mxv_i186 = mxs_appfront(_m,1062,T,mxs_TW_identabb(_m,1062));
				L186: ;
			}
			T1_l32 = mxv_i186;
			{  /* LetExpr */
				C_l33 = mxs_conc(_m,1063,S1_l31,T1_l32);
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,mxs_numsubterms(_m,1064,C_l33),mxs_itoe(_c,0,1)) ){
						mxv_i187 = mxs_subterm(_m,1064,mxs_itoe(_c,0,1),C_l33);
						goto L187;
					}
					mxv_i187 = C_l33;
					L187: ;
				}
				mxv_l33 = mxv_i187;
			}
			mxv_l32 = mxv_l33;
		}
		mxv_l31 = mxv_l32;
	}
		mxv_i182 = mxv_l31;
		L182: ;
	}
	return mxv_i182;
}

ELEMENT  mxs_node_parnr_fct(char *f, int l,ELEMENT N){
ELEMENT mxv_a1051, mxv_i209;
 IFNIL(N)
 IS(N,_SortId_,f,l,"node_parnr_fct",1)
	{  /* FormulaCaseList */
		if( mxs_is_node(_m,1151,N) ){
			mxv_i209 = mxs_itoe(_c,0,1);
			goto L209;
		}
		if( mxs_is(_m,1152,mxs_rbroth(_m,1152,N),_SortId_) ){
		{  /* Attribute access */
			mxv_a1051 = mxs_node_parnr_fct(_m,1152,mxs_rbroth(_m,1152,N));
		}
			mxv_i209 = mxs_add(_m,1152,mxs_itoe(_c,0,1),mxv_a1051);
			goto L209;
		}
		mxv_i209 = mxs_nil(_m,1153);
		L209: ;
	}
	return mxv_i209;
}

ELEMENT  mxs_encl_patcase(char *f, int l,ELEMENT N){
ELEMENT mxv_a1076, mxv_i216;
 IFNIL(N)
 IS(N,_Node,f,l,"encl_patcase",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp76;
			mxv_i216 = N;
			goto L216;
		}
		Lp76: ;
	{  /* Attribute access */
		mxv_a1076 = mxs_encl_patcase(_m,1182,mxs_fath(_m,1182,N));
	}
			mxv_i216 = mxv_a1076;
		L216: ;
	}
	return mxv_i216;
}

ELEMENT  mxs_pat_son_pos_nr(char *f, int l,ELEMENT N){
ELEMENT mxv_a1082, mxv_i217;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_son_pos_nr",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,1186,N),mxs_nil(_m,1186)) ){
			mxv_i217 = mxs_itoe(_c,0,1);
			goto L217;
		}
		if( mxs_is(_m,1187,mxs_lbroth(_m,1187,N),_Asterisk_) ){
			mxv_i217 = mxs_itoe(_c,0,0);
			goto L217;
		}
	{  /* Attribute access */
		mxv_a1082 = mxs_pat_son_pos_nr(_m,1188,mxs_lbroth(_m,1188,N));
	}
		mxv_i217 = mxs_add(_m,1188,mxv_a1082,mxs_itoe(_c,0,1));
		L217: ;
	}
	return mxv_i217;
}

ELEMENT  mxs_pat_son_neg_nr(char *f, int l,ELEMENT N){
ELEMENT mxv_a1088, mxv_i218;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_son_neg_nr",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,1191,N),mxs_nil(_m,1191)) ){
			mxv_i218 = mxs_itoe(_c,0,-1);
			goto L218;
		}
		if( mxs_is(_m,1192,mxs_rbroth(_m,1192,N),_Asterisk_) ){
			mxv_i218 = mxs_itoe(_c,0,0);
			goto L218;
		}
	{  /* Attribute access */
		mxv_a1088 = mxs_pat_son_neg_nr(_m,1193,mxs_rbroth(_m,1193,N));
	}
		mxv_i218 = mxs_sub(_m,1193,mxv_a1088,mxs_itoe(_c,0,1));
		L218: ;
	}
	return mxv_i218;
}

ELEMENT  mxs_pat_son_nr(char *f, int l,ELEMENT N){
ELEMENT mxv_i220, mxv_i219, mxv_l40, X_l40;
 IFNIL(N)
 IS(N,_Item_,f,l,"pat_son_nr",1)
	{  /* LetExpr */
		X_l40 = mxs_pat_son_pos_nr(_m,1196,N);
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,X_l40,mxs_itoe(_c,0,1)) ){
				mxv_i219 = mxs_itoe(_c,0,1);
				goto L219;
			}
			if( mxs_eq(_m,0,X_l40,mxs_itoe(_c,0,0)) ){
				mxv_i219 = mxs_pat_son_neg_nr(_m,1198,N);
				goto L219;
			}
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_pat_son_neg_nr(_m,1199,N),mxs_itoe(_c,0,-1)) ){
				mxv_i220 = mxs_itoe(_c,0,-1);
				goto L220;
			}
			mxv_i220 = X_l40;
			L220: ;
		}
			mxv_i219 = mxv_i220;
			L219: ;
		}
		mxv_l40 = mxv_i219;
	}
	return mxv_l40;
}

ELEMENT  mxs_pat_way(char *f, int l,ELEMENT V,ELEMENT N){
ELEMENT mxv_a1100, mxv_a1103, mxv_i223, mxv_a1111, mxv_a1114, mxv_i224, mxv_i222, mxv_a1122, mxv_a1126, mxv_i221;
 IFNIL(V) IFNIL(N)
 IS(V,_Item_,f,l,"pat_way",1) IS(N,_Item_,f,l,"pat_way",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_fath(_m,1203,V),mxs_fath(_m,1203,N)) ){
		{  /* FormulaCaseList */
			if( mxs_bef(_m,1204,mxs_before(_m,1204,V),mxs_before(_m,1204,N)) ){
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = V;
					mxv_IR = mxv_anchor;
					if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp77;
				{  /* Attribute access */
					mxv_a1100 = mxs_pat_way(_m,1206,mxs_rbroth(_m,1206,V),N);
				}
					mxv_i223 = mxs_TW_conc(_m,1206,mxs_TW_closure(_m,1206,mxs_TWrbroth(_m,1206)),mxv_a1100);
					goto L223;
				}
				Lp77: ;
			{  /* Attribute access */
				mxv_a1103 = mxs_pat_way(_m,1207,mxs_rbroth(_m,1207,V),N);
			}
					mxv_i223 = mxs_TW_conc(_m,1207,mxv_a1103,mxs_TWrbroth(_m,1207));
				L223: ;
			}
				mxv_i222 = mxv_i223;
				goto L222;
			}
			if( mxs_aft(_m,1208,mxs_before(_m,1208,V),mxs_before(_m,1208,N)) ){
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = V;
					mxv_IR = mxv_anchor;
					if( !mxs_is(_c,0,mxv_IR,_Asterisk_) ) goto Lp78;
				{  /* Attribute access */
					mxv_a1111 = mxs_pat_way(_m,1210,mxs_lbroth(_m,1210,V),N);
				}
					mxv_i224 = mxs_TW_conc(_m,1210,mxs_TW_closure(_m,1210,mxs_TWlbroth(_m,1210)),mxv_a1111);
					goto L224;
				}
				Lp78: ;
			{  /* Attribute access */
				mxv_a1114 = mxs_pat_way(_m,1211,mxs_lbroth(_m,1211,V),N);
			}
					mxv_i224 = mxs_TW_conc(_m,1211,mxv_a1114,mxs_TWlbroth(_m,1211));
				L224: ;
			}
				mxv_i222 = mxv_i224;
				goto L222;
			}
			mxv_i222 = mxs_TW_identabb(_m,1212);
			L222: ;
		}
			mxv_i221 = mxv_i222;
			goto L221;
		}
		if( mxs_desc(_m,1213,V,mxs_fath(_m,1213,mxs_fath(_m,1213,N))) ){
		{  /* Attribute access */
			mxv_a1122 = mxs_pat_way(_m,1213,mxs_fath(_m,1213,mxs_fath(_m,1213,V)),N);
		}
			mxv_i221 = mxs_TW_conc(_m,1213,mxs_TWfath(_m,1213),mxv_a1122);
			goto L221;
		}
	{  /* Attribute access */
		mxv_a1126 = mxs_pat_way(_m,1214,V,mxs_fath(_m,1214,mxs_fath(_m,1214,N)));
	}
		mxv_i221 = mxs_TW_conc(_m,1214,mxv_a1126,mxs_TWson(_m,1214,mxs_pat_son_nr(_m,1214,N)));
		L221: ;
	}
	return mxv_i221;
}

ELEMENT  mxs_enter_attrgroup(char *f, int l,ELEMENT J,ELEMENT ANL,ELEMENT M){
ELEMENT mxv_a1172, mxv_i230;
 IFNIL(J) IFNIL(ANL) IFNIL(M)
 IS(J,_Int,f,l,"enter_attrgroup",1) IS(ANL,_FuAtNodeList,f,l,"enter_attrgroup",2) IS(M,_Reference,f,l,"enter_attrgroup",3)
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1251,mxs_numsubterms(_m,1251,ANL),J) ){
			mxv_i230 = mxs_warshall_value(_m,1251,M,mxs_numsubterms(_m,1251,ANL));
			goto L230;
		}
	{  /* Attribute access */
		mxv_a1172 = mxs_enter_attrgroup(_m,1253,mxs_add(_m,1253,J,mxs_itoe(_c,0,1)),ANL,mxs_enter_attribute(_m,1254,mxs_sub(_m,1254,J,mxs_itoe(_c,0,1)),mxs_subterm(_m,1254,J,ANL),M,mxs_numsubterms(_m,1254,ANL)));
	}
		mxv_i230 = mxv_a1172;
		L230: ;
	}
	return mxv_i230;
}

ELEMENT  mxs_enter_attrgroup_list(char *f, int l,ELEMENT I,ELEMENT ALI,ELEMENT ALM){
ELEMENT mxv_a1179, mxv_i231;
 IFNIL(I) IFNIL(ALI) IFNIL(ALM)
 IS(I,_Int,f,l,"enter_attrgroup_list",1) IS(ALI,_FuAtListInfo,f,l,"enter_attrgroup_list",2) IS(ALM,_RefList,f,l,"enter_attrgroup_list",3)
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1258,mxs_numsubterms(_m,1258,ALI),I) ){
			mxv_i231 = ALM;
			goto L231;
		}
	{  /* Attribute access */
		mxv_a1179 = mxs_enter_attrgroup_list(_m,1259,mxs_add(_m,1259,I,mxs_itoe(_c,0,1)),ALI,mxs_appback(_m,1260,ALM,mxs_enter_attrgroup(_m,1261,mxs_itoe(_c,0,1),mxs_subterm(_m,1261,I,ALI),mxs_init_matrix(_m,1262,mxs_numsubterms(_m,1262,mxs_subterm(_m,1262,I,ALI))))));
	}
		mxv_i231 = mxv_a1179;
		L231: ;
	}
	return mxv_i231;
}

ELEMENT  mxs_simplify_closure(char *f, int l,ELEMENT T){
ELEMENT mxv_i234, mxv_i233, mxv_a1206, mxv_i236, mxv_i235, mxv_i240, mxv_i239, mxv_i244, mxv_i243, mxv_i247, mxv_i246, mxv_i245, mxv_i242, mxv_i241, mxv_i238, mxv_a1242, mxv_l45, X_l45, mxv_i237, mxv_l44, H_l44, mxv_l43, V_l43, mxv_i232;
 IFNIL(T)
 IS(T,_Value,f,l,"simplify_closure",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1287,T,_FList)) ){
			mxv_i233 = mxs_false(_m,0);
			goto L233;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_itoe(_c,0,1),mxs_numsubterms(_m,1287,T)) ){
			mxv_i234 = mxs_true(_m,0);
			goto L234;
		}
		mxv_i234 = mxs_false(_m,0);
		L234: ;
	}
		mxv_i233 = mxv_i234;
		L233: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i233) ){
		{  /* Attribute access */
			mxv_a1206 = mxs_simplify_closure(_m,1287,mxs_subterm(_m,1287,mxs_itoe(_c,0,1),T));
		}
			mxv_i232 = mxv_a1206;
			goto L232;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1288,T,_FList)) ){
			mxv_i235 = mxs_false(_m,0);
			goto L235;
		}
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1288,mxs_itoe(_c,0,1),mxs_numsubterms(_m,1288,T)) ){
			mxv_i236 = mxs_true(_m,0);
			goto L236;
		}
		mxv_i236 = mxs_false(_m,0);
		L236: ;
	}
		mxv_i235 = mxv_i236;
		L235: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i235) ){
		{  /* LetExpr */
			V_l43 = mxs_subterm(_m,1289,mxs_itoe(_c,0,1),T);
			{  /* LetExpr */
				H_l44 = mxs_subterm(_m,1290,mxs_itoe(_c,0,-1),T);
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1291,V_l43,_TWfath)) ){
						mxv_i239 = mxs_false(_m,0);
						goto L239;
					}
				{  /* FormulaCaseList */
					if( mxs_is(_m,1291,H_l44,_TWson) ){
						mxv_i240 = mxs_true(_m,0);
						goto L240;
					}
					mxv_i240 = mxs_false(_m,0);
					L240: ;
				}
					mxv_i239 = mxv_i240;
					L239: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i239) ){
						mxv_i238 = mxs_true(_m,0);
						goto L238;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1292,V_l43,_TWrbroth)) ){
						mxv_i243 = mxs_false(_m,0);
						goto L243;
					}
				{  /* FormulaCaseList */
					if( mxs_is(_m,1292,H_l44,_TWlbroth) ){
						mxv_i244 = mxs_true(_m,0);
						goto L244;
					}
					mxv_i244 = mxs_false(_m,0);
					L244: ;
				}
					mxv_i243 = mxv_i244;
					L243: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i243) ){
						mxv_i242 = mxs_true(_m,0);
						goto L242;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1293,V_l43,_TWlbroth)) ){
						mxv_i246 = mxs_false(_m,0);
						goto L246;
					}
				{  /* FormulaCaseList */
					if( mxs_is(_m,1293,H_l44,_TWrbroth) ){
						mxv_i247 = mxs_true(_m,0);
						goto L247;
					}
					mxv_i247 = mxs_false(_m,0);
					L247: ;
				}
					mxv_i246 = mxv_i247;
					L246: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i246) ){
						mxv_i245 = mxs_true(_m,0);
						goto L245;
					}
					mxv_i245 = mxs_false(_m,0);
					L245: ;
				}
					mxv_i242 = mxv_i245;
					L242: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i242) ){
						mxv_i241 = mxs_true(_m,0);
						goto L241;
					}
					mxv_i241 = mxs_false(_m,0);
					L241: ;
				}
					mxv_i238 = mxv_i241;
					L238: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i238) ){
					{  /* LetExpr */
						X_l45 = mxs_back(_m,1294,mxs_front(_m,1294,T));
						{  /* Attribute access */
							mxv_a1242 = mxs_simplify_closure(_m,1297,X_l45);
						}
						mxv_l45 = mxs_TW_or(_m,1295,mxs_TW_identabb(_m,1295),mxs_TW_conc(_m,1296,mxs_TW_conc(_m,1296,V_l43,X_l45),mxs_TW_conc(_m,1297,mxv_a1242,H_l44)));
					}
						mxv_i237 = mxv_l45;
						goto L237;
					}
					mxv_i237 = mxs_FClosure(_m,1299,T);
					L237: ;
				}
				mxv_l44 = mxv_i237;
			}
			mxv_l43 = mxv_l44;
		}
			mxv_i232 = mxv_l43;
			goto L232;
		}
		mxv_i232 = mxs_FClosure(_m,1300,T);
		L232: ;
	}
	return mxv_i232;
}

ELEMENT  mxs_normal_tw(char *f, int l,ELEMENT R,ELEMENT S,ELEMENT T){
ELEMENT mxv_i279, mxv_i282, mxv_i283, mxv_i281, mxv_l46, RN_l46, mxv_i280, mxv_i284, mxv_i285, mxv_i278;
 IFNIL(R) IFNIL(S) IFNIL(T)
 IS(R,_FList,f,l,"normal_tw",1) IS(S,_Value,f,l,"normal_tw",2) IS(T,_FValue,f,l,"normal_tw",3)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1312,S,_TWfath) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWson(_m,1313,mxs_itoe(_c,0,1))) ){
				mxv_i279 = mxs_appback(_m,1313,R,mxs_FClosure(_m,1313,mxs_TWlbroth(_m,1313)));
				goto L279;
			}
			mxv_i279 = mxs_appback(_m,1314,R,mxs_FClosure(_m,1314,mxs_TWrbroth(_m,1314)));
			L279: ;
		}
			mxv_i278 = mxv_i279;
			goto L278;
		}
		if( mxs_is(_m,1316,S,_TWson) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWfath(_m,1317)) ){
				mxv_i280 = mxs_FList(_m,1317);
				goto L280;
			}
		{  /* LetExpr */
			RN_l46 = mxs_subterm(_m,1319,mxs_itoe(_c,0,1),S);
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,T,mxs_TWrbroth(_m,1320)) ){
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,0)) ){
						mxv_i282 = mxs_appback(_m,1321,R,S);
						goto L282;
					}
					if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,-1)) ){
						mxv_i282 = mxs_TW_emptyset(_m,1322);
						goto L282;
					}
					mxv_i282 = mxs_appback(_m,1323,R,mxs_TWson(_m,1323,mxs_add(_m,1323,RN_l46,mxs_itoe(_c,0,1))));
					L282: ;
				}
					mxv_i281 = mxv_i282;
					goto L281;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,0)) ){
					mxv_i283 = mxs_appback(_m,1325,R,S);
					goto L283;
				}
				if( mxs_eq(_m,0,RN_l46,mxs_itoe(_c,0,1)) ){
					mxv_i283 = mxs_TW_emptyset(_m,1326);
					goto L283;
				}
				mxv_i283 = mxs_appback(_m,1327,R,mxs_TWson(_m,1327,mxs_sub(_m,1327,RN_l46,mxs_itoe(_c,0,1))));
				L283: ;
			}
				mxv_i281 = mxv_i283;
				L281: ;
			}
			mxv_l46 = mxv_i281;
		}
			mxv_i280 = mxv_l46;
			L280: ;
		}
			mxv_i278 = mxv_i280;
			goto L278;
		}
		if( mxs_is(_m,1329,S,_TWlbroth) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWrbroth(_m,1330)) ){
				mxv_i284 = R;
				goto L284;
			}
			mxv_i284 = mxs_appback(_m,1331,R,mxs_TWfath(_m,1331));
			L284: ;
		}
			mxv_i278 = mxv_i284;
			goto L278;
		}
		if( mxs_is(_m,1333,S,_TWrbroth) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,T,mxs_TWlbroth(_m,1334)) ){
				mxv_i285 = R;
				goto L285;
			}
			mxv_i285 = mxs_appback(_m,1335,R,mxs_TWfath(_m,1335));
			L285: ;
		}
			mxv_i278 = mxv_i285;
			goto L278;
		}
		if( mxs_is(_m,1337,S,_FClosure) ){
			mxv_i278 = mxs_appback(_m,1338,R,mxs_TWfath(_m,1338));
			goto L278;
		}
		mxv_i278 = mxs_nil(_m,1340);
		L278: ;
	}
	return mxv_i278;
}

ELEMENT  mxs_normal_closure(char *f, int l,ELEMENT R,ELEMENT T){
ELEMENT mxv_i287, mxv_i286;
 IFNIL(R) IFNIL(T)
 IS(R,_FList,f,l,"normal_closure",1) IS(T,_FClosure,f,l,"normal_closure",2)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,R,mxs_FList(_m,1344)) ){
			mxv_i286 = T;
			goto L286;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_subterm(_m,1346,mxs_itoe(_c,0,-1),R),mxs_subterm(_m,1346,mxs_itoe(_c,0,1),T)) ){
			mxv_i287 = mxs_TW_conc(_m,1346,mxs_normal_closure(_m,1346,mxs_front(_m,1346,R),T),mxs_subterm(_m,1346,mxs_itoe(_c,0,1),T));
			goto L287;
		}
		mxv_i287 = mxs_appback(_m,1347,R,T);
		L287: ;
	}
		mxv_i286 = mxv_i287;
		L286: ;
	}
	return mxv_i286;
}

ELEMENT  mxs_normalform(char *f, int l,ELEMENT R,ELEMENT T,ELEMENT N){
ELEMENT mxv_i293, mxv_i292, mxv_i294, mxv_i291, mxv_i290, mxv_l47, Z_l47, mxv_i289, mxv_i295, mxv_i299, mxv_i298, mxv_i300, mxv_i297, mxv_l48, N1_l48, mxv_i296, mxv_i301, mxv_l49, V_l49, mxv_i288;
 IFNIL(R) IFNIL(T) IFNIL(N)
 IS(R,_FList,f,l,"normalform",1) IS(T,_Value,f,l,"normalform",2) IS(N,_FuAtList_,f,l,"normalform",3)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1351,T,_DefId_) ){
			mxv_i288 = mxs_normalform(_m,1352,R,mxs_result_value(_m,1352,mxs_fath(_m,1352,T)),mxs_fath(_m,1352,mxs_fath(_m,1352,T)));
			goto L288;
		}
		if( mxs_is(_m,1354,T,_RelevAcc) ){
			mxv_i288 = mxs_normalform(_m,1355,R,mxs_result_value(_m,1355,mxs_son(_m,1355,mxs_subterm(_m,1355,mxs_itoe(_c,0,1),T),N)),N);
			goto L288;
		}
		if( mxs_is(_m,1357,T,_FValue) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,R,mxs_FList(_m,1358)) ){
				mxv_i289 = T;
				goto L289;
			}
		{  /* LetExpr */
			Z_l47 = mxs_subterm(_m,1360,mxs_itoe(_c,0,-1),R);
			{  /* FormulaCaseList */
				if( mxs_simplification(_m,1361,Z_l47,T) ){
					mxv_i290 = mxs_normal_tw(_m,1361,mxs_front(_m,1361,R),Z_l47,T);
					goto L290;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_lt(_m,1363,mxs_itoe(_c,0,1),mxs_numsubterms(_m,1363,R))) ){
					mxv_i292 = mxs_false(_m,0);
					goto L292;
				}
			{  /* FormulaCaseList */
				if( mxs_is(_m,1363,Z_l47,_FClosure) ){
					mxv_i293 = mxs_true(_m,0);
					goto L293;
				}
				mxv_i293 = mxs_false(_m,0);
				L293: ;
			}
				mxv_i292 = mxv_i293;
				L292: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i292) ){
				{  /* FormulaCaseList */
					if( mxs_simplification(_m,1364,mxs_subterm(_m,1364,mxs_itoe(_c,0,-2),R),T) ){
						mxv_i294 = mxs_TW_or(_m,1365,mxs_normal_tw(_m,1365,mxs_front(_m,1365,mxs_front(_m,1365,R)),mxs_subterm(_m,1365,mxs_itoe(_c,0,-2),R),T),mxs_normalform(_m,1366,mxs_appback(_m,1366,mxs_front(_m,1366,R),mxs_subterm(_m,1366,mxs_itoe(_c,0,1),Z_l47)),mxs_TW_conc(_m,1366,Z_l47,T),N));
						goto L294;
					}
					mxv_i294 = mxs_appback(_m,1368,R,T);
					L294: ;
				}
					mxv_i291 = mxv_i294;
					goto L291;
				}
				mxv_i291 = mxs_appback(_m,1369,R,T);
				L291: ;
			}
				mxv_i290 = mxv_i291;
				L290: ;
			}
			mxv_l47 = mxv_i290;
		}
			mxv_i289 = mxv_l47;
			L289: ;
		}
			mxv_i288 = mxv_i289;
			goto L288;
		}
		if( mxs_is(_m,1371,T,_OrValue) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1372,T),mxs_itoe(_c,0,0)) ){
				mxv_i295 = mxs_TW_emptyset(_m,1372);
				goto L295;
			}
			mxv_i295 = mxs_TW_or(_m,1373,mxs_normalform(_m,1373,R,mxs_subterm(_m,1373,mxs_itoe(_c,0,1),T),N),mxs_normalform(_m,1373,R,mxs_back(_m,1373,T),N));
			L295: ;
		}
			mxv_i288 = mxv_i295;
			goto L288;
		}
		if( mxs_is(_m,1375,T,_FList) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1376,T),mxs_itoe(_c,0,0)) ){
				mxv_i296 = R;
				goto L296;
			}
		{  /* LetExpr */
			N1_l48 = mxs_normalform(_m,1378,R,mxs_subterm(_m,1378,mxs_itoe(_c,0,1),T),N);
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,N1_l48,mxs_TW_emptyset(_m,1379)) ){
					mxv_i298 = mxs_true(_m,0);
					goto L298;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,N1_l48,mxs_nil(_m,1379)) ){
					mxv_i299 = mxs_true(_m,0);
					goto L299;
				}
				mxv_i299 = mxs_false(_m,0);
				L299: ;
			}
				mxv_i298 = mxv_i299;
				L298: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i298) ){
					mxv_i297 = N1_l48;
					goto L297;
				}
			{  /* FormulaCaseList */
				if( mxs_is(_m,1380,N1_l48,_FList) ){
					mxv_i300 = N1_l48;
					goto L300;
				}
				mxv_i300 = mxs_appback(_m,1381,mxs_FList(_m,1381),N1_l48);
				L300: ;
			}
				mxv_i297 = mxs_normalform(_m,1380,mxv_i300,mxs_back(_m,1381,T),N);
				L297: ;
			}
			mxv_l48 = mxv_i297;
		}
			mxv_i296 = mxv_l48;
			L296: ;
		}
			mxv_i288 = mxv_i296;
			goto L288;
		}
		if( mxs_is(_m,1383,T,_FClosure) ){
		{  /* LetExpr */
			V_l49 = mxs_simplify_closure(_m,1384,mxs_normalform(_m,1384,mxs_FList(_m,1384),mxs_subterm(_m,1384,mxs_itoe(_c,0,1),T),N));
			{  /* FormulaCaseList */
				if( mxs_is(_m,1385,V_l49,_FClosure) ){
					mxv_i301 = mxs_normal_closure(_m,1385,R,V_l49);
					goto L301;
				}
				mxv_i301 = mxs_normalform(_m,1386,R,V_l49,N);
				L301: ;
			}
			mxv_l49 = mxv_i301;
		}
			mxv_i288 = mxv_l49;
			goto L288;
		}
		mxv_i288 = mxs_nil(_m,1388);
		L288: ;
	}
	return mxv_i288;
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
ELEMENT mxv_a1423, mxv_a1428, mxv_a1430, mxv_i303, mxv_a1435, mxv_a1437, mxv_i304, mxv_i302;
 IFNIL(T)
 IS(T,_Value,f,l,"val_order",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1412,T,_TWson) ){
			mxv_i302 = mxs_Ord_son(_m,1412);
			goto L302;
		}
		if( mxs_is(_m,1413,T,_TWfath) ){
			mxv_i302 = mxs_Ord_fath(_m,1413);
			goto L302;
		}
		if( mxs_is(_m,1414,T,_TWrbroth) ){
			mxv_i302 = mxs_Ord_rbroth(_m,1414);
			goto L302;
		}
		if( mxs_is(_m,1415,T,_TWlbroth) ){
			mxv_i302 = mxs_Ord_lbroth(_m,1415);
			goto L302;
		}
		if( mxs_is(_m,1416,T,_FClosure) ){
		{  /* Attribute access */
			mxv_a1423 = mxs_val_order(_m,1416,mxs_subterm(_m,1416,mxs_itoe(_c,0,1),T));
		}
			mxv_i302 = mxs_OrdOp_closure(_m,1416,mxv_a1423);
			goto L302;
		}
		if( mxs_is(_m,1417,T,_FList) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1418,T),mxs_itoe(_c,0,0)) ){
				mxv_i303 = mxs_Ord_ident(_m,1418);
				goto L303;
			}
		{  /* Attribute access */
			mxv_a1428 = mxs_val_order(_m,1419,mxs_subterm(_m,1419,mxs_itoe(_c,0,1),T));
		}
		{  /* Attribute access */
			mxv_a1430 = mxs_val_order(_m,1419,mxs_back(_m,1419,T));
		}
			mxv_i303 = mxs_OrdOp_conc(_m,1419,mxv_a1428,mxv_a1430);
			L303: ;
		}
			mxv_i302 = mxv_i303;
			goto L302;
		}
		if( mxs_is(_m,1420,T,_OrValue) ){
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,1421,T),mxs_itoe(_c,0,0)) ){
				mxv_i304 = mxs_Ord_neutral(_m,1421);
				goto L304;
			}
		{  /* Attribute access */
			mxv_a1435 = mxs_val_order(_m,1422,mxs_subterm(_m,1422,mxs_itoe(_c,0,1),T));
		}
		{  /* Attribute access */
			mxv_a1437 = mxs_val_order(_m,1422,mxs_back(_m,1422,T));
		}
			mxv_i304 = mxs_OrdOp_or(_m,1422,mxv_a1435,mxv_a1437);
			L304: ;
		}
			mxv_i302 = mxv_i304;
			goto L302;
		}
		mxv_i302 = mxs_Ord_nothing(_m,1424);
		L302: ;
	}
	return mxv_i302;
}

ELEMENT  mxs_contains_attr(char *f, int l,ELEMENT FAL){
ELEMENT mxv_a1444, mxv_i305;
 IFNIL(FAL)
 IS(FAL,_FuAtNodeList,f,l,"contains_attr",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,FAL,mxs_FuAtNodeList(_m,1435)) ){
			mxv_i305 = mxs_false(_m,1435);
			goto L305;
		}
		if( mxs_is(_m,1436,mxs_subterm(_m,1436,mxs_itoe(_c,0,1),FAL),_Attribute_) ){
			mxv_i305 = mxs_true(_m,1436);
			goto L305;
		}
	{  /* Attribute access */
		mxv_a1444 = mxs_contains_attr(_m,1437,mxs_back(_m,1437,FAL));
	}
		mxv_i305 = mxv_a1444;
		L305: ;
	}
	return mxv_i305;
}

ELEMENT  mxs_encl_fctoratt(char *f, int l,ELEMENT N){
ELEMENT mxv_a1446, mxv_i306;
 IFNIL(N)
 IS(N,_Node,f,l,"encl_fctoratt",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp86;
			mxv_i306 = N;
			goto L306;
		}
		Lp86: ;
	{  /* Attribute access */
		mxv_a1446 = mxs_encl_fctoratt(_m,1441,mxs_fath(_m,1441,N));
	}
			mxv_i306 = mxv_a1446;
		L306: ;
	}
	return mxv_i306;
}

ELEMENT  mxs_filter_relev_acc(char *f, int l,ELEMENT AL){
ELEMENT mxv_a1488, mxv_a1492, mxv_i317, mxv_i316;
 IFNIL(AL)
 IS(AL,_ApplList,f,l,"filter_relev_acc",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,AL,mxs_ApplList(_m,1459)) ){
			mxv_i316 = mxs_ApplList(_m,1459);
			goto L316;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_appl_order(_m,1460,mxs_subterm(_m,1460,mxs_itoe(_c,0,1),AL)),mxs_Ord_neutral(_m,1460)) ){
		{  /* Attribute access */
			mxv_a1488 = mxs_filter_relev_acc(_m,1460,mxs_back(_m,1460,AL));
		}
			mxv_i317 = mxv_a1488;
			goto L317;
		}
	{  /* Attribute access */
		mxv_a1492 = mxs_filter_relev_acc(_m,1461,mxs_back(_m,1461,AL));
	}
		mxv_i317 = mxs_appfront(_m,1461,mxs_subterm(_m,1461,mxs_itoe(_c,0,1),AL),mxv_a1492);
		L317: ;
	}
		mxv_i316 = mxv_i317;
		L316: ;
	}
	return mxv_i316;
}

ELEMENT  mxs_list_intresexprs(char *f, int l,ELEMENT N){
ELEMENT mxv_a1588, mxv_a1590, mxv_a1591, mxv_i347;
 IFNIL(N)
 IS(N,_Node,f,l,"list_intresexprs",1)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,1533,N),mxs_nil(_m,1533)) ){
		{  /* Attribute access */
			mxv_a1588 = mxs_intresexprs(_m,1533,N);
		}
			mxv_i347 = mxv_a1588;
			goto L347;
		}
	{  /* Attribute access */
		mxv_a1590 = mxs_intresexprs(_m,1534,N);
	}
	{  /* Attribute access */
		mxv_a1591 = mxs_list_intresexprs(_m,1534,mxs_rbroth(_m,1534,N));
	}
		mxv_i347 = mxs_conc(_m,1534,mxv_a1590,mxv_a1591);
		L347: ;
	}
	return mxv_i347;
}

ELEMENT  mxs_intresexprs(char *f, int l,ELEMENT N){
ELEMENT mxv_a1597, mxv_i348;
 IFNIL(N)
 IS(N,_Node,f,l,"intresexprs",1)
	{  /* FormulaCaseList */
		if( mxs_is_intres(_m,1538,N) ){
			mxv_i348 = mxs_appback(_m,1538,mxs_IntResList(_m,1538),N);
			goto L348;
		}
		if( mxs_eq(_m,0,mxs_numsons(_m,1539,N),mxs_itoe(_c,0,0)) ){
			mxv_i348 = mxs_IntResList(_m,1539);
			goto L348;
		}
	{  /* Attribute access */
		mxv_a1597 = mxs_list_intresexprs(_m,1540,mxs_son(_m,1540,mxs_itoe(_c,0,1),N));
	}
		mxv_i348 = mxv_a1597;
		L348: ;
	}
	return mxv_i348;
}

ELEMENT  mxs_encl_part_intres(char *f, int l,ELEMENT N){
ELEMENT mxv_a1624, mxv_i351, mxv_a1625, mxv_i350, A_p307, C_p309, C_p311, L_p313, L_p315, I_p317, F_p319, F_p321, P_p323, F_p325;
 IFNIL(N)
 IS(N,_Node,f,l,"encl_part_intres",1)
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp93;
			A_p307 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = A_p307;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp93;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp93;
			if( !mxs_is(_c,0,mxv_IR,_ApplyEntity_) ) goto Lp93;
			mxv_i350 = N;
			goto L350;
		}
		Lp93: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp94;
			C_p309 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = C_p309;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp94;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp94;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp94;
			mxv_i350 = N;
			goto L350;
		}
		Lp94: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp95;
			C_p311 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = C_p311;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp95;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp95;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp95;
			mxv_i350 = N;
			goto L350;
		}
		Lp95: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp96;
			L_p313 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = L_p313;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp96;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp96;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp96;
			mxv_i350 = N;
			goto L350;
		}
		Lp96: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp97;
			L_p315 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = L_p315;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp97;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp97;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp97;
			mxv_i350 = N;
			goto L350;
		}
		Lp97: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp98;
			I_p317 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = I_p317;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp98;
			if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp98;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp98;
			mxv_i350 = N;
			goto L350;
		}
		Lp98: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp99;
			F_p319 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = F_p319;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp99;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp99;
			if( !mxs_is(_c,0,mxv_IR,_FormulaCase_) ) goto Lp99;
			mxv_i350 = N;
			goto L350;
		}
		Lp99: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp100;
			F_p321 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = F_p321;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp100;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp100;
			if( !mxs_is(_c,0,mxv_IR,_FormulaCase_) ) goto Lp100;
			mxv_i350 = N;
			goto L350;
		}
		Lp100: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp101;
			P_p323 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = P_p323;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp101;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp101;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp101;
			mxv_i350 = N;
			goto L350;
		}
		Lp101: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp102;
			F_p325 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = F_p325;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp102;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp102;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp102;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_maybe_wait(_m,1567,F_p325),mxs_true(_m,1567)) ){
				mxv_i351 = N;
				goto L351;
			}
		{  /* Attribute access */
			mxv_a1624 = mxs_encl_part_intres(_m,1567,F_p325);
		}
			mxv_i351 = mxv_a1624;
			L351: ;
		}
			mxv_i350 = mxv_i351;
			goto L350;
		}
		Lp102: ;
	{  /* Attribute access */
		mxv_a1625 = mxs_encl_part_intres(_m,1568,mxs_fath(_m,1568,N));
	}
			mxv_i350 = mxv_a1625;
		L350: ;
	}
	return mxv_i350;
}

ELEMENT  mxs_aux_var_need(char *f, int l,ELEMENT I,ELEMENT V){
ELEMENT mxv_i356, mxv_i355, mxv_a1638, mxv_a1640, mxv_i354, mxv_i353, mxv_l55, N_l55, mxv_i352;
 IFNIL(I) IFNIL(V)
 IS(I,_Int,f,l,"aux_var_need",1) IS(V,_FctOrAtt_,f,l,"aux_var_need",2)
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1575,mxs_number(_m,1575,_Name_),I) ){
			mxv_i352 = mxs_IntResList(_m,1575);
			goto L352;
		}
	{  /* LetExpr */
		N_l55 = mxs_element(_m,1577,I,_Name_);
		{  /* FormulaCaseList */
			if( mxs_desc(_m,1578,N_l55,V) ){
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! ( ! mxs_eq(_m,0,mxs_bind_pos(_m,1579,N_l55),N_l55))) ){
					mxv_i355 = mxs_false(_m,0);
					goto L355;
				}
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,1579,mxs_fath(_m,1579,mxs_bind_pos(_m,1579,N_l55)),_NameList_)) ){
					mxv_i356 = mxs_true(_m,0);
					goto L356;
				}
				mxv_i356 = mxs_false(_m,0);
				L356: ;
			}
				mxv_i355 = mxv_i356;
				L355: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i355) ){
				{  /* Attribute access */
					mxv_a1638 = mxs_aux_var_need(_m,1580,mxs_add(_m,1580,I,mxs_itoe(_c,0,1)),V);
				}
					mxv_i354 = mxs_appfront(_m,1580,N_l55,mxv_a1638);
					goto L354;
				}
			{  /* Attribute access */
				mxv_a1640 = mxs_aux_var_need(_m,1581,mxs_add(_m,1581,I,mxs_itoe(_c,0,1)),V);
			}
				mxv_i354 = mxv_a1640;
				L354: ;
			}
				mxv_i353 = mxv_i354;
				goto L353;
			}
			mxv_i353 = mxs_IntResList(_m,1582);
			L353: ;
		}
		mxv_l55 = mxv_i353;
	}
		mxv_i352 = mxv_l55;
		L352: ;
	}
	return mxv_i352;
}

ELEMENT  mxs_aux_intres_left(char *f, int l,ELEMENT N,ELEMENT I,ELEMENT Z){
ELEMENT mxv_a1647, mxv_i357;
 IFNIL(N) IFNIL(I) IFNIL(Z)
 IS(N,_IntResExpr_,f,l,"aux_intres_left",1) IS(I,_Int,f,l,"aux_intres_left",2) IS(Z,_IntResList,f,l,"aux_intres_left",3)
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_subterm(_m,1586,I,Z),N) ){
			mxv_i357 = mxs_IntResList(_m,1586);
			goto L357;
		}
	{  /* Attribute access */
		mxv_a1647 = mxs_aux_intres_left(_m,1587,N,mxs_add(_m,1587,I,mxs_itoe(_c,0,1)),Z);
	}
		mxv_i357 = mxs_appfront(_m,1587,mxs_subterm(_m,1587,I,Z),mxv_a1647);
		L357: ;
	}
	return mxv_i357;
}

ELEMENT  mxs_aux_intres_right(char *f, int l,ELEMENT LCP,ELEMENT PL,ELEMENT PR,ELEMENT L,ELEMENT I){
ELEMENT mxv_i363, mxv_i362, mxv_i361, mxv_i360, mxv_a1665, mxv_a1667, mxv_i359, mxv_l56, N_l56, mxv_i358;
 IFNIL(LCP) IFNIL(PL) IFNIL(PR) IFNIL(L) IFNIL(I)
 IS(LCP,_Point,f,l,"aux_intres_right",1) IS(PL,_Point,f,l,"aux_intres_right",2) IS(PR,_Point,f,l,"aux_intres_right",3) IS(L,_IntResList,f,l,"aux_intres_right",4) IS(I,_Int,f,l,"aux_intres_right",5)
	{  /* FormulaCaseList */
		if( mxs_lt(_m,1591,mxs_numsubterms(_m,1591,L),I) ){
			mxv_i358 = mxs_IntResList(_m,1591);
			goto L358;
		}
	{  /* LetExpr */
		N_l56 = mxs_subterm(_m,1593,I,L);
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! mxs_bef(_m,1594,PL,mxs_after(_m,1594,N_l56))) ){
				mxv_i360 = mxs_false(_m,0);
				goto L360;
			}
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! mxs_bef(_m,1594,mxs_after(_m,1594,N_l56),PR)) ){
				mxv_i362 = mxs_false(_m,0);
				goto L362;
			}
		{  /* FormulaCaseList */
			if( mxs_bef(_m,1594,mxs_after(_m,1594,mxs_bind_pos(_m,1594,N_l56)),LCP) ){
				mxv_i363 = mxs_true(_m,0);
				goto L363;
			}
			mxv_i363 = mxs_false(_m,0);
			L363: ;
		}
			mxv_i362 = mxv_i363;
			L362: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i362) ){
				mxv_i361 = mxs_true(_m,0);
				goto L361;
			}
			mxv_i361 = mxs_false(_m,0);
			L361: ;
		}
			mxv_i360 = mxv_i361;
			L360: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i360) ){
			{  /* Attribute access */
				mxv_a1665 = mxs_aux_intres_right(_m,1595,LCP,PL,PR,L,mxs_add(_m,1595,I,mxs_itoe(_c,0,1)));
			}
				mxv_i359 = mxs_appfront(_m,1595,N_l56,mxv_a1665);
				goto L359;
			}
		{  /* Attribute access */
			mxv_a1667 = mxs_aux_intres_right(_m,1596,LCP,PL,PR,L,mxs_add(_m,1596,I,mxs_itoe(_c,0,1)));
		}
			mxv_i359 = mxv_a1667;
			L359: ;
		}
		mxv_l56 = mxv_i359;
	}
		mxv_i358 = mxv_l56;
		L358: ;
	}
	return mxv_i358;
}



long  mxs_in(char *f, int l,ELEMENT N,ELEMENT lb,ELEMENT ub){
ELEMENT mxv_i5, mxv_i4, mxv_i8, mxv_i7, mxv_i6, mxv_i3;
 ISORNIL(N,_Node,f,l,"in",1) ISORNIL(lb,_Point,f,l,"in",2) ISORNIL(ub,_Point,f,l,"in",3)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_bef(_m,322,lb,mxs_before(_m,322,N)) ){
			mxv_i4 = mxs_true(_m,0);
			goto L4;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,lb,mxs_before(_m,322,N)) ){
			mxv_i5 = mxs_true(_m,0);
			goto L5;
		}
		mxv_i5 = mxs_false(_m,0);
		L5: ;
	}
		mxv_i4 = mxv_i5;
		L4: ;
	}
		if( ( ! mxs_eq(_m,0,mxs_true(_m,0),mxv_i4)) ){
			mxv_i3 = mxs_false(_m,0);
			goto L3;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_bef(_m,323,mxs_after(_m,323,N),ub) ){
			mxv_i7 = mxs_true(_m,0);
			goto L7;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,ub,mxs_after(_m,323,N)) ){
			mxv_i8 = mxs_true(_m,0);
			goto L8;
		}
		mxv_i8 = mxs_false(_m,0);
		L8: ;
	}
		mxv_i7 = mxv_i8;
		L7: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i7) ){
			mxv_i6 = mxs_true(_m,0);
			goto L6;
		}
		mxv_i6 = mxs_false(_m,0);
		L6: ;
	}
		mxv_i3 = mxv_i6;
		L3: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i3);
}

long  mxs_is_enumerable(char *f, int l,ELEMENT N){
ELEMENT mxv_i37, mxv_i36, mxv_i35, mxv_i34, mxv_i33, mxv_i32;
 ISORNIL(N,_SortId_,f,l,"is_enumerable",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,435,N,_NodeSortId_) ){
			mxv_i32 = mxs_true(_m,0);
			goto L32;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,436,mxs_son(_m,436,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Node")) ){
			mxv_i34 = mxs_true(_m,0);
			goto L34;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,436,mxs_son(_m,436,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Point")) ){
			mxv_i36 = mxs_true(_m,0);
			goto L36;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,436,mxs_son(_m,436,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Ident")) ){
			mxv_i37 = mxs_true(_m,0);
			goto L37;
		}
		mxv_i37 = mxs_false(_m,0);
		L37: ;
	}
		mxv_i36 = mxv_i37;
		L36: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i36) ){
			mxv_i35 = mxs_true(_m,0);
			goto L35;
		}
		mxv_i35 = mxs_false(_m,0);
		L35: ;
	}
		mxv_i34 = mxv_i35;
		L34: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i34) ){
			mxv_i33 = mxs_true(_m,0);
			goto L33;
		}
		mxv_i33 = mxs_false(_m,0);
		L33: ;
	}
		mxv_i32 = mxv_i33;
		L32: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i32);
}

long  mxs_ex_pattern_inbetween(char *f, int l,ELEMENT IT1,ELEMENT IT2){
ELEMENT mxv_i73, mxv_i72, mxv_i71, mxv_i70, mxv_i69, mxv_i68;
 ISORNIL(IT1,_Item_,f,l,"ex_pattern_inbetween",1) ISORNIL(IT2,_Item_,f,l,"ex_pattern_inbetween",2)
	{  /* FormulaCaseList */
		if( mxs_is(_m,544,IT1,_Pattern_) ){
			mxv_i68 = mxs_true(_m,0);
			goto L68;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,IT1,IT2))) ){
			mxv_i70 = mxs_false(_m,0);
			goto L70;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,545,IT1,_Blank_)) ){
			mxv_i72 = mxs_false(_m,0);
			goto L72;
		}
	{  /* FormulaCaseList */
		if( mxs_ex_pattern_inbetween(_m,545,mxs_rbroth(_m,545,IT1),IT2) ){
			mxv_i73 = mxs_true(_m,0);
			goto L73;
		}
		mxv_i73 = mxs_false(_m,0);
		L73: ;
	}
		mxv_i72 = mxv_i73;
		L72: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i72) ){
			mxv_i71 = mxs_true(_m,0);
			goto L71;
		}
		mxv_i71 = mxs_false(_m,0);
		L71: ;
	}
		mxv_i70 = mxv_i71;
		L70: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i70) ){
			mxv_i69 = mxs_true(_m,0);
			goto L69;
		}
		mxv_i69 = mxs_false(_m,0);
		L69: ;
	}
		mxv_i68 = mxv_i69;
		L68: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i68);
}

long  mxs_is_node(char *f, int l,ELEMENT N){
ELEMENT mxv_i206, mxv_i205;
 ISORNIL(N,_SortId_,f,l,"is_node",1)
	{  /* FormulaCaseList */
		if( mxs_is(_m,1135,N,_NodeSortId_) ){
			mxv_i205 = mxs_true(_m,0);
			goto L205;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,1135,mxs_son(_m,1135,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Node")) ){
			mxv_i206 = mxs_true(_m,0);
			goto L206;
		}
		mxv_i206 = mxs_false(_m,0);
		L206: ;
	}
		mxv_i205 = mxv_i206;
		L205: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i205);
}

long  mxs_simplification(char *f, int l,ELEMENT S,ELEMENT T){
ELEMENT mxv_i254, mxv_i253, mxv_i252, mxv_i251, mxv_i250, mxv_i249, mxv_i260, mxv_i259, mxv_i258, mxv_i257, mxv_i266, mxv_i265, mxv_i264, mxv_i263, mxv_i272, mxv_i271, mxv_i270, mxv_i269, mxv_i276, mxv_i275, mxv_i277, mxv_i274, mxv_i273, mxv_i268, mxv_i267, mxv_i262, mxv_i261, mxv_i256, mxv_i255, mxv_i248;
 ISORNIL(S,_Value,f,l,"simplification",1) ISORNIL(T,_FValue,f,l,"simplification",2)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1304,S,_TWson)) ){
			mxv_i249 = mxs_false(_m,0);
			goto L249;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWfath(_m,1304)) ){
			mxv_i251 = mxs_true(_m,0);
			goto L251;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWrbroth(_m,1304)) ){
			mxv_i253 = mxs_true(_m,0);
			goto L253;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWlbroth(_m,1304)) ){
			mxv_i254 = mxs_true(_m,0);
			goto L254;
		}
		mxv_i254 = mxs_false(_m,0);
		L254: ;
	}
		mxv_i253 = mxv_i254;
		L253: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i253) ){
			mxv_i252 = mxs_true(_m,0);
			goto L252;
		}
		mxv_i252 = mxs_false(_m,0);
		L252: ;
	}
		mxv_i251 = mxv_i252;
		L251: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i251) ){
			mxv_i250 = mxs_true(_m,0);
			goto L250;
		}
		mxv_i250 = mxs_false(_m,0);
		L250: ;
	}
		mxv_i249 = mxv_i250;
		L249: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i249) ){
			mxv_i248 = mxs_true(_m,0);
			goto L248;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,S,mxs_TWfath(_m,1305))) ){
			mxv_i257 = mxs_false(_m,0);
			goto L257;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWson(_m,1305,mxs_itoe(_c,0,1))) ){
			mxv_i259 = mxs_true(_m,0);
			goto L259;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWson(_m,1305,mxs_itoe(_c,0,-1))) ){
			mxv_i260 = mxs_true(_m,0);
			goto L260;
		}
		mxv_i260 = mxs_false(_m,0);
		L260: ;
	}
		mxv_i259 = mxv_i260;
		L259: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i259) ){
			mxv_i258 = mxs_true(_m,0);
			goto L258;
		}
		mxv_i258 = mxs_false(_m,0);
		L258: ;
	}
		mxv_i257 = mxv_i258;
		L257: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i257) ){
			mxv_i256 = mxs_true(_m,0);
			goto L256;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,S,mxs_TWlbroth(_m,1306))) ){
			mxv_i263 = mxs_false(_m,0);
			goto L263;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWfath(_m,1306)) ){
			mxv_i265 = mxs_true(_m,0);
			goto L265;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWrbroth(_m,1306)) ){
			mxv_i266 = mxs_true(_m,0);
			goto L266;
		}
		mxv_i266 = mxs_false(_m,0);
		L266: ;
	}
		mxv_i265 = mxv_i266;
		L265: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i265) ){
			mxv_i264 = mxs_true(_m,0);
			goto L264;
		}
		mxv_i264 = mxs_false(_m,0);
		L264: ;
	}
		mxv_i263 = mxv_i264;
		L263: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i263) ){
			mxv_i262 = mxs_true(_m,0);
			goto L262;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,S,mxs_TWrbroth(_m,1307))) ){
			mxv_i269 = mxs_false(_m,0);
			goto L269;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWfath(_m,1307)) ){
			mxv_i271 = mxs_true(_m,0);
			goto L271;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWlbroth(_m,1307)) ){
			mxv_i272 = mxs_true(_m,0);
			goto L272;
		}
		mxv_i272 = mxs_false(_m,0);
		L272: ;
	}
		mxv_i271 = mxv_i272;
		L271: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i271) ){
			mxv_i270 = mxs_true(_m,0);
			goto L270;
		}
		mxv_i270 = mxs_false(_m,0);
		L270: ;
	}
		mxv_i269 = mxv_i270;
		L269: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i269) ){
			mxv_i268 = mxs_true(_m,0);
			goto L268;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,S,mxs_FClosure(_m,1308,mxs_TWlbroth(_m,1308))) ){
			mxv_i275 = mxs_true(_m,0);
			goto L275;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,S,mxs_FClosure(_m,1308,mxs_TWrbroth(_m,1308))) ){
			mxv_i276 = mxs_true(_m,0);
			goto L276;
		}
		mxv_i276 = mxs_false(_m,0);
		L276: ;
	}
		mxv_i275 = mxv_i276;
		L275: ;
	}
		if( ( ! mxs_eq(_m,0,mxs_true(_m,0),mxv_i275)) ){
			mxv_i274 = mxs_false(_m,0);
			goto L274;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,T,mxs_TWfath(_m,1308)) ){
			mxv_i277 = mxs_true(_m,0);
			goto L277;
		}
		mxv_i277 = mxs_false(_m,0);
		L277: ;
	}
		mxv_i274 = mxv_i277;
		L274: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i274) ){
			mxv_i273 = mxs_true(_m,0);
			goto L273;
		}
		mxv_i273 = mxs_false(_m,0);
		L273: ;
	}
		mxv_i268 = mxv_i273;
		L268: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i268) ){
			mxv_i267 = mxs_true(_m,0);
			goto L267;
		}
		mxv_i267 = mxs_false(_m,0);
		L267: ;
	}
		mxv_i262 = mxv_i267;
		L262: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i262) ){
			mxv_i261 = mxs_true(_m,0);
			goto L261;
		}
		mxv_i261 = mxs_false(_m,0);
		L261: ;
	}
		mxv_i256 = mxv_i261;
		L256: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i256) ){
			mxv_i255 = mxs_true(_m,0);
			goto L255;
		}
		mxv_i255 = mxs_false(_m,0);
		L255: ;
	}
		mxv_i248 = mxv_i255;
		L248: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i248);
}

long  mxs_is_intres(char *f, int l,ELEMENT N){
ELEMENT mxv_i337, mxv_i336, mxv_i341, mxv_i340, mxv_i346, mxv_i345, mxv_i344, mxv_i343, mxv_i342, mxv_i339, mxv_i338, mxv_i335;
 ISORNIL(N,_Node,f,l,"is_intres",1)
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1528,N,_FuncAppl_)) ){
			mxv_i336 = mxs_false(_m,0);
			goto L336;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_maybe_wait(_m,1528,N),mxs_true(_m,1528)) ){
			mxv_i337 = mxs_true(_m,0);
			goto L337;
		}
		mxv_i337 = mxs_false(_m,0);
		L337: ;
	}
		mxv_i336 = mxv_i337;
		L336: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i336) ){
			mxv_i335 = mxs_true(_m,0);
			goto L335;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_is(_m,1529,N,_FuncAppl_))) ){
			mxv_i340 = mxs_false(_m,0);
			goto L340;
		}
	{  /* FormulaCaseList */
		if( mxs_is(_m,1529,N,_IntResExpr_) ){
			mxv_i341 = mxs_true(_m,0);
			goto L341;
		}
		mxv_i341 = mxs_false(_m,0);
		L341: ;
	}
		mxv_i340 = mxv_i341;
		L340: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i340) ){
			mxv_i339 = mxs_true(_m,0);
			goto L339;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1530,N,_Name_)) ){
			mxv_i343 = mxs_false(_m,0);
			goto L343;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,mxs_bind_pos(_m,1530,N),N))) ){
			mxv_i345 = mxs_false(_m,0);
			goto L345;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1530,mxs_fath(_m,1530,mxs_bind_pos(_m,1530,N)),_NameList_)) ){
			mxv_i346 = mxs_true(_m,0);
			goto L346;
		}
		mxv_i346 = mxs_false(_m,0);
		L346: ;
	}
		mxv_i345 = mxv_i346;
		L345: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i345) ){
			mxv_i344 = mxs_true(_m,0);
			goto L344;
		}
		mxv_i344 = mxs_false(_m,0);
		L344: ;
	}
		mxv_i343 = mxv_i344;
		L343: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i343) ){
			mxv_i342 = mxs_true(_m,0);
			goto L342;
		}
		mxv_i342 = mxs_false(_m,0);
		L342: ;
	}
		mxv_i339 = mxv_i342;
		L339: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i339) ){
			mxv_i338 = mxs_true(_m,0);
			goto L338;
		}
		mxv_i338 = mxs_false(_m,0);
		L338: ;
	}
		mxv_i335 = mxv_i338;
		L335: ;
	}
	return mxs_eq(_m,0,mxs_true(_m,0),mxv_i335);
}



static  void  mxe_term_basesorts( ELEMENT N, ELEMENT mxv_attvalue, int state, ELEMENT *mxv_waitpar ){
	ELEMENT  mxv_a66, mxv_i17, R_p21, mxv_i20, mxv_i19, mxv_a76, mxv_i21, I_p25, mxv_l2, D_l2, mxv_i18, mxv_l1, RL_l1,
		mxv_ax, mxv_res, mxv_par = N;
	AttInstSq mxv_waitsq, mxv_wsq;

	switch(state) {
		case 66 :
			mxv_a66 = mxv_attvalue;
			goto Lz66;
		case 76 :
			RL_l1 = mxv_waitpar[0];
			mxv_a76 = mxv_attvalue;
			goto Lz76;
	}
	{  /* LetExpr */
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR))) ) goto Lp3;
				if( mxs_before(_c,0,mxs_son(_c,0,-2,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp3;
				mxv_IR = mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor));
				if( mxv_IR == mxs_nil(_c,0) ) goto Lp3;
				if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp3;
				if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp3;
				mxv_IR = mxs_fath(_c,0,mxv_anchor);
				if( mxv_IR == mxs_nil(_c,0) ) goto Lp3;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp3;
				if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp3;
				R_p21 = mxs_rbroth(_c,0,mxv_anchor);
				mxv_IR = R_p21;
				if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR))) ) goto Lp3;
				if( mxs_before(_c,0,mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp3;
			{  /* Attribute access */
				mxv_ax = R_p21;
				mxv_a66 = mxs_term_basesorts(_m,358,mxv_ax);
				if( mxv_a66==MAXUNDEF ){
					insAttInst((EVALFCT)mxe_term_basesorts,mxv_par,66,mxw_term_basesorts,mxs_index(_c,0,mxv_ax,_SortId_));
					return;
				}
				Lz66:;
			}
				mxv_i17 = mxv_a66;
				goto L17;
			}
			Lp3: ;
				mxv_i17 = mxs_DefIdNodeList(_m,358);
			L17: ;
		}
		RL_l1 = mxv_i17;
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! mxs_is(_m,360,N,_TermSortId_)) ){
				mxv_i19 = mxs_false(_m,0);
				goto L19;
			}
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,mxs_id(_m,360,mxs_son(_m,360,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Node"))) ){
				mxv_i20 = mxs_true(_m,0);
				goto L20;
			}
			mxv_i20 = mxs_false(_m,0);
			L20: ;
		}
			mxv_i19 = mxv_i20;
			L19: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i19) ){
			{  /* LetExpr */
				D_l2 = mxs_decl(_m,361,N);
				{  /* PatternCaseList */
					{
						ELEMENT mxv_anchor, mxv_IR;
						mxv_anchor = D_l2;
						mxv_IR = mxv_anchor;
						if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp4;
						mxv_IR = mxs_fath(_c,0,mxv_anchor);
						if( mxv_IR == mxs_nil(_c,0) ) goto Lp4;
						if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp4;
						if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp4;
						mxv_IR = mxs_rbroth(_c,0,mxv_anchor);
						if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp4;
						if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp4;
						I_p25 = mxs_son(_c,0,1,mxs_rbroth(_c,0,mxv_anchor));
						mxv_IR = I_p25;
						if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp4;
					{  /* Attribute access */
						mxv_ax = I_p25;
						mxv_a76 = mxs_term_basesorts(_m,362,mxv_ax);
						if( mxv_a76==MAXUNDEF ){ ELEMENT *P;
							P = insAttInst((EVALFCT)mxe_term_basesorts,mxv_par,76,mxw_term_basesorts,mxs_index(_c,0,mxv_ax,_SortId_));
							P[0] = RL_l1;
							return;
						}
						Lz76:;
					}
						mxv_i21 = mxs_conc(_m,362,RL_l1,mxv_a76);
						goto L21;
					}
					Lp4: ;
						mxv_i21 = mxs_appback(_m,363,RL_l1,D_l2);
					L21: ;
				}
				mxv_l2 = mxv_i21;
			}
				mxv_i18 = mxv_l2;
				goto L18;
			}
			mxv_i18 = RL_l1;
			L18: ;
		}
		mxv_l1 = mxv_i18;
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
	ELEMENT  mxv_a91, mxv_i25, R_p36, mxv_i28, mxv_i27, mxv_a103, mxv_i30, mxv_i31, mxv_i29, I_p40, mxv_l4, D_l4, mxv_i26, mxv_l3, RL_l3,
		mxv_ax, mxv_res, mxv_par = N;
	AttInstSq mxv_waitsq, mxv_wsq;

	switch(state) {
		case 91 :
			mxv_a91 = mxv_attvalue;
			goto Lz91;
		case 103 :
			RL_l3 = mxv_waitpar[0];
			mxv_a103 = mxv_attvalue;
			goto Lz103;
	}
	{  /* LetExpr */
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR))) ) goto Lp5;
				if( mxs_before(_c,0,mxs_son(_c,0,-2,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp5;
				mxv_IR = mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor));
				if( mxv_IR == mxs_nil(_c,0) ) goto Lp5;
				if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp5;
				if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp5;
				mxv_IR = mxs_fath(_c,0,mxv_anchor);
				if( mxv_IR == mxs_nil(_c,0) ) goto Lp5;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp5;
				if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp5;
				R_p36 = mxs_rbroth(_c,0,mxv_anchor);
				mxv_IR = R_p36;
				if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR))) ) goto Lp5;
				if( mxs_before(_c,0,mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp5;
			{  /* Attribute access */
				mxv_ax = R_p36;
				mxv_a91 = mxs_node_basesorts(_m,377,mxv_ax);
				if( mxv_a91==MAXUNDEF ){
					insAttInst((EVALFCT)mxe_node_basesorts,mxv_par,91,mxw_node_basesorts,mxs_index(_c,0,mxv_ax,_SortId_));
					return;
				}
				Lz91:;
			}
				mxv_i25 = mxv_a91;
				goto L25;
			}
			Lp5: ;
				mxv_i25 = mxs_DefIdNodeList(_m,377);
			L25: ;
		}
		RL_l3 = mxv_i25;
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,RL_l3,mxs_AllNodes(_m,378)) ){
				mxv_i27 = mxs_true(_m,0);
				goto L27;
			}
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_id(_m,378,mxs_son(_m,378,mxs_itoe(_c,0,1),N)),mxs_atoe(_c,0,"Node")) ){
				mxv_i28 = mxs_true(_m,0);
				goto L28;
			}
			mxv_i28 = mxs_false(_m,0);
			L28: ;
		}
			mxv_i27 = mxv_i28;
			L27: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i27) ){
				mxv_i26 = mxs_AllNodes(_m,378);
				goto L26;
			}
		{  /* LetExpr */
			D_l4 = mxs_decl(_m,380,N);
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = D_l4;
					mxv_IR = mxv_anchor;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp6;
					mxv_IR = mxs_fath(_c,0,mxv_anchor);
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp6;
					if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp6;
					if( !mxs_is(_c,0,mxv_IR,_ClassProd_) ) goto Lp6;
					mxv_IR = mxs_rbroth(_c,0,mxv_anchor);
					if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp6;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp6;
					I_p40 = mxs_son(_c,0,1,mxs_rbroth(_c,0,mxv_anchor));
					mxv_IR = I_p40;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp6;
				{  /* FormulaCaseList */
					if( mxs_is(_m,382,N,_TermSortId_) ){
					{  /* Attribute access */
						mxv_ax = I_p40;
						mxv_a103 = mxs_node_basesorts(_m,382,mxv_ax);
						if( mxv_a103==MAXUNDEF ){ ELEMENT *P;
							P = insAttInst((EVALFCT)mxe_node_basesorts,mxv_par,103,mxw_node_basesorts,mxs_index(_c,0,mxv_ax,_SortId_));
							P[0] = RL_l3;
							return;
						}
						Lz103:;
					}
						mxv_i30 = mxs_sort_union(_m,382,RL_l3,mxv_a103);
						goto L30;
					}
					mxv_i30 = mxs_sort_union(_m,383,RL_l3,mxs_term_basesorts(_m,383,I_p40));
					L30: ;
				}
					mxv_i29 = mxv_i30;
					goto L29;
				}
				Lp6: ;
			{  /* FormulaCaseList */
				if( mxs_is(_m,385,N,_TermSortId_) ){
					mxv_i31 = RL_l3;
					goto L31;
				}
				mxv_i31 = mxs_appback(_m,386,RL_l3,D_l4);
				L31: ;
			}
					mxv_i29 = mxv_i31;
				L29: ;
			}
			mxv_l4 = mxv_i29;
		}
			mxv_i26 = mxv_l4;
			L26: ;
		}
		mxv_l3 = mxv_i26;
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
	ELEMENT  mxv_i49,
		mxv_ax, mxv_par = S;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp9;
			mxv_i49 = mxs_scope(_m,458,mxs_fath(_m,458,S));
			goto L49;
		}
		Lp9: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = S;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp10;
			mxv_i49 = mxs_scope(_m,459,mxs_fath(_m,459,S));
			goto L49;
		}
		Lp10: ;
			mxv_i49 = mxs_nil(_m,460);
		L49: ;
	}
	mxv_ax = mxs_index(_c,0,S,_Scope_);
	mxa_encl_scope[ mxv_ax ] = mxv_i49;
}

static  void  mxe_bind_pos( ELEMENT N ){
	ELEMENT  mxv_i63, mxv_i62, mxv_i65, mxv_i64, mxv_i66, mxv_l10, BDP_l10, mxv_i61,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
		if( mxs_is(_m,522,mxs_fath(_m,522,N),_NameList_) ){
			mxv_i61 = N;
			goto L61;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,523,mxs_fath(_m,523,N),_LetExpr_)) ){
			mxv_i62 = mxs_false(_m,0);
			goto L62;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_son(_m,523,mxs_itoe(_c,0,1),mxs_fath(_m,523,N)),N) ){
			mxv_i63 = mxs_true(_m,0);
			goto L63;
		}
		mxv_i63 = mxs_false(_m,0);
		L63: ;
	}
		mxv_i62 = mxv_i63;
		L62: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i62) ){
			mxv_i61 = N;
			goto L61;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,524,mxs_scope(_m,524,N),_Condition_)) ){
			mxv_i64 = mxs_false(_m,0);
			goto L64;
		}
	{  /* FormulaCaseList */
		if( mxs_desc(_m,524,N,mxs_son(_m,524,mxs_itoe(_c,0,1),mxs_scope(_m,524,N))) ){
			mxv_i65 = mxs_true(_m,0);
			goto L65;
		}
		mxv_i65 = mxs_false(_m,0);
		L65: ;
	}
		mxv_i64 = mxv_i65;
		L64: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i64) ){
			mxv_i61 = N;
			goto L61;
		}
		if( mxs_is(_m,525,mxs_fath(_m,525,N),_Pattern_) ){
		{  /* LetExpr */
			BDP_l10 = mxs_lookup(_m,526,mxs_term(_m,526,mxs_son(_m,526,mxs_itoe(_c,0,1),N)),mxs_encl_scope(_m,526,mxs_scope(_m,526,N)));
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,BDP_l10,mxs_nil(_m,527)) ){
					mxv_i66 = N;
					goto L66;
				}
				mxv_i66 = BDP_l10;
				L66: ;
			}
			mxv_l10 = mxv_i66;
		}
			mxv_i61 = mxv_l10;
			goto L61;
		}
		mxv_i61 = mxs_lookup(_m,528,mxs_term(_m,528,mxs_son(_m,528,mxs_itoe(_c,0,1),N)),mxs_scope(_m,528,N));
		L61: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Name_);
	mxa_bind_pos[ mxv_ax ] = mxv_i61;
}

static  void  mxe_numberofastrks( ELEMENT ITL ){
	ELEMENT 
		mxv_ax, mxv_par = ITL;
	mxv_ax = mxs_index(_c,0,ITL,_ItemList_);
	mxa_numberofastrks[ mxv_ax ] = mxs_countastrks(_m,540,mxs_term(_m,540,ITL),mxs_itoe(_c,0,0));
}

static  void  mxe_predeclprodcd( ELEMENT PP ){
	ELEMENT  mxv_i81, mxv_i80, ID_p155,
		mxv_ax, mxv_par = PP;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = PP;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 1 ) goto Lp18;
			if( !mxs_is(_c,0,mxv_IR,_PredeclProd_) ) goto Lp18;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp18;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp18;
			ID_p155 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = ID_p155;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp18;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_id(_m,584,ID_p155),mxs_atoe(_c,0,"Node")) ){
				mxv_i81 = mxs_itoe(_c,0,2);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,585,ID_p155),mxs_atoe(_c,0,"Point")) ){
				mxv_i81 = mxs_itoe(_c,0,1);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,586,ID_p155),mxs_atoe(_c,0,"nil")) ){
				mxv_i81 = mxs_itoe(_c,0,-1);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,587,ID_p155),mxs_atoe(_c,0,"Term")) ){
				mxv_i81 = mxs_itoe(_c,0,-2);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,588,ID_p155),mxs_atoe(_c,0,"NodeSort")) ){
				mxv_i81 = mxs_itoe(_c,0,-3);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,589,ID_p155),mxs_atoe(_c,0,"PredeclSort")) ){
				mxv_i81 = mxs_itoe(_c,0,-4);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,590,ID_p155),mxs_atoe(_c,0,"ClassSort")) ){
				mxv_i81 = mxs_itoe(_c,0,-5);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,591,ID_p155),mxs_atoe(_c,0,"TupelSort")) ){
				mxv_i81 = mxs_itoe(_c,0,-6);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,592,ID_p155),mxs_atoe(_c,0,"ListSort")) ){
				mxv_i81 = mxs_itoe(_c,0,-7);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,593,ID_p155),mxs_atoe(_c,0,"Ident")) ){
				mxv_i81 = mxs_itoe(_c,0,-8);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,594,ID_p155),mxs_atoe(_c,0,"Bool")) ){
				mxv_i81 = mxs_itoe(_c,0,-9);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,595,ID_p155),mxs_atoe(_c,0,"Char")) ){
				mxv_i81 = mxs_itoe(_c,0,-10);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,596,ID_p155),mxs_atoe(_c,0,"Int")) ){
				mxv_i81 = mxs_itoe(_c,0,-11);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,597,ID_p155),mxs_atoe(_c,0,"String")) ){
				mxv_i81 = mxs_itoe(_c,0,-12);
				goto L81;
			}
			if( mxs_eq(_m,0,mxs_id(_m,598,ID_p155),mxs_atoe(_c,0,"Reference")) ){
				mxv_i81 = mxs_itoe(_c,0,-13);
				goto L81;
			}
			mxv_i81 = mxs_nil(_m,599);
			L81: ;
		}
			mxv_i80 = mxv_i81;
			goto L80;
		}
		Lp18: ;
			mxv_i80 = mxs_nil(_m,600);
		L80: ;
	}
	mxv_ax = mxs_index(_c,0,PP,_PredeclProd_);
	mxa_predeclprodcd[ mxv_ax ] = mxv_i80;
}

static  void  mxe_tupelprodcd( ELEMENT TP ){
	ELEMENT 
		mxv_ax, mxv_par = TP;
	mxv_ax = mxs_index(_c,0,TP,_TupelProd_);
	mxa_tupelprodcd[ mxv_ax ] = mxs_neg(_m,603,mxs_add(_m,603,mxs_index(_m,603,TP,_TupelProd_),mxs_sub(_m,603,mxs_number(_m,603,_PredeclProd_),mxs_itoe(_c,0,2))));
}

static  void  mxe_listprodcd( ELEMENT LP ){
	ELEMENT 
		mxv_ax, mxv_par = LP;
	mxv_ax = mxs_index(_c,0,LP,_ListProd_);
	mxa_listprodcd[ mxv_ax ] = mxs_neg(_m,606,mxs_add(_m,606,mxs_index(_m,606,LP,_ListProd_),mxs_add(_m,607,mxs_number(_m,607,_TupelProd_),mxs_sub(_m,607,mxs_number(_m,607,_PredeclProd_),mxs_itoe(_c,0,2)))));
}

static  void  mxe_classprodcd( ELEMENT CP ){
	ELEMENT 
		mxv_ax, mxv_par = CP;
	mxv_ax = mxs_index(_c,0,CP,_ClassProd_);
	mxa_classprodcd[ mxv_ax ] = mxs_sub(_m,614,mxs_smallestlistprodcd(_m,614),mxs_index(_m,614,CP,_ClassProd_));
}

static  void  mxe_patnpos( ELEMENT PN ){
	ELEMENT  mxv_i85,
		mxv_ax, mxv_par = PN;
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,650,mxs_fath(_m,650,PN),_ItemList_)) ){
			mxv_i85 = mxs_TopPosition(_m,650);
			goto L85;
		}
		if( mxs_eq(_m,0,mxs_next_left_pat(_m,651,PN),mxs_nil(_m,651)) ){
			mxv_i85 = mxs_AbsPosition(_m,651,mxs_patnposition(_m,651,PN,mxs_itoe(_c,0,1)));
			goto L85;
		}
		mxv_i85 = mxs_RelPosition(_m,652,mxs_patnposition(_m,652,PN,mxs_itoe(_c,0,1)));
		L85: ;
	}
	mxv_ax = mxs_index(_c,0,PN,_Pattern_);
	mxa_patnpos[ mxv_ax ] = mxv_i85;
}

static  void  mxe_num_items( ELEMENT P ){
	ELEMENT  mxv_i123, mxv_l20, NUM_IT_l20,
		mxv_ax, mxv_par = P;
	{  /* LetExpr */
		NUM_IT_l20 = mxs_numsons(_m,814,mxs_son(_m,814,mxs_itoe(_c,0,2),P));
		{  /* FormulaCaseList */
			if( ( ! mxs_is(_m,815,mxs_son(_m,815,mxs_itoe(_c,0,2),P),_Blank_)) ){
				mxv_i123 = mxs_sub(_m,815,NUM_IT_l20,mxs_numberofastrks(_m,815,mxs_son(_m,815,mxs_itoe(_c,0,2),P)));
				goto L123;
			}
			mxv_i123 = mxs_itoe(_c,0,0);
			L123: ;
		}
		mxv_l20 = mxv_i123;
	}
	mxv_ax = mxs_index(_c,0,P,_Pattern_);
	mxa_num_items[ mxv_ax ] = mxv_l20;
}

static  void  mxe_args( ELEMENT F ){
	ELEMENT 
		mxv_ax, mxv_par = F;
	mxv_ax = mxs_index(_c,0,F,_FuncAppl_);
	mxa_args[ mxv_ax ] = mxs_son(_m,842,mxs_itoe(_c,0,2),F);
}

static  void  mxe_caseexpr( ELEMENT C ){
	ELEMENT  mxv_i126,
		mxv_ax, mxv_par = C;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,846,C),mxs_nil(_m,846)) ){
			mxv_i126 = mxs_appback(_m,846,mxs_ExprNList(_m,846),mxs_son(_m,846,mxs_itoe(_c,0,2),C));
			goto L126;
		}
		mxv_i126 = mxs_appback(_m,847,mxs_caseexpr(_m,847,mxs_lbroth(_m,847,C)),mxs_son(_m,847,mxs_itoe(_c,0,2),C));
		L126: ;
	}
	mxv_ax = mxs_index(_c,0,C,_IfCase_);
	mxa_caseexpr[ mxv_ax ] = mxv_i126;
}

static  void  mxe_allexpr( ELEMENT I ){
	ELEMENT 
		mxv_ax, mxv_par = I;
	mxv_ax = mxs_index(_c,0,I,_IfExpr_);
	mxa_allexpr[ mxv_ax ] = mxs_appback(_m,851,mxs_caseexpr(_m,851,mxs_son(_m,851,mxs_itoe(_c,0,-1),mxs_son(_m,851,mxs_itoe(_c,0,1),I))),mxs_son(_m,851,mxs_itoe(_c,0,2),I));
}

static  void  mxe_encl_patterncase( ELEMENT N ){
	ELEMENT  mxv_i127,
		mxv_ax, mxv_par = N;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp38;
			mxv_i127 = N;
			goto L127;
		}
		Lp38: ;
			mxv_i127 = mxs_encl_patterncase(_m,856,mxs_fath(_m,856,N));
		L127: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Node);
	mxa_encl_patterncase[ mxv_ax ] = mxv_i127;
}

static  void  mxe_top_pattern( ELEMENT N ){
	ELEMENT  mxv_i130, mxv_i129, mxv_i128,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_is(_m,860,mxs_fath(_m,860,N),_PatternCase_) ){
			mxv_i129 = mxs_true(_m,0);
			goto L129;
		}
	{  /* FormulaCaseList */
		if( mxs_is(_m,860,mxs_fath(_m,860,mxs_fath(_m,860,N)),_Condition_) ){
			mxv_i130 = mxs_true(_m,0);
			goto L130;
		}
		mxv_i130 = mxs_false(_m,0);
		L130: ;
	}
		mxv_i129 = mxv_i130;
		L129: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i129) ){
			mxv_i128 = N;
			goto L128;
		}
		mxv_i128 = mxs_top_pattern(_m,861,mxs_fath(_m,861,N));
		L128: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Node);
	mxa_top_pattern[ mxv_ax ] = mxv_i128;
}

static  void  mxe_son_nr( ELEMENT N ){
	ELEMENT  mxv_i188,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_lbroth(_m,1072,N),mxs_nil(_m,1072)) ){
			mxv_i188 = mxs_itoe(_c,0,1);
			goto L188;
		}
		mxv_i188 = mxs_add(_m,1073,mxs_itoe(_c,0,1),mxs_son_nr(_m,1073,mxs_lbroth(_m,1073,N)));
		L188: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FctOrAtt_);
	mxa_son_nr[ mxv_ax ] = mxv_i188;
}

static  void  mxe_relacc_nr( ELEMENT N ){
	ELEMENT  mxv_i191, mxv_i190, mxv_i189, mxv_l34, F_l34,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		F_l34 = mxs_fath(_m,1077,mxs_decl(_m,1077,mxs_son(_m,1077,mxs_itoe(_c,0,1),N)));
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( ( ! mxs_is(_m,1078,F_l34,_FctOrAtt_)) ){
				mxv_i190 = mxs_false(_m,0);
				goto L190;
			}
		{  /* FormulaCaseList */
			if( mxs_desc(_m,1078,N,mxs_fath(_m,1078,F_l34)) ){
				mxv_i191 = mxs_true(_m,0);
				goto L191;
			}
			mxv_i191 = mxs_false(_m,0);
			L191: ;
		}
			mxv_i190 = mxv_i191;
			L190: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i190) ){
				mxv_i189 = mxs_son_nr(_m,1078,F_l34);
				goto L189;
			}
			mxv_i189 = mxs_nil(_m,1079);
			L189: ;
		}
		mxv_l34 = mxv_i189;
	}
	mxv_ax = mxs_index(_c,0,N,_FuncAppl_);
	mxa_relacc_nr[ mxv_ax ] = mxv_l34;
}

static  void  mxe_appl_list_formula( ELEMENT N ){
	ELEMENT  mxv_i192, E_p238, X_p240, Y_p241, X_p243,
		mxv_ax, mxv_par = N;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp63;
			if( !mxs_is(_c,0,mxv_IR,_PredAppl_) ) goto Lp63;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp63;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp63;
			E_p238 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = E_p238;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp63;
			mxv_i192 = mxs_appl_list_expr(_m,1083,E_p238);
			goto L192;
		}
		Lp63: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp64;
			if( !mxs_is(_c,0,mxv_IR,_BinOp_) ) goto Lp64;
			X_p240 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = X_p240;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp64;
			Y_p241 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = Y_p241;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp64;
			mxv_i192 = mxs_conc(_m,1084,mxs_appl_list_formula(_m,1084,X_p240),mxs_appl_list_formula(_m,1084,Y_p241));
			goto L192;
		}
		Lp64: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 1 ) goto Lp65;
			if( !mxs_is(_c,0,mxv_IR,_Neg_) ) goto Lp65;
			X_p243 = mxs_son(_c,0,1,mxv_anchor);
			mxv_IR = X_p243;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp65;
			mxv_i192 = mxs_appl_list_formula(_m,1085,X_p243);
			goto L192;
		}
		Lp65: ;
			mxv_i192 = mxs_ApplList(_m,1086);
		L192: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Formula_);
	mxa_appl_list_formula[ mxv_ax ] = mxv_i192;
}

static  void  mxe_appl_list_case( ELEMENT N ){
	ELEMENT  mxv_i193, F_p245, E_p246, E_p248, mxv_i194, mxv_l35, AL_l35,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp66;
				if( !mxs_is(_c,0,mxv_IR,_FormulaCase_) ) goto Lp66;
				F_p245 = mxs_son(_c,0,1,mxv_anchor);
				mxv_IR = F_p245;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp66;
				E_p246 = mxs_son(_c,0,2,mxv_anchor);
				mxv_IR = E_p246;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp66;
				mxv_i193 = mxs_conc(_m,1091,mxs_appl_list_formula(_m,1091,F_p245),mxs_appl_list_expr(_m,1091,E_p246));
				goto L193;
			}
			Lp66: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp67;
				if( !mxs_is(_c,0,mxv_IR,_PatternCase_) ) goto Lp67;
				E_p248 = mxs_son(_c,0,2,mxv_anchor);
				mxv_IR = E_p248;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp67;
				mxv_i193 = mxs_appl_list_expr(_m,1092,E_p248);
				goto L193;
			}
			Lp67: ;
				mxv_i193 = mxs_ApplList(_m,1093);
			L193: ;
		}
		AL_l35 = mxv_i193;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_rbroth(_m,1094,N),mxs_nil(_m,1094)) ){
				mxv_i194 = AL_l35;
				goto L194;
			}
			mxv_i194 = mxs_conc(_m,1094,AL_l35,mxs_appl_list_case(_m,1094,mxs_rbroth(_m,1094,N)));
			L194: ;
		}
		mxv_l35 = mxv_i194;
	}
	mxv_ax = mxs_index(_c,0,N,_Case_);
	mxa_appl_list_case[ mxv_ax ] = mxv_l35;
}

static  void  mxe_appl_list_expr( ELEMENT N ){
	ELEMENT  mxv_i196, mxv_i195, C_p251, E_p252, E_p254, E_p257, mxv_i203, mxv_i202, mxv_i201, mxv_i200, mxv_i199, mxv_i198, mxv_i197, mxv_l36, AL_l36,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp68;
				if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp68;
				mxv_IR = mxs_son(_c,0,1,mxv_anchor);
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp68;
				if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp68;
				C_p251 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
				mxv_IR = C_p251;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp68;
				E_p252 = mxs_son(_c,0,2,mxv_anchor);
				mxv_IR = E_p252;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp68;
				mxv_i195 = mxs_conc(_m,1099,mxs_appl_list_case(_m,1099,C_p251),mxs_appl_list_expr(_m,1099,E_p252));
				goto L195;
			}
			Lp68: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp69;
				if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp69;
				E_p254 = mxs_son(_c,0,2,mxv_anchor);
				mxv_IR = E_p254;
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp69;
				mxv_i195 = mxs_appl_list_expr(_m,1100,E_p254);
				goto L195;
			}
			Lp69: ;
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp70;
				if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp70;
				mxv_IR = mxs_son(_c,0,2,mxv_anchor);
				if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp70;
				if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp70;
				E_p257 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
				mxv_IR = E_p257;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp70;
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_relacc_nr(_m,1102,N),mxs_nil(_m,1102)) ){
					mxv_i196 = mxs_appl_list_expr(_m,1102,E_p257);
					goto L196;
				}
				mxv_i196 = mxs_appback(_m,1103,mxs_appl_list_expr(_m,1103,E_p257),N);
				L196: ;
			}
				mxv_i195 = mxv_i196;
				goto L195;
			}
			Lp70: ;
				mxv_i195 = mxs_ApplList(_m,1104);
			L195: ;
		}
		AL_l36 = mxv_i195;
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_rbroth(_m,1105,N),mxs_nil(_m,1105)) ){
				mxv_i198 = mxs_true(_m,0);
				goto L198;
			}
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( mxs_is(_m,1105,mxs_rbroth(_m,1105,N),_Int_) ){
				mxv_i200 = mxs_true(_m,0);
				goto L200;
			}
		{  /* FormulaCaseList */
		{  /* FormulaCaseList */
			if( mxs_is(_m,1105,mxs_fath(_m,1105,N),_CaseRule_) ){
				mxv_i202 = mxs_true(_m,0);
				goto L202;
			}
		{  /* FormulaCaseList */
			if( mxs_is(_m,1105,mxs_fath(_m,1105,N),_CaseIs_) ){
				mxv_i203 = mxs_true(_m,0);
				goto L203;
			}
			mxv_i203 = mxs_false(_m,0);
			L203: ;
		}
			mxv_i202 = mxv_i203;
			L202: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i202) ){
				mxv_i201 = mxs_true(_m,0);
				goto L201;
			}
			mxv_i201 = mxs_false(_m,0);
			L201: ;
		}
			mxv_i200 = mxv_i201;
			L200: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i200) ){
				mxv_i199 = mxs_true(_m,0);
				goto L199;
			}
			mxv_i199 = mxs_false(_m,0);
			L199: ;
		}
			mxv_i198 = mxv_i199;
			L198: ;
		}
			if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i198) ){
				mxv_i197 = AL_l36;
				goto L197;
			}
			mxv_i197 = mxs_conc(_m,1106,AL_l36,mxs_appl_list_expr(_m,1106,mxs_rbroth(_m,1106,N)));
			L197: ;
		}
		mxv_l36 = mxv_i197;
	}
	mxv_ax = mxs_index(_c,0,N,_Expr_);
	mxa_appl_list_expr[ mxv_ax ] = mxv_l36;
}

static  void  mxe_appl_list( ELEMENT N ){
	ELEMENT  mxv_i204, E_p259,
		mxv_ax, mxv_par = N;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp71;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp71;
			E_p259 = mxs_son(_c,0,-1,mxv_anchor);
			mxv_IR = E_p259;
			if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp71;
			mxv_i204 = mxs_appl_list_expr(_m,1110,E_p259);
			goto L204;
		}
		Lp71: ;
			mxv_i204 = mxs_ApplList(_m,1111);
		L204: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FctOrAtt_);
	mxa_appl_list[ mxv_ax ] = mxv_i204;
}

static  void  mxe_def_value( ELEMENT N ){
	ELEMENT  mxv_i208, mxv_i207, mxv_l37, I_l37,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		I_l37 = mxs_idtos(_m,1139,mxs_term(_m,1139,mxs_son(_m,1139,mxs_itoe(_c,0,1),N)));
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,I_l37,mxs_atoe(_c,0,"fath")) ){
				mxv_i207 = mxs_TWfath(_m,1140);
				goto L207;
			}
			if( mxs_eq(_m,0,I_l37,mxs_atoe(_c,0,"son")) ){
				mxv_i207 = mxs_TWson(_m,1141,mxs_itoe(_c,0,0));
				goto L207;
			}
			if( mxs_eq(_m,0,I_l37,mxs_atoe(_c,0,"rbroth")) ){
				mxv_i207 = mxs_TWrbroth(_m,1142);
				goto L207;
			}
			if( mxs_eq(_m,0,I_l37,mxs_atoe(_c,0,"lbroth")) ){
				mxv_i207 = mxs_TWlbroth(_m,1143);
				goto L207;
			}
			if( mxs_eq(_m,0,I_l37,mxs_atoe(_c,0,"nil")) ){
				mxv_i207 = mxs_TW_emptyset(_m,1144);
				goto L207;
			}
		{  /* PatternCaseList */
			{
				ELEMENT mxv_anchor, mxv_IR;
				mxv_anchor = N;
				mxv_IR = mxv_anchor;
				if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp72;
				mxv_IR = mxs_fath(_c,0,mxv_anchor);
				if( mxv_IR == mxs_nil(_c,0) ) goto Lp72;
				if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp72;
				if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp72;
				mxv_i208 = N;
				goto L208;
			}
			Lp72: ;
				mxv_i208 = mxs_nil(_m,1146);
			L208: ;
		}
			mxv_i207 = mxv_i208;
			L207: ;
		}
		mxv_l37 = mxv_i207;
	}
	mxv_ax = mxs_index(_c,0,N,_DefId_);
	mxa_def_value[ mxv_ax ] = mxv_l37;
}

static  void  mxe_node_parnr( ELEMENT N ){
	ELEMENT  mxv_i210, SI_p267, SI_p270,
		mxv_ax, mxv_par = N;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp73;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp73;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp73;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp73;
			SI_p267 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = SI_p267;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp73;
			mxv_i210 = mxs_node_parnr_fct(_m,1156,SI_p267);
			goto L210;
		}
		Lp73: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp74;
			if( !mxs_is(_c,0,mxv_IR,_FuncDecl_) ) goto Lp74;
			mxv_IR = mxs_son(_c,0,2,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp74;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp74;
			SI_p270 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
			mxv_IR = SI_p270;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp74;
			mxv_i210 = mxs_node_parnr_fct(_m,1157,SI_p270);
			goto L210;
		}
		Lp74: ;
			mxv_i210 = mxs_nil(_m,1158);
		L210: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FctOrAttDecl_);
	mxa_node_parnr[ mxv_ax ] = mxv_i210;
}

static  void  mxe_appl_value( ELEMENT N ){
	ELEMENT  mxv_i213, SN_p273, mxv_i212, mxv_l38, F_l38, mxv_i211,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_relacc_nr(_m,1163,N),mxs_nil(_m,1163))) ){
			mxv_i211 = mxs_RelevAcc(_m,1163,mxs_relacc_nr(_m,1163,N));
			goto L211;
		}
	{  /* LetExpr */
		F_l38 = mxs_def_value(_m,1165,mxs_decl(_m,1165,mxs_son(_m,1165,mxs_itoe(_c,0,1),N)));
		{  /* FormulaCaseList */
			if( mxs_is(_m,1166,F_l38,_TWson) ){
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = N;
					mxv_IR = mxv_anchor;
					if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp75;
					if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp75;
					mxv_IR = mxs_son(_c,0,2,mxv_anchor);
					if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp75;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp75;
					SN_p273 = mxs_son(_c,0,1,mxs_son(_c,0,2,mxv_anchor));
					mxv_IR = SN_p273;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp75;
					if( !mxs_is(_c,0,mxv_IR,_Int_) ) goto Lp75;
					mxv_i213 = mxs_TWson(_m,1167,mxs_term(_m,1167,SN_p273));
					goto L213;
				}
				Lp75: ;
					mxv_i213 = F_l38;
				L213: ;
			}
				mxv_i212 = mxv_i213;
				goto L212;
			}
			mxv_i212 = F_l38;
			L212: ;
		}
		mxv_l38 = mxv_i212;
	}
		mxv_i211 = mxv_l38;
		L211: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FuncAppl_);
	mxa_appl_value[ mxv_ax ] = mxv_i211;
}

static  void  mxe_nodepar_expr( ELEMENT N ){
	ELEMENT  mxv_i215, mxv_i214, mxv_l39, F_l39,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		F_l39 = mxs_fath(_m,1172,mxs_decl(_m,1172,mxs_son(_m,1172,mxs_itoe(_c,0,1),N)));
		{  /* FormulaCaseList */
			if( mxs_is(_m,1173,F_l39,_FctOrAttDecl_) ){
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_node_parnr(_m,1174,F_l39),mxs_nil(_m,1174)) ){
					mxv_i215 = mxs_nil(_m,1174);
					goto L215;
				}
				mxv_i215 = mxs_son(_m,1174,mxs_node_parnr(_m,1174,F_l39),mxs_son(_m,1174,mxs_itoe(_c,0,2),N));
				L215: ;
			}
				mxv_i214 = mxv_i215;
				goto L214;
			}
			mxv_i214 = mxs_nil(_m,1175);
			L214: ;
		}
		mxv_l39 = mxv_i214;
	}
	mxv_ax = mxs_index(_c,0,N,_FuncAppl_);
	mxa_nodepar_expr[ mxv_ax ] = mxv_l39;
}

static  void  mxe_valueterm_list( ELEMENT C, ELEMENT mxv_attvalue, int state, ELEMENT *mxv_waitpar ){
	ELEMENT  mxv_a1133, mxv_a1136, mxv_a1138, mxv_i225,
		mxv_ax, mxv_res, mxv_par = C;
	AttInstSq mxv_waitsq, mxv_wsq;

	switch(state) {
		case 1133 :
			mxv_a1133 = mxv_attvalue;
			goto Lz1133;
		case 1136 :
			mxv_a1136 = mxv_attvalue;
			goto Lz1136;
		case 1138 :
			mxv_a1136 = mxv_waitpar[0];
			mxv_a1138 = mxv_attvalue;
			goto Lz1138;
	}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_rbroth(_m,1219,C),mxs_nil(_m,1219)) ){
		{  /* Attribute access */
			mxv_ax = mxs_son(_m,1219,mxs_itoe(_c,0,2),C);
			mxv_a1133 = mxs_valueterm(_m,1219,mxv_ax);
			if( mxv_a1133==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_valueterm_list,mxv_par,1133,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				return;
			}
			Lz1133:;
		}
			mxv_i225 = mxv_a1133;
			goto L225;
		}
	{  /* Attribute access */
		mxv_ax = mxs_rbroth(_m,1220,C);
		mxv_a1136 = mxs_valueterm_list(_m,1220,mxv_ax);
		if( mxv_a1136==MAXUNDEF ){
			insAttInst((EVALFCT)mxe_valueterm_list,mxv_par,1136,mxw_valueterm_list,mxs_index(_c,0,mxv_ax,_Case_));
			return;
		}
		Lz1136:;
	}
	{  /* Attribute access */
		mxv_ax = mxs_son(_m,1220,mxs_itoe(_c,0,2),C);
		mxv_a1138 = mxs_valueterm(_m,1220,mxv_ax);
		if( mxv_a1138==MAXUNDEF ){ ELEMENT *P;
			P = insAttInst((EVALFCT)mxe_valueterm_list,mxv_par,1138,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
			P[0] = mxv_a1136;
			return;
		}
		Lz1138:;
	}
		mxv_i225 = mxs_TW_or(_m,1220,mxv_a1136,mxv_a1138);
		L225: ;
	}
	mxv_ax = mxs_index(_c,0,C,_Case_);
	mxv_res = mxa_valueterm_list[ mxv_ax ] = mxv_i225;

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
	ELEMENT  mxv_a1144, mxv_i227, mxv_a1148, mxv_a1149, mxv_a1150, mxv_a1151, mxv_i228, mxv_a1158, mxv_a1163, mxv_l41, A_l41, mxv_i229, mxv_a1166, mxv_i226, C_p280, EX_p281, E_p283, E_p286, F_p287, PAT_p290,
		mxv_ax, mxv_res, mxv_par = N;
	AttInstSq mxv_waitsq, mxv_wsq;

	switch(state) {
		case 1144 :
			mxv_a1144 = mxv_attvalue;
			goto Lz1144;
		case 1148 :
			EX_p281 = mxv_waitpar[0];
			mxv_a1148 = mxv_attvalue;
			goto Lz1148;
		case 1149 :
			mxv_a1148 = mxv_waitpar[0];
			mxv_a1149 = mxv_attvalue;
			goto Lz1149;
		case 1150 :
			mxv_a1150 = mxv_attvalue;
			goto Lz1150;
		case 1151 :
			mxv_a1151 = mxv_attvalue;
			goto Lz1151;
		case 1158 :
			mxv_a1158 = mxv_attvalue;
			goto Lz1158;
		case 1163 :
			A_l41 = mxv_waitpar[0];
			PAT_p290 = mxv_waitpar[1];
			mxv_a1163 = mxv_attvalue;
			goto Lz1163;
		case 1166 :
			mxv_a1166 = mxv_attvalue;
			goto Lz1166;
	}
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp79;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_appl_value(_m,1224,N),mxs_TW_emptyset(_m,1224)) ){
				mxv_i227 = mxs_TW_emptyset(_m,1224);
				goto L227;
			}
		{  /* Attribute access */
			mxv_ax = mxs_nodepar_expr(_m,1225,N);
			mxv_a1144 = mxs_valueterm(_m,1225,mxv_ax);
			if( mxv_a1144==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_valueterm,mxv_par,1144,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				return;
			}
			Lz1144:;
		}
			mxv_i227 = mxs_TW_conc(_m,1225,mxv_a1144,mxs_appl_value(_m,1225,N));
			L227: ;
		}
			mxv_i226 = mxv_i227;
			goto L226;
		}
		Lp79: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp80;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp80;
			mxv_IR = mxs_son(_c,0,1,mxv_anchor);
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp80;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp80;
			C_p280 = mxs_son(_c,0,1,mxs_son(_c,0,1,mxv_anchor));
			mxv_IR = C_p280;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp80;
			EX_p281 = mxs_son(_c,0,2,mxv_anchor);
			mxv_IR = EX_p281;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp80;
		{  /* Attribute access */
			mxv_ax = C_p280;
			mxv_a1148 = mxs_valueterm_list(_m,1226,mxv_ax);
			if( mxv_a1148==MAXUNDEF ){ ELEMENT *P;
				P = insAttInst((EVALFCT)mxe_valueterm,mxv_par,1148,mxw_valueterm_list,mxs_index(_c,0,mxv_ax,_Case_));
				P[0] = EX_p281;
				return;
			}
			Lz1148:;
		}
		{  /* Attribute access */
			mxv_ax = EX_p281;
			mxv_a1149 = mxs_valueterm(_m,1226,mxv_ax);
			if( mxv_a1149==MAXUNDEF ){ ELEMENT *P;
				P = insAttInst((EVALFCT)mxe_valueterm,mxv_par,1149,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				P[0] = mxv_a1148;
				return;
			}
			Lz1149:;
		}
			mxv_i226 = mxs_TW_or(_m,1226,mxv_a1148,mxv_a1149);
			goto L226;
		}
		Lp80: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp81;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp81;
			E_p283 = mxs_son(_c,0,3,mxv_anchor);
			mxv_IR = E_p283;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp81;
		{  /* Attribute access */
			mxv_ax = E_p283;
			mxv_a1150 = mxs_valueterm(_m,1227,mxv_ax);
			if( mxv_a1150==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_valueterm,mxv_par,1150,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				return;
			}
			Lz1150:;
		}
			mxv_i226 = mxv_a1150;
			goto L226;
		}
		Lp81: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp82;
			mxv_IR = mxs_fath(_c,0,mxv_anchor);
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp82;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp82;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp82;
			E_p286 = mxs_rbroth(_c,0,mxv_anchor);
			mxv_IR = E_p286;
			if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp82;
		{  /* Attribute access */
			mxv_ax = E_p286;
			mxv_a1151 = mxs_valueterm(_m,1228,mxv_ax);
			if( mxv_a1151==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_valueterm,mxv_par,1151,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				return;
			}
			Lz1151:;
		}
			mxv_i226 = mxv_a1151;
			goto L226;
		}
		Lp82: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR))) ) goto Lp83;
			if( mxs_before(_c,0,mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp83;
			F_p287 = mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor));
			mxv_IR = F_p287;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp83;
			if( mxs_numsons(_c,0, mxv_IR ) < 3 ) goto Lp83;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp83;
			mxv_IR = mxs_fath(_c,0,mxv_anchor);
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp83;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp83;
			if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp83;
			if( !mxs_is(_c,0,mxv_IR,_NameList_) ) goto Lp83;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_son(_m,1231,mxs_node_parnr(_m,1231,F_p287),mxs_fath(_m,1231,N)),N) ){
				mxv_i228 = mxs_TW_identabb(_m,1231);
				goto L228;
			}
			mxv_i228 = mxs_nil(_m,1231);
			L228: ;
		}
			mxv_i226 = mxv_i228;
			goto L226;
		}
		Lp83: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp84;
			PAT_p290 = mxs_fath(_c,0,mxv_anchor);
			mxv_IR = PAT_p290;
			if( mxv_IR == mxs_nil(_c,0) ) goto Lp84;
			if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp84;
			if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp84;
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,mxs_bind_pos(_m,1234,N),N)) ){
			{  /* Attribute access */
				mxv_ax = mxs_bind_pos(_m,1234,N);
				mxv_a1158 = mxs_valueterm(_m,1234,mxv_ax);
				if( mxv_a1158==MAXUNDEF ){
					insAttInst((EVALFCT)mxe_valueterm,mxv_par,1158,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
					return;
				}
				Lz1158:;
			}
				mxv_i229 = mxv_a1158;
				goto L229;
			}
		{  /* LetExpr */
			A_l41 = mxs_pat_anchor(_m,1235,mxs_encl_patcase(_m,1235,N));
			{  /* Attribute access */
				mxv_ax = mxs_son(_m,1236,mxs_itoe(_c,0,3),A_l41);
				mxv_a1163 = mxs_valueterm(_m,1236,mxv_ax);
				if( mxv_a1163==MAXUNDEF ){ ELEMENT *P;
					P = insAttInst((EVALFCT)mxe_valueterm,mxv_par,1163,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
					P[0] = A_l41;
					P[1] = PAT_p290;
					return;
				}
				Lz1163:;
			}
			mxv_l41 = mxs_TW_conc(_m,1236,mxv_a1163,mxs_pat_way(_m,1236,A_l41,PAT_p290));
		}
			mxv_i229 = mxv_l41;
			L229: ;
		}
			mxv_i226 = mxv_i229;
			goto L226;
		}
		Lp84: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Name_) ) goto Lp85;
		{  /* Attribute access */
			mxv_ax = mxs_bind_pos(_m,1238,N);
			mxv_a1166 = mxs_valueterm(_m,1238,mxv_ax);
			if( mxv_a1166==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_valueterm,mxv_par,1166,mxw_valueterm,mxs_index(_c,0,mxv_ax,_Expr_));
				return;
			}
			Lz1166:;
		}
			mxv_i226 = mxv_a1166;
			goto L226;
		}
		Lp85: ;
			mxv_i226 = mxs_nil(_m,1239);
		L226: ;
	}
	mxv_ax = mxs_index(_c,0,N,_Expr_);
	mxv_res = mxa_valueterm[ mxv_ax ] = mxv_i226;

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
	mxa_attr_list_matlist[ mxv_ax ] = mxs_enter_attrgroup_list(_m,1266,mxs_itoe(_c,0,1),mxs_attr_list_groups(_m,1266,N),mxs_RefList(_m,1266));
}

static  void  mxe_result_value( ELEMENT N ){
	ELEMENT  mxv_l42, subtnr_l42,
		mxv_ax, mxv_par = N;
	{  /* LetExpr */
		subtnr_l42 = mxs_sub(_m,1273,mxs_eval_groupnr(_m,1273,N),mxs_eval_prev_grnum(_m,1273,mxs_fath(_m,1273,N)));
		mxv_l42 = mxs_mat_lookup(_m,1274,mxs_subterm(_m,1274,subtnr_l42,mxs_attr_list_matlist(_m,1274,mxs_fath(_m,1274,N))),mxs_numsubterms(_m,1275,mxs_eval_group(_m,1275,N)),mxs_group_index(_m,1275,N));
	}
	mxv_ax = mxs_index(_c,0,N,_FctOrAtt_);
	mxa_result_value[ mxv_ax ] = mxv_l42;
}

static  void  mxe_is_relev_att_access( ELEMENT FA ){
	ELEMENT  mxv_i313, mxv_i312, mxv_i311, mxv_i310, mxv_i309, mxv_i308, mxv_i307, mxv_l51, E_l51, mxv_l50, D_l50,
		mxv_ax, mxv_par = FA;
	{  /* LetExpr */
		D_l50 = mxs_fath(_m,1445,mxs_decl(_m,1445,mxs_son(_m,1445,mxs_itoe(_c,0,1),FA)));
		{  /* LetExpr */
			E_l51 = mxs_encl_fctoratt(_m,1446,FA);
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,1447,D_l50,_FctOrAtt_)) ){
					mxv_i308 = mxs_false(_m,0);
					goto L308;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_is(_m,1447,E_l51,_FctOrAtt_)) ){
					mxv_i310 = mxs_false(_m,0);
					goto L310;
				}
			{  /* FormulaCaseList */
			{  /* FormulaCaseList */
				if( ( ! mxs_eq(_m,0,mxs_eval_groupnr(_m,1447,D_l50),mxs_eval_groupnr(_m,1447,E_l51))) ){
					mxv_i312 = mxs_false(_m,0);
					goto L312;
				}
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,mxs_contains_attr(_m,1448,mxs_eval_group(_m,1448,E_l51)),mxs_true(_m,1448)) ){
					mxv_i313 = mxs_true(_m,0);
					goto L313;
				}
				mxv_i313 = mxs_false(_m,0);
				L313: ;
			}
				mxv_i312 = mxv_i313;
				L312: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i312) ){
					mxv_i311 = mxs_true(_m,0);
					goto L311;
				}
				mxv_i311 = mxs_false(_m,0);
				L311: ;
			}
				mxv_i310 = mxv_i311;
				L310: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i310) ){
					mxv_i309 = mxs_true(_m,0);
					goto L309;
				}
				mxv_i309 = mxs_false(_m,0);
				L309: ;
			}
				mxv_i308 = mxv_i309;
				L308: ;
			}
				if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i308) ){
					mxv_i307 = mxs_true(_m,1448);
					goto L307;
				}
				mxv_i307 = mxs_false(_m,1448);
				L307: ;
			}
			mxv_l51 = mxv_i307;
		}
		mxv_l50 = mxv_l51;
	}
	mxv_ax = mxs_index(_c,0,FA,_FuncAppl_);
	mxa_is_relev_att_access[ mxv_ax ] = mxv_l50;
}

static  void  mxe_appl_order( ELEMENT N ){
	ELEMENT  mxv_i315, mxv_l52, ORD_l52, mxv_i314,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_is_relev_att_access(_m,1451,N),mxs_true(_m,1451)) ){
		{  /* LetExpr */
			ORD_l52 = mxs_val_order(_m,1453,mxs_normalform(_m,1453,mxs_FList(_m,1453),mxs_valueterm(_m,1453,mxs_nodepar_expr(_m,1453,N)),mxs_fath(_m,1453,mxs_encl_fctoratt(_m,1453,N))));
			{  /* FormulaCaseList */
				if( mxs_eq(_m,0,ORD_l52,mxs_nil(_m,1454)) ){
					mxv_i315 = mxs_Ord_nothing(_m,1454);
					goto L315;
				}
				mxv_i315 = ORD_l52;
				L315: ;
			}
			mxv_l52 = mxv_i315;
		}
			mxv_i314 = mxv_l52;
			goto L314;
		}
		mxv_i314 = mxs_Ord_neutral(_m,1455);
		L314: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FuncAppl_);
	mxa_appl_order[ mxv_ax ] = mxv_i314;
}

static  void  mxe_appl_relacc_list( ELEMENT N ){
	ELEMENT 
		mxv_ax, mxv_par = N;
	mxv_ax = mxs_index(_c,0,N,_FctOrAtt_);
	mxa_appl_relacc_list[ mxv_ax ] = mxs_filter_relev_acc(_m,1464,mxs_appl_list(_m,1464,N));
}

static  void  mxe_maybe_wait( ELEMENT N ){
	ELEMENT  mxv_i326, mxv_i325, mxv_i324, mxv_i323, mxv_i331, mxv_i330, mxv_i329, mxv_i328, mxv_i327, mxv_i322, mxv_i321, mxv_i320, mxv_i319, mxv_l54, EA_l54, mxv_l53, FD_l53, mxv_i318,
		mxv_ax, mxv_par = N;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_is_relev_att_access(_m,1486,N),mxs_true(_m,1486)) ){
		{  /* LetExpr */
			FD_l53 = mxs_fath(_m,1487,mxs_decl(_m,1487,mxs_son(_m,1487,mxs_itoe(_c,0,1),N)));
			{  /* LetExpr */
				EA_l54 = mxs_encl_fctoratt(_m,1488,N);
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( mxs_no_strategy_found(_m,1490,EA_l54) ){
						mxv_i320 = mxs_true(_m,0);
						goto L320;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_eq(_m,0,mxs_eval_finegroup(_m,1492,FD_l53),mxs_eval_finegroup(_m,1492,EA_l54))) ){
						mxv_i323 = mxs_false(_m,0);
						goto L323;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_eq(_m,0,mxs_eval_aftbef(_m,1493,FD_l53),mxs_eval_aftbef(_m,1493,EA_l54))) ){
						mxv_i325 = mxs_false(_m,0);
						goto L325;
					}
				{  /* FormulaCaseList */
					if( mxs_maybe_same_node(_m,1493,mxs_appl_order(_m,1493,N)) ){
						mxv_i326 = mxs_true(_m,0);
						goto L326;
					}
					mxv_i326 = mxs_false(_m,0);
					L326: ;
				}
					mxv_i325 = mxv_i326;
					L325: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i325) ){
						mxv_i324 = mxs_true(_m,0);
						goto L324;
					}
					mxv_i324 = mxs_false(_m,0);
					L324: ;
				}
					mxv_i323 = mxv_i324;
					L323: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i323) ){
						mxv_i322 = mxs_true(_m,0);
						goto L322;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1495,EA_l54,_FctOrAtt_)) ){
						mxv_i328 = mxs_false(_m,0);
						goto L328;
					}
				{  /* FormulaCaseList */
				{  /* FormulaCaseList */
					if( ( ! mxs_is(_m,1495,FD_l53,_Function_)) ){
						mxv_i330 = mxs_false(_m,0);
						goto L330;
					}
				{  /* FormulaCaseList */
					if( mxs_eq(_m,0,mxs_eval_group(_m,1496,EA_l54),mxs_eval_group(_m,1496,FD_l53)) ){
						mxv_i331 = mxs_true(_m,0);
						goto L331;
					}
					mxv_i331 = mxs_false(_m,0);
					L331: ;
				}
					mxv_i330 = mxv_i331;
					L330: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i330) ){
						mxv_i329 = mxs_true(_m,0);
						goto L329;
					}
					mxv_i329 = mxs_false(_m,0);
					L329: ;
				}
					mxv_i328 = mxv_i329;
					L328: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i328) ){
						mxv_i327 = mxs_true(_m,0);
						goto L327;
					}
					mxv_i327 = mxs_false(_m,0);
					L327: ;
				}
					mxv_i322 = mxv_i327;
					L322: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i322) ){
						mxv_i321 = mxs_true(_m,0);
						goto L321;
					}
					mxv_i321 = mxs_false(_m,0);
					L321: ;
				}
					mxv_i320 = mxv_i321;
					L320: ;
				}
					if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i320) ){
						mxv_i319 = mxs_true(_m,1498);
						goto L319;
					}
					mxv_i319 = mxs_false(_m,1498);
					L319: ;
				}
				mxv_l54 = mxv_i319;
			}
			mxv_l53 = mxv_l54;
		}
			mxv_i318 = mxv_l53;
			goto L318;
		}
		mxv_i318 = mxs_false(_m,1499);
		L318: ;
	}
	mxv_ax = mxs_index(_c,0,N,_FuncAppl_);
	mxa_maybe_wait[ mxv_ax ] = mxv_i318;
}

static  void  mxe_cgen_name( ELEMENT N, ELEMENT mxv_attvalue, int state, ELEMENT *mxv_waitpar ){
	ELEMENT  mxv_i334, L_p298, I_p300, P_p301, I_p303, mxv_a1548, mxv_i333, mxv_i332,
		mxv_ax, mxv_res, mxv_par = N;
	AttInstSq mxv_waitsq, mxv_wsq;

	switch(state) {
		case 1548 :
			mxv_a1548 = mxv_attvalue;
			goto Lz1548;
	}
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Name_) ) goto Lp87;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,N,mxs_bind_pos(_m,1516,N)) ){
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = N;
					mxv_IR = mxv_anchor;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp88;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp88;
					L_p298 = mxs_fath(_c,0,mxv_anchor);
					mxv_IR = L_p298;
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp88;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp88;
					if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp88;
					I_p300 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = I_p300;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp88;
					mxv_i334 = mxi_string_conc(_m,1517,3,mxs_id(_m,1517,I_p300),mxs_atoe(_c,0,"_l"),mxs_aux_itoa(_m,1517,mxs_index(_m,1517,L_p298,_LetExpr_)));
					goto L334;
				}
				Lp88: ;
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = N;
					mxv_IR = mxv_anchor;
					if( mxv_IR != mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR)) ) goto Lp89;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp89;
					P_p301 = mxs_fath(_c,0,mxv_anchor);
					mxv_IR = P_p301;
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp89;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp89;
					if( !mxs_is(_c,0,mxv_IR,_Pattern_) ) goto Lp89;
					I_p303 = mxs_son(_c,0,1,mxv_anchor);
					mxv_IR = I_p303;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp89;
					mxv_i334 = mxi_string_conc(_m,1518,3,mxs_id(_m,1518,I_p303),mxs_atoe(_c,0,"_p"),mxs_aux_itoa(_m,1518,mxs_index(_m,1518,P_p301,_Pattern_)));
					goto L334;
				}
				Lp89: ;
					mxv_i334 = mxs_id(_m,1519,mxs_son(_m,1519,mxs_itoe(_c,0,1),N));
				L334: ;
			}
				mxv_i333 = mxv_i334;
				goto L333;
			}
		{  /* Attribute access */
			mxv_ax = mxs_bind_pos(_m,1520,N);
			mxv_a1548 = mxs_cgen_name(_m,1520,mxv_ax);
			if( mxv_a1548==MAXUNDEF ){
				insAttInst((EVALFCT)mxe_cgen_name,mxv_par,1548,mxw_cgen_name,mxs_index(_c,0,mxv_ax,_IntResOrName_));
				return;
			}
			Lz1548:;
		}
			mxv_i333 = mxv_a1548;
			L333: ;
		}
			mxv_i332 = mxv_i333;
			goto L332;
		}
		Lp87: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FuncAppl_) ) goto Lp90;
			mxv_i332 = mxi_string_conc(_m,1521,2,mxs_atoe(_c,0,"mxv_a"),mxs_aux_itoa(_m,1521,mxs_index(_m,1521,N,_FuncAppl_)));
			goto L332;
		}
		Lp90: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp91;
			mxv_i332 = mxi_string_conc(_m,1522,2,mxs_atoe(_c,0,"mxv_l"),mxs_aux_itoa(_m,1522,mxs_index(_m,1522,N,_LetExpr_)));
			goto L332;
		}
		Lp91: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp92;
			mxv_i332 = mxi_string_conc(_m,1523,2,mxs_atoe(_c,0,"mxv_i"),mxs_aux_itoa(_m,1523,mxs_index(_m,1523,N,_IfExpr_)));
			goto L332;
		}
		Lp92: ;
			mxv_i332 = mxs_nil(_m,1524);
		L332: ;
	}
	mxv_ax = mxs_index(_c,0,N,_IntResOrName_);
	mxv_res = mxa_cgen_name[ mxv_ax ] = mxv_i332;

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
	mxa_sces_appl[ mxv_ax ] = mxs_intresexprs(_m,1543,mxs_son(_m,1543,mxs_itoe(_c,0,-1),A));
}

static  void  mxe_sces1_cond( ELEMENT C ){
	ELEMENT 
		mxv_ax, mxv_par = C;
	mxv_ax = mxs_index(_c,0,C,_Condition_);
	mxa_sces1_cond[ mxv_ax ] = mxs_intresexprs(_m,1544,mxs_son(_m,1544,mxs_itoe(_c,0,2),C));
}

static  void  mxe_sces2_cond( ELEMENT C ){
	ELEMENT 
		mxv_ax, mxv_par = C;
	mxv_ax = mxs_index(_c,0,C,_Condition_);
	mxa_sces2_cond[ mxv_ax ] = mxs_intresexprs(_m,1545,mxs_son(_m,1545,mxs_itoe(_c,0,3),C));
}

static  void  mxe_sces1_let( ELEMENT L ){
	ELEMENT 
		mxv_ax, mxv_par = L;
	mxv_ax = mxs_index(_c,0,L,_LetExpr_);
	mxa_sces1_let[ mxv_ax ] = mxs_intresexprs(_m,1546,mxs_son(_m,1546,mxs_itoe(_c,0,2),L));
}

static  void  mxe_sces2_let( ELEMENT L ){
	ELEMENT 
		mxv_ax, mxv_par = L;
	mxv_ax = mxs_index(_c,0,L,_LetExpr_);
	mxa_sces2_let[ mxv_ax ] = mxs_intresexprs(_m,1547,mxs_son(_m,1547,mxs_itoe(_c,0,3),L));
}

static  void  mxe_sces_if( ELEMENT I ){
	ELEMENT 
		mxv_ax, mxv_par = I;
	mxv_ax = mxs_index(_c,0,I,_IfExpr_);
	mxa_sces_if[ mxv_ax ] = mxs_intresexprs(_m,1548,mxs_son(_m,1548,mxs_itoe(_c,0,2),I));
}

static  void  mxe_sces1_fcase( ELEMENT F ){
	ELEMENT 
		mxv_ax, mxv_par = F;
	mxv_ax = mxs_index(_c,0,F,_FormulaCase_);
	mxa_sces1_fcase[ mxv_ax ] = mxs_intresexprs(_m,1549,mxs_son(_m,1549,mxs_itoe(_c,0,1),F));
}

static  void  mxe_sces2_fcase( ELEMENT F ){
	ELEMENT 
		mxv_ax, mxv_par = F;
	mxv_ax = mxs_index(_c,0,F,_FormulaCase_);
	mxa_sces2_fcase[ mxv_ax ] = mxs_intresexprs(_m,1550,mxs_son(_m,1550,mxs_itoe(_c,0,2),F));
}

static  void  mxe_sces_pcase( ELEMENT P ){
	ELEMENT 
		mxv_ax, mxv_par = P;
	mxv_ax = mxs_index(_c,0,P,_PatternCase_);
	mxa_sces_pcase[ mxv_ax ] = mxs_intresexprs(_m,1551,mxs_son(_m,1551,mxs_itoe(_c,0,2),P));
}

static  void  mxe_sces_attacc( ELEMENT FA ){
	ELEMENT  mxv_i349,
		mxv_ax, mxv_par = FA;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_maybe_wait(_m,1553,FA),mxs_true(_m,1553)) ){
			mxv_i349 = mxs_intresexprs(_m,1553,mxs_son(_m,1553,mxs_itoe(_c,0,2),FA));
			goto L349;
		}
		mxv_i349 = mxs_nil(_m,1553);
		L349: ;
	}
	mxv_ax = mxs_index(_c,0,FA,_FuncAppl_);
	mxa_sces_attacc[ mxv_ax ] = mxv_i349;
}

static  void  mxe_lokvar_need( ELEMENT N ){
	ELEMENT 
		mxv_ax, mxv_par = N;
	mxv_ax = mxs_index(_c,0,N,_FctOrAtt_);
	mxa_lokvar_need[ mxv_ax ] = mxs_aux_var_need(_m,1600,mxs_add(_m,1600,mxs_index(_m,1600,mxs_son(_m,1600,mxs_itoe(_c,0,1),mxs_son(_m,1600,mxs_itoe(_c,0,3),N)),_Name_),mxs_itoe(_c,0,1)),N);
}

static  void  mxe_intres_collect( ELEMENT N ){
	ELEMENT  mxv_i367, mxv_i366, mxv_i368, X_p332, X_p337, mxv_i369, mxv_i370, V_p341, X_p343, mxv_l60, LCP_l60, mxv_l59, EIR_l59, mxv_l58, RCL_l58, mxv_l57, PIR_l57, mxv_i365, mxv_i364,
		mxv_ax, mxv_par = N;
	{  /* PatternCaseList */
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_FctOrAtt_) ) goto Lp103;
			mxv_i364 = mxs_IntResList(_m,1605);
			goto L364;
		}
		Lp103: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Predicate_) ) goto Lp104;
			mxv_i364 = mxs_nil(_m,1606);
			goto L364;
		}
		Lp104: ;
		{
			ELEMENT mxv_anchor, mxv_IR;
			mxv_anchor = N;
			mxv_IR = mxv_anchor;
			if( !mxs_is(_c,0,mxv_IR,_Condition_) ) goto Lp105;
			mxv_i364 = mxs_nil(_m,1607);
			goto L364;
		}
		Lp105: ;
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,1608,N,_FuncAppl_)) ){
			mxv_i366 = mxs_false(_m,0);
			goto L366;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_maybe_wait(_m,1608,N),mxs_false(_m,1608)) ){
			mxv_i367 = mxs_true(_m,0);
			goto L367;
		}
		mxv_i367 = mxs_false(_m,0);
		L367: ;
	}
		mxv_i366 = mxv_i367;
		L366: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i366) ){
			mxv_i365 = mxs_nil(_m,1608);
			goto L365;
		}
	{  /* LetExpr */
		PIR_l57 = mxs_encl_part_intres(_m,1610,N);
		{  /* LetExpr */
			{  /* PatternCaseList */
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = PIR_l57;
					mxv_IR = mxv_anchor;
					if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp106;
					mxv_IR = mxs_fath(_c,0,mxv_anchor);
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp106;
					if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp106;
					if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp106;
					X_p332 = mxs_rbroth(_c,0,mxv_anchor);
					mxv_IR = X_p332;
					if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp106;
					mxv_i368 = X_p332;
					goto L368;
				}
				Lp106: ;
				{
					ELEMENT mxv_anchor, mxv_IR;
					mxv_anchor = PIR_l57;
					mxv_IR = mxv_anchor;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp107;
					mxv_IR = mxs_fath(_c,0,mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor)));
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp107;
					if( mxs_numsons(_c,0, mxv_IR ) < 2 ) goto Lp107;
					if( !mxs_is(_c,0,mxv_IR,_IfExpr_) ) goto Lp107;
					mxv_IR = mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor));
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp107;
					if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp107;
					if( mxs_numsons(_c,0, mxv_IR ) < 1 ) goto Lp107;
					mxv_IR = mxs_fath(_c,0,mxv_anchor);
					if( mxv_IR == mxs_nil(_c,0) ) goto Lp107;
					if( mxs_before(_c,0,mxv_IR) < mxs_before(_c,0,mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR))) ) goto Lp107;
					if( mxs_before(_c,0,mxs_son(_c,0,-1,mxs_fath(_c,0,mxv_IR))) < mxs_before(_c,0,mxv_IR) ) goto Lp107;
					if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp107;
					if( !mxs_is(_c,0,mxv_IR,_FormulaCase_) ) goto Lp107;
					X_p337 = mxs_rbroth(_c,0,mxs_fath(_c,0,mxs_fath(_c,0,mxv_anchor)));
					mxv_IR = X_p337;
					if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp107;
					mxv_i368 = X_p337;
					goto L368;
				}
				Lp107: ;
					mxv_i368 = PIR_l57;
				L368: ;
			}
			RCL_l58 = mxv_i368;
			{  /* LetExpr */
				{  /* PatternCaseList */
					{
						ELEMENT mxv_anchor, mxv_IR;
						mxv_anchor = RCL_l58;
						mxv_IR = mxv_anchor;
						if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp108;
						mxv_IR = mxs_fath(_c,0,mxv_anchor);
						if( mxv_IR == mxs_nil(_c,0) ) goto Lp108;
						if( mxs_numsons(_c,0, mxv_IR ) != 2 ) goto Lp108;
						if( !mxs_is(_c,0,mxv_IR,_Case_) ) goto Lp108;
						mxv_i369 = mxs_fath(_m,1617,mxs_fath(_m,1617,mxs_fath(_m,1617,RCL_l58)));
						goto L369;
					}
					Lp108: ;
						mxv_i369 = mxs_fath(_m,1618,RCL_l58);
					L369: ;
				}
				EIR_l59 = mxv_i369;
				{  /* LetExpr */
					{  /* PatternCaseList */
						{
							ELEMENT mxv_anchor, mxv_IR;
							mxv_anchor = PIR_l57;
							mxv_IR = mxv_anchor;
							if( mxv_IR != mxs_son(_c,0,2,mxs_fath(_c,0,mxv_IR)) ) goto Lp109;
							mxv_IR = mxs_fath(_c,0,mxv_anchor);
							if( mxv_IR == mxs_nil(_c,0) ) goto Lp109;
							if( mxs_numsons(_c,0, mxv_IR ) != 3 ) goto Lp109;
							if( !mxs_is(_c,0,mxv_IR,_LetExpr_) ) goto Lp109;
							V_p341 = mxs_lbroth(_c,0,mxv_anchor);
							mxv_IR = V_p341;
							if( mxv_IR != mxs_son(_c,0,1,mxs_fath(_c,0,mxv_IR)) ) goto Lp109;
							X_p343 = mxs_rbroth(_c,0,mxv_anchor);
							mxv_IR = X_p343;
							if( mxv_IR != mxs_son(_c,0,3,mxs_fath(_c,0,mxv_IR)) ) goto Lp109;
							mxv_i370 = mxs_before(_m,1620,V_p341);
							goto L370;
						}
						Lp109: ;
							mxv_i370 = mxs_before(_m,1621,N);
						L370: ;
					}
					LCP_l60 = mxv_i370;
					mxv_l60 = mxs_intres_union(_m,1623,mxs_aux_intres_left(_m,1624,N,mxs_itoe(_c,0,1),mxs_intresexprs(_m,1624,PIR_l57)),mxs_intres_collect(_m,1625,EIR_l59),mxs_aux_intres_right(_m,1626,LCP_l60,mxs_after(_m,1626,N),mxs_after(_m,1626,RCL_l58),mxs_lokvar_need(_m,1626,mxs_encl_fctoratt(_m,1626,EIR_l59)),mxs_itoe(_c,0,1)));
				}
				mxv_l59 = mxv_l60;
			}
			mxv_l58 = mxv_l59;
		}
		mxv_l57 = mxv_l58;
	}
		mxv_i365 = mxv_l57;
		L365: ;
	}
			mxv_i364 = mxv_i365;
		L364: ;
	}
	mxv_ax = mxs_index(_c,0,N,_IntResExpr_);
	mxa_intres_collect[ mxv_ax ] = mxv_i364;
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
			mxv_errstr =  mxi_string_conc(_m,306,1,mxs_atoe(_c,0,"***** ?? only allowed in dynamic functions\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_2( void ){
	ELEMENT  mxv_c7, ID_p7, mxv_c8, L_p8, mxv_c9, C_p9, mxv_c6, mxv_i14, mxv_i13, mxv_i12, mxv_i11, mxv_i10, mxv_i9, mxv_c0 = 1L;
	long mxv_cix6,mxv_cbd6;
	mxv_cbd6 = mxs_number(_c,0,_NodeSortId_);
	for(mxv_cix6=1;mxv_cix6<=mxv_cbd6;mxv_cix6++){
		mxv_c6 = mxs_element(_c,0,mxv_cix6,_NodeSortId_);
		if( mxs_numsons(_c,0,mxv_c6)!=3 ) continue;
		mxv_c9 = mxs_son(_c,0,-1,mxv_c6);
		mxv_c8 = mxs_lbroth(_c,0,mxv_c9);
		mxv_c7 = mxs_lbroth(_c,0,mxv_c8);
		C_p9 = mxv_c9;
		L_p8 = mxv_c8;
		ID_p7 = mxv_c7;
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,mxs_id(_m,326,ID_p7),mxs_atoe(_c,0,"Node")))) ){
			mxv_i9 = mxs_false(_m,0);
			goto L9;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,mxs_id(_m,326,ID_p7),mxs_atoe(_c,0,"Point")))) ){
			mxv_i11 = mxs_false(_m,0);
			goto L11;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,mxs_id(_m,327,ID_p7),mxs_atoe(_c,0,"Term")))) ){
			mxv_i13 = mxs_false(_m,0);
			goto L13;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_id(_m,327,ID_p7),mxs_atoe(_c,0,"nil"))) ){
			mxv_i14 = mxs_true(_m,0);
			goto L14;
		}
		mxv_i14 = mxs_false(_m,0);
		L14: ;
	}
		mxv_i13 = mxv_i14;
		L13: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i13) ){
			mxv_i12 = mxs_true(_m,0);
			goto L12;
		}
		mxv_i12 = mxs_false(_m,0);
		L12: ;
	}
		mxv_i11 = mxv_i12;
		L11: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i11) ){
			mxv_i10 = mxs_true(_m,0);
			goto L10;
		}
		mxv_i10 = mxs_false(_m,0);
		L10: ;
	}
		mxv_i9 = mxv_i10;
		L9: ;
	}
		if( !(  mxs_eq(_m,0,mxs_true(_m,0),mxv_i9) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,329,8,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,328,L_p8),mxs_atoe(_c,0,", column "),mxs_s(_m,328,C_p9),mxs_atoe(_c,0,": \""),mxs_id(_m,328,ID_p7),mxs_atoe(_c,0,"\" not allowed with\n"),mxs_atoe(_c,0,"       node symbol @ \n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_3( void ){
	ELEMENT  mxv_c11, ID_p11, mxv_c12, L_p12, mxv_c13, C_p13, mxv_c10, mxv_i15, mxv_c0 = 1L;
	long mxv_cix10,mxv_cbd10;
	mxv_cbd10 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix10=1;mxv_cix10<=mxv_cbd10;mxv_cix10++){
		mxv_c10 = mxs_element(_c,0,mxv_cix10,_UsedId_);
		if( mxs_numsons(_c,0,mxv_c10)!=3 ) continue;
		mxv_c13 = mxs_son(_c,0,-1,mxv_c10);
		mxv_c12 = mxs_lbroth(_c,0,mxv_c13);
		mxv_c11 = mxs_lbroth(_c,0,mxv_c12);
		C_p13 = mxv_c13;
		L_p12 = mxv_c12;
		ID_p11 = mxv_c11;
		if( !(  mxs_eq(_m,0,mxs_numsubterms(_m,336,mxs_idtodecls(_m,336,mxs_term(_m,336,ID_p11))),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
		{  /* FormulaCaseList */
			if( mxs_eq(_m,0,mxs_numsubterms(_m,337,mxs_idtodecls(_m,337,mxs_term(_m,337,ID_p11))),mxs_itoe(_c,0,0)) ){
				mxv_i15 = mxi_string_conc(_m,339,8,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,338,L_p12),mxs_atoe(_c,0,", column "),mxs_s(_m,338,C_p13),mxs_atoe(_c,0,":"),mxs_atoe(_c,0,"  identifier \""),mxs_id(_m,339,ID_p11),mxs_atoe(_c,0,"\" not declared\n"));
				goto L15;
			}
			mxv_i15 = mxs_atoe(_c,0,"");
			L15: ;
		}
			mxv_errstr =  mxv_i15;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_4( void ){
	ELEMENT  mxv_c15, ID_p15, mxv_c16, L_p16, mxv_c17, C_p17, mxv_c14, mxv_i16, mxv_c0 = 1L;
	long mxv_cix14,mxv_cbd14;
	mxv_cbd14 = mxs_number(_c,0,_DefId_);
	for(mxv_cix14=1;mxv_cix14<=mxv_cbd14;mxv_cix14++){
		mxv_c14 = mxs_element(_c,0,mxv_cix14,_DefId_);
		if( mxs_numsons(_c,0,mxv_c14)!=3 ) continue;
		mxv_c17 = mxs_son(_c,0,-1,mxv_c14);
		mxv_c16 = mxs_lbroth(_c,0,mxv_c17);
		mxv_c15 = mxs_lbroth(_c,0,mxv_c16);
		C_p17 = mxv_c17;
		L_p16 = mxv_c16;
		ID_p15 = mxv_c15;
		if( !(  mxs_eq(_m,0,mxs_numsubterms(_m,342,mxs_idtodecls(_m,342,mxs_term(_m,342,ID_p15))),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
		{  /* FormulaCaseList */
			if( ( ! mxs_eq(_m,0,mxs_numsubterms(_m,343,mxs_idtodecls(_m,343,mxs_term(_m,343,ID_p15))),mxs_itoe(_c,0,1))) ){
				mxv_i16 = mxi_string_conc(_m,345,8,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,344,L_p16),mxs_atoe(_c,0,", column "),mxs_s(_m,344,C_p17),mxs_atoe(_c,0,":"),mxs_atoe(_c,0,"  identifier \""),mxs_id(_m,345,ID_p15),mxs_atoe(_c,0,"\" multiple declared\n"));
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

static  long  mxc_5( void ){
	ELEMENT  mxv_c28, ID_p28, mxv_c29, L_p29, mxv_c30, C_p30, mxv_c27, mxv_c32, S_p32, mxv_c31, mxv_c26, mxv_c0 = 1L;
	long mxv_cix26,mxv_cbd26;
	mxv_cbd26 = mxs_number(_c,0,_ClassProd_);
	for(mxv_cix26=1;mxv_cix26<=mxv_cbd26;mxv_cix26++){
		mxv_c26 = mxs_element(_c,0,mxv_cix26,_ClassProd_);
		if( mxs_numsons(_c,0,mxv_c26)!=2 ) continue;
		mxv_c31 = mxs_son(_c,0,-1,mxv_c26);
		mxv_c27 = mxs_lbroth(_c,0,mxv_c31);
		if( mxs_numsons(_c,0,mxv_c31) < 1 ) continue;
		mxv_c32 = mxs_son(_c,0,1,mxv_c31);
		S_p32 = mxv_c32;
		if( mxs_numsons(_c,0,mxv_c27)!=3 ) continue;
		mxv_c30 = mxs_son(_c,0,-1,mxv_c27);
		mxv_c29 = mxs_lbroth(_c,0,mxv_c30);
		mxv_c28 = mxs_lbroth(_c,0,mxv_c29);
		C_p30 = mxv_c30;
		L_p29 = mxv_c29;
		ID_p28 = mxv_c28;
		if( !(  ( ! mxs_eq(_m,0,mxs_term_basesorts(_m,366,S_p32),mxs_nil(_m,366))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,367,7,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,367,L_p29),mxs_atoe(_c,0,", column "),mxs_s(_m,367,C_p30),mxs_atoe(_c,0,": class \""),mxs_id(_m,367,ID_p28),mxs_atoe(_c,0,"\" is circular\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_6( void ){
	ELEMENT  mxv_c42, ID_p42, mxv_c43, L_p43, mxv_c44, C_p44, mxv_c41, UID_p41, mxv_c0 = 1L;
	long mxv_cix41,mxv_cbd41;
	mxv_cbd41 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix41=1;mxv_cix41<=mxv_cbd41;mxv_cix41++){
		mxv_c41 = mxs_element(_c,0,mxv_cix41,_UsedId_);
		UID_p41 = mxv_c41;
		if( mxs_numsons(_c,0,mxv_c41)!=3 ) continue;
		mxv_c44 = mxs_son(_c,0,-1,mxv_c41);
		mxv_c43 = mxs_lbroth(_c,0,mxv_c44);
		mxv_c42 = mxs_lbroth(_c,0,mxv_c43);
		C_p44 = mxv_c44;
		L_p43 = mxv_c43;
		ID_p42 = mxv_c42;
		if( !(  ( ! mxs_is(_m,391,mxs_fath(_m,391,mxs_decl(_m,391,UID_p41)),_Declaration_)||mxs_in(_m,392,UID_p41,mxs_after(_m,392,mxs_fath(_m,392,mxs_decl(_m,392,UID_p41))),mxs_after(_m,392,mxs_root(_m,392)))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,395,12,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,393,L_p43),mxs_atoe(_c,0,", column "),mxs_s(_m,393,C_p44),mxs_atoe(_c,0,": \""),mxs_id(_m,393,ID_p42),mxs_atoe(_c,0,"\" used outside scope\n"),mxs_atoe(_c,0,"       declaration is line "),mxs_s(_m,394,mxs_son(_m,394,mxs_itoe(_c,0,2),mxs_decl(_m,394,UID_p41))),mxs_atoe(_c,0,", column "),mxs_s(_m,395,mxs_son(_m,395,mxs_itoe(_c,0,3),mxs_decl(_m,395,UID_p41))),mxs_atoe(_c,0,"\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_7( void ){
	ELEMENT  mxv_c46, ID_p46, mxv_c47, L_p47, mxv_c48, C_p48, mxv_c45, UID_p45, mxv_c0 = 1L;
	long mxv_cix45,mxv_cbd45;
	mxv_cbd45 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix45=1;mxv_cix45<=mxv_cbd45;mxv_cix45++){
		mxv_c45 = mxs_element(_c,0,mxv_cix45,_UsedId_);
		UID_p45 = mxv_c45;
		if( mxs_numsons(_c,0,mxv_c45)!=3 ) continue;
		mxv_c48 = mxs_son(_c,0,-1,mxv_c45);
		mxv_c47 = mxs_lbroth(_c,0,mxv_c48);
		mxv_c46 = mxs_lbroth(_c,0,mxv_c47);
		C_p48 = mxv_c48;
		L_p47 = mxv_c47;
		ID_p46 = mxv_c46;
		if( !(  ( ! mxs_is(_m,398,mxs_fath(_m,398,mxs_decl(_m,398,UID_p45)),_Definition_)||mxs_in(_m,399,UID_p45,mxs_before(_m,399,mxs_fath(_m,399,mxs_fath(_m,399,mxs_decl(_m,399,UID_p45)))),mxs_after(_m,399,mxs_root(_m,399)))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,402,12,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,400,L_p47),mxs_atoe(_c,0,", column "),mxs_s(_m,400,C_p48),mxs_atoe(_c,0,": \""),mxs_id(_m,400,ID_p46),mxs_atoe(_c,0,"\" used outside scope\n"),mxs_atoe(_c,0,"       declaration is line "),mxs_s(_m,401,mxs_son(_m,401,mxs_itoe(_c,0,2),mxs_decl(_m,401,UID_p45))),mxs_atoe(_c,0,", column "),mxs_s(_m,402,mxs_son(_m,402,mxs_itoe(_c,0,3),mxs_decl(_m,402,UID_p45))),mxs_atoe(_c,0,"\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_8( void ){
	ELEMENT  mxv_c50, ID_p50, mxv_c51, L_p51, mxv_c52, C_p52, mxv_c49, UID_p49, mxv_c0 = 1L;
	long mxv_cix49,mxv_cbd49;
	mxv_cbd49 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix49=1;mxv_cix49<=mxv_cbd49;mxv_cix49++){
		mxv_c49 = mxs_element(_c,0,mxv_cix49,_UsedId_);
		UID_p49 = mxv_c49;
		if( mxs_numsons(_c,0,mxv_c49)!=3 ) continue;
		mxv_c52 = mxs_son(_c,0,-1,mxv_c49);
		mxv_c51 = mxs_lbroth(_c,0,mxv_c52);
		mxv_c50 = mxs_lbroth(_c,0,mxv_c51);
		C_p52 = mxv_c52;
		L_p51 = mxv_c51;
		ID_p50 = mxv_c50;
		if( !(  ( ! mxs_is(_m,406,mxs_fath(_m,406,mxs_decl(_m,406,UID_p49)),_DynFunc_)||mxs_in(_m,407,UID_p49,mxs_after(_m,407,mxs_fath(_m,407,mxs_fath(_m,407,mxs_fath(_m,407,mxs_decl(_m,407,UID_p49))))),mxs_after(_m,407,mxs_root(_m,407)))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,410,12,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,408,L_p51),mxs_atoe(_c,0,", column "),mxs_s(_m,408,C_p52),mxs_atoe(_c,0,": \""),mxs_id(_m,408,ID_p50),mxs_atoe(_c,0,"\" used outside scope\n"),mxs_atoe(_c,0,"       declaration is line "),mxs_s(_m,409,mxs_son(_m,409,mxs_itoe(_c,0,2),mxs_decl(_m,409,UID_p49))),mxs_atoe(_c,0,", column "),mxs_s(_m,410,mxs_son(_m,410,mxs_itoe(_c,0,3),mxs_decl(_m,410,UID_p49))),mxs_atoe(_c,0,"\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_9( void ){
	ELEMENT  mxv_c54, ID_p54, mxv_c55, L_p55, mxv_c56, C_p56, mxv_c53, UID_p53, mxv_c0 = 1L;
	long mxv_cix53,mxv_cbd53;
	mxv_cbd53 = mxs_number(_c,0,_UsedId_);
	for(mxv_cix53=1;mxv_cix53<=mxv_cbd53;mxv_cix53++){
		mxv_c53 = mxs_element(_c,0,mxv_cix53,_UsedId_);
		UID_p53 = mxv_c53;
		if( mxs_numsons(_c,0,mxv_c53)!=3 ) continue;
		mxv_c56 = mxs_son(_c,0,-1,mxv_c53);
		mxv_c55 = mxs_lbroth(_c,0,mxv_c56);
		mxv_c54 = mxs_lbroth(_c,0,mxv_c55);
		C_p56 = mxv_c56;
		L_p55 = mxv_c55;
		ID_p54 = mxv_c54;
		if( !(  ( ! mxs_is(_m,412,mxs_fath(_m,412,mxs_decl(_m,412,UID_p53)),_DynSemInput_)||mxs_in(_m,413,UID_p53,mxs_after(_m,413,mxs_fath(_m,413,mxs_fath(_m,413,mxs_fath(_m,413,mxs_decl(_m,413,UID_p53))))),mxs_after(_m,413,mxs_root(_m,413)))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,416,12,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,414,L_p55),mxs_atoe(_c,0,", column "),mxs_s(_m,414,C_p56),mxs_atoe(_c,0,": \""),mxs_id(_m,414,ID_p54),mxs_atoe(_c,0,"\" used outside scope\n"),mxs_atoe(_c,0,"       declaration is line "),mxs_s(_m,415,mxs_son(_m,415,mxs_itoe(_c,0,2),mxs_decl(_m,415,UID_p53))),mxs_atoe(_c,0,", column "),mxs_s(_m,416,mxs_son(_m,416,mxs_itoe(_c,0,3),mxs_decl(_m,416,UID_p53))),mxs_atoe(_c,0,"\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_10( void ){
	ELEMENT  mxv_c60, PID1_p60, mxv_c61, L1_p61, mxv_c62, C1_p62, mxv_c59, mxv_c64, PID2_p64, mxv_c65, L2_p65, mxv_c66, C2_p66, mxv_c63, mxv_c58, mxv_c57, mxv_c0 = 1L;
	long mxv_cix57,mxv_cbd57;
	mxv_cbd57 = mxs_number(_c,0,_ApplyEntity_);
	for(mxv_cix57=1;mxv_cix57<=mxv_cbd57;mxv_cix57++){
		mxv_c57 = mxs_element(_c,0,mxv_cix57,_ApplyEntity_);
		if( mxs_numsons(_c,0,mxv_c57) < 3 ) continue;
		mxv_c58 = mxs_son(_c,0,3,mxv_c57);
		if( mxs_numsons(_c,0,mxv_c58) < 2 ) continue;
		mxv_c59 = mxs_son(_c,0,1,mxv_c58);
		mxv_c63 = mxs_rbroth(_c,0,mxv_c59);
		do {
			do {
				if( mxs_numsons(_c,0,mxv_c63)!=3 ) goto CL22;
				mxv_c66 = mxs_son(_c,0,-1,mxv_c63);
				mxv_c65 = mxs_lbroth(_c,0,mxv_c66);
				mxv_c64 = mxs_lbroth(_c,0,mxv_c65);
				C2_p66 = mxv_c66;
				L2_p65 = mxv_c65;
				PID2_p64 = mxv_c64;
				if( mxs_numsons(_c,0,mxv_c59)!=3 ) goto CL22;
				mxv_c62 = mxs_son(_c,0,-1,mxv_c59);
				mxv_c61 = mxs_lbroth(_c,0,mxv_c62);
				mxv_c60 = mxs_lbroth(_c,0,mxv_c61);
				C1_p62 = mxv_c62;
				L1_p61 = mxv_c61;
				PID1_p60 = mxv_c60;
				if( !(  ( ! mxs_eq(_m,0,mxs_term(_m,420,PID1_p60),mxs_term(_m,420,PID2_p64))) )  ){
					mxv_c0 = 0L;
					mxv_errstr =  mxi_string_conc(_m,422,10,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,421,L1_p61),mxs_atoe(_c,0,"/"),mxs_s(_m,421,L2_p65),mxs_atoe(_c,0,", column "),mxs_s(_m,421,C1_p62),mxs_atoe(_c,0,"/"),mxs_s(_m,421,C2_p66),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"parameters have same identifier\n"));
					fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
				}
				CL22: ;
				mxv_c63 = mxs_rbroth(_c,0,mxv_c63);
			} while( mxv_c63 != mxs_nil(_c,0) );
			mxv_c59 = mxs_rbroth(_c,0,mxv_c59);
			mxv_c63 = mxs_rbroth(_c,0,mxv_c59);
		} while( mxv_c63 != mxs_nil(_c,0) );
	}

	return mxv_c0;
}

static  long  mxc_11( void ){
	ELEMENT  mxv_c69, L_p69, mxv_c70, C_p70, mxv_c68, mxv_c71, PARAML_p71, mxv_c67, mxv_c0 = 1L;
	long mxv_cix67,mxv_cbd67;
	mxv_cbd67 = mxs_number(_c,0,_AttrDecl_);
	for(mxv_cix67=1;mxv_cix67<=mxv_cbd67;mxv_cix67++){
		mxv_c67 = mxs_element(_c,0,mxv_cix67,_AttrDecl_);
		if( mxs_numsons(_c,0,mxv_c67) < 2 ) continue;
		mxv_c68 = mxs_son(_c,0,1,mxv_c67);
		mxv_c71 = mxs_rbroth(_c,0,mxv_c68);
		PARAML_p71 = mxv_c71;
		if( mxs_numsons(_c,0,mxv_c68)!=3 ) continue;
		mxv_c70 = mxs_son(_c,0,-1,mxv_c68);
		mxv_c69 = mxs_lbroth(_c,0,mxv_c70);
		C_p70 = mxv_c70;
		L_p69 = mxv_c69;
		if( !(  mxs_eq(_m,0,mxs_numsons(_m,425,PARAML_p71),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,426,5,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,426,L_p69),mxs_atoe(_c,0,", column "),mxs_s(_m,426,C_p70),mxs_atoe(_c,0,":  attribute must have arity 1\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_12( void ){
	ELEMENT  mxv_c74, L_p74, mxv_c75, C_p75, mxv_c73, mxv_c76, PARAML_p76, mxv_c72, mxv_c0 = 1L;
	long mxv_cix72,mxv_cbd72;
	mxv_cbd72 = mxs_number(_c,0,_Attribute_);
	for(mxv_cix72=1;mxv_cix72<=mxv_cbd72;mxv_cix72++){
		mxv_c72 = mxs_element(_c,0,mxv_cix72,_Attribute_);
		if( mxs_numsons(_c,0,mxv_c72) < 2 ) continue;
		mxv_c73 = mxs_son(_c,0,1,mxv_c72);
		mxv_c76 = mxs_rbroth(_c,0,mxv_c73);
		PARAML_p76 = mxv_c76;
		if( mxs_numsons(_c,0,mxv_c73)!=3 ) continue;
		mxv_c75 = mxs_son(_c,0,-1,mxv_c73);
		mxv_c74 = mxs_lbroth(_c,0,mxv_c75);
		C_p75 = mxv_c75;
		L_p74 = mxv_c74;
		if( !(  mxs_eq(_m,0,mxs_numsons(_m,429,PARAML_p76),mxs_itoe(_c,0,1)) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,430,5,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,430,L_p74),mxs_atoe(_c,0,", column "),mxs_s(_m,430,C_p75),mxs_atoe(_c,0,":  attribute must have arity 1\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_13( void ){
	ELEMENT  mxv_c80, ID_p80, mxv_c81, L_p81, mxv_c82, C_p82, mxv_c79, mxv_c78, mxv_c77, mxv_i41, mxv_i40, mxv_i39, mxv_i38, mxv_c0 = 1L;
	long mxv_cix77,mxv_cbd77;
	mxv_cbd77 = mxs_number(_c,0,_Attribute_);
	for(mxv_cix77=1;mxv_cix77<=mxv_cbd77;mxv_cix77++){
		mxv_c77 = mxs_element(_c,0,mxv_cix77,_Attribute_);
		if( mxs_numsons(_c,0,mxv_c77) < 2 ) continue;
		mxv_c78 = mxs_son(_c,0,2,mxv_c77);
		if( mxs_numsons(_c,0,mxv_c78)!=1 ) continue;
		mxv_c79 = mxs_son(_c,0,-1,mxv_c78);
		if( !mxs_is(_c,0,mxv_c79,_TermSortId_) ) continue;
		if( mxs_numsons(_c,0,mxv_c79)!=3 ) continue;
		mxv_c82 = mxs_son(_c,0,-1,mxv_c79);
		mxv_c81 = mxs_lbroth(_c,0,mxv_c82);
		mxv_c80 = mxs_lbroth(_c,0,mxv_c81);
		C_p82 = mxv_c82;
		L_p81 = mxv_c81;
		ID_p80 = mxv_c80;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,440,ID_p80),mxs_atoe(_c,0,"Node")) ){
			mxv_i38 = mxs_true(_m,0);
			goto L38;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,440,ID_p80),mxs_atoe(_c,0,"Point")) ){
			mxv_i40 = mxs_true(_m,0);
			goto L40;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,440,ID_p80),mxs_atoe(_c,0,"Ident")) ){
			mxv_i41 = mxs_true(_m,0);
			goto L41;
		}
		mxv_i41 = mxs_false(_m,0);
		L41: ;
	}
		mxv_i40 = mxv_i41;
		L40: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i40) ){
			mxv_i39 = mxs_true(_m,0);
			goto L39;
		}
		mxv_i39 = mxs_false(_m,0);
		L39: ;
	}
		mxv_i38 = mxv_i39;
		L38: ;
	}
		if( !(  mxs_eq(_m,0,mxs_true(_m,0),mxv_i38) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,441,5,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,441,L_p81),mxs_atoe(_c,0,", column "),mxs_s(_m,441,C_p82),mxs_atoe(_c,0,":  attribute sort not enumerable\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_14( void ){
	ELEMENT  mxv_c85, ID_p85, mxv_c86, L_p86, mxv_c87, C_p87, mxv_c84, FID_p84, mxv_c88, EXPL_p88, mxv_c83, mxv_i47, mxv_i46, mxv_i45, mxv_i44, mxv_i43, mxv_i42, mxv_c0 = 1L;
	long mxv_cix83,mxv_cbd83;
	mxv_cbd83 = mxs_number(_c,0,_FuncAppl_);
	for(mxv_cix83=1;mxv_cix83<=mxv_cbd83;mxv_cix83++){
		mxv_c83 = mxs_element(_c,0,mxv_cix83,_FuncAppl_);
		if( mxs_numsons(_c,0,mxv_c83)!=2 ) continue;
		mxv_c88 = mxs_son(_c,0,-1,mxv_c83);
		mxv_c84 = mxs_lbroth(_c,0,mxv_c88);
		EXPL_p88 = mxv_c88;
		FID_p84 = mxv_c84;
		if( mxs_numsons(_c,0,mxv_c84)!=3 ) continue;
		mxv_c87 = mxs_son(_c,0,-1,mxv_c84);
		mxv_c86 = mxs_lbroth(_c,0,mxv_c87);
		mxv_c85 = mxs_lbroth(_c,0,mxv_c86);
		C_p87 = mxv_c87;
		L_p86 = mxv_c86;
		ID_p85 = mxv_c85;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_numsons(_m,444,EXPL_p88),mxs_numsons(_m,444,mxs_rbroth(_m,444,mxs_decl(_m,444,FID_p84)))) ){
			mxv_i42 = mxs_true(_m,0);
			goto L42;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( ( ! mxs_eq(_m,0,mxs_numsons(_m,445,EXPL_p88),mxs_itoe(_c,0,0))) ){
			mxv_i44 = mxs_false(_m,0);
			goto L44;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_is(_m,446,mxs_fath(_m,446,mxs_decl(_m,446,FID_p84)),_ListProd_) ){
			mxv_i46 = mxs_true(_m,0);
			goto L46;
		}
	{  /* FormulaCaseList */
		if( mxs_is(_m,447,mxs_fath(_m,447,mxs_decl(_m,447,FID_p84)),_PredeclProd_) ){
			mxv_i47 = mxs_true(_m,0);
			goto L47;
		}
		mxv_i47 = mxs_false(_m,0);
		L47: ;
	}
		mxv_i46 = mxv_i47;
		L46: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i46) ){
			mxv_i45 = mxs_true(_m,0);
			goto L45;
		}
		mxv_i45 = mxs_false(_m,0);
		L45: ;
	}
		mxv_i44 = mxv_i45;
		L44: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i44) ){
			mxv_i43 = mxs_true(_m,0);
			goto L43;
		}
		mxv_i43 = mxs_false(_m,0);
		L43: ;
	}
		mxv_i42 = mxv_i43;
		L42: ;
	}
		if( !(  mxs_eq(_m,0,mxs_true(_m,0),mxv_i42) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,448,7,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,448,L_p86),mxs_atoe(_c,0,", column "),mxs_s(_m,448,C_p87),mxs_atoe(_c,0,": function \""),mxs_id(_m,448,ID_p85),mxs_atoe(_c,0,"\" used with wrong number of params\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_15( void ){
	ELEMENT  mxv_c117, ID_p117, mxv_c118, L_p118, mxv_c119, C_p119, mxv_c116, N_p116, mxv_c115, mxv_i60, mxv_i59, mxv_l8, M_l8, mxv_c0 = 1L;
	long mxv_cix115,mxv_cbd115;
	mxv_cbd115 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix115=1;mxv_cix115<=mxv_cbd115;mxv_cix115++){
		mxv_c115 = mxs_element(_c,0,mxv_cix115,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c115)!=3 ) continue;
		mxv_c116 = mxs_son(_c,0,-1,mxv_c115);
		if( !mxs_is(_c,0,mxv_c116,_Name_) ) continue;
		N_p116 = mxv_c116;
		if( mxs_numsons(_c,0,mxv_c116)!=3 ) continue;
		mxv_c119 = mxs_son(_c,0,-1,mxv_c116);
		mxv_c118 = mxs_lbroth(_c,0,mxv_c119);
		mxv_c117 = mxs_lbroth(_c,0,mxv_c118);
		C_p119 = mxv_c119;
		L_p118 = mxv_c118;
		ID_p117 = mxv_c117;
	{  /* FormulaCaseList */
		if( ( ! mxs_is(_m,505,mxs_scope(_m,505,N_p116),_Condition_)) ){
			mxv_i59 = mxs_false(_m,0);
			goto L59;
		}
	{  /* FormulaCaseList */
		if( mxs_desc(_m,505,N_p116,mxs_son(_m,505,mxs_itoe(_c,0,1),mxs_scope(_m,505,N_p116))) ){
			mxv_i60 = mxs_true(_m,0);
			goto L60;
		}
		mxv_i60 = mxs_false(_m,0);
		L60: ;
	}
		mxv_i59 = mxv_i60;
		L59: ;
	}
		if( !(  ( ! mxs_eq(_m,0,mxs_true(_m,0),mxv_i59)||mxs_eq(_m,0,mxs_lookup_cond(_m,506,mxs_term(_m,506,ID_p117),mxs_son(_m,506,mxs_itoe(_c,0,1),mxs_son(_m,506,mxs_itoe(_c,0,1),mxs_scope(_m,506,N_p116)))),N_p116)) )  ){
			mxv_c0 = 0L;
		{  /* LetExpr */
			M_l8 = mxs_lookup_cond(_m,507,mxs_term(_m,507,ID_p117),mxs_son(_m,507,mxs_itoe(_c,0,1),mxs_son(_m,507,mxs_itoe(_c,0,1),mxs_scope(_m,507,N_p116))));
			mxv_l8 = mxi_string_conc(_m,509,12,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,508,L_p118),mxs_atoe(_c,0,"/"),mxs_s(_m,508,mxs_son(_m,508,mxs_itoe(_c,0,2),M_l8)),mxs_atoe(_c,0,", column "),mxs_s(_m,508,C_p119),mxs_atoe(_c,0,"/"),mxs_s(_m,508,mxs_son(_m,508,mxs_itoe(_c,0,3),M_l8)),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"multiple binding of identifier \""),mxs_id(_m,509,ID_p117),mxs_atoe(_c,0,"\"\n"));
		}
			mxv_errstr =  mxv_l8;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_16( void ){
	ELEMENT  mxv_c122, ID_p122, mxv_c123, L_p123, mxv_c124, C_p124, mxv_c121, N_p121, mxv_c120, mxv_l9, M_l9, mxv_c0 = 1L;
	long mxv_cix120,mxv_cbd120;
	mxv_cbd120 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix120=1;mxv_cix120<=mxv_cbd120;mxv_cix120++){
		mxv_c120 = mxs_element(_c,0,mxv_cix120,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c120)!=3 ) continue;
		mxv_c121 = mxs_son(_c,0,-1,mxv_c120);
		if( !mxs_is(_c,0,mxv_c121,_Name_) ) continue;
		N_p121 = mxv_c121;
		if( mxs_numsons(_c,0,mxv_c121)!=3 ) continue;
		mxv_c124 = mxs_son(_c,0,-1,mxv_c121);
		mxv_c123 = mxs_lbroth(_c,0,mxv_c124);
		mxv_c122 = mxs_lbroth(_c,0,mxv_c123);
		C_p124 = mxv_c124;
		L_p123 = mxv_c123;
		ID_p122 = mxv_c122;
		if( !(  ( ! mxs_is(_m,513,mxs_scope(_m,513,N_p121),_PatternCase_)||mxs_eq(_m,0,mxs_lookup_item(_m,514,mxs_term(_m,514,ID_p122),mxs_son(_m,514,mxs_itoe(_c,0,1),mxs_scope(_m,514,N_p121))),N_p121)) )  ){
			mxv_c0 = 0L;
		{  /* LetExpr */
			M_l9 = mxs_lookup_item(_m,515,mxs_term(_m,515,ID_p122),mxs_son(_m,515,mxs_itoe(_c,0,1),mxs_scope(_m,515,N_p121)));
			mxv_l9 = mxi_string_conc(_m,517,12,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,516,L_p123),mxs_atoe(_c,0,"/"),mxs_s(_m,516,mxs_son(_m,516,mxs_itoe(_c,0,2),M_l9)),mxs_atoe(_c,0,", column "),mxs_s(_m,516,C_p124),mxs_atoe(_c,0,"/"),mxs_s(_m,516,mxs_son(_m,516,mxs_itoe(_c,0,3),M_l9)),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"multiple binding of identifier \""),mxs_id(_m,517,ID_p122),mxs_atoe(_c,0,"\"\n"));
		}
			mxv_errstr =  mxv_l9;
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_17( void ){
	ELEMENT  mxv_c126, ID_p126, mxv_c127, L_p127, mxv_c128, C_p128, mxv_c125, N_p125, mxv_c0 = 1L;
	long mxv_cix125,mxv_cbd125;
	mxv_cbd125 = mxs_number(_c,0,_Name_);
	for(mxv_cix125=1;mxv_cix125<=mxv_cbd125;mxv_cix125++){
		mxv_c125 = mxs_element(_c,0,mxv_cix125,_Name_);
		N_p125 = mxv_c125;
		if( mxs_numsons(_c,0,mxv_c125)!=3 ) continue;
		mxv_c128 = mxs_son(_c,0,-1,mxv_c125);
		mxv_c127 = mxs_lbroth(_c,0,mxv_c128);
		mxv_c126 = mxs_lbroth(_c,0,mxv_c127);
		C_p128 = mxv_c128;
		L_p127 = mxv_c127;
		ID_p126 = mxv_c126;
		if( !(  ( ! mxs_eq(_m,0,mxs_bind_pos(_m,531,N_p125),mxs_nil(_m,531))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,532,7,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,532,L_p127),mxs_atoe(_c,0,", column "),mxs_s(_m,532,C_p128),mxs_atoe(_c,0,": \""),mxs_id(_m,532,ID_p126),mxs_atoe(_c,0,"\" not declared\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_18( void ){
	ELEMENT  mxv_c132, L_p132, mxv_c131, mxv_c130, mxv_c129, mxv_c0 = 1L;
	long mxv_cix129,mxv_cbd129;
	mxv_cbd129 = mxs_number(_c,0,_PatternList_);
	for(mxv_cix129=1;mxv_cix129<=mxv_cbd129;mxv_cix129++){
		mxv_c129 = mxs_element(_c,0,mxv_cix129,_PatternList_);
		if( mxs_numsons(_c,0,mxv_c129) < 1 ) continue;
		mxv_c130 = mxs_son(_c,0,1,mxv_c129);
		do {
			if( mxs_numsons(_c,0,mxv_c130)!=3 ) goto CL52;
			mxv_c131 = mxs_son(_c,0,-3,mxv_c130);
			if( !mxs_is(_c,0,mxv_c131,_Blank_) ) goto CL52;
			if( mxs_numsons(_c,0,mxv_c131)!=1 ) goto CL52;
			mxv_c132 = mxs_son(_c,0,-1,mxv_c131);
			L_p132 = mxv_c132;
			if( !(  mxs_eq(_m,0,mxs_true(_m,549),mxs_false(_m,549)) )  ){
				mxv_c0 = 0L;
				mxv_errstr =  mxi_string_conc(_m,550,3,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,550,L_p132),mxs_atoe(_c,0,": outermost pattern may not be omitted\n"));
				fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
			}
			CL52: ;
			mxv_c130 = mxs_rbroth(_c,0,mxv_c130);
		} while( mxv_c130 != mxs_nil(_c,0) );
	}

	return mxv_c0;
}

static  long  mxc_19( void ){
	ELEMENT  mxv_c135, ID_p135, mxv_c136, L_p136, mxv_c137, C_p137, mxv_c134, mxv_c133, mxv_i77, mxv_i76, mxv_i75, mxv_i74, mxv_c0 = 1L;
	long mxv_cix133,mxv_cbd133;
	mxv_cbd133 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix133=1;mxv_cix133<=mxv_cbd133;mxv_cix133++){
		mxv_c133 = mxs_element(_c,0,mxv_cix133,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c133)!=3 ) continue;
		mxv_c134 = mxs_son(_c,0,-3,mxv_c133);
		if( !mxs_is(_c,0,mxv_c134,_TermSortId_) ) continue;
		if( mxs_numsons(_c,0,mxv_c134)!=3 ) continue;
		mxv_c137 = mxs_son(_c,0,-1,mxv_c134);
		mxv_c136 = mxs_lbroth(_c,0,mxv_c137);
		mxv_c135 = mxs_lbroth(_c,0,mxv_c136);
		C_p137 = mxv_c137;
		L_p136 = mxv_c136;
		ID_p135 = mxv_c135;
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,554,ID_p135),mxs_atoe(_c,0,"Node")) ){
			mxv_i74 = mxs_true(_m,0);
			goto L74;
		}
	{  /* FormulaCaseList */
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,554,ID_p135),mxs_atoe(_c,0,"Point")) ){
			mxv_i76 = mxs_true(_m,0);
			goto L76;
		}
	{  /* FormulaCaseList */
		if( mxs_eq(_m,0,mxs_id(_m,554,ID_p135),mxs_atoe(_c,0,"Ident")) ){
			mxv_i77 = mxs_true(_m,0);
			goto L77;
		}
		mxv_i77 = mxs_false(_m,0);
		L77: ;
	}
		mxv_i76 = mxv_i77;
		L76: ;
	}
		if( mxs_eq(_m,0,mxs_true(_m,0),mxv_i76) ){
			mxv_i75 = mxs_true(_m,0);
			goto L75;
		}
		mxv_i75 = mxs_false(_m,0);
		L75: ;
	}
		mxv_i74 = mxv_i75;
		L74: ;
	}
		if( !(  mxs_eq(_m,0,mxs_true(_m,0),mxv_i74) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,555,5,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,555,L_p136),mxs_atoe(_c,0,", column "),mxs_s(_m,555,C_p137),mxs_atoe(_c,0,":  pattern sort must be enumerable\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_20( void ){
	ELEMENT  mxv_c140, ID_p140, mxv_c141, L_p141, mxv_c142, C_p142, mxv_c139, mxv_c143, mxv_c138, mxv_c0 = 1L;
	long mxv_cix138,mxv_cbd138;
	mxv_cbd138 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix138=1;mxv_cix138<=mxv_cbd138;mxv_cix138++){
		mxv_c138 = mxs_element(_c,0,mxv_cix138,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c138)!=3 ) continue;
		mxv_c143 = mxs_son(_c,0,-2,mxv_c138);
		mxv_c139 = mxs_lbroth(_c,0,mxv_c143);
		if( !mxs_is(_c,0,mxv_c143,_ItemList_) ) continue;
		if( !mxs_is(_c,0,mxv_c139,_TermSortId_) ) continue;
		if( mxs_numsons(_c,0,mxv_c139)!=3 ) continue;
		mxv_c142 = mxs_son(_c,0,-1,mxv_c139);
		mxv_c141 = mxs_lbroth(_c,0,mxv_c142);
		mxv_c140 = mxs_lbroth(_c,0,mxv_c141);
		C_p142 = mxv_c142;
		L_p141 = mxv_c141;
		ID_p140 = mxv_c140;
		if( !(  mxs_eq(_m,0,mxs_id(_m,558,ID_p140),mxs_atoe(_c,0,"Node")) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,560,6,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,559,L_p141),mxs_atoe(_c,0,", column "),mxs_s(_m,559,C_p142),mxs_atoe(_c,0,":  no subpattern for ident and point "),mxs_atoe(_c,0,"allowed\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_21( void ){
	ELEMENT  mxv_c146, ID_p146, mxv_c147, L_p147, mxv_c148, C_p148, mxv_c145, UID_p145, mxv_c149, ITL_p149, mxv_c144, mxv_i79, mxv_i78, mxv_c0 = 1L;
	long mxv_cix144,mxv_cbd144;
	mxv_cbd144 = mxs_number(_c,0,_Pattern_);
	for(mxv_cix144=1;mxv_cix144<=mxv_cbd144;mxv_cix144++){
		mxv_c144 = mxs_element(_c,0,mxv_cix144,_Pattern_);
		if( mxs_numsons(_c,0,mxv_c144)!=3 ) continue;
		mxv_c149 = mxs_son(_c,0,-2,mxv_c144);
		mxv_c145 = mxs_lbroth(_c,0,mxv_c149);
		if( !mxs_is(_c,0,mxv_c149,_ItemList_) ) continue;
		ITL_p149 = mxv_c149;
		if( !mxs_is(_c,0,mxv_c145,_NodeSortId_) ) continue;
		UID_p145 = mxv_c145;
		if( mxs_numsons(_c,0,mxv_c145)!=3 ) continue;
		mxv_c148 = mxs_son(_c,0,-1,mxv_c145);
		mxv_c147 = mxs_lbroth(_c,0,mxv_c148);
		mxv_c146 = mxs_lbroth(_c,0,mxv_c147);
		C_p148 = mxv_c148;
		L_p147 = mxv_c147;
		ID_p146 = mxv_c146;
	{  /* FormulaCaseList */
		if( ( ! ( ! mxs_eq(_m,0,mxs_numberofastrks(_m,566,ITL_p149),mxs_itoe(_c,0,0))||mxs_eq(_m,0,mxs_numsons(_m,567,mxs_son(_m,567,mxs_itoe(_c,0,2),mxs_fath(_m,567,mxs_decl(_m,567,UID_p145)))),mxs_numsons(_m,567,ITL_p149)))) ){
			mxv_i78 = mxs_false(_m,0);
			goto L78;
		}
	{  /* FormulaCaseList */
		if( ( ! mxs_lt(_m,568,mxs_itoe(_c,0,0),mxs_numberofastrks(_m,568,ITL_p149))||mxs_le(_m,569,mxs_sub(_m,569,mxs_numsons(_m,569,ITL_p149),mxs_numberofastrks(_m,569,ITL_p149)),mxs_numsons(_m,570,mxs_son(_m,570,mxs_itoe(_c,0,2),mxs_fath(_m,570,mxs_decl(_m,570,UID_p145)))))) ){
			mxv_i79 = mxs_true(_m,0);
			goto L79;
		}
		mxv_i79 = mxs_false(_m,0);
		L79: ;
	}
		mxv_i78 = mxv_i79;
		L78: ;
	}
		if( !(  ( ! mxs_is(_m,564,mxs_fath(_m,564,mxs_decl(_m,564,UID_p145)),_TupelProd_)||mxs_eq(_m,0,mxs_true(_m,0),mxv_i78)) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,573,6,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,572,L_p147),mxs_atoe(_c,0,", column "),mxs_s(_m,572,C_p148),mxs_atoe(_c,0,":  pattern for tupel node sort never "),mxs_atoe(_c,0,"matches\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_22( void ){
	ELEMENT  mxv_c151, A1_p151, mxv_c152, A2_p152, mxv_c150, ITL_p150, mxv_c0 = 1L;
	long mxv_cix150,mxv_cbd150;
	mxv_cbd150 = mxs_number(_c,0,_ItemList_);
	for(mxv_cix150=1;mxv_cix150<=mxv_cbd150;mxv_cix150++){
		mxv_c150 = mxs_element(_c,0,mxv_cix150,_ItemList_);
		ITL_p150 = mxv_c150;
		if( mxs_numsons(_c,0,mxv_c150) < 2 ) continue;
		mxv_c151 = mxs_son(_c,0,1,mxv_c150);
		mxv_c152 = mxs_rbroth(_c,0,mxv_c151);
		do {
			do {
				if( !mxs_is(_c,0,mxv_c152,_Asterisk_) ) goto CL61;
				A2_p152 = mxv_c152;
				if( !mxs_is(_c,0,mxv_c151,_Asterisk_) ) goto CL61;
				A1_p151 = mxv_c151;
				if( !(  mxs_ex_pattern_inbetween(_m,577,mxs_rbroth(_m,577,A1_p151),A2_p152) )  ){
					mxv_c0 = 0L;
					mxv_errstr =  mxi_string_conc(_m,579,4,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,578,mxs_patlineno(_m,578,mxs_fath(_m,578,ITL_p150))),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"two asterisks must enclose a pattern\n"));
					fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
				}
				CL61: ;
				mxv_c152 = mxs_rbroth(_c,0,mxv_c152);
			} while( mxv_c152 != mxs_nil(_c,0) );
			mxv_c151 = mxs_rbroth(_c,0,mxv_c151);
			mxv_c152 = mxs_rbroth(_c,0,mxv_c151);
		} while( mxv_c152 != mxs_nil(_c,0) );
	}

	return mxv_c0;
}

static  long  mxc_23( void ){
	ELEMENT  mxv_c188, PC_p188, mxv_c0 = 1L;
	long mxv_cix188,mxv_cbd188;
	mxv_cbd188 = mxs_number(_c,0,_PatternCase_);
	for(mxv_cix188=1;mxv_cix188<=mxv_cbd188;mxv_cix188++){
		mxv_c188 = mxs_element(_c,0,mxv_cix188,_PatternCase_);
		PC_p188 = mxv_c188;
		if( !(  ( ! mxs_eq(_m,0,mxs_pat_anchor(_m,818,PC_p188),mxs_nil(_m,818))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,820,4,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,819,mxs_patlineno(_m,819,mxs_son(_m,819,mxs_itoe(_c,0,1),PC_p188))),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"ambigous pattern\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_24( void ){
	ELEMENT  mxv_c191, L_p191, mxv_c192, C_p192, mxv_c190, ID_p190, mxv_c193, EL_p193, mxv_c189, mxv_c0 = 1L;
	long mxv_cix189,mxv_cbd189;
	mxv_cbd189 = mxs_number(_c,0,_FuncAppl_);
	for(mxv_cix189=1;mxv_cix189<=mxv_cbd189;mxv_cix189++){
		mxv_c189 = mxs_element(_c,0,mxv_cix189,_FuncAppl_);
		if( mxs_numsons(_c,0,mxv_c189)!=2 ) continue;
		mxv_c193 = mxs_son(_c,0,-1,mxv_c189);
		mxv_c190 = mxs_lbroth(_c,0,mxv_c193);
		EL_p193 = mxv_c193;
		ID_p190 = mxv_c190;
		if( mxs_numsons(_c,0,mxv_c190)!=3 ) continue;
		mxv_c192 = mxs_son(_c,0,-1,mxv_c190);
		mxv_c191 = mxs_lbroth(_c,0,mxv_c192);
		C_p192 = mxv_c192;
		L_p191 = mxv_c191;
		if( !(  ( ! mxs_is(_m,830,mxs_fath(_m,830,mxs_decl(_m,830,ID_p190)),_FctOrAttDecl_)||mxs_eq(_m,0,mxs_numsons(_m,831,EL_p193),mxs_numsons(_m,831,mxs_rbroth(_m,831,mxs_decl(_m,831,ID_p190))))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,833,6,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,832,L_p191),mxs_atoe(_c,0,", column "),mxs_s(_m,832,C_p192),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"number of formal params doesn't match number of actual params\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_25( void ){
	ELEMENT  mxv_c196, L_p196, mxv_c197, C_p197, mxv_c195, ID_p195, mxv_c198, EL_p198, mxv_c194, mxv_i125, mxv_i124, mxv_c0 = 1L;
	long mxv_cix194,mxv_cbd194;
	mxv_cbd194 = mxs_number(_c,0,_PredAppl_);
	for(mxv_cix194=1;mxv_cix194<=mxv_cbd194;mxv_cix194++){
		mxv_c194 = mxs_element(_c,0,mxv_cix194,_PredAppl_);
		if( mxs_numsons(_c,0,mxv_c194)!=2 ) continue;
		mxv_c198 = mxs_son(_c,0,-1,mxv_c194);
		mxv_c195 = mxs_lbroth(_c,0,mxv_c198);
		EL_p198 = mxv_c198;
		ID_p195 = mxv_c195;
		if( mxs_numsons(_c,0,mxv_c195)!=3 ) continue;
		mxv_c197 = mxs_son(_c,0,-1,mxv_c195);
		mxv_c196 = mxs_lbroth(_c,0,mxv_c197);
		C_p197 = mxv_c197;
		L_p196 = mxv_c196;
	{  /* FormulaCaseList */
		if( mxs_is(_m,835,mxs_fath(_m,835,mxs_decl(_m,835,ID_p195)),_PredDecl_) ){
			mxv_i124 = mxs_true(_m,0);
			goto L124;
		}
	{  /* FormulaCaseList */
		if( mxs_is(_m,836,mxs_fath(_m,836,mxs_decl(_m,836,ID_p195)),_Predicate_) ){
			mxv_i125 = mxs_true(_m,0);
			goto L125;
		}
		mxv_i125 = mxs_false(_m,0);
		L125: ;
	}
		mxv_i124 = mxv_i125;
		L124: ;
	}
		if( !(  ( ! mxs_eq(_m,0,mxs_true(_m,0),mxv_i124)||mxs_eq(_m,0,mxs_numsons(_m,837,EL_p198),mxs_numsons(_m,837,mxs_rbroth(_m,837,mxs_decl(_m,837,ID_p195))))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,839,6,mxs_atoe(_c,0,"*****  Line "),mxs_s(_m,838,L_p196),mxs_atoe(_c,0,", column "),mxs_s(_m,838,C_p197),mxs_atoe(_c,0,": "),mxs_atoe(_c,0,"number of formal params doesn't match number of actual params\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_26( void ){
	ELEMENT  mxv_c262, ID_p262, mxv_c261, mxv_c260, N_p260, mxv_c0 = 1L;
	long mxv_cix260,mxv_cbd260;
	mxv_cbd260 = mxs_number(_c,0,_FctOrAtt_);
	for(mxv_cix260=1;mxv_cix260<=mxv_cbd260;mxv_cix260++){
		mxv_c260 = mxs_element(_c,0,mxv_cix260,_FctOrAtt_);
		N_p260 = mxv_c260;
		if( mxs_numsons(_c,0,mxv_c260) < 1 ) continue;
		mxv_c261 = mxs_son(_c,0,1,mxv_c260);
		if( mxs_numsons(_c,0,mxv_c261) < 1 ) continue;
		mxv_c262 = mxs_son(_c,0,1,mxv_c261);
		ID_p262 = mxv_c262;
		if( !(  ( ! mxs_eq(_m,0,mxs_appl_list(_m,1113,N_p260),mxs_nil(_m,1113))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,1114,3,mxs_atoe(_c,0,"*****  internal error: appl_list of the Function/Attribute "),mxs_id(_m,1114,ID_p262),mxs_atoe(_c,0," is nil()\n"));
			fprintf(stderr,"%s", mxs_etoa(_c,0,mxv_errstr) );
		}
	}

	return mxv_c0;
}

static  long  mxc_27( void ){
	ELEMENT  mxv_c296, ID_p296, mxv_c295, mxv_c294, N_p294, mxv_c0 = 1L;
	long mxv_cix294,mxv_cbd294;
	mxv_cbd294 = mxs_number(_c,0,_FctOrAtt_);
	for(mxv_cix294=1;mxv_cix294<=mxv_cbd294;mxv_cix294++){
		mxv_c294 = mxs_element(_c,0,mxv_cix294,_FctOrAtt_);
		N_p294 = mxv_c294;
		if( mxs_numsons(_c,0,mxv_c294) < 1 ) continue;
		mxv_c295 = mxs_son(_c,0,1,mxv_c294);
		if( mxs_numsons(_c,0,mxv_c295) < 1 ) continue;
		mxv_c296 = mxs_son(_c,0,1,mxv_c295);
		ID_p296 = mxv_c296;
		if( !(  ( ! mxs_eq(_m,0,mxs_appl_relacc_list(_m,1467,N_p294),mxs_nil(_m,1467))) )  ){
			mxv_c0 = 0L;
			mxv_errstr =  mxi_string_conc(_m,1468,3,mxs_atoe(_c,0,"***** internal error: Function/Attribute"),mxs_id(_m,1468,ID_p296),mxs_atoe(_c,0," : appl_relacc_list is nil\n"));
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



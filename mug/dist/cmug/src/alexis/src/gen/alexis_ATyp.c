          /* Analyse Typen der Phase alexis */
          /* ======================= */

struct g1scanner{
	short prodnum;
	struct g1scannerNN NN;
	union {
		struct {
			IDENT *p12;
			struct g1option *p13;
			struct g1definitions *p14;
			struct g1main *p15;
		} p1;
	} C;
};
struct g1actionspec{
	short prodnum;
	struct g1actionspecNN NN;
	union {
		struct {
			IDENT *p1411;
			struct g1parlist *p1413;
		} p141;
		struct {
			IDENT *p1421;
		} p142;
		struct {
			PROGSTRINGSY *p1431;
		} p143;
	} C;
};
struct g1definitions{
	short prodnum;
	struct g1definitionsNN NN;
	union {
		struct {
			struct g1definitions *p412;
		} p41;
		struct {
			struct g1makros *p421;
			struct g1definitions *p422;
		} p42;
		struct {
			struct g1makroact *p431;
			struct g1definitions *p432;
		} p43;
		struct {
			struct g1specialact *p441;
			struct g1definitions *p442;
		} p44;
	} C;
};
struct g1formparlist{
	short prodnum;
	struct g1formparlistNN NN;
	union {
		struct {
			FORMPAR *p811;
		} p81;
		struct {
			FORMPAR *p821;
			struct g1formparlist *p823;
		} p82;
	} C;
};
struct g1lexemes{
	short prodnum;
	struct g1lexemesNN NN;
	union {
		struct {
			struct g1regexpr *p1312;
			struct g1actionspec *p1314;
			struct g1lexemes *p1316;
		} p131;
		struct {
			struct g1regexpr *p1321;
			struct g1actionspec *p1323;
			struct g1lexemes *p1325;
		} p132;
		struct {
			struct g1lexemes *p1332;
		} p133;
	} C;
};
struct g1main{
	short prodnum;
	struct g1mainNN NN;
	union {
		struct {
			struct g1lexemes *p512;
		} p51;
	} C;
};
struct g1makroact{
	short prodnum;
	struct g1makroactNN NN;
	union {
		struct {
			struct g1makroactseq *p612;
		} p61;
	} C;
};
struct g1makroactseq{
	short prodnum;
	struct g1makroactseqNN NN;
	union {
		struct {
			IDENT *p711;
			struct g1formparlist *p713;
			PROGSTRINGSY *p715;
			struct g1makroactseq *p716;
		} p71;
		struct {
			IDENT *p721;
			PROGSTRINGSY *p722;
			struct g1makroactseq *p723;
		} p72;
	} C;
};
struct g1makrolexemes{
	short prodnum;
	struct g1makrolexemesNN NN;
	union {
		struct {
			IDENT *p1201;
			struct g1regexpr *p1203;
			struct g1makrolexemes *p1205;
		} p120;
		struct {
			IDENT *p1211;
			struct g1regexpr *p1213;
		} p121;
	} C;
};
struct g1makros{
	short prodnum;
	struct g1makrosNN NN;
	union {
		struct {
			struct g1makrolexemes *p1112;
		} p111;
	} C;
};
struct g1option{
	short prodnum;
	struct g1optionNN NN;
	union {
		struct {
			struct g1optionseq *p212;
		} p21;
	} C;
};
struct g1optionseq{
	short prodnum;
	struct g1optionseqNN NN;
	union {
		struct {
			INSTRUCTSY *p311;
			struct g1optionseq *p312;
		} p31;
	} C;
};
struct g1par{
	short prodnum;
	struct g1parNN NN;
	union {
		struct {
			INTEGERSY *p1611;
		} p161;
		struct {
			STRINGSY *p1621;
		} p162;
	} C;
};
struct g1parlist{
	short prodnum;
	struct g1parlistNN NN;
	union {
		struct {
			struct g1par *p1511;
		} p151;
		struct {
			struct g1par *p1521;
			struct g1parlist *p1523;
		} p152;
	} C;
};
struct g1regelem{
	short prodnum;
	struct g1regelemNN NN;
	union {
		struct {
			STRINGSY *p2111;
		} p211;
		struct {
			struct g1setseq *p2122;
		} p212;
		struct {
			struct g1setseq *p2133;
		} p213;
		struct {
			struct g1regexpr *p2142;
		} p214;
		struct {
			IDENT *p2151;
		} p215;
		struct {
			struct g1regexpr *p2163;
		} p216;
	} C;
};
struct g1regexpr{
	short prodnum;
	struct g1regexprNN NN;
	union {
		struct {
			struct g1regexpr *p1711;
			struct g1regterm *p1713;
		} p171;
		struct {
			struct g1regterm *p1721;
		} p172;
	} C;
};
struct g1regfaktor{
	short prodnum;
	struct g1regfaktorNN NN;
	union {
		struct {
			struct g1regelem *p1911;
			REGOP *p1912;
		} p191;
		struct {
			struct g1regelem *p1921;
			struct g1times *p1923;
		} p192;
		struct {
			struct g1regelem *p1931;
		} p193;
	} C;
};
struct g1regterm{
	short prodnum;
	struct g1regtermNN NN;
	union {
		struct {
			struct g1regterm *p1811;
			struct g1regfaktor *p1812;
		} p181;
		struct {
			struct g1regfaktor *p1821;
		} p182;
	} C;
};
struct g1setseq{
	short prodnum;
	struct g1setseqNN NN;
	union {
		struct {
			STRINGSY *p2311;
		} p231;
		struct {
			STRINGSY *p2321;
			struct g1setseq *p2323;
		} p232;
		struct {
			STRINGSY *p2331;
			STRINGSY *p2333;
		} p233;
		struct {
			STRINGSY *p2341;
			STRINGSY *p2343;
			struct g1setseq *p2345;
		} p234;
	} C;
};
struct g1specialact{
	short prodnum;
	struct g1specialactNN NN;
	union {
		struct {
			SPECIALSY *p911;
			PROGSTRINGSY *p912;
		} p91;
	} C;
};
struct g1times{
	short prodnum;
	struct g1timesNN NN;
	union {
		struct {
			INTEGERSY *p2011;
		} p201;
		struct {
			INTEGERSY *p2021;
		} p202;
		struct {
			INTEGERSY *p2032;
		} p203;
		struct {
			INTEGERSY *p2041;
			INTEGERSY *p2043;
		} p204;
	} C;
};

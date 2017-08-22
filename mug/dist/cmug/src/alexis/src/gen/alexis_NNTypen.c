struct g1scannerNN {
	int STATE;
	BOOL dscan;
	BOOL coda;
	KOMPRUEB ko;
	CLASSDESC cd;
	BOOL hb;
	BOOL hc;
	BOCLKO bck;
	};
struct g1actionspecNN {
	int STATE;
	BOOL icode;
	BOOL ignore;
	AUTOMAT iautom;
	AUTOMAT dautom;
	BOOL dcode;
	AUTBOOL aubo;
	PARTYPE dummy;
	INT null;
	PROGSTRINGSY nulp;
	};
struct g1definitionsNN {
	int STATE;
	BOOL icode;
	BOOL dcode;
	};
struct g1formparlistNN {
	int STATE;
	BOOL icode;
	INT iparanz;
	INT dparanz;
	BOOL dcode;
	INT plusone;
	};
struct g1lexemesNN {
	int STATE;
	BOOL icode;
	AUTOMAT iautom;
	AUTOMAT dautom;
	BOOL dcode;
	AUTBOOL aubo;
	};
struct g1mainNN {
	int STATE;
	BOOL icode;
	AUTOMAT dautom;
	BOOL dcode;
	BOOL auxc;
	BOOL auxd;
	AUTOMAT dis;
	AUTOMAT myh;
	AUTBOOL aubo1;
	AUTBOOL aubo2;
	AUTBOOL aubo3;
	};
struct g1makroactNN {
	int STATE;
	BOOL icode;
	BOOL dcode;
	};
struct g1makroactseqNN {
	int STATE;
	BOOL icode;
	BOOL dcode;
	INT zero;
	};
struct g1makrolexemesNN {
	int STATE;
	BOOL icode;
	BOOL dcode;
	};
struct g1makrosNN {
	int STATE;
	BOOL icode;
	BOOL dcode;
	};
struct g1optionNN {
	int STATE;
	BOOL icode;
	BOOL dcode;
	};
struct g1optionseqNN {
	int STATE;
	BOOL icode;
	BOOL dcode;
	};
struct g1parNN {
	int STATE;
	INT dpar;
	QUELLORT ort;
	INTORT dint;
	};
struct g1parlistNN {
	int STATE;
	BOOL icode;
	PARTYPE ipars;
	INT iparanz;
	PARTYPE dpars;
	INT dparanz;
	BOOL dcode;
	INT plusone;
	BOOLPAR bopa;
	};
struct g1regelemNN {
	int STATE;
	BOOL icode;
	AUTOMAT dautom;
	BOOL dcode;
	CHARSET chse;
	AUTBOOL aubo;
	};
struct g1regexprNN {
	int STATE;
	BOOL icode;
	AUTOMAT dautom;
	BOOL dcode;
	AUTBOOL aubo;
	};
struct g1regfaktorNN {
	int STATE;
	BOOL icode;
	AUTOMAT dautom;
	BOOL dcode;
	AUTBOOL aubo;
	};
struct g1regtermNN {
	int STATE;
	BOOL icode;
	AUTOMAT dautom;
	BOOL dcode;
	AUTBOOL aubo;
	};
struct g1setseqNN {
	int STATE;
	BOOL icode;
	CHARSET dset;
	BOOL dcode;
	CHARBOOL chbo;
	CHARSET set;
	};
struct g1specialactNN {
	int STATE;
	BOOL icode;
	BOOL dcode;
	};
struct g1timesNN {
	int STATE;
	INTEGERSY dug;
	INTEGERSY dog;
	};



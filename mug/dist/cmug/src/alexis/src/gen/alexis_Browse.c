

              /* Die Ausgabefunktionen */
              /* ===================== */


extern void ((*alexisBrowseTab[])());
#include"browse_proc.c"


void alexisprint_p1(K)
struct g1scanner *K;
/* p1 : scanner -> scannersy IDENT option definitions main  */

{
	BROWSE_print_vater("scanner", 1);
	BROWSE_print_attribut("coda", 'A', "BOOL", sizeof(K->NN.coda), 0, (char *)(&K->NN.coda));
	BROWSE_print_funktion("boclko2bool", 8);
	BROWSE_print_argument("coda", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_argument("bck", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("ko", 'A', "KOMPRUEB", sizeof(K->NN.ko), 0, (char *)(&K->NN.ko));
	BROWSE_print_funktion("boclko2kompr", 10);
	BROWSE_print_argument("ko", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_argument("bck", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("cd", 'A', "CLASSDESC", sizeof(K->NN.cd), 0, (char *)(&K->NN.cd));
	BROWSE_print_funktion("boclko2class", 9);
	BROWSE_print_argument("cd", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_argument("bck", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("hb", 'A', "BOOL", sizeof(K->NN.hb), 0, (char *)(&K->NN.hb));
	BROWSE_print_funktion("ScanTrue", 2);
	BROWSE_print_argument("hb", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("hc", 'A', "BOOL", sizeof(K->NN.hc), 0, (char *)(&K->NN.hc));
	BROWSE_print_funktion("sgentable", 21);
	BROWSE_print_argument("hc", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_argument("coda", 'A', "scanner", 1);
	BROWSE_print_argument("ko", 'A', "scanner", 1);
	BROWSE_print_argument("cd", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("bck", 'A', "BOCLKO", sizeof(K->NN.bck), 0, (char *)(&K->NN.bck));
	BROWSE_print_funktion("SKompress", 20);
	BROWSE_print_argument("bck", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dcode", 'D', "main", 6);
	BROWSE_print_argument("dautom", 'D', "main", 6);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dscan", 'D', "BOOL", sizeof(K->NN.dscan), 0, (char *)(&K->NN.dscan));
	BROWSE_print_funktion("SGenActions", 22);
	BROWSE_print_argument("dscan", 'D', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_argument("hc", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("scannersy", 2, 1);
	BROWSE_print_sohn("IDENT", 3, 1);
	BROWSE_print_sohn("option", 4, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p1.p13->NN.icode), 0, (char *)(&K->C.p1.p13->NN.icode));
	BROWSE_print_funktion("InitAlexis", 19);
	BROWSE_print_argument("icode", 'I', "option", 4);
	BROWSE_print_end_attr();

	BROWSE_print_argument("hb", 'A', "scanner", 1);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p1.p13->prodnum])(K->C.p1.p13);
	BROWSE_print_sohn("definitions", 5, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p1.p14->NN.icode), 1, (char *)(&K->C.p1.p14->NN.icode));
	BROWSE_print_argument("dcode", 'D', "option", 4);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p1.p14->prodnum])(K->C.p1.p14);
	BROWSE_print_sohn("main", 6, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p1.p15->NN.icode), 1, (char *)(&K->C.p1.p15->NN.icode));
	BROWSE_print_argument("dcode", 'D', "definitions", 5);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p1.p15->prodnum])(K->C.p1.p15);
	BROWSE_print_prod_end();
}


void alexisprint_p141(K)
struct g1actionspec *K;
/* p141 : actionspec -> IDENT openpsy parlist closepsy  */

{
	BROWSE_print_vater("actionspec", 90);
	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("DefMakAct", 38);
	BROWSE_print_argument("aubo", 'A', "actionspec", 90);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dcode", 'D', "parlist", 93);
	BROWSE_print_argument("ignore", 'I', "actionspec", 90);
	BROWSE_print_argument("iautom", 'I', "actionspec", 90);
	BROWSE_print_argument("dparanz", 'D', "parlist", 93);
	BROWSE_print_argument(NULL, ' ', "IDENT", 91);
	BROWSE_print_argument("dpars", 'D', "parlist", 93);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "actionspec", 90);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "actionspec", 90);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "actionspec", 90);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "actionspec", 90);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("IDENT", 91, 1);
	BROWSE_print_sohn("openpsy", 92, 1);
	BROWSE_print_sohn("parlist", 93, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p141.p1413->NN.icode), 1, (char *)(&K->C.p141.p1413->NN.icode));
	BROWSE_print_argument("icode", 'I', "actionspec", 90);
	BROWSE_print_attribut("ipars", 'I', "PARTYPE", sizeof(K->C.p141.p1413->NN.ipars), 0, (char *)(&K->C.p141.p1413->NN.ipars));
	BROWSE_print_funktion("GenEmptPars", 23);
	BROWSE_print_argument("ipars", 'I', "parlist", 93);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("iparanz", 'I', "INT", sizeof(K->C.p141.p1413->NN.iparanz), 0, (char *)(&K->C.p141.p1413->NN.iparanz));
	BROWSE_print_funktion("IntNull", 5);
	BROWSE_print_argument("iparanz", 'I', "parlist", 93);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p141.p1413->prodnum])(K->C.p141.p1413);
	BROWSE_print_sohn("closepsy", 94, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p142(K)
struct g1actionspec *K;
/* p142 : actionspec -> IDENT  */

{
	BROWSE_print_vater("actionspec", 95);
	BROWSE_print_attribut("dummy", 'A', "PARTYPE", sizeof(K->NN.dummy), 0, (char *)(&K->NN.dummy));
	BROWSE_print_funktion("GenEmptPars", 23);
	BROWSE_print_argument("dummy", 'A', "actionspec", 95);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("null", 'A', "INT", sizeof(K->NN.null), 0, (char *)(&K->NN.null));
	BROWSE_print_funktion("IntNull", 5);
	BROWSE_print_argument("null", 'A', "actionspec", 95);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("DefMakAct", 38);
	BROWSE_print_argument("aubo", 'A', "actionspec", 95);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "actionspec", 95);
	BROWSE_print_argument("ignore", 'I', "actionspec", 95);
	BROWSE_print_argument("iautom", 'I', "actionspec", 95);
	BROWSE_print_argument("null", 'A', "actionspec", 95);
	BROWSE_print_argument(NULL, ' ', "IDENT", 96);
	BROWSE_print_argument("dummy", 'A', "actionspec", 95);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "actionspec", 95);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "actionspec", 95);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "actionspec", 95);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "actionspec", 95);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("IDENT", 96, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p143(K)
struct g1actionspec *K;
/* p143 : actionspec -> PROGSTRINGSY  */

{
	BROWSE_print_vater("actionspec", 97);
	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("DefAction", 39);
	BROWSE_print_argument("aubo", 'A', "actionspec", 97);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "actionspec", 97);
	BROWSE_print_argument("ignore", 'I', "actionspec", 97);
	BROWSE_print_argument("iautom", 'I', "actionspec", 97);
	BROWSE_print_argument(NULL, ' ', "PROGSTRINGSY", 98);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "actionspec", 97);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "actionspec", 97);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "actionspec", 97);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "actionspec", 97);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("PROGSTRINGSY", 98, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p144(K)
struct g1actionspec *K;
/* p144 : actionspec ->  */

{
	BROWSE_print_vater("actionspec", 99);
	BROWSE_print_attribut("nulp", 'A', "PROGSTRINGSY", sizeof(K->NN.nulp), 0, (char *)(&K->NN.nulp));
	BROWSE_print_funktion("GenEProg", 40);
	BROWSE_print_argument("nulp", 'A', "actionspec", 99);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("DefAction", 39);
	BROWSE_print_argument("aubo", 'A', "actionspec", 99);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "actionspec", 99);
	BROWSE_print_argument("ignore", 'I', "actionspec", 99);
	BROWSE_print_argument("iautom", 'I', "actionspec", 99);
	BROWSE_print_argument("nulp", 'A', "actionspec", 99);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "actionspec", 99);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "actionspec", 99);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "actionspec", 99);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "actionspec", 99);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_prod_end();
}


void alexisprint_p41(K)
struct g1definitions *K;
/* p41 : definitions -> includesy definitions  */

{
	BROWSE_print_vater("definitions", 16);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "definitions", 18);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("includesy", 17, 1);
	BROWSE_print_sohn("definitions", 18, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p41.p412->NN.icode), 1, (char *)(&K->C.p41.p412->NN.icode));
	BROWSE_print_argument("icode", 'I', "definitions", 16);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p41.p412->prodnum])(K->C.p41.p412);
	BROWSE_print_prod_end();
}


void alexisprint_p42(K)
struct g1definitions *K;
/* p42 : definitions -> makros definitions  */

{
	BROWSE_print_vater("definitions", 19);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "definitions", 21);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("makros", 20, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p42.p421->NN.icode), 1, (char *)(&K->C.p42.p421->NN.icode));
	BROWSE_print_argument("icode", 'I', "definitions", 19);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p42.p421->prodnum])(K->C.p42.p421);
	BROWSE_print_sohn("definitions", 21, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p42.p422->NN.icode), 1, (char *)(&K->C.p42.p422->NN.icode));
	BROWSE_print_argument("dcode", 'D', "makros", 20);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p42.p422->prodnum])(K->C.p42.p422);
	BROWSE_print_prod_end();
}


void alexisprint_p43(K)
struct g1definitions *K;
/* p43 : definitions -> makroact definitions  */

{
	BROWSE_print_vater("definitions", 22);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "definitions", 24);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("makroact", 23, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p43.p431->NN.icode), 1, (char *)(&K->C.p43.p431->NN.icode));
	BROWSE_print_argument("icode", 'I', "definitions", 22);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p43.p431->prodnum])(K->C.p43.p431);
	BROWSE_print_sohn("definitions", 24, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p43.p432->NN.icode), 1, (char *)(&K->C.p43.p432->NN.icode));
	BROWSE_print_argument("dcode", 'D', "makroact", 23);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p43.p432->prodnum])(K->C.p43.p432);
	BROWSE_print_prod_end();
}


void alexisprint_p44(K)
struct g1definitions *K;
/* p44 : definitions -> specialact definitions  */

{
	BROWSE_print_vater("definitions", 25);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "definitions", 27);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("specialact", 26, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p44.p441->NN.icode), 1, (char *)(&K->C.p44.p441->NN.icode));
	BROWSE_print_argument("icode", 'I', "definitions", 25);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p44.p441->prodnum])(K->C.p44.p441);
	BROWSE_print_sohn("definitions", 27, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p44.p442->NN.icode), 1, (char *)(&K->C.p44.p442->NN.icode));
	BROWSE_print_argument("dcode", 'D', "specialact", 26);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p44.p442->prodnum])(K->C.p44.p442);
	BROWSE_print_prod_end();
}


void alexisprint_p45(K)
struct g1definitions *K;
/* p45 : definitions ->  */

{
	BROWSE_print_vater("definitions", 28);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("icode", 'I', "definitions", 28);
	BROWSE_print_end_attr();

	BROWSE_print_prod_end();
}


void alexisprint_p81(K)
struct g1formparlist *K;
/* p81 : formparlist -> FORMPAR  */

{
	BROWSE_print_vater("formparlist", 49);
	BROWSE_print_attribut("plusone", 'A', "INT", sizeof(K->NN.plusone), 0, (char *)(&K->NN.plusone));
	BROWSE_print_funktion("IPlus1", 4);
	BROWSE_print_argument("plusone", 'A', "formparlist", 49);
	BROWSE_print_end_attr();

	BROWSE_print_argument("iparanz", 'I', "formparlist", 49);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dparanz", 'D', "INT", sizeof(K->NN.dparanz), 1, (char *)(&K->NN.dparanz));
	BROWSE_print_argument("plusone", 'A', "formparlist", 49);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("ChkFormPar", 37);
	BROWSE_print_argument("dcode", 'D', "formparlist", 49);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "formparlist", 49);
	BROWSE_print_argument(NULL, ' ', "FORMPAR", 50);
	BROWSE_print_argument("plusone", 'A', "formparlist", 49);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("FORMPAR", 50, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p82(K)
struct g1formparlist *K;
/* p82 : formparlist -> FORMPAR commasy formparlist  */

{
	BROWSE_print_vater("formparlist", 51);
	BROWSE_print_attribut("plusone", 'A', "INT", sizeof(K->NN.plusone), 0, (char *)(&K->NN.plusone));
	BROWSE_print_funktion("IPlus1", 4);
	BROWSE_print_argument("plusone", 'A', "formparlist", 51);
	BROWSE_print_end_attr();

	BROWSE_print_argument("iparanz", 'I', "formparlist", 51);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dparanz", 'D', "INT", sizeof(K->NN.dparanz), 1, (char *)(&K->NN.dparanz));
	BROWSE_print_argument("dparanz", 'D', "formparlist", 54);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "formparlist", 54);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("FORMPAR", 52, 1);
	BROWSE_print_sohn("commasy", 53, 1);
	BROWSE_print_sohn("formparlist", 54, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p82.p823->NN.icode), 0, (char *)(&K->C.p82.p823->NN.icode));
	BROWSE_print_funktion("ChkFormPar", 37);
	BROWSE_print_argument("icode", 'I', "formparlist", 54);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "formparlist", 51);
	BROWSE_print_argument(NULL, ' ', "FORMPAR", 52);
	BROWSE_print_argument("plusone", 'A', "formparlist", 51);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("iparanz", 'I', "INT", sizeof(K->C.p82.p823->NN.iparanz), 1, (char *)(&K->C.p82.p823->NN.iparanz));
	BROWSE_print_argument("plusone", 'A', "formparlist", 51);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p82.p823->prodnum])(K->C.p82.p823);
	BROWSE_print_prod_end();
}


void alexisprint_p131(K)
struct g1lexemes *K;
/* p131 : lexemes -> ignoresy regexpr arrowsy actionspec semicolonsy lexemes  */

{
	BROWSE_print_vater("lexemes", 73);
	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("SAlternative", 32);
	BROWSE_print_argument("aubo", 'A', "lexemes", 73);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dautom", 'D', "actionspec", 77);
	BROWSE_print_argument("iautom", 'I', "lexemes", 73);
	BROWSE_print_argument("dcode", 'D', "actionspec", 77);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 1, (char *)(&K->NN.dautom));
	BROWSE_print_argument("dautom", 'D', "lexemes", 79);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "lexemes", 79);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("ignoresy", 74, 1);
	BROWSE_print_sohn("regexpr", 75, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p131.p1312->NN.icode), 1, (char *)(&K->C.p131.p1312->NN.icode));
	BROWSE_print_argument("icode", 'I', "lexemes", 73);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p131.p1312->prodnum])(K->C.p131.p1312);
	BROWSE_print_sohn("arrowsy", 76, 1);
	BROWSE_print_sohn("actionspec", 77, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p131.p1314->NN.icode), 1, (char *)(&K->C.p131.p1314->NN.icode));
	BROWSE_print_argument("dcode", 'D', "regexpr", 75);
	BROWSE_print_attribut("ignore", 'I', "BOOL", sizeof(K->C.p131.p1314->NN.ignore), 0, (char *)(&K->C.p131.p1314->NN.ignore));
	BROWSE_print_funktion("SetTrue", 6);
	BROWSE_print_argument("ignore", 'I', "actionspec", 77);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("iautom", 'I', "AUTOMAT", sizeof(K->C.p131.p1314->NN.iautom), 1, (char *)(&K->C.p131.p1314->NN.iautom));
	BROWSE_print_argument("dautom", 'D', "regexpr", 75);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p131.p1314->prodnum])(K->C.p131.p1314);
	BROWSE_print_sohn("semicolonsy", 78, 1);
	BROWSE_print_sohn("lexemes", 79, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p131.p1316->NN.icode), 0, (char *)(&K->C.p131.p1316->NN.icode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("icode", 'I', "lexemes", 79);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "lexemes", 73);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("iautom", 'I', "AUTOMAT", sizeof(K->C.p131.p1316->NN.iautom), 0, (char *)(&K->C.p131.p1316->NN.iautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("iautom", 'I', "lexemes", 79);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "lexemes", 73);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p131.p1316->prodnum])(K->C.p131.p1316);
	BROWSE_print_prod_end();
}


void alexisprint_p132(K)
struct g1lexemes *K;
/* p132 : lexemes -> regexpr arrowsy actionspec semicolonsy lexemes  */

{
	BROWSE_print_vater("lexemes", 80);
	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("SAlternative", 32);
	BROWSE_print_argument("aubo", 'A', "lexemes", 80);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dautom", 'D', "actionspec", 83);
	BROWSE_print_argument("iautom", 'I', "lexemes", 80);
	BROWSE_print_argument("dcode", 'D', "actionspec", 83);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 1, (char *)(&K->NN.dautom));
	BROWSE_print_argument("dautom", 'D', "lexemes", 85);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "lexemes", 85);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("regexpr", 81, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p132.p1321->NN.icode), 1, (char *)(&K->C.p132.p1321->NN.icode));
	BROWSE_print_argument("icode", 'I', "lexemes", 80);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p132.p1321->prodnum])(K->C.p132.p1321);
	BROWSE_print_sohn("arrowsy", 82, 1);
	BROWSE_print_sohn("actionspec", 83, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p132.p1323->NN.icode), 1, (char *)(&K->C.p132.p1323->NN.icode));
	BROWSE_print_argument("dcode", 'D', "regexpr", 81);
	BROWSE_print_attribut("ignore", 'I', "BOOL", sizeof(K->C.p132.p1323->NN.ignore), 0, (char *)(&K->C.p132.p1323->NN.ignore));
	BROWSE_print_funktion("SetFalse", 7);
	BROWSE_print_argument("ignore", 'I', "actionspec", 83);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("iautom", 'I', "AUTOMAT", sizeof(K->C.p132.p1323->NN.iautom), 1, (char *)(&K->C.p132.p1323->NN.iautom));
	BROWSE_print_argument("dautom", 'D', "regexpr", 81);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p132.p1323->prodnum])(K->C.p132.p1323);
	BROWSE_print_sohn("semicolonsy", 84, 1);
	BROWSE_print_sohn("lexemes", 85, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p132.p1325->NN.icode), 0, (char *)(&K->C.p132.p1325->NN.icode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("icode", 'I', "lexemes", 85);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "lexemes", 80);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("iautom", 'I', "AUTOMAT", sizeof(K->C.p132.p1325->NN.iautom), 0, (char *)(&K->C.p132.p1325->NN.iautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("iautom", 'I', "lexemes", 85);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "lexemes", 80);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p132.p1325->prodnum])(K->C.p132.p1325);
	BROWSE_print_prod_end();
}


void alexisprint_p133(K)
struct g1lexemes *K;
/* p133 : lexemes -> includesy lexemes  */

{
	BROWSE_print_vater("lexemes", 86);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 1, (char *)(&K->NN.dautom));
	BROWSE_print_argument("dautom", 'D', "lexemes", 88);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "lexemes", 88);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("includesy", 87, 1);
	BROWSE_print_sohn("lexemes", 88, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p133.p1332->NN.icode), 1, (char *)(&K->C.p133.p1332->NN.icode));
	BROWSE_print_argument("icode", 'I', "lexemes", 86);
	BROWSE_print_attribut("iautom", 'I', "AUTOMAT", sizeof(K->C.p133.p1332->NN.iautom), 1, (char *)(&K->C.p133.p1332->NN.iautom));
	BROWSE_print_argument("iautom", 'I', "lexemes", 86);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p133.p1332->prodnum])(K->C.p133.p1332);
	BROWSE_print_prod_end();
}


void alexisprint_p134(K)
struct g1lexemes *K;
/* p134 : lexemes ->  */

{
	BROWSE_print_vater("lexemes", 89);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 1, (char *)(&K->NN.dautom));
	BROWSE_print_argument("iautom", 'I', "lexemes", 89);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("icode", 'I', "lexemes", 89);
	BROWSE_print_end_attr();

	BROWSE_print_prod_end();
}


void alexisprint_p51(K)
struct g1main *K;
/* p51 : main -> lexemessy lexemes lexemesendsy  */

{
	BROWSE_print_vater("main", 29);
	BROWSE_print_attribut("auxc", 'A', "BOOL", sizeof(K->NN.auxc), 0, (char *)(&K->NN.auxc));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("auxc", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo2", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("auxd", 'A', "BOOL", sizeof(K->NN.auxd), 0, (char *)(&K->NN.auxd));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("auxd", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo1", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dis", 'A', "AUTOMAT", sizeof(K->NN.dis), 0, (char *)(&K->NN.dis));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dis", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo1", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("myh", 'A', "AUTOMAT", sizeof(K->NN.myh), 0, (char *)(&K->NN.myh));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("myh", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo2", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("aubo1", 'A', "AUTBOOL", sizeof(K->NN.aubo1), 0, (char *)(&K->NN.aubo1));
	BROWSE_print_funktion("DispLexMak", 25);
	BROWSE_print_argument("aubo1", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dautom", 'D', "lexemes", 31);
	BROWSE_print_argument("dcode", 'D', "lexemes", 31);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("aubo2", 'A', "AUTBOOL", sizeof(K->NN.aubo2), 0, (char *)(&K->NN.aubo2));
	BROWSE_print_funktion("SMyhill", 26);
	BROWSE_print_argument("aubo2", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dis", 'A', "main", 29);
	BROWSE_print_argument("auxd", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("aubo3", 'A', "AUTBOOL", sizeof(K->NN.aubo3), 0, (char *)(&K->NN.aubo3));
	BROWSE_print_funktion("SMinimize", 28);
	BROWSE_print_argument("aubo3", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_argument("myh", 'A', "main", 29);
	BROWSE_print_argument("auxc", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo3", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo3", 'A', "main", 29);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("lexemessy", 30, 1);
	BROWSE_print_sohn("lexemes", 31, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p51.p512->NN.icode), 1, (char *)(&K->C.p51.p512->NN.icode));
	BROWSE_print_argument("icode", 'I', "main", 29);
	BROWSE_print_attribut("iautom", 'I', "AUTOMAT", sizeof(K->C.p51.p512->NN.iautom), 0, (char *)(&K->C.p51.p512->NN.iautom));
	BROWSE_print_funktion("AutomatNil", 3);
	BROWSE_print_argument("iautom", 'I', "lexemes", 31);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p51.p512->prodnum])(K->C.p51.p512);
	BROWSE_print_sohn("lexemesendsy", 32, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p61(K)
struct g1makroact *K;
/* p61 : makroact -> actionmakrossy makroactseq makroendsy  */

{
	BROWSE_print_vater("makroact", 33);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "makroactseq", 35);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("actionmakrossy", 34, 1);
	BROWSE_print_sohn("makroactseq", 35, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p61.p612->NN.icode), 1, (char *)(&K->C.p61.p612->NN.icode));
	BROWSE_print_argument("icode", 'I', "makroact", 33);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p61.p612->prodnum])(K->C.p61.p612);
	BROWSE_print_sohn("makroendsy", 36, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p71(K)
struct g1makroactseq *K;
/* p71 : makroactseq -> IDENT openpsy formparlist closepsy PROGSTRINGSY makroactseq  */

{
	BROWSE_print_vater("makroactseq", 37);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "makroactseq", 43);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("IDENT", 38, 1);
	BROWSE_print_sohn("openpsy", 39, 1);
	BROWSE_print_sohn("formparlist", 40, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p71.p713->NN.icode), 1, (char *)(&K->C.p71.p713->NN.icode));
	BROWSE_print_argument("icode", 'I', "makroactseq", 37);
	BROWSE_print_attribut("iparanz", 'I', "INT", sizeof(K->C.p71.p713->NN.iparanz), 0, (char *)(&K->C.p71.p713->NN.iparanz));
	BROWSE_print_funktion("IntNull", 5);
	BROWSE_print_argument("iparanz", 'I', "formparlist", 40);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p71.p713->prodnum])(K->C.p71.p713);
	BROWSE_print_sohn("closepsy", 41, 1);
	BROWSE_print_sohn("PROGSTRINGSY", 42, 1);
	BROWSE_print_sohn("makroactseq", 43, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p71.p716->NN.icode), 0, (char *)(&K->C.p71.p716->NN.icode));
	BROWSE_print_funktion("InstActMak", 29);
	BROWSE_print_argument("icode", 'I', "makroactseq", 43);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dcode", 'D', "formparlist", 40);
	BROWSE_print_argument(NULL, ' ', "IDENT", 38);
	BROWSE_print_argument("dparanz", 'D', "formparlist", 40);
	BROWSE_print_argument(NULL, ' ', "PROGSTRINGSY", 42);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p71.p716->prodnum])(K->C.p71.p716);
	BROWSE_print_prod_end();
}


void alexisprint_p72(K)
struct g1makroactseq *K;
/* p72 : makroactseq -> IDENT PROGSTRINGSY makroactseq  */

{
	BROWSE_print_vater("makroactseq", 44);
	BROWSE_print_attribut("zero", 'A', "INT", sizeof(K->NN.zero), 0, (char *)(&K->NN.zero));
	BROWSE_print_funktion("IntNull", 5);
	BROWSE_print_argument("zero", 'A', "makroactseq", 44);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "makroactseq", 47);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("IDENT", 45, 1);
	BROWSE_print_sohn("PROGSTRINGSY", 46, 1);
	BROWSE_print_sohn("makroactseq", 47, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p72.p723->NN.icode), 0, (char *)(&K->C.p72.p723->NN.icode));
	BROWSE_print_funktion("InstActMak", 29);
	BROWSE_print_argument("icode", 'I', "makroactseq", 47);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "makroactseq", 44);
	BROWSE_print_argument(NULL, ' ', "IDENT", 45);
	BROWSE_print_argument("zero", 'A', "makroactseq", 44);
	BROWSE_print_argument(NULL, ' ', "PROGSTRINGSY", 46);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p72.p723->prodnum])(K->C.p72.p723);
	BROWSE_print_prod_end();
}


void alexisprint_p73(K)
struct g1makroactseq *K;
/* p73 : makroactseq ->  */

{
	BROWSE_print_vater("makroactseq", 48);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("icode", 'I', "makroactseq", 48);
	BROWSE_print_end_attr();

	BROWSE_print_prod_end();
}


void alexisprint_p120(K)
struct g1makrolexemes *K;
/* p120 : makrolexemes -> IDENT equalsy regexpr semicolonsy makrolexemes  */

{
	BROWSE_print_vater("makrolexemes", 62);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "makrolexemes", 67);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("IDENT", 63, 1);
	BROWSE_print_sohn("equalsy", 64, 1);
	BROWSE_print_sohn("regexpr", 65, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p120.p1203->NN.icode), 1, (char *)(&K->C.p120.p1203->NN.icode));
	BROWSE_print_argument("icode", 'I', "makrolexemes", 62);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p120.p1203->prodnum])(K->C.p120.p1203);
	BROWSE_print_sohn("semicolonsy", 66, 1);
	BROWSE_print_sohn("makrolexemes", 67, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p120.p1205->NN.icode), 0, (char *)(&K->C.p120.p1205->NN.icode));
	BROWSE_print_funktion("InstLexMak", 31);
	BROWSE_print_argument("icode", 'I', "makrolexemes", 67);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dcode", 'D', "regexpr", 65);
	BROWSE_print_argument(NULL, ' ', "IDENT", 63);
	BROWSE_print_argument("dautom", 'D', "regexpr", 65);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p120.p1205->prodnum])(K->C.p120.p1205);
	BROWSE_print_prod_end();
}


void alexisprint_p121(K)
struct g1makrolexemes *K;
/* p121 : makrolexemes -> IDENT equalsy regexpr semicolonsy  */

{
	BROWSE_print_vater("makrolexemes", 68);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("InstLexMak", 31);
	BROWSE_print_argument("dcode", 'D', "makrolexemes", 68);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dcode", 'D', "regexpr", 71);
	BROWSE_print_argument(NULL, ' ', "IDENT", 69);
	BROWSE_print_argument("dautom", 'D', "regexpr", 71);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("IDENT", 69, 1);
	BROWSE_print_sohn("equalsy", 70, 1);
	BROWSE_print_sohn("regexpr", 71, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p121.p1213->NN.icode), 1, (char *)(&K->C.p121.p1213->NN.icode));
	BROWSE_print_argument("icode", 'I', "makrolexemes", 68);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p121.p1213->prodnum])(K->C.p121.p1213);
	BROWSE_print_sohn("semicolonsy", 72, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p111(K)
struct g1makros *K;
/* p111 : makros -> lexmakrossy makrolexemes makroendsy  */

{
	BROWSE_print_vater("makros", 58);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("icode", 'I', "makrolexemes", 60);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("lexmakrossy", 59, 1);
	BROWSE_print_sohn("makrolexemes", 60, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p111.p1112->NN.icode), 1, (char *)(&K->C.p111.p1112->NN.icode));
	BROWSE_print_argument("icode", 'I', "makros", 58);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p111.p1112->prodnum])(K->C.p111.p1112);
	BROWSE_print_sohn("makroendsy", 61, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p21(K)
struct g1option *K;
/* p21 : option -> optionssy optionseq optionendsy  */

{
	BROWSE_print_vater("option", 7);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "optionseq", 9);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("optionssy", 8, 1);
	BROWSE_print_sohn("optionseq", 9, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p21.p212->NN.icode), 1, (char *)(&K->C.p21.p212->NN.icode));
	BROWSE_print_argument("icode", 'I', "option", 7);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p21.p212->prodnum])(K->C.p21.p212);
	BROWSE_print_sohn("optionendsy", 10, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p22(K)
struct g1option *K;
/* p22 : option ->  */

{
	BROWSE_print_vater("option", 11);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("icode", 'I', "option", 11);
	BROWSE_print_end_attr();

	BROWSE_print_prod_end();
}


void alexisprint_p31(K)
struct g1optionseq *K;
/* p31 : optionseq -> INSTRUCTSY optionseq  */

{
	BROWSE_print_vater("optionseq", 12);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "optionseq", 14);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("INSTRUCTSY", 13, 1);
	BROWSE_print_sohn("optionseq", 14, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p31.p312->NN.icode), 0, (char *)(&K->C.p31.p312->NN.icode));
	BROWSE_print_funktion("SetInstFl", 24);
	BROWSE_print_argument("icode", 'I', "optionseq", 14);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "optionseq", 12);
	BROWSE_print_argument(NULL, ' ', "INSTRUCTSY", 13);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p31.p312->prodnum])(K->C.p31.p312);
	BROWSE_print_prod_end();
}


void alexisprint_p32(K)
struct g1optionseq *K;
/* p32 : optionseq ->  */

{
	BROWSE_print_vater("optionseq", 15);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("icode", 'I', "optionseq", 15);
	BROWSE_print_end_attr();

	BROWSE_print_prod_end();
}


void alexisprint_p161(K)
struct g1par *K;
/* p161 : par -> INTEGERSY  */

{
	BROWSE_print_vater("par", 106);
	BROWSE_print_attribut("dint", 'A', "INTORT", sizeof(K->NN.dint), 0, (char *)(&K->NN.dint));
	BROWSE_print_funktion("SemIntToStr", 35);
	BROWSE_print_argument("dint", 'A', "par", 106);
	BROWSE_print_end_attr();

	BROWSE_print_argument(NULL, ' ', "INTEGERSY", 107);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dpar", 'D', "INT", sizeof(K->NN.dpar), 0, (char *)(&K->NN.dpar));
	BROWSE_print_funktion("intort2i", 15);
	BROWSE_print_argument("dpar", 'D', "par", 106);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dint", 'A', "par", 106);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("ort", 'D', "QUELLORT", sizeof(K->NN.ort), 0, (char *)(&K->NN.ort));
	BROWSE_print_funktion("intort2o", 16);
	BROWSE_print_argument("ort", 'D', "par", 106);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dint", 'A', "par", 106);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("INTEGERSY", 107, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p162(K)
struct g1par *K;
/* p162 : par -> STRINGSY  */

{
	BROWSE_print_vater("par", 108);
	BROWSE_print_attribut("dint", 'A', "INTORT", sizeof(K->NN.dint), 0, (char *)(&K->NN.dint));
	BROWSE_print_funktion("SemStrToStr", 36);
	BROWSE_print_argument("dint", 'A', "par", 108);
	BROWSE_print_end_attr();

	BROWSE_print_argument(NULL, ' ', "STRINGSY", 109);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dpar", 'D', "INT", sizeof(K->NN.dpar), 0, (char *)(&K->NN.dpar));
	BROWSE_print_funktion("intort2i", 15);
	BROWSE_print_argument("dpar", 'D', "par", 108);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dint", 'A', "par", 108);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("ort", 'D', "QUELLORT", sizeof(K->NN.ort), 0, (char *)(&K->NN.ort));
	BROWSE_print_funktion("intort2o", 16);
	BROWSE_print_argument("ort", 'D', "par", 108);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dint", 'A', "par", 108);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("STRINGSY", 109, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p151(K)
struct g1parlist *K;
/* p151 : parlist -> par  */

{
	BROWSE_print_vater("parlist", 100);
	BROWSE_print_attribut("plusone", 'A', "INT", sizeof(K->NN.plusone), 0, (char *)(&K->NN.plusone));
	BROWSE_print_funktion("IPlus1", 4);
	BROWSE_print_argument("plusone", 'A', "parlist", 100);
	BROWSE_print_end_attr();

	BROWSE_print_argument("iparanz", 'I', "parlist", 100);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("bopa", 'A', "BOOLPAR", sizeof(K->NN.bopa), 0, (char *)(&K->NN.bopa));
	BROWSE_print_funktion("InsParam", 33);
	BROWSE_print_argument("bopa", 'A', "parlist", 100);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "parlist", 100);
	BROWSE_print_argument("dpar", 'D', "par", 101);
	BROWSE_print_argument("ipars", 'I', "parlist", 100);
	BROWSE_print_argument("plusone", 'A', "parlist", 100);
	BROWSE_print_argument("ort", 'D', "par", 101);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dpars", 'D', "PARTYPE", sizeof(K->NN.dpars), 0, (char *)(&K->NN.dpars));
	BROWSE_print_funktion("bopar2par", 14);
	BROWSE_print_argument("dpars", 'D', "parlist", 100);
	BROWSE_print_end_attr();

	BROWSE_print_argument("bopa", 'A', "parlist", 100);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dparanz", 'D', "INT", sizeof(K->NN.dparanz), 1, (char *)(&K->NN.dparanz));
	BROWSE_print_argument("plusone", 'A', "parlist", 100);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("bopar2bool", 13);
	BROWSE_print_argument("dcode", 'D', "parlist", 100);
	BROWSE_print_end_attr();

	BROWSE_print_argument("bopa", 'A', "parlist", 100);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("par", 101, 0);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p151.p1511->prodnum])(K->C.p151.p1511);
	BROWSE_print_prod_end();
}


void alexisprint_p152(K)
struct g1parlist *K;
/* p152 : parlist -> par commasy parlist  */

{
	BROWSE_print_vater("parlist", 102);
	BROWSE_print_attribut("plusone", 'A', "INT", sizeof(K->NN.plusone), 0, (char *)(&K->NN.plusone));
	BROWSE_print_funktion("IPlus1", 4);
	BROWSE_print_argument("plusone", 'A', "parlist", 102);
	BROWSE_print_end_attr();

	BROWSE_print_argument("iparanz", 'I', "parlist", 102);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("bopa", 'A', "BOOLPAR", sizeof(K->NN.bopa), 0, (char *)(&K->NN.bopa));
	BROWSE_print_funktion("InsParam", 33);
	BROWSE_print_argument("bopa", 'A', "parlist", 102);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "parlist", 102);
	BROWSE_print_argument("dpar", 'D', "par", 103);
	BROWSE_print_argument("ipars", 'I', "parlist", 102);
	BROWSE_print_argument("plusone", 'A', "parlist", 102);
	BROWSE_print_argument("ort", 'D', "par", 103);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dpars", 'D', "PARTYPE", sizeof(K->NN.dpars), 1, (char *)(&K->NN.dpars));
	BROWSE_print_argument("dpars", 'D', "parlist", 105);
	BROWSE_print_attribut("dparanz", 'D', "INT", sizeof(K->NN.dparanz), 1, (char *)(&K->NN.dparanz));
	BROWSE_print_argument("dparanz", 'D', "parlist", 105);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "parlist", 105);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("par", 103, 0);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p152.p1521->prodnum])(K->C.p152.p1521);
	BROWSE_print_sohn("commasy", 104, 1);
	BROWSE_print_sohn("parlist", 105, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p152.p1523->NN.icode), 0, (char *)(&K->C.p152.p1523->NN.icode));
	BROWSE_print_funktion("bopar2bool", 13);
	BROWSE_print_argument("icode", 'I', "parlist", 105);
	BROWSE_print_end_attr();

	BROWSE_print_argument("bopa", 'A', "parlist", 102);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("ipars", 'I', "PARTYPE", sizeof(K->C.p152.p1523->NN.ipars), 0, (char *)(&K->C.p152.p1523->NN.ipars));
	BROWSE_print_funktion("bopar2par", 14);
	BROWSE_print_argument("ipars", 'I', "parlist", 105);
	BROWSE_print_end_attr();

	BROWSE_print_argument("bopa", 'A', "parlist", 102);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("iparanz", 'I', "INT", sizeof(K->C.p152.p1523->NN.iparanz), 1, (char *)(&K->C.p152.p1523->NN.iparanz));
	BROWSE_print_argument("plusone", 'A', "parlist", 102);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p152.p1523->prodnum])(K->C.p152.p1523);
	BROWSE_print_prod_end();
}


void alexisprint_p211(K)
struct g1regelem *K;
/* p211 : regelem -> STRINGSY  */

{
	BROWSE_print_vater("regelem", 142);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("SStrToAut", 46);
	BROWSE_print_argument("dautom", 'D', "regelem", 142);
	BROWSE_print_end_attr();

	BROWSE_print_argument(NULL, ' ', "STRINGSY", 143);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("icode", 'I', "regelem", 142);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("STRINGSY", 143, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p212(K)
struct g1regelem *K;
/* p212 : regelem -> openbracksy setseq closebracksy  */

{
	BROWSE_print_vater("regelem", 144);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("SSetToAut", 47);
	BROWSE_print_argument("dautom", 'D', "regelem", 144);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dset", 'D', "setseq", 146);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "setseq", 146);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("openbracksy", 145, 1);
	BROWSE_print_sohn("setseq", 146, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p212.p2122->NN.icode), 1, (char *)(&K->C.p212.p2122->NN.icode));
	BROWSE_print_argument("icode", 'I', "regelem", 144);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p212.p2122->prodnum])(K->C.p212.p2122);
	BROWSE_print_sohn("closebracksy", 147, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p213(K)
struct g1regelem *K;
/* p213 : regelem -> notsy openbracksy setseq closebracksy  */

{
	BROWSE_print_vater("regelem", 148);
	BROWSE_print_attribut("chse", 'A', "CHARSET", sizeof(K->NN.chse), 0, (char *)(&K->NN.chse));
	BROWSE_print_funktion("ComplSet", 34);
	BROWSE_print_argument("chse", 'A', "regelem", 148);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dset", 'D', "setseq", 151);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("SSetToAut", 47);
	BROWSE_print_argument("dautom", 'D', "regelem", 148);
	BROWSE_print_end_attr();

	BROWSE_print_argument("chse", 'A', "regelem", 148);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "setseq", 151);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("notsy", 149, 1);
	BROWSE_print_sohn("openbracksy", 150, 1);
	BROWSE_print_sohn("setseq", 151, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p213.p2133->NN.icode), 1, (char *)(&K->C.p213.p2133->NN.icode));
	BROWSE_print_argument("icode", 'I', "regelem", 148);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p213.p2133->prodnum])(K->C.p213.p2133);
	BROWSE_print_sohn("closebracksy", 152, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p214(K)
struct g1regelem *K;
/* p214 : regelem -> openpsy regexpr closepsy  */

{
	BROWSE_print_vater("regelem", 153);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 1, (char *)(&K->NN.dautom));
	BROWSE_print_argument("dautom", 'D', "regexpr", 155);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "regexpr", 155);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("openpsy", 154, 1);
	BROWSE_print_sohn("regexpr", 155, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p214.p2142->NN.icode), 1, (char *)(&K->C.p214.p2142->NN.icode));
	BROWSE_print_argument("icode", 'I', "regelem", 153);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p214.p2142->prodnum])(K->C.p214.p2142);
	BROWSE_print_sohn("closepsy", 156, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p215(K)
struct g1regelem *K;
/* p215 : regelem -> IDENT  */

{
	BROWSE_print_vater("regelem", 157);
	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("ExpndLexMak", 48);
	BROWSE_print_argument("aubo", 'A', "regelem", 157);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "regelem", 157);
	BROWSE_print_argument(NULL, ' ', "IDENT", 158);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "regelem", 157);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regelem", 157);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "regelem", 157);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regelem", 157);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("IDENT", 158, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p216(K)
struct g1regelem *K;
/* p216 : regelem -> allbutsy openpsy regexpr closepsy  */

{
	BROWSE_print_vater("regelem", 159);
	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("SAllbut", 49);
	BROWSE_print_argument("aubo", 'A', "regelem", 159);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dautom", 'D', "regexpr", 162);
	BROWSE_print_argument("dcode", 'D', "regexpr", 162);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "regelem", 159);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regelem", 159);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "regelem", 159);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regelem", 159);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("allbutsy", 160, 1);
	BROWSE_print_sohn("openpsy", 161, 1);
	BROWSE_print_sohn("regexpr", 162, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p216.p2163->NN.icode), 1, (char *)(&K->C.p216.p2163->NN.icode));
	BROWSE_print_argument("icode", 'I', "regelem", 159);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p216.p2163->prodnum])(K->C.p216.p2163);
	BROWSE_print_sohn("closepsy", 163, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p171(K)
struct g1regexpr *K;
/* p171 : regexpr -> regexpr barsy regterm  */

{
	BROWSE_print_vater("regexpr", 110);
	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("SAlternative", 32);
	BROWSE_print_argument("aubo", 'A', "regexpr", 110);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dautom", 'D', "regexpr", 111);
	BROWSE_print_argument("dautom", 'D', "regterm", 113);
	BROWSE_print_argument("dcode", 'D', "regterm", 113);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "regexpr", 110);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regexpr", 110);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "regexpr", 110);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regexpr", 110);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("regexpr", 111, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p171.p1711->NN.icode), 1, (char *)(&K->C.p171.p1711->NN.icode));
	BROWSE_print_argument("icode", 'I', "regexpr", 110);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p171.p1711->prodnum])(K->C.p171.p1711);
	BROWSE_print_sohn("barsy", 112, 1);
	BROWSE_print_sohn("regterm", 113, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p171.p1713->NN.icode), 1, (char *)(&K->C.p171.p1713->NN.icode));
	BROWSE_print_argument("dcode", 'D', "regexpr", 111);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p171.p1713->prodnum])(K->C.p171.p1713);
	BROWSE_print_prod_end();
}


void alexisprint_p172(K)
struct g1regexpr *K;
/* p172 : regexpr -> regterm  */

{
	BROWSE_print_vater("regexpr", 114);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 1, (char *)(&K->NN.dautom));
	BROWSE_print_argument("dautom", 'D', "regterm", 115);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "regterm", 115);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("regterm", 115, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p172.p1721->NN.icode), 1, (char *)(&K->C.p172.p1721->NN.icode));
	BROWSE_print_argument("icode", 'I', "regexpr", 114);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p172.p1721->prodnum])(K->C.p172.p1721);
	BROWSE_print_prod_end();
}


void alexisprint_p191(K)
struct g1regfaktor *K;
/* p191 : regfaktor -> regelem REGOP  */

{
	BROWSE_print_vater("regfaktor", 121);
	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("RegOperator", 45);
	BROWSE_print_argument("aubo", 'A', "regfaktor", 121);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dautom", 'D', "regelem", 122);
	BROWSE_print_argument(NULL, ' ', "REGOP", 123);
	BROWSE_print_argument("dcode", 'D', "regelem", 122);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "regfaktor", 121);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regfaktor", 121);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "regfaktor", 121);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regfaktor", 121);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("regelem", 122, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p191.p1911->NN.icode), 1, (char *)(&K->C.p191.p1911->NN.icode));
	BROWSE_print_argument("icode", 'I', "regfaktor", 121);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p191.p1911->prodnum])(K->C.p191.p1911);
	BROWSE_print_sohn("REGOP", 123, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p192(K)
struct g1regfaktor *K;
/* p192 : regfaktor -> regelem numbersy times  */

{
	BROWSE_print_vater("regfaktor", 124);
	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("SMultiply", 42);
	BROWSE_print_argument("aubo", 'A', "regfaktor", 124);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dcode", 'D', "regelem", 125);
	BROWSE_print_argument("dautom", 'D', "regelem", 125);
	BROWSE_print_argument("dug", 'D', "times", 127);
	BROWSE_print_argument("dog", 'D', "times", 127);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "regfaktor", 124);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regfaktor", 124);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "regfaktor", 124);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regfaktor", 124);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("regelem", 125, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p192.p1921->NN.icode), 1, (char *)(&K->C.p192.p1921->NN.icode));
	BROWSE_print_argument("icode", 'I', "regfaktor", 124);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p192.p1921->prodnum])(K->C.p192.p1921);
	BROWSE_print_sohn("numbersy", 126, 1);
	BROWSE_print_sohn("times", 127, 0);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p192.p1923->prodnum])(K->C.p192.p1923);
	BROWSE_print_prod_end();
}


void alexisprint_p193(K)
struct g1regfaktor *K;
/* p193 : regfaktor -> regelem  */

{
	BROWSE_print_vater("regfaktor", 128);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 1, (char *)(&K->NN.dautom));
	BROWSE_print_argument("dautom", 'D', "regelem", 129);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "regelem", 129);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("regelem", 129, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p193.p1931->NN.icode), 1, (char *)(&K->C.p193.p1931->NN.icode));
	BROWSE_print_argument("icode", 'I', "regfaktor", 128);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p193.p1931->prodnum])(K->C.p193.p1931);
	BROWSE_print_prod_end();
}


void alexisprint_p181(K)
struct g1regterm *K;
/* p181 : regterm -> regterm regfaktor  */

{
	BROWSE_print_vater("regterm", 116);
	BROWSE_print_attribut("aubo", 'A', "AUTBOOL", sizeof(K->NN.aubo), 0, (char *)(&K->NN.aubo));
	BROWSE_print_funktion("SConcat", 41);
	BROWSE_print_argument("aubo", 'A', "regterm", 116);
	BROWSE_print_end_attr();

	BROWSE_print_argument("dautom", 'D', "regterm", 117);
	BROWSE_print_argument("dautom", 'D', "regfaktor", 118);
	BROWSE_print_argument("dcode", 'D', "regfaktor", 118);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 0, (char *)(&K->NN.dautom));
	BROWSE_print_funktion("autbo2aut", 11);
	BROWSE_print_argument("dautom", 'D', "regterm", 116);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regterm", 116);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("autbo2bool", 12);
	BROWSE_print_argument("dcode", 'D', "regterm", 116);
	BROWSE_print_end_attr();

	BROWSE_print_argument("aubo", 'A', "regterm", 116);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("regterm", 117, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p181.p1811->NN.icode), 1, (char *)(&K->C.p181.p1811->NN.icode));
	BROWSE_print_argument("icode", 'I', "regterm", 116);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p181.p1811->prodnum])(K->C.p181.p1811);
	BROWSE_print_sohn("regfaktor", 118, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p181.p1812->NN.icode), 1, (char *)(&K->C.p181.p1812->NN.icode));
	BROWSE_print_argument("dcode", 'D', "regterm", 117);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p181.p1812->prodnum])(K->C.p181.p1812);
	BROWSE_print_prod_end();
}


void alexisprint_p182(K)
struct g1regterm *K;
/* p182 : regterm -> regfaktor  */

{
	BROWSE_print_vater("regterm", 119);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dautom", 'D', "AUTOMAT", sizeof(K->NN.dautom), 1, (char *)(&K->NN.dautom));
	BROWSE_print_argument("dautom", 'D', "regfaktor", 120);
	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "regfaktor", 120);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("regfaktor", 120, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p182.p1821->NN.icode), 1, (char *)(&K->C.p182.p1821->NN.icode));
	BROWSE_print_argument("icode", 'I', "regterm", 119);
	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p182.p1821->prodnum])(K->C.p182.p1821);
	BROWSE_print_prod_end();
}


void alexisprint_p231(K)
struct g1setseq *K;
/* p231 : setseq -> STRINGSY  */

{
	BROWSE_print_vater("setseq", 164);
	BROWSE_print_attribut("chbo", 'A', "CHARBOOL", sizeof(K->NN.chbo), 0, (char *)(&K->NN.chbo));
	BROWSE_print_funktion("makeset", 50);
	BROWSE_print_argument("chbo", 'A', "setseq", 164);
	BROWSE_print_end_attr();

	BROWSE_print_argument(NULL, ' ', "STRINGSY", 165);
	BROWSE_print_argument(NULL, ' ', "STRINGSY", 165);
	BROWSE_print_argument("icode", 'I', "setseq", 164);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dset", 'D', "CHARSET", sizeof(K->NN.dset), 0, (char *)(&K->NN.dset));
	BROWSE_print_funktion("charbo2char", 17);
	BROWSE_print_argument("dset", 'D', "setseq", 164);
	BROWSE_print_end_attr();

	BROWSE_print_argument("chbo", 'A', "setseq", 164);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("charbo2bool", 18);
	BROWSE_print_argument("dcode", 'D', "setseq", 164);
	BROWSE_print_end_attr();

	BROWSE_print_argument("chbo", 'A', "setseq", 164);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("STRINGSY", 165, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p232(K)
struct g1setseq *K;
/* p232 : setseq -> STRINGSY commasy setseq  */

{
	BROWSE_print_vater("setseq", 166);
	BROWSE_print_attribut("set", 'A', "CHARSET", sizeof(K->NN.set), 0, (char *)(&K->NN.set));
	BROWSE_print_funktion("charbo2char", 17);
	BROWSE_print_argument("set", 'A', "setseq", 166);
	BROWSE_print_end_attr();

	BROWSE_print_argument("chbo", 'A', "setseq", 166);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("chbo", 'A', "CHARBOOL", sizeof(K->NN.chbo), 0, (char *)(&K->NN.chbo));
	BROWSE_print_funktion("makeset", 50);
	BROWSE_print_argument("chbo", 'A', "setseq", 166);
	BROWSE_print_end_attr();

	BROWSE_print_argument(NULL, ' ', "STRINGSY", 167);
	BROWSE_print_argument(NULL, ' ', "STRINGSY", 167);
	BROWSE_print_argument("icode", 'I', "setseq", 166);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dset", 'D', "CHARSET", sizeof(K->NN.dset), 0, (char *)(&K->NN.dset));
	BROWSE_print_funktion("union_sets", 51);
	BROWSE_print_argument("dset", 'D', "setseq", 166);
	BROWSE_print_end_attr();

	BROWSE_print_argument("set", 'A', "setseq", 166);
	BROWSE_print_argument("dset", 'D', "setseq", 169);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "setseq", 169);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("STRINGSY", 167, 1);
	BROWSE_print_sohn("commasy", 168, 1);
	BROWSE_print_sohn("setseq", 169, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p232.p2323->NN.icode), 0, (char *)(&K->C.p232.p2323->NN.icode));
	BROWSE_print_funktion("charbo2bool", 18);
	BROWSE_print_argument("icode", 'I', "setseq", 169);
	BROWSE_print_end_attr();

	BROWSE_print_argument("chbo", 'A', "setseq", 166);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p232.p2323->prodnum])(K->C.p232.p2323);
	BROWSE_print_prod_end();
}


void alexisprint_p233(K)
struct g1setseq *K;
/* p233 : setseq -> STRINGSY doubledotsy STRINGSY  */

{
	BROWSE_print_vater("setseq", 170);
	BROWSE_print_attribut("chbo", 'A', "CHARBOOL", sizeof(K->NN.chbo), 0, (char *)(&K->NN.chbo));
	BROWSE_print_funktion("makeset", 50);
	BROWSE_print_argument("chbo", 'A', "setseq", 170);
	BROWSE_print_end_attr();

	BROWSE_print_argument(NULL, ' ', "STRINGSY", 171);
	BROWSE_print_argument(NULL, ' ', "STRINGSY", 173);
	BROWSE_print_argument("icode", 'I', "setseq", 170);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dset", 'D', "CHARSET", sizeof(K->NN.dset), 0, (char *)(&K->NN.dset));
	BROWSE_print_funktion("charbo2char", 17);
	BROWSE_print_argument("dset", 'D', "setseq", 170);
	BROWSE_print_end_attr();

	BROWSE_print_argument("chbo", 'A', "setseq", 170);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("charbo2bool", 18);
	BROWSE_print_argument("dcode", 'D', "setseq", 170);
	BROWSE_print_end_attr();

	BROWSE_print_argument("chbo", 'A', "setseq", 170);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("STRINGSY", 171, 1);
	BROWSE_print_sohn("doubledotsy", 172, 1);
	BROWSE_print_sohn("STRINGSY", 173, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p234(K)
struct g1setseq *K;
/* p234 : setseq -> STRINGSY doubledotsy STRINGSY commasy setseq  */

{
	BROWSE_print_vater("setseq", 174);
	BROWSE_print_attribut("set", 'A', "CHARSET", sizeof(K->NN.set), 0, (char *)(&K->NN.set));
	BROWSE_print_funktion("charbo2char", 17);
	BROWSE_print_argument("set", 'A', "setseq", 174);
	BROWSE_print_end_attr();

	BROWSE_print_argument("chbo", 'A', "setseq", 174);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("chbo", 'A', "CHARBOOL", sizeof(K->NN.chbo), 0, (char *)(&K->NN.chbo));
	BROWSE_print_funktion("makeset", 50);
	BROWSE_print_argument("chbo", 'A', "setseq", 174);
	BROWSE_print_end_attr();

	BROWSE_print_argument(NULL, ' ', "STRINGSY", 175);
	BROWSE_print_argument(NULL, ' ', "STRINGSY", 177);
	BROWSE_print_argument("icode", 'I', "setseq", 174);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dset", 'D', "CHARSET", sizeof(K->NN.dset), 0, (char *)(&K->NN.dset));
	BROWSE_print_funktion("union_sets", 51);
	BROWSE_print_argument("dset", 'D', "setseq", 174);
	BROWSE_print_end_attr();

	BROWSE_print_argument("set", 'A', "setseq", 174);
	BROWSE_print_argument("dset", 'D', "setseq", 179);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 1, (char *)(&K->NN.dcode));
	BROWSE_print_argument("dcode", 'D', "setseq", 179);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("STRINGSY", 175, 1);
	BROWSE_print_sohn("doubledotsy", 176, 1);
	BROWSE_print_sohn("STRINGSY", 177, 1);
	BROWSE_print_sohn("commasy", 178, 1);
	BROWSE_print_sohn("setseq", 179, 0);
	BROWSE_print_attribut("icode", 'I', "BOOL", sizeof(K->C.p234.p2345->NN.icode), 0, (char *)(&K->C.p234.p2345->NN.icode));
	BROWSE_print_funktion("charbo2bool", 18);
	BROWSE_print_argument("icode", 'I', "setseq", 179);
	BROWSE_print_end_attr();

	BROWSE_print_argument("chbo", 'A', "setseq", 174);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	(*alexisBrowseTab[K->C.p234.p2345->prodnum])(K->C.p234.p2345);
	BROWSE_print_prod_end();
}


void alexisprint_p91(K)
struct g1specialact *K;
/* p91 : specialact -> SPECIALSY PROGSTRINGSY  */

{
	BROWSE_print_vater("specialact", 55);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dcode", 'D', "BOOL", sizeof(K->NN.dcode), 0, (char *)(&K->NN.dcode));
	BROWSE_print_funktion("StoreSpec", 30);
	BROWSE_print_argument("dcode", 'D', "specialact", 55);
	BROWSE_print_end_attr();

	BROWSE_print_argument("icode", 'I', "specialact", 55);
	BROWSE_print_argument(NULL, ' ', "SPECIALSY", 56);
	BROWSE_print_argument(NULL, ' ', "PROGSTRINGSY", 57);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("SPECIALSY", 56, 1);
	BROWSE_print_sohn("PROGSTRINGSY", 57, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p201(K)
struct g1times *K;
/* p201 : times -> INTEGERSY  */

{
	BROWSE_print_vater("times", 130);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dug", 'D', "INTEGERSY", sizeof(K->NN.dug), 1, (char *)(&K->NN.dug));
	BROWSE_print_argument(NULL, ' ', "INTEGERSY", 131);
	BROWSE_print_attribut("dog", 'D', "INTEGERSY", sizeof(K->NN.dog), 1, (char *)(&K->NN.dog));
	BROWSE_print_argument(NULL, ' ', "INTEGERSY", 131);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("INTEGERSY", 131, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p202(K)
struct g1times *K;
/* p202 : times -> INTEGERSY commasy  */

{
	BROWSE_print_vater("times", 132);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dug", 'D', "INTEGERSY", sizeof(K->NN.dug), 1, (char *)(&K->NN.dug));
	BROWSE_print_argument(NULL, ' ', "INTEGERSY", 133);
	BROWSE_print_attribut("dog", 'D', "INTEGERSY", sizeof(K->NN.dog), 0, (char *)(&K->NN.dog));
	BROWSE_print_funktion("GenMOne", 43);
	BROWSE_print_argument("dog", 'D', "times", 132);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_sohn("INTEGERSY", 133, 1);
	BROWSE_print_sohn("commasy", 134, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p203(K)
struct g1times *K;
/* p203 : times -> commasy INTEGERSY  */

{
	BROWSE_print_vater("times", 135);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dug", 'D', "INTEGERSY", sizeof(K->NN.dug), 0, (char *)(&K->NN.dug));
	BROWSE_print_funktion("GenZero", 44);
	BROWSE_print_argument("dug", 'D', "times", 135);
	BROWSE_print_end_attr();

	BROWSE_print_end_attr();

	BROWSE_print_attribut("dog", 'D', "INTEGERSY", sizeof(K->NN.dog), 1, (char *)(&K->NN.dog));
	BROWSE_print_argument(NULL, ' ', "INTEGERSY", 137);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("commasy", 136, 1);
	BROWSE_print_sohn("INTEGERSY", 137, 1);
	BROWSE_print_prod_end();
}


void alexisprint_p204(K)
struct g1times *K;
/* p204 : times -> INTEGERSY commasy INTEGERSY  */

{
	BROWSE_print_vater("times", 138);
	BROWSE_print_end_attr();

	BROWSE_print_attribut("dug", 'D', "INTEGERSY", sizeof(K->NN.dug), 1, (char *)(&K->NN.dug));
	BROWSE_print_argument(NULL, ' ', "INTEGERSY", 139);
	BROWSE_print_attribut("dog", 'D', "INTEGERSY", sizeof(K->NN.dog), 1, (char *)(&K->NN.dog));
	BROWSE_print_argument(NULL, ' ', "INTEGERSY", 141);
	BROWSE_print_end_attr();

	BROWSE_print_sohn("INTEGERSY", 139, 1);
	BROWSE_print_sohn("commasy", 140, 1);
	BROWSE_print_sohn("INTEGERSY", 141, 1);
	BROWSE_print_prod_end();
}

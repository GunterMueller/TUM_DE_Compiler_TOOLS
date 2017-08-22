

              /* Die Programmautomaten */
              /* ===================== */


extern int alexisMUGEXPORT;

#ifndef VOIDPTR_T
#ifdef __STDC__
 typedef void *voidptr;
#else
 typedef char *voidptr;
#endif
#define VOIDPTR_T
#endif



voidptr alexisMUGAUTp1(K,putin)
struct g1scanner *K;
int putin;
/* p1 : scanner -> scannersy IDENT option definitions main  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=1 */
		ScanTrue(&K->NN.hb);
		InitAlexis(K->NN.hb
			,&K->C.p1.p13->NN.icode);
		K->NN.STATE=1;
		alexisMUGEXPORT=3;
		return((voidptr) K->C.p1.p13);
	case 1: /* PUTIN=4 */
		K->C.p1.p14->NN.icode= K->C.p1.p13->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=5;
		return((voidptr) K->C.p1.p14);
	case 2: /* PUTIN=6 */
		K->C.p1.p15->NN.icode= K->C.p1.p14->NN.dcode;
		K->NN.STATE=3;
		alexisMUGEXPORT=7;
		return((voidptr) K->C.p1.p15);
	case 3: /* PUTIN=8 */
		SKompress(K->C.p1.p15->NN.dcode
			,K->C.p1.p15->NN.dautom
			,&K->NN.bck);
		boclko2bool(K->NN.bck
			,&K->NN.coda);
		boclko2kompr(K->NN.bck
			,&K->NN.ko);
		boclko2class(K->NN.bck
			,&K->NN.cd);
		sgentable(K->NN.coda
			,K->NN.ko
			,K->NN.cd
			,&K->NN.hc);
		SGenActions(K->NN.hc
			,&K->NN.dscan);
		K->NN.STATE=4;
		alexisMUGEXPORT=2;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp141(K,putin)
struct g1actionspec *K;
int putin;
/* p141 : actionspec -> IDENT openpsy parlist closepsy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=25 */
		K->C.p141.p1413->NN.icode= K->NN.icode;
		GenEmptPars(&K->C.p141.p1413->NN.ipars);
		IntNull(&K->C.p141.p1413->NN.iparanz);
		K->NN.STATE=1;
		alexisMUGEXPORT=31;
		return((voidptr) K->C.p141.p1413);
	case 1: /* PUTIN=32 */
		DefMakAct(K->C.p141.p1413->NN.dcode
			,K->NN.ignore
			,K->NN.iautom
			,K->C.p141.p1413->NN.dparanz
			,*K->C.p141.p1411
			,K->C.p141.p1413->NN.dpars
			,&K->NN.aubo);
		autbo2aut(K->NN.aubo
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo
			,&K->NN.dcode);
		K->NN.STATE=2;
		alexisMUGEXPORT=26;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp142(K,putin)
struct g1actionspec *K;
int putin;
/* p142 : actionspec -> IDENT  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=25 */
		GenEmptPars(&K->NN.dummy);
		IntNull(&K->NN.null);
		DefMakAct(K->NN.icode
			,K->NN.ignore
			,K->NN.iautom
			,K->NN.null
			,*K->C.p142.p1421
			,K->NN.dummy
			,&K->NN.aubo);
		autbo2aut(K->NN.aubo
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo
			,&K->NN.dcode);
		K->NN.STATE=1;
		alexisMUGEXPORT=26;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp143(K,putin)
struct g1actionspec *K;
int putin;
/* p143 : actionspec -> PROGSTRINGSY  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=25 */
		DefAction(K->NN.icode
			,K->NN.ignore
			,K->NN.iautom
			,*K->C.p143.p1431
			,&K->NN.aubo);
		autbo2aut(K->NN.aubo
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo
			,&K->NN.dcode);
		K->NN.STATE=1;
		alexisMUGEXPORT=26;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp144(K,putin)
struct g1actionspec *K;
int putin;
/* p144 : actionspec ->  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=25 */
		GenEProg(&K->NN.nulp);
		DefAction(K->NN.icode
			,K->NN.ignore
			,K->NN.iautom
			,K->NN.nulp
			,&K->NN.aubo);
		autbo2aut(K->NN.aubo
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo
			,&K->NN.dcode);
		K->NN.STATE=1;
		alexisMUGEXPORT=26;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp41(K,putin)
struct g1definitions *K;
int putin;
/* p41 : definitions -> includesy definitions  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=5 */
		K->C.p41.p412->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=5;
		return((voidptr) K->C.p41.p412);
	case 1: /* PUTIN=6 */
		K->NN.dcode= K->C.p41.p412->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=6;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp42(K,putin)
struct g1definitions *K;
int putin;
/* p42 : definitions -> makros definitions  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=5 */
		K->C.p42.p421->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=11;
		return((voidptr) K->C.p42.p421);
	case 1: /* PUTIN=12 */
		K->C.p42.p422->NN.icode= K->C.p42.p421->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=5;
		return((voidptr) K->C.p42.p422);
	case 2: /* PUTIN=6 */
		K->NN.dcode= K->C.p42.p422->NN.dcode;
		K->NN.STATE=3;
		alexisMUGEXPORT=6;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp43(K,putin)
struct g1definitions *K;
int putin;
/* p43 : definitions -> makroact definitions  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=5 */
		K->C.p43.p431->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=13;
		return((voidptr) K->C.p43.p431);
	case 1: /* PUTIN=14 */
		K->C.p43.p432->NN.icode= K->C.p43.p431->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=5;
		return((voidptr) K->C.p43.p432);
	case 2: /* PUTIN=6 */
		K->NN.dcode= K->C.p43.p432->NN.dcode;
		K->NN.STATE=3;
		alexisMUGEXPORT=6;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp44(K,putin)
struct g1definitions *K;
int putin;
/* p44 : definitions -> specialact definitions  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=5 */
		K->C.p44.p441->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=15;
		return((voidptr) K->C.p44.p441);
	case 1: /* PUTIN=16 */
		K->C.p44.p442->NN.icode= K->C.p44.p441->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=5;
		return((voidptr) K->C.p44.p442);
	case 2: /* PUTIN=6 */
		K->NN.dcode= K->C.p44.p442->NN.dcode;
		K->NN.STATE=3;
		alexisMUGEXPORT=6;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp45(K,putin)
struct g1definitions *K;
int putin;
/* p45 : definitions ->  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=5 */
		K->NN.dcode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=6;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp81(K,putin)
struct g1formparlist *K;
int putin;
/* p81 : formparlist -> FORMPAR  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=27 */
		IPlus1(K->NN.iparanz
			,&K->NN.plusone);
		K->NN.dparanz= K->NN.plusone;
		ChkFormPar(K->NN.icode
			,*K->C.p81.p811
			,K->NN.plusone
			,&K->NN.dcode);
		K->NN.STATE=1;
		alexisMUGEXPORT=28;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp82(K,putin)
struct g1formparlist *K;
int putin;
/* p82 : formparlist -> FORMPAR commasy formparlist  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=27 */
		IPlus1(K->NN.iparanz
			,&K->NN.plusone);
		ChkFormPar(K->NN.icode
			,*K->C.p82.p821
			,K->NN.plusone
			,&K->C.p82.p823->NN.icode);
		K->C.p82.p823->NN.iparanz= K->NN.plusone;
		K->NN.STATE=1;
		alexisMUGEXPORT=27;
		return((voidptr) K->C.p82.p823);
	case 1: /* PUTIN=28 */
		K->NN.dparanz= K->C.p82.p823->NN.dparanz;
		K->NN.dcode= K->C.p82.p823->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=28;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp131(K,putin)
struct g1lexemes *K;
int putin;
/* p131 : lexemes -> ignoresy regexpr arrowsy actionspec semicolonsy lexemes  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=17 */
		K->C.p131.p1312->NN.icode= K->NN.icode;
		SetTrue(&K->C.p131.p1314->NN.ignore);
		K->NN.STATE=1;
		alexisMUGEXPORT=23;
		return((voidptr) K->C.p131.p1312);
	case 1: /* PUTIN=24 */
		K->C.p131.p1314->NN.icode= K->C.p131.p1312->NN.dcode;
		K->C.p131.p1314->NN.iautom= K->C.p131.p1312->NN.dautom;
		K->NN.STATE=2;
		alexisMUGEXPORT=25;
		return((voidptr) K->C.p131.p1314);
	case 2: /* PUTIN=26 */
		SAlternative(K->C.p131.p1314->NN.dautom
			,K->NN.iautom
			,K->C.p131.p1314->NN.dcode
			,&K->NN.aubo);
		autbo2bool(K->NN.aubo
			,&K->C.p131.p1316->NN.icode);
		autbo2aut(K->NN.aubo
			,&K->C.p131.p1316->NN.iautom);
		K->NN.STATE=3;
		alexisMUGEXPORT=17;
		return((voidptr) K->C.p131.p1316);
	case 3: /* PUTIN=18 */
		K->NN.dautom= K->C.p131.p1316->NN.dautom;
		K->NN.dcode= K->C.p131.p1316->NN.dcode;
		K->NN.STATE=4;
		alexisMUGEXPORT=18;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp132(K,putin)
struct g1lexemes *K;
int putin;
/* p132 : lexemes -> regexpr arrowsy actionspec semicolonsy lexemes  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=17 */
		K->C.p132.p1321->NN.icode= K->NN.icode;
		SetFalse(&K->C.p132.p1323->NN.ignore);
		K->NN.STATE=1;
		alexisMUGEXPORT=23;
		return((voidptr) K->C.p132.p1321);
	case 1: /* PUTIN=24 */
		K->C.p132.p1323->NN.icode= K->C.p132.p1321->NN.dcode;
		K->C.p132.p1323->NN.iautom= K->C.p132.p1321->NN.dautom;
		K->NN.STATE=2;
		alexisMUGEXPORT=25;
		return((voidptr) K->C.p132.p1323);
	case 2: /* PUTIN=26 */
		SAlternative(K->C.p132.p1323->NN.dautom
			,K->NN.iautom
			,K->C.p132.p1323->NN.dcode
			,&K->NN.aubo);
		autbo2bool(K->NN.aubo
			,&K->C.p132.p1325->NN.icode);
		autbo2aut(K->NN.aubo
			,&K->C.p132.p1325->NN.iautom);
		K->NN.STATE=3;
		alexisMUGEXPORT=17;
		return((voidptr) K->C.p132.p1325);
	case 3: /* PUTIN=18 */
		K->NN.dautom= K->C.p132.p1325->NN.dautom;
		K->NN.dcode= K->C.p132.p1325->NN.dcode;
		K->NN.STATE=4;
		alexisMUGEXPORT=18;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp133(K,putin)
struct g1lexemes *K;
int putin;
/* p133 : lexemes -> includesy lexemes  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=17 */
		K->C.p133.p1332->NN.icode= K->NN.icode;
		K->C.p133.p1332->NN.iautom= K->NN.iautom;
		K->NN.STATE=1;
		alexisMUGEXPORT=17;
		return((voidptr) K->C.p133.p1332);
	case 1: /* PUTIN=18 */
		K->NN.dautom= K->C.p133.p1332->NN.dautom;
		K->NN.dcode= K->C.p133.p1332->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=18;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp134(K,putin)
struct g1lexemes *K;
int putin;
/* p134 : lexemes ->  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=17 */
		K->NN.dautom= K->NN.iautom;
		K->NN.dcode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=18;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp51(K,putin)
struct g1main *K;
int putin;
/* p51 : main -> lexemessy lexemes lexemesendsy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=7 */
		K->C.p51.p512->NN.icode= K->NN.icode;
		AutomatNil(&K->C.p51.p512->NN.iautom);
		K->NN.STATE=1;
		alexisMUGEXPORT=17;
		return((voidptr) K->C.p51.p512);
	case 1: /* PUTIN=18 */
		DispLexMak(K->C.p51.p512->NN.dautom
			,K->C.p51.p512->NN.dcode
			,&K->NN.aubo1);
		autbo2bool(K->NN.aubo1
			,&K->NN.auxd);
		autbo2aut(K->NN.aubo1
			,&K->NN.dis);
		SMyhill(K->NN.dis
			,K->NN.auxd
			,&K->NN.aubo2);
		autbo2bool(K->NN.aubo2
			,&K->NN.auxc);
		autbo2aut(K->NN.aubo2
			,&K->NN.myh);
		SMinimize(K->NN.myh
			,K->NN.auxc
			,&K->NN.aubo3);
		autbo2aut(K->NN.aubo3
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo3
			,&K->NN.dcode);
		K->NN.STATE=2;
		alexisMUGEXPORT=8;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp61(K,putin)
struct g1makroact *K;
int putin;
/* p61 : makroact -> actionmakrossy makroactseq makroendsy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=13 */
		K->C.p61.p612->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=21;
		return((voidptr) K->C.p61.p612);
	case 1: /* PUTIN=22 */
		K->NN.dcode= K->C.p61.p612->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=14;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp71(K,putin)
struct g1makroactseq *K;
int putin;
/* p71 : makroactseq -> IDENT openpsy formparlist closepsy PROGSTRINGSY makroactseq  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=21 */
		K->C.p71.p713->NN.icode= K->NN.icode;
		IntNull(&K->C.p71.p713->NN.iparanz);
		K->NN.STATE=1;
		alexisMUGEXPORT=27;
		return((voidptr) K->C.p71.p713);
	case 1: /* PUTIN=28 */
		InstActMak(K->C.p71.p713->NN.dcode
			,*K->C.p71.p711
			,K->C.p71.p713->NN.dparanz
			,*K->C.p71.p715
			,&K->C.p71.p716->NN.icode);
		K->NN.STATE=2;
		alexisMUGEXPORT=21;
		return((voidptr) K->C.p71.p716);
	case 2: /* PUTIN=22 */
		K->NN.dcode= K->C.p71.p716->NN.dcode;
		K->NN.STATE=3;
		alexisMUGEXPORT=22;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp72(K,putin)
struct g1makroactseq *K;
int putin;
/* p72 : makroactseq -> IDENT PROGSTRINGSY makroactseq  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=21 */
		IntNull(&K->NN.zero);
		InstActMak(K->NN.icode
			,*K->C.p72.p721
			,K->NN.zero
			,*K->C.p72.p722
			,&K->C.p72.p723->NN.icode);
		K->NN.STATE=1;
		alexisMUGEXPORT=21;
		return((voidptr) K->C.p72.p723);
	case 1: /* PUTIN=22 */
		K->NN.dcode= K->C.p72.p723->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=22;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp73(K,putin)
struct g1makroactseq *K;
int putin;
/* p73 : makroactseq ->  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=21 */
		K->NN.dcode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=22;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp120(K,putin)
struct g1makrolexemes *K;
int putin;
/* p120 : makrolexemes -> IDENT equalsy regexpr semicolonsy makrolexemes  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=19 */
		K->C.p120.p1203->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=23;
		return((voidptr) K->C.p120.p1203);
	case 1: /* PUTIN=24 */
		InstLexMak(K->C.p120.p1203->NN.dcode
			,*K->C.p120.p1201
			,K->C.p120.p1203->NN.dautom
			,&K->C.p120.p1205->NN.icode);
		K->NN.STATE=2;
		alexisMUGEXPORT=19;
		return((voidptr) K->C.p120.p1205);
	case 2: /* PUTIN=20 */
		K->NN.dcode= K->C.p120.p1205->NN.dcode;
		K->NN.STATE=3;
		alexisMUGEXPORT=20;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp121(K,putin)
struct g1makrolexemes *K;
int putin;
/* p121 : makrolexemes -> IDENT equalsy regexpr semicolonsy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=19 */
		K->C.p121.p1213->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=23;
		return((voidptr) K->C.p121.p1213);
	case 1: /* PUTIN=24 */
		InstLexMak(K->C.p121.p1213->NN.dcode
			,*K->C.p121.p1211
			,K->C.p121.p1213->NN.dautom
			,&K->NN.dcode);
		K->NN.STATE=2;
		alexisMUGEXPORT=20;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp111(K,putin)
struct g1makros *K;
int putin;
/* p111 : makros -> lexmakrossy makrolexemes makroendsy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=11 */
		K->C.p111.p1112->NN.icode= K->NN.icode;
		K->NN.dcode= K->C.p111.p1112->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=19;
		return((voidptr) K->C.p111.p1112);
	case 1: /* PUTIN=20 */
		K->NN.STATE=2;
		alexisMUGEXPORT=12;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp21(K,putin)
struct g1option *K;
int putin;
/* p21 : option -> optionssy optionseq optionendsy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=3 */
		K->C.p21.p212->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=9;
		return((voidptr) K->C.p21.p212);
	case 1: /* PUTIN=10 */
		K->NN.dcode= K->C.p21.p212->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=4;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp22(K,putin)
struct g1option *K;
int putin;
/* p22 : option ->  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=3 */
		K->NN.dcode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=4;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp31(K,putin)
struct g1optionseq *K;
int putin;
/* p31 : optionseq -> INSTRUCTSY optionseq  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=9 */
		SetInstFl(K->NN.icode
			,*K->C.p31.p311
			,&K->C.p31.p312->NN.icode);
		K->NN.STATE=1;
		alexisMUGEXPORT=9;
		return((voidptr) K->C.p31.p312);
	case 1: /* PUTIN=10 */
		K->NN.dcode= K->C.p31.p312->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=10;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp32(K,putin)
struct g1optionseq *K;
int putin;
/* p32 : optionseq ->  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=9 */
		K->NN.dcode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=10;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp161(K,putin)
struct g1par *K;
int putin;
/* p161 : par -> INTEGERSY  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=35 */
		SemIntToStr(*K->C.p161.p1611
			,&K->NN.dint);
		intort2i(K->NN.dint
			,&K->NN.dpar);
		intort2o(K->NN.dint
			,&K->NN.ort);
		K->NN.STATE=1;
		alexisMUGEXPORT=36;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp162(K,putin)
struct g1par *K;
int putin;
/* p162 : par -> STRINGSY  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=35 */
		SemStrToStr(*K->C.p162.p1621
			,&K->NN.dint);
		intort2i(K->NN.dint
			,&K->NN.dpar);
		intort2o(K->NN.dint
			,&K->NN.ort);
		K->NN.STATE=1;
		alexisMUGEXPORT=36;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp151(K,putin)
struct g1parlist *K;
int putin;
/* p151 : parlist -> par  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=31 */
		IPlus1(K->NN.iparanz
			,&K->NN.plusone);
		K->NN.dparanz= K->NN.plusone;
		K->NN.STATE=1;
		alexisMUGEXPORT=35;
		return((voidptr) K->C.p151.p1511);
	case 1: /* PUTIN=36 */
		InsParam(K->NN.icode
			,K->C.p151.p1511->NN.dpar
			,K->NN.ipars
			,K->NN.plusone
			,K->C.p151.p1511->NN.ort
			,&K->NN.bopa);
		bopar2par(K->NN.bopa
			,&K->NN.dpars);
		bopar2bool(K->NN.bopa
			,&K->NN.dcode);
		K->NN.STATE=2;
		alexisMUGEXPORT=32;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp152(K,putin)
struct g1parlist *K;
int putin;
/* p152 : parlist -> par commasy parlist  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=31 */
		IPlus1(K->NN.iparanz
			,&K->NN.plusone);
		K->C.p152.p1523->NN.iparanz= K->NN.plusone;
		K->NN.STATE=1;
		alexisMUGEXPORT=35;
		return((voidptr) K->C.p152.p1521);
	case 1: /* PUTIN=36 */
		InsParam(K->NN.icode
			,K->C.p152.p1521->NN.dpar
			,K->NN.ipars
			,K->NN.plusone
			,K->C.p152.p1521->NN.ort
			,&K->NN.bopa);
		bopar2bool(K->NN.bopa
			,&K->C.p152.p1523->NN.icode);
		bopar2par(K->NN.bopa
			,&K->C.p152.p1523->NN.ipars);
		K->NN.STATE=2;
		alexisMUGEXPORT=31;
		return((voidptr) K->C.p152.p1523);
	case 2: /* PUTIN=32 */
		K->NN.dpars= K->C.p152.p1523->NN.dpars;
		K->NN.dparanz= K->C.p152.p1523->NN.dparanz;
		K->NN.dcode= K->C.p152.p1523->NN.dcode;
		K->NN.STATE=3;
		alexisMUGEXPORT=32;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp211(K,putin)
struct g1regelem *K;
int putin;
/* p211 : regelem -> STRINGSY  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=37 */
		SStrToAut(*K->C.p211.p2111
			,&K->NN.dautom);
		K->NN.dcode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=38;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp212(K,putin)
struct g1regelem *K;
int putin;
/* p212 : regelem -> openbracksy setseq closebracksy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=37 */
		K->C.p212.p2122->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=41;
		return((voidptr) K->C.p212.p2122);
	case 1: /* PUTIN=42 */
		SSetToAut(K->C.p212.p2122->NN.dset
			,&K->NN.dautom);
		K->NN.dcode= K->C.p212.p2122->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=38;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp213(K,putin)
struct g1regelem *K;
int putin;
/* p213 : regelem -> notsy openbracksy setseq closebracksy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=37 */
		K->C.p213.p2133->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=41;
		return((voidptr) K->C.p213.p2133);
	case 1: /* PUTIN=42 */
		K->NN.dcode= K->C.p213.p2133->NN.dcode;
		ComplSet(K->C.p213.p2133->NN.dset
			,&K->NN.chse);
		SSetToAut(K->NN.chse
			,&K->NN.dautom);
		K->NN.STATE=2;
		alexisMUGEXPORT=38;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp214(K,putin)
struct g1regelem *K;
int putin;
/* p214 : regelem -> openpsy regexpr closepsy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=37 */
		K->C.p214.p2142->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=23;
		return((voidptr) K->C.p214.p2142);
	case 1: /* PUTIN=24 */
		K->NN.dautom= K->C.p214.p2142->NN.dautom;
		K->NN.dcode= K->C.p214.p2142->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=38;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp215(K,putin)
struct g1regelem *K;
int putin;
/* p215 : regelem -> IDENT  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=37 */
		ExpndLexMak(K->NN.icode
			,*K->C.p215.p2151
			,&K->NN.aubo);
		autbo2aut(K->NN.aubo
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo
			,&K->NN.dcode);
		K->NN.STATE=1;
		alexisMUGEXPORT=38;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp216(K,putin)
struct g1regelem *K;
int putin;
/* p216 : regelem -> allbutsy openpsy regexpr closepsy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=37 */
		K->C.p216.p2163->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=23;
		return((voidptr) K->C.p216.p2163);
	case 1: /* PUTIN=24 */
		SAllbut(K->C.p216.p2163->NN.dautom
			,K->C.p216.p2163->NN.dcode
			,&K->NN.aubo);
		autbo2aut(K->NN.aubo
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo
			,&K->NN.dcode);
		K->NN.STATE=2;
		alexisMUGEXPORT=38;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp171(K,putin)
struct g1regexpr *K;
int putin;
/* p171 : regexpr -> regexpr barsy regterm  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=23 */
		K->C.p171.p1711->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=23;
		return((voidptr) K->C.p171.p1711);
	case 1: /* PUTIN=24 */
		K->C.p171.p1713->NN.icode= K->C.p171.p1711->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=29;
		return((voidptr) K->C.p171.p1713);
	case 2: /* PUTIN=30 */
		SAlternative(K->C.p171.p1711->NN.dautom
			,K->C.p171.p1713->NN.dautom
			,K->C.p171.p1713->NN.dcode
			,&K->NN.aubo);
		autbo2aut(K->NN.aubo
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo
			,&K->NN.dcode);
		K->NN.STATE=3;
		alexisMUGEXPORT=24;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp172(K,putin)
struct g1regexpr *K;
int putin;
/* p172 : regexpr -> regterm  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=23 */
		K->C.p172.p1721->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=29;
		return((voidptr) K->C.p172.p1721);
	case 1: /* PUTIN=30 */
		K->NN.dautom= K->C.p172.p1721->NN.dautom;
		K->NN.dcode= K->C.p172.p1721->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=24;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp191(K,putin)
struct g1regfaktor *K;
int putin;
/* p191 : regfaktor -> regelem REGOP  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=33 */
		K->C.p191.p1911->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=37;
		return((voidptr) K->C.p191.p1911);
	case 1: /* PUTIN=38 */
		RegOperator(K->C.p191.p1911->NN.dautom
			,*K->C.p191.p1912
			,K->C.p191.p1911->NN.dcode
			,&K->NN.aubo);
		autbo2aut(K->NN.aubo
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo
			,&K->NN.dcode);
		K->NN.STATE=2;
		alexisMUGEXPORT=34;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp192(K,putin)
struct g1regfaktor *K;
int putin;
/* p192 : regfaktor -> regelem numbersy times  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=33 */
		K->C.p192.p1921->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=37;
		return((voidptr) K->C.p192.p1921);
	case 1: /* PUTIN=38 */
		K->NN.STATE=2;
		alexisMUGEXPORT=39;
		return((voidptr) K->C.p192.p1923);
	case 2: /* PUTIN=40 */
		SMultiply(K->C.p192.p1921->NN.dcode
			,K->C.p192.p1921->NN.dautom
			,K->C.p192.p1923->NN.dug
			,K->C.p192.p1923->NN.dog
			,&K->NN.aubo);
		autbo2aut(K->NN.aubo
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo
			,&K->NN.dcode);
		K->NN.STATE=3;
		alexisMUGEXPORT=34;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp193(K,putin)
struct g1regfaktor *K;
int putin;
/* p193 : regfaktor -> regelem  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=33 */
		K->C.p193.p1931->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=37;
		return((voidptr) K->C.p193.p1931);
	case 1: /* PUTIN=38 */
		K->NN.dautom= K->C.p193.p1931->NN.dautom;
		K->NN.dcode= K->C.p193.p1931->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=34;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp181(K,putin)
struct g1regterm *K;
int putin;
/* p181 : regterm -> regterm regfaktor  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=29 */
		K->C.p181.p1811->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=29;
		return((voidptr) K->C.p181.p1811);
	case 1: /* PUTIN=30 */
		K->C.p181.p1812->NN.icode= K->C.p181.p1811->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=33;
		return((voidptr) K->C.p181.p1812);
	case 2: /* PUTIN=34 */
		SConcat(K->C.p181.p1811->NN.dautom
			,K->C.p181.p1812->NN.dautom
			,K->C.p181.p1812->NN.dcode
			,&K->NN.aubo);
		autbo2aut(K->NN.aubo
			,&K->NN.dautom);
		autbo2bool(K->NN.aubo
			,&K->NN.dcode);
		K->NN.STATE=3;
		alexisMUGEXPORT=30;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp182(K,putin)
struct g1regterm *K;
int putin;
/* p182 : regterm -> regfaktor  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=29 */
		K->C.p182.p1821->NN.icode= K->NN.icode;
		K->NN.STATE=1;
		alexisMUGEXPORT=33;
		return((voidptr) K->C.p182.p1821);
	case 1: /* PUTIN=34 */
		K->NN.dautom= K->C.p182.p1821->NN.dautom;
		K->NN.dcode= K->C.p182.p1821->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=30;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp231(K,putin)
struct g1setseq *K;
int putin;
/* p231 : setseq -> STRINGSY  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=41 */
		makeset(*K->C.p231.p2311
			,*K->C.p231.p2311
			,K->NN.icode
			,&K->NN.chbo);
		charbo2char(K->NN.chbo
			,&K->NN.dset);
		charbo2bool(K->NN.chbo
			,&K->NN.dcode);
		K->NN.STATE=1;
		alexisMUGEXPORT=42;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp232(K,putin)
struct g1setseq *K;
int putin;
/* p232 : setseq -> STRINGSY commasy setseq  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=41 */
		makeset(*K->C.p232.p2321
			,*K->C.p232.p2321
			,K->NN.icode
			,&K->NN.chbo);
		charbo2bool(K->NN.chbo
			,&K->C.p232.p2323->NN.icode);
		charbo2char(K->NN.chbo
			,&K->NN.set);
		K->NN.STATE=1;
		alexisMUGEXPORT=41;
		return((voidptr) K->C.p232.p2323);
	case 1: /* PUTIN=42 */
		union_sets(K->NN.set
			,K->C.p232.p2323->NN.dset
			,&K->NN.dset);
		K->NN.dcode= K->C.p232.p2323->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=42;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp233(K,putin)
struct g1setseq *K;
int putin;
/* p233 : setseq -> STRINGSY doubledotsy STRINGSY  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=41 */
		makeset(*K->C.p233.p2331
			,*K->C.p233.p2333
			,K->NN.icode
			,&K->NN.chbo);
		charbo2char(K->NN.chbo
			,&K->NN.dset);
		charbo2bool(K->NN.chbo
			,&K->NN.dcode);
		K->NN.STATE=1;
		alexisMUGEXPORT=42;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp234(K,putin)
struct g1setseq *K;
int putin;
/* p234 : setseq -> STRINGSY doubledotsy STRINGSY commasy setseq  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=41 */
		makeset(*K->C.p234.p2341
			,*K->C.p234.p2343
			,K->NN.icode
			,&K->NN.chbo);
		charbo2bool(K->NN.chbo
			,&K->C.p234.p2345->NN.icode);
		charbo2char(K->NN.chbo
			,&K->NN.set);
		K->NN.STATE=1;
		alexisMUGEXPORT=41;
		return((voidptr) K->C.p234.p2345);
	case 1: /* PUTIN=42 */
		union_sets(K->NN.set
			,K->C.p234.p2345->NN.dset
			,&K->NN.dset);
		K->NN.dcode= K->C.p234.p2345->NN.dcode;
		K->NN.STATE=2;
		alexisMUGEXPORT=42;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp91(K,putin)
struct g1specialact *K;
int putin;
/* p91 : specialact -> SPECIALSY PROGSTRINGSY  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=15 */
		StoreSpec(K->NN.icode
			,*K->C.p91.p911
			,*K->C.p91.p912
			,&K->NN.dcode);
		K->NN.STATE=1;
		alexisMUGEXPORT=16;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp201(K,putin)
struct g1times *K;
int putin;
/* p201 : times -> INTEGERSY  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=39 */
		K->NN.dug= *K->C.p201.p2011;
		K->NN.dog= *K->C.p201.p2011;
		K->NN.STATE=1;
		alexisMUGEXPORT=40;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp202(K,putin)
struct g1times *K;
int putin;
/* p202 : times -> INTEGERSY commasy  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=39 */
		K->NN.dug= *K->C.p202.p2021;
		GenMOne(&K->NN.dog);
		K->NN.STATE=1;
		alexisMUGEXPORT=40;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp203(K,putin)
struct g1times *K;
int putin;
/* p203 : times -> commasy INTEGERSY  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=39 */
		GenZero(&K->NN.dug);
		K->NN.dog= *K->C.p203.p2032;
		K->NN.STATE=1;
		alexisMUGEXPORT=40;
		return((voidptr) 0L);
	}
}


voidptr alexisMUGAUTp204(K,putin)
struct g1times *K;
int putin;
/* p204 : times -> INTEGERSY commasy INTEGERSY  */

{
	switch (K->NN.STATE)
	{
	case 0: /* PUTIN=39 */
		K->NN.dug= *K->C.p204.p2041;
		K->NN.dog= *K->C.p204.p2043;
		K->NN.STATE=1;
		alexisMUGEXPORT=40;
		return((voidptr) 0L);
	}
}

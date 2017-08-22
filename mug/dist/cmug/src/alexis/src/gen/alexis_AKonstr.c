          /* Analyse Konstruktoren der Phase alexis */
          /* =============================== */

#define MUGCMaxSt 10000
#define MUGAnzT 32
#define MUGCMinT 0
#define MUGCMinP 1

struct MUGStEntry {
	int MUGElem;
	int *MUGEntry;
};

struct MUGStEntry *MUGSt,MUGHStEntry;
int MUGStTop;
char MUGAccepted;
int MUGErrNum;
int MUGRCode,MUGCode,MUGZl,MUGSp;

int *ALLOC(size)
int size;
{
	int *p;
	if ((p=(int *)calloc(size,1))==NULL)
		printf("Speicher ist voll !\n"),exit(1);
	else return(p);
}

MUGPop(MUGOut)
struct MUGStEntry *MUGOut;
{
	if (MUGStTop>=0)
		*MUGOut=MUGSt[MUGStTop--];
}

MUGInitSt()
{
	MUGStTop=0;
	MUGSt=(struct MUGStEntry *)ALLOC(MUGCMaxSt*sizeof(struct MUGStEntry));
}

MUGPush(MUGIn)
struct MUGStEntry *MUGIn;
{
	if (MUGStTop<MUGCMaxSt)
		MUGSt[++MUGStTop]=(*MUGIn);
	else MUGErrNum=2;
}

MUGT11(MUGHStEntry)
struct MUGStEntry *MUGHStEntry;
{
	FORMPAR *MUGEntry;
	MUGHStEntry->MUGElem=11;
	MUGEntry=(FORMPAR *)ALLOC(sizeof(FORMPAR));
#ifdef READpr
	READFORMPAR(MUGRCode,MUGCode,MUGZl,MUGSp,MUGEntry);
#else
	readFORMPAR(MUGToken,MUGEntry);
#endif
	MUGHStEntry->MUGEntry=(int *)MUGEntry;
	MUGPush(MUGHStEntry);
}

MUGT12(MUGHStEntry)
struct MUGStEntry *MUGHStEntry;
{
	IDENT *MUGEntry;
	MUGHStEntry->MUGElem=12;
	MUGEntry=(IDENT *)ALLOC(sizeof(IDENT));
#ifdef READpr
	READIDENT(MUGRCode,MUGCode,MUGZl,MUGSp,MUGEntry);
#else
	readIDENT(MUGToken,MUGEntry);
#endif
	MUGHStEntry->MUGEntry=(int *)MUGEntry;
	MUGPush(MUGHStEntry);
}

MUGT15(MUGHStEntry)
struct MUGStEntry *MUGHStEntry;
{
	INSTRUCTSY *MUGEntry;
	MUGHStEntry->MUGElem=15;
	MUGEntry=(INSTRUCTSY *)ALLOC(sizeof(INSTRUCTSY));
#ifdef READpr
	READINSTRUCTSY(MUGRCode,MUGCode,MUGZl,MUGSp,MUGEntry);
#else
	readINSTRUCTSY(MUGToken,MUGEntry);
#endif
	MUGHStEntry->MUGEntry=(int *)MUGEntry;
	MUGPush(MUGHStEntry);
}

MUGT16(MUGHStEntry)
struct MUGStEntry *MUGHStEntry;
{
	INTEGERSY *MUGEntry;
	MUGHStEntry->MUGElem=16;
	MUGEntry=(INTEGERSY *)ALLOC(sizeof(INTEGERSY));
#ifdef READpr
	READINTEGERSY(MUGRCode,MUGCode,MUGZl,MUGSp,MUGEntry);
#else
	readINTEGERSY(MUGToken,MUGEntry);
#endif
	MUGHStEntry->MUGEntry=(int *)MUGEntry;
	MUGPush(MUGHStEntry);
}

MUGT27(MUGHStEntry)
struct MUGStEntry *MUGHStEntry;
{
	PROGSTRINGSY *MUGEntry;
	MUGHStEntry->MUGElem=27;
	MUGEntry=(PROGSTRINGSY *)ALLOC(sizeof(PROGSTRINGSY));
#ifdef READpr
	READPROGSTRINGSY(MUGRCode,MUGCode,MUGZl,MUGSp,MUGEntry);
#else
	readPROGSTRINGSY(MUGToken,MUGEntry);
#endif
	MUGHStEntry->MUGEntry=(int *)MUGEntry;
	MUGPush(MUGHStEntry);
}

MUGT28(MUGHStEntry)
struct MUGStEntry *MUGHStEntry;
{
	REGOP *MUGEntry;
	MUGHStEntry->MUGElem=28;
	MUGEntry=(REGOP *)ALLOC(sizeof(REGOP));
#ifdef READpr
	READREGOP(MUGRCode,MUGCode,MUGZl,MUGSp,MUGEntry);
#else
	readREGOP(MUGToken,MUGEntry);
#endif
	MUGHStEntry->MUGEntry=(int *)MUGEntry;
	MUGPush(MUGHStEntry);
}

MUGT31(MUGHStEntry)
struct MUGStEntry *MUGHStEntry;
{
	SPECIALSY *MUGEntry;
	MUGHStEntry->MUGElem=31;
	MUGEntry=(SPECIALSY *)ALLOC(sizeof(SPECIALSY));
#ifdef READpr
	READSPECIALSY(MUGRCode,MUGCode,MUGZl,MUGSp,MUGEntry);
#else
	readSPECIALSY(MUGToken,MUGEntry);
#endif
	MUGHStEntry->MUGEntry=(int *)MUGEntry;
	MUGPush(MUGHStEntry);
}

MUGT32(MUGHStEntry)
struct MUGStEntry *MUGHStEntry;
{
	STRINGSY *MUGEntry;
	MUGHStEntry->MUGElem=32;
	MUGEntry=(STRINGSY *)ALLOC(sizeof(STRINGSY));
#ifdef READpr
	READSTRINGSY(MUGRCode,MUGCode,MUGZl,MUGSp,MUGEntry);
#else
	readSTRINGSY(MUGToken,MUGEntry);
#endif
	MUGHStEntry->MUGEntry=(int *)MUGEntry;
	MUGPush(MUGHStEntry);
}

MUGP1()
{
	struct g1scanner *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1scanner *)ALLOC(sizeof(struct g1scanner));
	MUGOut->prodnum=1;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p1.p15=(struct g1main *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p1.p14=(struct g1definitions *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p1.p13=(struct g1option *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p1.p12=(IDENT *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=34;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP26()
{
	struct g1actionspec *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1actionspec *)ALLOC(sizeof(struct g1actionspec));
	MUGOut->prodnum=26;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p141.p1413=(struct g1parlist *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p141.p1411=(IDENT *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=59;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP27()
{
	struct g1actionspec *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1actionspec *)ALLOC(sizeof(struct g1actionspec));
	MUGOut->prodnum=27;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p142.p1421=(IDENT *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=60;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP28()
{
	struct g1actionspec *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1actionspec *)ALLOC(sizeof(struct g1actionspec));
	MUGOut->prodnum=28;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p143.p1431=(PROGSTRINGSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=61;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP29()
{
	struct g1actionspec *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1actionspec *)ALLOC(sizeof(struct g1actionspec));
	MUGOut->prodnum=29;
	MUGHStEntry.MUGElem=62;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP6()
{
	struct g1definitions *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1definitions *)ALLOC(sizeof(struct g1definitions));
	MUGOut->prodnum=6;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p41.p412=(struct g1definitions *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=39;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP7()
{
	struct g1definitions *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1definitions *)ALLOC(sizeof(struct g1definitions));
	MUGOut->prodnum=7;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p42.p422=(struct g1definitions *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p42.p421=(struct g1makros *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=40;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP8()
{
	struct g1definitions *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1definitions *)ALLOC(sizeof(struct g1definitions));
	MUGOut->prodnum=8;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p43.p432=(struct g1definitions *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p43.p431=(struct g1makroact *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=41;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP9()
{
	struct g1definitions *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1definitions *)ALLOC(sizeof(struct g1definitions));
	MUGOut->prodnum=9;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p44.p442=(struct g1definitions *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p44.p441=(struct g1specialact *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=42;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP10()
{
	struct g1definitions *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1definitions *)ALLOC(sizeof(struct g1definitions));
	MUGOut->prodnum=10;
	MUGHStEntry.MUGElem=43;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP16()
{
	struct g1formparlist *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1formparlist *)ALLOC(sizeof(struct g1formparlist));
	MUGOut->prodnum=16;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p81.p811=(FORMPAR *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=49;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP17()
{
	struct g1formparlist *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1formparlist *)ALLOC(sizeof(struct g1formparlist));
	MUGOut->prodnum=17;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p82.p823=(struct g1formparlist *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p82.p821=(FORMPAR *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=50;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP22()
{
	struct g1lexemes *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1lexemes *)ALLOC(sizeof(struct g1lexemes));
	MUGOut->prodnum=22;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p131.p1316=(struct g1lexemes *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p131.p1314=(struct g1actionspec *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p131.p1312=(struct g1regexpr *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=55;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP23()
{
	struct g1lexemes *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1lexemes *)ALLOC(sizeof(struct g1lexemes));
	MUGOut->prodnum=23;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p132.p1325=(struct g1lexemes *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p132.p1323=(struct g1actionspec *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p132.p1321=(struct g1regexpr *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=56;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP24()
{
	struct g1lexemes *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1lexemes *)ALLOC(sizeof(struct g1lexemes));
	MUGOut->prodnum=24;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p133.p1332=(struct g1lexemes *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=57;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP25()
{
	struct g1lexemes *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1lexemes *)ALLOC(sizeof(struct g1lexemes));
	MUGOut->prodnum=25;
	MUGHStEntry.MUGElem=58;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP11()
{
	struct g1main *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1main *)ALLOC(sizeof(struct g1main));
	MUGOut->prodnum=11;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p51.p512=(struct g1lexemes *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=44;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP12()
{
	struct g1makroact *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1makroact *)ALLOC(sizeof(struct g1makroact));
	MUGOut->prodnum=12;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p61.p612=(struct g1makroactseq *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=45;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP13()
{
	struct g1makroactseq *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1makroactseq *)ALLOC(sizeof(struct g1makroactseq));
	MUGOut->prodnum=13;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p71.p716=(struct g1makroactseq *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p71.p715=(PROGSTRINGSY *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p71.p713=(struct g1formparlist *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p71.p711=(IDENT *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=46;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP14()
{
	struct g1makroactseq *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1makroactseq *)ALLOC(sizeof(struct g1makroactseq));
	MUGOut->prodnum=14;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p72.p723=(struct g1makroactseq *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p72.p722=(PROGSTRINGSY *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p72.p721=(IDENT *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=47;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP15()
{
	struct g1makroactseq *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1makroactseq *)ALLOC(sizeof(struct g1makroactseq));
	MUGOut->prodnum=15;
	MUGHStEntry.MUGElem=48;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP20()
{
	struct g1makrolexemes *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1makrolexemes *)ALLOC(sizeof(struct g1makrolexemes));
	MUGOut->prodnum=20;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p120.p1205=(struct g1makrolexemes *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p120.p1203=(struct g1regexpr *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p120.p1201=(IDENT *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=53;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP21()
{
	struct g1makrolexemes *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1makrolexemes *)ALLOC(sizeof(struct g1makrolexemes));
	MUGOut->prodnum=21;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p121.p1213=(struct g1regexpr *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p121.p1211=(IDENT *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=54;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP19()
{
	struct g1makros *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1makros *)ALLOC(sizeof(struct g1makros));
	MUGOut->prodnum=19;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p111.p1112=(struct g1makrolexemes *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=52;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP2()
{
	struct g1option *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1option *)ALLOC(sizeof(struct g1option));
	MUGOut->prodnum=2;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p21.p212=(struct g1optionseq *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=35;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP3()
{
	struct g1option *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1option *)ALLOC(sizeof(struct g1option));
	MUGOut->prodnum=3;
	MUGHStEntry.MUGElem=36;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP4()
{
	struct g1optionseq *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1optionseq *)ALLOC(sizeof(struct g1optionseq));
	MUGOut->prodnum=4;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p31.p312=(struct g1optionseq *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p31.p311=(INSTRUCTSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=37;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP5()
{
	struct g1optionseq *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1optionseq *)ALLOC(sizeof(struct g1optionseq));
	MUGOut->prodnum=5;
	MUGHStEntry.MUGElem=38;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP32()
{
	struct g1par *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1par *)ALLOC(sizeof(struct g1par));
	MUGOut->prodnum=32;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p161.p1611=(INTEGERSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=65;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP33()
{
	struct g1par *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1par *)ALLOC(sizeof(struct g1par));
	MUGOut->prodnum=33;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p162.p1621=(STRINGSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=66;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP30()
{
	struct g1parlist *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1parlist *)ALLOC(sizeof(struct g1parlist));
	MUGOut->prodnum=30;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p151.p1511=(struct g1par *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=63;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP31()
{
	struct g1parlist *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1parlist *)ALLOC(sizeof(struct g1parlist));
	MUGOut->prodnum=31;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p152.p1523=(struct g1parlist *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p152.p1521=(struct g1par *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=64;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP45()
{
	struct g1regelem *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regelem *)ALLOC(sizeof(struct g1regelem));
	MUGOut->prodnum=45;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p211.p2111=(STRINGSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=78;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP46()
{
	struct g1regelem *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regelem *)ALLOC(sizeof(struct g1regelem));
	MUGOut->prodnum=46;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p212.p2122=(struct g1setseq *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=79;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP47()
{
	struct g1regelem *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regelem *)ALLOC(sizeof(struct g1regelem));
	MUGOut->prodnum=47;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p213.p2133=(struct g1setseq *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=80;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP48()
{
	struct g1regelem *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regelem *)ALLOC(sizeof(struct g1regelem));
	MUGOut->prodnum=48;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p214.p2142=(struct g1regexpr *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=81;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP49()
{
	struct g1regelem *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regelem *)ALLOC(sizeof(struct g1regelem));
	MUGOut->prodnum=49;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p215.p2151=(IDENT *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=82;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP50()
{
	struct g1regelem *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regelem *)ALLOC(sizeof(struct g1regelem));
	MUGOut->prodnum=50;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p216.p2163=(struct g1regexpr *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=83;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP34()
{
	struct g1regexpr *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regexpr *)ALLOC(sizeof(struct g1regexpr));
	MUGOut->prodnum=34;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p171.p1713=(struct g1regterm *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p171.p1711=(struct g1regexpr *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=67;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP35()
{
	struct g1regexpr *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regexpr *)ALLOC(sizeof(struct g1regexpr));
	MUGOut->prodnum=35;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p172.p1721=(struct g1regterm *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=68;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP38()
{
	struct g1regfaktor *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regfaktor *)ALLOC(sizeof(struct g1regfaktor));
	MUGOut->prodnum=38;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p191.p1912=(REGOP *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p191.p1911=(struct g1regelem *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=71;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP39()
{
	struct g1regfaktor *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regfaktor *)ALLOC(sizeof(struct g1regfaktor));
	MUGOut->prodnum=39;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p192.p1923=(struct g1times *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p192.p1921=(struct g1regelem *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=72;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP40()
{
	struct g1regfaktor *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regfaktor *)ALLOC(sizeof(struct g1regfaktor));
	MUGOut->prodnum=40;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p193.p1931=(struct g1regelem *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=73;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP36()
{
	struct g1regterm *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regterm *)ALLOC(sizeof(struct g1regterm));
	MUGOut->prodnum=36;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p181.p1812=(struct g1regfaktor *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p181.p1811=(struct g1regterm *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=69;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP37()
{
	struct g1regterm *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1regterm *)ALLOC(sizeof(struct g1regterm));
	MUGOut->prodnum=37;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p182.p1821=(struct g1regfaktor *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=70;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP51()
{
	struct g1setseq *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1setseq *)ALLOC(sizeof(struct g1setseq));
	MUGOut->prodnum=51;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p231.p2311=(STRINGSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=84;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP52()
{
	struct g1setseq *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1setseq *)ALLOC(sizeof(struct g1setseq));
	MUGOut->prodnum=52;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p232.p2323=(struct g1setseq *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p232.p2321=(STRINGSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=85;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP53()
{
	struct g1setseq *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1setseq *)ALLOC(sizeof(struct g1setseq));
	MUGOut->prodnum=53;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p233.p2333=(STRINGSY *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p233.p2331=(STRINGSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=86;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP54()
{
	struct g1setseq *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1setseq *)ALLOC(sizeof(struct g1setseq));
	MUGOut->prodnum=54;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p234.p2345=(struct g1setseq *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p234.p2343=(STRINGSY *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p234.p2341=(STRINGSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=87;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP18()
{
	struct g1specialact *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1specialact *)ALLOC(sizeof(struct g1specialact));
	MUGOut->prodnum=18;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p91.p912=(PROGSTRINGSY *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p91.p911=(SPECIALSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=51;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP41()
{
	struct g1times *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1times *)ALLOC(sizeof(struct g1times));
	MUGOut->prodnum=41;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p201.p2011=(INTEGERSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=74;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP42()
{
	struct g1times *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1times *)ALLOC(sizeof(struct g1times));
	MUGOut->prodnum=42;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p202.p2021=(INTEGERSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=75;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP43()
{
	struct g1times *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1times *)ALLOC(sizeof(struct g1times));
	MUGOut->prodnum=43;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p203.p2032=(INTEGERSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=76;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGP44()
{
	struct g1times *MUGOut;
	struct MUGStEntry MUGHStEntry;

	MUGOut=(struct g1times *)ALLOC(sizeof(struct g1times));
	MUGOut->prodnum=44;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p204.p2043=(INTEGERSY *)MUGHStEntry.MUGEntry;
	MUGPop(&MUGHStEntry);
	MUGOut->C.p204.p2041=(INTEGERSY *)MUGHStEntry.MUGEntry;
	MUGHStEntry.MUGElem=77;
	MUGHStEntry.MUGEntry=(int *)MUGOut;
	MUGPush(&MUGHStEntry);
}

MUGProdCons (ProdNum)
int ProdNum;
{
	switch (ProdNum)
	{
		case  1 : MUGP1(); break;
		case  2 : MUGP2(); break;
		case  3 : MUGP3(); break;
		case  4 : MUGP4(); break;
		case  5 : MUGP5(); break;
		case  6 : MUGP6(); break;
		case  7 : MUGP7(); break;
		case  8 : MUGP8(); break;
		case  9 : MUGP9(); break;
		case  10 : MUGP10(); break;
		case  11 : MUGP11(); break;
		case  12 : MUGP12(); break;
		case  13 : MUGP13(); break;
		case  14 : MUGP14(); break;
		case  15 : MUGP15(); break;
		case  16 : MUGP16(); break;
		case  17 : MUGP17(); break;
		case  18 : MUGP18(); break;
		case  19 : MUGP19(); break;
		case  20 : MUGP20(); break;
		case  21 : MUGP21(); break;
		case  22 : MUGP22(); break;
		case  23 : MUGP23(); break;
		case  24 : MUGP24(); break;
		case  25 : MUGP25(); break;
		case  26 : MUGP26(); break;
		case  27 : MUGP27(); break;
		case  28 : MUGP28(); break;
		case  29 : MUGP29(); break;
		case  30 : MUGP30(); break;
		case  31 : MUGP31(); break;
		case  32 : MUGP32(); break;
		case  33 : MUGP33(); break;
		case  34 : MUGP34(); break;
		case  35 : MUGP35(); break;
		case  36 : MUGP36(); break;
		case  37 : MUGP37(); break;
		case  38 : MUGP38(); break;
		case  39 : MUGP39(); break;
		case  40 : MUGP40(); break;
		case  41 : MUGP41(); break;
		case  42 : MUGP42(); break;
		case  43 : MUGP43(); break;
		case  44 : MUGP44(); break;
		case  45 : MUGP45(); break;
		case  46 : MUGP46(); break;
		case  47 : MUGP47(); break;
		case  48 : MUGP48(); break;
		case  49 : MUGP49(); break;
		case  50 : MUGP50(); break;
		case  51 : MUGP51(); break;
		case  52 : MUGP52(); break;
		case  53 : MUGP53(); break;
		case  54 : MUGP54(); break;
	}
}

MUGTermCons (Terminal)
int Terminal;
{
	switch (Terminal)
	{
		case  1 : break;
		case  2 : break;
		case  3 : break;
		case  4 : break;
		case  5 : break;
		case  6 : break;
		case  7 : break;
		case  8 : break;
		case  9 : break;
		case  10 : break;
		case  11 : MUGT11(&MUGHStEntry); break;
		case  12 : MUGT12(&MUGHStEntry); break;
		case  13 : break;
		case  14 : break;
		case  15 : MUGT15(&MUGHStEntry); break;
		case  16 : MUGT16(&MUGHStEntry); break;
		case  17 : break;
		case  18 : break;
		case  19 : break;
		case  20 : break;
		case  21 : break;
		case  22 : break;
		case  23 : break;
		case  24 : break;
		case  25 : break;
		case  26 : break;
		case  27 : MUGT27(&MUGHStEntry); break;
		case  28 : MUGT28(&MUGHStEntry); break;
		case  29 : break;
		case  30 : break;
		case  31 : MUGT31(&MUGHStEntry); break;
		case  32 : MUGT32(&MUGHStEntry); break;
	}
}

int alexisBAUMAUFBAU(argc,argv,input,MUGOut)
int argc; char *argv[];char *input;struct g1scanner **MUGOut;
{
	MUGInitSt();
	MUGANALYSATOR(argc,argv,input);
	if (MUGErrNum==0)
	{
		MUGPop(&MUGHStEntry);
		*MUGOut=(struct g1scanner *)MUGHStEntry.MUGEntry;
	}
	free(MUGSt);
	return(MUGErrNum);
}


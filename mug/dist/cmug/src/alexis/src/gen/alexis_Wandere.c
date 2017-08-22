

              /* Die Wandereprozedur */
              /* ===================== */


int alexisMUGEXPORT;
#ifndef VOIDPTR_T
#ifdef __STDC__
 typedef void *voidptr;
#else
 typedef char *voidptr;
#endif
#define VOIDPTR_T
#endif



voidptr ((* alexisAUTOMATEN[])())={
	0L,
	alexisMUGAUTp1,
	alexisMUGAUTp21,
	alexisMUGAUTp22,
	alexisMUGAUTp31,
	alexisMUGAUTp32,
	alexisMUGAUTp41,
	alexisMUGAUTp42,
	alexisMUGAUTp43,
	alexisMUGAUTp44,
	alexisMUGAUTp45,
	alexisMUGAUTp51,
	alexisMUGAUTp61,
	alexisMUGAUTp71,
	alexisMUGAUTp72,
	alexisMUGAUTp73,
	alexisMUGAUTp81,
	alexisMUGAUTp82,
	alexisMUGAUTp91,
	alexisMUGAUTp111,
	alexisMUGAUTp120,
	alexisMUGAUTp121,
	alexisMUGAUTp131,
	alexisMUGAUTp132,
	alexisMUGAUTp133,
	alexisMUGAUTp134,
	alexisMUGAUTp141,
	alexisMUGAUTp142,
	alexisMUGAUTp143,
	alexisMUGAUTp144,
	alexisMUGAUTp151,
	alexisMUGAUTp152,
	alexisMUGAUTp161,
	alexisMUGAUTp162,
	alexisMUGAUTp171,
	alexisMUGAUTp172,
	alexisMUGAUTp181,
	alexisMUGAUTp182,
	alexisMUGAUTp191,
	alexisMUGAUTp192,
	alexisMUGAUTp193,
	alexisMUGAUTp201,
	alexisMUGAUTp202,
	alexisMUGAUTp203,
	alexisMUGAUTp204,
	alexisMUGAUTp211,
	alexisMUGAUTp212,
	alexisMUGAUTp213,
	alexisMUGAUTp214,
	alexisMUGAUTp215,
	alexisMUGAUTp216,
	alexisMUGAUTp231,
	alexisMUGAUTp232,
	alexisMUGAUTp233,
	alexisMUGAUTp234,
	0L};


void alexisMUGWANDERE(K)
voidptr K;
{ voidptr Sohn;

	while (1)
		if ((Sohn=(*alexisAUTOMATEN[*(short *)K])(K,alexisMUGEXPORT))!=0)
			alexisMUGWANDERE(Sohn);
		else return;
}


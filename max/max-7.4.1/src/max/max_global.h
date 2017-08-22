/** values for struct OPT.pars **/

#include "config_ac.h"
#include "config_sc.h"

#define  SYN_ABSTRACT  1
#define  SYN_CONCRETE  2

struct	OPT {
	int onr, pro, trp, bro, frame, pars, make, warn, tc, mpp, mpponly;
	char *mppinc[100];
	char *mppdef[100];
        char *prefix;
};

extern struct OPT max_options;

extern double zeitmessung();

#define SORTCDT  short

typedef union {
	long  f;
	struct{
		short           length;
		SORTCDT         sortcd;
	} h;
#ifdef LOW_ENDIAN
        struct{
                short           code;
                unsigned char   tabno;
                unsigned char   class;
        } c;
#else
        struct{
                unsigned char   class;
                unsigned char   tabno;
                short           code;
        } c;
#endif
} SELEMENT;

static SELEMENT      se;
static unsigned char c;
static long          l;
#define class(E)                (c=(se.f=E,se.c.class))
#define elemcd(E)               (l=(se.f=E,se.c.class=0,se.f))
#define class_code(C,D)         (se.c.class=C,se.c.tabno=0,se.c.code=D,se.f)

#define DEFCONST_CL   0xE0
#define SORTCONST_CL  0xE4

#define  MAXIMALINT     16777215L
#define  MINIMALINT     -16777216L
#define  MAXUNDEF       -335544320L
#define  ROOT           -939524095L
#define  MAXTRUE        -268435455L
#define  MAXFALSE       -268435456L
#define  NIL            -536805377L

#define NODE_SORTCD			2
#define POINT_SORTCD		1
#define NIL_SORTCD			-1
#define TERM_SORTCD			-2
#define NODESORT_SORTCD		-3
#define PREDECLSORT_SORTCD	-4
#define CLASSSORT_SORTCD	-5
#define TUPELSORT_SORTCD	-6
#define LISTSORT_SORTCD		-7
#define IDENT_SORTCD		-8
#define BOOL_SORTCD			-9
#define CHAR_SORTCD			-10
#define INT_SORTCD			-11
#define STRING_SORTCD		-12
#define REFERENCE_SORTCD	-13

#define MIN_PREDECL_SORTCD    -13


typedef struct SortSqElem {
	SORTCDT             first;
	struct SortSqElem  *rest;
} *SortSq;

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif


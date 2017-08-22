
#include "AttrGlob.h"

char *getMem();
void pushattr();
void pushaux();
char *getattr();
char *getaux();
void redattr();
void redaux();

int outred(prod, lseite, plen)
    long prod;
    long lseite;
    long plen;

{
	char *M_voidptr;
	char *M_voidptr1;

	switch (prod) {
	case 1: /* P1 */
		M_voidptr = getMem(sizeof(number));
		printresult(*(number *)getattr(1), (number *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 2: /* P2 */
		M_voidptr = getMem(sizeof(number));
		makeadd(*(number *)getattr(3),*(addop *)getattr(2),*(number *)getattr(1), (number *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-4, 1);
		break;
	case 3: /* P3 */
		M_voidptr = getMem(sizeof(number));
		*((number *)M_voidptr) = *(number *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 4: /* P4 */
		M_voidptr = getMem(sizeof(number));
		makemult(*(number *)getattr(3),*(multop *)getattr(2),*(number *)getattr(1), (number *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-4, 1);
		break;
	case 5: /* P5 */
		M_voidptr = getMem(sizeof(number));
		*((number *)M_voidptr) = *(number *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 6: /* P6 */
		M_voidptr = getMem(sizeof(number));
		*((number *)M_voidptr) = *(number *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 7: /* P7 */
		M_voidptr = getMem(sizeof(number));
		*((number *)M_voidptr) = *(number *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	default:
		return(0);
		break; /* Fehler: Prod unbekannt */
	}
	return(1);
}



void outterm(token)
Token token;
{
	char *M_voidptr;

	switch(token->kc)  {
	case 1: /* number */
		M_voidptr = getMem(sizeof(number));
		readnumber(token,(number *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 2: /* addop */
		M_voidptr = getMem(sizeof(addop));
		readaddop(token,(addop *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 3: /* multop */
		M_voidptr = getMem(sizeof(multop));
		readmultop(token,(multop *)M_voidptr);
		pushattr(M_voidptr);
		break;
	default:
		return;
	}
}

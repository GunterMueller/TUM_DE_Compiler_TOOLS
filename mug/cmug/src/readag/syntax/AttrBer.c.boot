
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
	case 1: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		graminit( (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 2: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(2);
		pushattr(M_voidptr);
		break;
	case 3: /* CP */
		M_voidptr = getMem(sizeof(fparamIndex));
		StartArg(*(gramptr *)getattr(1), (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 4: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(2);
		pushattr(M_voidptr);
		break;
	case 5: /* CP */
		M_voidptr = getMem(sizeof(productIndex));
		AddAuxInf(*(gramptr *)getattr(2),*(productIndex *)getattr(3),*(attrposIndex *)getattr(1), (productIndex *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 6: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(2);
		pushattr(M_voidptr);
		break;
	case 7: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		EnterAxiom(*(gramptr *)getattr(2),*(ident *)getattr(1), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 8: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(4);
		pushattr(M_voidptr);
		break;
	case 9: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(4);
		pushattr(M_voidptr);
		break;
	case 10: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(3);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(fparamIndex));
		PrefixArg(*(gramptr *)getattr(4),*(ident *)getattr(2),*(fparamIndex *)getattr(3), (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 11: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(3);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(ident));
		*((ident *)M_voidptr) = *(ident *)getattr(2);
		pushattr(M_voidptr);
		break;
	case 12: /* CP */
		M_voidptr = getMem(sizeof(attrIndex));
		InitAList(*(gramptr *)getattr(1), (attrIndex *)M_voidptr);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(2);
		pushattr(M_voidptr);
		break;
	case 13: /* CP */
		M_voidptr = getMem(sizeof(attrIndex));
		SecondAttr(*(attrIndex *)getattr(1),*(attrIndex *)getattr(3), (attrIndex *)M_voidptr);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(3);
		pushattr(M_voidptr);
		break;
	case 14: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(3);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(prodposIndex));
		CreateProdpos(*(gramptr *)getattr(4),*(ident *)getattr(3),*(number *)getattr(2), (prodposIndex *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 15: /* CP */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(4);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(prodposIndex));
		PrefixProdpos(*(gramptr *)getattr(5),*(ident *)getattr(3),*(number *)getattr(2),*(prodposIndex *)getattr(4), (prodposIndex *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 16: /* CP */
		M_voidptr = getMem(sizeof(productIndex));
		*((productIndex *)M_voidptr) = *(productIndex *)getattr(3);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(3);
		pushattr(M_voidptr);
		break;
	case 17: /* CP */
		M_voidptr = getMem(sizeof(productIndex));
		*((productIndex *)M_voidptr) = *(productIndex *)getattr(3);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(3);
		pushattr(M_voidptr);
		break;
	case 18: /* CP */
		M_voidptr = getMem(sizeof(productIndex));
		*((productIndex *)M_voidptr) = *(productIndex *)getattr(4);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(4);
		pushattr(M_voidptr);
		break;
	case 19: /* CP */
		M_voidptr = getMem(sizeof(productIndex));
		*((productIndex *)M_voidptr) = *(productIndex *)getattr(3);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(3);
		pushattr(M_voidptr);
		break;
	case 20: /* CP */
		M_voidptr = getMem(sizeof(productIndex));
		CreateProd(*(gramptr *)getattr(5),*(ident *)getattr(4),*(prodposIndex *)getattr(2), (productIndex *)M_voidptr);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(2);
		pushattr(M_voidptr);
		break;
	case 21: /* CP */
		M_voidptr = getMem(sizeof(productIndex));
		*((productIndex *)M_voidptr) = *(productIndex *)getattr(3);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(7);
		pushattr(M_voidptr);
		break;
	case 22: /* P1 */
		M_voidptr = getMem(sizeof(gramptr));
		GramReturn(*(gramptr *)getattr(1), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-10, 1);
		break;
	case 23: /* P2 */
		M_voidptr = getMem(sizeof(gramptr));
		GramName(*(gramptr *)getattr(4),*(ident *)getattr(3),*(ident *)getattr(2),*(ident *)getattr(1), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-4, 1);
		break;
	case 24: /* P37a */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		break;
	case 25: /* P37b */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 26: /* P38a */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 27: /* P38b */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 28: /* P39 */
		M_voidptr = getMem(sizeof(gramptr));
		CreateFunct(*(gramptr *)getattr(6),*(ident *)getattr(5),*(fparamIndex *)getattr(3),*(fparamIndex *)getattr(1), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-6, 1);
		break;
	case 29: /* P40a */
		M_voidptr = getMem(sizeof(fparamIndex));
		EndArg(*(gramptr *)getattr(3),*(fparamIndex *)getattr(1), (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 30: /* P40b */
		M_voidptr = getMem(sizeof(fparamIndex));
		EmptyArg( (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 31: /* P41a */
		M_voidptr = getMem(sizeof(fparamIndex));
		PrefixArg(*(gramptr *)getattr(3),*(ident *)getattr(1),*(fparamIndex *)getattr(2), (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 32: /* P41b */
		M_voidptr = getMem(sizeof(fparamIndex));
		*((fparamIndex *)M_voidptr) = *(fparamIndex *)getattr(1);
		pushattr(M_voidptr);
		redattr(-5, 1);
		break;
	case 33: /* P44 */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 34: /* P45a */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		break;
	case 35: /* P45b */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 36: /* P46a */
		M_voidptr = getMem(sizeof(gramptr));
		NoAttr(*(gramptr *)getattr(2),*(nontermIndex *)getattr(1), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 37: /* P46b */
		M_voidptr = getMem(sizeof(gramptr));
		LinkAttr(*(gramptr *)getattr(4),*(nontermIndex *)getattr(3),*(attrIndex *)getattr(1), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-4, 1);
		break;
	case 38: /* P47a */
		M_voidptr = getMem(sizeof(nontermIndex));
		MakeNT(*(gramptr *)getattr(2),*(ident *)getattr(1), (nontermIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 39: /* P47b */
		M_voidptr = getMem(sizeof(nontermIndex));
		PrefixNT(*(gramptr *)getattr(4),*(ident *)getattr(3),*(nontermIndex *)getattr(1), (nontermIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-4, 1);
		break;
	case 40: /* P48a */
		M_voidptr = getMem(sizeof(attrIndex));
		MakeAttr(*(gramptr *)getattr(2),*(ident *)getattr(1), (attrIndex *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 41: /* P48b */
		M_voidptr = getMem(sizeof(attrIndex));
		AddAttr(*(gramptr *)getattr(6),*(attrIndex *)getattr(1),*(ident *)getattr(5), (attrIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-5, 1);
		break;
	case 42: /* P49 */
		M_voidptr = getMem(sizeof(attrIndex));
		*((attrIndex *)M_voidptr) = *(attrIndex *)getattr(1);
		pushattr(M_voidptr);
		redattr(-4, 1);
		break;
	case 43: /* P50a */
		M_voidptr = getMem(sizeof(attrIndex));
		SecondAttr(*(attrIndex *)getattr(1),*(attrIndex *)getattr(3), (attrIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 44: /* P50b */
		M_voidptr = getMem(sizeof(attrIndex));
		*((attrIndex *)M_voidptr) = *(attrIndex *)getattr(1);
		pushattr(M_voidptr);
		redattr(-5, 1);
		break;
	case 45: /* P51 */
		M_voidptr = getMem(sizeof(attrIndex));
		SpecAttr(*(gramptr *)getattr(5),*(attrIndex *)getattr(3),*(ident *)getattr(2),*(attrkenn *)getattr(1), (attrIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-5, 1);
		break;
	case 46: /* P52a */
		M_voidptr = getMem(sizeof(attrkenn));
		MakeInherited( (attrkenn *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 47: /* P52b */
		M_voidptr = getMem(sizeof(attrkenn));
		MakeSynthesized( (attrkenn *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 48: /* P53 */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(2);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 49: /* P54a */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 50: /* P54b */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 51: /* P55a */
		M_voidptr = getMem(sizeof(gramptr));
		EnterTerm(*(gramptr *)getattr(2),*(ident *)getattr(1), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 52: /* P55b */
		M_voidptr = getMem(sizeof(gramptr));
		EnterSemTerm(*(gramptr *)getattr(2),*(ident *)getattr(1), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 53: /* P56 */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 54: /* P57a */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 55: /* P57b */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 56: /* P58 */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-8, 1);
		break;
	case 57: /* P59 */
		M_voidptr = getMem(sizeof(prodposIndex));
		*((prodposIndex *)M_voidptr) = *(prodposIndex *)getattr(1);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(7);
		pushattr(M_voidptr);
		redattr(-7, 2);
		break;
	case 58: /* P60a */
		M_voidptr = getMem(sizeof(number));
		NoPos( (number *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 59: /* P60b */
		M_voidptr = getMem(sizeof(number));
		*((number *)M_voidptr) = *(number *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 60: /* P61a */
		M_voidptr = getMem(sizeof(prodposIndex));
		*((prodposIndex *)M_voidptr) = *(prodposIndex *)getattr(1);
		pushattr(M_voidptr);
		break;
	case 61: /* P61b */
		M_voidptr = getMem(sizeof(prodposIndex));
		*((prodposIndex *)M_voidptr) = *(prodposIndex *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 62: /* P62a */
		M_voidptr = getMem(sizeof(prodposIndex));
		PrefixProdpos(*(gramptr *)getattr(4),*(ident *)getattr(2),*(number *)getattr(1),*(prodposIndex *)getattr(3), (prodposIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 63: /* P62b */
		M_voidptr = getMem(sizeof(prodposIndex));
		*((prodposIndex *)M_voidptr) = *(prodposIndex *)getattr(1);
		pushattr(M_voidptr);
		redattr(-6, 1);
		break;
	case 64: /* P63a */
		M_voidptr = getMem(sizeof(gramptr));
		NoRules(*(gramptr *)getattr(1),*(productIndex *)getattr(2), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 65: /* P63b */
		M_voidptr = getMem(sizeof(gramptr));
		EnterRules(*(gramptr *)getattr(9),*(productIndex *)getattr(6),*(aufrufIndex *)getattr(1), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-9, 1);
		break;
	case 66: /* P64a */
		M_voidptr = getMem(sizeof(attrposIndex));
		*((attrposIndex *)M_voidptr) = *(attrposIndex *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 67: /* P64b */
		M_voidptr = getMem(sizeof(attrposIndex));
		NoAux( (attrposIndex *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 68: /* P65a */
		M_voidptr = getMem(sizeof(attrposIndex));
		*((attrposIndex *)M_voidptr) = *(attrposIndex *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 69: /* P65b */
		M_voidptr = getMem(sizeof(attrposIndex));
		PrefixAux(*(attrposIndex *)getattr(3),*(attrposIndex *)getattr(1), (attrposIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-4, 1);
		break;
	case 70: /* P66 */
		M_voidptr = getMem(sizeof(attrposIndex));
		CreateAux(*(gramptr *)getattr(3),*(ident *)getattr(2),*(ident *)getattr(1), (attrposIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 71: /* P67a */
		M_voidptr = getMem(sizeof(aufrufIndex));
		*((aufrufIndex *)M_voidptr) = *(aufrufIndex *)getattr(3);
		pushattr(M_voidptr);
		break;
	case 72: /* P67b */
		M_voidptr = getMem(sizeof(aufrufIndex));
		PrefixRule(*(aufrufIndex *)getattr(7),*(aufrufIndex *)getattr(1), (aufrufIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-5, 1);
		break;
	case 73: /* P68 */
		M_voidptr = getMem(sizeof(aufrufIndex));
		CrtRule(*(gramptr *)getattr(5),*(aparamIndex *)getattr(4),*(aufrufIndex *)getattr(1), (aufrufIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-5, 1);
		break;
	case 74: /* P69a */
		M_voidptr = getMem(sizeof(aparamIndex));
		*((aparamIndex *)M_voidptr) = *(aparamIndex *)getattr(2);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 75: /* P69b */
		M_voidptr = getMem(sizeof(aparamIndex));
		PrefAuftr(*(aparamIndex *)getattr(5),*(aparamIndex *)getattr(1), (aparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-6, 1);
		break;
	case 76: /* P70a */
		M_voidptr = getMem(sizeof(aparamIndex));
		*((aparamIndex *)M_voidptr) = *(aparamIndex *)getattr(2);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 77: /* P70b */
		M_voidptr = getMem(sizeof(aparamIndex));
		PrefAuftr(*(aparamIndex *)getattr(5),*(aparamIndex *)getattr(1), (aparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-6, 1);
		break;
	case 78: /* P71a */
		M_voidptr = getMem(sizeof(aparamIndex));
		aCrtSemAuftr(*(gramptr *)getattr(3),*(productIndex *)getattr(4),*(ident *)getattr(2),*(number *)getattr(1), (aparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(functIndex));
		fCrtSemAuftr(*(gramptr *)getattr(4),*(productIndex *)getattr(5),*(ident *)getattr(3),*(number *)getattr(2), (functIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-4, 2);
		break;
	case 79: /* P71b */
		M_voidptr = getMem(sizeof(aparamIndex));
		CrtAuftr(*(gramptr *)getattr(4),*(productIndex *)getattr(5),*(ident *)getattr(3),*(number *)getattr(2),*(ident *)getattr(1), (aparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		M_voidptr = getMem(sizeof(functIndex));
		NoFunct( (functIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-5, 2);
		break;
	case 80: /* P72a */
		M_voidptr = getMem(sizeof(aufrufIndex));
		CrtMakeid(*(gramptr *)getattr(3),*(aparamIndex *)getattr(2),*(functIndex *)getattr(1), (aufrufIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 81: /* P72b */
		M_voidptr = getMem(sizeof(aufrufIndex));
		CrtQuelle(*(gramptr *)getattr(5),*(ident *)getattr(4),*(aparamIndex *)getattr(1), (aufrufIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-5, 1);
		break;
	case 82: /* P63c */
		M_voidptr = getMem(sizeof(productIndex));
		*((productIndex *)M_voidptr) = *(productIndex *)getattr(1);
		pushattr(M_voidptr);
		break;
	case 83: /* P32a */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		break;
	case 84: /* P32b */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 85: /* P33a */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 86: /* P33b */
		M_voidptr = getMem(sizeof(gramptr));
		*((gramptr *)M_voidptr) = *(gramptr *)getattr(1);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 87: /* P34 */
		M_voidptr = getMem(sizeof(gramptr));
		CreateSFunct(*(gramptr *)getattr(5),*(ident *)getattr(4),*(fparamIndex *)getattr(2),*(ident *)getattr(1), (gramptr *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-5, 1);
		break;
	case 88: /* P35a */
		M_voidptr = getMem(sizeof(fparamIndex));
		EndArg(*(gramptr *)getattr(3),*(fparamIndex *)getattr(1), (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 89: /* P35b */
		M_voidptr = getMem(sizeof(fparamIndex));
		EmptyArg( (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 90: /* P36a */
		M_voidptr = getMem(sizeof(fparamIndex));
		PrefixArg(*(gramptr *)getattr(3),*(ident *)getattr(1),*(fparamIndex *)getattr(2), (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 91: /* P36b */
		M_voidptr = getMem(sizeof(fparamIndex));
		*((fparamIndex *)M_voidptr) = *(fparamIndex *)getattr(1);
		pushattr(M_voidptr);
		redattr(-5, 1);
		break;
	case 92: /* P42a */
		M_voidptr = getMem(sizeof(fparamIndex));
		CreateArg(*(gramptr *)getattr(2),*(ident *)getattr(1), (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 93: /* P42b */
		M_voidptr = getMem(sizeof(fparamIndex));
		EndArg(*(gramptr *)getattr(3),*(fparamIndex *)getattr(1), (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-3, 1);
		break;
	case 94: /* P43a */
		M_voidptr = getMem(sizeof(fparamIndex));
		PrefixArg(*(gramptr *)getattr(3),*(ident *)getattr(1),*(fparamIndex *)getattr(2), (fparamIndex *)M_voidptr);
		pushattr(M_voidptr);
		redattr(-2, 1);
		break;
	case 95: /* P43b */
		M_voidptr = getMem(sizeof(fparamIndex));
		*((fparamIndex *)M_voidptr) = *(fparamIndex *)getattr(1);
		pushattr(M_voidptr);
		redattr(-5, 1);
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
	case 7: /* ident */
		M_voidptr = getMem(sizeof(ident));
		readident(token,(ident *)M_voidptr);
		pushattr(M_voidptr);
		break;
	case 12: /* number */
		M_voidptr = getMem(sizeof(number));
		*(number *)M_voidptr = (number)SEMVAL(token);
		pushattr(M_voidptr);
		break;
	default:
		return;
	}
}

#include "AttrGlob.h"
/*#define DEBUG*/
#include "cdebug.h"



#ifdef __STDC__
extern void readREGOP(Token tok, REGOP *erg)
#else /* ! __STDC__ */
extern void readREGOP(tok,erg)
Token tok;
REGOP *erg;
#endif /* ! __STDC__ */
{ _BEGIN_ 
  erg->semval = tok->rcode;
  erg->ort = tok->ort;
  _END_
}

#ifdef __STDC__
extern void readFORMPAR(Token tok, FORMPAR *erg)
#else /* ! __STDC__ */
extern void readFORMPAR(tok,erg)
Token tok;
FORMPAR *erg;
#endif /* ! __STDC__ */
{ _BEGIN_ 
 erg->semval = tok->rcode;
  erg->ort = tok->ort;
  _END_
}

#ifdef __STDC__
extern void readINTEGERSY(Token tok, INTEGERSY *erg)
#else /* ! __STDC__ */
extern void readINTEGERSY(tok,erg)
Token tok;
INTEGERSY *erg;
#endif /* ! __STDC__ */
{ _BEGIN_ 
  erg->semval = tok->rcode;
  erg->ort = tok->ort;
  _END_
}

#ifdef __STDC__
extern void readINSTRUCTSY(Token tok, INSTRUCTSY *erg)
#else /* ! __STDC__ */
extern void readINSTRUCTSY(tok,erg)
Token tok;
INSTRUCTSY *erg;
#endif /* ! __STDC__ */
{_BEGIN_ 
 erg->semval = tok->rcode;
  erg->ort = tok->ort;
  _END_
}

#ifdef __STDC__
extern void readSPECIALSY(Token tok, SPECIALSY *erg)
#else /* ! __STDC__ */
extern void readSPECIALSY(tok,erg)
Token tok;
SPECIALSY *erg;
#endif /* ! __STDC__ */
{_BEGIN_ 
 erg->semval = tok->rcode;
  erg->ort = tok->ort;
  _END_
}

#ifdef __STDC__
extern void readPROGSTRINGSY(Token tok, PROGSTRINGSY *erg)
#else /* ! __STDC__ */
extern void readPROGSTRINGSY(tok,erg)
Token tok;
PROGSTRINGSY *erg;
#endif /* ! __STDC__ */
{_BEGIN_ 
 erg->semval = tok->rcode;
  erg->ort = tok->ort;
  _END_
}

#ifdef __STDC__
extern void readIDENT(Token tok, IDENT *erg)
#else /* ! __STDC__ */
extern void readIDENT(tok,erg)
Token tok;
IDENT *erg;
#endif /* ! __STDC__ */
{_BEGIN_ 
 erg->semval = tok->rcode;
  erg->ort = tok->ort;
  _END_
}

#ifdef __STDC__
extern void readSTRINGSY(Token tok, STRINGSY *erg)
#else /* ! __STDC__ */
extern void readSTRINGSY(tok,erg)
Token tok;
STRINGSY *erg;
#endif /* ! __STDC__ */
{_BEGIN_ 
 erg->semval = tok->rcode;
  erg->ort = tok->ort;
  _END_
} 



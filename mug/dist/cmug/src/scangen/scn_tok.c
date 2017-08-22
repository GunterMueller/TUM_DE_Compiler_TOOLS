
/* ****************************************************************** */
/* scn_tok.c: Routinen fuer die Zugriffe auf den Datentyp Token       */
/* erstellt  22.01.91, Ulrich Vollath                                 */
/* ****************************************************************** */

/*
 * (c) copyright 1989,1991 by Technische Universitaet Muenchen, Germany
 *
 *      This product is part of CMUG
 *      CMUG is a part of the compiler writing system
 *      MUG (Modularer Uebersetzer-Generator, TU Muenchen)
 *
 * Permission to use, duplicate or disclose this software must be
 * obtained in writing. Requests for such permissions may be sent to
 *
 *      Prof. Dr. J. Eickel
 *      Institut fuer Informatik
 *      Technische Universitaet Muenchen
 *      Postfach  20 24 20
 *      Arcisstr. 21
 *      D-8000 Muenchen 2
 *      Germany
 *
 * No version of this implementation may be used or distributed for gain,
 * all listings must contain our copyright notice, and the headings
 * produced by MUG-Modules must contain the text "MUG" and "TU - Muenchen".
 */

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#else
extern char *malloc();
#endif
#include <stdio.h>

#include "ps_token.h"  /* allgemeine Definitionen fuer Scanner         */
#include "pstokenP.h"  /* private Definitionen fuer Scanner            */
#include "scanfunk.h"  /* Funktionalitaten Scanner                     */

#ifdef L_ALLOCTOKEN
/* ====================================================== */
/* neue Schnittstelle: Speicher fuer Token allokieren     */
/* ====================================================== */
#ifdef __STDC__
Token allocToken(void)
#else
Token allocToken()
#endif
 {
  return((Token)malloc(sizeof(struct TokenR)));
 } /* allocToken */
#endif /* L_ALLOCTOKEN */

#ifdef L_FREETOKEN
/* ====================================================== */
/* neue Schnittstelle: Speicher fuer Token freigeben      */
/* ====================================================== */
#ifdef __STDC__
void freeToken(Token tok)
#else
void freeToken(tok)
 Token tok;
#endif
 {
  free((char *)(tok));
 } /* freeToken */
#endif /* L_FREETOKEN */

#ifdef L_COPYTOKEN
/* ====================================================== */
/* neue Schnittstelle: Speicher fuer Token freigeben      */
/* ====================================================== */
#ifdef __STDC__
Token copyToken(Token dest, Token source)
#else
Token copyToken(dest,source)
 Token dest;
 Token source;
#endif
 {
  *dest = *source;
  return(dest);
 } /* copyToken */
#endif /* L_COPYTOKEN */

#ifdef L_SETTOKENINVALID
/* ===================================================================== */
/* neue Schnittstelle: Token als semantisch ungueltig markieren          */
/* ===================================================================== */
#ifdef __STDC__
void setTokeninvalid(Token tok)
#else
void setTokeninvalid(tok)
 Token tok;
#endif
 {
  QUELL_ZL(QUELL_ORT(tok)) = 0;
  QUELL_SP(QUELL_ORT(tok)) = 0;
 } /* setTokeninvalid */
#endif /* L_SETTOKENINVALID */

#ifdef L_ISTOKENVALID
/* ===================================================================== */
/* neue Schnittstelle: feststellen, ob Token semantisch gueltig ist      */
/* ===================================================================== */
#ifdef __STDC__
int isTokenvalid(Token tok)
#else
int isTokenvalid(tok)
 Token tok;
#endif
 {
  return(QUELL_ZL(QUELL_ORT(tok)) &&  QUELL_SP(QUELL_ORT(tok)));
 } /* isTokenvalid */
#endif /* L_ISTOKENVALID */


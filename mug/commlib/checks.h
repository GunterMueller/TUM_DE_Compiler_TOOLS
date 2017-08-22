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


/* ********************************************************************** */
/* checks.h :                                                             */
/* Deklarationen zur Laufzeitueberpruefung von Zugriffen                  */
/* Aenderung 08.02.91, Ulrich Vollath: Fail2(), Ausgaben nach stderr      */
/*			stringify # bzw K&R-Aequivalent in Meldungen      */
/*		unter unix werden die Speicherzugriffe "echt" getestet 	  */
/* erstellt         : 7.3.89                                              */
/* ********************************************************************** */

#ifndef CHECKS_H
#define CHECKS_H

/* -------------------------------------------------------------------- */
/* Ueberpruefung von Pointern fuer Lesezugriffe                     	*/
/* Wert des Makros ist der gepruefte Zeiger 				*/
/* -------------------------------------------------------------------- */
#ifdef CHECKALL
#ifdef __STDC__ /* Stringify # verwenden */
#define CHECKED_PTR_READ(Pointer) \
  (!testRead((void *)(Pointer),sizeof(*(Pointer),#Pointer))\
    ? (Fail(__FILE__,__LINE__,""),(Pointer)) : (Pointer) )
#else /* ! __STDC__, auf Makrosubstitution in Strings hoffen */
#define CHECKED_PTR_READ(Pointer) \
  (!testRead((void *)(Pointer),sizeof(*(Pointer),"Pointer"))\
    ? (Fail(__FILE__,__LINE__,""),(Pointer)) : (Pointer) )
#endif
#define CHECK_PTR_READ(p) CHECKED_PTR_READ(p)
#else
#define CHECK_PTR_READ(p) 
#define CHECKED_PTR_READ(p) (p)
#endif
#define CHECKEDPT(p) CHECKED_PTR_READ(p)
#define CHECKPT(p) CHECK_PTR_READ(p)
/* -------------------------------------------------------------------- */
/* Ueberpruefung von Pointern fuer Lesezugriffe                     	*/
/* NULL wird als zulaessig erkannt                                  	*/
/* -------------------------------------------------------------------- */
#ifdef CHECKALL
#ifdef __STDC__  /* Stringify # verwenden */
#define CHECKED_PTR_READ_NULL(Pointer) \
  ((Pointer) != NULL && \
   !testRead((void *)(Pointer),sizeof(*(Pointer)),#Pointer)\
    ? (Fail(__FILE__,__LINE__,""),(Pointer)) : (Pointer) )
#else /* ! __STDC__, auf Makrosubstitution in Strings hoffen */
#define CHECKED_PTR_READ_NULL(Pointer) \
  ((Pointer) != NULL && \
   !testRead((void *)(Pointer),sizeof(*(Pointer)),"Pointer")\
    ? (Fail(__FILE__,__LINE__,""),(Pointer)) : (Pointer) )
#endif
#define CHECK_PTR_READ_NULL(p) CHECKED_PTR_READ_NULL(p)
#else
#define CHECKED_PTR_READ_NULL(p) (p)
#define CHECK_PTR_READ_NULL(p)
#endif
#define CHECKPTN(p) CHECK_PTR_READ_NULL(p)
/* -------------------------------------------------------------------- */
/* Ueberpruefung von Pointern fuer Schreibzugriffe                  	*/
/* -------------------------------------------------------------------- */
#ifdef CHECKALL
#ifdef __STDC__ /* Stringify # verwenden */
#define CHECKED_PTR_WRITE(Pointer) \
  (!testWrite((void *)(Pointer),sizeof(*(Pointer)),#Pointer)\
    ? (Fail(__FILE__,__LINE__,""),(Pointer)) : (Pointer) )
#else /* ! __STDC__, auf Makrosubstitution in Strings hoffen */
#define CHECKED_PTR_WRITE(Pointer) \
  (!testWrite((void *)(Pointer),sizeof(*(Pointer)),"Pointer")\
    ? (Fail(__FILE__,__LINE__,""),(Pointer)) : (Pointer) )
#endif
#define CHECK_PTR_WRITE(p) CHECKED_PTR_WRITE(p)
#else
#define CHECKED_PTR_WRITE(p) (p)
#define CHECK_PTR_WRITE(p)
#endif
/* ---------------------------------------------------------------- */
/* allgemeine Ueberpruefung mit Bedingung b                         */
/* falls Bedingung FALSE : Fail mit Meldung 	                    */
/* ---------------------------------------------------------------- */
#ifdef CHECKALL
#ifdef __STDC__
#define CHECKBED(Bed) \
  do{if (!(Bed)) Fail2(__FILE__,__LINE__,NULL,#Bed);}while(0)
#else
#define CHECKBED(Bed) \
  do{if (!(Bed)) Fail2(__FILE__,__LINE__,NULL,"Bed");}while(0)
#endif
#else
#define CHECKBED(b) 
#endif /* CHECKALL */

#ifdef __STDC__
extern int testWrite(void *,unsigned,const char *);
extern int testRead(const void *,unsigned,const char *);
void Fail(const char *,int,const char *);
void Fail2(const char *,int,const char *,const char *);
#else
extern int testWrite();
extern int testRead();
void Fail();
void Fail2();
#endif

#endif


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
/* Listen.h  :                                                            */
/* Header Verwaltungsroutinen fuer sortierte Listen ueber Datentypen      */
/* Header Verwaltungsroutinen fuer Keller ueber Datentypen                */
/* die erzeugten Datenstrukturen werden in aufrufenden Modul als char *   */
/* verwaltet, Struktur SORTED LIST OF (info)                              */    
/* Die Listen werden ohne Wiederholung gefuehrt                           */
/* Aenderung : 29.04.90, #ifdef __STDC__                                  */
/* Aenderung : 19.01.90, listenSuche()                                    */
/* Aenderung : 6.11.89 , Makro FOREACHLISTEL leicht modifiziert (Apollo)  */
/* Aenderung : 16.2.89 , Parametrisierung von LISTENFELDER                */
/* erstellt  : 3.2.89                                                     */
/* ********************************************************************** */

#ifndef LISTEN_H
#define LISTEN_H

/* ----------------------------------------------------------- */
/* genereller Basistyp fuer alle Listen und Keller             */
/* ----------------------------------------------------------- */
typedef char **Liste; 

/* ----------------------------------------------------------- */
/* Deklaration der fuer die Verkettung noetigen struct-Felder  */
/* Der Aufruf muss als Erstes in der struct-Deklaration der zu */
/* verwaltenden Listenelemente erfolgen !                      */
/* ----------------------------------------------------------- */
/* Zeiger auf das naechste Listenelement                       */
/* listyp = Zeigertyp der Listendatenstruktur                  */ 
/* ----------------------------------------------------------- */
#define LISTENFELDER(listyp)  listyp next;

/* ----------------------------------------------------------- */
/* liefert Zeiger auf Nachfolger des ersten Listenelementes    */
/* ----------------------------------------------------------- */
#define LISTNEXT(el) (el).next

/* --------------------------------------------------------------- */
/* Schleife ueber alle Zeiger auf Eintraege el in der Liste list   */
/* Liste el, Liste list                                            */
/* --------------------------------------------------------------- */
#define FOREACHLISTEL(list,el) for (el=(list);el!=NULL;el=LISTNEXT(*el))


/* ====================================================================== */
/* Eintragen der Kopie einer Information in eine Liste                    */
/* Neueintrag erfolgt, falls Information noch nicht vorhanden, sonst      */
/* Abgleich zwischen vorhandener und neuer Information                    */
/* Rueckgabe : Zeiger auf Listenelement                                   */
/*             NULL, falls kein Speicher fuer neue Eintraege              */
/* ====================================================================== */
#ifdef __STDC__
Liste listenEintrag(Liste *,Liste,int (*)(Liste,Liste),void (*)(Liste,Liste),
                    void (*)(Liste,Liste),unsigned,Liste *);
#else
Liste listenEintrag();
#endif
/* ====================================================================== */
/* Suchen einer Information in einer Liste                                */
/* Rueckgabe : Zeiger auf Listenelement                                   */
/*             NULL, falls nicht in Liste vorhanden                       */
/* ====================================================================== */
#ifdef __STDC__
Liste listenSuche(Liste *,Liste,int (*)(Liste,Liste) );
#else
Liste listenSuche();
#endif
/* ====================================================================== */
/* Eintragen der neuen Informationen einer Liste in eine andere Liste     */
/* Neueintrag erfolgt, falls Information noch nicht vorhanden, sonst      */
/* Abgleich zwischen vorhandener und neuer Information                    */
/* Rueckgabe : TRUE, falls erfolgreich                                    */
/*             FALSE, falls kein Speicher fuer neue Eintraege             */
/* ====================================================================== */
#ifdef __STDC__
BOOL listenMerge(Liste *,Liste,int (*)(Liste,Liste),void (*)(Liste,Liste),
                 void(*)(Liste,Liste),unsigned,Liste *);
#else
BOOL listenMerge();
#endif

#endif /* LISTEN_H */


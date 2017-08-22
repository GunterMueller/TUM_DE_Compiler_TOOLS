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
/* site.h :                                                               */
/* LR(k)-Parser-Generator                                                 */
/* Deklarationen, die maschinenabhaengig sein koennen                     */
/* Bereitstellung von Typen, die vorgegebene Laengen besitzen             */
/* erstellt  : 08.07.89                                                   */
/* ---------------------------------------------------------------------- */
/* ACHTUNG : Deklarationen der Typlaengen u.U. Compilerabhaengig          */
/* ********************************************************************** */

#ifndef SITE_H
#define SITE_H

typedef /* signed */ char  Int8;  /* Typ fuer 8-Bit signed            */
typedef unsigned char  Uint8;     /* Typ fuer 8-Bit unsigned          */
typedef /* signed */ short Int16; /* Typ fuer 16-Bit signed           */
typedef unsigned short Uint16;    /* Typ fuer 16-Bit unsigned         */
typedef /* signed */ long  Int32; /* Typ fuer 32-Bit signed           */
typedef unsigned long  Uint32;    /* Typ fuer 32-Bit unsigned         */

#endif /* SITE_H */

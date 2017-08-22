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
#endif
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

static jmp_buf fail_jmp;
typedef unsigned short Dummytype;
typedef Dummytype *Dummyptr;
static Dummytype save;

#ifdef __STDC__
static void memFault(int sig)
#else
static void memFault(sig)
 int sig;
#endif
 {
  longjmp(fail_jmp,1);
 } /* memFault */

#ifdef __STDC__
static int testWrite(void *addr)
#else
static int testWrite(addr)
 void *addr;
#endif
 {
  int res;

  if (res = !setjmp(fail_jmp))
   {
    signal(SIGBUS,memFault);
    signal(SIGSEGV,memFault);
    save = *((Dummyptr)addr);
    *((Dummyptr)addr) = save;
   }
  signal(SIGBUS,SIG_DFL);
  signal(SIGSEGV,SIG_DFL);
  return(res);
 }

#ifdef __STDC__
static int testRead(void *addr)
#else
static int testRead(addr)
 void *addr;
#endif
 {
  int res;

  if (res = !setjmp(fail_jmp))
   {
    signal(SIGBUS,memFault);
    signal(SIGSEGV,memFault);
    save = *((Dummyptr)addr);
   }
  signal(SIGBUS,SIG_DFL);
  signal(SIGSEGV,SIG_DFL);
  return(res);
 }

#ifdef __STDC__
int main(int argc, char *argv[])
#else
int main(argc,argv)
 int argc;
 char *argv[];
#endif
 {
#define test(a) \
  printf("Adresse %lx ist %sschreibbar\n",(long)(a),\
         testWrite((void *)a) ? "" : "nicht " );\
  printf("Adresse %lx ist %slesbar\n",(long)(a),\
         testRead((void *)a) ? "" : "nicht " );

  test(0);
  test(1);
  test(main);
  test(1111111);
  test(1111110);
  return(0);
 } /* main */

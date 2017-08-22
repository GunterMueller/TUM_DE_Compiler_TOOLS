#
# (c) copyright 1989,1991 by Technische Universitaet Muenchen, Germany
#
#      This product is part of CMUG
#      CMUG is a part of the compiler writing system
#      MUG (Modularer Uebersetzer-Generator, TU Muenchen)
#
# Permission to use, duplicate or disclose this software must be
# obtained in writing. Requests for such permissions may be sent to
#
#      Prof. Dr. J. Eickel
#      Institut fuer Informatik
#      Technische Universitaet Muenchen
#      Postfach  20 24 20
#      Arcisstr. 21
#      D-8000 Muenchen 2
#      Germany
#
# No version of this implementation may be used or distributed for gain,
# all listings must contain our copyright notice, and the headings
# produced by MUG-Modules must contain the text "MUG" and "TU - Muenchen".
#
#lagen/lalib/Makefile
#
TOPDIR=../..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#

#
DEFINES=
INCLUDES=-I../include -I$(PROJHOME)/include -I$(PROJHOME)/readag/zufunc \
 -I$(COMMLIB)/include -I$(PROJHOME)/readag/include -I$(PROJHOME)/scangen
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=
#
# diverse Betriebssystem-Kommandos
#
MAKE=make
#
all: lagen.o aguserlrgrm.o

#
aguserlrgrm.o: aguserlrgrm.c
	$(CC) -c $(CFLAGS) aguserlrgrm.c
lagen.o:  lagen.c
	$(CC) -c $(CFLAGS) lagen.c

clean realclean:
	-$(RM) $(WILD).o
install:

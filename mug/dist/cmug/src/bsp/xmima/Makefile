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

#
# Beispiel-Makefile: Syntaxchecker
#
# Sprache, die geparst wird
#
SPRACHE=mima
# Installationsorte der verwendeten Software
#
COMMLIB=/usr/proj/commlib
PROJHOME=/usr/wiss/vollath/cmug
#
# verwendete CMUG-Generatoren
#
LALRGEN=$(GENHOME)/lalrgen/lrkgen
SCANGEN=$(GENHOME)/scangen/scangen
READG=$(GENHOME)/readg/readg
TABCONV=$(GENHOME)/nparser/tabconv
#
# verwendete Libraries
#
PARSLIB=$(PROJHOME)/nparser/obj/$(LIBPREF)Parser$(LIBEXT) \
        $(PROJHOME)/nparser/obj/$(LIBPREF)Parsold$(LIBEXT) 
PARSMODR=$(PROJHOME)/nparser/obj/ti_mainr.o
PARSMODL=$(PROJHOME)/nparser/obj/ti_mainl.o
SCANLIB=$(PROJHOME)/scangen/obj/$(LIBPREF)Parscan$(LIBEXT) 
COMMLIBLIB=$(COMMLIB)/lib/$(LIBPREF)Common$(LIBEXT)
# Namenskonventionen
#
LIBEXT=.a
LIBPREF=lib
OBJ=obj
#
# verwendete Systembefehle
#
SHELL=/bin/sh
RM=rm -f
MKDIR=mkdir
MV=mv
CC=cc
LD=$(CC)
#
# C-Compiler-Flags
#
DBG=-g
OPT=
WARNS=
INCLUDES=-I$(PROJHOME)/include -I$(PROJHOME)/scangen \
	 -I$(PROJHOME)/nparser -I$(COMMLIB)/include
CFLAGS=$(WARNS) $(INCLUDES) $(OPT) $(DBG)
LDFLAGS=$(DBG)
#
all: $(OBJ) $(SPRACHE) $(SPRACHE).tab $(SPRACHE)1
#
test: $(OBJ) $(SPRACHE)
	for srcfile in $(SPRACHE)src/* ; do \
	  wc $$srcfile ; \
	  time $(SPRACHE) $$srcfile || /bin/true; \
	done
#
$(OBJ):
	$(MKDIR) $(OBJ)
# $(SPRACHE)-Compiler mit zur Laufzeit gelesener Parsertabelle
$(SPRACHE)1: $(OBJ)/$(SPRACHE)scan.o
	$(LD) $(LDFLAGS) -o $(SPRACHE)1 $(OBJ)/$(SPRACHE)scan.o \
 $(PARSMODR) $(PARSLIB) $(SCANLIB) $(PARSLIB) $(COMMLIBLIB) $(RMFAIL)
# $(SPRACHE)-Compiler mit gelinkter Parsertabelle
$(SPRACHE): $(OBJ)/$(SPRACHE).o $(OBJ)/$(SPRACHE)scan.o
	$(LD) $(LDFLAGS) -o $(SPRACHE) $(OBJ)/$(SPRACHE).o $(OBJ)/$(SPRACHE)scan.o \
 $(PARSMODL) $(PARSLIB) $(SCANLIB) $(PARSLIB) $(COMMLIBLIB) $(RMFAIL)
$(OBJ)/$(SPRACHE).o: $(SPRACHE).c
	$(CC) -c $(CFLAGS) $(SPRACHE).c && $(MV) $(SPRACHE).o $(OBJ)
$(SPRACHE).c: $(SPRACHE).tab
	$(TABCONV) $(SPRACHE).tab $(SPRACHE).c
$(SPRACHE).tab: $(SPRACHE).grm
	$(LALRGEN) $(SPRACHE).grm $(SPRACHE).tab
$(SPRACHE).grm: $(SPRACHE).g
	$(READG) $(SPRACHE).g $(SPRACHE).grm
$(OBJ)/$(SPRACHE)scan.o: $(SPRACHE)scan.c
	$(CC) -c $(CFLAGS) $(SPRACHE)scan.c && $(MV) $(SPRACHE)scan.o $(OBJ)
$(SPRACHE)scan.c: $(SPRACHE).scb
	$(SCANGEN) $(SPRACHE).scb $(SPRACHE)scan.c
#
clean:
	-$(RM) $(SPRACHE)scan* *.grm* $(OBJ)/* $(OBJ)/*.*  *.err gmon.*
	$(RM) $(SPRACHE).c *.err
realclean: clean
	$(RM) $(SPRACHE) $(SPRACHE).tab $(SPRACHE)1 *.err
install:

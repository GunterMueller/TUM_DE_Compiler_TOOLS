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
LANG=pascal
# Installationsorte der verwendeten Software
#
COMMLIB=/usr/proj/commlib
CMUG=/usr/proj/cmug
#
# verwendete CMUG-Generatoren
#
LALRGEN=$(CMUG)/bin/lrkgen
SCANGEN=$(CMUG)/bin/scangen
READG=$(CMUG)/bin/readg
TABCONV=$(CMUG)/bin/tabconv
#
# verwendete Libraries
#
PARSLIB=$(CMUG)/lib/$(LIBPREF)Parser$(LIBEXT) $(CMUG)/lib/$(LIBPREF)Parsold$(LIBEXT) 
PARSMODR=$(CMUG)/lib/ti_mainr.o
PARSMODL=$(CMUG)/lib/ti_mainl.o
SCANLIB=$(CMUG)/lib/$(LIBPREF)Parscan$(LIBEXT) 
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
INCLUDES=-I$(CMUG)/include -I$(COMMLIB)/include
CFLAGS=$(WARNS) $(INCLUDES) $(OPT) $(DBG)
LDFLAGS=$(DBG)
#
all: $(OBJ) $(LANG) $(LANG).tab $(LANG)1
#
test: $(OBJ) $(LANG)
	for srcfile in $(LANG)src/* ; do \
	  wc $$srcfile ; \
	  time $(LANG) $$srcfile || /bin/true; \
	done
#
$(OBJ):
	$(MKDIR) $(OBJ)
# $(LANG)-Compiler mit zur Laufzeit gelesener Parsertabelle
$(LANG)1: $(OBJ)/$(LANG)scan.o
	$(LD) $(LDFLAGS) -o $(LANG)1 $(OBJ)/$(LANG)scan.o \
 $(PARSMODR) $(PARSLIB) $(SCANLIB) $(PARSLIB) $(COMMLIBLIB)
# $(LANG)-Compiler mit gelinkter Parsertabelle
$(LANG): $(OBJ)/$(LANG).o $(OBJ)/$(LANG)scan.o
	$(LD) $(LDFLAGS) -o $(LANG) $(OBJ)/$(LANG).o $(OBJ)/$(LANG)scan.o \
 $(PARSMODL) $(PARSLIB) $(SCANLIB) $(PARSLIB) $(COMMLIBLIB)
$(OBJ)/$(LANG).o: $(LANG).c
	$(CC) -c $(CFLAGS) $(LANG).c && $(MV) $(LANG).o $(OBJ)
$(LANG).c: $(LANG).tab
	$(TABCONV) $(LANG).tab $(LANG).c
$(LANG).tab: $(LANG).grm
	$(LALRGEN) $(LANG).grm $(LANG).tab
$(LANG).grm: $(LANG).g
	$(READG) $(LANG).g $(LANG).grm
$(OBJ)/$(LANG)scan.o: $(LANG)scan.c
	$(CC) -c $(CFLAGS) $(LANG)scan.c && $(MV) $(LANG)scan.o $(OBJ)
$(LANG)scan.c: $(LANG).scb
	$(SCANGEN) $(LANG).scb $(LANG)scan.c
#
clean:
	-$(RM) $(LANG)scan* *.grm* $(OBJ)/* *.err gmon.*
	$(RM) $(LANG).c
realclean: clean
	$(RM) $(LANG) $(LANG).tab $(LANG)1
install:

#
# Beispiel-Makefile: Syntaxchecker
#
# Sprache, die geparst wird
#
#
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
TOPDIR=../..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#
SPRACHE=mima
# Installationsorte der verwendeten Software
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
#
OBJ=obj
#
# verwendete Systembefehle
#
#
# C-Compiler-Flags
#
INCLUDES=-I$(PROJHOME)/include -I$(PROJHOME)/scangen \
	 -I$(PROJHOME)/nparser -I$(COMMLIB)/include
DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS) $(DBG)
#
.PHONY: all clean realclean install test

all:: $(OBJ) $(SPRACHE) $(SPRACHE).tab $(SPRACHE)1
#
test: $(OBJ) $(SPRACHE)
	for srcfile in $(SPRACHE)src/$(WILD) ; do \
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

clean:
	$(RM) $(SPRACHE)scan$(WILD) $(WILD).grm* $(OBJ)/$(WILD)
	$(RM) $(SPRACHE).c $(WILD).err gmon.$(WILD)

realclean: clean
	$(RM) $(SPRACHE) $(SPRACHE).tab $(SPRACHE)1

install: $(INSTALLDIRS)
	$(RM) -r $(INSTALLBSPDIR)/$(SPRACHE)
	$(MKDIR) $(INSTALLBSPDIR)/$(SPRACHE)
	$(CP) -r $(SPRACHE).g $(SPRACHE).scb $(SPRACHE)src $(INSTALLBSPDIR)/$(SPRACHE)
	$(CP) Makefile.installed $(INSTALLBSPDIR)/$(SPRACHE)/Makefile

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@

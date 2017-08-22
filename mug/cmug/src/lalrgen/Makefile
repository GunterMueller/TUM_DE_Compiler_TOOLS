#
# Makefile fuer lrkgen
# LALR(k)-Parsertabellen-Generator
# letzte Aenderung: 18.03.91, Ulrich Vollath
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
TOPDIR=..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
# 
INSTALLBINS=lrkgen
INSTALLDOCS=NULL
INSTALLLIBS=NULL
INSTALLINCS=NULL
#
# falls INCATTR definiert ist, werden Lookaheads mit dem inkrementellen
# Fixpunktattributierer berechnet
#
DEFINES=#-DINCATTR
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS) $(DBG)
#

INCATTR=../../incattr/incattr/
#
OBJ=obj
#
LIBOBJS=$(COMMLIB)/lib/$(LIBPREF)Common$(LIBEXT) 
INCLIB=$(INCATTR)obj/$(LIBPREF)incattr$(LIBEXT)
#
INCLUDES=-I$(COMMLIB)/include -I$(PROJHOME)/include #-I$(INCATTR) 
# Objektmodule
OBJECTS = $(OBJ)/lrkgen.o $(OBJ)/lrkread.o $(OBJ)/lrkmat.o $(OBJ)/lrkmatp2.o \
$(OBJ)/lrkkont.o $(OBJ)/lrkaus.o $(OBJ)/lrkfiles.o $(OBJ)/lrkerrors.o \
$(OBJ)/lrkdec.o $(OBJ)/lrkzust.o $(OBJ)/lrkeps.o $(OBJ)/lrksets.o \
$(OBJ)/alpharel.o $(OBJ)/grammar.o $(OBJ)/lrklook.o
#
.PHONY: all clean realclean install

all:  $(OBJ) lrkgen # lrkgen.in
#
$(OBJ):
	 (MKDIR) $@

lrkgen: $(OBJECTS)
	@$(ECHO) $(LD) $(LDFLAGS) -o lrkgen $(OBJECTS) $(LIBOBJS)
	@$(LD) $(LDFLAGS) -o lrkgen $(OBJECTS) $(LIBOBJS) $(RMFAIL)


lrkgen.in: 
	$(MAKE) OBJ=obj_inc/ DEFINES=-DINCATTR lrkgen.inc
lrkgen.inc: obj_inc $(OBJECTS) 
	$(LD) $(LDFLAGS) -o lrkgen.inc $(OBJECTS) $(LIBOBJS) $(INCLIB) $(RMFAIL)
#
# generierte Abhaengigkeiten
#
$(OBJ)/lrkgen.o: lrkgen.c lrkgen.h grammar.h gramconst.h lrkread.h \
  lrkmat.h lrkzust.h lrkaus.h 
	$(CC) -c $(CFLAGS) lrkgen.c && $(MV) lrkgen.o $@
$(OBJ)/lrkread.o : lrkread.c grammar.h gramconst.h lrkread.h lrkfiles.h \
  lrkerrors.h lrkzust.h 
	$(CC) -c $(CFLAGS) lrkread.c && $(MV) lrkread.o $@
$(OBJ)/lrkmat.o : lrkmat.c grammar.h gramconst.h lrkzust.h lrkdec.h \
  lrkmat.h lrkmatp2.h lrkkont.h alpharel.h 
	$(CC) -c $(CFLAGS) lrkmat.c && $(MV) lrkmat.o $@
$(OBJ)/lrkmatp2.o : lrkmatp2.c \
  grammar.h gramconst.h lrkzust.h lrkdec.h lrkkont.h lrkmat.h \
  lrkmatp2.h 
	$(CC) -c $(CFLAGS) lrkmatp2.c && $(MV) lrkmatp2.o $@
$(OBJ)/lrkkont.o : lrkkont.c grammar.h \
  gramconst.h lrkzust.h lrkmat.h \
  lrkmatp2.h lrksets.h lrkkont.h 
	$(CC) -c $(CFLAGS) lrkkont.c && $(MV) lrkkont.o $@
$(OBJ)/lrkaus.o : lrkaus.c  lrkfiles.h \
  grammar.h gramconst.h lrkzust.h lrkdec.h lrkmat.h lrkaus.h 
	$(CC) -c $(CFLAGS) lrkaus.c && $(MV) lrkaus.o $@
$(OBJ)/lrkfiles.o : lrkfiles.c lrkfiles.h lrkerrors.h grammar.h \
  gramconst.h lrkzust.h 
	$(CC) -c $(CFLAGS) lrkfiles.c && $(MV) lrkfiles.o $@
$(OBJ)/lrkerrors.o : lrkerrors.c grammar.h gramconst.h lrkdec.h \
  lrkzust.h lrkmat.h lrkerrors.h  
	$(CC) -c $(CFLAGS) lrkerrors.c && $(MV) lrkerrors.o $@
$(OBJ)/lrkdec.o : lrkdec.c grammar.h gramconst.h lrkzust.h lrkdec.h 
	$(CC) -c $(CFLAGS) lrkdec.c && $(MV) lrkdec.o $@
$(OBJ)/lrkzust.o : lrkzust.c grammar.h gramconst.h lrkzust.h 
	$(CC) -c $(CFLAGS) lrkzust.c && $(MV) lrkzust.o $@
$(OBJ)/lrkeps.o : lrkeps.c grammar.h gramconst.h lrkeps.h lrkdec.h \
  lrkzust.h 
	$(CC) -c $(CFLAGS) lrkeps.c && $(MV) lrkeps.o $@
$(OBJ)/lrksets.o : lrksets.c grammar.h gramconst.h lrkdec.h lrkzust.h \
  lrksets.h 
	$(CC) -c $(CFLAGS) lrksets.c && $(MV) lrksets.o $@
$(OBJ)/lrklook.o : lrklook.c lrklook.h grammar.h \
 gramconst.h lrkdec.h 
	$(CC) -c $(CFLAGS) lrklook.c && $(MV) lrklook.o $@
$(OBJ)/grammar.o : grammar.c grammar.h gramconst.h 
	$(CC) -c $(CFLAGS) grammar.c && $(MV) grammar.o $@
$(OBJ)/alpharel.o : alpharel.c \
    grammar.h gramconst.h lrkmat.h \
  lrkzust.h lrksets.h alpharel.h 
	$(CC) -c $(CFLAGS) alpharel.c && $(MV) alpharel.o $@
# Ende generierte Abhaengigkeiten
$(OBJ)/tabdec.o: tabdec.c ti_defs.h ti_read.h ti_zugr.h
$(OBJ)/ti_read.o: ti_read.c ti_defs.h ti_read.h
$(OBJ)/ti_zugr.o: ti_zugr.c ti_defs.h ti_zugr.h
$(OBJ)/ti_parse.o: ti_parse.c ti_defs.h ti_zugr.h \
 ti_read.h ti_parse.h

clean:
	$(RM) obj/$(WILD) obj_inc/$(WILD) $(DEBRIS)

realclean: clean
	$(RM) lrkgen lrkgen.inc

install: $(INSTALLDIRS)
	@$(INSTALLALL)

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@

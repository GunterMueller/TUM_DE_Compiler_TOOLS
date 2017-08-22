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
# cmug/scangen/Makefile
# Makefile fuer die Generierung des Scannergenerators scangen
#
TOPDIR=..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#

INSTALLBINS=scangen
INSTALLLIBS=$(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/$(LIBPREF)Psold$(LIBEXT)
INSTALLINCS=ps_token.h ps_tab.h pstokenP.h
INSTALLDOCS=NULL

SCANGEN=$(GENHOME)/scangen/scangen
DEFINES=
INCLUDES=-I$(PROJHOME)/include -I$(COMMLIB)/include -I$(PROJHOME)/scangen
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS) $(DBG)
OBJ=obj
GEN=gen
#
# scangen  : normale Version des Generators
# 
all: $(OBJ) $(GEN) \
     $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/$(LIBPREF)Psold$(LIBEXT) \
     scangen
$(OBJ) $(GEN):
	$(MKDIR) $@
#
# Scannergenerator
#
scangen:   $(OBJ)/sgsc.o $(OBJ)/scangen.o $(OBJ)/$(LIBPREF)Parscan$(LIBEXT)
	$(LD) $(LDFLAGS) $(OBJ)/scangen.o $(OBJ)/sgsc.o \
 $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) \
 $(COMMLIB)/lib/$(LIBPREF)Common$(LIBEXT) -o scangen $(RMFAIL)
$(OBJ)/scangen.o: scangen.c scangen.h 
	$(CC) -c $(CFLAGS) scangen.c && mv scangen.o $(OBJ)/scangen.o
$(OBJ)/sgsc.o: $(GEN)/sgsc.c
	$(CC) -c $(CFLAGS) -I. $(GEN)/sgsc.c && $(MV) sgsc.o $(OBJ)/sgsc.o
$(GEN)/sgsc.c: scang.scb
	if [ $(EXEEXI) $(SCANGEN) ] ; then \
	  $(SCANGEN) scang.scb $(GEN)/sgsc.c ;\
	else \
	  $(CP) sgsc.c.boot $(GEN)/sgsc.c ;\
	fi
#
# Laufzeitbibliothek
#
FIXOBJS=$(OBJ)/scn_base.o $(OBJ)/scn_glob.o 
LINKOBJS=$(OBJ)/SCANLAH.o $(OBJ)/SCANSPECIALS.o $(OBJ)/COMMENTS.o \
	 $(OBJ)/MCOMMENTS.o $(OBJ)/CCOMMENTS.o $(OBJ)/IDENTS.o \
	 $(OBJ)/KEYWDS.o \
	 $(OBJ)/REALS.o $(OBJ)/NUMBERS.o $(OBJ)/STRINGS.o \
	 $(OBJ)/CCHARS.o $(OBJ)/CREALS.o $(OBJ)/CNUMBERS.o $(OBJ)/CSTRINGS.o \
	 $(OBJ)/SCANNDECODE.o $(OBJ)/SCANDECODE.o \
	 $(OBJ)/FDECQUELL.o $(OBJ)/WERRORF.o \
	 $(OBJ)/MEMERROR.o $(OBJ)/ALLOCTOKEN.o $(OBJ)/FREETOKEN.o \
	 $(OBJ)/COPYTOKEN.o $(OBJ)/SETTOKENINVAL.o $(OBJ)/ISTOKENVALID.o \
	 $(OBJ)/LINEDIRS.o
$(OBJ)/$(LIBPREF)Parscan$(LIBEXT): $(FIXOBJS) $(LINKOBJS)
	$(RANLIB) $@
#
# konstanter Anteil Scanner
#
$(OBJ)/scn_base.o: scn_base.c
	$(CC) -c $(CFLAGS) scn_base.c && \
	$(MV) scn_base.o $(OBJ)/scn_base.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/scn_base.o
$(OBJ)/scn_glob.o: scn_glob.c
	$(CC) -c $(CFLAGS) scn_glob.c && \
	$(MV) scn_glob.o $(OBJ)/scn_glob.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/scn_glob.o
#
# Variabler Anteil Scanner
#
$(OBJ)/SCANLAH.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_SCANLAH scn_link.c && \
	$(MV) scn_link.o $(OBJ)/SCANLAH.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/SCANLAH.o
$(OBJ)/SCANSPECIALS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_SCANSPECIALS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/SCANSPECIALS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/SCANSPECIALS.o
$(OBJ)/COMMENTS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_COMMENTS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/COMMENTS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/COMMENTS.o
$(OBJ)/MCOMMENTS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_MCOMMENTS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/MCOMMENTS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/MCOMMENTS.o
$(OBJ)/CCOMMENTS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_CCOMMENTS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/CCOMMENTS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/CCOMMENTS.o
$(OBJ)/IDENTS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_IDENTS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/IDENTS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/IDENTS.o
$(OBJ)/KEYWDS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_KEYWDS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/KEYWDS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/KEYWDS.o
$(OBJ)/REALS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_REALS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/REALS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/REALS.o
$(OBJ)/CREALS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_CREALS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/CREALS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/CREALS.o
$(OBJ)/NUMBERS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_NUMBERS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/NUMBERS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/NUMBERS.o
$(OBJ)/CNUMBERS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_CNUMBERS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/CNUMBERS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/CNUMBERS.o
$(OBJ)/STRINGS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_STRINGS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/STRINGS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/STRINGS.o
$(OBJ)/CSTRINGS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_CSTRINGS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/CSTRINGS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/CSTRINGS.o
$(OBJ)/CCHARS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_CCHARS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/CCHARS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/CCHARS.o
$(OBJ)/LINEDIRS.o: scn_link.c
	$(CC) -c $(CFLAGS) -DL_LINEDIRS scn_link.c && \
	$(MV) scn_link.o $(OBJ)/LINEDIRS.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/LINEDIRS.o
#
# Dekoderroutinen
#
$(OBJ)/FDECQUELL.o: scn_dec.c
	$(CC) -c $(CFLAGS) -DL_FDECQUELL scn_dec.c && \
	$(MV) scn_dec.o $(OBJ)/FDECQUELL.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/FDECQUELL.o
$(OBJ)/MEMERROR.o: scn_dec.c
	$(CC) -c $(CFLAGS) -DL_MEMERROR scn_dec.c && \
	$(MV) scn_dec.o $(OBJ)/MEMERROR.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/MEMERROR.o
$(OBJ)/SCANDECODE.o: scn_dec.c
	$(CC) -c $(CFLAGS) -DL_SCANDECODE scn_dec.c && \
	$(MV) scn_dec.o $(OBJ)/SCANDECODE.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/SCANDECODE.o
$(OBJ)/SCANNDECODE.o: scn_dec.c
	$(CC) -c $(CFLAGS) -DL_SCANNDECODE scn_dec.c && \
	$(MV) scn_dec.o $(OBJ)/SCANNDECODE.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/SCANNDECODE.o
$(OBJ)/WERRORF.o: scn_dec.c
	$(CC) -c $(CFLAGS) -DL_WERRORF scn_dec.c && \
	$(MV) scn_dec.o $(OBJ)/WERRORF.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/WERRORF.o
#
# Verwaltung Datenstruktur Token
#
$(OBJ)/ALLOCTOKEN.o: scn_tok.c
	$(CC) -c $(CFLAGS) -DL_ALLOCTOKEN scn_tok.c && \
	$(MV) scn_tok.o $(OBJ)/ALLOCTOKEN.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/ALLOCTOKEN.o
$(OBJ)/FREETOKEN.o: scn_tok.c
	$(CC) -c $(CFLAGS) -DL_FREETOKEN scn_tok.c && \
	$(MV) scn_tok.o $(OBJ)/FREETOKEN.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/FREETOKEN.o
$(OBJ)/COPYTOKEN.o: scn_tok.c
	$(CC) -c $(CFLAGS) -DL_COPYTOKEN scn_tok.c && \
	$(MV) scn_tok.o $(OBJ)/COPYTOKEN.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/COPYTOKEN.o
$(OBJ)/SETTOKENINVAL.o: scn_tok.c
	$(CC) -c $(CFLAGS) -DL_SETTOKENINVALID scn_tok.c && \
	$(MV) scn_tok.o $(OBJ)/SETTOKENINVAL.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/SETTOKENINVAL.o
$(OBJ)/ISTOKENVALID.o: scn_tok.c
	$(CC) -c $(CFLAGS) -DL_ISTOKENVALID scn_tok.c && \
	$(MV) scn_tok.o $(OBJ)/ISTOKENVALID.o
	$(AR) $(OBJ)/$(LIBPREF)Parscan$(LIBEXT) $(OBJ)/ISTOKENVALID.o
#
# Kompatibilitaetsmoduln
#
KOMPOBJS=$(OBJ)/O_MABORT.o $(OBJ)/O_SCANDECODE.o $(OBJ)/O_SCAN.o
$(OBJ)/$(LIBPREF)Psold$(LIBEXT): $(KOMPOBJS)
	$(RANLIB) $@
$(OBJ)/O_MABORT.o: scn_komp.c
	$(CC) -c $(CFLAGS) -DL_O_MABORT scn_komp.c && \
	$(MV) scn_komp.o $(OBJ)/O_MABORT.o
	$(AR) $(OBJ)/$(LIBPREF)Psold$(LIBEXT) $(OBJ)/O_MABORT.o
$(OBJ)/O_SCANDECODE.o: scn_komp.c
	$(CC) -c $(CFLAGS) -DL_O_SCANDECODE scn_komp.c && \
	$(MV) scn_komp.o $(OBJ)/O_SCANDECODE.o
	$(AR) $(OBJ)/$(LIBPREF)Psold$(LIBEXT) $(OBJ)/O_SCANDECODE.o
$(OBJ)/O_SCAN.o: scn_komp.c
	$(CC) -c $(CFLAGS) -DL_O_SCAN scn_komp.c && \
	$(MV) scn_komp.o $(OBJ)/O_SCAN.o
	$(AR) $(OBJ)/$(LIBPREF)Psold$(LIBEXT) $(OBJ)/O_SCAN.o
#
# Loeschen aller Dateien, die nur zur Generierung benoetigt wurden
#
clean:
	-$(RM) $(OBJ)/$(WILD).o $(WILD).err $(WILD).tmp $(GEN)/$(WILD).o \
		$(DEBRIS)

realclean: 
	-$(RM) $(OBJ)/$(WILD).o $(GEN)/$(WILD).$(WILD)
	$(RM) $(INSTALLBINS) $(INSTALLLIBS)

install: $(INSTALLDIRS)
	@$(INSTALLALL)

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@

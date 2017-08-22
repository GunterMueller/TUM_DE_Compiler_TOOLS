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
# makefile fuer Grammatikeinleser readg
#
TOPDIR=..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#
INSTALLBINS=readg
INSTALLDOCS=NULL
INSTALLLIBS=NULL
INSTALLINCS=NULL
#
SCANGEN=$(GENHOME)/scangen/scangen
SLRGEN=$(GENHOME)/slrgen/slrgen
LALRGEN=$(GENHOME)/lalrgen/lrkgen
TABCONV=$(GENHOME)/nparser/tabconv
PARSDIR=$(PROJHOME)/nparser/
PARSLIB=$(PARSDIR)/obj/$(LIBPREF)Parser$(LIBEXT)
SCANLIB=$(PROJHOME)/scangen/obj/$(LIBPREF)Parscan$(LIBEXT)
READG=$(GENHOME)/readg/readg
#
OBJ=obj
GEN=gen
#
INCLUDES=-I$(PROJHOME)/include -I$(PROJHOME)/scangen \
 -I$(COMMLIB)/include -I$(PROJHOME)/nparser
DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS) $(DBG)
#
all: $(OBJ) $(GEN) readg
$(OBJ) $(GEN):
	$(MKDIR) $@
readg: $(OBJ)/rgp.o $(OBJ)/rgs.o $(OBJ)/readgakt.o 
	$(LD) $(LDFLAGS) -o readg $(OBJ)/readgakt.o $(OBJ)/rgp.o $(OBJ)/rgs.o \
 $(PARSLIB) $(SCANLIB) $(COMMLIB)/lib/$(LIBPREF)Common$(LIBEXT) $(RMFAIL)
$(OBJ)/rgs.o: $(GEN)/rgs.c 
	$(CC) -c $(CFLAGS) $(GEN)/rgs.c && $(MV) rgs.o $(OBJ)
$(GEN)/rgs.c: readg.scb 
	$(SCANGEN) readg.scb $(GEN)/rgs.c
$(OBJ)/rgp.o: $(GEN)/rgp.c 
	$(CC) -c $(CFLAGS) $(GEN)/rgp.c && $(MV) rgp.o $(OBJ)
$(GEN)/rgp.c: $(GEN)/rgp.tab
	$(TABCONV) $(GEN)/rgp.tab $(GEN)/rgp.c
$(GEN)/rgp.tab: $(GEN)/readg.grm
	$(LALRGEN) $(GEN)/readg.grm $(GEN)/rgp.tab
$(GEN)/readg.grm: readg.g
	if [ $(EXEEXI) $(READG) ] ; then \
	  $(READG) readg.g $(GEN)/readg.grm; \
	else \
	  $(CP) readg.grm.boot $(GEN)/readg.grm ; \
	  $(CP) readg.grm.h.boot $(GEN)/readg.grm.h ; \
	fi
$(OBJ)/readgakt.o: readgakt.c $(GEN)/readg.grm.h 
	$(CC) -c $(CFLAGS) -I$(GEN) readgakt.c && $(MV) readgakt.o $(OBJ)

clean:
	-$(RM) $(OBJ)/$(WILD) $(GEN)/$(WILD) $(DEBRIS)

realclean: clean
	$(RM) readg

install: $(INSTALLDIRS)
	@$(INSTALLALL)

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@


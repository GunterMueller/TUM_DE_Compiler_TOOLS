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
#readag/Makefile
#
TOPDIR=../..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#

SATTRGEN=$(GENHOME)/sattrgen/sattrgen
LALRGEN=$(GENHOME)/lalrgen/lrkgen
TABCONV=$(GENHOME)/nparser/tabconv
SCANGEN =$(GENHOME)/scangen/scangen
#
DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS) $(DBG)
INCLUDES=-I../include -I$(PROJHOME)/include -I. \
 -I$(PROJHOME)/scangen -I$(PROJHOME)/nparser -I$(COMMLIB)/include 
#
OBJ=obj
GEN=gen

all: $(OBJ) $(GEN) modSyntax.o

$(OBJ):
	$(MKDIR) $(OBJ)

$(GEN):
	$(MKDIR) $(GEN)

modSyntax.o: $(OBJ)/readagpars.o $(OBJ)/readagscan.o $(OBJ)/AttrBer.o
	$(INCLD) modSyntax.o $(OBJ)/readagpars.o $(OBJ)/readagscan.o \
 $(OBJ)/AttrBer.o 

$(OBJ)/readagpars.o: $(GEN)/readagpars.c 
	$(CC) -c $(CFLAGS) $(GEN)/readagpars.c && $(MV) readagpars.o $(OBJ)

$(OBJ)/readagscan.o: $(GEN)/readagscan.c
	$(CC) -c $(CFLAGS) $(GEN)/readagscan.c  && $(MV) readagscan.o $(OBJ)

$(OBJ)/AttrBer.o: $(GEN)/AttrBer.c
	$(CC) -c $(CFLAGS) $(GEN)/AttrBer.c && $(MV) AttrBer.o $(OBJ)

$(GEN)/readagpars.c : $(GEN)/readag.grm $(GEN)/stamp-readag
	$(LALRGEN) $(GEN)/readag.grm $(GEN)/readag.tab && \
	$(TABCONV) $(GEN)/readag.tab $(GEN)/readagpars.c

$(GEN)/readagscan.c : readag.scb
	$(SCANGEN) readag.scb $(GEN)/readagscan.c

$(GEN)/readag.grm $(GEN)/AttrBer.c: $(GEN)/stamp-readag

$(GEN)/stamp-readag : readag.ag
	if [ $(EXEEXI) $(SATTRGEN) ] ; then \
           $(SATTRGEN) readag.ag && \
	   $(MV) AttrBer.c readag.grm $(GEN); \
         else \
           $(CP) AttrBer.c.boot $(GEN)/AttrBer.c ; \
           $(CP) readag.grm.boot $(GEN)/readag.grm ; \
         fi 
	touch $(GEN)/stamp-readag

clean: 
	-$(RM) $(GEN)/$(WILD) $(OBJ)/$(WILD) $(WILD).err $(DEBRIS)

realclean: clean
	$(RM) $(WILD).o

install: 

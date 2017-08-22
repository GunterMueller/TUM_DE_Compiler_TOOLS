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

GEN = gen
GENINT=$(GEN)/aguserinternform.o $(GEN)/printgram.o $(GEN)/zufuncgram.o
GENTRANS=$(GEN)/agusertransform.o $(GEN)/agtransform.o
GENECTS=$(GEN)/aguserkwgrm.o $(GEN)/cmbi.o $(GEN)/kwgen.o $(GEN)/grmfile.o

DEFINES=
INCLUDES=-I../include -I$(PROJHOME)/include -I$(PROJHOME)/readag/zufunc \
 -I$(COMMLIB)/include -I$(PROJHOME)/readag/include -I$(PROJHOME)/scangen
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=

all: $(GEN) modKwgen.o modInternform.o modTransform.o

modKwgen.o: $(GENECTS)
	$(INCLD) $@ $(GENECTS)

modInternform.o: $(GENINT)
	$(INCLD) $@ $(GENINT)

modTransform.o: $(GENTRANS)
	$(INCLD) $@ $(GENTRANS)

$(GEN):
	$(MKDIR) $(GEN)

$(GEN)/aguserkwgrm.o: aguserkwgrm.c
	$(CC) -c $(CFLAGS) aguserkwgrm.c && $(MV) aguserkwgrm.o $(GEN)

$(GEN)/cmbi.o:  cmbi.c
	$(CC) -c $(CFLAGS) cmbi.c && $(CP) cmbi.o $(GEN)

$(GEN)/kwgen.o:  kwgen.c
	$(CC) -c $(CFLAGS) kwgen.c && $(MV) kwgen.o $(GEN)

$(GEN)/grmfile.o: grmfile.c
	$(CC) -c $(CFLAGS) grmfile.c && $(CP) grmfile.o $(GEN)

$(GEN)/printgram.o: printgram.c
	$(CC) -c $(CFLAGS) printgram.c && $(MV) printgram.o $(GEN)

$(GEN)/zufuncgram.o: zufuncgram.c
	$(CC) -c $(CFLAGS) zufuncgram.c && $(MV) zufuncgram.o $(GEN)

$(GEN)/aguserinternform.o: aguserinternform.c
	$(CC) -c $(CFLAGS) aguserinternform.c && $(MV) aguserinternform.o $(GEN)

$(GEN)/agusertransform.o: agusertransform.c
	$(CC) -c $(CFLAGS) agusertransform.c && $(MV) agusertransform.o $(GEN)

$(GEN)/agtransform.o: agtransform.c
	$(CC) -c $(CFLAGS) agtransform.c && $(MV) agtransform.o $(GEN)

clean:
	-$(RM) $(GEN)/$(WILD)

realclean: clean
	$(RM) $(WILD).o $(DEBRIS)

install:

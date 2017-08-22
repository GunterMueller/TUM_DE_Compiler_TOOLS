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
#einleser/zufunc/Makefile
#
TOPDIR=../..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#

DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS)
INCLUDES=-I../include -I$(PROJHOME)/include \
 -I$(PROJHOME)/nparser -I$(PROJHOME)/scangen -I$(COMMLIB)/include
OBJ=obj
OBJECTS=$(OBJ)/zufunc.o

all: $(OBJ) $(LIBPREF)Zufunc$(LIBEXT)

$(LIBPREF)Zufunc$(LIBEXT): $(OBJECTS) 
	$(RANLIB) $@

$(OBJ):
	$(MKDIR) $(OBJ)

$(OBJ)/zufunc.o : zufunc.c zufunc.h
	$(CC) -c $(CFLAGS) zufunc.c && $(MV) zufunc.o $(OBJ)
	$(AR) $(LIBPREF)Zufunc$(LIBEXT) $(OBJ)/zufunc.o 

clean:	
	-$(RM) obj/$(WILD) $(DEBRIS)

realclean: clean
	$(RM) $(LIBPREF)Zufunc$(LIBEXT) 

install:

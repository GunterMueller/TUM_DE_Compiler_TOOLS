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
#einleser/Makefile
#
TOPDIR=../..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#

DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=
INCLUDES=-I../include -I$(PROJHOME)/include \
 -I$(PROJHOME)/nparser -I$(PROJHOME)/scangen -I$(COMMLIB)/include
OBJ=obj
OBJECTS=$(OBJ)/semfunk.o $(OBJ)/semakt.o $(OBJ)/printgram.o

all: $(OBJ) modEinleser.o

modEinleser.o: $(OBJECTS) 
	$(INCLD) modEinleser.o $(OBJECTS) 
$(OBJ):
	$(MKDIR) $(OBJ)
# Fuer den Einleser :
$(OBJ)/semfunk.o: semfunk.c 
	$(CC) -c $(CFLAGS) semfunk.c  && $(MV) semfunk.o $(OBJ)
$(OBJ)/semakt.o : semakt.c
	$(CC) -c $(CFLAGS) semakt.c && $(MV) semakt.o $(OBJ)
$(OBJ)/printgram.o : printgram.c
	$(CC) -c $(CFLAGS) printgram.c && $(MV) printgram.o $(OBJ)

clean:	
	-$(RM) obj/$(WILD) $(DEBRIS)

realclean: clean
	$(RM) modEinleser.o

install:

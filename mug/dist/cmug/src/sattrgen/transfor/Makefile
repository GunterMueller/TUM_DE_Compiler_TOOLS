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
#transfor/Makefile
#
TOPDIR=../..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#

OBJ = obj
#
DEFINES=
INCLUDES=-I../include -I$(PROJHOME)/include -I$(COMMLIB)/include \
 -I$(PROJHOME)/readag/include -I$(PROJHOME)/readag/zufunc
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=

all: $(OBJ) modTransfor.o 

OBJECTS=$(OBJ)/trans.o $(OBJ)/identcop.o $(OBJ)/transfor.o \
 $(OBJ)/datengen.o $(OBJ)/grm_out.o $(OBJ)/output.o

modTransfor.o: $(OBJECTS)
	$(INCLD) modTransfor.o $(OBJECTS)

$(OBJ):
	$(MKDIR) $(OBJ)

# Fuer das Transformationsprogramm :

$(OBJ)/trans.o  :  trans.c  globals.h
	$(CC) -c $(CFLAGS)  trans.c && $(MV) trans.o $(OBJ)

$(OBJ)/identcop.o :  identcop.c  globals.h
	$(CC) -c $(CFLAGS)  identcop.c && $(MV) identcop.o $(OBJ)

$(OBJ)/transfor.o :  transfor.c  globals.h
	$(CC) -c $(CFLAGS)  transfor.c && $(MV) transfor.o $(OBJ)

$(OBJ)/datengen.o :  datengen.c  globals.h 
	$(CC) -c $(CFLAGS)  datengen.c && $(MV) datengen.o $(OBJ)

$(OBJ)/grm_out.o  :  grm_out.c
	$(CC) -c $(CFLAGS)  grm_out.c && $(MV) grm_out.o $(OBJ)

$(OBJ)/output.o   :  output.c 
	$(CC) -c $(CFLAGS)  output.c && $(MV) output.o $(OBJ)

clean:
	-$(RM) $(OBJ)/$(WILD) $(DEBRIS)

realclean: clean
	$(RM) modTransfor.o

install:

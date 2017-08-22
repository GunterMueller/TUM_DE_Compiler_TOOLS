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
# Makefile fuer die automatische Konfigurationsbestimmung
# letzte Aenderung : 15.03.91, Ulrich Vollath
#
# Aufruf zur Generierung                  : make
# Aufruf zum Loeschen temporaerer Dateien : make clean
#
#
SHELL=/bin/sh
CC=gcc
CP=cp
RM=rm -f
MV=mv
MKDIR=mkdir
ECHO=echo
AR=ar rcv
WILD=*
#
DEFINES=
WARNS=
INCLUDES=
DBG=-g
OPT=
CFLAGS =$(DBG) $(WARNS) $(OPT) $(INCLUDES) $(DEFINES)
#
OBJ=obj
#
# scangen  : normale Version des Generators
# 
all: $(OBJ) getuname
$(OBJ):
	$(MKDIR) $(OBJ)
#
# Ersatz fuer uname-Befehl (1)
#
getuname: getuname.c
	$(CC) $(CFLAGS) -o getuname getuname.c
#
# Loeschen aller Dateien, die nur zur Generierung benoetigt wurden
#
clean:
	-$(RM) $(OBJ)/$(WILD).o 
realclean: clean
	$(RM) getuname
install: 


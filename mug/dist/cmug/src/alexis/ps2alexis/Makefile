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

INSTALLBINS=ps2alexis
INSTALLDOCS=NULL
INSTALLLIBS=NULL
INSTALLINCS=NULL

INCLUDES= -I$(PROJHOME)/alexis/src/include -I.
DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS) $(DBG)

.PHONY: all install clean realclean

all:: ps2alexis

automat.o: table.h
	$(CC) -c $(CFLAGS) $(PROJHOME)/alexis/src/automat.c
 
table.h actions.c: ps2alexis.scb
	$(GENHOME)/alexis/src/alexis ps2alexis.scb

ps2alexis: actions.o automat.o ps2alexis.o
	$(LD) -o ps2alexis $(LDFLAGS) ps2alexis.o automat.o actions.o \
          $(PROJHOME)/alexis/src/alexislib.a || ( $(RM) ps2alexis && /bin/false)

clean:
	- $(RM) $(WILD).o table.h actions.c $(DEBRIS)

realclean: clean
	- $(RM) ps2alexis

install: $(INSTALLDIRS)
	@$(INSTALLALL)

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@

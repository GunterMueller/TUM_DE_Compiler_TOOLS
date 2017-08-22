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

INSTALLBINS=NULL
INSTALLDOCS=NULL
INSTALLLIBS=$(LIBPREF)Sattr$(LIBEXT)
INSTALLINCS=NULL

OBJ = obj
#
INCLUDES=-I$(PROJHOME)/readag/include -I$(PROJHOME)/include \
 -I$(PROJHOME)/scangen
DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS) $(DBG)

.PHONY: all install clean realclean

all: $(OBJ) $(LIBPREF)Sattr$(LIBEXT)

$(LIBPREF)Sattr$(LIBEXT): $(OBJ) $(OBJ)/AttrVerw.o $(OBJ)/getmem.o 
	$(RANLIB) $(LIBPREF)Sattr$(LIBEXT)

$(OBJ):
	$(MKDIR) $(OBJ)

$(OBJ)/AttrVerw.o: AttrVerw.c	 
	$(CC) -c $(CFLAGS) AttrVerw.c && $(MV) AttrVerw.o $(OBJ)
	$(AR) $(LIBPREF)Sattr$(LIBEXT) $(OBJ)/AttrVerw.o

$(OBJ)/getmem.o: getmem.c	 
	$(CC) -c $(CFLAGS) getmem.c && $(MV) getmem.o $(OBJ)
	$(AR) $(LIBPREF)Sattr$(LIBEXT) $(OBJ)/getmem.o

clean:
	-$(RM) $(OBJ)/$(WILD) $(DEBRIS)

realclean: clean
	$(RM) $(LIBPREF)Sattr$(LIBEXT)

install: $(INSTALLDIRS)
	@$(INSTALLALL)

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@


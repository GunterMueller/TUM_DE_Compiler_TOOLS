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
TOPDIR=..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#
# alle Unterdirektories, in denen fuer alle Targets etwas gemacht werden muss
SUBDIRS = lalib
#
LOCALTARGETS=lagen
#
# Taetigkeiten auf dieser Make-Ebene
INSTALLBINS=lagen
INSTALLDOCS=NULL
INSTALLINCS=NULL
INSTALLLIBS=NULL
#
DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=INCLUDES=-I../include -I$(PROJHOME)/include -I$(COMMLIB)/include
#
CMBI=$(PROJHOME)/kwgen/kwlib/cmbi.o
GRMF=$(PROJHOME)/kwgen/kwlib/grmfile.o
PARSMOD=$(PROJHOME)/nparser/obj/ti_mainl.o
PARSLIB=$(PROJHOME)/nparser/obj/$(LIBPREF)Parser$(LIBEXT) \
        $(PROJHOME)/nparser/obj/$(LIBPREF)Parsold$(LIBEXT) 
COMMLIBLIB=$(COMMLIB)/lib/$(LIBPREF)Common$(LIBEXT)
SCANLIB=$(PROJHOME)/scangen/obj/$(LIBPREF)Parscan$(LIBEXT) \
	$(PROJHOME)/scangen/obj/$(LIBPREF)Psold$(LIBEXT)
#
GENPART =lalib/lagen.o lalib/aguserlrgrm.o
EINLESERPART = $(PROJHOME)/readag/modReadag.o
SATTRLIB=$(PROJHOME)/sattrgen/sattrlib/$(LIBPREF)Sattr$(LIBEXT)
ZUFUNCLIB=$(PROJHOME)/readag/zufunc/$(LIBPREF)Zufunc$(LIBEXT)

all::

lagen: $(GENPART) $(EINLESERPART) $(SATTRLIB) $(ZUFUNCLIB)
	$(CC) $(PARSMOD) $(GENPART) $(EINLESERPART) $(SATTRLIB) $(CMBI) \
		$(ZUFUNCLIB) $(PARSLIB) $(SCANLIB) $(COMMLIBLIB) $(GRMF) \
		-o lagen $(RMFAIL)

.PHONY: all install clean realclean

all clean realclean install::
	@for dir in $(SUBDIRS) ; do \
	    ( echo "  making $@ in lagen/$$dir"; \
	      cd $$dir; \
	      $(MAKE) $@ ) \
	  done

all:: $(LOCALTARGETS)

clean::
	$(RM) $(DEBRIS)

realclean:: clean
	$(RM) $(LOCALTARGETS)

install:: $(INSTALLDIRS)
	@$(INSTALLALL)

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@

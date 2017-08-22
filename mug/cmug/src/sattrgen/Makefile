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
# makefile fuer S-Attributauswerter
#
TOPDIR=..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#

# alle Unterdirektories, in denen fuer alle Targets etwas gemacht werden muss
#
SUBDIRS = sattrlib transfor
#
LOCALTARGETS=sattrgen
all::
#
#
# Taetigkeiten auf dieser Make-Ebene
#
INSTALLBINS=sattrgen
INSTALLDOCS=NULL
INSTALLINCS=NULL
INSTALLLIBS=NULL
#
LALRGEN=$(GENHOME)/lalrgen/lrkgen
TABCONV=$(GENHOME)/nparser/tabconv
#
DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=INCLUDES=-I../include -I$(PROJHOME)/include -I$(COMMLIB)/include
#
PARSMOD=$(PROJHOME)/nparser/obj/ti_mainl.o
PARSLIB=$(PROJHOME)/nparser/obj/$(LIBPREF)Parser$(LIBEXT) \
        $(PROJHOME)/nparser/obj/$(LIBPREF)Parsold$(LIBEXT) 
COMMLIBLIB=$(COMMLIB)/lib/$(LIBPREF)Common$(LIBEXT)
SCANLIB=$(PROJHOME)/scangen/obj/$(LIBPREF)Parscan$(LIBEXT) \
	$(PROJHOME)/scangen/obj/$(LIBPREF)Psold$(LIBEXT)
#
OBJ=obj
TRANSFORPART = transfor/modTransfor.o  
EINLESERPART = $(PROJHOME)/readag/modReadag.o 
SATTRLIB=sattrlib/$(LIBPREF)Sattr$(LIBEXT)
ZUFUNCLIB=$(PROJHOME)/readag/zufunc/$(LIBPREF)Zufunc$(LIBEXT)

sattrgen: $(TRANSFORPART) $(EINLESERPART) $(SATTRLIB) $(ZUFUNCLIB)
	@$(ECHO) $(CC) $(PARSMOD) $(TRANSFORPART) $(EINLESERPART) $(SATTRLIB) \
		$(ZUFUNCLIB) $(PARSLIB) $(SCANLIB) $(COMMLIBLIB) \
		-o sattrgen
	@$(CC) $(PARSMOD) $(TRANSFORPART) $(EINLESERPART) $(SATTRLIB) \
		$(ZUFUNCLIB) $(PARSLIB) $(SCANLIB) $(COMMLIBLIB) \
		-o sattrgen $(RMFAIL)

.PHONY: all install clean realclean
all clean realclean install::
	@for dir in $(SUBDIRS) ; do \
	    ( echo "  making $@ in sattrgen/$$dir"; \
	      cd $$dir; \
	      $(MAKE) $@ ) \
	done

all:: $(LOCALTARGETS)

realclean::
	$(RM) $(LOCALTARGETS) $(DEBRIS)

install:: $(INSTALLDIRS)
	@$(INSTALLALL)

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@




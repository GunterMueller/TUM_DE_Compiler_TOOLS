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
# makefile fuer Grammatik-Einleser
#
TOPDIR=..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#

# alle Unterdirektories, in denen fuer alle Targets etwas gemacht werden muss
#
SUBDIRS = einleser syntax zufunc
#
LOCALTARGETS=modReadag.o
LDFLAGS=
all::
#
#
# Taetigkeiten auf dieser Make-Ebene
#
modReadag.o: syntax/modSyntax.o einleser/modEinleser.o 
	$(INCLD) modReadag.o syntax/modSyntax.o \
 einleser/modEinleser.o
#
#
.PHONY: all install clean realclean
all clean realclean install::
	@for dir in $(SUBDIRS) ; do \
	    ( echo "  making $@ in readag/$$dir"; \
	      cd $$dir; \
	      $(MAKE) $(MFLAGS) $@ ) \
	done

all:: $(LOCALTARGETS)

realclean::
	$(RM) $(LOCALTARGETS) $(DEBRIS)

install::

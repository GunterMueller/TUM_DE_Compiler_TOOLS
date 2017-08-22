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
TOPDIR=..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#

INSTALLBSPDIR=$(INSTALLDIR)/bsp
INSTALLSPRACHES=pascal mima expr
INSTALLDIRS=$(INSTALLDIR) $(INSTALLBSPDIR) \
 $(INSTALLBSPDIR)/mima $(INSTALLBSPDIR)/pascal

# alle Unterdirektories, in denen fuer alle Targets etwas gemacht werden muss
SUBDIRS=mima pascal expr

.PHONY:all install clean realclean test

all clean realclean install test:
	@for dir in $(SUBDIRS) ; do \
	    ( echo "  making $@ in bsp/$$dir"; \
	      cd $$dir; \
	      $(MAKE)  $@ ) \
	done

#
# (c) copyright 1995 by Technische Universitaet Muenchen, Germany
#
#	This product is part of MUGBrowser
#	MUGBrowser is a part of the compiler writing system
#	MUG (Modularer Uebersetzer-Generator, TU Muenchen)
#
# Permission to use, duplicate or disclose this software must be
# obtained in writing. Requests for such permissions may be sent to
#
#	Prof. Dr. J. Eickel
#	Institut fuer Informatik
#	Technische Universitaet Muenchen
#	D-80290 Muenchen
#	Germany
#
# No version of this implementation may be used or distributed for gain,
# all listings must contain our copyright notice, and the headings
# produced by MUG-Modules must contain the text "MUG" and "TU - Muenchen".
#
TOPDIR=..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all

# alle Unterdirektories, in denen fuer alle Targets etwas gemacht werden muss
#
SUBDIRS = doc
#
LOCALTARGETS=mugbrowser
#
#
# Taetigkeiten auf dieser Make-Ebene
#
INSTALLBINS=mugbrowser
INSTALLDOCS=NULL
INSTALLINCS=header/browse_proc.c header/browse_ds.h header/browse_len.h
INSTALLLIBS=NULL


SRC	= src
HEADER	= header
ICONS	= icons

all:: mugbrowser

mugbrowser:	mugbrowse.o visualize.o
		$(CC) -o mugbrowser mugbrowse.o visualize.o $(X11LIB) \
		$(SOCKETLIB) -lXaw -lXmu -lXt -lXext -lX11

mugbrowse.o:	$(SRC)/mugbrowse.c $(HEADER)/browse_const.h \
		$(HEADER)/browse_ds.h $(HEADER)/browse_len.h \
		$(HEADER)/browse_types.h
		$(CC) -c $(SRC)/mugbrowse.c

visualize.o:	$(SRC)/visualize.c $(HEADER)/visualize.h \
		$(HEADER)/browse_const.h $(HEADER)/browse_len.h \
		$(HEADER)/browse_types.h $(HEADER)/configure.h \
		$(ICONS)/internal/* $(ICONS)/compiler/* \
		$(ICONS)/geometrics/* $(ICONS)/listings/* $(ICONS)/numbers/* \
		$(ICONS)/objects/* $(ICONS)/solids/* $(ICONS)/letters/*
		$(CC) $(X11INC) -c $(SRC)/visualize.c

all clean realclean install::
	@for dir in $(SUBDIRS) ; do \
		( echo "  making $@ in browser/$$dir"; \
		  cd $$dir; \
		  $(MAKE) $@ ) \
	done


clean::
	@$(RM) visualize.o mugbrowse.o $(DEBRIS)

realclean:: clean
	$(RM) $(LOCALTARGETS)

install:: $(INSTALLDIRS)
	@$(INSTALLALL)


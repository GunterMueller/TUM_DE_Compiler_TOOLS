#
# (c) copyright 1995 by Technische Universitaet Muenchen, Germany
#
#       This product is part of MUGBrowser
#       MUGBrowser is a part of the compiler writing system
#       MUG (Modularer Uebersetzer-Generator, TU Muenchen)
#
# Permission to use, duplicate or disclose this software must be
# obtained in writing. Requests for such permissions may be sent to
#
#       Prof. Dr. J. Eickel
#       Institut fuer Informatik
#       Technische Universitaet Muenchen
#       D-80290 Muenchen
#       Germany
#
# No version of this implementation may be used or distributed for gain,
# all listings must contain our copyright notice, and the headings
# produced by MUG-Modules must contain the text "MUG" and "TU - Muenchen".
#

#
#
TOPDIR=../..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#
INSTALLBINS=NULL
INSTALLLIBS=NULL
INSTALLINCS=NULL
INSTALLDOCS=MUGBrowser.dvi MUGBrowser.StyleGuide MUGBrowser.Kurzdoku

.PHONY: all clean realclean install

all: MUGBrowser.dvi

MUGBrowser.dvi:  MUGBrowser.tex
	latex MUGBrowser.tex
	latex MUGBrowser.tex

clean realclean:
	@$(RM) $(WILD).dvi $(WILD).aux $(WILD).log $(WILD).toc $(DEBRIS)

install: $(INSTALLDIRS)
	@$(INSTALLALL)

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@


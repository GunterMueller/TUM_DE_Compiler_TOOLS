################################################################################
#
#	ACHTUNG! ACHTUNG! ACHTUNG! ACHTUNG! ACHTUNG! ACHTUNG!
#
#	vor make-Aufruf Pfad-Namen anpassen im File:
#			config/makeinclude.all
#
################################################################################
#
# Hauptmakefile fuer das CMUG-System
# 
# (c) copyright 1991 by Technische Universitaet Muenchen, Germany
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
# diverse Betriebssystem-Kommandos
MAKE=make
CHMOD=chmod
RM=rm -f
MV=mv
ABORT=/bin/false

TOPDIR=.
#
# Subdirectory fuer die automatische Konfiguration
CONFIG=$(TOPDIR)/config
#
#maschinenunabhaengiges Include-File
include $(CONFIG)/makeinclude.all
#
#zu generierendes maschinenabhaengiges Include-File
INCLUDEMACH=$(CONFIG)/makeinclude.mach
#
# alle Unterdirektories, in denen fuer alle Targets etwas gemacht werden muss
#
SUBDIRS=lalrgen nparser scangen readg readag sattrgen kombin kwgen lagen \
	alexis include doc browser bsp 
TESTDIRS=bsp
#
# Rahmen fuer den Aufruf der make's in Unterverzeichnissen
#
.PHONY:all install clean realclean dist test configmach
all install clean realclean:: $(COMMLIB) configmach
	@for dir in $(SUBDIRS) ; do \
	  ( echo "making $@ in $$dir"; \
	    cd $$dir; \
	    $(MAKE) $(MFLAGS) $@ ) \
	done
clean realclean::
	@for dir in $(CONFIG); do \
	  ( echo "making $@ in $$dir"; \
	    cd $$dir; \
	    $(MAKE) $(MFLAGS) $@) \
	done
realclean::
	$(RM) -r run cmug.tgz
	$(RM) $(INCLUDEMACH)
test:
	@for dir in $(TESTDIRS) ; do \
	  ( echo "making $@ in $$dir"; \
	    cd $$dir; \
	    $(MAKE) $(MFLAGS) $@ ) \
	done
$(COMMLIB):
	@echo "Bibliothek in $(COMMLIB) noch nicht installiert"
	@$(ABORT)
$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@

#Anlegen des files $(INCLUDEMACH) = symb. Link auf config/<uname>.flg
configmach:
	@$(CONFIG)/genmakeincludemach $(INCLUDEMACH)
#
# Erstellen der Distribution
#
dist:
	$(RM) cmug.tgz
	tar crf - -C .. ./cmug | gzip > /tmp/cmug.tgz && \
	$(MV) /tmp/cmug.tgz .

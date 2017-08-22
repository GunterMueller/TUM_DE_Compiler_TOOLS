#
# Beispiel-Makefile fuer einen Uebersetzer mit Kellerattributierer
#
# zu uebersetzende Sprache
LANG=expr
#
MUGHOME=/usr/wiss/wittner/cmug-installed
COMMLIBHOME=/usr/proj/commlib
#
COMMLIB=$(COMMLIBHOME)/lib/libCommon.a
SATTRLIB = $(MUGHOME)/lib/libSattr.a
PARSLIB=$(MUGHOME)/lib/libParser.a
PARSMOD=$(MUGHOME)/lib/ti_mainl.o
SCANLIB=$(MUGHOME)/lib/libParscan.a
#
INCLUDES = -I$(MUGHOME)/include -I$(COMMLIBHOME)/include -I.
DBG=-g
CFLAGS =$(INCLUDES) $(DBG)
LDFLAGS= $(DBG)
#
#verwendeter C-Compiler
CC=cc
#verwendeter Loader
LD=$(CC)
# verwendete cmug-Generatoren
#
LALRGEN=$(MUGHOME)/bin/lrkgen
TABCONV=$(MUGHOME)/bin/tabconv
SCANGEN=$(MUGHOME)/bin/scangen
SATTRGEN=$(MUGHOME)/bin/sattrgen
#
#
.PHONY: all install clean realclean
all: gen $(LANG)
gen:
	mkdir gen
#      *************** Compiler *******************
$(LANG): gen/$(LANG)pars.o gen/$(LANG)scan.o gen/$(LANG)sem.o gen/AttrBer.o
	$(LD) $(LDFLAGS) $(PARSMOD) gen/$(LANG)pars.o gen/$(LANG)scan.o \
 gen/$(LANG)sem.o gen/AttrBer.o $(PARSLIB) $(SCANLIB) $(SATTRLIB) \
 $(COMMLIB) -o $(LANG) || ( /bin/rm -f $(LANG) && /bin/false)

gen/$(LANG)pars.o: gen/$(LANG)pars.c 
	$(CC) -c $(CFLAGS) gen/$(LANG)pars.c  && mv $(LANG)pars.o gen

gen/$(LANG)scan.o: gen/$(LANG)scan.c
	$(CC) -c $(CFLAGS) gen/$(LANG)scan.c  && mv $(LANG)scan.o gen

gen/AttrBer.o: gen/AttrBer.c AttrGlob.h
	$(CC) -c $(CFLAGS) gen/AttrBer.c  && mv AttrBer.o gen

gen/$(LANG)sem.o: $(LANG)sem.c
	$(CC) -c $(CFLAGS) $(LANG)sem.c  && mv $(LANG)sem.o gen

gen/$(LANG)pars.c : gen/$(LANG).grm
	$(LALRGEN) gen/$(LANG).grm gen/$(LANG)pars.tab && \
	$(TABCONV) gen/$(LANG)pars.tab gen/$(LANG)pars.c

gen/$(LANG)scan.c : $(LANG).scb
	$(SCANGEN) $(LANG).scb gen/$(LANG)scan.c

gen/AttrBer.c gen/$(LANG).grm: gen/stamp-sattrgen
gen/stamp-sattrgen: $(LANG).ag
	$(SATTRGEN) $(LANG).ag && mv AttrBer.c $(LANG).grm gen
	touch gen/stamp-sattrgen
clean:
	-/bin/rm -f gen/* compiler.err
realclean: clean
	/bin/rm -f $(LANG)
test: gen $(LANG)
	for srcfile in $(LANG)src/* ; do \
	  wc $$srcfile ; \
	  time ./$(LANG) $$srcfile || /bin/true; \
	done
install:

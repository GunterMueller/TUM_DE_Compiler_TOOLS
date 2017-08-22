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

SPRACHE=alexis
INSTALLBINS=$(SPRACHE)
INSTALLDOCS=NULL
INSTALLLIBS=alexislib.a automat.c
INSTALLINCS=include/actions.h include/automat.h include/buffer.h \
	include/automat_proc.h include/cdebug.h include/scan.h mugdefs.sci 
#
#
PARSLIB=$(PROJHOME)/nparser/obj/libParser.a
SCANLIB=alexislib.a
#
INCLUDES = -I./include -I$(PROJHOME)/nparser -I$(COMMLIB)/include \
	-I$(PROJHOME)/kombin -I./gen -I$(PROJHOME)/include
DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS) $(DBG)
 

# verwendete cmug-Generatoren
#
LALRGEN=$(GENHOME)/lalrgen/lrkgen
TABCONV=$(GENHOME)/nparser/tabconv
SCANGEN=./alexis
KWGEN=$(GENHOME)/kwgen/kwgen
KOMBIN=$(GENHOME)/kombin/kombin
#
#
ALEXMOD=mugactio.o alexerr.o readfunct.o autops.o autstack.o error.o eveset.o \
	kompress.o maketab.o minimier.o quickset.o stateset.o var.o genactio.o \
	alexsem.o strfunctions.o sem-schnittstelle.o  

.PHONY: all install clean realclean

all: gen alexislib.a $(SPRACHE)
gen:
	- $(MKDIR) gen
#      *************** Compiler *******************
$(SPRACHE): gen/$(SPRACHE)pars.o gen/$(SPRACHE)scan.a $(ALEXMOD) gen/$(SPRACHE)comp.o
	$(CC) -o  $(SPRACHE) $(LDFLAGS) $(PARSMOD) gen/$(SPRACHE)pars.o \
        alexislib.a \
	gen/$(SPRACHE)scan.a $(ALEXMOD) gen/$(SPRACHE)comp.o  \
	$(PARSLIB) alexislib.a $(COMMLIB)/lib/libCommon.a gen/$(SPRACHE)scan.a \
	|| ( $(RM) $(SPRACHE) && /bin/false)


gen/$(SPRACHE)pars.o: gen/$(SPRACHE)pars.c 
	$(CC) -c $(CFLAGS) gen/$(SPRACHE)pars.c
	$(MV) $(SPRACHE)pars.o gen

gen/$(SPRACHE)scan.a: gen/table.h gen/actions.c
	$(CC) -c $(CFLAGS) automat.c gen/actions.c 
	$(AR) $(SPRACHE)scan.a automat.o actions.o 
	$(RANLIB) $(SPRACHE)scan.a
	$(RM) actions.o automat.o 
	$(MV) $(SPRACHE)scan.a gen 

gen/$(SPRACHE)comp.o: gen/$(SPRACHE)comp.c include/AttrGlob.h
	$(CC) -c $(CFLAGS) gen/$(SPRACHE)comp.c
	$(MV) $(SPRACHE)comp.o gen

gen/$(SPRACHE)pars.c : gen/$(SPRACHE).grm
	$(LALRGEN) gen/$(SPRACHE).grm gen/$(SPRACHE)pars.tab
	$(TABCONV) gen/$(SPRACHE)pars.tab gen/$(SPRACHE)pars.c

gen/actions.c gen/table.h : $(SPRACHE).scb
	if [ -f $(SCANGEN) ] ; then \
	        $(SCANGEN) $(SPRACHE).scb ; \
	        $(MV) table.h gen ; \
	        $(MV) actions.c gen ; \
	else \
	   $(CP) actions.c.boot gen/actions.c ; \
	   $(CP) table.h.boot gen/table.h ; \
	fi

gen/$(SPRACHE)comp.c: gen/stamp-attrgen
	cd gen ; $(KOMBIN) gtok $(SPRACHE) $(SPRACHE)

gen/$(SPRACHE).Desk gen/$(SPRACHE).grm: gen/stamp-attrgen

gen/stamp-attrgen: $(SPRACHE).ag
	cd gen ; $(KWGEN) ../$(SPRACHE).ag
	touch gen/stamp-attrgen

alexislib.a: scan.o buffer.o symtab.o mugactio.o mugerr.o var.o
	$(AR) alexislib.a scan.o buffer.o symtab.o mugactio.o mugerr.o var.o
	$(RANLIB) alexislib.a

clean:
	$(RM) -r gen
	$(RM) $(WILD).o $(DEBRIS)

realclean: clean
	$(RM) $(SPRACHE) $(SPRACHE)lib.a

.c.o:
	$(CC) -c $(CFLAGS) $<
	$(CP) $*.o gen

install:: $(INSTALLDIRS)
	@$(INSTALLALL)

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@


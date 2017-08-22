#
TOPDIR=../..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all

SPRACHE=expr
#
#
SATTRLIB = $(PROJHOME)/sattrgen/sattrlib/$(LIBPREF)Sattr$(LIBEXT)
PARSMOD=$(PROJHOME)/nparser/obj/ti_mainl.o
PARSLIB=$(PROJHOME)/nparser/obj/$(LIBPREF)Parser$(LIBEXT)
SCANLIB=$(PROJHOME)/scangen/obj/$(LIBPREF)Parscan$(LIBEXT)
COMMLIBLIB=$(COMMLIB)/lib/$(LIBPREF)Common$(LIBEXT)
#
DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS) $(DBG)
INCLUDES = -I$(PROJHOME)/include -I$(PROJHOME)/nparser \
 -I$(PROJHOME)/scangen -I$(COMMLIB)/include -I.
#
# verwendete cmug-Generatoren
#
LALRGEN=$(GENHOME)/lalrgen/lrkgen
TABCONV=$(GENHOME)/nparser/tabconv
SCANGEN=$(GENHOME)/scangen/scangen
SATTRGEN=$(GENHOME)/sattrgen/sattrgen
#
OBJ = obj
GEN=gen
#
TOUCH=touch
#
.PHONY: all install clean realclean

all: $(OBJ) $(GEN) $(SPRACHE)

$(OBJ) $(GEN):
	$(MKDIR) $@

install :: all

#      *************** Compiler *******************
$(SPRACHE): $(OBJ)/$(SPRACHE)pars.o $(OBJ)/$(SPRACHE)scan.o \
         $(OBJ)/$(SPRACHE)sem.o $(OBJ)/AttrBer.o
	$(LD) $(LDFLAGS) $(PARSMOD) $(OBJ)/$(SPRACHE)pars.o $(OBJ)/$(SPRACHE)scan.o \
 $(OBJ)/$(SPRACHE)sem.o $(OBJ)/AttrBer.o $(PARSLIB) $(SCANLIB) $(SATTRLIB) \
 $(COMMLIBLIB) -o $(SPRACHE) $(RMFAIL)

$(OBJ)/$(SPRACHE)pars.o: $(GEN)/$(SPRACHE)pars.c 
	$(CC) -c $(CFLAGS) $(GEN)/$(SPRACHE)pars.c  && $(MV) $(SPRACHE)pars.o $(OBJ)

$(OBJ)/$(SPRACHE)scan.o: $(GEN)/$(SPRACHE)scan.c
	$(CC) -c $(CFLAGS) $(GEN)/$(SPRACHE)scan.c  && $(MV) $(SPRACHE)scan.o $(OBJ)

$(OBJ)/AttrBer.o: $(GEN)/AttrBer.c AttrGlob.h
	$(CC) -c $(CFLAGS) $(GEN)/AttrBer.c  && $(MV) AttrBer.o $(OBJ)

$(OBJ)/$(SPRACHE)sem.o: $(SPRACHE)sem.c
	$(CC) -c $(CFLAGS) $(SPRACHE)sem.c  && $(MV) $(SPRACHE)sem.o $(OBJ)

$(GEN)/$(SPRACHE)pars.c : $(GEN)/$(SPRACHE).grm
	$(LALRGEN) $(GEN)/$(SPRACHE).grm $(GEN)/$(SPRACHE)pars.tab && \
	$(TABCONV) $(GEN)/$(SPRACHE)pars.tab $(GEN)/$(SPRACHE)pars.c

$(GEN)/$(SPRACHE)scan.c : $(SPRACHE).scb
	$(SCANGEN) $(SPRACHE).scb $(GEN)/$(SPRACHE)scan.c

$(GEN)/AttrBer.c $(GEN)/$(SPRACHE).grm: $(GEN)/stamp-sattrgen
$(GEN)/stamp-sattrgen: $(SPRACHE).ag
	$(SATTRGEN) $(SPRACHE).ag && $(MV) AttrBer.c $(SPRACHE).grm $(GEN)
	$(TOUCH) $(GEN)/stamp-sattrgen

clean:
	-$(RM) $(OBJ)/$(WILD) $(GEN)/$(WILD)

realclean: clean
	$(RM) $(SPRACHE)

test: $(OBJ) $(SPRACHE)
	for srcfile in $(SPRACHE)src/$(WILD) ; do \
	  wc $$srcfile ; \
	  time ./$(SPRACHE) $$srcfile || /bin/true; \
	done

install:: $(INSTALLDIRS)
	$(RM) -r $(INSTALLBSPDIR)/$(SPRACHE)
	$(MKDIR) $(INSTALLBSPDIR)/$(SPRACHE)
	$(CP) -r $(SPRACHE).ag $(SPRACHE).scb $(SPRACHE)sem.c \
		$(SPRACHE)src AttrGlob.h $(INSTALLBSPDIR)/$(SPRACHE)
	$(CP) Makefile.installed $(INSTALLBSPDIR)/$(SPRACHE)/Makefile

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@


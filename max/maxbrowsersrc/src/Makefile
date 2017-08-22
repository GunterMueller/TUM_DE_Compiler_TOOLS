include ../config/MACHINE.flg

# zu generierende Systemteile
SRCSUBDIRS=bim bim_util Node tprint attr

ARCHIVFILES=bim_util/bim_util.o Node/Node.o tprint/tprint.o attr/attr.o
ARCHIVNAME=$(INSTALLIBDIR)/maxbrowse.a
INCFILES=tprint/maxbrowse.h inc/nodeinfo.h inc/attr_mask.h \
	 inc/tprint_structs.h bim/bim_std.c
PROGFILES=bim/bim
SRCSUBDIRS=bim bim_util Node tprint attr

# default target

all: 
	@for i in $(SRCSUBDIRS) ; do \
	(echo "      making $@ in $$i";cd $$i ; $(MAKE) INSTALLDIR=$(INSTALLDIR) HOMEDIR=$(HOMEDIR) all ;) done

install: all
	-$(MKDIR) $(INSTALLDIR)
	-$(MKDIR) $(INSTALLBINDIR)
	-$(MKDIR) $(INSTALLIBDIR)
	-$(MKDIR) $(INSTALLINCDIR)
	$(AR) $(ARCHIVNAME) $(ARCHIVFILES)
	$(RANLIB) $(ARCHIVNAME)
	(cd $(INSTALLIBDIR) ; $(CHMOD) a+rx * ; )
	$(CP) $(PROGFILES) $(INSTALLBINDIR)
	(cd $(INSTALLBINDIR) ; $(CHMOD) a+rx * ; )
	$(CP) $(INCFILES) $(INSTALLINCDIR)
	(cd $(INSTALLINCDIR) ; $(CHMOD) a+rx * ; )

test:

clean realclean::
	@$(RM) $(RMFILES)
	@for i in $(SRCSUBDIRS) ; do \
	( echo "      making $@ in $$i";cd $$i ; $(MAKE) clean ; ) done

realclean:: clean
	@$(RM) $(RMFILES)


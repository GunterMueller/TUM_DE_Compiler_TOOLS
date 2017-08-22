#Name des aktuellen DIRs
HOMEDIR=/usr/proj/maxbrowsersrc
INSTALLDIR=/usr/proj/uebbau/max

#basename von HOMEDIR
DISTNAME=maxbrowsersrc

SUBDIRS=src

all clean realclean install test : configuration
	@for dir in $(SUBDIRS) ; do \
          ( echo "   making $@ in $$dir"; \
            cd $$dir; \
            $(MAKE) INSTALLDIR=$(INSTALLDIR) HOMEDIR=$(HOMEDIR) $@ ) \
        done


configuration:
	@( cd config ; ./config )

dist: realclean
	rm -f $(DISTNAME).tgz
	tar cf - -C .. ./$(DISTNAME) |gzip > /tmp/$(DISTNAME).tgz && \
	mv /tmp/$(DISTNAME).tgz .


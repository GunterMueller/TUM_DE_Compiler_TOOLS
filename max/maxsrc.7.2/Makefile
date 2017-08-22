INSTALLDIR=/usr/proj/uebbau/max

#basename des aktuellen Verzeichnisses
DIST=maxsrc.7.2

SUBDIRS=src

all clean realclean install : configuration
	@for dir in $(SUBDIRS) ; do \
          ( echo "   making $@ in $$dir"; \
            cd $$dir; \
            make INSTALLDIR=$(INSTALLDIR) $@ ) \
        done

test:

configuration:
	@( cd config ; ./config )

dist: realclean
	rm -f $(DIST).tgz
	tar cf - -C .. ./$(DIST) |gzip > /tmp/$(DIST).tgz && \
	mv /tmp/$(DIST).tgz .

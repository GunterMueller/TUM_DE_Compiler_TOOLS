
all: ../configure config_ac.h.in

config_ac.h.in: configure.in acconfig.h
	rm -f ac.h.in
	autoheader configure.in >config_ac.h.in

../configure: configure.in aclocal.m4
	rm -f ../configure
	autoconf configure.in >../configure
	chmod a+x ../configure

clean:

distclean:
	-rm -f ../config.status ../config.cache ../config.log config_ac.h

realclean: distclean
	-rm -f ../configure config_ac.h.in


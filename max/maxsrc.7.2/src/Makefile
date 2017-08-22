#
# Makefile for MAX Version 7.2
# Version : extended Patterns, optimierte Auswertung,
#           Generation of Scanner, Parser and Makefile,
#           Type Checking
# 12.9.95
#

include ../config/MACHINE.flg

MAXOPTS=
MAX=max

OBJS = y.tab.c y.tab.o lex.yy.c  max_std.o max_spec.o max_spec.c max_spec.h \
	max_extrn.o max_hgen.o max_ggen.o max_sgen.o max_ygen.o max_dgen.o \
	typecheck.o sigma.o metasort.o max.o 

all: max
max : $(OBJS)
	$(CC) $(DEBUG) -o max y.tab.o  max_std.o  max_spec.o \
	max_extrn.o  max.o  max_ygen.o max_hgen.o max_ggen.o max_sgen.o \
	max_dgen.o metasort.o sigma.o typecheck.o

y.tab.o: y.tab.c  lex.yy.c  max_spec.h
	$(CC) $(CFLAGS) -c y.tab.c

y.tab.c: max_pars.y 
	$(YACC) max_pars.y	

lex.yy.c: max_scan.l 
	$(LEX) max_scan.l
	
max_std.o :  max_std.c  max_std.h
	$(CC) $(CFLAGS) -c max_std.c

max_spec.o :  max_spec.c
	$(CC) $(CFLAGS) -c max_spec.c

max_spec.c max_spec.h :  max_spec.m
	if [ -x $(MAX) ] ; then $(MAX) $(MAXOPTS) max_spec.m ; \
        else cp max_boot.c max_spec.c ; \
             cp max_boot.h max_spec.h ; \
             cp max_boot.g max_spec.g ; fi

max_extrn.o :  max_extrn.c  max_spec.h  max.h
	$(CC) $(CFLAGS) -c max_extrn.c

max_hgen.o :  max_hgen.c  max_spec.h  max.h
	$(CC) $(CFLAGS) -c max_hgen.c

max_ggen.o :  max_ggen.c  max_spec.h  max.h
	$(CC) $(CFLAGS) -c max_ggen.c

max_sgen.o :  max_sgen.c  max_spec.h  max.h
	$(CC) $(CFLAGS) -c max_sgen.c

max_ygen.o :  max_ygen.c  max_spec.h  max.h
	$(CC) $(CFLAGS) -c -DMAXPATHNAME=\"$(INSTALLDIR)/bin\" max_ygen.c

max_dgen.o :  max_dgen.c  max_spec.h  max.h
	$(CC) $(CFLAGS) -c max_dgen.c

max.o :  max.c  max_spec.h  max.h
	$(CC) $(CFLAGS) -c max.c

typecheck.o : typecheck.c  max.h max_spec.h metasort.h typecheck.h
	$(CC) $(CFLAGS) -c typecheck.c

metasort.o : metasort.c metasort.h typecheck.h max_spec.h
	$(CC) $(CFLAGS) -c metasort.c

sigma.o : sigma.c max_spec.h typecheck.h metasort.h
	$(CC) $(CFLAGS) -c sigma.c

install: max max_std.o
	mkdirhier $(INSTALLDIR)/bin $(INSTALLDIR)/obj
	$(CP) max $(INSTALLDIR)/bin/
	$(CP) max_std.o $(INSTALLDIR)/obj/
	$(CHMOD) a+rx $(INSTALLDIR)/bin/max
	$(CHMOD) a+r $(INSTALLDIR)/obj/max_std.o

clean:
	@$(RM) *.o y.tab.c lex.yy.c max_spec.[cgh] max

realclean: clean
	@$(RM) ../config/MACHINE.flg max



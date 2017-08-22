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
# Makefile fuer Bibliotheksroutinen libCommon.a
#
SHELL=/bin/sh
#
# Directory, in die Library generiert wird (= current directory Makefile)
#
HOME=/sw/free/pkg/MUG/dist/commlib/src
#
# Directory, in dem die Library installiert wird
#
INSTALLDIR=/sw/free/pkg/MUG
INSTALLBINDIR=$(INSTALLDIR)/bin
INSTALLBSPDIR=$(INSTALLDIR)/lib/bsp
INSTALLLIBDIR=$(INSTALLDIR)/lib
INSTALLINCDIR=$(INSTALLDIR)/include
INSTALLDOCDIR=$(INSTALLDIR)/lib/doc
INSTALLDIRS=$(INSTALLDIR) $(INSTALLBINDIR) $(INSTALLBSPDIR) \
            $(INSTALLLIBDIR) $(INSTALLINCDIR) $(INSTALLDOCDIR)
CMBINFLAGS=755 # rwxr-xr-x
CMLIBFLAGS=755 # rwxr-xr-x
CMINCFLAGS=644 # rw-r--r--
CMDOCFLAGS=755 # rw-r--r--
CMDIRFLAGS=755 # rwxr-xr-x
#
#
INSTALLBINS=
INSTALLBSPS=
INSTALLLIBS=libCommon.a
INSTALLINCS=allocate.h defs.h listen.h magics.h site.h \
checks.h listenpdt.h millisec.h dbg.h  list_epd.h readfile.h
#
AR=ar r
#RANLIB=ranlib
RANLIB=true #Solaris hat kein ranlib
MV=mv
RM=rm -f
CP=cp
MKDIR=mkdir
WILD=*
CHMOD=chmod
#
OBJ=obj
#
CC=gcc
DCC=gcc
PCC=gcc
DEFINES=-DHZ=50
WARN=#-Wall
OPT=#+O3 -fstrength-reduce -fcombine-regs -fomit-frame-pointer -fforce-mem -fforce-addr -finline-functions -fcaller-saves
POPT=#-O -fstrength-reduce -fcombine-regs 
# -fforce-mem -fforce-addr -finline-functions -fcaller-saves
DBG=-g
CFLAGS =-c $(WARN) $(OPT) $(INCLUDES) $(DEFINES)
DCFLAGS=-c -g $(DEFINES)
PCFLAGS=-c $(POPT) $(INCLUDES) $(DEFINES)
#
OE=.o
AE=.a
OP=$(OBJ)/
#
all: $(OBJ)
	$(MAKE) OE=_nd$(OE) AE=$(AE) libCommon.a
	$(MAKE) OE=_g$(OE) AE=_g$(AE) CC=$(DCC) "CFLAGS=$(DCFLAGS)" \
 libCommon_g$(AE)
	$(MAKE) OE=_p$(OE) AE=_p$(AE) CC=$(PCC) "CFLAGS=$(PCFLAGS)" \
 libCommon_p$(AE)
	$(MAKE) OE=_d$(OE) AE=_d$(AE) CC=$(DCC) "CFLAGS=$(DCFLAGS) -DDEBUG" \
 libCommon_d$(AE)
$(OBJ):
	$(MKDIR) $(OBJ)
#
OBJS= $(OP)allocate$(OE) $(OP)checks$(OE) $(OP)listen$(OE) \
 $(OP)dbg$(OE) $(OP)millisec$(OE) $(OP)readfile$(OE)
libCommon$(AE): $(OBJS)
	$(AR) libCommon$(AE) $(OBJS)
	$(RANLIB) libCommon$(AE)
#
$(OP)allocate$(OE): allocate.c allocate.h checks.h
	$(CC) $(CFLAGS) allocate.c && $(MV) allocate.o $(OP)allocate$(OE)
$(OP)listen$(OE): listen.c listen.h allocate.h checks.h
	$(CC) $(CFLAGS) listen.c && $(MV) listen.o $(OP)listen$(OE)
$(OP)checks$(OE): checks.c checks.h
	$(CC) $(CFLAGS) checks.c && $(MV) checks.o $(OP)checks$(OE)
$(OP)dbg$(OE): dbg.c dbg.h
	$(CC) $(CFLAGS) dbg.c && $(MV) dbg.o $(OP)dbg$(OE)
$(OP)millisec$(OE): millisec.c millisec.h
	$(CC) $(CFLAGS) millisec.c && $(MV) millisec.o $(OP)millisec$(OE)
$(OP)readfile$(OE): readfile.c readfile.h
	$(CC) $(CFLAGS) readfile.c && $(MV) readfile.o $(OP)readfile$(OE)
clean:
	-$(RM) $(OP)$(WILD).o 
	-$(RM) mylib.bak core mon.out gmon.out
realclean: clean
	-$(RM) $(WILD).a
dist:
	$(RM) commlib.tgz
	tar crf - -C .. ./commlib | gzip > /tmp/commlib.tgz && \
 $(MV) /tmp/commlib.tgz .
install: all $(INSTALLDIRS)
#	$(CP) $(INSTALLBINS) $(INSTALLBINDIR)
#	$(CHMOD) $(CMBINFLAGS) $(INSTALLBINDIR)/*	
	$(CP) $(INSTALLLIBS) $(INSTALLLIBDIR)
	$(RANLIB) $(INSTALLLIBDIR)/lib$(WILD).a
	$(CHMOD) $(CMLIBFLAGS) $(INSTALLLIBDIR)/*	
	$(CP) $(INSTALLINCS) $(INSTALLINCDIR)
	$(CHMOD) $(CMINCFLAGS) $(INSTALLINCDIR)/*	
$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@



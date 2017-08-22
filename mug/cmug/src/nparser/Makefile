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
# makefile fuer lalr-Tabellen-Interpreter
#
TOPDIR=..
include $(TOPDIR)/config/makeinclude.mach
include $(TOPDIR)/config/makeinclude.all
#

INSTALLBINS=tabconv
INSTALLDOCS=NULL
INSTALLLIBS=$(OBJ)/$(LIBPREF)Parser$(LIBEXT) $(OBJ)/$(LIBPREF)Parsold$(LIBEXT) \
 $(OBJ)/ti_mainr.o $(OBJ)/ti_mainl.o 
INSTALLINCS=ti_defs.h ti_zugr.h

OBJ=obj
LIBOBJS=$(COMMLIB)/lib/$(LIBPREF)Common$(LIBEXT)
INCLUDES=-I$(COMMLIB)/include -I$(PROJHOME)/include
DEFINES=
CFLAGS =$(FLGS) $(DBG) $(WARNS) $(OPT) $(INCLS) $(INCLUDES) $(DEFS) $(DEFINES) 
LDFLAGS=$(FLGS) $(DBG)
#
# all die feinen Sachen, die zu machen sind
#
all: $(OBJ) $(OBJ)/$(LIBPREF)Parser$(LIBEXT) $(OBJ)/$(LIBPREF)Parsold$(LIBEXT) \
 $(OBJ)/ti_mainr.o $(OBJ)/ti_mainl.o tabconv
$(OBJ):
	$(MKDIR) $(OBJ)
TISTUB_OBJS= \
 $(OBJ)/s_semerr.o $(OBJ)/s_semin.o $(OBJ)/s_semcl.o $(OBJ)/s_semab.o \
 $(OBJ)/s_errdat.o $(OBJ)/s_errfil.o $(OBJ)/s_scnein.o $(OBJ)/s_proto.o \
 $(OBJ)/s_operr.o $(OBJ)/s_out.o
TILIB_OBJS= $(OBJ)/ti_read.o $(OBJ)/ti_zugr.o \
 $(OBJ)/ti_parse.o $(OBJ)/ti_errs.o \
 $(OBJ)/s_parsin.o $(OBJ)/s_parscl.o $(OBJ)/s_parsab.o $(OBJ)/s_parse.o \
 $(OBJ)/s_parser.o $(OBJ)/s_parsta.o
$(OBJ)/$(LIBPREF)Parser$(LIBEXT): $(TILIB_OBJS)
	$(AR) $(OBJ)/$(LIBPREF)Parser$(LIBEXT) $(TILIB_OBJS)
	$(RANLIB) $(OBJ)/$(LIBPREF)Parser$(LIBEXT)
$(OBJ)/$(LIBPREF)Parsold$(LIBEXT): $(TISTUB_OBJS)
	$(AR) $(OBJ)/$(LIBPREF)Parsold$(LIBEXT) $(TISTUB_OBJS)
	$(RANLIB) $(OBJ)/$(LIBPREF)Parsold$(LIBEXT)
tabconv: $(OBJ)/tabconv.o $(OBJ)/ti_read.o $(OBJ)/ti_zugr.o
	$(LD) $(LDFLAGS) -o tabconv $(OBJ)/tabconv.o $(OBJ)/ti_read.o \
 $(OBJ)/ti_zugr.o $(RMFAIL)
parstest: $(OBJ)/ti_parse.o $(OBJ)/ti_read.o $(OBJ)/ti_zugr.o
	$(LD) $(LDFLAGS) -o parstest $(OBJ)/ti_parse.o $(OBJ)/ti_read.o \
 $(OBJ)/ti_zugr.o
$(OBJ)/tabconv.o:  tabconv.c  ti_defs.h  ti_read.h \
                  ti_zugr.h
	$(CC) -c $(CFLAGS)   tabconv.c && $(MV) tabconv.o $(OBJ)/
$(OBJ)/ti_read.o:  ti_read.c  ti_defs.h  ti_read.h
	$(CC) -c $(CFLAGS)  ti_read.c  && $(MV) ti_read.o $(OBJ)/
$(OBJ)/ti_zugr.o:  ti_zugr.c  ti_defs.h  ti_zugr.h
	$(CC) -c $(CFLAGS)  ti_zugr.c && $(MV) ti_zugr.o $(OBJ)/ 
$(OBJ)/ti_parse.o:  ti_parse.c  ti_defs.h  ti_zugr.h \
  ti_read.h  ti_parse.h  ti_errs.h  ti_token.h
	$(CC) -c $(CFLAGS)  ti_parse.c  && $(MV) ti_parse.o $(OBJ)/
$(OBJ)/ti_errs.o:  ti_errs.c  ti_errs.h  ti_defs.h \
  ti_zugr.h  ti_read.h  ti_parse.h  ti_token.h
	$(CC) -c $(CFLAGS)  ti_errs.c  && $(MV) ti_errs.o $(OBJ)/
# Basisschnittstellen
$(OBJ)/s_parsin.o:  ti_base.c
	$(CC) -DL_PARSEINIT -c $(CFLAGS)  ti_base.c && \
 $(MV) ti_base.o $(OBJ)/s_parsin.o
$(OBJ)/s_parser.o: ti_base.c
	$(CC) -DL_PARSER -c $(CFLAGS)  ti_base.c && \
 $(MV) ti_base.o $(OBJ)/s_parser.o
$(OBJ)/s_parscl.o:  ti_base.c
	$(CC) -DL_PARSECLOSE -c $(CFLAGS)  ti_base.c && \
 $(MV) ti_base.o $(OBJ)/s_parscl.o
$(OBJ)/s_parsab.o:  ti_base.c
	$(CC) -DL_PARSEABORT -c $(CFLAGS)  ti_base.c && \
 $(MV) ti_base.o $(OBJ)/s_parsab.o
$(OBJ)/s_parse.o:  ti_base.c 
	$(CC) -DL_PARSE -c $(CFLAGS)  ti_base.c && \
 $(MV) ti_base.o $(OBJ)/s_parse.o
$(OBJ)/s_parsta.o:  ti_base.c
	$(CC) -DL_PARSETAB -c $(CFLAGS)  ti_base.c && \
 $(MV) ti_base.o $(OBJ)/s_parsta.o
#
# Stummelroutinen
#
$(OBJ)/s_semerr.o:  ti_stub.c
	$(CC) -DL_SEMERRORS -c $(CFLAGS)  ti_stub.c && \
 $(MV) ti_stub.o $(OBJ)/s_semerr.o
$(OBJ)/s_semin.o:  ti_stub.c 
	$(CC) -DL_SEMINIT -c $(CFLAGS)  ti_stub.c && \
 $(MV) ti_stub.o $(OBJ)/s_semin.o
$(OBJ)/s_semcl.o:  ti_stub.c 
	$(CC) -DL_SEMCLOSE -c $(CFLAGS)  ti_stub.c && \
 $(MV) ti_stub.o $(OBJ)/s_semcl.o
$(OBJ)/s_semab.o:  ti_stub.c 
	$(CC) -DL_SEMABORT -c $(CFLAGS)  ti_stub.c && \
 $(MV) ti_stub.o $(OBJ)/s_semab.o
$(OBJ)/s_errdat.o:  ti_stub.c
	$(CC) -DL_ERRDAT -c $(CFLAGS)  ti_stub.c && \
 $(MV) ti_stub.o $(OBJ)/s_errdat.o
$(OBJ)/s_errfil.o:  ti_stub.c
	$(CC) -DL_ERRFILE -c $(CFLAGS)  ti_stub.c && \
 $(MV) ti_stub.o $(OBJ)/s_errfil.o
$(OBJ)/s_scnein.o:  ti_stub.c
	$(CC) -DL_SCANEIN -c $(CFLAGS)  ti_stub.c && \
 $(MV) ti_stub.o $(OBJ)/s_scnein.o
$(OBJ)/s_proto.o:  ti_stub.c
	$(CC) -DL_PROTO -c $(CFLAGS)  ti_stub.c && \
 $(MV) ti_stub.o $(OBJ)/s_proto.o
$(OBJ)/s_operr.o:  ti_stub.c
	$(CC) -DL_OPENERR -c $(CFLAGS)  ti_stub.c && \
 $(MV) ti_stub.o $(OBJ)/s_operr.o
$(OBJ)/s_out.o:  ti_stub.c 
	$(CC) -DL_OUT -c $(CFLAGS)  ti_stub.c && \
 $(MV) ti_stub.o $(OBJ)/s_out.o
#
# Aufrufroutinen
#
$(OBJ)/ti_mainr.o:  ti_main.c  ti_defs.h  ti_zugr.h \
  ti_read.h  ti_parse.h
	$(CC) -c $(CFLAGS) -DREAD_PTAB  ti_main.c \
              && $(MV) ti_main.o $(OBJ)/ti_mainr.o
$(OBJ)/ti_mainl.o:  ti_main.c  ti_defs.h  ti_zugr.h \
  ti_parse.h
	$(CC) -c $(CFLAGS)  ti_main.c  && $(MV) ti_main.o $(OBJ)/ti_mainl.o
# Tabellenvergleicher
tctest: $(OBJ)/tctest.o $(OBJ)/ti_read.o $(OBJ)/ti_zugr.o $(OBJ)/ttab.o
	$(CC) -o tctest $(OBJ)/tctest.o ttab.o $(OBJ)/ti_read.o $(OBJ)/ti_zugr.o
$(OBJ)/ttab.o: ttab.c
	$(CC) -c $(CFLAGS)  ttab.c  && $(MV)) ttab.o $(OBJ)/ttab.o
ttab.c: ttab.bin
	tabconv ttab.bin ttab.c
$(OBJ)/tctest.o:  tctest.c  ti_defs.h  ti_zugr.h \
  ti_parse.h  ti_read.h 
	$(CC) -c $(CFLAGS)  tctest.c  && $(MV) tctest.o $(OBJ)/tctest.o
clean:
	rm -f $(OBJ)/$(WILD).o $(DEBRIS)
realclean: clean
	rm -f $(OBJ)/$(LIBPREF)Parser$(LIBEXT) \
		 $(OBJ)/$(LIBPREF)Parsold$(LIBEXT) tabconv

install: $(INSTALLDIRS)
	@$(INSTALLALL)

$(INSTALLDIRS):
	$(MKDIR) $@
	$(CHMOD) $(CMDIRFLAGS) $@


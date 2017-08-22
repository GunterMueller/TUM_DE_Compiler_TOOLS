#
# Makefile fuer das Node Widget
#

include ../../config/MACHINE.flg

CFLAGS	= $(DEBUG) $(DEFINES) $(INCLUDES)

all: Node.o

Node.o: Node.c Node.h NodeP.h
	$(CC) $(CFLAGS) -c Node.c 

clean:
	@$(RM) $(RMFILES)

realclean: clean


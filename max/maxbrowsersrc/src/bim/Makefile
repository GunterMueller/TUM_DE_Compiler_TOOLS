include ../../config/MACHINE.flg

all: bim

bim: bim.tab.o lex.yy.o main.o bimsem.o bimcode.o
	$(CC) $(CFLAGS) bim.tab.o lex.yy.o main.o bimsem.o bimcode.o -o bim

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

lex.yy.c: bim.lex bim.tab.h
	$(LEX) $(LEXFLAGS) bim.lex

bim.tab.o: bim.tab.c
	$(CC) $(CFLAGS) -c bim.tab.c

bim.tab.c: bim.y
	$(YACC) $(YACCFLAGS) bim.y

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

bimsem.o: bimsem.c bimsem.h
	$(CC) $(CFLAGS) -c bimsem.c


bimcode.o: bimcode.c bimsem.h
	$(CC) $(CFLAGS) -c bimcode.c

clean: 
	@$(RM) $(RMFILES) lex.yy.c bim.tab.c

realclean: clean
	@$(RM) bim



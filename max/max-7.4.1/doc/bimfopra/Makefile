
NAME=bimfopra

all: $(NAME).ps

$(NAME).dvi: $(NAME).tex
	latex $(NAME).tex
	latex $(NAME).tex

$(NAME).ps: $(NAME).dvi
	dvips $(NAME).dvi

clean:
	-rm -f *.aux *.log *.toc

realclean: clean
	-rm -f $(NAME).dvi
	-rm -f $(NAME).ps

distclean: clean


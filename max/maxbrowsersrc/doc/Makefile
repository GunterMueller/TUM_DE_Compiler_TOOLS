all: doc.ps

doc.dvi: doc.tex \
         Node/Node.tex \
	 browser/browser.tex \
	 browser/tprint.tex \
	 widgethierarchie/widget.tex \
	bim/algdatst.tex \
	bim/bimcode.tex \
	bim/bimsem.tex \
	bim/bimutil.tex \
	bim/maxmodif.tex \
	 widgethierarchie/figures/widgeth.eps \
	 widgethierarchie/figures/GlobalMenu.eps \
	 widgethierarchie/figures/NodeMenu.eps \
	 widgethierarchie/figures/MaskWindow.eps \
	 widgethierarchie/figures/SortListWindow.eps \
	 widgethierarchie/figures/AttributList.eps
	latex doc

doc.ps: doc.dvi
	dvitps -C doc > doc.ps

realclean clean:
	@find . "(" -name "*".ps -o -name "*".dvi -o -name "*".aux \
		-o -name "*".log -o -name "*".toc ")" -exec /bin/rm {} \;


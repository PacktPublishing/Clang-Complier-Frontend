all: clangbook.tex
	pdflatex -shell-escape clangbook.tex
	bibtex clangbook
	pdflatex -shell-escape clangbook.tex
	pdflatex -shell-escape clangbook.tex
	pdftk A=clangbook.pdf cat A15-32 output chapters/ch1.pdf
	pdftk A=clangbook.pdf cat A33-64 output chapters/ch2.pdf
	pdftk A=clangbook.pdf cat A65-92 output chapters/ch3.pdf

clean:
	rm -rf *.aux *.bbl clangbook*.dvi  clangbook*.idv  clangbook*.lg  clangbook*.pyg  clangbook*.xref
	rm -rf clangbook*.blg clangbook*.toc clangbook*.out clangbook*.idx clangbook*.ilg clangbook*.ind
	rm -rf algorithmic.sty  algorithm.sty
	rm -rf _minted-*
	find . \( -name "*.log" -o -name "*~" -o -name "*.tmp" \) -exec rm -rf {} \;
	rm -rf *.4ct *.4tc *.css *.html
	cd src; make clean

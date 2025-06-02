all: lst report
	pdftk A=Z3431_Довыденков_АС.pdf B=listings.pdf cat A1-r2 B1-end output Отчет.pdf

report:
	libreoffice --convert-to pdf Z3431_Довыденков_АС.odt

lst: report
	xelatex -synctex=1 -shell-escape -interaction=nonstopmode listings.tex > /dev/null || echo "Done"
	rm -f listings.aux listings.log listings.out listings.synctex.gz listings.toc


gen:
	cp listings_base.tex listings.tex

	echo "\\setcounter{page}{`pdftk Z3431_Довыденков_АС.pdf dump_data | grep NumberOfPages |  cut -d' ' -f2`}" >> listings.tex
	find algo/include -name "**.hpp" -exec echo "\section*{ {} } \inputminted[linenos,fontsize=\small, breaklines]{cpp}{ {} } " \; >> listings.tex
	find algo/include -name "**.h" -exec echo "\section*{ {} } \inputminted[linenos,fontsize=\small, breaklines]{cpp}{ {} } " \; >> listings.tex
	find algo/src -name "**.cpp" -exec echo "\section*{ {} } \inputminted[linenos,fontsize=\small, breaklines]{cpp}{ {} } " \; >> listings.tex
	find src -name "**.*" -exec echo "\section*{ {} } \inputminted[linenos,fontsize=\small, breaklines]{cpp}{ {} } " \; >> listings.tex
	echo '  ' >> listings.tex
	echo ' \\end{document}' >> listings.tex

web:
	pandoc -f gfm -t html5 --standalone --toc --css screen.css -o index.html 01-intro.md

pdf:
	pandoc \
		-f gfm \
		-t pdf \
		--pdf-engine=lualatex \
		-V documentclass=jlreq \
		-V classoption=a4paper \
		-V classoption=oneside \
		-V geometry:a4paper \
		-V geometry:margin=25mm \
		--toc \
		-o body.pdf 01-intro.md
	qpdf \
		--empty \
		--pages cover.pdf body.pdf \
		-- index.pdf

clean:
	rm -rf index.html index.pdf body.pdf

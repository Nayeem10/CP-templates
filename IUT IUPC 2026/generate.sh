!/bin/sh
python script.py
pdflatex out.tex
pdflatex out.tex
mv out.pdf team-notebook.pdf 
rm out*
evince team-notebook.pdf

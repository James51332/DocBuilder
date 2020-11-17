NAME=doc
BUILDDIR=bin

SRCFILES=\
src/DocBuilder/Main.cpp

.SILENT:
build:
	clang++ $(SRCFILES) -std=c++17 -o $(BUILDDIR)/$(NAME)
	rm /usr/local/bin/doc
	ln ./bin/doc /usr/local/bin/doc
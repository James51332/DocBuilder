NAME=doc
BUILDDIR=bin

SRCFILES=\
src/DocBuilder/Main.cpp \
src/DocBuilder/Parser.cpp \
src/DocBuilder/FileManager.cpp \
src/DocBuilder/Logger.cpp


F2SFILES=\
src/File2String/f2s.cpp

.PHONY: build

.SILENT:
build:
	clang++ $(SRCFILES) -std=c++17 -o $(BUILDDIR)/$(NAME)
	rm /usr/local/bin/doc
	ln ./bin/doc /usr/local/bin/doc

f:
	clang++ $(F2SFILES) -std=c++17 -o $(BUILDDIR)/f2s
	rm /usr/local/bin/f2s
	ln ./bin/f2s /usr/local/bin/f2s
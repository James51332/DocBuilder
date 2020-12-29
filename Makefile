CXX=clang++

NAME=jdab-builder
BUILDDIR=bin

SRCFILES=\
src/BlogBuilder/Main.cpp \
src/BlogBuilder/CommandParser.cpp \
src/BlogBuilder/FileManager.cpp \
src/BlogBuilder/Parser.cpp \
src/BlogBuilder/HTMLBuilder.cpp

.PHONY: build

.SILENT:
build:
	$(CXX) $(SRCFILES) -std=c++17 -o $(BUILDDIR)/$(NAME)
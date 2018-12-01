# Makefile for cat.exe

CC = gcc
FILES = cat.c
BINFOLDER = bin
EXE = $(BINFOLDER)/cat.exe
DEBUGEXE = $(BINFOLDER)/cat-debug.exe
STD = c89
CFLAGS = -Werror -Wall -Wextra -pedantic

$(EXE): | $(BINFOLDER)
	$(CC) -o $(EXE) $(FILES) $(CFLAGS) -std=$(STD) -O3

debug: | $(BINFOLDER)
	$(CC) -o $(DEBUGEXE) $(FILES) $(CFLAGS) -std=$(STD) -DDEBUG

$(BINFOLDER):
	mkdir $(BINFOLDER)
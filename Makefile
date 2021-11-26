CC=gcc
CFLAGS=-Wall -Werror -std=c11 -pedantic -ggdb
LIBS=-lSDL2
BIN=sapper

$(BIN):main.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

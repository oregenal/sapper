CC=gcc
CFLAGS=-Wall -Werror -std=c11 -pedantic -ggdb `pkg-config --cflags sdl2`
LIBS=`pkg-config --libs sdl2`

BIN=sapper
SRCDIR=src
OBJDIR=obj

HDRS=$(wildcard $(SRCDIR)/*.h)
OBJS=$(patsubst $(SRCDIR)/%.h, $(OBJDIR)/%.o, $(HDRS))

.PHONY:default

default:$(BIN)

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o:$(SRCDIR)/%.c $(SRCDIR)/%.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN):$(SRCDIR)/main.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf obj/ $(BIN)

CC=gcc
CFLAGS=-Wall -Werror -std=c11 -pedantic -ggdb `pkg-config --cflags sdl2`
LIBS=`pkg-config --libs sdl2`

BIN=sapper
SRCDIR=src
OBJDIR=obj
DESTDIR=/usr/local

HDRS=$(wildcard $(SRCDIR)/*.h)
OBJS=$(patsubst $(SRCDIR)/%.h, $(OBJDIR)/%.o, $(HDRS))

.PHONY:default clean release install

default:$(BIN)

release:CFLAGS=-std=c11 -O2 -DNDEBUG `pkg-config --cflags sdl2`
release:clean
release:$(BIN)

install:$(BIN)
	mkdir -p $(DESTDIR)/bin
	cp -f $(BIN) $(DESTDIR)/bin
	chmod 755 $(DESTDIR)/bin/$(BIN)

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o:$(SRCDIR)/%.c $(SRCDIR)/%.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN):$(SRCDIR)/main.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(OBJDIR) $(BIN)

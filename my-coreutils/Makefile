# Compiler
CC=gcc
CFLAGS=-Wall -g -O0
FAST_CFLAGS=-O3

# Dirs
SDIR=src
BDIR=bin

# Files
BFILES=bin/cat bin/cp bin/file bin/head bin/touch bin/tail bin/time bin/ls bin/sort bin/rm bin/rmdir


all: create_build_dir $(BFILES)

$(BDIR)/%: $(SDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^

create_build_dir:
	mkdir -p $(BDIR)

clean:
	rm -r $(BDIR)

CC = clang
DEBUG = -g
WARN = -Weverything

CFLAGS = $(DEBUG) $(WARN) -Isrc
COBJFLAGS = $(CFLAGS) -c

CLEANLIST = test.out minalg.o

default: minalg

test: test/test.c minalg
	$(CC) $(CFLAGS) test/test.c -o test.out minalg.o

minalg: src/minalg.c
	$(CC) $(COBJFLAGS) $< -o minalg.o

debug:


clean: 
	rm -rf $(CLEANLIST)	

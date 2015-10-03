CC=gcc
CFLAGS=-g -m32

all: pingpong pingpongpang

pingpong: pingpong.c
	$(CC) -o pingpong contexte.c pingpong.c  $(CFLAGS)

pingpongpang: pingpongpang.c
	$(CC) -o pingpongpang contexte.c pingpongpang.c $(CFLAGS)

test: pingpongpangtest.c
	$(CC) -o test contexte.c pingpongpangtest.c $(CFLAGS)

clean:
	rm -f *~ *.o pingpong pingpongpang

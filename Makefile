CC=gcc
CFLAGS=-m32

all: pingpong pingpongpang

pingpong: pingpong.c
	$(CC) -o pingpong contexte.c pingpong.c  $(CFLAGS)

pingpongpang: pingpongpang.c
	$(CC) -o pingpongpang contexte.c pingpongpang.c $(CFLAGS)

clean:
	rm -f *~ *.o pingpong pingpongpang

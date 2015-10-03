CC=gcc
CFLAGS=-m32 -g

all: pingpong_y pingpongpang_y pingpong

pingpong_y: pingpong_y.o contexte.o hw/hw.o
	$(CC) -o $@ $^  $(CFLAGS)

pingpongpang_y: pingpongpang_y.o contexte.o hw/hw.o
	$(CC) -o $@ $^ $(CFLAGS)

pingpong: pingpong.o contexte.c hw/hw.o
	$(CC) -o $@ $^  $(CFLAGS)

%.o : %.c
	$(CC) -c $(FLAGS) -o $@ $<

clean:
	rm -f *~ *.o pingpong_y pingpongpang_y pingpong

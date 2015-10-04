CC=gcc
CFLAGS=-m32 -g
EXEC=pingpong


all: $(EXEC)

pingpong_y: pingpong_y.c hw/hw.c contexte.c
	$(CC) -o $@ $^ $(CFLAGS)

pingpongpang_y: pingpongpang_y.c hw/hw.c contexte.c
	$(CC) -o $@ $^ $(CFLAGS)

pingpong: pingpong.c hw/hw.c contexte.c
	$(CC) -o $@ $^ $(CFLAGS)

%.o : %.c
	$(CC) -o $@ -c $< $(FLAGS)

.PHONY: clean realclean

clean:
	rm -rf *~ *.o hw/*.o hw/*~

realclean:
	make clean
	rm -rf $(EXEC)

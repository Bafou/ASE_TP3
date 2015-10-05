CC=gcc
CFLAGS=-m32 -g
CLIB=-I./include -L./lib -lhardware
EXEC=pingpong philo


all: $(EXEC)

pingpong_y: pingpong_y.c contexte.c
	$(CC) -o $@ $^ $(CFLAGS) $(CLIB)

pingpongpang_y: pingpongpang_y.c contexte.c
	$(CC) -o $@ $^ $(CFLAGS) $(CLIB)

pingpong: pingpong.c contexte.c
	$(CC) -o $@ $^ $(CFLAGS) $(CLIB)

philo: philo.c contexte.c
	$(CC) -o $@ $^ $(CFLAGS) $(CLIB)

%.o : %.c
	$(CC) -o $@ -c $< $(FLAGS)

.PHONY: clean realclean

clean:
	rm -rf *~ *.o hw/*.o hw/*~

realclean:
	make clean
	rm -rf $(EXEC)

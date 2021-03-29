CC = gcc
CFLAGS =-O3
all: execNN main.o

.PHONY: clean

execNN: main.o
	$(CC) -o execNN main.o -lm

main.o: main.c NN.h NN_init.h NN_fct.h Struct.h
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o

mrproper: clean
	rm -f execNN

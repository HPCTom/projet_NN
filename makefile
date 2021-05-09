CC = mpicc
#CFLAGS =-O3 -lpng -lm -Wall -g
CFLAGS =-Ofast -lpng -lm -Wall -g -funroll-loops -march=native -mtune=native -ftree-vectorize
all: execNN main.o

.PHONY: clean

lirepng.o: lirepng.c lirepng.h dossier.h
	$(CC) $(CFLAGS) -o lirepng.o -c lirepng.c

dossier.o: dossier.c dossier.h
	$(CC) $(CFLAGS) -o dossier.o -c dossier.c

execNN: main.o dossier.o lirepng.o
	$(CC) -o execNN main.o dossier.o lirepng.o -lm -lpng

main.o: main.c NN.h NN_init.h NN_fct.h Struct.h lirepng.h dossier.h mesure.h
	$(CC) $(CFLAGS) -o main.o -c main.c

clean:
	rm -rf *.o

mrproper: clean
	rm -f execNN

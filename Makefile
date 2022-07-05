CFLAGS=-g -Wall -pedantic
CC=gcc

todos: compilar

compilar: i-banco.o commandlinereader.o contas.o
	$(CC) $(CFLAGS) -o main-v2 main-v2.o commandlinereader.o contas.o

main-v2.o: i-banco.c contas.h commandlinereader.h
	$(CC) $(CFLAGS) -c main-v2.c

contas.o: contas.c contas.h
	$(CC) $(CFLAGS) -c contas.c

commandlinereader.o: commandlinereader.c commandlinereader.h
	$(CC) $(CFLAGS) -c commandlinereader.c

clean:
	rm -f *.o main-v2

run:
	./i-banco

CC=gcc
CFLAGS=-Wall -g

all: main.o
	$(CC) $(CFLAGS) main.o Board.o TTTIO.o -o tictac
	./tictac
main.o: Board.o TTTIO.o
	$(CC) $(CFLAGS) -c main.c
Board.o:
	$(CC) $(CFLAGS) -c Board.c
TTTIO.o: Board.o
	$(CC) $(CFLAGS) -c TTTIO.c
clean:
	rm -rf *.o *~ tictac

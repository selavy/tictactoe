CC=gcc
CFLAGS=-Wall -g

all: main.o
	$(CC) $(CFLAGS) main.o Board.o TTTIO.o AI.o -o tictac
main.o: Board.o TTTIO.o AI.o
	$(CC) $(CFLAGS) -c main.c
Board.o:
	$(CC) $(CFLAGS) -c Board.c
TTTIO.o: Board.o
	$(CC) $(CFLAGS) -c TTTIO.c
AI.o:
	$(CC) $(CFLAGS) -c AI.c
clean:
	rm -rf *.o *~ tictac

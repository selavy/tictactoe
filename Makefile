CC=gcc
DEBUG=-g
CFLAGS=-Wall -Werror $(DEBUG)

OBJS=main.o
PROG=tictactoe

PROG: $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c $<

.PHONY:clean
clean:
	rm -rf $(OBJS) $(PROG)

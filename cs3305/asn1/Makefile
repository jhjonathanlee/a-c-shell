CC = gcc
CFLAGS = -O0 -std=gnu11

all: csh.c option_parser.o history.o
	$(CC) $(CFLAGS) -D_GNU_SOURCE -o csh csh.c option_parser.o history.o

option_parser.o: option_parser.c option_parser.h
	$(CC) $(CFLAGS) -D_GNU_SOURCE -c option_parser.c

history.o: history.c history.h
	$(CC) $(CFLAGS) -c history.c

clean:
	rm -f csh *.o *.gch

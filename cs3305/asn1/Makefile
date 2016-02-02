CC = gcc
CFLAGS = -O0 -std=gnu11

all: csh.c option_parser.o
	$(CC) $(CFLAGS) -D_GNU_SOURCE -o csh csh.c option_parser.o

option_parser.o: option_parser.c option_parser.h
	$(CC) $(CFLAGS) -D_GNU_SOURCE -c option_parser.c

clean:
	rm -f csh *.o

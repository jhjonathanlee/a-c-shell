CC = gcc
CFLAGS = -O0 -Wall -Werror

all: csh.c
	$(CC) $(CFLAGS) -o csh csh.c

option_parser: option_parser.c option_parser.h
	$(CC) $(CFLAGS) -D_GNU_SOURCE -c option_parser.c

clean:
	rm -f csh *.o

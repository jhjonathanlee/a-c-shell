CC = gcc
CFLAGS = -std=gnu11 -O0

asn1_a:
	$(CC) $(CFLAGS) -o asn1_a fib.c

asn1_b: fib2.c
	$(CC) $(CFLAGS) -o asn1_b fib2.c

clean:
	rm -f *.o asn1_a asn1_b

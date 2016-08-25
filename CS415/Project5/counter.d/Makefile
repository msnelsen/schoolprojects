CC=gcc
CFLAGS=-g -D_REENTRANT
LIBS=-lpthread

counter: counter.c
	$(CC) $(CFLAGS) -o counter counter.c $(LIBS)

clean:
	rm -f counter core.*

CC=gcc
CFLAGS=-g

all: nim_server nim nim_match_server

nim_server: nim_server.o
	$(CC) -o nim_server nim_server.o

nim:nim.o
	$(CC) -o nim nim.o

nm_match_server: nim_match_server.o
	$(CC) -o nm_match_server nim_match_server.o

clean:
	rm -f *.o nim_server nim nim_match_server

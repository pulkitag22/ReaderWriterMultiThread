CC=gcc

CFLAGS=-c -Wall

all:main

main: main.o
	$(CC) main.o -pthread -o main

main.o: main.c definations.h
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *o main

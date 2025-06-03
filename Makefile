
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: main

main: main.o mymemory.o
	$(CC) $(CFLAGS) -o main main.o mymemory.o

main.o: main.c mymemory.h
	$(CC) $(CFLAGS) -c main.c

mymemory.o: mymemory.c mymemory.h
	$(CC) $(CFLAGS) -c mymemory.c

clean:
	rm -f *.o main

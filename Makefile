CC = gcc

CFLAGS = -Wall -g

LD = gcc

LDFLAGS =

slosh: slosh.o
	$(LD) $(LDFLAGS) -o slosh slosh.o

slosh.o: slosh.c
	$(CC) $(CFLAGS) -c -o slosh.o slosh.c

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

all: main.o vec.o
	$(CC) $(CFLAGS) -o main main.o vec.o 

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

vec.o: vec.c
	$(CC) $(CFLAGS) -c vec.c

clean:
	rm -f *.o main

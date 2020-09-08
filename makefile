CC=gcc
CFLAGS= -g -Wall -Werror -Wconversion -std=c99 -Wtype-limits -pedantic -O0

build: 
	$(CC) *.c $(CFLAGS) -o heap

valgrind: 
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./heap

.PHONY : clean

clean:
	rm hash
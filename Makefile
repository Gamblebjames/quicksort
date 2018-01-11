CC=gcc

all: quicksort 

quicksort: quicksort.c
	$(CC) -std=gnu99 -o quicksort quicksort.c

clean:
	rm quicksort

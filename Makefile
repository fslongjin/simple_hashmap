CROSS_COMPILE:=

CC:=$(CROSS_COMPILE)gcc
CFLAGS:=-Wall -Wextra -Werror -std=c99 -pedantic -O2

simple_hashmap.o: simple_hashmap.c
	$(CC) $(CFLAGS) -c -o simple_hashmap.o simple_hashmap.c

# Test target
.PHONY: test
test: simple_hashmap.o
	$(CC) $(CFLAGS) -o test test.c simple_hashmap.o
	./test

.PHONY: benchmark
benchmark: simple_hashmap.o
	$(CC) $(CFLAGS) -o benchmark benchmark.c simple_hashmap.o
	./benchmark

.PHONY: clean
clean:
	rm -f *.o test
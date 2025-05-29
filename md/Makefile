CC ?= gcc
CFLAGS ?= 
CFLAGS += -Wall -Wextra -Werror

all: md2.out md4_test.out

md2.out: md2.c
	$(CC) $(CFLAGS) md2.c -o md2.out

md4.o: md4.c
	$(CC) $(CFLAGS) -c md4.c

md4_test.out: md4_test.c md4.o
	$(CC) $(CFLAGS) md4_test.c md4.o -o md4_test.out

clean:
	rm *.out *.o

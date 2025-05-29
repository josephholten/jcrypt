CC ?= gcc
CFLAGS ?= 
CFLAGS += -Wall -Wextra -Werror

all: md2_test.out md4_test.out

md2.o: md2.c
	$(CC) $(CFLAGS) -c md2.c

md2_test.out: md2_test.c md2.o
	$(CC) $(CFLAGS) md2_test.c md2.o -o md2_test.out

md4.o: md4.c
	$(CC) $(CFLAGS) -c md4.c

md4_test.out: md4_test.c md4.o
	$(CC) $(CFLAGS) md4_test.c md4.o -o md4_test.out

clean:
	rm *.out *.o

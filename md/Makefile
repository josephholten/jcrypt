CC ?= gcc
CFLAGS ?= 
CFLAGS += -Wall -Wextra -Werror

all: md2.out md4.out md4ref.out md4ref2.out

md2.out: md2.c
	$(CC) $(CFLAGS) md2.c -o md2.out

md4.out: md4.c
	$(CC) $(CFLAGS) md4.c -o md4.out

clean:
	rm *.out

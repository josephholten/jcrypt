CFLAGS=-g

md2.out: md2.c
	$(CC) $(CFLAGS) md2.c -o md2.out

sha1.out: sha1.c
	$(CC) $(CFLAGS) sha1.c -o sha1.out

rsa.out: rsa.c
	$(CC) $(CFLAGS) rsa.c -o rsa.out

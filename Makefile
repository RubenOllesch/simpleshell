simpleshell: simpleshell.c
	$(CC) simpleshell.c -o simpleshell

all:	simpleshell

clean:
	rm -rf simpleshell

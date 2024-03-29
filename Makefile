CC:=$(CC) $(CFLAGS)
OBJ:=simpleshell.o builtin.o util.o

%.o: %.c
	$(CC) -c $< -o $@

simpleshell: $(OBJ)
	$(CC) $(OBJ) -o simpleshell

all:	simpleshell

clean:
	rm -rf simpleshell *.o

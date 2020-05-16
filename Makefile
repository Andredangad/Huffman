CC=gcc
CFLAGS=-Wall -ansi
LDFLAGS=
DEPS=visualtree.h tree.h 
OBJ=visualtree.o tree.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

huffman: main.o $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) huffman main.o current-tree.dot current-tree.pdf
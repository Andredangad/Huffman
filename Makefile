CC=gcc
CFLAGS=-Wall -ansi
LDFLAGS=
DEPS=$(HPATH)visualtree.h  $(HPATH)prioqueue.h  $(HPATH)tree.h 
OBJ=visualtree.o tree.o prioqueue.o
SRCPATH=src/
HPATH=headers/

%.o: $(SRCPATH)%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

encode: encode.o $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

decode: decode.o $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) encode decode encode.o decode.o current-tree.dot current-tree.pdf
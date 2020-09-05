CC=gcc
SRC:=$(shell find . -name *.c)

CFLAGS= -Isrc/kosmonaut/ -lSDL2 -lGL -lGLEW -lm -o SBC -g -pg

main: $(SRC)

	$(CC) $(SRC) $(CFLAGS)
	
clean: SBC
	rm SBC

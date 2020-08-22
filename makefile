CC=gcc
SRC:=$(shell find . -name *.c)

CFLAGS= -Isrc/SCBE/ -lSDL2 -lGL -lGLEW -lm -o SBC -g -pg

main: $(SRC)

	$(CC) $(SRC) $(CFLAGS)
	
clean: SBC
	rm SBC

CC=gcc
CC_win=x86_64-w64-mingw32-gcc

SRC:=$(shell find . -name *.c)
SRC_lib:=$(shell find src/kosmonaut/. -name *.c)

CFLAGS= -Isrc/kosmonaut/ libkosmonaut.a -lSDL2 -lGL -lGLEW -lm -o SBC -g -pg
CFLAGS_lib= -Isrc/kosmonaut/ -lSDL2 -lGL -lGLEW -lm -c -g -pg
CFLAGS_win=-mwindows -Isrc/kosmonaut/ -Iwindows/include/  -Lwindows/lib/ -lglew32 -lglew32mx -lSDL2 -lSDL2main -lopengl32 -lmingw32 -lm -o SBC.exe -g -pg


main: $(SRC)
	$(CC) src/main.c $(CFLAGS)

windows: $(SRC)
	$(CC_win) $(SRC) $(CFLAGS_win)

kosmonaut: $(SRC_lib)
	$(CC) $(SRC_lib) $(CFLAGS_lib)
	mv *.o obj/kosmonaut
	ar ruv libkosmonaut.a obj/kosmonaut/*.o

clean: SBC
	rm SBC

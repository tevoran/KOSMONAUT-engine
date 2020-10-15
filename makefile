CC=gcc
CC_win=x86_64-w64-mingw32-gcc

SRC:=$(shell find src/game/. -name *.c)
SRC_win:=$(shell find src/. -name *.c)
SRC_lib:=$(shell find src/kosmonaut/. -name *.c)

CFLAGS=-Isrc/kosmonaut/ -Isrc/game/game/ libkosmonaut.a -lSDL2 -lGL -lGLEW -lm -lnng -lpthread -o SBC -g -pg
CFLAGS_lib= -Isrc/kosmonaut/ -lSDL2 -lGL -lGLEW -lm -lnng -lpthread -c -g -pg
CFLAGS_win=-mwindows -Isrc/kosmonaut/ -Isrc/game/game/ -Iwindows/include/  -Lwindows/lib/ -lnng -lglew32 -lglew32mx -lSDL2 -lSDL2main -lopengl32 -lmingw32 -lm -o SBC.exe -g -pg


main: $(SRC) kosmonaut
	$(CC) $(SRC) $(CFLAGS)

windows: $(SRC)
	$(CC_win) $(SRC_win) $(CFLAGS_win)

kosmonaut: $(SRC_lib)
	mkdir -p obj
	mkdir -p obj/kosmonaut
	$(CC) $(SRC_lib) $(CFLAGS_lib)
	mv *.o obj/kosmonaut
	ar ruv libkosmonaut.a obj/kosmonaut/*.o

clean: SBC
	rm SBC

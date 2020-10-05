CC=gcc
CC_win=x86_64-w64-mingw32-gcc

SRC:=$(shell find . -name *.c)

CFLAGS= -Isrc/kosmonaut/ -lSDL2 -lGL -lGLEW -lm -o SBC -g -pg
CFLAGS_win=-mwindows -Isrc/kosmonaut/ -Iwindows/include/  -Lwindows/lib/ -lglew32 -lglew32mx -lSDL2 -lSDL2main -lopengl32 -lmingw32 -lm -o SBC.exe -g -pg

main: $(SRC)

	$(CC) $(SRC) $(CFLAGS)
	
windows: $(SRC)
	$(CC_win) $(SRC) $(CFLAGS_win)

clean: SBC
	rm SBC

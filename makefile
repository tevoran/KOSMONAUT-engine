CC=gcc
SRC:=src/main.c
SRC_ENGINE:=$(wildcard src/include/gfx/gl/*.c)
SRC_GFX:=$(wildcard src/include/engine/*.c)
SRC_GAME:=$(wildcard src/include/game/*.c)
SRC_MATHS:=$(wildcard src/include/maths/*.c)
CFLAGS= -Isrc/include/ -lSDL2 -lGL -lGLEW -lm -o main

main: $(SRC) $(SIM_SRC) $(WCE_SRC)

	$(CC) $(SRC) $(SRC_ENGINE) $(SRC_GFX) $(SRC_GAME) $(SRC_MATHS) $(CFLAGS)
	
clean: main
	rm main
CC=gcc
SRC:=$(shell find . -name *.c)

CFLAGS= -Isrc/include/ -lSDL2 -lGL -lGLEW -lm -o main

main: $(SRC) $(SIM_SRC) $(WCE_SRC)

	$(CC) $(SRC) $(SRC_ENGINE) $(SRC_GFX) $(SRC_GAME) $(SRC_MATHS) $(CFLAGS)
	
clean: main
	rm main
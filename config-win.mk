INCS = -I./include -I/usr/include
LIBS = -L/usr/lib `sdl2-config --libs` -lGLEW32 -lopengl32 -lSDL2_ttf

CFLAGS += -std=c99 -Wall -pedantic `sdl2-config --cflags` ${INCS}
LDFLAGS += ${LIBS}

CC = gcc

INCS = -I./include -I/usr/include
LIBS = -L/usr/lib -lc `sdl2-config --libs` -lGLEW

CFLAGS += -std=c99 -Wall -pedantic ${INCS}
LDFLAGS += ${LIBS}

CC = gcc

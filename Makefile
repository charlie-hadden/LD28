# ludum dare 28

include config.mk

SRC = ${wildcard src/*.c}
OBJ = ${SRC:src/%.c=obj/%.o}

all: options game

options:
	@echo build options
	@echo "CFLAGS  = ${CFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC      = ${CC}"

${OBJ}: obj/%.o: src/%.c
	@echo CC $<
	@${CC} -c ${CFLAGS} $< -o $@

game: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f game ${OBJ}

.PHONY: all options clean

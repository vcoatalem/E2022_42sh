NONE=

CC?= gcc
CPPFLAGS= \
          -D_DEFAULT_SOURCE \
          -D_POSIX_C_SOURCE \
          -Isrc \
          ${NONE}
CFLAGS= \
        -Wall \
        -Werror \
        -Wextra \
        -pedantic \
        -std=c99 \
        ${NONE} \

LDFLAGS= \
         -lreadline \
         ${NONE}

OBJS= \
      readline.o \
      readline_exec.o \
      ${NONE}

VPATH= src

BIN= readline_exec

all: ${BIN}

debug: CFLAGS+= -g -fsanitize=address
debug: LDFLAGS+= -fsanitize=address
debug: ${BIN}

${BIN}: ${OBJS}

clean:
	${RM} ${BIN} ${OBJS}

.PHONY: all clean

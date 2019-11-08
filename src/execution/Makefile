CC=gcc
CFLAGS=-g -Wall -Werror -Wextra -pedantic -std=c99

OBJS=   command.o \
        redirection.o \
        pipe.o

TESTS=$(shell find tests -name "*.test.c")

all: $(OBJS)

%.test: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $@.c -o $@

check: $(foreach test,$(TESTS), $(basename $(test)))

clean:
	$(RM) $(OBJS)

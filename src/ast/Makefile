CC=gcc
CFLAGS=-g -Wall -Werror -Wextra -pedantic -std=c99

OBJS= ast.o ast_print.o

TESTS=$(shell find tests -name "*.test.c")

all: $(OBJS)

%.test: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $@.c -o $@

check: $(foreach test,$(TESTS), $(basename $(test)))

clean:
	$(RM) $(OBJS) $(foreach test,$(TESTS), $(basename $(test)))


NAME      := ds
CC        := gcc
CFLAGS    := -std=c17 -Wall -Wextra -Wpedantic -O2 -Iinclude -MMD -MP
AR        := ar
ARFLAGS   := rcs

SRC       := $(wildcard src/*.c)
OBJ       := $(SRC:src/%.c=build/%.o)
DEP       := $(OBJ:.o=.d)

LIB       := lib/lib$(NAME).a
TEST_BIN  := build/tests

all: $(LIB)

$(LIB): $(OBJ)
	@mkdir -p lib
	$(AR) $(ARFLAGS) $@ $^

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB)
	$(CC) $(CFLAGS) -o $(TEST_BIN) tests/*.c -Llib -l$(NAME)
	$(TEST_BIN)

clean:
	rm -rf build lib

-include $(DEP)

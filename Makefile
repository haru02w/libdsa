
CC=gcc
AR=ar
CFLAGS=-g -Wall

SRC_DIR=src
OBJ_DIR=obj
TEST_DIR=tests
INCLUDE_DIR=include
BUILD_DIR=build
LIB_DIR=.

SRCS=$(shell find $(SRC_DIR) -name '*.c')
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TESTS=$(shell find $(TEST_DIR) -name '*.c')
LIB=$(LIB_DIR)/libdsa.a

.PHONY: all test clean

all:$(LIB)

$(LIB): $(OBJS)
	$(AR) rcs $(LIB) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB) $(TESTS)
	$(CC) $(CFLAGS) $(TESTS) -I$(INCLUDE_DIR) -L$(LIB_DIR) -l$(patsubst lib%,%,$(basename $(notdir $(LIB)))) -o $(BUILD_DIR)/$@

run: test
	@$(BUILD_DIR)/test

clean:
	rm -rf $(OBJ_DIR)/* $(BUILD_DIR)/* $(LIB)

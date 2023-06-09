CC=gcc
AR=ar
CFLAGS=-g -Wall

SRC_DIR=src
OBJ_DIR=obj
INCLUDE_DIR=include
BUILD_DIR=build
TEST_DIR=tests

ALL_DIRS=$(SRC_DIR) $(OBJ_DIR) $(INCLUDE_DIR) \
			$(BUILD_DIR) $(TEST_DIR) $(BUILD_DIR)/$(TEST_DIR)\
			$(OBJ_DIR)/$(TEST_DIR)

SRCS=$(shell find $(SRC_DIR) -name '*.c' | sort $1)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TESTS=$(shell find $(TEST_DIR) -name '*.c' | sort $1)
TEST_OBJS=$(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/$(TEST_DIR)/%.o,$(TESTS))

TEST_BINS=$(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/$(TEST_DIR)/%,$(TESTS))
LIB=$(BUILD_DIR)/libdsa.a

LDFLAGS=-L$(BUILD_DIR) -l$(patsubst lib%,%,$(basename $(notdir $(LIB))))
INCFLAGS=-I$(INCLUDE_DIR)

.PHONY: all test clean

all: dir $(LIB) 

$(LIB): $(OBJS)
	$(AR) rcs $(LIB) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

test: all $(TEST_BINS)
	@for test in $(TEST_BINS) ; do \
		echo "-- Running test: $$test"; \
		if ! $$test; then \
            echo "Error code: $$?"; \
            break; \
        fi; \
	done

$(BUILD_DIR)/$(TEST_DIR)/%: $(OBJ_DIR)/$(TEST_DIR)/%.o
	$(CC) $< $(CFLAGS) $(LDFLAGS) $(INCFLAGS) -o $@

$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $< $(CFLAGS) $(INCFLAGS) -c  -o $@

dir: $(ALL_DIRS)

$(ALL_DIRS):
	@mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(BUILD_DIR)/* $(LIB)

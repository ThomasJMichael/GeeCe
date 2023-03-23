CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -g
LDFLAGS =
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_SRCS))

all: geece

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR)/%: $(TEST_DIR)/%.c $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(OBJS)

geece: $(OBJS) $(BIN_DIR)/test_heap $(BIN_DIR)/test_object $(BIN_DIR)/test_reference $(BIN_DIR)/test_garbage_collector $(BIN_DIR)/test_mark_and_sweep $(BIN_DIR)/test_reference_counting
	$(CC) $(CFLAGS) $(LDFLAGS) -o geece $(OBJS)

clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/* geece

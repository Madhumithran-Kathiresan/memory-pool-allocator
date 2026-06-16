CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -Iinclude
BUILD_DIR = build
SRC = src/main.c src/mempool.c
TARGET = $(BUILD_DIR)/mempool

.PHONY: all clean run setup-coredump run-with-coredump

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

setup-coredump:
	@bash setup_coredump.sh

run-with-coredump: setup-coredump $(TARGET)
	ulimit -c unlimited && ./$(TARGET)

# Compiler and flags
CC = riscv64-unknown-elf-gcc
CFLAGS = -Iinclude -Wall -Werror

# Directories
SRC_DIR = src
OBJ_DIR = outputs
BIN_DIR = outputs

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(SRC_DIR)/assemblySubroutine.S
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(SRC_DIR)/%.S=$(OBJ_DIR)/%.o)

# Output executable
TARGET = $(BIN_DIR)/rv64_binary

# Default target
build: $(TARGET)

# Rule to link object files and create the final executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET)

# Rule to compile C source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile assembly source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: build clean


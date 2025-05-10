SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
PROGRAM = $(BIN_DIR)/lab2
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))

all : $(PROGRAM)

$(PROGRAM) : $(OBJ_FILES) | $(BIN_DIR)
	$(CC) -o $(PROGRAM) $(OBJ_FILES)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $^

$(OBJ_DIR) : | $(BUILD_DIR)
	mkdir $(OBJ_DIR)

$(BUILD_DIR) :
	mkdir $(BUILD_DIR)

$(BIN_DIR) : | $(BUILD_DIR)
	mkdir $(BIN_DIR)
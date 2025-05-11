SRC_DIR = src
INC_DIR = inc


BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
DOC_DIR = $(BUILD_DIR)/doc

PROGRAM = $(BIN_DIR)/lab2
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -I$(INC_DIR)

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.d,$(SRC_FILES))

-include $(OBJ_DIR)/%.d 

all : $(PROGRAM)

$(PROGRAM) : $(OBJ_FILES) | $(BIN_DIR)
	$(CC) -o $(PROGRAM) $(OBJ_FILES)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -c -o $@ $<

$(OBJ_DIR) : | $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

$(BIN_DIR) : | $(BUILD_DIR)
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR)/obj/*.o $(BUILD_DIR)/obj/*.d $(PROGRAM)

doc:
	doxygen Doxyfile
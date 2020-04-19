TARGETS := fundot

MV := mv

CC := g++
CFLAGS := -g -Wall -Werror -std=c++11
CPPFLAGS := -Iinclude

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := /usr/local/bin

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
BIN := $(BIN_DIR)/$(TARGETS)

.PHONY: build move clean

move: $(BIN)

$(BIN): $(TARGETS) | $(BIN_DIR)
	sudo $(MV) $< $@

build: $(TARGETS)

$(TARGETS): $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

clean:
	rm -r $(OBJ_DIR)

CXX := g++
CXXFLAGS := -std=c++17 -O2 -g -Wall -Wextra -Werror

LD := g++
LDFLAGS := -std=c++17

TARGETS := fundot

SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
BINS := $(BIN_DIR)/$(TARGETS)

.PHONY: all clean

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -o $@ $(CXXFLAGS) -c $< -I $(INC_DIR)

$(OBJ_DIR):
	mkdir $@

clean:
	rm -r obj

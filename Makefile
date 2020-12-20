# MIT License

# Copyright (c) 2020 Jiacheng Huang

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CXX := g++
CXXFLAGS := -std=c++17 -O0 -g -Wall -Wextra -Werror

LD := g++
LDFLAGS := -std=c++17

TARGETS := fundot

SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin
TEST_DIR := test

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
BINS := $(BIN_DIR)/$(TARGETS)

TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS_FROM_SRC := $(filter-out $(OBJ_DIR)/main.o,$(OBJS))
TEST_OBJS_FROM_TEST := $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJS := $(TEST_OBJS_FROM_SRC) $(TEST_OBJS_FROM_TEST)
TEST_BINS := $(BIN_DIR)/test

.PHONY: all test clean

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -o $@ $(CXXFLAGS) -c $< -I $(INC_DIR) -I $(SRC_DIR)

$(OBJ_DIR):
	mkdir $@

test: $(TEST_BINS)

$(TEST_BINS): $(TEST_OBJS) | $(BIN_DIR)
	$(LD) -o $@ $(LDFLAGS) $^

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -o $@ $(CXXFLAGS) -c $< -I $(INC_DIR) -I $(SRC_DIR)

$(BIN_DIR):
	mkdir $@

clean:
	rm -r obj

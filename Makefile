CXX ?= g++
SRC_DIR ?= ./src
SRC_EXT = cpp
OBJ_DIR = build
SRC_FILES := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJ_FILES = $(SRC_FILES:$(SRC_PATH)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
BIN_PATH = $(OBJ_DIR)/bin
DEPS = $(OBJ_FILES:.o=.d)

default: make

make: 
	$(CXX) $(SRC_FILES) -o speeljongen

dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJ_FILES))
	@mkdir -p $(BIN_PATH)

clean:
	rm -rf *.o

APPNAME := advent2024
CPP_COMPILER := g++
CPP_FLAGS := -std=c++20

SRC_DIR := src
OBJ_DIR := obj

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))

single:
	$(CPP_COMPILER) $(CPP_FLAGS) $(LDFLAGS) -o $(APPNAME) $(CPP_FILES)

all: $(OBJ_FILES)
	$(CPP_COMPILER) $(LDFLAGS) -o $(APPNAME) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	${CPP_COMPILER} $(CPP_FLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $@
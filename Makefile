APPNAME := advent2024
CPP_COMPILER := g++
COMPILER_FLAGS := -std=c++20 -fdiagnostics-color=always

SRC_DIR := src
OBJ_DIR := obj

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))

full:
	$(CPP_COMPILER) $(COMPILER_FLAGS) $(LDFLAGS) -o $(APPNAME) $(CPP_FILES)

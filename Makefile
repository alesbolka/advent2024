APPNAME := advent2024
BUILDER := g++
COMPILER_FLAGS := -std=c++20 -fdiagnostics-color=always

SRC_DIR := src
OBJ_DIR := build

SOURCE_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJECT_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCE_FILES))
HEADER_FILES := $(wildcard $(SRC_DIR)/**/*.h)

DEPENDS := $(patsubst %.cpp,%.d,$(SOURCE_FILES))

-include $(DEPENDS)

full: $(OBJECT_FILES) $(HEADER_FILES)
	$(BUILDER) $(OBJECT_FILES) -o $(APPNAME)

partial: $(OBJECT_FILES)
	$(BUILDER) $(OBJECT_FILES) -o $(APPNAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER_FILES)
	$(info Compiling $<...)
	@$(shell mkdir -p $(dir $@))
	@$(BUILDER) $(COMPILER_FLAGS) -MMD -MP -c $< -o $@

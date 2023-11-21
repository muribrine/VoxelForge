CXX := g++  # Change this to your compiler if using a different one
CXXFLAGS := -std=c++17 -Wall -Wextra -Iengine
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

SRC_DIR := engine
OBJ_DIR := bin
BIN_DIR := bin

SOURCES := $(wildcard $(SRC_DIR)/**/**/**/*.cpp $(SRC_DIR)/**/**/*.cpp $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp) game/main.cpp
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

EXECUTABLE := game

all: $(BIN_DIR)/$(EXECUTABLE)

$(BIN_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(EXECUTABLE)

.PHONY: all clean
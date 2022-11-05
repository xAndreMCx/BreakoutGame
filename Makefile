TARGET = Breakout.exe

INCLUDE_DIR = ./include
LIB_DIR = ./lib
BIN_DIR = ./bin
SRC_DIR = ./src
SOURCE_DIR = $(SRC_DIR) $(SRC_DIR)/Game $(SRC_DIR)/OpenGL

CXX = g++
CC = gcc
WARNFLAGS = -Wall -Wextra
CXXFLAGS = -g $(WARNFLAGS) -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR) -lglad -lglfw3 -lgdi32

CPPFILES = $(foreach DIR, $(SOURCE_DIR), $(wildcard $(DIR)/*.cpp))
OBJECTS = $(CPPFILES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
DEPENDS = $(patsubst %.cpp, $(BIN_DIR)/%.d, $(notdir $(CPPFILES)))
# DEPENDS = $(CPPFILES:$=)

.PHONY: all clean list

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) $(OBJECTS)

list:
	@echo "obj: " $(OBJECTS)
	@echo "cpp: " $(CPPFILES)
	@echo "dep: " $(DEPENDS)

test:
	g++ -MM -c src/main.cpp -I./include
CC = g++
CFLAGS = -Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces -g -O0
INCLUDE_PATHS = -I. -IC:/raylib/raylib-5.5_win64_mingw-w64/include
LDFLAGS = -L. -LC:/raylib/raylib-5.5_win64_mingw-w64/lib
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRC_DIR = src
OBJ_DIR = obj

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Output executable
TARGET = main

# Create obj directory if it doesn't exist
$(shell mkdir -p $(OBJ_DIR))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

clean:
	del /Q $(OBJ_DIR)\*.o $(TARGET).exe

.PHONY: all clean


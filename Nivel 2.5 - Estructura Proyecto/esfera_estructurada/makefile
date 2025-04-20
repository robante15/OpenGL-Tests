# Makefile para el proyecto de esferas rebotando
CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lGL -lGLU -lglut -std=c++11
TARGET = bouncing_spheres
SOURCES = main.cpp scene.cpp sphere.cpp camera.cpp math.cpp
BUILD_DIR = build
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BUILD_DIR)/$(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
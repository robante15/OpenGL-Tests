# Makefile para el proyecto de esferas rebotando
CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lGL -lGLU -lglut -std=c++11
TARGET = bouncing_spheres
SOURCES = escena.cpp sphere.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
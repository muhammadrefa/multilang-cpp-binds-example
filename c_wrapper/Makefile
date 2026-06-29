# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

CXX = g++
CXXFLAGS = -fPIC -Wall -std=c++17
LDFLAGS = -shared -L. -lmylibrary -Wl,-rpath,'$$ORIGIN'

# Source and object files
SOURCES = calculator.cpp circular_buffer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
LIBRARY = libmylibraryc.so

# Default target
all: $(LIBRARY)

# Create shared library
$(LIBRARY): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

libtest: main.c $(LIBRARY)
	$(CC) $(CFLAGS) -o libtest main.c -L. -lmylibraryc -lmylibrary -Wl,-rpath,.

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(LIBRARY) libtest

.PHONY: all clean

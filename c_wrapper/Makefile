# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -shared -L. -lmylibrary -Wl,-rpath,'$$ORIGIN'

# For Windows
ifeq ($(OS),Windows_NT)
	DLL_PREFIX = 
	DLL_EXT = dll
	CXXFLAGS += -DMYLIB_BUILD_DLL
else
	DLL_PREFIX = lib
	DLL_EXT = so
	CXXFLAGS += -fPIC
endif

# Source and object files
SOURCES = calculator.cpp circular_buffer.cpp
SOURCES += animal/animal.cpp animal/dog.cpp animal/cat.cpp animal/tiger.cpp
OBJECTS = $(SOURCES:.cpp=.o)
LIBRARY = $(DLL_PREFIX)mylibraryc.$(DLL_EXT)

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

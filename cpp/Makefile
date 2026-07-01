# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -shared

# For Windows
ifeq ($(OS),Windows_NT)
	DLL_PREFIX = 
	DLL_EXT = dll
else
	DLL_PREFIX = lib
	DLL_EXT = so
	CXXFLAGS += -fPIC
endif

# Source and object files
SOURCES = calculator.cpp circular_buffer.cpp
SOURCES += animal/animal.cpp animal/dog.cpp animal/cat.cpp animal/tiger.cpp
OBJECTS = $(SOURCES:.cpp=.o)
LIBRARY = $(DLL_PREFIX)mylibrary.$(DLL_EXT)

# Default target
all: $(LIBRARY)

# Create shared library
$(LIBRARY): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and run test (C++ version)
libtest: main.cpp $(LIBRARY)
	$(CXX) $(CXXFLAGS) -o libtest main.cpp -L. -lmylibrary -Wl,-rpath,.

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(LIBRARY) libtest

.PHONY: all clean

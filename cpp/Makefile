# Compiler and flags
CXX = g++
CXXFLAGS = -fPIC -Wall -std=c++17
LDFLAGS = -shared

# Source and object files
SOURCES = calculator.cpp circular_buffer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
LIBRARY = libmylibrary.so

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

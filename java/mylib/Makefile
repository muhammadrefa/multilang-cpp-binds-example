# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Inative/inc
LDFLAGS = -shared -Lnative/lib -lmylibraryc -Wl,-rpath,'$$ORIGIN'

# For Windows
ifeq ($(OS),Windows_NT)
	DLL_PREFIX = 
	DLL_EXT = dll

    JAVA_HOME ?= C:/Program Files/Java/jdk-21
    JNI_INC = \
    -I$(JAVA_HOME)/include \
    -I$(JAVA_HOME)/include/win32
else
	DLL_PREFIX = lib
	DLL_EXT = so
    CFLAGS += -fPIC

    JAVA_HOME ?= /usr/lib64/jvm/java-1.8.0-openjdk
    JNI_INC = \
		-I$(JAVA_HOME)/include \
		-I$(JAVA_HOME)/include/linux
endif

SOURCES = \
	src/main/jni/CalculatorNative.c \
	src/main/jni/helpers/ref_helper.c

OBJECTS = $(SOURCES:.c=.o)
LIBRARY = $(DLL_PREFIX)mylibrary_jni.$(DLL_EXT)

# Default target
all: $(LIBRARY)

# Create shared library
$(LIBRARY): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile .cpp to .o
%.o: %.c
	$(CC) $(CFLAGS) $(JNI_INC) -c $< -o $@

# headers:
#     javac -h src/main/jni $(shell find src/main/java -name "*.java")

clean:
	rm -f $(OBJECTS) $(LIBRARY)

.PHONY: all clean

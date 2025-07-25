# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
# CXXFLAGS += -DUSE_WOLFRAM_LIB -fPIC -shared
# Paths
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILE = $(TEST_DIR)/test_main.cpp
TEST_EXE = $(BUILD_DIR)/test_main

# Wolfram build
WOLFRAM_TARGET = $(BUILD_DIR)/Triangulate.dylib
WOLFRAM_FLAGS = -DUSE_WOLFRAM_LIB -fPIC -shared
WOLFRAM_INCLUDE = -I"$(WOLFRAM_KERNEL_INCLUDE)"
# Optional Wolfram support
ifeq ($(USE_WOLFRAM_LIB),1)
    CXXFLAGS += -DUSE_WOLFRAM_LIB -fPIC -shared -I$(WOLFRAM_KERNEL_INCLUDE)
endif

# Default target
all: $(TEST_EXE)

# Build test executable
$(TEST_EXE): $(SRC_FILES) $(TEST_FILE)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Build Wolfram-compatible shared library
wolfram: export WOLFRAM_KERNEL_INCLUDE := /usr/local/Wolfram/Mathematica/12.3/SystemFiles/IncludeFiles/C
wolfram: $(SRC_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(WOLFRAM_FLAGS) $(WOLFRAM_INCLUDE) $^ -o $(WOLFRAM_TARGET)

# Clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all wolfram clean

benchmark:
	g++ -std=c++17 -Wall -Iinclude test/test_benchmark.cpp src/EarClippingCore.cpp src/Geometry.cpp -o build/benchmark
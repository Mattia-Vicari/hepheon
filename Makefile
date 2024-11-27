CXX = g++ -std=c++20
SRCS = $(shell find src -name "*.cpp")
LIBS = -lglfw3 -lglm
INCLUDES = -Iinclude
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

DEBUG_DIR = build/debug
DEBUG_FLAGS = -Wall -Wextra -O0 


clean:
	rm -rf $(DEBUG_DIR)/main

build_debug:
	$(CXX) $(DEBUG_FLAGS) $(LIBS) $(FRAMEWORKS) $(INCLUDES) -o $(DEBUG_DIR)/main $(SRCS)

run_debug:
	./$(DEBUG_DIR)/main

debug: clean build_debug run_debug


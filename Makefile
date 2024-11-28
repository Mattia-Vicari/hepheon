OS_NAME := $(shell uname -s)

CXX = g++ -std=c++20
SRCS = $(shell find src -name "*.cpp")
INCLUDES = -Iinclude

DEBUG_DIR = build/debug
TEST_DIR = test/build

DEBUG_FLAGS = -Wall -Wextra -O0 
TEST_FLAGS = -Wall -Wextra -O0 -fprofile-arcs -ftest-coverage

ifeq ($(OS_NAME), Darwin)
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
LIBS = -lglfw3 -lglm
LCOV_IGNORE = --ignore-errors inconsistent
else
FRAMEWORKS =
LIBS = -lGL -lGLEW -lglfw
LCOV_IGNORE =
endif

clean:
	rm -rf $(DEBUG_DIR)/main
	rm -rf $(TEST_DIR)/*

build_debug:
	@mkdir -p $(DEBUG_DIR)
	$(CXX) $(DEBUG_FLAGS) $(LIBS) $(FRAMEWORKS) $(INCLUDES) -o $(DEBUG_DIR)/main $(SRCS) main.cpp

run_debug:
	./$(DEBUG_DIR)/main

debug: clean build_debug run_debug

linux_env:
	sudo apt-get update && sudo apt-get install -y xorg-dev libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev xvfb
	sudo apt-get update && sudo apt-get install -y libglew-dev libglfw3 libglfw3-dev libglm-dev 
	sudo apt-get update && sudo apt-get install -y lcov

build_test:
	@mkdir -p $(TEST_DIR)
	$(CXX) $(TEST_FLAGS) $(FRAMEWORKS) $(INCLUDES) -o $(TEST_DIR)/test $(shell find test -name "*.cpp") $(SRCS) $(LIBS)

coverage:
	./$(TEST_DIR)/test
	gcov -o ./$(TEST_DIR) src/*.cpp 

coverage_report:
	cd $(TEST_DIR) && lcov --capture --directory . --output-file coverage.info $(LCOV_IGNORE) 
	cd $(TEST_DIR) && lcov --extract coverage.info '*/src/*' --output-file coverage.info
	cd $(TEST_DIR) && genhtml coverage.info --output-directory report 

open_coverage_report:
	cd $(TEST_DIR)/report && open index.html

test: clean build_test coverage coverage_report

run_test_report: clean test coverage coverage_report open_coverage_report
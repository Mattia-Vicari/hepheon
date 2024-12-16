OS_NAME := $(shell uname -s)

CXX = g++ -std=c++20
SRCS = $(shell find src -name "*.cpp")
IMGUI = deps/imgui
DEPS = $(IMGUI)/imgui.cpp \
	   $(IMGUI)/imgui_draw.cpp \
	   $(IMGUI)/imgui_widgets.cpp \
	   $(IMGUI)/imgui_tables.cpp \
	   $(IMGUI)/imgui_demo.cpp \
	   $(IMGUI)/backends/imgui_impl_glfw.cpp \
	   $(IMGUI)/backends/imgui_impl_opengl3.cpp
INCLUDES = -Iinclude -Ideps/imgui

DEBUG_DIR = build/debug
RELEASE_DIR = build/release
TEST_DIR = test/build

DEBUG_FLAGS = -Wall -Wextra -O0 
RELEASE_FLAGS = -Wall -Wextra -O3
TEST_FLAGS = -Wall -Wextra -O0 -fprofile-arcs -ftest-coverage

ifeq ($(OS_NAME), Darwin)
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
INCLUDES += -I/opt/homebrew/include/lua
LIBS = -lglfw3 -lglm -L/opt/homebrew/lib -llua 
LCOV_IGNORE = --ignore-errors inconsistent
else
FRAMEWORKS =
INCLUDES += -I/usr/include/lua5.4
LIBS = -lGL -lGLEW -lglfw -llua5.4
LCOV_IGNORE =
endif

clean:
	rm -rf $(DEBUG_DIR)/main
	rm -rf $(RELEASE_DIR)/main
	rm -rf $(TEST_DIR)/*

build_debug:
	@mkdir -p $(DEBUG_DIR)
	$(CXX) $(DEBUG_FLAGS) $(FRAMEWORKS) $(INCLUDES) -o $(DEBUG_DIR)/main $(SRCS) $(DEPS) main.cpp $(LIBS) 

run_debug:
	./$(DEBUG_DIR)/main

debug: clean build_debug run_debug

build_release:
	@mkdir -p $(RELEASE_DIR)
	$(CXX) $(RELEASE_FLAGS) $(FRAMEWORKS) $(INCLUDES) -o $(RELEASE_DIR)/main $(SRCS) $(DEPS) main.cpp $(LIBS)

run_release:
	./$(RELEASE_DIR)/main

release: clean build_release run_release

linux_env:
	sudo apt-get update && sudo apt-get install -y xorg-dev libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev xvfb
	sudo apt-get update && sudo apt-get install -y libglew-dev libglfw3 libglfw3-dev libglm-dev 
	sudo apt-get update && sudo apt-get install -y lcov
	sudo apt-get update && sudo apt-get install -y lua5.4 liblua5.4-dev

build_test:
	@mkdir -p $(TEST_DIR)
	$(CXX) $(TEST_FLAGS) $(FRAMEWORKS) $(INCLUDES) -o $(TEST_DIR)/test $(shell find test -name "*.cpp") $(SRCS) $(DEPS) $(LIBS)

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

run_test_report: clean test open_coverage_report
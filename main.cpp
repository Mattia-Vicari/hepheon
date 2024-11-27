#if defined (__APPLE_CC__)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h> 
#endif

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <ui/ui.h>
#include <ui/panel.h>
#include <ui/button.h>

const int WIDTH = 1080;
const int HEIGHT = 720;
const bool FULLSCREEN = false;
const char* WINDOW_TITLE = "Universa";


std::string read_shader_source(const char *file_path) {
    std::ifstream shader_file(file_path);
    std::stringstream shader_stream;
    shader_stream << shader_file.rdbuf();
    shader_file.close();

    return shader_stream.str();
}


unsigned int compile(int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}


unsigned int create_program(const char* vertex_shader_path, const char* fragment_shader_path) {
    unsigned int program;
    std::string vertex_code  = read_shader_source(vertex_shader_path);
    std::string fragment_code = read_shader_source(fragment_shader_path);

    unsigned int vertex_shader = compile(GL_VERTEX_SHADER, vertex_code.c_str());
    unsigned int fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_code.c_str());

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // Check for linking errors
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Press ESC
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    ui::UI* ui = (ui::UI*) glfwGetWindowUserPointer(window);

    if (ui == nullptr) {
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        ui->check_click(xpos, ypos);
    }
}


int main() {
    if (!glfwInit()) {
        std::cerr << "ERROR: Impossible to initialize glfw." << std::endl;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    GLFWwindow* window;

    if (FULLSCREEN) {
        window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, glfwGetPrimaryMonitor(), NULL);
    } else {
        window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, NULL, NULL);
    }
    
    if (!window) {
        std::cerr << "ERROR: Impossible to create a window." << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSwapInterval(0);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned int ui_program = create_program(
        "src/shaders/ui_vertex_shader.glsl",
        "src/shaders/ui_fragment_shader.glsl"
    );

    ui::Panel panel = ui::Panel(
        glm::vec3(0, -1, 0),
        glm::vec3(0.2, 0.0, 0.0),
        glm::ivec2(2*WIDTH, 200),
        0,
        ui::Anchor::BOTTOM,
        glm::vec2(2*WIDTH, 2*HEIGHT)
    );

    ui::Button button = ui::Button(
        glm::vec3(0, 0, -0.1),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::ivec2(200, 100),
        25,
        ui::Anchor::CENTER,
        glm::vec2(2*WIDTH, 2*HEIGHT)
    );

    ui::Button button2 = ui::Button(
        glm::vec3(0, 0.5, -0.1),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::ivec2(200, 100),
        25,
        ui::Anchor::CENTER,
        glm::vec2(2*WIDTH, 2*HEIGHT)
    );


    ui::UI ui;
    ui.add_panel(panel);
    ui.add_button(button);
    ui.add_button(button2);

    glfwSetWindowUserPointer(window, &ui);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int width;
        int height;

        glfwGetWindowSize(window, &width, &height);

        ui.draw(ui_program);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteProgram(ui_program);
    glfwTerminate();

    return 0;
}


// needs to be before glfw include to suppress deprecation warnings
#include "opengl.h"

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "error.h"
#include "shaders/compiler.h"
#include "ui/ui.h"
#include "ui/panel.h"
#include "ui/button.h"

const int WIDTH = 1080;
const int HEIGHT = 720;
const bool FULLSCREEN = false;
const char* WINDOW_TITLE = "Hepheon";


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
        error("Impossible to initialize glfw.");
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
        error("Impossible to create a window.");
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

    unsigned int ui_program = shaders::create_program(
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


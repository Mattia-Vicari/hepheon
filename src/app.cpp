#include "app.h"


void app::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Press ESC
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // Reload Lua with Ctrl + R
    if (key == GLFW_KEY_R && action == GLFW_PRESS && mods == GLFW_MOD_CONTROL) {
        lua::load();
    }
}


void app::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
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


void app::framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    ui::UI* ui = (ui::UI*) glfwGetWindowUserPointer(window);

    if (ui == nullptr) {
        return;
    }

    int window_width;
    int window_height;

    glfwGetWindowSize(window, &window_width, &window_height);

    ui->resize(
        glm::ivec2(window_width, window_height),
        glm::ivec2(width, height)
    );
}


app::App::App() {
    if (!glfwInit()) {
        logger::error("Impossible to initialize glfw.");
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    if (app::FULLSCREEN) {
        window = glfwCreateWindow(app::WIDTH, app::HEIGHT, app::WINDOW_TITLE, glfwGetPrimaryMonitor(), NULL);
    } else {
        window = glfwCreateWindow(app::WIDTH, app::HEIGHT, app::WINDOW_TITLE, NULL, NULL);
    }
    
    if (!window) {
        logger::error("Impossible to create a window.");
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSwapInterval(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


app::App::~App() {
    glfwDestroyWindow(window);
    glfwTerminate();
}


void app::App::attach_ui(ui::UI* ui) {
    this->ui = ui;
    glfwSetWindowUserPointer(window, ui);
}


void app::App::run(const unsigned int ui_program) {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ui->draw(ui_program);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

#include "app.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
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
}


void app::framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
}
#pragma clang diagnostic pop


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
        window = glfwCreateWindow(app::WIDTH, app::HEIGHT, app::WINDOW_TITLE.c_str(), glfwGetPrimaryMonitor(), NULL);
    } else {
        window = glfwCreateWindow(app::WIDTH, app::HEIGHT, app::WINDOW_TITLE.c_str(), NULL, NULL);
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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    // Compile shaders
    render_program = shaders::create_program("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
}


app::App::~App() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}


void app::App::run() {
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Shaders rendering 
    glUseProgram(render_program);

    // Create buffers for a white cube
    float vertices[] = {
        // Positions          // Colors (white)
        -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  // Back bottom-left
        0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  // Back bottom-right
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  // Back top-right
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  // Back top-left

        -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  // Front bottom-left
        0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  // Front bottom-right
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  // Front top-right
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  // Front top-left
    };

    unsigned int indices[] = {
        // Back face
        0, 1, 2,  // Triangle 1
        2, 3, 0,  // Triangle 2

        // Front face
        4, 5, 6,  // Triangle 3
        6, 7, 4,  // Triangle 4

        // Left face
        0, 3, 7,  // Triangle 5
        7, 4, 0,  // Triangle 6

        // Right face
        1, 5, 6,  // Triangle 7
        6, 2, 1,  // Triangle 8

        // Bottom face
        0, 1, 5,  // Triangle 9
        5, 4, 0,  // Triangle 10

        // Top face
        3, 2, 6,  // Triangle 11
        6, 7, 3   // Triangle 12
    };

    unsigned int vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Create proj * view * model matrix
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)app::WIDTH / (float)app::HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 pvm = proj * view * model;

    // Pass pvm in uniform buffer
    unsigned int pvm_location = glGetUniformLocation(render_program, "pvm");
    glUniformMatrix4fv(pvm_location, 1, GL_FALSE, &pvm[0][0]);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // ImGui rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    // Cleanup
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}


GLFWwindow* app::App::get_window() {
    return window;
}
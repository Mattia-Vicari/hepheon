#ifndef __APP_H__ 
#define __APP_H__

#include <stdio.h>

#include "opengl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "logger.h"
#include "lua/loader.h"
#include "shaders/compiler.h"
#include "state.h"

namespace app {

/**
 * @brief Callback for key events.
 * 
 * @param[in] window The window that received the event.
 * @param[in] key The keyboard key that was pressed or released.
 * @param[in] scancode The system-specific scancode of the key.
 * @param[in] action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
 * @param[in] mods Bit field describing which modifier keys were held down.
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

/**
 * @brief Callback for mouse button events.
 * 
 * @param[in] window The window that received the event.
 * @param[in] button The mouse button that was pressed or released.
 * @param[in] action GLFW_PRESS or GLFW_RELEASE.
 * @param[in] mods Bit field describing which modifier keys were held down.
 */
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

/**
 * @brief Callback for window resize events.
 * 
 * @param[in] window The window that was resized.
 * @param[in] width The new width of the window.
 * @param[in] height The new height of the window.
 */
void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

class App {
 public:
    App();
    ~App();
    void run();
    GLFWwindow* get_window();

 private:
    GLFWwindow* window;
    unsigned int render_program;
};

}

#endif  // __APP_H__ 

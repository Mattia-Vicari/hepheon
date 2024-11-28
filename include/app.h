#ifndef __APP_H__ 
#define __APP_H__

#include <GLFW/glfw3.h>

#include "../app/settings.h"

#include "error.h"
#include "ui/ui.h"

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

class App {
 public:
    App();
    ~App();
    void attach_ui(ui::UI* ui);
    void run(const unsigned int ui_program);

 private:
    GLFWwindow* window;
    ui::UI* ui;
};

}

#endif  // __APP_H__ 

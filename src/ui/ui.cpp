#include "ui/ui.h"


void ui::UI::add_panel(Panel panel) {
    panels.push_back(panel);
}


void ui::UI::add_button(Button button) {
    buttons.push_back(button);
}


void ui::UI::draw(const GLuint ui_program) {
    for (Panel panel : panels) {
        panel.draw(ui_program);
    }

    for (Button button : buttons) {
        button.draw(ui_program);
    }
}


void ui::UI::check_click(int x, int y) {
    for (Button button : buttons) {
        if (button.hit(x, y)) {
            button.execute_callback();
        }
    }
}


void ui::UI::resize(glm::ivec2 window_size, glm::ivec2 framebuffer_size) {
    for (Panel& panel : panels) {
        panel.resize(window_size, framebuffer_size);
    }

    for (Button& button : buttons) {
        button.resize(window_size, framebuffer_size);
    }
}

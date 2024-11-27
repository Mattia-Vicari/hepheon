#ifndef __UI_UI_H__
#define __UI_UI_H__

#include <iostream>

#include <vector>
#include <ui/panel.h>
#include <ui/button.h>

namespace ui {

class UI {
 public:
    std::vector<Panel> panels;
    std::vector<Button> buttons;

    UI() {};

    void add_panel(Panel panel) {
        panels.push_back(panel);
    }

    void add_button(Button button) {
        buttons.push_back(button);
    }

    void draw(const GLuint ui_program) {
        for (Panel panel : panels) {
            panel.draw(ui_program);
        }

        for (Button button : buttons) {
            button.draw(ui_program);
        }
    }

    void check_click(int x, int y) {
        for (Button button : buttons) {
            if (button.hit(x, y)) {
                std::cout << "Button clicked!" << std::endl;
            }
        }
    }
};

}  // namespace ui

#endif  // __UI_UI_H__
#ifndef __UI_BUTTON_H__
#define __UI_BUTTON_H__

#include <iostream>

#include "ui/panel.h"

namespace ui {

class Button : Panel {
 public:
    Button(
        glm::vec3 rel_pos,
        glm::vec3 color,
        glm::ivec2 rel_size,
        int radius,
        Anchor anchor,
        glm::vec2 window_size
    ) : Panel(rel_pos, color, rel_size, radius, anchor, window_size) {};

    void draw(const GLuint ui_program) {
        Panel::draw(ui_program);
    }

    bool hit(const int x, const int y) {
        return (
            x >= screen_pos.x - abs_size.x * scale_x / 2 &&
            x <= screen_pos.x + abs_size.x * scale_x / 2 &&
            y >= screen_pos.y - abs_size.y * scale_y / 2 &&
            y <= screen_pos.y + abs_size.y * scale_y / 2
        );
    }
};

}  // namespace ui

#endif  // __UI_BUTTON_H__
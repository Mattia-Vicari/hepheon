#include "ui/button.h"


ui::Button::Button(
    glm::vec3 rel_pos,
    glm::vec3 color,
    glm::ivec2 rel_size,
    int radius,
    Anchor anchor,
    glm::vec2 framebuffer_size,
    glm::vec2 window_size
) : Panel(rel_pos, color, rel_size, radius, anchor, framebuffer_size, window_size) {};


void ui::Button::draw(const GLuint ui_program) {
    Panel::draw(ui_program);
}


bool ui::Button::hit(const int x, const int y) {
    return (
        x >= screen_pos.x - abs_size.x * scale_x / 2 &&
        x <= screen_pos.x + abs_size.x * scale_x / 2 &&
        y >= screen_pos.y - abs_size.y * scale_y / 2 &&
        y <= screen_pos.y + abs_size.y * scale_y / 2
    );
}

void ui::Button::resize(glm::ivec2 window_size, glm::ivec2 framebuffer_size) {
    Panel::resize(window_size, framebuffer_size);
}


void ui::Button::set_callback(std::function<void()> callback) {
    this->callback = callback;
}


void ui::Button::execute_callback() {
    callback();
}

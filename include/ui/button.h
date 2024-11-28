#ifndef __UI_BUTTON_H__
#define __UI_BUTTON_H__

#include <iostream>

#include "ui/panel.h"

namespace ui {

class Button : Panel {
 public:
    /**
     * @brief Construct a new Button object.
     * 
     * @param[in] rel_pos The relative position of the button.
     * @param[in] color The color of the button.
     * @param[in] rel_size The relative size of the button.
     * @param[in] radius The radius of the button.
     * @param[in] anchor The anchor of the button.
     * @param[in] window_size The size of the window.
     */
    Button(
        glm::vec3 rel_pos,
        glm::vec3 color,
        glm::ivec2 rel_size,
        int radius,
        Anchor anchor,
        glm::vec2 window_size
    );

    /**
     * @brief Draw the button.
     * 
     * @param[in] ui_program The program to use for drawing the button.
     */
    void draw(const GLuint ui_program);

    /**
     * @brief Check if the button was clicked.
     * 
     * @param[in] x The x coordinate of the click.
     * @param[in] y The y coordinate of the click.
     * @return true if the button was clicked, false otherwise.
     */
    bool hit(const int x, const int y);
};

}  // namespace ui

#endif  // __UI_BUTTON_H__
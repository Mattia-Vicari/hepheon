#ifndef __UI_UI_H__
#define __UI_UI_H__

#include <iostream>
#include <vector>

#include "ui/panel.h"
#include "ui/button.h"

namespace ui {

class UI {
 public:
    std::vector<Panel> panels;
    std::vector<Button> buttons;

    /**
     * @brief Construct a new UI object.
     */
    UI() {};

    /**
     * @brief Add a panel to the UI.
     * 
     * @param[in] panel The panel to add.
     */
    void add_panel(Panel panel);

    /**
     * @brief Add a button to the UI.
     * 
     * @param[in] button The button to add.
     */
    void add_button(Button button);

    /**
     * @brief Draw the UI.
     * 
     * @param[in] ui_program The program to use for drawing the UI.
     */
    void draw(const GLuint ui_program);

    /**
     * @brief Check if a button was clicked.
     * 
     * @param[in] x The x coordinate of the click.
     * @param[in] y The y coordinate of the click.
     */
    void check_click(int x, int y);
};

}  // namespace ui

#endif  // __UI_UI_H__
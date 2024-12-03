#ifndef __APP_UI_H__
#define __APP_UI_H__

#include "settings.h"

#include "logger.h"
#include "ui/button.h"
#include "ui/panel.h"
#include "ui/ui.h"

namespace app {

/**
 * Populate the UI
 * 
 * @param[out] ui The UI to populate
 */
inline void populate_ui(ui::UI* ui) {
    ui::Panel panel = ui::Panel(
        glm::vec3(0, -1, 0),
        glm::vec3(0.2, 0.0, 0.0),
        glm::ivec2(2*WIDTH, 200),
        0,
        ui::Anchor::BOTTOM,
        glm::vec2(2*WIDTH, 2*HEIGHT),
        glm::vec2(WIDTH, HEIGHT)
    );

    ui::Button button = ui::Button(
        glm::vec3(0, 0, -0.1),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::ivec2(200, 100),
        25,
        ui::Anchor::CENTER,
        glm::vec2(2*WIDTH, 2*HEIGHT),
        glm::vec2(WIDTH, HEIGHT)
    );

    button.set_callback([]() {
        logger::info("Button 1 clicked!");
    });

    ui::Button button2 = ui::Button(
        glm::vec3(0, 0.5, -0.1),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::ivec2(200, 100),
        25,
        ui::Anchor::CENTER,
        glm::vec2(2*WIDTH, 2*HEIGHT),
        glm::vec2(WIDTH, HEIGHT)
    );

    button2.set_callback([]() {
        logger::info("Button 2 clicked!");
    });

    ui->add_panel(panel);
    ui->add_button(button);
    ui->add_button(button2);
}

}  // namespace app

#endif  // __APP_UI_H__


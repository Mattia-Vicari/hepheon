#include "ui/ui.h"

void ui::UI::check_click(int x, int y) {
    for (Button button : buttons) {
        if (button.hit(x, y)) {
            std::cout << "Button clicked!" << std::endl;
        }
    }
}
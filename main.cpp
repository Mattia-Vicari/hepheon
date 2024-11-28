#include "app/settings.h"
#include "app/ui.h"

#include "app.h"
#include "error.h"
#include "shaders/compiler.h"
#include "ui/ui.h"


int main() {
    app::App hepheon;
    ui::UI ui;
    app::populate_ui(&ui);
    hepheon.attach_ui(&ui);


    unsigned int ui_program = shaders::create_program(
        "src/shaders/ui_vertex_shader.glsl",
        "src/shaders/ui_fragment_shader.glsl"
    );

    hepheon.run(ui_program);

    glDeleteProgram(ui_program);

    return 0;
}

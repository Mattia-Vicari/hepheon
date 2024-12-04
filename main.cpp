#include "app/settings.h"
#include "app/ui.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "app.h"
#include "logger.h"
#include "lua/loader.h"
#include "shaders/compiler.h"
#include "ui/ui.h"


int main() {
    logger::info("Welcome to Hepheon!");
    
    lua::load();

    app::App hepheon;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(hepheon.get_window(), true);
    ImGui_ImplOpenGL3_Init("#version 150");

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    hepheon.run();

    return 0;
}

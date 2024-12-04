#include "app.h"
#include "logger.h"
#include "lua/loader.h"
#include "shaders/compiler.h"


int main() {
    logger::info("Welcome to Hepheon!");
    
    lua::load();

    app::App hepheon;

    hepheon.run();

    return 0;
}

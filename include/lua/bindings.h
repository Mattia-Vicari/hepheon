#ifndef __LUA_BINDINGS_H__
#define __LUA_BINDINGS_H__

#include <lua.hpp>

#include "logger.h"
#include "state.h"

namespace lua {

inline int log_info(lua_State* L) {
    const char* message = lua_tostring(L, 1);
    logger::info(message);
    return 0;
}

inline int log_warning(lua_State* L) {
    const char* message = lua_tostring(L, 1);
    logger::warning(message);
    return 0;
}

inline int log_error(lua_State* L) {
    const char* message = lua_tostring(L, 1);
    logger::error(message);
    return 0;
}

inline int set_width(lua_State* L) {
    int width = lua_tointeger(L, 1);
    app::WIDTH = width;
    return 0;
}

inline int set_height(lua_State* L) {
    int height = lua_tointeger(L, 1);
    app::HEIGHT = height;
    return 0;
}

inline int set_fullscreen(lua_State* L) {
    bool fullscreen = lua_toboolean(L, 1);
    app::FULLSCREEN = fullscreen;
    return 0;
}

inline int set_window_title(lua_State* L) {
    const char* title = lua_tostring(L, 1);
    app::WINDOW_TITLE = title;
    return 0;
}

inline void register_bindings(lua_State* L) {
    lua_register(L, "_log_info", log_info);
    lua_register(L, "_log_warning", log_warning);
    lua_register(L, "_log_error", log_error);
    lua_register(L, "_set_width", set_width);
    lua_register(L, "_set_height", set_height);
    lua_register(L, "_set_fullscreen", set_fullscreen);
    lua_register(L, "_set_window_title", set_window_title);
}

}

#endif  // __LUA_BINDINGS_H__
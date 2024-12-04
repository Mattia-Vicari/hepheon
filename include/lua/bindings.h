#ifndef __LUA_BINDINGS_H__
#define __LUA_BINDINGS_H__

#include <lua.hpp>

#include "logger.h"

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

inline void register_bindings(lua_State* L) {
    lua_register(L, "c_log_info", log_info);
    lua_register(L, "c_log_warning", log_warning);
    lua_register(L, "c_log_error", log_error);
}

}

#endif  // __LUA_BINDINGS_H__
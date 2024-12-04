#ifndef __LUA_LOADER_H__
#define __LUA_LOADER_H__

#include <lua.hpp>

#include "lua/bindings.h"
#include "logger.h"

namespace lua {

inline void load() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    register_bindings(L);

    if (luaL_dofile(L, "lua/main.lua") != LUA_OK) {
        const char* error = lua_tostring(L, -1);
        logger::error(error);
    }

    lua_getglobal(L, "load");

    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        const char* error = lua_tostring(L, -1);
        logger::error(error);
    }

    logger::info("Lua loaded successfully!");

    lua_close(L);
}

}



#endif  // __LUA_LOADER_H__
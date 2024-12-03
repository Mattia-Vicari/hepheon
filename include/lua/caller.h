#ifndef __LUA_CALLER_H__
#define __LUA_CALLER_H__

#include <lua.hpp>

#include "logger.h"

namespace lua {

void init() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, "lua/main.lua") != LUA_OK) {
        const char* error = lua_tostring(L, -1);
        logger::error(error);
    } else {
        logger::info("Lua main script loaded successfully!");
    }

    lua_getglobal(L, "init");

    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        const char* error = lua_tostring(L, -1);
        logger::error(error);
    } else {
        logger::info("Lua init function executed successfully!");
    }

    lua_close(L);
}

}



#endif  // __LUA_CALLER_H__
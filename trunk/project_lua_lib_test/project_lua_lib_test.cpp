#include "project_lua_lib_test.h"
#include <stdio.h>
#include <iostream>

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

static int add(lua_State* L) {
    int a = lua_tonumber(L,1);
    int b = lua_tonumber(L,2);
    int c = a+b;
    lua_pop(L,2);
    lua_pushnumber(L,c);
    return 1;
}

static int project_lua_lib_test2(lua_State* L);

static int start(lua_State* L) {
    luaL_requiref(L, "project_lua_lib_test2", project_lua_lib_test2, 0);
    return 0;
}

int luaopen_project_lua_lib_test(lua_State* L) {
    luaL_Reg l[] = {
        { "add", add },
        { "start", start },
        { NULL, NULL },
    };
    luaL_checkversion(L);
    luaL_newlib(L,l);

    return 1;
}

static int project_lua_lib_test2(lua_State* L) {
    luaL_Reg l[] = {
        { "add", add },
        { NULL, NULL },
    };
    luaL_checkversion(L);
    luaL_newlib(L,l);

    return 1;
}

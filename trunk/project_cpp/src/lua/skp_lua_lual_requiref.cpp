#include "skp_lua_lual_requiref.h"
#include "src/common.h"
#include <stdio.h>
#include <iostream>

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class Clual_requiref
{
public:
    int add(int a, int b)
    {
        return a + b;
    }
};

struct Clual_requiref_userdata
{
    Clual_requiref *m_Clual_requiref;
};

static int lual_requiref_new(lua_State* L)
{
    log_print("lual_requiref_new");
    Clual_requiref_userdata *p = (Clual_requiref_userdata *)lua_newuserdata(L, sizeof(Clual_requiref_userdata));
    p->m_Clual_requiref = new Clual_requiref();
    luaL_getmetatable(L, "lual_requiref");
    lua_setmetatable(L, -2);
    return 1;
}

static int lual_requiref_add(lua_State* L) {
    log_print("lual_requiref_add");
    Clual_requiref_userdata *p = (Clual_requiref_userdata *)luaL_checkudata(L, 1, "lual_requiref");

    int a = luaL_checkinteger(L, 2);
    int b = luaL_checkinteger(L, 3);

    log_print("a = %d, b = %d", a, b);
    int c = p->m_Clual_requiref->add(a, b);
    log_print("c = %d", c);
    lua_pushinteger(L, c);

    return 1;
}

static int lual_requiref_to_string(lua_State* L) {
    log_print("lual_requiref_to_string");
    Clual_requiref_userdata *p = (Clual_requiref_userdata *)luaL_checkudata(L, 1, "lual_requiref");

    char msg[256] = "Clual_requiref";
    lua_pushstring(L, msg);

    return 1;
}

/*
static int lual_requiref2(lua_State* L);

static int start(lua_State* L) {
    luaL_requiref(L, "lual_requiref2", lual_requiref2, 0);
    return 0;
}

static int lual_requiref2(lua_State* L) {
    luaL_Reg l[] = {
        { "add", lual_requiref_add },
        { NULL, NULL },
    };
    luaL_checkversion(L);
    luaL_newlib(L,l);

    return 1;
}
*/

static luaL_Reg lual_requiref_lib[] = {
    { "new", lual_requiref_new },
    //{ "start", start },
    { NULL, NULL },
};

static luaL_Reg lual_requiref_func_lib[] = {
    { "add", lual_requiref_add },
    { "__tostring", lual_requiref_to_string},
    { NULL, NULL },
};


int luaopen_lual_requiref(lua_State* L) {


    assert_ret(luaL_newmetatable(L, "lual_requiref"));
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, lual_requiref_func_lib, 0);
    luaL_newlib(L, lual_requiref_lib);

    return 1;
}

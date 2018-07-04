#include "skp_lua_lual_requiref.h"
#include "src/skp_common.h"
#include "src/skp_log.h"
#include <stdio.h>
#include <iostream>
#include "skp_lua_common.h"
#include <assert.h>

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class Clual_requiref
{
public:
    Clual_requiref() :
        m_add(0)
    {

    }

    int add(int a, int b)
    {
        m_add = a + b;
        return m_add;
    }
    int m_add;
};

struct Clual_requiref_userdata
{
    Clual_requiref *m_Clual_requiref;
};

static int lual_requiref_new(lua_State* L)
{
    log_print("c++ : lual_requiref_new");
    Clual_requiref_userdata *p = (Clual_requiref_userdata *)lua_newuserdata(L, sizeof(Clual_requiref_userdata));
    p->m_Clual_requiref = new Clual_requiref();
    luaL_getmetatable(L, "lual_requiref");
    lua_setmetatable(L, -2);
    return 1;
}

static int lual_requiref_add(lua_State* L) {
    log_print("c++ : lual_requiref_add");
    Clual_requiref_userdata *p = (Clual_requiref_userdata *)luaL_checkudata(L, 1, "lual_requiref");

    int a = luaL_checkinteger(L, 2);
    int b = luaL_checkinteger(L, 3);

    log_print("c++ : a = %d, b = %d", a, b);
    int c = p->m_Clual_requiref->add(a, b);
    log_print("c++ : c = %d", c);
    lua_pushinteger(L, c);

    return 1;
}

static int lual_requiref_to_string(lua_State* L) {
    log_print("c++ : lual_requiref_to_string");
    Clual_requiref_userdata *p = (Clual_requiref_userdata *)luaL_checkudata(L, 1, "lual_requiref");

    char msg[256] = "";
    snprintf(msg, sizeof(msg), "add = %d", p->m_Clual_requiref->m_add);
    log_print("c++ : %s", msg);
    lua_pushstring(L, msg);

    return 1;
}

static int lual_requiref_register(lua_State* L);

static luaL_Reg lual_requiref_lib[] = {
    { "new", lual_requiref_new },
    { "register", lual_requiref_register },
    { NULL, NULL },
};

static luaL_Reg lual_requiref_func_lib[] = {
    { "add", lual_requiref_add },
    { "__tostring", lual_requiref_to_string},
    { NULL, NULL },
};


int luaopen_lual_requiref(lua_State* L) {

    log_print("c++ : luaopen_lual_requiref");
    assert(luaL_newmetatable(L, "lual_requiref") == 1);

    lua_pushvalue(L, -1);

    lua_setfield(L, -2, "__index");

    luaL_setfuncs(L, lual_requiref_func_lib, 0);

    luaL_newlib(L, lual_requiref_lib);

    return 1;
}




/********************************************/





static int lual_requiref2_add(lua_State* L) {
    log_print("c++ : lual_requiref2_add");

    int a = luaL_checkinteger(L, -1);
    int b = luaL_checkinteger(L, -2);

    log_print("c++ : a = %d, b = %d", a, b);
    int c = a + b;
    log_print("c++ : c = %d", c);
    lua_pushinteger(L, c);

    return 1;
}


static int lual_requiref2(lua_State* L) {
    log_print("c++ : lual_requiref2");
    luaL_Reg l[] = {
        { "add", lual_requiref2_add },
        { NULL, NULL },
    };
    luaL_checkversion(L);
    luaL_newlib(L,l);

    return 1;
}

static int lual_requiref_register(lua_State* L) {
    log_print("c++ : lual_requiref_register");
    luaL_requiref(L, "lual_requiref2", lual_requiref2, 1);
    return 0;
}






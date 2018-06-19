#include "skp_lua.h"
#include "src/common.h"
#include <string>
#include "skp_lua_lual_requiref.h"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}


int lua_test_1_add(lua_State *L, int x,int y)
{
    int sum;
    /*the function name*/
    lua_getglobal(L,"add");
    /*the first argument*/
    lua_pushnumber(L,x);
    /*the second argument*/
    lua_pushnumber(L,y);
    /*call the function with 2 arguments, return 1 result.*/
    lua_call(L,2,1);
    /*get the result.*/
    sum = (int)lua_tonumber(L,-1);
    assert_ret(sum == x + y);
    /*cleanup the return*/
    lua_pop(L,1);

    return sum;
}

void lua_test_1()
{
    /* create state */
    lua_State *L = NULL;
    assert_ret((L =  luaL_newstate()) != NULL);
    /*load Lua base libraries*/
    luaL_openlibs(L);
    /*load the script*/
    assert_ret(luaL_dofile(L,"lua/add.lua") == 0);
    /*call the add function*/
    int sum = lua_test_1_add(L,10,15);
    /*print the result*/
    log_print("sum = %d", sum);
    /*cleanup Lua*/
    lua_close(L);
}


void lua_test_2()
{
    /* create state */
    lua_State *L = NULL;
    assert_ret((L =  luaL_newstate()) != NULL);
    /*load Lua base libraries*/
    luaL_openlibs(L);
    //执行内存脚本
    std::string str = "print (\"Hello world!\")";
    assert_ret(luaL_loadbuffer(L, str.c_str(), str.length(), "line") == 0);
    assert_ret(lua_pcall(L, 0, 0, 0) == 0);
    lua_close(L);
}

void lua_test_3()
{
    /* create state */
    lua_State *L = NULL;
    assert_ret((L =  luaL_newstate()) != NULL);
    /*load Lua base libraries*/
    luaL_openlibs(L);
    /*load the script*/
    assert_ret(luaL_dofile(L,"lua/lua_lib.lua") == 0);
    /*cleanup Lua*/
    lua_close(L);
}

void lua_test_4()
{
    /* create state */
    lua_State *L = NULL;
    assert_ret((L =  luaL_newstate()) != NULL);
    /*load Lua base libraries*/
    luaL_openlibs(L);

    //执行内存脚本
    std::string str =  "local lua_lib_test = require \"project_lua_lib_test\"" \
                        "local c = lua_lib_test.add(1,2)"\
                        "print(c)"\
                        "lua_lib_test.start()"\
                        "local lua_lib_test2 = require \"project_lua_lib_test2\""\
                        " local c = lua_lib_test2.add(1,2)"\
                        " print(c)";


    assert_ret(luaL_loadbuffer(L, str.c_str(), str.length(), "line") == 0);
    assert_ret(lua_pcall(L, 0, 0, 0) == 0);

    /*cleanup Lua*/
    lua_close(L);
}

void lua_test_5()
{
    /* create state */
    lua_State *L = NULL;
    assert_ret((L =  luaL_newstate()) != NULL);

//    luaopen_base(L);
//    luaopen_table(L);
//    luaopen_package(L);
//    luaopen_io(L);
//    luaopen_string(L);

    luaL_requiref(L, "lual_requiref", luaopen_lual_requiref, 1);

    /*load Lua base libraries*/
    luaL_openlibs(L);

    //执行内存脚本

    std::string str =   "local test = lual_requiref:new()" \
                        "local c = test:add(1, 3)" \
                        "print(c)" \
                        "print(test)";

    //@1
    //    assert_ret(luaL_loadbuffer(L, str.c_str(), str.length(), "line") == 0);
    //    assert_ret(lua_pcall(L, 0, 0, 0) == 0);

    //@2
    luaL_dostring(L, str.c_str());

    //@3
    //assert_ret(luaL_dofile(L,"lua/lual_requiref.lua") == 0);

    /*cleanup Lua*/
    lua_close(L);
}


void lua_test()
{
    func_run(lua_test_1());
    func_run(lua_test_2());
    func_run(lua_test_3());
    func_run(lua_test_4());
    func_run(lua_test_5());
}

#include "skp_lua.h"
#include "src/common.h"
#include <string>
#include "skp_lua_lual_requiref.h"
#include "skp_lua_common.h"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

LogFile logfile("../../../cpp_study/trunk/lua/lua.log");


void loadFile(const std::string &str, std::string &data)
{
    FILE *f = fopen(str.c_str(), "rb");
    while (!feof(f)) {
        char line[1024] = "";
        fgets(line, sizeof(line), f);
        data += line;
    }

    fclose(f);
}

static const std::string lua_config_path = "../../../cpp_study/trunk/lua/";

void skp_lua_base_loadbuffer(const std::string &str)
{
    /* create state */
    lua_State *L = NULL;
    assert_ret((L =  luaL_newstate()) != NULL);
    /*load Lua base libraries*/
    luaL_openlibs(L);
    //执行内存脚本
    //std::string str = "print (\"Hello world!\")";
    assert_ret(luaL_loadbuffer(L, str.c_str(), str.length(), "line") == 0);
    assert_ret(lua_pcall(L, 0, 0, 0) == 0);
    lua_close(L);
}

void skp_lua_base_dostring(const std::string &str)
{
    /* create state */
    lua_State *L = NULL;
    assert_ret((L =  luaL_newstate()) != NULL);
    /*load Lua base libraries*/
    luaL_openlibs(L);
    //执行内存脚本
    //std::string str = "print (\"Hello world!\")";
    luaL_dostring(L, str.c_str());
    lua_close(L);
}

void skp_lua_base_dofile(const std::string &str)
{
    /* create state */
    lua_State *L = NULL;
    assert_ret((L =  luaL_newstate()) != NULL);
    /*load Lua base libraries*/
    luaL_openlibs(L);
    /*load the script*/
    assert_ret(luaL_dofile(L,str.c_str()) == 0);
    /*cleanup Lua*/
    lua_close(L);
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
    std::string path = lua_config_path + "add.lua";
    assert_ret(luaL_dofile(L,path.c_str()) == 0);
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
    std::string path = lua_config_path + "lua_lib.lua";
    assert_ret(luaL_dofile(L, path.c_str()) == 0);
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
                        " print(c)"
                        ;


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

    LUA_TOP_PRINT;//0

    luaL_requiref(L, "lual_requiref", luaopen_lual_requiref, 1);

    LUA_TOP_PRINT;//1

    /*load Lua base libraries*/
    luaL_openlibs(L);

    //执行内存脚本

//    std::string str =   "local test = lual_requiref:new()" \
//                        "local c = test:add(1, 3)" \
//                        "print(c)" \
//                        "print(test)" \
//                        "lual_requiref:register()" \
//                        "local test2 = require \"lual_requiref2\""\
//                        "local d = test2:add(2, 4)" \
//                        "print(d)"
//                        ;

    std::string str =   "local test = lual_requiref:new()" \
                        "local c = test:add(1, 3)" \
                        "print(c)" \
                        "print(test)" \
                        "lual_requiref:register()" \
                        "local d = lual_requiref2:add(2, 4)" \
                        "print(d)"
                        ;



    const int branch = 2;

    if( 1 == branch)
    {
    //@1
        assert_ret(luaL_loadbuffer(L, str.c_str(), str.length(), "line") == 0);
        assert_ret(lua_pcall(L, 0, 0, 0) == 0);
    }
    else if( 2 == branch)
    {
    //@2
        luaL_dostring(L, str.c_str());
    }

    else
    {
    //@3
        std::string path = lua_config_path + "lual_requiref.lua";
        assert_ret(luaL_dofile(L, path.c_str()) == 0);
    }

    /*cleanup Lua*/
    lua_close(L);
}

void lua_table_test_1()
{
    std::string str =   "function setDefaultValues(t,d)  " \
                                "local mt = {__index = function() return d end} " \
                                "setmetatable(t, mt)  "\
                        " end  "\
                        " tab = {x=10,y=20}  "\
                        " print(tab.x ,tab.y,tab.z)"\
                        " setDefaultValues(tab,100)"\
                        " print(tab.z)"
                        ;
/*
    " print(tab.x ,tab.y,tab.z) --由于没有设置元方法则为nil"\
    " setDefaultValues(tab,100) --设置默认值（设置__index元方法）"\
    " print(tab.z) --检查到有__index的元方法则返回默认值" ;
*/



    func_run(skp_lua_base_loadbuffer(str));


    str =   "local mt = {  "
                "__newindex = function (table,key,value)  "
                "print(\"newindex call\")  "
            "end  "
            "}  "
            "local t = {} "
            "setmetatable(t, mt)  "
            "t[1] = 20  "
            "for k,v in pairs(t) do  "
                "print(k ,v)  "
            "end  "
            ;
    func_run(skp_lua_base_loadbuffer(str));


    str =   "local kk = {}"
            "local mt = {"
                "__newindex = kk"
            "}"
            "local t = {}"
            "setmetatable(t, mt)"
            "print(\"111\")"
            "for k,v in pairs(kk) do  "
                "print(k ,v)  "
            "end  "
            "t[1] = 20"
            "print(\"ttt:\")"
            "for k,v in pairs(t) do  "
                "print(k ,v)  "
            "end  "
            "print(\"kkk:\")"
            "for k,v in pairs(kk) do  "
                "print(k ,v)  "
            "end  "
            ;

    func_run(skp_lua_base_loadbuffer(str));

    str =   "local tb = {\"apple\", \"pear\", \"orange\", \"grape\"}"
            "for k,v in pairs(tb) do  "
                "print(k ,v)  "
            "end  "
            ;

    func_run(skp_lua_base_loadbuffer(str));


}

void lua_table_test_2()
{
    func_run(skp_lua_base_dofile(lua_config_path + "class1.lua"));

    func_run(skp_lua_base_dofile(lua_config_path + "class2.lua"));

    func_run(skp_lua_base_dofile(lua_config_path + "class3.lua"));
}

void lua_dostring_test()
{
    std::string data;
    func_run(loadFile(lua_config_path + "class2.lua", data));

    log_print("class2.lua : \n[\n%s]", data.c_str());
    func_run(skp_lua_base_dostring(data));

}

void lua_test()
{
    func_run(lua_test_1());
//    func_run(lua_test_2());
//    func_run(lua_test_3());
//    func_run(lua_test_4());
//    func_run(lua_test_5());
//    func_run(lua_table_test_1());
//    func_run(lua_table_test_2());
//    func_run(lua_dostring_test());
}

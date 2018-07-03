#include "skp_lua.h"
#include "src/common.h"
#include <string>
#include "skp_lua_lual_requiref.h"
#include "skp_lua_common.h"
#include "skp_lua_log.h"
#include "skp_lua_call.h"
#include "gtest/gtest.h"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

TEST(lua, loadbuffer)
{

    int32_t x = 10;
    int32_t y = 15;
    int32_t z = 0;
    TLuaBind bindIn[] =
    {
        {FIELD_INT32, &x},
        {FIELD_INT32, &y},
        {FIELD_END}
    };

    TLuaBind binOut[] =
    {
        {FIELD_INT32, &z},
        {FIELD_END}
    };

    std::string data;
    loadFile("func.lua", data);

    skp_lua_base_loadbuffer(data, "add", bindIn, binOut);
    EXPECT_EQ(x + y, z);
    log_print("%d + %d = %d", x, y, z);
}



TEST(lua, dostring)
{
    int32_t x = 10;
    int32_t y = 15;
    int32_t z = 0;
    TLuaBind bindIn[] =
    {
        {FIELD_INT32, &x},
        {FIELD_INT32, &y},
        {FIELD_END}
    };

    TLuaBind binOut[] =
    {
        {FIELD_INT32, &z},
        {FIELD_END}
    };

    std::string data;
    loadFile("func.lua", data);
    skp_lua_base_dostring(data, "add", bindIn, binOut);
    EXPECT_EQ(x + y, z);
    log_print("%d + %d = %d", x, y, z);
}

TEST(lua, dofile)
{
    int32_t x = 10;
    int32_t y = 15;
    int32_t z = 0;
    TLuaBind bindIn[] =
    {
        {FIELD_INT32, &x},
        {FIELD_INT32, &y},
        {FIELD_END}
    };

    TLuaBind binOut[] =
    {
        {FIELD_INT32, &z},
        {FIELD_END}
    };

    skp_lua_base_dofile("func.lua", "add", bindIn, binOut);
    EXPECT_EQ(x + y, z);
    log_print("%d + %d = %d", x, y, z);
}


TEST(lua, call)
{
    int8_t arg_int8 = 1;
    uint8_t arg_uint8 = 2;
    int16_t arg_int16 = 3;
    uint16_t arg_uint16 = 4;
    int32_t arg_int32 = 5;
    uint32_t arg_uint32 = 6;
    int64_t arg_int64 = 7;
    uint64_t arg_uint64 = 8;
    double arg_double = 9;
    char *arg_char = "12345";
    char arg_binary[] = "\0ab\0cde\0fg\0";

    TLuaBind bindIn[] =
    {
        {FIELD_INT8, &arg_int8},
        {FIELD_UINT8, &arg_uint8},
        {FIELD_INT16, &arg_int16},
        {FIELD_UINT16, &arg_uint16},
        {FIELD_INT32, &arg_int32},
        {FIELD_UINT32, &arg_uint32},
        {FIELD_INT64, &arg_int64},
        {FIELD_UINT64, &arg_uint64},
        {FIELD_DOUBLE, &arg_double},
        {FIELD_CHAR, arg_char},
        {FIELD_BINARY, arg_binary, sizeof(arg_binary)},
        {FIELD_END}
    };


    int8_t out_arg_int8 = 0;
    uint8_t out_arg_uint8 = 0;
    int16_t out_arg_int16 = 0;
    uint16_t out_arg_uint16 = 0;
    int32_t out_arg_int32 = 0;
    uint32_t out_arg_uint32 = 0;
    int64_t out_arg_int64 = 0;
    uint64_t out_arg_uint64 = 0;
    double out_arg_double = 0;
    char out_arg_char[128] = "";
    char out_arg_binary[128] = "";

    TLuaBind binOut[] =
    {
        {FIELD_INT8, &out_arg_int8},
        {FIELD_UINT8, &out_arg_uint8},
        {FIELD_INT16, &out_arg_int16},
        {FIELD_UINT16, &out_arg_uint16},
        {FIELD_INT32, &out_arg_int32},
        {FIELD_UINT32, &out_arg_uint32},
        {FIELD_INT64, &out_arg_int64},
        {FIELD_UINT64, &out_arg_uint64},
        {FIELD_DOUBLE, &out_arg_double},
        {FIELD_CHAR, out_arg_char, sizeof(out_arg_char)},
        {FIELD_BINARY, out_arg_binary, sizeof(out_arg_binary)},
        {FIELD_END}
    };

    skp_lua_base_dofile("func.lua", "more_arg", bindIn, binOut);

    assert(arg_int8 == out_arg_int8);
    assert(arg_uint8 == out_arg_uint8);
    assert(arg_int16 == out_arg_int16);
    assert(arg_uint16 == out_arg_uint16);
    assert(arg_int32 == out_arg_int32);
    assert(arg_uint32 == out_arg_uint32);
    assert(arg_int64 == out_arg_int64);
    assert(arg_uint64 == out_arg_uint64);
    assert(arg_double == out_arg_double);
    assert(strcmp(arg_char, out_arg_char) == 0);
    assert(sizeof(arg_binary) == binOut[10].size);
    assert(memcmp(arg_binary, out_arg_binary, sizeof(arg_binary)) == 0);

    char bufferBinary[1024] = "";
    log_print("%d %d %d %d %d %u, %lld, %llu, %lf, %s, %s", out_arg_int8, out_arg_uint8, out_arg_int16, out_arg_uint16, out_arg_int32, out_arg_uint32, out_arg_int64, out_arg_uint64, out_arg_double, out_arg_char, getBinary(bufferBinary, sizeof(bufferBinary), out_arg_binary, binOut[10].size));

}


TEST(lua, helloWorld)
{
    std::string str = "local lua_log = require(\"lua_log\")  lua_log.print (\"Hello world!\")";
    skp_lua_base_dostring(str);
}

TEST(lua, lib)
{
    skp_lua_base_dofile("lua_lib.lua");
}

TEST(lua, requiref)
{
    lua_State *L = NULL;
    assert_null(L =  luaL_newstate());

    //    luaopen_base(L);
    //    luaopen_table(L);
    //    luaopen_package(L);
    //    luaopen_io(L);
    //    luaopen_string(L);

    luaL_requiref(L, "lua_log", luaopen_lua_log, 1);
    luaL_requiref(L, "lual_requiref", luaopen_lual_requiref, 1);

    luaL_openlibs(L);
    std::string path = lua_config_path + "lual_requiref.lua";
    assert_func(luaL_dofile(L, path.c_str()));

    lua_close(L);
}

TEST(lua, table)
{
    std::string str =   "local lua_log = require(\"lua_log\") " \
                        "function setDefaultValues(t,d)  " \
                        "local mt = {__index = function() return d end} " \
                        "setmetatable(t, mt)  "\
                        " end  "\
                        " tab = {x=10,y=20}  "\
                        " lua_log.print(tab.x ,tab.y, tab.z)"\
                        " setDefaultValues(tab,100)"\
                        " lua_log.print(tab.z)"
            ;

    //    " print(tab.x ,tab.y,tab.z) --由于没有设置元方法则为nil"\
    //    " setDefaultValues(tab,100) --设置默认值（设置__index元方法）"\
    //    " print(tab.z) --检查到有__index的元方法则返回默认值" ;

    skp_lua_base_loadbuffer(str);




    str =   "local lua_log = require(\"lua_log\") " \
            "local mt = {  " \
            "__newindex = function (table,key,value)  "
            "lua_log.print(\"newindex call\")  "
            "end  "
            "}  "
            "local t = {} "
            "setmetatable(t, mt)  "
            "t[1] = 20  "
            "for k,v in pairs(t) do  "
            "lua_log.print(k ,v)  "
            "end  "
            ;
    skp_lua_base_loadbuffer(str);


    str =   "local lua_log = require(\"lua_log\") "
            "local kk = {}"
            "local mt = {"
            "__newindex = kk"
            "}"
            "local t = {}"
            "setmetatable(t, mt)"
            "lua_log.print(\"111\")"
            "for k,v in pairs(kk) do  "
            "lua_log.print(k ,v)  "
            "end  "
            "t[1] = 20"
            "lua_log.print(\"ttt:\")"
            "for k,v in pairs(t) do  "
            "lua_log.print(k ,v)  "
            "end  "
            "lua_log.print(\"kkk:\")"
            "for k,v in pairs(kk) do  "
            "lua_log.print(k ,v)  "
            "end  "
            ;

    skp_lua_base_loadbuffer(str);

    str =   "local lua_log = require(\"lua_log\") "
            "local tb = {\"apple\", \"pear\", \"orange\", \"grape\"}"
            "for k,v in pairs(tb) do  "
            "lua_log.print(k ,v)  "
            "end  "
            ;

    skp_lua_base_loadbuffer(str);
}

TEST(lua, class1)
{
    skp_lua_base_dofile("class1.lua");
}

TEST(lua, class2)
{
    skp_lua_base_dofile("class2.lua");
}


TEST(lua, class3)
{
    skp_lua_base_dofile("class3.lua");
}

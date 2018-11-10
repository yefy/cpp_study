#include "skp_lua_test.h"
#include "src/skp_common.h"
#include "src/skp_log.h"

#include "skp_lua_common.h"
#include "skp_lua_log.h"
#include "skp_lua_call.h"
#include "skp_lua_lual_requiref.h"

#include <vector>

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class CCalcTest: public testing::Test
{
protected:
    virtual void SetUp()
    {
        vec.push_back(1);
        vec.push_back(2);
    }
    virtual void TearDown()
    {
        vec.clear();
    }

    std::vector<int> vec;
};

SKP_TEST_F(CCalcTest, CCalcTest1)
{
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
}

SKP_TEST_F(CCalcTest, CCalcTest2)
{
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
}



class Clua : public testing::Test
{
protected:
    static void SetUpTestCase()
    {
        //L = NULL;

        L = luaL_newstate();
        ASSERT_TRUE(L);
        luaL_requiref(L, "lua_log", luaopen_lua_log, 1);
        luaL_requiref(L, "lual_requiref", luaopen_lual_requiref, 1);
        luaL_openlibs(L);

    }

    static void TearDownTestCase()
    {
        if(L)
        {
            lua_close(L);
            L = NULL;
        }
    }

    static lua_State *L;
};


lua_State *Clua::L = NULL;

SKP_TEST_F(Clua, lua_loadbuffer)
{
    START_INFO_TOP(lua_loadbuffer);

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
    ASSERT_FALSE(loadFile("func.lua", data));
    ASSERT_FALSE(skp_lua_base_loadbuffer(L, data, "add", bindIn, binOut));
    ASSERT_EQ(x + y , z) << "x + y == z";
}



SKP_TEST_F(Clua, lua_dostring)
{
    START_INFO_TOP(lua_dostring);

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
    ASSERT_FALSE(loadFile("func.lua", data));
    ASSERT_FALSE(skp_lua_base_dostring(L, data, "add", bindIn, binOut));
    ASSERT_EQ(x + y, z);
}

SKP_TEST_F(Clua, lua_dofile)
{
    START_INFO_TOP(lua_dofile);

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

    ASSERT_FALSE(skp_lua_base_dofile(L, "func.lua", "add", bindIn, binOut));
    ASSERT_EQ(x + y, z);
}


SKP_TEST_F(Clua, lua_call_test)
{
    START_INFO_TOP(lua_call_test);

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

    ASSERT_FALSE(skp_lua_base_dofile(L, "func.lua", "more_arg", bindIn, binOut));

    ASSERT_EQ(arg_int8 , out_arg_int8);
    ASSERT_EQ(arg_uint8 , out_arg_uint8);
    ASSERT_EQ(arg_int16 , out_arg_int16);
    ASSERT_EQ(arg_uint16 , out_arg_uint16);
    ASSERT_EQ(arg_int32 , out_arg_int32);
    ASSERT_EQ(arg_uint32 , out_arg_uint32);
    ASSERT_EQ(arg_int64 , out_arg_int64);
    ASSERT_EQ(arg_uint64 , out_arg_uint64);
    ASSERT_EQ(arg_double , out_arg_double);
    ASSERT_STREQ(arg_char, out_arg_char);
    ASSERT_EQ(sizeof(arg_binary) , binOut[10].size);
    ASSERT_TRUE(memcmp(arg_binary, out_arg_binary, sizeof(arg_binary)) == 0);

    char bufferBinary[1024] = "";
    log_print("%d %d %d %d %d %u, %lld, %llu, %lf, %s, %s", out_arg_int8, out_arg_uint8, out_arg_int16,
              out_arg_uint16, out_arg_int32, out_arg_uint32, out_arg_int64, out_arg_uint64, out_arg_double, out_arg_char,
              binaryToStr(bufferBinary, sizeof(bufferBinary), out_arg_binary, binOut[10].size));

}


SKP_TEST_F(Clua, lua_helloWorld)
{
    START_INFO_TOP(lua_helloWorld);

    std::string str = "local lua_log = require(\"lua_log\")  lua_log.print (\"Hello world!\")";
    ASSERT_FALSE(skp_lua_base_dostring(L, str));
}

SKP_TEST_F(Clua, lua_lib)
{
    START_INFO_TOP(lua_lib);

    ASSERT_FALSE(skp_lua_base_dofile(L, "lua_lib.lua"));
}

SKP_TEST_F(Clua, lua_requiref)
{
    START_INFO_TOP(lua_requiref);

    ASSERT_FALSE(skp_lua_base_dofile(L, "lua_lib.lua"));

    /*
    lua_State *L = NULL;
    ASSERT_TRUE(L =  luaL_newstate());

    //    luaopen_base(L);
    //    luaopen_table(L);
    //    luaopen_package(L);
    //    luaopen_io(L);
    //    luaopen_string(L);

    luaL_requiref(L, "lua_log", luaopen_lua_log, 1);
    luaL_requiref(L, "lual_requiref", luaopen_lual_requiref, 1);

    luaL_openlibs(L);
    std::string path = lua_config_path + "lual_requiref.lua";
    ASSERT_FALSE(luaL_dofile(L, path.c_str()));

    lua_close(L);
    */
}

SKP_TEST_F(Clua, lua_table)
{
    START_INFO_TOP(lua_table);

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

    ASSERT_FALSE(skp_lua_base_loadbuffer(L, str));




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
    ASSERT_FALSE(skp_lua_base_loadbuffer(L, str));


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

    ASSERT_FALSE(skp_lua_base_loadbuffer(L, str));

    str =   "local lua_log = require(\"lua_log\") "
            "local tb = {\"apple\", \"pear\", \"orange\", \"grape\"}"
            "for k,v in pairs(tb) do  "
            "lua_log.print(k ,v)  "
            "end  "
            ;

    ASSERT_FALSE(skp_lua_base_loadbuffer(L, str));
}

SKP_TEST_ONECE_F(Clua, lua_class1)
{
    START_INFO_TOP(lua_class1);

    ASSERT_FALSE(skp_lua_base_dofile(L, "class1.lua"));
}

SKP_TEST_ONECE_F(Clua, lua_class2)
{
    START_INFO_TOP(lua_class2);

    ASSERT_FALSE(skp_lua_base_dofile(L, "class2.lua"));
}


SKP_TEST_F(Clua, lua_class3)
{
    START_INFO_TOP(lua_class3);

    ASSERT_FALSE(skp_lua_base_dofile(L, "class3.lua"));
}


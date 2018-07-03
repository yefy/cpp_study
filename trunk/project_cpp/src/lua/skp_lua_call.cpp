#include "skp_lua_call.h"
#include <stdarg.h>
#include "src/common.h"
#include "skp_lua_log.h"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

char FieldTypeName[100][100] =
{
    "FIELD_END",
    "FIELD_INT8",
    "FIELD_UINT8",
    "FIELD_INT16",
    "FIELD_UINT16",
    "FIELD_INT32",
    "FIELD_UINT32",
    "FIELD_INT64",
    "FIELD_UINT64",
    "FIELD_DOUBLE",
    "FIELD_CHAR",
    "FIELD_BINARY"
};

int32_t FieldTypeSize[] =
{
    0,
    sizeof(int8_t),
    sizeof(uint8_t),
    sizeof(int16_t),
    sizeof(uint16_t),
    sizeof(int32_t),
    sizeof(uint32_t),
    sizeof(int64_t),
    sizeof(uint64_t),
    sizeof(double),
    0,
    0,
};




int32_t skp_lua_bindIn(lua_State *L, TLuaBind *binds, int32_t &size)
{
    log_print("*******star skp_lua_bindIn***********");
    size = 0;
    if(!binds)
    {
        log_print("bindIn size = [0]");
        log_print("*******end skp_lua_bindIn***********");
        return 0;
    }

    int32_t i = 0;

    for(; binds[i].type != 0; ++i)
    {
        const TLuaBind &bind = binds[i];
        if(0 == bind.dataAddr)
        {
            log_print("error index[%d], name[%s] type[%d], size[%d], 0 == bind.dataAddr",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
            return -1;
        }

        switch(bind.type)
        {

        case FIELD_END:
        {
            break;
        }
        case FIELD_INT8:
        {
            log_print("index[%d], name[%s] type[%d], size[%d], data[%d]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(int8_t *)bind.dataAddr);
            lua_pushinteger(L, *(int8_t *)bind.dataAddr);
            break;
        }
        case FIELD_UINT8:
        {
            log_print("index[%d], name[%s] type[%d], size[%d], data[%d]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(uint8_t *)bind.dataAddr);
            lua_pushinteger(L, *(uint8_t *)bind.dataAddr);
            break;
        }
        case FIELD_INT16:
        {
            log_print("index[%d], name[%s] type[%d], size[%d], data[%d]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(int16_t *)bind.dataAddr);
            lua_pushinteger(L, *(int16_t *)bind.dataAddr);
            break;
        }
        case FIELD_UINT16:
        {
            log_print("index[%d], name[%s] type[%d], size[%d], data[%d]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(uint16_t *)bind.dataAddr);
            lua_pushinteger(L, *(uint16_t *)bind.dataAddr);
            break;
        }
        case FIELD_INT32:
        {
            log_print("index[%d], name[%s] type[%d], size[%d], data[%d]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(int32_t *)bind.dataAddr);
            lua_pushinteger(L, *(int32_t *)bind.dataAddr);
            break;
        }
        case FIELD_UINT32:
        {
            log_print("index[%d], name[%s] type[%d], size[%d], data[%u]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(uint32_t *)bind.dataAddr);
            lua_pushunsigned(L, *(uint32_t *)bind.dataAddr);
            break;
        }
        case FIELD_INT64:
        {
            log_print("index[%d], name[%s] type[%d], size[%d], data[%lld]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(int64_t *)bind.dataAddr);
            lua_pushnumber(L, *(int64_t *)bind.dataAddr);
            break;
        }
        case FIELD_UINT64:
        {
            log_print("index[%d], name[%s] type[%d], size[%d], data[%llu]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(uint64_t *)bind.dataAddr);
            lua_pushnumber(L, *(uint64_t *)bind.dataAddr);
            break;
        }
        case FIELD_DOUBLE:
        {
            log_print("index[%d], name[%s] type[%d], size[%d], data[%lf]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(double *)bind.dataAddr);
            lua_pushnumber(L, *(double *)bind.dataAddr);
            break;
        }
        case FIELD_CHAR:
        {
            log_print("index[%d], name[%s] type[%d], size[%d], data[%s]",
                i + 1, FieldTypeName[bind.type], bind.type, strlen((char *)bind.dataAddr), (char *)bind.dataAddr);
            lua_pushstring(L, (char *)bind.dataAddr);

            break;
        }
        case FIELD_BINARY:
        {
            char bufferBinary[1024] = "";
            log_print("index[%d], name[%s] type[%d], size[%d], data[%s]",
                i + 1, FieldTypeName[bind.type], bind.type, bind.size, getBinary(bufferBinary, sizeof(bufferBinary), (char *)bind.dataAddr, bind.size));

            lua_pushlstring(L, (char *)bind.dataAddr,  bind.size);
            break;
        }

        default:
        {
            log_print("index[%d], 类型不匹配", i + 1);
            return -1;
        }
        }
    }


    size = i;
    log_print("bindIn size = [%d]", size);
    log_print("*******end skp_lua_bindIn***********");

    return 0;
}

int32_t skp_lua_bindOut(lua_State *L, TLuaBind *binds, int32_t size)
{
    log_print("*******start skp_lua_bindOut***********");
    if(!binds)
    {
        log_print("bindOut size = [0]");
        log_print("*******end skp_lua_bindOut***********");
        return 0;
    }

    int top = lua_gettop(L);

    if(size > top)
    {
        log_print("size= %d > top = %d", size, top);
        return -1;
    }

    for(int32_t i = 0; i < size; ++i)
    {
        int32_t luaIndex = -(size - i);
        log_print("luaIndex = %d", luaIndex);
        TLuaBind &bind = binds[i];
        if(0 == bind.dataAddr)
        {
            log_print("error index[%d], name[%s] type[%d], size[%d], 0 == bind.dataAddr",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
            return -1;
        }

        switch(bind.type)
        {
        case FIELD_END:
        {
            break;
        }
        case FIELD_INT8:
        {
            if(!lua_isnumber(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }
            int8_t data = lua_tointeger(L, luaIndex);
            *(int8_t *)bind.dataAddr = data;
            log_print("index[%d], name[%s] type[%d], size[%d], data[%d]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(int8_t *)bind.dataAddr);
            break;
        }
        case FIELD_UINT8:
        {
            if(!lua_isnumber(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }
            uint8_t data = lua_tointeger(L, luaIndex);
            *(uint8_t *)bind.dataAddr = data;
            log_print("index[%d], name[%s] type[%d], size[%d], data[%d]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(uint8_t *)bind.dataAddr);
            break;
        }
        case FIELD_INT16:
        {
            if(!lua_isnumber(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }
            int16_t data = lua_tointeger(L, luaIndex);
            *(int16_t *)bind.dataAddr = data;
            log_print("index[%d], name[%s] type[%d], size[%d], data[%d]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(int16_t *)bind.dataAddr);
            break;
        }
        case FIELD_UINT16:
        {
            if(!lua_isnumber(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }
            uint16_t data = lua_tointeger(L, luaIndex);
            *(uint16_t *)bind.dataAddr = data;
            log_print("index[%d], name[%s] type[%d], size[%d], data[%d]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(uint16_t *)bind.dataAddr);
            break;
        }
        case FIELD_INT32:
        {
            if(!lua_isnumber(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }
            int32_t data = lua_tointeger(L, luaIndex);
            *(int32_t *)bind.dataAddr = data;
            log_print("index[%d], name[%s] type[%d], size[%d], data[%d]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(int32_t *)bind.dataAddr);
            break;
        }
        case FIELD_UINT32:
        {
            if(!lua_isnumber(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }
            uint32_t data = lua_tounsigned(L, luaIndex);
            *(uint32_t *)bind.dataAddr = data;
            log_print("index[%d], name[%s] type[%d], size[%d], data[%u]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(uint32_t *)bind.dataAddr);
            break;
        }
        case FIELD_INT64:
        {
            if(!lua_isnumber(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }
            int64_t data = lua_tonumber(L, luaIndex);
            *(int64_t *)bind.dataAddr = data;
            log_print("index[%d], name[%s] type[%d], size[%d], data[%lld]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(int64_t *)bind.dataAddr);
            break;
        }
        case FIELD_UINT64:
        {
            if(!lua_isnumber(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }
            uint64_t data = lua_tonumber(L, luaIndex);
            *(uint64_t *)bind.dataAddr = data;
            log_print("index[%d], name[%s] type[%d], size[%d], data[%llu]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(uint64_t *)bind.dataAddr);
            break;
        }
        case FIELD_DOUBLE:
        {
            if(!lua_isnumber(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }
            double data = lua_tonumber(L, luaIndex);
            *(double *)bind.dataAddr = data;
            log_print("index[%d], name[%s] type[%d], size[%d], data[%lf]",
                i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type], *(double *)bind.dataAddr);
            break;
        }
        case FIELD_CHAR:
        {
            if(!lua_isstring(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }
            if(bind.size > 0)
            {
                const char *data = lua_tostring(L, luaIndex);
                memset(bind.dataAddr, 0x00, bind.size);
                strncpy((char *)bind.dataAddr, data, bind.size - 1);
                int len = strlen(data);
                if(len > bind.size)
                {
                    log_print("len = %d > bind.size = %d", len, bind.size);
                }
            }
            else
            {
                log_print("bind.size <= 0");
            }

            log_print("index[%d], name[%s] type[%d], size[%d], data[%s]",
                i + 1, FieldTypeName[bind.type], bind.type, strlen((char *)bind.dataAddr), (char *)bind.dataAddr);

            break;
        }
        case FIELD_BINARY:
        {
            if(!lua_isstring(L, luaIndex))
            {
                log_print("error index[%d], name[%s] type[%d], size[%d]",
                    i + 1, FieldTypeName[bind.type], bind.type, FieldTypeSize[bind.type]);
                return -1;
            }

            size_t len = 0;
            const char *data = lua_tolstring(L, luaIndex, &len);
            int32_t minSize = std::min(len, (size_t)bind.size);
            log_print("len = %d, bind.size = %d, minSize = %d", len, bind.size, minSize);

            memset(bind.dataAddr, 0x00, bind.size);
            memcpy((char *)bind.dataAddr, data, minSize);
            bind.size = minSize;

            char bufferBinary[1024] = "";
            log_print("index[%d], name[%s] type[%d], size[%d], data[%s]",
                i + 1, FieldTypeName[bind.type], bind.type, bind.size, getBinary(bufferBinary, sizeof(bufferBinary), (char *)bind.dataAddr, bind.size));

            break;
        }

        default:
        {
            log_print("index[%d], 类型不匹配", i + 1);
            return -1;
        }
        }
    }
    lua_pop(L, size);

    log_print("bindOut size = [%d]", size);
    log_print("*******end skp_lua_bindOut***********");
    return 0;
}



int32_t skp_lua_call(lua_State *L, const char * func, TLuaBind *bindIn, TLuaBind *binOut)
{
    int32_t sizeBindIn = 0;
    int32_t sizeBindOut = 0;
    lua_getglobal(L, func);//函数入栈


    assert_func(skp_lua_bindIn(L, bindIn, sizeBindIn));

    for(int32_t i = 0; binOut[i].type != 0; ++i)
    {
        ++sizeBindOut;
    }
    //调用Lua函数
    assert_func(lua_pcall(L,sizeBindIn,sizeBindOut,0));

    assert_func(skp_lua_bindOut(L, binOut, sizeBindOut));

    return 0;
}

void skp_lua_base_loadbuffer(const std::string &str, const char * func, TLuaBind *bindIn, TLuaBind *binOut)
{
    /* create state */
    lua_State *L = NULL;
    assert_null(L =  luaL_newstate());
    luaL_requiref(L, "lua_log", luaopen_lua_log, 1);
    /*load Lua base libraries*/
    luaL_openlibs(L);
    //执行内存脚本
    assert_func(luaL_loadbuffer(L, str.c_str(), str.length(), "line"));
    assert_func(lua_pcall(L, 0, 0, 0));
    if(func)
    {
        assert_func(skp_lua_call(L, func, bindIn, binOut));
    }
    lua_close(L);
}

void skp_lua_base_dostring(const std::string &str, const char * func, TLuaBind *bindIn, TLuaBind *binOut)
{
    /* create state */
    lua_State *L = NULL;
    assert_null(L =  luaL_newstate());
    luaL_requiref(L, "lua_log", luaopen_lua_log, 1);
    /*load Lua base libraries*/
    luaL_openlibs(L);
    //执行内存脚本
    luaL_dostring(L, str.c_str());
    if(func)
    {
        assert_func(skp_lua_call(L, func, bindIn, binOut));
    }
    lua_close(L);
}

void skp_lua_base_dofile(const std::string &name, const char * func, TLuaBind *bindIn, TLuaBind *binOut)
{
    std::string full_path = lua_config_path + name;

    /* create state */
    lua_State *L = NULL;
    assert_null(L =  luaL_newstate());
    luaL_requiref(L, "lua_log", luaopen_lua_log, 1);
    /*load Lua base libraries*/
    luaL_openlibs(L);
    /*load the script*/
    assert_func(luaL_dofile(L,full_path.c_str()));
    if(func)
    {
        assert_func(skp_lua_call(L, func, bindIn, binOut));
    }
    /*cleanup Lua*/
    lua_close(L);
}

void loadFile(const std::string &name, std::string &data)
{
    std::string full_path = lua_config_path + name;

    FILE *f = fopen(full_path.c_str(), "rb");
    assert_null(f);
    while (!feof(f)) {
        char line[1024] = "";
        fgets(line, sizeof(line), f);
        data += line;
    }

    fclose(f);
}

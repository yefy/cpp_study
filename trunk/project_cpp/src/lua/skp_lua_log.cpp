#include "skp_lua_log.h"
#include "src/common.h"
#include <stdio.h>
#include <iostream>
#include "skp_lua_common.h"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

bool isDouble(const char *str)
{
    int size = strlen(str);
    for(int i = 0; i < size; ++i)
    {
        if(str[i] == '.')
            return true;
    }
    return false;
}

static int lua_log_print(lua_State* L) {

    char buffer[2048] = "";
    int bufferIndex = 0;

    int top = lua_gettop(L);
    //printf("top = %d \n", top);
    for(int i = top - 1; i >= 0; --i)
    {
        int index = 0 - i - 1;
        //printf("index = %d \n", index);
        //lua_isnumber(L, index);

        if(lua_isstring(L, index))
        {
            const char *str = NULL;
            size_t size = 0;
            char lstr[1024] = "";
            if((str = luaL_checklstring(L, index, &size)) != NULL)
            {
                bool islStr = false;
                memcpy(lstr, str, size);
                for(int k = 0; k < size; ++k)
                {
                    if('\0' == lstr[k])
                    {
                        lstr[k] = '~';
                        islStr = true;
                    }
                }
                str = lstr;
                if(islStr)
                    log_print("FIELD_BINARY size = %d, lstr = %s", size, str);
            }
            else
            {
                str = luaL_checkstring(L, index);
            }
            bufferIndex += snprintf(&buffer[bufferIndex], sizeof(buffer) - bufferIndex, "%s ", str);
            //printf("lua_isstring = %s \n", str);
        }
        else if(lua_isnumber(L, index))
        {
            int64_t number = luaL_checkinteger(L, index);
            bufferIndex += snprintf(&buffer[bufferIndex], sizeof(buffer) - bufferIndex, "%lld ", number);
            //printf("lua_isnumber = %lld\n", number);
            //printf("buffer = %s \n", buffer);
        }
        else if(lua_isnil(L, index))
        {
            bufferIndex += snprintf(&buffer[bufferIndex], sizeof(buffer) - bufferIndex, "%s ", "nil");
            //printf("lua_isnil \n");
            //printf("buffer = %s \n", buffer);
        }
        else if(lua_isboolean(L, index))
        {
            int64_t number = lua_toboolean(L, index);
            bufferIndex += snprintf(&buffer[bufferIndex], sizeof(buffer) - bufferIndex, "%s ", number?"true":"false");
            //printf("lua_isboolean = %s \n", number?"true":"false");
            //printf("buffer = %s \n", buffer);
        }
        else
        {
            bufferIndex += snprintf(&buffer[bufferIndex], sizeof(buffer) - bufferIndex, "%s ", "NULL");
            //printf("NULL \n");
            //printf("buffer = %s \n", buffer);
        }
    }

    //printf("buffer = %s \n", buffer);
    log_print(buffer);

    return 1;
}


int luaopen_lua_log(lua_State* L) {
    luaL_Reg l[] = {
        { "print", lua_log_print },
        { NULL, NULL },
    };
    luaL_checkversion(L);
    luaL_newlib(L,l);

    return 1;
}






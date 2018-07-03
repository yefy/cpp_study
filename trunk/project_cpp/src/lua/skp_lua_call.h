#ifndef SKP_LUA_CALL_H
#define SKP_LUA_CALL_H

#include <stdint.h>
#include <string>

typedef struct lua_State lua_State;

//数据字段类型，用于绑定
typedef enum _FIELD_TYPE_
{
    FIELD_END = 0x00
    ,FIELD_INT8 =0x01
    ,FIELD_UINT8 = 0x02
    ,FIELD_INT16 = 0x03
    ,FIELD_UINT16 = 0x04
    ,FIELD_INT32 = 0x05
    ,FIELD_UINT32 = 0x06
    ,FIELD_INT64 = 0x07
    ,FIELD_UINT64 = 0x08
    ,FIELD_DOUBLE = 0x09
    ,FIELD_CHAR = 0x0A
    ,FIELD_BINARY = 0x0B
}FieldType;

struct TLuaBind
{
    FieldType      type;
    void            *dataAddr;
    int32_t         size;
};

int32_t skp_lua_call(lua_State *L, const char * func, TLuaBind *bindIn, TLuaBind *binOut);
void skp_lua_base_loadbuffer(const std::string &str, const char * func = NULL, TLuaBind *bindIn = NULL, TLuaBind *binOut = NULL);
void skp_lua_base_dostring(const std::string &str, const char * func = NULL, TLuaBind *bindIn = NULL, TLuaBind *binOut = NULL);
void skp_lua_base_dofile(const std::string &name, const char * func = NULL, TLuaBind *bindIn = NULL, TLuaBind *binOut = NULL);
void loadFile(const std::string &name, std::string &data);


static const std::string lua_config_path = "../../../cpp_study/trunk/lua/src/test/";

#endif // SKP_LUA_CALL_H

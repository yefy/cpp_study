#ifndef SKP_LUA_LOG_H
#define SKP_LUA_LOG_H

#define LIB_API

#ifdef __cplusplus
extern "C" {
#endif
#include "lauxlib.h"

LIB_API int luaopen_lua_log(lua_State *L);

#ifdef __cplusplus
}
#endif

#endif // SKP_LUA_LOG_H

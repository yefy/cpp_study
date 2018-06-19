#ifndef SKP_LUA_LUAL_REQUIREF_H
#define SKP_LUA_LUAL_REQUIREF_H

#define LIB_API

#ifdef __cplusplus
extern "C" {
#endif
#include "lauxlib.h"

LIB_API int luaopen_lual_requiref(lua_State *L);

#ifdef __cplusplus
}
#endif

#endif // SKP_LUA_LUAL_REQUIREF_H

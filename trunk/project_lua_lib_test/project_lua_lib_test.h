#ifndef PROJECT_LUA_LIB_TEST_H
#define PROJECT_LUA_LIB_TEST_H

//#define _LIB_EXPORT_

//#ifdef _LIB_EXPORT_
//#define LIB_API __declspec(dllexport)
//#else
//#define LIB_API __declspec(dllimport)
//#endif

#define LIB_API

#ifdef __cplusplus
extern "C" {
#endif
#include "lauxlib.h"

LIB_API int luaopen_project_lua_lib_test(lua_State *L);

#ifdef __cplusplus
}
#endif


#endif // PROJECT_LUA_LIB_TEST_H

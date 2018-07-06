#ifndef SKP_LUA_TEST_H
#define SKP_LUA_TEST_H

#include "gtest/gtest.h"
#include "src/skp_log.h"



class LuaEnvironment : public testing::Environment
 {
 public:
     virtual void SetUp()
     {
         log_print("LuaEnvironment SetUP");
     }
     virtual void TearDown()
     {
         log_print("LuaEnvironment TearDown");
     }
 };


#endif // SKP_LUA_TEST_H

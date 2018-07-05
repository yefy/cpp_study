#ifndef SKP_LUA_H
#define SKP_LUA_H

#include "gtest/gtest.h"



class LuaEnvironment : public testing::Environment
 {
 public:
     virtual void SetUp()
     {
         std::cout << "LuaEnvironment SetUP" << std::endl;
     }
     virtual void TearDown()
     {
         std::cout << "LuaEnvironment TearDown" << std::endl;
     }
 };


#endif // SKP_LUA_H

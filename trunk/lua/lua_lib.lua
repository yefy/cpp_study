local lua_lib_test = require "project_lua_lib_test"

local c = lua_lib_test.add(1,2)
print(c)
 
lua_lib_test.start()
 
local lua_lib_test2 = require "project_lua_lib_test2"
 
local c = lua_lib_test2.add(1,2)
print(c)
local lua_log = require("lua_log")
local test = lual_requiref:new()
local c = test:add(1, 3)

lua_log.print(c)
lua_log.print(string.format("%s", test))

lual_requiref:register()
local test2 = require "lual_requiref2"
local d = test2:add(2, 4)
lua_log.print(d)

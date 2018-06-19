local test = lual_requiref:new()
local c = test:add(1, 3)
print(c)
print(test)
lual_requiref:register()
local test2 = require "lual_requiref2"
local d = test2:add(2, 4)
print(d)
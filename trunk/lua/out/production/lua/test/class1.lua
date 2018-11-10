local lua_log = require("lua_log")

local Object = {class_id = 0}

function Object:new(o)
    o = o or {}
    setmetatable(o,self) -- 对象o调用不存在的成员时都会去self中查找，而这里的self指的就是Object
    self.__index = self
    return o
end

function Object:add()
    self.class_id = self.class_id + 1;
end

function Object:clone()
    return self;
end


---以下我们创建对象来测试以下
local o1 = Object:new()
o1.class_id = 11;

local o2 = Object:new()
o2.class_id = 22;

lua_log.print(Object.class_id);
lua_log.print(o1.class_id);
lua_log.print(o2.class_id);

Object:add()
lua_log.print(Object.class_id);
lua_log.print(o1.class_id);
lua_log.print(o2.class_id);


o1:add()
lua_log.print(Object.class_id);
lua_log.print(o1.class_id);
lua_log.print(o2.class_id);

Object:add()
lua_log.print(Object.class_id);
lua_log.print(o1.class_id);
lua_log.print(o2.class_id);


local object_clone = Object:clone()
lua_log.print(object_clone.class_id);
lua_log.print(Object.class_id);
lua_log.print(o1.class_id);
lua_log.print(o2.class_id);


object_clone:add()
lua_log.print(object_clone.class_id);
lua_log.print(Object.class_id);
lua_log.print(o1.class_id);
lua_log.print(o2.class_id);


--==========================================================================
lua_log.print(string.rep("=",30))

local mymetatable = {class_id = 1}
mytable = setmetatable({key1 = "value1"}, { __newindex = mymetatable })

lua_log.print(mytable.key1)

mytable.newkey = "新值2"
lua_log.print(mytable.newkey,mymetatable.newkey)

mytable.key1 = "新值1"
lua_log.print(mytable.key1,mymetatable.key1)

lua_log.print("mymetatable", mymetatable.class_id)
lua_log.print("mytable", mytable.class_id)


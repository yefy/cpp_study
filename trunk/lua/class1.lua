local lua_log = require("lua_log")

local Object = {class_id = 0}

function Object:new(o)
    o = o or {}
    setmetatable(o,self) -- ����o���ò����ڵĳ�Աʱ����ȥself�в��ң��������selfָ�ľ���Object
    self.__index = self
    return o
end

function Object:add()
    self.class_id = self.class_id + 1;
end

function Object:clone()
    return self;
end


---�������Ǵ�����������������
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

mytable.newkey = "��ֵ2"
lua_log.print(mytable.newkey,mymetatable.newkey)

mytable.key1 = "��ֵ1"
lua_log.print(mytable.key1,mymetatable.key1)

lua_log.print("mymetatable", mymetatable.class_id)
lua_log.print("mytable", mytable.class_id)


Object = {class_id = 0}

print(string.rep("*",30))
print(Object);
print(string.rep("*",30))

function Object:new(o)
    o = o or {}

    print(self);
    print(o);
    print(string.rep("*",30))

    setmetatable(o,self) -- 对象o调用不存在的成员时都会去self中查找，而这里的self指的就是Object
    self.__index = self
    return o
end

function Object:add()
    self.class_id = self.class_id + 1;
    print(self);
    print(string.rep("*",30))
end

function Object:clone()
    print(self);
    print(string.rep("*",30))
    return self;
end


---以下我们创建对象来测试以下
local o1 = Object:new()
print(o1);
print(string.rep("*",30))

o1.class_id = 11;

local o2 = Object:new()
print(o2);
print(string.rep("*",30))

o2.class_id = 22;

print(Object.class_id);
print(o1.class_id);
print(Object.class_id);
print(o2.class_id);
print(Object.class_id);
print(string.rep("*",30))

Object:add()
print(Object.class_id);
print(string.rep("*",30))
Object:add()
print(Object.class_id);
print(string.rep("*",30))


o1:add()
print(o1.class_id);
print(string.rep("*",30))
o1:add()
print(o1.class_id);
print(string.rep("*",30))

Object:add()
print(Object.class_id);
print(string.rep("*",30))


local object_clone = Object:clone()
print(object_clone);
print(string.rep("*",30))


object_clone:add()
print(object_clone.class_id);
print(string.rep("*",30))

Object:add()
print(Object.class_id);
print(string.rep("*",30))

--==========================================================================
print(string.rep("=",30))

mymetatable = {class_id = 1}
mytable = setmetatable({key1 = "value1"}, { __newindex = mymetatable })

print(mytable.key1)

mytable.newkey = "新值2"
print(mytable.newkey,mymetatable.newkey)

mytable.key1 = "新值1"
print(mytable.key1,mymetatable.key1)

print("mymetatable", mymetatable.class_id)
print("mytable", mytable.class_id)


--==========================================================================
print(string.rep("=",30))

mymetatable = {class_id = 1}

--mytable = setmetatable({key1 = "value1"}, { __index = mymetatable })


local basetable = {};
setmetatable(basetable, mymetatable)
mymetatable.__index = mymetatable
mytable = setmetatable({key1 = "value1"}, basetable)
basetable.__index = basetable


--mytable = setmetatable({key1 = "value1"}, mymetatable)
--mymetatable.__index = mymetatable

print("mymetatable.class_id", mymetatable.class_id)

print("mytable.key1", mytable.key1)
print("mytable.key2", mytable.key2)
print("mytable.class_id", mytable.class_id)
mytable.class_id = 11
print("mytable.class_id", mytable.class_id)

local mymetatable2 = getmetatable(mytable)
print("mymetatable2.class_id", mymetatable2.class_id)

mytable.class_id = nil
print("mytable.class_id", mytable.class_id)


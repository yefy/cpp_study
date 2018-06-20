--[[
Object = {class_id = 0}

function Object:new(o)
    self.class_id = 1
end

function Object:add()
    self.class_id = self.class_id + 1
end


function Object_new()
    return Object
end

local ob = Object_new()
print("ob.class_id", ob.class_id);

ob:new()
print("ob.class_id", ob.class_id);

ob:add()
print("ob.class_id", ob.class_id);
--]]




function Object1_new()
    local Ob1 = {o1 = 10}

    function Ob1:add1()
        self.o1 = self.o1 + 1
    end

    return Ob1
end


function Object2_new()
    local ob1 = Object1_new()

    local Ob2 = {o2 = 20}

    function Ob2:add2()
        self.o2 = self.o2 + 1
    end

    setmetatable(Ob2,ob1)
    ob1.__index = ob1
    --ob1.__newindex = ob1


    return Ob2
end

print(string.rep("*",30), "Object1_new()", string.rep("*",30))

local obj1 = Object1_new()
print("obj1.o1", obj1.o1);
print(string.rep("*",30), "obj1:add1()", string.rep("*",30))
obj1:add1()
print("obj1.o1", obj1.o1);

print(string.rep("*",30), "Object2_new()", string.rep("*",30))

local obj2 = Object2_new()
print("obj2.o1", obj2.o1);
print("obj2.o2", obj2.o2);

print(string.rep("*",30), "obj2:add1()", string.rep("*",30))
obj2:add1()
--obj2.o1 = obj2.o1 + 1
print("obj2.o1", obj2.o1);
print("obj2.o2", obj2.o2);

print(string.rep("*",30), "obj2.o1 = nil", string.rep("*",30))

obj2.o1 = nil
print("obj2.o1", obj2.o1);
print("obj2.o2", obj2.o2);

print(string.rep("*",30), "obj2:add2()", string.rep("*",30))

obj2:add2()
print("obj2.o1", obj2.o1);
print("obj2.o2", obj2.o2);




print(string.rep("*",30), "Object2_new()", string.rep("*",30))

local obj22 = Object2_new()
print("obj22.o1", obj22.o1);
print("obj22.o2", obj22.o2);

print(string.rep("*",30), "obj22:add1()", string.rep("*",30))
obj22:add1()
--obj22.o1 = obj22.o1 + 1
print("obj22.o1", obj22.o1);
print("obj22.o2", obj22.o2);

print(string.rep("*",30), "obj22.o1 = nil", string.rep("*",30))

obj22.o1 = nil
print("obj22.o1", obj22.o1);
print("obj22.o2", obj22.o2);

print(string.rep("*",30), "obj22:add2()", string.rep("*",30))

obj22:add2()
print("obj22.o1", obj22.o1);
print("obj22.o2", obj22.o2);











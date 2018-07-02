local lua_log = require("lua_log")
require("class")
require("common")

function Object1_new()
    local Ob1 = {o1 = 10}

    function Ob1:add1()
        self.o1 = self.o1 + 1
    end

    function Ob1:printf()
        lua_log.print("Ob1:printf()")
    end

    function Ob1:var_printf()
        self:printf()
    end

    return Ob1
end


function Object2_new()
    local ob1 = Object1_new()

    local Ob2 = {o2 = 20}

    function Ob2:add2()
        self.o2 = self.o2 + 1
    end

    function Ob2:printf()
        lua_log.print("Ob2:printf()")
    end

    register_parent(Ob2, ob1, "Object1")

    return Ob2
end


function Object3_new()
    local ob2 = Object2_new()

    local Ob3 = {o3 = 30}

    function Ob3:add3()
        self.o3 = self.o3 + 1
    end

    function Ob3:printf()
        lua_log.print("Ob3:printf()")
    end

    register_parent(Ob3, ob2, "Object2")

    return Ob3
end

function Object4_new()
    local ob3 = Object3_new()

    local Ob4 = {o4 = 40}

    function Ob4:add4()
        self.o4 = self.o4 + 1
    end

    function Ob4:printf()
        lua_log.print("Ob4:printf()")
    end

    register_parent(Ob4, ob3, "Object3")

    return Ob4
end



print_sep1("Object1_new()");
local obj1 = Object1_new()
lua_log.print("obj1.o1", obj1.o1);
obj1:printf();
print_sep2("obj1:var_printf()");
obj1:var_printf();



print_sep2("print_table(obj1.parent_table)");
print_table(obj1.parent_table);

print_sep2("print_table(obj1)");
print_table(obj1);




print_sep1("Object2_new()");
local obj2 = Object2_new()
lua_log.print("obj2.o1", obj2.o1);
lua_log.print("obj2.Object1.o1", obj2.Object1.o1);
lua_log.print("obj2.o2", obj2.o2);
obj2.Object1:printf();
obj2:printf();
print_sep2("obj2:var_printf()");
obj2:var_printf();

print_sep2("print_table(obj2.parent_table)");
print_table(obj2.parent_table);

print_sep2("print_table(obj2)");
print_table(obj2);





print_sep1("Object3_new()");
local obj3 = Object3_new()
lua_log.print("obj3.o1", obj3.o1);
lua_log.print("obj3.Object1.o1", obj3.Object1.o1);
lua_log.print("obj3.o2", obj3.o2);
lua_log.print("obj3.Object2.o2", obj3.Object2.o2);
lua_log.print("obj3.o3", obj3.o3);
obj3.Object1:printf();
obj3.Object2:printf();
obj3:printf();
print_sep2("obj3:var_printf()");
obj3:var_printf();

print_sep2("print_table(obj3.parent_table)");
print_table(obj3.parent_table);

print_sep2("print_table(obj3)");
print_table(obj3);




print_sep1("Object4_new()");
local obj4 = Object4_new()
lua_log.print("obj4.o1", obj4.o1);
lua_log.print("obj4.Object1.o1", obj4.Object1.o1);
lua_log.print("obj4.o2", obj4.o2);
lua_log.print("obj4.Object2.o2", obj4.Object2.o2);
lua_log.print("obj4.o3", obj4.o3);
lua_log.print("obj4.Object3.o3", obj4.Object3.o3);
lua_log.print("obj4.o4", obj4.o4);

obj4.Object1:printf();
obj4.Object2:printf();
obj4.Object3:printf();
obj4:printf();
print_sep2("obj4:var_printf()");
obj4:var_printf();

print_sep2("print_table(obj4.parent_table)");
print_table(obj4.parent_table);

print_sep2("print_table(obj4)");
print_table(obj4);








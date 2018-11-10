local lua_log = require("lua_log")

local _class={}

function class(super)
        local class_type={}
        class_type.ctor=false
        class_type.super=super
        class_type.new=function(...)
                        local obj={}
                        do
                                local create
                                create = function(c,...)
                                        if c.super then
                                                create(c.super,...)
                                        end
                                        if c.ctor then
                                                c.ctor(obj,...)
                                        end
                                end

                                create(class_type,...)
                        end
                        setmetatable(obj,{ __index=_class[class_type] })
                        return obj
                end
        local vtbl={}
        _class[class_type]=vtbl

        setmetatable(class_type,{__newindex=
                function(t,k,v)
                        vtbl[k]=v
                end
        })

        if super then
                setmetatable(vtbl,{__index=
                        function(t,k)
                                local ret=_class[super][k]
                                vtbl[k]=ret
                                return ret
                        end
                })
        end

        return class_type
end




base_type=class()		-- 定义一个基类 base_type

function base_type:ctor(x)	-- 定义 base_type 的构造函数
        lua_log.print("base_type ctor")
        self.x=x
end

function base_type:print_x()	-- 定义一个成员函数 base_type:print_x
        lua_log.print(self.x)
end

function base_type:hello()	-- 定义另一个成员函数 base_type:hello
        lua_log.print("hello base_type")
end



test=class(base_type)	-- 定义一个类 test 继承于 base_type

function test:ctor()	-- 定义 test 的构造函数
        lua_log.print("test ctor")
end

function test:hello()	-- 重载 base_type:hello 为 test:hello
        lua_log.print("hello test")
end


lua_log.print("base_type", base_type);
lua_log.print("test", test);

for k,v in pairs(_class) do
    lua_log.print("_class", k ,v)
end

lua_log.print("_class[base_type]", _class[base_type]);
lua_log.print("_class[test]", _class[test]);

lua_log.print(string.rep("*",30), "pairs(base_type)", string.rep("*",30))
for k,v in pairs(base_type) do
    lua_log.print("_class", k ,v)
end

lua_log.print(string.rep("*",30), "pairs(test)", string.rep("*",30))
for k,v in pairs(test) do
    lua_log.print("_class", k ,v)
end

lua_log.print(string.rep("*",30), "pairs(_class[base_type])", string.rep("*",30))
for k,v in pairs(_class[base_type]) do
    lua_log.print("_class", k ,v)
end

lua_log.print(string.rep("*",30), "pairs(_class[test])", string.rep("*",30))
for k,v in pairs(_class[test]) do
    lua_log.print("_class", k ,v)
end


lua_log.print(string.rep("*",30), "a=test.new(1)", string.rep("*",30))
a=test.new(1)	-- 输出两行，base_type ctor 和 test ctor 。这个对象被正确的构造了。


lua_log.print(string.rep("*",30), "pairs(_class[base_type])", string.rep("*",30))
for k,v in pairs(_class[base_type]) do
    lua_log.print("_class", k ,v)
end

lua_log.print(string.rep("*",30), "pairs(_class[test])", string.rep("*",30))
for k,v in pairs(_class[test]) do
    lua_log.print("_class", k ,v)
end


lua_log.print(string.rep("*",30), "pairs(a)", string.rep("*",30))
for k,v in pairs(a) do
    lua_log.print("_class", k ,v)
end



mb=_class[base_type]
mt=_class[test]
lua_log.print(mb.x);
lua_log.print(mt.x);

a:print_x()	-- 输出 1 ，这个是基类 base_type 中的成员函数。
a:hello()	-- 输出 hello test ，这个函数被重载了。

a.x = 11
a:print_x()

a.x = nil
a:print_x()


b=test.new(1)	-- 输出两行，base_type ctor 和 test ctor 。这个对象被正确的构造了。
b:print_x()	-- 输出 1 ，这个是基类 base_type 中的成员函数。
b:hello()	-- 输出 hello test ，这个函数被重载了。

b.x = 111
b:print_x()
a:print_x()


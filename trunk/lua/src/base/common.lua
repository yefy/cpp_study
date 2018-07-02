local lua_log = require("lua_log")
function print_sep1(str)
    lua_log.print(string.rep("*",30), "[", str, "]", string.rep("*",30))
end

function print_sep2(str)
    lua_log.print(string.rep("*",15), "[", str, "]", string.rep("*",15))
end

function print_sep3(str)
    lua_log.print(string.rep("*",5), "[", str, "]", string.rep("*",5))
end

function print_table(table)
    if table then
        for k,v in pairs(table) do
            lua_log.print("key : ", "[", k, "]", "     |     ", "value : " , "[", v, "]")
        end
    end
end

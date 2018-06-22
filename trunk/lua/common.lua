function print_sep1(str)
    print(string.rep("*",30), "[", str, "]", string.rep("*",30))
end

function print_sep2(str)
    print(string.rep("*",15), "[", str, "]", string.rep("*",15))
end

function print_sep3(str)
    print(string.rep("*",5), "[", str, "]", string.rep("*",5))
end

function print_table(table)
    if table then
        for k,v in pairs(table) do
            print("key : ", "[", k, "]", "     |     ", "value : " , "[", v, "]")
        end
    end
end


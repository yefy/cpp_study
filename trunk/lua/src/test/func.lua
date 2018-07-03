local lua_log = require("lua_log")
require("common")

lua_log.print("start func.lua");

function add(x,y)  
       lua_log.print(string.format("%d + %d = %d", x, y, x + y));
       return x + y
end 

function more_arg(arg_int8, arg_uint8, arg_int16, arg_uint16, arg_int32, arg_uint32, arg_int64, arg_uint64, arg_double, arg_char, arg_binary)

    lua_log.print(arg_int8, arg_uint8, arg_int16, arg_uint16, arg_int32, arg_uint32, arg_int64, arg_uint64, arg_double, arg_char, arg_binary);

    print(arg_int8, arg_uint8, arg_int16, arg_uint16, arg_int32, arg_uint32, arg_int64, arg_uint64, arg_double, arg_char, get_binary(arg_binary));

    return arg_int8, arg_uint8, arg_int16, arg_uint16, arg_int32, arg_uint32, arg_int64, arg_uint64, arg_double, arg_char, arg_binary
end

lua_log.print("end func.lua");



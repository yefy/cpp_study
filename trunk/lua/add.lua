local lua_log = require("lua_log")

function add(x,y)  
       lua_log.print(string.format("%d + %d = %d", x, y, x + y));
       return x + y   
end 





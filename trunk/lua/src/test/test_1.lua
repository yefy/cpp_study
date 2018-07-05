--½×²ãº¯Êý

--[[½×²ãº¯Êý]]

--[[
½×²ãº¯Êý
--]]

function fact (n)
	if n == 0 then
		return 1
	else
		return n * fact(n - 1)
	end
end

print("test nill")
print(test_nill)

print("test global number")
number = 9
print(number)
number = nil

print("test local number")
local localNumber = 19
print(localNumber)
localNumber = nil

print("enter a number:")
a = io.read("*number")
print(fact(a))
---[[
os.exit()
--]]

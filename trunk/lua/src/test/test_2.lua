print(type("Hello world"))      --> string
print(type(10.4*3))             --> number
print(type(print))              --> function
print(type(type))               --> function
print(type(true))               --> boolean
print(type(nil))                --> nil
print(type(type(X)))            --> string

local localNumber = 9
print(type(localNumber))        --> number

print("---------------------")

table_test = {}

table_test["x"] = 7
print(table_test["x"])
print(table_test.x)

table_test.y = 5
print(table_test["y"])
print(table_test.y)

table_test["11"] = 11
print(table_test["11"])
--print(table_test.11) 错误

table_test[10] = 10
print(table_test[10])
--print(table_test.10) 错误

table_test[100] = 100
print(table_test[100])
--print(table_test.100) 错误

print(#table_test)
print(table.maxn(table_test))


print("---------------------")


table_test_2 = {}
for i = 1, 1 do
print "enter a number"
	table_test_2[i] = assert(io.read("*number"), "invalid input")
end

---[[
for i = 1, #table_test_2 do
	print(table_test_2[i])
end
--]]

print(#table_test_2)
print(table.maxn(table_test_2))

print("---------------------")
print(a == b)


c = nil
local d = nil
print(c == d)

print(nil == nil)


e = e or 10
print(e)

if not f then
	f = 11
end
print(f)


print("ab" .. "cd")
print(12 .. 34)


globle_number_1 = 1
local local_number_1 = globle_number_1
local_number_1 = local_number_1 + 1

print(globle_number_1, local_number_1)



function foo()
	--return 这里加return 错误

	--下面这样才是正确的
	--[[
	do
		return
    end
	--]]

	return "a", "b"
end

stra, strb = foo()
print(stra, strb)

stra, strb, strc = "aa", foo()
print(stra, strb, strc)

stra, strb, strc = foo(), "aa" --注意这里    "a" "aa" nil
print(stra, strb, strc)


function unpack_test(t, i)
	i = i or 1
	if t[i] then
		return t[i], unpack(t, i + 1)
	end
end


f = string.find
a = {"Hello", "ll"}

print(f(unpack_test(a)))


print(string.format("a = %d, b = %d ", 4, 5))
print(string.format("a = %s, b = %s ", "a", "b"))


function error_test(number)
	print "error_test"
	print(number)
	---[[
	if number == nil or number == 0 then
		print "error"
		error("error")
	else
		print "not error"
		return number
	end
	--]]
end


---[[
print "------------------ start"
local status, err = pcall(error_test)
print "------------------ return"
if status then
	print "not error"
	print(err)
else
	print "error"
	print(err)
end
print "------------------ end"
--]]


---[[
print "------------------ start"
local status, err = pcall(error_test, 1)
print "------------------ return"
if status then
	print "not error"
	print(err)
else
	print "error"
	print(err)
end
print "------------------ end"
--]]

print "------------------ traceback"
print(debug.traceback())

print "------------------ xpcall"
print(xpcall(function(i) print(i) error('error..') end, function() print(debug.traceback()) end, 33))

print "error_test_end"

print "------------------ coroutine"

co = coroutine.create(function ()
    print("hi")
end)

print(co)     --> thread: 0x8071d98

print(coroutine.status(co))     --> suspended

coroutine.resume(co)

print(coroutine.status(co))     --> dead

print "-------------------------"
co = coroutine.create(function ()
    for i=1,2 do
       print("co", i)
       print(coroutine.yield())
    end
end)

print(coroutine.resume(co))
print(coroutine.status(co))     --> suspended

print(coroutine.resume(co))
print(coroutine.status(co))     --> suspended

print(coroutine.resume(co, 1, 2))     -- prints nothing
print(coroutine.status(co))     --> dead

print(coroutine.resume(co))     --> false   cannot resume dead coroutine

print "-------------------------"
co = coroutine.create(function (a,b,c)
    print("co", a,b,c)
end)
print(coroutine.resume(co, 1, 2, 3))      --> co  1  2  3

print "-------------------------"
co = coroutine.create(function (a,b)
    coroutine.yield(a + b, a - b)
end)
print(coroutine.resume(co, 20, 10))    --> true  30  10
print(coroutine.status(co))
print(coroutine.resume(co, 20, 10))
print(coroutine.status(co))
print(coroutine.resume(co, 20, 10))

print "-------------------------"
co = coroutine.create (function ()
    print("co", coroutine.yield())
end)
print(coroutine.resume(co))
print(coroutine.resume(co, 4, 5))      --> co  4  5

print "-------------------------"
co = coroutine.create(function ()
    return 6, 7
end)
print(coroutine.resume(co))     --> true  6  7
print(coroutine.resume(co))



--[[
print "-------------------------producer  consumer"
function receive (prod)
    local status, value = coroutine.resume(prod)
    return value
end

function send (x)
    coroutine.yield(x)
end

function producer ()
    return coroutine.create(function ()
       while true do
           local x = io.read("*number")      -- produce new value
		   if x ~= nil then
				send(x)
			else
				print "io.read nil"
			end
       end
    end)
end

function filter (prod)
    return coroutine.create(function ()
       local line = 1
       while true do
           local x = receive(prod)  -- get new value
           x = string.format("%5d %d", line, x)
           send(x)       -- send it to consumer
           line = line + 1
       end
    end)
end

function consumer (prod)
    while true do
       local x = receive(prod)  -- get new value
       io.write(x, "\n")        -- consume new value
    end
end


p = producer()
f = filter(p)
consumer(f)
--]]


print "-------------------------permgen"
function permgen (a, n)
	n = n or #a
    if n <= 1 then
       --printResult(a)
	   coroutine.yield(a)
    else
       for i=1,n do

           -- put i-th element as the last one
           a[n], a[i] = a[i], a[n]

           -- generate all permutations of the other elements
           permgen(a, n - 1)

           -- restore i-th element
           a[n], a[i] = a[i], a[n]

       end
    end
end

function printResult (a)
    for i,v in ipairs(a) do
       io.write(v, " ")
    end
    io.write("\n")
end


--permgen ({1,2,3,4}, 4)


function perm (a)
    local n = table.getn(a)
    local co = coroutine.create(function () permgen(a, n) end)
    return function ()   -- iterator
       local code, res = coroutine.resume(co)
	   print(code, res)
       return res
    end
end


for p in perm{"a", "b", "c"} do
	print(p)
    printResult(p)
end


--[[
print "-------------------------download file"

require "socket"

--host = "www.w3.org"
host = "www.baidu.com"
file = "/TR/REC-html32.html"


function download (host, file)
    local c = assert(socket.connect(host, 80))
	print("socket.connect", c)
    local count = 0      -- counts number of bytes read
    print("c:send", c:send("GET " .. file .. " HTTP/1.0\r\n\r\n"))
    while true do
       local s, status, partial = receive(c)
	   print("receive", s, status, partial)
       count = count + #(s or partial)
	   print("count", count)
       if status == "closed" then break end
    end
    c:close()
    print("c:close", file, count)
end


function receive (connection)
    connection:settimeout(0)    -- do not block
    local s, status, partial = connection:receive(2^10)
	print("connection:receive", s, status, partial)
    if status == "timeout" then
		print "timeout yield"
        coroutine.yield(connection)
    end
    return s or partial, status
end

threads = {}      -- list of all live threads
function get (host, file)
    -- create coroutine
    local co = coroutine.create(function ()
       download(host, file)
    end)
    -- insert it in the list
    table.insert(threads, co)
end


function dispatcher ()
	local i = 1
	local connetcions = {}
    while true do
		if threads[i] == nil then
			if threads[1] == nil then break end
			i = 1
			connetcions = {}
		end


		local status, res = coroutine.resume(threads[i])
		if not res then
			table.remove(threads, i)
		else
			i = i + 1
			connetcions[#connetcions + 1] = res

			if #connetcions == #threads then
				print("socket.select")
				socket.select(connections)
			end
       end
    end
end


host = "www.w3c.org"

get(host, "/TR/html401/html40.txt")
get(host, "/TR/2002/REC-xhtml1-20020801/xhtml1.pdf")
get(host, "/TR/REC-html32.html")
get(host,
    "/TR/2000/REC-DOM-Level-2-Core-20001113/DOM2-Core.txt")

dispatcher()      -- main loop
--]]


astr = 'a "problematic" \\string'
print(astr)
print(string.format("%q", astr))

--assert(false)


print "-------------------------class"

a = { index1 = 1, index2 = 2 }
print(a.index1, a.index2)


b = a
print(b.index1, b.index2)

b.index1 = 2
print(a.index1, a.index2)
print(b.index1, b.index2)



Account = {
    balance=0,
    withdraw = function (self, v)
       self.balance = self.balance - v
	   print(self.balance)
    end
}

function Account:balanceValue ()
	print(self.balance)
end

function Account:deposit (v)
    self.balance = self.balance + v
	print(self.balance)
end


function Account.withdraw_2 (v)
    Account.balance = Account.balance - v
	print(Account.balance)
end


function Account.withdraw_3 (self, v)
    self.balance = self.balance - v
	print(self.balance)
end

function Account:new (o)
    o = o or {}   -- create object if user does not provide one
    setmetatable(o, self)
    self.__index = self
    return o
end

print "-------------------------1111111111111"
Account:balanceValue()
Account:deposit(200.00)
Account.deposit(Account, 200.00)
Account:withdraw(100.00)
Account.withdraw(Account, 100.00)


Account.withdraw_2(300.00)
--Account:withdraw_2(300.00) error

Account.withdraw_3(Account, 300.00)
Account:withdraw_3(300.00)

print "-------------------------22222222222222222"


aa = Account:new{balance = 0}
aa:balanceValue()
aa:deposit(100.00)
aa:deposit(100.00)

Account:balanceValue()
Account:deposit(200.00)
Account:deposit(200.00)

print "-------------------------3333333333333333"

bb = Account:new()
bb :balanceValue()
bb:deposit(100.00)
bb:deposit(100.00)

Account:balanceValue()
Account:deposit(200.00)
Account:deposit(200.00)

print "-------------------------44444444444"

SpecialAccount = Account:new{balance = 10}

function SpecialAccount:getLimit ()
    value = self.limit or 0
	print(value)
	 return value
end

function SpecialAccount:deposit (v)
    self.balance = self.balance + v + self:getLimit()
	print(self.balance)
end


s = SpecialAccount:new{limit = 30}

s:getLimit()
s:balanceValue()
s:deposit(100)


print "-------------------------5555555555"


local function search (k, plist)
    for i=1, #plist do
       local v = plist[i][k]    -- try 'i'-th superclass
       if v then
			print("search", i)
			return v
	   end
    end
end

function createClass (...)
    local c = {}      -- new class
	local parents = {...}

    -- class will search for each method in the list of its
    -- parents (`arg' is the list of parents)
    setmetatable(c, {__index = function (t, k)

		return search(k, parents)
	end})

-- prepare `c' to be the metatable of its instances
	c.__index = c

-- define a new constructor for this new class
	function c:new (o)
		o = o or {}
		setmetatable(o, c)
		return o
	end

-- return new class
    return c
end


Named = {}
function Named:getname ()
    return self.name
end

function Named:setname (n)
    self.name = n
end


Sex = {}
function Sex:getsex ()
    return self.sex
end

function Sex:setsex (n)
    self.sex = n
end

---[[
NamedSex = createClass(Sex, Named)
namedSex = NamedSex:new{name = "Paul", sex = "girl"}
print(namedSex:getname())    --> Paul
print(namedSex:getsex())
--]]

--NamedAccount = createClass(Account, Named)
NamedAccount = createClass(Named, Account)
namedAccount = NamedAccount:new{name = "Paul"}
print(namedAccount:getname())    --> Paul

print "-------------------------private"


function newAccount (initialBalance)
    local self = {balance = initialBalance}
    local withdraw = function (v)
       self.balance = self.balance - v
    end

    local deposit = function (v)
       self.balance = self.balance + v
    end

    local getBalance = function () return self.balance end

    return {
       withdraw = withdraw,
       deposit = deposit,
       getBalance = getBalance
    }
end

collectgarbage("collect")
local memoryCount1 = collectgarbage("count")
print(">>>>>>>>>>> memoryCount1", memoryCount1)

acc1 = newAccount(100.00)

local memoryCount2 = collectgarbage("count")
print(">>>>>>>>>>> memoryCount2", memoryCount2)

collectgarbage("collect")
local memoryCount3 = collectgarbage("count")
print(">>>>>>>>>>> memoryCount3", memoryCount3)

acc1.withdraw(40.00)
print(acc1.getBalance())    --> 60



function newObject (value)
    return function (action, v)
       if action == "get" then return value
       elseif action == "set" then value = v
       else error("invalid action")
       end
    end
end


d = newObject(0)
print(d("get"))      --> 0
d("set", 10)
print(d("get"))      --> 10


print "-------------------------math"

math.randomseed(os.time())
for i = 1, 10 do
	print(i, math.random(6, 10))
end


lines = {
	luaH_set = 10,
	luaH_get = 24,
	luaH_present = 48,
}

a = {}

for n in pairs(lines) do
	a[#a + 1] = n
end

table.sort(a, function (a, b) return string.lower(a) < string.lower(b) end)

for i, n in ipairs(a) do
	print(i, n, lines[n])
end


function unescape(s)
	s = string.gsub(s, "+", " ")
	print(s)
	s = string.gsub(s, "%%(%x%x)",
						function (h)
							print("h = ", h)
							local str = string.char(tonumber(h, 16))
							print("str = ", str)
							return str
						end
					)
	return s
end

print(unescape("a%2Bb+%3D+c"))

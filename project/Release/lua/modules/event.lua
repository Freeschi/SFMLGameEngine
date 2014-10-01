-- Event
event = {}

-- Event Listener Table
event.Listeners = {}

-- AddListener
function event.AddListener(eventname, callback)
	assert(type(eventname) == "string")
	assert(type(callback) == "function")
	
	if event.Listeners[eventname] == nil then
		event.Listeners[eventname] = {}
	end
	
	table.insert(event.Listeners[eventname], callback)
end

-- RemoveListener
function event.RemoveListener(eventname, callback)
	assert(type(eventname) == "string")
	assert(type(callback) == "function")
	
	if event.Listeners[eventname] == nil then return end
end

-- Call
function event.Call(eventname, ...)
	assert(type(eventname) == "string")
	
	if event.Listeners[eventname] ~= nil then
		for _,callback in ipairs(event.Listeners[eventname]) do
			callback(...)
		end
	end
end
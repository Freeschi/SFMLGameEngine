-- Event
event = event or {}

-- Event Listener Table
if event.Listeners == nil then
	event.Listeners = {}
end

-- AddListener
function event.AddListener(eventname, callbackname, callback)
	checkarg(1, eventname, "string")
	checkarg(2, callbackname, "string")
	checkarg(3, callback, "function")

	if event.Listeners[eventname] == nil then
		event.Listeners[eventname] = {}
	end
	event.Listeners[eventname][callbackname] = callback
end

-- RemoveListener
function event.RemoveListener(eventname, callbackname)
	checkarg(1, eventname, "string")
	checkarg(2, callbackname, "string")
	
	if event.Listeners[eventname] == nil then return end
	event.Listeners[eventname][callbackname] = nil
end

-- Call
function event.Call(eventname, ...)
	--checkarg(1, eventname, "string") 
	
	if event.Listeners[eventname] ~= nil then
		for _,callback in pairs(event.Listeners[eventname]) do
			callback(...)
		end
	end
end
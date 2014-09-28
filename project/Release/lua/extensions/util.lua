-- type
_type = type
function type(obj)
	local t = _type(obj)
	if t == "table" or t == "userdata" or t == "metatable" then
		if obj.__type ~= nil then
			return obj.__type
		end
	end
	
	return t
end
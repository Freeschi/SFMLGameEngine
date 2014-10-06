-- type
if _type == nil then
	_type = type
end
function type(obj)
	local t = _type(obj)
	if t == "table" or t == "userdata" or t == "metatable" then
		if obj.__type ~= nil then
			if _type(obj.__type) == "function" then
				return obj:__type()
			end
			return obj.__type
		end 
	end
	
	return t
end

-- math.round
function math.round(num, idp)
	local mult = 10^(idp or 0)
	return math.floor(num * mult + 0.5) / mult
end

-- checkarg
function checkarg(i, v, expect)
	if type(v) ~= expect then
		error("expected argument " .. i .. " to be " .. expect .. " (got " .. type(v) .. " instead)")
	end
end 

-- IsValid
function IsValid(obj)
	if obj == nil then return false end
	
	if type(obj) == "table" or type(obj) == "userdata" then
		if obj.IsValid then
			return obj:IsValid()
		end
	end
	
	return true
end
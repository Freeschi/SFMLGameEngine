--[[---------------------------------------------------------
	Vector 2
-----------------------------------------------------------]]
Vector2.__type = "Vector2"
Vector2.__tostring = function(s)
	return s.x .. " " .. s.y
end

-- Operator
Vector2.__add = function(a, b)
	return Vector2(a.x + b.x, a.y + b.y)
end
Vector2.__sub = function(a, b)
	return Vector2(a.x - b.x, a.y - b.y)
end
Vector2.__mul = function(a, b)
	if type(b) == "Vector2" then
		return Vector2(a.x * b.x, a.y * b.y)
	elseif type(b) == "number" then
		return Vector2(a.x * b, a.y * b)
	end
	return a
end
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
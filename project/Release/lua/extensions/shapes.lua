--[[---------------------------------------------------------
	Shape
-----------------------------------------------------------]]
sfShape.__type = "sfShape"
sfShape.__tostring = function(s)
	return "[Base sfShape]"
end

--[[---------------------------------------------------------
	Rectangle Shape
-----------------------------------------------------------]]
sfRectangleShape.__type = "sfRectangleShape"
sfRectangleShape.__tostring = function(s)
	return "[sfRectangleShape]"
end

--[[---------------------------------------------------------
	Circle Shape
-----------------------------------------------------------]]
sfCircleShape.__type = "sfCircleShape"
sfCircleShape.__tostring = function(s)
	return "[sfCircleShape]"
end
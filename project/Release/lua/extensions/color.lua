--[[---------------------------------------------------------
	Color
-----------------------------------------------------------]]
--class "Color"
function Color(r, g, b, a)
	local c = {}
	
	c.r = r or 0
	c.g = g or 0
	c.b = b or 0
	c.a = a or 255
	c.__type = "Color"
	
	return c
end
--[[
Color.__type = "Color"
Color.__tostring = function(s)
	return "[Color "..s.r.." "..s.g.." "..s.b.." "..s.a.."]"
end

--[[---------------------------------------------------------
	Static Colors
-----------------------------------------------------------
Color.White = Color(255,255,255)
Color.Black = Color(0,0,0)
Color.Red	= Color(255,0,0)
Color.Green = Color(0,255,0)
Color.Blue	= Color(0,0,255)

--]]
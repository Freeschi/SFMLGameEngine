-- Draw
draw.RelativePosition = {0, 0}

-- Relative Position
function draw.SetRelativePosition(x, y)
	draw.RelativePosition = {x, y}
end

-- Line
function draw.Line(x, y, x2, y2, col, col2)
	checkarg(1, x, "number")
	checkarg(2, y, "number")
	checkarg(3, x2, "number")
	checkarg(4, y2, "number")

	local r = draw.RelativePosition
	
	if col == nil then
		col = Color(255,255,255)
	end
	if col2 == nil then
		col2 = col
	end
	return draw.internal_Line(r[1] + x, r[2] + y, r[1] + x2, r[2] + y2, col, col2)
end

-- Rectangle
function draw.Rectangle(x, y, w, h, c)
	checkarg(1, x, "number")
	checkarg(2, y, "number")
	checkarg(3, w, "number")
	checkarg(4, h, "number")

	local r = draw.RelativePosition
	return draw.internal_Rectangle(r[1] + x, r[2] + y, w, h, c or Color(255,255,255))
end

-- Outlined Rectangle
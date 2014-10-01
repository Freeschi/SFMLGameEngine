--[[---------------------------------------------------------
	SpriteNode
-----------------------------------------------------------]]
SpriteNode.__type = "SpriteNode"
SpriteNode.__tostring = function(s)
	if s:IsValid() then
		return "[SpriteNode:" .. s:Index().." " .. s:GetClassName() .. "]"
	else
		return "[NULL SpriteNode]"
	end
end
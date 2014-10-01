--[[---------------------------------------------------------
	Entity
-----------------------------------------------------------]]
Entity.__type = "Entity"
Entity.__tostring = function(s)
	if s:IsValid() then
		return "[Entity:" .. s:Index().." " .. s:GetClassName() .. "]"
	else
		return "[NULL Entity]"
	end
end

--[[---------------------------------------------------------
	Scene Node
-----------------------------------------------------------]]
SceneNode.__type = "SceneNode"
SceneNode.__tostring = function(s)
	if s:IsValid() then
		return "[SceneNode]"
	else
		return "[NULL SceneNode]"
	end
end
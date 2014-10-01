--[[---------------------------------------------------------
	Human
-----------------------------------------------------------]]
Human.__type = "Human"
Human.__tostring = function(s)
	if s:IsValid() then
		return "[Human:" .. s:Index().." " .. s:GetClassName() .. "]"
	else
		return "[NULL Human]"
	end
end

--[[---------------------------------------------------------
	Player
-----------------------------------------------------------]]
Player.__type = "Player"
Player.__tostring = function(s)
	if s:IsValid() then
		return "[Player:" .. s:Index().." " .. s:GetClassName() .. "]"
	else
		return "[NULL Player]"
	end
end
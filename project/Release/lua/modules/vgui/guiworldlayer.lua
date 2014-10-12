--[[---------------------------------------------------------
	GUI World Layer
-----------------------------------------------------------]]
vgui.WorldLayer = vgui.WorldLayer or {}
vgui.WorldLayer.Children = vgui.WorldLayer.Children or {}

-- AddChild
function vgui.WorldLayer:Add(obj)
	if obj:Index() ~= nil then
		return obj:Index()
	end
	
	table.insert(self.Children, obj)
	return #self.Children
end

-- IsRegistered
function vgui.WorldLayer:IsRegistered(obj)
	for k,v in pairs(self.Children) do
		if v == obj then
			return true
		end
	end
end

-- Remove
function vgui.WorldLayer:Remove(obj)
	self.Children[obj:Index()] = nil
end

-- Draw
function vgui.WorldLayer:Draw()
	for k,v in pairs(self.Children) do
		if IsValid(v) then
			if v:GetParent() == nil and v.__draw ~= nil then
				v:__draw()
			end
		end
	end
end
 
-- Draw
event.AddListener("DrawHUD", "vgui_draw", function()
	vgui.WorldLayer:Draw()
end)
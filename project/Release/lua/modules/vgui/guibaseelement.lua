--[[---------------------------------------------------------
	GUIBaseElement
-----------------------------------------------------------]]
class "GUIBaseElement"
function GUIBaseElement.__type(s)
	return s:GetClassName()
end
function GUIBaseElement.__tostring(s)
	if s:IsValid() then
		return "[GUI " .. s:GetClassName() .. "]"
	else
		return "[NULL " .. s:GetClassName() .."]"
	end
end

-- Accessor
util.ACCESSOR_FUNC(GUIBaseElement, "Position", "m_vPosition")
util.ACCESSOR_FUNC(GUIBaseElement, "Color", "m_cColor")
util.ACCESSOR_FUNC(GUIBaseElement, "Parent", "m_pParent")

-- Init
function GUIBaseElement:__init(classname)
	self.ClassName = classname
	self.Children  = {}
	
	self:SetPosition(Vector2(0,0))
	self:SetColor(Color(255,255,255))
end

-- Remove
function GUIBaseElement:Remove()
	if self:IsValid() then
		vgui.WorldLayer:Remove(self)
		self._vgui_Index = nil
	end
end

-- Index
function GUIBaseElement:Index()
	return self._vgui_Index
end

-- IsValid
function GUIBaseElement:IsValid()
	return self:Index() ~= nil and self:Index() > 0
end

-- ClassName
function GUIBaseElement:GetClassName()
	return self.ClassName or "GUIBaseElement"
end

-- Draw
function GUIBaseElement:__draw()
	-- Relative Position
	local v = self:GetPosition()
	local r = draw.RelativePosition
	draw.SetRelativePosition(v.x + r[1], v.y + r[2])

	-- Draw self
	if self.Draw ~= nil then
		self:Draw()
	end
	
	-- Draw children
	for k,v in pairs(self.Children) do
		if IsValid(v) then
			v:__draw()
		end
	end
end

--[[---------------------------------------------------------
	Children
-----------------------------------------------------------]]
function GUIBaseElement:AddChild(obj)
	-- Remove current parent
	local parent = obj:GetParent()
	if IsValid(parent) then
		if parent == self then
			return
		end
		
		parent:RemoveChild(obj)
	end
	
	-- Add as child
	obj:SetParent(self)
	table.insert(self.Children, obj)
end
function GUIBaseElement:RemoveChild(obj)
	local parent = obj:GetParent()
	if not IsValid(parent) then return end
	if parent ~= self then return end
	
	for k,v in pairs(self.Children) do
		if v == obj then
			table.remove(self.Children, k)
			return
		end
	end
end
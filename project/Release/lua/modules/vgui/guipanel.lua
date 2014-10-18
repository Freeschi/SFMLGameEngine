--[[---------------------------------------------------------
	GUIPanel
-----------------------------------------------------------]]
class "GUIPanel" (GUIBaseElement)
util.ACCESSOR_FUNC(GUIPanel, "BackgroundColor", "m_cBackgroundColor")

-- Init
function GUIPanel:__init()
	GUIBaseElement.__init(self)
	self.ClassName = "GUIPanel"
	
	self:SetSize(5, 5)
	self:SetBackgroundColor(Color(50,50,50))
	
	print("GUIPanel::ctor")
end

-- Size
function GUIPanel:SetSize(w,h)
	self.m_vSize = Vector2(w,h)
end
function GUIPanel:GetWidth() return self.m_vSize.x end
function GUIPanel:GetHeight() return self.m_vSize.y end
function GUIPanel:GetSize()
	return self:GetWidth(), self:GetHeight()
end

-- Draw
function GUIPanel:Draw()
	local x,y = self:GetPosition().x, self:GetPosition().y
	local w,h = self:GetSize()
	local col = self:GetBackgroundColor()
	
	--print(x, y, w, h, col)
	draw.Rectangle(x, y, w, h, col)
end

-- Register
vgui.RegisterClass("Panel", GUIPanel)
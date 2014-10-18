--[[---------------------------------------------------------
	GUIWindow
-----------------------------------------------------------]]
class "GUIWindow" (GUIPanel)
util.ACCESSOR_FUNC(GUIWindow, "TitleHeight", "m_iTitleHeight")
util.ACCESSOR_FUNC(GUIWindow, "TitleBackgroundColor", "m_cTitleColor")
util.ACCESSOR_FUNC(GUIWindow, "Title", "m_sTitle")

-- Init
function GUIWindow:__init()
	GUIBaseElement.__init(self)
	self.ClassName = "GUIWindow"
	self:SetTitleHeight(20)
	self:SetTitleBackgroundColor(Color(33, 33, 33))
end

function drawLine(x,y,w,h)
	--
end

-- Draw
function GUIWindow:Draw()
	-- Panel
	GUIPanel.Draw(self)

	-- Title
	draw.Rectangle(0, 0, self:GetWidth(), self:GetTitleHeight(), self:GetTitleBackgroundColor())
end

-- Register
vgui.RegisterClass("Window", GUIWindow) 
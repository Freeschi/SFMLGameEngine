--[[---------------------------------------------------------
	GUIText
-----------------------------------------------------------]]
class "GUIText" (GUIBaseElement)
util.ACCESSOR_FUNC(GUIText, "Text", "m_sText")
util.ACCESSOR_FUNC(GUIText, "Size", "m_iTextSize")

-- Init
function GUIText:__init()
	GUIBaseElement.__init(self)
	self.ClassName = "GUIText"
	self:SetText("GUIText")
	self:SetSize(16)
	self.Text = sfText()
end

-- Font
function GUIText:SetFont(f)
	if type(f) == "string" then
		font = game.GetFont(f)
		if font == nil then
			error("Unknown font " .. f)
		end
		self.m_fFont = font
	else
		self.m_fFont = f
	end
end

-- Draw
function GUIText:Draw()
	self.Text:SetFont(game.GetFont("Arial"))
	self.Text:SetSize(self:GetSize())
	self.Text:SetText(self:GetText())
	self.Text:SetPosition(self:GetPosition())
	if self.m_fFont ~= nil then
		self.Text:SetFont(self.m_fFont)
	end
	self.Text:SetColor(self:GetColor())
	window:Draw(self.Text)
end

-- Register
vgui.RegisterClass("Text", GUIText)
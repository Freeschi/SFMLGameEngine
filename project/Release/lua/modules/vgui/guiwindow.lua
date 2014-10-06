--[[---------------------------------------------------------
	GUIWindow
-----------------------------------------------------------]]
class "GUIWindow" (GUIPanel)

-- Init
function GUIWindow:__init()
	GUIBaseElement.__init(self)
	self.ClassName = "GUIWindow"
end

-- Register
vgui.RegisterClass("Window", GUIGUIWindowText)
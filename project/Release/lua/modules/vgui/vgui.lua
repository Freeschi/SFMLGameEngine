-- VGUI
vgui = vgui or {}
vgui.RegisteredClasses = {}

-- Register
function vgui.RegisterClass(name, obj)
	vgui.RegisteredClasses[name] = obj
end

-- Create
vgui.Create = function(classname)
	local obj = vgui.RegisteredClasses[classname]
	if obj == nil then
		error("Attempted to create unknown VGUI " .. classname)
	end
	
	local element = obj()
	element._vgui_Index = vgui.WorldLayer:Add(element)
	return element
end

-- Includes
include("guiworldlayer.lua")
include("guibaseelement.lua")
include("guipanel.lua")
include("guiwindow.lua")
include("guitext.lua")
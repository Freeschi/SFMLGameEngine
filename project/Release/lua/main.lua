-- Main
function _main()
	print("[Lua] Initializing..")
	
	-- Includes
	include("modules/event.lua")
	
	-- Events
	event.AddListener("OnGameInitialized", function()
		print("Hi!")
		
		local sftime = sfTime()
		
		local ent = Entity()
		print(ent:GetClassName())
		ent:Update(sftime)
	end)
end
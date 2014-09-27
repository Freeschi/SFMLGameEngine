-- Main
function _main()
	print("[Lua] Initializing..")
	
	-- Includes
	include("modules/event.lua")
	
	-- Events
	event.AddListener("OnGameInitialized", function()
		print("Hi!")
	end)
end
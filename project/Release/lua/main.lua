-- Main
function _main()
	print("[Lua] Initializing..")
	
	-- Includes
	include("modules/event.lua")
	include("extensions/vector.lua")
	include("extensions/entity.lua")
	include("extensions/util.lua")
	
	-- Events
	event.AddListener("OnGameInitialized", function()
		print("OnGameInitialized event")
		
		
	end)
	
	event.AddListener("BuildScene", function(scene)
		
	end)
	
	event.AddListener("OnEntityRemoved", function(ent)
		--
	end)
	
	local tp = 0
	event.AddListener("Update", function(slo)
		--print(slo:GetClassName())
	end)
end
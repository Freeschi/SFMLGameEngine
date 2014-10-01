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
		
		local ent = world.CreateEntity("aircraft_raptor")
		print(type(ent))
		ent:Activate()
		ent:SetPosition(Vector2(320,1760))
		
		print("----------------------------------")
		print(ent.AircraftType)
	end)
	
	event.AddListener("OnEntityRemoved", function(ent)
		--
	end)
	
	local tp = 0
	event.AddListener("Update", function(slo)
		--print(slo:GetClassName())
	end)
end
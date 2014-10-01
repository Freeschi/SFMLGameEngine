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
		ent:Activate()
		ent:SetPosition(Vector2(320,1760))
		
		local ent2 = world.CreateEntity("aircraft_eagle")
		ent2:Activate()
		ent2:SetPosition(ent:GetPosition() + Vector2(50,0))
		--ent2:SetParent(ent)
		print(ent2:GetParent())
	end)
	
	event.AddListener("OnEntityRemoved", function(ent)
		--
	end)
end
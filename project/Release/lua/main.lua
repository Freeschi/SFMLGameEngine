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
		print(ent)
		ent:Activate()
		ent:SetPosition(Vector2(320,1760))
		--print(ent)
		--print(ent:GetClassName())
		--ent:GetTable().test = "helloooo"
	end)
	
	event.AddListener("OnEntityRemoved", function(ent)
		print(type(ent))
		print(ent:GetClassName())
		--print(ent:GetTable().test)
	end)
end
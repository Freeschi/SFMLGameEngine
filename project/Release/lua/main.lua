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
		print("BuildScene event")
		
		local bounds = FloatRect(0, 0, 1280, 720)
		world.SetBounds(bounds)
		scene:SetBackgroundTexture("Background1")
		
		for i = 0, 15, 1 do
			if i > 0 and i < 14 then
				scene:Add(Vector2(i * 64,0), "Wall1")
				scene:Add(Vector2(i * 64, 64 * 10), "Wall1")
			end
			if i < 11 then
				scene:Add(Vector2(0, i * 64), "Wall1")
				scene:Add(Vector2(64 * 14, i * 64), "Wall1")
			end
		end
		
		for i = 0, 4, 1 do
			local y = i * 128
			
			scene:Add(Vector2(128,y), "Wall1")
			scene:Add(Vector2(128 + 64 * 2,y), "Wall1")
			scene:Add(Vector2(128 + 64 * 4,y), "Wall1")
			scene:Add(Vector2(128 + 64 * 6,y), "Wall1")
			scene:Add(Vector2(128 + 64 * 8,y), "Wall1")
			scene:Add(Vector2(128 + 64 * 10,y), "Wall1")
		end
	end)
	
	event.AddListener("OnEntityRemoved", function(ent)
		--
	end)
	
	local tp = 0
	event.AddListener("Update", function(slo)
		--print(slo:GetClassName())
	end)
end
-- Main
function _main()
	print("[Lua] Initializing..")
	
	-- Includes
	include("modules/event.lua")
	include("extensions/vector.lua")
	include("extensions/util.lua")
	
	-- Events
	event.AddListener("OnGameInitialized", function()
		print("Hi!")
		
		class 'test_lua_entity' (Entity)
		function test_lua_entity:__init()
			Entity.__init(self, "test_lua_entity")
		end
		function test_lua_entity:UpdateCurrent()
			print("test_lua_entity")
		end
		
		print(world.GetSceneLayer(0))
	end)
end
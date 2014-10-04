MAP = {
	Textures = {
		{ "Big1", "Media/Textures/ReallyBigTexture_1.png" },
		{ "Big2", "Media/Textures/ReallyBigTexture_2.png" },
		{ "Big3", "Media/Textures/ReallyBigTexture_3.png" },
		{ "Player1", "Media/Textures/Player1.png" },
		{ "Wall1", "Media/Textures/Wall1.png" },
		{ "Background1", "Media/Textures/Background1.png" },
		{ "Block1", "Media/Textures/Block1.png" }
	},
	
	LocalPlayer = {
		Texture = "Player1",
		Position = Vector2(64 + 9, 64 + 9)
	},
	
	World = {
		Bounds = FloatRect(0, 0, 1280, 720),
		Texture = "Background1"
	},
	
	BuildScene = function(scene, player)
		-- Area around field
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
	end
}

game.RegisterMap("default", MAP)
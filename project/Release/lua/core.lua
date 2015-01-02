-- Events
event.AddListener("OnGameInitialized", "_main_OnGameInitialized", function()  
	print("OnGameInitialized event")
end)

event.AddListener("LoadingScreenResources", "_main_loadingscreenresources", function(ls)
	print("Preparing resources..")    
	--ls:AddTexture("Big1", "Media/Textures/ReallyBigTexture_1.png")
	--ls:AddTexture("Big2", "Media/Textures/ReallyBigTexture_2.png")
	--ls:AddTexture("Big3", "Media/Textures/ReallyBigTexture_3.png")
	ls:AddTexture("Player1", "Media/Textures/Player1.png")
	ls:AddTexture("Wall1", "Media/Textures/Wall1.png")
	ls:AddTexture("Background1", "Media/Textures/Background1.png")
	ls:AddTexture("Block1", "Media/Textures/Block1.png")
	ls:AddFont("Arial", "Media/arial.ttf")
end)  

PLAYER = nil
event.AddListener("BuildScene", "_main_BuildScene", function(scene, player)
	-- Setup World Bounds 
	local bounds = FloatRect(0, 0, 1280, 720)
	world.SetBounds(bounds) 
	scene:SetBackgroundTexture("Background1") 
	
	-- Player 
	player:SetPosition(Vector2(64, 64 ))
	player:SetTexture("Player1")  
	PLAYER = player
	
	-- Area round field 
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

event.AddListener("DrawHUD", "_main_DrawHUD", function(window)

end)
  
if panel ~= nil and panel:IsValid() then
	panel:Remove()
	print("Removed") 
end   
          


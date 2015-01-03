#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <iostream>
#include <string>
#include <map>
#include "Singleton.hpp"
#include "SDL.h"
#include "SDL_image.h"

#define g_pTexturemanager Texturemanager::Get()

class Texturemanager : public TSingleton <Texturemanager>
{
public:

	bool Load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	bool Delete(std::string id); //Delete a specific Texture

	void Clean(); //Clean the Texturemanager

	void Draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:

	std::map<std::string, SDL_Texture*> m_TextureMap;
};



#endif // Texturemanager - Define
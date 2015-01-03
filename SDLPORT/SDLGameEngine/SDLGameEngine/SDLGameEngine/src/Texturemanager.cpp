#include "Texturemanager.hpp"

bool Texturemanager::Load(std::string fileName, std::string  id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0)
	{
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != NULL)
	{
		m_TextureMap[id] = pTexture;
		std::cout << "[TEXTUREMANAGER] Texture with id: " << id << " registred at: " << m_TextureMap[id] << std::endl;
		return true; //Everything worked
	}

	return false; //Something went wrong if this is reached
}

bool Texturemanager::Delete(std::string id)
{
	if (m_TextureMap[id] != NULL)
	{
		m_TextureMap[id] = NULL;
		std::cout << "[TEXTUREMANAGER] Deleted Texture with id: " << id << " [" << m_TextureMap[id] << "]\n";
		return true;
	}
	std::cout << "[TEXTUREMANAGER] failed to delete texture with id: " << id << " (ALREADY NULL)\n";
	return false;
}

void Texturemanager::Draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)  //STATIC IMAGE
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void Texturemanager::DrawFrame(std::string id, int x, int y, int width, int height,int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip) //ANIMATED IMAGE
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentFrame - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_TextureMap[id], &srcRect, &destRect, 0, 0, flip);
}
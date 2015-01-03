#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <iostream>
#include "SDL.h"

class Gameobject
{
public:

	void Load(int x, int y, int width, int height, std::string textureid);
	void Draw(SDL_Renderer* pRenderer);
	void Update();
	void Clean();

protected:

	std::string m_textureID;

	int m_currentFrame;
	int m_currentRow;

	int m_x;
	int m_y;

	int m_width;
	int m_height;
};

#endif //Gameobject - Define
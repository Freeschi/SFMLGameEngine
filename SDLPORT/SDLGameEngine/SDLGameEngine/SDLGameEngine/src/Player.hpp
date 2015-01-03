#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Gameobject.hpp"

class Player : public Gameobject
{
public:
	void Load(int x, int y, int width, int height, std::string textureID);
	void Draw(SDL_Renderer* pRenderer);
	void Update();
	void Clean();
};


#endif // PLAYER - Define
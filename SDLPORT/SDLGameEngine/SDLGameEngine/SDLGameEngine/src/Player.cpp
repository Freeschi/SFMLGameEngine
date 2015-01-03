#include "Player.hpp"

void Player::Load(int x, int y, int width, int height, std::string textureID) 
{ 
	Gameobject::Load(x, y, width, height, textureID); 
}

void Player::Draw(SDL_Renderer* pRenderer)
{
	Gameobject::Draw(pRenderer);
}

void Player::Update()
{
	m_x -= 1;
}
#include "Player.hpp"

Player::Player(const Loaderparams* pParams) : SDLGameobject(pParams)
{

}

void Player::Draw()
{
	SDLGameobject::Draw();
}

void Player::Update()
{
	m_x -= 1;
	//m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Player::Clean()
{

}
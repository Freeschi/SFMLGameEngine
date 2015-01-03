#include "Gameobject.hpp"
#include "Texturemanager.hpp"

void Gameobject::Load(int x, int y, int width, int height, std::string textureID)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_textureID = textureID;

	m_currentRow = 1;
	m_currentFrame = 1;
}

void Gameobject::Draw(SDL_Renderer* pRenderer)
{
	g_pTexturemanager->DrawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, pRenderer);
}

void Gameobject::Update()
{
	m_x += 1;
}
#include "SDLGameobject.hpp"
#include "Texturemanager.hpp"
#include "Framework.hpp"

SDLGameobject::SDLGameobject(const Loaderparams* pParams) : Gameobject(pParams)
{
	m_x = pParams->GetX();
	m_y = pParams->GetY();
	m_width = pParams->GetWidth();
	m_height = pParams->GetHeight();
	m_TextureID = pParams->GetTextureID();

	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLGameobject::Draw()
{
	g_pTexturemanager->DrawFrame(m_TextureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, g_pFramework->GetRenderer());
}

void SDLGameobject::Update()
{

}

void SDLGameobject::Clean()
{

}
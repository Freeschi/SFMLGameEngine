#ifndef SDLGAMEOBJECT_HPP
#define SDLGAMEOBJECT_HPP

#include "Gameobject.hpp"
#include "Loaderparams.hpp"
#include <string>

class SDLGameobject : public Gameobject
{
public: 

	SDLGameobject(const Loaderparams* pParams);

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

protected:

	int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	std::string m_TextureID;
};

#endif //SDLGAMEOBJECT - Define
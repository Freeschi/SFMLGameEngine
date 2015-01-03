#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <vector>
#include <iostream>
#include "SDLGameobject.hpp"
#include "Player.hpp"
#include "Singleton.hpp"
#include "SDL.h"
#include "SDL_image.h"


#define g_pFramework Framework::Get ()

class Framework : public TSingleton<Framework>
{
public:
	Framework() {}
	~Framework() {}

	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);

	//Base Functions
	void Render();
	void Update();
	void HandleEvents();
	void Clean();

	//m_bRunning Getter
	bool IsRunning() { return m_bRunning; }

	int SetCurrentFrame(int frame) { m_CurrentFrame = frame;  }
	int GetCurrentFrame() { return m_CurrentFrame; }

	SDL_Renderer* GetRenderer() const { return m_pRenderer; }

private:

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;
	int m_CurrentFrame;

	

	std::vector<SDLGameobject*> m_GameObjects;
	

};



#endif //FRAMEWORK_HPP - Define
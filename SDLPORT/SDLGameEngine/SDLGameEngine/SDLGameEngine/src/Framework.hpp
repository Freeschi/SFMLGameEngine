#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include "SDL.h"
#include <iostream>

class Framework
{
public:
	Framework() {}
	~Framework() {}

	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);

	//Base Functions
	void Render();
	//void Update();
	void HandleEvents();
	void Clean();

	//m_bRunning Getter
	bool IsRunning() { return m_bRunning; }

private:

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;

};



#endif //FRAMEWORK_HPP - Define
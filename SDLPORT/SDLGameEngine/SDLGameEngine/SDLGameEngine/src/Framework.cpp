#include "Framework.hpp"
#include "Texturemanager.hpp"

bool Framework::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "[SDL] Init success\n"; // Everything is good with SDL2
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags); //Create the SDL2 Window

		if (m_pWindow != 0) // Window init success
		{
			std::cout << "[SDL] Window successfully created\n"; //Everything is good with SDL2 Window
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0)
			{
				std::cout << "[SDL] Renderer successfully created\n"; //Everything is good with SDL2 Renderer
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "[SDL] Renderer creation failed\n"; //SDL2 Renderer has a problem
				return false; //SDL2 Renderer failed
			}
		}
		else
		{
			std::cout << "[SDL] Window creation failed\n"; //SDL2 Window has a problem
			return false; //SDL2 Window failed
		}
	}
	else
	{
		std::cout << "[SDL] Init failed\n"; //SDL2 Init has a problem
		return false; //SDL2 Init failed
	}
	std::cout << "[FREESCHI] Main-Init success\n"; //Main-Init completed
	m_bRunning = true; //All working start the looooooooooooooop!

	g_pTexturemanager->Load("Data/test.png", "Test", m_pRenderer);
	
	m_go.Load(100, 100, 128, 82, "Test");
	m_player.Load(300, 300, 128, 82, "Test");
	
	return true;
}

void Framework::Render()
{
	SDL_RenderClear(m_pRenderer); //Clear

	m_go.Draw(m_pRenderer); 
	m_player.Draw(m_pRenderer);


	SDL_RenderPresent(m_pRenderer); //Draw
}

void Framework::Update()
{
	m_go.Update();
	m_player.Update();
}
void Framework::Clean()
{
	std::cout << "[FREESCHI] Cleaning...\n";
	g_pTexturemanager->Clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
	
}

void Framework::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;

		default:
			break;
		}
	}
}
#include <iostream>
#include "Framework.hpp"


int main(int argc, char* argv[])
{
	g_pFramework->Init("Freeschi SDL Port", 100, 100, 640, 480, 0);

	while (g_pFramework->IsRunning())
	{
		g_pFramework->HandleEvents();
		g_pFramework->Update();
		g_pFramework->Render();

		SDL_Delay(10);
	}

	g_pFramework->Clean();

	return 0;
}
#include <iostream>
#include "Framework.hpp"

Framework* Application = nullptr;

int main(int argc, char* argv[])
{
	Application = new Framework();
	Application->Init("Freeschi SDL Port", 100, 100, 640, 480, 0);

	while (Application->IsRunning())
	{
		Application->HandleEvents();
		//Application->Update();
		Application->Render();
	}

	Application->Clean();

	return 0;
}
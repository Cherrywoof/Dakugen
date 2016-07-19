#include "MainScript.h"

void main_script()
{
	CWindow* window = window_create();

	bool quit = false;
	while (!quit)
	{
		SDL_Event close;
		while (SDL_PollEvent(&close) != 0)
		{
			if (close.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
	// Deallocate memory before the shit hits the fan
	window->DeAlloc();
}

CWindow* window_create()
{
	const int SCREEN_WIDTH = 600;
	const int SCREEN_HEIGHT = 480;

	// Create a window class and open a window
	CWindow window;
	std::cout << "Creating window.." << std::endl;
	window.CreateRenderWindow("MIKO PLEASE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, VSYNC::ON, SDL_WINDOW_SHOWN);

	return &window;
}
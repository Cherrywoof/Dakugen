#include "CWindow.h" // This is just here for clarity as CEnemy already loads CWindow, but thanks to header guards it won't scramble our code
#include "CEnemy.h"

int main(int argc, char* args[])
{
	const int SCREEN_WIDTH = 600;
	const int SCREEN_HEIGHT = 480;

	// Create a window class and open a window
	CWindow window;
	std::cout << "Creating window.." << std::endl;
	window.CreateRenderWindow("MIKO PLEASE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, VSYNC::ON, SDL_WINDOW_SHOWN);

	const int MIKO_IDLE = 4;     // Amount of frames in Miko's idle animation
	const int MIKO_WIDTH = 100;  // Dimensions per frame in pixels
	const int MIKO_HEIGHT = 100;
	const int IDLE_X = 0;        // Starting point coordinates for idle animation
	const int IDLE_Y = 0;

	CEnemy miko;                           // Create our enemy object - in this case she is a boss
	miko.SetWindow(&window);               // Tell the object which window we're using, renderer is automatically set
	miko.SetAnimFrames(MIKO_IDLE, 10);     // This second value is the speed at which we want the animation to play; 10 means 6 animations per second
	SDL_Rect clipSize[MIKO_IDLE];          // We'll use 4 frames in her spritesheet
	miko.SetClipRect(clipSize, MIKO_WIDTH,
		     MIKO_HEIGHT, IDLE_X, IDLE_Y); // Create a rectangle for each clip we'll be using

	miko.LoadFromFile("img/sprite/miko.png");
	miko.CreateClip();                     // Miko only has 4 frames for her idle animation, 
										   // and it starts at xy = 0, so we only input her animation count

	int miko_x;  // Predefining variables for Miko's coordinates
	int miko_y;

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
		miko_x = (window.GetWidth() - miko.GetClipWidth()) / 2;   // By updating this here, Miko will always be at the center of the window
		miko_y = (window.GetHeight() - miko.GetClipHeight()) / 2; // Even if the window's size changes somehow
		miko.RenderSprite(miko_x, miko_y);
	}
	// Deallocate memory before the shit hits the fan
	window.DeAlloc();
	miko.DeAllocAll();
	return 0;
}
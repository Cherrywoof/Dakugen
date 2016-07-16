#include <iostream>
#include <string.h>
#include <SDL.h>
#include "CWindow.h"
#include "CTexture.h"
#include "CRenderSprite.h"

using namespace std;

int main(int argc, char* args[])
{
	const int SCREEN_WIDTH = 600;
	const int SCREEN_HEIGHT = 480;
	const int MIKO_IDLE_FRAMES = 4;

	// Create a window class and open a window
	CWindow window;
	cout << "Creating window.." << endl;
	window.CreateRenderWindow("MIKO PLEASE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, VSYNC::ON, SDL_WINDOW_SHOWN);


		CTexture sMikoTex;                                  // Create an object for the sprite's texture
		sMikoTex.LoadFromFile("img/sprite/miko.png", window.GetRenderer()); // Load spritesheet onto renderer
		SDL_Rect clipSize[MIKO_IDLE_FRAMES];                // We'll use 4 frames in her spritesheet
		sMikoTex.SetClipRect(clipSize);                     // Load in our clip's size
		sMikoTex.SpriteClips(MIKO_IDLE_FRAMES);             // Create clips of the sprite with aforementioned values

		CRenderSprite sMiko;                                // We want to be rendering Toyosatomimi no Miko
		sMiko.SetRenAndWin(window.GetRenderer(), window);   // Link renderer and window to object
		sMiko.SetSprite(sMikoTex);
		sMiko.animFrames = MIKO_IDLE_FRAMES;
		sMiko.animPerSecond = 10;                           // This number just happens to look the smoothest while animating. 
		sMiko.SetClips(sMikoTex.GetClip());

		
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
			sMiko.RenderSprite();
		}
		// Deallocate memory before the shit hits the fan
		window.DeAlloc();
		sMikoTex.DeAlloc();

	return 0;
}
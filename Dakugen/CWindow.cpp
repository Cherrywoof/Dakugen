/* Class for creating windows using SDL. Will initialize SDL, a window and the renderer, *
 * set texture filtering, and enable or disable vsync. On exiting, will destroy all      *
 * allocated memory.															         */

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "CWindow.h"


using namespace std;

CWindow::CWindow() : mWindowWidth(640), mWindowHeight(480)
{
}

CWindow::~CWindow()
{
//	DeAlloc(); Dealloacte manually to prevent renderer destruction at end of a function
}

void CWindow::DeAlloc()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mRenderer = nullptr;
	mWindow = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
}

void CWindow::InitSDL()
{
	if (!mInitCheck) //Make sure SDL doesn't initialize twice in the same program
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		}

		cout << "Initialized SDL.\n";
		mInitCheck = true;
	}

	else { cout << "SDL has already been initalized!\n"; }

}

void CWindow::InitRenderer(VSYNC syncState)
{
	int hex_Max = 0xFF;

	cout << "VSync is " << (syncState == VSYNC::ON ? "on." : "off.") << endl;

	//GPU accelerated renderer with option vSync enabled
	mRenderer = SDL_CreateRenderer(mWindow, -1, syncState == VSYNC::ON ? SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC : SDL_RENDERER_ACCELERATED);
	if (mRenderer == nullptr)
	{
		cout << "Could not initialize renderer! SDL Error: " << SDL_GetError() << endl;
	}
	// Maxes out the settings for a white opaque bg
	SDL_SetRenderDrawColor(mRenderer, hex_Max, hex_Max, hex_Max, hex_Max); 

	int imgFlags = IMG_INIT_PNG;
	if (!IMG_Init(imgFlags) &imgFlags)
	{
		cout << "Could not initialize PNG loader! SDL_Image Error: " << IMG_GetError() << endl;
	}

}

SDL_Renderer* CWindow::GetRenderer()
{
	return mRenderer;
}

void CWindow::CreateRenderWindow(const char* title, int posX, int posY, const int &C_WIDTH, const int &C_HEIGHT, VSYNC syncState, Uint32 flags)
{
	InitSDL();
	mWindowWidth = C_WIDTH;
	mWindowHeight = C_HEIGHT;

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		cout << "Warning: Linear texture filtering not enabled.\n";
	}

	mWindow = SDL_CreateWindow(title, posX, posY, mWindowWidth, mWindowHeight, SDL_WINDOW_OPENGL);
	if (mWindow == nullptr)
	{
		cout << "Could not create window! SDL Error: " << SDL_GetError() << endl;
	}

	InitRenderer(syncState);

	cout << "Render window successfully created.\n";
}

int CWindow::GetWidth()
{
	return mWindowWidth;
}

int CWindow::GetHeight()
{
	return mWindowHeight;
}

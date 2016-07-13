#include <iostream>
#include <string.h>
#include <vector>
#include <SDL.h>
#include "CWindow.h"
#include "CTexture.h"
#include "CRenderSprite.h"

using namespace std;

CRenderSprite::CRenderSprite() : maxHex(0xFF)
{
}

CRenderSprite::~CRenderSprite()
{
}

void CRenderSprite::SetRenAndWin(SDL_Renderer* ren, CWindow win)
{
	sRenderer = ren;
	cWindow = win;
}

void CRenderSprite::RenderSprite(CTexture* cSprite, SDL_Renderer* sRenderer)
{
	//Clear screen
	SDL_SetRenderDrawColor(sRenderer, maxHex, maxHex, maxHex, maxHex);
	SDL_RenderClear(sRenderer);

	//Render current frame
	SDL_Rect* currentClip = &mClips[(++frame / animPerSecond) % animFrames];
	cSprite->render((cWindow.GetWidth() - currentClip->w) / 2, (cWindow.GetHeight() - currentClip->h) / 2, currentClip, sRenderer);

	//Update screen
	SDL_RenderPresent(sRenderer);
}

void CRenderSprite::LoadSprite(CTexture cSprite, string path)
{
	// Create a texture class and load a sprite onto it
	cout << "Loading sprite..." << endl;
	cSprite.LoadFromFile(path.c_str(), sRenderer);
	cout << "Successfully loaded sprite." << endl;
}

void CRenderSprite::SpriteClips()
{
	for (int i = 0; i < (animFrames - 1); i++)
	{
		int count = 100 * i;

		mClips[i].x = count;
		mClips[i].y = 0;
		mClips[i].w = 100;
		mClips[i].h = 100;

	}
}
/*
void CRenderSprite::InitLoop()
{
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
		RenderSprite();
	}
}
*/
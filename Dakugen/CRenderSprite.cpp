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
	mRenderer = ren;
	mWindow = win;
}

void CRenderSprite::SetSprite(CTexture &sprite)
{
	// Assign sprite
	mSprite = sprite;

	//Get dimensions
	iWidth = mSprite.GetWidth(); // Image dimensions
	iHeight = mSprite.GetHeight();
	sWidth = mWindow.GetWidth(); // Window (screen) dimensions
	sHeight = mWindow.GetHeight();
}

void CRenderSprite::SetClips(SDL_Rect* clips)
{
	mClips = clips;
}

void CRenderSprite::SetInitCoords(int x, int y)
{
	xCoord = x; 
	yCoord = y;
}

void CRenderSprite::RenderSprite()
{
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, maxHex, maxHex, maxHex, maxHex);
	SDL_RenderClear(mRenderer);

	// Create clip from our clip array
	SDL_Rect* currentClip = &mClips[(++frame / animPerSecond) % animFrames];

	//Set rendering space and clip rendering dimensions
	SDL_Rect renderQuad = { xCoord, yCoord, iWidth, iHeight };
	renderQuad.w = currentClip->w;
	renderQuad.h = currentClip->h;

	//Render to screen
	SDL_RenderCopy(mRenderer, mSprite.GetTexture(), currentClip, &renderQuad);

	//Update screen
	SDL_RenderPresent(mRenderer);
}

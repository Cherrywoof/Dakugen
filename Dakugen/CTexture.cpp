/* Class for loading and handling textures using SDL. Will initialize SDL_Image,           *
 * load an image from the specified path, get the image's dimensions, deallocate textures  *
 * when not needed anymore, and render the textures at any given point within the window.  */

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "CTexture.h"

using namespace std;

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
//	DeAlloc(); Call this manually as well for the same reasons as listed in CWindow.cpp
}

void CTexture::DeAlloc()
{
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void CTexture::LoadFromFile(std::string path, SDL_Renderer* mRenderer)
{
	// Will automatically delete previous image if new image is called within the same class
	//DeAlloc();

	// Final texture
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		cout << "Unable to load image! SDL_Image error: " << IMG_GetError() << endl;
	}
	
	cout << "Image successfully loaded." << endl;

	//Create new texture from surface pixel
	newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
	if (newTexture == nullptr)
	{
		cout << "Unable to create texture from " << path.c_str() << ". SDL error: " << SDL_GetError() << endl;
	}

	cout << "Texture successfully created from \"" << path.c_str() << "\"" << endl;

	//Get image dimensions
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
	
	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	mTexture = newTexture;
}

void CTexture::render(int x, int y, SDL_Rect* clip, SDL_Renderer* mRenderer)
{
	//Set rendering space
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopy(mRenderer, mTexture, clip, &renderQuad);
}

int CTexture::GetWidth()
{
	return mWidth;
}

int CTexture::GetHeight()
{
	return mHeight;
}

SDL_Texture* CTexture::GetTexture()
{
	return mTexture;
}
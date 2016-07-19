/* Class for loading and handling textures using SDL. Will initialize SDL_Image,           *
 * load an image from the specified path, get the image's dimensions, deallocate textures  *
 * when not needed anymore, and render the textures at any given point within the window.  */

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
	DeAlloc();

	// Final texture
	SDL_Texture* newTexture = nullptr;

	// From here on we just load the surface and create a texture from it, 
	// filling our member variables with their appropriate values.
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		cout << "Unable to load image! SDL_Image error: " << IMG_GetError() << endl;
	}
	
	cout << "Image successfully loaded." << endl;

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

void CTexture::cStaticClip(int yCoord, int width, int height, int frames)
{
	for (int i = 0; i < (frames); i++)
	{
		                    // Only x needs to be multiplied since 
							// we're only doing animations horizontally
		mClips[i].x = width * i;
		mClips[i].y = yCoord;
		mClips[i].w = width;
		mClips[i].h = height;

	}
}

void CTexture::cDynamicClip(int xCoord, int yCoord, int width, int height, int frames)
{
	for (int i = 1; i < (frames); i++)
	{
		// Only x needs to be multiplied since 
		// we're only doing animations horizontally
		mClips[i - 1].x = (xCoord - width) + (width * i);
		mClips[i - 1].y = yCoord;
		mClips[i - 1].w = width;
		mClips[i - 1].h = height;

	}
}

void CTexture::SetClipRect(SDL_Rect* clip)
{
	mClips = clip;
}

int CTexture::GetWidth()
{
	return mWidth;
}

int CTexture::GetHeight()
{
	return mHeight;
}

SDL_Rect* CTexture::GetClip()
{
	return mClips;
}

SDL_Texture* CTexture::GetTexture()
{
	return mTexture;
}
/* Class for loading and handling textures using SDL. Will initialize SDL_Image,           *
 * load an image from the specified path, get the image's dimensions, deallocate textures  *
 * when not needed anymore, and render the textures at any given point within the window.  */

#include "CEnemy.h"

CEnemy::CEnemy() : m_maxHex(0xFF)
{
}

CEnemy::~CEnemy()
{
//	DeAllocAll(); Call this manually as well for the same reasons as listed in CWindow.cpp
}


void CEnemy::SetWindow(CWindow* win)
{
	mWindow = win;
	mRenderer = win->GetRenderer();

	m_sWidth = mWindow->GetWidth(); // We immediately set the window (screen) dimensions to prevent any hassle later on
	m_sHeight = mWindow->GetHeight();
}

void CEnemy::SetAnimFrames(int af, int aps)
{
	m_animFrames = af;
	m_animPerSecond = aps;
}

void CEnemy::SetClipRect(SDL_Rect* clip, int width, int height, int x, int y)
{
	mClips = clip;
	m_cWidth = width;
	m_cHeight = height;
	m_xCoord = x;
	m_yCoord = y;
}


void CEnemy::LoadFromFile(std::string path)
{
	// Will automatically delete previous image if new image is called within the same class
	DeAllocTex();

	// Final texture
	SDL_Texture* newTexture = nullptr;

	// From here on we just load the surface and create a texture from it, 
	// filling our member variables with their appropriate values.
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		std::cout << "Unable to load image! SDL_Image error: " << IMG_GetError() << std::endl;
	}
	
	std::cout << "Image successfully loaded." << std::endl;

	newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
	if (newTexture == nullptr)
	{
		std::cout << "Unable to create texture from " << path.c_str() << ". SDL error: " << SDL_GetError() << std::endl;
	}

	std::cout << "Texture successfully created from \"" << path.c_str() << "\"" << std::endl;

	//Get image dimensions
	m_iWidth = loadedSurface->w;
	m_iHeight = loadedSurface->h;
	
	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	mTexture = newTexture;
}

void CEnemy::CreateClip()
{

	if (m_xCoord == 0)
	{
		for (int i = 0; i < m_animFrames; i++)
		{
			// Only x needs to be multiplied since 
			// we're only doing animations horizontally
			mClips[i].x = m_cWidth * i;
			mClips[i].y = m_yCoord;
			mClips[i].w = m_cWidth;
			mClips[i].h = m_cHeight;

		}
	}
	else
	{
		for (int i = 1; i < (m_animFrames + 1); i++)
		{
			mClips[i - 1].x = (m_xCoord - m_cWidth) + (m_xCoord * i);
			mClips[i - 1].y = m_yCoord;
			mClips[i - 1].w = m_cWidth;
			mClips[i - 1].h = m_cHeight;

		}
	}
}

void CEnemy::RenderSprite(int xCoord, int yCoord)
{
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, m_maxHex, m_maxHex, m_maxHex, m_maxHex);
	SDL_RenderClear(mRenderer);

	// Create clip from our clip array
	SDL_Rect* currentClip = &mClips[(++m_frame / m_animPerSecond) % m_animFrames];

	//Set rendering space and clip rendering dimensions
	SDL_Rect renderQuad = { xCoord, yCoord, m_iWidth, m_iHeight };
	renderQuad.w = currentClip->w;
	renderQuad.h = currentClip->h;

	//Render to screen
	SDL_RenderCopy(mRenderer, mTexture, currentClip, &renderQuad);

	//Update screen
	SDL_RenderPresent(mRenderer);
}

int CEnemy::GetSheetWidth()
{
	return m_iWidth;
}

int CEnemy::GetSheetHeight()
{
	return m_iHeight;
}

int CEnemy::GetClipWidth()
{
	return m_cWidth;
}

int CEnemy::GetClipHeight()
{
	return m_cHeight;
}

SDL_Rect* CEnemy::GetClip()
{
	return mClips;
}

SDL_Texture* CEnemy::GetTexture()
{
	return mTexture;
}

void CEnemy::DeAllocTex()
{

	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		m_iWidth = 0;
		m_iHeight = 0;
	}
}

void CEnemy::DeAllocAll()
{
	SDL_DestroyTexture(mTexture);
	mTexture = nullptr;
	mClips = nullptr;
	mWindow = nullptr;
	mRenderer = nullptr;
	m_maxHex = 0;
	m_frame = 0;
	m_xCoord = 0;
	m_yCoord = 0;
	m_sWidth = 0;
	m_sHeight = 0;
	m_cWidth = 0;
	m_cHeight = 0;
	m_iWidth = 0;
	m_iHeight = 0;
}
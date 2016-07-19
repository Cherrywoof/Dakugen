#include "CBoss.h"

void CBoss::SetTexture(std::string path, CWindow* window)
{
	mWindow = window;
	CTexture sMikoTex;                                  // Create an object for the sprite's texture
	sMikoTex.LoadFromFile("img/sprite/miko.png",
		mWindow->GetRenderer());        // Load spritesheet onto renderer
}

void CBoss::CreateClip(SDL_Rect* clipSize)
{
	bTex->SetClipRect(clipSize);               // Load in our clip's size
	bTex->cStaticClip(frame_count, frame_y,
		        frame_width, frame_height);    // Create clips of the sprite with aforementioned values
}
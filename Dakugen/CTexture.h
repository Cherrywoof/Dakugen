#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class CTexture
{
public:
	CTexture();
	~CTexture();

	void LoadFromFile(std::string path, SDL_Renderer* mRenderer);        // Loads image from file at specified path. Accessed by Load() functions
	void SetClipRect(SDL_Rect* clip);                                    // Assigns formerly created SDL_Rect to mClips
	void cStaticClip(int yCoord, int width, int height, int frames = 1); // Creates clips from sheet within an array. For animations that start at the far left of the image.
	void cDynamicClip(int xCoord, int yCoord, int width, int height,
		                                                int frames = 1); // This function also creates clips, 
	void DeAlloc();                                                      // Deallocates memory
	int GetWidth();                                                      // Gets image dimensions
	int GetHeight();      
	SDL_Rect* GetClip();                                                 // Returns mClip
	SDL_Texture* GetTexture();                                           // Returns mTexture

private:
	SDL_Texture* mTexture;      // The actual hardware texture
	int mWidth;                 // Image dimensions
	int mHeight;
	SDL_Rect* mClips;           // Array that contains spritesheet clips

};

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

	void LoadFromFile(std::string path, SDL_Renderer* mRenderer);  // Loads image from file at specified path. Accessed by Load() functions
	void SetClipRect(SDL_Rect* clip);                              // Assigns formerly created SDL_Rect to mClips
	void SpriteClips(int frames = 1);                              // If image is a spritesheet, creates clips from sheet within an array
	void DeAlloc();                                                // Deallocates memory
	int GetWidth();                                                // Gets image dimensions
	int GetHeight();
	SDL_Rect* GetClip();
	SDL_Texture* GetTexture();                                     // Returns mTexture

private:
	SDL_Texture* mTexture;                                         // The actual hardware texture
	int mWidth;                                                    // Image dimensions
	int mHeight;
	SDL_Rect* mClips;                                              // Array that contains spritesheet clips

};

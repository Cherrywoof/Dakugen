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
	void render(int x, int y, SDL_Rect* clip = nullptr, 
		                      SDL_Renderer* mRenderer = nullptr);  // Renders texture at given point
	void DeAlloc();                                                // Deallocates memory
	int GetWidth();                                                // Gets image dimensions
	int GetHeight();
	SDL_Texture* GetTexture();                                     // Returns mTexture

private:
	SDL_Texture* mTexture;                                         // The actual hardware texture
	int mWidth;                                                    // Image dimensions
	int mHeight;

};

#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "CWindow.h"
#include "CTexture.h"

class CRenderSprite
{
public:
	CRenderSprite();
	~CRenderSprite();

	void SetRenAndWin(SDL_Renderer* ren, CWindow win);             // Links the renderer and window created within CWindow to CRenderSprite
	void SetSprite(CTexture &sprite);                              // Assigns sprite to texture object
	void LoadSprite(std::string path);                             // Loads sprite
	void SpriteClips();                                            // Creates clips from sprite
//	void InitLoop();                                               // Loop that keeps window running until closed
	void RenderSprite();                                           // Renders given sprite

	int animFrames;                                                // Number of frames required for a full animation loop
	int animPerSecond;                                             // This number will be used to calculate the speed of the animation loop
	SDL_Rect* mClips;                                              // Array to create clips of the spritesheet from

private:
	int maxHex;                                                    // Standard value for max hex value (0xFF, initialized in constructor)
	int frame;                                                     // Base frame counter
	SDL_Renderer* sRenderer;                                       // Must contain the renderer created through CWindow::CreateWindow();
	CWindow cWindow;                                               // Must contain the window created through CWindow::CreateWindow();
	CTexture cSprite;                                              // We use CTexture here to load the sprite through our functions.
};
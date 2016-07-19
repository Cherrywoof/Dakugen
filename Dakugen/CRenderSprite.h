#pragma once

#include "CWindow.h"
#include "CTexture.h"

class CRenderSprite
{
public:
	CRenderSprite();
	~CRenderSprite();

	void SetRenAndWin(SDL_Renderer* ren, CWindow win);  // Links the renderer and window created within CWindow to CRenderSprite
	void SetSprite(CTexture &sprite);                   // Assigns sprite to texture object
	void SetClips(SDL_Rect* clips);                     // Assigns clip array to mClips
	void SetInitCoords(int x, int y);                   // Sets initial coordinates for sprite (0,0 is top left of screen)
	void RenderSprite();                                // Renders current object's sprite

	int animFrames;                                     // Number of frames required for a full animation loop
	int animPerSecond;                                  // This number will be used to calculate the speed of the animation loop

private:
	int maxHex;              // Standard value for max hex value (0xFF, initialized in constructor)
	int frame;               // Base frame counter
	int xCoord;              // Object's coordinates within the given window
	int yCoord;
	int iWidth;              // Image dimensions
	int iHeight;
	int sWidth;              // Window (screen) dimensions
	int sHeight;

	SDL_Renderer* mRenderer; // Must contain the renderer created through CWindow::CreateWindow();
	CWindow mWindow;         // Must contain the window created through CWindow::CreateWindow();
	CTexture mSprite;        // We use CTexture here to load the sprite through our functions.
	SDL_Rect* mClips;        // Array that contains spritesheet clips
};
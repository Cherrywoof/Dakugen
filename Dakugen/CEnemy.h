#pragma once

class CEnemy
{
public:
	CEnemy();
	~CEnemy();

	void SetWindow(CWindow* win);                            // Links the renderer and window created within CWindow to CRenderSprite
	void SetAnimFrames(int af = 1, int aps = 1);             // Tells us how many frames are within our loop, and how fast to animate the sprite
	void SetClipRect(SDL_Rect* clip, int width, int height,  // Assigns formerly created SDL_Rect to mClips, as well as setting the
		                                     int x, int y);  // width and height of the sprite, and the starting coordinates of the first animation

	void LoadFromFile(std::string path);       // Loads image from file at specified path. Accessed by Load() functions
	void CreateClip();                         // Creates clips starting from the x and y coordinates provided
	void RenderSprite(int xCoord, int yCoord); // Renders current object's sprite

	void DeAllocAll();    // Deallocates all variables
	void DeAllocTex();    // Deallocates texture variables only
	int GetSheetWidth();  // Returns sheet dimensions
	int GetSheetHeight();      
	int GetClipWidth();   // Returns clip dimensions
	int GetClipHeight();
	SDL_Rect* GetClip();                                
	SDL_Texture* GetTexture();                          

private:
	int m_maxHex;            // Standard value for max hex value (0xFF, initialized in constructor)
	int m_frame;             // Base frame counter
	int m_animFrames;        // Number of frames required for a full animation loop
	int m_animPerSecond;     // This number will be used to calculate the speed of the animation loop

	int m_xCoord;            // Clip starting coordinates
	int m_yCoord;

	int m_sWidth;            // Window (screen) dimensions
	int m_sHeight;

	int m_iWidth;            // Spritesheet texture dimensions
	int m_iHeight;

	int m_cWidth;            // Clip dimensions
	int m_cHeight;

	SDL_Renderer* mRenderer; // Must contain the renderer created through CWindow::CreateWindow();
	SDL_Rect* mClips;        // Array that contains spritesheet clips
	CWindow* mWindow;        // Must contain the window created through CWindow::CreateWindow();
	SDL_Texture* mTexture;   // The actual hardware texture

};

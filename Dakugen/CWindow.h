#pragma once

/* Class for creating windows using SDL. Will initialize SDL, a window and the renderer, *
 * set texture filtering, and enable or disable vsync. On exiting, will destroy all      *
 * allocated memory.															         */


enum class VSYNC
{
	ON,
	OFF
	
};

class CWindow 
{
public:
	CWindow();

	~CWindow();  				 

	void CreateRenderWindow(const char* title, int posX, int posY, // Creates an SDL window.
		                  const int &C_WIDTH, const int &C_HEIGHT, // Use SDL_WINDOWPOS_UNDEFINED for default window positioning.
		                              VSYNC syncState = VSYNC::ON, // View SDL_CreateWindow documentation for info on flags.
		                                     Uint32 flags = NULL); // <<-- nullptr is incompatible here, so we use NULL.

	SDL_Renderer* GetRenderer();                                   // Returns a pointer to mRenderer, so the renderer can be accessed for 
	                                                               // other rendering functions.
                                                                   // Main game loop to run after window has been created. 
	int GetWidth();                                                // Returns window width
	int GetHeight();                                               // Returns window height
	void DeAlloc();                                                // Deallocates all memory and destroys variables used

private:
	void InitSDL();                                                // Initializes SDL. Will be called by CreateRenderWindow.
	void InitRenderer(VSYNC syncState = VSYNC::ON);                // Initializes the renderer. Will be called by CreateRenderWindow.

	bool mInitCheck;                                               // Ensures that SDL won't be initialized twice within the same class.
	int mWindowWidth;
	int mWindowHeight;

	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
};



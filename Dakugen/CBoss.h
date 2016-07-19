/* Class for creating boss objects. It's currently incomplete, only capable of defining  *
 * a boss and giving it a texture and animation. In the future it should also include    *
 * features such as defining the boss's HP and giving it a hitbox of variable size.      */

#pragma once

#include "CRenderSprite.h"

class CBoss
{
public:
	void SetTexture(std::string path, CWindow* window);
	void SetSpriteObj();

	void CreateClipFromTex(SDL_Rect* clip);
	void SetTexObjVals();
	void InitSpriteObj();

	CTexture* GetTexture();
	CRenderSprite* GetSprite();

private:
	CTexture* bTex;         
	CRenderSprite* bSprite;
	CWindow* mWindow;
	int frame_count;
	int frame_width;
	int frame_height;
	int frame_y;

};

void anim_Idle(CWindow* window)
{
	

	


	CRenderSprite sMikoSprite;                                // We want to be rendering Toyosatomimi no Miko
	sMikoSprite.SetRenAndWin(window->GetRenderer(), *window); // Link renderer and window to object
	sMikoSprite.SetSprite(sMikoTex);
	sMikoSprite.animFrames = IDLE_FRAME_COUNT;
	sMikoSprite.animPerSecond = 10;                           // This number just happens to look the smoothest while animating. 
	sMikoSprite.SetClips(sMikoTex.GetClip());
}

void renderAnim(CRenderSprite* sprite)
{
	sprite->RenderSprite();
}
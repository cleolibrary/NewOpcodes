#pragma once

#include "game_sa\CRect.h"
#include "CRGBA.h"

#define MAX_NO_SPRITES 200

#include "RenderWare.h"

class NOSprite
{
public:
	RwTexture *m_pTexture;
	CRect m_rect;
	CRGBA m_color[4];
	float m_angle;
	void Draw();
};

class SpriteDrawer
{
	NOSprite m_sprites[MAX_NO_SPRITES];
public:
	unsigned int m_numSpritesThisFrame;
	SpriteDrawer();
	void DrawSpriteThisFrame(RwTexture *texture, CRect const& rect, CRGBA const& color1, CRGBA const& color2, 
		CRGBA const& color3, CRGBA const& color4, float angle);
	void DrawSprites();
	void Reset();
};

extern SpriteDrawer spriteDrawer;
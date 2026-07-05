#pragma once

#include "game_sa\CFont.h"

#define MAX_NO_PRINTS 100

struct tFontPrint
{
	char m_text[100];
	float m_fX, m_fY;
	float m_fWidth, m_fHeight;
	unsigned char m_nStyle, m_nProp, m_nOutline, m_nShadow;
	unsigned char m_nJustify, m_nAlign, m_nBackground;
	CRGBA m_Color, m_DropColor, m_BackColor;
	float m_fWrap;
};

class TextDrawer
{
public:
	unsigned int m_dwNumPrintsThisFrame;
	tFontPrint m_aPrints[MAX_NO_PRINTS];
	void DrawPrints();
};

extern TextDrawer textDrawer;
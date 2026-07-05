#include "Text.h"
#include "TextDrawer.h"

// 0D65=6,print %1s% at %2d% %3d% scale %4d% %5d% style %6d%
// 0D65: print "Hello, world" at 50.0 50.0 scale 1.0 1.0 style FONT_GOTHIC
// PRINT_TEMPORARY_TEXT
OpcodeResult WINAPI Text::Print(CScriptThread* thread)
{
	OpcodeParams params(thread, 6);
	if(textDrawer.m_dwNumPrintsThisFrame < MAX_NO_PRINTS)
	{
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_text;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_fX;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_fY;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_fWidth;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_fHeight;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nStyle;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nProp = TRUE;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nAlign = ALIGN_LEFT;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_fWrap = 600.0f;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nJustify = FALSE;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_Color.r = 255;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_Color.g = 255;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_Color.b = 255;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_Color.a = 255;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nOutline = 1;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nShadow = 0;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_DropColor.r = 0;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_DropColor.g = 0;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_DropColor.b = 0;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_DropColor.a = 255;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nBackground = FALSE;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_BackColor.r = 0;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_BackColor.g = 0;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_BackColor.b = 0;
		textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_BackColor.a = 0;
		textDrawer.m_dwNumPrintsThisFrame++;
	}
	return OR_CONTINUE;
}

// 0D66=25,print %1s% at %2d% %3d% scale %4d% %5d% style %6d% prop %7d% align %8d% wrap %9d% justify %10d% color %11d% %12d% %13d% %14d% outline %15d% shadow %16d%
// dropColor %17d% %18d% %19d% %20d% background %21d% backColor %22d% %23d% %24d% %25d%
// 0D66: print "Hello, world" at 50.0 50.0 scale 1.0 1.0 style FONT_GOTHIC prop TRUE align ALIGN_LEFT wrap 600.0 justify FALSE color 255 255 255 255 outline 0 shadow 0
// dropColor 0 0 0 0 background FALSE backColor 0 0 0 0
// PRINT_TEMPORARY_TEXT_EX
OpcodeResult WINAPI Text::PrintEx(CScriptThread* thread)
{
	OpcodeParams params(thread, 25);
	if(textDrawer.m_dwNumPrintsThisFrame < MAX_NO_PRINTS)
	{
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_text;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_fX;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_fY;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_fWidth;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_fHeight;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nStyle;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nProp;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nAlign;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_fWrap;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nJustify;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_Color.r;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_Color.g;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_Color.b;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_Color.a;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nOutline;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nShadow;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_DropColor.r;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_DropColor.g;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_DropColor.b;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_DropColor.a;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_nBackground;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_BackColor.r;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_BackColor.g;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_BackColor.b;
		params >> textDrawer.m_aPrints[textDrawer.m_dwNumPrintsThisFrame].m_BackColor.a;
		textDrawer.m_dwNumPrintsThisFrame++;
	}
	return OR_CONTINUE;
}
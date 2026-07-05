#include "Sprite.h"
#include "SpriteDrawer.h"

// 0D7E=11,draw_sprite_with_texture %1d% at_cornerA %2d% %3d% cornerB %4d% %5d% color %6d% %7d% %8d% %9d% angle %10d%
// 0D7E: draw_sprite_with_texture 0@ at_cornerA 100.0 100.0 cornerB 300.0 300.0 color 255 255 255 255 angle 0.0
// SCR: DRAW_2D_SPRITE
OpcodeResult WINAPI Sprite::DrawSprite(CScriptThread* thread)
{
	OpcodeParams params(thread, 10);
	CRect rect; CRGBA color; float angle; unsigned int texture;
	params >> texture >> rect.left >> rect.top >> rect.right >> rect.bottom >> color >> angle;
	spriteDrawer.DrawSpriteThisFrame((RwTexture *)texture, rect, color, color, color, color, angle);
    return OR_CONTINUE;
}

// 0D7F=22,draw_gradient_sprite_with_texture %1d% at_cornerA %2d% %3d% cornerB %4d% %5d% colors %6d% %7d% %8d% %9d%  %10d% %11d% %12d% %13d%  %14d% %15d% %16d% %17d%  %18d% %19d% %20d% %21d% angle %22d%
// 0D7F: draw_gradient_sprite_with_texture 0@ at_cornerA 100.0 100.0 cornerB 300.0 300.0 colors 255 255 255 255  255 255 255 255  255 255 255 255  255 255 255 255 angle 0.0
// SCR: DRAW_2D_SPRITE_WITH_GRADIENT
OpcodeResult WINAPI Sprite::DrawSpriteWithGradient(CScriptThread* thread)
{
	OpcodeParams params(thread, 22);
	CRect rect; CRGBA color[4]; float angle; unsigned int texture;
	params >> texture >> rect.left >> rect.top >> rect.right >> rect.bottom >> color[0] >> color[1] >> color[2] >>
		color[3] >> angle;
	spriteDrawer.DrawSpriteThisFrame((RwTexture *)texture, rect, color[0], color[1], color[2], color[3], angle);
    return OR_CONTINUE;
}
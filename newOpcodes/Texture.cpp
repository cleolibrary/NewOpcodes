#include "Texture.h"
#include "TextureManager.h"

// 0D61=3, %3d% = load_texture_from %1s% with_mask %2s% // IF and SET
// 0D61: 0@ = load_texture_from "image.bmp" with_mask "imagea.bmp" // IF and SET
// SCR: LOAD_TEXTURE_FROM_BMP_FILE
OpcodeResult WINAPI Texture::LoadBMPTextureWithAlpha(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	char image[128], mask[128];
	params >> image >> mask;
	RwTexture *texture = TexMgr.LoadMaskedTextureFromBMPFile(image, *mask == '\0'? NULL : mask);
	params << texture << (texture? orTrue : orFalse);
    return OR_CONTINUE;
}

// 0D64=2, %2d% = load_texture_png_from %1s% // IF and SET
// 0D64: 0@ = load_texture_png_from "image.png" // IF and SET
// SCR: LOAD_TEXTURE_FROM_PNG_FILE
OpcodeResult WINAPI Texture::LoadPNGTexture(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	char image[128];
	params >> image;
	RwTexture *texture = TexMgr.LoadTextureFromPNGFile(image);
	params << texture << (texture? orTrue : orFalse);
    return OR_CONTINUE;
}

// 0D7C=2, %2d% = load_texture_dds_from %1s% // IF and SET
// 0D7C: 0@ = load_texture_dds_from "image.dds" // IF and SET
// SCR: LOAD_TEXTURE_FROM_DDS_FILE
OpcodeResult WINAPI Texture::LoadDDSTexture(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	char image[128];
	params >> image;
	RwTexture *texture = TexMgr.LoadTextureFromDDSFile(image);
	params << texture << (texture? orTrue : orFalse);
    return OR_CONTINUE;
}

// 0D7D=1, clean_loaded_texture %1d%
// 0D7D: clean_loaded_texture 0@
// SCR: CLEAN_LOADED_TEXTURE
OpcodeResult WINAPI Texture::UnloadTexture(CScriptThread* thread)
{
	OpcodeParams params(thread, 1);
	unsigned int tex;
	params >> tex;
	TexMgr.UnloadTexture((RwTexture *)tex);
    return OR_CONTINUE;
}
#pragma once

#define MAX_NO_TEXTURES 500

#include "RenderWare.h"

class TextureManager
{
	RwTexture *m_apTextures[MAX_NO_TEXTURES];
public:
	RwTexture *LoadTextureFromPNGFile(char *path);
	RwTexture *LoadMaskedTextureFromBMPFile(char *imagePath, char *maskPath);
	RwTexture *LoadTextureFromDDSFile(char *path);
	void UnloadTexture(RwTexture *texture);
	void UnloadAllTextures();
};

extern TextureManager TexMgr;
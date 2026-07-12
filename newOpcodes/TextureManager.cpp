#include "TextureManager.h"
#include <cstring>

TextureManager TexMgr;

RwTexture *TextureManager::LoadTextureFromPNGFile(char *path)
{
	RwInt32 width, height, depth, flags; RwImage *image; char fileName[_MAX_FNAME];
	RwRaster *raster; RwTexture **freeTex = NULL;
	for(int i = 0; i < MAX_NO_TEXTURES; i++)
	{
		if(!m_apTextures[i])
		{
			freeTex = &m_apTextures[i];
			break;
		}
	}
	if(freeTex)
	{
		image = RtPNGImageRead(path);
		if(image)
		{
			RwImageFindRasterFormat(image, 4, &width, &height, &depth, &flags);
			raster = RwRasterCreate(width, height, depth, flags);
			RwRasterSetFromImage(raster, image);
			RwImageDestroy(image);
			*freeTex = RwTextureCreate(raster);
			_splitpath(path, NULL, NULL, fileName, NULL);
			strcpy((*freeTex)->name, fileName);;
			return *freeTex;
		}
	}
	return NULL;
}

RwTexture *TextureManager::LoadMaskedTextureFromBMPFile(char *imagePath, char *maskPath)
{
	RwInt32 width, height, depth, flags; RwImage *image, *mask; char fileName[_MAX_FNAME];
	RwRaster *raster; RwTexture **freeTex = NULL;
	for(int i = 0; i < MAX_NO_TEXTURES; i++)
	{
		if(!m_apTextures[i])
		{
			freeTex = &m_apTextures[i];
			break;
		}
	}
	if(freeTex)
	{
		image = RtBMPImageRead(imagePath);
		if(!image)
			return NULL;
		if(maskPath && *maskPath != '\0')
		{
			mask = RtBMPImageRead(maskPath);
			if(mask)
			{
				RwImageMakeMask(mask);
				RwImageApplyMask(image, mask);
				RwImageDestroy(mask);
			}
		}
		RwImageFindRasterFormat(image, 4, &width, &height, &depth, &flags);
		raster = RwRasterCreate(width, height, depth, flags);
		RwRasterSetFromImage(raster, image);
		RwImageDestroy(image);
		*freeTex = RwTextureCreate(raster);
		_splitpath(imagePath, NULL, NULL, fileName, NULL);
		strcpy((*freeTex)->name, fileName);;
		return *freeTex;
	}
	else return NULL;
}

RwTexture *TextureManager::LoadTextureFromDDSFile(char *path)
{
	char fileName[_MAX_FNAME], texPath[_MAX_PATH]; RwTexture **freeTex = NULL; RwTexture *rwTex;
	for(int i = 0; i < MAX_NO_TEXTURES; i++)
	{
		if(!m_apTextures[i])
		{
			freeTex = &m_apTextures[i];
			break;
		}
	}
	if(freeTex)
	{
		size_t pathLen = strnlen_s(path, _MAX_PATH);
		if(pathLen < 4 || pathLen == _MAX_PATH)
			return NULL;
		memcpy(texPath, path, pathLen - 4);
		texPath[pathLen - 4] = '\0';
		rwTex = RwD3D9DDSTextureRead(texPath, NULL);
		if(rwTex)
		{
			*freeTex = rwTex;
			_splitpath(path, NULL, NULL, fileName, NULL);
			strcpy((*freeTex)->name, fileName);;
			return *freeTex;
		}
	}
	return NULL;
}

void TextureManager::UnloadTexture(RwTexture *texture)
{
	if(!texture)
		return;
	for(int i = 0; i < MAX_NO_TEXTURES; i++)
	{
		if(m_apTextures[i] == texture)
		{
			RwTextureDestroy(texture);
			m_apTextures[i] = NULL;
			break;
		}
	}
}

void TextureManager::UnloadAllTextures()
{
	for(int i = 0; i < MAX_NO_TEXTURES; i++)
		UnloadTexture(m_apTextures[i]);
}
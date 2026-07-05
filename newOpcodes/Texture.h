#pragma once

#include "OpcodeParams.h"

class Texture
{
public:
	static OpcodeResult WINAPI LoadBMPTextureWithAlpha(CScriptThread* thread);
	static OpcodeResult WINAPI LoadPNGTexture(CScriptThread* thread);
	static OpcodeResult WINAPI LoadDDSTexture(CScriptThread* thread);
	static OpcodeResult WINAPI UnloadTexture(CScriptThread* thread);
};
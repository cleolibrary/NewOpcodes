#pragma once

#include "OpcodeParams.h"

class Sprite
{
public:
	static OpcodeResult WINAPI DrawSprite(CScriptThread* thread);
	static OpcodeResult WINAPI DrawSpriteWithGradient(CScriptThread* thread);
};
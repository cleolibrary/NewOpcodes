#pragma once

#include "OpcodeParams.h"

class Colpoint
{
public:
	static OpcodeResult WINAPI GetCollisionBetweenPoints(CScriptThread* thread);
	static OpcodeResult WINAPI GetNormal(CScriptThread* thread);
	static OpcodeResult WINAPI GetSurface(CScriptThread* thread);
	static OpcodeResult WINAPI GetLighting(CScriptThread* thread);
	static OpcodeResult WINAPI GetDepth(CScriptThread* thread);
};
#pragma once

#include "OpcodeParams.h"

class Vector
{
public:
	static OpcodeResult WINAPI Normalise(CScriptThread* thread);
	static OpcodeResult WINAPI Setup(CScriptThread* thread);
	static OpcodeResult WINAPI GetValues(CScriptThread* thread);
};
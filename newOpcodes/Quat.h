#pragma once

#include "OpcodeParams.h"

class Quat
{
public:
	static OpcodeResult WINAPI FromMatrix(CScriptThread* thread);
	static OpcodeResult WINAPI Rotate(CScriptThread* thread);
	static OpcodeResult WINAPI Normalise(CScriptThread* thread);
	static OpcodeResult WINAPI Multiply(CScriptThread* thread);
	static OpcodeResult WINAPI Slerp(CScriptThread* thread);
	static OpcodeResult WINAPI Setup(CScriptThread* thread);
	static OpcodeResult WINAPI GetValues(CScriptThread* thread);
};
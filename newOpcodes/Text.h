#pragma once

#include "OpcodeParams.h"

class Text
{
public:
	static OpcodeResult WINAPI Print(CScriptThread* thread);
	static OpcodeResult WINAPI PrintEx(CScriptThread* thread);
};
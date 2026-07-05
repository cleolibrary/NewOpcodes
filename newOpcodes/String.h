#pragma once

#include "OpcodeParams.h"

class String
{
public:
	static OpcodeResult WINAPI StrCmp(CScriptThread* thread);
	static OpcodeResult WINAPI StrCat(CScriptThread* thread);
	static OpcodeResult WINAPI StrStr(CScriptThread* thread);
	static OpcodeResult WINAPI StrLen(CScriptThread* thread);
	static OpcodeResult WINAPI StrCpy(CScriptThread* thread);
};
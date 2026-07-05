#pragma once

#include "OpcodeParams.h"

class Memory
{
public:
	static OpcodeResult WINAPI MemCpy(CScriptThread* thread);
	static OpcodeResult WINAPI SetStructParam(CScriptThread* thread);
	static OpcodeResult WINAPI GetStructParam(CScriptThread* thread);
	static OpcodeResult WINAPI SetStructOffset(CScriptThread* thread);
	static OpcodeResult WINAPI GetStructOffset(CScriptThread* thread);
};
#pragma once

#include "OpcodeParams.h"

class Txd
{
public:
	static OpcodeResult WINAPI LoadTxd(CScriptThread* thread);
	static OpcodeResult WINAPI GetTxdId(CScriptThread* thread);
	static OpcodeResult WINAPI FindTextureInTxdWithName(CScriptThread* thread);
	static OpcodeResult WINAPI FindTextureInTxdWithId(CScriptThread* thread);
};
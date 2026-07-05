#pragma once

#include "OpcodeParams.h"

class CLEOAudio
{
public:
	static OpcodeResult WINAPI SetAudioStreamPos(CScriptThread* thread);
	static OpcodeResult WINAPI GetAudioStreamPos(CScriptThread* thread);
	static OpcodeResult WINAPI SetAudiStreamEffect(CScriptThread* thread);
	static OpcodeResult WINAPI RemoveAudioStreamEffect(CScriptThread* thread);
	static OpcodeResult WINAPI SetEffectParameters(CScriptThread* thread);
	static OpcodeResult WINAPI GetEffectParameters(CScriptThread* thread);
	static OpcodeResult WINAPI ResetEffect(CScriptThread* thread);
	static OpcodeResult WINAPI SetAudioStreamAttribute(CScriptThread* thread);
	static OpcodeResult WINAPI GetAudioStreamAttribute(CScriptThread* thread);
	static OpcodeResult WINAPI Set3DAudioStreamAttributes(CScriptThread* thread);
	static OpcodeResult WINAPI Get3DAudioStreamAttributes(CScriptThread* thread);
};
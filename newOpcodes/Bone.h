#pragma once

#include "OpcodeParams.h"

class Bone
{
public:
	static OpcodeResult WINAPI GetMatrix(CScriptThread* thread);
	static OpcodeResult WINAPI GetBone(CScriptThread* thread);
	static OpcodeResult WINAPI GetBoneOffset(CScriptThread* thread);
	static OpcodeResult WINAPI GetBoneQuat(CScriptThread* thread);
};
#pragma once

#include "OpcodeParams.h"

class Matrix
{
public:
	static OpcodeResult WINAPI Multiply(CScriptThread* thread);
	static OpcodeResult WINAPI RotateOnAxis(CScriptThread* thread);
	static OpcodeResult WINAPI GetXAngle(CScriptThread* thread);
	static OpcodeResult WINAPI GetYAngle(CScriptThread* thread);
	static OpcodeResult WINAPI GetZAngle(CScriptThread* thread);
	static OpcodeResult WINAPI SetPosn(CScriptThread* thread);
	static OpcodeResult WINAPI GetPosn(CScriptThread* thread);
	static OpcodeResult WINAPI GetLocalOffset(CScriptThread* thread);
	static OpcodeResult WINAPI Rotate(CScriptThread* thread);
	static OpcodeResult WINAPI Copy(CScriptThread* thread);
	static OpcodeResult WINAPI TransformPoint(CScriptThread* thread);
	static OpcodeResult WINAPI RotateX(CScriptThread* thread);
	static OpcodeResult WINAPI RotateY(CScriptThread* thread);
	static OpcodeResult WINAPI RotateZ(CScriptThread* thread);
	static OpcodeResult WINAPI FromQuat(CScriptThread* thread);
	static OpcodeResult WINAPI Slerp(CScriptThread* thread);
	static OpcodeResult WINAPI Setup(CScriptThread* thread);
};
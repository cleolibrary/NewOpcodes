#pragma once

#include "OpcodeParams.h"

class Shape
{
public:
	static OpcodeResult WINAPI DrawShape(CScriptThread* thread);
	static OpcodeResult WINAPI SetShapeVertex(CScriptThread* thread);
	static OpcodeResult WINAPI RotateShapeVertices(CScriptThread* thread);
};
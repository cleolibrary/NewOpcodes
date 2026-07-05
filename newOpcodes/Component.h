#pragma once

#include "OpcodeParams.h"

class Component
{
public:
	static OpcodeResult WINAPI GetMatrix(CScriptThread* thread);
	static OpcodeResult WINAPI FindComponent(CScriptThread* thread);
	static OpcodeResult WINAPI SetComponentState(CScriptThread* thread);
	static OpcodeResult WINAPI SetComponentModelAlpha(CScriptThread* thread);
	static OpcodeResult WINAPI GetChildComponent(CScriptThread* thread);
	static OpcodeResult WINAPI GetNextComponent(CScriptThread* thread);
	static OpcodeResult WINAPI GetName(CScriptThread* thread);
	static OpcodeResult WINAPI GetLTM(CScriptThread* thread);
	static OpcodeResult WINAPI GetMM(CScriptThread* thread);
	static OpcodeResult WINAPI GetParentComponent(CScriptThread* thread);
	static OpcodeResult WINAPI GetComponentNumObjects(CScriptThread* thread);
	static OpcodeResult WINAPI GetComponentObject(CScriptThread* thread);
	static OpcodeResult WINAPI HideObjectAtomic(CScriptThread* thread);
	static OpcodeResult WINAPI GetObjectAtomicFlag(CScriptThread* thread);
	static OpcodeResult WINAPI SetObjectAtomicFlag(CScriptThread* thread);
	static OpcodeResult WINAPI GetObjectAtomicNumMaterials(CScriptThread* thread);
	static OpcodeResult WINAPI GetObjectMaterialTexture(CScriptThread* thread);
};
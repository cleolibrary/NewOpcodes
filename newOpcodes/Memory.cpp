#include "Memory.h"

// 0D27=3,copy_memory_from %1d% to %2d% size %3d%
// 0D27: copy_memory_from 0@ to 1@ size 32
// SCR: MEMCPY
OpcodeResult WINAPI Memory::MemCpy(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	void *src, *dst; unsigned int size;
	params >> src >> dst >> size;
	memcpy(dst, src, size);
    return OR_CONTINUE;
}

// 0D37=3,struct %1d% param %2d% = %3d%
// 0D37: struct 0@ param 0 = 10.0
// SCR: SET_STRUCT_PARAM
OpcodeResult WINAPI Memory::SetStructParam(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int *struc, param, value;
	params >> struc >> param >> value;
	memcpy(&struc[param], &value, 4);
    return OR_CONTINUE;
}

// 0D38=3,%3d% = struct %1d% param %2d%
// 0D38: 1@ = struct 0@ param 0
// SCR: GET_STRUCT_PARAM
OpcodeResult WINAPI Memory::GetStructParam(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int *struc, param, value;
	params >> struc >> param;
	memcpy(&value, &struc[param], 4);
	params << value;
    return OR_CONTINUE;
}

// 0D4E=4,%4d% = struct %1d% offset %2d% size %3d%
// 0D4E: 1@ = struct 0@ offset 0x4C4 size 4
// SCR: GET_STRUCT_FIELD
OpcodeResult WINAPI Memory::GetStructOffset(CScriptThread* thread)
{
	OpcodeParams params(thread, 4);
	unsigned int struc, offset, size, result = 0;
	params >> struc >> offset >> size;
	if(params.IsStringParam())
		params << (char *)(struc + offset);
	else
	{
		memcpy(&result, (void *)(struc + offset), size);
		params << result;
	}
    return OR_CONTINUE;
}

// 0D4F=4,struct %1d% offset %2d% size %3d% = %4d%
// 0D4F: struct 0@ offset 0x4C4 size 4 = 0
// SCR: SET_STRUCT_FIELD
OpcodeResult WINAPI Memory::SetStructOffset(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int struc, offset, size, value;
	params >> struc >> offset >> size;
	if(params.IsStringParam())
		params >> (char *)(struc + offset);
	else
		memcpy((void *)(struc + offset), &value, size);
    return OR_CONTINUE;
}
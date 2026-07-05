#include "Vector.h"
#include "CVector.h"

// 0D1C=1,normalize_vector %1d%
// 0D1C: normalize_vector 0@
// SCR: NORMALISE_VECTOR
OpcodeResult WINAPI Vector::Normalise(CScriptThread* thread)
{
	OpcodeParams params(thread, 1);
	CVector *vector;
	params >> vector;
	vector->Normalize();
    return OR_CONTINUE;
}

// 0D26=4,set_vector %1d% elements %2d% %3d% %4d%
// 0D26: set_vector 0@ elements 1.0 0.0 0.0
// SCR: INITIALISE_VECTOR
OpcodeResult WINAPI Vector::Setup(CScriptThread* thread)
{
	OpcodeParams params(thread, 4);
	CVector *vec;
	params >> vec;
	params >> *vec;
    return OR_CONTINUE;
}

// 0D28=4,get_vector %1d% elements_to %2d% %3d% %4d%
// 0D28: get_vector 0@ elements_to 1@ 2@ 3@
// SCR: GET_VECTOR_ELEMENTS
OpcodeResult WINAPI Vector::GetValues(CScriptThread* thread)
{
	OpcodeParams params(thread, 4);
	CVector *vec;
	params >> vec;
	params << *vec;
    return OR_CONTINUE;
}
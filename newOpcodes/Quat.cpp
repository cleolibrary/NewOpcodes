#include "Quat.h"

// 0D17=2,convert_matrix %1d% to_quat %2d%
// 0D17: convert_matrix 0@ to_quat 1@
// SCR: SET_QUAT_FROM_MATRIX
OpcodeResult WINAPI Quat::FromMatrix(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	CMatrix *matrix; CQuaternion *quat;
	params >> matrix >> quat;
	quat->Set(*reinterpret_cast<RwMatrix *>(matrix));
    return OR_CONTINUE;
}

// 0D18=6,rotate_quat %1d% axis_vector %2d% %3d% %4d% angle %5d% combine_op %6d%
// 0D18: rotate_quat 0@ axis_vector 1.0 0.0 0.0 angle 45.0 combine_op 2
// SCR: ROTATE_QUAT_ON_AXIS
OpcodeResult WINAPI Quat::Rotate(CScriptThread* thread)
{
	OpcodeParams params(thread, 6);
	RtQuat *quat; RwV3d axis; float angle; unsigned int combineOp;
	params >> quat >> axis >> angle >> combineOp;
	RtQuatRotate(quat, &axis, angle, static_cast<RwOpCombineType>(combineOp));
    return OR_CONTINUE;
}

// 0D19=2,get_normalised_quat %1d% to_quat %2d%
// 0D19: get_normalised_quat 0@ to_quat 1@
// SCR: GET_NORMALISED_QUAT
OpcodeResult WINAPI Quat::Normalise(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	CQuaternion *dst, *src; CQuaternion quat;
	params >> src >> dst;
	quat = *src;
	quat.Normalise();
	*dst = quat;
    return OR_CONTINUE;
}

// 0D1A=3,quat %3d% = quat %1d% * quat %2d%
// 0D1A: quat 2@ = quat 0@ * quat 1@
// SCR: MULTIPLY_QUATS
OpcodeResult WINAPI Quat::Multiply(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	CQuaternion *result, *quat1, *quat2;
	params >> quat1 >> quat2 >> result;
	result->Multiply(*quat1, *quat2);
    return OR_CONTINUE;
}

// 0D1E=4,quat_slerp %1d% from_quat %2d% to_quat %3d% t %4d%
// 0D1E: quat_slerp 0@ from_quat 1@ to_quat 2@ t 0.5
// SCR: MULTIPLY_QUATS
OpcodeResult WINAPI Quat::Slerp(CScriptThread* thread)
{
	OpcodeParams params(thread, 4);
	CQuaternion *result, *from, *to; float t;
	params >> result >> from >> to >> t;
	result->Slerp(*from, *to, t);
    return OR_CONTINUE;
}

// 0D24=5,set_quat %1d% elements %2d% %3d% %4d% %5d%
// 0D24: set_quat 0@ elements 1.0 0.0 0.0 45.0
// SCR: INITIALISE_QUAT
OpcodeResult WINAPI Quat::Setup(CScriptThread* thread)
{
	OpcodeParams params(thread, 5);
	CQuaternion *quat;
	params >> quat;
	params >> *quat;
    return OR_CONTINUE;
}

// 0D29=5,get_quat %1d% elements_to %2d% %3d% %4d% %5d%
// 0D29: get_quat 0@ elements_to 1@ 2@ 3@ 4@
// SCR: GET_QUAT_ELEMENTS
OpcodeResult WINAPI Quat::GetValues(CScriptThread* thread)
{
	OpcodeParams params(thread, 5);
	CQuaternion *quat;
	params >> quat;
	params << *quat;
    return OR_CONTINUE;
}
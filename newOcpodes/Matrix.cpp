#include "Matrix.h"
#include <math.h>
#include <cstdint>
#include "RenderWare.h"
#include "game_sa\CGeneral.h"
#include "game_sa\common.h"

// 0D00=3,matrix %3d% = matrix %1d% * matrix %2d%
// 0D00: matrix 0@ = matrix 0@ * matrix 1@
// SCR: MULTIPLY_MATRICES
OpcodeResult WINAPI Matrix::Multiply(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	RwMatrix *left, *right, *result;
	params >> left >> right >> result;
	RwMatrixMultiply(result, left, right);
    return OR_CONTINUE;
}

// 0D01=6,rotate_matrix %1d% on_axis %2d% %3d% %4d% angle %5d% combine_op %6d%
// 0D01: rotate_matrix 0@ on_axis 1.0 0.0 0.0 angle 45.0 combine_op 2
// SCR: ROTATE_MATRIX_ON_AXIS
OpcodeResult WINAPI Matrix::RotateOnAxis(CScriptThread* thread)
{
	OpcodeParams params(thread, 6);
	RwMatrix *matrix; RwV3d axis; float angle; unsigned int combineOp;
	params >> matrix >> axis >> angle >> combineOp;
	RwMatrixRotate(matrix, &axis, angle, static_cast<RwOpCombineType>(combineOp));
    return OR_CONTINUE;
}

// 0D02=2,%2d% = matrix %1d% x_angle
// 0D02: 1@ = matrix 0@ x_angle
// SCR: GET_MATRIX_X_ANGLE
OpcodeResult WINAPI Matrix::GetXAngle(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwMatrix *matrix;
	params >> matrix;
	float x = matrix->right.x;
	float y = matrix->right.y;
	float z = matrix->right.z;
	float angle = CGeneral::GetATanOfXY(z, sqrt(x * x + y * y)) * 57.295776f - 90.0f;
	while(angle < 0.0)
		angle += 360.0;
	params << angle;
    return OR_CONTINUE;
}

// 0D03=2,%2d% = matrix %1d% y_angle
// 0D03: 1@ = matrix 0@ y_angle
// SCR: GET_MATRIX_Y_ANGLE
OpcodeResult WINAPI Matrix::GetYAngle(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwMatrix *matrix;
	params >> matrix;
	float x = matrix->up.x;
	float y = matrix->up.y;
	float z = matrix->up.z;
	float angle = CGeneral::GetATanOfXY(z, sqrt(x * x + y * y)) * 57.295776f - 90.0f;
	while(angle < 0.0)
		angle += 360.0;
	params << angle;
    return OR_CONTINUE;
}

// 0D04=2,%2d% = matrix %1d% z_angle
// 0D04: 1@ = matrix 0@ z_angle
// SCR: GET_MATRIX_Z_ANGLE
OpcodeResult WINAPI Matrix::GetZAngle(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwMatrix *matrix;
	params >> matrix;
	float angle = CGeneral::GetATanOfXY(matrix->right.x, matrix->right.y) * 57.295776f - 90.0f;
	while(angle < 0.0)
		angle += 360.0;
	params << angle;
    return OR_CONTINUE;
}

// 0D05=4,set_matrix %1d% position %2d% %3d% %4d%
// 0D05: set_matrix 0@ position 0.0 0.0 1.0
// SCR: SET_MATRIX_POSITION
OpcodeResult WINAPI Matrix::SetPosn(CScriptThread* thread)
{
	OpcodeParams params(thread, 4);
	RwMatrix *matrix;
	params >> matrix;
	params >> matrix->pos;
    return OR_CONTINUE;
}

// 0D06=4,get_matrix %1d% position_to %2d% %3d% %4d%
// 0D06: get_matrix 0@ position_to 1@ 2@ 3@
// SCR: GET_MATRIX_POSITION
OpcodeResult WINAPI Matrix::GetPosn(CScriptThread* thread)
{
	OpcodeParams params(thread, 4);
	RwMatrix *matrix;
	params >> matrix;
	params << matrix->pos;
    return OR_CONTINUE;
}

// 0D07=7,get_coords %1d% %2d% %3d% offsets_relative_to_matrix %4d% store_to %5d% %6d% %7d%
// 0D07: get_coords 0@ 1@ 2@ offsets_relative_to_matrix 3@ store_to 4@ 5@ 6@
// SCR: GET_COORDS_OFFSETS_RELATIVELY_TO_MATRIX
OpcodeResult WINAPI Matrix::GetLocalOffset(CScriptThread* thread)
{
	OpcodeParams params(thread, 7);
	CVector coors, result; CMatrix *matrix; CMatrix matrixInv;
	params >> coors >> matrix;
	RwMatrixInvert(reinterpret_cast<RwMatrix *>(&matrixInv), reinterpret_cast<RwMatrix *>(matrix));
	result = Multiply3x3(matrixInv, VectorSub(coors, (CVector&)matrix->pos));
	params << result;
	return OR_CONTINUE;
}

// 0D08=4,set_matrix %1d% rotation %2d% %3d% %4d%
// 0D08: set_matrix 0@ rotation 172.0 7@ 0.0
// SCR: SET_MATRIX_ROTATION
OpcodeResult WINAPI Matrix::Rotate(CScriptThread* thread)
{
	OpcodeParams params(thread, 4);
	CMatrix *matrix; CVector posn, rotation;
	params >> matrix >> rotation;
	posn = (CVector&)matrix->pos;
	matrix->SetRotate(rotation.x, rotation.y, rotation.z);
	matrix->pos.x = posn.x;
	matrix->pos.y = posn.y;
	matrix->pos.z = posn.z;
	return OR_CONTINUE;
}

// 0D09=2,copy_matrix %1d% to %2d%
// 0D09: copy_matrix 0@ to 1@
// SCR: COPY_MATRIX
OpcodeResult WINAPI Matrix::Copy(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwMatrix *dst, *src;
	params >> dst >> src;
	memcpy(dst, src, sizeof(RwMatrix));
	return OR_CONTINUE;
}

// 0D0A=7,store_coords_to %5d% %6d% %7d% from_matrix %1d% with_offsets %2d% %3d% %4d%
// 0D0A: store_coords_to 1@ 2@ 3@ from_matrix 0@ with_offsets 0.0 2.0 0.0
// SCR: GET_OFFSET_FROM_MATRIX_IN_WORLD_COORDS
OpcodeResult WINAPI Matrix::TransformPoint(CScriptThread* thread)
{
	OpcodeParams params(thread, 7);
	RwMatrix *matrix; RwV3d offset; RwV3d result;
	params >> matrix >> offset;
	RwV3dTransformPoint(&result, &offset, matrix);
	params << result;
	return OR_CONTINUE;
}

// 0D13=3,set_matrix %1d% x_angle %2d%
// 0D13: set_matrix 0@ x_angle 45.0
// SCR: SET_MATRIX_X_ROTATION
OpcodeResult WINAPI Matrix::RotateX(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	CMatrix *matrix; float angle;
	params >> matrix >> angle;
	matrix->SetRotateXOnly(angle * 0.0174532925f);
	return OR_CONTINUE;
}

// 0D14=3,set_matrix %1d% y_angle %2d%
// 0D14: set_matrix 0@ y_angle 45.0
// SCR: SET_MATRIX_Y_ROTATION
OpcodeResult WINAPI Matrix::RotateY(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	CMatrix *matrix; float angle;
	params >> matrix >> angle;
	matrix->SetRotateYOnly(angle * 0.0174532925f);
	return OR_CONTINUE;
}

// 0D15=3,set_matrix %1d% z_angle %2d%
// 0D15: set_matrix 0@ z_angle 45.0
// SCR: SET_MATRIX_Z_ROTATION
OpcodeResult WINAPI Matrix::RotateZ(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	CMatrix *matrix; float angle;
	params >> matrix >> angle;
	matrix->SetRotateZOnly(angle * 0.0174532925f);
	return OR_CONTINUE;
}

// 0D16=2,set_matrix %1d% rotation_from_quat %2d%
// 0D16: set_matrix 0@ rotation_from_quat 1@
// SCR: SET_MATRIX_ROTATION_FROM_QUAT
OpcodeResult WINAPI Matrix::FromQuat(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	CMatrix *matrix; CQuaternion *quat;
	params >> matrix >> quat;
	matrix->SetRotate(*quat);
	return OR_CONTINUE;
}

// 0D1D=4,matrix_slerp %1d% from_matrix %2d% to_matrix %3d% t %4d%
// 0D1D: matrix_slerp 0@ m1 1@ m2 2@ t 0.5
// SCR: INTERPOLATE_MATRIX
OpcodeResult WINAPI Matrix::Slerp(CScriptThread* thread)
{
	OpcodeParams params(thread, 4);
	CMatrix *out, *matrix1, *matrix2; float t; CQuaternion quat, quat1, quat2;
	params >> out >> matrix1 >> matrix2 >> t;
	quat1.Set(*reinterpret_cast<RwMatrix *>(matrix1));
	quat2.Set(*reinterpret_cast<RwMatrix *>(matrix2));
	quat.Slerp(quat1, quat2, t);
	out->SetRotate(quat);
	return OR_CONTINUE;
}

// 0D25=17,set_matrix %1d% elements %2d% %3d% %4d% %5d% %6d% %7d% %8d% %9d% %10d% %11d% %12d% %13d% %14d% %15d% %16d% %17d%
// 0D25: set_matrix 0@ elements 0.0 0.0 0.0 0 0.0 0.0 0.0 0 0.0 0.0 0.0 0 0.0 0.0 0.0 0
// SCR: INITIALISE_MATRIX
OpcodeResult WINAPI Matrix::Setup(CScriptThread* thread)
{
	OpcodeParams params(thread, 17);
	CMatrix *matrix;
	params >> matrix;
	for(int i = 0; i < 16; i++)
		params >> *reinterpret_cast<float *>(reinterpret_cast<uintptr_t>(matrix) + 4 * i);
    return OR_CONTINUE;
}
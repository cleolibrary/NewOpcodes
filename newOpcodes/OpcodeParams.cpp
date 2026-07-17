#pragma once

#include "OpcodeParams.h"
#include "NewOpcodes.h"
#include "game_sa\CPools.h"

OpcodeParams::OpcodeParams(CScriptThread *thread, unsigned int count)
{
	pThread = thread;
	paramsCount = count;
}

OpcodeParams::~OpcodeParams()
{
	if(paramsCount > 0)
		CLEO_SkipOpcodeParams(pThread, paramsCount);
}

OpcodeParams& OpcodeParams::operator>>(RwMatrix *&result)
{
	RwMatrix *m = (RwMatrix *)CLEO_GetIntOpcodeParam(pThread);
	if((unsigned int)m > 0 && (unsigned int)m <= 10)
		result = &NewOpcodes::stdParams.m_aMatrices[(unsigned int)m - 1];
	else
		result = m;
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(RwMatrix *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(CMatrix *&result)
{
	CMatrix *m = (CMatrix *)CLEO_GetIntOpcodeParam(pThread);
	if((unsigned int)m > 0 && (unsigned int)m <= 10)
		result = (CMatrix *)&NewOpcodes::stdParams.m_aMatrices[(unsigned int)m - 1];
	else
		result = m;
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(CMatrix *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(RwMatrix &result)
{
	result.right.x = CLEO_GetFloatOpcodeParam(pThread);
	result.right.y = CLEO_GetFloatOpcodeParam(pThread);
	result.right.z = CLEO_GetFloatOpcodeParam(pThread);
	result.flags = CLEO_GetIntOpcodeParam(pThread);
	result.up.x = CLEO_GetFloatOpcodeParam(pThread);
	result.up.y = CLEO_GetFloatOpcodeParam(pThread);
	result.up.z = CLEO_GetFloatOpcodeParam(pThread);
	result.pad1 = CLEO_GetIntOpcodeParam(pThread);
	result.at.x = CLEO_GetFloatOpcodeParam(pThread);
	result.at.y = CLEO_GetFloatOpcodeParam(pThread);
	result.at.z = CLEO_GetFloatOpcodeParam(pThread);
	result.pad2 = CLEO_GetIntOpcodeParam(pThread);
	result.pos.x = CLEO_GetFloatOpcodeParam(pThread);
	result.pos.y = CLEO_GetFloatOpcodeParam(pThread);
	result.pos.z = CLEO_GetFloatOpcodeParam(pThread);
	result.pad3 = CLEO_GetIntOpcodeParam(pThread);
	paramsCount -= 16;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(RwMatrix value)
{
	CLEO_SetFloatOpcodeParam(pThread, value.right.x);
	CLEO_SetFloatOpcodeParam(pThread, value.right.y);
	CLEO_SetFloatOpcodeParam(pThread, value.right.z);
	CLEO_SetIntOpcodeParam(pThread, value.flags);
	CLEO_SetFloatOpcodeParam(pThread, value.up.x);
	CLEO_SetFloatOpcodeParam(pThread, value.up.y);
	CLEO_SetFloatOpcodeParam(pThread, value.up.z);
	CLEO_SetIntOpcodeParam(pThread, value.pad1);
	CLEO_SetFloatOpcodeParam(pThread, value.at.x);
	CLEO_SetFloatOpcodeParam(pThread, value.at.y);
	CLEO_SetFloatOpcodeParam(pThread, value.at.z);
	CLEO_SetIntOpcodeParam(pThread, value.pad2);
	CLEO_SetFloatOpcodeParam(pThread, value.pos.x);
	CLEO_SetFloatOpcodeParam(pThread, value.pos.y);
	CLEO_SetFloatOpcodeParam(pThread, value.pos.z);
	CLEO_SetIntOpcodeParam(pThread, value.pad3);
	paramsCount -= 16;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(CMatrix &result)
{
	result.right.x = CLEO_GetFloatOpcodeParam(pThread);
	result.right.y = CLEO_GetFloatOpcodeParam(pThread);
	result.right.z = CLEO_GetFloatOpcodeParam(pThread);
	result.flags = CLEO_GetIntOpcodeParam(pThread);
	result.up.x = CLEO_GetFloatOpcodeParam(pThread);
	result.up.y = CLEO_GetFloatOpcodeParam(pThread);
	result.up.z = CLEO_GetFloatOpcodeParam(pThread);
	result.pad1 = CLEO_GetIntOpcodeParam(pThread);
	result.at.x = CLEO_GetFloatOpcodeParam(pThread);
	result.at.y = CLEO_GetFloatOpcodeParam(pThread);
	result.at.z = CLEO_GetFloatOpcodeParam(pThread);
	result.pad2 = CLEO_GetIntOpcodeParam(pThread);
	result.pos.x = CLEO_GetFloatOpcodeParam(pThread);
	result.pos.y = CLEO_GetFloatOpcodeParam(pThread);
	result.pos.z = CLEO_GetFloatOpcodeParam(pThread);
	result.pad3 = CLEO_GetIntOpcodeParam(pThread);
	this->paramsCount -= 16;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(CMatrix value)
{
	CLEO_SetFloatOpcodeParam(pThread, value.right.x);
	CLEO_SetFloatOpcodeParam(pThread, value.right.y);
	CLEO_SetFloatOpcodeParam(pThread, value.right.z);
	CLEO_SetIntOpcodeParam(pThread, value.flags);
	CLEO_SetFloatOpcodeParam(pThread, value.up.x);
	CLEO_SetFloatOpcodeParam(pThread, value.up.y);
	CLEO_SetFloatOpcodeParam(pThread, value.up.z);
	CLEO_SetIntOpcodeParam(pThread, value.pad1);
	CLEO_SetFloatOpcodeParam(pThread, value.at.x);
	CLEO_SetFloatOpcodeParam(pThread, value.at.y);
	CLEO_SetFloatOpcodeParam(pThread, value.at.z);
	CLEO_SetIntOpcodeParam(pThread, value.pad2);
	CLEO_SetFloatOpcodeParam(pThread, value.pos.x);
	CLEO_SetFloatOpcodeParam(pThread, value.pos.y);
	CLEO_SetFloatOpcodeParam(pThread, value.pos.z);
	CLEO_SetIntOpcodeParam(pThread, value.pad3);
	paramsCount -= 16;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(CQuaternion *&result)
{
	CQuaternion *q = (CQuaternion *)CLEO_GetIntOpcodeParam(pThread);
	if((unsigned int)q > 0 && (unsigned int)q <= 10)
		result = (CQuaternion *)&NewOpcodes::stdParams.m_aQuats[(unsigned int)q - 1];
	else
		result = q;
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(CQuaternion *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(RtQuat *&result)
{
	RtQuat *q = (RtQuat *)CLEO_GetIntOpcodeParam(pThread);
	if((unsigned int)q > 0 && (unsigned int)q <= 10)
		result = &NewOpcodes::stdParams.m_aQuats[(unsigned int)q - 1];
	else
		result = q;
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(RtQuat *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(RwV3d &result)
{
	result.x = CLEO_GetFloatOpcodeParam(pThread);
	result.y = CLEO_GetFloatOpcodeParam(pThread);
	result.z = CLEO_GetFloatOpcodeParam(pThread);
	paramsCount -= 3;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(RwV3d value)
{
	CLEO_SetFloatOpcodeParam(pThread, value.x);
	CLEO_SetFloatOpcodeParam(pThread, value.y);
	CLEO_SetFloatOpcodeParam(pThread, value.z);
	paramsCount -= 3;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(CVector &result)
{
	result.x = CLEO_GetFloatOpcodeParam(pThread);
	result.y = CLEO_GetFloatOpcodeParam(pThread);
	result.z = CLEO_GetFloatOpcodeParam(pThread);
	paramsCount -= 3;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(CVector value)
{
	CLEO_SetFloatOpcodeParam(pThread, value.x);
	CLEO_SetFloatOpcodeParam(pThread, value.y);
	CLEO_SetFloatOpcodeParam(pThread, value.z);
	paramsCount -= 3;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(CRGBA &result)
{
	result.r = CLEO_GetIntOpcodeParam(pThread);
	result.g = CLEO_GetIntOpcodeParam(pThread);
	result.b = CLEO_GetIntOpcodeParam(pThread);
	result.a = CLEO_GetIntOpcodeParam(pThread);
	paramsCount -= 4;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(CRGBA value)
{
	CLEO_SetIntOpcodeParam(pThread, value.r);
	CLEO_SetIntOpcodeParam(pThread, value.g);
	CLEO_SetIntOpcodeParam(pThread, value.b);
	CLEO_SetIntOpcodeParam(pThread, value.a);
	paramsCount -= 4;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(RtQuat &result)
{
	result.imag.x = CLEO_GetFloatOpcodeParam(pThread);
	result.imag.y = CLEO_GetFloatOpcodeParam(pThread);
	result.imag.z = CLEO_GetFloatOpcodeParam(pThread);
	result.real = CLEO_GetFloatOpcodeParam(pThread);
	paramsCount -= 4;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(RtQuat value)
{
	CLEO_SetFloatOpcodeParam(pThread, value.imag.x);
	CLEO_SetFloatOpcodeParam(pThread, value.imag.y);
	CLEO_SetFloatOpcodeParam(pThread, value.imag.z);
	CLEO_SetFloatOpcodeParam(pThread, value.real);
	paramsCount -= 4;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(CQuaternion &result)
{
	result.imag.x = CLEO_GetFloatOpcodeParam(pThread);
	result.imag.y = CLEO_GetFloatOpcodeParam(pThread);
	result.imag.z = CLEO_GetFloatOpcodeParam(pThread);
	result.real = CLEO_GetFloatOpcodeParam(pThread);
	paramsCount -= 4;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(CQuaternion value)
{
	CLEO_SetFloatOpcodeParam(pThread, value.imag.x);
	CLEO_SetFloatOpcodeParam(pThread, value.imag.y);
	CLEO_SetFloatOpcodeParam(pThread, value.imag.z);
	CLEO_SetFloatOpcodeParam(pThread, value.real);
	paramsCount -= 4;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(CVector *&result)
{
	CVector *v = (CVector *)CLEO_GetIntOpcodeParam(pThread);
	if((unsigned int)v > 0 && (unsigned int)v <= 10)
		result = (CVector *)&NewOpcodes::stdParams.m_aVectors[(unsigned int)v - 1];
	else
		result = v;
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(CVector *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(RwV3d *&result)
{
	RwV3d *v = (RwV3d *)CLEO_GetIntOpcodeParam(pThread);
	if((unsigned int)v > 0 && (unsigned int)v <= 10)
		result = &NewOpcodes::stdParams.m_aVectors[(unsigned int)v - 1];
	else
		result = v;
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(RwV3d *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(CEntity *&result)
{
	result = (CEntity *)CLEO_GetIntOpcodeParam(pThread);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(CEntity *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(unsigned int &result)
{
	result = CLEO_GetIntOpcodeParam(pThread);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(unsigned int value)
{
	CLEO_SetIntOpcodeParam(pThread, value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(float &result)
{
	result = CLEO_GetFloatOpcodeParam(pThread);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(float value)
{
	CLEO_SetFloatOpcodeParam(pThread, value);
	paramsCount--;
	return *this;
}

template <> CPed *OpcodeParams::AtHandle(unsigned int handle)
{
	return CPools::GetPed(handle);
}

template <> CVehicle *OpcodeParams::AtHandle(unsigned int handle)
{
	return CPools::GetVehicle(handle);
}

template <> CObject *OpcodeParams::AtHandle(unsigned int handle)
{
	return CPools::GetObject(handle);
}

unsigned int OpcodeParams::ToHandle(CPed *ped)
{

}

unsigned int OpcodeParams::ToHandle(CVehicle *vehicle)
{

}

unsigned int OpcodeParams::ToHandle(CObject *object)
{

}

OpcodeParams& OpcodeParams::operator>>(signed int &result)
{
	result = CLEO_GetIntOpcodeParam(pThread);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(signed int value)
{
	CLEO_SetIntOpcodeParam(pThread, value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(unsigned char &result)
{
	result = CLEO_GetIntOpcodeParam(pThread);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(unsigned char value)
{
	CLEO_SetIntOpcodeParam(pThread, value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(char *str)
{
	int type = CLEO_GetOperandType(this->pThread);
	if(!type)
	{
		*str = '\0';
		CLEO_SkipOpcodeParams(this->pThread, 1);
	}
	else if(type >= 1 && type <= 8)
		strcpy_s(str, 100, (char *)CLEO_GetIntOpcodeParam(this->pThread));
	else
		CLEO_ReadStringOpcodeParam(this->pThread, str, 100);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(char *str)
{
	int type = CLEO_GetOperandType(this->pThread);
	if(!type)
		CLEO_SkipOpcodeParams(this->pThread, 1);
	else if(type >= 1 && type <= 8)
		strcpy_s((char *)CLEO_GetIntOpcodeParam(this->pThread), 100, str);
	else
		CLEO_WriteStringOpcodeParam(this->pThread, str);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(RwFrame *&result)
{
	result = (RwFrame *)CLEO_GetIntOpcodeParam(pThread);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(RwFrame *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(RpAtomic *&result)
{
	result = (RpAtomic *)CLEO_GetIntOpcodeParam(pThread);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(RpAtomic *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(void *&result)
{
	result = (void *)CLEO_GetIntOpcodeParam(pThread);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(void *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(AnimBlendFrameData *&result)
{
	result = (AnimBlendFrameData *)CLEO_GetIntOpcodeParam(pThread);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(AnimBlendFrameData *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(CColPoint *&result)
{
	CColPoint *colPoint = (CColPoint *)CLEO_GetIntOpcodeParam(pThread);
	if((unsigned int)colPoint == 1)
		result = &NewOpcodes::stdParams.m_colPoint;
	else
		result = colPoint;
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(CColPoint *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator>>(unsigned int *&result)
{
	result = (unsigned int *)CLEO_GetIntOpcodeParam(pThread);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(unsigned int *value)
{
	CLEO_SetIntOpcodeParam(pThread, (unsigned int)value);
	paramsCount--;
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(eOpcodeResult result)
{
	CLEO_SetThreadCondResult(pThread, result);
	return *this;
}

OpcodeParams& OpcodeParams::operator<<(iOptional param)
{
	switch(CLEO_GetOperandType(pThread))
	{
	case globalVar:
	case localVar:
	case globalArr:
	case localArr:
		CLEO_SetIntOpcodeParam(pThread, param);
		break;
	default:
		CLEO_SkipOpcodeParams(pThread, 1);
	}
	paramsCount--;
	return *this;
}

bool OpcodeParams::IsStringParam()
{
	int type = CLEO_GetOperandType(pThread);
	if(type > 8)
		return true;
	return false;
}

bool OpcodeParams::IsOptionalParam()
{
	switch(CLEO_GetOperandType(pThread))
	{
	case globalVar:
	case localVar:
	case globalArr:
	case localArr:
		return false;
	}
	CLEO_SkipOpcodeParams(pThread, 1);
	paramsCount--;
	return true;
}
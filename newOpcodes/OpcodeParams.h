#pragma once

#include "CLEO.h"
#include "RenderWare.h"
#include "CVector.h"
#include "game_sa\CMatrix.h"
#include "game_sa\CVehicle.h"
#include "game_sa\CPed.h"
#include "game_sa\CObject.h"
#include "game_sa\AnimBlendFrameData.h"
#include "game_sa\CColPoint.h"
#include "CRGBA.h"

enum eOpcodeResult
{
	orFalse, orTrue 
};

enum iOptional : int
{
};

class OpcodeParams
{
	CScriptThread *pThread;
	int paramsCount;
public:
	OpcodeParams(CScriptThread *thread, unsigned int count = 0);
	~OpcodeParams();
	template<class T> static T *AtHandle(unsigned int handle);
	static unsigned int ToHandle(CPed *ped);
	static unsigned int ToHandle(CVehicle *vehicle);
	static unsigned int ToHandle(CObject *object);
	OpcodeParams& operator>>(RwMatrix *&result);
	OpcodeParams& operator<<(RwMatrix *value);
	OpcodeParams& operator>>(CMatrix *&result);
	OpcodeParams& operator<<(CMatrix *value);
	OpcodeParams& operator>>(RwMatrix &result);
	OpcodeParams& operator<<(RwMatrix value);
	OpcodeParams& operator>>(CMatrix &result);
	OpcodeParams& operator<<(CMatrix value);
	OpcodeParams& operator>>(CQuaternion *&result);
	OpcodeParams& operator<<(CQuaternion *value);
	OpcodeParams& operator>>(RtQuat *&result);
	OpcodeParams& operator<<(RtQuat *value);
	OpcodeParams& operator>>(CQuaternion &result);
	OpcodeParams& operator<<(CQuaternion value);
	OpcodeParams& operator>>(RtQuat &result);
	OpcodeParams& operator<<(RtQuat value);
	OpcodeParams& operator>>(RwV3d &result);
	OpcodeParams& operator<<(RwV3d value);
	OpcodeParams& operator>>(CVector &result);
	OpcodeParams& operator<<(CVector value);
	OpcodeParams& operator>>(CVector *&result);
	OpcodeParams& operator<<(CVector *value);
	OpcodeParams& operator>>(RwV3d *&result);
	OpcodeParams& operator<<(RwV3d *value);
	OpcodeParams& operator>>(CEntity *&result);
	OpcodeParams& operator<<(CEntity *value);
	OpcodeParams& operator>>(CRGBA &result);
	OpcodeParams& operator<<(CRGBA value);
	OpcodeParams& operator>>(unsigned int &result);
	OpcodeParams& operator<<(unsigned int value);
	OpcodeParams& operator>>(unsigned char &result);
	OpcodeParams& operator<<(unsigned char value);
	OpcodeParams& operator>>(float &result);
	OpcodeParams& operator<<(float value);
	OpcodeParams& operator>>(signed int &result);
	OpcodeParams& operator<<(signed int value);
	OpcodeParams& operator>>(char *str);
	OpcodeParams& operator<<(char *str);
	OpcodeParams& operator>>(RwFrame *&frame);
	OpcodeParams& operator<<(RwFrame *frame);
	OpcodeParams& operator>>(RpAtomic *&frame);
	OpcodeParams& operator<<(RpAtomic *frame);
	OpcodeParams& operator>>(void *&data);
	OpcodeParams& operator<<(void *data);
	OpcodeParams& operator>>(unsigned int *&data);
	OpcodeParams& operator<<(unsigned int *data);
	OpcodeParams& operator>>(CColPoint *&data);
	OpcodeParams& operator<<(CColPoint *data);
	OpcodeParams& operator>>(AnimBlendFrameData *&data);
	OpcodeParams& operator<<(AnimBlendFrameData *data);
	OpcodeParams& operator<<(eOpcodeResult result);
	OpcodeParams& operator<<(iOptional param);
	bool IsStringParam();
	bool IsOptionalParam();
};
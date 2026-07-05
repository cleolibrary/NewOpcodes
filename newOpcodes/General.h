#pragma once

#include "OpcodeParams.h"

class General
{
public:
	static OpcodeResult WINAPI SetCarModelAlpha(CScriptThread* thread);
	static OpcodeResult WINAPI SetActorModelAlpha(CScriptThread* thread);
	static OpcodeResult WINAPI SetObjectModelAlpha(CScriptThread* thread);
	static OpcodeResult WINAPI GetEntityTypeClass(CScriptThread* thread);
	static OpcodeResult WINAPI GetCarNumCollidedEntities(CScriptThread* thread);
	static OpcodeResult WINAPI GetActorNumCollidedEntities(CScriptThread* thread);
	static OpcodeResult WINAPI GetObjectNumCollidedEntities(CScriptThread* thread);
	static OpcodeResult WINAPI GetLocalTimeInfo(CScriptThread* thread);
	static OpcodeResult WINAPI SetThreadVar(CScriptThread* thread);
	static OpcodeResult WINAPI GetThreadVar(CScriptThread* thread);
	static OpcodeResult WINAPI SetCarWindowState(CScriptThread* thread);
	static OpcodeResult WINAPI GetCarCollidedEntities(CScriptThread* thread);
	static OpcodeResult WINAPI GetActorCollidedEntities(CScriptThread* thread);
	static OpcodeResult WINAPI GetObjectCollidedEntities(CScriptThread* thread);
	static OpcodeResult WINAPI GetActorMaxHelath(CScriptThread* thread);
	static OpcodeResult WINAPI CirclesIntersection(CScriptThread* thread);
	static OpcodeResult WINAPI GetModelTxd(CScriptThread* thread);
	static OpcodeResult WINAPI GetModelCRC(CScriptThread* thread);
	static OpcodeResult WINAPI AddPermanentShadow(CScriptThread* thread);
	static OpcodeResult WINAPI AddTemporaryShadow(CScriptThread* thread);
	static OpcodeResult WINAPI AddLight(CScriptThread* thread);
	static OpcodeResult WINAPI AddCorona(CScriptThread* thread);
	static OpcodeResult WINAPI AddCoronaEx(CScriptThread* thread);
	static OpcodeResult WINAPI GetSunColors(CScriptThread* thread);
	static OpcodeResult WINAPI GetSunScreenCoors(CScriptThread* thread);
	static OpcodeResult WINAPI GetSunWorldCoors(CScriptThread* thread);
	static OpcodeResult WINAPI GetSunSize(CScriptThread* thread);
	static OpcodeResult WINAPI GetWeather(CScriptThread* thread);
	static OpcodeResult WINAPI GetTraffLightsColor(CScriptThread* thread);
	static OpcodeResult WINAPI AddSpotLight(CScriptThread* thread);
	static OpcodeResult WINAPI CarLightGetDamageState(CScriptThread* thread);
	static OpcodeResult WINAPI CarLightSetDamageState(CScriptThread* thread);
	static OpcodeResult WINAPI GetVehicleClass(CScriptThread* thread);
	static OpcodeResult WINAPI GetVehicleDummyPosn(CScriptThread* thread);
	static OpcodeResult WINAPI AddProjectile(CScriptThread* thread);
	static OpcodeResult WINAPI SetCarRemap(CScriptThread* thread);
	static OpcodeResult WINAPI SetCarCustomColor(CScriptThread* thread);
	static OpcodeResult WINAPI GetGameVolume(CScriptThread* thread);
	static OpcodeResult WINAPI GetScreenWidthHeight(CScriptThread* thread);
};
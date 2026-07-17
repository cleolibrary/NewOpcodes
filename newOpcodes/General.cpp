#include "General.h"
#include "NewOpcodes.h"
#include "SpotLightDrawer.h"
#include "game_sa\common.h"
#include "game_sa\CClumpModelInfo.h"
#include "game_sa\CMenuManager.h"
#include "game_sa\CModelInfo.h"
#include "game_sa\CShadows.h"
#include "game_sa\CPointLights.h"
#include "game_sa\CCoronas.h"
#include "game_sa\CDamageManager.h"
#include "game_sa\CDraw.h"
#include "game_sa\CTimeCycle.h"
#include "game_sa\CWeather.h"
#include <Windows.h>
#include <math.h>

// 0D0F=2,set_car %1d% model_alpha %2d% // IF and SET
// 0D0F: set_car 0@ model_alpha 255 // IF and SET
// SCR: SET_CAR_MODEL_ALPHA
OpcodeResult WINAPI General::SetCarModelAlpha(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	unsigned int handle, alpha;
	params >> handle >> alpha;
	CVehicle *vehicle = params.AtHandle<CVehicle>(handle);
	if(vehicle->m_pRwObject)
	{
		vehicle->SetRwObjectAlpha(alpha);
		params << orTrue;
	}
	else
		params << orFalse;
	return OR_CONTINUE;
}

// 0D10=2,set_actor %1d% model_alpha %2d% // IF and SET
// 0D10: set_actor 0@ model_alpha 255 // IF and SET
// SCR: SET_CHAR_MODEL_ALPHA
OpcodeResult WINAPI General::SetActorModelAlpha(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	unsigned int handle, alpha;
	params >> handle >> alpha;
	CPed *ped = params.AtHandle<CPed>(handle);
	if(ped->m_pRwObject)
	{
		ped->SetRwObjectAlpha(alpha);
		params << orTrue;
	}
	else
		params << orFalse;
	return OR_CONTINUE;
}

// 0D11=2,set_object %1d% model_alpha %2d% // IF and SET
// 0D11: set_object 0@ model_alpha 255 // IF and SET
// SCR: SET_OBJECT_MODEL_ALPHA
OpcodeResult WINAPI General::SetObjectModelAlpha(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	unsigned int handle, alpha;
	params >> handle >> alpha;
	CObject *object = params.AtHandle<CObject>(handle);
	if(object->m_pRwObject)
	{
		object->SetRwObjectAlpha(alpha);
		params << orTrue;
	}
	else
		params << orFalse;
	return OR_CONTINUE;
}

// 0D1B=2,get_entity %1d% type_to %2d% class_to %3d%
// 0D1B: get_entity 0@ type_to 1@ class_to 2@
// SCR: GET_ENTITY_TYPE_AND_CLASS
OpcodeResult WINAPI General::GetEntityTypeClass(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	CEntity *entity;
	params >> entity;
	params << entity->m_nType << *(unsigned int *)entity;
	return OR_CONTINUE;
}

// 0D2A=2,%2d% = get_car %1d% number_of_collided_entites
// 0D2A: 1@ = get_car 0@ number_of_collided_entites
// SCR: GET_CAR_NUM_COLLIDED_ENTITIES
OpcodeResult WINAPI General::GetCarNumCollidedEntities(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	unsigned int handle;
	params >> handle;
	params << params.AtHandle<CVehicle>(handle)->m_nNumEntitiesCollided;
	return OR_CONTINUE;
}

// 0D2B=2,%2d% = get_actor %1d% number_of_collided_entites
// 0D2B: 1@ = get_actor 0@ number_of_collided_entites
// SCR: GET_CHAR_NUM_COLLIDED_ENTITIES
OpcodeResult WINAPI General::GetActorNumCollidedEntities(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	unsigned int handle;
	params >> handle;
	params << params.AtHandle<CPed>(handle)->m_nNumEntitiesCollided;
	return OR_CONTINUE;
}

// 0D2C=2,%2d% = get_object %1d% number_of_collided_entites
// 0D2C: 1@ = get_object 0@ number_of_collided_entites
// SCR: GET_OBJECT_NUM_COLLIDED_ENTITIES
OpcodeResult WINAPI General::GetObjectNumCollidedEntities(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	unsigned int handle;
	params >> handle;
	params << params.AtHandle<CObject>(handle)->m_nNumEntitiesCollided;
	return OR_CONTINUE;
}

// 0D2D=8,get_local_time_year_to %1d% month_to %2d% day_of_week_to %3d% day_to %4d% hour_to %5d% minute_to %6d% second_to %7d% milliseconds_to %8d%
// 0D2D: get_local_time_year_to 0@ month_to 1@ day_of_week_to 2@ day_to 3@ hour_to 4@ minute_to 5@ second_to 6@ milliseconds_to 7@
// SCR: GET_LOCAL_TIME
OpcodeResult WINAPI General::GetLocalTimeInfo(CScriptThread* thread)
{
	OpcodeParams params(thread, 8);
	SYSTEMTIME time;
	GetLocalTime(&time);
	params << (iOptional)time.wYear << (iOptional)time.wMonth << (iOptional)time.wDayOfWeek << (iOptional)time.wDay << (iOptional)time.wHour
		<< (iOptional)time.wMinute << (iOptional)time.wSecond << (iOptional)time.wMilliseconds;
	return OR_CONTINUE;
}

// 0D2E=3,set_thread %1d% var %2d% to %3d%
// 0D2E: set_thread 0@ var 10 to 10.0
// SCR: SET_THREAD_VAR
OpcodeResult WINAPI General::SetThreadVar(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	void *t, *value; unsigned int var; SCRIPT_VAR scrVal;
	params >> t >> var >> value;
	scrVal.pParam = value;
	((CScriptThread *)t)->tls[var] = scrVal;
	return OR_CONTINUE;
}

// 0D2F=3,%3d% = get_thread %1d% var %2d%
// 0D2F: 1@ = get_thread 0@ var 10
// SCR: GET_THREAD_VAR
OpcodeResult WINAPI General::GetThreadVar(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	void *t, *value; unsigned int var; SCRIPT_VAR scrVal;
	params >> t >> var;
	params << ((CScriptThread *)t)->tls[var].pParam;
	return OR_CONTINUE;
}

// 0D33=3,set_car %1d% door %2d% window_state %3d%
// 0D33: set_car 0@ door DOOR_RF window_state OPENED
// SCR: SET_CAR_DOOR_WINDOW_STATE
OpcodeResult WINAPI General::SetCarWindowState(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int handle, door, state;
	params >> handle >> door >> state;
	CVehicle *vehicle = params.AtHandle<CVehicle>(handle);
	if(state)
		vehicle->SetWindowOpenFlag(door);
	else
		vehicle->ClearWindowOpenFlag(door);
	return OR_CONTINUE;
}

// 0D34=7,store_car %1d% collided_entities_to %2d% %3d% %4d% %5d% %6d% %7d%
// 0D34: store_car 0@ collided_entities_to 1@ 2@ -1 -1 -1 -1
// SCR: GET_CAR_COLLIDED_ENTITIES
OpcodeResult WINAPI General::GetCarCollidedEntities(CScriptThread* thread)
{
	OpcodeParams params(thread, 7);
	unsigned int handle;
	params >> handle;
	CVehicle *vehicle = params.AtHandle<CVehicle>(handle);
	for(int i = 0; i < 6; i++)
		params << (iOptional)(unsigned int)vehicle->m_apCollidedEntities[i];
	return OR_CONTINUE;
}

// 0D35=7,store_actor %1d% collided_entities_to %2d% %3d% %4d% %5d% %6d% %7d%
// 0D35: store_actor 0@ collided_entities_to 1@ 2@ -1 -1 -1 -1
// SCR: GET_CHAR_COLLIDED_ENTITIES
OpcodeResult WINAPI General::GetActorCollidedEntities(CScriptThread* thread)
{
	OpcodeParams params(thread, 7);
	unsigned int handle;
	params >> handle;
	CPed *ped = params.AtHandle<CPed>(handle);
	for(int i = 0; i < 6; i++)
		params << (iOptional)(unsigned int)ped->m_apCollidedEntities[i];
	return OR_CONTINUE;
}

// 0D36=7,store_object %1d% collided_entities_to %2d% %3d% %4d% %5d% %6d% %7d%
// 0D36: store_object 0@ collided_entities_to 1@ 2@ -1 -1 -1 -1
// SCR: GET_OBJECT_COLLIDED_ENTITIES
OpcodeResult WINAPI General::GetObjectCollidedEntities(CScriptThread* thread)
{
	OpcodeParams params(thread, 7);
	unsigned int handle;
	params >> handle;
	CObject *object = params.AtHandle<CObject>(handle);
	for(int i = 0; i < 6; i++)
		params << (iOptional)(unsigned int)object->m_apCollidedEntities[i];
	return OR_CONTINUE;
}

// 0D39=2,%2d% = actor %1d% max_health
// 0D39: 1@ = actor 0@ max_health
// SCR: GET_CHAR_MAX_HEALTH
OpcodeResult WINAPI General::GetActorMaxHelath(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	unsigned int handle;
	params >> handle;
	CPed *ped = params.AtHandle<CPed>(handle);
	params << ped->m_fMaxHealth;
	return OR_CONTINUE;
}

// 0D3F=10,find_intersection_between_circles_xyr1 %1d% %2d% %3d% and_xyr2 %4d% %5d% %6d% store_point1_to %7d% %8d% point2_to %9d% %10d% // IF and SET
// 0D3F: find_intersection_between_circles_xyr1 0.0 0.0 20.0 and_xyr2 10.0 10.0 20.0 store_point1_to 0@ 1@ point2_to 2@ 3@ // IF and SET
// SCR: GET_CHAR_MAX_HEALTH
OpcodeResult WINAPI General::CirclesIntersection(CScriptThread* thread)
{
	OpcodeParams params(thread, 10);
	float x0, y0, r0, x1, y1, r1, a, dx, dy, d, h, rx, ry, x2, y2;
	params >> x0 >> y0 >> r0 >> x1 >> y1 >> r1;
	dx = x1 - x0;
	dy = y1 - y0;
	d = hypot(dx,dy);
	if((d > (r0 + r1)) || (d < fabs(r0 - r1)))
		params << 0.0f << 0.0f << 0.0f << 0.0f << orFalse;
	else
	{
		a = ((r0 * r0) - (r1 * r1) + (d * d)) / (2.0f * d) ;
		x2 = x0 + (dx * a / d);
		y2 = y0 + (dy * a / d);
		h = sqrt((r0 * r0) - (a * a));
		rx = -dy * (h / d);
		ry = dx * (h / d);
		params << x2 + rx << y2 + ry << x2 - rx << y2 - ry << orTrue;
	}
	return OR_CONTINUE;
}

// 0D47=2,%2d% = model %1d% txd_id // IF and SET
// 0D47: 0@ = model #BANSHEE txd_id // IF and SET
// SCR: GET_MODEL_TXD_ID
OpcodeResult WINAPI General::GetModelTxd(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	unsigned int mi;
	params >> mi;
	CBaseModelInfo *model = CModelInfo::ms_modelInfoPtrs[mi];
	if(model)
		params << model->m_nTxdIndex << orTrue;
	else
		params << -1 << orFalse;
	return OR_CONTINUE;
}

// 0D48=2,%2d% = model %1d% crc32_key // IF and SET
// 0D48: 1@ = model 0@ crc32_key // IF and SET
// SCR: GET_MODEL_CRC
OpcodeResult WINAPI General::GetModelCRC(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	unsigned int mi;
	params >> mi;
	CBaseModelInfo *model = CModelInfo::ms_modelInfoPtrs[mi];
	if(model)
		params << model->m_nKey << orTrue;
	else
		params << 0 << orFalse;
	return OR_CONTINUE;
}

// 0D50=14,draw_shadow_type %1d% position %2d% %3d% %4d% width %5d% height %6d% rotation %7d% distance %8d% texture %9d% intensity %10d% RGB %11d% %12d% %13d% shadow_data %14d%
// 0D50: draw_shadow_type 2 position 0@ 1@ 2@ width 3@ height 4@ rotation 5@ distance 6@ texture 7@ intensity 255 RGB 255 255 255 shadow_data 0
// SCR: DRAW_TEMPORARY_SHADOW
OpcodeResult WINAPI General::AddTemporaryShadow(CScriptThread* thread)
{
	OpcodeParams params(thread, 14);
	unsigned int type, intensity, red, green, blue, texture; float width, height, rotation, distance; void *shadowData; CVector posn;
	params >> type >> posn >> width >> height >> rotation >> distance >> texture >> intensity >> red >> green >>
		blue >> shadowData;
	float a = rotation * 0.0174532925f;
	float y1 = sin(a) * width / 2.0f;
	float x1 = cos(a) * width / 2.0f;
	float y2 = sin(a + 90.0f) * height / 2.0f;
	float x2 = cos(a + 90.0f) * height / 2.0f;
	if(texture < 11)
	{
		switch ( texture )
		{
		case 1:
		    texture = (unsigned int)gpShadowCarTex;
		    break;
		case 2:
		    texture = (unsigned int)gpShadowPedTex;
		    break;
		case 3:
		    texture = (unsigned int)gpShadowExplosionTex;
		    break;
		case 4:
		    texture = (unsigned int)gpShadowHeliTex;
		    break;
		case 5:
		    texture = (unsigned int)gpShadowHeadLightsTex;
		    break;
		case 6:
		    texture = (unsigned int)gpBloodPoolTex;
		    break;
		case 7:
		    texture = (unsigned int)gpShadowHeadLightsTex2;
		    break;
		case 8:
		    texture = (unsigned int)gpShadowBikeTex;
		    break;
		case 9:
		    texture = (unsigned int)gpShadowBaronTex;
		    break;
		case 10:
		    texture = (unsigned int)gpPostShadowTex;
		    break;
		default:
			texture = (unsigned int)gpShadowExplosionTex;
		}
	}
	CShadows::StoreShadowToBeRendered(type, (RwTexture *)texture, &posn, x1, y1, x2, y2, intensity, red, green, blue, distance,
		false, 1.0f, (CRealTimeShadow *)shadowData, false);
	return OR_CONTINUE;
}

// 0D51=14,draw_permanent_shadow_type %1d% position %2d% %3d% %4d% width %5d% height %6d% rotation %7d% distance %8d% texture %9d% intensity %10d% RGB %11d% %12d% %13d% time %14d%
// 0D51: draw_permanent_shadow_type 2 position 0@ 1@ 2@ width 3@ height 4@ rotation 5@ distance 6@ texture 7@ intensity 255 RGB 255 255 255 time 5000
// SCR: DRAW_PERMANENT_SHADOW
OpcodeResult WINAPI General::AddPermanentShadow(CScriptThread* thread)
{
	OpcodeParams params(thread, 14);
	unsigned int type, intensity, red, green, blue, texture, time; float width, height, rotation, distance; CVector posn;
	params >> type >> posn >> width >> height >> rotation >> distance >> texture >> intensity >> red >> green >>
		blue >> time;
	float a = rotation * 0.0174532925f;
	float y1 = sin(a) * width / 2.0f;
	float x1 = cos(a) * width / 2.0f;
	float y2 = sin(a + 90.0f) * height / 2.0f;
	float x2 = cos(a + 90.0f) * height / 2.0f;
	if(texture < 11)
	{
		switch ( texture )
		{
		case 1:
		    texture = (unsigned int)gpShadowCarTex;
		    break;
		case 2:
		    texture = (unsigned int)gpShadowPedTex;
		    break;
		case 3:
		    texture = (unsigned int)gpShadowExplosionTex;
		    break;
		case 4:
		    texture = (unsigned int)gpShadowHeliTex;
		    break;
		case 5:
		    texture = (unsigned int)gpShadowHeadLightsTex;
		    break;
		case 6:
		    texture = (unsigned int)gpBloodPoolTex;
		    break;
		case 7:
		    texture = (unsigned int)gpShadowHeadLightsTex2;
		    break;
		case 8:
		    texture = (unsigned int)gpShadowBikeTex;
		    break;
		case 9:
		    texture = (unsigned int)gpShadowBaronTex;
		    break;
		case 10:
		    texture = (unsigned int)gpPostShadowTex;
		    break;
		default:
			texture = (unsigned int)gpShadowExplosionTex;
		}
	}
	CShadows::AddPermanentShadow(type, (RwTexture *)texture, &posn, x1, y1, x2, y2, intensity, red, green, blue, distance,
		1.0f, time);
	return OR_CONTINUE;
}

// 0D52=12,draw_light_type %1d% position %2d% %3d% %4d% direction %5d% %6d% %7d% radius %8d% RGB %9d% %10d% %11d% affect_entity %12d%
// 0D52: draw_light_type 1 position 0@ 1@ 2@ direction 3@ 4@ 5@ radius 3.0 RGB 255 0 0 affect_entity 0
// SCR: DRAW_TEMPORARY_LIGHT
OpcodeResult WINAPI General::AddLight(CScriptThread* thread)
{
	OpcodeParams params(thread, 12);
	unsigned int type, red, green, blue, entity; float radius; CVector posn, dir;
	params >> type >> posn >> dir >> radius >> red >> green >> blue >> entity;
	CPointLights::AddLight(type, posn, dir, radius, (float)red / 255.0f, (float)green / 255.0f, (float)blue / 255.0f,
		0, false, (CEntity *)entity);
	return OR_CONTINUE;
}

// 0D53=10,draw_corona_with_texture %1d% color %2d% %3d% %4d% %5d% on_entity %6d% at %7d% %8d% %9d% size %10d%
// 0D53: draw_corona_with_texture CORONASTAR color 255 255 255 255 on_entity 0 at 0@ 1@ 2@ size 0.5
// SCR: DRAW_TEMPORARY_CORONA
OpcodeResult WINAPI General::AddCorona(CScriptThread* thread)
{
	OpcodeParams params(thread, 10);
	unsigned int texture, red, green, blue, alpha, entity; float size; CVector posn;
	params >> texture >> red >> green >> blue >> alpha >> entity >> posn >> size;
	if(texture < 10)
	{
		switch ( texture )
		{
		case 1:
		    texture = (unsigned int)gpCoronaTexture[1];
		    break;
		case 2:
		    texture = (unsigned int)gpCoronaTexture[2];
		    break;
		case 3:
		    texture = (unsigned int)gpCoronaTexture[3];
		    break;
		case 4:
		    texture = (unsigned int)gpCoronaTexture[4];
		    break;
		case 9:
		    texture = (unsigned int)gpCoronaTexture[9];
		    break;
		default:
			texture = (unsigned int)gpCoronaTexture[0];
		}
	}
	CCoronas::RegisterCorona(NewOpcodes::m_nCurrentCoronaId, (CEntity *)entity, red, green, blue, alpha, posn, size, 100.0f,
		(RwTexture *)texture, FLARETYPE_NONE, false, false, 0, 0.0f, false, 0.15f, 0, 15.0f, false, false);
	NewOpcodes::m_nCurrentCoronaId++;
	return OR_CONTINUE;
}

// 0D54=18,draw_corona_with_extra_params_texture %1d% color %2d% %3d% %4d% %5d% on_entity %6d% at %7d% %8d% %9d% size %10d% far_clip %11d% near_clip %12d% flare %13d% enable_reflection %14d% check_obstacles %15d% flash_while_fading %16d% fade_speed %17d% only_from_below %18d%
// 0D54: draw_corona_with_texture CORONASTAR color 255 255 255 255 on_entity 0 at 0@ 1@ 2@ size 0.5 far_clip 150.0 near_clip 1.5 flare 0 enable_reflection 1 check_obstacles 0 flash_while_fading 0 fade_speed 15.0 only_from_below 0
// SCR: DRAW_TEMPORARY_CORONA_EX
OpcodeResult WINAPI General::AddCoronaEx(CScriptThread* thread)
{
	OpcodeParams params(thread, 18);
	unsigned int texture, red, green, blue, alpha, entity, flare, reflection, checkObstacles, onlyFromBelow, flashWhileFading; 
	float size, farClip, nearClip, fadeSpeed; CVector posn;
	params >> texture >> red >> green >> blue >> alpha >> entity >> posn >> size >> farClip >> nearClip >>
		flare >> reflection >> checkObstacles >> flashWhileFading >> fadeSpeed >> onlyFromBelow;
	if(texture < 10)
	{
		switch ( texture )
		{
		case 1:
		    texture = (unsigned int)gpCoronaTexture[1];
		    break;
		case 2:
		    texture = (unsigned int)gpCoronaTexture[2];
		    break;
		case 3:
		    texture = (unsigned int)gpCoronaTexture[3];
		    break;
		case 4:
		    texture = (unsigned int)gpCoronaTexture[4];
		    break;
		case 9:
		    texture = (unsigned int)gpCoronaTexture[9];
		    break;
		default:
			texture = (unsigned int)gpCoronaTexture[0];
		}
	}
	CCoronas::RegisterCorona(NewOpcodes::m_nCurrentCoronaId, (CEntity *)entity, red, green, blue, alpha, posn, size, farClip,
		(RwTexture *)texture, static_cast<eCoronaFlareType>(flare), reflection, checkObstacles, 0, 0.0f, false, nearClip, flashWhileFading, fadeSpeed, 
		onlyFromBelow, false);
	NewOpcodes::m_nCurrentCoronaId++;
	return OR_CONTINUE;
}

// 0D55=6,get_sun_colors_core_to %1d% %2d% %3d% glow_to %4d% %5d% %6d%
// 0D55: get_sun_colors_core_to 0@ 1@ 2@ glow_to 3@ 4@ 5@
// SCR: GET_SUN_COLORS
OpcodeResult WINAPI General::GetSunColors(CScriptThread* thread)
{
	OpcodeParams params(thread, 6);
	params << CTimeCycle::m_CurrentColours.m_nSunCoreRed
	       << CTimeCycle::m_CurrentColours.m_nSunCoreGreen
	       << CTimeCycle::m_CurrentColours.m_nSunCoreBlue
	       << CTimeCycle::m_CurrentColours.m_nSunCoronaRed
	       << CTimeCycle::m_CurrentColours.m_nSunCoronaGreen
	       << CTimeCycle::m_CurrentColours.m_nSunCoronaBlue;
	return OR_CONTINUE;
}

// 0D56=2,get_sun_screen_coords_XY_to %1d% %2d%
// 0D56: get_sun_screen_coords_XY_to 0@ 1@
// SCR: GET_SUN_SCREEN_COORS
OpcodeResult WINAPI General::GetSunScreenCoors(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	params << CCoronas::SunScreenX << CCoronas::SunScreenY;
	return OR_CONTINUE;
}

// 0D57=3,get_sun_position_to %1d% %2d% %3d% // IF and SET
// 0D57: get_sun_position_to 0@ 1@ 2@ // IF and SET
// SCR: GET_SUN_WORLD_COORS
OpcodeResult WINAPI General::GetSunWorldCoors(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	CVector *sunPos;
	float sunDistance = CDraw::ms_fFarClipZ * 2.0f;
	sunPos = &CTimeCycle::m_VectorToSun[CTimeCycle::m_CurrentStoredValue];
	if(sunPos->z > -0.1f)
		params << orTrue;
	else
		params << orFalse;
	params << sunPos->x * sunDistance << sunPos->y * sunDistance << sunPos->z * sunDistance;
	return OR_CONTINUE;
}

// 0D58=2,get_sun_size_core_to %1d% glow_to %2d%
// 0D58: get_sun_size_core_to 0@ glow_to 1@
// SCR: GET_SUN_SIZE
OpcodeResult WINAPI General::GetSunSize(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	params << CTimeCycle::m_CurrentColours.m_fSunSize * 2.7335f << CTimeCycle::m_CurrentColours.m_fSunSize * 6.0f;
	return OR_CONTINUE;
}

// 0D59=1,%1d% = current_weather
// 0D59: 0@ = current_weather
// SCR: GET_CURRENT_WEATHER
OpcodeResult WINAPI General::GetWeather(CScriptThread* thread)
{
	OpcodeParams params(thread, 1);
	params << (unsigned short)CWeather::OldWeatherType;
	return OR_CONTINUE;
}

// 0D5A=2,get_trafficlights_type_NS_current_color_to %1d% type_WE_current_color_to %2d%
// 0D5A: get_trafficlights_type_NS_current_color_to 0@ type_WE_current_color_to 1@
// SCR: GET_TRAFFICLIGHTS_CURRENT_COLOR
OpcodeResult WINAPI General::GetTraffLightsColor(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	unsigned char ns = ((unsigned char (__cdecl *)())0x49D3A0)();
	unsigned char we = ((unsigned char (__cdecl *)())0x49D350)();
	params << ns << we;
	return OR_CONTINUE;
}

// 0D5B=12,draw_spotlight_from %1d% %2d% %3d% to %4d% %5d% %6d% base_radius %7d% target_radius %8d% enable_shadow %9d% shadow_intensity %10d% flag1 %11d% flag2 %12d%
// 0D5B: draw_spotlight_from 0@ 1@ 2@ to 3@ 4@ 5@ base_radius 1.0 target_radius 5.0 enable_shadow 1 shadow_intensity 1.0 flag1 1 flag2 1
// SCR: DRAW_SPOTLIGHT
OpcodeResult WINAPI General::AddSpotLight(CScriptThread* thread)
{
	OpcodeParams params(thread, 12);
	if(spotlightDrawer.m_dwNumSpotLightsThisFrame < MAX_NO_SPOTLIGHTS)
	{
		params >> spotlightDrawer.m_aSpotLights[spotlightDrawer.m_dwNumSpotLightsThisFrame].m_vOrigin;
		params >> spotlightDrawer.m_aSpotLights[spotlightDrawer.m_dwNumSpotLightsThisFrame].m_vTarget;
		params >> spotlightDrawer.m_aSpotLights[spotlightDrawer.m_dwNumSpotLightsThisFrame].m_fOriginRadius;
		params >> spotlightDrawer.m_aSpotLights[spotlightDrawer.m_dwNumSpotLightsThisFrame].m_fTargetRadius;
		params >> spotlightDrawer.m_aSpotLights[spotlightDrawer.m_dwNumSpotLightsThisFrame].m_nEnableShadow;
		params >> spotlightDrawer.m_aSpotLights[spotlightDrawer.m_dwNumSpotLightsThisFrame].m_nShadowIntensity;
		params >> spotlightDrawer.m_aSpotLights[spotlightDrawer.m_dwNumSpotLightsThisFrame].m_nFlag1;
		params >> spotlightDrawer.m_aSpotLights[spotlightDrawer.m_dwNumSpotLightsThisFrame].m_nFlag2;
		spotlightDrawer.m_dwNumSpotLightsThisFrame++;
	}
	return OR_CONTINUE;
}

// 0D5C=3,%3d% =  get_car %1d% light %2d% damage_state
// 0D5C: 1@ = get_car 0@ light HEAD_LIGHT_LEFT damage_state
// SCR: GET_CAR_LIGHT_DAMAGE_STATUS
OpcodeResult WINAPI General::CarLightGetDamageState(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	CVehicle *vehicle; unsigned int handle, lightId;
	params >> handle >> lightId;
	vehicle = params.AtHandle<CVehicle>(handle);
	params << ((unsigned char (__thiscall *)(CDamageManager *, unsigned int))0x6C2130)((CDamageManager *)(
		(unsigned int)vehicle + 0x5A0), lightId);
	return OR_CONTINUE;
}

// 0D5D=3,set_car %1d% light %2d% damage_state %3d%
// 0D5D: set_car 0@ light HEAD_LIGHT_LEFT damage_state 0
// SCR: SET_CAR_LIGHT_DAMAGE_STATUS
OpcodeResult WINAPI General::CarLightSetDamageState(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	CVehicle *vehicle; unsigned int handle, lightId, state;
	params >> handle >> lightId >> state;
	vehicle = params.AtHandle<CVehicle>(handle);
	((unsigned char (__thiscall *)(CDamageManager *, unsigned int, unsigned char))0x6C2100)((CDamageManager *)(
		(unsigned int)vehicle + 0x5A0), lightId, state);
	return OR_CONTINUE;
}

// 0D5E=3,get_vehicle %1d% class_to %2d% subclass_to %3d%
// 0D5E: get_vehicle 0@ class_to 1@ subclass_to 2@
// SCR: GET_VEHICLE_CLASS_AND_SUBCLASS
OpcodeResult WINAPI General::GetVehicleClass(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	CVehicle *vehicle; unsigned int handle;
	params >> handle;
	vehicle = params.AtHandle<CVehicle>(handle);
	params << static_cast<unsigned int>(vehicle->m_nVehicleClass) << static_cast<unsigned int>(vehicle->m_nVehicleSubClass);
	return OR_CONTINUE;
}

// 0D5F=7,get_vehicle %1d% dummy_element %2d% position %3d% to %5d% %6d% %7d% %4d% // IF and SET
// 0D5F: get_vehicle 0@ dummy_element TAILIGHTS position WORLD to 1@ 2@ 3@ invert_x false // IF and SET
// SCR: GET_VEHICLE_DUMMY_POSN
OpcodeResult WINAPI General::GetVehicleDummyPosn(CScriptThread* thread)
{
	OpcodeParams params(thread, 7);
	CVehicle *vehicle; CVehicleModelInfo *vehModel; unsigned int handle, dummy, posflag, xflag;
	CVector posn(0.0f, 0.0f, 0.0f);
	params >> handle >> dummy >> posflag >> xflag;
	if(dummy < 15)
	{
		vehicle = params.AtHandle<CVehicle>(handle);
		vehModel = (CVehicleModelInfo *)CModelInfo::ms_modelInfoPtrs[vehicle->m_nModelIndex];
		if(vehModel && vehModel->m_pVehicleStruct)
		{
			posn = vehModel->m_pVehicleStruct->m_avDummyPos[dummy];
			if(xflag)
				posn.x *= -1.0f;
			if(posflag)
				posn = vehicle->TransformFromObjectSpace(posn);
			params << posn << orTrue;
			return OR_CONTINUE;
		}
	}
	params << posn << orFalse;
	return OR_CONTINUE;
}

auto CreateProjectile = (char(__cdecl *)(int, int, float, float, float, float, CVector *, int))0x737C80;

// 0D60=10,create_projectile_type %1d% launched_from_entity %2d% origin %3d% %4d% %5d% target %6d% %7% %8d% target_entity %9d% force %10d%
// 0D60: create_projectile_type PROJECTILE_MISSILE launched_from_entity 0@ origin 1@ 2@ 3@ target 4@ 5@ 6@ target_entity 0 force 1.0 // IF and SET
// SCR: CREATE_PROJECTILE
OpcodeResult WINAPI General::AddProjectile(CScriptThread* thread)
{
	OpcodeParams params(thread, 10);
	unsigned int type, entity, targetEntity; float force; CVector origin, target;
	params >> type >> entity >> origin >> target >> targetEntity >> force;
	if(CreateProjectile(entity, type, origin.x, origin.y, origin.z, force, &target, targetEntity))
		params << orTrue;
	else
		params << orFalse;
	return OR_CONTINUE;
}

// 0D62=2,set_car %1d% remap_texture %2d% // removed in NO 2.0
// 0D62: set_car 0@ remap_texture 1@ // removed in NO 2.0
// SCR: SET_CAR_REMAP_TEXTURE
OpcodeResult WINAPI General::SetCarRemap(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	return OR_CONTINUE;
}

// 0D63=5,set_car %1d% color %2d% RGB %3d% %4d% %5d%
// 0D63: set_car 0@ color PRIMARY_COLOR RGB 255 255 255
// SCR: SET_CAR_CUSTOM_COLOR
OpcodeResult WINAPI General::SetCarCustomColor(CScriptThread* thread)
{
	OpcodeParams params(thread, 5);
	return OR_CONTINUE;
}

// 0D72=3,get_sfx_volume_to %2d% radio_volume_to %3d% type %1d%
// 0D72: get_sfx_volume_to 0@ radio_volume_to NULL type TYPE_FLOAT
// SCR: GET_GAME_VOLUME
OpcodeResult WINAPI General::GetGameVolume(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int type;
	params >> type;
	if(!params.IsOptionalParam())
		params << (type? (float)FrontEndMenuManager.m_nPrefsSfxVolume : FrontEndMenuManager.m_nPrefsSfxVolume);
	if(!params.IsOptionalParam())
		params << (type? (float)FrontEndMenuManager.m_nPrefsMusicVolume : FrontEndMenuManager.m_nPrefsMusicVolume);
	return OR_CONTINUE;
}

// 0D73=3,get_screen_width_to %2d% height_to %3d% type %1d%
// 0D73: get_screen_width_to 0@ height_to 1@ type TYPE_FLOAT
// SCR: GET_SCREEN_WIDTH_AND_HEIGHT
OpcodeResult WINAPI General::GetScreenWidthHeight(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int type;
	params >> type;
	if(!params.IsOptionalParam())
		params << (type? (float)RsGlobal.maximumWidth : RsGlobal.maximumWidth);
	if(!params.IsOptionalParam())
		params << (type? (float)RsGlobal.maximumHeight : RsGlobal.maximumHeight);
	return OR_CONTINUE;
}
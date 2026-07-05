#include "Colpoint.h"
#include "game_sa\CColpoint.h"
#include "game_sa\CWorld.h"

// 0D3A=20,get_collision_between_points %1d% %2d% %3d% and %4d% %5d% %6d% flags %7d% %8d% %9d% %10d% %11d% %12d% %13d% %14d% ignore_entity %15d% store_point_to %17d% %18d% %19d% entity_to %20d% colpoint_data_to %16d%
// 0D3A: get_collision_between_points 0@ 1@ 2@ and 3@ 4@ 5@ flags 1 1 1 1 1 1 1 1 ignore_entity 0 store_point_to 0@ 1@ 2@ entity_to 3@ colpoint_data_to STD_COLPOINT_DATA // IF and SET
// SCR: GET_COLLISION_BETWEEN_POINTS
OpcodeResult WINAPI Colpoint::GetCollisionBetweenPoints(CScriptThread* thread)
{
	OpcodeParams params(thread, 20);
	CVector origin, target, outPoint; unsigned int flag[8]; CEntity *colEntity, *ignoringEntity; CColPoint *colPoint; bool result;
	params >> origin >> target >> flag[0] >> flag[1] >> flag[2] >> flag[3] >> flag[4] >> flag[5] >> flag[6] >> flag[7] >>
		ignoringEntity >> colPoint;
	CWorld::pIgnoreEntity = ignoringEntity;
	result = CWorld::ProcessLineOfSight(origin, target, *colPoint, colEntity, flag[0], flag[1], flag[2], flag[3], flag[4], flag[5], 
		flag[6], flag[7]);
	CWorld::pIgnoreEntity = NULL;
	if(result)
		params << colPoint->m_vecPoint << colEntity << orTrue;
	else
		params << CVector(0.0, 0.0, 0.0) << NULL << orFalse;
	return OR_CONTINUE;
}

// 0D3B=4,get_colpoint_data %1d% normal_XYZ_to %2d% %3d% %4d%
// 0D3B: get_colpoint_data STD_COLPOINT_DATA normal_XYZ_to 0@ 1@ 2@
// SCR: GET_COL_DATA_NORMAL_VECTOR
OpcodeResult WINAPI Colpoint::GetNormal(CScriptThread* thread)
{
	OpcodeParams params(thread, 4);
	CColPoint *colPoint;
	params >> colPoint;
	params << colPoint->m_vecNormal;
	return OR_CONTINUE;
}

// 0D3C=2,get_colpoint_data %1d% depth_to %2d%
// 0D3C: get_colpoint_data STD_COLPOINT_DATA depth_to 0@
// SCR: GET_COL_DATA_DEPTH
OpcodeResult WINAPI Colpoint::GetDepth(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	CColPoint *colPoint;
	params >> colPoint;
	params << colPoint->m_fDepth;
	return OR_CONTINUE;
}

// 0D3D=2,get_colpoint_data %1d% surface_to %2d%
// 0D3D: get_colpoint_data STD_COLPOINT_DATA surface_to 0@
// SCR: GET_COL_DATA_SURFACE
OpcodeResult WINAPI Colpoint::GetSurface(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	CColPoint *colPoint;
	params >> colPoint;
	params << colPoint->m_nSurfaceTypeB;
	return OR_CONTINUE;
}

// 0D3E=2,get_colpoint_data %1d% lighting_to %2d%
// 0D3E: get_colpoint_data STD_COLPOINT_DATA lighting_to 0@
// SCR: GET_COL_DATA_LIGHTING
OpcodeResult WINAPI Colpoint::GetLighting(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	CColPoint *colPoint;
	params >> colPoint;
	params << static_cast<unsigned char>(colPoint->m_nLightingB.day | (colPoint->m_nLightingB.night << 4));
	return OR_CONTINUE;
}
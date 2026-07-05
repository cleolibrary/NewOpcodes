#include "SpotLightDrawer.h"
#include "Patch.h"

SpotLightDrawer spotlightDrawer;

void SpotLightDrawer::Initialise()
{
	plugin::patch::RedirectCall(0x53E1D6, DrawSpotLights);
}

auto DrawSpotLightCone = (void(cdecl *)(int, float, float, float, float, float, float, float, float, char, char, 
	CVector *, CVector *, CVector *, char, float)) 0x6C58E0;

void SpotLightDrawer::DrawSpotLights()
{
	plugin::CallDynGlobal(0x493E30);
	CVector vec(0.0f, 0.0f, 0.0f);
	if(spotlightDrawer.m_dwNumSpotLightsThisFrame > 0)
	{
		for(int i = 0; i < spotlightDrawer.m_dwNumSpotLightsThisFrame; i++)
	    {
			DrawSpotLightCone(i + 15000, 
				spotlightDrawer.m_aSpotLights[i].m_vOrigin.x, 
				spotlightDrawer.m_aSpotLights[i].m_vOrigin.y, 
				spotlightDrawer.m_aSpotLights[i].m_vOrigin.z, 
				spotlightDrawer.m_aSpotLights[i].m_vTarget.x, 
				spotlightDrawer.m_aSpotLights[i].m_vTarget.y, 
				spotlightDrawer.m_aSpotLights[i].m_vTarget.z, 
				spotlightDrawer.m_aSpotLights[i].m_fTargetRadius,
				spotlightDrawer.m_aSpotLights[i].m_nShadowIntensity,
				spotlightDrawer.m_aSpotLights[i].m_nFlag1,
				spotlightDrawer.m_aSpotLights[i].m_nEnableShadow,
				&vec, &vec, &vec,
				spotlightDrawer.m_aSpotLights[i].m_nFlag2,
				spotlightDrawer.m_aSpotLights[i].m_fOriginRadius);
	    }
		spotlightDrawer.m_dwNumSpotLightsThisFrame = 0;
	}
}
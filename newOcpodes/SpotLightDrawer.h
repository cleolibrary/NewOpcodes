#pragma once

#include "CVector.h"

#define MAX_NO_SPOTLIGHTS 100

struct SpotLight
{
	CVector m_vOrigin, m_vTarget;
	float m_fOriginRadius, m_fTargetRadius;
	unsigned char m_nEnableShadow, m_nShadowIntensity, m_nFlag1, m_nFlag2;
};

class SpotLightDrawer
{
public:
	SpotLight m_aSpotLights[MAX_NO_SPOTLIGHTS];
	unsigned int m_dwNumSpotLightsThisFrame;
	void Initialise();
	static void DrawSpotLights();
};

extern SpotLightDrawer spotlightDrawer;
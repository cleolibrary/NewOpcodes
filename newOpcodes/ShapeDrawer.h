#pragma once

#include "RenderWare.h"
#include "TextureManager.h"
#include "CRGBA.h"

#define MAX_NO_SHAPES 100
#define MAX_NO_VERTICES 20

class NOShape
{
public:
	unsigned char m_nPrimType, m_nNumVertices, m_nAlphaEnable, m_nBlendSrc, m_nBlendDst;
	RwTexture *m_pTexture;
	RwD3D9Vertex m_vertices[MAX_NO_VERTICES];

	void Draw();
};

class ShapeDrawer
{
	NOShape m_shapes[MAX_NO_SHAPES];
public:
	unsigned int m_nNumShapesThisFrame;
	bool DrawShapeThisFrame(unsigned char primType, unsigned char numVertices,
		unsigned char alphaEnable, unsigned char blendSrc, unsigned char dlendDst, RwTexture *texture,
		RwD3D9Vertex *vertices);
	void DrawShapes();
	void SetupShapeVertex(RwD3D9Vertex *vertex, RwV3d posn, float u, float v, float rhw, CRGBA color);
};

extern ShapeDrawer shapeDrawer;
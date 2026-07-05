#include "ShapeDrawer.h"
#include <cstdint>

ShapeDrawer shapeDrawer;

void NOShape::Draw()
{
	if(m_pTexture)
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, m_pTexture->raster);
	else
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(static_cast<uintptr_t>(m_nAlphaEnable)));
	RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void *>(static_cast<uintptr_t>(m_nBlendSrc)));
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void *>(static_cast<uintptr_t>(m_nBlendDst)));
	RwIm2DRenderPrimitive((RwPrimitiveType)m_nPrimType, reinterpret_cast<RwIm2DVertex *>(m_vertices), m_nNumVertices);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, 0);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
	RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void *>(5));
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void *>(6));
}

bool ShapeDrawer::DrawShapeThisFrame(unsigned char primType, unsigned char numVertices,
									 unsigned char alphaEnable, unsigned char blendSrc, unsigned char dlendDst, RwTexture *texture,
									 RwD3D9Vertex *vertices)
{
	if(m_nNumShapesThisFrame < MAX_NO_SHAPES)
	{
		m_shapes[m_nNumShapesThisFrame].m_nNumVertices = numVertices;
		m_shapes[m_nNumShapesThisFrame].m_nPrimType = primType;
		m_shapes[m_nNumShapesThisFrame].m_pTexture = texture;
		m_shapes[m_nNumShapesThisFrame].m_nAlphaEnable = alphaEnable;
		m_shapes[m_nNumShapesThisFrame].m_nBlendSrc = blendSrc;
		m_shapes[m_nNumShapesThisFrame].m_nBlendDst = dlendDst;
		for(unsigned char i = 0; i < numVertices && i < MAX_NO_VERTICES; i++)
		{
			m_shapes[m_nNumShapesThisFrame].m_vertices[i].x = vertices[i].x;
			m_shapes[m_nNumShapesThisFrame].m_vertices[i].y = vertices[i].y;
			m_shapes[m_nNumShapesThisFrame].m_vertices[i].z = vertices[i].z;
			m_shapes[m_nNumShapesThisFrame].m_vertices[i].rhw = vertices[i].rhw;
			m_shapes[m_nNumShapesThisFrame].m_vertices[i].emissiveColor = vertices[i].emissiveColor;
			m_shapes[m_nNumShapesThisFrame].m_vertices[i].u = vertices[i].u;
			m_shapes[m_nNumShapesThisFrame].m_vertices[i].v = vertices[i].v;
		}
		m_nNumShapesThisFrame++;
		return true;
	}
	else
		return false;
}

void ShapeDrawer::DrawShapes()
{
	for(unsigned int i = 0; i < m_nNumShapesThisFrame; i++)
		m_shapes[i].Draw();
	m_nNumShapesThisFrame = 0;
}

void ShapeDrawer::SetupShapeVertex(RwD3D9Vertex *vertex, RwV3d posn, float u, float v, float rhw, CRGBA color)
{
	vertex->x = posn.x;
	vertex->y = posn.y;
	vertex->z = posn.z;
	vertex->u = u;
	vertex->v = v;
	vertex->rhw = rhw;
	vertex->emissiveColor = color.ToInt();
}
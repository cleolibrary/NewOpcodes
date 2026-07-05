#include "Shape.h"
#include "ShapeDrawer.h"
#include "NewOpcodes.h"
#include <math.h>

// 0D40=8,draw_2d_shape_type %3d% texture %4d% numVerts %2d% pVerts %1d% vertexAlpha %5d% srcBlend %6d% dstBlend %7d% _unused %8d%
// 0D40: draw_2d_shape_type PRIMTYPETRIFAN texture 0@ numVerts 4 pVerts 1@ vertexAlpha 0 srcBlend 2 dstBlend 2 priority 0
// SCR: DRAW_SHAPE
OpcodeResult WINAPI Shape::DrawShape(CScriptThread* thread)
{
	OpcodeParams params(thread, 8);
	unsigned int type, texture, numVerts, pVerts, vertexAlpha, srcBlend, dstBlend, unused;
	params >> type >> texture >> numVerts >> pVerts >> vertexAlpha >> srcBlend >> dstBlend >> unused;
	if(shapeDrawer.DrawShapeThisFrame(type, numVerts, vertexAlpha, srcBlend, dstBlend, (RwTexture *)texture, (RwD3D9Vertex *)pVerts))
		params << orTrue;
	else
		params << orFalse;
	return OR_CONTINUE;
}

// 0D41=14,set_vertices %1d% vertex %2d% xyz %5d% %6d% %7d% rhw %8d% RGBA %9d% %10d% %11d% %12d% uv %13d% %14d% invertX %3d% invertY %4d%
// 0D41: set_vertices 0@ vertex 1 xyz 0.0 0.0 0.0 rhw 3.33 RGBA 255 255 255 255 uv 0.0 0.0 screenX false screenY true
// SCR: SETUP_SHAPE_VERTEX
OpcodeResult WINAPI Shape::SetShapeVertex(CScriptThread* thread)
{
	OpcodeParams params(thread, 14);
	unsigned int pVerts, vertex, r, g, b, a, invX, invY;
	RwV3d posn;
	float rhw, u, v;
	params >> pVerts >> vertex >> posn >> rhw >> r >> g >> b >> a >> u >> v >> invX >> invY;
	CRGBA color(b, g, r, a);
	if(invX)
	{
		posn.x = (float)(*(int*)(0xC17044)) - posn.x;
		u = 1.0f - u;
	}
	if(invY)
	{
		posn.y = (float)(*(int*)(0xC17048)) - posn.y;
		v = 1.0f - v;
	}
	shapeDrawer.SetupShapeVertex(pVerts == 1 ? (RwD3D9Vertex *)(pVerts + (vertex - 1) * sizeof(RwD3D9Vertex)) :
		&NewOpcodes::stdParams.m_aVerts[vertex - 1], posn, u, v, rhw, color);
	return OR_CONTINUE;
}

// 0D45=5,rotate_2d_vertices_shape %1d% num_verts %2d% aroundXY %3d% %4d% angle %5d%
// 0D45: rotate_2d_vertices_shape 0@ num_verts 4 aroundXY 1@ 2@ angle 90.0
// SCR: ROTATE_SHAPE_VERTICES
OpcodeResult WINAPI Shape::RotateShapeVertices(CScriptThread* thread)
{
	OpcodeParams params(thread, 5);
	float x, y, xc, yc, a, _sin, _cos; unsigned int vertices, numVerts;
	params >> vertices >> numVerts >> xc >> yc >> a;
	a /= 57.2957795f;
	RwD3D9Vertex *rwVerts = vertices == 1 ? &NewOpcodes::stdParams.m_aVerts[0] : (RwD3D9Vertex *)vertices;
	_sin = sin(a);
	_cos = cos(a);
	while(numVerts)
	{
		x = rwVerts->x;
		y = rwVerts->y;
		rwVerts->x = xc + (x - xc) * _cos + (y - yc) * _sin;
		rwVerts->y = yc - (x - xc) * _sin + (y - yc) * _cos;
		rwVerts++;
		numVerts--;
	}
	return OR_CONTINUE;
}
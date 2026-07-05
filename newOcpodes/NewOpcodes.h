#pragma once

#include <Windows.h>
#include "CLEO.h"
#include "RenderWare.h"
#include "game_sa\CColPoint.h"
#include "ShapeDrawer.h"

#define TOTAL_NUM_OPCODES 128
#define OPCODE_BASE_ID 0xD00

struct tNewOpcodesStdParams
{
	RwV3d m_aVectors[10];
	RtQuat m_aQuats[10];
	RwMatrix m_aMatrices[10];
	CColPoint m_colPoint;
	RwIm2DVertex m_aVerts[MAX_NO_VERTICES];
};

class NewOpcodes
{
	static _pOpcodeHandler OpcodeFunctions[];
public:
	static tNewOpcodesStdParams stdParams;
	static unsigned int m_nCurrentCoronaId;
	static bool Initialise();
	static void ReInitialise();
	static void Shutdown();
	static void DefaultDraw();
	static void BeforeScriptsProcessing();
};
#include "NewOpcodes.h"
#include "plugin.h"
#include "Matrix.h"
#include "Bone.h"
#include "Component.h"
#include "General.h"
#include "Quat.h"
#include "Vector.h"
#include "Memory.h"
#include "Colpoint.h"
#include "Shape.h"
#include "Txd.h"
#include "String.h"
#include "Texture.h"
#include "Text.h"
#include "CLEOAudio.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "ShapeDrawer.h"
#include "SpotLightDrawer.h"
#include "TextDrawer.h"
#include "SpriteDrawer.h"
#include "TxdManager.h"
#include <stdio.h>

tNewOpcodesStdParams NewOpcodes::stdParams;
unsigned int NewOpcodes::m_nCurrentCoronaId;

bool NewOpcodes::Initialise()
{
	for(int i = 0; i < TOTAL_NUM_OPCODES; i++)
	{
		if(!CLEO_RegisterOpcode(OPCODE_BASE_ID + i, OpcodeFunctions[i]))
			return false;
	}
	plugin::Events::initScriptsEvent += ReInitialise;
	plugin::Events::shutdownRwEvent += Shutdown;
	plugin::Events::drawingEvent += DefaultDraw;
	plugin::Events::processScriptsEvent.before += BeforeScriptsProcessing;
	return true;
}

void NewOpcodes::ReInitialise()
{
	TexMgr.UnloadAllTextures();
	m_nCurrentCoronaId = 10000;
	spotlightDrawer.m_dwNumSpotLightsThisFrame = 0;
	shapeDrawer.m_nNumShapesThisFrame = 0;
	textDrawer.m_dwNumPrintsThisFrame = 0;
	spriteDrawer.m_numSpritesThisFrame = 0;
	txdManager.CleanAll();
}

void NewOpcodes::Shutdown()
{
	TexMgr.UnloadAllTextures();
	txdManager.CleanAll();
}

void NewOpcodes::DefaultDraw()
{
	shapeDrawer.DrawShapes();
	textDrawer.DrawPrints();
	spriteDrawer.DrawSprites();
}

void NewOpcodes::BeforeScriptsProcessing()
{
	m_nCurrentCoronaId = 10000;
	shapeDrawer.m_nNumShapesThisFrame = 0;
	spotlightDrawer.m_dwNumSpotLightsThisFrame = 0;
	textDrawer.m_dwNumPrintsThisFrame = 0;
	spriteDrawer.m_numSpritesThisFrame = 0;
}

_pOpcodeHandler NewOpcodes::OpcodeFunctions[] = { 
	Matrix::Multiply, 
	Matrix::RotateOnAxis,
	Matrix::GetXAngle,
	Matrix::GetYAngle,
	Matrix::GetZAngle,
	Matrix::SetPosn,
	Matrix::GetPosn,
	Matrix::GetLocalOffset,
	Matrix::Rotate,
	Matrix::Copy,
	Matrix::TransformPoint,
	Bone::GetMatrix,
	Component::GetMatrix,
	Component::FindComponent,
	Component::SetComponentState,
	General::SetCarModelAlpha,
	General::SetActorModelAlpha,
	General::SetObjectModelAlpha,
	Component::SetComponentModelAlpha,
	Matrix::RotateX,
	Matrix::RotateY,
	Matrix::RotateZ,
	Matrix::FromQuat,
	Quat::FromMatrix,
	Quat::Rotate,
	Quat::Normalise,
	Quat::Multiply,
	General::GetEntityTypeClass,
	Vector::Normalise,
	Matrix::Slerp,
	Quat::Slerp,
	Component::GetChildComponent,
	Component::GetNextComponent,
	Component::GetName,
	Component::GetLTM,
	Component::GetMM,
	Quat::Setup,
	Matrix::Setup,
	Vector::Setup,
	Memory::MemCpy,
	Vector::GetValues,
	Quat::GetValues,
	General::GetCarNumCollidedEntities,
	General::GetActorNumCollidedEntities,
	General::GetObjectNumCollidedEntities,
	General::GetLocalTimeInfo,
	General::SetThreadVar,
	General::GetThreadVar,
	Bone::GetBone,
	Bone::GetBoneOffset,
	Bone::GetBoneQuat,
	General::SetCarWindowState,
	General::GetCarCollidedEntities,
	General::GetActorCollidedEntities,
	General::GetObjectCollidedEntities,
	Memory::SetStructParam,
	Memory::GetStructParam,
	General::GetActorMaxHelath,
	Colpoint::GetCollisionBetweenPoints,
	Colpoint::GetNormal,
	Colpoint::GetSurface,
	Colpoint::GetLighting,
	Colpoint::GetDepth,
	General::CirclesIntersection,
	Shape::DrawShape,
	Shape::SetShapeVertex,
	Txd::LoadTxd,
	Txd::GetTxdId,
	Txd::FindTextureInTxdWithName,
	Shape::RotateShapeVertices,
	Txd::FindTextureInTxdWithId,
	General::GetModelTxd,
	General::GetModelCRC,
	String::StrCmp,
	String::StrCat,
	String::StrStr,
	String::StrLen,
	String::StrCpy,
	Memory::GetStructOffset,
	Memory::SetStructOffset,
	General::AddTemporaryShadow,
	General::AddPermanentShadow,
	General::AddLight,
	General::AddCorona,
	General::AddCoronaEx,
	General::GetSunColors,
	General::GetSunScreenCoors,
	General::GetSunWorldCoors,
	General::GetSunSize,
	General::GetWeather,
	General::GetTraffLightsColor,
	General::AddSpotLight,
	General::CarLightGetDamageState,
	General::CarLightSetDamageState,
	General::GetVehicleClass,
	General::GetVehicleDummyPosn,
	General::AddProjectile,
	Texture::LoadBMPTextureWithAlpha,
	General::SetCarRemap,
	General::SetCarCustomColor,
	Texture::LoadPNGTexture,
	Text::Print,
	Text::PrintEx,
	CLEOAudio::SetAudioStreamPos,
	CLEOAudio::GetAudioStreamPos,
	CLEOAudio::SetAudiStreamEffect,
	CLEOAudio::RemoveAudioStreamEffect,
	CLEOAudio::SetEffectParameters,
	CLEOAudio::GetEffectParameters,
	CLEOAudio::ResetEffect,
	CLEOAudio::SetAudioStreamAttribute,
	CLEOAudio::GetAudioStreamAttribute,
	CLEOAudio::Set3DAudioStreamAttributes,
	CLEOAudio::Get3DAudioStreamAttributes,
	General::GetGameVolume,
	General::GetScreenWidthHeight,
	Component::GetParentComponent,
	Component::GetComponentNumObjects,
	Component::GetComponentObject,
	Component::HideObjectAtomic,
	Component::GetObjectAtomicFlag,
	Component::SetObjectAtomicFlag,
	Component::GetObjectAtomicNumMaterials,
	Component::GetObjectMaterialTexture,
	Texture::LoadDDSTexture,
	Texture::UnloadTexture,
	Sprite::DrawSprite,
	Sprite::DrawSpriteWithGradient
};
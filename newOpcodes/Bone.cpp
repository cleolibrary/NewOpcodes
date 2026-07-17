#include "Bone.h"
#include "game_sa\common.h"

// 0D0B=3,get_actor %1d% bone %2d% matrix_to %3d% // IF and SET
// 0D0B: get_actor $3 bone 6 matrix_to 0@ // IF and SET
// SCR: GET_CHAR_BONE_MATRIX
OpcodeResult WINAPI Bone::GetMatrix(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int handle, bone;
	params >> handle >> bone;
	CPed *ped = params.AtHandle<CPed>(handle);
	if(!ped->m_pRwObject)
	{
		params << NULL << orFalse;
		return OR_CONTINUE;
	}
	ped->UpdateRpHAnim();
	RpHAnimHierarchy *hierarchy = GetAnimHierarchyFromSkinClump((RpClump *)ped->m_pRwObject);
	if(!hierarchy)
		params << reinterpret_cast<RwMatrix *>(&ped->GetMatrix());
	else
		params << &RpHAnimHierarchyGetMatrixArray(hierarchy)[RpHAnimIDGetIndex(hierarchy, bone)];
	params << orTrue;
	return OR_CONTINUE;
}

// 0D30=3,%3d% = actor %1d% bone %2d% // IF and SET
// 0D30: 0@ = actor $3 bone 4 // IF and SET
// SCR: GET_CHAR_BONE
OpcodeResult WINAPI Bone::GetBone(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int handle, boneIndex; char boneName[128]; bool useName = false; AnimBlendFrameData *bone;
	params >> handle;
	CPed *ped = params.AtHandle<CPed>(handle);
	if(params.IsStringParam())
	{
		useName = true;
		params >> boneName;
	}
	else params >> boneIndex;
	if(!ped->m_pRwObject || (useName && *boneName == '\0'))
	{
		params << NULL << orFalse;
		return OR_CONTINUE;
	}
	if(useName)
	{
		bone = RpAnimBlendClumpFindFrame((RpClump *)ped->m_pRwObject, boneName);
		if(bone)
			params << bone << orTrue;
		else
			params << NULL << orFalse;
	}
	else
		params << &RpClumpGetAnimBlendClumpData((RpClump *)ped->m_pRwObject)->m_pFrames[boneIndex] << orTrue;
	return OR_CONTINUE;
}

// 0D31=2,%2d% = bone %1d% offset_vector
// 0D31: 1@ = bone 0@ offset_vector
// SCR: GET_BONE_OFFSET
OpcodeResult WINAPI Bone::GetBoneOffset(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	AnimBlendFrameData *bone;
	params >> bone;
	params << &bone->m_vecOffset;
	return OR_CONTINUE;
}

// 0D32=2,%2d% = bone %1d% quat
// 0D32: 1@ = bone 0@ quat
// SCR: GET_BONE_QUAT
OpcodeResult WINAPI Bone::GetBoneQuat(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	AnimBlendFrameData *bone;
	params >> bone;
	if(!bone || !bone->m_pIFrame)
	{
		params << NULL;
		return OR_CONTINUE;
	}
	RtQuat *quat = (RtQuat *)bone->m_pIFrame;
	params << quat;
	return OR_CONTINUE;
}
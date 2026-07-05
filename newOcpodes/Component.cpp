#include "Component.h"
#include "game_sa\CVehicle.h"
#include "game_sa\CClumpModelInfo.h"
#include "game_sa\CVisibilityPlugins.h"
#include "game_sa\NodeName.h"
#include <cstdint>

// 0D0C=3,get_car %1d% component %2s% matrix_to %3d% // IF and SET
// 0D0C: get_car 0@ component "wheel_lf_dummy" matrix_to 1@ // IF and SET
// SCR: GET_CAR_COMPONENT_MATRIX
OpcodeResult WINAPI Component::GetMatrix(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int handle; RwFrame *component; char name[128];
	params >> handle >> name;
	CVehicle *vehicle = params.AtHandle<CVehicle>(handle);
	if(vehicle->m_pRwObject && *name != '\0')
	{
		component = CClumpModelInfo::GetFrameFromName((RpClump *)vehicle->m_pRwObject, name);
		if(component)
		{
			params << RwFrameGetLTM(component) << orTrue;
			return OR_CONTINUE;
		}
	}
	params << NULL << orFalse;
	return OR_CONTINUE;
}

// 0D0D=3,%3d% = get_car %1d% component %2s% // IF and SET
// 0D0D: 1@ = get_car 0@ component "wheel_lf_dummy" // IF and SET
// SCR: GET_CAR_COMPONENT
OpcodeResult WINAPI Component::FindComponent(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int handle; RwFrame *component; char name[128];
	params >> handle >> name;
	CVehicle *vehicle = params.AtHandle<CVehicle>(handle);
	if(vehicle->m_pRwObject && *name != '\0')
	{
		component = CClumpModelInfo::GetFrameFromName((RpClump *)vehicle->m_pRwObject, name);
		if(component)
		{
			params << component << orTrue;
			return OR_CONTINUE;
		}
	}
	params << NULL << orFalse;
	return OR_CONTINUE;
}

// 0D0E=3,set_car %1d% component %2s% state %3d% // IF and SET
// 0D0E: set_car 0@ component "bump_front_dummy" state STATE_DAM // IF and SET
// SCR: SET_CAR_COMPONENT_STATE
OpcodeResult WINAPI Component::SetComponentState(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int handle; RwFrame *component; char name[128]; unsigned int state;
	params >> handle >> name >> state;
	CVehicle *vehicle = params.AtHandle<CVehicle>(handle);
	if(vehicle->m_pRwObject && *name != '\0')
	{
		component = CClumpModelInfo::GetFrameFromName((RpClump *)vehicle->m_pRwObject, name);
		if(component)
		{
			vehicle->SetComponentVisibility(component, state);
			params << orTrue;
			return OR_CONTINUE;
		}
	}
	params << orFalse;
	return OR_CONTINUE;
}

// 0D12=3,set_car %1d% component %2s% model_alpha %3d% // IF and SET
// 0D12: set_car 0@ component "door_lf_dummy" model_alpha 50 // IF and SET
// SCR: SET_CAR_COMPONENT_MODEL_ALPHA
OpcodeResult WINAPI Component::SetComponentModelAlpha(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	unsigned int handle, alpha; RwFrame *component; char name[128];
	params >> handle >> name >> alpha;
	CVehicle *vehicle = params.AtHandle<CVehicle>(handle);
	if(vehicle->m_pRwObject && *name != '\0')
	{
		component = CClumpModelInfo::GetFrameFromName((RpClump *)vehicle->m_pRwObject, name);
		if(component)
		{
			RwFrameForAllObjects(
				component, 
				[](RwObject *object, void *data) -> RwObject * 
				{
					if(RwObjectGetType(object) == rpATOMIC)
						CVehicle::SetComponentAtomicAlpha(reinterpret_cast<RpAtomic *>(object), static_cast<int>(reinterpret_cast<uintptr_t>(data)));
					return object;
				}, 
				reinterpret_cast<void *>(alpha));
			params << orTrue;
			return OR_CONTINUE;
		}
	}
	params << orFalse;
	return OR_CONTINUE;
}

// 0D1F=2,%2d% = component %1d% child
// 0D1F: 1@ = component 0@ child
// SCR: GET_COMPONENT_CHILD_COMPONENT
OpcodeResult WINAPI Component::GetChildComponent(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwFrame *component;
	params >> component;
	params << component->child;
	return OR_CONTINUE;
}

// 0D20=2,%2d% = component %1d% next_component
// 0D20: 1@ = component 0@ next_component
// SCR: GET_COMPONENT_NEXT_COMPONENT
OpcodeResult WINAPI Component::GetNextComponent(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwFrame *component;
	params >> component;
	params << component->next;
	return OR_CONTINUE;
}

// 0D21=2,%2s% = component %1d% name
// 0D21: 1@v = component 0@ name
// SCR: GET_COMPONENT_NAME
OpcodeResult WINAPI Component::GetName(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwFrame *component;
	params >> component;
	params << GetFrameNodeName(component);
	return OR_CONTINUE;
}

// 0D22=2,%2d% = component %1d% world_matrix
// 0D22: 1@ = component 0@ world_matrix
// SCR: GET_COMPONENT_WORLD_MATRIX
OpcodeResult WINAPI Component::GetLTM(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwFrame *component;
	params >> component;
	params << RwFrameGetLTM(component);
	return OR_CONTINUE;
}

// 0D23=2,%2d% = component %1d% modelling_matrix
// 0D23: 1@ = component 0@ modelling_matrix
// SCR: GET_COMPONENT_MODELLING_MATRIX
OpcodeResult WINAPI Component::GetMM(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwFrame *component;
	params >> component;
	params << &component->modelling;
	return OR_CONTINUE;
}

// 0D74=2,%2d% = component %1d% parent_component
// 0D74: 1@ = component 0@ parent_component
// SCR: GET_COMPONENT_PARENT_COMPONENT
OpcodeResult WINAPI Component::GetParentComponent(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwFrame *component;
	params >> component;
	params << component->object.parent;
	return OR_CONTINUE;
}

struct AtomicSearchInfo
{
	unsigned int counter;
	unsigned int number;
	RpAtomic *result;
};

// 0D75=2,%2d% = component %1d% num_objects
// 0D75: 1@ = component 0@ num_objects
// SCR: GET_COMPONENT_NUM_OBJECTS
OpcodeResult WINAPI Component::GetComponentNumObjects(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RwFrame *component;
	params >> component;
	unsigned int counter = 0;
    RwFrameForAllObjects(
		component, 
		[](RwObject* object, void* data) -> RwObject* 
		{
			if (RwObjectGetType(object) == rpATOMIC)
				++(*reinterpret_cast<unsigned int*>(data));
			return object;
		}, 
		&counter);
	params << counter;
	return OR_CONTINUE;
}

// 0D76=3,%2d% = component %1d% object 0
// 0D76: 1@ = component 0@ object 0
// SCR: GET_COMPONENT_OBJECT
OpcodeResult WINAPI Component::GetComponentObject(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	RwFrame *component; RpAtomic *object = NULL; unsigned int number, counter = 0;
	params >> component >> number;
	AtomicSearchInfo data;
	data.counter = 0;
	data.number = number;
	data.result = NULL;
    RwFrameForAllObjects(
        component,
        [](RwObject* object, void* rawData) -> RwObject* 
		{
			AtomicSearchInfo* data = reinterpret_cast<AtomicSearchInfo*>(rawData);
			if (RwObjectGetType(object) == rpATOMIC) {
				if (data->counter == data->number) {
					data->result = reinterpret_cast<RpAtomic*>(object);
					return NULL;
				}
				data->counter++;
			}
			return object;
        },
        &data);
	params << data.result;
	if(data.result)
		params << orTrue;
	else
		params << orFalse;
	return OR_CONTINUE;
}

// 0D77=2,object_atomic %1d% hide 1
// 0D77: object_atomic 0@ hide 1
// SCR: HIDE_OBJECT_ATOMIC
OpcodeResult WINAPI Component::HideObjectAtomic(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RpAtomic *object; unsigned int hide;
	params >> object >> hide;
	if(hide)
		object->object.object.flags = 0;
	else
		object->object.object.flags = 4;
	return OR_CONTINUE;
}

// 0D78=3,%3d% = get_object %1d% atomic_flag %2d%
// 0D78: 2@ = get_object 0@ atomic_flag 1@
// SCR: GET_OBJECT_ATOMIC_FLAG
OpcodeResult WINAPI Component::GetObjectAtomicFlag(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	RpAtomic *object; unsigned int flag;
	params >> object >> flag;
	if(RpAtomicGetVisibilityPlugin(object)->m_wFlags & flag)
		params << TRUE;
	else
		params << FALSE;
	return OR_CONTINUE;
}

// 0D79=3,set_object 0@ atomic_flag 1@ state ENABLE
// 0D79: set_object %1d% atomic_flag %2d% state %3d%
// SCR: SET_OBJECT_ATOMIC_FLAG
OpcodeResult WINAPI Component::SetObjectAtomicFlag(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	RpAtomic *object; unsigned int flag, state;
	params >> object >> flag >> state;
	if(state)
		CVisibilityPlugins::SetAtomicFlag(object, static_cast<int>(flag));
	else
		CVisibilityPlugins::ClearAtomicFlag(object, static_cast<int>(flag));
	return OR_CONTINUE;
}

// 0D7A=2,%2d% = get_object %1d% num_materials // IF and SET
// 0D7A: 1@ = get_object 0@ num_materials // IF and SET
// SCR: GET_OBJECT_ATOMIC_NUM_MATERIALS
OpcodeResult WINAPI Component::GetObjectAtomicNumMaterials(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	RpAtomic *object;
	params >> object;
	if(object->geometry)
		params << object->geometry->matList.numMaterials << orTrue;
	else
		params << 0 << orFalse;
	return OR_CONTINUE;
}

// 0D7B=3,%3d% = get_object %1d% material %2d% texture // IF and SET
// 0D7B: 1@ = get_object 0@ material 0 texture // IF and SET
// SCR: GET_OBJECT_ATOMIC_MATERIAL_TEXTURE
OpcodeResult WINAPI Component::GetObjectMaterialTexture(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	RpAtomic *object; unsigned int material;
	params >> object >> material;
	if(object->geometry && object->geometry->matList.numMaterials > material)
		params << object->geometry->matList.materials[material]->texture << orTrue;
	else
		params << NULL << orFalse;
	return OR_CONTINUE;
}
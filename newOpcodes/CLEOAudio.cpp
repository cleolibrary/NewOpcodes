#include "CLEOAudio.h"

// 0D67=2,set_audiostream %1d% position_time %2d%
// 0D67: set_audiostream 0@ position_time 30.0
// SCR: SET_AUDIO_STREAM_POSITION_TIME
OpcodeResult WINAPI CLEOAudio::SetAudioStreamPos(CScriptThread* thread)
{
	OpcodeParams(thread, 2);
	return OR_CONTINUE;
}

// 0D68=2, %2d% = get_audiostream %1d% position_time
// 0D68: 1@ = get_audiostream 0@ position_time
// SCR: GET_AUDIO_STREAM_POSITION_TIME
OpcodeResult WINAPI CLEOAudio::GetAudioStreamPos(CScriptThread* thread)
{
	OpcodeParams(thread, 2);
	return OR_CONTINUE;
}

// 0D69=4,%3d% = set_audiostream %1d% effect %2d% priority %3d%
// 0D69: 1@ = set_audiostream 0@ effect AUDIOSTREAMEFFECT_ECHO priority 0
// SCR: SET_AUDIO_STREAM_EFFECT
OpcodeResult WINAPI CLEOAudio::SetAudiStreamEffect(CScriptThread* thread)
{
	OpcodeParams(thread, 4);
	return OR_CONTINUE;
}

// 0D6A=2,remove_audiostream %1d% effect %2d%
// 0D6A: remove_audiostream 0@ effect 1@
// SCR: REMOVE_AUDIO_STREAM_EFFECT
OpcodeResult WINAPI CLEOAudio::RemoveAudioStreamEffect(CScriptThread* thread)
{
	OpcodeParams(thread, 2);
	return OR_CONTINUE;
}

// 0D6B=2,set_audiostream_effect %1d% parameters_from_buf %2d%
// 0D6B: set_audiostream_effect 0@ parameters_from_buf 1@
// SCR: SET_AUDIO_STREAM_PARAMETERS
OpcodeResult WINAPI CLEOAudio::SetEffectParameters(CScriptThread* thread)
{
	OpcodeParams(thread, 2);
	return OR_CONTINUE;
}

// 0D6C=2,get_audiostream_effect %1d% parameters_to_buf %2d%
// 0D6C: get_audiostream_effect 0@ parameters_to_buf 1@
// SCR: GET_AUDIO_STREAM_PARAMETERS
OpcodeResult WINAPI CLEOAudio::GetEffectParameters(CScriptThread* thread)
{
	OpcodeParams(thread, 2);
	return OR_CONTINUE;
}

// 0D6D=1,reset_audiostream_effect %1d%
// 0D6D: reset_audiostream_effect 0@
// SCR: RESET_AUDIO_STREAM_EFFECT
OpcodeResult WINAPI CLEOAudio::ResetEffect(CScriptThread* thread)
{
	OpcodeParams(thread, 1);
	return OR_CONTINUE;
}

// 0D6E=3,set_audiostream %1d% attribute %2d% to %3d%
// 0D6E: set_audiostream 0@ attribute AUDIOSTREAMATTRIB_SPEED to 2.0
// SCR: SET_AUDIO_STREAM_ATTRIBUTE
OpcodeResult WINAPI CLEOAudio::SetAudioStreamAttribute(CScriptThread* thread)
{
	OpcodeParams(thread, 3);
	return OR_CONTINUE;
}

// 0D6F=3, %3d% = get_audiostream %1d% attribute %2d%
// 0D6F: 1@ = get_audiostream 0@ attribute AUDIOSTREAMATTRIB_SPEED
// SCR: GET_AUDIO_STREAM_ATTRIBUTE
OpcodeResult WINAPI CLEOAudio::GetAudioStreamAttribute(CScriptThread* thread)
{
	OpcodeParams(thread, 3);
	return OR_CONTINUE;
}

// 0D70=7,set_3d_audiostream %1d% 3d_attributes_mode %2d% min %3d% max %4d% iangle %5d% oangle %6d% outvol %7d%
// 0D70: set_3d_audiostream 0@ 3d_attributes_mode BASS_3DMODE_NORMAL min -1.0 max -1.0 iangle -1 oangle -1 outvol -1.0
// SCR: SET_3D_AUDIO_STREAM_ATTRIBUTES
OpcodeResult WINAPI CLEOAudio::Set3DAudioStreamAttributes(CScriptThread* thread)
{
	OpcodeParams(thread, 7);
	return OR_CONTINUE;
}

// 0D71=7,get_3d_audiostream %1d% 3d_attributes_mode_to %2d% min_to %3d% max_to %4d% iangle_to %5d% oangle_to %6d% outvol_to %7d%
// 0D71: get_3d_audiostream 0@ 3d_attributes_mode_to 1@ min_to 2@ max_to 3@ iangle_to NULL oangle_to NULL outvol_to NULL
// SCR: GET_3D_AUDIO_STREAM_ATTRIBUTES
OpcodeResult WINAPI CLEOAudio::Get3DAudioStreamAttributes(CScriptThread* thread)
{
	OpcodeParams(thread, 7);
	return OR_CONTINUE;
}
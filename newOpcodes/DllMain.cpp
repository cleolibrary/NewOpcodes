#include <Windows.h>
#include "NewOpcodes.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if(ul_reason_for_call == DLL_PROCESS_ATTACH)
		return NewOpcodes::Initialise();
	else
		return TRUE;
}
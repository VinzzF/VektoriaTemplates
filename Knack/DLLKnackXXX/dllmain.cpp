// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "KnackXXX.h"



namespace Vektoria
{
	extern "C" __declspec(dllexport) CKnackXXX * CreateKnackModule()
	{
		return new CKnackXXX;
	}
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


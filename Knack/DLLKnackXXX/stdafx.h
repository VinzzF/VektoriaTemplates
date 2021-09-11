//-----------------------------------------------------------------------
// Pre-kompilierter Header
// 
// Erklärung: Für häufig verwendete Bibliotheken im gesamten Modul
// Autor    : 
// Zeit     : 
//------------------------------------------------------------------------

#pragma once

// Windows
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
//#define _WIN32_WINNT _WIN32_WINNT_WIN10
#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>

// für Dateisystem- / Pfad-Operationen
#include <shlwapi.h>
#pragma comment (lib, "Shlwapi.lib")

// Vektoria
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif

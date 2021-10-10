#pragma once

//-----------------------------------------------------------------------
// PCH (pre complied header)
// 
// Erklärung: Prä-compilierte Header Datei für Biliotheks-Includes
//            Vermeidet mühselige, mehrfache Inkludierung von Headern
//            und beschleunigt die Kompilierzeit immens
// Autor    : Vinzenz Funk
// Zeit     : seit Oktober 2021
//------------------------------------------------------------------------

// Windows
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
//#define _WIN32_WINNT _WIN32_WINNT_WIN10
#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>

// für Dateisystem- / Pfad-Operationen
#include <shlwapi.h>
#pragma comment (lib, "Shlwapi.lib")

// C Libs
#include <cassert>

// C++ / STL Libs
#include <iostream>

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

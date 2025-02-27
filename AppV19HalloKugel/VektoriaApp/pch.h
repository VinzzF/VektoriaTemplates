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
#define WIN32_LEAN_AND_MEAN
//#define _WIN32_WINNT _WIN32_WINNT_WIN10	// nicht zwingend nötig
#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>

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
#include "Vektoria\Root.h"
using namespace Vektoria;	// sollte bei größeren Projekten herausgenommen werden

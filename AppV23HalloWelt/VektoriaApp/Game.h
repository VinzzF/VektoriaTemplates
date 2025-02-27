#pragma once
//-----------------------------------------------------------------------
// CGame
// 
// Erklärung : Eine Klasse, 
//             sinnfällig in eine Windows-Applikation eingebettet,
//             welche eine Hello-Welt-Kugel als Beispiel und zum Testen erzeugt. 
// Autor     : Prof. Dr. Tobias Breiner
// Ort       : Pfungstadt
// Zeit      : seit Aug. 2011 (mit seitdem ständigen Verbesserungs-Updates)
// Copyright : Tobias Breiner  
// Disclaimer: Nutzung auf eigene Gefahr, keine Gewähr, no warranty!
//------------------------------------------------------------------------



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

using namespace Vektoria;


class CGame
{
public:
	// Wird vor Begin einmal aufgerufen (Konstruktor):
	CGame();																				

	// Wird nach Ende einmal aufgerufen (Destruktor):
	~CGame();																				


	// Wird zu Begin einmal aufgerufen:
	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	

	// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen:
	void Tick(float fTime, float fTimeDelta);						

	// Wird am Ende einmal aufgerufen:
	void Fini();																				

	// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat:
	void WindowReSize(int iNewWidth, int iNewHeight);											

	// Holt das minimale Zeitdelta zur eventuellen Frame-Rate-Beschränkung:
	float GetTimeDeltaMin();																	

	// Holt die Versionsnummer:
	float GetVersion();


private:
    // Hier ist Platz für Deine Vektoriaobjekte:
	CRoot m_zr;
	CFrame m_zf;
	CViewport m_zv;
	CLightParallel m_zl;
	CScene m_zs;

	CPlacement m_zpCamera;
	CCamera m_zc;

	CPlacement m_zpSphere;
	CGeoSphere m_zgSphere;
	CMaterial m_zmSphereLowRes;
	CMaterial m_zmSphereHighRes;

	CPlacement m_zpSky;
	CGeoSphere m_zgSky;
	CMaterial m_zmSkyLowRes;
	CMaterial m_zmSkyHighRes;

	CWriting m_zwHalloWelt;
	CWriting m_azwAdditionalText[4];
	CWritingFont m_zwfRed;
	CWritingFont m_zwfWhite;
};



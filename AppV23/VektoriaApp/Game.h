#pragma once
//-----------------------------------------------------------------------
// CGame
// 
// Erkl�rung : Eine weitestgehend leere Klasse, 
//             sinnf�llig in eine Windows-Applikation eingebettet,
//             um ein Spiel bzw. eine 3D-Simulation zu erzeugen
// Autor     : Prof. Dr. Tobias Breiner
// Ort       : Pfungstadt
// Zeit      : seit Aug. 2011 (mit seitdem st�ndigen Verbesserungs-Updates)
// Copyright : Tobias Breiner  
// Disclaimer: Nutzung auf eigene Gefahr, keine Gew�hr, no warranty!
//------------------------------------------------------------------------


class CGame
{
public:
	// Wird vor Begin einmal aufgerufen (Konstruktor):
	CGame();																				

	// Wird nach Ende einmal aufgerufen (Destruktor):
	~CGame();																				


	// Wird zu Begin einmal aufgerufen:
	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	

	// Wird w�hrend der Laufzeit bei jedem Bildaufbau aufgerufen:
	void Tick(float fTime, float fTimeDelta);						

	// Wird am Ende einmal aufgerufen:
	void Fini();																				

	// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergr��e ver�ndert hat:
	void WindowReSize(int iNewWidth, int iNewHeight);											

	// Holt das minimale Zeitdelta zur eventuellen Frame-Rate-Beschr�nkung:
	float GetTimeDeltaMin();																	

	// Holt die Versionsnummer:
	float GetVersion();


private:

	// Die Wurzel des Szenengrafen: 
	CRoot m_zr; 

	// Hier ist Platz f�r Deine weiteren Vektoriaobjekte:


};



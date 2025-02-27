#include "pch.h"
#include "Game.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	//---------------------------------
	// Initialisiere die Knotenobjekte:
	//---------------------------------

	// Zuallererst muss die Root mit dem Splash-Screen initialisiert werden, 
	// damit die Engine freigeschaltet wird:
	m_zr.Init(psplash);

	// Hier kommen alle weiteren Initialisierungen hinein: 

}

void CGame::Tick(float fTime, float fTimeDelta)
{
	//-------------------------------------------
	// Ver�nderungen w�hrend der Simulationszeit:
	//-------------------------------------------

	// Hier kommen die Ver�nderungen pro Renderschritt hinein: 



	// Traversiere am Schluss den Szenengraf und rendere:
	m_zr.Tick(fTimeDelta);
}

void CGame::Fini()
{
	//-------------------------------
	// Finalisiere die Knotenobjekte:
	//-------------------------------

	// Hier die Finalisierung Deiner Vektoria-Objekte einf�gen:

	// Auch die Root sollte finalisiert werden:   
	m_zr.Fini();
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergr��e ver�ndert wurde.
	// Hier kannst Du dann die Aufl�sung des Viewports neu einstellen:
	// z.B. mittels: m_zf.ReSize(iNewWidth, iNewHeight);
}

float CGame::GetTimeDeltaMin()
{
	return m_zr.GetTimeDeltaMin();
}

float CGame::GetVersion()
{
	return m_zr.GetVersion();
}



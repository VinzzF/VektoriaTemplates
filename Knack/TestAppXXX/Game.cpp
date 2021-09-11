#include "stdafx.h"
#include "Game.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	m_zr.Init(psplash);
	m_zc.Init(QUARTERPI);
	// m_zf.SetApiRender(eApiRender_DirectX11_Shadermodel50_Monolight);
	m_zf.Init(hwnd, procOS); 
	m_zv.InitFull(&m_zc);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));
	m_zgSphere.Init(1.5F, nullptr, 50, 50);

	m_zr.AddFrame(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);
	m_zs.AddPlacement(&m_zpSphere);
	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddLightParallel(&m_zl);
	m_zpCamera.AddCamera(&m_zc);
	m_zpSphere.AddGeo(&m_zgSphere);

	m_zpCamera.TranslateZ(8.0f);

	// Das Knack-Modul heißt "XXX" (andere Knack-Module haben andere Namen)
	// Log-Daten werden automatisch bereits gesetzt, kein manueller Aufruf von SetLogFileData() nötig!
	m_knackXXX.Init("XXX", "default_xxx.ini", &m_zs, &m_zv);

	// Abfragen von Properties des Knack-Moduls
	int test = m_knackXXX.GetPropInt(0, 0);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Veränderungen einfügen:
	m_zr.Tick(fTimeDelta);

	// Zur Vermeidung extrem hoher Frameraten in einer leeren Szene, falls benötigt
	//Sleep(1);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}


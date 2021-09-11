#include "Game.h"



CGame::CGame(void)
{
}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einf�gen:
	m_zr.Init(psplash);
	m_zf.Init(hwnd, procOS);
	m_zv.InitFull(&m_zc);
	m_zi.Init("textures\\HalloWelt.png");
	m_zo.InitFull(&m_zi);
	m_zc.Init();

	m_zr.AddFrame(&m_zf);
	m_zr.AddScene(&m_zs);
	m_zs.AddPlacement(&m_zp);
	m_zp.AddCamera(&m_zc);
	m_zf.AddViewport(&m_zv);
	m_zv.AddOverlay(&m_zo);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Hier die Echtzeit-Ver�nderungen einf�gen:
	m_zr.Tick(fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einf�gen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergr��e ver�ndert wurde.
	// Hier kannst Du dann die Aufl�sung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}


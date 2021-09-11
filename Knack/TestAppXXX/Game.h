#pragma once

class CGame
{
public:
	CGame();																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame();																				// Wird nach Ende einmal aufgerufen (Destruktor)

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat

private:
    // Vektoria Szene
	CRoot m_zr;
	CScene m_zs;
	CPlacement m_zpCamera;
	CPlacement m_zpSphere;
	CGeoSphere m_zgSphere;
	CFrame m_zf;
	CViewport m_zv;
	CCamera m_zc;
	CLightParallel m_zl;

	// Knack Modul
	CKnack m_knackXXX;
};



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

	// Verwende DirectX12 und nicht DirectX11.
	// Falls kein Bild erscheint oder der Rechner abst�rzen sollte, hast du einen Rechner, der nicht DirectX12-kompatibel ist. 
	// Dann kannst du das DirectX11 SDK installieren (siehe Manual, erster Foliensatz) und hier eApiRender_DirectX11 eintragen:
	m_zf.SetApiRender(eApiRender_DirectX12);
	
	// Begrenze die Bildwiederholrate auf max. 100 Hz, damit empfindliche Rechner nicht �berhitzen:
	m_zr.SetFrameRateMax(100.0f);

	// Initialisiere die Kamera mit einem horizontalen �ffnungswinkel von 60�:
	m_zc.Init(THIRDPI);

	// Initialisiere den Frame (Fensterrenderbereich)! 
	// �bergebe dabei das Handle auf das Window, und ein Funktionspointer auf die Betriebssystem-Callback-Routine:
	m_zf.Init(hwnd, procOS); 

	// Setze den Viewport (Renderbereich f�r eine Kamera) auf die volle Gr��e des Frames:
	m_zv.InitFull(&m_zc);

	// Initialisiere ein wei�es Parallellicht, welches von rechts oben vorne strahlt:
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	// Initialisiere eine Kugel mit 1,5 Metern Radius und mappe erst einmal kein Material drauf (dammit schwachbr�stige Rechner mit wenig Texturspeicher nicht abst�rzen)!
	// Die Vertex-Granulatit�t betr�gt 50 mal 50 Vertices:  
	m_zgSphere.Init(1.5F, nullptr, 50, 50);

	// Initialisiere die Sky-Dome-Kugel mit 1 km Radius und mappe erst mal kein Material drauf (dammit schwachbr�stige Rechner mit wenig Texturspeicher nicht abst�rzen)!
	// Die Vertex-Granulatit�t betr�gt 20 mal 20 Vertices.  
	// Flippe danach seine Vertexnormalen, damit sie nach innen zeigen:
	m_zgSky.Init(1000.0F, nullptr, 20, 20);
	m_zgSky.Flip();

	// Informiere das Sky-Dome-Placement, dass es sich mit der Kamera verschieben soll:
	m_zpSky.SetSky();

	// Initialisiere die Schrifsatzmaterialien aus der Font-Bibliothek, der eine mit OCRA in Wei� und der andere in rot: 
	m_zwfRed.LoadPreset("OCRAExtendedRed");
	m_zwfWhite.LoadPreset("OCRAExtendedWhite");

	// Initialisiere das Writing (2d-Text auf der Oberfl�che) f�r die Hallo-Welt-Ausgabe : 
	// 1. Parameter:	Das HalloWelt-Writing hat 40% Breite und 20% H�he bez�glich des �bergeordneten Viewports.
	//					Es beginnt links bei 30% und oben bei 10%.
	// 2. Parameter:	Es kann maximal 12 Buchstaben darstellen.
	// 3. Parameter:	Es verwendet die Schriftart m_zwfRed.
	m_zwHalloWelt.Init(C2dRect(0.4f, 0.2f, 0.3f, 0.1f), 12, &m_zwfRed);

	// Das Writing soll "Hallo Welt ausgeben"
	m_zwHalloWelt.PrintF("Hallo Welt!");

	// Initialisiere die Writings f�r die Ausgabe zus�tzlicher Infos: 
	// 1. Parameter:	Die Addiutionnal-Text-Writings haben 80% Breite und 10% H�he bez�glich des �bergeordneten Viewports.
	//					Es beginnt links bei 10% und oben bei unterschiedlichen Werten.
	// 2. Parameter:	Es kann maximal 32 Buchstaben darstellen.
	// 3. Parameter:	Es verwendet die Schriftart m_zwfWhite.
	for (int i = 0; i < 4; i++)
	{
		m_azwAdditionalText[i].Init(C2dRect(0.9f, 0.1f, 0.05f, 0.4f + (float)i * 0.15f), 56, &m_zwfWhite);
	}

	// Schreibe die Erkl�rungen: 
	m_azwAdditionalText[0].PrintF("          Hurra! Vektoria funktioniert! :-)");
	m_azwAdditionalText[1].PrintF("ACHTUNG: Ich lade gleich eine einfache 3D-Szene.");
	m_azwAdditionalText[2].PrintF("Falls es dann crashen sollte,");
	m_azwAdditionalText[3].PrintF("sollten Sie Ihren Grafikkartentreiber aktualisieren.");

	// H�nge die Sky-Dome-Geometrie an das Sky-Placement:
	m_zpSky.AddGeo(&m_zgSky);

	// Lass die Kamera immer auf die Kugel schauen:
	m_zpCamera.SetPointing(&m_zpSphere);

	//----------------------------
	// Vernetze die Knotenobjekte:
	//----------------------------

	// H�nge den Frame an die Root:
	m_zr.AddFrame(&m_zf);

	// H�nge den Viewport an den Frame:
	m_zf.AddViewport(&m_zv);

	// H�nge die Szene an den Frame:
	m_zr.AddScene(&m_zs);

	// H�nge das Hallo-Welt-Kugelplacement an die Szene:
	m_zs.AddPlacement(&m_zpSphere);

	// H�nge das Kameraplacement an die Szene:
	m_zs.AddPlacement(&m_zpCamera);

	// H�nge das Parallellicht an die Szene:
	m_zs.AddLightParallel(&m_zl);

	// H�nge die Kamera an das Kameraplacement:
	m_zpCamera.AddCamera(&m_zc);

	// H�nge die Kugelgeometrie an das Kugelplacemnent:
	m_zpSphere.AddGeo(&m_zgSphere);

	// H�nge das Sky-Placement an die Szene:
	m_zs.AddPlacement(&m_zpSky);

	// H�nge die Writings an den Viewport
	m_zv.AddWriting(&m_zwHalloWelt);
	for(int i= 0; i<4;i++)
		m_zv.AddWriting(&m_azwAdditionalText[i]);

	// Schalte alle 3D-Elemente erst einmal aus: 
	m_zpSphere.SwitchOff();
	m_zpSky.SwitchOff();

	// Schalte alle 2D-Erkl�relemente erst einmal aus: 
	for (int i = 0; i < 4; i++)
		m_azwAdditionalText[i].SwitchOff();
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	// Lass das "HalloWelt" die erten 10 Sekunden nach oben wandern: 
	if(fTime < 5.0f)
		m_zwHalloWelt.SetPos(0.3f, 0.4f-fTime*0.05f);

	// Wenn 5 Sekunden verstrichen sind: 
	if (m_zr.IsTime(5.0f))
	{
		// Schalte die Erkl�r-Writings an: 
		for (int i = 0; i < 4; i++)
			m_azwAdditionalText[i].SwitchOn();
	}

	// Wenn 15 Sekunden verstrichen sind: 
	if (m_zr.IsTime(15.0f))
	{
		// Lade die Low-Res-Textur f�r den Sky-Dome, 
		// damit die Rechner mit wenig Speicherrkapazit�t nicht abschmieren, lade die Variante mit geringerer Aufl�sung:
		// Neuere Rechner k�nnen statt EnvChurchLowRes auch EnvChurch laden, das sieht besser aus: 
		m_zmSkyLowRes.LoadPreset("EnvChurchLowRes");

		m_zgSky.SetMaterial(&m_zmSkyLowRes);
		m_zr.AddMaterial(&m_zmSkyLowRes);

		// Lade das Hallo-Welt-Material aus der Materialbibliothek.
		// �ndere seine Environmental-Textur auf die Sky-Dome-Textur:
		m_zmSphereLowRes.LoadPreset("HalloWeltLowRes");
		m_zmSphereLowRes.AlterEnvPath("..//..//lib//Materials//EnvChurchLowRes//EnvChurchLowResD.jpg", false);
		m_zr.AddMaterial(&m_zmSphereLowRes);

		m_zgSphere.SetMaterial(&m_zmSphereLowRes);
		m_zr.AddMaterial(&m_zmSkyLowRes);

		// Schalte alle 3D-Elemente an: 
		m_zpSphere.SwitchOn();
		m_zpSky.SwitchOn();

		// Schalte die Writings aus: 
		m_zwHalloWelt.SwitchOff();
		for (int i = 0; i < 4; i++)
			m_azwAdditionalText[i].SwitchOff();
	}

	// Wenn 20 Sekunden verstrichen sind: 
	if (m_zr.IsTime(20.0f))
	{
		m_azwAdditionalText[0].PrintF("             3D funktioniert also auch! :-)");
		m_azwAdditionalText[1].PrintF("ACHTUNG: Ich erh�he gleich die Texturaufl�sungen.",20, 146);
		m_azwAdditionalText[2].PrintF("Falls es dann crashen sollte, haben Sie einen extrem");
		m_azwAdditionalText[3].PrintF("kleinen Texturspeicher, reduzieren Sie die Aufl�sungen!", 146);

		// Schalte alle 3D-Elemente wieder aus: 
		m_zpSphere.SwitchOff();
		m_zpSky.SwitchOff();

		// Schalte die Writings weieder an: 
		m_zwHalloWelt.SwitchOn();
		for (int i = 0; i < 4; i++)
			m_azwAdditionalText[i].SwitchOn();
	}

	// Wenn 28 Sekunden verstrichen sind: 
	if (m_zr.IsTime(28.0f))
	{
		// Lade die High-Res-Textur f�r den Sky-Dome, 
		// damit die Rechner mit wenig Speicherrkapazit�t nicht abschmieren, lade die Variante mit geringerer Aufl�sung:
		// Neuere Rechner k�nnen statt EnvChurchLowRes auch EnvChurch laden, das sieht besser aus: 
		m_zmSkyHighRes.LoadPreset("EnvChurch");
		m_zgSky.SetMaterial(&m_zmSkyHighRes);

		// Lade das Hallo-Welt-Material aus der Materialbibliothek.
		// �ndere seine Environmental-Textur auf die Sky-Dome-Textur:
		m_zmSphereHighRes.LoadPreset("HalloWelt");
		m_zmSphereHighRes.AlterEnvPath("..//..//lib//Materials//EnvChurch//EnvChurchD.jpg", false);
		m_zgSphere.SetMaterial(&m_zmSphereHighRes);

		// Alle Materialien, die nicht im ersten Tick vorkommen, m�ssen an der Root angemeldet werden. 
		m_zr.AddMaterial(&m_zmSkyHighRes);
		m_zr.AddMaterial(&m_zmSphereHighRes);
		m_zr.AddMaterial(&m_zmSkyHighRes);

		// Schalte alle 3D-Elemente an: 
		m_zpSphere.SwitchOn();
		m_zpSky.SwitchOn();

		// Schalte die Writings aus: 
		m_zwHalloWelt.SwitchOff();
		for (int i = 0; i < 4; i++)
			m_azwAdditionalText[i].SwitchOff();
	}




	// Lass die Kugel rotieren:
	m_zpSphere.RotateY(-fTime);
	m_zpSphere.RotateXDelta(0.8f*sinf(fTime*0.2f));

	// Lass die Kamera in 7 Metern Abstand zur Kugel rotieren:
	m_zpCamera.TranslateZ(7.0f);
	m_zpCamera.RotateYDelta(fTime*0.1f);


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
	m_zf.ReSize(iNewWidth, iNewHeight);
}

float CGame::GetTimeDeltaMin()
{
	return m_zr.GetTimeDeltaMin();
}

float CGame::GetVersion()
{
	return m_zr.GetVersion();
}



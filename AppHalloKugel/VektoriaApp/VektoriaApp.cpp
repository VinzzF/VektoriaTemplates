// ------------------------------------------------------------------------
// VektoriaApp.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung
// Autor: Tobias Breiner
// ------------------------------------------------------------------------

#include <windows.h> // Windows
#include "resource.h" // Das Icon
#include "Game.h" // Das Spiel
#include "Vektoria\Timer.h" // Timer fütr die Frame-Rate-Anzeige
#include "Vektoria\Splash.h" // Für den Splash-Screen (Allgemein)
#include "Mmsystem.h" // Für den Splash-Screen-Sound

#pragma comment(lib, "winmm.lib")

// ------------------
// Globale Variablen:
// ------------------

TCHAR szClassName[] = TEXT("VektoriaWindowClass"); // Klassenname
static bool g_bFullscreen = false; // Flag, ob Fullscreen, per default in Nicht-Fullscreen gestartet 
CGame g_game; // Das Spiel:
CSplash g_splash;// Der Vektoria-Splash-Screen

// --------------------
// Callback-Funktionen:
// --------------------

static void ChangeDisplay(HWND hWnd, unsigned int uWndFlags)
{
	static bool s_bNextIsText = false;
	static unsigned int s_uNextIsProgressEvents = 0;
	static unsigned int s_uProgressEvents = 0;
	static unsigned int s_uFrames = 0;
	static unsigned int s_uViewports = 0;
	static unsigned int s_uGeos = 0;
	static unsigned int s_uMaterials = 0;
	static unsigned int s_uAudios = 0;

	static unsigned int s_uFrame = 0;
	static unsigned int s_uViewport = 0;
	static unsigned int s_uGeo = 0;
	static unsigned int s_uMaterial = 0;
	static unsigned int s_uAudio = 0;


	DWORD dwExStyle;
	DWORD dwStyle;
	if (s_bNextIsText)
	{
		char ac[200];
		switch (uWndFlags)
		{
		case 'F':
			s_uFrame++;
			sprintf(ac, "Initializing Frame %i", s_uViewport);
			break;
		case 'V':
			s_uViewport++;
			sprintf(ac, "Initializing Viewport %i", s_uViewport);
			break;
		case 'G':
			s_uGeo++;
			sprintf(ac, "Creating Geometry %i", s_uGeo);
			break;
		case 'M':
			s_uMaterial++;
			sprintf(ac, "Loading Material %i", s_uMaterial);
			break;
		case 'A':
			s_uMaterial++;
			sprintf(ac, "Loading Audio %i", s_uMaterial);
			break;
		case 'a':
			s_uMaterial++;
			sprintf(ac, "Initializing Sound Api");
			break;
		default:
			sprintf(ac, "Initializing App");
			break;
		}
		SetWindowTextA(hWnd, ac);
		s_bNextIsText = false;
	}
	else if (s_uNextIsProgressEvents > 0)
	{
		switch (s_uNextIsProgressEvents)
		{
		case 5: s_uFrames = uWndFlags; break;
		case 4: s_uViewports = uWndFlags; break;
		case 3: s_uGeos = uWndFlags; break;
		case 2: s_uMaterials = uWndFlags; break;
		case 1: s_uAudios = uWndFlags;
			s_uProgressEvents = (s_uMaterials + s_uGeos + 1)*s_uFrames + s_uViewports + s_uAudios + 2;
			break;
		}
		s_uNextIsProgressEvents--;
	}
	else if (uWndFlags == 2) // Schalte Fullscreen aus:
	{
		g_bFullscreen = false;
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
		SetWindowLongPtr(hWnd, GWL_EXSTYLE, dwExStyle);
		SetWindowLongPtr(hWnd, GWL_STYLE, dwStyle);

		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 1920, 1080, SWP_SHOWWINDOW); //TODO: alte width und height werte merken und dann wieder setzen
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);
		ChangeDisplaySettings(NULL, 0);
	}
	else if (uWndFlags == 3) // Schalte Fullscreen an:
	{
		g_bFullscreen = true;
		// Automatisch die Größe des primären Monitors ermitteln
		int iWidth = GetSystemMetrics(SM_CXSCREEN);
		int iHeight = GetSystemMetrics(SM_CYSCREEN);

		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (DWORD)iWidth;
		dmScreenSettings.dmPelsHeight = (DWORD)iHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		SetWindowLongPtr(hWnd, GWL_EXSTYLE, dwExStyle);
		SetWindowLongPtr(hWnd, GWL_STYLE, dwStyle);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, (DWORD)iWidth, (DWORD)iHeight, SWP_SHOWWINDOW);
		g_game.WindowReSize(iWidth, iHeight);
		SetForegroundWindow(hWnd);
		SetFocus(hWnd);
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
	}
	else if (uWndFlags == 4) // Rücke Fortschrittsanzeiger weiter:
	{
		static int s_uProgress = 0;



		s_uProgress++;
		if (s_uProgressEvents>0)
			g_splash.ShowProgressBar((float)s_uProgress / (float)s_uProgressEvents);

		s_bNextIsText = true;

	}
	else if (uWndFlags == 8) // Versteckte Fortschrittsanzeiger:
	{
		g_splash.HideProgressBar();
		s_uProgressEvents = 1;
		s_uFrame = 0;
		s_uViewport = 0;
		s_uGeo = 0;
		s_uMaterial = 0;
		s_uAudio = 0;
	}
	else if (uWndFlags == 16) // Nächste fünf Events werden Knotenanzahlen übermittelt:
	{
		s_uNextIsProgressEvents = 5;
	}
}

//  Diese Funktion wird von Windows aufgerufen:
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		g_game.WindowReSize(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_F11)
		{
			g_bFullscreen = !g_bFullscreen;
			if (g_bFullscreen)
				ChangeDisplay(hwnd, 3);
			else
				ChangeDisplay(hwnd, 2);

		}
		if (wParam != VK_ESCAPE)
			break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}


// Eintrittspunkt:
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// INIT-Teil:

	// Initialisierung des Fensters:
	WNDCLASSA window_class = { 0 };
	window_class.lpfnWndProc = WndProc;
	window_class.lpszClassName = "Vektoria";
	window_class.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	window_class.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClassA(&window_class);

	// Definiere Fenster:
	HWND hwnd = CreateWindowA
	(
		window_class.lpszClassName,  // Fenstername (sollte identisch mit Klassenname sein)
		window_class.lpszClassName, // Klassenname
		WS_OVERLAPPEDWINDOW, // Stil
		CW_USEDEFAULT, CW_USEDEFAULT, // linke obere Ecke in Pixeln => Windows entscheidet
		CW_USEDEFAULT, CW_USEDEFAULT, // Größe des Fensters in Pixeln  => Windows entscheidet
		HWND_DESKTOP,           // Das Fenster ist ein Unterfenster des Desktops
		NULL, // Handle zum Menu => gibts nicht => 0
		hInstance,
		0   // Keine Fenstererzeugungsdaten

	);
	
	if (!hwnd)
	{
		MessageBoxA(NULL, "CreateWindow failed!", "Vektoria", NULL);
		return 1;
	}


	ShowWindow(hwnd, SW_SHOW);

	g_game.Init(hwnd, ChangeDisplay,&g_splash);

   // Zeig den Splash-Screen:
	g_splash.Init(hwnd, hInstance);
	g_splash.Show();

	// Zeig das Fenster:
	ShowWindow(hwnd, nCmdShow);

	// Initialisiere den Timer: 
	CTimer timer;
	timer.SwitchFrameRateCalculationOn();
	double dStartTime = timer.GetElapsedTime();
	double dLastTime = dStartTime;

	float fTimeDelta;
	float fTime;
	float fTimeLastShow = 0.0F;
	bool bFirstTick = true;


	// TICK-Teil: 
	bool bQuit = false;

	do
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // if => Pro Frame wird eine Message verarbeitet, while =>  => Pro Frame werden alle anstehenden Messages verarbeitet. Achtung, zweiter Parameter muss NULL sein!
		{
			if (msg.message == WM_QUIT)
			{
				bQuit = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//FrameRate
			timer.Tick(fTime, fTimeDelta);

			if (fTime - fTimeLastShow >= 0.2F) // SetWindowTextA stürzt ab, wenn es zu schnell hintereinander aufgerufen wird (Microsoft-Fehler) => daher die Zeitbegrenzung
			{
				char ac[300];
				sprintf_s(ac, 300, "VektoriaApp        FR-Average: %.3f; FR-Long Average: %.3f; FR Min: %.3f; FR Max: %.3f", timer.m_fFrameRateAverage, timer.m_fFrameRateAverageLong, timer.m_fFrameRateMin, timer.m_fFrameRateMax);
				SetWindowTextA(hwnd, ac);
				fTimeLastShow = fTime;
			}

			// Game Tick
			g_game.Tick(fTime, fTimeDelta);
			if (bFirstTick)
			{
				g_splash.Hide();
				bFirstTick = false;
			}
		}

	} while (!bQuit);

	// FINI-Teil:
	g_game.Fini();

	return 0;
}






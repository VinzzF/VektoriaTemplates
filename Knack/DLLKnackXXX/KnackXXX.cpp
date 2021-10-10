#include "pch.h"
#include "KnackXXX.h"
#include "XXXDefines.h"


// Author: 
namespace Vektoria
{

	//------------------BEGIN MOIFs

	// Die Wichtigste Funktion: 



	void CKnackXXX::Input(float frGas, float frBrakes, float fSteering, int iGear, bool bBooster)
	{
	}


	void CKnackXXX::Tick(float & fTimeDelta, CGeoTerrains & zgsColTerrain, CGeos & zgsColGround, CGeos & zgsColFrontal)
	{
	}




	int CKnackXXX::GetPropInt(unsigned int iItem, unsigned int eProp)
	{
		switch (eProp)
		{

		};

		return 0;
	};

	float CKnackXXX::GetPropFloat(unsigned int iItem, unsigned int eProp)
	{
		switch (eProp)
		{

		}

		return 0.0f;
	};



	char * CKnackXXX::GetPropChararray(unsigned int iItem, unsigned int eProp)
	{
		switch (iItem)
		{
		}

		return "";
	};

	CHMat CKnackXXX::GetPropMat(unsigned int iItem, unsigned int eProp)// in this case, gets the current wheel pos
	{
		static const CHMat mDefault(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		return mDefault;
	};

	CHVector CKnackXXX::GetPropVector(unsigned int idItem, unsigned int eProp)
	{
		static const CHVector v(0.0f, 0.0f, 0.0f);
		return v;
	}


	CColor CKnackXXX::GetPropColor(unsigned int iItem, unsigned int eProp)
	{
		static const CColor cDefault(0.0f, 0.0f, 0.0f);
		return cDefault;
	};


	void CKnackXXX::SetPropInt(unsigned int idItem, unsigned int eProp, int i)
	{

	}

	void CKnackXXX::SetPropFloat(unsigned int idItem, unsigned int eProp, float f)
	{

	}

	void CKnackXXX::SetPropChararray(unsigned int idItem, unsigned int eProp, char * ac)
	{

	}

	void CKnackXXX::SetPropMat(unsigned int idItem, unsigned int eProp, CHMat m)
	{

	}

	void CKnackXXX::SetPropVector(unsigned int idItem, unsigned int eProp, CHVector v)
	{
	}

	void CKnackXXX::SetPropColor(unsigned int idItem, unsigned int eProp, CColor color)
	{

	}







	//------------------END MOIFs




	CKnackXXX::CKnackXXX()
		: m_pzs(nullptr)
		, m_pzv(nullptr)
	{
		*m_acFixedLibPath = 0;	// Null-Terminierung für leeren String
	}

	CKnackXXX::~CKnackXXX()
	{
	}

	void CKnackXXX::Init(char* acIni, char * acLib, CScene * pzs, CViewport * pzv)
	{
		// "Hack", damit während des Debuggens auf das DLL Projekt, nicht die Vektoria-Lib, zugegeriffen wird
		// Gepublishte Projekte müssen Header und Bibliotheksdateien des DLL Knack Moduls in die Vektoria Lib integrieren
		FixLibPath(acLib);

		// Referenzen auf Szene und Viewport, falls benötigt
		m_pzs = pzs;
		m_pzv = pzv;

		// Laden von Konfigurationswerten aus der .ini Datei
		LoadIni(acIni);
	}

	void CKnackXXX::FixLibPath(const char* acLib)
	{
		strcpy(m_acFixedLibPath, acLib);

		if (::IsDebuggerPresent())
		{
			// Pfad des Working-Directory als Basis.
			// To-Do: Wenn das Verzeichnis vor Init des Moduls geändert wird, funktioniert das nicht mehr.
			char acModPath[MAX_PATH];
			if (::GetCurrentDirectoryA(_countof(acModPath), acModPath) == 0u)
				return;

			// Ein Verzeichnis "nach oben"
			char* pcRSep = strrchr(acModPath, '\\');
			if (pcRSep && pcRSep > acModPath)
				*pcRSep = 0;

			// Extrahieren des Lib Suffixes z.B. "DLLKnackXXX"
			char* pcRLib = ::StrStrIA(m_acFixedLibPath, "Lib");
			if (pcRLib)
				pcRLib = strchr(pcRLib, '\\');
			if (pcRLib)
				++pcRLib;

			// Ersetzen des Lib-Pfades durch den neuen Pfad zum DLL Knack Modul
			if (pcRLib)
				::PathCombineA(m_acFixedLibPath, acModPath, pcRLib);
		}
	}

	void CKnackXXX::LoadIni(const char* acIni)
	{
		ULSection("Loading XXX Parameters");

		char acIniWithPath[MAX_PATH];
		sprintf(acIniWithPath, "%s\\%s", m_acFixedLibPath, acIni);

		ULCheckFile(acIniWithPath);
		CFileVektoria filevektoria;
		filevektoria.OpenToLoad(acIniWithPath);

		filevektoria.SetSection("Section");

		char szTest[64];
		filevektoria.LoadChararray(szTest, "szTest");

		filevektoria.Close();
	}

	void CKnackXXX::Fini()
	{
	}

	void CKnackXXX::Reset()
	{
	}

	void CKnackXXX::Ignite(CHMat m)
	{
	}

	void CKnackXXX::SetLogFileData(FILE * pfile, unsigned int uStartTime, char * acFile)
	{
		// Setzen des Logfiles
		ULInit(acFile);
		ULSetLogFilePtr(pfile);
		ULSetLogTime(uStartTime);

		ULInfo("Knack XXX Log Initialized");
	}
}

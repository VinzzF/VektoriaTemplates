#pragma once

//-----------------------------------------------------------------------
// CKnackXXX
// 
// Erklärung: Interfaceklasse für die Ansteuerung von Knack Modulfunktionen
// Autor    : 
// Zeit     : 
//------------------------------------------------------------------------

#include "Vektoria\ApiKnack.h"

namespace Vektoria
{
	class CScene;

	class CKnackXXX : public CApiKnack
	{
	public:
		// constructor and deconstructor, yin and yang:
		CKnackXXX();
		~CKnackXXX();

		//--------------------------------------------------
		// Begin: Knack Object Interface Functions (MOIFs):
		//--------------------------------------------------
		void Init(char* acIni, char * acLib, CScene * pzs, CViewport * pzv) override;
		void Tick(float & fTimeDelta, CGeoTerrains & zgsColTerrain, CGeos & zgsColGround, CGeos & zgsColFrontal) override;
		void Fini() override;

		void Input(float frGas, float frBrakes, float fSteering, int iGear, bool bBooster) override;

		void Reset() override;

		// Setzt die Matrix vom Auto, resettet und schaltet Zündung an:
		void Ignite(CHMat m) override;

		int GetPropInt(unsigned int idItem, unsigned int eProp) override;
		float GetPropFloat(unsigned int idItem, unsigned int eProp) override;
		char * GetPropChararray(unsigned int idItem, unsigned int eProp) override;
		CHMat GetPropMat(unsigned int idItem, unsigned int eProp) override;
		CHVector GetPropVector(unsigned int idItem, unsigned int eProp) override;
		CColor GetPropColor(unsigned int idItem, unsigned int eProp) override;

		void SetPropInt(unsigned int idItem, unsigned int eProp, int i) override;
		void SetPropFloat(unsigned int idItem, unsigned int eProp, float f) override;
		void SetPropChararray(unsigned int idItem, unsigned int eProp, char * ac) override;
		void SetPropMat(unsigned int idItem, unsigned int eProp, CHMat m) override;
		void SetPropVector(unsigned int idItem, unsigned int eProp, CHVector v) override;
		void SetPropColor(unsigned int idItem, unsigned int eProp, CColor color) override;

		void SetLogFileData(FILE * pfile, unsigned int uStartTime, char * acFile) override;

		// ----------
		// End: MOIFs
		// ----------

	private:
		// -------------------
		// Initialisierungs Functionen:
		// -------------------

		///<summary>
		///<para>Passt den Bibliothekspfad zum Knack Modul so an,</para>
		///<para>dass während des Debuggens auf das DLL Projekt, nicht die Vektoria-Lib, zugegeriffen wird.</para>
		///</summary>
		///<param name="acLib">Name des Modulbibliothek, z.B. "DLLKnackXXX"</param>
		void FixLibPath(const char* acLib);

		///<summary>
		///<para>Lädt Konfigurationswerte aus der initialisierten .ini Datei.</para>
		///</summary>
		///<param name="acIni">Pfad zur .ini Datei</param>
		void LoadIni(const char* acIni);


		// -------------------
		// Display Functionen:
		// -------------------


		// drive calc functions:


		// ----------------
		// Membervariablen:
		// ----------------
		CScene* m_pzs;
		CViewport* m_pzv;

		char m_acFixedLibPath[MAX_PATH];
	};
}

# Vektoria Templates
Projektvorlagen für die didaktische Game Engine "Vektoria" https://games.hs-kempten.de/vektoria/

**Setup eigener Projekte**
1. Den Ordner mit der gewünschten Projektvorlage in eigene Ordnerstruktur kopieren / integrieren
2. *Nur* den "**Lib**" Ordner aus dem Vektoria Download (http://games.hs-kempten.de/vektoria-download/) (Version 20) in das Hauptverzeichnis kopieren (wo die "ADD VEKTORIA LIB FOLDER IN THIS DIR" Datei liegt)
3. Ggf. Ordner / Dateien umbennen
4. Gewünschte Solution (z.B. "Knack/Knack.sln") öffnen
5. Ggf. auf eigene Compiler und Windows SDK Versionen ausrichten. Projektmappe -> Rechtsklick -> Neu ausrichten
6. Entwickeln oder Builden :)

**DLL Knack Module**
Während des Debuggens wird der interne Bibliothekspfad auf das Modul im Projektordner gesetzt, damit dieses direkt von dort entwickelt werden kann und Kopiervorgänge bei jedem Build vermieden werden. Beim Publishen müssen alle Header- und Bibliotheksdateien des DLL Knack Moduls in den Lib Ordner (neben "Vektoria") kopiert werden!

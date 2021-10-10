# Vektoria Templates
Projektvorlagen für die didaktische Game Engine "Vektoria" https://games.hs-kempten.de/vektoria/

# Setup eigener Projekte
1. Den Ordner mit der gewünschten Projektvorlage in eigene Ordnerstruktur kopieren / integrieren
2. *Nur* den "**Lib**" Ordner aus dem Vektoria Download (http://games.hs-kempten.de/vektoria-download/) (Version 20) in das Hauptverzeichnis kopieren (wo die "ADD VEKTORIA LIB FOLDER IN THIS DIR" Datei liegt)
3. Ggf. Ordner / Dateien umbennen
4. Gewünschte Solution (z.B. "Knack/Knack.sln") öffnen
5. Ggf. auf eigene Compiler und Windows SDK Versionen ausrichten. Projektmappe -> Rechtsklick -> Neu ausrichten
6. Entwickeln oder Builden :)

# Prä-kompilierte Header
Um mehrfache Inkludierung von Bibliotheks-Headern (z.B. windows.h, iostream, string, vector, ...) zu vermeiden, verwenden alle Projektvorlagen sogenannte "Pre-compiled header" (PCH auch "stdafx"). Das beschleunigt auch die Kompilierzeit der Projekte erheblich, gerade wenn diese größer werden. Solltet ihr bestimmte Header häufig in euren .cpp Dateien inkludieren, inkludiert diese stattdessen einmal in der "pch.h" Datei bei den anderen Biblioitheks-Includes.

# Projekteinstellungen (Property Sheets)
Die Einbindung der Vektoria-Bibliotheken (Includes, Libs, Environment, ...) erfolgt vollständig über externe Property Sheets, die im Hauptverzeichnis unter "Props" sowie den Projektverzeichnissen zu finden sind. Damit können Projekteinstellungen frei von der Gefahr die Abhängigkeiten zu verändern geändert werden, so lange bei allen Einstellungen die Vererbung von Einstellungen aktiviert ist.

![property_inheritance](https://user-images.githubusercontent.com/73252260/132992247-8f68cd3a-599b-4486-8146-68a326c4668a.png)

Zudem können Vektoria-relevante Einstellungen separat von Projekteinstellungen verwaltet werden. Auch kann der Hauptordner "Lib" beliebig verschoben werden, es bedarf nur einer Änderung der "PROJEKT/Props/Vektoria.LibDir.props" Datei, um den Pfad zu dieser anzupassen! Das Debug-Environment über die temporäre ".vcxproj.user" Datei (die nicht versioniert werden sollte) zu setzen, ist auch nicht mehr nötig.

# DLL Knack Module
Während des Debuggens wird der interne Bibliothekspfad auf das Modul im Projektordner gesetzt, damit dieses direkt von dort entwickelt werden kann und Kopiervorgänge bei jedem Build vermieden werden. Beim Publishen müssen alle Header- und Bibliotheksdateien des DLL Knack Moduls in den Lib Ordner (neben "Vektoria") kopiert werden!

#define _CRT_SECURE_NO_WARNINGS
#include "Windows.h"
#include <Propitious\Propitious.hpp>
#include <iostream>

using namespace Propitious;

EXPORT void handleStart(int argc, char** argv)
{
	Propitious::initialise();

	String ourDir = Propitious::getPathToExe();
	String gameFolder = ourDir + "\\demo";
#ifdef PROPITIOUS_ARCHITECTURE_X64
	String gameBinaries = gameFolder + "\\bin64";
#else
	String gameBinaries = gameFolder + "\\bin32";
#endif

	DLL::addDLLDirectory(gameBinaries);
	DLL gameDLL("client.dll");

	typedef void(*GameInitialiseFunction)(const char*);
	GameInitialiseFunction initFunc = (GameInitialiseFunction)gameDLL.getFunction("gameInitialise");
	if (!initFunc)
	{
		MessageBoxA(0, "Could not load library: client.dll", "Fatal Error!", MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		return;
	}
	initFunc(unwiden(cString(gameFolder)));
}
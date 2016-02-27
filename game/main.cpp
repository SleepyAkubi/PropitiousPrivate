#define _CRT_SECURE_NO_WARNINGS
#include "Windows.h"
#include "Propitious\Common.hpp"
#include "Propitious\Utility\DLL.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	std::string ourDir = Propitious::getPathToExe();
	std::string gameFolder = ourDir + "\\demo";
	std::string gameBinaries = gameFolder + "\\bin";

	Propitious::DLL::addDLLDirectory(gameBinaries);
	Propitious::DLL gameDLL("game.dll");

	typedef void(*GameInitialiseFunction)(const char*);
	GameInitialiseFunction initFunc = (GameInitialiseFunction) gameDLL.getFunction("gameInitialise");
	if (!initFunc)
	{
		MessageBoxA(0, "Could not find a valid game dll!", "Fatal Error!", MB_OK);
	}
	initFunc(gameFolder.c_str());
	return 0;
}
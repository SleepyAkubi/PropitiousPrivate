#include "Windows.h"
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

int main(int argc, char** argv)
{
	HMODULE hModule = GetModuleHandleA(NULL);
	char path[MAX_PATH];
	GetModuleFileNameA(hModule, path, MAX_PATH);
	PathRemoveFileSpecA(path);

#ifdef _WIN64
	strcat(path, "\\bin64\\");
#else
	strcat(path, "\\bin32\\");
#endif

	SetDllDirectoryA(path);
	HMODULE launcherDLL = LoadLibraryA("gamelauncher.dll");

	typedef void(*LauncherFunction)(int argc, char** argv);
	LauncherFunction function = (LauncherFunction) GetProcAddress(launcherDLL, "handleStart");
	if (function == nullptr)
	{
		MessageBoxA(0, "Could not load library: gamelauncher.dll", "Fatal Error!", MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		return -1;
	}

	function(argc, argv);

	return 1;
}
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Game.h"

// ------------
// Entry point
// ------------
int main()
{
	game();
	return 0;
}
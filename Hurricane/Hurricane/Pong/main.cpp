#include <Debug.h>
#include "Pong.h"

int main(int argc, char** argv) {

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

#if defined(DEBUG) || defined(_DEBUG)
	Debug::Init();

	// Avoid memory leaks by catching them
	// Won't catch all of them (but you gotta catch 'em all right? lol)
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
#endif

	Pong pong;
	pong.Run();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
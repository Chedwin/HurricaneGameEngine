#include <Macro.h>
#include <Timer.h>
#include "TestGame.h"

hINT main(hINT argc, hCHAR** argv) {

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);


	/// Debug mode stuff
#if defined(DEBUG) | defined(_DEBUG)

	// Avoid memory leaks by catching them
	// Won't catch all of them (but you gotta catch 'em all right? lol)
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Enable run-time memory leaks checks for debug builds
	// By default, this function will call _CrtDumpMemoryLeaks() at any exit point
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// If a memory leak is found, the main function will NOT return 0
	// This will trigger the breakpoint below to find the mem leak
	if (!_CrtSetBreakAlloc(0)) {
		LOG->Error("MEMORY LEAK DETECTED");
		_CrtDbgBreak();
	}

#endif

	// Now for the real game!
	static_assert(sizeof(void*) == 4, "64-bit code generation not supported!\n");


	TestGame test;
	test.Run();



	return 0;
}
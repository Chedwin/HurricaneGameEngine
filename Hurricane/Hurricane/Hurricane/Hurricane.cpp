#include <SDL.h>
#include "Macro.h"
#include "Game.h"

void QuitWindowPrompt() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ 0, 0, "Cancel" }, // (flags, buttonid, text)
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" }
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, // flags
		NULL, // window
		"Quit", // window title
		"Are you sure you want to quit?", // message
		SDL_arraysize(buttons), // num of buttons
		buttons // buttons
	};

	hINT buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
	}
	if (buttonid == 1) {
		GAME->SetRunState(false);
	}
}
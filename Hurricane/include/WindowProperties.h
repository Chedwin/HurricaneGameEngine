#ifndef WINDOW_PROPERTIES
#define WINDOW_PROPERTIES

#include "PCH.h"

namespace Hurricane 
{
	class Event;

	struct WindowProperties 
	{
		using EventCallbackFunc = std::function<void(Event&)>;

		EventCallbackFunc Callback;
		unsigned int Width;
		unsigned int Height;
		bool Fullscreen;
		bool VSyncEnabled;
		std::string Title;

		explicit WindowProperties(
			const std::string& title = "New Window",
			unsigned int width = 1280,
			unsigned int height = 720,
			bool isFullscreen = false, 
			bool isVSync = false)
			: Title(title), Width(width), Height(height), Fullscreen(isFullscreen), VSyncEnabled(isVSync)
		{
		}
	};

}


#endif WINDOW_PROPERTIES
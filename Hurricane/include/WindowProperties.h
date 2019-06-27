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
		bool IsFullscreen;
		bool IsVSync;
		std::string Title;

		explicit WindowProperties(
			const std::string& title = "New Window",
			unsigned int width = 1280,
			unsigned int height = 720,
			bool isFullscreen = false, 
			bool isVSync = false)
			: Title(title), Width(width), Height(height), IsFullscreen(isFullscreen), IsVSync(isVSync)
		{
		}
	};

}


#endif WINDOW_PROPERTIES
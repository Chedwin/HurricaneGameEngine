#ifndef WINDOW_H
#define WINDOW_H

#include "PCH.h"

#include <GLFW/glfw3.h>

#include "Event.h"
#include "WindowProperties.h"

namespace Hurricane 
{

	class Window {
	private:
		GLFWwindow* m_Window;
		WindowProperties m_Properties;

		using EventCallbackFunc = std::function<void(Event&)>;

	public:
		Window();
		~Window();

	public:
		bool Init(const WindowProperties& windowProps);
		void Shutdown();
		void Update();

		void SetVSync(bool enabled);
		void SetEventCallback(const EventCallbackFunc& callback);

		bool IsVSync() const;

		inline WindowProperties Properties() const 
		{
			return m_Properties;
		}
	};
	/*
	*/
}



#endif WINDOW_H
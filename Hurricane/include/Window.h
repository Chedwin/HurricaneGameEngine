#ifndef WINDOW_H
#define WINDOW_H

#include "PCH.h"

#include <GLFW/glfw3.h>

#include "Event.h"
#include "WindowProperties.h"

namespace Hurricane 
{
	class Application;

	class Window {
		friend class Application;
	private:
		GLFWwindow* m_GlfwWindow;
		WindowProperties m_Properties;

		using EventCallbackFunc = std::function<void(Event&)>;

	private:
		Window();

	public:
		~Window();

		bool Init(const WindowProperties& windowProps);
		void Shutdown();
		void Update();

		void SetVSync(bool enabled);
		void SetEventCallback(const EventCallbackFunc& callback);
		void SetProperties(const WindowProperties& windowProps);

		void SetTitle(const std::string& title);
		void SetTitle(const char* title);

		bool IsVSync() const;

		inline WindowProperties Properties() const
		{
			return m_Properties;
		}
	};
}



#endif WINDOW_H
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Event.h"
#include "ApplicationEvent.h"
#include "Window.h"
#include "Macro.h"

namespace Hurricane 
{

	class Application {
	protected:
		static Application* s_Instance;

		bool m_IsRunning;
		std::unique_ptr<Window> m_Window;

	public:
		Application();
		virtual ~Application() = 0;

		void Run();

		void OnEvent(Event& evt);

		inline static Application& Get() 
		{
			return *s_Instance; 
		}

	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	};

	// To be implemented by the concrete game implementation
	extern Application* CreateApplication();
}

#endif APPLICATION_H
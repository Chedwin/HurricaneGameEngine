#ifndef APPLICATION_H
#define APPLICATION_H

#include "Event.h"
#include "Window.h"

namespace Hurricane 
{

	class Application {
	private:
		static Application* s_Instance;

		bool m_IsRunning;
		Window* m_Window;

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& evt);

		inline static Application& Get() 
		{
			return *s_Instance; 
		}

	private:
		bool OnWindowClose();
	};


	Application* CreateApplication();
}

#endif APPLICATION_H
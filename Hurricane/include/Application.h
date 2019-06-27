#ifndef APPLICATION_H
#define APPLICATION_H

namespace Hurricane 
{

	class Application {
	private:
		static Application* s_Instance;
		bool m_IsRunning = true;

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent();

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
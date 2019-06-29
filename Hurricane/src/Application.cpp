#include "PCH.h"
#include "Macro.h"
#include "Application.h"
#include "ApplicationEvent.h"
#include "Timer.h"

namespace Hurricane 
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_IsRunning(true)
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(new Window);
	}

	Application::~Application()
	{
	}

	void Application::Run() 
	{
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));


		Timer gameTimer;
		gameTimer.Start();

		// Game loop
		while (m_IsRunning) 
		{
			gameTimer.Tick();
			
			std::ostringstream ss;
			ss << gameTimer.GetDeltaTime();
			std::string deltaTimeString(ss.str());

			m_Window->Update();

			// TODO: update the window's title to show FPS instead of deltatime
			m_Window->SetTitle(deltaTimeString);
		}

		gameTimer.Stop();
		float finalTime = gameTimer.GetTotalDuration();
	}

	void Application::OnEvent(Event& evt)
	{
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		// TODO: handle incoming events from each scene
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_IsRunning = false;
		event.Handled = true;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent & event)
	{
		event.Handled = true;
		return true;
	}
}
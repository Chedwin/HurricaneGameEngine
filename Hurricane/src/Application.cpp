#include "PCH.h"
#include "Macro.h"
#include "Application.h"
#include "ApplicationEvent.h"

namespace Hurricane 
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_IsRunning(true), m_Window(nullptr)
	{

		s_Instance = this;
		m_Window = std::unique_ptr<Window>(new Window);
		WindowProperties props;

		m_Window->Init(props);
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run() 
	{

		while (m_IsRunning) 
		{
			m_Window->Update();
		}

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
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent & event)
	{
		return true;
	}
}
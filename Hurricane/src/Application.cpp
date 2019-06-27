#include "PCH.h"
#include "Application.h"
#include "ApplicationEvent.h"

namespace Hurricane 
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	Application::Application()
		: m_IsRunning(true), m_Window(nullptr)
	{

	}


	Application::~Application()
	{

	}

	void Application::Run() 
	{
		m_Window = new Window();
		WindowProperties props;

		m_Window->Init(props);
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		while (m_IsRunning) 
		{
			m_Window->Update();
		}

		delete m_Window;
	}

	void Application::OnEvent(Event& evt)
	{
		OnWindowClose();
		// TODO: handle incoming events
	}

	bool Application::OnWindowClose()
	{
		m_IsRunning = false;
		return true;
	}
}
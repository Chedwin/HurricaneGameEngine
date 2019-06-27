#include "PCH.h"
#include "Application.h"

namespace Hurricane 
{
	Application* Application::s_Instance = nullptr;


	Application::Application()
	{
	}


	Application::~Application()
	{

	}

	void Application::Run() 
	{
		while (m_IsRunning) 
		{

		}

	}
	bool Application::OnWindowClose()
	{
		m_IsRunning = false;
		return false;
	}
}
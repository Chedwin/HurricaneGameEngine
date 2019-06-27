#include "PCH.h"
#include "Window.h"
#include "ApplicationEvent.h"

namespace Hurricane 
{

	Window::Window() 
		: m_Window(nullptr)
	{
	}

	Window::~Window() 
	{
		Shutdown();
	}

	bool Window::Init(const WindowProperties& windowProps)
	{
		m_Properties.Width = windowProps.Width;
		m_Properties.Height = windowProps.Height;
		m_Properties.IsFullscreen = windowProps.IsFullscreen;
		m_Properties.IsVSync = windowProps.IsVSync;
		m_Properties.Callback = windowProps.Callback;

		// Initialize the library 
		if (!glfwInit()) 
		{
			return false;
		}

		// Create a windowed mode window
		m_Window = glfwCreateWindow(windowProps.Width, windowProps.Height, windowProps.Title.c_str(), NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			return false;
		}

		glfwSetWindowUserPointer(m_Window, &m_Properties);

		// Make the window's context current
		glfwMakeContextCurrent(m_Window);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowProperties& winProps = *(WindowProperties*)glfwGetWindowUserPointer(window);
			WindowCloseEvent evt;
			winProps.Callback(evt);
		});

		return true;
	}

	void Window::Shutdown() 
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwPollEvents();
	}

	void Window::SetVSync(bool enabled)
	{
		m_Properties.IsVSync = enabled;
	}

	void Window::SetEventCallback(const EventCallbackFunc & callback)
	{
		m_Properties.Callback = callback;
	}

	bool Window::IsVSync() const
	{
		return m_Properties.IsVSync;
	}

}
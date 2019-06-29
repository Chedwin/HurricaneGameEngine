#include "PCH.h"
#include "Window.h"
#include "ApplicationEvent.h"

namespace Hurricane 
{

	Window::Window() 
		: m_GlfwWindow(nullptr)
	{
	}

	Window::~Window() 
	{
		Shutdown();
	}

	bool Window::Init(const WindowProperties& windowProps)
	{
		SetProperties(windowProps);

		// Initialize the library 
		if (!glfwInit()) 
		{
			return false;
		}

		// Create a windowed mode window
		m_GlfwWindow = glfwCreateWindow(windowProps.Width, windowProps.Height, windowProps.Title.c_str(), nullptr, nullptr);
		if (!m_GlfwWindow)
		{
			glfwTerminate();
			return false;
		}

		glfwSetWindowUserPointer(m_GlfwWindow, &m_Properties);

		// Make the window's context current
		glfwMakeContextCurrent(m_GlfwWindow);

		glfwSetWindowCloseCallback(m_GlfwWindow, [](GLFWwindow* window)
		{
			WindowProperties* winProps = static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

			WindowCloseEvent evt;
			winProps->Callback(evt);
		});

		glfwSetWindowSizeCallback(m_GlfwWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowProperties* winProps = static_cast<WindowProperties*>(glfwGetWindowUserPointer(window));

			winProps->Width = width;
			winProps->Height = height;

			WindowResizeEvent evt(width, height);
			winProps->Callback(evt);
		});

		return true;
	}

	void Window::Shutdown() 
	{
		glfwDestroyWindow(m_GlfwWindow);
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwPollEvents();
	}

	void Window::SetVSync(bool enabled)
	{
		m_Properties.VSyncEnabled = enabled;
	}

	void Window::SetEventCallback(const EventCallbackFunc& callback)
	{
		m_Properties.Callback = callback;
	}

	void Window::SetProperties(const WindowProperties& windowProps)
	{
		m_Properties.Title = windowProps.Title;
		m_Properties.Width = windowProps.Width;
		m_Properties.Height = windowProps.Height;
		m_Properties.Fullscreen = windowProps.Fullscreen;
		m_Properties.VSyncEnabled = windowProps.VSyncEnabled;
		m_Properties.Callback = windowProps.Callback;
	}

	void Window::SetTitle(const std::string & title)
	{
		glfwSetWindowTitle(m_GlfwWindow, title.c_str());
	}

	void Window::SetTitle(const char* title)
	{
		glfwSetWindowTitle(m_GlfwWindow, title);
	}

	bool Window::IsVSync() const
	{
		return m_Properties.VSyncEnabled;
	}

}
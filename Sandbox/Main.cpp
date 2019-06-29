#include "Application.h"
#include "EntryPoint.h"
#include "WindowProperties.h"

#define WIDTH 1500
#define HEIGHT 900

class Sandbox : public Hurricane::Application {
public:
	Sandbox() 
		: Hurricane::Application()
	{
		Hurricane::WindowProperties props("Sandbox Game", WIDTH, HEIGHT);
		m_Window->Init(props);
	}

	~Sandbox() {}
};

Hurricane::Application* Hurricane::CreateApplication()
{
	return new Sandbox();
}
#include "Application.h"
#include "EntryPoint.h"

class Sandbox : public Hurricane::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

Hurricane::Application* Hurricane::CreateApplication() 
{
	return new Sandbox();
}

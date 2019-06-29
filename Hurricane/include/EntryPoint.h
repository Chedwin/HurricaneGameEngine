#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#include "Application.h"

int main(int argc, char** argv)
{
	Hurricane::Application* app = Hurricane::CreateApplication();
	app->Run();
	delete app;

	return 0;
}


#endif ENTRY_POINT_H

#ifndef ENTRY_POINT_H
#define ENTRY_POINT_H

#include "Application.h"

int main(int argc, char** argv)
{
	Hurricane::Application* appplication = Hurricane::CreateApplication();
	appplication->Run();
	delete appplication;

	return 0;
}


#endif ENTRY_POINT_H

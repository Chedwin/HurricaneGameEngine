#include <SDL.h>
#undef main

#include <Macro.h>
#include <Controller.h>
#include <ControllerManager.h>

int main(int argc, char** argv) 
{
	Controller* p1 = new Controller();
	Controller* p2 = new Controller();
	Controller* p3 = new Controller();
	Controller* p4 = new Controller();
	Controller* p5 = new Controller();

	CTRL_MANAGER->AddPlayer(p1);
	CTRL_MANAGER->AddPlayer(p2);
	CTRL_MANAGER->AddPlayer(p3);
	CTRL_MANAGER->AddPlayer(p4);

	CTRL_MANAGER->AddPlayer(p5);

	CTRL_MANAGER->RemovePlayer();

	delete p5;
	p5 = nullptr;

	GETCHAR();
	return 0;
}
#ifndef APP_H
#define APP_H

class App 
{
public:
	App();
	virtual ~App();

	virtual bool Init() = 0;
	virtual void Run() = 0;
};

#endif APP_H
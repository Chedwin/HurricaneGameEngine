#include "Game.h"
#include "OpenGLRenderer.h"
#include "ModelManager.h"

/// See the header file regarding unique_ptr
Game* Game::_gameInstance(nullptr);

Game* Game::GetGameInstance() 
{
	if (!_gameInstance) 
	{
		_gameInstance = new Game();
	}
	return _gameInstance;
}

Game::Game() :
	_isRunning(true), properties(nullptr), input(nullptr), renderer(nullptr), modelManager(nullptr),
	currentLevel(nullptr), levelToLoad(nullptr),
	fps(0.0f), frames(0), timeBetweenLastFrame(0.0f), timeSinceLastUpdate(0.0f), cam3D(nullptr)
{
	// EMPTY
}

Game::~Game() 
{
	DestroySystems(); // Clean up the game systems
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

hBOOL Game::InitSystems()
{
	// GAME TIME
	Clock::init(); // Start the global game clock
	gameTimer = new Timer();
	gameTimer->Start();


	// PROPERTIES
	properties = H_PROPERTIES;

	STRING name = properties->GetGeneralProperties()->gameName;

	hINT width = properties->GetVideoProperties()->screenWidth;
	hINT height = properties->GetVideoProperties()->screenHeight;
	hUINT fullscreen = properties->GetVideoProperties()->fullScreen;

	hINT master = properties->GetAudioProperties()->masterVolume;
	hINT music = properties->GetAudioProperties()->musicVolume;
	hINT sound = properties->GetAudioProperties()->soundVolume;

	// RENEDERER
	renderer = new OpenGLRenderer();
	if (!renderer->Init(name, width, height, fullscreen)) 
	{
		LOG->Error("RENDERER CANNOT BE INITIALIZED", __LINE__, __FILE__);
		return false;
	}

	// OTHER
	input = INPUT;
	physicsEngine = PHYSICS;
	modelManager = MODEL_MANAGER;

	//Model* myModel = new SimpleModel();
	//modelManager->modelResources.Add((STRING)"myModel", myModel);
	//modelManager->modelResources.Add((STRING)"myModel", myModel);

	//Model* myMo = new SimpleModel();



	// GAME CAMERA
	cam3D = new Camera(levelToLoad);
	cam3D->Init(width, height);



	LoadLevel(levelToLoad);

	return true;
}

void Game::DestroySystems()
{
	// REMEMBER: Don't have to delete singletons! (that are created w/ unique pointer)

	delete cam3D;
	cam3D = nullptr;

	delete gameTimer;
	gameTimer = nullptr;

	delete renderer;
	renderer = nullptr;
}

hBOOL Game::LoadLevel(Level* _level)
{
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::Run() 
{
	hBOOL init = InitSystems();

	if (!init) 
	{
		LOG->ConsoleError("GAME COULD NOT BE INITIALIZED");
		GETCHAR();
	}

	if (init) 
	{
		GameLoop();
	}
}

void Game::GameLoop() 
{
	SDL_Event evnt;

	while (_isRunning) 
	{
		// UPDATE CAMERA
		cam3D->Update();

		//// FPS CALCULATION ////
		hFLOAT startTicks = gameTimer->GetTimerTicks();
		gameTimer->UpdateTimer();

		CalculateFPS();
		static hINT frameCounter = 0;

		frameCounter++;
		if (frameCounter >= 10) {
			frameCounter = 0;
		}

		hFLOAT frameTicks = gameTimer->GetTimerTicks() - startTicks;

		if (1000.0f / MAX_FPS > frameTicks) 
		{
			SDL_Delay(1000.0f / MAX_FPS - frameTicks);
		}
		///////////////////////////


		while (SDL_PollEvent(&evnt)) 
		{
			input->ProcessInput(evnt);

			switch (evnt.type) 
			{
			case SDL_QUIT:
				_isRunning = false;
				break;
			}		
		}
		SDL_PumpEvents();


		EngineUpdate(timeSinceLastUpdate);

		PreRender();
		EngineRender();
	}
}


void Game::PreRender()
{
	
}

void Game::EngineRender() 
{
	GameRender();
	PostRender();
}

void Game::PostRender()
{
	renderer->SwapBuffers();
}

void Game::EngineUpdate(const hFLOAT _timeStep)
{
	GameUpdate(_timeStep);
}

void Game::CalculateFPS() 
{
	static const hINT NUM_SAMPLES = 100;
	static hFLOAT frameTimes[NUM_SAMPLES];
	static hINT currentFrame = 0;

	static hFLOAT prevTicks = gameTimer->GetTimerTicks();
	hFLOAT currTicks = gameTimer->GetTimerTicks();

	frameTime = currTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = frameTime;

	prevTicks = currTicks;

	hINT count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES) 
	{
		count = currentFrame;
	}
	else 
	{
		count = NUM_SAMPLES;
	}

	hFLOAT frameTimeAverage = 0;
	for (int i = 0; i < count; i++) 
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) 
	{
		fps = 1000.0f / frameTimeAverage;
	}
	else 
	{
		fps = MAX_FPS;
	}
}
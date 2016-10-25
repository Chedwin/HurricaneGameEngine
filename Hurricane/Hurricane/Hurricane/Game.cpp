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
	_isRunning(true), properties(nullptr), input(nullptr), renderer(nullptr),
	currentLevel(nullptr), levelToLoad(nullptr),
	fps(0.0f), frames(0), timeBetweenLastFrame(0.0f), timeSinceLastUpdate(0.0f)
{
	// EMPTY
}

Game::~Game() 
{
	DestroySystems(); // Clean up the game systems
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

hBOOL Game::InitEngine()
{
	// GAME TIME
	Clock::init(); // Start the global game clock
	gameTimer = new Timer();
	gameTimer->Start();

	/*timeSinceLastUpdate = SDL_GetTicks();*/

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

	LoadLevel(levelToLoad);

	return true;
}

// Clean up after ourselves
// REMEMBER: Don't have to delete singletons! (that are created w/ unique pointer)
void Game::DestroySystems()
{
	if (currentLevel) {
		delete currentLevel;
	}

	delete gameTimer;
	gameTimer = nullptr;

	delete renderer;
	renderer = nullptr;
}

hBOOL Game::LoadLevel(Level* _level)
{
	currentLevel = _level;
	//currentLevel->InitLevel();
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::Run() 
{
	hBOOL init = InitEngine();

	if (!init) 
	{
		LOG->ConsoleError("GAME COULD NOT BE INITIALIZED");
		GETCHAR();
	}

	if (init) 
	{
		// Allow the game to initialize its own special options
		InitGame(); 

		// Start the game loop
		GameLoop();
	}
}

void Game::GameLoop() 
{
	SDL_Event evnt;

	while (_isRunning) 
	{

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


		// CALCULATE DELTA-TIME
		timeSinceLastUpdate = SDL_GetTicks() - lastUpdateTime;

		// This is the timestep variable we'll use to 
		hFLOAT deltaTime = timeSinceLastUpdate / 1000.0f;

		// Set the last update time w/ ticks from "this" iteration of the game loop
		lastUpdateTime = SDL_GetTicks();


		// INPUT HANDLING LOOP w/ SDL EVENT
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


		// PASS OUR DELTA TIME TO OUR PHYSICS ENGINE
		physicsEngine->FixedUpdate(deltaTime);
		COUT << deltaTime << ENDL;


		// RENDER THE GAME
		PreRender();
		EngineRender();
	}
}


void Game::PreRender()
{
	renderer->Render();
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
	// TODO:
	// Update engine stuff before game-specific stuff

	// Now we can update the game
	GameUpdate(_timeStep);
}

// Calculate Frame rate based on ticks
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
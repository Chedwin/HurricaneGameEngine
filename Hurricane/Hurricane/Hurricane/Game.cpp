#include "Game.h"
#include "OpenGLRenderer.h"
//#include "ModelManager.h"


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
	_isRunning(true), gameWindow(nullptr),
	//properties(nullptr), input(nullptr), renderer(nullptr),
	//currentLevel(nullptr), levelToLoad(nullptr),
	fps(0.0f), timeSinceLastUpdate(0.0f)
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
	//// INIT SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// GAME TIME
	Clock::init(); // Start the global game clock
	gameTimer = new Timer();
	gameTimer->Start();

	// PROPERTIES
	hINT width = H_PROPERTIES->GetVideoProperties()->screenWidth;
	hINT height = H_PROPERTIES->GetVideoProperties()->screenHeight;
	hUINT fullscreen = H_PROPERTIES->GetVideoProperties()->fullScreen;

	hINT master = H_PROPERTIES->GetAudioProperties()->masterVolume;
	hINT music = H_PROPERTIES->GetAudioProperties()->musicVolume;
	hINT sound = H_PROPERTIES->GetAudioProperties()->soundVolume;

	// WINDOW
	gameWindow = new Window();
	gameWindow->Init(width, height, fullscreen);

	if (fullscreen) {
		SDL_SetWindowFullscreen(gameWindow->GetWindow(), SDL_WINDOW_FULLSCREEN);
	}


	// OPENGL RENDERER
	renderer = new OpenGLRenderer();

	return true;
}

// Clean up after ourselves
// REMEMBER: Don't have to delete singletons! (that are created w/ unique pointer)
void Game::DestroySystems()
{
	delete gameTimer;
	gameTimer = nullptr;

	delete renderer;
	renderer = nullptr;

	delete gameWindow;
	gameWindow = nullptr;

	SDL_Quit();
}

//hBOOL Game::LoadLevel(Level* _level)
//{
//	//currentLevel = _level;
//	//currentLevel->InitLevel();
//	return true;
//}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::Run()
{
	hBOOL init = InitEngine();

	if (!init)
	{
		Debug::ConsoleError("ENGINE INITIALIZATION FAILED", __FILE__, __LINE__);
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
			INPUT->ProcessInput(evnt);

			switch (evnt.type) {
			case SDL_QUIT:
				const SDL_MessageBoxButtonData buttons[] = {
					{ 0, 0, "Cancel" }, // (flags, buttonid, text)
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" }
				};

				const SDL_MessageBoxData messageboxdata = {
					SDL_MESSAGEBOX_INFORMATION, // flags
					NULL, // window
					"Quit", // window title
					"Are you sure you want to quit?", // message
					SDL_arraysize(buttons), // num of buttons
					buttons // buttons
				};

				hINT buttonid;
				if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
					SDL_Log("error displaying message box");
				}
				if (buttonid == 1) {
					_isRunning = false;
				}
				break;
			}
		}
		SDL_PumpEvents();


		// PASS OUR DELTA TIME TO OUR PHYSICS ENGINE
		//physicsEngine->FixedUpdate(deltaTime);

		// UPDATE THE GAME
		EngineUpdate(deltaTime);

		// RENDER
		PreRender();
		EngineRender();
	}
}

// UPDATE
void Game::EngineUpdate(const hFLOAT _timeStep)
{
	// TODO:
	// Update engine stuff before game-specific stuff

	// Now we can update the game
	GameUpdate(_timeStep);
}


// RENDER
void Game::PreRender()
{
	renderer->RenderPrimitive(PrimitiveType::TRIANGLES);
}
void Game::EngineRender()
{
	GameRender();
	PostRender();
}

void Game::PostRender()
{
	SDL_GL_SwapWindow(gameWindow->GetWindow());
	glFlush();
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
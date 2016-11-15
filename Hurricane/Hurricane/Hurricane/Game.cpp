#include "Game.h"
#include "OpenGLRenderer.h"
#include "Hurricane.h"

Game* Game::_gameInstance(nullptr);

Game* Game::GetGameInstance() {
	if (!_gameInstance) {
		_gameInstance = new Game();
	}
	return _gameInstance;
}

Game::Game() :
	_isRunning(true), gameWindow(nullptr),
	_fps(0.0f), timeSinceLastUpdate(0.0f)
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

	_fpsCounter.Init(MAX_FPS);

	// PROPERTIES
	hProperties = H_PROPERTIES;

	hINT width = hProperties->GetVideoProperties()->screenWidth;
	hINT height = hProperties->GetVideoProperties()->screenHeight;
	hUINT fullscreen = hProperties->GetVideoProperties()->fullScreen;

	hINT master = hProperties->GetAudioProperties()->masterVolume;
	hINT music = hProperties->GetAudioProperties()->musicVolume;
	hINT sound = hProperties->GetAudioProperties()->soundVolume;

	// WINDOW
	gameWindow = new Window();
	gameWindow->Init(width, height, fullscreen);

	if (fullscreen) {
		SDL_SetWindowFullscreen(gameWindow->GetWindow(), SDL_WINDOW_FULLSCREEN);
	}

	// AUDIO
	audio = AUDIO;

	// INPUT
	input = INPUT;

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::GameLoop()
{
	SDL_Event evnt;

	while (_isRunning)
	{
		// BEGIN FPS COUNT FOR THIS FRAME
		_fpsCounter.BeginFrame();

		// CALCULATE DELTA-TIME
		timeSinceLastUpdate = SDL_GetTicks() - lastUpdateTime;

		// This is the timestep variable we'll use to 
		_deltaTime = timeSinceLastUpdate / 1000.0f;

		// Set the last update time w/ ticks from "this" iteration of the game loop
		lastUpdateTime = SDL_GetTicks();


		// INPUT HANDLING LOOP w/ SDL EVENT
		while (SDL_PollEvent(&evnt))
		{
			GameInput(evnt); // force the input to the game for now.....

			switch (evnt.type) {
			case SDL_KEYDOWN:
				input->PressKey(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				input->ReleaseKey(evnt.key.keysym.sym);
				break;
			case SDL_EventType::SDL_QUIT:
				QuitWindowPrompt();
				break;
			}
			
		}
		SDL_PumpEvents();


		// PASS OUR DELTA TIME TO OUR PHYSICS ENGINE
		PHYSICS->FixedUpdate(_deltaTime);

		// UPDATE THE GAME
		EngineUpdate(_deltaTime);

		// RENDER
		PreRender();
		EngineRender();


		// FRAME RATE UPDATE FOR THIS FRAME
		_fps = _fpsCounter.End();
		static hINT frameCounter = 0;
		frameCounter++;
		if (frameCounter >= 10) {
			frameCounter = 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// UPDATE
void Game::EngineUpdate(const hFLOAT _timeStep)
{
	// TODO:
	// Update engine stuff before game-specific stuff

	// Now we can update the game
	GameUpdate(_timeStep);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
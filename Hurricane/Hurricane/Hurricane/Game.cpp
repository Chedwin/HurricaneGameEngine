#include "Game.h"
#include "OpenGLRenderer.h"
#include "ModelManager.h"
/// See the header file regarding unique_ptr
UNIQUE_PTR(Game) Game::_gameInstance(nullptr);

Game* Game::GetGameInstance() 
{
	if (_gameInstance.get() == nullptr) 
	{
		_gameInstance.reset(new Game());
	}
	return _gameInstance.get();
}

Game::Game() :
	_isRunning(true), properties(nullptr), gameDebugLogger(nullptr), input(nullptr), renderer(nullptr), modelManager(nullptr),
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

bool Game::InitSystems()
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
	if (!renderer->Init(name, width, height, fullscreen)) {
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

	return true;
}

void Game::DestroySystems()
{
	// REMEMBER: Don't have to delete singletons! (that are created w/ unique pointer)

	delete gameTimer;
	gameTimer = nullptr;

	delete renderer;
	renderer = nullptr;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::Run() 
{
	hBOOL init = InitSystems();

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
		gameTimer->UpdateTimer();
		totalTime = gameTimer->SecondsPassed();

		timeSinceLastUpdate = gameTimer->GetTimerTicks() - lastUpdateTime;

		if (timeSinceLastUpdate > 300.0f) {
			timeSinceLastUpdate = 300.0f;
		}

		lastUpdateTime = gameTimer->GetTimerTicks();

		while (SDL_PollEvent(&evnt)) 
		{
			input->TakeEvent(evnt);

			switch (evnt.type) 
			{
			case SDL_QUIT:
				_isRunning = false;
				break;
			}		
		}
		SDL_PumpEvents();


		EngineUpdate(2.0f);

		PreRender();
		EngineRender();
	}
}


void Game::PreRender()
{
	
}

void Game::EngineRender() 
{
	hUINT updateTime = gameTimer->GetTimerTicks();

	timeSinceLastUpdate = updateTime;
	frames++;

	if (frames >= 10) 
	{
		fps = frames / (hFLOAT)(updateTime - timeSinceLastFPSUpdate) * 1000.0f;
		frames = 0;
		timeSinceLastFPSUpdate = updateTime;
	}

	GameRender();
	PostRender();
}

void Game::PostRender()
{
	renderer->SwapBuffers();
}

void Game::EngineUpdate(const hFLOAT _timeStep)
{

}
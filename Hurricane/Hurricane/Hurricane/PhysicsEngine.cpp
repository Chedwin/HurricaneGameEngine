#include "PhysicsEngine.h"
#include "Debug.h"

// Static fields
UNIQUE_PTR(PhysicsEngine) PhysicsEngine::_physicsEngine = nullptr;
hBOOL PhysicsEngine::isPhysicsRunning = false;


PhysicsEngine * PhysicsEngine::GetPhysicsEngine()
{
	if (_physicsEngine.get() == nullptr) {
		_physicsEngine.reset(new PhysicsEngine());
	}
	return _physicsEngine.get();
}

/////////////////////////////////////////////////
PhysicsEngine::PhysicsEngine()
{
	// Init the gravity 
	gravity = GRAVITY;
	isPhysicsRunning = true;
}

PhysicsEngine::~PhysicsEngine()
{
	// EMPTY
}

///////////////////////////////////////////////////////////////////////////////////////////////
void PhysicsEngine::FixedUpdate(const hFLOAT _timeStep) 
{
	lastTimeStep = _timeStep;

	if (isPhysicsRunning) 
	{
		// TODO: Collision Response
	}
}
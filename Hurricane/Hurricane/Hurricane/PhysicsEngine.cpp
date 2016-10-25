#include "PhysicsEngine.h"
#include "DebugLog.h"

UNIQUE_PTR(PhysicsEngine) PhysicsEngine::_physicsEngine = nullptr;

PhysicsEngine * PhysicsEngine::GetPhysicsEngine()
{
	if (_physicsEngine.get() == nullptr) {
		_physicsEngine.reset(new PhysicsEngine());
	}
	return _physicsEngine.get();
}

hBOOL PhysicsEngine::isPhysicsRunning = true;

PhysicsEngine::PhysicsEngine() 
{
}

PhysicsEngine::~PhysicsEngine()
{
	
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
hBOOL PhysicsEngine::InitPhysics() 
{
	return true;
}

void PhysicsEngine::FixedUpdate(const hFLOAT _timeStep)
{
	
}
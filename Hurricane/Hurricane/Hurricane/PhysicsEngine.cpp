#include "PhysicsEngine.h"

UNIQUE_PTR(PhysicsEngine) PhysicsEngine::_physicsEngine = nullptr;

PhysicsEngine * PhysicsEngine::GetPhysicsEngine()
{
	if (_physicsEngine.get() == nullptr) {
		_physicsEngine.reset(new PhysicsEngine());
	}
	return _physicsEngine.get();
}




PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}
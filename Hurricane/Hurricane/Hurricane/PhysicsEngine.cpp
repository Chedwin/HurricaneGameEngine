#include "PhysicsEngine.h"
#include "Debug.h"

// Static fields
UNIQUE_PTR(PhysicsEngine) PhysicsEngine::_physicsEngine = nullptr;
hBOOL PhysicsEngine::isPhysicsRunning = false;


PhysicsEngine* PhysicsEngine::GetPhysicsEngine()
{
	if (_physicsEngine.get() == nullptr) {
		_physicsEngine.reset(new PhysicsEngine());
	}
	return _physicsEngine.get();
}

/////////////////////////////////////////////////
PhysicsEngine::PhysicsEngine()
{
	lastTimeStep = 0.0f;
	isPhysicsRunning = true;
}

PhysicsEngine::~PhysicsEngine()
{
	physicsObjects.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////
void PhysicsEngine::FixedUpdate(const hFLOAT _timeStep) 
{
	lastTimeStep = _timeStep;

	if ((isPhysicsRunning == true) && (physicsObjects.size() > 0)) 
	{
		// TODO: Collision detection
		for (auto iter = physicsObjects.begin(); iter != physicsObjects.end(); iter++)
		{
			RigidbodyComponent* rb = (*iter);
			if (rb && rb->checkEnabled()) {

			}
		}

		// TODO: Forces & Impulses
	}
}
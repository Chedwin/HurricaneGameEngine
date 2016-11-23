//*******************************//
//
// Name:			PhysicsEngine.h
// Description:		Defines the physics manager.
//					Handles the updating of collision detection, gravity, and forces.
//
// Author:			Edwin Chen
// Created:			Sep 27, 2016
// Last updated:	Nov 11, 2016
//
//*******************************//

#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "Macro.h"
#include "HMath.h"
#include "RigidbodyComponent.h"

#define PHYSICS PhysicsEngine::GetPhysicsEngine()
#define GRAVITY VEC3(0.0f, -9.8f, 0.0f)

class PhysicsEngine {
	friend class Game;
protected:
	PhysicsEngine();

	inline void SetPhysicRunning(hBOOL b) {
		isPhysicsRunning = b;
	}

public:
	~PhysicsEngine();

	static PhysicsEngine* GetPhysicsEngine();

	void FixedUpdate(const hFLOAT _timeStep);

	inline hFLOAT GetTimeStep() const {
		return lastTimeStep;
	}
	

protected:
	static UNIQUE_PTR(PhysicsEngine) _physicsEngine;
	friend DEFAULT_DELETE(PhysicsEngine);

public:
	const VEC3 gravity = GRAVITY;
	hFLOAT lastTimeStep;
	static hBOOL isPhysicsRunning;

	VECTOR(RigidbodyComponent*) physicsObjects;
};

#endif
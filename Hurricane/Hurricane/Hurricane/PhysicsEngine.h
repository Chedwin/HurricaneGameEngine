//*******************************//
//
// Name:			PhysicsEngine.h
// Description:		Defines the physics manager
//
// Author:			Edwin Chen
// Created:			Sep 27, 2016
// Last updated:	Oct 24, 2016
//
//*******************************//

#pragma once

#include "Macro.h"
#include <btBulletDynamicsCommon.h>


#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#define PHYSICS PhysicsEngine::GetPhysicsEngine()

class PhysicsEngine {
protected:
	PhysicsEngine();
public:
	~PhysicsEngine();

	static PhysicsEngine* GetPhysicsEngine();

	hBOOL InitPhysics();

	void FixedUpdate(const hFLOAT _timeStep);

protected:
	static UNIQUE_PTR(PhysicsEngine) _physicsEngine;
	friend DEFAULT_DELETE(PhysicsEngine);
public:
	static hBOOL isPhysicsRunning;

};

#endif
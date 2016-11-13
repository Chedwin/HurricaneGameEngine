//*******************************//
//
// Name:			Scene.h
// Description:		Establishes an abstract "Scene" class for all types of Scene to use.
//
// Author:			Edwin Chen
// Created:			Mar 22, 2016
// Last updated:	Nov 12, 2016
//
//*******************************//

#ifndef SCENE_H
#define SCENE_H

#include "Macro.h"
#include "HMath.h"
#include "Camera.h"

// forward declare the Game Scene Manager
class GameSceneManager;

class Scene {
	friend class GameSceneManager;
public:
	explicit Scene() {}
	virtual ~Scene() {}

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	inline STRING GetSceneName() const {
		return _name;
	}

protected:
	STRING _name;
public:
};


#endif
//*******************************//
//
// Name:			Scene.h
// Description:		Establishes an abstract "Scene" class for all types of Scene to use.
//					Contains a root game object that begins the start of the "scene graph"
//
// Author:			Edwin Chen
// Special Thanks:  Unity, Aidan Dearing
//					
//
// Created:			Mar 22, 2016
// Last updated:	Nov 17, 2016
//
//*******************************//

#ifndef SCENE_H
#define SCENE_H

#include "Macro.h"
#include "HMath.h"
#include "Camera.h"
#include "SceneGraph.h"

// forward declare the Game Scene Manager
class Game;

class Scene {
	friend class Game;
public:
	explicit Scene();
	virtual ~Scene();

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	inline STRING GetSceneName() const {
		return _name;
	}
	inline void SetSceneName(const STRING& n) {
		_name = n;
	}

protected:
	STRING _name;
	Camera* _mainCamera;
public:
	GameObject* rootNode;
	UNORDERED_MAP(STRING, GameObject*) sceneMap;
};


#endif
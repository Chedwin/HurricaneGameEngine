//*******************************//
//
// Name:			Scene.h
// Description:		Establishes an abstract "Scene" class for all types of Scene to use.
//					Contains a root game object that begins the start of the "scene graph"
//
// Author:			Edwin Chen
// Special Thanks:  Unity, Aidan Dearing, Mark Seaman
//					
//
// Created:			Mar 22, 2016
// Last updated:	Nov 18, 2016
//
//*******************************//

#ifndef SCENE_H
#define SCENE_H

#include "Macro.h"
#include "HMath.h"
#include "GameObject.h"
#include "Camera.h"
#include "SceneGraph.h"

// forward declare the Game Scene Manager
class Game;

class Scene {
	friend class Game;
public:
	Scene();
	virtual ~Scene();

	virtual void InitScene() = 0;
	virtual void Update(const hFLOAT _timeStep) = 0;
	virtual void Render() = 0;

	inline STRING GetSceneName() const {
		return _name;
	}
	inline void SetSceneName(const STRING& n) {
		_name = n;
	}

	void AddSceneNode(GameObject* g, const STRING& name="");
	void RemoveSceneNode(const STRING& gName);
	void RemoveAllSceneNodes();
	GameObject* GetSceneNode(const STRING& name);

	inline hINT GetNumSceneNodes() const {
		return sceneGraph.size();
	}

protected:
	STRING _name;
public:
	Camera* mainCamera;
	Camera* currentCamera;

	GameObject* rootNode;
	UNORDERED_MAP(STRING, GameObject*) sceneGraph;
};


#endif
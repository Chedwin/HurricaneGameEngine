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
// Last updated:	Nov 21, 2016
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

//#define ROOT_NODE Scene::_rootNode.get()

class Scene {
	friend class Game;
public:
	Scene();
	virtual ~Scene();

	virtual void InitScene() = 0;
	virtual void Update(const hFLOAT _timeStep) = 0;
	virtual void Render() = 0;

	void SetCamera(Camera* _c);


	void AddSceneNode(GameObject* g);
	void RemoveSceneNode(const STRING& gName);
	void ClearAllSceneNodes();

	GameObject* FindSceneNode(const STRING& name);
	GameObject* FindSceneNode(GameObject* g);


	inline STRING GetSceneName() const {
		return _name;
	}
	inline void SetSceneName(const STRING& n) {
		_name = n;
	}
	inline hINT GetSceneSize() const {
		return _rootNode->childObjects.size();
	}


protected:
	STRING _name;
	UNIQUE_PTR(GameObject) _rootNode; // NOTE: the root node IS the scene graph
	friend DEFAULT_DELETE(GameObject);
public:
	Camera* mainCamera;
	Camera* currentCamera;

};


#endif
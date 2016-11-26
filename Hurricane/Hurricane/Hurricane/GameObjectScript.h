//*******************************//
//
// Name:			GameObjectScript.h
// Description:		Allows a way for game objects to implement and execute individual behaviours.
//					To create a new script:
//						1) Create a new class deriving from GameObjectScript 
//							(i.e. class PlayerMovement : public GameObjectScript)
//						2) Override the UpdateScript() function
//						3) Add in any "initial" of starting behaviours in your child class constructor
//						4) Add any new functions and called them appropriately in you UpdateScript function
//						5) Instantiate a script inside of a game scene's constructor
//						6) Attach said script to a game object
//
//					This scripting behaviour was highly influenced by MonoBehavior from Unity
//
// Author:			Edwin Chen
// Special Thanks:	Unity
//
// Created:			Nov 21, 2016
// Last updated:	Nov 25, 2016
//
//*******************************//


#ifndef GAME_OBJECT_SCRIPT_H
#define GAME_OBJECT_SCRIPT_H

#include "Macro.h"

class GameObject;

class GameObjectScript {
public:
	explicit GameObjectScript(const STRING& n);
	virtual ~GameObjectScript();

	virtual hBOOL UpdateScript(GameObject* gameObject, const hFLOAT _timeStep);

	inline STRING GetName() {
		return _scriptName;
	}
	inline void SetName(const STRING& n) {
		_scriptName = n;
	}

protected:
	STRING _scriptName;
public:
	typedef FUNCTION(hBOOL(GameObject*, hFLOAT)) ScriptLambda;
	ScriptLambda		userUpdateFunction = nullptr;

};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class GameObjectMultiScript {
public:
	GameObjectMultiScript();
	~GameObjectMultiScript();

	void AddScript(const STRING& n, GameObjectScript* script);
	void DeleteScript(const STRING& n);
	void ClearAllScripts();

	hBOOL UpdateAllScripts(GameObject* gameObject, const hFLOAT _timeStep);
public:
	MAP(STRING, GameObjectScript*) scriptMap;
};

#endif
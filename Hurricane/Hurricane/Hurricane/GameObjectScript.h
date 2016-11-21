//*******************************//
//
// Name:			GameObjectScript.h
// Description:		
//
// Author:			Edwin Chen
//
// Created:			Nov 21, 2016
// Last updated:	Nov 21, 2016
//
//*******************************//


#ifndef GAME_OBJECT_SCRIPT_H
#define GAME_OBJECT_SCRIPT_H

#include "Macro.h"

class GameObject;

class GameObjectScript {
public:
	GameObjectScript(const STRING& n);
	~GameObjectScript();

	virtual hBOOL UpdateScript(GameObject* gameObject, const hFLOAT _timeStep);

public:
	typedef FUNCTION(hBOOL(GameObject*, hFLOAT)) ScriptLambda;
	ScriptLambda		userFunction = nullptr;
	STRING scriptName;
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
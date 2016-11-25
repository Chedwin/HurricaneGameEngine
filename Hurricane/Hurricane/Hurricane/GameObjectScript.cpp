#include "GameObjectScript.h"

GameObjectScript::GameObjectScript(const STRING& n)
{
	scriptName = n;
}

GameObjectScript::~GameObjectScript()
{
	// EMPTY
}


hBOOL GameObjectScript::UpdateScript(GameObject * gameObject, const hFLOAT _timeStep)
{
	if (userUpdateFunction) {
		return userUpdateFunction(gameObject, _timeStep);
	}
	return true;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameObjectMultiScript::GameObjectMultiScript()
{
	// EMPTY
}

GameObjectMultiScript::~GameObjectMultiScript()
{
	ClearAllScripts();
}

void GameObjectMultiScript::AddScript(const STRING& n, GameObjectScript* script)
{
	auto f = scriptMap.find(n);

	script->scriptName = n;
	if (f != scriptMap.end()) {
		scriptMap.insert(PAIR(STRING, GameObjectScript*)(n, script));
	}
}

void GameObjectMultiScript::DeleteScript(const STRING& n)
{
	auto f = scriptMap.find(n);

	if (f != scriptMap.end()) {
		delete f->second;
		scriptMap.erase(f->first);
	}
}

void GameObjectMultiScript::ClearAllScripts() 
{
	if (scriptMap.size() > 0)
	{
		MAP(STRING, GameObjectScript*)::iterator iter = scriptMap.begin();

		for (iter = scriptMap.begin(); iter != scriptMap.end(); iter++)
		{
			delete iter->second;
		}
	}
	scriptMap.clear();
}

hBOOL GameObjectMultiScript::UpdateAllScripts(GameObject* gameObject, const hFLOAT _timeStep)
{
	hBOOL result = true;

	MAP(STRING, GameObjectScript*)::iterator iter = scriptMap.begin();

	for (iter = scriptMap.begin(); (iter != scriptMap.end()) && result; iter++)
	{
		auto temp = iter->second;
		result = temp->UpdateScript(gameObject, _timeStep);
	}

	return result;
}

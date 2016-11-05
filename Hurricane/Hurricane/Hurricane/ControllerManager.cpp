#include "ControllerManager.h"
#include "Debug.h"


UNIQUE_PTR(ControllerManager) ControllerManager::_ctrlManager(nullptr); // Declare static unique pointer

ControllerManager* ControllerManager::GetCtrlManager() {
	if (_ctrlManager.get() == nullptr) {
		_ctrlManager.reset(new ControllerManager());
	}
	return _ctrlManager.get();
}


ControllerManager::ControllerManager()
{
	_ctrlList.reserve(MAX_PLAYERS);
	_numPlayers = 0;
}

ControllerManager::~ControllerManager()
{
	if (_ctrlList.size() > 0) {
		for (int i = 0; i < _ctrlList.size(); i++) {
			delete _ctrlList[i];
			_ctrlList[i] = nullptr;
		}
	}
	_ctrlList.clear();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Controller* ControllerManager::GetPlayerCtrl(PLAYER_NUM _player)
{
	Controller* temp = _ctrlList[_player - 1];

	if (!temp) {
		Debug::ConsoleError("Player not connected", __FILE__, __LINE__);
		return nullptr;
	}

	return temp;
}

void ControllerManager::AddPlayer(Controller* _cont) 
{
	if (_ctrlList.size() == MAX_PLAYERS) {
		Debug::ConsoleError("Max amount of controllers plugged in is full.", __FILE__, __LINE__);
		return;
	}

	//if (_ctrlList[_numPlayers] != nullptr) {
	//	Debug::ConsoleError("Controller already exists.", __FILE__, __LINE__);
	//	return;
	//}

	_ctrlList.push_back(_cont);
	_numPlayers++;
}

void ControllerManager::RemovePlayer() 
{
	if (_ctrlList.size() == 0) {
		Debug::ConsoleError("No external gamepads are connected.", __FILE__, __LINE__);
		return;
	}

	_ctrlList.pop_back();
	_numPlayers--;
}
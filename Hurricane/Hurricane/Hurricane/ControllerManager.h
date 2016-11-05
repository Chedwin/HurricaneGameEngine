//*******************************//
//
// Name:			ContollerManager.h
// Description:		Manages multiple controller (gamepad) inputs.
//					Maximum of 4 players per game (if enabled)
//
//					Note: (Nov 05, 2016) - I don't think this manager SHOULD be used very much at this stage
//									     - For now, only 1 player should be connected to the game
//
// Author:			Edwin Chen
// Created:			Nov 05, 2016
// Last updated:	Nov 05, 2016
//
//*******************************//

#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include "Macro.h"
#include "Controller.h"

#define CTRL_MANAGER ControllerManager::GetCtrlManager()
#define MAX_PLAYERS 4

class ControllerManager {
protected:
	ControllerManager();
	~ControllerManager();
public:
	enum PLAYER_NUM : hINT {
		NONE = 0,
		PLAYER_1 = 1,
		PLAYER_2 = 2,
		PLAYER_3 = 3,
		PLAYER_4 = 4
	};

	static ControllerManager* GetCtrlManager();

	Controller* GetPlayerCtrl(PLAYER_NUM _player);

	// Sequentially add the next player to the list
	void AddPlayer(Controller* _cont);


	// Remove the player at the back of the list
	void RemovePlayer();
	void RemovePlayer(PLAYER_NUM _player);

	inline hINT GetNumPlayers() const {
		return (hINT)_ctrlList.size();
	}

protected:
	// List of all controllers connected (Limit of 4)
	VECTOR(Controller*) _ctrlList;

	// how many players are currently connected?
	hINT _numPlayers; 

	static UNIQUE_PTR(ControllerManager) _ctrlManager;
	friend DEFAULT_DELETE(ControllerManager);
};

#endif
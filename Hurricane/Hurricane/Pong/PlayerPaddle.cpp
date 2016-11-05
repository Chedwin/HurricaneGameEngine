#include <Debug.h>
#include <InputHandler.h>
#include "PlayerPaddle.h"

PlayerPaddle::PlayerPaddle() : GameObject() 
{
	gameObject = this; // change the instance pointer reference
}

void PlayerPaddle::Update(const hFLOAT _deltaTime) 
{
	
}
#ifndef PLAYER_PADDLE_H
#define PLAYER_PADDLE_H

#include <Macro.h>
#include <GameObject.h>

class PlayerPaddle : public GameObject
{
public:
	PlayerPaddle();
	~PlayerPaddle() {}

	void Update(const hFLOAT _deltaTime) override;
};

#endif
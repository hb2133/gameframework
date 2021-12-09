#pragma once
#include "SDLGameObject.h"
#include <vector>
#include "GameObject.h"
#include "Player.h"

class Enemy : public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	int getHp() { return hp; }


private:
	int o_L;
	int o_R;
	int o_T;
	int o_B;
	void gravity(float g_power);
	void checkCollision();
	void move();
	int p_PosX;
	int hp;

};
#pragma once
#include "SDLGameObject.h"
#include <vector>
#include "GameObject.h"

class Bullet : public SDLGameObject
{
public:
	Bullet(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	void look();
	void DeleteBullet();
	void checkCollision();

	//int bullet_num; //ÃÑ¾Ë ¹øÈ£

private:
	int mouseX;
	int mouseY;
	bool bullet_flip;
	int moveSpeed = 5;
};
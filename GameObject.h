#pragma once
#include "LoaderParams.h"

class GameObject
{
public:
	GameObject() {};
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual ~GameObject() {}

protected:
	GameObject(const LoaderParams* pParams) {}
};
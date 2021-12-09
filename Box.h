#pragma once
#include "SDLGameObject.h"

class Box : public SDLGameObject
{
public:
	Box(const LoaderParams* pParams);
	virtual void draw();
	virtual void clean();

};
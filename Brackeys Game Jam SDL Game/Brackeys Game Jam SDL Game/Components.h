#pragma once
#include <SDL.h>

#include "ECS.h"

class positionComponent : public Component
{
private:
	int xpos = 0;
	int ypos = 0;
public:
	int x()
	{
		return xpos;
	}
	int y()
	{
		return ypos;
	}

	void init() override
	{
		xpos = 0;
		ypos = 0;
	}

	void update() override
	{
		xpos++;
		ypos++;
	}

	void setPosition(int x, int y)
	{
		xpos = x;
		ypos = y;
	}
};

#pragma once
#include "InputHandler.h"
#include <math.h>

class Controller :
	public InputHandler
{
public:

	float gravity;
	float angle;
	float push;

	Controller();
	~Controller();


	virtual void update(SDL_Event* event);


};

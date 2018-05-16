#pragma once
#include <SDL.h>
#include "Character.h"


class InputHandler
{
public:
	Character* character;


	InputHandler();
	~InputHandler();

	virtual void update(SDL_Event* event) = 0;

};


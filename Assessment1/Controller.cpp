#include "Controller.h"


Controller::Controller()
{
}


Controller::~Controller()
{
}

void Controller::update(SDL_Event* event)
{
	gravity = 2000; //accumulates as pixels per second
	angle = 0;
	push = 270;

	//button presses for our hero
	if (event->type == SDL_KEYDOWN)
	{
		//reset hero position if press R
		if (event->key.keysym.scancode == SDL_SCANCODE_R)
		{
			character->pos.x = 200;
			character->pos.y = 200;

		}
		//TODO add attacks or other actions here for button presses
	}

	//check if a button is held down

	//first get state of all keyboard buttons(1 pressed, 0 not pressed)
	const Uint8 *keystates = SDL_GetKeyboardState(NULL); //you can pass it a smaller array, or null to return all keys
	//if holding up key
	if (keystates[SDL_SCANCODE_UP])
	{
		character->velocity.y = -5000;
		//character->velocity.y += (push*sin(angle / 180 * M_PI)) + gravity*dt;
	}

	//left
	if (keystates[SDL_SCANCODE_LEFT])
		character->velocity.x = -20;
	//right
	if (keystates[SDL_SCANCODE_RIGHT])
		character->velocity.x = 20;
	//check if none are held down
	if (!keystates[SDL_SCANCODE_LEFT] && !keystates[SDL_SCANCODE_RIGHT])
	{
		character->velocity.x = 0;
	}
}
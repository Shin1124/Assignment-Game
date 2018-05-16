#include "Jump.h"


Jump::Jump()
{
	velocity.x = 0;
	velocity.y = 0;
	gravity = 2000; //accumulates as pixels per second
	angle = 0;
	push = 270;
}


Jump::~Jump()
{
}

void Jump::update(float dt)
{
	velocity.y += (push*sin(angle / 180 * M_PI)) + gravity*dt;

	updateMovement(dt);
}
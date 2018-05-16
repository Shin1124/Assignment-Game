#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}

void Character::setAnimation(Animation* animation)
{
	this->animation = animation;
}

void Character::update(float dt)
{
	//face direction based on velocity.x value
	if (velocity.x >= 0){
		faceRight = true;
	}
	if (velocity.x < 0){
		faceRight = false;
	}

	//use basic entity movement to move around
	updateMovement(dt);

	//update animations too
	animation->update(dt);
}

void Character::draw()
{
	if (animation != NULL)
	{
		if (faceRight)
			animation->draw(pos.x, pos.y);
		else
			animation->draw(pos.x, pos.y, true);
	}

}

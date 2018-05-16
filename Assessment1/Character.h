#pragma once
#include "Entity.h"
#include "Animation.h"


class Character :
	public Entity
{
private:
	Animation* animation = NULL;
	bool faceRight = true;


public:
	Character();
	~Character();

	void setAnimation(Animation* animation);

	virtual void update(float dt);
	virtual void draw();
};


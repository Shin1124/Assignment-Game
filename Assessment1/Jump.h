#pragma once
#include <math.h>
#include "Entity.h"

class Jump :
	public Entity
{
public:
	float gravity;
	float angle;
	float push;

	Jump();
	~Jump();

	void update(float dt);
};


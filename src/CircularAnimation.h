#pragma once
#include "animation.h"
class CircularAnimation :
	public Animation
{
public:
	CircularAnimation(void);
	~CircularAnimation(void);
	float center[3];
	float radius;
	float startang;
	float rotang;
};


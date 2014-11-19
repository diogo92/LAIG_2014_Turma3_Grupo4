#pragma once
#include "animation.h"
class CircularAnimation :
	public Animation
{
public:
	CircularAnimation(void);
	~CircularAnimation(void);
	void update(unsigned long t);
	void init(unsigned long t);
	void reset();
	void calcValues();
	void apply();
	cor center;
	float radius;
	float startang;
	float rotang;
	float stepAngle;
	float correction;
};


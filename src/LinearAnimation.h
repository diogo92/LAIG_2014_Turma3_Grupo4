#pragma once
#include "animation.h"
#include <vector>

using std::vector;

class LinearAnimation :
	public Animation
{
public:
	LinearAnimation(void);
	~LinearAnimation(void);
	vector<float *> control_points;
};


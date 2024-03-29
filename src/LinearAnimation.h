#pragma once
#include "animation.h"
#include <math.h>
#include <vector>

using std::vector;

class LinearAnimation :
	public Animation
{
public:
	LinearAnimation(void);
	~LinearAnimation(void);
	vector<cor> control_points;
	vector<cor> velocidades_segmentos;
	vector<float> angles;
	unsigned int segmento_atual;
	void update(unsigned long t);
	void init(unsigned long t);
	void reset();
	void apply();
	float sector;
	void calcValues();
};


#pragma once
#include <CGFobject.h>
#include <string>

using std::string;

struct cor{
	float x,y,z;
};

class Animation
{
public:
	Animation(void);
	~Animation(void);
	virtual void update(unsigned long t){};
	virtual void init(unsigned long t){};
	virtual void reset(){};
	virtual void calcValues(){};
	virtual void apply(){};
	string id;
	unsigned long animT;
	float span;
	unsigned long startTime;
	unsigned char doReset;
	bool ended;
	cor dT;
	float angle;
};


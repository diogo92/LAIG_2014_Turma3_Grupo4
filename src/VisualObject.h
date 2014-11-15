#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <string>
#include <CGFobject.h>

using std::string;

class VisualObject{
public:
	float tex_s,tex_t;
	VisualObject();
	virtual void update(unsigned long t){printf("");};
	virtual void draw(){printf("I'm a virtual function\n");};
	float matrix[16];
};

#endif
#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <string>
#include <CGFobject.h>

using std::string;

class VisualObject{
public:
	VisualObject();
	virtual void draw(){printf("I'm a virtual function\n");};
	float matrix[16];
};

#endif
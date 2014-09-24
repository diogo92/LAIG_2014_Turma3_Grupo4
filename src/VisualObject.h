#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <string>
#include <CGFobject.h>

using std::string;

class VisualObject: public CGFobject{
public:
	virtual void drawVisual(void);
	VisualObject();
	float matrix[16];
};

#endif
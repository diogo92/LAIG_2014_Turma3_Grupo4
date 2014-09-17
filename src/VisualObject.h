#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <string>
#include <CGFobject.h>

using std::string;

class VisualObject: public CGFobject{
public:
	int numLista;
	virtual void drawVisual(void);
	VisualObject();
	float matrix[4][4];
};

#endif
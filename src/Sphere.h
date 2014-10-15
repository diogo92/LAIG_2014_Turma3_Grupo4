#ifndef SPHERE_H
#define SPHERE_H

#include "VisualObject.h"

class Sphere : public VisualObject {
	int lados;
	int andares;
	float raio;
	GLUquadricObj *obj;
	public:
		Sphere(float raio, int slices, int stacks);
		~Sphere();
	    void draw();
};
	



#endif

#ifndef SPHERE_H
#define SPHERE_H

#include "VisualObject.h"

class Sphere : public VisualObject {
	int lados;
	int andares;
	int raio;
	GLUquadricObj *obj;
	public:
		Sphere(double raio, int slices, int stacks);
		~Sphere();
	    void draw();
};
	



#endif

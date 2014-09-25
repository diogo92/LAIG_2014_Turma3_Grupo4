#ifndef SPHERE_H
#define SPHERE_H

#include "VisualObject.h"

class Sphere : public VisualObject {
	int lados;
	int andares;
	int raio;
	public:
		Sphere(double raio, int slices, int stacks);
	    void draw();
};
	



#endif

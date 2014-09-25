#ifndef CYLINDER_H
#define CYLINDER_H

#include "VisualObject.h"

class Cylinder : public VisualObject {
	
	int lados;
	int andares;
	double raioBase;
	double raioTopo;
	double altura;
	public:
		Cylinder(double raioBase, double raioTopo, double altura, int slices, int stacks);
	    void draw();
		void drawTop();
		void drawBase();
};
	



#endif
